/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmPubMOm.c
    Description :
    History     :
      1.  qilili00145085  2008-10-30  Draft Enact
      2.  hanlufeng 41410   2009-05-05  BJ9D00629   透明命令的两个设置被明确的
                                        参数设置命令代替，不在透明命令中执行
      3.  zhengjunyan 00148421   2011-05-28 文件名由 NasMmPubMOm.c修改为
                                           NasLmmPubMOm.c
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
/*#include    "IpDhcpv4Server.h"*/
#include    "NasERabmIpFilter.h"
#include    "NasEmmSecuOm.h"
#include    "ImsaNvInterface.h"
#include    "SysNvId.h"

#include    "omringbuffer.h"
#include    "omnvinterface.h"
#if (VOS_WIN32 == VOS_OS_VER)
#include    "NasMmPubMTest.h"
#endif
#include    "NasEmmAttDetInclude.h"

#include    "TlPsDrv.h"

#include    "NasCommSndOm.h"

#include    "NasMmlCtx.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMOM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMOM_C
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
NAS_EMM_DRX_CYCLE_LEN_CHANGE_ENUM_UINT32    g_ulDrxCycleLenChange
                                            = NAS_EMM_DRX_CYCLE_LEN_NOT_CHANGED;
/*
static APP_MM_REPORT_MODE_ENUM_UINT32      g_ulMmInfoRptFlag = APP_MM_RM_AUTO;
static APP_EMM_INFO_STRU                   g_stAppEmmInfo = {0};
*/

#if (FEATURE_ON == FEATURE_PTM)
LNAS_ERRLOG_GLO_INFO_STRU  stErrlogGloInfo;
/* LNAS模块Error Log异常级别表 */
LNAS_ERRLOG_ALM_LEVEL_STRU g_astLNasErrAlmLevelTb[] = {
    {LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL,         LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL,            LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL,         LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL,    LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL,    LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL,         LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_RAT_FAIL,            LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_CONN_FAIL,   LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_DISCONN_FAIL,LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_RES_MOD_FAIL,    LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_RES_ALLOC_FAIL,  LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL,       LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL,   LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ,            LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE,   LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
};

LNAS_ERR_LOG_ALM_REPORT_TYPE_STRU   g_astLNasErrAlmUnsoliReportTypeTb[] = {
    {LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL,         EMM_ERR_LOG_ALARM_REPORT},
    {LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE,   EMM_ERR_LOG_ALARM_REPORT},
};


NAS_LMM_CN_CAUSE_TRANS_STRU          g_astEmmErrlogCnCauseMap[] =
{
    /*------------casue-----------------------------------error id---------------------------*/
    {NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS,                 EMM_OM_ERRLOG_CN_CAUSE_IMSI_UNKNOWN_IN_HSS},
    {NAS_LMM_CAUSE_ILLEGAL_UE,                          EMM_OM_ERRLOG_CN_CAUSE_ILLEGAL_UE},
    {NAS_LMM_CAUSE_IMEI_NOT_ACCEPTED,                   EMM_OM_ERRLOG_CN_CAUSE_IMEI_NOT_ACCEPTED},
    {NAS_LMM_CAUSE_ILLEGAL_ME,                          EMM_OM_ERRLOG_CN_CAUSE_ILLEGAL_ME},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW,                  EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_NOT_ALLOW},
    {NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW, EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW},
    {NAS_LMM_CAUSE_UE_ID_NOT_DERIVED,                   EMM_OM_ERRLOG_CN_CAUSE_UE_ID_NOT_DERIVED},
    {NAS_LMM_CAUSE_IMPLICIT_DETACHED,                   EMM_OM_ERRLOG_CN_CAUSE_IMPLICIT_DETACHED},
    {NAS_LMM_CAUSE_PLMN_NOT_ALLOW,                      EMM_OM_ERRLOG_CN_CAUSE_PLMN_NOT_ALLOW},
    {NAS_LMM_CAUSE_TA_NOT_ALLOW,                        EMM_OM_ERRLOG_CN_CAUSE_TA_NOT_ALLOW},
    {NAS_LMM_CAUSE_ROAM_NOT_ALLOW,                      EMM_OM_ERRLOG_CN_CAUSE_ROAM_NOT_ALLOW},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,          EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN},
    {NAS_LMM_CAUSE_NO_SUITABL_CELL,                     EMM_OM_ERRLOG_CN_CAUSE_NO_SUITABL_CELL},
    {NAS_LMM_CAUSE_MSC_UNREACHABLE,                     EMM_OM_ERRLOG_CN_CAUSE_MSC_UNREACHABLE},
    {NAS_LMM_CAUSE_NETWORK_FAILURE,                     EMM_OM_ERRLOG_CN_CAUSE_NETWORK_FAILURE},
    {NAS_LMM_CAUSE_CS_NOT_AVAIL,                        EMM_OM_ERRLOG_CN_CAUSE_CS_NOT_AVAIL},
    {NAS_LMM_CAUSE_ESM_FAILURE,                         EMM_OM_ERRLOG_CN_CAUSE_ESM_FAILURE},
    {NAS_LMM_CAUSE_MAC_FAILURE,                         EMM_OM_ERRLOG_CN_CAUSE_MAC_FAILURE},
    {NAS_LMM_CAUSE_SYNCH_FAILURE,                       EMM_OM_ERRLOG_CN_CAUSE_SYNCH_FAILURE},
    {NAS_LMM_CAUSE_PROCEDURE_CONGESTION,                EMM_OM_ERRLOG_CN_CAUSE_PROCEDURE_CONGESTION},
    {NAS_LMM_CAUSE_UE_SECU_CAP_MISMATCH,                EMM_OM_ERRLOG_CN_CAUSE_UE_SECU_CAP_MISMATCH},
    {NAS_LMM_CAUSE_SECU_MODE_REJECTED_UNSPECIFIED,      EMM_OM_ERRLOG_CN_CAUSE_SECU_MODE_REJECTED_UNSPECIFIED},
    {NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,         EMM_OM_ERRLOG_CN_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG},
    {NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN, EMM_OM_ERRLOG_CN_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN},
    {NAS_LMM_CAUSE_CS_FALLBACK_CALL_EST_NOT_ALLOWED,    EMM_OM_ERRLOG_CN_CAUSE_CS_FALLBACK_CALL_EST_NOT_ALLOWED},
    {NAS_LMM_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED,           EMM_OM_ERRLOG_CN_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED},
    {NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,     EMM_OM_ERRLOG_CN_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED},
    {NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE,              EMM_OM_ERRLOG_CN_CAUSE_SERVER_NETWORK_FAILURE},
    {NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG,          EMM_OM_ERRLOG_CN_CAUSE_SEMANTICALLY_INCORRECT_MSG},
    {NAS_LMM_CAUSE_INVALID_MANDATORY_INF,               EMM_OM_ERRLOG_CN_CAUSE_INVALID_MANDATORY_INFORMATION},
    {NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED,          EMM_OM_ERRLOG_CN_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT},
    {NAS_LMM_CAUSE_MSG_TYPE_NOT_COMPATIBLE,             EMM_OM_ERRLOG_CN_CAUSE_MSG_TYPE_NOT_COMPATIBLE},
    {NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE,          EMM_OM_ERRLOG_CN_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT},
    {NAS_LMM_CAUSE_CONDITIONAL_IE_ERROR,                EMM_OM_ERRLOG_CN_CAUSE_CONDITIONAL_IE_ERROR},
    {NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE,                  EMM_OM_ERRLOG_CN_CAUSE_MSG_NOT_COMPATIBLE},
    {NAS_LMM_CAUSE_PROTOCOL_ERROR,                      EMM_OM_ERRLOG_CN_CAUSE_PROTOCOL_ERROR},
};

static VOS_UINT32   g_astEmmErrlogCnCauseNum
        = sizeof(g_astEmmErrlogCnCauseMap)/sizeof(NAS_LMM_CN_CAUSE_TRANS_STRU);
#endif


static NAS_EMM_PROTOCOL_STATE_MAP_STRU g_astProtocolStateMap[] =
{
    /* 空状态 */
    { EMM_MS_NULL               ,     MM_SS_BUTT,      \
      APP_EMM_MS_NULL           ,     APP_EMM_SS_NULL                       },

    /* 去注册状态 */
    { EMM_MS_DEREG              ,     EMM_SS_DEREG_NORMAL_SERVICE,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_NORMAL_SERVICE       },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_LIMITED_SERVICE,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_LIMITED_SERVICE      },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_ATTEMPT_TO_ATTACH    },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_PLMN_SEARCH,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_PLMN_SEARCH          },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_NO_IMSI,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_NO_IMSI              },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_ATTACH_NEEDED,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_ATTACH_NEEDED        },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_NO_CELL_AVAILABLE,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_NO_CELL_AVAILABLE    },



    /* 注册状态 */
    { EMM_MS_REG                ,     EMM_SS_REG_NORMAL_SERVICE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_NORMAL_SERVICE         },

    { EMM_MS_REG                ,     EMM_SS_REG_ATTEMPTING_TO_UPDATE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_ATTEMPTING_TO_UPDATE   },

    { EMM_MS_REG                ,     EMM_SS_REG_LIMITED_SERVICE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_LIMITED_SERVICE        },

    { EMM_MS_REG                ,     EMM_SS_REG_PLMN_SEARCH,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_PLMN_SEARCH            },

    { EMM_MS_REG                ,     EMM_SS_REG_WAIT_ACCESS_GRANT_IND,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_WAIT_ACCESS_GRANT_IND},

    { EMM_MS_REG                ,     EMM_SS_REG_NO_CELL_AVAILABLE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_NO_CELL_AVAILABLE      },

    { EMM_MS_REG                ,     EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_ATTEMPT_TO_UPDATE_MM      },

    { EMM_MS_REG                ,     EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_IMSI_DETACH_WAIT_CN_DETACH_CNF      },



    /* 注册过程中 */
    { EMM_MS_REG_INIT           ,     MM_SS_BUTT,      \
      APP_EMM_MS_REG_INIT       ,     APP_EMM_SS_NULL                       },

    /* TAU过程中  */
    { EMM_MS_TAU_INIT           ,     MM_SS_BUTT,      \
      APP_EMM_MS_TAU_INIT       ,     APP_EMM_SS_NULL                       },

    /* SERVICE过程中 */
    { EMM_MS_SER_INIT           ,     MM_SS_BUTT,      \
      APP_EMM_MS_SER_INIT       ,     APP_EMM_SS_NULL                       },

    /* 去注册过程中 */
    { EMM_MS_DEREG_INIT         ,     MM_SS_BUTT,      \
      APP_EMM_MS_DEREG_INIT     ,     APP_EMM_SS_NULL                       }
};

static VOS_UINT32   g_ulProtocolStateMapNum
        = sizeof(g_astProtocolStateMap)/sizeof(NAS_EMM_PROTOCOL_STATE_MAP_STRU);

static  NAS_LMM_OM_ACT_STRU  g_astOmDataMap[] =
{
    /* APP_MM_MSG_TYPE_ENUM_UINT32      NAS_LMM_OM_ACTION_FUN */


    {ID_APP_MM_INQ_LTE_CS_REQ,         NAS_LMM_PubmDaInqLteCs},

    {ID_APP_MM_INQ_UE_MODE_REQ,         NAS_LMM_PubmDaInqUeMode},

    /* niuxiufan DT begin */
    {ID_APP_MM_INQ_LTE_GUTI_REQ,         NAS_LMM_PubmDaInqGuti},
    {ID_APP_MM_INQ_IMSI_REQ,             NAS_LMM_PubmDaInqImsi},
    {ID_APP_MM_INQ_EMM_STATE_REQ,        NAS_LMM_PubmDaInqEmmState},
    /* niuxiufan DT end */
};

static VOS_UINT32   g_astOmDataMapNum
        = sizeof(g_astOmDataMap)/sizeof(NAS_LMM_OM_ACT_STRU);


NAS_LMM_OM_MSG_ID_CHANGE_STRU g_stMmOmMsgIdStru[] =
{
    {0,NAS_EMM_CN_MT_ATTACH_ACP,    NAS_EMM_ATTACH_ACP,     EMM_OMT_KE_ATTACH_ACP},
    {0,NAS_EMM_CN_MT_ATTACH_REJ,    NAS_EMM_ATTACH_REJ,     EMM_OMT_KE_ATTACH_REJ},
    {0,NAS_EMM_CN_MT_DETACH_REQ_MT, NAS_EMM_DETACH_REQ_MT,  EMM_OMT_KE_DETACH_REQ_MT},
    {0,NAS_EMM_CN_MT_DETACH_ACP_MO, NAS_EMM_DETACH_ACP_MO,  EMM_OMT_KE_DETACH_ACP_MO},
    {0,NAS_EMM_CN_MT_TAU_ACP,       NAS_EMM_TAU_ACP,        EMM_OMT_KE_TAU_ACP},
    {0,NAS_EMM_CN_MT_TAU_REJ,       NAS_EMM_TAU_REJ,        EMM_OMT_KE_TAU_REJ},
    {0,NAS_EMM_CN_MT_SER_REJ,       NAS_EMM_SER_REJ,        EMM_OMT_KE_SER_REJ},
    {0,NAS_EMM_CN_MT_GUTI_CMD,      NAS_EMM_GUTI_CMD,       EMM_OMT_KE_GUTI_CMD},
    {0,NAS_EMM_CN_MT_AUTH_REQ,      NAS_EMM_AUTH_REQ,       EMM_OMT_KE_AUTH_REQ},
    {0,NAS_EMM_CN_MT_AUTH_RSP,      NAS_EMM_AUTH_RSP,       EMM_OMT_KE_AUTH_RSP},
    {0,NAS_EMM_CN_MT_AUTH_REJ,      NAS_EMM_AUTH_REJ,       EMM_OMT_KE_AUTH_REJ},
    {0,NAS_EMM_CN_MT_IDEN_REQ,      NAS_EMM_IDEN_REQ,       EMM_OMT_KE_IDEN_REQ},
    {0,NAS_EMM_CN_MT_SMC_CMD,       NAS_EMM_SECU_CMD,       EMM_OMT_KE_SECU_CMD},
    {0,NAS_EMM_CN_MT_SMC_CMP,       NAS_EMM_SECU_CMP,       EMM_OMT_KE_SECU_CMP},
    {0,NAS_EMM_CN_MT_EMM_STATUS,    NAS_EMM_STATUS,         EMM_OMT_KE_EMM_STATUS},
    {0,NAS_EMM_CN_MT_EMM_INFO,      NAS_EMM_INFO,           EMM_OMT_KE_EMM_INFO},
    {0,NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT, NAS_EMM_DOWNLINK_NAS_TRANSPORT, EMM_OMT_KE_EMM_DOWNLINK_NAS_TRANSPORT},
    {0,NAS_EMM_CN_CS_SER_NOTIFICATION, NAS_EMM_CS_SER_NOTIFICATION, EMM_OMT_KE_CS_SER_NOTIFICATION}
};
VOS_UINT32 g_ulSzieof_g_stMmOmMsgIdStru = sizeof(g_stMmOmMsgIdStru);

/*niuxiufan DT begin */
APP_MM_DT_REPORT_CTRL_STRU  gastNasDtRptCtrlTbl[NAS_DT_RPT_CTRL_MAX_ITEM_NUM] = {{0}};
VOS_UINT32                  g_ulNasEmmOmMsgHookFlag = 0;
/*niuxiufan DT end */

VOS_UINT32                  g_NasEmmOmInfoIndFlag = 0;

EMM_FTM_INFO_MANAGE_STRU             g_astEmmFtmInfoManage;
EMM_DATABASE_INFO_STRU               g_astEmmInfo;

APP_MM_DT_STRU                    g_stEmmDtInfo;
NAS_LMM_OM_ENTITY_STRU g_stEmmOmEntity;
NAS_LMM_ADD_ATTACH_COUNTER_TYPE_PROC_STRU g_stEmmAddAttachCounterProcTbl[] =
{
    {NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL,               NAS_LMM_AddAttachTotalCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_SUCC,                NAS_LMM_AddAttachSuccCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_BAR,                 NAS_LMM_AddAttachBarFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_NO_RF,               NAS_LMM_AddAttachNoRfFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL,            NAS_LMM_AddAttachEstFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EXP,                 NAS_LMM_AddAttachExpFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ,              NAS_LMM_AddAttachRejFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL,            NAS_LMM_AddAttachRelFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_ESM_FAIL,            NAS_LMM_AddAttachEsmFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL,       NAS_LMM_AddAttachDataReqFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL,         NAS_LMM_AddAttachOtherFailCounter}
};
VOS_UINT32        g_stEmmAddAttachCounterProcTblLen = sizeof(g_stEmmAddAttachCounterProcTbl)
                                                    / sizeof(NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_STRU);
/* 大数据: TAU计数动作表 */
NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_STRU g_stEmmAddTauCounterProcTbl[] =
{
    {NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL,               NAS_LMM_AddTauTotalCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_SUCC,                NAS_LMM_AddTauSuccCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_BAR,                 NAS_LMM_AddTauBarFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_NO_RF,               NAS_LMM_AddTauNoRfFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL,            NAS_LMM_AddTauEstFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EXP,                 NAS_LMM_AddTauExpFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ,              NAS_LMM_AddTauRejFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL,            NAS_LMM_AddTauRelFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL,       NAS_LMM_AddTauDataReqFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL,         NAS_LMM_AddTauOtherFailCounter}
};
VOS_UINT32        g_stEmmAddTauCounterProcTblLen = sizeof(g_stEmmAddTauCounterProcTbl)
                                                    / sizeof(NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_STRU);
/* 大数据: Ser计数动作表 */
NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_STRU  g_stEmmAddSerCounterProcTbl[] =
{
    {NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL,               NAS_LMM_AddSerTotalCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_SUCC,                NAS_LMM_AddSerSuccCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_BAR,                 NAS_LMM_AddSerBarFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_NO_RF,               NAS_LMM_AddSerNoRfFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL,            NAS_LMM_AddSerOtherEstFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EXP,                 NAS_LMM_AddSerExpFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ,              NAS_LMM_AddSerRejFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL,            NAS_LMM_AddSerRelFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL,       NAS_LMM_AddSerDataReqFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL,         NAS_LMM_AddSerOtherFailCounter}
};
VOS_UINT32  g_stEmmAddSerCounterProcTblLen = sizeof(g_stEmmAddSerCounterProcTbl)
                                                    / sizeof(NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_STRU);

LNAS_EXC_LOG_INFO_STRU  g_stLNasResetInfo;
/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_LMM_OmFindFun
 Description     : 查找对应的操作函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-4-15  Draft Enact

*****************************************************************************/


NAS_LMM_OM_ACTION_FUN  NAS_LMM_OmFindFun( VOS_UINT32          ulMsgId)
{
    VOS_UINT32                          i;
    NAS_LMM_OM_ACTION_FUN                pActFun = NAS_LMM_NULL_PTR;

    /* 在g_astNvDataMap中查找对应的NV TYPE*/
    for(i = 0; i < g_astOmDataMapNum; i++)
    {
        /* 若NV类型相同,则找到了,返回当前的NV动作函数，退出循环 */
        if(ulMsgId == g_astOmDataMap[i].ulMsgId)
        {
            pActFun            = g_astOmDataMap[i].pfFun;
            break;
        }
    }

    return  pActFun;
}

/*****************************************************************************
 Function Name   : NAS_LMM_OmCommFindFun
 Description     : OM通用的查找对应的操作函数
 Input           : aucActMap        : 动作表的首地址
                   ulMapElementNum  : 动作表的成员个数
                   ulMsgId          : 消息类型
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-4-15  Draft Enact

*****************************************************************************/
NAS_LMM_OM_ACTION_FUN  NAS_LMM_OmCommFindFun
(
    const NAS_LMM_OM_ACT_STRU           *aucActMap,
    VOS_UINT32                          ulMapElementNum,
    VOS_UINT32                          ulMsgId
)
{
    VOS_UINT32                          i;
    NAS_LMM_OM_ACTION_FUN                pActFun = NAS_LMM_NULL_PTR;

    /* 在aucActMap中查找对应的 ulMsgId */
    for(i = 0; i < ulMapElementNum; i++)
    {
        /* 若ulMsgId类型相同,则找到了,返回当前的ulMsgId动作函数，退出循环 */
        if(ulMsgId == aucActMap[i].ulMsgId)
        {
            pActFun = aucActMap[i].pfFun;
            break;
        }
    }

    return  pActFun;
}

/*****************************************************************************
 Function Name   : NAS_LMM_OmMaintain
 Description     : OM操作维护消息总入口
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.  qilili00145085  2008-10-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_OmMaintain( MsgBlock            *pMsg)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSrcMsgId;
    NAS_EMM_GENERAL_MSG_HEADER_STRU    *pstSrcMsg;
    NAS_LMM_OM_ACTION_FUN                pActFun = NAS_LMM_NULL_PTR;


    ulRet                               = NAS_LMM_MSG_DISCARD;
    pstSrcMsg                           = (NAS_EMM_GENERAL_MSG_HEADER_STRU*)pMsg;
    ulSrcMsgId                          = pstSrcMsg->ulMsgId;


    pActFun = NAS_LMM_OmFindFun(ulSrcMsgId);
    if (NAS_LMM_NULL_PTR != pActFun)
    {   /* 若这里找到了，就在这里执行APP的请求 */
        (*pActFun)(pMsg);
        ulRet = NAS_LMM_MSG_HANDLED;
    }
    else
    {
        /* 如果找不到处理函数，表示当前没有该处理函数 */
/*        NAS_LMM_PUBM_LOG_INFO("in NAS_LMM_OmFindFun, Action functin is NOT FOUND. ");*/

    }

    return  ulRet;

}
/*****************************************************************************
 Function Name   : NAS_EMM_OmInfoIndMsgProc
 Description     : 上报EMM信息的控制消息处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2013-06-21  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_OmInfoIndMsgProc( MsgBlock    *pMsg )
{
    OM_EMM_INFO_REPORT_REQ_STRU           *pMmOmInfoReqMsg;
    OM_EMM_INFO_REPORT_CNF_STRU           *pMmOmInfoCnfMsg;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_OmInfoIndMsgProc: enter !!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_OmInfoIndMsgProc_ENUM
,LNAS_ENTRY);

    pMmOmInfoReqMsg = (OM_EMM_INFO_REPORT_REQ_STRU *)pMsg;

    if (OM_EMM_INFO_REPORT_OPEN == pMmOmInfoReqMsg->enRptCtrl)
    {
        g_NasEmmOmInfoIndFlag = OM_EMM_REPORT_INFO_OPEN;
    }
    else
    {
        g_NasEmmOmInfoIndFlag = OM_EMM_REPORT_INFO_CLOSE;

    }
    /* 将保存上报信息的全局变量清除 */
    NAS_LMM_MEM_SET_S(&g_stEmmOmInfo, sizeof(OM_EMM_STATE_INFO_STRU), 0, sizeof(OM_EMM_STATE_INFO_STRU));

    /* 为消息分配地址 */
    pMmOmInfoCnfMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(OM_EMM_INFO_REPORT_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pMmOmInfoCnfMsg)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_OmInfoIndMsgProc: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_OmInfoIndMsgProc_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }


    /* 结构初始化 */
    NAS_LMM_MEM_SET_S(  pMmOmInfoCnfMsg,
                        sizeof(OM_EMM_INFO_REPORT_CNF_STRU),
                        0,
                        sizeof(OM_EMM_INFO_REPORT_CNF_STRU));


    /* 打包消息头 */
    pMmOmInfoCnfMsg->ulSenderCpuId = pMmOmInfoReqMsg->ulReceiverCpuId;
    pMmOmInfoCnfMsg->ulSenderPid     = pMmOmInfoReqMsg->ulReceiverPid;
    pMmOmInfoCnfMsg->ulReceiverPid   = pMmOmInfoReqMsg->ulSenderPid;
    pMmOmInfoCnfMsg->ulReceiverCpuId  = pMmOmInfoReqMsg->ulSenderCpuId;
    pMmOmInfoCnfMsg->ulLength = EMM_MSG_LENTH_NO_HEADER(OM_EMM_INFO_REPORT_CNF_STRU);
    /* OM融合，所有透传消息CNF和REQ中的usOriginalId和usTerminalId必须对应，不能颠倒 */
    pMmOmInfoCnfMsg->usOriginalId    = pMmOmInfoReqMsg->usOriginalId;
    pMmOmInfoCnfMsg->usTerminalId    = pMmOmInfoReqMsg->usTerminalId;
    pMmOmInfoCnfMsg->ulTimeStamp     = pMmOmInfoReqMsg->ulTimeStamp;
    pMmOmInfoCnfMsg->ulSN            = pMmOmInfoReqMsg->ulSN;


    /*设置OPID*/
    pMmOmInfoCnfMsg->ulOpId      = pMmOmInfoReqMsg->ulOpId;

    /*设置消息类型*/
    pMmOmInfoCnfMsg->ulMsgId     = ID_OM_EMM_INFO_REPORT_CNF;

    pMmOmInfoCnfMsg->ulRslt      = APP_SUCCESS;

    /* 发送消息 */
    NAS_LMM_SEND_MSG(pMmOmInfoCnfMsg);

    /* xiongxianghui 253310 FOR PCLINT  begin 20130926*/
    return NAS_LMM_MSG_HANDLED;
    /* xiongxianghui 253310 FOR PCLINT  end  20130926*/
}
/*****************************************************************************
 Function Name   : NAS_LMM_CompareEmmInfo
 Description     : 判断EMM模块维护且需要上报给HSO的信息是否发生变化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2013-06-21    Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_CompareEmmInfo( VOS_VOID )
{
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
    EMM_UPDATE_STATE_ENUM_UINT32    enEmmUpState;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32                   ulLteUeMode;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_CompareEmmInfo: enter !!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_CompareEmmInfo_ENUM,LNAS_ENTRY);

    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();
    /* 由EMM当前状态获取协议状态 */
    NAS_LMM_PubmGetEmmState(&ulProtoclMainState,
                            &ulProtoclSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());
    /* 获取EU值 */
    NAS_LMM_PubmGetEmmUpdateState(&enEmmUpState);

    if ((ulProtoclMainState != g_stEmmOmInfo.enMainState)
        || (ulProtoclSubState != g_stEmmOmInfo.enSubState))
    {
        g_stEmmOmInfo.enMainState = ulProtoclMainState;
        g_stEmmOmInfo.enSubState = ulProtoclSubState;
        ulRst = NAS_EMM_FAIL;
    }



    if (enEmmUpState != g_stEmmOmInfo.enEmmUpState)
    {
        g_stEmmOmInfo.enEmmUpState = enEmmUpState;
        ulRst = NAS_EMM_FAIL;
    }

    /* 比较GUTI信息 */
    if (NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&g_stEmmOmInfo.stGuti,
                                                    NAS_LMM_GetEmmInfoUeidGutiAddr(),
                                                    sizeof(NAS_MM_GUTI_STRU)))
    {
        NAS_LMM_MEM_CPY_S(  &g_stEmmOmInfo.stGuti,
                            sizeof(OM_GUTI_STRU),
                            NAS_LMM_GetEmmInfoUeidGutiAddr(),
                            sizeof(NAS_MM_GUTI_STRU));
        ulRst = NAS_EMM_FAIL;
    }

    /* 比较加密和完整性保护算法 */
    if ((NAS_EMM_GetSecuEca() != g_stEmmOmInfo.enAlgSecurity)
        || (NAS_EMM_GetSecuEia() != g_stEmmOmInfo.enAlgIntegrity))
    {
        g_stEmmOmInfo.enAlgSecurity = NAS_EMM_GetSecuEca();
        g_stEmmOmInfo.enAlgIntegrity = NAS_EMM_GetSecuEia();
        ulRst = NAS_EMM_FAIL;
    }

    /* 比较UE操作模式 */
    if (ulLteUeMode != g_stEmmOmInfo.enLteUeMode)
    {
        g_stEmmOmInfo.enLteUeMode = ulLteUeMode;
        ulRst = NAS_EMM_FAIL;
    }
    return ulRst;
}


/*****************************************************************************
 Function Name   : NAS_LMM_DtCompareGuti
 Description     : 判断EMM模块维护且需要上报给路测的Guti信息是否发生变化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_DtCompareGuti(VOS_VOID)
{
    NAS_MM_GUTI_STRU                  *pstEmmCurGuti;
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    pstEmmCurGuti                       = NAS_LMM_GetEmmInfoUeidGutiAddr();

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&g_stEmmDtInfo.stGuti,pstEmmCurGuti,
                                                 sizeof(NAS_MM_GUTI_STRU)))
    {
       ulRst = NAS_EMM_FAIL;
    }

    return ulRst;

}

/*****************************************************************************
 Function Name   : NAS_LMM_DtCompareImsi
 Description     : 判断EMM模块维护且需要上报给路测的Imsi信息是否发生变化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_DtCompareImsi(VOS_VOID)
{
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    NAS_OM_IMSI_INFO_STRU              stImsiInfo;
    VOS_UINT8                          ucIndex;

    NAS_LMM_MEM_SET_S(  &stImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        0,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

    /*如果当前无卡,向OM回复查询IMSI为空*/
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {

        /* 获取IMSI */
        stImsiInfo.ucImsiLen = (VOS_UINT8)((g_stEmmInfo.stMmUeId.aucImsi[0])*2 - 1);

        /*最后一个字节最高4位为F,则表明IMSI为偶数个 */
        if (0xF0 == (g_stEmmInfo.stMmUeId.aucImsi[g_stEmmInfo.stMmUeId.aucImsi[0]] & 0xF0))
        {
            stImsiInfo.ucImsiLen -= 1;
        }

        for(ucIndex= 0; ucIndex< stImsiInfo.ucImsiLen; ucIndex++)
        {
            if (0 == (ucIndex+1)%2)
            {
                stImsiInfo.ucImsi[ucIndex] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(ucIndex+1)/2 + 1]);
            }
            else
            {
                stImsiInfo.ucImsi[ucIndex] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(ucIndex+1)/2 + 1] >> 4);
            }
        }
    }


    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&g_stEmmDtInfo.stImsi,&stImsiInfo,
                                                 sizeof(NAS_OM_IMSI_INFO_STRU)))
    {
       ulRst = NAS_EMM_FAIL;
    }

    return ulRst;

}

/*****************************************************************************
 Function Name   : NAS_LMM_DtCompareEmmState
 Description     : 判断EMM模块维护且需要上报给路测的EmmState信息是否发生变化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_DtCompareEmmState(VOS_VOID)
{
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
    VOS_UINT16                           usStaTId;           /* 定时器信息*/

    /* 由EMM当前状态获取协议状态 */
    NAS_LMM_PubmGetEmmState(&ulProtoclMainState,
                            &ulProtoclSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());
    /* 获取定时器信息 */
    usStaTId = (VOS_UINT16)NAS_LMM_GetEmmCurTimer();

    if ((ulProtoclMainState != g_stEmmDtInfo.stEmmState.enMainState)
        || (ulProtoclSubState != g_stEmmDtInfo.stEmmState.enSubState)
        || (usStaTId != g_stEmmDtInfo.stEmmState.usStaTId))
    {
        ulRst = NAS_EMM_FAIL;
    }

    return ulRst;

}

/*****************************************************************************
 Function Name   : NAS_LMM_DtJudgeifNeedRpt
 Description     : 判断EMM模块维护且需要上报给路测的信息是否发生变化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_DtJudgeifNeedRpt(VOS_VOID)
{

    /*判断是否需要上报GUTI*/
    if (NAS_DT_RPT_START== NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus)
    {
        if(NAS_EMM_FAIL == NAS_LMM_DtCompareGuti())
        {
        #if (VOS_WIN32 != VOS_OS_VER)
           /*上报GUTI信息*/
           NAS_LMM_PubmIndGuti();
        #endif

        }
    }
     /*判断是否需要上报IMSI*/
    if (NAS_DT_RPT_START== NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus)
    {
        if(NAS_EMM_FAIL == NAS_LMM_DtCompareImsi())
        {
        #if (VOS_WIN32 != VOS_OS_VER)
           /*上报Imsi信息*/
           NAS_LMM_PubmIndImsi();
        #endif

        }
    }

    /* 判断是否需要上报EMM状态*/
    if(NAS_DT_RPT_START== NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus)
    {
        if(NAS_EMM_FAIL == NAS_LMM_DtCompareEmmState())
        {
        #if(VOS_WIN32 != VOS_OS_VER)
           /*上报EMM状态*/
           NAS_LMM_PubmIndEmmState();
        #endif
        }
    }
    return;
}



VOS_VOID  NAS_LMM_SetAppParaValue
(
    NAS_LMM_APP_PARA_SET_RESLT_STRU      *pstParaInfo,
    const NAS_LMM_APP_PARA_SET_HEAD_STRU       *pstAppMsg
)
{
    pstParaInfo->ulOpId                 = pstAppMsg->ulOpId;

    /*交叉MID参数*/
    pstParaInfo->usOriginalId = pstAppMsg->usOriginalId;
    pstParaInfo->usTerminalId = pstAppMsg->usTerminalId;
    pstParaInfo->ulTimeStamp  = pstAppMsg->ulTimeStamp;

    /*设置SN参数*/
    pstParaInfo->ulSN = pstAppMsg->ulSN;
    return;
}


VOS_VOID NAS_EMM_SendIntraTauReq
(
    APP_MM_MSG_TYPE_ENUM_UINT32         ulOmMmMsgType,
    NAS_LMM_INTRA_TAU_TYPE_ENUM_UINT32  enIntraTauType
)
{
    VOS_UINT32                          ulMsgLenthNoHeader;
    NAS_LMM_INTRA_TAU_REQ_STRU           *pEmmIntraTauReq;
/*    VOS_UINT32                          ulRst;*/

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SendIntraTauReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendIntraTauReq_ENUM
,LNAS_ENTRY);

     /* 计算EMM要发给OM的消息长度, 不包含VOS头 */
    ulMsgLenthNoHeader = EMM_MSG_LENTH_NO_HEADER(NAS_LMM_INTRA_TAU_REQ_STRU);

    /* 申请DOPRA消息 */
    /*lint -e433 -e826*/
    pEmmIntraTauReq = (VOS_VOID *)NAS_LMM_GetSendIntraMsgBuffAddr(ulMsgLenthNoHeader);
    /*lint +e433 +e826*/

    if(NAS_LMM_NULL_PTR  == pEmmIntraTauReq)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SendIntraTauReq: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SendIntraTauReq_ENUM
,LNAS_NULL_PTR);
        return;
    }

    /* 打包消息头 */
    NAS_EMM_COMP_INTRA_MSG_HEADER(      pEmmIntraTauReq,
                                        ulMsgLenthNoHeader);


    /* 填写消息ID */
    pEmmIntraTauReq->ulMsgId            = ID_NAS_LMM_INTRA_TAU_REQ;

    pEmmIntraTauReq->ulOmMsgType        = ulOmMmMsgType;

    pEmmIntraTauReq->enIntraTauType     = enIntraTauType;

    /* 发送消息 */
    /*
    ulRst = NAS_LMM_SendIntraMsg(        pEmmIntraTauReq);
    if(NAS_EMM_SUCC != ulRst)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendIntraTauReq: SendIntraMsg ERR !!");
    }
    */
    NAS_EMM_SEND_INTRA_MSG(             pEmmIntraTauReq);

    return;

}



/*****************************************************************************
 Function Name  : IMSA_ReadImsaNvImsCapability()
 Description    : 读取IMS能力配置信息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leili 00132387      2013-10-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadImsaNvImsCapability( VOS_UINT8 *pucSmsOverIms, VOS_UINT8 *pucSrvcc)
{
    IMS_NV_IMS_CAP_STRU             stNvImsCapability;
    VOS_UINT32                      ulRslt;
    /*lint -e718*/
    /*lint -e732*/
    /*lint -e516*/
    ulRslt = LPs_NvimItem_Read(EN_NV_ID_IMS_CAPABILITY,&stNvImsCapability,\
                 sizeof(IMS_NV_IMS_CAP_STRU));
    /*lint +e516*/
    /*lint +e732*/
    /*lint +e718*/

    if(ulRslt == VOS_OK)
    {
        /*根据NV内容设置*/
        *pucSmsOverIms = stNvImsCapability.ucSmsOnImsSupportFlag;
        *pucSrvcc = stNvImsCapability.ucSrvccOnImsSupportFlag;

    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("IMSA_ReadImsaNvImsCapability: read NV err!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ReadImsaNvImsCapability_ENUM
,LNAS_ERROR);

        /*设置初始值*/
        *pucSmsOverIms = VOS_TRUE;
        *pucSrvcc = VOS_TRUE;
    }

}

/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqLteCs
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY        2012-02-17    Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqLteCs(MsgBlock *pMsg)
{
    APP_MM_INQ_LTE_CS_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_LTE_CS_CNF_STRU      *pstAppInqCnf;
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;

    enAddUpdateRslt = NAS_EMM_GetAddUpdateRslt();

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqLteCs: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_ENTRY);

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* 为消息分配地址 */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_LTE_CS_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqLteCs: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_NULL_PTR);
        return;
    }


    /* 结构初始化 */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_LTE_CS_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_LTE_CS_CNF_STRU));

    /* 打包消息头 */
    EMM_COMP_APP_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_LTE_CS_CNF_STRU),
                                pstAppInqReq);

    /*设置OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*设置消息类型*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_LTE_CS_CNF;

    pstAppInqCnf->ulRslt      = APP_SUCCESS;

    if(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: REG domain  NAS_LMM_REG_DOMAIN_CS_PS!!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_FUNCTION_LABEL1);
        pstAppInqCnf->stLtecsInfo.ucSmsOverSGs = NAS_LMM_LTE_CS_SERVICE_SUPPORT;

        if(NAS_LMM_ADDITIONAL_UPDATE_BUTT == enAddUpdateRslt)
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: Addition Update Result not exist!!");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_FUNCTION_LABEL2);
            pstAppInqCnf->stLtecsInfo.ucCSFB = NAS_LMM_LTE_CS_SERVICE_SUPPORT;
        }
        else
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: Addition Update Resultsexist!!");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_FUNCTION_LABEL3);
            /*lint -e960*/
            if((NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED == enAddUpdateRslt) ||
                (NAS_LMM_ADDITIONAL_UPDATE_NO_INFO == enAddUpdateRslt))
            /*lint +e960*/
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: Addition Update Result is NO_INFO or CSFB_NOT_PREFERED!!");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_FUNCTION_LABEL4);
                pstAppInqCnf->stLtecsInfo.ucCSFB = NAS_LMM_LTE_CS_SERVICE_SUPPORT;
            }
        }
    }
    NAS_LMM_ReadImsaNvImsCapability(&pstAppInqCnf->stLtecsInfo.ucSmsOverIMS,&pstAppInqCnf->stLtecsInfo.ucSrVcc);

    /* 发送消息 */
    /*lint -e960*/
    NAS_LMM_SEND_MSG(pstAppInqCnf);
    /*lint +e960*/

    return;
}


/* niuxiufan DT begin */
/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqGuti
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501        2012-09-07    Draft Enact
    2.l00195322                 2014-4-23,  CNF只上报成功或失败，IND上报消息内容

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqGuti(MsgBlock *pMsg)
{
    APP_MM_INQ_LTE_GUTI_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_LTE_GUTI_CNF_STRU      *pstAppInqCnf;

    pstAppInqReq                       = (VOS_VOID *)pMsg;


    /* 根据命令判断是否停止GUTI上报 */
    if (DT_CMD_STOP == pstAppInqReq->enCmd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: START");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqGuti_ENUM
,LNAS_FUNCTION_LABEL1);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus = NAS_DT_RPT_STOP;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqGuti_ENUM
,LNAS_FUNCTION_LABEL2);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enDtRptItem = NAS_DT_REPORT_TYPE_GUTI;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus = NAS_DT_RPT_START;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptType = APP_MM_RM_AUTO;
    }

    /* 为消息分配地址 */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_LTE_GUTI_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqGuti_ENUM
,LNAS_NULL_PTR);
        return;
    }


    /* 结构初始化 */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_LTE_GUTI_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_LTE_GUTI_CNF_STRU));

    /* 打包消息头 */
    EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_LTE_GUTI_CNF_STRU),
                                pstAppInqReq);

    /*设置OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*设置消息类型*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_LTE_GUTI_CNF;

    pstAppInqCnf->ulRslt      = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppInqCnf);
    }
#endif


    /* 发送消息 */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    NAS_LMM_PubmIndGuti();

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqImsi
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501        2012-09-07    Draft Enact
    2.l00195322                 2014-4-23,  CNF只上报成功或失败，IND上报消息内容
*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqImsi(MsgBlock *pMsg)
{
    APP_MM_INQ_IMSI_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_IMSI_CNF_STRU      *pstAppInqCnf;

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* 根据命令判断是否停止IMSI上报 */
    /* chengmin 00285307 修改缩进 begin */
    if (DT_CMD_STOP == pstAppInqReq->enCmd)
    /* chengmin 00285307 修改缩进 end */
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqImsi: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqImsi_ENUM
,LNAS_FUNCTION_LABEL1);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus = NAS_DT_RPT_STOP;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqImsi: START");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqImsi_ENUM
,LNAS_FUNCTION_LABEL2);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enDtRptItem = NAS_DT_REPORT_TYPE_IMSI;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus = NAS_DT_RPT_START;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptType = APP_MM_RM_AUTO;
    }

    /* 为消息分配地址 */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_IMSI_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqImsi: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqImsi_ENUM
,LNAS_NULL_PTR);
        return;
    }


    /* 结构初始化 */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_IMSI_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_IMSI_CNF_STRU));

    /* 打包消息头 */
    EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_IMSI_CNF_STRU),
                                pstAppInqReq);

    /*设置OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*设置消息类型*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_IMSI_CNF;
    pstAppInqCnf->ulRslt      = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppInqCnf);
    }
#endif
    /* 发送消息 */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    NAS_LMM_PubmIndImsi();

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqEmmState
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501        2012-09-07    Draft Enact
    2.l00195322                 2014-4-23,  CNF只上报成功或失败，IND上报消息内容

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqEmmState(MsgBlock *pMsg)
{
    APP_MM_INQ_EMM_STATE_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_EMM_STATE_CNF_STRU      *pstAppInqCnf;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: enter");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqEmmState_ENUM
,LNAS_FUNCTION_LABEL1);

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* 根据命令判断是否停止EMM State上报 */
    if (DT_CMD_STOP == pstAppInqReq->enCmd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqEmmState_ENUM
,LNAS_FUNCTION_LABEL2);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus = NAS_DT_RPT_STOP;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: START");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqEmmState_ENUM
,LNAS_FUNCTION_LABEL3);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enDtRptItem = NAS_DT_REPORT_TYPE_EMM_STATE;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus = NAS_DT_RPT_START;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptType = APP_MM_RM_AUTO;
    }

    /* 为消息分配地址 */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_EMM_STATE_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqEmmState_ENUM
,LNAS_FUNCTION_LABEL4);
        return;
    }


    /* 结构初始化 */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_EMM_STATE_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_EMM_STATE_CNF_STRU));

    /* 打包消息头 */
    EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_EMM_STATE_CNF_STRU),
                                pstAppInqReq);

    /*设置OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*设置消息类型*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_EMM_STATE_CNF;

    pstAppInqCnf->ulRslt      = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppInqCnf);
    }
#endif

    /* 发送消息 */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    NAS_LMM_PubmIndEmmState();

    return;
}

VOS_VOID  NAS_LMM_PubmIndGuti(VOS_VOID)
{
    APP_MM_INQ_LTE_GUTI_IND_STRU      *pstAppGutiInd;
    NAS_MM_GUTI_STRU                  *pstEmmCurGuti;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndGuti: enter");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndGuti_ENUM
,LNAS_ENTRY);

    /* 根据命令判断是否停止GUTI上报 */
    if (NAS_DT_RPT_STOP == NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndGuti: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndGuti_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* 为消息分配地址 */
    pstAppGutiInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_LTE_GUTI_IND_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppGutiInd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndGuti_ENUM
,LNAS_FUNCTION_LABEL2);
        return;
    }


    /* 结构初始化 */
    NAS_LMM_MEM_SET_S(  pstAppGutiInd,
                        sizeof(APP_MM_INQ_LTE_GUTI_IND_STRU),
                        0,
                        sizeof(APP_MM_INQ_LTE_GUTI_IND_STRU));

    /* 打包消息头 */
    EMM_COMP_APP_DT_IND_MSG_HEADER( pstAppGutiInd,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_LTE_GUTI_IND_STRU));

    /*打包APP消息头*/
    EMM_COMP_OMT_APP_MSG_HEADER( pstAppGutiInd);

    /*设置消息类型*/
    pstAppGutiInd->ulMsgId     = ID_APP_MM_INQ_LTE_GUTI_IND;
    pstAppGutiInd->ulOpId      = DIAG_CMD_EMM_APP_GUTI_INFO_IND;


    /* 获取GUTI */
    pstEmmCurGuti                       = NAS_LMM_GetEmmInfoUeidGutiAddr();
    NAS_LMM_MEM_CPY_S(  &pstAppGutiInd->stGuti,
                        sizeof(APP_GUTI_STRU),
                        pstEmmCurGuti,
                        sizeof(NAS_LMM_GUTI_STRU));

    /*保存GUTI信息至全局变量*/
    NAS_LMM_MEM_CPY_S(  &g_stEmmDtInfo.stGuti,
                        sizeof(NAS_MM_GUTI_STRU),
                        pstEmmCurGuti,
                        sizeof(NAS_MM_GUTI_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppGutiInd);
    }
#endif
    /* 发送消息 */
    NAS_LMM_SEND_MSG(pstAppGutiInd);
    return;
}

VOS_VOID  NAS_LMM_PubmIndImsi(VOS_VOID)
{
    APP_MM_INQ_IMSI_IND_STRU      *pstAppImsiInd;
    NAS_OM_IMSI_INFO_STRU          stImsiInfo;
    VOS_UINT8                      i;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndImsi: enter");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndImsi_ENUM
,LNAS_ENTRY);


    /* 根据命令判断是否停止IMSI上报 */
    if (NAS_DT_RPT_STOP == NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndImsi: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndImsi_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* 为消息分配地址 */
    pstAppImsiInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_IMSI_IND_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppImsiInd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndImsi: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndImsi_ENUM
,LNAS_FUNCTION_LABEL2);
        return;
    }


    /* 结构初始化 */
    NAS_LMM_MEM_SET_S(  pstAppImsiInd,
                        sizeof(APP_MM_INQ_IMSI_IND_STRU),
                        0,
                        sizeof(APP_MM_INQ_IMSI_IND_STRU));

    /* 打包消息头 */
    EMM_COMP_APP_DT_IND_MSG_HEADER( pstAppImsiInd,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_IMSI_IND_STRU));

    /*打包APP消息头*/
    EMM_COMP_OMT_APP_MSG_HEADER( pstAppImsiInd);

    /*设置消息类型*/
    pstAppImsiInd->ulMsgId     = ID_APP_MM_INQ_IMSI_IND;
    pstAppImsiInd->ulOpId      = DIAG_CMD_EMM_APP_IMSI_INFO_IND;


    NAS_LMM_MEM_SET_S(  &stImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        0,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

    /*如果当前无卡,向OM回复查询IMSI为空*/
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {

        /* 获取IMSI */
        stImsiInfo.ucImsiLen = (VOS_UINT8)((g_stEmmInfo.stMmUeId.aucImsi[0])*2 - 1);

        /*最后一个字节最高4位为F,则表明IMSI为偶数个 */
        if (0xF0 == (g_stEmmInfo.stMmUeId.aucImsi[g_stEmmInfo.stMmUeId.aucImsi[0]] & 0xF0))
        {
            stImsiInfo.ucImsiLen -= 1;
        }

        for(i = 0; i < stImsiInfo.ucImsiLen; i++)
        {
            if (0 == (i+1)%2)
            {
                stImsiInfo.ucImsi[i] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(i+1)/2 + 1]);
            }
            else
            {
                stImsiInfo.ucImsi[i] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(i+1)/2 + 1] >> 4);
            }
        }
    }

    NAS_LMM_MEM_CPY_S( &pstAppImsiInd->stImsi,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        &stImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

    /*保存IMSI信息至全局变量*/
    NAS_LMM_MEM_CPY_S(  &g_stEmmDtInfo.stImsi,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        &stImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppImsiInd);
    }
#endif
    /* 发送消息 */
    NAS_LMM_SEND_MSG(pstAppImsiInd);

    return;
}

VOS_VOID  NAS_LMM_PubmIndEmmState(VOS_VOID)
{
    APP_MM_INQ_EMM_STATE_IND_STRU      *pstAppEmmStateInd;
    NAS_OM_EMM_STATE_STRU               stEmmPtlState = {0};

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndEmmState: enter");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndEmmState_ENUM
,LNAS_ENTRY);


    /* 根据命令判断是否停止EMM State上报 */
    if (NAS_DT_RPT_STOP == NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndEmmState: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndEmmState_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }


    /* 为消息分配地址 */
    pstAppEmmStateInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_EMM_STATE_IND_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppEmmStateInd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndEmmState: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndEmmState_ENUM
,LNAS_FUNCTION_LABEL2);
        return;
    }


    /* 结构初始化 */
    NAS_LMM_MEM_SET_S(  pstAppEmmStateInd,
                        sizeof(APP_MM_INQ_EMM_STATE_IND_STRU),
                        0,
                        sizeof(APP_MM_INQ_EMM_STATE_IND_STRU));

    /* 打包消息头 */
    EMM_COMP_APP_DT_IND_MSG_HEADER( pstAppEmmStateInd,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_EMM_STATE_IND_STRU));

    /*打包APP消息头*/
    EMM_COMP_OMT_APP_MSG_HEADER( pstAppEmmStateInd);


    /*设置消息类型*/
    pstAppEmmStateInd->ulMsgId     = ID_APP_MM_INQ_EMM_STATE_IND;
    pstAppEmmStateInd->ulOpId      = DIAG_CMD_EMM_APP_EMM_STATE_IND;

    /* 获取协议状态信息 */
    NAS_LMM_PubmGetEmmState(&(stEmmPtlState.enMainState),
                           &(stEmmPtlState.enSubState),
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());

    stEmmPtlState.usStaTId = (VOS_UINT16)NAS_LMM_GetEmmCurTimer();

    /* coverity[uninit_use_in_call] */
    NAS_LMM_MEM_CPY_S(  &pstAppEmmStateInd->stEmmState,
                        sizeof(NAS_OM_EMM_STATE_STRU),
                        &stEmmPtlState,
                        sizeof(NAS_OM_EMM_STATE_STRU));

    /*协议状态信息保存至全局变量*/
    /* coverity[uninit_use_in_call] */
    NAS_LMM_MEM_CPY_S(  &g_stEmmDtInfo.stEmmState,
                        sizeof(NAS_OM_EMM_STATE_STRU),
                        &stEmmPtlState,
                        sizeof(NAS_OM_EMM_STATE_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppEmmStateInd);
    }
#endif
    /* 发送消息 */
    NAS_LMM_SEND_MSG(pstAppEmmStateInd);
    return;
}

/* niuxiufan DT end */



/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqUeMode
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY        2012-02-17    Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqUeMode(MsgBlock *pMsg)
{
    APP_MM_INQ_UE_MODE_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_UE_MODE_CNF_STRU      *pstAppInqCnf;

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* 为消息分配地址 */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_UE_MODE_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqUeMode: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqUeMode_ENUM
,LNAS_ENTRY);
        return;
    }

    /*lint -e960*/

    /* 结构初始化 */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_UE_MODE_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_UE_MODE_CNF_STRU));

    /* 打包消息头 */
    EMM_COMP_APP_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_UE_MODE_CNF_STRU),
                                pstAppInqReq);

    /*设置消息体*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_UE_MODE_CNF;
    pstAppInqCnf->ulRslt      = APP_SUCCESS;
    pstAppInqCnf->enCurrentUeMode = NAS_LMM_GetEmmInfoUeOperationMode();
    /*当前UE支持CS\PS和PS模式，所以数量为2*/
    pstAppInqCnf->ulSupportModeCnt = 2;
    if(EMM_SETTING_DATA_CENTRIC == NAS_LMM_GetEmmInfoUeCenter())
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqUeMode: UE Center is DATA_CENTRIC!!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqUeMode_ENUM
,LNAS_FUNCTION_LABEL1);
        pstAppInqCnf->aenSupportModeList[0] = NAS_LMM_UE_PS_MODE_2;
        pstAppInqCnf->aenSupportModeList[1] = NAS_LMM_UE_CS_PS_MODE_2;

    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqUeMode: UE Center is VOICE_CENTRIC!!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqUeMode_ENUM
,LNAS_FUNCTION_LABEL2);
        pstAppInqCnf->aenSupportModeList[0] = NAS_LMM_UE_PS_MODE_1;
        pstAppInqCnf->aenSupportModeList[1] = NAS_LMM_UE_CS_PS_MODE_1;
    }

    /* 发送消息 */
    NAS_LMM_SEND_MSG(pstAppInqCnf);
    /*lint +e960*/

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PubmGetEmmState
 Description     : 获取协议状态
 Input           : APP_EMM_MAIN_STATE_ENUM_UINT32      *pulProtoclMainState
                   APP_EMM_SUB_STATE_ENUM_UINT32       *pulProtoclSubState
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-3-20  Draft Enact
    2.lifuxin 00253982      2014-10-31 建链流程重构

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmGetEmmState
(
    APP_EMM_MAIN_STATE_ENUM_UINT16      *pulProtoclMainState,
    APP_EMM_SUB_STATE_ENUM_UINT16       *pulProtoclSubState,
    NAS_LMM_MAIN_STATE_ENUM_UINT16      enMainState,
    NAS_LMM_SUB_STATE_ENUM_UINT16       enSubState
)
{
    APP_EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    APP_EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
    VOS_UINT32                          ulLoop;

    NAS_LMM_FSM_STATE_STACK_STRU         *pstFsmStack;        /* 状态机栈地址 */
    NAS_LMM_FSM_STATE_STRU               *pstFsmStackTop;     /* 指向栈顶状态 */


    /* 初始化协议状态 */
    ulProtoclMainState                  = APP_EMM_MS_NULL;
    ulProtoclSubState                   = APP_EMM_SS_NULL;


    /* 连接建立过程,释放过程,鉴权过程 需要从状态栈获取状态 */
    /*add by lifuxin for Lnas est&rel process re-construct*/
    if(EMM_MS_AUTH_INIT == enMainState)
    {
        /* 获取状态栈栈顶地址 */
        pstFsmStack
            =  NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);
        pstFsmStackTop
            = &((pstFsmStack->astFsmStack)[pstFsmStack->ucStackDepth - 1]);

        /* 从状态栈获取状态 */
        enMainState                     = pstFsmStackTop->enMainState;
        enSubState                      = pstFsmStackTop->enSubState;
    }

    /*挂起过程中 */
    if (EMM_MS_SUSPEND == enMainState)
    {
        enMainState = NAS_EMM_GetMsBefSuspend();
        enSubState = NAS_EMM_GetSsBefSuspend();
    }

    if (EMM_MS_RESUME == enMainState)
    {
        if (EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND == enSubState)
        {
            enMainState = NAS_EMM_GetMsBefResume();
            enSubState = NAS_EMM_GetSsBefResume();
        }
        else
        {
            if ((NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL == NAS_EMM_GetResumeType())
                || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO == NAS_EMM_GetResumeType())
                || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO == NAS_EMM_GetResumeType())
                || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR == NAS_EMM_GetResumeType()))
            {
                enMainState = NAS_EMM_GetMsBefSuspend();
                enSubState = NAS_EMM_GetSsBefSuspend();
            }
            else
            {
                enMainState = NAS_EMM_GetMsBefResume();
                enSubState = NAS_EMM_GetSsBefResume();
            }
        }
    }

    /* 根据状态映射表读取协议状态 */
    for (ulLoop = 0; ulLoop< g_ulProtocolStateMapNum; ulLoop++)
    {
        if ( (enMainState == g_astProtocolStateMap[ulLoop].enMainState)
            &&((enSubState == g_astProtocolStateMap[ulLoop].enSubState)
              || (MM_SS_BUTT == g_astProtocolStateMap[ulLoop].enSubState)) )
        {
            /*lint -e960*/
            ulProtoclMainState
                = g_astProtocolStateMap[ulLoop].ulProtoclMainState;
            ulProtoclSubState
                = g_astProtocolStateMap[ulLoop].ulProtoclSubState;
            break;
            /*lint +e960*/
        }
    }

    /* 赋值输出 */
    *pulProtoclMainState                = ulProtoclMainState;
    *pulProtoclSubState                 = ulProtoclSubState;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PubmGetEmmUpdateState
 Description     : 获取EMM更新状态
 Input           : APP_EMM_UPDATE_STATE_ENUM_UINT32    *pulEmmUpState
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-3-20  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmGetEmmUpdateState
(
    APP_EMM_UPDATE_STATE_ENUM_UINT32    *pulEmmUpState
)
{
    *pulEmmUpState                      =  NAS_EMM_UPDATE_STAE;

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PubmGetAreaInfo
 Description     : 获取GUTI,TA列表,当前TA
 Input           : APP_GUTI_STRU                       *pstGuti
                   APP_TA_LIST_STRU                    *pstTaiList
                   APP_TA_STRU                         *pstLastTa
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-3-20  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmGetAreaInfo
(
    APP_GUTI_STRU                       *pstGuti,
    APP_TA_LIST_STRU                    *pstTaiList,
    APP_TA_STRU                         *pstLastTa
)
{
    NAS_MM_GUTI_STRU                    *pstEmmCurGuti;
    NAS_MM_TA_LIST_STRU                 *pstEmmCurTaiList;
    NAS_MM_NETWORK_ID_STRU              *pstEmmCurNetId;

    /* 获取GUTI */
    pstEmmCurGuti                       = NAS_LMM_GetEmmInfoUeidGutiAddr();

    /*lint -e960*/

    NAS_LMM_MEM_CPY_S(  pstGuti,
                        sizeof(APP_GUTI_STRU),
                        pstEmmCurGuti,
                        sizeof(NAS_LMM_GUTI_STRU));

    /* 获取TAI列表 */
    pstEmmCurTaiList                    = NAS_LMM_GetEmmInfoNetInfoTaiListAddr();
    NAS_LMM_MEM_CPY_S(  pstTaiList,
                        sizeof(APP_TA_LIST_STRU),
                        pstEmmCurTaiList,
                        sizeof(NAS_MM_TA_LIST_STRU));

    /* 获取TA */
    pstEmmCurNetId                      = NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr();
    NAS_LMM_MEM_CPY_S(  &pstLastTa->stPlmnId,
                        sizeof(APP_PLMN_ID_STRU),
                        &pstEmmCurNetId->stPlmnId,
                        sizeof(NAS_MM_PLMN_ID_STRU));
    NAS_LMM_MEM_CPY_S(  &pstLastTa->stTac,
                        sizeof(APP_TAC_STRU),
                        &pstEmmCurNetId->stTac,
                        sizeof(NAS_MM_TAC_STRU));

    /*lint +e960*/

    return;

}


/*****************************************************************************
 Function Name   : NAS_LMM_PubmGetEmmInfo
 Description     : 获取移动性信息
 Input           : APP_EMM_INFO_STRU        *pstEmmInfoCnf
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-3-20  Draft Enact
    2.yangfan 00159566      2010-5-11  Modify

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmGetEmmInfo
(
    APP_EMM_INFO_STRU                   *pstEmmInfoCnf
)
{
    /* 获取协议状态信息 */
    NAS_LMM_PubmGetEmmState(&(pstEmmInfoCnf->ulMainState),
                           &(pstEmmInfoCnf->ulSubState),
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());
    /* 获取EMM update状态 */
    NAS_LMM_PubmGetEmmUpdateState(&(pstEmmInfoCnf->ulEmmUpState));

    /* 获取 GUTI,TaiList,Last Ta */
    NAS_LMM_PubmGetAreaInfo(&(pstEmmInfoCnf->stGuti),
                           &(pstEmmInfoCnf->stTaiList),
                           &(pstEmmInfoCnf->stLastTa));

}

/*****************************************************************************
 Function Name  : Nas_Emm_SendOmtKeyEvent
 Discription    : 给OMT发送关键事件
 Input          :
 Output         : None
 Return         : None
 History:
      1.  qilili00145085  2008-10-30  Draft Enact
      2.  z00138739        2009-5-22  Modify, BJ9D00871
*****************************************************************************/
VOS_VOID    NAS_LMM_SendOmtKeyEvent(     PS_EMM_OMT_KEY_EVENT_TYPE_ENUM_UINT8
                                        ucEmmOmtKeyEvent  )
{
    /*z00282933, 多模OM融合添加 - BEGIN*/
#if (VOS_WIN32 != VOS_OS_VER)
    DIAG_EVENT_IND_STRU stDiagEventInd;

#ifndef PS_ITT_PC_TEST
    NAS_LMM_MEM_SET_S(  &stDiagEventInd,
                        sizeof(DIAG_EVENT_IND_STRU),
                        0,
                        sizeof(DIAG_EVENT_IND_STRU));

    stDiagEventInd.ulModule = LPS_OM_ID(UE_MODULE_MM_ID, DIAG_LOG_TYPE_INFO);
    stDiagEventInd.ulPid = UE_MODULE_MM_ID;
    stDiagEventInd.ulEventId = (VOS_UINT32)(ucEmmOmtKeyEvent+OM_PS_KEY_EVENT_BASE_ID);

    /*lint -e778*/
    /*lint -e648*/
    if(ERR_MSP_SUCCESS != LDRV_DIAG_EVENTREPORT(&stDiagEventInd))
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_SendOmtKeyEvent: Send Msg Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_SendOmtKeyEvent_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }
    /*lint +e648*/
    /*lint +e778*/
#endif

#endif
    /*z00282933, 多模OM融合添加 - END*/
}


/*****************************************************************************
 Function Name  : NAS_LMM_SendOmtAirMsg
 Discription    : 向OMT发送空口消息
 Input          : ulDir,
                  ulAirMsgId
                  pstNasMsg
 Output         : None
 Return         : None
 History:
      1.  qilili00145085  2008-10-30  Draft Enact
      2.  z00138739        2009-5-22  Modify, BJ9D00871
*****************************************************************************/
VOS_VOID    NAS_LMM_SendOmtAirMsg(       NAS_LMM_OM_AIR_MSG_UP_DOWN_ENUM_UINT8  ucDir,
                                        NAS_LMM_OM_AIR_MSG_ID_ENUM_UINT8       ucAirMsgId,
                                        NAS_MSG_STRU                       *pstNasMsg)
{
#ifndef PS_ITT_PC_TEST
    /*z00282933, 多模OM融合添加 - BEGIN*/
    DIAG_AIR_IND_STRU        stAirMsg;
    /*z00282933, 多模OM融合添加 - END*/
    VOS_UINT8                   *pucTmpData = VOS_NULL_PTR;

    /*分配空口消息空间*/
    pucTmpData = (VOS_UINT8*)
                        NAS_LMM_MEM_ALLOC(pstNasMsg->ulNasMsgSize);

    if(VOS_NULL_PTR== pucTmpData)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SendOmtAirMsg: MEM_ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendOmtAirMsg_ENUM
,LNAS_NULL_PTR);
        return;
    }

    /*lint -e960*/

    NAS_LMM_MEM_CPY_S( (pucTmpData),
                        (pstNasMsg->ulNasMsgSize),
                        (pstNasMsg->aucNasMsg),
                        (pstNasMsg->ulNasMsgSize));

    /*z00282933, 多模OM融合添加 - BEGIN*/
    /*空口消息赋值*/
    if(NAS_EMM_OMT_AIR_MSG_UP == ucDir)
    {
        stAirMsg.ulModule = DIAG_AIR_MSG_LOG_ID(PS_PID_MM, OS_MSG_UL);
        stAirMsg.ulPid = PS_PID_MM;
        stAirMsg.ulDirection = DIAG_SIDE_NET;
    }
    else
    {
        stAirMsg.ulModule = DIAG_AIR_MSG_LOG_ID(PS_PID_MM, OS_MSG_DL);
        stAirMsg.ulPid = PS_PID_MM;
        stAirMsg.ulDirection = DIAG_SIDE_UE;
    }
    stAirMsg.ulMsgId = (VOS_UINT32)(ucAirMsgId+ PS_MSG_ID_AIR_BASE);
    stAirMsg.ulLength = pstNasMsg->ulNasMsgSize;
    stAirMsg.pData = (void*)pucTmpData;

    /*上报空口消息*/
    if(ERR_MSP_SUCCESS != LDRV_DIAG_AIRMSGREPORT(&stAirMsg))
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_SendOmtAirMsg: Send Msg Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_SendOmtAirMsg_ENUM,LNAS_FAIL);
    }
    /*z00282933, 多模OM融合添加 - END*/

    /*释放内存空间*/
    NAS_LMM_MEM_FREE(pucTmpData);
    /*lint +e960*/

#endif
    (VOS_VOID)(pstNasMsg);
}


VOS_VOID   NAS_LMM_FindAirMsgId( VOS_UINT8 ucCnMsgType,
                                VOS_UINT8 *pucAirMsg,
                                VOS_UINT8 *pucKeyEvent)
{
    VOS_UINT8 i;
    VOS_UINT8 ucLen;
    ucLen = sizeof(g_stMmOmMsgIdStru)/(sizeof(NAS_LMM_OM_MSG_ID_CHANGE_STRU));
    for(i = 0;i < ucLen;i++)
    {
        /*lint -e960*/
        if (ucCnMsgType == g_stMmOmMsgIdStru[i].enCnMsgType)
        {
            *pucAirMsg   = g_stMmOmMsgIdStru[i].enAirMsg;
            *pucKeyEvent = g_stMmOmMsgIdStru[i].enKeyEvent;
            break;
        }
        /*lint +e960*/
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaSetCnf
 Description     : 设置类命令，向APP响应结果
 Input           : None
 Output          : None
 Return          : ulMsgId  : 响应消息的类型
                   ucRst    : 设置结果
                   pReqMsg  : 指向APP发来的设置类REQ消息, 用于获取APP头中的数据

 History         :
    1.h41410      2009-4-14  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmDaSendSetCnf( const NAS_LMM_APP_PARA_SET_RESLT_STRU *pstAppRslt )
{

    APP_MM_SET_CMD_CNF_STRU            *pstEmmSetCnf;

    NAS_LMM_PUBM_LOG3_NORM("NAS_LMM_PubmDaSetCnf:  ulMsgId =, ulRslt =, ulOpId = ",
                                        pstAppRslt->ulMsgId,
                                        pstAppRslt->ulRslt,
                                        pstAppRslt->ulOpId);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_PubmDaSendSetCnf_ENUM
,LNAS_FUNCTION_LABEL1,
                                        pstAppRslt->ulMsgId);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_PubmDaSendSetCnf_ENUM
,LNAS_FUNCTION_LABEL2,
                                        pstAppRslt->ulRslt,
                                        pstAppRslt->ulOpId);

    /* 申请DOPRA消息 */
    pstEmmSetCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(
                                        sizeof(APP_MM_SET_CMD_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstEmmSetCnf)
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PubmDaSetCnf: alloc NULL_PTR !! ulMsgId = ",
                                        pstAppRslt->ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PubmDaSendSetCnf_ENUM
,LNAS_FUNCTION_LABEL3,
                                         pstAppRslt->ulMsgId);
        return;
    }

    /*lint -e960*/

    NAS_LMM_MEM_SET_S(  pstEmmSetCnf,
                        sizeof(APP_MM_SET_CMD_CNF_STRU),
                        0,
                        sizeof(APP_MM_SET_CMD_CNF_STRU));


    /* 打包消息头 */
    EMM_COMP_APP_MSG_VOS_HEADER( pstEmmSetCnf,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_SET_CMD_CNF_STRU),
                                 pstAppRslt);

    /* 填写消息体 */
    pstEmmSetCnf->ulMsgId               = pstAppRslt->ulMsgId;
    pstEmmSetCnf->ulOpId                = pstAppRslt->ulOpId;
    pstEmmSetCnf->ulRslt                = pstAppRslt->ulRslt;

    /* 发送消息 */
    NAS_LMM_SEND_MSG(pstEmmSetCnf);

    /*lint +e960*/

    return;

}

/*****************************************************************************
 Function Name   : NAS_LMM_CheckAppDrxParam
 Description     : 检查APP下发的DRX参数是否有效
 Input           :
 Output          :
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_CheckAppDrxParam( CONST APP_DRX_STRU *pstAppDrxParam )
{
    /*检查入参指针*/
    if (VOS_NULL_PTR == pstAppDrxParam)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: Input NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_NULL_PTR);
        return NAS_EMM_PARA_INVALID;
    }

    /*SPLIT on CCCH有效性验证*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxSplitOnCcchValid(pstAppDrxParam->ucSplitOnCcch))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: SplitOnCcch InValid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_PARA_INVALID;
    }

    /*non_DRX Timer有效性验证*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxNonDrxTimerValid(pstAppDrxParam->ucNonDrxTimer))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: NonDrxTimer InValid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_PARA_INVALID;
    }

    /*SPLIT PG CYCLE CODE有效性验证*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxPgCycleCodeValid(pstAppDrxParam->ucSplitPgCode))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: SplitPgCycleCode InValid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_PARA_INVALID;
    }

    /* DRX Valude for S1 Mode有效性验证*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsUeDrxCycleValid(pstAppDrxParam->ucPsDrxLen))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: UeSpecDrxCycle InValid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_PARA_INVALID;
    }

    return NAS_EMM_PARA_VALID;

}

/*****************************************************************************
 Function Name   : NAS_LMM_IsDrxSplitOnCcchValid
 Description     : 判断DRX参数中ucSplitOnCcch是否有效:
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_IsDrxSplitOnCcchValid( VOS_UINT8 ucSplitOnCcch )
{
    /*ucSplitOnCcch取值:0 or 1*/
    if ((NAS_LMM_SPLIT_ON_CCCH_NOT_SUPPORT != ucSplitOnCcch)
      &&(NAS_LMM_SPLIT_ON_CCCH_SUPPORT != ucSplitOnCcch))
    {
        return NAS_EMM_PARA_INVALID;
    }
    return NAS_EMM_PARA_VALID;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IsDrxNonDrxTimerValid
 Description     : 判断DRX参数中ucNonDrxTimer是否有效
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_IsDrxNonDrxTimerValid( VOS_UINT8 ucNonDrxTimer )
{
    /*ucNonDrxTimer取值范围:[0,7]*/
    if (NAS_LMM_MAX_NON_DRX_TIMER < ucNonDrxTimer)
    {
        return NAS_EMM_PARA_INVALID;
    }
    return NAS_EMM_PARA_VALID;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IsDrxPgCycleCodeValid
 Description     : 判断DRX参数中ucSplitPgCode是否有效
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_IsDrxPgCycleCodeValid( VOS_UINT8 ucSplitPgCode )
{
    /*ucSplitPgCode取值范围:[0,98]*/
    if (NAS_LMM_MAX_SPLIT_PG_CYCLE_CODE < ucSplitPgCode)
    {
        return NAS_EMM_PARA_INVALID;
    }
    return NAS_EMM_PARA_VALID;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IsUeDrxCycleValid
 Description     : 判断DRX参数中ucPsDrxLen是否有效
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_IsUeDrxCycleValid( VOS_UINT8 ucPsDrxLen )
{
    /*Drx Value for S1 Mode: 24008-930 10.5.5.6*/
    CONST VOS_UINT32 aulUeSpecDrxValue[NAS_LMM_UE_SPEC_DRX_VALUE_NUM] = {0,6,7,8,9};
    VOS_UINT32                          i;

    for(i = 0; i < NAS_LMM_UE_SPEC_DRX_VALUE_NUM; i++)
    {
        if(aulUeSpecDrxValue[i] == ucPsDrxLen)
        {
           return NAS_EMM_PARA_VALID;
        }
    }

    return NAS_EMM_PARA_INVALID;
}

/*PC REPLAY MODIFY BY LEILI DELETE*/

/*****************************************************************************
 Function Name   : NAS_LMM_OmInfoIndProc
 Description     : EMM模块处理OM信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-10-31    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_OmInfoIndProc(VOS_VOID)
{
    VOS_UINT32 ulFtmRst = NAS_EMM_FAIL;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_OmInfoIndProc!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_OmInfoIndProc_ENUM
,LNAS_ENTRY);

    if(NAS_EMM_FTM_ACTION_FLAG_OPEN == NAS_EMM_GetFtmInfoActionFlag())
    {
        ulFtmRst = NAS_LMM_CompareEmmDatabaseInfo();
    }

    NAS_LMM_UpdateEmmDatabaseInfo();

    if(NAS_EMM_SUCC == ulFtmRst)
    {
        NAS_LMM_SendOmFtmMsg();
    }
}


/*****************************************************************************
 Function Name   : NAS_LMM_FtmInfoInit
 Description     : 初始化工程模式信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-10-31    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_FtmInfoInit( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_FtmInfoInit!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_FtmInfoInit_ENUM
,LNAS_ENTRY);

    /*lint -e960*/

    NAS_LMM_MEM_SET_S(  NAS_EMM_GetFtmInfoManageAddr(),
                        sizeof(EMM_FTM_INFO_MANAGE_STRU),
                        0,
                        sizeof(EMM_FTM_INFO_MANAGE_STRU));

    NAS_LMM_MEM_SET_S(  NAS_EMM_GetEmmInfoAddr(),
                        sizeof(EMM_DATABASE_INFO_STRU),
                        0,
                        sizeof(EMM_DATABASE_INFO_STRU));

    /*lint +e960*/

    NAS_EMM_GetFtmInfoActionFlag() = NAS_EMM_FTM_ACTION_FLAG_CLOSE;

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_CompareEmmDatabaseInfo
 Description     : 判断EMM模块上报给OM的信息是否发生变化
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-10-31    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_CompareEmmDatabaseInfo( VOS_VOID )
{
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;
    APP_EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    APP_EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;


    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CompareEmmDatabaseInfo!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_CompareEmmDatabaseInfo_ENUM
,LNAS_ENTRY);

    /* 由EMM当前状态获取协议状态 */
    NAS_LMM_PubmGetEmmState(&ulProtoclMainState,
                            &ulProtoclSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());

    if((ulProtoclMainState != NAS_EMM_GetEmmInfoAddr()->enMainState)
        || (ulProtoclSubState != NAS_EMM_GetEmmInfoAddr()->enSubState))
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&NAS_EMM_GetEmmInfoAddr()->stGuti,
                                                    NAS_LMM_GetEmmInfoUeidGutiAddr(),
                                                    sizeof(NAS_MM_GUTI_STRU)))
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&NAS_EMM_GetEmmInfoAddr()->stPlmnId,
                                                    NAS_LMM_GetEmmInfoLastRegPlmnAddr(),
                                                    sizeof(NAS_MM_PLMN_ID_STRU)))
    {
        return NAS_EMM_SUCC;
    }

    if((NAS_EMM_GetEmmInfoAddr()->enEmmCnRejCause) != NAS_EMM_GetFtmInfoCnRej())
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&NAS_EMM_GetEmmInfoAddr()->stTac,
                                                    NAS_LMM_GetEmmInfoLastRegTacAddr(),
                                                    sizeof(NAS_MM_TAC_STRU)))
    {
        return NAS_EMM_SUCC;
    }

    /*lint -e506 -e944 -e636 */
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(TI_NAS_EMM_PTL_T3412);
    /*lint +e506 +e944 +e636 */
    if(NAS_EMM_GetEmmInfoAddr()->ulTimerLen3412 != pstPtlTimer->ulTimerLen)
    {
        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;
}


/*****************************************************************************
 Function Name   : NAS_LMM_UpdateEmmDatabaseInfo
 Description     : EMM模块更新基本信息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-10-31    Draft Enact
*****************************************************************************/
 VOS_VOID NAS_LMM_UpdateEmmDatabaseInfo(VOS_VOID)
 {
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_UpdateEmmDatabaseInfo!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_UpdateEmmDatabaseInfo_ENUM
,LNAS_ENTRY);

    /* 更新EMM状态 */
    NAS_LMM_PubmGetEmmState(&NAS_EMM_GetEmmInfoAddr()->enMainState,
                            &NAS_EMM_GetEmmInfoAddr()->enSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());

    /*lint -e960*/

    /* 更新GUTI信息 */
    NAS_LMM_MEM_CPY_S(  &NAS_EMM_GetEmmInfoAddr()->stGuti,
                        sizeof(NAS_MM_GUTI_STRU),
                        NAS_LMM_GetEmmInfoUeidGutiAddr(),
                        sizeof(NAS_MM_GUTI_STRU));

    /* 更新PlmnId信息 */
    NAS_LMM_MEM_CPY_S(  &NAS_EMM_GetEmmInfoAddr()->stPlmnId,
                        sizeof(NAS_MM_PLMN_ID_STRU),
                        NAS_LMM_GetEmmInfoLastRegPlmnAddr(),
                        sizeof(NAS_MM_PLMN_ID_STRU));

    /* 更新TAC信息 */
    NAS_LMM_MEM_CPY_S(  &NAS_EMM_GetEmmInfoAddr()->stTac,
                        sizeof(NAS_MM_TAC_STRU),
                        NAS_LMM_GetEmmInfoLastRegTacAddr(),
                        sizeof(NAS_MM_TAC_STRU));

    /*lint +e960*/


    /* 更新CN拒绝原因 */
    NAS_EMM_GetEmmInfoAddr()->enEmmCnRejCause = NAS_EMM_GetFtmInfoCnRej();

    /* 更新TimerLen3412 */
    /*lint -e506 -e944 -e636 */
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(TI_NAS_EMM_PTL_T3412);
    /*lint +e506 +e944 +e636 */
    NAS_EMM_GetEmmInfoAddr()->ulTimerLen3412 = pstPtlTimer->ulTimerLen;

    return;
 }

 /*****************************************************************************
  Function Name   : NAS_LMM_RevOmFtmCtrlMsg
  Description     : 收到OM工程模式控制消息
  Input           : 1.MsgBlock   *pMsgStru
  Output          : None
  Return          : VOS_UINT32

  History         :
     1. lifuxin 00253982 2013-10-31 新建

 *****************************************************************************/
 VOS_UINT32   NAS_LMM_RevOmFtmCtrlMsg(MsgBlock   *pMsgStru)
 {
     OM_FTM_CTRL_IND_STRU  *pstOmFtmCtlInfo;

     NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmFtmCtrlMsg!");
     TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmFtmCtrlMsg_ENUM
,LNAS_ENTRY);

     if (VOS_NULL_PTR == pMsgStru)
     {
         NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmFtmCtrlMsg, input point is null!");
         TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmFtmCtrlMsg_ENUM
,LNAS_NULL_PTR);

         return NAS_LMM_MSG_DISCARD;
     }

     pstOmFtmCtlInfo = (OM_FTM_CTRL_IND_STRU *)(VOS_VOID *)pMsgStru;

     if(1 == pstOmFtmCtlInfo->ucActionFlag)
     {
        /*设置工程模式上报功能打开*/
         NAS_EMM_SetFtmOmManageFtmActionFlag(NAS_EMM_FTM_ACTION_FLAG_OPEN);

        /*上报当前信息 */
         NAS_LMM_SendOmFtmMsg();
     }
     else
     {
         /*关闭工程模式上报，*/
          NAS_EMM_SetFtmOmManageFtmActionFlag(NAS_EMM_FTM_ACTION_FLAG_CLOSE);
     }

     return NAS_LMM_MSG_HANDLED;

 }

 /*****************************************************************************
  Function Name   : NAS_LMM_SendOmFtmMsg
  Description     : 发送状态变化消息到OM
  Input           : None
  Output          : None
  Return          : None

  History         :
     1.lifuxin 00253982      2013-10-31  新建

 *****************************************************************************/
 VOS_VOID     NAS_LMM_SendOmFtmMsg(VOS_VOID)
 {
     LNAS_OM_FTM_REPROT_IND_STRU *pFtmMsg;

     NAS_LMM_PUBM_LOG1_INFO("LMM_OM_SendOmFtmMsg: ActionFlag = ", NAS_EMM_GetFtmInfoActionFlag());
     TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendOmFtmMsg_ENUM
,LNAS_FUNCTION_LABEL1,NAS_EMM_GetFtmInfoActionFlag());

     /* 若工程模式关闭，则不发送 */
     if(NAS_EMM_FTM_ACTION_FLAG_OPEN != NAS_EMM_GetFtmInfoActionFlag())
     {
         return;
     }

     /*申请消息内存*/
     pFtmMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LNAS_OM_FTM_REPROT_IND_STRU));

     /*判断申请结果，若失败退出*/
     if (VOS_NULL_PTR == pFtmMsg)
     {
         return;
     }

     /*构造ID_EMM_ESM_PDN_CON_IND消息*/
     /*填充消息头*/

     /*lint -e960*/
     NAS_LMM_COMP_OM_MSG_HEADER(         pFtmMsg,
                                         (sizeof(LNAS_OM_FTM_REPROT_IND_STRU)-
                                         NAS_EMM_LEN_VOS_MSG_HEADER));
     /*lint +e960*/

     /*填充消息ID*/
     pFtmMsg->ulMsgName                  = ID_OM_FTM_REPROT_IND;

     /*填充消息内容*/
     pFtmMsg->ulMsgType                  = OM_ERR_LOG_MSG_FTM_REPORT;
     pFtmMsg->ulMsgSN                    = NAS_EMM_GetFtmInfoMsgSN();
     NAS_EMM_GetFtmInfoMsgSN()++;
     pFtmMsg->ulRptlen                   = sizeof(LNAS_OM_FTM_REPROT_CONTENT_STRU);

     pFtmMsg->stLnasFtmContent.ulMsgModuleID  = OM_ERR_LOG_MOUDLE_ID_LMM;
     pFtmMsg->stLnasFtmContent.usModemId      = 0;
     pFtmMsg->stLnasFtmContent.usProjectID    = 0;
     pFtmMsg->stLnasFtmContent.ulLength       = sizeof(LNAS_LMM_FTM_INFO_STRU);

    /*填充拒绝原因*/
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.ucEmmCnRejCause =
         g_astEmmFtmInfoManage.enEmmCnRejCause;

    /*填充PlmnID*/
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stPlmnId.aucPlmnId[0] =
         g_astEmmInfo.stPlmnId.aucPlmnId[0];
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stPlmnId.aucPlmnId[1] =
         g_astEmmInfo.stPlmnId.aucPlmnId[1];
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stPlmnId.aucPlmnId[2] =
         g_astEmmInfo.stPlmnId.aucPlmnId[2];

    /*填充Guti*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMmeCode.ucMmeCode =
        g_astEmmInfo.stGuti.stMmeCode.ucMmeCode;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMmeGroupId.ucGroupId =
        g_astEmmInfo.stGuti.stMmeGroupId.ucGroupId;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMmeGroupId.ucGroupIdCnt =
        g_astEmmInfo.stGuti.stMmeGroupId.ucGroupIdCnt;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsi =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsi;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsiCnt1 =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsiCnt1;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsiCnt2 =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsiCnt2;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsiCnt3 =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsiCnt3;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stPlmnId.aucPlmnId[0] =
        g_astEmmInfo.stGuti.stPlmnId.aucPlmnId[0];
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stPlmnId.aucPlmnId[1] =
        g_astEmmInfo.stGuti.stPlmnId.aucPlmnId[1];
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stPlmnId.aucPlmnId[2] =
        g_astEmmInfo.stGuti.stPlmnId.aucPlmnId[2];

    /*填充Timer3412*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.ulTimerLen3412 =
        g_astEmmInfo.ulTimerLen3412;

    /*填充Tac*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stTac.ucTac =
        g_astEmmInfo.stTac.ucTac;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stTac.ucTacCnt =
        g_astEmmInfo.stTac.ucTacCnt;

    /*填充mainstate, substate*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stEmmState.ulLmmMainState =
        g_astEmmInfo.enMainState;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stEmmState.ulLmmSubState =
        g_astEmmInfo.enSubState;


     /*向OM模块发送状态变化消息*/
     /*lint -e960*/
     NAS_LMM_SEND_MSG( pFtmMsg);
     /*lint +e960*/

     return;

 }

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 Function Name   : NAS_LMM_GetPositionInfo
 Description     : 获取位置信息
 Input           : pMsg
 Output          : None
 Return          : None
 History         :
    1.yanglei 00307272     2015-09-29 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_GetPositionInfo(LNAS_OM_ERRLOG_POSITION_INFO_STRU *pstPositionInfo)
{


    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_GetPositionInfo Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_GetPositionInfo_ENUM,LNAS_ENTRY);

    pstPresentNetInfo                  = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();

    if(NAS_EMM_NULL_PTR == pstPositionInfo)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_GetPositionInfo PRT NULL.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_GetPositionInfo_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_FAIL;
    }

    NAS_LMM_MEM_CPY_S(                  &pstPositionInfo->stPlmnId,
                                        sizeof(LNAS_OM_ERRLOG_PLMN_ID_STRU),
                                        &pstPresentNetInfo->stPlmnId,
                                        sizeof(LNAS_OM_ERRLOG_PLMN_ID_STRU));

    NAS_LMM_MEM_CPY_S(                  &pstPositionInfo->stTac,
                                        sizeof(LNAS_OM_ERRLOG_TAC_STRU),
                                        &pstPresentNetInfo->stTac,
                                        sizeof(LNAS_OM_ERRLOG_TAC_STRU));

    pstPositionInfo->ulCellId         = pstPresentNetInfo->ulCellId;

    pstPositionInfo->ulArfcn          = pstPresentNetInfo->ulArfcn;

    pstPositionInfo->aulLteBand[0]    = pstPresentNetInfo->aulLteBand[0];

    pstPositionInfo->aulLteBand[1]    = pstPresentNetInfo->aulLteBand[1];
    return NAS_LMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgEsmSaveErrlogInd
 Description     : 保存ESM发给EMM的ESM ERRLOG信息到环形buffer
 Input           : pMsg
 Output          : None
 Return          : None
 History         :
    1.lifuxin 00253982     2014-12-31 Draft Enact
*****************************************************************************/
/*lint -e826*/
VOS_UINT32 NAS_LMM_PreProcMsgEsmSaveErrlogInd(MsgBlock *     pMsg)
{
    EMM_ESM_SAVE_ERRLOG_IND_STRU        *pstSaveEsmErrMsg = VOS_NULL;
    VOS_VOID                            *pstEsmErrlogRslt = VOS_NULL;
    VOS_UINT32                          ulLength = 0;
    VOS_UINT32                          ulResult = 0;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgEsmSaveErrlogInd Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgEsmSaveErrlogInd_ENUM
,LNAS_ENTRY);

    /*取出buffer中的ESM errlog数据*/
    pstSaveEsmErrMsg = (EMM_ESM_SAVE_ERRLOG_IND_STRU*)pMsg;
    pstEsmErrlogRslt = (VOS_VOID*)pstSaveEsmErrMsg->stEmmEsmErrlog.aucEsmMsg;
    ulLength = pstSaveEsmErrMsg->stEmmEsmErrlog.ulEsmMsgSize;

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)pstEsmErrlogRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_LMM_PreProcMsgEsmSaveErrlogInd: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_LMM_PreProcMsgEsmSaveErrlogInd_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e826*/
/*****************************************************************************
Function Name   : NAS_LMM_RevNvCtrl
Description     : nv控制模块
Input           : None
Output          : None
Return          : VOS_UINT32

History         :

1.lifuxin       00253982     2014-12-29    Errlog 重构
*****************************************************************************/
VOS_VOID NAS_LMM_RevNvCtrl(VOS_VOID)
{
    VOS_UINT32                              ulRslt;
    NV_ID_ERR_LOG_CTRL_INFO_STRU            stOMErrLogCtrlInfo;
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevNvCtrl!!!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_RevNvCtrl_ENUM
,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(  &stOMErrLogCtrlInfo,
                        sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU),
                        0x00,
                        sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));

    ulRslt = LPs_NvimItem_Read(en_NV_Item_ErrLogCtrlInfo, &stOMErrLogCtrlInfo, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU) );
    if(PS_SUCC != ulRslt)
    {
        return;
    }

    /* 更新ERRLOG控制标识, 0表示关闭errlog， 1表示开启errlog*/
    if ((VOS_FALSE == stOMErrLogCtrlInfo.ucAlmStatus)
     || (VOS_TRUE  == stOMErrLogCtrlInfo.ucAlmStatus))
    {
        NAS_EMM_SetErrlogCtrlInfoCtrlFlag(stOMErrLogCtrlInfo.ucAlmStatus);
    }

    /*根据下发的errlog等级去决定是否存储log信息*/
    if ((stOMErrLogCtrlInfo.ucAlmLevel >= LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (stOMErrLogCtrlInfo.ucAlmLevel <= LNAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        NAS_EMM_SetErrlogCtrlInfoALMLevel(stOMErrLogCtrlInfo.ucAlmLevel);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_RevOmErrlogCtrlMsg
 Description     : EMM模块收到OM商用Errlog控制消息
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-11-07    Draft Enact
    2.lifuxin       00253982     2014-12-29    Errlog 重构
 *****************************************************************************/
VOS_UINT32 NAS_LMM_RevOmErrlogCtrlMsg(MsgBlock   *pMsgStru)
{
    OM_ERROR_LOG_CTRL_IND_STRU  *pstOmErrlogCtlInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmErrlogCtrlMsg!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmErrlogCtrlMsg_ENUM
,LNAS_ENTRY);

    if (VOS_NULL_PTR == pMsgStru)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmErrlogCtrlMsg, input point is null!");
       TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmErrlogCtrlMsg_ENUM
,LNAS_NULL_PTR);

        return NAS_LMM_MSG_DISCARD;
    }

    pstOmErrlogCtlInfo = (OM_ERROR_LOG_CTRL_IND_STRU *)(VOS_VOID *)pMsgStru;

    /* 更新ERRLOG控制标识, 0表示关闭errlog， 1表示开启errlog*/
    if ((VOS_FALSE == pstOmErrlogCtlInfo->ucAlmStatus)
     || (VOS_TRUE  == pstOmErrlogCtlInfo->ucAlmStatus))
    {
        NAS_EMM_SetErrlogCtrlInfoCtrlFlag(pstOmErrlogCtlInfo->ucAlmStatus);
    }

    /*根据下发的errlog等级去决定是否存储log信息*/
    if ((pstOmErrlogCtlInfo->ucAlmLevel >= LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (pstOmErrlogCtlInfo->ucAlmLevel <= LNAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        NAS_EMM_SetErrlogCtrlInfoALMLevel(pstOmErrlogCtlInfo->ucAlmLevel);
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
Function Name   : NAS_EMM_GetErrLogRingBufUseBytes
Description     : 获取环形buffer已经使用数据的字节数
Input           : None
Output          : None
Return          : VOS_UINT32 字节数

History         :
 1. lifuxin 00253982 2013-11-07 新建
*****************************************************************************/

VOS_UINT32 NAS_EMM_GetErrLogRingBufUseBytes(VOS_VOID)
{
    return (VOS_UINT32)OM_RingBufferNBytes(NAS_EMM_GetErrlogBufferInfoRingBuffer());
}

/*****************************************************************************
Function Name   : NAS_EMM_GetErrLogRingBufContent
Description     : 获取环形buffer已经使用数据的内容
Input           : None
Output          : None
Return          : VOS_UINT32 获取实际字节流的总数

History         :
 1. lifuxin 00253982 2013-12-29 新建
*****************************************************************************/
 VOS_UINT32 NAS_EMM_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    return (VOS_UINT32)OM_RingBufferGet(NAS_EMM_GetErrlogBufferInfoRingBuffer(), pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
Function Name   : NAS_EMM_CleanErrLogRingBuf
Description     : 清空环形buffer
Input           : None
Output          : None
Return          : NONE

History         :
 1. lifuxin 00253982 2013-12-29 新建
*****************************************************************************/
VOS_VOID NAS_EMM_CleanErrLogRingBuf(VOS_VOID)
{
    OM_RingBufferFlush(NAS_EMM_GetErrlogBufferInfoRingBuffer());

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetErrLogAlmLevel
 Description     : 根据ALM ID去获取对应的告警等级
 Input           : enAlmId
 Output          : None
 Return          : VOS_UINT16 返回对应的log等级

 History         :
    1. lifuxin 00253982 2014-12-29 新建
*****************************************************************************/
VOS_UINT16 NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId)
{
     VOS_UINT16                          usTableLen;
     VOS_UINT16                          usStep;

     /* 获取Tab表长度 */
     usTableLen = sizeof(g_astLNasErrAlmLevelTb)/sizeof(g_astLNasErrAlmLevelTb[0]);

     /* 查表返回对应Alm ID的log等级 */
     for (usStep = 0; usStep < usTableLen; usStep++)
     {
         if (g_astLNasErrAlmLevelTb[usStep].enAlmID == enAlmId)
         {
             return g_astLNasErrAlmLevelTb[usStep].usLogLevel;
         }
     }

 /* 未查到，返回未定义等级 */
 return LNAS_ERR_LOG_CTRL_LEVEL_NULL;
}

/*****************************************************************************
 函 数 名  : NAS_EMM_GetErrLogUnsoliReportType
 功能描述  : 获取ERR LOG主动上报类型
 输入参数  : LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId
 输出参数  : 无
 返 回 值  : EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月5日
    作    者   : wangchen 00209181
    修改内容   : 新生成函数

*****************************************************************************/
EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_UINT16 NAS_EMM_GetErrLogUnsoliReportType(LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId)
{
    VOS_UINT16                          usTableLen;
    VOS_UINT16                          usStep;

    /* 获取Tab表长度 */
    usTableLen = sizeof(g_astLNasErrAlmUnsoliReportTypeTb)/sizeof(g_astLNasErrAlmUnsoliReportTypeTb[0]);

    /* 查表返回对应Alm ID的log等级 */
    for (usStep = 0; usStep < usTableLen; usStep++)
    {
        if (g_astLNasErrAlmUnsoliReportTypeTb[usStep].enAlmID == enAlmId)
        {
            return g_astLNasErrAlmUnsoliReportTypeTb[usStep].enReportType;
        }
    }

    /* 未查到，返回未定义等级 */
    return EMM_ERR_LOG_REPORT_TYPE_BUTT;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndAcpuOmErrLogReportCnf
 Description     : OM模块请求errlog，通过该函数上报
 Input           : pbuffer，填充的内容, ulBufUseLen数据的有效内容
 Output          : None
 Return          : None

 History         :
    1. lifuxin 00253982 2014-12-29 新建
*****************************************************************************/
VOS_VOID NAS_EMM_SndAcpuOmErrLogReportCnf(
 VOS_CHAR                           *pbuffer,
 VOS_UINT32                          ulBufUseLen
)
{
     LNAS_OM_ERR_LOG_REPORT_CNF_STRU     *pstReqErrlogCnf = VOS_NULL_PTR;
     VOS_UINT32                          ulMsgLen;

     /* 上报的消息总长度 */
     ulMsgLen  = sizeof(LNAS_OM_ERR_LOG_REPORT_CNF_STRU) - 4 + ulBufUseLen;

     /* 消息空间申请 */
     pstReqErrlogCnf = (VOS_VOID*)NAS_LMM_ALLOC_MSG(ulMsgLen);
     if (VOS_NULL_PTR == pstReqErrlogCnf)
     {
         NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SndAcpuOmErrLogReportCnf, Alloc mem error!");
         TLPS_PRINT2LAYER_INFO(NAS_EMM_SndAcpuOmErrLogReportCnf_ENUM
,LNAS_NULL_PTR);
         return;
     }

     pstReqErrlogCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
     pstReqErrlogCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
     pstReqErrlogCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
     pstReqErrlogCnf->ulSenderPid      = PS_PID_MM;
     pstReqErrlogCnf->ulMsgName        = ID_LNAS_OM_ERR_LOG_REPORT_CNF;
     pstReqErrlogCnf->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
     pstReqErrlogCnf->ulMsgSN          = 0;
     pstReqErrlogCnf->ulRptlen         = ulBufUseLen;

     if (VOS_NULL_PTR != pbuffer)
     {
         NAS_LMM_MEM_CPY_S(pstReqErrlogCnf->aucContent, ulBufUseLen, pbuffer, ulBufUseLen);
     }

     NAS_LMM_SEND_MSG(pstReqErrlogCnf);

     return;
}

/*****************************************************************************
Function Name   : NAS_LMM_RevOmReadErrlogReq
Description     : LMM收到读取errlog信息请求
Input           : 1.MsgBlock   *pMsgStru
Output          : None
Return          : VOS_UINT32

History         :
 1. lifuxin 00253982 2013-11-07 新建
 2. lifuxin 00253982 2014-12-29 errlog 重构
*****************************************************************************/
VOS_UINT32   NAS_LMM_RevOmReadErrlogReq(MsgBlock   *pMsgStru)
{
    VOS_CHAR                                       *pbuffer   = VOS_NULL_PTR;
    VOS_UINT32                                     ulBufUseLen;
    VOS_UINT32                                     ulRealLen;
    VOS_UINT32                                     ulTotalLen;
    LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU        stLnasErrLogOverflowEvent;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmReadErrlogReq!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmReadErrlogReq_ENUM
,LNAS_ENTRY);

    if (VOS_NULL_PTR == pMsgStru)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmReadErrlogReq, input point is null!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmReadErrlogReq_ENUM
,LNAS_NULL_PTR);

        return NAS_LMM_MSG_DISCARD;
    }

    /* RING BUFFER数据长度 */
    ulBufUseLen = NAS_EMM_GetErrLogRingBufUseBytes();

    ulTotalLen = ulBufUseLen + sizeof(LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU);

    pbuffer = (VOS_CHAR *)NAS_LMM_MEM_ALLOC(ulTotalLen);
    if (VOS_NULL_PTR == pbuffer)
    {
        /* 发送ID_OM_ERR_LOG_REPORT_CNF内容为空的消息给OM */
        NAS_EMM_SndAcpuOmErrLogReportCnf(VOS_NULL_PTR, 0);
        return VOS_TRUE;
    }

    NAS_LMM_MEM_SET_S(pbuffer, ulTotalLen, 0, ulTotalLen);

    /* 获取RING BUFFER的内容 */
    ulRealLen = NAS_EMM_GetErrLogRingBufContent(pbuffer, ulBufUseLen);
    if (ulRealLen != ulBufUseLen)
    {
        /* 发送ID_OM_ERR_LOG_REPORT_CNF内容为空的消息给OM */
        NAS_EMM_SndAcpuOmErrLogReportCnf(VOS_NULL_PTR, 0);
        NAS_LMM_MEM_FREE(pbuffer);
        return VOS_TRUE;
    }

    /* 将缓冲区溢出次数信息追加在RingBuf后面 */
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stLnasErrLogOverflowEvent.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL,
                                      NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL),
                                      VOS_GetSlice(),
                                      (sizeof(LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stLnasErrLogOverflowEvent.ulOverflowCount = NAS_EMM_GetErrlogBufferInfoOverflowCnt();

    NAS_LMM_MEM_CPY_S(  pbuffer + ulBufUseLen,
                        ulTotalLen - ulBufUseLen,
                        &stLnasErrLogOverflowEvent,
                        sizeof(stLnasErrLogOverflowEvent));

    /* 获取完了后需要将RINGBUFFER清空 */
    NAS_EMM_CleanErrLogRingBuf();

    /* 重置溢出计数 */
    NAS_EMM_SetErrlogBufferInfoOverflowCnt(0);

    /* 发送ID_OM_ERR_LOG_REPORT_CNF消息给ACPU OM */
    NAS_EMM_SndAcpuOmErrLogReportCnf(pbuffer, ulTotalLen);

    NAS_LMM_MEM_FREE(pbuffer);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
Function Name   : NAS_EMM_IsErrLogNeedRecord
Description     : 判断当前错误流程是否需要记录
Input           : 对应的log记录等级
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-29 errlog 新建
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsErrLogNeedRecord(VOS_UINT16 usLevel)
{
     /* Log开关关闭，不需要上报 */
     if (0 == NAS_EMM_GetErrlogCtrlInfoCtrlFlag())
     {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsErrLogNeedRecord1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsErrLogNeedRecord_ENUM
,LNAS_FUNCTION_LABEL1);
        return VOS_FALSE;
     }

     /* 模块log级别usLevel大于用户设置的log上报级别或usLevel无效，不需要上报 */
     if ((NAS_EMM_GetErrlogCtrlInfoALMLevel() < usLevel)
      || (LNAS_ERR_LOG_CTRL_LEVEL_NULL == usLevel))
     {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsErrLogNeedRecord2");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsErrLogNeedRecord_ENUM
,LNAS_FUNCTION_LABEL2);
        return VOS_FALSE;
     }

     return VOS_TRUE;
}

/*****************************************************************************
 Function Name   :  NAS_LMM_CnCauseProc
 Description     :  将内部网络拒绝原因转换成Lnas error log对应的枚举值
 Input           :  ucCauseCode 表示网络拒绝原因

 Output          :  输出一个Lnas error log的枚举变量
 Return          :

 History         :
    1.lifuxin 00253982         2013-11-07  新增文件
    2.lifuxin 00253982         2014-12-29  errlog重构

*****************************************************************************/
EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16  NAS_LMM_CnCauseProc(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucCnCause)
{
    EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16   ulErrId = 0;
    VOS_UINT32 i;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CnCauseProc!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_CnCauseProc_ENUM
,LNAS_ENTRY);

    for(i = 0; i < g_astEmmErrlogCnCauseNum; i++)
    {
        if(ucCnCause == g_astEmmErrlogCnCauseMap[i].ulCauseId)
        {
            ulErrId = g_astEmmErrlogCnCauseMap[i].ulErrorlogID;
            break;
        }
    }
    if(g_astEmmErrlogCnCauseNum == i)
    {
        ulErrId = EMM_OM_ERRLOG_CN_CAUSE_OTHERS;
    }

    return ulErrId;
}

/*****************************************************************************
Function Name   : NAS_EMM_PutErrLogRingBuf
Description     : 将errlog信息写入到环形buffer
Input           : 写入的数据，已经对应的长度
Output          : None
Return          : 实际写入的长度

History         :
 1. lifuxin 00253982 2014-12-30 errlog 新建
*****************************************************************************/
VOS_UINT32 NAS_EMM_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pLnasRingBuffer;

    pLnasRingBuffer = NAS_EMM_GetErrlogBufferInfoRingBuffer();
    if (VOS_NULL_PTR == pLnasRingBuffer)
    {
        return 0;
    }

    /* 如果写入比RING BUFFER还大则不写入 */
    if (ulbytes > LNAS_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* 获取RING BUFFER剩余空间大小 */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pLnasRingBuffer);

    ulCount = NAS_EMM_GetErrlogBufferInfoOverflowCnt();
    /* 如果剩余空间不足写入的大小，则清空RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        NAS_EMM_SetErrlogBufferInfoOverflowCnt(ulCount);

        OM_RingBufferFlush(pLnasRingBuffer);
    }

    /* 写入RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pLnasRingBuffer, pbuffer, (VOS_INT)ulbytes);
}



/*****************************************************************************
 Function Name   :  NAS_LMM_EstCnfFailRsltProc
 Description     :  将LRRC的建链原因值转成ERRLOG的原因值
 Input           :

 Output          :
 Return          :

 History         :
    1.lifuxin 00253982         2015-02-10  新函数
*****************************************************************************/
EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32  NAS_LMM_EstCnfFailRsltProc(LRRC_LNAS_EST_RESULT_ENUM_UINT32 ulLrrcEstCnfRslt)
{
    EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32   ulErrlogEstRslt = 0;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_EstCnfFailRsltProc!");

    switch(ulLrrcEstCnfRslt)
    {
        case LRRC_EST_DELING:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_DELING;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_CALL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CALL;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_SIGNAL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_SIGNAL;
            break;
        case LRRC_EST_ACCESS_BARRED_ALL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_ALL;
            break;
        case LRRC_EST_EST_CONN_FAIL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_EST_CONN_FAIL;
            break;
        case LRRC_EST_CELL_SEARCHING:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_CELL_SEARCHING;
            break;
        case LRRC_EST_ACCESS_BARRED_MT_CALL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MT_CALL;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_CSFB:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CSFB;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CALL_AND_CSFB;
            break;
        default:
             ulErrlogEstRslt = EMM_OM_ERRLOG_EST_RESULT_BUTT;
            break;
    }

    return ulErrlogEstRslt;
}

/*****************************************************************************
 Function Name   :  NAS_LMM_DataCnfFailRsltProc
 Description     :  将LRRC的直传原因值转成ERRLOG的原因值
 Input           :

 Output          :
 Return          :

 History         :
    1.lifuxin 00253982         2015-02-10  新函数
*****************************************************************************/
EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32  NAS_LMM_DataCnfFailRsltProc(LRRC_LMM_SEND_RSLT_ENUM_UINT32 ulLrrcDataCnfRslt)
{
    EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32   ulErrlogDataCnfRslt = 0;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_DataCnfFailRsltProc!");

    switch(ulLrrcDataCnfRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_HO;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_CONN_REL;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_CTRL_NOT_CONN:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_CTRL_NOT_CONN;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_TXN;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_RLF;
            break;
        default:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_BUTT;
            break;
    }

    return ulErrlogDataCnfRslt;
}
/*****************************************************************************
Function Name   : NAS_LMM_AttachErrRecord
Description     : attach流程记录错误信息
Input           : attach fail以及对应的错误类型
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-29 errlog 新建
*****************************************************************************/
VOS_VOID NAS_EMM_AttachErrRecord(
         VOS_VOID*                         pstAttachFail,
         EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)
{
    EMM_ERR_INFO_ATTACH_RESULT_EVENT_STRU                   stAttachRslt;
    NAS_EMM_CN_ATTACH_ACP_STRU                              *pstCnAttachEpsOnly = VOS_NULL_PTR;
    LRRC_LMM_EST_CNF_STRU                                   *pstEstCnfMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_CNF_STRU                                  *pRrcDataCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_AttachErrRecord!!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AttachErrRecord_ENUM
,LNAS_ENTRY);
    if(VOS_NULL_PTR == pstAttachFail)
    {
        return;
    }

    /*根据attach不同的fail类型决定传入的结构类型*/
    switch(enErrType)
    {
        case EMM_OM_ERRLOG_TYPE_CN_REJ:
            break;
        case EMM_OM_ERRLOG_TYPE_EPS_ONLY:
            pstCnAttachEpsOnly = (NAS_EMM_CN_ATTACH_ACP_STRU*)(VOS_VOID*)pstAttachFail;
            break;
        case EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL:
            pstEstCnfMsg = (LRRC_LMM_EST_CNF_STRU*)(VOS_VOID*)pstAttachFail;
            break;
        case EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL:
            pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU*)(VOS_VOID*)pstAttachFail;
            break;
        case EMM_OM_ERRLOG_TYPE_TIMEOUT:
        case EMM_OM_ERRLOG_TYPE_LRRC_REL:
            break;
        default:
            NAS_LMM_PUBM_LOG_ERR("NAS_EMM_AttachErrRecord: Err Type");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttachErrRecord_ENUM
,LNAS_ERROR);
            return;
    }

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_ATTACH_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stAttachRslt, ulLength, 0x00, ulLength);

    /*填充attach fail异常场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stAttachRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    stAttachRslt.enErrType = enErrType;

    /*lint -e613*/
    /*填充对于attach rej引起的attach fail异常相关的信息，目前填充拒绝原因值，以及attach类型*/
    if(EMM_OM_ERRLOG_TYPE_CN_REJ == stAttachRslt.enErrType)
    {
        stAttachRslt.stAttachCnRej.enCnRejCause = NAS_LMM_CnCauseProc(NAS_EMM_GLO_AD_GetAttRejCau());
        stAttachRslt.stAttachCnRej.enOriginalRejectCause =
                           NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(NAS_EMM_GLO_AD_GetAttRejCau()));
        stAttachRslt.stAttachCnRej.enReqType = (VOS_UINT16)NAS_EMM_GLO_GetCnAttReqType();
    }
    else if(EMM_OM_ERRLOG_TYPE_EPS_ONLY == stAttachRslt.enErrType)
    {
        if (NAS_EMM_BIT_SLCT == pstCnAttachEpsOnly->ucBitOpEmmCau)
        {
            stAttachRslt.stAttachCnRej.enCnRejCause = NAS_LMM_CnCauseProc(pstCnAttachEpsOnly->ucEMMCause); /* [false alarm]:代码保证不会访问空指针 */
            /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, begin
            attach accept中的原因不会被替换 */
            stAttachRslt.stAttachCnRej.enOriginalRejectCause = NAS_LMM_CnCauseProc(pstCnAttachEpsOnly->ucEMMCause);
        }
        else
        {
            stAttachRslt.stAttachCnRej.enCnRejCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
            stAttachRslt.stAttachCnRej.enOriginalRejectCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
        }
        stAttachRslt.stAttachCnRej.enReqType = (VOS_UINT16)NAS_EMM_GLO_GetCnAttReqType();
    }
    else if(EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL == stAttachRslt.enErrType)
    {
        stAttachRslt.enEstCnfRslt = NAS_LMM_EstCnfFailRsltProc(pstEstCnfMsg->enResult);/* [false alarm]:代码保证不会访问空指针 */
    }
    else if(EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL == stAttachRslt.enErrType)
    {
        stAttachRslt.enDataCnfRslt = NAS_LMM_DataCnfFailRsltProc(pRrcDataCnf->enSendRslt);/* [false alarm]:代码保证不会访问空指针 */
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_AttachErrRecord: No item to Save!");
    }
    /*lint +e613*/
    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stAttachRslt.stPositionInfo));

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stAttachRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_AttachErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_AttachErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,
                                        ulLength, ulResult);
    }

    return;
}

 /*****************************************************************************
 Function Name   :  NAS_LMM_TauTypeTrans
 Description     :  网侧TAU类型与发给OM的TAU类型映射
 Input           :

 Output          :
 Return          :

 History         :
   1.lifuxin 00253982         2014-12-30  新建
*****************************************************************************/
EMM_ERR_LOG_TAU_TYPE_ENUM_UINT16  NAS_LMM_TauTypeTrans(NAS_EMM_CN_TAU_TYPE_ENUM_UINT32 ulTauType)
{
    EMM_ERR_LOG_TAU_TYPE_ENUM_UINT16   ulErrTauType = 0;

    switch(ulTauType)
    {
        case NAS_EMM_CN_TAU_TYPE_TA_UPDATING:
            ulErrTauType = EMM_ERR_LOG_TA_UPDATING;
            break;

        case NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING:
            ulErrTauType = EMM_ERR_LOG_COMBINED_TA_LA_UPDATING;
            break;

        case NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI:
            ulErrTauType = EMM_ERR_LOG_COMBINED_TA_LA_WITH_IMSI;
            break;

        case NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING:
            if(NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
            {
                ulErrTauType = EMM_ERR_LOG_PS_PERIODIC_UPDATING;
            }
            else if(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
            {
                ulErrTauType = EMM_ERR_LOG_CS_PS_PERIODIC_UPDATING;
            }
            else
            {

            }
            break;

        default:
            break;
    }

    return ulErrTauType;
}


/*****************************************************************************
Function Name   : NAS_LMM_TAUErrRecord
Description     : TAU流程记录错误信息
Input           : TAU fail以及对应的错误类型
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog 新建
*****************************************************************************/
VOS_VOID NAS_EMM_TAUErrRecord(
         VOS_VOID*                         pstTAUFail,
         EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)
{
    EMM_ERR_INFO_TAU_RESULT_EVENT_STRU                      stTAURslt;
    NAS_EMM_CN_TAU_ACP_STRU                                 *pstCnTAUEpsOnly = VOS_NULL_PTR;
    LRRC_LMM_EST_CNF_STRU                                   *pstEstCnfMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_CNF_STRU                                  *pRrcDataCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_TAUErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAUErrRecord_ENUM
,LNAS_ENTRY);
    if(VOS_NULL_PTR == pstTAUFail)
    {
        return;
    }

    /*根据attach不同的fail类型决定传入的结构类型*/
    switch(enErrType)
    {
        case EMM_OM_ERRLOG_TYPE_CN_REJ:
            break;
        case EMM_OM_ERRLOG_TYPE_EPS_ONLY:
            pstCnTAUEpsOnly = (NAS_EMM_CN_TAU_ACP_STRU*)(VOS_VOID*)pstTAUFail;
            break;
        case EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL:
            pstEstCnfMsg = (LRRC_LMM_EST_CNF_STRU*)(VOS_VOID*)pstTAUFail;
            break;
        case EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL:
            pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU*)(VOS_VOID*)pstTAUFail;
            break;
        case EMM_OM_ERRLOG_TYPE_TIMEOUT:
        case EMM_OM_ERRLOG_TYPE_LRRC_REL:
            break;
        default:
            NAS_LMM_PUBM_LOG_ERR("NAS_EMM_TAUErrRecord: Err Type");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAUErrRecord_ENUM
,LNAS_ERROR);
            return;
    }

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_TAU_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stTAURslt, ulLength, 0x00, ulLength);

    /*填充TAU fail异常场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stTAURslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    stTAURslt.enErrType = enErrType;

    /*lint -e613*/
    /*填充对于TAU rej引起的TAU fail异常相关的信息，目前填充拒绝原因值，以及TAU类型*/
    if(EMM_OM_ERRLOG_TYPE_CN_REJ == stTAURslt.enErrType)
    {
        stTAURslt.stTauCnRej.enCnRejCause = NAS_LMM_CnCauseProc(NAS_EMM_TAU_GetEmmTauCnRejCause());
        stTAURslt.stTauCnRej.enOriginalRejectCause =
                              NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(NAS_EMM_TAU_GetEmmTauCnRejCause()));
        stTAURslt.stTauCnRej.enReqType = NAS_LMM_TauTypeTrans(NAS_EMM_TAU_GetTAUtype());
    }
    else if(EMM_OM_ERRLOG_TYPE_EPS_ONLY == stTAURslt.enErrType)
    {
        if (NAS_EMM_BIT_SLCT == pstCnTAUEpsOnly->ucBitOpEmmCau)
        {
            stTAURslt.stTauCnRej.enCnRejCause = NAS_LMM_CnCauseProc(pstCnTAUEpsOnly->ucEMMCause);/* [false alarm]:代码保证不会访问空指针 */
            /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, begin
            tau accept中的cause不会做替换，所以原始拒绝原因值和适配的原因一样 */
            stTAURslt.stTauCnRej.enOriginalRejectCause = NAS_LMM_CnCauseProc(pstCnTAUEpsOnly->ucEMMCause);
        }
        else
        {
            stTAURslt.stTauCnRej.enCnRejCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
            stTAURslt.stTauCnRej.enOriginalRejectCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
        }
        stTAURslt.stTauCnRej.enReqType = NAS_LMM_TauTypeTrans(NAS_EMM_TAU_GetTAUtype());
    }
    else if(EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL == stTAURslt.enErrType)
    {
        stTAURslt.enEstCnfRslt = NAS_LMM_EstCnfFailRsltProc(pstEstCnfMsg->enResult);/* [false alarm]:代码保证不会访问空指针 */
    }
    else if(EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL == stTAURslt.enErrType)
    {
        stTAURslt.enDataCnfRslt = NAS_LMM_DataCnfFailRsltProc(pRrcDataCnf->enSendRslt);/* [false alarm]:代码保证不会访问空指针 */
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_TAUErrRecord: No item to Save!");
    }
    /*lint +e613*/

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stTAURslt.stPositionInfo));
    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stTAURslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_TAUErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_TAUErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}


/*****************************************************************************
Function Name   : NAS_EMM_DetachErrRecord
Description     : Detach流程记录错误信息,目前只关心网络侧detach的场景
Input           : 网络侧detach的结构
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog 新建
*****************************************************************************/
VOS_VOID NAS_EMM_DetachErrRecord(
        NAS_EMM_CN_DETACH_REQ_MT_STRU       *pstCnDetach)
{
    EMM_ERR_INFO_MT_DETACH_RESULT_EVENT_STRU                stDetachRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_DetachErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DetachErrRecord_ENUM
,LNAS_ENTRY);
    if(VOS_NULL_PTR == pstCnDetach)
    {
       return;
    }

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_MT_DETACH_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stDetachRslt, ulLength, 0x00, ulLength);

    /*填充Cn Detach fail异常场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stDetachRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*填充Cn Detach相关上报项*/
    /*如果网络侧带原因值，则直接填充，如果不带原因值，则设置成NULL*/
    if(NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
    {
        stDetachRslt.enCnDetCause = NAS_LMM_CnCauseProc(NAS_EMM_GLO_AD_GetDetEmmCau());
        stDetachRslt.enOriginalRejectCause = NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }
    else
    {
        stDetachRslt.enCnDetCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
        stDetachRslt.enOriginalRejectCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
    }
    stDetachRslt.enCnDetReqType = pstCnDetach->ucDetType;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stDetachRslt.stPositionInfo));
    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stDetachRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_DetachErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_DetachErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_NorServiceErrRecord
Description     : Normal Service 流程相关异常上报
Input           :
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog 新建
*****************************************************************************/
VOS_VOID NAS_EMM_NorServiceErrRecord(
            VOS_VOID*                         pstNorServiceFail,
            EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)

{
    EMM_ERR_INFO_NOR_SERVICE_RESULT_EVENT_STRU              stNorServerRslt;
    NAS_EMM_CN_SER_REJ_STRU                                 *pstCnSerRej = VOS_NULL_PTR;
    LRRC_LMM_EST_CNF_STRU                                   *pstEstCnfMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_CNF_STRU                                  *pRrcDataCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_NorServiceErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_NorServiceErrRecord_ENUM
,LNAS_ENTRY);
    if(VOS_NULL_PTR == pstNorServiceFail)
    {
        return;
    }

    /*根据service不同的fail类型决定传入的结构类型*/
    switch(enErrType)
    {
        case EMM_OM_ERRLOG_TYPE_CN_REJ:
            pstCnSerRej = (NAS_EMM_CN_SER_REJ_STRU*)(VOS_VOID*)pstNorServiceFail;
            break;
        case EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL:
            pstEstCnfMsg = (LRRC_LMM_EST_CNF_STRU*)(VOS_VOID*)pstNorServiceFail;
            break;
        case EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL:
            pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU*)(VOS_VOID*)pstNorServiceFail;
            break;
        case EMM_OM_ERRLOG_TYPE_TIMEOUT:
        case EMM_OM_ERRLOG_TYPE_LRRC_REL:
            break;
        default:
            NAS_LMM_PUBM_LOG_ERR("NAS_EMM_NorServiceErrRecord: Err Type");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_NorServiceErrRecord_ENUM
,LNAS_ERROR);
            return;
    }

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_NOR_SERVICE_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stNorServerRslt, ulLength, 0x00, ulLength);

    /*填充Service异常场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stNorServerRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stNorServerRslt.enErrType = enErrType;

    /*lint -e613*/
    if(EMM_OM_ERRLOG_TYPE_CN_REJ == stNorServerRslt.enErrType)
    {
        stNorServerRslt.stNorServiceCnRej.enCnRejCause =
                                        NAS_LMM_CnCauseProc(pstCnSerRej->ucEMMCause);/* [false alarm]:代码保证不会访问空指针 */
        stNorServerRslt.stNorServiceCnRej.enOriginalRejectCause  =
                                        NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(pstCnSerRej->ucEMMCause));
    }
    else if(EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL == stNorServerRslt.enErrType)
    {
        stNorServerRslt.enEstCnfRslt = NAS_LMM_EstCnfFailRsltProc(pstEstCnfMsg->enResult);/* [false alarm]:代码保证不会访问空指针 */
    }
    else if(EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL == stNorServerRslt.enErrType)
    {
        stNorServerRslt.enDataCnfRslt = NAS_LMM_DataCnfFailRsltProc(pRrcDataCnf->enSendRslt);/* [false alarm]:代码保证不会访问空指针 */
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_NorServiceErrRecord: No item need to Save!");
    }
    /*lint +e613*/

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stNorServerRslt.stPositionInfo));

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stNorServerRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_NorServiceErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_NorServiceErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_ExtServiceErrRecord
Description     : Service 流程相关异常上报
Input           :
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog 新建
*****************************************************************************/
VOS_VOID NAS_EMM_ExtServiceErrRecord(
        NAS_EMM_CN_CAUSE_ENUM_UINT8                 enCnRejCause,
        EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM_UINT8       enCsfbFailCause)
{
    EMM_ERR_INFO_EXT_SERVICE_RESULT_EVENT_STRU              stExtServerRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_ExtServiceErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ExtServiceErrRecord_ENUM
,LNAS_ENTRY);

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_EXT_SERVICE_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stExtServerRslt, ulLength, 0x00, ulLength);

    /*填充Service异常场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stExtServerRslt.stHeader,
                                    VOS_GetModemIDFromPid(PS_PID_MM),
                                    LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL,
                                    usLevel,
                                    VOS_GetSlice(),
                                    (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stExtServerRslt.enCsfbFailCause = enCsfbFailCause;
    stExtServerRslt.enCnRejCause = NAS_LMM_CnCauseProc(enCnRejCause);
    stExtServerRslt.enOriginalRejectCause =
                     NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(enCnRejCause));

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stExtServerRslt.stPositionInfo));

    /*
     将异常信息写入Buffer中
     实际写入的字符数与需要写入的不等则打印异常
    */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stExtServerRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_ExtServiceErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_ExtServiceErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_DetachErrRecord
Description     : PS IMSI PAGING流程导致丢网上报errlog信息
Input           : IMSI PAGING结构
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog 新建
 2. wangchen 00209181 2015-08-04 Modify:CHR
*****************************************************************************/
VOS_VOID NAS_EMM_PagingErrRecord
(
    EMM_OM_ERRLOG_PAGING_ENUM_UINT16  enPagingType,
    EMM_OM_LMM_PAGING_FAIL_CAUSE_ENUM_UINT8 enPagingFailCause
)
{
    EMM_ERR_INFO_PAGING_RESULT_EVENT_STRU                   stPagingRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;


    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PagingErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PagingErrRecord_ENUM
,LNAS_ENTRY);

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);


    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_PAGING_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stPagingRslt, ulLength, 0x00, ulLength);

    /*填充PS IMSI PAGING fail异常场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stPagingRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*填充IMSI PAGING相关上报项*/
    stPagingRslt.enPagingProcess = enPagingType;

    stPagingRslt.enPagingFailCause  = enPagingFailCause;

    stPagingRslt.enMainState            = NAS_LMM_GetEmmCurFsmMS();
    stPagingRslt.enSubState             = NAS_LMM_GetEmmCurFsmSS();

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stPagingRslt.stPositionInfo));

    /* 在paging直接丢弃时，增加主动上报 */
    if (EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS == enPagingFailCause)
    {
        NAS_EMM_SndAcpuOmFaultErrLogInd(&stPagingRslt, ulLength, LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL);
    }
    else
    {
        /*
           将异常信息写入Buffer中
           实际写入的字符数与需要写入的不等则打印异常
         */
        ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stPagingRslt, ulLength);
        if (ulResult != ulLength)
        {
            NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_PagingErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
            TLPS_PRINT2LAYER_ERROR2(NAS_EMM_PagingErrRecord_ENUM ,LNAS_FUNCTION_LABEL1, ulLength, ulResult);
        }
    }
    return;
}
/*****************************************************************************
Function Name   : NAS_EMM_ImprovePerformceeErrReport
Description     : 用户体验提升项目主动上报
Input           : IMSI PAGING结构
Output          : None
Return          : None

History         :
 1. wangchen 00209181 2015-08-05 Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_ImprovePerformceeErrReport
(
    EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ENUM_UINT16  enImproveType
)
{
    EMM_ERR_INFO_IMPROVEMENT_EVENT_STRU                     stImproveEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_ImprovePerformceeErrReport!!");

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_IMPROVEMENT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stImproveEvent, ulLength, 0x00, ulLength);

    /*填充体验提升的场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stImproveEvent.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 填充项目体验提升的类型 */
    stImproveEvent.enImproveType    = enImproveType;

    /* 将该事件主动上报给OM */
    NAS_EMM_SndAcpuOmFaultErrLogInd(&stImproveEvent, ulLength, LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE);

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_RatErrRecord
Description     : RAT流程导致丢网上报errlog信息
Input           : 导致丢网的异系统类型
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog 新建
*****************************************************************************/
VOS_VOID NAS_EMM_RatErrRecord(
            EMM_OM_ERRLOG_RAT_ENUM_UINT16           enRatType)
{
    EMM_ERR_INFO_RAT_RESULT_EVENT_STRU                      stRatRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_RatErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RatErrRecord_ENUM
,LNAS_ENTRY);

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_RAT_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stRatRslt, ulLength, 0x00, ulLength);

    /*填充rat异常场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stRatRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_RAT_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*填充RAT相关上报项*/
    stRatRslt.enRatProcess = enRatType;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stRatRslt.stPositionInfo));

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stRatRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_RatErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_RatErrRecord_ENUM,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_LocalDetachErrRecord
Description     : Local detach场景的errlog存储
Input           : local detach的类型
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2015-02-10 errlog 新建
*****************************************************************************/
VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType)
{
    EMM_ERR_INFO_LOCAL_DETACH_RESULT_EVENT_STRU             stLocalDetRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_LocalDetachErrRecord!!");

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_LOCAL_DETACH_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stLocalDetRslt, ulLength, 0x00, ulLength);

    /*填充Cn Detach fail异常场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stLocalDetRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*填充Cn Detach相关上报项*/
    stLocalDetRslt.enLocalDetType = enLocalDetType;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stLocalDetRslt.stPositionInfo));
    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stLocalDetRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_LocalDetachErrRecord: Push buffer error.");
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_AuthCnFailErrRecord
Description     : Auth Fail场景的errlog存储
Input           :
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2015-02-10 errlog 新建
*****************************************************************************/
VOS_VOID NAS_EMM_AuthCnFailErrRecord(
        EMM_OM_ERRLOG_AUTH_FAIL_ENUM_UINT16       enErrAuthFail)
{
    EMM_ERR_INFO_AUTH_FAIL_RESULT_EVENT_STRU                stAuthCnFailRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_AuthCnFailErrRecord!!");

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_AUTH_FAIL_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stAuthCnFailRslt, ulLength, 0x00, ulLength);

    /*填充Cn Detach fail异常场景头*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stAuthCnFailRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*填充Cn Detach相关上报项*/
    stAuthCnFailRslt.enAuthFail = enErrAuthFail;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stAuthCnFailRslt.stPositionInfo));

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stAuthCnFailRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_AuthCnFailErrRecord: Push buffer error.");
    }

    return;
}
/*****************************************************************************
Function Name   : NAS_EMM_SndAcpuOmFaultErrLogInd
Description     : CHR信息主动上报
Input           :
Output          : None
Return          : None

History         :
 1. wangchen 00209181   2015-08-05  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen,
    LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16   usAlmId
)
{
    OM_FAULT_ERR_LOG_IND_STRU                              *pstFaultRptInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLen;
    VOS_UINT32                                              ulContentAddr;
    EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_UINT16              enReportType;

    /* 申请消息结构内存 */
    /*lint -e961*/
    ulMsgLen     = sizeof(OM_FAULT_ERR_LOG_IND_STRU) - 4 + ulDataLen;
    /*lint +e961*/
    pstFaultRptInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(ulMsgLen);
    if (VOS_NULL_PTR == pstFaultRptInd)
    {
        return;
    }

    /* 构造消息结构体 */
    pstFaultRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFaultRptInd->ulSenderPid       = PS_PID_MM;
    pstFaultRptInd->ulMsgName         = ID_OM_FAULT_ERR_LOG_IND;

    enReportType = NAS_EMM_GetErrLogUnsoliReportType(usAlmId);

    if (EMM_ERR_LOG_FAULT_REPORT == enReportType)
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_FAULT_REPORT;
    }
    else if (EMM_ERR_LOG_ALARM_REPORT == enReportType)
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_ALARM_REPORT;
    }
    else
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_TYPE_BUTT;
    }

    pstFaultRptInd->ulMsgSN           = 0;
    pstFaultRptInd->ulRptlen          = ulDataLen;

    ulContentAddr                     = (VOS_UINT32)pstFaultRptInd->aucContent;

    NAS_LMM_MEM_CPY_S((VOS_UINT8 *)ulContentAddr, ulDataLen, pData, ulDataLen);

    /* 发送消息到ACPU OM模块 */
    NAS_LMM_SEND_MSG(pstFaultRptInd);

    return;
}
#endif


/*****************************************************************************
 Function Name   : NAS_LMM_ExportEmmInfoExcLog
 Description     : 复位时导出Nas信息
 Input           : pulExcLogAddr 数据保存地址
 Output          : pulLeftSpace 剩余空间长度
 Return          : Nas使用的空间大小

 History         :
    1.x00183216     2013-9-17  Draft Enact
    2.leixiantiao 00258641 2014-12-26
*****************************************************************************/
VOS_UINT32 NAS_LMM_ExportEmmInfoExcLog(VOS_UINT32* pulExcLogAddr, VOS_UINT32 *pulLeftSpace)
{
    VOS_UINT32                     *pulSaveAddr = pulExcLogAddr;
    VOS_UINT32                      ulSaveSize = 0;
    VOS_UINT32                      ulstNasInfoSize = 0;
    LNAS_EXC_LOG_STRU               stNasInfo;
    VOS_UINT32                      ulLoop;

    if((0 == *pulLeftSpace)||(NAS_EMM_NULL_PTR == pulExcLogAddr))
    {
        return ulSaveSize;
    }
    NAS_LMM_MEM_SET_S(&stNasInfo, sizeof(LNAS_EXC_LOG_STRU), 0, sizeof(LNAS_EXC_LOG_STRU));
    /* 填充需要到处的信息 */
    for(ulLoop = 0; ulLoop < NAS_LMM_PARALLEL_FSM_BUTT; ulLoop++)
    {
        stNasInfo.astCurFsm[ulLoop].enFsmId = NAS_LMM_GetCurFsmAddr(ulLoop)->enFsmId;
        stNasInfo.astCurFsm[ulLoop].enMainState = NAS_LMM_GetCurFsmAddr(ulLoop)->enMainState;
        stNasInfo.astCurFsm[ulLoop].enStaTId = NAS_LMM_GetCurFsmAddr(ulLoop)->enStaTId;
        stNasInfo.astCurFsm[ulLoop].enSubState = NAS_LMM_GetCurFsmAddr(ulLoop)->enSubState;
    }
    stNasInfo.ucRrcConnState = NAS_EMM_GetConnState();
    stNasInfo.ulCurLteState = NAS_EMM_GetCurLteState();
    /*获取拷贝长度*/
    ulstNasInfoSize = sizeof(LNAS_EXC_LOG_STRU);
    /* 保存EMM状态机和安全状态机 */
    if(ulstNasInfoSize < *pulLeftSpace)
    {
        NAS_LMM_MEM_CPY_S((VOS_VOID *)pulSaveAddr, *pulLeftSpace, &stNasInfo,ulstNasInfoSize);
        ulSaveSize = ulstNasInfoSize;
        *pulLeftSpace -= ulstNasInfoSize;
    }
    else
    {
        NAS_LMM_MEM_CPY_S((VOS_VOID *)pulSaveAddr, *pulLeftSpace, &stNasInfo, *pulLeftSpace);
        ulSaveSize = *pulLeftSpace;
        *pulLeftSpace = 0;
    }
    return ulSaveSize;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmDamPara
 Description     : 将DAM相关参数输出到OM
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmDamPara(VOS_VOID)
{
    NAS_EMM_OM_DAM_PARA_LOG_STRU            *pstMsg = VOS_NULL_PTR;
    NAS_MM_NETWORK_ID_STRU                  *pstAreaInfo;
    NAS_MM_DAM_PLMN_LIST_STRU               *pstDamPlmnList;
    NAS_DAM_IMSI_PLMN_LIST                  *pstImsiPlmnList;

    pstDamPlmnList  = NAS_EMM_GetEmmInfoDamParaPlmnListAddr();
    pstImsiPlmnList = NAS_EMM_GetEmmInfoDamParaImsiPlmnListAddr();
    pstAreaInfo    = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    pstMsg = (NAS_EMM_OM_DAM_PARA_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_DAM_PARA_LOG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndOmDamPara: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndOmDamPara_ENUM
,LNAS_NULL_PTR);
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_DAM_PARA_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_DAM_PARA_LOG;

    /* CService最大值和当前计数 */
    pstMsg->ulCServiceMax               = NAS_EMM_GetEmmInfoDamParaCserviceMax();
    pstMsg->ulCService                  = NAS_EMM_GetEmmInfoDamParaCserviceCnt();

    /* 当前驻留的PLMN ID和DAM PLMN LIST */
    NAS_LMM_MEM_SET_S(  &pstMsg->stCampPlmnId,
                        sizeof(NAS_MM_PLMN_ID_STRU),
                        0,
                        sizeof(NAS_MM_PLMN_ID_STRU));

    if(NAS_EMM_BIT_SLCT == pstAreaInfo->bitOpPlmnId)
    {
        NAS_LMM_MEM_CPY_S(  &pstMsg->stCampPlmnId,
                            sizeof(NAS_MM_PLMN_ID_STRU),
                            &pstAreaInfo->stPlmnId,
                            sizeof(NAS_MM_PLMN_ID_STRU));
    }

    NAS_LMM_MEM_CPY_S(  &pstMsg->stImsiPlmnList,
                        sizeof(NAS_DAM_IMSI_PLMN_LIST),
                        pstImsiPlmnList,
                        sizeof(NAS_DAM_IMSI_PLMN_LIST));

    NAS_LMM_MEM_CPY_S(  &pstMsg->stDamPlmnList,
                        sizeof(NAS_MM_DAM_PLMN_LIST_STRU),
                        pstDamPlmnList,
                        sizeof(NAS_MM_DAM_PLMN_LIST_STRU));

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLmmCommConfigPara
 Description     : 将LMM定制需求公共参数输出到OM
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmCommConfigPara
(
    LNAS_LMM_NV_COMM_CONFIG_PARA_STRU   *pstNvCommPara
)
{
    NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_COMM_CONFIG_PARA_LOG;

    NAS_LMM_MEM_CPY_S(  &pstMsg->stNvCommPara,
                        sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU),
                        pstNvCommPara,
                        sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU));

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmRej19Cnt
 Description     : 将LMM被拒绝#19的相关计数输出到OM
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmRej19Cnt(VOS_VOID)
{
    NAS_EMM_OM_REJ19_CNT_LOG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_EMM_OM_REJ19_CNT_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_REJ19_CNT_LOG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_REJ19_CNT_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_REJ19_CNT_LOG;

    /* 填充当前达到的尝试次数 */
    pstMsg->ulRej19AtmptCnt = NAS_EMM_GLO_AD_GetAttRej19AtmpCnt();

    /* 填充NV中配置的最大尝试次数标识 */
    pstMsg->ulRej19AtmptCntFlag = NAS_EMM_GetEmmInfoRej19AtmptCntFlag();

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmSetTmoActiveFlag
 Description     : 设置TMO的active flag标识时，上报OM消息到HIDS
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2015-03-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmSetTmoActiveFlag(VOS_UINT32 ulTmoActiveFlagStatus)
{
    NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG;

    /* 填写标识状态 */
    pstMsg->ulTmoActiveFlagStatus       = ulTmoActiveFlagStatus;

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}
/*****************************************************************************
 Function Name   :NAS_LMM_SndDebugInfoInd
 Description     : EMM可维可测，勾出当前状态
 Input           :
 Output          : None
 Return          :

 History         :
    1.leixiantiao     2014-10-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_SndDebugInfoInd(VOS_UINT32 ulFileName, VOS_UINT32 ulLineNo, VOS_UINT16 ucPara1, VOS_UINT16 ucPara2, VOS_UINT16 ucPara3, VOS_UINT16 ucPara4)
{
    NAS_EMM_DBG_INFO_IND_STRU            stMsg = {0};
    NAS_LMM_FSM_STATE_STRU               *pstEmmCurState  = NAS_LMM_GetEmmCurFsmAddr();
    NAS_LMM_FSM_STATE_STRU               *pstSecuCurState = NAS_LMM_GetSecuFsmAddr();

    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = PS_PID_MM;
    stMsg.ulReceiverPid       = PS_PID_MM;
    stMsg.ulLength            = sizeof(NAS_EMM_DBG_INFO_IND_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    stMsg.ulMsgId             = ID_NAS_EMM_OM_DEBUG_INFO_LOG;
    stMsg.ulFileName          = ulFileName;
    stMsg.ulLineNo            = ulLineNo;
    stMsg.enEmmMainState      = pstEmmCurState->enMainState ;
    stMsg.enEmmSubState       = pstEmmCurState->enSubState;
    stMsg.enSecuMainState     = pstSecuCurState->enMainState ;
    stMsg.enSecuSubState      = pstSecuCurState->enSubState;
    stMsg.ucPara1             = ucPara1;
    stMsg.ucPara2             = ucPara2;
    stMsg.ucPara3             = ucPara3;
    stMsg.ucPara4             = ucPara4;

    #if (VOS_WIN32 != VOS_OS_VER)
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)&stMsg);
    #endif

        return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauTotalCounter
 Description     : 更新TAU发起次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachTotalCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttTolTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauSuccCounter
 Description     : 更新TAU成功次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachSuccCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttSuccTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauBarFailCounter
 Description     : 更新TAU被bar次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachBarFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttBarFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauNoRfFailCounter
 Description     : 更新TAU NoRf次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachNoRfFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttNoRfFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauEstFailCounter
 Description     : 更新TAU EST Fail次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachEstFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttEstFailTimes()++;
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AddTauExpFailCounter
 Description     : 更新TAU超时次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachExpFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttExpFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauRejFailCounter
 Description     : 更新TAU被拒次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachRejFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttRejFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauRelFailCounter
 Description     : 更新TAU Rel次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachRelFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttRelFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauEsmFailCounter
 Description     : 更新TAU ESM Fail次数:ESM流程失败
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachEsmFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttEsmFailTimes()++;
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AddTauDataReqFailCounter
 Description     : 更新TAU及Comm流程上行直传发送失败次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachDataReqFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttDataReqFailTimes()++;
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :Attach fail Other Cause次数统计
 Input           :None
 Return          :VOS_UINT32 计数是否增加

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddAttachOtherFailCounter(VOS_VOID)
{
    VOS_UINT16 usTimes = 0;

    /* 计算当前纪录Attach成功与失败次数总和 */
    usTimes = NAS_EMM_GetOmSuccRationAttBarFailTimes()
                + NAS_EMM_GetOmSuccRationAttNoRfFailTimes()
                + NAS_EMM_GetOmSuccRationAttEstFailTimes()
                + NAS_EMM_GetOmSuccRationAttExpFailTimes()
                + NAS_EMM_GetOmSuccRationAttRejFailTimes()
                + NAS_EMM_GetOmSuccRationAttEsmFailTimes()
                + NAS_EMM_GetOmSuccRationAttDataReqFailTimes()
                + NAS_EMM_GetOmSuccRationAttOtherFailTimes()
                + NAS_EMM_GetOmSuccRationAttRelFailTimes()
                + NAS_EMM_GetOmSuccRationAttSuccTimes();

     /* 若Attach发起次数是否比当前Attach成功与失败次数总和，说明当前有Attach Other Fail */
     if(NAS_EMM_GetOmSuccRationAttTolTimes() > usTimes)
     {
        NAS_EMM_GetOmSuccRationAttOtherFailTimes() += (NAS_EMM_GetOmSuccRationAttTolTimes() - usTimes);
        return NAS_EMM_YES;
     }
     return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :Attach成功率本地计数维护
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16  enCounterType)
{
    VOS_UINT32                                  ulRslt = NAS_EMM_NO;
    VOS_UINT32                                  ulIndex = 0;
    NAS_LMM_ADD_ATTACH_COUNTER_TYPE_PROC_FUN    pfAddAttachCounterProcFun = VOS_NULL_PTR;
    for(ulIndex = 0; ulIndex < g_stEmmAddAttachCounterProcTblLen; ulIndex++)
    {
        if(enCounterType == g_stEmmAddAttachCounterProcTbl[ulIndex].enCounterType)
        {
            pfAddAttachCounterProcFun = g_stEmmAddAttachCounterProcTbl[ulIndex].pfAddAttachCounterProcFun;
            break;
        }
    }
    if(VOS_NULL_PTR != pfAddAttachCounterProcFun)
    {
        ulRslt = (pfAddAttachCounterProcFun)();
    }
    if((NAS_EMM_YES == NAS_EMM_GetOmSwitchSuccRatioFlag())
        &&(NAS_EMM_YES == ulRslt)
        &&(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL != enCounterType))
    {
        NAS_LMM_SndOmAttSuccRatioInfo();
    }
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :记录ATTACH流程Start时间戳
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachStartTimeStamp(VOS_VOID)
{
    NAS_LMM_OM_ATTACH_DELAY_INFO_STRU *pstAttachDelayInfo;
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    /* 记录ATTACH流程发起时间前清空本地时延数据 */
    pstAttachDelayInfo = NAS_EMM_GetOmAttachDelayInfoAddr();
    NAS_LMM_MEM_SET_S(  pstAttachDelayInfo,
                        sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_STRU));
    NAS_EMM_GetOmAttachDelayInfoStartTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :记录ATTACH REQ Snd时间戳
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachReqSndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmAttachDelayInfoReqSndTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :记录ATTACH EST SUCC时间戳
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachEstSuccTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);
    NAS_EMM_GetOmAttachDelayInfoOpEstSucc() = NAS_EMM_BIT_SLCT;
    NAS_EMM_GetOmAttachDelayInfoEstSuccTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :记录收到ATTACH ACP时间戳
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachAcpTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmAttachDelayInfoulAcceptTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :记录ATTACH Cmp 发送时间戳
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachCmpSndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmAttachDelayInfoCmpSndTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :记录ATTACH流程完成时间戳
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachEndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmAttachDelayInfoEndTime() = stCurrTime.ul32KTStampLowBit;
    /* 若时延信息上报开关打开则上报 */
    if(NAS_EMM_YES == NAS_EMM_GetOmSwitchDelayFlag())
    {
        NAS_LMM_SndOmAttachDelayInfo();
    }
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauTotalCounter
 Description     : 更新TAU发起次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauTotalCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauTolalTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauTolalTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauSuccCounter
 Description     : 更新TAU成功次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauSuccCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauSuccTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauSuccTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauBarFailCounter
 Description     : 更新TAU被bar次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauBarFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauBarFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauBarFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauNoRfFailCounter
 Description     : 更新TAU NoRf次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauNoRfFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauNoRfFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauNoRfFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauEstFailCounter
 Description     : 更新TAU EST Fail次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauEstFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauEstFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauEstFailTimes()++;
    }
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AddTauExpFailCounter
 Description     : 更新TAU超时次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauExpFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauExpFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauExpFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauRejFailCounter
 Description     : 更新TAU被拒次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauRejFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauRejFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauRejFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauRelFailCounter
 Description     : 更新TAU Rel次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauRelFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauRelFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauRelFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauDataReqFailCounter
 Description     : 更新TAU及Comm流程上行直传发送失败次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauDataReqFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauDatReqFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauDatReqFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauOtherFailCounter
 Description     : 更新TAU其他原因失败次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauOtherFailCounter(VOS_VOID)
{
    VOS_UINT16 usInterTimes = 0;
    VOS_UINT16 usIntraTimes = 0;
    VOS_UINT32 ulRslt = NAS_EMM_NO;
    /* 计算当前纪录Inter Tau成功与失败次数总和 */
    usInterTimes = NAS_EMM_GetInterTauSuccTimes()
                    + NAS_EMM_GetInterTauBarFailTimes()
                    + NAS_EMM_GetInterTauNoRfFailTimes()
                    + NAS_EMM_GetInterTauEstFailTimes()
                    + NAS_EMM_GetInterTauExpFailTimes()
                    + NAS_EMM_GetInterTauRejFailTimes()
                    + NAS_EMM_GetInterTauRelFailTimes()
                    + NAS_EMM_GetInterTauDatReqFailTimes()
                    + NAS_EMM_GetInterTauOtherFailTimes();

     /* 若Attach发起次数是否比当前Attach成功与失败次数总和，说明当前有Attach Other Fail */
     if(NAS_EMM_GetInterTauTolalTimes() > usInterTimes)
     {
        NAS_EMM_GetInterTauOtherFailTimes() += (NAS_EMM_GetInterTauTolalTimes() - usInterTimes);
        ulRslt = NAS_EMM_YES;
     }

     /* 计算当前纪录Intra Tau成功与失败次数总和 */
    usIntraTimes = NAS_EMM_GetIntraTauSuccTimes()
                    + NAS_EMM_GetIntraTauBarFailTimes()
                    + NAS_EMM_GetIntraTauNoRfFailTimes()
                    + NAS_EMM_GetIntraTauEstFailTimes()
                    + NAS_EMM_GetIntraTauExpFailTimes()
                    + NAS_EMM_GetIntraTauRejFailTimes()
                    + NAS_EMM_GetIntraTauRelFailTimes()
                    + NAS_EMM_GetIntraTauDatReqFailTimes()
                    + NAS_EMM_GetIntraTauOtherFailTimes();

     /* 若Attach发起次数是否比当前Attach成功与失败次数总和，说明当前有Attach Other Fail */
     if(NAS_EMM_GetIntraTauTolalTimes() > usIntraTimes)
     {
        NAS_EMM_GetIntraTauOtherFailTimes() += (NAS_EMM_GetIntraTauTolalTimes() - usIntraTimes);
        ulRslt = NAS_EMM_YES;
     }
    return ulRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauCounter
 Description     : 更新TAU大数据本地存储数据
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_VOID NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16   enCounterType)
{
    VOS_UINT32                              ulRslt = NAS_EMM_NO;
    VOS_UINT32                              ulIndex = 0;
    NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_FUN   pfAddTauCounterProcFun = VOS_NULL_PTR;
    for(ulIndex = 0; ulIndex < g_stEmmAddTauCounterProcTblLen; ulIndex++)
    {
        if(enCounterType == g_stEmmAddTauCounterProcTbl[ulIndex].enCounterType)
        {
            pfAddTauCounterProcFun = g_stEmmAddTauCounterProcTbl[ulIndex].pfAddTauCounterProcFun;
            break;
        }
    }
    if(VOS_NULL_PTR != pfAddTauCounterProcFun)
    {
        ulRslt = (pfAddTauCounterProcFun)();
    }
    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_AddTauCounter ulRslt = ", ulRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_AddTauCounter_ENUM
,LNAS_FUNCTION_LABEL1,ulRslt);
    if((NAS_EMM_YES == NAS_EMM_GetOmSwitchSuccRatioFlag())
        &&(NAS_EMM_YES == ulRslt)
        &&(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL != enCounterType))
    {
        NAS_LMM_SndOmTauSuccRatioInfo();
    }
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerTotalCounter
 Description     : 更新Ser发起次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerTotalCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerTolalTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerTolalTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerSuccCounter
 Description     : 更新Ser成功次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerSuccCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerSuccTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerSuccTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerBarFailCounter
 Description     : 更新Ser被bar次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerBarFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerBarFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerBarFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerNoRfFailCounter
 Description     : 更新Ser NoRf次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerNoRfFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerNoRfFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerNoRfFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerEstFailCounter
 Description     : 更新Ser EST Fail次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerOtherEstFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerEstFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerEstFailTimes()++;
    }
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AddSerExpFailCounter
 Description     : 更新Ser超时次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerExpFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerExpFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerExpFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerRejFailCounter
 Description     : 更新Ser被拒次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerRejFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerRejFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerRejFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerRelFailCounter
 Description     : 更新Ser Rel次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerRelFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerRelFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerRelFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerDataReqFailCounter
 Description     : 更新Ser及Comm流程上行直传发送失败次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerDataReqFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerDataReqFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerDataReqFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerOtherFailCounter
 Description     : 更新Ser其他原因失败次数
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerOtherFailCounter(VOS_VOID)
{
    VOS_UINT16 usMtSerTimes = 0;
    VOS_UINT16 usMoSerTimes = 0;
    VOS_UINT32 ulRslt = NAS_EMM_NO;
    /* 计算当前纪录MT Tau成功与失败次数总和 */
    usMtSerTimes = NAS_EMM_GetMtSerSuccTimes()
                    + NAS_EMM_GetMtSerBarFailTimes()
                    + NAS_EMM_GetMtSerNoRfFailTimes()
                    + NAS_EMM_GetMtSerEstFailTimes()
                    + NAS_EMM_GetMtSerExpFailTimes()
                    + NAS_EMM_GetMtSerRejFailTimes()
                    + NAS_EMM_GetMtSerRelFailTimes()
                    + NAS_EMM_GetMtSerDataReqFailTimes()
                    + NAS_EMM_GetMtSerOtherFailTimes();

     /* 若Attach发起次数是否比当前Attach成功与失败次数总和，说明当前有Attach Other Fail */
     if(NAS_EMM_GetMtSerTolalTimes() > usMtSerTimes)
     {
        NAS_EMM_GetMtSerOtherFailTimes() += (NAS_EMM_GetMtSerTolalTimes() - usMtSerTimes);
        ulRslt = NAS_EMM_YES;
     }

     /* 计算当前纪录Intra Tau成功与失败次数总和 */
    usMoSerTimes = NAS_EMM_GetMoSerSuccTimes()
                    + NAS_EMM_GetMoSerBarFailTimes()
                    + NAS_EMM_GetMoSerNoRfFailTimes()
                    + NAS_EMM_GetMoSerEstFailTimes()
                    + NAS_EMM_GetMoSerExpFailTimes()
                    + NAS_EMM_GetMoSerRejFailTimes()
                    + NAS_EMM_GetMoSerRelFailTimes()
                    + NAS_EMM_GetMoSerDataReqFailTimes()
                    + NAS_EMM_GetMoSerOtherFailTimes();

     /* 若Attach发起次数是否比当前Attach成功与失败次数总和，说明当前有Attach Other Fail */
     if(NAS_EMM_GetMoSerTolalTimes() > usMoSerTimes)
     {
        NAS_EMM_GetMoSerOtherFailTimes() += (NAS_EMM_GetMoSerTolalTimes() - usMoSerTimes);
        ulRslt = NAS_EMM_YES;
     }
    return ulRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerCounter
 Description     : 更新Ser大数据本地存储数据
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16   enCounterType)
{
    VOS_UINT32                              ulRslt = NAS_EMM_NO;
    VOS_UINT32                              ulIndex = 0;
    NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_FUN   pfAddSerCounterProcFun = VOS_NULL_PTR;
    if(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        return;
    }
    for(ulIndex = 0; ulIndex < g_stEmmAddSerCounterProcTblLen; ulIndex++)
    {
        if(enCounterType == g_stEmmAddSerCounterProcTbl[ulIndex].enCounterType)
        {
            pfAddSerCounterProcFun = g_stEmmAddSerCounterProcTbl[ulIndex].pfAddSerCounterProcFun;
            break;
        }
    }
    if(VOS_NULL_PTR != pfAddSerCounterProcFun)
    {
        ulRslt = (pfAddSerCounterProcFun)();
    }
    if((NAS_EMM_YES == NAS_EMM_GetOmSwitchSuccRatioFlag())
        &&(NAS_EMM_YES == ulRslt)
        &&(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL != enCounterType))
    {
        NAS_LMM_SndOmSerSuccRatioInfo();
    }
}
/*****************************************************************************
 Function Name   : NAS_LMM_UpdateSerEstFailCounter
 Description     : 根据EST FAIL 原因值进行计数
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_UpdateSerEstFailCounter(LRRC_LNAS_EST_RESULT_ENUM_UINT32   enEstResult)
{
    if((LRRC_EST_ACCESS_BARRED_MO_CALL == enEstResult)
        ||(LRRC_EST_ACCESS_BARRED_ALL == enEstResult)
        ||(LRRC_EST_ACCESS_BARRED_ALL == enEstResult)
        ||(LRRC_EST_ACCESS_BARRED_MT_CALL == enEstResult)
        ||(LRRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB == enEstResult))
     {
        NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_BAR);
     }
     else
     {
        NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL);
     }
}
/*****************************************************************************
 Function Name   : NAS_LMM_UpdateSerOtherFailCounter
 Description     : 根据当前连接状态更新Ser OTHER FAIL计数，用于连接状态转换时调用
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_UpdateSerOtherFailCounter(VOS_VOID)
{
    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        ||(NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
        ||(NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState()))
     {
        NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
     }
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveMtSerStartTimeStamp
 Description     : 记录Mt Ser流程启动时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMtSerStartTimeStamp(VOS_VOID)
{
    NAS_LMM_OM_MT_SERVICE_DELAY_INFO_STRU *pstSerDelayInfo;
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    pstSerDelayInfo = NAS_EMM_GetOmMtSerDelayInfoAddr();
    NAS_LMM_MEM_SET_S(  pstSerDelayInfo,
                        sizeof(NAS_LMM_OM_MT_SERVICE_DELAY_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_MT_SERVICE_DELAY_INFO_STRU));
    NAS_EMM_GetOmMtSerStartTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMtSerReqSndTimeStamp
 Description     : 记录Mt Ser Req Snd时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMtSerReqSndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMtSerReqSndTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMtSerEstSuccTimeStamp
 Description     : 记录Mt Ser Est Succ时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMtSerEstSuccTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMtSerEstSuccTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMtSerEndTimeStamp
 Description     : 记录Mt Ser流程结束时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMtSerEndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMtSerEndTime() = stCurrTime.ul32KTStampLowBit;
    /* 若时延信息上报开关打开则上报 */
    if(NAS_EMM_YES == NAS_EMM_GetOmSwitchDelayFlag())
    {
        NAS_LMM_SndOmServiceDelayInfo(NAS_EMM_YES);
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMoSerStartTimeStamp
 Description     : 记录Mo Ser流程启动时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMoSerStartTimeStamp(VOS_VOID)
{
    NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU *pstSerDelayInfo;
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    pstSerDelayInfo = NAS_EMM_GetOmMoSerDelayInfoAddr();
    NAS_LMM_MEM_SET_S(  pstSerDelayInfo,
                        sizeof(NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU));
    NAS_EMM_GetOmMoSerStartTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMoSerReqSndTimeStamp
 Description     : 记录Mo Ser Req Snd时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMoSerReqSndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMoSerReqSndTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMoSerEstSuccTimeStamp
 Description     : 记录Mo Ser Est Succ时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMoSerEstSuccTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMoSerEstSuccTime() = stCurrTime.ul32KTStampLowBit;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveMoSerEndTimeStamp
 Description     : 记录Mo Ser流程完成时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMoSerEndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* 获取当前时间 */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMoSerEndTime() = stCurrTime.ul32KTStampLowBit;
    /* 若时延信息上报开关打开则上报 */
    if(NAS_EMM_YES == NAS_EMM_GetOmSwitchDelayFlag())
    {
        NAS_LMM_SndOmServiceDelayInfo(NAS_EMM_NO);
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveSerReqSndTimeStamp
 Description     : 记录Ser Req Snd时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveSerReqSndTimeStamp()
{
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        if((NAS_EMM_SER_START_CAUSE_RABM_REEST == NAS_EMM_SER_GetEmmSERStartCause())
            ||(NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC == NAS_EMM_SER_GetEmmSERStartCause()))
        {
            NAS_EMM_SaveMoSerReqSndTimeStamp();
        }
        else if(NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_SaveMtSerReqSndTimeStamp();
        }
        else
        {
        }
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveSerEstSuccTimeStamp
 Description     : 记录Ser EST SUCC时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveSerEstSuccTimeStamp(VOS_VOID)
{
    if((NAS_EMM_SER_START_CAUSE_RABM_REEST == NAS_EMM_SER_GetEmmSERStartCause())
        ||(NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        NAS_EMM_SaveMoSerEstSuccTimeStamp();
    }
    else if(NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_SaveMtSerEstSuccTimeStamp();
    }
    else
    {
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveSerEndTimeStamp
 Description     : 记录Ser流程结束时间戳
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveSerEndTimeStamp(VOS_VOID)
{
    if((NAS_EMM_SER_START_CAUSE_RABM_REEST == NAS_EMM_SER_GetEmmSERStartCause())
        ||(NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        NAS_EMM_SaveMoSerEndTimeStamp();
    }
    else if(NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_SaveMtSerEndTimeStamp();
    }
    else
    {
    }
}

/*****************************************************************************
 Function Name   : NAS_LMM_CalcDelayLen
 Description     : 大数据时计算时延函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_CalcDelayLen(VOS_UINT32 ulTimeStampBegin, VOS_UINT32 ulTimeStampEnd)
{
    VOS_UINT32 ulLen;
    if(ulTimeStampEnd > ulTimeStampBegin)
    {
        ulLen = ulTimeStampEnd - ulTimeStampBegin;
    }
    else
    {
        /* 出现反转的情况 */
        ulLen = (NAS_EMM_UINT32_MAX - ulTimeStampBegin) + ulTimeStampEnd;
    }
    return ulLen;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmAttSuccRatioInfo
 Description     : 大数据attach成功率上报
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmAttSuccRatioInfo(VOS_VOID)
{
    NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU));
    pstMsg->stTlKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulLength        = sizeof(NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiHdr.enType          = TL_KPI_TYPE_EST;
    pstMsg->stTlKpiHdr.ulMsgName       = ID_NAS_EMM_OM_ATTACH_SUCC_RATIO_INFO;

    NAS_LMM_MEM_CPY_S(  &pstMsg->stNasLmmOmAttSuccRatioInfo,
                        sizeof(NAS_LMM_OM_SUCC_RATIO_ATTTACH_STRU),
                        NAS_EMM_GetOmSuccRationAttInfoAddr(),
                        sizeof(NAS_LMM_OM_SUCC_RATIO_ATTTACH_STRU));

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmTauSuccRatioInfo
 Description     : 大数据tau成功率上报
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmTauSuccRatioInfo(VOS_VOID)
{
    NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU));
    pstMsg->stTlKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulLength        = sizeof(NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiHdr.enType          = TL_KPI_TYPE_EST;
    pstMsg->stTlKpiHdr.ulMsgName       = ID_NAS_EMM_OM_TAU_SUCC_RATIO_INFO;

    NAS_LMM_MEM_CPY_S(  &pstMsg->stNasLmmOmTauSuccRatioInfo,
                        sizeof(NAS_LMM_OM_SUCC_RATIO_TAU_STRU),
                        NAS_EMM_GetOmSuccRationTauInfoAddr(),
                        sizeof(NAS_LMM_OM_SUCC_RATIO_TAU_STRU));

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmSerSuccRatioInfo
 Description     : 大数据service成功率上报
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmSerSuccRatioInfo(VOS_VOID)
{
    NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU));
    pstMsg->stTlKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulLength        = sizeof(NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiHdr.enType          = TL_KPI_TYPE_EST;
    pstMsg->stTlKpiHdr.ulMsgName       = ID_NAS_EMM_OM_SERVICE_SUCC_RATIO_INFO;

    /* 填写标识状态 */
    NAS_LMM_MEM_CPY_S(  &pstMsg->stNasLmmOmSerSuccRatioInfo,
                        sizeof(NAS_LMM_OM_SUCC_RATIO_SER_STRU),
                        NAS_EMM_GetOmSuccRationSerInfoAddr(),
                        sizeof(NAS_LMM_OM_SUCC_RATIO_SER_STRU));

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmAttachDelayInfo
 Description     : 大数据attach时延上报
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmAttachDelayInfo(VOS_VOID)
{
    NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                               ulTimeDelayLen;
    pstMsg = (NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU));
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulLength        = sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.enType          = TL_KPI_TYPE_DELAY;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulMsgName       = ID_NAS_EMM_OM_ATTACH_DELAY_INFO;

    /* 计算总时延 */
    ulTimeDelayLen = NAS_LMM_CalcDelayLen(NAS_EMM_GetOmAttachDelayInfoStartTime(), NAS_EMM_GetOmAttachDelayInfoEndTime());

    pstMsg->stTlKpiDelayHdr.ulDelay = ulTimeDelayLen;
    pstMsg->stTlKpiDelayHdr.ulStartTime = NAS_EMM_GetOmAttachDelayInfoStartTime();
    pstMsg->stTlKpiDelayHdr.ulEnd = NAS_EMM_GetOmAttachDelayInfoEndTime();

    /* 拷贝本地时延信息 */
    pstMsg->bitOpEstSucc        = NAS_EMM_GetOmAttachDelayInfoOpEstSucc();
    pstMsg->ulAttachReqSnd      = NAS_EMM_GetOmAttachDelayInfoReqSndTime();
    pstMsg->ulAttachAccept      = NAS_EMM_GetOmAttachDelayInfoulAcceptTime();
    pstMsg->ulEstSucc           = NAS_EMM_GetOmAttachDelayInfoEstSuccTime();
    pstMsg->ulAttachCompleteSnd = NAS_EMM_GetOmAttachDelayInfoCmpSndTime();
    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmServiceDelayInfo
 Description     : 大数据service时延上报
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmServiceDelayInfo(VOS_UINT32 ulIsMtService)
{
    NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;
    NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU     *pstNasServiceDelayInfo = VOS_NULL_PTR;
    VOS_UINT32                                 ulTimeDelayLen = 0;
    pstMsg = (NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU));
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulLength        = sizeof(NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.enType          = TL_KPI_TYPE_DELAY;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulMsgName       = ID_NAS_EMM_OM_SERVICE_DELAY_INFO;
    pstMsg->ulIsMtServiceFlag                        = ulIsMtService;
    /* 判断是是否是Mt Ser */
    if(NAS_EMM_YES == ulIsMtService)
    {
        pstNasServiceDelayInfo = NAS_EMM_GetOmMtSerDelayInfoAddr();
    }
    else
    {
        pstNasServiceDelayInfo = NAS_EMM_GetOmMoSerDelayInfoAddr();
    }
    /* 计算总时延 */
    ulTimeDelayLen = NAS_LMM_CalcDelayLen(pstNasServiceDelayInfo->ulStart, pstNasServiceDelayInfo->ulEnd);

    pstMsg->stTlKpiDelayHdr.ulDelay = ulTimeDelayLen;
    pstMsg->stTlKpiDelayHdr.ulStartTime = pstNasServiceDelayInfo->ulStart;
    pstMsg->stTlKpiDelayHdr.ulEnd = pstNasServiceDelayInfo->ulEnd;

    pstMsg->ulServiceReqSnd = pstNasServiceDelayInfo->ulServiceReqSnd;
    pstMsg->ulEstSucc       = pstNasServiceDelayInfo->ulEstSucc;
    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmTauStartTypeInfo
 Description     : 上报TAU发起原因
 Input           : enTauStartType: TAU发起原因
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641   2015-07-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SndOmTauStartTypeInfo(NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 enTauStartType)
{
    NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU stTauStartTypeInfo;

    NAS_LMM_MEM_SET_S(  &stTauStartTypeInfo,
                        sizeof(NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU));
    stTauStartTypeInfo.stMsgHeader.ulSenderCpuId         = VOS_LOCAL_CPUID;
    stTauStartTypeInfo.stMsgHeader.ulSenderPid           = PS_PID_MM;
    stTauStartTypeInfo.stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    stTauStartTypeInfo.stMsgHeader.ulReceiverPid         = PS_PID_MM;
    stTauStartTypeInfo.stMsgHeader.ulLength              = sizeof(NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    stTauStartTypeInfo.stMsgHeader.ulMsgName             = ID_NAS_LMM_OM_LOG_TAU_START_TYPE_INFO;

    stTauStartTypeInfo.enTauStartType                    = enTauStartType;
    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)&stTauStartTypeInfo);
}


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 Function Name   :LNAS_InitErrLogGloInfo
 Description     : 初始化Errlog全局信息
 Input           :
 Output          : None
 Return          :

 History         :
    1.lifuxin  00253982    2014-12-27  Draft Enact
*****************************************************************************/
/*lint -e593*/
VOS_VOID  LNAS_InitErrLogGloInfo(LNAS_ERRLOG_GLO_INFO_STRU *pstErrlogGloInfo)
{
    VOS_CHAR                               *pbuffer;
    OM_RING_ID                              pRingbuffer;

    pstErrlogGloInfo->stCtrlInfo.ucErrLogCtrlFlag         = VOS_FALSE;
    pstErrlogGloInfo->stCtrlInfo.usAlmLevel               = LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL;

    /* 申请cache的动态内存 , 长度加1是因为读和写指针之间在写满时会相差一个字节 */
    pbuffer = (char *)NAS_LMM_MEM_ALLOC(LNAS_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
         pstErrlogGloInfo->stBuffInfo.pstRingBuffer = VOS_NULL_PTR;
         return;
    }

    /* 调用OM的接口，将申请的动态内存创建为RING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, LNAS_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        NAS_LMM_MEM_FREE(pbuffer);
    }

    /* 保存ringbuffer指针 */
    pstErrlogGloInfo->stBuffInfo.pstRingBuffer = pRingbuffer;

    pstErrlogGloInfo->stBuffInfo.ulOverflowCnt = 0;

    NAS_LMM_RevNvCtrl();

    return;
}
/*lint +e593*/
#endif
/*****************************************************************************
 Function Name   : NAS_EMM_SaveRecvMsgList
 Description     : 记录LMM收到的消息队列,最大50条
 Input           : pMsg:消息
 Output          : None
 Return          : None

 History         :
    1.leixiantiao  00258641    2015-07-17  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveRecvMsgList(VOS_VOID *pMsg)
{
    PS_MSG_HEADER_STRU         *pMsgHeader    = (PS_MSG_HEADER_STRU *)pMsg;
    LNAS_EXC_MSG_MNTN_STRU     *pstMsgMntn    = VOS_NULL_PTR;
    LNAS_EXC_MSG_ELEMENT_STRU  *pstMsgElement = VOS_NULL_PTR;
    pstMsgMntn = &g_stLNasResetInfo.stLNasMsgList;
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }
    /* 循环保存消息到指定全局变量 */
    if(pstMsgMntn->ulNextIndex >= LNAS_EXC_MAX_SAVE_MSG_NUM)
    {
        pstMsgMntn->ulNextIndex = 0;
    }
    pstMsgElement = &(pstMsgMntn ->astMsgList[pstMsgMntn->ulNextIndex]);
    /* 保存时间戳以及消息ID等信息 */
    pstMsgElement->ulTimeStamp      = VOS_GetSlice();
    pstMsgElement->ulCompPid        = TLPS_EXC_BUILD_MSG_PID(pMsgHeader->ulSenderPid,
                                                                pMsgHeader->ulReceiverPid);
    pstMsgElement->ulMsgId          = pMsgHeader->ulMsgName;
    pstMsgElement->enCurrMainState  = NAS_LMM_GetEmmCurFsmMS();
    pstMsgElement->enCurrSubState   = NAS_LMM_GetEmmCurFsmSS();

    /*目前暂时对所有消息都多保存4个字节,这4个字节基本是OPid或者切态或者切模式的方向 */
    pstMsgElement->ulPrivate = *((VOS_UINT32*)pMsg + TLPS_EXC_MSG_PRIVATE_OFFSET);

    /* 先保存后索引加1,所以Index前一个记录是复位前最后一条记录 */
    pstMsgMntn->ulNextIndex++;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveEmmPreState
 Description     : 记录LMM 转状态之前状态,用于复位时确认LMM是从哪个状态下转到当
                   前状态
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.leixiantiao  00258641    2015-07-17  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SavePreEmmState(VOS_VOID)
{
    LNAS_EXC_PRE_STATE_STRU             *pstLNasPreState = VOS_NULL_PTR;
    pstLNasPreState = &g_stLNasResetInfo.stLNasPreState;

    pstLNasPreState->enPreMainState = NAS_LMM_GetEmmCurFsmMS();
    pstLNasPreState->enPreSubState  = NAS_LMM_GetEmmCurFsmSS();
    pstLNasPreState->ulTimeStamp    = VOS_GetSlice();
}
/*****************************************************************************
 Function Name  : NAS_EMM_ExportMsgInfoExcLog
 Discription    : 导NAS消息队列到复位文件中
 Input          : pulExcLogAddr:目标地址
 Output         : pulLeftSize  :TLPS可维可测内存剩余长度
 Return         : VOS_UINT32   :存储LMM消息队列使用的长度

 History:
      1.leixiantiao  00258641    2015-07-17  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_ExportMsgInfoExcLog(VOS_UINT8* pulExcLogAddr, VOS_UINT32 *pulLeftSize)
{
    VOS_UINT32                  ulLoop        = 0;
    VOS_UINT8                   *pulSaveAddr   = pulExcLogAddr;
    VOS_UINT32                  ulSaveSize    = 0;
    VOS_UINT32                  ulMsgStruSize = sizeof(LNAS_EXC_MSG_ELEMENT_STRU);
    VOS_UINT32                  ulMsgNum      = 0;
    LNAS_EXC_MSG_MNTN_STRU     *pstMsgMntn    = VOS_NULL_PTR;

    pstMsgMntn = &g_stLNasResetInfo.stLNasMsgList;

    /* 获取复位前最后一条消息索引 */
    if(0 == pstMsgMntn->ulNextIndex)
    {
        ulLoop = LNAS_EXC_MAX_SAVE_MSG_NUM - 1;
    }
    else
    {
        ulLoop = pstMsgMntn->ulNextIndex - 1;
    }

    /* 循环保存到rdr内存中 */
    for( ; ulMsgNum < LNAS_EXC_MAX_SAVE_MSG_NUM; ulMsgNum++ )
    {
        /* 当分给TLPS的复位可维可测剩余内存小于一条消息所需内存时退出 */
        if(*pulLeftSize < ulMsgStruSize)
        {
            return ulSaveSize;
        }

        /* 拷贝数据 */
        *pulLeftSize -= ulMsgStruSize;
        ulSaveSize += ulMsgStruSize;

        NAS_LMM_MEM_CPY_S(  pulSaveAddr,
                            ulMsgStruSize,
                            &(pstMsgMntn->astMsgList[ulLoop]),
                            ulMsgStruSize);

        pulSaveAddr += ulMsgStruSize;

        /* 索引循环 */
        if(0 == ulLoop)
        {
            ulLoop = LNAS_EXC_MAX_SAVE_MSG_NUM;
        }
        ulLoop--;
    }
    return ulSaveSize;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmSerStartTypeInfo
 Description     : 上报SERVICE发起原因
 Input           : NAS_LMM_OM_SER_START_TYPE_ENUM_UINT32 enSerStartType
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-08-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_ENUM_UINT32 enSerStartType)
{
    NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU                 *pstSerStartTypeInfo;
    pstSerStartTypeInfo = (NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU));
    if (VOS_NULL_PTR == pstSerStartTypeInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstSerStartTypeInfo,
                        sizeof(NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU));
    pstSerStartTypeInfo->stMsgHeader.ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstSerStartTypeInfo->stMsgHeader.ulSenderPid            = PS_PID_MM;
    pstSerStartTypeInfo->stMsgHeader.ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstSerStartTypeInfo->stMsgHeader.ulReceiverPid          = PS_PID_MM;
    pstSerStartTypeInfo->stMsgHeader.ulLength               = sizeof(NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstSerStartTypeInfo->stMsgHeader.ulMsgName              = ID_NAS_LMM_OM_LOG_SER_START_TYPE_INFO;
    pstSerStartTypeInfo->enSerStartType                     = enSerStartType;


    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstSerStartTypeInfo);
    NAS_LMM_MEM_FREE(pstSerStartTypeInfo);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmAnyCellJudgingInfo
 Description     : 当识别为ANY CELL小区时上报
 Input           : NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType,
                   MMC_LMM_PLMN_CTRL_ENUM_UINT32       ulPlmnCtrl,
                   NAS_MM_TA_STRU                     *pstTa
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-08-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmAnyCellJudgingInfo
(
    NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType,
    MMC_LMM_PLMN_CTRL_ENUM_UINT32       ulPlmnCtrl,
    const   NAS_MM_TA_STRU             *pstTa
)
{
    NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU               *pstAnyCellJudgingInfo = VOS_NULL_PTR;
    NAS_MM_TA_LIST_STRU                                     *pstForbTaListForRoaming = VOS_NULL_PTR;
    NAS_MM_TA_LIST_STRU                                     *pstForbTaListForRpos = VOS_NULL_PTR;

    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstForbTaListForRpos = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS);

    pstAnyCellJudgingInfo = (NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU));
    if (VOS_NULL_PTR == pstAnyCellJudgingInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstAnyCellJudgingInfo,
                        sizeof(NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU));
    pstAnyCellJudgingInfo->stMsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstAnyCellJudgingInfo->stMsgHeader.ulSenderPid          = PS_PID_MM;
    pstAnyCellJudgingInfo->stMsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstAnyCellJudgingInfo->stMsgHeader.ulReceiverPid        = PS_PID_MM;
    pstAnyCellJudgingInfo->stMsgHeader.ulLength             = sizeof(NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstAnyCellJudgingInfo->stMsgHeader.ulMsgName            = ID_NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO;
    pstAnyCellJudgingInfo->ulSimStat                        = NAS_LMM_GetSimState();
    pstAnyCellJudgingInfo->enPsSimValidity                  = NAS_LMM_GetPsSimValidity();
    pstAnyCellJudgingInfo->enSimType                        = enSimType;
    pstAnyCellJudgingInfo->enPlmnForb                       = ulPlmnCtrl;
    NAS_LMM_MEM_CPY_S(  &pstAnyCellJudgingInfo->stForbTaForRoam,
                        sizeof(NAS_MM_FORB_TA_LIST_STRU),
                        pstForbTaListForRoaming,
                        sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(  &pstAnyCellJudgingInfo->stForbTaForRpos,
                        sizeof(NAS_MM_FORB_TA_LIST_STRU),
                        pstForbTaListForRpos,
                        sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(  &pstAnyCellJudgingInfo->stTa,
                        sizeof(NAS_MM_TA_STRU),
                        pstTa,
                        sizeof(NAS_MM_TA_STRU));

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAnyCellJudgingInfo);
    NAS_LMM_MEM_FREE(pstAnyCellJudgingInfo);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetImsiInfo
 Description     : 获取imsi info
 Input           :
 Output          : NAS_OM_IMSI_INFO_STRU *stImsiInfo
 Return          : VOS_UINT32

 History         :
    1.yanglei 00307272        2015-08-18    Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_GetImsiInfo(NAS_OM_IMSI_INFO_STRU *pstImsiInfo)
{
    VOS_UINT8                           i;
    NAS_LMM_UEID_STRU                  *pstMmUeId;

    pstMmUeId                           = NAS_LMM_GetEmmInfoUeidAddr();
    NAS_LMM_MEM_SET_S(  pstImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        0,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

    /*如果当前无卡,向OM回复查询IMSI为空*/
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {
        /* 获取IMSI */
        /* usim保护，PS:I CANT STAND IT ANYMORE */
        if((pstMmUeId->aucImsi[0] > NAS_LMM_NVIM_IMSI_FILE_LEN - 1)
            ||(pstMmUeId->aucImsi[0] == 0))
        {
            pstImsiInfo->ucImsiLen = 0x0F;
            if (0xF0 == (pstMmUeId->aucImsi[8] & 0xF0))
            {
                pstImsiInfo->ucImsiLen -= 1;
            }
        }
        else
        {
            pstImsiInfo->ucImsiLen = (VOS_UINT8)((pstMmUeId->aucImsi[0])*2 - 1);

            /*最后一个字节最高4位为F,则表明IMSI为偶数个 */
            if (0xF0 == (pstMmUeId->aucImsi[pstMmUeId->aucImsi[0]] & 0xF0))
            {
                pstImsiInfo->ucImsiLen -= 1;
            }

        }
        for(i = 0; i < pstImsiInfo->ucImsiLen; i++)
        {
            if (0 == (i+1)%2)
            {
                pstImsiInfo->ucImsi[i] = 0x0F & (pstMmUeId->aucImsi[(i+1)/2 + 1]);
            }
            else
            {
                pstImsiInfo->ucImsi[i] = 0x0F & (pstMmUeId->aucImsi[(i+1)/2 + 1] >> 4);
            }
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmStaticUeIdInfo
 Description     : 上报静态UE ID信息
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-08-18  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmStaticUeIdInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU                   *pstStaticUeIdInfo = VOS_NULL_PTR;
    VOS_UINT32                                              *pulImsiMncLen;
    NAS_LMM_UEID_STRU                                       *pstMmUeId;

    pstMmUeId                           = NAS_LMM_GetEmmInfoUeidAddr();
    pulImsiMncLen                       = NAS_LMM_GetEmmInfoUeidImsiMncLenAddr();
    pstStaticUeIdInfo                   = (NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU *)NAS_LMM_MEM_ALLOC \
                                                (sizeof(NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU));
    if (VOS_NULL_PTR == pstStaticUeIdInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstStaticUeIdInfo,
                        sizeof(NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU));
    pstStaticUeIdInfo->stMsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstStaticUeIdInfo->stMsgHeader.ulSenderPid          = PS_PID_MM;
    pstStaticUeIdInfo->stMsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstStaticUeIdInfo->stMsgHeader.ulReceiverPid        = PS_PID_MM;
    pstStaticUeIdInfo->stMsgHeader.ulLength             = sizeof(NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstStaticUeIdInfo->stMsgHeader.ulMsgName            = ID_NAS_LMM_OM_LOG_STATIC_UE_ID_INFO;
    pstStaticUeIdInfo->stMmUeid.bitOpImei               = pstMmUeId->bitOpImei;
    pstStaticUeIdInfo->stMmUeid.bitOpImeisv             = pstMmUeId->bitOpImeisv;
    NAS_LMM_MEM_CPY_S(  pstStaticUeIdInfo->stMmUeid.aucImei,
                        NAS_MM_MAX_UEID_BUF_SIZE,
                        NAS_LMM_GetEmmInfoUeidImeiAddr(),
                        sizeof(VOS_UINT8)*NAS_MM_MAX_UEID_BUF_SIZE);
    NAS_LMM_MEM_CPY_S(  pstStaticUeIdInfo->stMmUeid.aucImeisv,
                        NAS_MM_MAX_UEID_BUF_SIZE,
                        NAS_LMM_GetEmmInfoUeidImeisvAddr(),
                        sizeof(VOS_UINT8)*NAS_MM_MAX_UEID_BUF_SIZE);
    NAS_LMM_GetImsiInfo(&pstStaticUeIdInfo->stMmUeid.stImsiInfo);
    pstStaticUeIdInfo->stMmUeid.ulImsiMncLen            = *pulImsiMncLen;

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstStaticUeIdInfo);
    NAS_LMM_MEM_FREE(pstStaticUeIdInfo);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmConnstateInfo
 Description     : 上报连接状态
 Input           : NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucConnstate
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-08-18  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmConnstateInfo(NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucConnstate)
{
    NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU                   *pstConnStateInfo = VOS_NULL_PTR;

    pstConnStateInfo = (NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU));
    if (VOS_NULL_PTR == pstConnStateInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstConnStateInfo,
                        sizeof(NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU));
    pstConnStateInfo->stMsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstConnStateInfo->stMsgHeader.ulSenderPid          = PS_PID_MM;
    pstConnStateInfo->stMsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstConnStateInfo->stMsgHeader.ulReceiverPid        = PS_PID_MM;
    pstConnStateInfo->stMsgHeader.ulLength             = sizeof(NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstConnStateInfo->stMsgHeader.ulMsgName            = ID_NAS_LMM_OM_LOG_CONN_STATE_INFO;
    pstConnStateInfo->ucPreConnState                   = NAS_EMM_GetConnState();
    pstConnStateInfo->ucCurConnState                   = ucConnstate;

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstConnStateInfo);
    NAS_LMM_MEM_FREE(pstConnStateInfo);
    return;
}




/*****************************************************************************
 Function Name   : NAS_EMM_SndOmGradualForbParaLog
 Description     : Gradual Forb参数可维可测
 Input           : stNvGradualForbPara: 从NV中读出的配置信息
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SndOmGradualForbParaLog(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU  stNvGradualForbPara)
{
    NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU    stOmGradualForbPara;

    /* 消息结构初始化 */
    NAS_LMM_MEM_SET_S(  &stOmGradualForbPara,
                        sizeof(NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU),
                        0,
                        sizeof(NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU));
    /* 填写消息头 */
    stOmGradualForbPara.stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stOmGradualForbPara.stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stOmGradualForbPara.stMsgHeader.ulSenderPid     = PS_PID_MM;
    stOmGradualForbPara.stMsgHeader.ulReceiverPid   = PS_PID_MM;
    stOmGradualForbPara.stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    stOmGradualForbPara.stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_GRADUAL_FORB_PARA_LOG;

    /* 可维可测消息内容赋值 */
    NAS_LMM_MEM_CPY_S(  &stOmGradualForbPara.stNvGradualForbPara,
                        sizeof(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU),
                        &stNvGradualForbPara,
                        sizeof(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU));

    stOmGradualForbPara.ucGradualForbFlag            = g_ucLmmGradualForbFlag;
    stOmGradualForbPara.ulGradualForbTimerFirstLen   = g_ulGradualForbTimerFirstLen;
    stOmGradualForbPara.ulGradualForbTimerSecondLen  = g_ulGradualForbTimerSecondLen;
    stOmGradualForbPara.ulGradualForbTimerAgingLen   = g_ulGradualForbAgingTimerLen;

    /* 勾出可维可测消息 */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)&stOmGradualForbPara);
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndOmGradualForbTaInfo
 Description     : Gradual Forb TA以及TA LIST可维可测
 Input           : stOperaTa  :操作TA
                   enOperaType:操作类型
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SndOmGradualForbTaInfo(NAS_MM_TA_STRU *pstOperaTa,
                                                        NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_ENUM_UINT8 enOperaType)
{
    NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU        *pstOmGradualForbTaInfo = VOS_NULL_PTR;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList             = VOS_NULL_PTR;
    VOS_UINT32                                   i;

    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    pstOmGradualForbTaInfo = NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU));
    if(VOS_NULL_PTR == pstOmGradualForbTaInfo)
    {
        return;
    }
    /* 初始化消息 */
    NAS_LMM_MEM_SET_S(  pstOmGradualForbTaInfo,
                        sizeof(NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU),
                        0,
                        sizeof(NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU));

    /* 填充消息头 */
    pstOmGradualForbTaInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstOmGradualForbTaInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstOmGradualForbTaInfo->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstOmGradualForbTaInfo->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstOmGradualForbTaInfo->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstOmGradualForbTaInfo->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_GRADUAL_FORB_TA_INFO;

    /* 填充消息内容 */
    pstOmGradualForbTaInfo->enOperationType             = enOperaType;
    NAS_LMM_MEM_CPY_S(&pstOmGradualForbTaInfo->stOperaTa, sizeof(NAS_MM_TA_STRU), pstOperaTa, sizeof(NAS_MM_TA_STRU));
    for(i = 0; i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; i++)
    {
        NAS_LMM_MEM_CPY_S(  &pstOmGradualForbTaInfo->stGradualForbTaList.astGradualForbTa[i],
                            sizeof(NAS_LMM_GRADUAL_FORB_TA),
                            &pstTaList->astGradualForbTa[i],
                            sizeof(NAS_LMM_GRADUAL_FORB_TA));
    }
    pstOmGradualForbTaInfo->stGradualForbTaList.ulTaNum = pstTaList->ulTaNum;

    /* 勾出可维可测消息 */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstOmGradualForbTaInfo);

    NAS_LMM_MEM_FREE(pstOmGradualForbTaInfo);
}


/*****************************************************************************
 Function Name   : NAS_LMM_SndOmRegDomainInfo
 Description     : 设置注册域时, 上报可维可测信息
 Input           : enRegDomainCur  :当前注册域
                   enRegDomainDst  :目标注册域
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-08-28  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_SndOmRegDomainInfo(NAS_LMM_REG_DOMAIN_ENUM_UINT32  enRegDomainCur,
                                                        NAS_LMM_REG_DOMAIN_ENUM_UINT32   enRegDomainDst)
{
    NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU     *pstRegDomainInfo;
    NAS_EMMC_GLOBAL_STRU                    *pstEmmcInfo;

    /* 获取Rej18PLMN列表 */
    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    pstRegDomainInfo = NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU));
    if(VOS_NULL_PTR == pstRegDomainInfo)
    {
        return;
    }
    /* 初始化消息 */
    NAS_LMM_MEM_SET_S(  pstRegDomainInfo,
                        sizeof(NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU));

    /* 填充消息头 */
    pstRegDomainInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstRegDomainInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRegDomainInfo->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstRegDomainInfo->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstRegDomainInfo->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstRegDomainInfo->stMsgHeader.ulMsgName       = ID_NAS_LMM_OM_LOG_SET_REG_DOMAIN;

    /* 填充消息 */
    pstRegDomainInfo->enRegDomainCur       = enRegDomainCur;
    pstRegDomainInfo->enRegDomainDst       = enRegDomainDst;
    pstRegDomainInfo->ucCsRej18Cause18Flg  = (VOS_UINT8)NAS_EMMC_GetRejCause18Flag();
    pstRegDomainInfo->ucCsRejCause2Flag    = (VOS_UINT8)NAS_LMM_GetEmmInfoRejCause2Flag();

    /* 此处直接调用MML接口, 防止出现重复上报可维可测消息 */
    pstRegDomainInfo->ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();
    pstRegDomainInfo->ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

    NAS_LMM_MEM_CPY_S(  &pstRegDomainInfo->stRej18PlmnList,
                        sizeof(NAS_MM_PLMN_LIST_STRU),
                        &pstEmmcInfo->stRej18PlmnList,
                        sizeof(NAS_MM_PLMN_LIST_STRU));

    /* 勾出可维可测消息 */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstRegDomainInfo);

    /* 释放内存 */
    NAS_LMM_MEM_FREE(pstRegDomainInfo);
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmImsiRefreshStatus
 Description     : 上报imsi刷新状态
 Input           : VOS_UINT8   ucImsiRefreshStatusFlag
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-11-18  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmImsiRefreshStatus(VOS_UINT8   ucImsiRefreshStatusFlag)
{
    NAS_EMM_IMSI_REFRESH_STATUS_STRU                   *pstImsiRefreshStatusInfo = VOS_NULL_PTR;

    pstImsiRefreshStatusInfo = (NAS_EMM_IMSI_REFRESH_STATUS_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_IMSI_REFRESH_STATUS_STRU));
    if (VOS_NULL_PTR == pstImsiRefreshStatusInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstImsiRefreshStatusInfo,
                        sizeof(NAS_EMM_IMSI_REFRESH_STATUS_STRU),
                        0,
                        sizeof(NAS_EMM_IMSI_REFRESH_STATUS_STRU));

    pstImsiRefreshStatusInfo->stMsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstImsiRefreshStatusInfo->stMsgHeader.ulSenderPid          = PS_PID_MM;
    pstImsiRefreshStatusInfo->stMsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstImsiRefreshStatusInfo->stMsgHeader.ulReceiverPid        = PS_PID_MM;
    pstImsiRefreshStatusInfo->stMsgHeader.ulLength             = sizeof(NAS_EMM_IMSI_REFRESH_STATUS_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstImsiRefreshStatusInfo->stMsgHeader.ulMsgName            = LNAS_OM_LOG_IMSI_REFRESH_STATUS_IND;
    pstImsiRefreshStatusInfo->ucImsiRefreshStatusFlag          = ucImsiRefreshStatusFlag;

    /* 单板发送，PC则因打桩无操作不会发送消息，不会影响PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstImsiRefreshStatusInfo);
    NAS_LMM_MEM_FREE(pstImsiRefreshStatusInfo);
    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of 子系统+模块+文件名.c */
