/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SmMain.c
  Description  : SM的入口，初始化及消息分发函数
  Function List:
              NAS_SM_FillPDPContextInfo
              NAS_SM_RestoreContextData
              NAS_SM_Restore_SmEntity
              NAS_SM_Restore_SmPdpAddrApn
              NAS_SM_SndOutsideContextData
              Sm_FillQosInfo
              SM_GmmMsgDistr
              SM_Init
              SM_MemCmp
              SM_NwActProtectTimerExpire
              SM_NwModifyProtectTimerExpire
              Sm_OmQuery
              Sm_PowerOff
              SM_RabmMsgDistr
              SM_RcvStatusMsg
              SM_RcvTimerMsgDistr
              SM_RegisterProtectTimerExpire
              SM_ReportN2MOtaMsg
              SM_T3380Expire
              SM_T3381Expire
              SM_T3390Expire
              SM_TafMsgDistr
              Sm_TaskEntry
              SM_TimerStart
              SM_TimerStop
              WuepsSmPidInit
  History:
      1.   张志勇       2003.12.08   新规作成
      2.   h41410  2005.10.19  打印全局数据结构 问题单A32D00636
      3.   added by h41410 2005-10-19 for A32D00636
      4.   2006-04-14 delete by h41410 for A32d03181
      5.   2006-8-11 changed by f49086  for A32D04825
      6.   Date        : 2006-09-14
           Author      : l47619
           Modification: 根据问题单新增:A32D05600
      7.   Date        : 2006-11-25
           Author      : l47619
           Modification: 根据问题单新增:A32D07646
      8.   L47619 2007.10.27   A32D13038
      9.日    期   : 2010年02月26日
        作    者   : z00163274
        修改内容   : 增加PS域可维可测功能
*******************************************************************************/
#include "SmInclude.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasSmMultiMode.h"
#endif
#include "NVIM_Interface.h"
#include "MnComm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SM_MAIN_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/


VOS_UINT8      g_ucSmSystemAppConfigAddr;

/* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
VOS_UINT8      g_ucSmTimerFiveExpireFlag = VOS_FALSE;
/* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

NAS_SM_GMM_ERR_CODE_MAP_STRU            g_astNasSmGmmErrCodeMapTbl[] =
{
    { SM_TAF_CAUSE_GMM_GPRS_NOT_SUPPORT,                    GMM_SM_CAUSE_GPRS_NOT_SUPPORT               },
    { SM_TAF_CAUSE_GMM_ATTACH_MAX_TIMES,                    GMM_SM_CAUSE_ATTACH_MAX_TIMES               },
    { SM_TAF_CAUSE_GMM_FORBID_LA,                           GMM_SM_CAUSE_FORBID_LA                      },
    { SM_TAF_CAUSE_GMM_AUTHENTICATION_FAIL,                 GMM_SM_CAUSE_AUTHENTICATION_FAIL            },
    { SM_TAF_CAUSE_GMM_AUTHENTICATION_REJ,                  GMM_SM_CAUSE_AUTHENTICATION_REJ             },
    { SM_TAF_CAUSE_GMM_PS_DETACH,                           GMM_SM_CAUSE_PS_DETACH                      },
    { SM_TAF_CAUSE_GMM_RRC_EST_FAIL,                        GMM_SM_CAUSE_RRC_EST_FAIL                   },
    { SM_TAF_CAUSE_GMM_ACCESS_BARRED,                       GMM_SM_CAUSE_ACCESS_BARRED                  },
    { SM_TAF_CAUSE_GMM_SIM_PS_DOMAIN_REG_INVALID,           GMM_SM_CAUSE_SIM_PS_DOMAIN_REG_INVALID      },
    { SM_TAF_CAUSE_GMM_T3310_EXPIRED,                       GMM_SM_CAUSE_T3310_EXPIRED                  },
    { SM_TAF_CAUSE_GMM_T3317_EXPIRED,                       GMM_SM_CAUSE_T3317_EXPIRED                  },
    { SM_TAF_CAUSE_GMM_TIMER_SIGNALING_PROTECT_EXPIRED,     GMM_SM_CAUSE_TIMER_SIGNALING_PROTECT_EXPIRED},
    { SM_TAF_CAUSE_GMM_STARTUP,                             GMM_SM_CAUSE_STARTUP                        },
    { SM_TAF_CAUSE_GMM_NULL,                                GMM_SM_CAUSE_NULL                           },
    { SM_TAF_CAUSE_GMM_RESET,                               GMM_SM_CAUSE_GMM_RESET                      },
    { SM_TAF_CAUSE_GMM_RAU_ACCEPT,                          GMM_SM_CAUSE_RAU_ACCEPT                     },
    { SM_TAF_CAUSE_GMM_SERVICE_ACCEPT,                      GMM_SM_CAUSE_SERVICE_ACCEPT                 },
    { SM_TAF_CAUSE_GMM_UNKNOWN,                             GMM_SM_CAUSE_UNKNOWN                        },

    { SM_TAF_CAUSE_GMM_NW_IMSI_UNKNOWN_IN_HLR,              GMM_SM_CAUSE_IMSI_UNKNOWN_IN_HLR            },
    { SM_TAF_CAUSE_GMM_NW_ILLEGAL_MS,                       GMM_SM_CAUSE_ILLEGAL_MS                     },
    { SM_TAF_CAUSE_GMM_NW_IMSI_NOT_ACCEPTED,                GMM_SM_CAUSE_IMSI_NOT_ACCEPTED              },
    { SM_TAF_CAUSE_GMM_NW_ILLEGAL_ME,                       GMM_SM_CAUSE_ILLEGAL_ME                     },
    { SM_TAF_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW,              GMM_SM_CAUSE_GPRS_SERV_NOT_ALLOW            },
    { SM_TAF_CAUSE_GMM_NW_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW, GMM_SM_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW },
    { SM_TAF_CAUSE_GMM_NW_MS_ID_NOT_DERIVED,                 GMM_SM_CAUSE_MS_ID_NOT_DERIVED             },
    { SM_TAF_CAUSE_GMM_NW_IMPLICIT_DETACHED,                 GMM_SM_CAUSE_IMPLICIT_DETACHED             },
    { SM_TAF_CAUSE_GMM_NW_PLMN_NOT_ALLOW,                    GMM_SM_CAUSE_PLMN_NOT_ALLOW                },
    { SM_TAF_CAUSE_GMM_NW_LA_NOT_ALLOW,                      GMM_SM_CAUSE_LA_NOT_ALLOW                  },
    { SM_TAF_CAUSE_GMM_NW_ROAMING_NOT_ALLOW_IN_LA,           GMM_SM_CAUSE_ROAMING_NOT_ALLOW_IN_LA       },
    { SM_TAF_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW_IN_PLMN,       GMM_SM_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN   },
    { SM_TAF_CAUSE_GMM_NW_NO_SUITABL_CELL,                   GMM_SM_CAUSE_NO_SUITABL_CELL               },
    { SM_TAF_CAUSE_GMM_NW_MSC_UNREACHABLE,                   GMM_SM_CAUSE_MSC_UNREACHABLE               },
    { SM_TAF_CAUSE_GMM_NW_NETWORK_FAILURE,                   GMM_SM_CAUSE_NETWORK_FAILURE               },
    { SM_TAF_CAUSE_GMM_NW_MAC_FAILURE,                       GMM_SM_CAUSE_MAC_FAILURE                   },
    { SM_TAF_CAUSE_GMM_NW_SYNCH_FAILURE,                     GMM_SM_CAUSE_SYNCH_FAILURE                 },
    { SM_TAF_CAUSE_GMM_NW_PROCEDURE_CONGESTION,              GMM_SM_CAUSE_PROCEDURE_CONGESTION          },
    { SM_TAF_CAUSE_GMM_NW_GSM_AUT_UNACCEPTABLE,              GMM_SM_CAUSE_GSM_AUT_UNACCEPTABLE          },
    { SM_TAF_CAUSE_GMM_NW_NOT_AUTHORIZED_FOR_THIS_CSG,       GMM_SM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG   },
    { SM_TAF_CAUSE_GMM_NW_NO_PDP_CONTEXT_ACT,                GMM_SM_CAUSE_NO_PDP_CONTEXT_ACT            },
    { SM_TAF_CAUSE_GMM_NW_RETRY_UPON_ENTRY_CELL,             GMM_SM_CAUSE_RETRY_UPON_ENTRY_CELL         },
    { SM_TAF_CAUSE_GMM_NW_SEMANTICALLY_INCORRECT_MSG,        GMM_SM_CAUSE_SEMANTICALLY_INCORRECT_MSG    },
    { SM_TAF_CAUSE_GMM_NW_INVALID_MANDATORY_INF,             GMM_SM_CAUSE_INVALID_MANDATORY_INF         },
    { SM_TAF_CAUSE_GMM_NW_MSG_NONEXIST_NOTIMPLEMENTE,        GMM_SM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE    },
    { SM_TAF_CAUSE_GMM_NW_MSG_TYPE_NOT_COMPATIBLE,           GMM_SM_CAUSE_MSG_TYPE_NOT_COMPATIBLE       },
    { SM_TAF_CAUSE_GMM_NW_IE_NONEXIST_NOTIMPLEMENTED,        GMM_SM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED    },
    { SM_TAF_CAUSE_GMM_NW_CONDITIONAL_IE_ERROR,              GMM_SM_CAUSE_CONDITIONAL_IE_ERROR          },
    { SM_TAF_CAUSE_GMM_NW_MSG_NOT_COMPATIBLE,                GMM_SM_CAUSE_MSG_NOT_COMPATIBLE            },
    { SM_TAF_CAUSE_GMM_NW_PROTOCOL_ERROR,                    GMM_SM_CAUSE_PROTOCOL_ERROR                }
};

NAS_MNTN_SM_INFO_STRU                   g_stNasMntnErrorlogSm;

/*******************************************************************************
  Module:      SM_ReportN2MOtaMsg
  Function:    在trace中勾取SM的空口消息
  Input:       VOS_UINT8       ucMsgType   SM msg type
               NAS_MSG_STRU*   pNasMsg     SM空口消息
  NOTE:
  Return:      VOS_VOID
  History:
      1. 鲁琳    2009.07.11   新规作成
*******************************************************************************/
VOS_VOID SM_ReportN2MOtaMsg(VOS_UINT8 ucMsgType, NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_ReportN2MOtaMsg:NORMAL: msg type is ", ucMsgType);

    switch(ucMsgType)
    {
        case SM_REQ_PDP_CONTEXT_ACT:
            usNasOtaMsyId = NAS_OTA_MSG_REQ_PDP_CONTEXT_ACT;
            break;

        case SM_ACT_PDP_CONTEXT_ACC:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_PDP_CONTEXT_ACC;
            break;

        case SM_ACT_PDP_CONTEXT_REJ:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_PDP_CONTEXT_REJ;
            break;

        case SM_ACT_SEC_PDP_CONTEXT_ACC:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_SEC_PDP_CONTEXT_ACC;
            break;

        case SM_ACT_SEC_PDP_CONTEXT_REJ:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_SEC_PDP_CONTEXT_REJ;
            break;

        case SM_MOD_PDP_CONTEXT_REQ_N2M:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_REQ_N2M;
            break;

        case SM_MOD_PDP_CONTEXT_ACC_N2M:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_ACC_N2M;
            break;

        case SM_MOD_PDP_CONTEXT_REJ:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_REJ;
            break;

        case SM_DEACT_PDP_CONTEXT_REQ:
            usNasOtaMsyId = NAS_OTA_MSG_DEACT_PDP_CONTEXT_NET_REQ;
            break;

        case SM_DEACT_PDP_CONTEXT_ACC:
            usNasOtaMsyId = NAS_OTA_MSG_DEACT_PDP_CONTEXT_ACC;
            break;

        case SM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_SM_STATUS;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ReportN2MOtaMsg:WARNING: invalid msg type!");
            /*不属于SM的空口消息，不在trace中显示*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_SM, usNasOtaMsyId, NAS_OTA_DIRECTION_DOWN, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
}


#ifdef __PS_WIN32_RECUR__
/*****************************************************************************
 函 数 名  : NAS_SM_Restore_SmEntity
 功能描述  : 恢复SM全局变量。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年03月16日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : SM保存的QOS和APN由动态内存改为静态数组
*****************************************************************************/
VOS_VOID NAS_SM_Restore_SmEntity(SM_ENTITY_STRU  *pSmEntity)
{
    int i;

    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        pSmEntity->aHoldMsg[i].pHoldRcvMsg = g_SmEntity.aHoldMsg[i].pHoldRcvMsg;
        pSmEntity->aPdpCntxtList[i].pHoldSndMsg = g_SmEntity.aPdpCntxtList[i].pHoldSndMsg;
    }

    PS_MEM_CPY(&g_SmEntity, pSmEntity, sizeof(SM_ENTITY_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_Restore_SmPdpAddrApn
 功能描述  : 恢复SM全局变量。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年03月16日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : SM保存的QOS和APN由动态内存改为静态数组
*****************************************************************************/
VOS_VOID NAS_SM_Restore_SmPdpAddrApn(SM_PDP_ADDR_AND_APN_STRU  *pSmPdpAddrApn)
{
    PS_MEM_CPY(&g_SmPdpAddrApn, pSmPdpAddrApn, sizeof(SM_PDP_ADDR_AND_APN_STRU));

    return;
}


/*****************************************************************************
 函 数 名  : NAS_SM_RestoreContextData
 功能描述  : 恢复SM全局变量。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年03月16日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_SM_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_SM_SDT_MSG_ST                      *pRcvMsgCB;
    NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_SM_SDT_MSG_ST *)pMsg;

    if (EVT_NAS_SM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        g_ucTiExt = pstOutsideCtx->pc_g_ucTiExt;
        PS_MEM_CPY(g_TiMapToNsapi, pstOutsideCtx->pc_g_TiMapToNsapi, 256);
        PS_MEM_CPY(g_CrMapToNsapi, pstOutsideCtx->pc_g_CrMapToNsapi, 256);
        PS_MEM_CPY(g_aucSapi, pstOutsideCtx->pc_g_aucSapi, (SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET)*2);

        NAS_SM_Restore_SmEntity(&pstOutsideCtx->pc_g_SmEntity);
        NAS_SM_Restore_SmPdpAddrApn(&pstOutsideCtx->pc_g_SmPdpAddrApn);

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM: NAS_SM_RestoreContextData - data is restored.");
    }
    return SM_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_SM_SndOutsideContextData
 功能描述  : 把SM外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年03月16日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_SM_SndOutsideContextData()
{
    NAS_SM_SDT_MSG_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_SM_SDT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_SM, sizeof(NAS_SM_SDT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_SM_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    pstOutsideCtx->pc_g_ucTiExt = g_ucTiExt;
    PS_MEM_CPY(pstOutsideCtx->pc_g_TiMapToNsapi, g_TiMapToNsapi, 256);
    PS_MEM_CPY(pstOutsideCtx->pc_g_CrMapToNsapi, g_CrMapToNsapi, 256);
    PS_MEM_CPY(pstOutsideCtx->pc_g_aucSapi, g_aucSapi, (SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET)*2);

    PS_MEM_CPY(&pstOutsideCtx->pc_g_SmEntity, &g_SmEntity, sizeof(SM_ENTITY_STRU));
    PS_MEM_CPY(&pstOutsideCtx->pc_g_SmPdpAddrApn, &g_SmPdpAddrApn, sizeof(SM_PDP_ADDR_AND_APN_STRU));

    pSndMsgCB->ulReceiverPid = WUEPS_PID_SM;
    pSndMsgCB->ulSenderPid   = WUEPS_PID_SM;
    pSndMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength      = sizeof(NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST) + 4;
    pSndMsgCB->usMsgID       = EVT_NAS_SM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;
    pSndMsgCB->usReserved    = 0;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_SM, pSndMsgCB);

    return;
}

/***********************************************************************
*  MODULE   : Sm_TaskEntry
*  FUNCTION : SM模块TASK入口处理
*  INPUT    : struct MsgCB* pMsg-----------消息指针
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : 消息指针由DOPRA释放，入口函数不需要释放
*  HISTORY  :
*     1.  张志勇   05-01-28  新规作成
*     2.  张志勇   05-03-08  使用PID进行分发处理
      3.  日    期   : 2011年06月24日
          作    者   : c00173809
          修改内容   : 根据问题单号：DTS2011051202669，SM的T3380,T3390超时消息解析不正确。

************************************************************************/
VOS_VOID Sm_TaskEntry( struct MsgCB* pMsg )
{
    MSG_HEADER_STRU         *pHeader;                                           /* 定义消息头指针                           */
    REL_TIMER_MSG           *pTimer;                                            /* 定义TIMER消息指针                        */

    pHeader = (MSG_HEADER_STRU *) pMsg;                                         /* 获取消息头指针                           */
    pTimer  = (REL_TIMER_MSG *) pMsg;                                           /* 获取TIMER消息指针                        */

    if ( VOS_PID_TIMER == pMsg->ulSenderPid)
    {                                                                       /* 如果是TIMER消息                          */
        SM_RcvTimerMsgDistr( pTimer->ulPara );                              /* TIMER溢出消息分发函数                    */
    }
    else
    {
        switch(pHeader->ulSenderPid)
        {
        case MSP_PID_DIAG_APP_AGENT:
            /*SM_AgentMsgDistr( ( VOS_VOID * )pMsg );*/                         /* AGENT原语分发                            */
            Sm_OmQuery( ( VOS_VOID * )pMsg );
            break;
        case WUEPS_PID_TAF:/*Modified by Jim for prj*/
            NAS_SM_RcvTafMsg( pHeader );                                      /* TAF原语分发                              */
            break;
        case WUEPS_PID_GMM:
            SM_GmmMsgDistr( ( VOS_VOID * )pMsg );                               /* GMM原语分发                              */
            break;
        case WUEPS_PID_RABM:
            SM_RabmMsgDistr( ( VOS_VOID * )pMsg );                              /* RABM原语分发                             */
            break;
        case WUEPS_PID_ADMIN:
            break;
#ifdef __PS_WIN32_RECUR__
        case WUEPS_PID_SM:
            NAS_SM_RestoreContextData(pMsg);
            break;
#endif
        default:
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "LogRecord_Timer_HW:WARNING:SM: SenderPid error!");
            break;
        }
    }

#ifndef __PS_WIN32_RECUR__
    NAS_SM_SndOutsideContextData();
#endif
}

/*****************************************************************************
 函 数 名  : SM_GetSystemAppConfigAddr
 功能描述  : 获取SM模块控制特性的NV的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 控制特性的信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月07日
   作    者   : s62952
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8* SM_GetSystemAppConfigAddr(VOS_VOID)
{
    return &g_ucSmSystemAppConfigAddr;
}

/*****************************************************************************
 函 数 名  : SM_ReadSystemAppConfigNV
 功能描述  : 读取特性控制NV相关信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月18日
    作    者   : s62952
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年05月17日
    作    者   : m00217266
    修改内容   : nv项拆分
*****************************************************************************/
VOS_VOID  SM_ReadSystemAppConfigNV(VOS_VOID)
{
    VOS_UINT8                                      *pucSystemAppConfig;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU                 stSysAppConfig;


    stSysAppConfig.usSysAppConfigType= SYSTEM_APP_BUTT;


    /* 获取控制特性的NV上下文地址 */
    pucSystemAppConfig                  = SM_GetSystemAppConfigAddr();


    /*读取失败按默认值处理 */
    if (VOS_OK != NV_Read(en_NV_Item_System_APP_Config,&stSysAppConfig,sizeof(VOS_UINT16)))
    {
        *pucSystemAppConfig  = SYSTEM_APP_MP;
        return;
    }

    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType)
    {
        *pucSystemAppConfig  = SYSTEM_APP_MP;
    }
    else
    {
        *pucSystemAppConfig  = (VOS_UINT8)stSysAppConfig.usSysAppConfigType;
    }

    return;
}

/*******************************************************************************
  Module:   SM_Init
  Function: Sm的初始化函数
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.12   新规作成
      2.   张志勇  2005.01.05   移植修改
      3.日    期   : 2013年05月18日
        作    者   : l00198894
        修改内容   : Taf&Sm接口优化
      2. 日    期   : 2013年07月222日
        作    者   : j00177245
        修改内容   : 清理编译warning
*******************************************************************************/
VOS_VOID SM_Init()
{
    SM_ENTITY_STRU                     *pstSmEntity     = VOS_NULL_PTR;
    SM_PDP_ADDR_AND_APN_STRU           *pstSmPdpAddrApn = VOS_NULL_PTR;
    VOS_UINT8                          *pucTiMapToNsapi = VOS_NULL_PTR;
    VOS_UINT8                          *pucCrMapToNsapi = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstSmEntity     = NAS_SM_GetSmEntity();
    pstSmPdpAddrApn = NAS_SM_GetSmPdpAddrApn();
    pucTiMapToNsapi = NAS_SM_GetTiMapToNsapi();
    pucCrMapToNsapi = NAS_SM_GetCrMapToNsapi();

    SM_MemSet((VOS_VOID *)pstSmEntity,0, sizeof(SM_ENTITY_STRU));
    SM_MemSet(pstSmPdpAddrApn, 0, sizeof(SM_PDP_ADDR_AND_APN_STRU));
    SM_MemSet(pucTiMapToNsapi, (VOS_CHAR)0xFF, 256);
    SM_MemSet(pucCrMapToNsapi, (VOS_CHAR)0xFF, 256);

    SM_MemSet(&g_stNasMntnErrorlogSm, 0, sizeof(g_stNasMntnErrorlogSm));

    NAS_SM_SetTiExt(SM_FALSE);                                                  /* 初始化TI没有扩展标志                     */

    SM_ReadSystemAppConfigNV();

    /*初始化存放SAPI的数组*/
    for(i = 0; i < (SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET) ; i++)
    {
        NAS_SM_GetSapi(i)[0] = 0;
    }

    /* 初始化SGSN版本信息为"R99及以后版本" */
    NAS_SM_SetSmSgsnVersion(GMMSM_SGSN_RELEASE99_ONWARDS);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_RcvTafMsg
 功能描述  : 处理TAF消息
 输入参数  : MSG_HEADER_STRU                       *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年12月09日
    作    者   : 郑 伟
    修改内容   : 新生成函数

  2.日    期   : 2011年12月20日
    作    者   : A00165503
    修改内容   : PS Project: 增加ID_APS_SM_PDP_ABORT_REQ原语处理

  3.日    期   : 2013年4月23日
    作    者   : L47619
    修改内容   : V9R1 IPv6&TAF/SM接口优化项目修改
*****************************************************************************/
VOS_VOID NAS_SM_RcvTafMsg(
    MSG_HEADER_STRU                    *pMsg
)
{
    switch (pMsg->ulMsgName)
    {
        case ID_SMREG_PDP_ACTIVATE_REQ:
            NAS_SM_RcvTafPdpCnxtActReq((SMREG_PDP_ACTIVATE_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_ACTIVATE_REJ_RSP:
            NAS_SM_RcvTafPdpCnxtActRejRsp((SMREG_PDP_ACTIVATE_REJ_RSP_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_MODIFY_REQ:
            NAS_SM_RcvTafPdpCntxtModifyReq((SMREG_PDP_MODIFY_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_DEACTIVATE_REQ:
            NAS_SM_RcvTafPdpCnxtDeActReq((SMREG_PDP_DEACTIVATE_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_ACTIVATE_SEC_REQ:
            NAS_SM_RcvTafPdpCnxtActSecReq((SMREG_PDP_ACTIVATE_SEC_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_MODIFY_RSP:
            NAS_SM_RcvTafPdpModifyRsp((SMREG_PDP_MODIFY_RSP_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_MODIFY_REJ_RSP:
            NAS_SM_RcvTafPdpModifyRejRsp((SMREG_PDP_MODIFY_REJ_RSP_STRU*)pMsg);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case ID_SMREG_BEARER_ACTIVATE_IND:
            NAS_SM_RcvTafBearerActivateInd((SMREG_BEARER_ACTIVATE_IND_STRU*)pMsg);
            break;

        case ID_SMREG_BEARER_MODIFY_IND:
            NAS_SM_RcvTafBearerModifyInd((SMREG_BEARER_MODIFY_IND_STRU*)pMsg);
            break;

        case ID_SMREG_BEARER_DEACTIVATE_IND:
            NAS_SM_RcvTafBearerDeactivateInd((SMREG_BEARER_DEACTIVATE_IND_STRU*)pMsg);
            break;
#endif
        case ID_SMREG_PDP_ABORT_REQ:
            NAS_SM_RcvTafPdpAbortReq((SMREG_PDP_ABORT_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_LOCAL_DEACTIVATE_REQ:
            NAS_SM_RcvTafPdpLocalDeactivateReq((SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU*)pMsg);
            break;

        default:
            NAS_NORMAL_LOG(WUEPS_PID_SM, "SM_TafMsgDistr:WARNING:SM: Message type non-existent !");
            break;
    }

    return;
}

/*******************************************************************************
  Module:   SM_GmmMsgDistr
  Function: GMM消息分发处理
  Input:    VOS_VOID    *pRcvMsg           收到的消息
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1.   郑 伟   2003.12.11   新规作成
  2.日    期   : 2012年8月25日
    作    者   : m00217266
    修改内容   : 修改接口SM_RcvGmmSmServiceRej，上报原因值
*******************************************************************************/
VOS_VOID SM_GmmMsgDistr(
    VOS_VOID                            *pRcvMsg
)
{
    MSG_HEADER_STRU                     *pstGmmMsg;

    pstGmmMsg = (MSG_HEADER_STRU*)pRcvMsg;

    switch( pstGmmMsg->ulMsgName )
    {
        case GMMSM_ESTABLISH_CNF:
            NAS_NORMAL_LOG(WUEPS_PID_SM, "\n GMM->SM: GMMSM_ESTABLISH_CNF\r");
            SM_RcvGmmSmEstabishCnf ((GMMSM_ESTABLISH_CNF_STRU*)pRcvMsg);
            break;

        case GMMSM_DATA_IND:
            NAS_SM_RcvGmmSmDataInd((GMMSM_DATA_IND_STRU*)pRcvMsg);
            break;

        case GMMSM_STATUS_IND:
            SM_RcvGmmSmStatusInd ((GMMSM_STATUS_IND_STRU*)pRcvMsg);
            break;

        case GMMSM_SERVICE_REJ:
            SM_RcvGmmSmServiceRej((GMMSM_SERVICE_REJ_STRU*)pRcvMsg);

            break;

        case GMMSM_SYS_INFO_IND:
            SM_RcvGmmSysInfoInd((GMMSM_SYS_INFO_IND_STRU *)pRcvMsg);
            break;

        case GMMSM_PDP_STATUS_IND:
            SM_RcvGmmSmPdpStatusInd((GMMSM_PDP_STATUS_IND_STRU *)pRcvMsg);
            break;

        case GMMSM_REL_IND:
            SM_RcvGmmRelInd((GMMSM_REL_IND_STRU *)pRcvMsg);
            break;

        case GMMSM_SIG_CONN_IND:
            NAS_SM_RcvGmmSigConnInd((GMMSM_SIG_CONN_IND_STRU *)pRcvMsg);
            break;

        default:
            NAS_NORMAL_LOG(WUEPS_PID_SM, "SM_GmmMsgDistr:WARNING:NW->SM Message name non-existent!");
            break;
    }

    /* 初始化TI没有扩展标志 */
    g_ucTiExt = SM_FALSE;

    return;
}

/*******************************************************************************
  Module:   SM_RcvStatusMsg
  Function: 接收SM STATUS消息的处理
  Input:    VOS_VOID    *pRcvMsg           收到的消息
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. 郑 伟   2003.12.11   新规作成
  2. 张志勇  2005.01.06   移植修改

  3.日    期   : 2010年10月25日
    作    者   : z00161729
    修改内容   : CS Only情况,PDP去激活后,SM需要通过pdp_deactive_ind消息通知GMM进行detach

  4.日    期   : 2012年01月17日
    作    者   : f00179208
    修改内容   : PS融合项目，UE处于IDLE，pdp激活过程中，网络侧下发SM Status，
                 原因值为Invalid transaction identifier value（#81）UE没有回到IDLE态

  5.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  6.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
  7.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_RcvStatusMsg(GMMSM_DATA_IND_STRU *pGmmDataInd)
{
    VOS_UINT8       ucTi;
    VOS_UINT8       ucSmCause;
    VOS_UINT8       ucCntxtIndex;
    VOS_UINT8       ucAddrIndex;


    if( 0x70 ==(pGmmDataInd->SmMsg.aucNasMsg[0] & 0x70) )
    {
        ucTi = (pGmmDataInd->SmMsg.aucNasMsg[1] & 0x7F)
            | (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x80);                         /* 获取Ti值                                 */
        ucSmCause = pGmmDataInd->SmMsg.aucNasMsg[3];
    }
    else
    {
        ucTi = ((pGmmDataInd->SmMsg.aucNasMsg[0] & 0x70)>>4)
                | (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x80);                     /* 获取Ti值                                 */
        ucSmCause = pGmmDataInd->SmMsg.aucNasMsg[2];

        if (SM_NW2UE_STATUS_CAUSE_TI_INVALID == ucSmCause)
        {   /*若网络发来的状态报告的原因是TI非法*/
            /*在网络发来TI前添加网络发来TI需要的标识*/
            ucTi |= 0x80;
        }
    }

    ucCntxtIndex  = g_TiMapToNsapi[ucTi];                                       /* 根据TI获取ucCntxtIndex                   */
    if( 0xFF == ucCntxtIndex )
    {                                                                           /* 在去激活状态                             */

        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_RcvStatusMsg:WARNING:NW->SM: PdpContext non-existent!");
    }
    else
    {
        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;
        switch( g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {                                                                       /* 消息类型                                 */
        case SM_PDP_ACTIVE_PENDING:
            if ( (TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)                     /* #81 invalid transaction identifier value*/
              || (TAF_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT == ucSmCause) )
            {                                                                   /* #97 "message type non-existent or not im
                                                                                 * plemented".                              */
                SM_ComClearPdpCntxt(ucCntxtIndex);                              /* 释放实体                                 */

                SM_SndTafSmPdpDeActInd(
                      g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                      NAS_SM_MapSmNWCause(ucSmCause),
                      SM_FALSE);
                SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                            /* 通知RABM去激活                           */
                SM_ComClearPdpAddrApn(ucAddrIndex);                                     /* 清除Addr Apn实体                         */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* 状态切换到SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvStatusMsg:NORMAL:SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_INACTIVE");
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;     /* 维护g_CrMapToNsapi                       */
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xff;     /* 维护g_TiMapToNsapi                       */
                NAS_EventReport(WUEPS_PID_SM,
                                NAS_OM_EVENT_PDP_ACTIVE_FAIL,
                                (VOS_VOID *)&(ucSmCause),
                                NAS_OM_EVENT_PDP_ACTIVE_FAIL_LEN);

                /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */
                NAS_SM_SndGmmPdpDeactivatedInd();
            }
            break;
        case SM_PDP_INACTIVE_PENDING:
            if ( (TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)                     /* #81 "invalid transaction identifier value" or #97 "Message type non-existent or not implemented"*/
              || (TAF_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT == ucSmCause) )
            {
                SM_TimerStop(ucCntxtIndex);                                     /* 停止T3390                                */
                SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );  /* 释放备份的消息                           */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                SM_SndTafSmPdpDeActInd(
                  g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                  NAS_SM_MapSmNWCause(ucSmCause),
                  SM_FALSE);
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* 状态切换到SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                    "SM_RcvStatusMsg:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE");

                NAS_SM_SndGmmPdpStatusInd();
                NAS_SM_SndGmmPdpDeactivatedInd();                               /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xff;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;
            }
            break;
        case SM_PDP_MODIFY_PENDING:
            if( TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)
            {                                                                   /* #81 "invalid transaction identifier value" */
                SM_SndRabmSmDeactivateInd (1, &ucCntxtIndex);                   /* 通知RABM去激活Nsapi                      */
                SM_SndTafSmPdpDeActInd(
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                    NAS_SM_MapSmNWCause(ucSmCause),
                    SM_FALSE);
                SM_ComClearPdpCntxt(ucCntxtIndex);
                SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* 状态切换到SM_PDP_INACTIVE                */

                PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                        "SM_RcvStatusMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_INACTIVE");

                NAS_SM_SndGmmPdpStatusInd();
                NAS_SM_SndGmmPdpDeactivatedInd();                               /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */
                g_TiMapToNsapi[ucTi] = 0xFF;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF;
            }
            else
            {                                                                   /* #97,#96                                  */
                SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);    /* 释放备份的消息                           */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                SM_TimerStop(ucCntxtIndex);                                     /* 停止T3381                                */
                SM_SndTafSmPdpModifyRej(
                    NAS_SM_MapSmNWCause(ucSmCause),
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE; /* 状态切换到SM_PDP_ACTIVE                  */

                PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                        "SM_RcvStatusMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
            }
            break;
        case SM_PDP_ACTIVE:
        case SM_PDP_NW_MODIFY:
            break;
        default:
            break;
        }
    }

    NAS_SM_EndSession();

    return;
}

/*******************************************************************************
  Module:   SM_RabmMsgDistr
  Function: RABM 消息分发处理
  Input:    VOS_VOID    *pRcvMsg           收到的消息
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.11   新规作成
*******************************************************************************/
VOS_VOID SM_RabmMsgDistr(
                    VOS_VOID            *pRcvMsg                                    /* 接收到的消息                             */
                    )
{
    MSG_HEADER_STRU     *pNasMsg;                                               /* 定义NAS消息指针                          */

    pNasMsg = (MSG_HEADER_STRU *)pRcvMsg;
    switch(pNasMsg->ulMsgName)
    {                                                                           /* 消息类型                                 */
    case RABMSM_DEACTIVATE_REQ:

        PS_NAS_LOG1(        WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                        "\n RABMSM_DEACTIVATE_REQ: ulNsapi = %ld\r",
            (VOS_INT32)(( (RABMSM_DEACTIVATE_REQ_STRU *)pRcvMsg) -> ulNsapi));

        SM_RcvRabmDeActReq ((RABMSM_DEACTIVATE_REQ_STRU *)pNasMsg);
        break;
    case RABMSM_ACTIVATE_RSP:
        break;
    default:
        break;
    }
    return;
}

/*******************************************************************************
  Module:   SM_RcvTimerMsgDistr
  Function: Timer消息的分发处理
  Input:    VOS_UINT8   ucTimerId
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.09   新规作成
*******************************************************************************/
VOS_VOID SM_RcvTimerMsgDistr(
                        VOS_UINT32            ulTimerId                              /* Timer Id                                 */
                        )
{
    if( SM_REGISTER_TIMER_ID == ulTimerId )
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO:SM TimerExpire: RegisterProtectTimer");

        SM_RegisterProtectTimerExpire((VOS_UINT8)ulTimerId);
    }
    else
    {
        switch(g_SmEntity.aPdpCntxtList[ulTimerId].TimerInfo.ucTimerType)
        {
        case SM_TIMER_TYPE_T3380:
            if( SM_PDP_ACTIVE_PENDING ==
                g_SmEntity.aPdpCntxtList[ulTimerId].ucState )
            {
                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO:SM TimerExpire(EntityIndex): T3380", (VOS_INT32)ulTimerId);

                SM_T3380Expire((VOS_UINT8)ulTimerId);
            }
            break;
        case SM_TIMER_TYPE_T3381:
            if( SM_PDP_MODIFY_PENDING ==
                g_SmEntity.aPdpCntxtList[ulTimerId].ucState )
            {
                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO:SM TimerExpire(EntityIndex): T3381", (VOS_INT32)ulTimerId);

                SM_T3381Expire ((VOS_UINT8)ulTimerId);
            }
            break;
        case SM_TIMER_TYPE_T3390:
            if( SM_PDP_INACTIVE_PENDING ==
                g_SmEntity.aPdpCntxtList[ulTimerId].ucState)
            {
                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO: SM TimerExpire(EntityIndex): T3390", (VOS_INT32)ulTimerId);

                SM_T3390Expire ((VOS_UINT8)ulTimerId);
            }
            break;
        case SM_TIMER_TYPE_T0003:
            SM_TimerStop((VOS_UINT8)ulTimerId);                                     /* 停止Timer                                */
            if( SM_PDP_NW_MODIFY
                == g_SmEntity.aPdpCntxtList[ulTimerId].ucState )
            {
                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO: SM TimerExpire(EntityIndex): T0003", (VOS_INT32)ulTimerId);

                SM_NwModifyProtectTimerExpire((VOS_UINT8)ulTimerId);
            }
            break;
        default:
            break;
        }
    }
    return;
}

/*******************************************************************************
  Module:   SM_T3380Expire
  Function: T3380超时的处理
  Input:    VOS_UINT8          ucCntxtIndex     PDP context的索引
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1.   郑 伟   2003.12.09   新规作成

  2. 日    期   : 2010年10月22日
     作    者   : z00161729
     修改内容   : 问题单:DTS2010102003076,E5 GCF测试要求pdp激活达到最大次数后,如果网侧没响应则主动释放链路
                  SM需要给GMM发送pdp deactivated ind 消息

  3. 日    期   : 2013年04月10日
     作    者   : Y00213812
     修改内容   : DTS2013040902281,增加可维可测

  4. 日    期   : 2013年06月30日
     作    者   : m00217266
     修改内容   : DCM LOGGER项目定时器事件上报

  5.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  6.日    期   : 2014年12月17日
    作    者   : A00165503
    修改内容   : DTS2014112107909: 每次信令流程发起时, 需要申请新的资源

  7.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
  8.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_T3380Expire(VOS_UINT8 ucCntxtIndex)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCntxt = VOS_NULL_PTR;
    GMMSM_DATA_REQ_STRU                *pstHoldMsg  = VOS_NULL_PTR;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucCause;

    /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
    NAS_TIMER_EventReport(SM_TIMER_TYPE_T3380, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);
    /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

    pstPdpCntxt = NAS_SM_GetPdpCtxInfoAddr(ucCntxtIndex);
    pstHoldMsg  = (GMMSM_DATA_REQ_STRU *)pstPdpCntxt->pHoldSndMsg;

    ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

    g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes++;           /* 超时的次数加1                            */

    if( SM_MAX_EXPIRE_TIMES
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes)
    {                                                                           /* 达到最大的次数(SM_MAX_EXPIRE_TIMES)      */
        NAS_MNTN_RecordPdpActiveFail(NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_TIMEOUT,
                                     ucCntxtIndex,
                                     NAS_MNTN_SM_REJ_CAUSE_INVALID,
                                     g_SmEntity.ucRegisterFlg);

        if( SM_ACT_PDP_CONTEXT_REQ
            == *( (pstHoldMsg->SmMsg.aucNasMsg) + sizeof(VOS_UINT8)) )
        {                                                                       /* PDP context activation过程               */
            SM_SndTafSmPdpActivateRej(
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                SM_TAF_CAUSE_SM_MAX_TIME_OUT,
                VOS_NULL_PTR );
        }
        else if( SM_ACT_SEC_PDP_CONTEXT_REQ
            == *( (pstHoldMsg->SmMsg.aucNasMsg) + sizeof(VOS_UINT8)) )
        {                                                                       /* Secondary PDP context activation过程     */
            SM_SndTafSmPdpActSecRej(
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
               SM_TAF_CAUSE_SM_MAX_TIME_OUT);
        }
        else
        {
        }

        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
        /* T3380 5次超时，停止定时器时不发送定时器停止事件 */
        g_ucSmTimerFiveExpireFlag = VOS_TRUE;
        SM_ComClearPdpCntxt(ucCntxtIndex);                                      /* 释放实体                                 */
        g_ucSmTimerFiveExpireFlag = VOS_FALSE;
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

        SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                            /* 通知RABM去激活                           */
        SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* 状态切换到SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_T3380Expire:NORMAL:SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_INACTIV");
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr]=0xff;       /* 维护g_CrMapToNsapi                       */
        g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi]=0xff;       /* 维护g_TiMapToNsapi                       */

        /* 5次激活超时，通知GMM终止缓存处理流程 */
        NAS_SM_SndGmmPdpStatusInd();
        NAS_SM_SndGmmPdpDeactivatedInd();                                       /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */

        NAS_SM_EndSession();

        ucCause = NAS_OM_SM_REJ_CAUSE_TIMER_TIMEOUT;
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL_LEN);
    }
    else
    {
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
        NAS_TIMER_EventReport(SM_TIMER_TYPE_T3380, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_START);
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

        NAS_SM_BeginSession();

        /* 发送缓存的消息 */
        NAS_SM_SndPdpCntxtHoldMsg(pstPdpCntxt);

        /* 可维可测消息 */
        SM_ReportM2NOtaMsg(&(pstHoldMsg->SmMsg));
    }

    return;
}

/*******************************************************************************
  Module:   SM_T3381Expire
  Function: T3381超时的处理
  Input:    VOS_UINT8          ucCntxtIndex     PDP context的索引
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. 郑 伟   2003.12.09   新规作成

  2. 日    期   : 2013年06月30日
     作    者   : m00217266
     修改内容   : DCM LOGGER项目定时器事件上报

  3.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  4.日    期   : 2014年12月17日
    作    者   : A00165503
    修改内容   : DTS2014112107909: 每次信令流程发起时, 需要申请新的资源
  5.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_T3381Expire(VOS_UINT8 ucCntxtIndex)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCntxt = VOS_NULL_PTR;
    GMMSM_DATA_REQ_STRU                *pstHoldMsg  = VOS_NULL_PTR;
    VOS_UINT8                           ucCause;

    /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
    NAS_TIMER_EventReport(SM_TIMER_TYPE_T3381, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);
    /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

    pstPdpCntxt = NAS_SM_GetPdpCtxInfoAddr(ucCntxtIndex);
    pstHoldMsg  = (GMMSM_DATA_REQ_STRU *)pstPdpCntxt->pHoldSndMsg;

    g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes++;           /* 超时的次数加1                            */

    if( SM_MAX_EXPIRE_TIMES
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes)
    {                                                                           /* 达到最大的次数(SM_MAX_EXPIRE_TIMES)      */
        SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);            /* 释放备份的消息                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;

        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
        /* T3381 5次超时，停止定时器时不发送定时器停止事件 */
        g_ucSmTimerFiveExpireFlag = VOS_TRUE;
        SM_TimerStop(ucCntxtIndex);                                             /* 停止T3381                                */
        g_ucSmTimerFiveExpireFlag = VOS_FALSE;
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* 状态切换到SM_PDP_ACTIVE                  */

        SM_SndTafSmPdpModifyRej(
            SM_TAF_CAUSE_SM_MAX_TIME_OUT,
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);

        NAS_SM_EndSession();

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_T3381Expire:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
        ucCause = NAS_OM_SM_REJ_CAUSE_TIMER_TIMEOUT;
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL_LEN);
    }
    else
    {
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
        NAS_TIMER_EventReport(SM_TIMER_TYPE_T3381, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_START);
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

        NAS_SM_BeginSession();

        /* 发送缓存的消息 */
        NAS_SM_SndPdpCntxtHoldMsg(pstPdpCntxt);

        /* 可维可测消息 */
        SM_ReportM2NOtaMsg(&(pstHoldMsg->SmMsg));
    }

    return;
}

/*******************************************************************************
  Module:   SM_T3390Expire
  Function: T3390超时的处理
  Input:    VOS_UINT8          ucCntxtIndex     PDP context的索引
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. 郑 伟   2003.12.09   新规作成
  2. 日    期   : 2010年08月13日
     作    者   : a165503
     修改内容   : 问题单号:DTS2010070502076，接收到PDP去激活时，CS ONLY下待SM指示PDP去激活完成后进行PS DETACH

  3. 日    期  : 2013年03月13日
     作    者  : z00214637
     修改内容  : BodySAR项目

  4. 日    期  : 2013年06月30日
     作    者  : m00217266
     修改内容  : DCM LOGGER项目定时器事件上报

  5.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  6.日    期   : 2014年12月17日
    作    者   : A00165503
    修改内容   : DTS2014112107909: 每次信令流程发起时, 需要申请新的资源

  7.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
  8.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_T3390Expire(VOS_UINT8 ucCntxtIndex)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCntxt = VOS_NULL_PTR;
    GMMSM_DATA_REQ_STRU                *pstHoldMsg  = VOS_NULL_PTR;

    /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
    NAS_TIMER_EventReport(SM_TIMER_TYPE_T3390, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);
    /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

    pstPdpCntxt = NAS_SM_GetPdpCtxInfoAddr(ucCntxtIndex);
    pstHoldMsg  = (GMMSM_DATA_REQ_STRU *)pstPdpCntxt->pHoldSndMsg;

    g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes++;           /* 超时的次数加1                            */

    if( SM_MAX_EXPIRE_TIMES
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes)
    {                                                                           /* 达到最大的次数(SM_MAX_EXPIRE_TIMES)      */
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
        /* T3390 5次超时，停止定时器时不发送定时器停止事件 */
        g_ucSmTimerFiveExpireFlag = VOS_TRUE;
        SM_TimerStop(ucCntxtIndex);                                             /* 停止T3390                                */
        g_ucSmTimerFiveExpireFlag = VOS_FALSE;
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* 释放备份的消息                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;

        SM_SndTafSmPdpDeActInd(
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
            SM_TAF_CAUSE_SM_MAX_TIME_OUT,
            SM_FALSE);                                                          /* 通知TAF去激活                            */

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* 状态切换到SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_T3390Expire:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE ");
        g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xff;
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;

        NAS_SM_SndGmmPdpStatusInd();

        /* 向GMM发送GMMSM_PDP_DEACTIVATED_IND消息，报告当前PDP状态 */
        NAS_SM_SndGmmPdpDeactivatedInd();

        NAS_SM_EndSession();

    }
    else
    {
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, begin */
        NAS_TIMER_EventReport(SM_TIMER_TYPE_T3390, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_START);
        /* added  by m00217266 for v9r1 dcm logger可维可测项目, 2013-06-30, end */

        NAS_SM_BeginSession();

        /* 发送缓存的消息 */
        NAS_SM_SndPdpCntxtHoldMsg(pstPdpCntxt);

        /* 可维可测消息 */
        SM_ReportM2NOtaMsg(&(pstHoldMsg->SmMsg));
    }

    return;
}

/*******************************************************************************
  Module:   SM_RegisterProtectTimerExpire
  Function: 注册保护Timer超时
  Input:    VOS_UINT8          ucCntxtIndex     PDP context的索引
  Output:   VOS_VOID
  NOTE:     VOS_VOID
  Return:   VOS_VOID
  History:
  1.   郑 伟   2003.12.10   新规作成

  2.日    期   : 2010年01月04日
    作    者   : w00166186
    修改内容   : 问题单号:DTS2010122004132 W CS ONLY PDP激活过程重定向到G,PDP激活失败

  3.日    期   : 2014年05月05日
    作    者   : Y00213812
    修改内容   : 如果当前为正在注册状态才继续清理缓存等操作

  4.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源

  5.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
  6.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_RegisterProtectTimerExpire(VOS_UINT8 ucCntxtIndex)
{
    VOS_UINT8                           i;
    MSG_HEADER_STRU                    *pHoldMsg;

    SM_TimerStop(SM_REGISTER_TIMER_ID);                                         /* 停止注册保护Timer                        */

    if (SM_PS_REGISTERING != g_SmEntity.ucRegisterFlg)
    {
        return;
    }

    g_SmEntity.ucRegisterFlg = SM_PS_NOTREGISTER;                               /* 设定注册标志为没有注册                   */

    for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        if( SM_NULL != g_SmEntity.aHoldMsg[i].pHoldRcvMsg )
        {                                                                       /* 存在缓存消息                             */
            pHoldMsg = (MSG_HEADER_STRU *)g_SmEntity.aHoldMsg[i].pHoldRcvMsg;
            switch( pHoldMsg->ulMsgName )
            {                                                                   /* 消息类型                                 */
            case ID_SMREG_PDP_ACTIVATE_REQ:
                SM_SndTafSmPdpActivateRej(
                    ((SMREG_PDP_ACTIVATE_REQ_STRU *)pHoldMsg)->ucConnectId,
                    SM_TAF_CAUSE_SM_CONN_ESTABLISH_MAX_TIME_OUT,
                    VOS_NULL_PTR);
                break;
            case ID_SMREG_PDP_DEACTIVATE_REQ:
                SM_SndTafSmPdpDeActInd (
                    ((SMREG_PDP_DEACTIVATE_REQ_STRU *)pHoldMsg)->ucConnectId,
                    SM_TAF_CAUSE_SM_CONN_ESTABLISH_MAX_TIME_OUT,
                    SM_FALSE);

                NAS_SM_SndGmmPdpStatusInd();
                break;
            default:
                break;
            }

            SM_ComClearPdpCntxt(i);                                             /* 调用清除PDP实体的处理                    */
            SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);                        /* 释放保留消息                             */
            g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;                       /* 清除缓存消息                             */
        }
        else
        {
            break;
        }
    }

    NAS_SM_SndGmmPdpDeactivatedInd();

    NAS_SM_EndSession();


    return;
}

/*******************************************************************************
  Module:   SM_NwModifyProtectTimerExpire
  Function: Network发起PDP context Modify保护Timer超时的处理
  Input:    VOS_UINT8          ucCntxtIndex
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1.郑 伟   2003.12.10   新规作成

  2.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程发起前申请资源

  3.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
  4.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID SM_NwModifyProtectTimerExpire(VOS_UINT8 ucCntxtIndex)
{
    NAS_SM_NORM_LOG("SM_NwModifyProtectTimerExpire: SM_PDP_NW_MODIFY ==> SM_PDP_INACTIVE_PENDING");

    SM_ComClearPdpCntxt(ucCntxtIndex);                                          /* 清除实体                                 */
    SM_ComDelNsapiFromAddr(
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex,
        ucCntxtIndex);                                                          /* 维护Addr和Apn实体                        */
    SM_SndRabmSmDeactivateInd(1,&ucCntxtIndex);                                 /* 通知RABM                                 */

    SM_SndTafSmPdpDeActInd(
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
        SM_TAF_CAUSE_SM_MAX_TIME_OUT,
        SM_FALSE);

    NAS_SM_BeginSession();

    SM_SndPdpDeActReqMsg(SM_NULL, ucCntxtIndex);                                /* 发送去激活消息                           */
    g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;         /* Timer 超时次数清0                        */
    SM_TimerStart(ucCntxtIndex,SM_T3390_LENGTH,SM_TIMER_TYPE_T3390);            /* 启动T3390                                */
    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
        = SM_PDP_INACTIVE_PENDING;                                              /* 状态切换到SM_PDP_INACTIVE_PENDING        */

    NAS_SM_SndGmmPdpStatusInd();
    return;
}

/*******************************************************************************
  Module:   SM_TimerStart
  Function: 启动Timer
  Input:    VOS_UINT8   ucTimerId
            VOS_UINT32   ulTimerLen
            VOS_UINT8   ucTimerType
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.09   新规作成
      2.   Date        : 2006-11-25
           Author      : l47619
           Modification: 根据问题单新增:A32D07646
      3.   日    期   : 2011年06月24日
           作    者   : c00173809
           修改内容   : 根据问题单号：DTS2011051202669，SM的T3380,T3390超时消息解析不正确。
*******************************************************************************/
VOS_VOID SM_TimerStart(
                   VOS_UINT8        ucEntId,                                        /* Timer ID 为实体的索引                    */
                   VOS_UINT32        ulTimerLen,                                     /* Timer的时长                              */
                   VOS_UINT8        ucTimerType
                   )
{
    if( SM_REGISTER_TIMER_ID == ucEntId )
    {
        if (VOS_OK !=
            NAS_StartRelTimer(&g_SmEntity.ulRegTimerID,WUEPS_PID_SM,ulTimerLen,(VOS_UINT32)ucTimerType,(VOS_UINT32)ucEntId,VOS_RELTIMER_LOOP))
        {
              PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,"start reltimer error");
        }

        g_SmEntity.ucRegTimerSta = SM_TIMER_STA_ON;


        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart: RegisterProtectTimer");

    }
    else
    {
        if (VOS_OK != NAS_StartRelTimer(&g_SmEntity.
            aPdpCntxtList[ucEntId].TimerInfo.TimerId,WUEPS_PID_SM,ulTimerLen,(VOS_UINT32)ucTimerType,(VOS_UINT32)ucEntId,VOS_RELTIMER_LOOP))
        {
              PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,"start reltimer error");
        }

        g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerType
            = ucTimerType;
        g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerStaFlg
            = SM_TIMER_STA_ON;

        g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucExpireTimes = 0;

        switch( ucTimerType )
        {
        case SM_TIMER_TYPE_T3380    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T3380", ucEntId);
            break;
        case SM_TIMER_TYPE_T3381    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T3381", ucEntId);

            break;
        case SM_TIMER_TYPE_T3390    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T3390", ucEntId);

            break;
        case SM_TIMER_TYPE_T0001    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T0001", ucEntId);

            break;
        case SM_TIMER_TYPE_T0002    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T0002", ucEntId);

            break;
        case SM_TIMER_TYPE_T0003    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T0003", ucEntId);

            break;
        default :
            break;
        }

    }
    return;
}

/*******************************************************************************
  Module:   SM_TimerStop
  Function: 停止Timer
  Input:    VOS_UINT8   ucTimerId
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郑 伟   2003.12.09   新规作成
*******************************************************************************/
VOS_VOID SM_TimerStop(
                   VOS_UINT8        ucEntId                                         /* Timer ID 为实体的索引                    */
                  )
{
    if( SM_REGISTER_TIMER_ID == ucEntId )
    {
        if( SM_TIMER_STA_ON == g_SmEntity.ucRegTimerSta )
        {
            if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_SM, ucEntId, &g_SmEntity.ulRegTimerID))
            {
                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO: SM TimerStop fail");
            }

            g_SmEntity.ucRegTimerSta = SM_TIMER_STA_OFF;


            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO: SM TimerStop: RegisterProtectTimer");

        }
    }
    else
    {
        if( SM_TIMER_STA_ON
            == g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerStaFlg )
        {
            if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_SM, g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerType, &g_SmEntity
                .aPdpCntxtList[ucEntId].TimerInfo.TimerId))
             {
                 PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO: SM TimerStop fail");
             }
            g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerStaFlg
                = SM_TIMER_STA_OFF;

            switch( g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerType )
            {
            case SM_TIMER_TYPE_T3380    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityIndex): T3380", ucEntId);
                break;
            case SM_TIMER_TYPE_T3381    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityIndex): T3381", ucEntId);

                break;
            case SM_TIMER_TYPE_T3390    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityInde): T3390", ucEntId);
                break;
            case SM_TIMER_TYPE_T0001    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityInde): T0001", ucEntId);
                break;
            case SM_TIMER_TYPE_T0002    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityIndex): T0002", ucEntId);
                break;
            case SM_TIMER_TYPE_T0003    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityIndex): T0003", ucEntId);
                break;
            default :
                break;
            }
        }
    }
    return;
}


/*******************************************************************************
  Module:   SM_MemCmp
  Function: 比较内存
  Input:    VOS_UINT8   *p1
            VOS_UINT8   *p2
            VOS_UINT16  length
  Output:   VOS_VOID
  NOTE:
  Return:   SM_FALSE:  内存相等
            SM_TRUE:   内存不相等
  History:
      1.   张志勇      2003.12.26   新规作成
*******************************************************************************/
VOS_UINT8 SM_MemCmp(VOS_UINT8 *p1, VOS_UINT8 *p2, VOS_UINT32 ulLength)
{
    for(; ulLength > 0; ulLength--)
    {
        if(*p1 != *p2)
        {
            return SM_TRUE;
        }
        p1++;
        p2++;
    }
    return SM_FALSE;
}

/******************************************************************************
 * 函数名称 ： WuepsSmPidInit
 * 功能描述 ： WUEPS SM PID的初始化函数
 * 参数说明 ： 无
 * 备    注 ：
 * 返 回 值 ： VOS_UINT32 初始化结果：
 *             0  : 成功
 *             非0: 失败
 *
 * 变更历史 ：
 *           No.  姓名      变更                                    日   期
 *           1    张志勇    新建                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsSmPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
    case VOS_IP_LOAD_CONFIG:
        SM_Init();                                                          /* 初始化                                   */
        break;
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}


/*****************************************************************************
 Prototype      : Sm_PowerOff()
 Description    : 软关机过程中，用以回收资源。包括动态分配的内存和定时器等。
 Input          : VOS_VOID
 Output         :
 Return Value   : VOID
 Calls          :
 Called By      :
 History        :
  1.Date        : 2006-09-14
    Author      : l47619
    Modification: 根据问题单新增:A32D05600

  2.日    期   : 2013年2月6日
    作    者   : A00165503
    修改内容   : DTS2013020505170: SM关机函数有内存泄露风险

  3.日    期   : 2014年6月28日
    作    者   : A00165503
    修改内容   : DSDS III 项目, 信令流程结束后释放资源
  4.日    期   : 2015年4月28日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_VOID  Sm_PowerOff(VOS_VOID)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    NAS_SM_PDP_ADDR_INFO_STRU          *pstPdpAddrInfo;
    VOS_UINT8                           ucCntxtIndex;

    /*关闭公用定时器:*/
    SM_TimerStop(SM_REGISTER_TIMER_ID);

    for (ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
    {
        pstPdpCtxInfo  = NAS_SM_GetPdpCtxInfoAddr(ucCntxtIndex);
        pstPdpAddrInfo = NAS_SM_GetPdpAddrInfoAddr(ucCntxtIndex);

        /* 释放缓存的消息 */
        if (VOS_NULL_PTR != pstPdpCtxInfo->pHoldSndMsg)
        {
            SM_Free(pstPdpCtxInfo->pHoldSndMsg);
            pstPdpCtxInfo->pHoldSndMsg = VOS_NULL_PTR;
        }

        /* 释放QOS信息 */
        pstPdpCtxInfo->QoS.ulQosLength = 0;
        PS_MEM_SET(pstPdpCtxInfo->QoS.aucQosValue,
                   0x00,
                   sizeof(pstPdpCtxInfo->QoS.aucQosValue));

        /* 释放APN消息 */
        pstPdpAddrInfo->PdpApn.ulApnLength = 0;
        PS_MEM_SET(pstPdpAddrInfo->PdpApn.aucApnValue,
                   0x00,
                   sizeof(pstPdpAddrInfo->PdpApn.aucApnValue));

        /* 释放PS域未注册场景下发起PDP激活请求产生的缓存 */
        if (VOS_NULL_PTR != g_SmEntity.aHoldMsg[ucCntxtIndex].pHoldRcvMsg)
        {
            SM_Free(g_SmEntity.aHoldMsg[ucCntxtIndex].pHoldRcvMsg);
            g_SmEntity.aHoldMsg[ucCntxtIndex].pHoldRcvMsg = VOS_NULL_PTR;
        }
    }

    /*调用初始化函数:*/
    SM_Init();

    NAS_SM_EndSession();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_CalcMaxSduSize
 功能描述  : 解析Qos中Maximum SDU size的值
 输入参数  : VOS_UINT8      *pucQos     - Qos数组码流
             VOS_UINT8      ucCurrOctet - Qos数组码流当前字节索引
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 NAS_SM_CalcMaxSduSize(
    VOS_UINT8                           *pucQos,
    VOS_UINT8                           ucCurrOctet
)
{
    VOS_UINT16                          usMaxSduSize;
    VOS_UINT8                           ucQosOctet;

    ucQosOctet = *(pucQos + ucCurrOctet);

    

    if ((ucQosOctet >= 1) && (ucQosOctet <= 150))
    {
        usMaxSduSize = ucQosOctet * 10;
    }
    else if (151 == ucQosOctet)
    {
        usMaxSduSize = 1502;
    }
    else if (152 == ucQosOctet)
    {
        usMaxSduSize = 1510;
    }
    else if (153 == ucQosOctet)
    {
        usMaxSduSize = 1520;
    }
    else
    {
        usMaxSduSize = ucQosOctet;
    }

    return usMaxSduSize;
}

/*****************************************************************************
 函 数 名  : NAS_SM_CalcQosBitRate
 功能描述  : 根据 TS 24.008 10.5.6.5 中的规定，计算QOS中Maximum(Guaranteed) bit
             rate for uplink(downlink)的值
 输入参数  : VOS_UINT8      *pucQos          - Qos数组码流
             VOS_UINT8      ucCurrOctetIndex - Qos数组码流当前字节索引
             VOS_UINT8      ucExtOctetIndex  - 上行或下行速率的扩展字节索引
             VOS_UINT8      ucBitRateType    - 上行或下行
             VOS_UINT32     ulQosLen         - Qos数组码流长度
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月20日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_SM_CalcQosBitRate(
    VOS_UINT8                           *pucQos,
    VOS_UINT8                           ucCurrOctetIndex,
    VOS_UINT8                           ucExtOctetIndex,
    VOS_UINT8                           ucBitRateType,
    VOS_UINT32                          ulQosLen
)
{
    VOS_UINT32                          ulQosBitRate;
    VOS_UINT8                           ucQosOctet;
    VOS_UINT8                           *pucBitRate;

    ucQosOctet = *(pucQos + ucCurrOctetIndex);

    /*--------------------------------------------------------------------------
      Maximum(Guaranteed) bit rate for uplink, octet 8(12)
      Maximum(Guaranteed) bit rate for downlink, octet 9(13)
      8 7 6 5 4 3 2 1
      In MS to network direction:
      0 0 0 0 0 0 0 0       Subscribed maximum bit rate
      In network to MS direction:
      0 0 0 0 0 0 0 0       Reserved
      In MS to network direction and in network to MS direction:
      0 0 0 0 0 0 0 1(1)    The maximum(guaranteed) bit rate is
      0 0 1 1 1 1 1 1(63)   binary coded in 8 bits, using a granularity of 1 kbps
                            giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

      0 1 0 0 0 0 0 0(64)   The maximumv(guaranteed) bit rate is
      0 1 1 1 1 1 1 1(127)  64 kbps + ((the binary coded value in 8 bits –01000000) * 8 kbps)
                            giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

      1 0 0 0 0 0 0 0(128)  The maximum(guaranteed) bit rate is
      1 1 1 1 1 1 1 0(254)  576 kbps + ((the binary coded value in 8 bits –10000000) * 64 kbps)
                            giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

      1 1 1 1 1 1 1 1(255)  0kbps

      If the sending entity wants to indicate a Maximum(Guaranteed) bit rate higher
      than 8640 kbps, it shall set octet to '11111110', i.e. 8640 kbps, and
      shall encode the value for the Maximum(Guaranteed) bit rate in extended octet.
    --------------------------------------------------------------------------*/
    if (ucQosOctet <= 63)
    {
        ulQosBitRate = ucQosOctet;
    }
    else if ((ucQosOctet >= 64) && (ucQosOctet <= 127))
    {
        ulQosBitRate = 64 + ((ucQosOctet - 64) * 8);
    }
    else if ((ucQosOctet >= 128) && (ucQosOctet < 254))
    {
        ulQosBitRate = 576 + ((ucQosOctet - 128) * 64);
    }
    else if (254 == ucQosOctet)
    {
        #if(PS_UE_REL_VER < PS_PTL_VER_R7)
        ulQosBitRate = 576 + ((ucQosOctet - 128) * 64);
        #else
        if (((NAS_SM_QOS_BIT_RATE_TYPE_DL == ucBitRateType) && (ulQosLen < 14))
         || ((NAS_SM_QOS_BIT_RATE_TYPE_UL == ucBitRateType) && (ulQosLen < 16)))
        {
            ulQosBitRate = 576 + ((ucQosOctet - 128) * 64);
        }
        else
        {
            /*pucBitRate 指向Maximum(Guaranteed) bit rate (extended)*/
            pucBitRate = pucQos + ucExtOctetIndex;

            /*------------------------------------------------------------------
              Maximum(Guaranteed) bit rate for uplink (extended), octet 17(18)
              Maximum(Guaranteed) bit rate for downlink (extended), octet 15(16)
              8 7 6 5 4 3 2 1
              In MS to network direction and in network to MS direction:
              0 0 0 0 0 0 0 0   Use the value indicated by the Maximum(Guaranteed)
                                bit rate for downlink in octet 8(12).

              For all other values: Ignore the value indicated by the Maximum(Guaranteed)
              bit rate for uplink in octet 8(12)/downlink in octet 9(13) and use the following value:
              0 0 0 0 0 0 0 1(1)    The maximum(guaranteed) bit rate is
              0 1 0 0 1 0 1 0(74)   8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
                                    giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

              0 1 0 0 1 0 1 1(75)   The maximum(guaranteed) bit rate is
              1 0 1 1 1 0 1 0(186)  16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
                                    giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

              1 0 1 1 1 0 1 1(187)  The maximum(guaranteed) bit rate is
              1 1 1 1 1 0 1 0(250)  128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
                                    giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
            --------------------------------------------------------------------*/
            if (*pucBitRate <= 74)
            {
                ulQosBitRate = 8600 + (*pucBitRate * 100);
            }
            else if (*pucBitRate <= 186)
            {
                ulQosBitRate = 16000 + ((*pucBitRate - 74) * 1000);
            }
            else if (*pucBitRate <= 250)
            {
                ulQosBitRate = 128000 + ((*pucBitRate - 186) * 2000);
            }
            else
            {
                /* 若大于APS_3GPP_QOS_BIT_256MBPS，则赋值为256000 */
                ulQosBitRate = 256000;
            }
        }
        #endif
    }
    else
    {
        ulQosBitRate = 0;
    }

    return ulQosBitRate;
}

/*****************************************************************************
 函 数 名  : NAS_SM_CalcTransDelay
 功能描述  :
 输入参数  : VOS_UINT8          *pucQos     - Qos数组码流
             VOS_UINT8          ucCurrOctet - Qos数组码流当前字节索引
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 NAS_SM_CalcTransDelay(
    VOS_UINT8                           *pucQos,
    VOS_UINT8                           ucCurrOctet
)
{
    VOS_UINT16                          usTransDelay;
    VOS_UINT8                           ucQosOctet;

    ucQosOctet = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_TRANSFER_DELAY_MASK) >> 2;

    /*--------------------------------------------------------------------------
      Transfer delay, octet 11 (See 3GPP TS 23.107)
      8 7 6 5 4 3
      In MS to network direction:
      0 0 0 0 0 0   Subscribed transfer delay
      In network to MS direction:
      0 0 0 0 0 0   Reserved
      In MS to network direction and in network to MS direction:

      0 0 0 0 0 1(1)    The Transfer delay is binary coded in 6 bits, using a granularity of 10 ms
      0 0 1 1 1 1(15)   giving a range of values from 10 ms to 150 ms in 10 ms increments

      0 1 0 0 0 0(16)   The transfer delay is 200 ms + ((the binary coded value in 6 bits – 010000) * 50 ms)
      0 1 1 1 1 1(31)   giving a range of values from 200 ms to 950 ms in 50ms increments

      1 0 0 0 0 0(32)   The transfer delay is 1000 ms + ((the binary coded value in 6 bits – 100000) * 100 ms)
      1 1 1 1 1 0(62)   giving a range of values from 1000 ms to 4000 ms in 100ms increments

      1 1 1 1 1 1(63)   Reserved
    --------------------------------------------------------------------------*/
    if ((ucQosOctet >= 1) && (ucQosOctet <= 15))
    {
        usTransDelay = ucQosOctet;
    }
    else if ((ucQosOctet >= 16) && (ucQosOctet <= 31))
    {
        usTransDelay = 200 + ((ucQosOctet - 16) * 50);
    }
    else if ((ucQosOctet >= 32) && (ucQosOctet <= 62))
    {
        usTransDelay = 1000 + ((ucQosOctet - 32) * 100);

    }
    else
    {
        usTransDelay = 63;
    }

    return usTransDelay;
}

/*****************************************************************************
 函 数 名  : NAS_SM_FillQos
 功能描述  : 填写OM查询所需要Qos信息
 输入参数  : NAS_QOS_STRUCT     *pMsg       - 待填写的Qos信息
             VOS_UINT8          *pucQos     - Qos数组码流
             VOS_UINT32         *pulQosLen  - Qos数组码流的长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月18日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2015年9月17日
    作    者   : zwx247453
    修改内容   : Dallas寄存器按原语上报及BBP采数项目

*****************************************************************************/
VOS_VOID NAS_SM_FillQos(
    NAS_QOS_IND_STRUCT                  *pMsg,
    VOS_UINT8                           *pucQos,
    VOS_UINT32                          ulQosLen
)
{
    VOS_UINT8                           ucCurrOctet;

    ucCurrOctet = 0;

    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    /* Octet 3 of Qos struct. Refer to sction 10.5.6 in TS 24.008 */
    pMsg->enDelayClass           = (*(pucQos) & NAS_SM_QOS_DELAY_CLASS_MASK) >> 3;
    pMsg->enReliabilityClass     = (*(pucQos) & NAS_SM_QOS_RELIABILITY_CLASS_MASK);

    ucCurrOctet++;

    /* Octet 4 */
    pMsg->enPeakThrough          = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_PEAK_THROUGHPUT_MASK) >> 4;
    pMsg->enPrecedenceClass      = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_PRECEDENCE_CLASS_MASK);

    ucCurrOctet++;

    /* Octet 5 */
    pMsg->enMeanThrough          = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_MEAN_THROUGHPUT_MASK);

    ucCurrOctet++;

    /* Octet 6 */
    pMsg->enTrafficClass         = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_TRAFFIC_CLASS_MASK) >> 5;
    pMsg->enDeliverOrder         = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_DELIVERY_ORDER_MASK) >> 3;
    pMsg->enDeliverOfErrSdu      = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK);

    ucCurrOctet++;

    /* Octet 7 */
    pMsg->usMaximSduSize         = NAS_SM_CalcMaxSduSize(pucQos, ucCurrOctet);

    ucCurrOctet++;

    /*--------------------------------------------------------------------------
      Octet 8
      Maximum bit rate for uplink 扩展字节位于Qos数组码流中的第14个字节，
      计算 Maximum bit rate for uplink 时需要将扩展字节的值考虑进去。
    ---------------------------------------------------------------------------*/
    pMsg->ulMaxBitRateUl         = NAS_SM_CalcQosBitRate(pucQos,
                                                    ucCurrOctet,
                                                    14,
                                                    NAS_SM_QOS_BIT_RATE_TYPE_UL,
                                                    ulQosLen);

    ucCurrOctet++;

    /*--------------------------------------------------------------------------
      Octet 9
      Maximum bit rate for downlink 扩展字节位于Qos数组码流中的第12个字节，
      计算 Maximum bit rate for downlink 时需要将扩展字节的值考虑进去。
    ---------------------------------------------------------------------------*/
    pMsg->ulMaxBitRateDl         = NAS_SM_CalcQosBitRate(pucQos,
                                                    ucCurrOctet,
                                                    12,
                                                    NAS_SM_QOS_BIT_RATE_TYPE_DL,
                                                    ulQosLen);

    ucCurrOctet++;

    /* Octet 10 */
    pMsg->enResidualBer          = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_RESIDUAL_BER_MASK) >> 4;
    pMsg->enSduErrRatio          = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_SDU_ERROR_RATIO_MASK);

    ucCurrOctet++;

    /* Octet 11 */
    pMsg->usTransDelay           = NAS_SM_CalcTransDelay(pucQos, ucCurrOctet);
    pMsg->enTraffHandlPrior      = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_TRAFFIC_HANDLING_PRIORITY_MASK);
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */

    ucCurrOctet++;

    /*--------------------------------------------------------------------------
      Octet 12
      Guaranteed bit rate for uplink 扩展字节位于Qos数组码流中的第15个字节，
      计算 Guaranteed bit rate for uplink 时需要将扩展字节的值考虑进去。
    ---------------------------------------------------------------------------*/
    pMsg->ulGuarantBitRateUl     = NAS_SM_CalcQosBitRate(pucQos,
                                                    ucCurrOctet,
                                                    15,
                                                    NAS_SM_QOS_BIT_RATE_TYPE_UL,
                                                    ulQosLen);

    ucCurrOctet++;

    /*--------------------------------------------------------------------------
      Octet 13
      Guaranteed bit rate for downlink 扩展字节位于Qos数组码流中的第13个字节，
      计算 Guaranteed bit rate for uplink 时需要将扩展字节的值考虑进去。
    ---------------------------------------------------------------------------*/
    pMsg->ulGuarantBitRateDl     = NAS_SM_CalcQosBitRate(pucQos,
                                                    ucCurrOctet,
                                                    13,
                                                    NAS_SM_QOS_BIT_RATE_TYPE_UL,
                                                    ulQosLen);
}

/*****************************************************************************
 函 数 名  : NAS_SM_FindCurrPdpId
 功能描述  : 获取当前PDP的ID，并判断其Qos是否有效
 输入参数  : 无
 输出参数  : VOS_UINT8      *pucNSAPI - 存储当前PDP context的NSAPI值
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月21日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_SM_FindCurrPdpId(
    VOS_UINT8                           *pucNSAPI
)
{
    VOS_UINT32                          ulIndex;

    *pucNSAPI = 0;

    for (ulIndex = 0; ulIndex < SM_MAX_NSAPI_NUM; ulIndex++)
    {
        if ((SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ulIndex].ucState)
         || (SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[ulIndex].ucState)
         || (SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ulIndex].ucState))
        {
            /* 当前版本只支持一个PDP激活，所以ucNSAPI的值应当是唯一的 */
            *pucNSAPI = (VOS_UINT8)ulIndex + SM_NSAPI_OFFSET;
            break;
        }
    }

    if ((0 != *pucNSAPI)
     && (0 != g_SmEntity.aPdpCntxtList[*pucNSAPI - SM_NSAPI_OFFSET].QoS.ulQosLength))
    {
        return VOS_TRUE;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_FindCurrPdpId:WARNING: length of QoS is 0!");
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : Sm_FillQosInfo
 功能描述  : 填写OM查询所需要的Qos信息
 输入参数  : NAS_QOS_STRUCT *pMsg - 待填写的QOS内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月23日
    作    者   : A00165503
    修改内容   : SM降圈复杂度

  2.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : SM保存的QOS和APN由动态内存改为静态数组
*****************************************************************************/
VOS_VOID Sm_FillQosInfo(
    NAS_QOS_IND_STRUCT                 *pMsg
)
{
    VOS_UINT8                          *pucQosvalue;
    VOS_UINT32                          ulQosLength;
    VOS_UINT32                          ulStatus;

    if (VOS_NULL_PTR == pMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM, "Sm_FillQosInfo: Wrong Parameter,Null pointer!");
        return;
    }

    /* 获取当前PDP的ID，并判断其Qos是否有效 */
    ulStatus = NAS_SM_FindCurrPdpId(&(pMsg->ucNSAPI));

    if (VOS_TRUE == ulStatus)
    {
        pucQosvalue = g_SmEntity.aPdpCntxtList[pMsg->ucNSAPI - SM_NSAPI_OFFSET].QoS.aucQosValue;
        ulQosLength = g_SmEntity.aPdpCntxtList[pMsg->ucNSAPI - SM_NSAPI_OFFSET].QoS.ulQosLength;

        NAS_SM_FillQos(pMsg, pucQosvalue, ulQosLength);
    }

    return;
}

/*****************************************************************************
 函 数 名  : Sm_FillPDPContextInfo
 功能描述  : 填写上报的PDP上下文的信息
 输入参数  : NAS_PDP_CONTEXT_STRU *
 输出参数  : 无
 返 回 值  : None
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月26日
    作    者   : z00163274
    修改内容   : 新生成函数

  2.日    期   : 2015年7月14日
    作    者   : wx270776
    修改内容   : OM融合

*****************************************************************************/
VOS_VOID NAS_SM_FillPDPContextInfo(
    NAS_OM_PDP_CONTEXT_IND_STRU        *pstPdpCntxt
)
{
    VOS_UINT8                           ucCntxtIndex;

    if (VOS_NULL_PTR == pstPdpCntxt)
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "NAS_SM_FillPDPContextInfo:Wrong Parameter,Null pointer!");
        return;
    }

    /* Deleted by wx270776 for OM融合, 2015-7-14, begin */
    /* 删除PS_MEM_SET。在调用前已经初始化过。 */
    /* Deleted by wx270776 for OM融合, 2015-7-14, end */

    /*查询PDP当前状态是否是处于激活状态*/
    for (ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
    {
        if ( (SM_PDP_ACTIVE         == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
          || (SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
          || (SM_PDP_NW_MODIFY      == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState) )
        {
            Aps_GetPdpContextInfo(ucCntxtIndex + SM_NSAPI_OFFSET,
                                  &(pstPdpCntxt->astPdpContext[pstPdpCntxt->ulPdpCnt]));

            pstPdpCntxt->ulPdpCnt++;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_SM_CheckPdpActiveState
 功能描述  : 检查当前是否有激活的PDP context
 输出参数  : 无
 返 回 值  : VOS_UINT32
             VOS_FALSE  - 没有激活的PDP context
             VOS_TRUE   - 有激活的PDP context
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月14日
    作    者   : A00165503
    修改内容   : 新生成函数，问题单号：DTS2010081802507

*****************************************************************************/
VOS_UINT32 NAS_SM_CheckPdpActiveState()
{
    VOS_UINT32                          ucCntxtIndex;

    /*查询PDP当前状态是否是处于激活状态*/
    for (ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
    {
        if ((SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
         || (SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
         || (SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/* Added by wx270776 for OM融合, 2015-7-21, begin */
/*****************************************************************************
 函 数 名  : NAS_SM_SndOmQosIndMsg
 功能描述  : 发送OM的查询消息透传消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ulRet: 结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年7月21日
   作    者   : wx270776
   修改内容   : OM融合
 2.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目
*****************************************************************************/
VOS_UINT32 NAS_SM_SndOmQosIndMsg(VOS_VOID)
{
    NAS_QOS_IND_STRUCT                  stNasQosInd;
    DIAG_TRANS_IND_STRU                 stDiagTransInd;
    VOS_UINT32                          ulRet;

    /* 初始化 */
    PS_MEM_SET(&stNasQosInd, 0x00, sizeof(NAS_QOS_IND_STRUCT));

    /* 填充消息内容 */
    Sm_FillQosInfo(&stNasQosInd);
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    stNasQosInd.enPrimId            = ID_NAS_OM_QOS_CONFIRM;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
    stNasQosInd.usToolsId           = 0;

    stDiagTransInd.ulModule         = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_SM), DIAG_MODE_UMTS);;
    stDiagTransInd.ulPid            = WUEPS_PID_SM;
    /* Modified by zwx247453 for 寄存器上报, 2015-11-09, begin */
    stDiagTransInd.ulMsgId          = ((VOS_UINT32)(VOS_GetModemIDFromPid(WUEPS_PID_SM)) << 16) + ID_NAS_OM_QOS_CONFIRM;
    /* Modified by zwx247453 for 寄存器上报, 2015-11-09, end */
    stDiagTransInd.ulLength         = sizeof(NAS_QOS_IND_STRUCT);
    stDiagTransInd.pData            = &stNasQosInd;

    /* 发送消息 */
    ulRet = DIAG_TransReport(&stDiagTransInd);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_SndOmQosIndMsg:WARNING: Send msg fail.");
    }

    return ulRet;

}


/*****************************************************************************
 函 数 名  : NAS_SM_SndOmPdpCtxIndMsg
 功能描述  : 发送OM的查询消息透传消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : ulRet: 结果
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年7月21日
   作    者   : wx270776
   修改内容   : OM融合
 2.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目
*****************************************************************************/
VOS_UINT32 NAS_SM_SndOmPdpCtxIndMsg(VOS_VOID)
{
    NAS_OM_PDP_CONTEXT_IND_STRU        *pstNasOmPdpCtxInd = VOS_NULL_PTR;
    DIAG_TRANS_IND_STRU                 stDiagTransInd;
    VOS_UINT32                          ulRet;

    /* 申请内存 */
    pstNasOmPdpCtxInd = (NAS_OM_PDP_CONTEXT_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_SM, sizeof(NAS_OM_PDP_CONTEXT_IND_STRU));
    if (VOS_NULL_PTR == pstNasOmPdpCtxInd)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_SndOmPdpCtxIndMsg:PS_MEM_ALLOC fail.");
        return VOS_ERR;
    }

    /* 初始化 */
    PS_MEM_SET(pstNasOmPdpCtxInd, 0x00, sizeof(NAS_OM_PDP_CONTEXT_IND_STRU));

    /*获取相应的PDP上下文的IE值*/
    NAS_SM_FillPDPContextInfo(pstNasOmPdpCtxInd);
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    pstNasOmPdpCtxInd->enPrimId     = ID_NAS_OM_PDP_CONTEXT_CONFIRM;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
    pstNasOmPdpCtxInd->usToolsId    = 0;

    stDiagTransInd.ulModule         = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_SM), DIAG_MODE_UMTS);;
    stDiagTransInd.ulPid            = WUEPS_PID_SM;
    /* Modified by zwx247453 for 寄存器上报, 2015-11-09, begin */
    stDiagTransInd.ulMsgId          = ((VOS_UINT32)(VOS_GetModemIDFromPid(WUEPS_PID_SM)) << 16) + ID_NAS_OM_PDP_CONTEXT_CONFIRM;
    /* Modified by zwx247453 for 寄存器上报, 2015-11-09, end */
    stDiagTransInd.ulLength         = sizeof(NAS_OM_PDP_CONTEXT_IND_STRU);
    stDiagTransInd.pData            = pstNasOmPdpCtxInd;

    /* 发送消息 */
    ulRet = DIAG_TransReport(&stDiagTransInd);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_SndOmPdpCtxIndMsg:WARNING: Send msg fail.");
    }

    PS_MEM_FREE(WUEPS_PID_SM, pstNasOmPdpCtxInd);

    return ulRet;

}
/* Added by wx270776 for OM融合, 2015-7-21, end */

/*****************************************************************************
 函 数 名  : Sm_OmQuery
 功能描述  :
 输入参数  :

 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年9月01日
    作    者   :
    修改内容   : 新生成函数

  2.日    期   : 2010年2月26日
    作    者   : z00163274
    修改内容   : 增加PDP上下文的可维可测需求

  3.日    期   : 2010年2月26日
    作    者   : o00132663
    修改内容   : DTS2011022105462,NAS回复给SDT的透明消息长度错误

  4.日    期   : 2012年11月1日
    作    者   : z40661
    修改内容   : DTS2012102501504

  5.日    期   : 2015年7月9日
    作    者   : wx270776
    修改内容   : OM融合
*****************************************************************************/
VOS_VOID Sm_OmQuery(
    VOS_VOID                           *pMsg
)
{
    /* Modified by wx270776 for OM融合, 2015-7-1, begin */
    ID_NAS_OM_INQUIRE_STRU             *pOmMsg;
    NAS_QOS_STRUCT                     *pQosMsg;
    VOS_UINT32                          ulRet;
    NAS_OM_PDP_CONTEXT_STRU            *pPDPCntxtMsg;                          /*增加PDP上下文的可维可测*/
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulSndOmRet;

    pOmMsg = (ID_NAS_OM_INQUIRE_STRU *)pMsg;

    switch (pOmMsg->ulMsgId)
    {
    case ID_NAS_OM_QOS_INQUIRE:
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Sm_OmQuery:receive om message!");

        /* 1. 向OM发送IND消息 */
        ulSndOmRet = NAS_SM_SndOmQosIndMsg();

        /* 2. 向工具侧回复CNF消息 */
        /* 申请消息 */
        ulMsgLen = sizeof(NAS_QOS_STRUCT) - VOS_MSG_HEAD_LENGTH;

        pQosMsg = (NAS_QOS_STRUCT *)PS_ALLOC_MSG(WUEPS_PID_SM, ulMsgLen);
        if (VOS_NULL_PTR == pQosMsg)
        {
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Sm_OmQuery:Error: Memory Allocate fail!");

            return;
        }

        /* 初始化 */
        PS_MEM_SET((VOS_UINT8*)pQosMsg + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

        /* 填写消息内容 */
        pQosMsg->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
        pQosMsg->ulMsgId          = ID_NAS_OM_QOS_CONFIRM;
        pQosMsg->usOriginalId     = pOmMsg->usOriginalId;
        pQosMsg->usTerminalId     = pOmMsg->usTerminalId;
        pQosMsg->ulTimeStamp      = pOmMsg->ulTimeStamp;
        pQosMsg->ulSN             = pOmMsg->ulSN;
        pQosMsg->enResult         = ulSndOmRet;

        /* 发送消息 */
        ulRet = PS_SEND_MSG(WUEPS_PID_SM, pQosMsg);
        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");
        }
        else
        {
            MN_INFO_LOG("NAS_MMC_SndOmOtaCnf:ID_NAS_OM_QOS_CONFIRM has been sent.");
        }

        break;

    /*增加PDP上下文的可维可测*/
    case ID_NAS_OM_PDP_CONTEXT_INQUIRE:

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Sm_OmQuery:receive om message ID_NAS_OM_PDP_CONTEXT_INQUIRE!");

        /* 1. 向OM发送IND消息 */
        ulSndOmRet = NAS_SM_SndOmPdpCtxIndMsg();

        /* 2. 向工具侧回复CNF消息 */
        /* 申请消息 */
        ulMsgLen     = sizeof(NAS_OM_PDP_CONTEXT_STRU) - VOS_MSG_HEAD_LENGTH;

        pPDPCntxtMsg = (NAS_OM_PDP_CONTEXT_STRU *)PS_ALLOC_MSG(WUEPS_PID_SM, ulMsgLen);
        if (VOS_NULL_PTR == pPDPCntxtMsg)
        {
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Sm_OmQuery:Error: Memory Allocate NAS_PDP_CONTEXT_STRU fail!");

            return;
        }

        /* 初始化 */
        PS_MEM_SET((VOS_UINT8*)pPDPCntxtMsg + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

        /* 填写消息内容 */
        pPDPCntxtMsg->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
        pPDPCntxtMsg->ulMsgId          = ID_NAS_OM_PDP_CONTEXT_CONFIRM;
        pPDPCntxtMsg->usOriginalId     = pOmMsg->usOriginalId;
        pPDPCntxtMsg->usTerminalId     = pOmMsg->usTerminalId;
        pPDPCntxtMsg->ulTimeStamp      = pOmMsg->ulTimeStamp;
        pPDPCntxtMsg->ulSN             = pOmMsg->ulSN;
        pPDPCntxtMsg->enResult         = ulSndOmRet;

        /* 发送消息 */
        ulRet = PS_SEND_MSG(WUEPS_PID_SM, pPDPCntxtMsg);
        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");
        }
        else
        {
            MN_INFO_LOG("NAS_MMC_SndOmOtaCnf:ID_NAS_OM_PDP_CONTEXT_CONFIRM has been sent.");
        }

        break;

    default:
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Sm_OmQuery:wrong PrimId!");
        break;
    }

    /* Modified by wx270776 for OM融合, 2015-7-1, end */
}

/*****************************************************************************
 函 数 名  : NAS_SM_MapGmmCause
 功能描述  : 将GMM错误码映射成SM/APS错误码
 输入参数  : enGmmCause - GMM错误码
 输出参数  : 无
 返 回 值  : SM_TAF_CAUSE_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
SM_TAF_CAUSE_ENUM_UINT16 NAS_SM_MapGmmCause(
    GMM_SM_CAUSE_ENUM_UINT16            enGmmCause
)
{
    NAS_SM_GMM_ERR_CODE_MAP_STRU       *pstGmmErrMapTblPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulGmmErrMapTblSize;
    VOS_UINT32                          ulCnt;

    pstGmmErrMapTblPtr = NAS_SM_GET_GMM_ERR_CODE_MAP_TBL_PTR();
    ulGmmErrMapTblSize = NAS_SM_GET_GMM_ERR_CODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulGmmErrMapTblSize; ulCnt++)
    {
        if (pstGmmErrMapTblPtr[ulCnt].enGmmCause == enGmmCause)
        {
            return pstGmmErrMapTblPtr[ulCnt].enSmCuase;
        }
    }

    return SM_TAF_CAUSE_GMM_UNKNOWN;
}

/*****************************************************************************
 函 数 名  : NAS_SM_MapSmNWCause
 功能描述  : 将SM NW的错误码进行偏移得到SM的错误码
 输入参数  : ucSmCause - SM NW的错误码
 输出参数  : 无
 返 回 值  : SM_TAF_CAUSE_ENUM_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月24日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
SM_TAF_CAUSE_ENUM_UINT16 NAS_SM_MapSmNWCause(VOS_UINT8 ucSmCause)
{
    SM_TAF_CAUSE_ENUM_UINT16            usSmCause;

    usSmCause = NAS_SM_TRANS_SM_NW_CAUSE(ucSmCause);

    /* # 95: - 111: protocol errors. */
    if ( (SM_TAF_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE <= usSmCause)
      && (SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED       >= usSmCause))
    {
        usSmCause = SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED;
    }

    return usSmCause;
}

/*lint +e958*/



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
