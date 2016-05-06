/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcApsMsg.c
  Description     : 该C文件实现APS消息处理和APS消息发送
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaConnManagement.h"
#include "ImsaProcApsMsg.h"
#include "TafApsApi.h"
#include "ImsaPublic.h"
#include "ImsaIntraInterface.h"
#include "ImsaProcAtMsg.h"
#include "ImsaCallManagement.h"
#include "ImsaServiceManagement.h"
#include "ImsaRegManagement.h"
/*lint -e767*/
#define    THIS_FILE_ID      PS_FILE_ID_IMSAPROCAPSMSG_C
#define    THIS_NAS_FILE_ID  NAS_FILE_ID_IMSAPROCAPSMSG_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
const IMSA_CONN_PS_EVT_FUNC_TBL_STRU    g_astImsaConnPsEvtFuncTbl[] =
{
    /* PS CALL */
    {ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF,
        IMSA_CONN_ProcTafPsEvtPdpActivateCnf},
    {ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ,
        IMSA_CONN_ProcTafPsEvtPdpActivateRej},
    {ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND,
        IMSA_CONN_ProcTafPsEvtPdpActivateInd},
    {ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND,
        IMSA_CONN_ProcTafPsEvtPdpModifyInd},
    {ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF,
        IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf},
    {ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND,
        IMSA_CONN_ProcTafPsEvtPdpDeactivateInd},
    {ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND,
        IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd},
    {ID_EVT_TAF_PS_CALL_ORIG_CNF,
        IMSA_CONN_ProcTafPsEvtCallOrigCnf},
    {ID_EVT_TAF_PS_CALL_END_CNF,
        IMSA_CONN_ProcTafPsEvtCallEndCnf},
    {ID_EVT_TAF_PS_SRVCC_CANCEL_NOTIFY_IND,
        IMSA_CONN_ProcTafPsEvtSrvccCancelInd},
};

const VOS_UINT32 g_ulImsaConnPsEvtFuncTblSize  = sizeof(g_astImsaConnPsEvtFuncTbl) / sizeof(g_astImsaConnPsEvtFuncTbl[0]);

extern VOS_VOID IMSA_CONN_WaitForIpv4PDPActiveCNF
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);

extern VOS_VOID IMSA_CONN_WaitForIpv6InfoProc
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);
/*
extern VOS_UINT32 IMSA_CONN_SipSignalPdpActOrig
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucCid,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
);
*/
extern VOS_VOID  IMSA_CONN_ProcActCnfBack
(
    const TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstPdpActivateCnf
);
extern VOS_VOID  IMSA_CONN_ProcIpv4ActCnf
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstPdpActivateCnf
);
extern VOS_VOID  IMSA_CONN_ProcIpv6ActCnf
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstPdpActivateCnf
);
extern VOS_VOID  IMSA_CONN_ProcIpv4v6ActCnf
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType
);
extern VOS_VOID IMSA_CONN_ProcActRejCurReqIpv4v6
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU    *pstPdpActivateRej
);
extern VOS_VOID IMSA_CONN_ProcActRejCurReqIpv4
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU    *pstPdpActivateRej
);
extern VOS_VOID IMSA_CONN_ProcActRejCurReqIpv6
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU    *pstPdpActivateRej
);

extern VOS_UINT32 IMSA_CONN_MatchIPV4V6FallBackCause
(
    TAF_PS_CAUSE_ENUM_UINT32                    enCause
);

extern VOS_VOID IMSA_CONN_ProcNoPcscf
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);
extern VOS_UINT32 IMSA_CONN_ProcTempCause
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);
extern VOS_UINT32 IMSA_CONN_ProcTimeOutMaxTimes
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);
extern VOS_UINT32 IMSA_CONN_ProcPermCause
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvt
 Description    : IMSA CONN模块处理APS消息
 Input          : pstConnModifyIndMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcTafPsEvt
(
    TAF_PS_EVT_STRU                    *pstEvt
)
{
    VOS_UINT32                          i           = IMSA_NULL;
    VOS_UINT32                          ulResult    = IMSA_NULL;
    IMSA_CONN_PS_EVT_FUNC               pPsEvtFunc  = VOS_NULL_PTR;


    /* 在事件处理表中查找处理函数 */
    for ( i = 0; i < g_ulImsaConnPsEvtFuncTblSize; i++ )
    {
        if ( pstEvt->ulEvtId == g_astImsaConnPsEvtFuncTbl[i].ulEvtId )
        {
            /* 事件ID匹配 */
            pPsEvtFunc = g_astImsaConnPsEvtFuncTbl[i].pPsEvtFunc;
            break;
        }
    }

    /* 如果处理函数存在则调用 */
    if ( VOS_NULL_PTR != pPsEvtFunc )
    {
        ulResult = pPsEvtFunc(pstEvt->aucContent);
    }
    else
    {
        IMSA_ERR_LOG1("IMSA_CONN_ProcTafPsEvt: Unexpected event received! <EvtId>",
            pstEvt->ulEvtId);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CONN_ProcTafPsEvt_ENUM, LNAS_MSG_INVALID, pstEvt->ulEvtId);
        ulResult    = VOS_ERR;
    }

    if ( VOS_OK != ulResult )
    {
        IMSA_ERR_LOG1("IMSA_CONN_ProcTafPsEvt: Handle this event failed! <EvtId>",
            pstEvt->ulEvtId);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CONN_ProcTafPsEvt_ENUM, LNAS_FAIL, pstEvt->ulEvtId);
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_WaitForIpv4PDPActiveCNF
 Description    : 等待APS进一步上报IPV4类型的承载建立成功消息
 Input          : enConnType-------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-05-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_WaitForIpv4PDPActiveCNF
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_IP_ADDRESS_STRU               *pstPdpIpAddr    = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;
    VOS_UINT8                           aucTemp[IMSA_IPV4_ADDR_LEN] = {0};

    /* 获取IPV4的PDP参数，如果存在则通知SERVICE模块连接建立成功 */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
        for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
        {
            pstPdpIpAddr = &pstNormalConn->astSipSignalPdpArray[i].stPdpAddr;
            if (((IMSA_IP_TYPE_IPV4 == pstPdpIpAddr->enIpType)
                    || (IMSA_IP_TYPE_IPV4V6 == pstPdpIpAddr->enIpType))
                && (0 != IMSA_MEM_CMP(aucTemp, pstPdpIpAddr->aucIpV4Addr, IMSA_IPV4_ADDR_LEN)))
            {
                /* 通知SERVICE模块连接建立成功 */
                IMSA_CONN_SetupConnSucc(enConnType);
                return ;
            }
        }
    }
    else
    {
        /* 紧急的场景不可能会出现两个紧急承载的情况，所以对紧急的场景不处理 */
    }

}

/*****************************************************************************
 Function Name  : IMSA_CONN_WaitForIpv6Info
 Description    : 等待APS进一步上报IPV6参数
 Input          : enConnType-------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_WaitForIpv6InfoProc
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    IMSA_IP_ADDRESS_STRU               *pstPdpIpAddr    = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;
    VOS_UINT8                           aucTemp[IMSA_IPV6_PREFIX_LEN] = {0};

    /* 获取PRIM PDP参数的格式 */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
        for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
        {
            pstPdpIpAddr = &pstNormalConn->astSipSignalPdpArray[i].stPdpAddr;
            if (((IMSA_IP_TYPE_IPV6 == pstPdpIpAddr->enIpType)
                    || (IMSA_IP_TYPE_IPV4V6 == pstPdpIpAddr->enIpType))
                && (0 == IMSA_MEM_CMP(aucTemp, pstPdpIpAddr->aucIpV6Addr, IMSA_IPV6_PREFIX_LEN)))
            {
                /* 启动等待IPV6参数定时器，等待APS的ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND消息，
                   不修改连接状态 */
                IMSA_CONN_StartTimer(IMSA_CONN_TYPE_NORMAL, TI_IMSA_WAIT_IPV6_INFO);

                return ;
            }
        }
    }
    else
    {
        pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();
        pstPdpIpAddr = &pstEmcConn->stSipSignalPdp.stPdpAddr;
        if (((IMSA_IP_TYPE_IPV6 == pstPdpIpAddr->enIpType)
                || (IMSA_IP_TYPE_IPV4V6 == pstPdpIpAddr->enIpType))
            && (0 == IMSA_MEM_CMP(aucTemp, pstPdpIpAddr->aucIpV6Addr, IMSA_IPV6_PREFIX_LEN)))
        {
            /* 启动等待IPV6参数定时器，等待APS的ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND消息，
               不修改连接状态 */
            IMSA_CONN_StartTimer(IMSA_CONN_TYPE_EMC, TI_IMSA_WAIT_IPV6_INFO);

            return ;
        }
    }

    IMSA_CONN_SetupConnSucc(enConnType);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_SipSignalPdpActOrig
 Description    : IMSA CONN模块发起信令PDP激活
 Input          : enConnType--------------连接类型
                  ucCid-------------------CID
                  enIpType----------------PDN类型
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-06-25  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_SipSignalPdpActOrig
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucCid,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
)
{
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo     = VOS_NULL_PTR;
    /* TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt = {0}; */
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid              = IMSA_NULL;

    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();
    pstEmcConn      = IMSA_CONN_GetEmcConnAddr();

    IMSA_INFO_LOG1("IMSA_CONN_SipSignalPdpActOrig: enConnType:", enConnType);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_SipSignalPdpActOrig_ENUM, IMSA_CONN_TYPE, enConnType);
    IMSA_INFO_LOG1("IMSA_CONN_SipSignalPdpActOrig: ucCid:", ucCid);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_SipSignalPdpActOrig_ENUM, IMSA_CID, ucCid);
    IMSA_INFO_LOG1("IMSA_CONN_SipSignalPdpActOrig: enIpType:", enIpType);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_SipSignalPdpActOrig_ENUM, IMSA_IP_TYPE, enIpType);

    /* 获取PRIM PDP参数的格式 */
    /*
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        IMSA_CONN_GetPrimPdpCntFromSelSdfPara(&pstNormalConn->stSelSdfPara, &stPdpPrimContextExt);
    }
    else
    {
        IMSA_CONN_GetPrimPdpCntFromSelSdfPara(&pstEmcConn->stSelSdfPara, &stPdpPrimContextExt);
    }

    stPdpPrimContextExt.enPdpType   = enIpType;
    stPdpPrimContextExt.ucCid       = ucCid;

    IMSA_CONN_AssignOpid(enConnType, &ucOpid);

    if (VOS_ERR == TAF_PS_SetPrimPdpContextInfo(PS_PID_IMSA, IMSA_CLIENT_ID,
                                                ucOpid, &stPdpPrimContextExt))
    {
        IMSA_ERR_LOG("IMSA_CONN_SipSignalPdpActOrig:TAF_PS_SetPrimPdpContextInfo failed!");

        return IMSA_FAIL;
    }
    */

    /* 获取拨号参数 */
    pstDialParaInfo = IMSA_MEM_ALLOC(sizeof(TAF_PS_DIAL_PARA_STRU));
    if (VOS_NULL_PTR == pstDialParaInfo)
    {
        /*打印不合法信息*/
        IMSA_ERR_LOG("IMSA_CONN_SipSignalPdpActOrig:TAF_PS_DIAL_PARA_STRU ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SipSignalPdpActOrig_ENUM, LNAS_NULL_PTR);

        return IMSA_FAIL;
    }

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        IMSA_CONN_GetImsDailParaFromSelSdfPara(&pstNormalConn->stSelSdfPara, pstDialParaInfo);

        pstNormalConn->stSelSdfPara.ucCid = ucCid;
        pstNormalConn->stSelSdfPara.enPdnType = enIpType;
    }
    else
    {
        IMSA_CONN_GetImsDailParaFromSelSdfPara(&pstEmcConn->stSelSdfPara, pstDialParaInfo);

        pstEmcConn->stSelSdfPara.ucCid = ucCid;
        pstEmcConn->stSelSdfPara.enPdnType = enIpType;
    }

    pstDialParaInfo->ucCid        = ucCid;
    pstDialParaInfo->enPdpType    = enIpType;


    IMSA_CONN_AssignOpid(enConnType, &ucOpid);
    /* IMSA_CONN_SetNormalConnOpid(ucOpid); */
    IMSA_CONN_SetOpid(enConnType, ucOpid);

    if (VOS_OK == TAF_PS_CallOrig(PS_PID_IMSA,IMSA_CLIENT_ID, ucOpid, pstDialParaInfo))
    {
        /* 启动IMS拨号定时器 */
        IMSA_CONN_StartTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

        /* 修改当前拨号请求的PDN类型 */
        IMSA_CONN_SaveCurReqPdnType(enConnType, enIpType);

        IMSA_MEM_FREE(pstDialParaInfo);

        return IMSA_SUCC;
    }

    IMSA_MEM_FREE(pstDialParaInfo);
    return IMSA_FAIL;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcActCnfBack
 Description    : IMSA CONN模块DP ACTIVATE CNF事件的回退处理
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_CONN_ProcActCnfBack
(
    const TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstPdpActivateCnf
)
{
    VOS_UINT8                           ucCid   = IMSA_NULL;
    VOS_UINT32                          ulRet   = IMSA_FAIL;
    VOS_UINT8                           ucOpid  = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CONN_ProcActCnfBack is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcActCnfBack_ENUM, LNAS_ENTRY);

    if ((VOS_TRUE == pstPdpActivateCnf->bitOpCause)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED != pstPdpActivateCnf->enCause))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcActCnfBack:Not Back!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcActCnfBack_ENUM, 1);

        /* 不会发起另一个SIP信令承载的建立 */

        /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
        IMSA_CONN_WaitForIpv6InfoProc(IMSA_CONN_TYPE_NORMAL);
        return ;
    }

    if (TAF_PDP_IPV4 == pstPdpActivateCnf->stPdpAddr.enPdpType)
    {
        if (IMSA_PDP_STATE_ACTIVE == IMSA_CONN_GetSipSignalPdpState(IMSA_CONN_TYPE_NORMAL,
                                                                    TAF_PDP_IPV6))
        {
            IMSA_INFO_LOG("IMSA_CONN_ProcActCnfBack:IPV6 is already active!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcActCnfBack_ENUM, IMSA_IPV6);

            /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
            IMSA_CONN_WaitForIpv6InfoProc(IMSA_CONN_TYPE_NORMAL);
            return ;
        }

        /* 查找一个未激活的CID进行激活 */
        IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_NORMAL, &ucOpid);
        ulRet = TAF_PS_GetUnusedCid(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, &ucCid);
        if (VOS_OK != ulRet)
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcActCnfBack:IPV4,get cid failed");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActCnfBack_ENUM, 2);

            IMSA_CONN_SetupConnSucc(IMSA_CONN_TYPE_NORMAL);
            return ;
        }

        ulRet = IMSA_CONN_SipSignalPdpActOrig(IMSA_CONN_TYPE_NORMAL, ucCid, TAF_PDP_IPV6);
        if (IMSA_SUCC != ulRet)
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcActCnfBack:IPV4,IMSA_CONN_SipSignalPdpActOrig failed");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActCnfBack_ENUM, 3);

            IMSA_CONN_SetupConnSucc(IMSA_CONN_TYPE_NORMAL);
            return ;
        }
        return ;
    }
    else if (TAF_PDP_IPV6 == pstPdpActivateCnf->stPdpAddr.enPdpType)
    {
        if (IMSA_PDP_STATE_ACTIVE == IMSA_CONN_GetSipSignalPdpState(IMSA_CONN_TYPE_NORMAL,
                                                                    TAF_PDP_IPV4))
        {
            IMSA_INFO_LOG("IMSA_CONN_ProcActCnfBack:IPV4 is already active!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcActCnfBack_ENUM, IMSA_IPV4);

            /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
            IMSA_CONN_WaitForIpv6InfoProc(IMSA_CONN_TYPE_NORMAL);\
            return ;
        }

        /* 查找一个未激活的CID进行激活 */
        IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_NORMAL, &ucOpid);
        ulRet = TAF_PS_GetUnusedCid(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, &ucCid);
        if (VOS_OK != ulRet)
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcActCnfBack:IPV6,get cid failed");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActCnfBack_ENUM, 4);

            /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
            IMSA_CONN_WaitForIpv6InfoProc(IMSA_CONN_TYPE_NORMAL);
            return ;
        }

        ulRet = IMSA_CONN_SipSignalPdpActOrig(IMSA_CONN_TYPE_NORMAL, ucCid, TAF_PDP_IPV4);
        if (IMSA_SUCC != ulRet)
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcActCnfBack:IPV6,IMSA_CONN_SipSignalPdpActOrig failed");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActCnfBack_ENUM, 5);

            /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
            IMSA_CONN_WaitForIpv6InfoProc(IMSA_CONN_TYPE_NORMAL);
            return ;
        }
        return ;
    }
    else
    {
        ;
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcIpv4ActCnf
 Description    : IMSA CONN模块处理PDP ACTIVATE CNF事件，且PDN类型为IPV4
 Input          : enConnType---------------------连接类型
                  pstPdpActivateCnf--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-25  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_CONN_ProcIpv4ActCnf
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstPdpActivateCnf
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT8                           ucCid           = IMSA_NULL;
    VOS_UINT32                          ulRet           = IMSA_FAIL;
    VOS_UINT8                           ucOpid          = IMSA_NULL;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcIpv4ActCnf:EMC!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIpv4ActCnf_ENUM, IMSA_EMERGENCY);

        /* 由于3GPP协议要求同一时刻只能存在一个紧急承载，因此不会再发起另一个紧急
           承载建立 */

        IMSA_CONN_SetupConnSucc(IMSA_CONN_TYPE_EMC);

        return ;
    }

    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();

    /* 如果是IPV4V6，需要激活另一个PDP */
    if (IMSA_IP_TYPE_IPV4V6 != pstNormalConn->enFirstReqPdnType)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcIpv4ActCnf:Not ipv4v6");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIpv4ActCnf_ENUM, 1);

        IMSA_CONN_SetupConnSucc(IMSA_CONN_TYPE_NORMAL);

        return ;
    }

    switch (pstNormalConn->enCurReqPdnType)
    {
        /* 这种情况不属于PDP回退，是前面PDP激活被拒绝后，分别发起IPV4、
           IPV6的PDP激活。*/
        case IMSA_IP_TYPE_IPV4:
            if (IMSA_PDP_STATE_ACTIVE == IMSA_CONN_GetSipSignalPdpState(IMSA_CONN_TYPE_NORMAL,
                                                                        IMSA_IP_TYPE_IPV6))
            {
                IMSA_INFO_LOG("IMSA_CONN_ProcIpv4ActCnf:ipv6 already active");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIpv4ActCnf_ENUM, IMSA_IPV6);

                /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
                IMSA_CONN_WaitForIpv6InfoProc(IMSA_CONN_TYPE_NORMAL);
                return ;
            }

            /* 查找一个未激活的CID进行激活 */
            IMSA_CONN_AssignOpid(enConnType, &ucOpid);
            ulRet = TAF_PS_GetUnusedCid(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, &ucCid);

            if (VOS_OK != ulRet)
            {
                IMSA_WARN_LOG("IMSA_CONN_ProcIpv4ActCnf:get cid failed!");
                TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcIpv4ActCnf_ENUM, IMSA_CALL_API_ERROR);

                IMSA_CONN_SetupConnSucc(IMSA_CONN_TYPE_NORMAL);
                return ;
            }

            ulRet = IMSA_CONN_SipSignalPdpActOrig(IMSA_CONN_TYPE_NORMAL, ucCid, TAF_PDP_IPV6);
            if (IMSA_SUCC != ulRet)
            {
                IMSA_WARN_LOG("IMSA_CONN_ProcIpv4ActCnf:IMSA_CONN_SipSignalPdpActOrig failed!");
                TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcIpv4ActCnf_ENUM, IMSA_CALL_API_ERROR);

                IMSA_CONN_SetupConnSucc(IMSA_CONN_TYPE_NORMAL);
                return ;
            }

            break;

        /* 这里是PDP激活回退功能实现 */
        /* chengmin 00285307 将TAF_PDP_IPV4V6改为IMSA_IP_TYPE_IPV4V6 消除coverity警告*/
        case IMSA_IP_TYPE_IPV4V6:
            IMSA_CONN_ProcActCnfBack(pstPdpActivateCnf);
            break;

        default:
            IMSA_WARN_LOG("IMSA_CONN_ProcIpv4ActCnf:current requst Pdn Type is error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcIpv4ActCnf_ENUM, LNAS_PARAM_INVALID);
            break;
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcIpv6ActCnf
 Description    : IMSA CONN模块处理PDP ACTIVATE CNF事件，且PDN类型为IPV6
 Input          : enConnType---------------------连接类型
                  pstPdpActivateCnf--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_CONN_ProcIpv6ActCnf
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstPdpActivateCnf
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        /* 由于3GPP协议要求同一时刻只能存在一个紧急承载，因此不会再发起另一个紧急
           承载建立 */

        /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
        IMSA_CONN_WaitForIpv6InfoProc(IMSA_CONN_TYPE_EMC);

        return ;
    }

    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();

    /* 如果是IPV4V6，需要激活另一个PDP */
    if (IMSA_IP_TYPE_IPV4V6 != pstNormalConn->enFirstReqPdnType)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcIpv6ActCnf:Not ipv4v6");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIpv4ActCnf_ENUM, 1);

        /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
        IMSA_CONN_WaitForIpv6InfoProc(IMSA_CONN_TYPE_NORMAL);

        return ;
    }

    /* 如果是IPV4V6，需要激活另一个PDP */
    switch (pstNormalConn->enCurReqPdnType)
    {
        case TAF_PDP_IPV6:
            /* 这种情况不属于PDP回退，是前面PDP激活被拒绝后，分别发起IPV4、
               IPV6的PDP激活, IPV6激活后不再发起IPV4的PDP激活 */

            /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
            IMSA_CONN_WaitForIpv6InfoProc(IMSA_CONN_TYPE_NORMAL);
            break;

        /* 这里是PDP激活回退功能实现 */
        case TAF_PDP_IPV4V6:

           IMSA_CONN_ProcActCnfBack(pstPdpActivateCnf);
           break;

        default:
           IMSA_WARN_LOG("IMSA_CONN_ProcIpv4ActCnf:current requst Pdn Type is error!");
           TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcIpv4ActCnf_ENUM, LNAS_PARAM_INVALID);
           break;
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcIpv4v6ActCnf
 Description    : IMSA CONN模块处理PDP ACTIVATE CNF事件，且PDN类型为IPV4V6
 Input          : enConnType---------------------连接类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_CONN_ProcIpv4v6ActCnf
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType
)
{
    /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
    IMSA_CONN_WaitForIpv6InfoProc(enConnType);
}

/*****************************************************************************
 Function Name  : IMSA_CONN_MatchIPV4V6FallBackCause
 Description    : IMSA处理IPV4V6回退原因值
 Input          : enCause------------------------拒绝原因值
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.x00253310      2014-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_MatchIPV4V6FallBackCause
(
    TAF_PS_CAUSE_ENUM_UINT32                    enCause
)
{
    IMSA_CONN_MANAGER_STRU              *pstConnManager;
    VOS_UINT32                          ulCnt               = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CONN_MatchIPV4V6FallBackCause is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_MatchIPV4V6FallBackCause_ENUM, LNAS_ENTRY);

    if (TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE == enCause)
    {
        IMSA_INFO_LOG("IMSA_CONN_MatchIPV4V6FallBackCause: cause match #28!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_MatchIPV4V6FallBackCause_ENUM, 1);
        return IMSA_SUCC;
    }

    pstConnManager = IMSA_CONN_GetConnManagerAddr();
    for (ulCnt = 0; ulCnt < pstConnManager->stIpv6FallBackExtCause.ulCauseNum; ulCnt++)
    {
        if (pstConnManager->stIpv6FallBackExtCause.aenPsCause[ulCnt] == enCause)
        {
            IMSA_INFO_LOG("IMSA_CONN_MatchIPV4V6FallBackCause: cause match succ!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_MatchIPV4V6FallBackCause_ENUM, LNAS_SUCC);
            return IMSA_SUCC;
        }
    }

    return IMSA_FAIL;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcActRejCurReqIpv4v6
 Description    : IMSA CONN模块处理PDP ACTIVATE REJ事件，current req pdn type:ipv4v6
 Input          : enConnType---------------------连接类型
                  pstPdpActivateRej--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-29  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcActRejCurReqIpv4v6
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU    *pstPdpActivateRej
)
{
    VOS_UINT32                          ulResult            = IMSA_FAIL;
    VOS_UINT8                           ucCid               = IMSA_NULL;

    /* 这种情况，需要分别发起IPv4、IPv6的PDP激活 */
    if (IMSA_SUCC == IMSA_CONN_MatchIPV4V6FallBackCause(pstPdpActivateRej->enCause))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcActRejCurReqIpv4v6: match fallback cause succ!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcActRejCurReqIpv4v6_ENUM, LNAS_SUCC);

        IMSA_CONN_GetConnSelectedCid(enConnType, ucCid);
        ulResult = IMSA_CONN_SipSignalPdpActOrig(enConnType, ucCid, IMSA_IP_TYPE_IPV4);
        if (IMSA_SUCC != ulResult)
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcActRejCurReqIpv4v6:unknown pdp addr or type,IMSA_CONN_SipSignalPdpActOrig failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActRejCurReqIpv4v6_ENUM, LNAS_FAIL);

            IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_CN_REJ,pstPdpActivateRej->enCause);

            return ;
        }

        return ;
    }

    if (IMSA_IP_TYPE_IPV4V6 == pstPdpActivateRej->enPdpType)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcActRejCurReqIpv4v6:ipv4v6");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActRejCurReqIpv4v6_ENUM, IMSA_IPV4V6);

        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_CN_REJ,pstPdpActivateRej->enCause);
        #if (FEATURE_ON == FEATURE_PTM)
        /* 等删除旧的CHR时，需要修改IMSA_PDN_CnRejCauseProc函数的返回值类型 */
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ,
                                        (IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16)IMSA_PDN_CnRejCauseProc(pstPdpActivateRej->enCause),
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ);
        #endif
        return ;
    }

    if ((IMSA_OP_TRUE == pstPdpActivateRej->bitOpCauseEx)
        && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED != pstPdpActivateRej->enCauseEx))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcActRejCurReqIpv4v6:Causeex is not sigle addr bearers only allowed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActRejCurReqIpv4v6_ENUM, 1);

        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_CN_REJ,pstPdpActivateRej->enCause);
        #if (FEATURE_ON == FEATURE_PTM)
        /* 等删除旧的CHR时，需要修改IMSA_PDN_CnRejCauseProc函数的返回值类型 */
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ,
                                        (IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16)IMSA_PDN_CnRejCauseProc(pstPdpActivateRej->enCause),
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ);
        #endif
        return ;
    }

    if (IMSA_IP_TYPE_IPV4 == pstPdpActivateRej->enPdpType)
    {
        IMSA_CONN_GetConnSelectedCid(enConnType, ucCid);
        ulResult = IMSA_CONN_SipSignalPdpActOrig(enConnType, ucCid, IMSA_IP_TYPE_IPV6);
        if (IMSA_SUCC != ulResult)
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcActRejCurReqIpv4v6:qos not accepted,ipv4,IMSA_CONN_SipSignalPdpActOrig failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActRejCurReqIpv4v6_ENUM, 2);

            IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_CN_REJ,pstPdpActivateRej->enCause);
            return ;
        }

        return ;
    }
    else
    {
        IMSA_CONN_GetConnSelectedCid(enConnType, ucCid);
        ulResult = IMSA_CONN_SipSignalPdpActOrig(enConnType, ucCid, IMSA_IP_TYPE_IPV4);
        if (IMSA_SUCC != ulResult)
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcActRejCurReqIpv4v6:qos not accepted,ipv6,IMSA_CONN_SipSignalPdpActOrig failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActRejCurReqIpv4v6_ENUM, 3);

            IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_CN_REJ,pstPdpActivateRej->enCause);
            return ;
        }

        /* 由于IPV6已经确定不会成功，为了防止后续再尝试IPV6类型，将
           first requst pdn type设置为IPV4 */
        IMSA_CONN_SaveFirstReqPdnType(enConnType, IMSA_IP_TYPE_IPV4);

        return ;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcActRejCurReqIpv4
 Description    : IMSA CONN模块处理PDP ACTIVATE REJ事件，current req pdn type:ipv4
 Input          : enConnType---------------------连接类型
                  pstPdpActivateRej--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-29  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcActRejCurReqIpv4
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU    *pstPdpActivateRej
)
{
    VOS_UINT32                          ulResult            = IMSA_FAIL;
    VOS_UINT8                           ucCid               = IMSA_NULL;

    /* 用户发起IPv4v6类型的PDP激活, 而且被网络拒绝, 原因为28, 协议栈需要
       分别发起IPv4/IPv6类型的PDP激活, 协议栈首先发起IPv4, 再发起IPv6,
       如果IPV4类型的PDP激活再次被网络拒绝, 协议栈还需要尝试IPV6类型的
       PDP激活为了防止PDP激活嵌套, 如果IPv6类型的PDP激活失败, 将不再尝试
       IPv4类型的PDP激活 */
    if (IMSA_PDP_STATE_ACTIVE == IMSA_CONN_GetSipSignalPdpState(enConnType, IMSA_IP_TYPE_IPV6))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcActRejCurReqIpv4:ipv6 already active");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcActRejCurReqIpv4_ENUM, IMSA_IPV6);

        /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
        IMSA_CONN_WaitForIpv6InfoProc(enConnType);
        return ;
    }

    IMSA_CONN_GetConnSelectedCid(enConnType, ucCid);
    ulResult = IMSA_CONN_SipSignalPdpActOrig(enConnType, ucCid, IMSA_IP_TYPE_IPV6);
    if (IMSA_SUCC != ulResult)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcActRejCurReqIpv4:IMSA_CONN_SipSignalPdpActOrig failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActRejCurReqIpv4_ENUM, LNAS_FAIL);

        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_CN_REJ,pstPdpActivateRej->enCause);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ,
                                        (IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16)IMSA_PDN_CnRejCauseProc(pstPdpActivateRej->enCause),
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ);
        #endif
        return ;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcActRejCurReqIpv6
 Description    : IMSA CONN模块处理PDP ACTIVATE REJ事件，current req pdn type:ipv6
 Input          : enConnType---------------------连接类型
                  pstPdpActivateRej--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-29  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcActRejCurReqIpv6
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU    *pstPdpActivateRej
)
{
    if (IMSA_PDP_STATE_ACTIVE == IMSA_CONN_GetSipSignalPdpState(enConnType, IMSA_IP_TYPE_IPV4))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcActRejCurReqIpv6:ipv4 already active");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcActRejCurReqIpv6_ENUM, IMSA_IPV4);

        IMSA_CONN_SetupConnSucc(enConnType);
        return ;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcActRejCurReqIpv6:ipv4 not active,ipv6 rej!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcActRejCurReqIpv6_ENUM, LNAS_FAIL);

        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_CN_REJ,pstPdpActivateRej->enCause);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ,
                                        (IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16)IMSA_PDN_CnRejCauseProc(pstPdpActivateRej->enCause),
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ);
        #endif
        return ;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtPdpActivateCnf
 Description    : IMSA CONN模块处理PDP ACTIVATE CNF事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-25  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtPdpActivateCnf
(
    VOS_VOID                           *pEvtInfo
)
{
    VOS_UINT32                          ulResult            = IMSA_FAIL;
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf   = VOS_NULL_PTR;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = IMSA_CONN_TYPE_BUTT;
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpInfo          = VOS_NULL_PTR;

    /* 初始化 */
    pstPdpActivateCnf  = (TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU*)pEvtInfo;

    IMSA_INFO_LOG1("IMSA_CONN_ProcTafPsEvtPdpActivateCnf is entered! opid:", pstPdpActivateCnf->stCtrl.ucOpId);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcTafPsEvtPdpActivateCnf_ENUM, IMSA_NORMAL_OPID, pstPdpActivateCnf->stCtrl.ucOpId);

    pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
    pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();

    /* 根据OPID查找其关联的连接实体类型 */
    ulResult = IMSA_CONN_GetConnTypeByOpid( pstPdpActivateCnf->stCtrl.ucOpId,
                                            &enConnType);

    /* 如果查找失败，则直接退出 */
    if (IMSA_FAIL == ulResult)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsCallEvtPdpActivateCnf:Get Opid Failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateCnf_ENUM, LNAS_FAIL);
        return IMSA_FAIL;
    }

    /* 不是CONNING状态，则直接退出 */
    if (IMSA_FALSE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_CONNING))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsCallEvtPdpActivateCnf:CONNING state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateCnf_ENUM, IMSA_STATUS_CONNECTING);
        return IMSA_FAIL;
    }

    /* 如果不是缺省承载，则直接丢弃，暂时支持缺省承载类型的SIP信令承载 */
    if (IMSA_OP_TRUE == pstPdpActivateCnf->bitOpLinkdRabId)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsCallEvtPdpActivateCnf:Illegal Bearer Type!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateCnf_ENUM, 1);
        return IMSA_FAIL;
    }

    /* 若没有携带PCSCF地址，需要进行单独处理 */
    if ((IMSA_OP_TRUE != pstPdpActivateCnf->stPcscf.bitOpPrimPcscfAddr) &&
        (IMSA_OP_TRUE != pstPdpActivateCnf->stIpv6Pcscf.bitOpPrimPcscfAddr))
    {
        IMSA_CONN_ProcNoPcscf(enConnType);
        return IMSA_FAIL;
    }


    /* 存储SIP信令承载信息，包括P-CSCF、DNS、IP地址信息等 */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        if (IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM == pstNormalConn->ulSipSignalPdpNum)
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcTafPsCallEvtPdpActivateCnf:signal pdp is already max num!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateCnf_ENUM, 2);
            return IMSA_FAIL;
        }

        pstPdpInfo                      = &pstNormalConn->astSipSignalPdpArray[pstNormalConn->ulSipSignalPdpNum];

        IMSA_CONN_SaveSipSignalPdpInfo( pstPdpInfo, pstPdpActivateCnf);

        pstNormalConn->ulSipSignalPdpNum++;

        /* 如果拨号请求中携带了APN，且承载激活消息中也带了APN，比较两者是否一致 */
        if ((IMSA_OP_TRUE == pstNormalConn->stSelSdfPara.bitOpApn) &&
            (IMSA_OP_TRUE == pstPdpActivateCnf->bitOpApn))
        {
            if (IMSA_FALSE == IMSA_MEM_CMP( &(pstNormalConn->stSelSdfPara.stApnInfo),
                                            &(pstPdpActivateCnf->stApn),
                                            sizeof(TAF_PDP_APN_STRU)))
            {
                pstNormalConn->ucIsApnChanged = IMSA_TRUE;
            }
        }
    }
    else
    {
        pstPdpInfo                      = &pstEmcConn->stSipSignalPdp;

        IMSA_CONN_SaveSipSignalPdpInfo( pstPdpInfo, pstPdpActivateCnf);

        /* 如果拨号请求中携带了APN，且承载激活消息中也带了APN，比较两者是否一致 */
        if ((IMSA_OP_TRUE == pstEmcConn->stSelSdfPara.bitOpApn) &&
            (IMSA_OP_TRUE == pstPdpActivateCnf->bitOpApn))
        {
            if (IMSA_FALSE == IMSA_MEM_CMP( &(pstEmcConn->stSelSdfPara.stApnInfo),
                                            &(pstPdpActivateCnf->stApn),
                                            sizeof(TAF_PDP_APN_STRU)))
            {
                pstEmcConn->ucIsApnChanged = IMSA_TRUE;
            }
        }
    }

    /* 给REG模块配置地址对 */
    IMSA_CONN_ConfigPdpInfo2Reg(enConnType, pstPdpInfo);

    /* 给底软配置IP地址和DNS地址 */
    /* IMSA_CONN_ConfigPdpInfo2Bsp(pstPdpInfo); */

    /* 停止IMS拨号定时器 */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

    /* 给CDS配置下行过滤承载 */
    IMSA_CONN_SndCdsSetImsBearerReq();

    /* 根据PDP类型分别处理*/
    switch ( pstPdpActivateCnf->stPdpAddr.enPdpType )
    {
        case TAF_PDP_IPV4:
            IMSA_CONN_ProcIpv4ActCnf(enConnType, pstPdpActivateCnf);
            break;

        case TAF_PDP_IPV6:
            IMSA_CONN_ProcIpv6ActCnf(enConnType, pstPdpActivateCnf);
            break;

        case TAF_PDP_IPV4V6:
            IMSA_CONN_ProcIpv4v6ActCnf(enConnType);
            break;

        default:
            IMSA_WARN_LOG("IMSA_CONN_ProcTafPsCallEvtPdpActivateCnf:pdp type invaild!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateCnf_ENUM, LNAS_PARAM_INVALID);
            break;
    }

    return IMSA_SUCC;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtPdpActivateRej
 Description    : IMSA CONN模块处理PDP ACTIVATE REJ事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtPdpActivateRej
(
    VOS_VOID                           *pEvtInfo
)
{
    VOS_UINT32                          ulResult            = IMSA_FAIL;
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstPdpActivateRej   = VOS_NULL_PTR;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = IMSA_CONN_TYPE_BUTT;
    IMSA_IP_TYPE_ENUM_UINT8             enFirstReqPdnType   = IMSA_IP_TYPE_BUTT;
    IMSA_IP_TYPE_ENUM_UINT8             enCurReqPdnType     = IMSA_IP_TYPE_BUTT;

    /* 初始化 */
    pstPdpActivateRej  = (TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU*)pEvtInfo;

    IMSA_INFO_LOG1("IMSA_CONN_ProcTafPsEvtPdpActivateRej is entered! opid:", pstPdpActivateRej->stCtrl.ucOpId);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcTafPsEvtPdpActivateRej_ENUM, IMSA_NORMAL_OPID, pstPdpActivateRej->stCtrl.ucOpId);

    /* 根据OPID查找其关联的连接实体类型 */
    ulResult = IMSA_CONN_GetConnTypeByOpid( pstPdpActivateRej->stCtrl.ucOpId,
                                            &enConnType);

    /* 如果查找失败，则直接退出 */
    if (IMSA_FAIL == ulResult)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpActivateRej:Get Conn Type Failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateRej_ENUM, LNAS_FAIL);
        return IMSA_FAIL;
    }

    /* 不是CONNING状态，则直接退出 */
    if (IMSA_FALSE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_CONNING))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpActivateRej:NOT CONNING state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateRej_ENUM, IMSA_STATE_ERROR);
        return IMSA_FAIL;
    }

    /* 停止IMS拨号定时器 */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

    IMSA_CONN_GetConnFirstReqPdnType(enConnType, enFirstReqPdnType);
    IMSA_CONN_GetConnCurReqPdnType(enConnType, enCurReqPdnType);


    IMSA_INFO_LOG1("enFirstReqPdnType:", enFirstReqPdnType);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcTafPsEvtPdpActivateRej_ENUM, IMSA_PDN_TYPE, enFirstReqPdnType);

    /* 临时原因值处理 */
    if (IMSA_HANDLED == IMSA_CONN_ProcTempCause(enConnType, pstPdpActivateRej->enCause))
    {
        return IMSA_SUCC;
    }

    /* Pdn激活超时处理 */
    if (IMSA_HANDLED == IMSA_CONN_ProcTimeOutMaxTimes(enConnType, pstPdpActivateRej->enCause))
    {
        return IMSA_SUCC;
    }

    /* 永久原因值处理 */
    if (IMSA_HANDLED == IMSA_CONN_ProcPermCause(enConnType, pstPdpActivateRej->enCause))
    {
        return IMSA_SUCC;
    }

    /* 如果是IPV4 ONLY、IPV6 ONLY直接上报拨号失败. */
    if (IMSA_IP_TYPE_IPV4V6 != enFirstReqPdnType)
    {
        if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            IMSA_CONN_SetupConnSucc(enConnType);
            return IMSA_SUCC;
        }
        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_CN_REJ, pstPdpActivateRej->enCause);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ,
                                        (IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16)IMSA_PDN_CnRejCauseProc(pstPdpActivateRej->enCause),
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ);
        #endif

        return IMSA_SUCC;
    }

    /* IPV4V6则需要视具体实现分别发起IPv4，IPv6类型的PDP激活 */
    if (IMSA_IP_TYPE_IPV4V6 == enCurReqPdnType)
    {
        IMSA_CONN_ProcActRejCurReqIpv4v6(enConnType, pstPdpActivateRej);
    }
    else if (IMSA_IP_TYPE_IPV4 == enCurReqPdnType)
    {
        IMSA_CONN_ProcActRejCurReqIpv4(enConnType, pstPdpActivateRej);
    }
    else
    {
        IMSA_CONN_ProcActRejCurReqIpv6(enConnType, pstPdpActivateRej);
    }

    return IMSA_SUCC;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtPdpActivateInd
 Description    : IMSA CONN模块处理PDP ACTIVATE IND事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:emc dedicated
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtPdpActivateInd
(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_ACTIVATE_IND_STRU  *pstPdpActivateInd   = VOS_NULL_PTR;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = IMSA_CONN_TYPE_BUTT;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32  enSipPdpType        = IMSA_CONN_SIP_PDP_TYPE_BUTT;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext       = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpActivateInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpActivateInd_ENUM, LNAS_ENTRY);

    /* 初始化 */
    pstPdpActivateInd  = (TAF_PS_CALL_PDP_ACTIVATE_IND_STRU*)pEvtInfo;

    /* 如果不是专有承载，则直接退出 */
    if (IMSA_OP_TRUE != pstPdpActivateInd->bitOpLinkdRabId)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpActivateInd:not dedicated!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateInd_ENUM, 1);
        return IMSA_FAIL;
    }

    /* 获取承载上下文 */
    if (IMSA_SUCC       != IMSA_CONN_GetPdpContextByPdpId(  IMSA_CONN_TYPE_NORMAL,
                                                            pstPdpActivateInd->ucLinkdRabId,
                                                            &enSipPdpType,
                                                            &pstPdpContext))
    {
        if (IMSA_SUCC   != IMSA_CONN_GetPdpContextByPdpId(  IMSA_CONN_TYPE_EMC,
                                                            pstPdpActivateInd->ucLinkdRabId,
                                                            &enSipPdpType,
                                                            &pstPdpContext))
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpActivateInd:Get LinkRabId context failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateInd_ENUM, 2);
            return IMSA_FAIL;
        }
        else
        {
            enConnType          = IMSA_CONN_TYPE_EMC;
        }
    }
    else
    {
        enConnType          = IMSA_CONN_TYPE_NORMAL;
    }

    if (IMSA_CONN_SIP_PDP_TYPE_SIGNAL != enSipPdpType)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpActivateInd:linked pdp is not signal pdp!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateInd_ENUM, 3);
        return IMSA_FAIL;
    }

    /* 不是CONN状态，则直接退出 */
    if (IMSA_FALSE == IMSA_CONN_IsConnStatusEqual(  enConnType,
                                                    IMSA_CONN_STATUS_CONN))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpActivateInd:Not CONN state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpActivateInd_ENUM, IMSA_STATE_ERROR);
        return IMSA_FAIL;
    }

    /* 存储SIP媒体承载信息 */
    IMSA_CONN_SaveSipMediaPdpInfo(enConnType, pstPdpActivateInd);

    if (IMSA_TRUE == IMSA_CONN_IsVoiceMediaPdpType((IMSA_PDP_TFT_INFO_STRU *)&pstPdpActivateInd->stTft,
                                                    pstPdpActivateInd->stEpsQos.ucQCI))
    {

        /* 通知SERVICE模块媒体承载建立成功 */
        IMSA_CONN_SndConnMediaSetupInd(IMSA_CONN_RESULT_SUCCESS,
                                        enConnType,
                                        IMSA_CONN_MEDIA_PDP_TYPE_VOICE);
    }
    else
    {
        /* 通知SERVICE模块媒体承载建立成功 */
        IMSA_CONN_SndConnMediaSetupInd(IMSA_CONN_RESULT_SUCCESS,
                                        enConnType,
                                        IMSA_CONN_MEDIA_PDP_TYPE_VIDEO);
    }

    /* 音频和视频承载配给CDS */
    IMSA_CONN_SndCdsSetImsBearerReq();

    return IMSA_SUCC;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtPdpModifyInd
 Description    : IMSA CONN模块处理PDP MODIFY IND事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtPdpModifyInd
(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_MODIFY_IND_STRU    *pstPdpModifyInd     = VOS_NULL_PTR;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = IMSA_CONN_TYPE_BUTT;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32  enSipPdpType        = IMSA_CONN_SIP_PDP_TYPE_BUTT;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext       = VOS_NULL_PTR;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContextOld    = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpModifyInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpModifyInd_ENUM, LNAS_ENTRY);

    /* 初始化 */
    pstPdpModifyInd     = (TAF_PS_CALL_PDP_MODIFY_IND_STRU*)pEvtInfo;

    if (IMSA_SUCC != IMSA_CONN_GetPdpContextByCidOrPdpId(pstPdpModifyInd->ucCid,
                                                         pstPdpModifyInd->ucRabId,
                                                         &enSipPdpType,
                                                         &pstPdpContext,
                                                         &enConnType))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpModifyInd_ENUM:Get pdp context failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpModifyInd_ENUM, LNAS_FAIL);

        return IMSA_FAIL;
    }

    IMSA_INFO_LOG1("IMSA_CONN_ProcTafPsEvtPdpModifyInd: Conn type :", enConnType);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcTafPsEvtPdpModifyInd_ENUM, IMSA_CONN_TYPE, enConnType);

    /* 如果是IDLE状态，则直接退出 */
    if (IMSA_TRUE       == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_IDLE))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpModifyInd:IDLE state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpModifyInd_ENUM, IMSA_STATUS_IDLE);
        return IMSA_FAIL;
    }

    pstPdpContextOld = IMSA_MEM_ALLOC(sizeof(IMSA_PDP_CNTXT_INFO_STRU));

    if(VOS_NULL_PTR == pstPdpContextOld)
    {
        return IMSA_FAIL;
    }
    /* 备份原有的承载信息 */
    IMSA_MEM_CPY_S( pstPdpContextOld,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU),
                    pstPdpContext,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU));

    /* 修改SIP承载信息 */
    IMSA_CONN_ModifySipPdpInfo(enSipPdpType, pstPdpContext, pstPdpModifyInd);

    /* 如果修改的承载中携带P-CSCF地址,判断当前注册地址是否失效 */
    if (((IMSA_OP_TRUE == pstPdpModifyInd->stPcscf.bitOpPrimPcscfAddr) ||
         (IMSA_OP_TRUE == pstPdpModifyInd->stIpv6Pcscf.bitOpPrimPcscfAddr)))
    {
        IMSA_CONN_ProcPcscfInvalid(enConnType,pstPdpContext,pstPdpContextOld);
    }

    /* 如果是媒体承载，则通知SERVICE媒体承载修改 */
    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == enSipPdpType)
    {
        if (IMSA_TRUE == IMSA_CONN_IsVoiceMediaPdpType(&pstPdpContext->stTft, pstPdpModifyInd->stEpsQos.ucQCI))
        {

            /* 通知SERVICE模块媒体承载建立成功 */
            IMSA_CONN_SndConnMediaPdpModifyInd(enConnType, IMSA_CONN_MEDIA_PDP_TYPE_VOICE);
            /* 给CDS配置下行过滤承载 */
            IMSA_CONN_SndCdsSetImsBearerReq();
        }
        else
        {
            /* 通知SERVICE模块媒体承载建立成功 */
            IMSA_CONN_SndConnMediaPdpModifyInd(enConnType, IMSA_CONN_MEDIA_PDP_TYPE_VIDEO);
        }
    }

    IMSA_MEM_FREE(pstPdpContextOld);

    return IMSA_SUCC;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf
 Description    : IMSA CONN模块处理PDP DEACTIVATE CNF事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf
(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU    *pstPdpDeactivateCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult            = IMSA_FAIL;
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType          = IMSA_CONN_TYPE_BUTT;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType        = IMSA_CONN_SIP_PDP_TYPE_BUTT;
    IMSA_PDP_CNTXT_INFO_STRU               *pstPdpContext       = VOS_NULL_PTR;
    VOS_UINT32                              ulRegParaInvalidFlag= IMSA_NULL;

    pstPdpDeactivateCnf  = (TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU*)pEvtInfo;

    IMSA_INFO_LOG1("IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf is entered! opid:", pstPdpDeactivateCnf->stCtrl.ucOpId);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf_ENUM, IMSA_CONN_TYPE, enConnType);

    /* 根据OPID查找其关联的连接实体类型 */
    ulResult = IMSA_CONN_GetConnTypeByOpid( pstPdpDeactivateCnf->stCtrl.ucOpId,
                                            &enConnType);

    /* 如果查找失败，则直接退出 */
    if (IMSA_FAIL == ulResult)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf:Get Opid Failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf_ENUM, LNAS_FAIL);
        return IMSA_FAIL;
    }

    /* 不是RELEASING状态，则直接退出 */
    if (IMSA_FALSE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_RELEASING))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf:Not releasing state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf_ENUM, IMSA_STATE_ERROR);
        return IMSA_FAIL;
    }

    /* CID不存在，则直接退出 */
    if (IMSA_SUCC != IMSA_CONN_GetPdpContextByCid(  enConnType,
                                                    pstPdpDeactivateCnf->ucCid,
                                                    &enSipPdpType,
                                                    &pstPdpContext))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf:cid not exist!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf_ENUM, 1);
        return IMSA_SUCC;
    }

    /* 如果不是信令承载，则直接退出 */
    if (IMSA_CONN_SIP_PDP_TYPE_SIGNAL != enSipPdpType)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf:Not signal pdp!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpDeactivateCnf_ENUM, 2);
        return IMSA_FAIL;
    }

    /* 停止IMS拨号定时器 */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_END);

    /* 删除信令承载信息 */
    IMSA_CONN_DeletePdpInfo(enConnType, pstPdpDeactivateCnf->ucCid, pstPdpDeactivateCnf->ucRabId, &ulRegParaInvalidFlag);

    if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
    {
        /* 请求APS释放连接 */
        IMSA_CONN_RequestApsRelConn(enConnType);
    }
    else
    {
        IMSA_CONN_ClearConnResourceExeptMedia(enConnType);

        /* 通知SERVICE模块连接释放 */
        IMSA_CONN_SndConnRelInd(enConnType, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
    }

    return IMSA_SUCC;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtPdpDeactivateInd
 Description    : IMSA CONN模块处理PDP DEACTIVATE IND事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:Emc dedicated
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtPdpDeactivateInd
(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU    *pstPdpDeactivateInd = VOS_NULL_PTR;
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType          = IMSA_CONN_TYPE_BUTT;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType        = IMSA_CONN_SIP_PDP_TYPE_BUTT;
    IMSA_PDP_CNTXT_INFO_STRU               *pstPdpContext       = VOS_NULL_PTR;
    VOS_UINT32                              ulRegParaValidFlag  = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, LNAS_ENTRY);

    /* 初始化 */
    pstPdpDeactivateInd = (TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU*)pEvtInfo;

    if (IMSA_SUCC != IMSA_CONN_GetPdpContextByCidOrPdpId(pstPdpDeactivateInd->ucCid,
                                                         pstPdpDeactivateInd->ucRabId,
                                                         &enSipPdpType,
                                                         &pstPdpContext,
                                                         &enConnType))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateInd:Get pdp context failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, LNAS_FAIL);

        return IMSA_FAIL;
    }

     /* 删除承载信息前，备份释放承载的类型和CID */
    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus() ||
        IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_RegSaveRegedPara((IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                            pstPdpDeactivateInd->ucCid,
                            pstPdpDeactivateInd->enPdpType);
    }

    /* 删除承载信息 */
    IMSA_CONN_DeletePdpInfo(enConnType, pstPdpDeactivateInd->ucCid, pstPdpDeactivateInd->ucRabId, &ulRegParaValidFlag);

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == enSipPdpType)
        {
            IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateInd:EMC media");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, IMSA_EMERGENCY);

            IMSA_CONN_SndConnRelInd(enConnType, IMSA_CONN_SIP_PDP_TYPE_MEDIA);

            return IMSA_SUCC;
        }

        IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateInd:EMC sig");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, 1);

        /* 停止IMS拨号定时器 */
        IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_END);

        /* 清除连接资源 */
        /* IMSA_CONN_ClearConnResource(enConnType); */
        /*IMSA_CONN_SetConnStatus(IMSA_CONN_TYPE_EMC, IMSA_CONN_STATUS_IDLE);*/
        /* IMSA_CONN_ClearConnResourceExeptMedia(enConnType); */

        /* IMSA_CONN_SndConnRelInd(enConnType, IMSA_CONN_SIP_PDP_TYPE_SIGNAL); */
        if (IMSA_CONN_STATUS_CONNING == IMSA_CONN_GetEmcConnStatus())
        {
            /* 通知SERVICE模块建立失败 */
            IMSA_CONN_SetupConnFail(  enConnType,
                                      IMSA_CONN_RESULT_FAIL_TIMER_EXP,
                                      (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);
        }
        else
        {
            /* 通知SERVICE模块连接释放 */
            IMSA_CONN_ClearConnResourceExeptMedia(enConnType);
            IMSA_CONN_SndConnRelInd(enConnType, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        }

        return IMSA_SUCC;
    }

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateInd:MEDIA");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, 2);

        IMSA_CONN_SndConnRelInd(enConnType, IMSA_CONN_SIP_PDP_TYPE_MEDIA);

        return IMSA_SUCC;
    }

    if (IMSA_CONN_STATUS_CONNING == IMSA_CONN_GetNormalConnStatus())
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateInd:normal,conning");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, IMSA_STATUS_CONNECTING);
        /* 停止等待IPV6参数定时器 */
        /* IMSA_CONN_StopTimer(enConnType, TI_IMSA_WAIT_IPV6_INFO);
        IMSA_CONN_ClearConnResourceExeptMedia(enConnType);
        IMSA_CONN_SndConnRelInd(enConnType, IMSA_CONN_SIP_PDP_TYPE_SIGNAL); */

        if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            /* 两个信令承载，IPV4激活成功，IPV6等待前缀。如果去激活IPV4，
               等待IPV6前缀定时器在运行，则继续等待IPV6前缀；如果去激活IPV6，
               则发送建立成功 */
            if (IMSA_TRUE == IMSA_IsTimerRunning(IMSA_CONN_GetNormalConnProtectTimerAddr()))
            {
                IMSA_CONN_WaitForIpv6InfoProc(enConnType);
            }
            else
            {
                IMSA_CONN_SetupConnSucc(IMSA_CONN_TYPE_NORMAL);
            }
        }
        else
        {
            /* 一个信令承载，IPV4或IPV6，在建立过程中被去激活，则发送建立失败 */
            IMSA_CONN_SetupConnFail(  enConnType,
                                      IMSA_CONN_RESULT_FAIL_TIMER_EXP,
                                      (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);
        }

        return IMSA_SUCC;
    }

    if (IMSA_CONN_STATUS_RELEASING == IMSA_CONN_GetNormalConnStatus())
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateInd:normal,releasing");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, IMSA_STATUS_RELEASING);

        if (IMSA_TRUE != IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            /* 停止IMS拨号定时器 */
            IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_END);

            /* 清除连接资源 */
            IMSA_CONN_ClearConnResourceExeptMedia(enConnType);

            /* 通知SERVICE模块连接释放 */
            IMSA_CONN_SndConnRelInd(enConnType, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        }

        return IMSA_SUCC;
    }

    if (IMSA_TRUE != IMSA_CONN_HasActiveSipSignalPdp(enConnType))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateInd:normal,conn,no active pdp!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, 3);

        /* 清除连接资源 */
        /* IMSA_CONN_ClearConnResource(enConnType); */
        /*IMSA_CONN_SetConnStatus(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_STATUS_IDLE);*/
        IMSA_CONN_ClearConnResourceExeptMedia(enConnType);

        /* 通知SERVICE模块连接释放 */
        IMSA_CONN_SndConnRelInd(enConnType, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return IMSA_SUCC;
    }

    /* 如果注册参数失效，且还有其他激活的信令承载时，通知SERVICE模块注册参数失效 */
    if (IMSA_CONN_REG_PARA_INVALID == ulRegParaValidFlag)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpDeactivateInd:normal,conn,active pdp,reg para invalid!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpDeactivateInd_ENUM, LNAS_PARAM_INVALID);

        IMSA_CONN_SndConnRegParaInvalid();

        return IMSA_SUCC;
    }

    return IMSA_SUCC;
}

/* lihong00150010 ims begin 2013-01-08 防止网侧重播路由公告 */
/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd
 Description    : IMSA CONN模块处理PDP IPV6 INFO IND事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_IsIpv6PrefixChanged
(
    const IMSA_PDP_CNTXT_INFO_STRU             *pstPdpInfo,
    const TAF_PS_IPV6_INFO_IND_STRU            *pstIpv6InfoInd
)
{
    if (0 == IMSA_MEM_CMP(  pstPdpInfo->stPdpAddr.aucIpV6Addr,
                            pstIpv6InfoInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                            IMSA_IPV6_PREFIX_LEN))
    {
        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}
/* lihong00150010 ims end 2013-01-08 防止网侧重播路由公告 */

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd
 Description    : IMSA CONN模块处理PDP IPV6 INFO IND事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd
(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_IPV6_INFO_IND_STRU          *pstPsIpv6InfoInd    = VOS_NULL_PTR;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = IMSA_CONN_TYPE_BUTT;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32  enSipPdpType        = IMSA_CONN_SIP_PDP_TYPE_BUTT;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext       = VOS_NULL_PTR;
    VOS_CHAR                            acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd_ENUM, LNAS_ENTRY);

    /* 初始化 */
    pstPsIpv6InfoInd     = (TAF_PS_IPV6_INFO_IND_STRU*)pEvtInfo;

    /* 如果没有携带前缀信息，则直接退出 */
    if (0 == pstPsIpv6InfoInd->stIpv6RaInfo.ulPrefixNum)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd:No prefix!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd_ENUM, 1);
        return IMSA_FAIL;
    }

    /* 获取承载上下文 */
    if (IMSA_SUCC       != IMSA_CONN_GetPdpContextByPdpId(  IMSA_CONN_TYPE_NORMAL,
                                                            pstPsIpv6InfoInd->ucRabId,
                                                            &enSipPdpType,
                                                            &pstPdpContext))
    {
        if (IMSA_SUCC   != IMSA_CONN_GetPdpContextByPdpId(  IMSA_CONN_TYPE_EMC,
                                                            pstPsIpv6InfoInd->ucRabId,
                                                            &enSipPdpType,
                                                            &pstPdpContext))
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd:Get pdp context failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd_ENUM, LNAS_FAIL);
            return IMSA_FAIL;
        }
        else
        {
            enConnType  = IMSA_CONN_TYPE_EMC;
        }
    }
    else
    {
        enConnType      = IMSA_CONN_TYPE_NORMAL;
    }

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == enSipPdpType)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd:not signal pdp type!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd_ENUM, 2);
        return IMSA_FAIL;
    }

    /* 如果是CONN状态，则更新PDP上下文 */
    if (IMSA_TRUE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_CONN))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpModifyInd:CONN state!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd_ENUM, IMSA_STATUS_CONN);

        /* 存储IPV6信息 */
        /* lihong00150010 ims begin 2013-01-08 防止网侧重播路由公告 */
        if (IMSA_TRUE == IMSA_CONN_IsIpv6PrefixChanged(pstPdpContext, pstPsIpv6InfoInd))
        {
            IMSA_CONN_SaveIpv6Info(pstPdpContext, pstPsIpv6InfoInd);

            /* 给REG模块配置IPV6地址 */
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpContext->stPdpAddr.aucIpV6Addr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                    IMSA_IP_TYPE_IPV6,
                                                    acUeAddr);

            /* 给底软配置IPv6地址和IPv6 DNS地址 */
            /* IMSA_CONN_ConfigPdpIPv6Info2Bsp(pstPdpContext); */
        }
        /* lihong00150010 ims end 2013-01-08 防止网侧重播路由公告 */

        return IMSA_SUCC;
    }

    /* 如果是CONNING状态，则更新PDP上下文，通知SERVICE连接建立成功 */
    if (IMSA_TRUE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_CONNING))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtPdpModifyInd:CONNING state!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtPdpIpv6InfoInd_ENUM, IMSA_STATUS_CONNECTING);

        /* 存储IPV6信息 */
        /* lihong00150010 ims begin 2013-01-08 防止网侧重播路由公告 */
        if (IMSA_TRUE == IMSA_CONN_IsIpv6PrefixChanged(pstPdpContext, pstPsIpv6InfoInd))
        {
            IMSA_CONN_SaveIpv6Info(pstPdpContext, pstPsIpv6InfoInd);

            /* 给REG模块配置IPV6地址 */
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpContext->stPdpAddr.aucIpV6Addr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                    IMSA_IP_TYPE_IPV6,
                                                    acUeAddr);

            /* 给底软配置IPv6地址和IPv6 DNS地址 */
            /* IMSA_CONN_ConfigPdpIPv6Info2Bsp(pstPdpContext); */
        }
        /* lihong00150010 ims end 2013-01-08 防止网侧重播路由公告 */

        /* 如果当前还在请求IPV4的SIP信令承载建立，则等待IPV4信令承载建立完成后
           再通知SERVICE模块连接建立成功 */
        if (IMSA_TRUE == IMSA_CONN_IsEqualToSelectedCid(enConnType, pstPsIpv6InfoInd->ucCid))
        {
            /* 通知SERIVCE连接建立成功 */
            IMSA_CONN_SetupConnSucc(enConnType);
        }
        /*等待IPV4的SIP信令承载建立，如果已经建立完成，则通知SERVICE模块连接建立成功*/
        else
        {
            IMSA_CONN_WaitForIpv4PDPActiveCNF(enConnType);
        }

        /* 停止等待IPV6参数定时器 */
        IMSA_CONN_StopTimer(enConnType, TI_IMSA_WAIT_IPV6_INFO);

        return IMSA_SUCC;
    }

    return IMSA_FAIL;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtCallOrigCnf
 Description    : IMSA CONN模块处理CALL ORIG CNF事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-25  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtCallOrigCnf
(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_ORIG_CNF_STRU          *pstCallOrigCnf  = VOS_NULL_PTR;
    VOS_UINT32                          ulResult        = IMSA_FAIL;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType      = IMSA_CONN_TYPE_BUTT;

    pstCallOrigCnf  = (TAF_PS_CALL_ORIG_CNF_STRU*)pEvtInfo;

    IMSA_INFO_LOG1("IMSA_CONN_ProcTafPsEvtCallOrigCnf is entered! opid:", pstCallOrigCnf->stCtrl.ucOpId);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcTafPsEvtCallOrigCnf_ENUM, IMSA_NORMAL_OPID, pstCallOrigCnf->stCtrl.ucOpId);

    /* 根据OPID查找其关联的连接实体类型 */
    ulResult = IMSA_CONN_GetConnTypeByOpid( pstCallOrigCnf->stCtrl.ucOpId,
                                            &enConnType);

    /* 如果查找失败，则直接退出 */
    if (IMSA_FAIL == ulResult)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtCallOrigCnf:Get Opid Failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtCallOrigCnf_ENUM, LNAS_FAIL);
        return IMSA_FAIL;
    }

    /* 不是CONNING状态，则直接退出 */
    if (IMSA_FALSE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_CONNING))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtCallOrigCnf:Not CONNING state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtCallOrigCnf_ENUM, IMSA_STATE_ERROR);
        return IMSA_FAIL;
    }

    /* APS参数检查正确，直接退出 */
    if (TAF_PS_CAUSE_SUCCESS == pstCallOrigCnf->enCause)
    {
        return IMSA_SUCC;
    }

    /* 停止IMS拨号定时器 */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

    if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
    {
        /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
        IMSA_CONN_WaitForIpv6InfoProc(enConnType);

        return IMSA_SUCC;
    }

    /* 给SERVICE回复IMSA_CONN_SETUP_IND消息，如果是TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT，
           则结果值填为FAIL_PDP_ACTIVATE_LIMIT，否则填为FAIL_PARA_ERR */
    if (TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT == pstCallOrigCnf->enCause)
    {
        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_PDP_ACTIVATE_LIMIT, (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_PDP_ACTIVATE_LIMIT,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDP_ACTIVATE_LIMIT);
        #endif
    }
    else if (TAF_PS_CAUSE_OPERATION_CONFLICT == pstCallOrigCnf->enCause)
    {
        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING, (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_SAME_APN_OPERATING,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SAME_APN_OPERATING);
        #endif
    }
    else
    {
        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_PARA_ERR, (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_PARA_ERR,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDP_CONTEXT_PARA_ERR);

        #endif
    }

    return IMSA_SUCC;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtCallEndCnf
 Description    : IMSA CONN模块处理CALL END事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-02  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtCallEndCnf
(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_END_CNF_STRU           *pstCallEndCnf           = VOS_NULL_PTR;
    VOS_UINT32                          ulResult                = IMSA_FAIL;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType              = IMSA_CONN_TYPE_BUTT;
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32  enSipPdpType            = IMSA_CONN_SIP_PDP_TYPE_BUTT;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext           = VOS_NULL_PTR;
    VOS_UINT32                          ulRegParaInvalidFlag    = IMSA_NULL;

    pstCallEndCnf  = (TAF_PS_CALL_END_CNF_STRU*)pEvtInfo;

    IMSA_INFO_LOG1("IMSA_CONN_ProcTafPsEvtCallEndCnf is entered! opid:",pstCallEndCnf->stCtrl.ucOpId);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcTafPsEvtCallEndCnf_ENUM, IMSA_NORMAL_OPID, pstCallEndCnf->stCtrl.ucOpId);

    /* 根据OPID查找其关联的连接实体类型 */
    ulResult = IMSA_CONN_GetConnTypeByOpid( pstCallEndCnf->stCtrl.ucOpId,
                                            &enConnType);

    /* 如果查找失败，则直接退出 */
    if (IMSA_FAIL == ulResult)
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtCallEndCnf:Get Opid Failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtCallEndCnf_ENUM, LNAS_FAIL);
        return IMSA_FAIL;
    }

    /* 不是RELEASING状态，则直接退出 */
    if (IMSA_FALSE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_RELEASING))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtCallEndCnf:Not releasing state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtCallEndCnf_ENUM, IMSA_STATE_ERROR);
        return IMSA_FAIL;
    }

    /* APS参数检查正确，直接退出 */
    if (TAF_PS_CAUSE_SUCCESS == pstCallEndCnf->enCause)
    {
        return IMSA_SUCC;
    }

    /* CID不存在，则直接退出 */
    if (IMSA_SUCC != IMSA_CONN_GetPdpContextByCid(  enConnType,
                                                    pstCallEndCnf->ucCid,
                                                    &enSipPdpType,
                                                    &pstPdpContext))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTafPsEvtCallEndCnf:cid not exist!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTafPsEvtCallEndCnf_ENUM, IMSA_CID_ERROR);
        return IMSA_SUCC;
    }

    /* 停止IMS拨号定时器 */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_END);

    /* 删除信令承载信息 */
    IMSA_CONN_DeletePdpInfo(enConnType, pstCallEndCnf->ucCid, 0, &ulRegParaInvalidFlag);

    if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
    {
        /* 请求APS释放连接 */
        IMSA_CONN_RequestApsRelConn(enConnType);
    }

    return IMSA_SUCC;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTafPsEvtSrvccCancelInd
 Description    : IMSA CONN模块处理SRVCC CANCEL事件
 Input          : pEvtInfo--------------事件信息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-10-14  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTafPsEvtSrvccCancelInd
(
    VOS_VOID                           *pEvtInfo
)
{
    IMSA_INFO_LOG("IMSA_CONN_ProcTafPsEvtSrvccCancelInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTafPsEvtSrvccCancelInd_ENUM, LNAS_ENTRY);

    (VOS_VOID)pEvtInfo;

    /*清除等待异系统指示标示*/
    IMSA_CallSetSrvccFlag(IMSA_FALSE);

    /* 清除不能上报ALL RELEASED事件标识 */
    IMSA_CallSetNotReportAllReleasedFlag(IMSA_FALSE);

    /*收到该消息时，终端的异系统流程还没有启动，出了通知IMS和AT上报，不需要做特殊处理*/

    /*收到ESM/SM Notification ind事件，需要通知IMS协议栈发起re-invite流程*/
    (VOS_VOID)IMSA_CallSendImsMsgSrvcc(IMSA_IMS_INPUT_CALL_REASON_SRVCC_CANCELED);

    /*上报HO失败*/
    IMSA_SndMsgAtCirephInd(AT_IMSA_SRVCC_HANDOVER_FAILURE);

    return IMSA_SUCC;
}


/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp
 Description    : TI_IMSA_SIP_SIGAL_PDP_ORIG定时器超时处理函数
 Input          : pMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-02  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp
(
    const VOS_VOID                     *pMsg
)
{
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType = IMSA_CONN_TYPE_BUTT;

    IMSA_INFO_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp_ENUM, LNAS_ENTRY);

    enConnType = PS_GET_REL_TIMER_PARA(pMsg);

    if (enConnType >= IMSA_CONN_TYPE_BUTT)
    {
        IMSA_ERR_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp:Illegal Para!");
        return ;
    }

    /* 不是CONNING状态，则直接退出 */
    if (IMSA_FALSE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_CONNING))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp:Not CONNING state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp_ENUM, IMSA_STATE_ERROR);
        return ;
    }

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp:EMC,conning!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp_ENUM, IMSA_STATUS_CONNECTING);

        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_TIMER_EXP, (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);

        return ;
    }

    IMSA_INFO_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp:normal,conning!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp_ENUM, IMSA_NORMAL);
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTimerMsgSipSignalPdpOrigExp_ENUM, IMSA_STATUS_CONNECTING);

    if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
    {
        /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器 */
        IMSA_CONN_WaitForIpv6InfoProc(enConnType);
    }
    else
    {
        /* 判断临时被禁特性控制开关是否打开 */
        if (IMSA_TRUE == IMSA_GetTempForbFetureCtrlFlag())
        {
            IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_TEMP_FORBIDDEN, (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);
        }
        else
        {
            IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_TIMER_EXP, (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);
        }

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ORIG_TIMER_EXP,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SIP_SIGAL_PDP_ORIG_TIMER_EXP);
        #endif
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp
 Description    : TI_IMSA_SIP_SIGAL_PDP_END定时器超时处理函数
 Input          : pMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-02  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp
(
    const VOS_VOID                     *pMsg
)
{
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType              = IMSA_CONN_TYPE_BUTT;
    VOS_UINT32                          ulRegParaInvalidFlag    = IMSA_NULL;
    IMSA_NORMAL_CONN_STRU              *pstNormalConn           = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn              = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp_ENUM, LNAS_ENTRY);

    enConnType = PS_GET_REL_TIMER_PARA(pMsg);

    if (enConnType >= IMSA_CONN_TYPE_BUTT)
    {
        IMSA_ERR_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp:Illegal Para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp_ENUM, LNAS_PARAM_INVALID);

        return ;
    }

    /* 不是RELEASING状态，则直接退出 */
    if (IMSA_FALSE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_RELEASING))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp:Not releasing state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp_ENUM, IMSA_STATE_ERROR);
        return ;
    }

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstNormalConn   = IMSA_CONN_GetNormalConnAddr();

        /* 删除信令承载信息 */
        IMSA_CONN_DeletePdpInfo(    enConnType,
                                    pstNormalConn->astSipSignalPdpArray[0].ucCid,
                                    pstNormalConn->astSipSignalPdpArray[0].ucPdpId,
                                    &ulRegParaInvalidFlag);
    }
    else
    {
        pstEmcConn      = IMSA_CONN_GetEmcConnAddr();

        /* 删除信令承载信息 */
        IMSA_CONN_DeletePdpInfo(    enConnType,
                                    pstEmcConn->stSipSignalPdp.ucCid,
                                    pstEmcConn->stSipSignalPdp.ucPdpId,
                                    &ulRegParaInvalidFlag);
    }

    if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
    {
        /* 请求APS释放连接 */
        IMSA_CONN_RequestApsRelConn(enConnType);
    }
    else
    {
        IMSA_CONN_ClearConnResourceExeptMedia(enConnType);

        /* 通知SERVICE模块连接释放 */
        IMSA_CONN_SndConnRelInd(enConnType, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTimerMsgWaitIpv6InfoExp
 Description    : TI_IMSA_WAIT_IPV6_INFO定时器超时处理函数
 Input          : pMsg--------------消息指针
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-02  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcTimerMsgWaitIpv6InfoExp
(
    const VOS_VOID                     *pMsg
)
{
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType              = IMSA_CONN_TYPE_BUTT;

    IMSA_INFO_LOG("IMSA_CONN_ProcTimerMsgWaitIpv6InfoExp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcTimerMsgWaitIpv6InfoExp_ENUM, LNAS_ENTRY);

    enConnType = PS_GET_REL_TIMER_PARA(pMsg);

    if (enConnType >= IMSA_CONN_TYPE_BUTT)
    {
        IMSA_ERR_LOG("IMSA_CONN_ProcTimerMsgWaitIpv6InfoExp:Illegal Para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcTimerMsgWaitIpv6InfoExp_ENUM, LNAS_PARAM_INVALID);

        return ;
    }

    /* 不是CONNING状态，则直接退出 */
    if (IMSA_FALSE == IMSA_CONN_IsConnStatusEqual(enConnType, IMSA_CONN_STATUS_CONNING))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp:Not CONNING state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTimerMsgWaitIpv6InfoExp_ENUM, IMSA_STATE_ERROR);
        return ;
    }

    if ((IMSA_PDP_STATE_ACTIVE == IMSA_CONN_GetSipSignalPdpState(enConnType, IMSA_IP_TYPE_IPV4))
        || (IMSA_PDP_STATE_ACTIVE == IMSA_CONN_GetSipSignalPdpState(enConnType, IMSA_IP_TYPE_IPV4V6)))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcTimerMsgSipSignalPdpEndExp:IPV4 OR IPV4V6 PDP!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTimerMsgWaitIpv6InfoExp_ENUM, 1);

        IMSA_CONN_SetupConnSucc(enConnType);
    }
    else
    {
        #if (FEATURE_ON == FEATURE_PTM)
        /* 等删除旧的CHR时，需要修改IMSA_PDN_CnRejCauseProc函数的返回值类型 */
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_TIMER_WAIT_IPV6_INFO_EXP,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_WAIT_IPV6_INFO_TIMER_EXP);
        #endif
        if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            /* 请求APS释放连接 */
            IMSA_CONN_RequestApsRelConn(enConnType);
        }

        IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_TIMER_EXP, (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTempCause
 Description    : Pdn临时被拒原因值处理
 Input          : enConnType--------------Conn类型
                  enCause-----------------Rej类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTempCause
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    /* 紧急不能被禁 */
    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        return IMSA_NOT_HANDLED;
    }

    /* 临时被禁特性不打开 */
    if(IMSA_FALSE == IMSA_GetTempForbFetureCtrlFlag())
    {
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTempCause_ENUM, IMSA_IMPROVEMENT_CLOSED);
        return IMSA_NOT_HANDLED;
    }

    /* 原因值不在临时被禁NV配置列表中 */
    if (IMSA_FALSE == IMSA_IsCauseInPdnTempRejCauseList(enCause))
    {
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTempCause_ENUM, IMSA_NOT_IN_CAUSE_LIST);
        return IMSA_NOT_HANDLED;
    }

    /* 如果有其他信令承载激活，则临时被禁不生效 */
    if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
    {
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTempCause_ENUM, IMSA_HAS_ACTIVE_SIP_SIGNAL_PDP);
        return IMSA_NOT_HANDLED;
    }

    /* 抛出可维可测 */
    IMSA_SndOmConnForbiddenInfo(IMSA_OM_PDN_REJ_CAUSE_IN_TEMP_LIST);

    IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_TEMP_FORBIDDEN, enCause);

    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_PdnConnFailErrLogRecord(   enConnType,
                                    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ,
                                    (IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16)IMSA_PDN_CnRejCauseProc(enCause),
                                    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ);
    #endif

    return IMSA_HANDLED;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcTimeOutMaxTimes
 Description    : Pdn建立超时处理
 Input          : enConnType--------------Conn类型
                  enCause-----------------Rej类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcTimeOutMaxTimes
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    /* 紧急不能被禁 */
    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        return IMSA_NOT_HANDLED;
    }

    /* 临时被禁特性不打开 */
    if (IMSA_FALSE == IMSA_GetTempForbFetureCtrlFlag())
    {
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTimeOutMaxTimes_ENUM, IMSA_IMPROVEMENT_CLOSED);
        return IMSA_NOT_HANDLED;
    }

    if (TAF_PS_CAUSE_SM_MAX_TIME_OUT != enCause)
    {
        return IMSA_NOT_HANDLED;
    }

    /* 如果有其他信令承载激活，则临时被禁不生效 */
    if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
    {
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcTimeOutMaxTimes_ENUM, IMSA_HAS_ACTIVE_SIP_SIGNAL_PDP);
        return IMSA_NOT_HANDLED;
    }

    /* 抛出可维可测 */
    IMSA_SndOmConnForbiddenInfo(IMSA_OM_PDN_TIMER_OUT_MAX_TIMES);

    IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_TEMP_FORBIDDEN, enCause);

    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_PdnConnFailErrLogRecord(   enConnType,
                                    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ,
                                    (IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16)IMSA_PDN_CnRejCauseProc(enCause),
                                    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ);
    #endif

    return IMSA_HANDLED;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcPermCause
 Description    : Pdn临时被拒原因值处理
 Input          : enConnType--------------Conn类型
                  enCause-----------------Rej类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CONN_ProcPermCause
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    /* 紧急不能被禁 */
    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        return IMSA_NOT_HANDLED;
    }

    /* 恒定被禁特性不打开 */
    if (IMSA_FALSE == IMSA_GetPermForbFetureCtrlFlag())
    {
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcPermCause_ENUM, IMSA_IMPROVEMENT_CLOSED);
        return IMSA_NOT_HANDLED;
    }

    /* 原因值不在恒定被禁NV配置列表中 */
    if (IMSA_FALSE == IMSA_IsCauseInPdnPermRejCauseList(enCause))
    {
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcPermCause_ENUM, IMSA_NOT_IN_CAUSE_LIST);
        return IMSA_NOT_HANDLED;
    }

    /* 如果有其他信令承载激活，则临时被禁不生效 */
    if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
    {
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcPermCause_ENUM, IMSA_HAS_ACTIVE_SIP_SIGNAL_PDP);
        return IMSA_NOT_HANDLED;
    }

    /* 抛出可维可测 */
    IMSA_SndOmConnForbiddenInfo(IMSA_OM_PDN_REJ_CAUSE_IN_PERM_LIST);

    IMSA_CONN_SetupConnFail(enConnType, IMSA_CONN_RESULT_FAIL_PERM_FORBIDDEN, enCause);

    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_PdnConnFailErrLogRecord(   enConnType,
                                    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ,
                                    (IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16)IMSA_PDN_CnRejCauseProc(enCause),
                                    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ);
    #endif

    return IMSA_HANDLED;
}

/*****************************************************************************
 Function Name  : IMSA_CONN_ProcNoPcscf
 Description    : 收到PDP ACTIVE CNF但是没有PCSCF地址处理
 Input          : enConnType--------------Conn类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONN_ProcNoPcscf
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo       = VOS_NULL_PTR;
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid          = IMSA_NULL;
    IMSA_CONN_RESULT_ENUM_UINT32        enResult        = IMSA_CONN_RESULT_FAIL_PARA_ERR;
    VOS_UINT8                           ucCid           = 0;

    pstNwInfo       = IMSA_GetNetInfoAddress();
    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();
    pstEmcConn      = IMSA_CONN_GetEmcConnAddr();

    /* 判断是否有IPV6信令承载激活，如果有，则返回建链成功，释放当前激活的承载，停止定时器； */
    if (IMSA_PDP_STATE_ACTIVE == IMSA_CONN_GetSipSignalPdpState(enConnType, IMSA_IP_TYPE_IPV6))
    {
        /* 停止IMS拨号定时器 */
        IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

        /* 如果IPV6全局地址已获得，回复连接建立成功；否则启动等待IPV6参数定时器
           备注:如果是IPV4V6发起请求，先激活IPV6之后，不会启动等待IPV6前缀定时器，
           而是会在建立IPV4之后才启动 */
        IMSA_CONN_WaitForIpv6InfoProc(enConnType);

        /* 请求APS释放连接 */
        IMSA_CONN_AssignOpid(enConnType, &ucOpid);

        if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                        pstNormalConn->stSelSdfPara.ucCid))
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcNoPcscf:normal,conninig,CallEnd failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcNoPcscf_ENUM, IMSA_CallEndFail);
        }

        return ;
    }

    /* 判断是否有IPV4信令承载激活，如果有，则返回建链成功，释放当前激活的承载，停止定时器； */
    if (IMSA_PDP_STATE_ACTIVE == IMSA_CONN_GetSipSignalPdpState(enConnType, IMSA_IP_TYPE_IPV4))
    {
        IMSA_CONN_SetupConnSucc(enConnType);

        /* 停止IMS拨号定时器 */
        IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

        /* 请求APS释放连接 */
        IMSA_CONN_AssignOpid(enConnType, &ucOpid);

        if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                        pstNormalConn->stSelSdfPara.ucCid))
        {
            IMSA_WARN_LOG("IMSA_CONN_ProcNoPcscf:normal,conninig,CallEnd failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcNoPcscf_ENUM, IMSA_CallEndFail);
        }

        return ;
    }

    /*  如果没有其他激活承载，再判断是在LTE模且是普通信令承载，则释放当前承载，
        返回连接失败，原因值为永久禁止;如果是在GU模或者LTE模且是紧急信令承载，
        则释放当前承载，返回连接失败，原因值为IMSA_CONN_RESULT_FAIL_PARA_ERR */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        if (IMSA_CAMPED_RAT_TYPE_EUTRAN == pstNwInfo->enImsaCampedRatType)
        {
            enResult = IMSA_CONN_RESULT_FAIL_PERM_FORBIDDEN;
        }

        ucCid = pstNormalConn->stSelSdfPara.ucCid;
    }
    else
    {
        ucCid = pstEmcConn->stSelSdfPara.ucCid;
    }

    /* 停止IMS拨号定时器 */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

    /* 请求APS释放连接 */
    IMSA_CONN_AssignOpid(enConnType, &ucOpid);

    if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                    ucCid))
    {
        IMSA_WARN_LOG("IMSA_CONN_ProcNoPcscf:normal,CallEnd failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_ProcNoPcscf_ENUM, IMSA_CallEndFail);
    }

    /* 返回连接失败，原因值为永久禁止 */
    IMSA_CONN_SetupConnFail(enConnType, enResult, (TAF_PS_CAUSE_ENUM_UINT32)TAF_PS_CAUSE_BUTT);

    return ;
}

/*lint +e961*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcApsMsg.c*/



