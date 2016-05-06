


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmcMain.h"
#include  "NasEmmcPublic.h"
#include  "NasEmmcRcvMsg.h"

/*lint -e767*/
#define    THIS_FILE_ID           PS_FILE_ID_NASEMMCMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMCMAIN_C
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
  3 Function
*****************************************************************************/
static NAS_EMMC_COMM_ACT_STRU                     g_astEmmcRsvMsgProcMap[] =
{
    /* MM_MSG_TYPE_ENUM_UINT32          NAS_LMM_COMM_ACTION_FUN */

    /*========== MMC_MSG ==========*/
    {ID_MMC_LMM_PLMN_SRCH_REQ                  ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcPlmnSrchReq                  },
    {ID_MMC_LMM_EPLMN_NOTIFY_REQ               ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcEplmnNotifyReq               },
    {ID_MMC_LMM_STOP_PLMN_SRCH_REQ             ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcStopSrchReq                  },
    {ID_MMC_LMM_USER_PLMN_END_NOTIFY           ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcUserPlmnEndNotify            },
    {ID_MMC_LMM_WCDMA_SYS_INFO_IND             ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcUmtsSysInfoInd                 },
    {ID_MMC_LMM_GSM_SYS_INFO_IND               ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcGsmSysInfoInd                 },
    {ID_MMC_LMM_BG_PLMN_SEARCH_REQ             ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcBgPlmnSearchReq              },
    {ID_MMC_LMM_STOP_BG_PLMN_SEARCH_REQ        ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcStopBgPlmnSearchReq          },
    {ID_MMC_LMM_CELL_SELECTION_CTRL_REQ        ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcCellSelectionReq             },
    {ID_MMC_LMM_LTE_SYS_INFO_IND               ,  WUEPS_PID_MMC,      NAS_LMM_PreProcMmcLteSysInfoInd             },

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {ID_MMC_LMM_BG_SEARCH_HRPD_REQ             ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcBgSearchHrpdReq              },
    {ID_MMC_LMM_STOP_BG_SEARCH_HRPD_REQ        ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcStopBgSearchHrpdReq          },
    #endif
    #if (FEATURE_ON == FEATURE_CSG)
    {ID_MMC_LMM_CSG_LIST_SEARCH_REQ            ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcCsgListSearchReq             },
    {ID_MMC_LMM_CSG_WHITE_LIST_NOTIFY          ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcCsgWhiteListNotify           },
    {ID_MMC_LMM_CSG_BG_SEARCH_REQ              ,  WUEPS_PID_MMC,      NAS_EMMC_RcvMmcCsgBgPlmnSearchReq           },
    #endif
    /*========== EMM_MSG ==========*/
    {ID_EMMC_EMM_START_REQ                     ,  PS_PID_MM    ,      NAS_EMMC_RcvEmmStartReq                     },
    {ID_EMMC_EMM_STOP_REQ                      ,  PS_PID_MM    ,      NAS_EMMC_RcvEmmStopReq                      },

    /*========== LRRC_MSG ==========*/
    {ID_LRRC_LMM_SEARCHED_PLMN_INFO_IND        ,  PS_PID_ERRC  ,      NAS_EMMC_RcvRrcSearchPlmnInfoInd            },

    {ID_LRRC_LMM_PLMN_SEARCH_CNF               ,  PS_PID_ERRC  ,      NAS_EMMC_RcvRrcPlmnSrchCnf                  },
    {ID_LRRC_LMM_SYS_INFO_IND                  ,  PS_PID_ERRC  ,      NAS_EMMC_RcvRrcSysInfoInd                   },
    {ID_LRRC_LMM_PLMN_SEARCH_STOP_CNF          ,  PS_PID_ERRC  ,      NAS_EMMC_RcvRrcPlmnSrchStopCnf              },
    {ID_LRRC_LMM_AREA_LOST_IND                 ,  PS_PID_ERRC  ,      NAS_EMMC_RcvRrcAreaLostInd                  },
    {ID_LRRC_LMM_BG_PLMN_SEARCH_CNF            ,  PS_PID_ERMM  ,      NAS_EMMC_RcvRrcBgPlmnSearchCnf              },
    {ID_LRRC_LMM_BG_PLMN_SEARCH_STOP_CNF       ,  PS_PID_ERMM  ,      NAS_EMMC_RcvRrcBgPlmnSearchStopCnf          },
    {ID_LRRC_LMM_NOT_CAMP_ON_IND               ,  PS_PID_ERRC  ,      NAS_EMMC_RcvRrcNotCampOnInd                 },
    #if (FEATURE_ON == FEATURE_CSG)
    {ID_LRRC_LMM_CSG_BG_SEARCH_CNF             ,  PS_PID_ERRC  ,      NAS_EMMC_RcvRrcCsgBgPlmnSearchCnf           },
    {ID_LRRC_LMM_CSG_LIST_SEARCH_CNF           ,  PS_PID_ERRC  ,      NAS_EMMC_RcvRrcCsgListSrchCnf               },
    {ID_LRRC_LMM_CSG_ID_HOME_NODEB_NAME_IND    ,  PS_PID_ERRC  ,      NAS_EMMC_RcvRrcCsgIdHomeNodeBNameInd        },
    #endif
    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {ID_LRRC_LMM_BG_SEARCH_HRPD_CNF            ,  PS_PID_ERMM  ,      NAS_EMMC_RcvRrcBgSearchHrpdCnf              },
    {ID_LRRC_LMM_BG_SEARCH_HRPD_STOP_CNF       ,  PS_PID_ERMM  ,      NAS_EMMC_RcvRrcBgSearchHrpdStopCnf          },
    #endif

    /*========== TIMER_MSG ==========*/
    {TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER,  VOS_PID_TIMER,      NAS_EMMC_ProcTimerMsgWaitPlmnSrchcnfTimerExp},

};



static VOS_UINT32   g_astEmmcRsvMsgProcMapNum
        = sizeof(g_astEmmcRsvMsgProcMap)/sizeof(NAS_LMM_COMM_ACT_STRU);



/*lint -e960*/
VOS_UINT32  NAS_EMMC_MsgDistr( MsgBlock *pMsg )
{

    VOS_UINT32                          ulRet       = NAS_LMM_MSG_DISCARD;
    NAS_EMMC_COMM_ACTION_FUN            pActFun     = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulMsgId     = NAS_EMM_NULL;
    PS_MSG_HEADER_STRU                 *pHeader     = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pMsg;
    NAS_EMMC_GetNameFromMsg(ulMsgId, pMsg);

    pActFun = NAS_EMMC_CommFindFun(     (NAS_EMMC_COMM_ACT_STRU *)g_astEmmcRsvMsgProcMap,
                                        g_astEmmcRsvMsgProcMapNum,
                                        ulMsgId,
                                        pHeader->ulSenderPid);
    if (NAS_EMMC_NULL_PTR != pActFun)
    {
        /* 若这里找到了，就在这里执行 */
        ulRet = (*pActFun)(pMsg);
    }

    return ulRet;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_ProcTimerMsgWaitPlmnSrchcnfTIMERExp
 Description     : 等待PlmnSrchcnf超时的处理
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1. wangchen 00209181     2012-05-28

*****************************************************************************/
VOS_UINT32 NAS_EMMC_ProcTimerMsgWaitPlmnSrchcnfTimerExp(MsgBlock *pMsg)
{
    /*打印进入该函数*/
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_ProcTimerMsgWaitPlmnSrchcnfTimerExp entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcTimerMsgWaitPlmnSrchcnfTimerExp_ENUM
,LNAS_ENTRY);

    (VOS_VOID)pMsg;

    NAS_EMMC_SetPlmnSrchFlag(NAS_EMM_PLMN_SRCH_FLAG_INVALID);

    return NAS_LMM_MSG_HANDLED;
}


VOS_VOID  NAS_EMMC_Init(VOS_VOID )
{
    /*打印进入该函数*/
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC                          START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_Init_ENUM
,LNAS_ENTRY);

    /*初始化EMMC全局变量*/
    /*NAS_LMM_MEM_SET_S(NAS_EMMC_GetEmmcInfoAddr(),
                        sizeof(NAS_EMMC_GLOBAL_STRU),
                        (VOS_CHAR)0xff,
                        sizeof(NAS_EMMC_GLOBAL_STRU));*/

    NAS_LMM_MEM_SET_S(  NAS_EMMC_GetEmmcInfoAddr(),
                        sizeof(NAS_EMMC_GLOBAL_STRU),
                        0,
                        sizeof(NAS_EMMC_GLOBAL_STRU));

    /* s00265702  为RRC增加保存GU系统消息  begin */
    /*初始化保存GU消息的全局变量，并设置PLMN信息为无效值 */
    
    NAS_LMM_MEM_SET_S(  NAS_EMMC_GetGuSysInfoAddr(),
                        sizeof(NAS_EMMC_GU_SYS_INFO_STRU),
                        0,
                        sizeof(NAS_EMMC_GU_SYS_INFO_STRU));
    
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[0] = 0xFF;
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[1] = 0xFF;
    NAS_EMMC_GetGuSysInfoPlmnAddr()->aucPlmnId[2] = 0xFF;
    /* s00265702  为RRC增加保存GU系统消息  end */

    return;
}
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif






