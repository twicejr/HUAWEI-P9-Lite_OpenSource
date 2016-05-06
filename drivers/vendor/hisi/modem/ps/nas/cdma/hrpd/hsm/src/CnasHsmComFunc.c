

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmComFunc.h"
#include "CnasTimerMgmt.h"
#include "CnasMntn.h"
#include "CnasHsmCtx.h"
#include "CnasHsmSndTtf.h"
#include "CnasHsmSndAs.h"
#include "CnasHsmSndHsd.h"
#include "CnasHsmSndAps.h"
#include "CnasHsmCtx.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "CnasHsmMntn.h"
#include "CnasHsmFsmMain.h"
#include "CnasHsmKeepAlive.h"
#include "CnasHsmProcNvim.h"
#include "CnasHsmSndRrm.h"
#include "CnasHsmSndMma.h"

#include "CnasHsmFsmTbl.h"
#include "CnasHsmFsmUatiRequest.h"
#include "Nas_Mem.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_COM_FUNC_C

#ifdef DMT
    VOS_UINT32                          g_ulCurRandEsn     = 0x0001E240;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/
/*****************************************************************************
 Variable Name       : g_astHsmDeactReasonMapReasonSendAnTbl
 Description         : Session deacitve map reason sned to AN table
                       该表仅列出需要给网络发SessionClose的原因值
 1.DATE              : 2015-05-29
   AUTHOR            : y00174758
   Modification      : Create
 2.Date              : 2015-09-23
   Author            : t00323010
   Modify content    : HSM MNTN(DTS2015092201636): add uati aborted by power save/power off
*****************************************************************************/
CNAS_HSM_DEACT_REASON_MAP_REASON_SEND_AN_STRU g_astHsmDeactReasonMapReasonSendAnTbl[] =
{
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_NEG_FAIL,             /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,  /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_EXP,               /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,        /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_FAIL,       /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,        /* Reason in SessionClose send to AN */
        {0, 0},
    },

    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_EXPLICITLY_REJ,       /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                       /* Reason in SessionClose send to AN */
        {0, 0},
    },

    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,       /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                       /* Reason in SessionClose send to AN */
        {0, 0},
    },

    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_PERS_INVALID,         /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_SESS_CONF_FAIL,  /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_RSP_EXP,          /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,  /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_MSG_FAIL,         /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,  /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_GAUP_FAIL,         /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,  /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_IRAT_TO_LTE,          /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,        /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_NO_RF,                /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,        /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_NEG_FAIL,        /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,              /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_AN_EXP,          /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                    /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CONN_OPEN_FAIL,  /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                    /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_CONN_OPEN_DENY,      /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                    /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_PERS_INVALID,        /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_SESS_CONF_FAIL,              /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CFG_RSP_EXP,     /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,              /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CFG_MSG_FAIL,    /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,              /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_AN_GAUP_FAIL,    /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,              /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_IRAT_TO_LTE,     /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                    /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_NO_RF,           /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                    /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_EHRPD_TO_HRPD,             /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,         /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_HRPD_TO_EHRPD,             /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,         /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_AN_CLOSE_SESSION_IN_VACANT,       /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_REPLY,                   /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_AN_CLOSE_SESSION,   /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_REPLY,                   /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_POWER_SAVE,         /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_POWER_OFF,          /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_EHRPD_NOT_AVAILABLE,    /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                    /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_PA_MODE_NTF,   /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,           /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_NEG_FAIL,   /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,      /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_AN_EXP, /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,        /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CONN_OPEN_FAIL, /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CONN_OPEN_DENY, /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_PERS_INVALID,   /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_SESS_CONF_FAIL,          /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_RSP_EXP,    /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,          /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_MSG_FAIL,   /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,          /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_AN_GAUP_FAIL,   /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_CONF_FAIL,              /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_IRAT_TO_LTE,    /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_NO_RF,          /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_POWER_SAVE,  /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_POWER_OFF,   /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_PROT_ERR,                /* Reason in SessionClose send to AN */
        {0, 0},
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_AN_CLOSE_SESSION,    /* Session deactive reason */
        CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_REPLY,                           /* Reason in SessionClose send to AN */
        {0, 0},
    },
};


CNAS_HSM_SCP_FAIL_REASON_MAP_SESSION_DEACT_REASON_STRU g_astHsmScpFailReasonMapSessionDeactReasonTbl[] =
{
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_FAILURE,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_NEG_FAIL,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_EXPIRED,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_EXP,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_FAIL,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_GENERAL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_NW_BUSY,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_AUTH_BILL_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_EXPLICITLY_REJ,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_PREF_CHAN_NOT_AVAIL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_PERSONALITY_INVALID,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_PERS_INVALID,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_RSP_EXPIRED,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_RSP_EXP,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_MSG_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_MSG_FAIL,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_GAUP_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_GAUP_FAIL,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_IRAT_TO_LTE,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_IRAT_TO_LTE,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_NO_RF,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_NO_RF,
        {0, 0},
    },
};


CNAS_HSM_SCP_FAIL_REASON_MAP_SESSION_DEACT_REASON_STRU g_astHsmScpNegRsltIndFailReasonMapSessionDeactReasonTbl[] =
{
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_FAILURE,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_NEG_FAIL,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_EXPIRED,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_AN_EXP,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CONN_OPEN_FAIL,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_GENERAL,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_CONN_OPEN_DENY,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_NW_BUSY,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_CONN_OPEN_DENY,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_AUTH_BILL_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_CONN_OPEN_DENY,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CONN_OPEN_DENY_PREF_CHAN_NOT_AVAIL,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_CONN_OPEN_DENY,
        {0, 0},
    },

    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_PERSONALITY_INVALID,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_PERS_INVALID,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_RSP_EXPIRED,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CFG_RSP_EXP,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_CFG_MSG_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CFG_MSG_FAIL,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_AN_GAUP_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_AN_GAUP_FAIL,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_IRAT_TO_LTE,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_IRAT_TO_LTE,
        {0, 0},
    },
    {   CAS_CNAS_HRPD_SCP_NEG_RSLT_NO_RF,
        CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_NO_RF,
        {0, 0},
    },
};



CNAS_HSM_APS_ERR_CODE_MAP_STRU g_astHsmApsErrCodeMapTbl[] =
{
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_SUCC,{0,0,0},                      HSM_APS_CAUSE_SUCCESS},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_FAIL,{0,0,0},                      HSM_APS_CAUSE_CONN_FAIL},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_PERSIST_FAIL,{0,0,0},              HSM_APS_CAUSE_CONN_FAIL},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_MAX_PROBE,{0,0,0},                 HSM_APS_CAUSE_MAX_ACCESS_PROBES},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_AUTH_BILLING_FAIL,{0,0,0},         HSM_APS_CAUSE_CONN_DENY},

    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_GENERAL,{0,0,0},                   HSM_APS_CAUSE_CONN_DENY},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_BS_BUSY,{0,0,0},                   HSM_APS_CAUSE_CONN_DENY},

    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_PREFER_CH_NOT_VALID,{0,0,0},       HSM_APS_CAUSE_HRPD_PREFER_CH_NOT_VALID},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_TCA_RTC_ACK_TIMEOUT,{0,0,0},       HSM_APS_CAUSE_RTCACK_FAIL},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_NO_RF,{0,0,0},                     HSM_APS_CAUSE_NO_RF},
};


CNAS_HSM_EHSM_ERR_CODE_MAP_STRU g_astHsmEhsmErrCodeMapTbl[] =
{
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_SUCC,{0,0,0},                      EHSM_HSM_RSLT_SUCCESS},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_FAIL,{0,0,0},                      EHSM_HSM_RSLT_CONN_FAIL},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_PERSIST_FAIL,{0,0,0},              EHSM_HSM_RSLT_CONN_FAIL},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_MAX_PROBE,{0,0,0},                 EHSM_HSM_RSLT_MAX_ACCESS_PROBES},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_AUTH_BILLING_FAIL,{0,0,0},         EHSM_HSM_RSLT_CONN_DENY},

    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_GENERAL,{0,0,0},                   EHSM_HSM_RSLT_CONN_DENY},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_BS_BUSY,{0,0,0},                   EHSM_HSM_RSLT_CONN_DENY},

    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_PREFER_CH_NOT_VALID,{0,0,0},       EHSM_HSM_RSLT_PREFER_CH_NOT_VALID},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_TCA_RTC_ACK_TIMEOUT,{0,0,0},       EHSM_HSM_RSLT_RTCACK_FAIL},
    {CAS_CNAS_HRPD_CONN_OPEN_RSLT_NO_RF,{0,0,0},                     EHSM_HSM_RSLT_NO_RF},
};



CNAS_HSM_TIMER_PRECISION_MAP_TBL_STRU g_astHsmTimerPrecisionMapTbl[] =
{
    {TI_CNAS_HSM_WAIT_SCP_ACTIVE_CNF,                               VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_UATI_REQUEST_WAIT_SNP_DATA_CNF,                    VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_SESSION_CLOSE_WAIT_SNP_DATA_CNF,                   VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF,                   VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_MO_KEEP_ALIVE_WAIT_SNP_DATA_CNF,                   VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_MT_KEEP_ALIVE_WAIT_SNP_DATA_CNF,                   VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_HARDWARE_ID_RSP_WAIT_SNP_DATA_CNF,                 VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_WAIT_UATI_ASSIGN,                                  VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_ADDRESS_TIMER,                                     VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_KEEP_ALIVE_TIMER,                                  VOS_TIMER_PRECISION_5},
    {TI_CNAS_HSM_WAIT_HRPD_CONN_CLOSE_IND,                          VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_WAIT_HRPD_CONN_OPEN_IND,                           VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_WAIT_SCP_DEACTIVE_CNF,                             VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,                VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_WAIT_PA_RAT_MODE_NTF,                              VOS_TIMER_NO_PRECISION},
    {TI_CNAS_HSM_WAIT_CARD_READ_CNF,                                VOS_TIMER_NO_PRECISION}
};

#ifdef DMT
VOS_UINT32                              g_ulCurTick = 0;
CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU        g_stAmpNegAttribs;
CAS_HRPD_DEFAULT_SMP_ATTRIB_STRU        g_stSmpNegAttribs;
#endif

/*****************************************************************************
  3 Function Define
*****************************************************************************/

VOS_VOID CNAS_HSM_StartTimer(
    CNAS_HSM_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    CNAS_TIMER_INFO_STRU                stTimerInfo;

    if (0 == ulTimerLen)
    {
        CNAS_WARNING_LOG1(UEPS_PID_HSM, "CNAS_HSM_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return;
    }

    NAS_MEM_SET_S(&stTimerInfo, sizeof(stTimerInfo), 0, sizeof(CNAS_TIMER_INFO_STRU));
    stTimerInfo.ulTimerId               = enTimerId;
    stTimerInfo.ulTimerLen              = ulTimerLen;
    stTimerInfo.ulParam                 = 0;
    /* The timer precision is obtained from the global timer precision table */
    stTimerInfo.ulTimerPrecision        = CNAS_HSM_GetTimerPrecision(enTimerId);

    CNAS_StartTimer(UEPS_PID_HSM, &stTimerInfo);
}



VOS_VOID CNAS_HSM_StopTimer(
    CNAS_HSM_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    CNAS_StopTimer(UEPS_PID_HSM, enTimerId, 0);
}



VOS_UINT32  CNAS_HSM_GenerateInitSessionSeed(VOS_VOID)
{
    CNAS_HSM_HARDWARE_ID_TYPE_ENUM_UINT32   enHwidType;
    VOS_UINT32                              ulCurrentSilce;
    VOS_UINT32                              ulHwid;
    CNAS_HSM_HARDWARE_ID_INFO_STRU         *pstHwidInfo;
    VOS_UINT32                              ulSessionSeed;

    pstHwidInfo = CNAS_HSM_GetHardwareIdInfo();

    enHwidType = pstHwidInfo->enHwidType;

    switch (enHwidType)
    {
        case CNAS_HSM_HARDWARE_ID_TYPE_MEID:
            ulHwid =  ((VOS_UINT32)pstHwidInfo->aucMeId[3] << 24)
                     | (VOS_UINT32)(pstHwidInfo->aucMeId[2] << 16)
                     | (VOS_UINT32)(pstHwidInfo->aucMeId[1] << 8)
                     | (VOS_UINT32)(pstHwidInfo->aucMeId[0]);
            break;

        case CNAS_HSM_HARDWARE_ID_TYPE_ESN:
            ulHwid = pstHwidInfo->ulEsn;
            break;

        default:
            ulHwid = 0;
            break;
    }

    do
    {
        ulCurrentSilce = VOS_GetSlice();
        ulSessionSeed = (ulHwid ^ ulCurrentSilce) % CNAS_HSM_RAND_M_VAL;
    }while (0 == ulSessionSeed);

    return ulSessionSeed;
}


VOS_UINT32  CNAS_HSM_GenerateCurrentSessionSeed(VOS_UINT32 ulPreSessionSeed)
{
#ifdef DMT
    return g_ulCurSessionSeed;
#else
    VOS_UINT32                          ulProductHigh;
    VOS_UINT32                          ulProductLow;
    VOS_UINT32                          ulQuotientHigh;
    VOS_UINT32                          ulQuotientLow;
    VOS_UINT32                          ulRemainder;
    VOS_UINT32                          ulResult;

    ulRemainder     = 0;
    ulQuotientHigh  = 0;
    ulProductLow    = 0;

    /*a * z(n-1)*/
    ulResult = VOS_64Multi32(0x00,
                             CNAS_HSM_RAND_A_VAL,
                             ulPreSessionSeed,
                             &ulProductHigh,
                             &ulProductLow);

    if (VOS_OK != ulResult)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_GenerateCurrentSessionSeed: Generate Session Seed Error in VOS_64Multi32!");

        return ulRemainder;
    }

    /*a * z(n-1) mod(2^31 - 1)*/
    ulResult = VOS_64Div32(ulProductHigh,
                           ulProductLow,
                           CNAS_HSM_RAND_M_VAL,
                           &ulQuotientHigh,
                           &ulQuotientLow,
                           &ulRemainder);

    if (VOS_OK != ulResult)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_GenerateCurrentSessionSeed: Generate Session Seed Error in VOS_64Div32!");

        return ulRemainder;
    }

    return ulRemainder;

#endif
}

VOS_UINT16 CNAS_HSM_CovertBitLenToByteLen(
    VOS_UINT16                   usMsgBitLen
)
{
    VOS_UINT16                   usMsgByteLen;

    if (usMsgBitLen % CNAS_HSM_BIT_LEN_PER_BYTE == 0)
    {
        usMsgByteLen = usMsgBitLen / CNAS_HSM_BIT_LEN_PER_BYTE;
    }
    else
    {
        usMsgByteLen = usMsgBitLen / CNAS_HSM_BIT_LEN_PER_BYTE + 1;
    }

    return usMsgByteLen;
}


VOS_VOID CNAS_HSM_ProcPowerOffReq(VOS_VOID)
{
    if (VOS_FALSE == CNAS_HSM_GetFirstSysAcqFlag())
    {
        /* 如果缓存队列中有ID_CNAS_HSM_HSM_SESSION_CLOSE_IND消息，将Session Info中的状态设置成CLOSE */
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, begin */
        if (CNAS_HSM_INVAILD_CACHE_INDEX != CNAS_HSM_GetCacheIndexByEventType(CNAS_BuildEventType(UEPS_PID_HSM, ID_CNAS_HSM_HSM_SESSION_CLOSE_IND)))
        /* Modified by w00176964 for CNAS内存裁剪, 2015-9-18, end */
        {
            CNAS_HSM_SetSessionStatus(CNAS_HSM_SESSION_STATUS_CLOSE);

            /* 可维可测信息 */
            CNAS_HSM_UpdateHrpdAtiInfo();
        }

        /* HSM updates the Session Keep Alive Info and stops the Keep alive timer */
        CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_POWER_OFF);

        /* HSM will write the Session Keep alive info to NV */
        CNAS_HSM_WriteSessionKeepAliveInfoNvim(CNAS_HSM_GetSessionKeepAliveInfoAddr());
        CNAS_HSM_WriteHrpdSessionInfoNvim();
        CNAS_HSM_WriteHrpdAccessAuthInfoNvim();
    }

    CNAS_HSM_SndHsdPowerOffCnf();

    CNAS_HSM_StopAllTimer();

    CNAS_HSM_InitCtx(CNAS_HSM_INIT_CTX_POWEROFF);
}


VOS_VOID CNAS_HSM_StopAllTimer(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < TI_CNAS_HSM_TIMER_BUTT; i++)
    {
        CNAS_HSM_StopTimer(i);
    }
}


CTTF_HRPD_ATI_TYPE_ENUM_UINT8 CNAS_HSM_CovertHsmAtiTypeToTtfAtiType(
    CNAS_HSM_ATI_TYPE_ENUM_UINT8        enHsmAtiType
)
{
    CTTF_HRPD_ATI_TYPE_ENUM_UINT8 enTtfAtiType = CTTF_HRPD_ATI_TYPE_ENUM_BUTT;

    switch (enHsmAtiType)
    {
        case CNAS_HSM_ATI_TYPE_BATI:
            enTtfAtiType = CTTF_HRPD_BROADCAST_ATI;
            break;

        case CNAS_HSM_ATI_TYPE_MATI:
            enTtfAtiType = CTTF_HRPD_MULTICAST_ATI;
            break;

        case CNAS_HSM_ATI_TYPE_UATI:
            enTtfAtiType = CTTF_HRPD_UNICAST_ATI;
            break;

        case CNAS_HSM_ATI_TYPE_RATI:
            enTtfAtiType = CTTF_HRPD_RANDOM_ATI;
            break;

        case CNAS_HSM_ATI_TYPE_INACTIVE:
            enTtfAtiType = CTTF_HRPD_INACTIVE_ATI;
            break;

        default:
            enTtfAtiType = CTTF_HRPD_ATI_TYPE_ENUM_BUTT;
            break;
    }

    return enTtfAtiType;
}


VOS_VOID CNAS_HSM_SetRandEsnAsHardwareIdInfo(VOS_VOID)
{
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstHwIdInfo;
    VOS_UINT32                          ulTick;

    pstHwIdInfo                         = CNAS_HSM_GetHardwareIdInfo();

    pstHwIdInfo->enHwidType     = CNAS_HSM_HARDWARE_ID_TYPE_ESN;
    pstHwIdInfo->enHwidSrcType  = CNAS_HSM_HARDWARE_ID_SRC_TYPE_RAND;

    /*generate rand ESN*/
    ulTick = VOS_GetTick();
    VOS_SetSeed(ulTick);
#ifdef DMT
    pstHwIdInfo->ulEsn = g_ulCurRandEsn;
#else
    pstHwIdInfo->ulEsn = VOS_Rand(0x00FFFFFF);
#endif
    CNAS_HSM_LogHwIdInfo(pstHwIdInfo);
    return;
}


VOS_UINT8 CNAS_HSM_CompareSeqNum(
    VOS_UINT8                           ucNewSeqNum,
    VOS_UINT8                           ucOldSeqNum
)
{
    VOS_UINT8                           ucIsGreater;
    VOS_UINT16                          usGreaterNumLimit;
    VOS_UINT16                          usSeqSpace;

    usSeqSpace = 1 << CNAS_HSM_SEQ_NUM_BIT_LEN; /* If # of bits = s, seq space = 2^s, Here s = 8 */

    /* Calculate the range limit for which a new sequence number is considered
       greater than the old one.*/
    usGreaterNumLimit = ucOldSeqNum + usSeqSpace / 2;

    /* C.S0024-A_v3: 14.6 Sequence Number Validation
     ---------------------------------------------------------------------------
     For any sequence number N, the numbers in the range [N+1, N+2^(s-1)-1] is
     greater than N. Any number in the range [N-2^(s-1), N-1] is smaller
     ---------------------------------------------------------------------------
     */

    if (ucNewSeqNum > ucOldSeqNum)
    {
        if (ucNewSeqNum < usGreaterNumLimit)
        {
            ucIsGreater = VOS_TRUE;
        }
        else
        {
            ucIsGreater = VOS_FALSE;
        }
    }
    else
    {
        if ((ucOldSeqNum - ucNewSeqNum) > usSeqSpace / 2)
        {
            ucIsGreater = VOS_TRUE;
        }
        else
        {
            ucIsGreater = VOS_FALSE;
        }
    }

    return ucIsGreater;
}


VOS_UINT8 CNAS_HSM_IsValidUatiAssignment(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU      *pstUatiAssignMsg
)
{
    /* C.S0024-A_v3: 14.6 Sequence Number Validation
     ---------------------------------------------------------------------------
     When a message arrives, the receiver compares the sequence number of the message
     with V(R). If the sequence number is greater than V(R), the message
     is considered a valid message and V(R)is set to this sequence number; otherwise,
     the message is considered an invalid message.

     For any sequence number N, the numbers in the range [N+1, N+2^(s-1)-1] is
     greater than N. Any number in the range [N-2^(s-1), N-1] is smaller
     ---------------------------------------------------------------------------
    */

    return (CNAS_HSM_CompareSeqNum(pstUatiAssignMsg->ucMsgSeq, CNAS_HSM_GetCurrUATIAssignMsgSeqNum()));
}


VOS_UINT8 CNAS_HSM_IsFreshUatiAssignment(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU      *pstUatiAssignMsg
)
{
    /* C.S0024-A_v3: 7.3.7.1.5.1 Access Terminal Requirements
    --------------------------------------------------------------------------------------------
    A valid UATIAssignment message that satisfies either of the following conditions is
    called a "fresh" UATIAssignment message:

    1. OverheadParametersUpToDate, provided as the public data of the Overhead Messages
       Protocol, is equal to 1 and the UATIColorCode field in the message matches the ColorCode,
       given as public data of the Overhead Messages Protocol, or

    2. the SubnetIncluded field of the message is equal to 1.
    --------------------------------------------------------------------------------------------
    */

    if (1 == pstUatiAssignMsg->ucSubnetIncluded)
    {
        return VOS_TRUE;
    }

    /* UATISubnetMask and UATI104 not included */
    if (1 == CNAS_HSM_GetOhmParameterUpToDate())
    {
        if ((pstUatiAssignMsg->ucUATIColorCode) == (CNAS_HSM_GetHrpdSysInfoAddr()->ucColorCode))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT8 CNAS_HSM_IsUatiAssignValidAndFresh(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU          *pstUatiAssignMsg
)
{
    if (VOS_FALSE == CNAS_HSM_IsValidUatiAssignment(pstUatiAssignMsg))
    {
        /* hook the message */
        CNAS_HSM_LogUatiAssignMsg(pstUatiAssignMsg, CNAS_HSM_UATI_ASSIGN_CATE_INVALID);

        return VOS_FALSE;
    }

    if (VOS_FALSE == CNAS_HSM_IsFreshUatiAssignment(pstUatiAssignMsg))
    {
        /* hook the message */
        CNAS_HSM_LogUatiAssignMsg(pstUatiAssignMsg, CNAS_HSM_UATI_ASSIGN_CATE_NOT_FRESH);

        return VOS_FALSE;
    }

    /* hook the message */
    CNAS_HSM_LogUatiAssignMsg(pstUatiAssignMsg, CNAS_HSM_UATI_ASSIGN_CATE_NORMAL);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_HSM_SquareRoot(VOS_UINT32 ulNumber)
{
    VOS_UINT32                          i;
    VOS_FLOAT                           x;
    VOS_FLOAT                           y;
    VOS_FLOAT                           f;
    VOS_UINT32                          ulResult;

    f   = 1.5F;

    x   = ulNumber * 0.5F;

    y   = ulNumber;

    i   = * ( VOS_UINT32 * ) &y;

    i   = 0x5f375a86 - ( i >> 1 );         /*魔术数*/

    y   = * ( VOS_FLOAT * ) &i;

    y   = y * ( f - ( x * y * y ) );        /*迭代1    1/sqrt(number)  */

    y   = y * ( f - ( x * y * y ) );        /*迭代2    1/sqrt(number)  */

    y   = y * ( f - ( x * y * y ) );        /*迭代3    1/sqrt(number)  */

    ulResult = (VOS_UINT32)(ulNumber * y);

    return ulResult;
}


VOS_UINT32 CNAS_HSM_CalcNoMonitorDistance(
    VOS_INT32                           ulOldLat,
    VOS_INT32                           ulOldLong,
    VOS_INT32                           ulNewLat,
    VOS_INT32                           ulNewLong
)
{
    VOS_UINT32                          ulDeltaLat;
    VOS_INT32                           lDeltaLong;
    VOS_UINT32                          ulDist;
    VOS_DOUBLE                          dCosRlst;

    if (ulNewLat > ulOldLat)
    {
        ulDeltaLat = (VOS_UINT32)(ulNewLat - ulOldLat);
    }
    else
    {
        ulDeltaLat = (VOS_UINT32)(ulOldLat - ulNewLat);
    }

    dCosRlst = cos((VOS_DOUBLE)(((3.14F) / 180 * ulOldLat) / 14400));

    lDeltaLong = (VOS_INT32)((ulNewLong - ulOldLong) * dCosRlst);

    if (0 > lDeltaLong)
    {
        lDeltaLong = -lDeltaLong;
    }

    if (CNAS_HSM_180DEGREE < lDeltaLong)
    {
        lDeltaLong = CNAS_HSM_360DEGREE - lDeltaLong;
    }

    /* prevent overflow */
    if ((0x10000 < ulDeltaLat) || (0x10000 < lDeltaLong))
    {
        ulDist = CNAS_HSM_SquareRoot(((ulDeltaLat >> 4) * (ulDeltaLat >> 4))
                        + ((((VOS_UINT32)lDeltaLong) >> 4) * (((VOS_UINT32)lDeltaLong) >> 4)));
    }
    else
    {
        ulDist = CNAS_HSM_SquareRoot((ulDeltaLat * ulDeltaLat) + (lDeltaLong * lDeltaLong));
        ulDist = ulDist >> 4;
    }

    return ulDist;
}


VOS_VOID CNAS_HSM_HandleUatiAssignMsg(
    CNAS_HSM_UATI_ASSIGN_MSG_STRU      *pstUatiAssignMsg
)
{
    CNAS_HSM_L1_STA_ENUM_UINT32         enCurrMainState;

    /* save sequence number here */
    /* C.S0024: 7.3.7.1.2 UATIAssignment Message Validation:
      When the access terminal receives a UATIAssignment message, it shall validate the message,
      using the procedure defined in 14.6 (S is equal to 8).
      The access terminal shall discard the message if it is invalid.
    */
    CNAS_HSM_SetCurrUATIAssignMsgSeqNum(pstUatiAssignMsg->ucMsgSeq);

    enCurrMainState = CNAS_HSM_GetCurrMainState();

    if (CNAS_HSM_L1_STA_OPEN == enCurrMainState)
    {
        CNAS_HSM_HandleUatiAssignMsg_OpenState(pstUatiAssignMsg);
    }
    else
    {
        /* Main state is SetupState*/
        CNAS_HSM_HandleUatiAssignMsg_SetupState(pstUatiAssignMsg);
    }

    /* 可维可测信息 */
    CNAS_HSM_UpdateHrpdAtiInfo();
}


/*****************************************************************************
Function Name   :   CNAS_HSM_GetCloseReasonSendAnByDeactReason
Description     :   Get session close reason sent to AN by session deative reason
Input parameters:   enSessionDeactReason  - Session deactive reason
Outout parameters:  penOutCloseReasonSendToAn - Session close reason send to AN
                    原因值为BUTT说明不需要给网络发SessionClose
Return Value    :   None

Modify History  :
1)  Date           : 2015-05-29
    Author         : y00174758
    Modify content : Create
*****************************************************************************/
VOS_VOID CNAS_HSM_GetCloseReasonSendAnByDeactReason(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason,
    CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_ENUM_UINT8      *penOutCloseReasonSendToAn
)
{
    VOS_UINT8                                               ucReasonCnt;
    VOS_UINT8                                               ucLoop;

    ucReasonCnt = sizeof(g_astHsmDeactReasonMapReasonSendAnTbl) /
                        sizeof(CNAS_HSM_DEACT_REASON_MAP_REASON_SEND_AN_STRU);

    for (ucLoop = 0; ucLoop < ucReasonCnt; ucLoop++)
    {
        if (enSessionDeactReason == g_astHsmDeactReasonMapReasonSendAnTbl[ucLoop].enSessionDeactReason)
        {
            *penOutCloseReasonSendToAn = g_astHsmDeactReasonMapReasonSendAnTbl[ucLoop].enCloseReasonSendToAn;

            return;
        }
    }

    *penOutCloseReasonSendToAn = CNAS_HSM_SESSION_CLOSE_PROTOCOL_REASON_BUTT;
}


CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8 CNAS_HSM_ConvertScpActiveFailReasonToSessionDeactReason(
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpReason
)
{
    VOS_UINT8                                               ucReasonCnt;
    VOS_UINT8                                               ucLoop;

    ucReasonCnt = sizeof(g_astHsmScpFailReasonMapSessionDeactReasonTbl) /
                            sizeof(CNAS_HSM_SCP_FAIL_REASON_MAP_SESSION_DEACT_REASON_STRU);

    for (ucLoop = 0; ucLoop < ucReasonCnt; ucLoop++)
    {
        if (enScpReason == g_astHsmScpFailReasonMapSessionDeactReasonTbl[ucLoop].enScpReason)
        {
            return g_astHsmScpFailReasonMapSessionDeactReasonTbl[ucLoop].enSessionDeactReason;
        }
    }

    return CNAS_HSM_SESSION_DEACT_REASON_SCP_NEG_FAIL;
}


CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8 CNAS_HSM_ConvertScpNegRsltIndFailReasonToSessionDeactReason(
    CAS_CNAS_HRPD_SCP_NEG_RSLT_ENUM_UINT8                   enScpReason
)
{
    VOS_UINT8                                               ucReasonCnt;
    VOS_UINT8                                               ucLoop;

    ucReasonCnt = sizeof(g_astHsmScpNegRsltIndFailReasonMapSessionDeactReasonTbl) /
                            sizeof(CNAS_HSM_SCP_FAIL_REASON_MAP_SESSION_DEACT_REASON_STRU);

    for (ucLoop = 0; ucLoop < ucReasonCnt; ucLoop++)
    {
        if (enScpReason == g_astHsmScpNegRsltIndFailReasonMapSessionDeactReasonTbl[ucLoop].enScpReason)
        {
            return g_astHsmScpNegRsltIndFailReasonMapSessionDeactReasonTbl[ucLoop].enSessionDeactReason;
        }
    }

    return CNAS_HSM_SESSION_DEACT_REASON_SCP_NEG_FAIL;
}



HSM_HLU_SESSION_RAT_MODE_ENUM_UINT8 CNAS_HSM_ConvertHsmSessionTypeToHluSessionRatMode(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8    enSessionType
)
{
    HSM_HLU_SESSION_RAT_MODE_ENUM_UINT8 enHluSessionRatMode;

    enHluSessionRatMode = HSM_HLU_SESSION_RAT_MODE_ENUM_BUTT;

    switch (enSessionType)
    {
        case CNAS_HSM_SESSION_TYPE_HRPD:
            enHluSessionRatMode = HSM_HLU_SESSION_RAT_MODE_HRPD;
            break;

        case CNAS_HSM_SESSION_TYPE_EHRPD:
            enHluSessionRatMode = HSM_HLU_SESSION_RAT_MODE_EHRPD;
            break;

        default:
            break;
    }

    return enHluSessionRatMode;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_ConvertPaModeToHsmSessionType
 功能描述  : convert session type from PA mode to hsm session info type formate
 输入参数  : 无
 输出参数  : 无
 返 回 值  : CAS_HSM_SESSION_TYPE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
CNAS_HSM_SESSION_TYPE_ENUM_UINT8 CNAS_HSM_ConvertPaModeToHsmSessionType(
    CAS_CNAS_HRPD_PA_MODE_ENUM_UINT8    enPaMode
)
{
    switch (enPaMode)
    {
        case CAS_CNAS_HRPD_PA_MODE_HRPD:
            return CNAS_HSM_SESSION_TYPE_HRPD;

        case CAS_CNAS_HRPD_PA_MODE_EHRPD :
            return CNAS_HSM_SESSION_TYPE_EHRPD;

        default:
            return CNAS_HSM_SESSION_TYPE_BUTT;
    }
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_ConvertHsmSessionToEhsmSessionType
 功能描述  : convert HSM session type to EHSM session type formate
 输入参数  : 无
 输出参数  : 无
 返 回 值  : EHSM_HSM_SESSION_TYPE_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月30日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
EHSM_HSM_SESSION_TYPE_ENUM_UINT32 CNAS_HSM_ConvertHsmSessionToEhsmSessionType(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8   enSessionType
)
{
    switch (enSessionType)
    {
        case CNAS_HSM_SESSION_TYPE_HRPD:
            return EHSM_HSM_SESSION_TYPE_HRPD;

        case CNAS_HSM_SESSION_TYPE_EHRPD:
            return EHSM_HSM_SESSION_TYPE_EHRPD;

        default:
            return EHSM_HSM_SESSION_TYPE_BUTT;
    }
}


VOS_UINT8 CNAS_HSM_IsUIMIDValid(
    VOS_UINT8                          *pucEFRUIMID
)
{
    VOS_UINT8                           ucUIMIDByteNum;
    VOS_UINT8                           i;

    /* the first byte of EFRUIMID indicates the bytes num of UIMID (here,the num is 4) in EFRUIMID */
    ucUIMIDByteNum = pucEFRUIMID[0];

    /*
      according to the protocal C.S0023-D_v2.0_R-UIM ,the EF of EFRuimid store the 32-bit UIMID constructed in the following way:

      Bytes              Description                M/O                Length

        1               number of Bytes              M                  1byte

        2               lowest-order byte            M                  1byte

        3                   ...                      M                  1byte

        4                   ...                      M                  1byte

        5                   ...                      M                  1byte

        6                   ...                      O                  1byte

        7                   ...                      O                  1byte

        8               highest-order byte           O                  1byte

        the EF consists of 8 bytes,in which the first byte indicates the bytes num of UIMID (here,the num is 4) in EF,
        so,when check the validity of UIMID,just need to check from the second byte to the fifth byte
        if all the bits of the four bytes which indicates the UIMID value from the second byte to the fifth byte are 1,then UIMID is invalid
        vice versa
    */
    for (i = 1; i <= ucUIMIDByteNum; i++)
    {
        if (0xFF != pucEFRUIMID[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_VOID CNAS_HSM_SetUIMIDAsHardwareIdInfo(VOS_VOID)
{

    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstHwIdInfo;
    CNAS_CCB_UIMID_STRU                *pstUIMID;
    VOS_UINT8                           ucIndex;

    pstHwIdInfo                     = CNAS_HSM_GetHardwareIdInfo();
    pstUIMID                        = CNAS_CCB_GetUIMID();

    pstHwIdInfo->enHwidType         = CNAS_HSM_HARDWARE_ID_TYPE_ESN;
    pstHwIdInfo->enHwidSrcType      = CNAS_HSM_HARDWARE_ID_SRC_TYPE_UIM;

    pstHwIdInfo->ulEsn              = 0;

     /*
      according to the protocal C.S0023-D_v2.0_R-UIM ,the EF of EFRuimid store the 32-bit UIMID constructed in the following way:

      Bytes              Description                M/O                Length
        1               number of Bytes              M                  1byte
        2               lowest-order byte            M                  1byte
        3                   ...                      M                  1byte
        4                   ...                      M                  1byte
        5                   ...                      M                  1byte
        6                   ...                      O                  1byte
        7                   ...                      O                  1byte
        8               highest-order byte           O                  1byte

        the EF consists of 8 bytes,in which the first byte indicates the bytes num of UIMID (here,the num is 4) in EF,
        the following 4 bytes indicates the UIMID value and the highest-order byte is the fifth byte,
        so,when read the UIMID value,should read the bytes from fifth byte to the the second byte
    */
    /* the highest order byte is the last M byte */
    for (ucIndex = CNAS_CCB_UIMID_OCTET_LEN; ucIndex > 0; ucIndex--)
    {
        pstHwIdInfo->ulEsn <<= CNAS_HSM_BIT_LEN_PER_BYTE;
        pstHwIdInfo->ulEsn  |= pstUIMID->aucEFRUIMID[ucIndex];
    }

}



 VOS_UINT8 CNAS_HSM_IsPesnValid(
    NV_PESN_STRU                       *pstPesn
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < PESN_NV_DATA_LEN; ucIndex++)
    {
        if (0x00 != pstPesn->aucPEsn[ucIndex])
        {
           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


 VOS_UINT8 CNAS_HSM_IsMeidValid(
    NV_MEID_STRU                       *pstMeid
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < MEID_NV_DATA_LEN_NEW; ucIndex++)
    {
        if (0x00 != pstMeid->aucMeID[ucIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID CNAS_HSM_ConvertCdmaSysTimeToHsmFormat(
    VOS_UINT32                         *pulCdmaSysTime,
    VOS_UINT32                         *pulHsmSysTime
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          aulPartialResult[CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME];
    VOS_UINT32                          ulRemainder;

    if ((VOS_NULL_PTR == pulCdmaSysTime)
     || (VOS_NULL_PTR == pulHsmSysTime))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ConvertCdmaSysTimeToHsmFormat: NULL_PTR passed to function!");
        return ;
    }

    NAS_MEM_SET_S(pulHsmSysTime, CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME * sizeof(VOS_UINT32), 0x00, CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME * sizeof(VOS_UINT32));

    /* SystemTime from sync message,  pulCdmaSysTime[0] bit[31:0] = systemTime bit[31:0],
    pulCdmaSysTime[1] bit[4:0] = systemTime bit[36:32] unit 26.67 ms (26670 microsec) */

    /* The operation done is: HSM_Sys_time = (CDMA_Sys_Time * 26670) / 1000 */

    /* For better accuracy, proceed in two steps: first multiply the Sys time by 26670 */
    ulRslt = VOS_64Multi32(pulCdmaSysTime[1],
                           pulCdmaSysTime[0],
                           (VOS_UINT32) CNAS_HSM_CDMA_SYS_TIME_MICROSEC_UNIT,
                           &(aulPartialResult[1]),
                           &(aulPartialResult[0]));

    if (VOS_OK != ulRslt)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ConvertCdmaSysTimeToHsmFormat: Error in VOS_64Multi32!");
        return;
    }

    ulRemainder = 0;

    /* Second step, divide the partial result by 1000. Discard the remainder */
    ulRslt = VOS_64Div32(aulPartialResult[1],
                         aulPartialResult[0],
                         (VOS_UINT32) 1000,
                         &(pulHsmSysTime[1]),
                         &(pulHsmSysTime[0]),
                         &(ulRemainder));

    if (VOS_OK != ulRslt)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ConvertCdmaSysTimeToHsmFormat: Error in VOS_64Div32!");
        return;
    }

    return;
}




VOS_VOID CNAS_HSM_64Add32(
    CNAS_HSM_64_BIT_DATA_STRU          *pstAddend,
    VOS_UINT32                          ulAddFactor,
    CNAS_HSM_64_BIT_DATA_STRU          *pstRslt
)
{
    if (0xFFFFFFFF - pstAddend->ulLowerOrderWord >= ulAddFactor)
    {
        pstRslt->ulLowerOrderWord   = pstAddend->ulLowerOrderWord + ulAddFactor;
        pstRslt->ulHigherOrderWord  = pstAddend->ulHigherOrderWord;
    }
    else
    {
        if (0xFFFFFFFF == pstAddend->ulHigherOrderWord)
        {
            CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_64Add32: Overflow detected! ");
            return;
        }

        pstRslt->ulHigherOrderWord = pstAddend->ulHigherOrderWord + 1;
        pstRslt->ulLowerOrderWord  = ulAddFactor - (0xFFFFFFFF - pstAddend->ulLowerOrderWord) - 1;
    }

    return;
}




VOS_VOID CNAS_HSM_64Sub64(
    CNAS_HSM_64_BIT_DATA_STRU          *pstMinuend,
    CNAS_HSM_64_BIT_DATA_STRU          *pstSubtrahend,
    CNAS_HSM_64_BIT_DATA_STRU          *pstResult
)
{
    /* If the Minuend is less than the subtrahend, then make error log and return */
    if (pstMinuend->ulHigherOrderWord < pstSubtrahend->ulHigherOrderWord)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_64Sub64: Minuend is less than Subtrahend!");
        return;
    }

    if(pstMinuend->ulLowerOrderWord >= pstSubtrahend->ulLowerOrderWord)
    {
        pstResult->ulHigherOrderWord = pstMinuend->ulHigherOrderWord - pstSubtrahend->ulHigherOrderWord;
        pstResult->ulLowerOrderWord  = pstMinuend->ulLowerOrderWord  - pstSubtrahend->ulLowerOrderWord;
    }
    else if (pstMinuend->ulHigherOrderWord >= pstSubtrahend->ulHigherOrderWord + 1)
    {
        pstResult->ulHigherOrderWord = pstMinuend->ulHigherOrderWord - pstSubtrahend->ulHigherOrderWord - 1;
        pstResult->ulLowerOrderWord  = pstMinuend->ulLowerOrderWord  + (0xFFFFFFFF - pstSubtrahend->ulLowerOrderWord) + 1;
    }
    else
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_64Sub64: Minuend is less than Subtrahend!");
    }

    return;
}



VOS_TIMER_PRECISION_ENUM_UINT32 CNAS_HSM_GetTimerPrecision(
    CNAS_HSM_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLoopLimit;
    VOS_TIMER_PRECISION_ENUM_UINT32     enTimerPrecision;

    ucLoopLimit = sizeof(g_astHsmTimerPrecisionMapTbl) / sizeof(CNAS_HSM_TIMER_PRECISION_MAP_TBL_STRU);

    for (ucLoop = 0; ucLoop < ucLoopLimit; ucLoop++)
    {
        if (enTimerId == g_astHsmTimerPrecisionMapTbl[ucLoop].enTimerId)
        {
            enTimerPrecision = g_astHsmTimerPrecisionMapTbl[ucLoop].enTimerPrecision;

            return enTimerPrecision;
        }
    }

    /* Return No precision by default */
    return VOS_TIMER_NO_PRECISION;
}




VOS_VOID CNAS_HSM_SaveSysTimeAndCurSysTick(
    VOS_UINT32                         *pulCdmaSysTime
)
{
    VOS_UINT32                          aulCurSysTime[CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME];

    if (VOS_NULL_PTR == pulCdmaSysTime)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SaveSysTimeAndCurSysTick: Input Ptr is NULL!");

        return;
    }

    NAS_MEM_SET_S(aulCurSysTime, sizeof(aulCurSysTime), 0x00, CNAS_HSM_NUM_WORDS_IN_CDMA_SYS_TIME * sizeof(VOS_UINT32));

    /* Convert the CDMA Sys time received from Sync Message to HSM format */
    CNAS_HSM_ConvertCdmaSysTimeToHsmFormat(pulCdmaSysTime, aulCurSysTime);

    /* Save the current sys tick and sys time to global variable */
    CNAS_HSM_SetReferenceSysTick(CNAS_HSM_GetSysTick());

    /* Save the Current Sys Time to global variable */
    CNAS_HSM_SetLastReceivedSysTime(aulCurSysTime);

    return;
}




VOS_UINT32  CNAS_HSM_GetSysTick(VOS_VOID)
{
    #ifdef DMT
        return g_ulCurTick;
    #else
        return VOS_GetTick();
    #endif
}



CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8 CNAS_HSM_ConvertCasSessionRelTypeToHsmSessionRelType(
    CAS_CNAS_HRPD_SESSION_RELEASE_TYPE_UINT8                enSessionReleaseType
)
{
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enHsmSessinRelType;

    enHsmSessinRelType = CNAS_HSM_SESSION_RELEASE_TYPE_BUTT;

    switch (enSessionReleaseType)
    {
        case CAS_CNAS_HRPD_SESSION_RELEASE_0:
            enHsmSessinRelType = CNAS_HSM_SESSION_RELEASE_TYPE_0;
            break;

        case CAS_CNAS_HRPD_SESSION_RELEASE_A:
            enHsmSessinRelType = CNAS_HSM_SESSION_RELEASE_TYPE_A;
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ConvertCasSessionRelTypeToHsmSessionRelType: unknow session rel type!");
            break;
    }

    return enHsmSessinRelType;
}


VOS_UINT8 CNAS_HSM_IsIccIdValid(
    VOS_UINT8                          *pucIccId
)
{
    VOS_UINT8                           i;

    /* ICCID的长度为CNAS_CCB_ICCID_OCTET_LEN，若其为全F，则认为该ICCID为无效 */
    for (i = 0; i < CNAS_CCB_ICCID_OCTET_LEN; i++)
    {
        if (0xFF != pucIccId[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 CNAS_HSM_IsInUatiProcedure(VOS_VOID)
{
    CNAS_HSM_SS_ID_ENUM_UINT32                              enSubSta;

    enSubSta = CNAS_HSM_GetCurrSubState();

    if ((CNAS_HSM_SS_UATI_REQUEST_WAIT_SNP_DATA_CNF == enSubSta)
     || (CNAS_HSM_SS_UATI_REQUEST_WAIT_UATI_ASSIGN  == enSubSta))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 CNAS_HSM_IsInScpProcedure(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32         enMainState;
    CNAS_HSM_SS_ID_ENUM_UINT32          enSubSta;

    enMainState = CNAS_HSM_GetCurrMainState();
    enSubSta    = CNAS_HSM_GetCurrSubState();

    if (CNAS_HSM_L1_STA_OPEN != enMainState)
    {
        return VOS_FALSE;
    }

    if ((CNAS_HSM_SS_SESSION_ACT_WAIT_SCP_ACTIVE_CNF  == enSubSta)
     || (CNAS_HSM_SS_SESSION_ACT_WAIT_PA_RAT_MODE_NTF == enSubSta))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 CNAS_HSM_IsEqualIccId(
    VOS_UINT8                          *pucSrcIccId,
    VOS_UINT8                          *pucDstIccId
)
{
    VOS_UINT8                           i;

    for (i = 0; i < CNAS_CCB_ICCID_OCTET_LEN; i++)
    {
        if (pucSrcIccId[i] != pucDstIccId[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_UINT8 CNAS_HSM_IsEqualMeId(
    VOS_UINT8                          *pucSrcMeId,
    VOS_UINT8                          *pucDstMeId
)
{
    VOS_UINT8                           i;

    for (i = 0; i < CNAS_HSM_MEID_OCTET_NUM; i++)
    {
        if (pucSrcMeId[i] != pucDstMeId[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_UINT8 CNAS_HSM_IsIccidChanged(
    VOS_UINT8                          *pucSrcIccId,
    VOS_UINT8                          *pucDstIccId
)
{
    if (VOS_FALSE == CNAS_HSM_IsIccIdValid(pucSrcIccId))
    {
        return VOS_TRUE;
    }

    if (VOS_FALSE == CNAS_HSM_IsIccIdValid(pucDstIccId))
    {
        return VOS_TRUE;
    }

    if (VOS_FALSE == CNAS_HSM_IsEqualIccId(pucSrcIccId, pucDstIccId))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 CNAS_HSM_IsHardwareIdChanged(
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstSrcHwid,
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstDstHwid
)
{
    if ((CNAS_HSM_HARDWARE_ID_TYPE_NULL == pstSrcHwid->enHwidType)
     || (CNAS_HSM_HARDWARE_ID_TYPE_NULL == pstDstHwid->enHwidType)
     || (CNAS_HSM_HARDWARE_ID_TYPE_BUTT == pstSrcHwid->enHwidType)
     || (CNAS_HSM_HARDWARE_ID_TYPE_BUTT == pstDstHwid->enHwidType))
    {
        return VOS_TRUE;
    }

    if (pstSrcHwid->enHwidType != pstDstHwid->enHwidType)
    {
        return VOS_TRUE;
    }

    if ((CNAS_HSM_HARDWARE_ID_SRC_TYPE_BUTT == pstSrcHwid->enHwidSrcType)
     || (CNAS_HSM_HARDWARE_ID_SRC_TYPE_BUTT == pstDstHwid->enHwidSrcType))
    {
        return VOS_TRUE;
    }

    if (pstSrcHwid->enHwidSrcType != pstDstHwid->enHwidSrcType)
    {
        return VOS_TRUE;
    }

    if (CNAS_HSM_HARDWARE_ID_TYPE_ESN == pstSrcHwid->enHwidType)
    {
        if (pstSrcHwid->ulEsn != pstDstHwid->ulEsn)
        {
            return VOS_TRUE;
        }
    }

    if (CNAS_HSM_HARDWARE_ID_TYPE_MEID == pstSrcHwid->enHwidType)
    {
        if (VOS_FALSE == CNAS_HSM_IsEqualMeId(pstSrcHwid->aucMeId, pstDstHwid->aucMeId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT8 CNAS_HSM_IsHrpdAccessAuthUserChanged(
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstSrcAccessAuthInfo,
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstDstAccessAuthInfo
)
{
    if ((VOS_TRUE != pstSrcAccessAuthInfo->ucAccessAuthAvailFlag)
     || (VOS_TRUE != pstDstAccessAuthInfo->ucAccessAuthAvailFlag))
    {
        return VOS_TRUE;
    }

    if (pstSrcAccessAuthInfo->ucAccessAuthUserNameLen != pstDstAccessAuthInfo->ucAccessAuthUserNameLen)
    {
        return VOS_TRUE;
    }

    if (0 != PS_MEM_CMP(pstSrcAccessAuthInfo->aucAccessAuthUserName,
                        pstDstAccessAuthInfo->aucAccessAuthUserName,
                        pstDstAccessAuthInfo->ucAccessAuthUserNameLen))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 CNAS_HSM_IsEsnMeidMeChanged(
    CNAS_HSM_STORE_ESN_MEID_RSLT_STRU                      *pstStoreEsnMeidRslt,
    CNAS_CCB_ESNMEIDME_INFO_STRU                           *pstEsnMeidMeInfo,
    CNAS_HSM_HARDWARE_ID_INFO_STRU                         *pstDstHwid
)
{
    /* 如果卡做了store操作，若返回的结果是未改变则认为未换卡，否则为换卡了
    *  如果卡未做store操作，则根据卡中的meid或者esn与nv中保存的最后一次session的meid
    *  或者esn进行比较，判断是否换卡 */
    if (VOS_TRUE == pstStoreEsnMeidRslt->ucIsStored)
    {
        if (VOS_TRUE == pstStoreEsnMeidRslt->ucIsChanged)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* 若都为meid,判断卡中的meid和nv中保存的最后一次session的meid，若相同，则未换卡，否则换卡了 */
    if ((CNAS_CCB_ESN_MEID_TYPE_MEID    == pstEsnMeidMeInfo->enEsnMeidType)
     && (CNAS_HSM_HARDWARE_ID_TYPE_MEID == pstDstHwid->enHwidType))
    {
        if (0 != PS_MEM_CMP(pstEsnMeidMeInfo->u.aucMeid, pstDstHwid->aucMeId, sizeof(pstDstHwid->aucMeId)))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
    /* 若都为esn,判断卡中的meid和nv中保存的最后一次session的esn，若相同，则未换卡，否则换卡了 */
    else if ((CNAS_CCB_ESN_MEID_TYPE_ESN    == pstEsnMeidMeInfo->enEsnMeidType)
          && (CNAS_HSM_HARDWARE_ID_TYPE_ESN == pstDstHwid->enHwidType))
    {
        if (0 != PS_MEM_CMP(pstEsnMeidMeInfo->u.aucEsn, &(pstDstHwid->ulEsn), sizeof(pstDstHwid->ulEsn)))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
    /* 若类型不同或者不对，则认为换卡了 */
    else
    {
        return VOS_TRUE;
    }
}



VOS_VOID CNAS_HSM_ProcTrafficFlowOnForwardChannel(VOS_VOID)
{
    VOS_UINT32                          ulCurSysTick;
    /* get the current system tick and save to Keep Alive Ctrl ctx */
    ulCurSysTick = CNAS_HSM_GetSysTick();

    /* Save the tick to the global variable */
    CNAS_HSM_SetSysTickFwdTrafficChan(ulCurSysTick);

    return;
}


HSM_APS_CAUSE_ENUM_UINT32 CNAS_HSM_MapApsCause(
    CAS_CNAS_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                 enRslt
)
{
    VOS_UINT8                                               ucReasonCnt;
    VOS_UINT8                                               ucLoop;
    HSM_APS_CAUSE_ENUM_UINT32                               enApsCause;

    ucReasonCnt = sizeof(g_astHsmApsErrCodeMapTbl) / sizeof(CNAS_HSM_APS_ERR_CODE_MAP_STRU);

    for (ucLoop = 0; ucLoop < ucReasonCnt; ucLoop++)
    {
        if (enRslt == g_astHsmApsErrCodeMapTbl[ucLoop].enCasRslt)
        {
            enApsCause = g_astHsmApsErrCodeMapTbl[ucLoop].enApsRslt;

            return enApsCause;
        }
    }

    return HSM_APS_CAUSE_BUTT;
}


EHSM_HSM_RSLT_ENUM_UINT32 CNAS_HSM_MapEhsmCause(
    CAS_CNAS_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                 enRslt
)
{
    VOS_UINT8                                               ucReasonCnt;
    VOS_UINT8                                               ucLoop;
    EHSM_HSM_RSLT_ENUM_UINT32                               enEhsmRlst;

    ucReasonCnt = sizeof(g_astHsmEhsmErrCodeMapTbl) / sizeof(CNAS_HSM_EHSM_ERR_CODE_MAP_STRU);

    for (ucLoop = 0; ucLoop < ucReasonCnt; ucLoop++)
    {
        if (enRslt == g_astHsmEhsmErrCodeMapTbl[ucLoop].enCasRslt)
        {
            enEhsmRlst = g_astHsmEhsmErrCodeMapTbl[ucLoop].enEhsmRslt;

            return enEhsmRlst;
        }
    }

    return EHSM_HSM_RSLT_BUTT;
}


VOS_VOID CNAS_HSM_UpdateHrpdSysInfo(
    HSD_HSM_OVERHEAD_MSG_IND_STRU      *pstOverHeadMsgInd
)
{
    CNAS_HSM_HRPD_SYS_INFO_STRU        *pstHprdSysInfo;

    pstHprdSysInfo    = CNAS_HSM_GetHrpdSysInfoAddr();

    CNAS_HSM_SetOhmParameterUpToDate(1);

    pstHprdSysInfo->ucColorCode                     = pstOverHeadMsgInd->ucColorCode;
    pstHprdSysInfo->ucSecondaryColorCodeCount       = pstOverHeadMsgInd->ucSecondaryColorCodeCount;
    pstHprdSysInfo->ucSubNetMask                    = pstOverHeadMsgInd->ucSubNetMask;

    NAS_MEM_CPY_S(pstHprdSysInfo->aucSectorId,
                  sizeof(pstHprdSysInfo->aucSectorId),
                  pstOverHeadMsgInd->aucSectorId,
                  CNAS_HSM_SUBNET_ID_MAX_LENGTH);

    NAS_MEM_CPY_S(pstHprdSysInfo->aucSecondaryColorCode,
                  sizeof(pstHprdSysInfo->aucSecondaryColorCode),
                  pstOverHeadMsgInd->aucSecondaryColorCode,
                  CNAS_HSM_SECOND_COLORCODE_MAX_LENGTH);

}



HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8 CNAS_HSM_ConvertConnOpenRsltFromCasToHsm(
    CAS_CNAS_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                 enConnOpenIndRslt
)
{
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enConnOpenIndRsltConvert;

    enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_BUTT;

    switch(enConnOpenIndRslt)
    {
        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_SUCC:
            enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_SUCC;
            break;

        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_FAIL:
            enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_FAIL;
            break;

        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_PERSIST_FAIL:
            enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_PERSIST_FAIL;
            break;

        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_MAX_PROBE:
            enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_MAX_PROBE;
            break;

        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_AUTH_BILLING_FAIL:
            enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_AUTH_BILLING_FAIL;
            break;

        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_GENERAL:
        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_BS_BUSY:
            enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_BS_BUSY_OR_GENERAL;
            break;

        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_PREFER_CH_NOT_VALID:
            enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_PREFER_CH_NOT_VALID;
            break;

        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_TCA_RTC_ACK_TIMEOUT:
            enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_TCA_RTC_ACK_TIMEOUT;
            break;

        case CAS_CNAS_HRPD_CONN_OPEN_RSLT_NO_RF:
            enConnOpenIndRsltConvert = HSM_HSD_HRPD_CONN_OPEN_RSLT_NO_RF;
            break;

        default:
            break;
    }

    return enConnOpenIndRsltConvert;
}

/*****************************************************************************
 函 数 名  : CNAS_HSM_UpdateHrpdAtiInfo
 功能描述  : UATI RATI session status发生变化的时候上报给mma
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月4日
    作    者   : y00322978
    修改内容   : 新生成函数

  2.日    期   : 2015年08月20日
    作    者   : t00323010
    修改内容   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_HSM_UpdateHrpdAtiInfo(VOS_VOID)
{
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enCurrSessionStatus;

    enCurrSessionStatus = CNAS_HSM_GetSessionStatus();

    if (CNAS_HSM_SESSION_STATUS_BUTT == enCurrSessionStatus)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_UpdateHrpdAtiInfo: Curr SessionStatus is BUTT!");
    }

    CNAS_HSM_SndMmaHrpdInfo(CNAS_HSM_GetSessionSeed(),
                            CNAS_HSM_GetUatiInfoAddr()->aucCurUATI,
                            enCurrSessionStatus);

}

/*****************************************************************************
Function Name   :   CNAS_HSM_ConvertHrpdNetworkLostRsltToHsmApsErrCode
Description     :   将cas的掉网原因值转换为hsm与aps之间的错误码
Input parameters:   CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16     enNetworkLostReason
Outout parameters:  None
Return Value    :   HSM_APS_CAUSE_ENUM_UINT32

Modify History  :
1)  Date           : 2015-11-25
    Author         : y00307564
    Modify content : Create

*****************************************************************************/
HSM_APS_CAUSE_ENUM_UINT32 CNAS_HSM_ConvertHrpdNetworkLostRsltToHsmApsErrCode(
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
)
{
    HSM_APS_CAUSE_ENUM_UINT32           enHsmApsCause;

    enHsmApsCause = HSM_APS_CAUSE_BUTT;

    switch(enNetworkLostReason)
    {
        case CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT:
            enHsmApsCause = HSM_APS_CAUSE_REDIRECT;
            break;

        case CAS_CNAS_HRPD_NETWORK_LOST_NO_RF:
            enHsmApsCause = HSM_APS_CAUSE_NO_RF;
            break;

        default:
            enHsmApsCause = HSM_APS_CAUSE_SIGNAL_FADE;
            break;
    }

    return enHsmApsCause;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_ConvertHrpdNetworkLostRsltToHsmEhsmErrCode
Description     :   将cas的掉网原因值转换为hsm与ehsm之间的错误码
Input parameters:   CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16     enNetworkLostReason
Outout parameters:  None
Return Value    :   EHSM_HSM_RSLT_ENUM_UINT32

Modify History  :
1)  Date           : 2015-11-25
    Author         : y00307564
    Modify content : Create

*****************************************************************************/
EHSM_HSM_RSLT_ENUM_UINT32 CNAS_HSM_ConvertHrpdNetworkLostRsltToHsmEhsmErrCode(
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
)
{
    EHSM_HSM_RSLT_ENUM_UINT32           enHsmEhsmRslt;

    enHsmEhsmRslt = EHSM_HSM_RSLT_BUTT;

    switch(enNetworkLostReason)
    {
        case CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT:
            enHsmEhsmRslt = EHSM_HSM_RSLT_REDIRECT;
            break;

        case CAS_CNAS_HRPD_NETWORK_LOST_NO_RF:
            enHsmEhsmRslt = EHSM_HSM_RSLT_NO_RF;
            break;

        default:
            enHsmEhsmRslt = EHSM_HSM_RSLT_SIGNAL_FADE;
            break;
    }

    return enHsmEhsmRslt;
}



VOS_VOID CNAS_HSM_VoteEnterSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_ENUM_UINT8 enSlotVoteType)
{
    VOS_UINT8       ucOldSlotVoteBox;
    VOS_UINT8       ucNewSlotVoteBox;

    ucOldSlotVoteBox  =   CNAS_HSM_GetSlotVoteBox();

    ucNewSlotVoteBox  = (ucOldSlotVoteBox & (~enSlotVoteType));

    if ((0 != ucOldSlotVoteBox) && (0 == ucNewSlotVoteBox))
    {
        CNAS_HSM_SndCasHrpdSlotVoteNtf(CNAS_CAS_HRPD_SLOT_VOTE_ENABLE_SLOT);
    }

    CNAS_HSM_SetSlotVoteBox(ucNewSlotVoteBox);
}



VOS_VOID CNAS_HSM_VoteExitSlottedMode(CNAS_HSM_SLOT_VOTE_TYPE_ENUM_UINT8 enSlotVoteType)
{
    VOS_UINT8       ucOldSlotVoteBox;
    VOS_UINT8       ucNewSlotVoteBox;

    ucOldSlotVoteBox  =   CNAS_HSM_GetSlotVoteBox();

    ucNewSlotVoteBox  = (ucOldSlotVoteBox | enSlotVoteType);

    if ((0 == ucOldSlotVoteBox) && (0 != ucNewSlotVoteBox))
    {
        CNAS_HSM_SndCasHrpdSlotVoteNtf(CNAS_CAS_HRPD_SLOT_VOTE_DSIABLE_SLOT);
    }

    CNAS_HSM_SetSlotVoteBox(ucNewSlotVoteBox);
}




VOS_VOID CNAS_HSM_ProcWaitUaitAssignTimerLen(
    VOS_UINT8     ucInWaitUaitAssigntimerLen,
    VOS_UINT8    *pucOutInWaitUaitAssigntimerLen)
{
    VOS_UINT8     ucWaitUaitAssigntimerLen;

    /* 等待UATI assignment 的最大时长为120s，最短时长为5s */
    if (ucInWaitUaitAssigntimerLen < CNAS_HSM_MIN_WAIT_UATI_ASSIGN_TIMER_LEN)
    {
        ucWaitUaitAssigntimerLen = CNAS_HSM_MIN_WAIT_UATI_ASSIGN_TIMER_LEN;
    }
    else if(ucInWaitUaitAssigntimerLen > CNAS_HSM_MAX_WAIT_UATI_ASSIGN_TIMER_LEN)
    {
        ucWaitUaitAssigntimerLen = CNAS_HSM_MAX_WAIT_UATI_ASSIGN_TIMER_LEN;
    }
    else
    {
        ucWaitUaitAssigntimerLen = ucInWaitUaitAssigntimerLen;
    }

    *pucOutInWaitUaitAssigntimerLen = ucWaitUaitAssigntimerLen;

}


VOS_UINT8  CNAS_HSM_IsUERevInfoChanged(VOS_VOID)
{
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                        *pstHrpdUERevInfo;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                        *pstLastHrpdUERevInfo;

    pstHrpdUERevInfo     = CNAS_HSM_GetHrpdUERevInfoCtxAddr();
    pstLastHrpdUERevInfo = CNAS_HSM_GetLastHrpdUERevInfoCtxAddr();

    /***********************************************************************************
     判断准则:
     REV0 -> REVA: 重新发起初始协商
     REVA -> REV0: 重新发起初始协商
     REVA -> REVA: enSuppDoaWithMfpa\enSuppDoaWithEmfpa\enSuppDoaEhrpd这三个参数只要发生变化就无条件发起初始协商
     REV0 -> REV0: enSuppDoaWithMfpa\enSuppDoaWithEmfpa\enSuppDoaEhrpd三个参数本身就是忽略的，所以即便有变化也不发起初始协商
    *************************************************************************************/
    if ((PS_TRUE == pstLastHrpdUERevInfo->enSuppOnlyDo0)
     && (PS_TRUE == pstHrpdUERevInfo->enSuppOnlyDo0))
    {
        /* REV0 -> REV0 */
        return VOS_FALSE;
    }

    if ((PS_TRUE == pstLastHrpdUERevInfo->enSuppOnlyDo0)
     && (PS_FALSE == pstHrpdUERevInfo->enSuppOnlyDo0))
    {
        /* REV0 -> REVA */
        return VOS_TRUE;
    }

    if ((PS_FALSE == pstLastHrpdUERevInfo->enSuppOnlyDo0)
     && (PS_TRUE  == pstHrpdUERevInfo->enSuppOnlyDo0))
    {
        /* REVA -> REV0 */
        return VOS_TRUE;
    }

    if ((PS_FALSE  == pstLastHrpdUERevInfo->enSuppOnlyDo0)
     && (PS_FALSE  == pstHrpdUERevInfo->enSuppOnlyDo0))
    {
        /* REVA -> REVA */
        if ((pstLastHrpdUERevInfo->enSuppDoaWithMfpa  !=  pstHrpdUERevInfo->enSuppDoaWithMfpa)
         || (pstLastHrpdUERevInfo->enSuppDoaWithEmfpa !=  pstHrpdUERevInfo->enSuppDoaWithEmfpa)
         || (pstLastHrpdUERevInfo->enSuppDoaEhrpd     !=  pstHrpdUERevInfo->enSuppDoaEhrpd))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



HSM_APS_CAUSE_ENUM_UINT32 CNAS_HSM_ConvertCasCloseReasonToHsmCause(
    CAS_CNAS_HRPD_CONN_CLOSE_REASON_ENUM_UINT16             enConnCloseReason
)
{
    switch (enConnCloseReason)
    {
        case CAS_CNAS_HRPD_CONN_CLOSE_REASON_TO_1X:

            return HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X;

        default:
            return HSM_APS_CAUSE_BUTT;
    }
}

/*****************************************************************************
Function Name   :   CNAS_HSM_IsSubnetEqual
Description     :   判断两个子网是否相同
Input parameters:   pucDestSubnet 子网1
                    pucSrcSubnet  子网2
Outout parameters:  none
Return Value    :   VOS_FALSE:两个子网不同。VOS_TRUE:两个子网相同

Modify History  :
1)  Date           : 2016-01-08
    Author         : m00312079
    Modify content : Create
*****************************************************************************/

VOS_UINT8 CNAS_HSM_IsSubnetEqual(
    VOS_UINT8                          *pucDestSubnet,
    VOS_UINT8                          *pucSrcSubnet
)
{
    VOS_UINT32       ulLoop;

    for (ulLoop = 0; ulLoop < CNAS_HSM_SUBNET_ID_MAX_LENGTH; ulLoop++)
    {
        if (pucDestSubnet[ulLoop] != pucSrcSubnet[ulLoop])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}
/*****************************************************************************
Function Name   :   CNAS_HSM_GetSubnet
Description     :   获取子网。
Input parameters:   pucInSectorId  sectorId
                    ucSubetMask   子网掩码
Outout parameters:  pucOutSubnet  子网
Return Value    :   VOS_VOID

Modify History  :
1)  Date           : 2016-01-08
    Author         : m00312079
    Modify content : Create
*****************************************************************************/

VOS_VOID CNAS_HSM_GetSubnet(
    VOS_UINT8                          *pucOutSubnet,
    VOS_UINT8                          *pucInSectorId,
    VOS_UINT8                           ucSubetMask
)
{
    VOS_UINT8                           ucQuotient;
    VOS_UINT8                           ucRemainder;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLeftMask;

    if (0 == ucSubetMask)
    {
        return;
    }

    ucQuotient  = ucSubetMask / CNAS_HSM_BIT_LEN_PER_BYTE;
    ucRemainder = ucSubetMask % CNAS_HSM_BIT_LEN_PER_BYTE;

    for (ucLoop = 0; ucLoop < ucQuotient; ucLoop++)
    {
        pucOutSubnet[ucLoop] = pucInSectorId[ucLoop];
    }

    if (0 == ucRemainder)
    {
        return;
    }

    ucLeftMask = (VOS_UINT8)(((VOS_UINT32)1) << ucRemainder);
    ucLeftMask -= 1;
    ucLeftMask = (VOS_UINT8)(((VOS_UINT32)ucLeftMask) << (CNAS_HSM_BIT_LEN_PER_BYTE - ucRemainder));

    pucOutSubnet[ucLoop] = pucInSectorId[ucLoop] & ucLeftMask;

    return;
}


VOS_UINT8 CNAS_HSM_IsHardWareIdResSnpDataCnf(
    VOS_UINT16                                              usOpId
)
{
    VOS_UINT8       ucRslt;
    VOS_UINT16      usHardWareIdResOpId;

    ucRslt              = VOS_FALSE;
    usHardWareIdResOpId = CNAS_HSM_GetHardWareIdRspSnpDataReqOpId();

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_HARDWARE_ID_RSP_WAIT_SNP_DATA_CNF, 0))
    {
        if (usHardWareIdResOpId ==  usOpId)
        {
            ucRslt = VOS_TRUE;
        }
    }

    return ucRslt;
}


VOS_UINT8 CNAS_HSM_IsKeepAliveReqSnpDataCnf(
    VOS_UINT16                                              usOpId
)
{
    VOS_UINT8       ucRslt;
    VOS_UINT16      usKeepAliveReqOpId;

    ucRslt              = VOS_FALSE;
    usKeepAliveReqOpId  = CNAS_HSM_GetKeepAliveReqSnpDataReqOpId();

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_MO_KEEP_ALIVE_WAIT_SNP_DATA_CNF, 0))
    {
        if (usKeepAliveReqOpId == usOpId)
        {
            ucRslt = VOS_TRUE;
        }
    }

    return ucRslt;
}


VOS_UINT8 CNAS_HSM_IsKeepAliveResSnpDataCnf(
    VOS_UINT16                                              usOpId
)
{
    VOS_UINT8       ucRslt;
    VOS_UINT16      usKeepAliveRespOpId;

    ucRslt              = VOS_FALSE;
    usKeepAliveRespOpId = CNAS_HSM_GetKeepAliveRspSnpDataReqOpId();

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_MT_KEEP_ALIVE_WAIT_SNP_DATA_CNF, 0))
    {
        if (usKeepAliveRespOpId == usOpId)
        {
            ucRslt = VOS_TRUE;
        }
    }

    return ucRslt;
}


VOS_UINT8 CNAS_HSM_IsUatiCmplSnpDataCnf(
    VOS_UINT16                                              usOpId
)
{
    VOS_UINT8       ucRslt;
    VOS_UINT16      usUatiCmplOpId;

    ucRslt              = VOS_FALSE;
    usUatiCmplOpId      = CNAS_HSM_GetUatiCmplSnpDataReqOpId();

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, 0))
    {
        if (usUatiCmplOpId == usOpId)
        {
            ucRslt = VOS_TRUE;
        }
    }

    return ucRslt;
}

#ifdef DMT


VOS_VOID CAS_HRPD_HSCP_GetDefaultAmpAttr(
    CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU                       *pstDeAmp
)
{
    NAS_MEM_CPY_S(pstDeAmp, sizeof(CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU), &g_stAmpNegAttribs, sizeof(CAS_HRPD_DEFAULT_AMP_ATTRIB_STRU));

    return;
}




VOS_VOID CAS_HRPD_HSCP_GetDefaultSmpAttr(
    CAS_HRPD_DEFAULT_SMP_ATTRIB_STRU                       *pstDeSmp
)
{
    NAS_MEM_CPY_S(pstDeSmp, sizeof(CAS_HRPD_DEFAULT_SMP_ATTRIB_STRU), &g_stSmpNegAttribs, sizeof(CAS_HRPD_DEFAULT_SMP_ATTRIB_STRU));

    return;
}




VOS_VOID CTTF_HRPD_FSPS_RegTrafficFlowMonitor(CTTF_HRPD_FSPS_TRAFFIC_FLOW_MONITOR_CB pfTrafficFlowMonitor)
{
    return;
}




VOS_VOID CTTF_HRPD_FSPS_DeregTrafficFlowMonitor(VOS_VOID)
{
    return;
}



#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




