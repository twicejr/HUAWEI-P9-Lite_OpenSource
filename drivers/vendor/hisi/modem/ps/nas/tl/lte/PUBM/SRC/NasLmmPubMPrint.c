/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLmmPubMPrint.c
  Description     : 状态机、消息和定时器相关的打印函数
  History         :
     1.lining 00141619       2008-10-24   Draft Enact
     2.hanlufeng 41410 2008-05-07 BJ9D00610 初始化修改后，修订几个定时器
                                            的打印
     3.zhengjunyan 00148421   2011-05-28 文件名由 NasMmPubMPrint.c修改为
                                           NasLmmPubMPrint.c
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasLmmPubMPrint.h"
#include  "NasLmmPubMOsa.h"
#include  "NasLmmPubMEntry.h"
#include  "MmcLmmInterface.h"
#include  "GmmLmmInterface.h"
#include  "LmmSmsInterface.h"
#include  "LPsOm.h"

#include  "omerrorlog.h"

#if (FEATURE_LPP == FEATURE_ON)
#include "EmmLppInterface.h"
#include "LmmLcsInterface.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMPRINT_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMPRINT_C
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


/*****************************************************************************
  2.1 状态机状态打印数组
*****************************************************************************/
/* 并行状态机打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmParallelFsmArray[] =
{
    {   NAS_LMM_PARALLEL_FSM_EMM,
            "NAS_LMM_EMM \t"              },
   /* {   NAS_LMM_PARALLEL_FSM_MMC,
            "NAS_LMM_MMC \t"              },*/
    {   NAS_LMM_PARALLEL_FSM_SECU,
            "NAS_LMM_SECU\t"             }
};

/* 主状态打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmMainStateArray[] =
{
    /*=================== EMM的主状态 =====================*/
    {   EMM_MS_NULL                     ,
            "MS:  EMM_MS_NULL         "    },
    {   EMM_MS_DEREG                    ,
            "MS:  EMM_MS_DEREG        "    },
    {   EMM_MS_REG_INIT                 ,
            "MS:  EMM_MS_REG_INIT     "    },
    {   EMM_MS_REG                      ,
            "MS:  EMM_MS_REG          "    },
    {   EMM_MS_TAU_INIT                 ,
            "MS:  EMM_MS_TAU_INIT     "    },
    {   EMM_MS_SER_INIT                 ,
            "MS:  EMM_MS_SER_INIT     "    },
    {   EMM_MS_DEREG_INIT               ,
            "MS:  EMM_MS_DEREG_INIT   "    },
    {   EMM_MS_AUTH_INIT                ,
            "MS:  EMM_MS_AUTH_INIT    "    },
    {   EMM_MS_SUSPEND                ,
            "MS:  EMM_MS_SUSPEND      "    },
    {   EMM_MS_RESUME                ,
            "MS:  EMM_MS_RESUME       "    },


    /*=================== MMC的主状态 =====================*/
    {   MMC_MS_NULL                     ,
            "MS:  MMC_MS_NULL         "    },
    {   MMC_MS_TRYING_PLMN             ,
            "MS:  MMC_MS_TRYING_PLMN  "    },
    {   MMC_MS_TRYING_PLMN_LIST              ,
            "MS:  MMC_MS_TRYING_PLMN_LIST "    },
    {   MMC_MS_ON_PLMN                  ,
            "MS:  MMC_MS_ON_PLMN      "    },
    {   MMC_MS_NOT_ON_PLMN              ,
            "MS:  MMC_MS_NOT_ON_PLMN  "    },
    {   MMC_MS_WAIT_FOR_PLMN            ,
            "MS:  MMC_MS_WAIT_FOR_PLMN "    },
    {   MMC_MS_NO_IMSI                  ,
            "MS:  MMC_MS_NO_IMSI      "    },


    /*=================== SECU 的 CUR 状态 =====================*/
    {   EMM_CUR_SECU_NOT_EXIST,
            "CS:  EMM_CUR_SECU_NOT_EXIST"    },

    {   EMM_CUR_SECU_EXIST_NOT_ACTIVE,
            "CS:  EMM_CUR_SECU_EXIST_NOT_ACTIVE"    },

    {   EMM_CUR_SECU_EXIST_ACTIVE,
            "CS:  EMM_CUR_SECU_EXIST_ACTIVE    "    }


};

/* 子状态打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmSubStateArray[] =
{
    /*=================== EMM的子状态 =====================*/
    /*========== NULL下的子状态 ===============*/
    {   EMM_SS_NULL_WAIT_APP_START_REQ  ,
            "SS:  EMM_SS_NULL_WAIT_APP_START_REQ     "    },
    {   EMM_SS_NULL_WAIT_READING_USIM  ,
            "SS:  EMM_SS_NULL_WAIT_READING_USIM     "    },
/*    {   EMM_SS_NULL_WAITING_USIM_READY  ,
            "SS:  EMM_SS_NULL_WAITING_USIM_READY     "    },*/
    {   EMM_SS_NULL_WAIT_MMC_START_CNF  ,
            "SS:  EMM_SS_NULL_WAIT_MMC_START_CNF     "    },
    {   EMM_SS_NULL_WAIT_RRC_START_CNF  ,
            "SS:  EMM_SS_NULL_WAIT_RRC_START_CNF     "    },
    {   EMM_SS_NULL_WAIT_SWITCH_OFF     ,
            "SS:  EMM_SS_NULL_WAIT_SWITCH_OFF        "    },
    {   EMM_SS_NULL_WAIT_MMC_STOP_CNF   ,
            "SS:  EMM_SS_NULL_WAIT_MMC_STOP_CNF      "    },
    {   EMM_SS_NULL_WAIT_RRC_STOP_CNF   ,
            "SS:  EMM_SS_NULL_WAIT_RRC_STOP_CNF      "    },

    /*========== DEREG下的子状态 ==============*/
    {   EMM_SS_DEREG_NORMAL_SERVICE     ,
            "SS:  EMM_SS_DEREG_NORMAL_SERVICE        "    },
    {   EMM_SS_DEREG_LIMITED_SERVICE    ,
            "SS:  EMM_SS_DEREG_LIMITED_SERVICE       "    },
    {   EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,
            "SS:  EMM_SS_DEREG_ATTEMPTING_TO_ATTACH  "    },
    {   EMM_SS_DEREG_PLMN_SEARCH        ,
            "SS:  EMM_SS_DEREG_PLMN_SEARCH           "    },
    {   EMM_SS_DEREG_NO_IMSI            ,
            "SS:  EMM_SS_DEREG_NO_IMSI               "    },
    {   EMM_SS_DEREG_ATTACH_NEEDED      ,
            "SS:  EMM_SS_DEREG_ATTACH_NEEDED         "    },
    {   EMM_SS_DEREG_NO_CELL_AVAILABLE  ,
            "SS:  EMM_SS_DEREG_NO_CELL_AVAILABLE     "    },


    /*========== ATTACH_INIT的子状态 ==========*/
    {   EMM_SS_ATTACH_WAIT_ESM_PDN_RSP   ,
            "SS:  EMM_SS_ATTACH_WAIT_ESM_PDN_RSP     "    },
    {   EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF,
            "SS:  EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF   "    },
    {   EMM_SS_ATTACH_WAIT_MRRC_REL_CNF ,
            "SS:  EMM_SS_ATTACH_WAIT_MRRC_REL_CNF    "    },
    {   EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF,
            "SS:  EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF  "    },
    {   EMM_SS_ATTACH_WAIT_RRC_DATA_CNF,
            "SS:  EMM_SS_ATTACH_WAIT_RRC_DATA_CNF    "    },

    /*========== REG下的子状态 ================*/
    {   EMM_SS_REG_NORMAL_SERVICE       ,
            "SS:  EMM_SS_REG_NORMAL_SERVICE          "    },
    {   EMM_SS_REG_ATTEMPTING_TO_UPDATE ,
            "SS:  EMM_SS_REG_ATTEMPTING_TO_UPDATE    "    },
    {   EMM_SS_REG_LIMITED_SERVICE      ,
            "SS:  EMM_SS_REG_LIMITED_SERVICE         "    },
    {   EMM_SS_REG_PLMN_SEARCH          ,
            "SS:  EMM_SS_REG_PLMN_SEARCH             "    },
    {   EMM_SS_REG_WAIT_ACCESS_GRANT_IND,
            "SS:  EMM_SS_REG_WAIT_ACCESS_GRANT_IND           "    },
    {   EMM_SS_REG_NO_CELL_AVAILABLE    ,
            "SS:  EMM_SS_REG_NO_CELL_AVAILABLE       "    },

    {   EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM    ,
            "SS:  EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM "    },
    {   EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF    ,
            "SS:  EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF "    },


    /*========== TAU_INIT的子状态  ============*/
    {   EMM_SS_TAU_WAIT_CN_TAU_CNF      ,
            "SS:  EMM_SS_TAU_WAIT_CN_TAU_CNF         "    },

    /*========== SER_INIT的子状态 =============*/
    {   EMM_SS_SER_WAIT_CN_SER_CNF      ,
            "SS:  EMM_SS_SER_WAIT_CN_SER_CNF         "    },


    /*========== DETACH_INIT的子状态 ==========*/
    {   EMM_SS_DETACH_WAIT_CN_DETACH_CNF,
            "SS:  EMM_SS_DETACH_WAIT_CN_DETACH_CNF   "    },
    {   EMM_SS_DETACH_WAIT_MRRC_REL_CNF ,
            "SS:  EMM_SS_DETACH_WAIT_MRRC_REL_CNF    "    },



    /*========== EMM_MS_RRC_CONN_INIT的子状态 =*/
    {   EMM_SS_RRC_CONN_WAIT_EST_CNF    ,
            "SS:  EMM_SS_RRC_CONN_WAIT_EST_CNF       "    },
    {   EMM_SS_RRC_CONN_WAIT_REL_CNF    ,
            "SS:  EMM_SS_RRC_CONN_WAIT_REL_CNF       "    },

    /*========== AUTH过程中的子状态 ===========*/
    {   EMM_SS_AUTH_WAIT_CN_AUTH,
            "SS:  EMM_SS_AUTH_WAIT_CN_AUTH           "    },



    /*========== 异系统过程中的子状态 ===========*/
    {   EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND,
            "SS:  EMM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND "    },

    {   EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND,
            "SS:  EMM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND "    },

    {   EMM_SS_SUSPEND_WAIT_END,
            "SS:  EMM_SS_SUSPEND_WAIT_END            "    },
    {   EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,
            "SS:  EMM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND "    },

    {   EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
            "SS:  EMM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND "    },

    {   EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME,
            "SS:  EMM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME "    },

    {   EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND,
            "SS:  EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND    "    },

    {   EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,
            "SS:  EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND    "    },

    /*========== GUTI     过程暂无子状态  =====*/
    /*========== IDEN     过程暂无子状态  =====*/
    /*========== SECURITY 过程暂无子状态  =====*/


    /*=================== SECU的NEW状态 ===================*/
    {   EMM_NEW_SECU_NOT_EXIST          ,
            "NS:  EMM_NEW_SECU_NOT_EXIST             "    },
    {   EMM_NEW_SECU_EXIST          ,
            "NS:  EMM_NEW_SECU_EXIST                 "    }

};


/*****************************************************************************
  2.2 辅助状态机打印数组
*****************************************************************************/
/* EMM更新状态打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmEmmUpStateArray[] =
{
    {   EMM_US_UPDATED_EU1              ,
            "EmmUpState:  EMM_US_UPDATED_EU1                       "    },
    {   EMM_US_NOT_UPDATED_EU2          ,
            "EmmUpState:  EMM_US_NOT_UPDATED_EU2                   "    },
    {   EMM_US_ROAMING_NOT_ALLOWED_EU3  ,
            "EmmUpState:  EMM_US_ROAMING_NOT_ALLOWED_EU3           "    }
};

/* RRC连接状态打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmRrcConnStateArray[] =
{
    {   NAS_EMM_CONN_IDLE          ,
            "RrcConnState:  NAS_EMM_CONN_IDLE                 "    },
    {   NAS_EMM_CONN_SIG             ,
            "RrcConnState:  NAS_EMM_CONN_SIG                  "    },
    {   NAS_EMM_CONN_ESTING              ,
            "RrcConnState:  NAS_EMM_CONN_ESTING               "    },
    {   NAS_EMM_CONN_DATA,
            "RrcConnState:  NAS_EMM_CONN_DATA                 "    },
    {   NAS_EMM_CONN_RELEASING,
            "RrcConnState:  NAS_EMM_CONN_RELEASING            "    }

};

/* SIM卡状态打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmUsimStateArray[] =
{
    {   EMM_USIM_STATE_VALID            ,
            "UsimState:  EMM_USIM_STATE_VALID                      "},
    {   EMM_USIM_STATE_INVALID          ,
            "UsimState:  EMM_USIM_STATE_INVALID                    "}
};


/*****************************************************************************
  2.3 定时器打印数组
*****************************************************************************/
/* 状态定时器打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmStateTimerArray[] =
{
    /*=================== EMM的状态定时器 ===================*/
    /*========== 保留状态定时器 =================*/
    {   TI_NAS_EMM_STATE_NO_TIMER                 ,
            "STATE TI:  TI_NAS_EMM_STATE_NO_TIMER               "},
    {   TI_NAS_EMM_STATE_T3440                    ,
            "STATE TI:  TI_NAS_EMM_STATE_T3440                  "},
    {   TI_NAS_EMM_STATE_DEL_FORB_TA_PROID        ,
            "STATE TI:  TI_NAS_EMM_STATE_DEL_FORB_TA_PROID      "},

    /*========== PUB模块状态定时器 =================*/
    /*========== PUB模块定时器 ===================*/
    {   TI_NAS_LMM_TIMER_WAIT_USIM_CNF             ,
            "STATE TI:  TI_NAS_LMM_TIMER_WAIT_USIM_CNF           "},
    {   TI_NAS_LMM_TIMER_WAIT_USIM_READY_START     ,
                "STATE TI:  TI_NAS_LMM_TIMER_WAIT_USIM_READY_START"},
    /*========== MRRC 模块状态定时器 ============*/
    {   TI_NAS_EMM_STATE_MRRC_BOUNDARY_START      ,
            "STATE TI:  TI_NAS_EMM_STATE_MRRC_BOUNDARY_START    "},
    {   TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF         ,
            "STATE TI:  TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF       "},
    {   TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF          ,
            "STATE TI:  TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF        "},
    /*========== ATTACH 模块状态定时器 ==========*/
    {   TI_NAS_EMM_STATE_REG_BOUNDARY_START       ,
            "STATE TI:  TI_NAS_EMM_STATE_REG_BOUNDARY_START     "},
    {   TI_NAS_EMM_T3410                          ,
            "STATE TI:  TI_NAS_EMM_T3410                        "},
    {   TI_NAS_EMM_WAIT_ESM_PDN_RSP                ,
            "STATE TI:  TI_NAS_EMM_WAIT_ESM_PDN_RSP             "},
    {   TI_NAS_EMM_WAIT_ESM_BEARER_CNF             ,
            "STATE TI:  TI_NAS_EMM_WAIT_ESM_BEARER_CNF          "},
    {   TI_NAS_EMM_WAIT_RRC_DATA_CNF             ,
                "STATE TI:  TI_NAS_EMM_WAIT_RRC_DATA_CNF    "},
    /*========== DETACH 模块状态定时器 ==========*/
    {   TI_NAS_EMM_STATE_DEREG_BOUNDARY_START     ,
            "STATE TI:  TI_NAS_EMM_STATE_DEREG_BOUNDARY_START   "},
    {   TI_NAS_EMM_T3421     ,
            "STATE TI:  TI_NAS_EMM_T3421                        "},

    /*========== TAU 模块状态定时器 =============*/
    {   TI_NAS_EMM_STATE_TAU_BOUNDARY_START       ,
            "STATE TI:  TI_NAS_EMM_STATE_TAU_BOUNDARY_START     "},
    {   TI_NAS_EMM_STATE_TAU_T3430                ,
            "STATE TI:  TI_NAS_EMM_STATE_TAU_T3430              "},
    /*========== SERVICE 模块状态定时器 =========*/
    {   TI_NAS_EMM_STATE_SERVICE_BOUNDARY_START   ,
            "STATE TI:  TI_NAS_EMM_STATE_SERVICE_BOUNDARY_START "},
    {   TI_NAS_EMM_STATE_SERVICE_T3417            ,
            "STATE TI:  TI_NAS_EMM_STATE_SERVICE_T3417          "},

    {   TI_NAS_EMM_STATE_SERVICE_T3417_EXT            ,
            "STATE TI:  TI_NAS_EMM_STATE_SERVICE_T3417_EXT       "},
    {   TI_NAS_EMM_STATE_SERVICE_T3442            ,
            "STATE TI:  TI_NAS_EMM_STATE_SERVICE_T3442           "},
    /*========== PLMN 模块状态定时器 ============*/
    {   TI_NAS_EMM_STATE_PLMN_BOUNDARY_START      ,
            "STATE TI:  TI_NAS_EMM_STATE_PLMN_BOUNDARY_START    "},
    {   TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER       ,
            "STATE TI:  TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER     "},
    {   TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER       ,
            "STATE TI:  TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER     "},
    {   TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER        ,
            "STATE TI:  TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER      "},
    {   TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER        ,
            "STATE TI:  TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER      "},

    /*========== SECU 模块定时器 ==============*/
    {   TI_NAS_EMM_STATE_AUTH_BOUNDARY_START      ,
            "STATE TI:  TI_NAS_EMM_STATE_AUTH_BOUNDARY_START    "},
    {   TI_NAS_EMM_T3418      ,
            "STATE TI:  TI_NAS_EMM_T3418                        "},
    {   TI_NAS_EMM_T3420      ,
            "STATE TI:  TI_NAS_EMM_T3420                        "},


    /*========== 系统变换定时器 ==============*/
    {   TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER      ,
            "STATE TI:  TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER "},
    {   TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER,
        "STATE TI:  TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER "},
    {   TI_NAS_EMM_WAIT_SUSPEND_END_TIMER      ,
            "STATE TI:  TI_NAS_EMM_WAIT_SUSPEND_END_TIMER    "},
    {   TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER      ,
            "STATE TI:  TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER "},
    {   TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER      ,
            "STATE TI:  TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER  "},
    {   TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER      ,
            "STATE TI:  TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER    "},
    {   TI_NAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER      ,
            "STATE TI:  TI_NAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER    "},
    {   TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER      ,
            "STATE TI:  TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER    "},


    /*==========  ==============*/
    {   NAS_LMM_STATE_TI_BUTT,
            "STATE TI:  TI_NO_STATE_TIMER                       "}
};

/* 协议定时器打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmPtlTimerArray[] =
{
    /*=================== EMM的协议定时器 ===================*/

    /*========== 公共定时器 =====================*/
    {   TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START       ,
            "PTL TI:  TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START       "},


    /*========== ATTACH 模块定时器 ==============*/

    /*========== DETACH 模块定时器 ==============*/

    /*========== TAU 模块定时器 =================*/
    {   TI_NAS_EMM_PTL_T3412                      ,
            "PTL TI:  TI_NAS_EMM_PTL_T3412                      "},
    {   TI_NAS_EMM_PTL_T3423                      ,
            "PTL TI:  TI_NAS_EMM_PTL_T3423                      "},
    {   TI_NAS_EMM_PTL_T3402                      ,
            "PTL TI:  TI_NAS_EMM_PTL_T3402                      "},

    /*========== AUTH 模块定时器 =================*/
    {   TI_NAS_EMM_PTL_T3416                      ,
            "PTL TI:  TI_NAS_EMM_PTL_T3416                      "},

    /*========== 关机定时器 ====================*/
    {   TI_NAS_EMM_PTL_SWITCH_OFF_TIMER          ,
            "PTL TI: TI_NAS_EMM_PTL_SWITCH_OFF_TIMER            "},


    /*=================== MMC的协议定时器 ===================*/

    {   TI_NAS_EMM_PTL_T3411                ,
            "STATE TI:  TI_NAS_EMM_PTL_T3411                   "},
    {   TI_NAS_EMM_PTL_T3346                ,
            "STATE TI:  TI_NAS_EMM_PTL_T3346                   "}
};


/*****************************************************************************
  2.4 消息打印数组
*****************************************************************************/
/* MM内部消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmIntraMsgIdArray[] =
{
    /*=================== MMC 的假消息 ===============================*/
    {   ID_NAS_LMM_INTRA_EMMC_EMM_START_REQ                   ,
            "MSG:  ID_NAS_LMM_INTRA_EMMC_EMM_START_REQ               "},
    {   ID_NAS_LMM_INTRA_EMMC_EMM_START_CNF                   ,
            "MSG:  ID_NAS_LMM_INTRA_EMMC_EMM_START_CNF               "},
    {   ID_NAS_LMM_INTRA_EMMC_EMM_STOP_REQ                    ,
            "MSG:  ID_NAS_LMM_INTRA_EMMC_EMM_STOP_REQ                "},
    {   ID_NAS_LMM_INTRA_EMMC_EMM_STOP_CNF                    ,
            "MSG:  ID_NAS_LMM_INTRA_EMMC_EMM_STOP_CNF                "},
    {   ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND                    ,
            "MSG:  ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND                "},
    {   ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND                ,
            "MSG:  ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND            "},
    {   ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND           ,
            "MSG:  ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND       "},
    /*{   ID_NAS_LMM_INTRA_EMMC_EMM_ACTION_RESULT_REQ           ,
            "MSG:  ID_NAS_LMM_INTRA_EMMC_EMM_ACTION_RESULT_REQ       "},*/
    {   ID_NAS_LMM_INTRA_EMMC_EMM_USIM_STATUS_IND             ,
            "MSG:  ID_NAS_LMM_INTRA_EMMC_EMM_USIM_STATUS_IND         "},
    {   ID_NAS_LMM_INTRA_EIA0_ACT_NOTIFY             ,
            "MSG:  ID_NAS_LMM_INTRA_EIA0_ACT_NOTIFY                  "},

    /*=================== MRRC的内部消息 =============================*/
    {   ID_NAS_LMM_INTRA_MRRC_DATA_REQ                       ,
            "MSG:  ID_NAS_LMM_INTRA_MRRC_DATA_REQ                   "},
    {   ID_NAS_LMM_INTRA_MRRC_REL_REQ                        ,
            "MSG:  ID_NAS_LMM_INTRA_MRRC_REL_REQ                    "},
    {   ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND                        ,
            "MSG:  ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND           "},


    /*=================== REG的内部消息 ==============================*/
    {   ID_NAS_LMM_INTRA_ATTACH_REQ                          ,
            "MSG:  ID_NAS_LMM_INTRA_ATTACH_REQ                      "},
    /*=================== DEREG的内部消息 ============================*/
    {   ID_NAS_LMM_INTRA_DETACH_REQ                          ,
            "MSG:  ID_NAS_LMM_INTRA_DETACH_REQ                      "},

    /*=================== TAU内部消息 ================================*/
    {   ID_NAS_LMM_INTRA_TAU_REQ                             ,
            "MSG:  ID_NAS_LMM_INTRA_TAU_REQ                         "},

    {   ID_NAS_LMM_INTRA_DATA_IND                            ,
            "MSG:  ID_NAS_LMM_INTRA_DATA_IND                        "},

    {   ID_NAS_LMM_INTRA_CONN2IDLE_REQ                       ,
            "MSG:  ID_NAS_LMM_INTRA_CONN2IDLE_REQ                   "}
};


/* RRC-MM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmRrcMsgIdArray[] =
{
    /* MM发给RRC的原语 */
    {   ID_LRRC_LMM_START_REQ             ,
            "MSG:  ID_LRRC_LMM_START_REQ                             "},
    {   ID_LRRC_LMM_PLMN_SEARCH_REQ       ,
            "MSG:  ID_LRRC_LMM_PLMN_SEARCH_REQ                       "},
    {   ID_LRRC_LMM_PLMN_SEARCH_STOP_REQ  ,
            "MSG:  ID_LRRC_LMM_PLMN_SEARCH_STOP_REQ                  "},
    {   ID_LRRC_LMM_EQU_PLMN_NOTIFY_REQ   ,
            "MSG:  ID_LRRC_LMM_EQU_PLMN_NOTIFY_REQ                   "},
    {   ID_LRRC_LMM_NAS_INFO_CHANGE_REQ   ,
            "MSG:  ID_LRRC_LMM_NAS_INFO_CHANGE_REQ                   "},
    {   ID_LRRC_LMM_CELL_SELECTION_CTRL_REQ,
            "MSG:  ID_LRRC_LMM_CELL_SELECTION_CTRL_REQ               "},
    {   ID_LRRC_LMM_EST_REQ               ,
            "MSG:  ID_LRRC_LMM_EST_REQ                               "},
    {   ID_LRRC_LMM_REL_REQ               ,
            "MSG:  ID_LRRC_LMM_REL_REQ                               "},
    {   ID_LRRC_LMM_DATA_REQ              ,
            "MSG:  ID_LRRC_LMM_DATA_REQ                              "},
    {   ID_LRRC_LMM_POWER_OFF_REQ         ,
            "MSG:  ID_LRRC_LMM_POWER_OFF_REQ                         "},
    {   ID_LRRC_LMM_SUSPEND_RSP           ,
            "MSG:  ID_LRRC_LMM_SUSPEND_RSP                           "},
    {   ID_LRRC_LMM_RESUME_RSP            ,
            "MSG:  ID_LRRC_LMM_RESUME_RSP                            "},
    {   ID_LRRC_LMM_SUSPEND_REQ           ,
            "MSG:  ID_LRRC_LMM_SUSPEND_REQ                           "},
    {   ID_LRRC_LMM_SECU_PARA_RSP         ,
            "MSG:  ID_LRRC_LMM_SECU_PARA_RSP                         "},
    {   ID_LRRC_LMM_SYS_CFG_REQ           ,
            "MSG:  ID_LRRC_LMM_SYS_CFG_REQ                           "},
    {   ID_LRRC_LMM_OOS_STATE_REQ         ,
            "MSG:  ID_LRRC_LMM_OOS_STATE_REQ                         "},
    {   ID_LRRC_LMM_CLEAR_BUFF_NOTIFY         ,
            "MSG:  ID_LRRC_LMM_CLEAR_BUFF_NOTIFY                     "},
    {   ID_LRRC_LMM_BG_PLMN_SEARCH_REQ    ,
            "MSG:  ID_LRRC_LMM_BG_PLMN_SEARCH_REQ                    "},
    {   ID_LRRC_LMM_BG_PLMN_SEARCH_STOP_REQ,
            "MSG:  ID_LRRC_LMM_BG_PLMN_SEARCH_STOP_REQ               "},

    {   ID_LRRC_LMM_SUSPEND_REL_REQ           ,
                "MSG:  ID_LRRC_LMM_SUSPEND_REL_REQ                       "},
    #if (FEATURE_ON == FEATURE_DSDS)
    {   ID_LRRC_LMM_BEGIN_SESSION_NOTIFY           ,
                "MSG:  ID_LRRC_LMM_BEGIN_SESSION_NOTIFY                       "},
    {   ID_LRRC_LMM_END_SESSION_NOTIFY           ,
                "MSG:  ID_LRRC_LMM_END_SESSION_NOTIFY                       "},
    #endif
    {   ID_LRRC_LMM_UTRAN_MODE_REQ           ,
                "MSG:  ID_LRRC_LMM_UTRAN_MODE_REQ                       "},
    {   ID_LRRC_LMM_CELL_SIGN_REPORT_NOTIFY           ,
                "MSG:  ID_LRRC_LMM_CELL_SIGN_REPORT_NOTIFY           "},

    {   ID_LRRC_LMM_DISABLE_LTE_NOTIFY           ,
                "MSG:  ID_LRRC_LMM_DISABLE_LTE_NOTIFY           "},

    {   ID_LRRC_LMM_CSFB_NOTIFY           ,
            "ID_LRRC_LMM_CSFB_NOTIFY                                 "},

    {   ID_LRRC_LMM_CSG_LIST_SEARCH_REQ           ,
            "MSG: ID_LRRC_LMM_CSG_LIST_SEARCH_REQ                                 "},
    {   ID_LRRC_LMM_CSG_WHITE_LIST_NOTIFY           ,
            "MSG: ID_LRRC_LMM_CSG_WHITE_LIST_NOTIFY                                 "},
    {   ID_LRRC_LMM_CSG_BG_SEARCH_REQ           ,
            "MSG: ID_LRRC_LMM_CSG_BG_SEARCH_REQ                                 "},


    /* RRC发给MM的原语 */
    {   ID_LRRC_LMM_START_CNF             ,
            "MSG:  ID_LRRC_LMM_START_CNF                             "},
    {   ID_LRRC_LMM_PLMN_SEARCH_CNF       ,
            "MSG:  ID_LRRC_LMM_PLMN_SEARCH_CNF                       "},
    {   ID_LRRC_LMM_PLMN_SEARCH_STOP_CNF  ,
            "MSG:  ID_LRRC_LMM_PLMN_SEARCH_STOP_CNF                  "},
    {   ID_LRRC_LMM_EST_CNF               ,
            "MSG:  ID_LRRC_LMM_EST_CNF                               "},
    {   ID_LRRC_LMM_REL_CNF               ,
            "MSG:  ID_LRRC_LMM_REL_CNF                               "},
    {   ID_LRRC_LMM_REL_IND               ,
            "MSG:  ID_LRRC_LMM_REL_IND                               "},
    {   ID_LRRC_LMM_ERR_IND               ,
            "MSG:  ID_LRRC_LMM_ERR_IND                               "},
    {   ID_LRRC_LMM_AREA_LOST_IND         ,
            "MSG:  ID_LRRC_LMM_AREA_LOST_IND                         "},
    {   ID_LRRC_LMM_SYS_INFO_IND          ,
            "MSG:  ID_LRRC_LMM_SYS_INFO_IND                          "},
    {   ID_LRRC_LMM_PAGING_IND            ,
            "MSG:  ID_LRRC_LMM_PAGING_IND                            "},
    {   ID_LRRC_LMM_DATA_IND              ,
            "MSG:  ID_LRRC_LMM_DATA_IND                              "},
    {   ID_LRRC_LMM_SECURITY_IND          ,
            "MSG:  ID_LRRC_LMM_SECURITY_IND                          "},
    {   ID_LRRC_LMM_POWER_OFF_CNF         ,
            "MSG:  ID_LRRC_LMM_POWER_OFF_CNF                         "},
    {   ID_LRRC_LMM_ACCESS_GRANT_IND      ,
            "MSG:  ID_LRRC_LMM_ACCESS_GRANT_IND                      "},
    {   ID_LRRC_LMM_DATA_CNF              ,
                "MSG:  ID_LRRC_LMM_DATA_CNF                          "},
    {   ID_LRRC_LMM_SUSPEND_IND           ,
                "MSG:  ID_LRRC_LMM_SUSPEND_IND                       "},
    {   ID_LRRC_LMM_RESUME_IND            ,
                "MSG:  ID_LRRC_LMM_RESUME_IND                        "},
    {   ID_LRRC_LMM_SUSPEND_CNF           ,
                "MSG:  ID_LRRC_LMM_SUSPEND_CNF                       "},
    {   ID_LRRC_LMM_SECU_PARA_IND         ,
                "MSG:  ID_LRRC_LMM_SECU_PARA_IND                     "},
    {   ID_LRRC_LMM_SYS_CFG_CNF           ,
                "MSG:  ID_LRRC_LMM_SYS_CFG_CNF                       "},
    {   ID_LRRC_LMM_SUSPEND_REL_CNF           ,
                "MSG:  ID_LRRC_LMM_SUSPEND_REL_CNF                       "},

    {   ID_LRRC_LMM_MBMS_SESSION_CFG_CNF  ,
                "MSG:  ID_LRRC_LMM_MBMS_SESSION_CFG_CNF              "},
    {   ID_LRRC_LMM_MBMS_SESSION_IND      ,
                "MSG:  ID_LRRC_LMM_MBMS_SESSION_IND                  "},
    {   ID_LRRC_LMM_BG_PLMN_SEARCH_CNF    ,
                "MSG:  ID_LRRC_LMM_BG_PLMN_SEARCH_CNF                "},
    {   ID_LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF,
                "MSG:  ID_LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF           "},
    {   ID_LRRC_LMM_NOT_CAMP_ON_IND       ,
                "MSG:  ID_LRRC_LMM_NOT_CAMP_ON_IND                   "},
    {   ID_LRRC_LMM_UTRAN_MODE_CNF           ,
                "MSG:  ID_LRRC_LMM_UTRAN_MODE_CNF                     "},
    {   ID_LRRC_LMM_INTER_OPT_IND           ,
                "MSG:  ID_LRRC_LMM_INTER_OPT_IND                     "},

    {   ID_LRRC_LMM_CSG_LIST_SEARCH_CNF           ,
                "MSG:  ID_LRRC_LMM_CSG_LIST_SEARCH_CNF                     "},
    {   ID_LRRC_LMM_CSG_BG_SEARCH_CNF           ,
                "MSG:  ID_LRRC_LMM_CSG_BG_SEARCH_CNF                     "},
    {   ID_LRRC_LMM_CSG_ID_HOME_NODEB_NAME_IND           ,
                "MSG:  ID_LRRC_LMM_CSG_ID_HOME_NODEB_NAME_IND                     "},
    {   ID_LRRC_LMM_UE_CAP_CHANGE_IND           ,
                "MSG:  ID_LRRC_LMM_UE_CAP_CHANGE_IND                     "},

};

/* APP-MM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmAppMsgIdArray[] =
{
    {   ID_APP_MM_REG_STAT_IND         ,
            "MSG:  ID_APP_MM_REG_STAT_IND                          "},
    #if (FEATURE_PTM == FEATURE_ON)
    {   ID_OM_LNAS_ERR_LOG_CTRL_IND         ,
            "MSG:  ID_OM_LNAS_ERR_LOG_CTRL_IND                     "},
    {   ID_OM_LNAS_ERR_LOG_REPORT_REQ       ,
            "MSG:  ID_OM_LNAS_ERR_LOG_REPORT_REQ                   "},
    {   ID_LNAS_OM_ERR_LOG_REPORT_CNF       ,
            "MSG:  ID_LNAS_OM_ERR_LOG_REPORT_CNF                   "},
    {   ID_OM_FTM_CTRL_IND             ,
            "MSG:  ID_OM_FTM_CTRL_IND                              "},
    {   ID_OM_FTM_REPROT_IND           ,
            "MSG:  ID_OM_FTM_REPROT_IND                            "},
    #endif
};

/* MMC-MM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmMmcMsgIdArray[] =
{
    {   ID_MMC_LMM_START_REQ              ,
            "MSG:  ID_MMC_LMM_START_REQ                         "},
    {   ID_MMC_LMM_STOP_REQ              ,
            "MSG:  ID_MMC_LMM_STOP_REQ                          "},
    {   ID_MMC_LMM_PLMN_SRCH_REQ           ,
            "MSG:  ID_MMC_LMM_PLMN_SRCH_REQ                     "},
    {   ID_MMC_LMM_STOP_PLMN_SRCH_REQ               ,
            "MSG:  ID_MMC_LMM_STOP_PLMN_SRCH_REQ                     "},
    {   ID_MMC_LMM_EPLMN_NOTIFY_REQ,
            "MSG:  ID_MMC_LMM_EPLMN_NOTIFY_REQ                  "},
    {   ID_MMC_LMM_CELL_SELECTION_CTRL_REQ,
            "MSG:  ID_MMC_LMM_CELL_SELECTION_CTRL_REQ           "},
    {   ID_MMC_LMM_ACTION_RESULT_REQ,
            "MSG:  ID_MMC_LMM_ACTION_RESULT_REQ                 "},
    {   ID_MMC_LMM_REL_REQ,
            "MSG:  ID_MMC_LMM_REL_REQ                           "},
    {   ID_MMC_LMM_SUSPEND_REQ,
            "MSG:  ID_MMC_LMM_SUSPEND_REQ                       "},
    {   ID_MMC_LMM_CSFB_REQ,
            "MSG:  ID_MMC_LMM_CSFB_REQ                          "},
    {   ID_MMC_LMM_SYS_CFG_REQ,
            "MSG:  ID_MMC_LMM_SYS_CFG_REQ                       "},
    {   ID_MMC_LMM_USIM_STATUS_REQ,
            "MSG:  ID_MMC_LMM_USIM_STATUS_REQ                   "},
    {   ID_MMC_LMM_ATTACH_REQ,
            "MSG:  ID_MMC_LMM_ATTACH_REQ                        "},
    {   ID_MMC_LMM_DETACH_REQ,
            "MSG:  ID_MMC_LMM_DETACH_REQ                        "},
    {   ID_MMC_LMM_RESUME_NOTIFY,
            "MSG:  ID_MMC_LMM_RESUME_NOTIFY                     "},
    {   ID_MMC_LMM_SUSPEND_REL_REQ,
            "MSG:  ID_MMC_LMM_SUSPEND_REL_REQ                     "},
    {   ID_MMC_LMM_SUSPEND_RSP,
            "MSG:  ID_MMC_LMM_SUSPEND_RSP                       "},
    {   ID_MMC_LMM_DISABLE_LTE_NOTIFY,
            "MSG:  ID_MMC_LMM_DISABLE_LTE_NOTIFY                "},
    {   ID_MMC_LMM_ENABLE_LTE_NOTIFY,
            "MSG:  ID_MMC_LMM_ENABLE_LTE_NOTIFY                 "},
    {   ID_MMC_LMM_USER_PLMN_END_NOTIFY,
            "MSG:  ID_MMC_LMM_USER_PLMN_END_NOTIFY               "},
    {   ID_MMC_LMM_UE_OOC_STATUS_NOTIFY,
            "MSG:  ID_MMC_LMM_UE_OOC_STATUS_NOTIFY                       "},
    {   ID_MMC_LMM_WCDMA_SYS_INFO_IND,
            "MSG:  ID_MMC_LMM_WCDMA_SYS_INFO_IND                 "},
    {   ID_MMC_LMM_GSM_SYS_INFO_IND,
            "MSG:  ID_MMC_LMM_GSM_SYS_INFO_IND                  "},
    {   ID_MMC_LMM_BG_PLMN_SEARCH_REQ,
            "MSG:  ID_MMC_LMM_BG_PLMN_SEARCH_REQ                "},
    {   ID_MMC_LMM_STOP_BG_PLMN_SEARCH_REQ,
            "MSG:  ID_MMC_LMM_STOP_BG_PLMN_SEARCH_REQ                "},
    {   ID_MMC_LMM_UTRAN_MODE_REQ,
            "MSG:  ID_MMC_LMM_UTRAN_MODE_REQ                    "},
    {   ID_MMC_LMM_LTE_SYS_INFO_IND,
            "MSG:  ID_MMC_LMM_LTE_SYS_INFO_IND                   "},
    #if (FEATURE_ON == FEATURE_DSDS)
    {   ID_MMC_LMM_BEGIN_SESSION_NOTIFY           ,
                "MSG:  ID_MMC_LMM_BEGIN_SESSION_NOTIFY                       "},
    {   ID_MMC_LMM_END_SESSION_NOTIFY           ,
                "MSG:  ID_MMC_LMM_END_SESSION_NOTIFY                       "},
    #endif


    {   ID_LMM_MMC_START_CNF              ,
            "MSG:  ID_LMM_MMC_START_CNF                         "},
    {   ID_LMM_MMC_STOP_CNF              ,
            "MSG:  ID_LMM_MMC_STOP_CNF                          "},
    {   ID_LMM_MMC_PLMN_SRCH_CNF           ,
            "MSG:  ID_LMM_MMC_PLMN_SRCH_CNF                     "},
    {   ID_LMM_MMC_STOP_PLMN_SRCH_CNF               ,
            "MSG:  ID_LMM_MMC_STOP_PLMN_SRCH_CNF                     "},
    {   ID_LMM_MMC_AREA_LOST_IND,
            "MSG:  ID_LMM_MMC_AREA_LOST_IND                     "},
    {   ID_LMM_MMC_SYS_INFO_IND         ,
            "MSG:  ID_LMM_MMC_SYS_INFO_IND                      "},
    {   ID_LMM_MMC_EMM_INFO_IND,
            "MSG:  ID_LMM_MMC_EMM_INFO_IND                      "},
    {   ID_LMM_MMC_ERR_IND         ,
            "MSG:  ID_LMM_MMC_ERR_IND                           "},
    {   ID_LMM_MMC_EPS_SERVICE_IND         ,
            "MSG:  ID_LMM_MMC_EPS_SERVICE_IND                   "},
    {   ID_LMM_MMC_SUSPEND_IND,
            "MSG:  ID_LMM_MMC_SUSPEND_IND                       "},
    {   ID_LMM_MMC_SUSPEND_CNF,
            "MSG:  ID_LMM_MMC_SUSPEND_CNF                       "},
    {   ID_LMM_MMC_RESUME_IND,
            "MSG:  ID_LMM_MMC_RESUME_IND                        "},
    {   ID_LMM_MMC_STATUS_IND,
            "MSG:  ID_LMM_MMC_STATUS_IND                        "},
    {   ID_LMM_MMC_SYS_CFG_CNF,
            "MSG:  ID_LMM_MMC_SYS_CFG_CNF                       "},
    {   ID_LMM_MMC_USIM_STATUS_CNF,
            "MSG:  ID_LMM_MMC_USIM_STATUS_CNF                   "},
    {   ID_LMM_MMC_ATTACH_CNF,
            "MSG:  ID_LMM_MMC_ATTACH_CNF                        "},
    {   ID_LMM_MMC_ATTACH_IND,
            "MSG:  ID_LMM_MMC_ATTACH_IND                        "},
    {   ID_LMM_MMC_DETACH_CNF,
            "MSG:  ID_LMM_MMC_DETACH_CNF                        "},
    {   ID_LMM_MMC_DETACH_IND,
            "MSG:  ID_LMM_MMC_DETACH_IND                        "},
    {   ID_LMM_MMC_TAU_RESULT_IND,
            "MSG:  ID_LMM_MMC_TAU_RESULT_IND                    "},
    {   ID_LMM_MMC_SERVICE_RESULT_IND,
            "MSG:  ID_LMM_MMC_SERVICE_RESULT_IND                "},
    {   ID_LMM_MMC_TIN_TYPE_IND,
            "MSG:  ID_LMM_MMC_TIN_TYPE_IND                      "},
    /*{   ID_LMM_MMC_SERVICE_STATUS_IND,
            "MSG:  ID_LMM_MMC_SERVICE_STATUS_IND                "},*/
    /*{   ID_LMM_MMC_REGISTER_STATUS_IND,
            "MSG:  ID_LMM_MMC_REGISTER_STATUS_IND               "},*/
    {   ID_LMM_MMC_BG_PLMN_SEARCH_CNF,
            "MSG:  ID_LMM_MMC_BG_PLMN_SEARCH_CNF                "},
    {   ID_LMM_MMC_STOP_BG_PLMN_SEARCH_CNF,
            "MSG:  ID_LMM_MMC_STOP_BG_PLMN_SEARCH_CNF           "},
    {   ID_LMM_MMC_NOT_CAMP_ON_IND,
            "MSG:  ID_LMM_MMC_NOT_CAMP_ON_IND                    "},
    {   ID_LMM_MMC_UTRAN_MODE_CNF,
            "MSG:  ID_LMM_MMC_UTRAN_MODE_CNF                    "},
    {   ID_LMM_MMC_SUSPEND_REL_CNF,
            "MSG:  ID_LMM_MMC_SUSPEND_REL_CNF                     "},
    {   ID_LMM_MMC_TIMER_STATE_NOTIFY,
            "MSG:  ID_LMM_MMC_TIMER_STATE_NOTIFY                 "},
    {   ID_LMM_MMC_EMC_PDP_STATUS_NOTIFY,
            "MSG:  ID_LMM_MMC_EMC_PDP_STATUS_NOTIFY              "},
    {   ID_LMM_MMC_INFO_CHANGE_NOTIFY,
            "MSG:  ID_LMM_MMC_INFO_CHANGE_NOTIFY              "},
    {   ID_LMM_MMC_SIM_AUTH_FAIL_IND,
            "MSG:  ID_LMM_MMC_SIM_AUTH_FAIL_IND              "},
    {   ID_LMM_MMC_CELL_SIGN_REPORT_IND,
            "MSG:  ID_LMM_MMC_CELL_SIGN_REPORT_IND           "},
    {   ID_LMM_MMC_T3402_LEN_NOTIFY,
            "MSG:  ID_LMM_MMC_T3402_LEN_NOTIFY           "},

    {   ID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY,
            "MSG:  ID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY           "},
    {   ID_MMC_LMM_CSG_WHITE_LIST_NOTIFY,
            "MSG:  ID_MMC_LMM_CSG_WHITE_LIST_NOTIFY           "},
    {   ID_MMC_LMM_CSG_LIST_SEARCH_REQ,
            "MSG:  ID_MMC_LMM_CSG_LIST_SEARCH_REQ           "},
    {   ID_MMC_LMM_CSG_BG_SEARCH_REQ,
            "MSG:  ID_MMC_LMM_CSG_BG_SEARCH_REQ           "},
    {   ID_LMM_MMC_CSG_LIST_SEARCH_CNF,
            "MSG:  ID_LMM_MMC_CSG_LIST_SEARCH_CNF           "},
    {   ID_LMM_MMC_CSG_BG_SEARCH_CNF,
            "MSG:  ID_LMM_MMC_CSG_BG_SEARCH_CNF           "},
    {   ID_LMM_MMC_CSG_ID_HOME_NODEB_NAME_IND,
            "MSG:  ID_LMM_MMC_CSG_ID_HOME_NODEB_NAME_IND           "},


};

/* GMM-MM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmGmmMsgIdArray[] =
{
    {   ID_GMM_LMM_RESEL_SECU_INFO_REQ              ,
            "MSG:  ID_GMM_LMM_RESEL_SECU_INFO_REQ               "},
    {   ID_GMM_LMM_HO_SECU_INFO_REQ              ,
            "MSG:  ID_GMM_LMM_HO_SECU_INFO_REQ                  "},
    {   ID_GMM_LMM_TIMER_STATE_NOTIFY              ,
            "MSG:  ID_GMM_LMM_TIMER_STATE_NOTIFY                  "},
    #if (FEATURE_ON == FEATURE_DSDS)
    {   ID_GMM_LMM_BEGIN_SESSION_NOTIFY           ,
                "MSG:  ID_GMM_LMM_BEGIN_SESSION_NOTIFY                       "},
    {   ID_GMM_LMM_END_SESSION_NOTIFY           ,
                "MSG:  ID_GMM_LMM_END_SESSION_NOTIFY                       "},
    #endif
    {   ID_LMM_GMM_RESEL_SECU_INFO_CNF              ,
            "MSG:  ID_LMM_GMM_RESEL_SECU_INFO_CNF               "},
    {   ID_LMM_GMM_HO_SECU_INFO_CNF              ,
            "MSG:  ID_LMM_GMM_HO_SECU_INFO_CNF                  "},

};

/* MM-LMM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmlmmMsgIdArray[] =
{
    {   ID_MM_LMM_CSFB_SERVICE_START_NOTIFY              ,
            "MSG:  ID_MM_LMM_CSFB_SERVICE_START_NOTIFY               "},
    {   ID_MM_LMM_CSFB_SERVICE_ABORT_NOTIFY              ,
            "MSG:  ID_MM_LMM_CSFB_SERVICE_ABORT_NOTIFY               "},
    #if (FEATURE_ON == FEATURE_DSDS)
    {   ID_MM_LMM_BEGIN_SESSION_NOTIFY           ,
                "MSG:  ID_MM_LMM_BEGIN_SESSION_NOTIFY                       "},
    {   ID_MM_LMM_END_SESSION_NOTIFY           ,
                "MSG:  ID_MM_LMM_END_SESSION_NOTIFY                       "},
    #endif
    {   ID_LMM_MM_COMBINED_START_NOTIFY_REQ              ,
            "MSG:  ID_LMM_MM_COMBINED_START_NOTIFY_REQ               "},
    {   ID_LMM_MM_CSFB_SERVICE_END_IND              ,
            "MSG:  ID_LMM_MM_CSFB_SERVICE_END_IND                    "},
    {   ID_LMM_MM_CSFB_SERVICE_PAGING_IND              ,
            "MSG:  ID_LMM_MM_CSFB_SERVICE_PAGING_IND                 "},
    {   ID_LMM_MM_INFO_CHANGE_NOTIFY              ,
            "MSG:  ID_LMM_MM_INFO_CHANGE_NOTIFY                      "},
};

/* SMS-LMM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astLmmSmsMsgIdArray[] =
{
    {   ID_SMS_LMM_EST_REQ              ,
            "MSG:  ID_SMS_LMM_EST_REQ                         "},
    {   ID_SMS_LMM_DATA_REQ              ,
            "MSG:  ID_SMS_LMM_DATA_REQ                        "},

    {   ID_LMM_SMS_EST_CNF              ,
            "MSG:  ID_LMM_SMS_EST_CNF                         "},
    {   ID_LMM_SMS_DATA_IND              ,
            "MSG:  ID_LMM_SMS_DATA_IND                        "},
    {   ID_LMM_SMS_ERR_IND              ,
            "MSG:  ID_LMM_SMS_ERR_IND                         "},
    {   ID_LMM_SMS_SERVICE_STATUS_IND              ,
            "MSG:  ID_LMM_SMS_SERVICE_STATUS_IND              "},

};

NAS_COMM_PRINT_MSG_LIST_STRU g_astMmCnMsgArray[] =
{
    {   EMM_MSG_TYPE_INVALID            ,
            "CN MSG:\tEMM_MSG_TYPE_INVALID                         "},
    {   NAS_EMM_CN_MT_ATTACH_REQ        ,
            "UE-->CN:\tNAS_EMM_CN_MT_ATTACH_REQ                    "},
    {   NAS_EMM_CN_MT_ATTACH_ACP        ,
            "CN-->UE:\tNAS_EMM_CN_MT_ATTACH_ACP                    "},
    {   NAS_EMM_CN_MT_ATTACH_CMP        ,
            "UE-->CN:\tNAS_EMM_CN_MT_ATTACH_CMP                    "},
    {   NAS_EMM_CN_MT_ATTACH_REJ        ,
            "CN-->UE:\tNAS_EMM_CN_MT_ATTACH_REJ                    "},
    {   NAS_EMM_CN_MT_DETACH_REQ_MT     ,
            "UE/CN-->CN/UE:\tNAS_EMM_CN_MT_DETACH_REQ              "},
    {   NAS_EMM_CN_MT_DETACH_ACP_MO     ,
            "CN/UE-->UE/CN:\tNAS_EMM_CN_MT_DETACH_ACP              "},
    {   NAS_EMM_CN_MT_TAU_REQ           ,
            "UE-->CN:\tNAS_EMM_CN_MT_TAU_REQ                       "},
    {   NAS_EMM_CN_MT_TAU_ACP           ,
            "CN-->UE:\tNAS_EMM_CN_MT_TAU_ACP                       "},
    {   NAS_EMM_CN_MT_TAU_CMP           ,
            "UE-->CN:\tNAS_EMM_CN_MT_TAU_CMP                       "},
    {   NAS_EMM_CN_MT_TAU_REJ           ,
            "CN-->UE:\tNAS_EMM_CN_MT_TAU_REJ                       "},
    {   NAS_EMM_CN_MT_SER_REQ           ,
            "UE-->CN:\tNAS_EMM_CN_MT_SER_REQ,                      "},
    {   NAS_EMM_CN_MT_SER_REJ           ,
            "CN-->UE:\tNAS_EMM_CN_MT_SER_REJ                       "},
    {   NAS_EMM_CN_MT_GUTI_CMD          ,
            "CN-->UE:\tNAS_EMM_CN_MT_GUTI_CMD                      "},
    {   NAS_EMM_CN_MT_GUTI_CMP          ,
            "UE-->CN:\tNAS_EMM_CN_MT_GUTI_CMP                      "},
    {   NAS_EMM_CN_MT_AUTH_REQ          ,
            "CN-->UE:\tNAS_EMM_CN_MT_AUTH_REQ                      "},
    {   NAS_EMM_CN_MT_AUTH_RSP          ,
            "UE-->CN:\tNAS_EMM_CN_MT_AUTH_RSP                      "},
    {   NAS_EMM_CN_MT_AUTH_REJ          ,
            "CN-->UE:\tNAS_EMM_CN_MT_AUTH_REJ                      "},

    {   NAS_EMM_CN_MT_IDEN_REQ          ,
            "CN-->UE:\tNAS_EMM_CN_MT_IDEN_REQ                      "},
    {   NAS_EMM_CN_MT_IDEN_RSP          ,
            "UE-->CN:\tNAS_EMM_CN_MT_IDEN_RSP                      "},
    {   NAS_EMM_CN_MT_AUTH_FAIl          ,
            "UE-->CN:\tNAS_EMM_CN_MT_AUTH_FAIL                     "},

    {   NAS_EMM_CN_MT_SMC_CMD          ,
            "CN-->UE:\tNAS_EMM_CN_MT_SMC_CMD                       "},
    {   NAS_EMM_CN_MT_SMC_CMP          ,
            "UE-->CN:\tNAS_EMM_CN_MT_SMC_CMP                       "},
    {   NAS_EMM_CN_MT_SMC_REJ          ,
            "UE-->CN:\tNAS_EMM_CN_MT_SMC_REJ                       "},


    {   NAS_EMM_CN_MT_EMM_STATUS          ,
            "CN-->UE:\tNAS_EMM_CN_MT_EMM_STATUS                    "},
    {   NAS_EMM_CN_MT_EMM_INFO          ,
            "CN-->UE:\tNAS_EMM_CN_MT_EMM_INFO                      "},

    {   NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT          ,
            "CN-->UE:\tNAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT        "},
    {   NAS_EMM_CN_MT_UPLINK_NAS_TRANSPORT          ,
            "UE-->CN:\tNAS_EMM_CN_MT_UPLINK_NAS_TRANSPORT          "},
    {   NAS_EMM_CN_CS_SER_NOTIFICATION          ,
            "UE-->CN:\tNAS_EMM_CN_CS_SER_NOTIFICATION              "},
    {   NAS_EMM_CN_MT_EXT_SER_REQ           ,
            "UE-->CN:\tNAS_EMM_CN_MT_EXT_SER_REQ,                  "},

};

/* EMM-ESM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astMmUsimMsgIdArray[] =
{
    {   ID_MMC_LMM_USIM_STATUS_REQ               ,
            "MSG:  ID_MMC_LMM_USIM_STATUS_REQ                           "},
    {   USIMM_AUTHENTICATION_CNF               ,
            "MSG:  USIMM_AUTHENTICATION_CNF                              "},
    {   USIMM_UPDATEFILE_CNF,
            "MSG:  USIMM_UPDATEFILE_CNF                           "},
    {   USIMM_READFILE_CNF            ,
            "MSG:  USIMM_READFILE_CNF                           "}
};

#if (FEATURE_LPP == FEATURE_ON)
/* LPP-EMM 消息打印数组 */
NAS_COMM_PRINT_MSG_LIST_STRU g_astLMmLppMsgIdArray[] =
{
    {   ID_LPP_LMM_EST_REQ               ,
            "MSG:  ID_LPP_LMM_EST_REQ                              "},
    {   ID_LMM_LPP_EST_CNF               ,
            "MSG:  ID_LMM_LPP_EST_CNF                              "},
    {   ID_LPP_LMM_DATA_REQ               ,
            "MSG:  ID_LPP_LMM_DATA_REQ                              "},
    {   ID_LMM_LPP_DATA_CNF               ,
            "MSG:  ID_LMM_LPP_DATA_CNF                              "},
    {   ID_LMM_LPP_START_IND               ,
            "MSG:  ID_LMM_LPP_START_IND                              "},
    {   ID_LMM_LPP_STOP_IND               ,
            "MSG:  ID_LMM_LPP_STOP_IND                              "},
    {   ID_LMM_LPP_CELL_CHANGE_IND               ,
            "MSG:  ID_LMM_LPP_CELL_CHANGE_IND                       "},
    {   ID_LMM_LPP_DATA_IND               ,
            "MSG:  ID_LMM_LPP_DATA_IND                              "},
    {   ID_LMM_LPP_REL_IND               ,
            "MSG:  ID_LMM_LPP_REL_IND                              "}
};
NAS_COMM_PRINT_MSG_LIST_STRU g_astLMmLcsMsgIdArray[] =
{
    {   ID_LCS_LMM_EST_REQ               ,
            "MSG:  ID_LCS_LMM_EST_REQ                              "},
    {   ID_LCS_LMM_DATA_REQ               ,
            "MSG:  ID_LCS_LMM_DATA_REQ                              "},
    {   ID_LMM_LCS_EST_CNF               ,
            "MSG:  ID_LMM_LCS_EST_CNF                              "},
    {   ID_LMM_LCS_DATA_CNF               ,
            "MSG:  ID_LMM_LCS_DATA_CNF                              "},
    {   ID_LMM_LCS_DATA_IND               ,
            "MSG:  ID_LMM_LCS_DATA_IND                              "},
    {   ID_LMM_LCS_POS_CAP_INFO_IND               ,
            "MSG:  ID_LMM_LCS_POS_CAP_INFO_IND                      "},
    {   ID_LMM_LCS_REL_IND                ,
            "MSG:  ID_LMM_LCS_REL_IND                               "}
};

#endif


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
  3.1 外部模块调用打印函数
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_LMM_PrintFsmState
 Description     : 打印状态机状态(包括并行状态，主状态，子状态，状态定时器，系统TICK值)
 Input           : enParallelFsm -- NAS_LMM_PARALLEL_FSM_ENUM_UINT16
                                    -- NAS_LMM_PARALLEL_FSM_EMM
                                    -- NAS_LMM_PARALLEL_FSM_MMC
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_LMM_PrintFsmState(
                    NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId )
{
    NAS_LMM_FSM_STATE_STRU               *pstFsmState;
    VOS_INT32                           ilOutPutLen;
    VOS_UINT16                          usTotalLen         = 0;

    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    pstFsmState = NAS_LMM_GetCurFsmAddr(enParallelFsmId);

    /* 打印状态机(包括并行状态，主状态，子状态，状态定时器) */
    ilOutPutLen = NAS_LMM_PUBM_PrintFsmState(
                        NAS_COMM_GET_MM_PRINT_BUF(),
                        usTotalLen,
                        pstFsmState);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintFsmState, NAS_LMM_PUBM_PrintFsmState exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintFsmState_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);

    NAS_COMM_Print(NAS_COMM_GET_MM_PRINT_BUF(), usTotalLen);

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PrintFsmStateStack
 Description     : 打印状态机状态堆栈(包括堆栈深度，状态机状态，系统TICK值)
 Input           : enParallelFsm -- NAS_LMM_PARALLEL_FSM_ENUM_UINT16
                                    -- NAS_LMM_PARALLEL_FSM_EMM
                                    -- NAS_LMM_PARALLEL_FSM_MMC
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PrintFsmStateStack(
                    NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId )
{
    VOS_UINT32                          ulLoop;
    NAS_LMM_FSM_STATE_STACK_STRU         *pstFsmStateStack;
    VOS_UINT8                           ucStackDepth;
    VOS_INT32                           ilOutPutLen        = 0;
    VOS_UINT16                          usTotalLen         = 0;

    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    pstFsmStateStack = NAS_LMM_GetFsmStackAddr(enParallelFsmId);
    ucStackDepth = pstFsmStateStack->ucStackDepth;

    /* 打印状态机状态堆栈深度 */
    NAS_COMM_nsprintf_1(NAS_COMM_GET_MM_PRINT_BUF(),
                           usTotalLen,
                           "MmFsmStateStack Total Depth: %d   \r\n",
                           ucStackDepth,
                           &ilOutPutLen);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintFsmState, Print stack total depth exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintFsmStateStack_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }
    usTotalLen += (VOS_UINT16)ilOutPutLen;

    for ( ulLoop = 0; ulLoop < ucStackDepth ; ulLoop++ )
    {
        /* 打印状态机状态堆栈深度编号 */
        NAS_COMM_nsprintf_1(NAS_COMM_GET_MM_PRINT_BUF(),
                               usTotalLen,
                               "Depth %d  : ",
                               ulLoop,
                               &ilOutPutLen);
        if ( 0 == ilOutPutLen )
        {
            NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintFsmState, Print stack depth num exception.");
            TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintFsmStateStack_ENUM
,LNAS_FUNCTION_LABEL2);
            return;
        }
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        /* 打印状态机状态(包括并行状态，主状态，子状态，状态定时器) */
        ilOutPutLen = NAS_LMM_PUBM_PrintFsmState(
                            NAS_COMM_GET_MM_PRINT_BUF(),
                            usTotalLen,
                            &(pstFsmStateStack->astFsmStack[ulLoop]));
        if ( 0 == ilOutPutLen )
        {
            NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintFsmStateStack, NAS_LMM_PUBM_PrintFsmState exception.");
            TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintFsmStateStack_ENUM
,LNAS_FUNCTION_LABEL3);
            return;
        }
        usTotalLen += (VOS_UINT16)(ilOutPutLen);

        /* 打印系统TICK值 */
        NAS_COMM_nsprintf_1(NAS_COMM_GET_MM_PRINT_BUF(),
                               usTotalLen,
                               "[ TICK:  %ld ]\r\n",
                               PS_GET_TICK(),
                               &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        /* 打印回车换行 */
        NAS_COMM_nsprintf(NAS_COMM_GET_MM_PRINT_BUF(),
                             usTotalLen,
                             "\r\n",
                             &ilOutPutLen);
        if ( 0 == ilOutPutLen )
        {
            NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintFsmState, Print CR sign exception.");
            TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintFsmStateStack_ENUM
,LNAS_FUNCTION_LABEL4);
            return;
        }
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    NAS_COMM_Print(NAS_COMM_GET_MM_PRINT_BUF(), usTotalLen);

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PrintFsmState
 Description     : 打印状态(包括EMM更新状态，RRC连接状态，SIM卡状态，系统TICK值)
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PrintAuxFsm( VOS_VOID )
{
    NAS_LMM_AUXILIARY_FSM_STRU            *pstAuxFsm;
    VOS_INT32                            ilOutPutLen;
    VOS_UINT16                           usTotalLen         = 0;

    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    pstAuxFsm = NAS_LMM_GetMmAuxFsmAddr();

    /* 打印辅助状态机(包括EMM更新状态，RRC连接状态，SIM卡状态) */
    ilOutPutLen = NAS_LMM_PUBM_PrintAuxFsm(
                        NAS_COMM_GET_MM_PRINT_BUF(),
                        usTotalLen,
                        pstAuxFsm);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintAuxFsm, NAS_LMM_PUBM_PrintAuxFsm exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintAuxFsm_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);

    /* 打印系统TICK值 */
    NAS_COMM_nsprintf_1(NAS_COMM_GET_MM_PRINT_BUF(),
                           usTotalLen,
                           "[ TICK:  %ld ]\r\n",
                           PS_GET_TICK(),
                           &ilOutPutLen);
    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(NAS_COMM_GET_MM_PRINT_BUF(), usTotalLen);

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PrintCnMsgAndData
 Description     : 打印CN消息和携带的数据
 Input           : enMsgId  -- NAS_EMM_CN_MSG_TYPE_ENUM_UINT8
                   pstCnMsg -- LRRC_LNAS_MSG_STRU
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PrintCnMsgAndData
(
    LRRC_LNAS_MSG_STRU                    *pstCnMsg
)
{
    VOS_UINT16                          usTotalLen          = 0;
    VOS_INT32                           ilOutPutLen;
    VOS_UINT8                           enMsgId;
    VOS_UINT8                           ucProtocolDes;

    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    /*leixiantiao00258641在使用前对pstCnMsg进行空指针检查*/
    if ( VOS_NULL_PTR == pstCnMsg )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintCnMsgAndData, pstCnMsg is Null pointer!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintCnMsgAndData_ENUM
,LNAS_NULL_PTR);
        return ;
    }

    ucProtocolDes                       = pstCnMsg->aucNasMsg[0]&0x0f;
    /* EMM的消息
    */
    if(EMM_CN_MSG_PD_EMM                    ==  ucProtocolDes)
    {
       if(NAS_EMM_CN_MT_SER_REQ         ==  pstCnMsg->aucNasMsg[0])
       {
            enMsgId                     =    NAS_EMM_CN_MT_SER_REQ            ;
       }
       else
       {
            enMsgId                     = pstCnMsg->aucNasMsg[NAS_LMM_CN_MSG_MT_POS];
       }
    }
    /* ESM消息
    */
    else
    {
        enMsgId                         = pstCnMsg->aucNasMsg[2];
    }

    ilOutPutLen = NAS_LMM_PUBM_PrintCnMsg(
                        NAS_COMM_GET_MM_PRINT_BUF(),
                        usTotalLen,
                        enMsgId);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintCnMsgAndData, NAS_LMM_PUBM_PrintCnMsg exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintCnMsgAndData_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_nsprintf(NAS_COMM_GET_MM_PRINT_BUF(),
                     usTotalLen,
                     "\r\n",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintCnMsgAndData, print begin expception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintCnMsgAndData_ENUM
,LNAS_FUNCTION_LABEL2);
        return;
    }
    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印CN消息携带的数据 */
    ilOutPutLen = NAS_LMM_PUBM_PrintData(
                         NAS_COMM_GET_MM_PRINT_BUF(),
                         usTotalLen,
                         pstCnMsg);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PrintCnMsgAndData, NAS_LMM_PUBM_PrintData exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PrintCnMsgAndData_ENUM
,LNAS_FUNCTION_LABEL3);
        return;
    }
    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(NAS_COMM_GET_MM_PRINT_BUF(), usTotalLen);

    return;
}


/*****************************************************************************
  3.3 文件内部调用打印函数
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintParallelFsm
 Description     : 打印并行状态(文件内部调用函数,入参空指针检查省略)
 Input           : pcBuff          -- Formatted buffer
                   usOffset        -- Offset
                   enParallelFsmId -- NAS_LMM_PARALLEL_FSM_ENUM_UINT16
                                      -- NAS_LMM_PARALLEL_FSM_EMM
                                      -- NAS_LMM_PARALLEL_FSM_MMC
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintParallelFsm(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmParallelFsmNum;
    VOS_INT32                           ilOutPutLen         = 0;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmParallelFsmNum = sizeof(g_astMmParallelFsmArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmParallelFsmNum; ulLoop++)
    {
        if (g_astMmParallelFsmArray[ulLoop].ulId == enParallelFsmId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmParallelFsmNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usOffset,
                    (VOS_CHAR *)(g_astMmParallelFsmArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
    }
    else
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintParallelFsm, Invalid enParallelFsmId: ",
                              enParallelFsmId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintParallelFsm_ENUM
,LNAS_FUNCTION_LABEL1,
                              enParallelFsmId);
    }

    return ilOutPutLen;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintMainState
 Description     : 打印主状态
 Input           : pcBuff      -- Formatted buffer
                   usOffset    -- Offset
                   enMainState -- NAS_LMM_MAIN_STATE_ENUM_UINT16
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintMainState(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_LMM_MAIN_STATE_ENUM_UINT16           enMainState )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmMainStateNum;
    VOS_INT32                           ilOutPutLen         = 0;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmMainStateNum = sizeof(g_astMmMainStateArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmMainStateNum; ulLoop++)
    {
        if (g_astMmMainStateArray[ulLoop].ulId == enMainState)
        {
            break;
        }
    }

    if ( ulLoop < ulMmMainStateNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usOffset,
                    (VOS_CHAR *)(g_astMmMainStateArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
    }
    else
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintMainState, Invalid enMainState: ",
                              enMainState);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintMainState_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMainState);
    }

    return ilOutPutLen;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintSubState
 Description     : 打印子状态
 Input           : pcBuff     -- Formatted buffer
                   usOffset   -- Offset
                   enSubState -- NAS_LMM_SUB_STATE_ENUM_UINT16
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintSubState(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_LMM_SUB_STATE_ENUM_UINT16            enSubState )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmSubStateNum;
    VOS_INT32                           ilOutPutLen         = 0;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmSubStateNum = sizeof(g_astMmSubStateArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmSubStateNum; ulLoop++)
    {
        if (g_astMmSubStateArray[ulLoop].ulId == enSubState)
        {
            break;
        }
    }

    if ( ulLoop < ulMmSubStateNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usOffset,
                    (VOS_CHAR *)(g_astMmSubStateArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
    }
    else
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintSubState, Invalid enSubState: ",
                              enSubState);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintSubState_ENUM
,LNAS_FUNCTION_LABEL1,
                              enSubState);
    }

    return ilOutPutLen;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintStateTimer
 Description     : 打印状态定时器
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enStaTId -- NAS_LMM_STATE_TI_ENUM_UINT16
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintStateTimer(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_LMM_STATE_TI_ENUM_UINT16             enStaTId )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulStateTimerNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulStateTimerNum = sizeof(g_astMmStateTimerArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulStateTimerNum; ulLoop++)
    {
        if (g_astMmStateTimerArray[ulLoop].ulId == enStaTId)
        {
            break;
        }
    }

    if ( ulLoop < ulStateTimerNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usOffset,
                    (VOS_CHAR *)(g_astMmStateTimerArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK:  %ld ] ",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintStateTimer, Invalid enStaTId: ",
                              enStaTId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintStateTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                               enStaTId);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintPtlTimer
 Description     : 打印协议定时器
 Input           : VOS_CHAR *pcBuff
                   VOS_UINT16 usOffset
                   NAS_LMM_PTL_TI_ENUM_UINT16 usPtlTId
 Output          : None
 Return          : VOS_INT32

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintPtlTimer(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTId )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulPtlTimerNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulPtlTimerNum = sizeof(g_astMmPtlTimerArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulPtlTimerNum; ulLoop++)
    {
        if (g_astMmPtlTimerArray[ulLoop].ulId == enPtlTId)
        {
            break;
        }
    }

    if ( ulLoop < ulPtlTimerNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usOffset,
                    (VOS_CHAR *)(g_astMmPtlTimerArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintPtlTimer,Invalid enPtlTId: ",
                              enPtlTId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintPtlTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                              enPtlTId);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintFsmState
 Description     : 打印状态机状态(包括并行状态，主状态，子状态，状态定时器)
 Input           : pcBuff      -- Formatted buffer
                   usOffset    -- Offset
                   pstFsmState -- NAS_LMM_FSM_STATE_STRU
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintFsmState(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    const NAS_LMM_FSM_STATE_STRU             *pstFsmState )
{
    VOS_UINT16                          usLoop;
    VOS_INT32                           ilOutPutLen;
    VOS_UINT16                          usTotalLen          = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    /*======================= 打印并行状态 ===================================*/
    ilOutPutLen = NAS_LMM_PUBM_PrintParallelFsm(
                        pcBuff,
                        usTotalLen,
                        pstFsmState->enFsmId);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PUBM_PrintFsmState, NAS_LMM_PUBM_PrintParallelFsm exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PUBM_PrintFsmState_ENUM
,LNAS_FUNCTION_LABEL1);
        return 0;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);

    /* 为对齐, 打印该段字符后,后面从固定位置打印下一段 */
    for(usLoop=usTotalLen-1; usLoop<(usTotalLen+NAS_COMM_PRINT_SEP_LEN); usLoop++)
    {
        pcBuff[usLoop] = 32;            /* ASCII: 32 = space */
    }
    usTotalLen += NAS_COMM_PRINT_SEP_LEN;


    /*======================= 打印主状态 =====================================*/
    ilOutPutLen = NAS_LMM_PUBM_PrintMainState(
                        pcBuff,
                        usTotalLen,
                        pstFsmState->enMainState);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PUBM_PrintFsmState, NAS_LMM_PUBM_PrintMainState exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PUBM_PrintFsmState_ENUM
,LNAS_FUNCTION_LABEL2);
        return 0;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);

    /* 为对齐, 打印该段字符后,后面从固定位置打印下一段 */
    for(usLoop=usTotalLen-1; usLoop<(usTotalLen+NAS_COMM_PRINT_SEP_LEN); usLoop++)
    {
        pcBuff[usLoop] = 32;            /* ASCII: 32 = space */
    }
    usTotalLen += NAS_COMM_PRINT_SEP_LEN;


    /*======================= 打印子状态 =====================================*/
    ilOutPutLen = NAS_LMM_PUBM_PrintSubState(
                        pcBuff,
                        usTotalLen,
                        pstFsmState->enSubState);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PUBM_PrintFsmState, NAS_LMM_PUBM_PrintSubState exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PUBM_PrintFsmState_ENUM
,LNAS_FUNCTION_LABEL3);
        return 0;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);

    /* 为对齐, 打印该段字符后,后面从固定位置打印下一段 */
    for(usLoop=usTotalLen-1; usLoop<(usTotalLen+NAS_COMM_PRINT_SEP_LEN); usLoop++)
    {
        pcBuff[usLoop] = 32;            /* ASCII: 32 = space */
    }
    usTotalLen += NAS_COMM_PRINT_SEP_LEN;

    /*======================= 打印状态定时器 =================================*/
    ilOutPutLen = NAS_LMM_PUBM_PrintStateTimer(
                        pcBuff,
                        usTotalLen,
                        pstFsmState->enStaTId);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PUBM_PrintFsmState, NAS_LMM_PUBM_PrintStateTimer exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PUBM_PrintFsmState_ENUM
,LNAS_FUNCTION_LABEL4);
        return 0;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);

    /* 为对齐, 打印该段字符后,后面从固定位置打印下一段 */
    for(usLoop=usTotalLen-1; usLoop<(usTotalLen+NAS_COMM_PRINT_SEP_LEN); usLoop++)
    {
        pcBuff[usLoop] = 32;            /* ASCII: 32 = space */
    }
    usTotalLen += NAS_COMM_PRINT_SEP_LEN;

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintEmmUpState
 Description     : 打印EMM更新状态
 Input           : pcBuff       -- Formatted buffer
                   usOffset     -- Offset
                   enEmmUpState -- NAS_EMM_UPDATE_STATE_ENUM_UINT8
                                   -- EMM_US_UPDATED_EU1
                                   -- EMM_US_NOT_UPDATED_EU2
                                   -- EMM_US_ROAMING_NOT_ALLOWED_EU3
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintEmmUpState(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_EMM_UPDATE_STATE_ENUM_UINT8         enEmmUpState )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmEmmUpStateNum;
    VOS_INT32                           ilOutPutLen         = 0;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmEmmUpStateNum = sizeof(g_astMmEmmUpStateArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmEmmUpStateNum; ulLoop++)
    {
        if (g_astMmEmmUpStateArray[ulLoop].ulId == enEmmUpState)
        {
            break;
        }
    }

    if ( ulLoop < ulMmEmmUpStateNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usOffset,
                    (VOS_CHAR *)(g_astMmEmmUpStateArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
    }
    else
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintEmmUpState, Invalid enEmmUpState: ",
                              enEmmUpState);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintEmmUpState_ENUM
,LNAS_FUNCTION_LABEL1,
                              enEmmUpState);
    }

    return ilOutPutLen;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintRrcConnState
 Description     : 打印RRC连接状态
 Input           : pcBuff         -- Formatted buffer
                   usOffset       -- Offset
                   enRrcConnState -- NAS_EMM_RRC_CONN_STATE_ENUM_UINT8
                                     -- NAS_EMM_CONN_IDLE
                                     -- EMM_RCS_CONN_EXIST
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintRrcConnState(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_EMM_RRC_CONN_STATE_ENUM_UINT8       enRrcConnState )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmRrcConnStateNum;
    VOS_INT32                           ilOutPutLen         = 0;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmRrcConnStateNum = sizeof(g_astMmRrcConnStateArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmRrcConnStateNum; ulLoop++)
    {
        if (g_astMmRrcConnStateArray[ulLoop].ulId == enRrcConnState)
        {
            break;
        }
    }

    if ( ulLoop < ulMmRrcConnStateNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usOffset,
                    (VOS_CHAR *)(g_astMmRrcConnStateArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
    }
    else
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintRrcConnState, Invalid enRrcConnState: ",
                              enRrcConnState);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintRrcConnState_ENUM
,LNAS_FUNCTION_LABEL1,
                              enRrcConnState);
    }

    return ilOutPutLen;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintUsimState
 Description     : 打印SIM卡状态
 Input           : pcBuff      -- Formatted buffer
                   usOffset    -- Offset
                   enUsimState -- NAS_EMM_USIM_STATE_ENUM_UINT8
                                  -- EMM_USIM_STATE_VALID
                                  -- EMM_USIM_STATE_INVALID
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintUsimState(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_EMM_USIM_STATE_ENUM_UINT8           enUsimState )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmUsimStateNum;
    VOS_INT32                           ilOutPutLen         = 0;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmUsimStateNum = sizeof(g_astMmUsimStateArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmUsimStateNum; ulLoop++)
    {
        if (g_astMmUsimStateArray[ulLoop].ulId == enUsimState)
        {
            break;
        }
    }

    if ( ulLoop < ulMmUsimStateNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usOffset,
                    (VOS_CHAR *)(g_astMmUsimStateArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
    }
    else
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintUsimState, Invalid enUsimState: ",
                              enUsimState);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintUsimState_ENUM
,LNAS_FUNCTION_LABEL1,
                              enUsimState);
    }

    return ilOutPutLen;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintAuxFsm
 Description     : 打印辅助状态机(包括EMM更新状态，RRC连接状态，SIM卡状态)
 Input           : pcBuff    -- Formatted buffer
                   usOffset  -- Offset
                   pstAuxFsm -- NAS_LMM_AUXILIARY_FSM_STRU
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintAuxFsm(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    const NAS_LMM_AUXILIARY_FSM_STRU               *pstAuxFsm )
{
    VOS_UINT16                          usLoop;
    VOS_INT32                           ilOutPutLen;
    VOS_UINT16                          usTotalLen          = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    /*======================= 打印EMM更新状态 ================================*/
    ilOutPutLen = NAS_LMM_PUBM_PrintEmmUpState(
                        pcBuff,
                        usTotalLen,
                        pstAuxFsm->ucEmmUpStat);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PUBM_PrintAuxFsm, NAS_LMM_PUBM_PrintEmmUpState exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PUBM_PrintAuxFsm_ENUM
,LNAS_FUNCTION_LABEL1);
        return 0;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);

    /* 为对齐, 打印该段字符后,后面从固定位置打印下一段 */
    for(usLoop=usTotalLen-1; usLoop<(usTotalLen+NAS_COMM_PRINT_SEP_LEN); usLoop++)
    {
        pcBuff[usLoop] = 32;            /* ASCII: 32 = space */
    }
    usTotalLen += NAS_COMM_PRINT_SEP_LEN;


    /*======================= 打印RRC连接状态 ================================*/
    ilOutPutLen = NAS_LMM_PUBM_PrintRrcConnState(
                        pcBuff,
                        usTotalLen,
                        pstAuxFsm->ucRrcConnState);
    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PUBM_PrintAuxFsm, NAS_LMM_PUBM_PrintMainState exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PUBM_PrintAuxFsm_ENUM
,LNAS_FUNCTION_LABEL2);
        return 0;
    }
    usTotalLen += (VOS_UINT16)(ilOutPutLen);

    /* 为对齐, 打印该段字符后,后面从固定位置打印下一段 */
    for(usLoop=usTotalLen-1; usLoop<(usTotalLen+NAS_COMM_PRINT_SEP_LEN); usLoop++)
    {
        pcBuff[usLoop] = 32;            /* ASCII: 32 = space */
    }
    usTotalLen += NAS_COMM_PRINT_SEP_LEN;


    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintTimer
 Description     : 打印定时器
 Input           : pcBuff       -- Formatted buffer
                   usOffset     -- Offset
                   pRelTimerMsg -- REL_TIMER_MSG
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintTimer(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    const REL_TIMER_MSG                     *pRelTimerMsg)
{
    VOS_INT32                           ilOutPutLen         = 0;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    switch ( pRelTimerMsg->ulPara )
    {
        case NAS_LMM_STATE_TIMER :
            ilOutPutLen = NAS_LMM_PUBM_PrintStateTimer(
                                pcBuff,
                                usOffset,
                                (VOS_UINT16)pRelTimerMsg->ulName);
            break;

        case NAS_LMM_PTL_TIMER :
            ilOutPutLen = NAS_LMM_PUBM_PrintPtlTimer(
                                pcBuff,
                                usOffset,
                                (VOS_UINT16)pRelTimerMsg->ulName);
            break;

        default:
            NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintTimer, Invalid TimerId: ",
                                  pRelTimerMsg->ulName);
            TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                  pRelTimerMsg->ulName);
            return 0;
    }

    return ilOutPutLen;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintMmIntraMsg
 Description     : 打印MM内部消息
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- NAS_LMM_INTRA_MSG_ID_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintMmIntraMsg(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_LMM_INTRA_MSG_ID_ENUM_UINT32         enMsgId )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmIntraMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmIntraMsgNum = sizeof(g_astMmIntraMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmIntraMsgNum; ulLoop++)
    {
        if (g_astMmIntraMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmIntraMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmIntraMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintMmIntraMsg, Invalid enMsgId: ",
                              enMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintMmIntraMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintRrcMsg
 Description     : 打印收到RRC消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- LRRC_LNAS_MSG_ID_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintRrcMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    LRRC_LNAS_MSG_ID_ENUM_UINT32          enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmRrcMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmRrcMsgNum = sizeof(g_astMmRrcMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmRrcMsgNum; ulLoop++)
    {
        if (g_astMmRrcMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmRrcMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmRrcMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintRrcMsg, Invalid enMsgId: ",
                              enMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintRrcMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintAppMsg
 Description     : 打印收到APP消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- APP_MM_MSG_TYPE_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintAppMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    APP_MM_MSG_TYPE_ENUM_UINT32         enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmAppMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmAppMsgNum = sizeof(g_astMmAppMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmAppMsgNum; ulLoop++)
    {
        if (g_astMmAppMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmAppMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmAppMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintAppMsg, Invalid enMsgId: ",
                              enMsgId);
       TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintAppMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintMmcMsg
 Description     : 打印收到APP消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- APP_MM_MSG_TYPE_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintMmcMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    MMC_LMM_MSG_ID_ENUM_UINT32          enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmMmcMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmMmcMsgNum = sizeof(g_astMmMmcMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmMmcMsgNum; ulLoop++)
    {
        if (g_astMmMmcMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmMmcMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmMmcMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintMmcMsg, Invalid enMsgId: ",
                              enMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintMmcMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}


/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintGmmMsg
 Description     : 打印收到APP消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- APP_MM_MSG_TYPE_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintGmmMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    MMC_LMM_MSG_ID_ENUM_UINT32          enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmMmcMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmMmcMsgNum = sizeof(g_astMmGmmMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmMmcMsgNum; ulLoop++)
    {
        if (g_astMmGmmMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmMmcMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmGmmMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintGmmMsg, Invalid enMsgId: ",
                              enMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintGmmMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintMmMsg
 Description     : 打印MM消息
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- APP_MM_MSG_TYPE_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lihong 00150010      2011-12-07  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintMmMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    MM_LMM_MSG_ID_ENUM_UINT32           enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmMmcMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    ulMmMmcMsgNum = sizeof(g_astMmlmmMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmMmcMsgNum; ulLoop++)
    {
        if (g_astMmlmmMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmMmcMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmlmmMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintMmMsg, Invalid enMsgId: ",
                              enMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintMmMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintSmsMsg
 Description     : 打印SMS消息
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- APP_MM_MSG_TYPE_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.


 History         :
    1.sunbing 49683      2011-11-3  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintSmsMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    MMC_LMM_MSG_ID_ENUM_UINT32          enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmMmcMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    ulMmMmcMsgNum = sizeof(g_astLmmSmsMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmMmcMsgNum; ulLoop++)
    {
        if (g_astLmmSmsMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmMmcMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astLmmSmsMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintSmsMsg, Invalid enMsgId: ",
                              enMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintSmsMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintUsimMsg
 Description     : 打印收到USIM消息(文件内部调用函数)
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  --
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.H41410 Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintUsimMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMsgNum = sizeof(g_astMmUsimMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMsgNum; ulLoop++)
    {
        if (g_astMmUsimMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmUsimMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintUsimMsg, Invalid enMsgId: ",
                              enMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintUsimMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintLppMsg
 Description     : 打印LPP消息
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- APP_MM_MSG_TYPE_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lifuxin 00253982 2015-08-08 新开发

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintLppMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    APP_MM_MSG_TYPE_ENUM_UINT32         enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmLppMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmLppMsgNum = sizeof(g_astLMmLppMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmLppMsgNum; ulLoop++)
    {
        if (g_astLMmLppMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmLppMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astMmLppMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintLppMsg, Invalid enMsgId: ",
                              enMsgId);
       TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintAppMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintLcsMsg
 Description     : 打印LPP消息
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- APP_MM_MSG_TYPE_ENUM_UINT32
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lifuxin 00253982 2015-08-08 新开发

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintLcsMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    APP_MM_MSG_TYPE_ENUM_UINT32         enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmLppMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmLppMsgNum = sizeof(g_astLMmLcsMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmLppMsgNum; ulLoop++)
    {
        if (g_astLMmLcsMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmLppMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astLMmLcsMsgIdArray[ulLoop].aucPrintString),
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
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PUBM_PrintLcsMsg, Invalid enMsgId: ",
                              enMsgId);
       TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintAppMsg_ENUM
,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return (usTotalLen - usOffset);
}


#endif

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintRevMsg
 Description     : 打印消息
 Input           : ulPid    -- MSG Sender PID or Receiver PID
                   pstMsg   -- NAS_LMM_PID_MSG_STRU
                   pcBuff   -- Formatted buffer
                   usOffset -- Offset
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact
    2.X00148705            2009-10-20  改名为NAS_LMM_PUBM_PrintRevMsg

*****************************************************************************/
VOS_VOID NAS_LMM_PUBM_PrintRevMsg
(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "NAS EMM Receive Message:",
                         &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PUBM_PrintRevMsg, Print receive msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PUBM_PrintRevMsg_ENUM
,LNAS_FUNCTION_LABEL1);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulSenderPid )
    {
        case PS_PID_MM :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "MM-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintMmIntraMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;

        case PS_PID_ESM :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "ESM-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmEsmMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case PS_PID_RABM :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "RABM-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmRabmMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);
            break;

        case PS_PID_ERRC :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "ERRC-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintRrcMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        /*case PS_PID_APP :*/
        case PS_PID_OM  :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "APP(OM)-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintAppMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
        #if (FEATURE_PTM == FEATURE_ON)
        case MSP_PID_DIAG_APP_AGENT  :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "APP(MSP_PID_DIAG_APP_AGENT)-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintAppMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
        #endif
        case WUEPS_PID_MMC  :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "MMC-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintMmcMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
         case WUEPS_PID_GMM  :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "GMM-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintGmmMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
        case WUEPS_PID_MM  :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "MM-->LMM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintMmMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;


         case WUEPS_PID_SMS  :
            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "SMS-->LMM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintSmsMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        case VOS_PID_TIMER :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "TIMER-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintTimer(pcBuff,
                                             usTotalLen,
                                             (REL_TIMER_MSG *)pstMsg);
            break;

        case WUEPS_PID_USIM  :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "USIM-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintUsimMsg(pcBuff,
                                                   usTotalLen,
                                                   pstMsg->ulMsgName);
            break;

        case PS_PID_TC:
            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "TC-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmTcMsg(pcBuff,
                                           usTotalLen,
                                           pstMsg->ulMsgName);

            break;

        #if (FEATURE_LPP == FEATURE_ON)
        case PS_PID_LPP:
            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "LPP-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintLppMsg(pcBuff,
                                           usTotalLen,
                                           pstMsg->ulMsgName);

            break;

        /* LCS模块PID变更为WUEPS_PID_LCS */
        case WUEPS_PID_LCS:

            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "LCS-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintLcsMsg(pcBuff,
                                           usTotalLen,
                                           pstMsg->ulMsgName);

            break;
        #endif

        default:
            NAS_LMM_PUBM_LOG2_WARN("NAS_LMM_PUBM_PrintRevMsg,Invalid Pid, MsgId: ",
                                  pstMsg->ulSenderPid,
                                  pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_WARNING2(NAS_LMM_PUBM_PrintRevMsg_ENUM
,LNAS_FUNCTION_LABEL2,
                                  pstMsg->ulSenderPid,
                                  pstMsg->ulMsgName);
            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG2_WARN("NAS_LMM_PUBM_PrintRevMsg, print return zero length.SenderPid, MsgId: ",
                              pstMsg->ulSenderPid,
                              pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING2(NAS_LMM_PUBM_PrintRevMsg_ENUM
,LNAS_FUNCTION_LABEL3,
                              pstMsg->ulSenderPid,
                              pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;
}


VOS_VOID NAS_LMM_PUBM_PrintSendMsg
(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
)
{
    NAS_LMM_PID_MSG_STRU                *pMmPidMsg;
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    /* 打印标题*/
    NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "NAS EMM Send Message:",
                         &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PUBM_PrintSendMsg, Print send msg header exception.");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PUBM_PrintSendMsg_ENUM
,LNAS_FUNCTION_LABEL1);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulReceiverPid )
    {
        case PS_PID_MM :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "MM-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintMmIntraMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;

        case PS_PID_ESM :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "MM-->ESM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmEsmMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case PS_PID_RABM :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "MM-->RABM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_COMM_PrintMmRabmMsg(pcBuff,
                                             usTotalLen,
                                             pstMsg->ulMsgName);
            break;

        case PS_PID_ERRC :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "MM-->ERRC\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintRrcMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        case PS_PID_ERMM :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "MM-->ERMM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintRrcMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        /*case PS_PID_APP :*/
        case PS_PID_OM  :
            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "MM-->APP(OM)\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintAppMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
        #if (FEATURE_PTM == FEATURE_ON)
        case MSP_PID_DIAG_APP_AGENT:
            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "MM-->APP(MSP_PID_DIAG_APP_AGENT)\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintAppMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
        #endif
        #if (FEATURE_LPP == FEATURE_ON)
        case PS_PID_LPP:
            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "MM-->LPP\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintLppMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        /* LCS模块PID变更为WUEPS_PID_LCS */
        case WUEPS_PID_LCS:

            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "MM-->LCS\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintLcsMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
        #endif


        case WUEPS_PID_MMC  :
            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "MM-->MMC\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintMmcMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
         case WUEPS_PID_GMM  :
            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "MM-->GMM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintGmmMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        case WUEPS_PID_MM  :
            NAS_COMM_nsprintf(pcBuff,
                                usTotalLen,
                                "LMM-->MM\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintMmMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

         case WUEPS_PID_SMS  :
            NAS_COMM_nsprintf(pcBuff,
                                 usTotalLen,
                                 "LMM-->SMS\t",
                                &ilOutPutLenHead);
            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = NAS_LMM_PUBM_PrintSmsMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;


        default:
            NAS_LMM_PUBM_LOG2_WARN("NAS_LMM_PUBM_PrintSendMsg,Invalid Pid, MsgId: ",
                                  pstMsg->ulReceiverPid,
                                  pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_WARNING2(NAS_LMM_PUBM_PrintSendMsg_ENUM
,LNAS_FUNCTION_LABEL2,
                                  pstMsg->ulReceiverPid,
                                  pstMsg->ulMsgName);
            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        NAS_LMM_PUBM_LOG2_WARN("NAS_LMM_PUBM_PrintSendMsg, print return zero length. ReceiverPid, MsgId: ",
                              pstMsg->ulReceiverPid,
                              pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING2(NAS_LMM_PUBM_PrintSendMsg_ENUM
,LNAS_FUNCTION_LABEL3,
                              pstMsg->ulReceiverPid,
                              pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff,usTotalLen);


    /*打印当前安全上下文状态和空口消息原始码流*/
    pMmPidMsg = (NAS_LMM_PID_MSG_STRU *)pstMsg;
    NAS_LMM_PUBM_LOG_NORM("=============OUT MSG CONTENT is :====================");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PUBM_PrintSendMsg_ENUM
,LNAS_FUNCTION_LABEL4);
    NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                     (VOS_UINT8 *)pMmPidMsg,
                                     (pMmPidMsg->ulLength + NAS_EMM_LEN_VOS_MSG_HEADER));
    NAS_LMM_PUBM_LOG_NORM("====================================================");

    return ;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintCnMsg
 Description     : 打印CN消息
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   enMsgId  -- NAS_EMM_CN_MSG_TYPE_ENUM_UINT8
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintCnMsg(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8          enMsgId )
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMmCnMsgNum;
    VOS_INT32                           ilOutPutLen = 0;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulMmCnMsgNum = sizeof(g_astMmCnMsgArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulMmCnMsgNum; ulLoop++)
    {
        if (g_astMmCnMsgArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulMmCnMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usOffset,
                    (VOS_CHAR *)(g_astMmCnMsgArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
    }
    else
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS ESM MSG_TYPE: ",
                              enMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PUBM_PrintCnMsg_ENUM,LNAS_FUNCTION_LABEL1,
                              enMsgId);
    }

    return ilOutPutLen;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_PrintData
 Description     : 打印CN消息携带的数据
 Input           : pcBuff   -- Formatted buffer
                   usOffset -- Offset
                   pstMsg   -- LRRC_LNAS_MSG_STRU
 Output          : None
 Return          : The number of bytes that have been stored in the output buffer pcBuff
                   If the input parameter is erroneous, the return value will be 0.

 History         :
    1.lining 00141619      2008-10-24  Draft Enact

*****************************************************************************/
VOS_INT32   NAS_LMM_PUBM_PrintData(
                    VOS_CHAR                                *pcBuff,
                    VOS_UINT16                              usOffset,
                    LRRC_LNAS_MSG_STRU                        *pstMsg )
{
    VOS_UINT16                          usTotalLen          = usOffset;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usLoop;
/*    VOS_UINT16                          usLineNo            = 1;*/
    VOS_UINT32                          usDataLen           = pstMsg->ulNasMsgSize;
    VOS_UINT8                           *pCnMsgData         = pstMsg->aucNasMsg;
    VOS_UINT8                           ucCnMsgData;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    /* 打印数据, 一行最多10个字节 */
    for (usLoop = 0; usLoop < usDataLen; usLoop++)
    {
        /* 每行结束时打印行号 */
        if ( (0 != usLoop) && (0 == (usLoop%NAS_COMM_PRINT_MAX_BYTES_PER_LINE)) )
        {
            if(usTotalLen<NAS_COMM_PRINT_BUFF_LEN)
            {
                pcBuff[usTotalLen] = '\n';
                usTotalLen++;
            }

        }

        ucCnMsgData = pCnMsgData[usLoop];
        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "%02x ",
                               ucCnMsgData,
                               &ilOutPutLen);
        if ( 0 == ilOutPutLen )
        {
            NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PUBM_PrintData, Print data exception.");
            TLPS_PRINT2LAYER_WARNING(NAS_LMM_PUBM_PrintData_ENUM,LNAS_FUNCTION_LABEL1);
            return 0;

        }
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }

    return (usTotalLen - usOffset);
}
/*lint +e961*/
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

