/************************************************************************
*                                                                      *
*                             ppp_perf.c                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2013/04/17                                      *
*  Author:             wangyong                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP模块性能统计                                 *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_PERF_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/



/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */


VOID PPP_PerfStatisticByReleaseCode(PPPINFO_S *pstPppInfo)
{
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = NULL;
    VOS_UINT32 ulResult = 0;

    if (NULL == pstPppInfo)
    {
        PPPC_ERROR_LOG(
                     "\r\n [ppp]PPP_PerfStatisticByReleaseCode:  pstPppInfo=NULL!");
        return;
    }

    /*获取rp上下文*/
    ulResult = (VOS_UINT32)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOID**)&pstRpContext);
    if ((SDB_SUCCESS != ulResult) || (NULL == pstRpContext))
    {
        PPPC_WARNING_LOG1(
                     "\r\n PPP_PerfStatisticByReleaseCode: User %u isn't exist!", pstPppInfo->ulRPIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_540);
        return;
    }

    switch (pstRpContext->ulReleaseCode)
    {
        case AM_RELCODE_LAP_ALLOC_FAIL:
        case AM_RELCODE_LAP_NO_FREE_IP:                  /* 没有空闲地址 */
        case AM_RELCODE_LAP_CONFLICT:                    /* 静态地址冲突 */
        case AM_RELCODE_LAP_RECYLE:                      /* 地址回收 */
            PPP_DBG_OK_CNT(PPP_PHOK_1208);
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_ALLOC_IP_FAIL);
            break;
        default:
            PPP_DBG_OK_CNT(PPP_PHOK_1209);
            break;
    }

    return;
}


#define ___PPP_HSGW___

VOID SNMP_LCPPhaseProcForEhrpd(PPPINFO_S *pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        PPPC_ERROR_LOG(
                     "\r\n [ppp]SNMP_LCPPhaseProcForEhrpd:  pstPppInfo=NULL!");
        return;
    }

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_LCP_NEGOFAIL:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_NEGO_FAIL,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_NEGOFAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1210);
            break;
        }

        case FSM_ALARM_LCP_MS_NO_RSP:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_NO_RESPONSE,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_MS_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1211);
            break;
        }

        case FSM_ALARM_LCP_PCF_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_REL_A10,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1212);
            break;
        }

        case FSM_ALARM_LCP_MS_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_MS_TERM,
                                           pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                           1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_MS_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1213);
            break;
        }
        case FSM_ALARM_LCP_OTHER:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_OTHER,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1214);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_541);
            PPPC_INFO_LOG4("\r\n[SNMP_LCPPhaseProcForEhrpd]:LCP failtype = %u, bReNego = %u, bIpcpSucFlag = %u, bIPTech = %u, ",
                pstPppInfo->ucFSMFailType,
                pstPppInfo->bReNego,
                pstPppInfo->bIpcpSucFlag,
                pstPppInfo->bIPTech);
            PPPC_INFO_LOG3("bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                pstPppInfo->bAuthClient,
                pstPppInfo->bAuthServer,
                pstPppInfo->bPppMode);
            break;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1215);
#if 0
    A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM,
                                    pstPppInfo->ulPcfIP,
                                    A11_PERF_OPERATOR_PLUS,
                                    1);
#endif
    if (VOS_TRUE != pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1216);
#if 0
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM,
                                        pstPppInfo->ulPcfIP,
                                        A11_PERF_OPERATOR_PLUS,
                                        1);
#endif
    }

    return;
}

VOID SNMP_AuthPhaseProcForEhrpd(PPPINFO_S *pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        PPPC_ERROR_LOG(
                     "\r\n [ppp]SNMP_AuthPhaseProcForEhrpd:  pstPppInfo=NULL!");
        return;
    }

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_AUTH_PCF_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_REL_A10,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1217);
            break;
        }

        case FSM_ALARM_AUTH_MS_NO_RSP:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_MS_NO_REPONSE,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_MS_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1218);
            break;
        }

        case FSM_ALARM_AUTH_MS_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_MS_TERM,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_MS_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1219);
            break;
        }
        case FSM_ALARM_AUTH_AAA_NO_RSP:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_AAA_NO_REPONSE,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_AAA_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1220);
            break;
        }
        case FSM_ALARM_AUTH_OTHER:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_OTHER,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1221);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_542);
            return;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1222);
#if 0
    A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM,
                                    pstPppInfo->ulPcfIP,
                                    A11_PERF_OPERATOR_PLUS,
                                    1);
#endif
    if (VOS_TRUE != pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1223);
#if 0
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM,
                                        pstPppInfo->ulPcfIP,
                                        A11_PERF_OPERATOR_PLUS,
                                        1);
#endif
    }


    return;
}


VOID SNMP_GetFailReasonByReleaseCode(VOS_UINT32 ulReleaseCode, UCHAR *pucFailType)
{
    if ( NULL == pucFailType )
    {
        return;
    }

    switch ( ulReleaseCode )
    {

        case AM_RELCODE_PDN_PCRF_ACT_FAIL :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL;
            break;

        case AM_RELCODE_PDN_PCRF_ACT_TIMOUT :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP;
            break;

        case AM_RELCODE_PDN_PCRF_UPD_FAIL :
        case AM_RELCODE_PDN_PCRF_UPD_TIMOUT :
        case AM_RELCODE_PDN_PCRF_REL :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER;
            break;

        case AM_RELCODE_PMIPV6_LMA_TOUT :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP;
            break;

        case AM_RELCODE_PMIPV6_LMA_FAIL :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PGW_FAIL;
            break;

        case AM_RELCODE_PMIPV6_LMA_CHECK_ERR :
        case AM_RELCODE_PMIPV6_LIFE_TOUT :
        case AM_RELCODE_PMIPV6_PGW_REL_NORMAL :
        case AM_RELCODE_PMIPV6_PGW_REL_SAME_HAND :
        case AM_RELCODE_PMIPV6_PGW_REL_DIFF_HAND :
        case AM_RELCODE_PMIPV6_PGW_REL_UNKNOWN_HAND :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PGW_OTHER;
            break;

        default:
            break;
    }

    return;
}


VOID SNMP_VSNCPPhaseProc(PPPINFO_S *pstPppInfo)
{
    if(NULL == pstPppInfo)
    {
        PPPC_ERROR_LOG(
                     "\r\n [ppp]SNMP_VSNCPPhaseProc:  pstPppInfo=NULL!");
        return;
    }

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_MS_NO_RESPONSE,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1224);
            break;
        }

        case FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_REL_A10,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1225);
            break;
        }

        case FSM_ALARM_EHRPD_VSNCP_MS_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_MS_TERM,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_MS_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1226);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_NEGOFAIL:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_NEGO_FAIL,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_NEGOFAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1227);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_OTHER:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_OTHER,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1228);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1460);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1461);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1462);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PGW_FAIL:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PGW_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1463);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1464);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PGW_OTHER:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PGW_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1465);
            break;
        }

        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_543);
            PPPC_INFO_LOG4("\r\n[SNMP_VSNCPPhaseProc]:IPCP failtype = %u, bReNego = %u, bIpcpSucFlag = %u, bIPTech = %u, ",
                pstPppInfo->ucFSMFailType,
                pstPppInfo->bReNego,
                pstPppInfo->bIpcpSucFlag,
                pstPppInfo->bIPTech);
            PPPC_INFO_LOG3("bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                pstPppInfo->bAuthClient,
                pstPppInfo->bAuthServer,
                pstPppInfo->bPppMode);

            break;
        }
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1229);
#if 0
    A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM,
                                    pstPppInfo->ulPcfIP,
                                    A11_PERF_OPERATOR_PLUS,
                                    1);
#endif
    if (VOS_TRUE != pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1230);
#if 0
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM,
                                        pstPppInfo->ulPcfIP,
                                        A11_PERF_OPERATOR_PLUS,
                                        1);
#endif
    }

    return;
}


/*CR-0000060209*/
VOID SNMP_EhrpdUserDeaProc(SDB_PDSN_RP_CONTEXT_S * pstRpContext)
{
    PPPINFO_S *pstPppInfo = NULL;
    UCHAR eAlarmCode = FSM_ALARM_NULL;

    if ( NULL == pstRpContext )
    {
        PPPC_ERROR_LOG(
                     "\r\n [ppp]SNMP_EhrpdUserDeaProc:  rpcontext null");
        return;
    }

    if ( (USM_STATE_ACTIVE <= pstRpContext->ucUsmState) || (VOS_TRUE != pstRpContext->beHRPDMode) )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_544);
        PPPC_ERROR_LOG1(
                     "\r\n [ppp]SNMP_EhrpdUserDeaProc:  ucUsmState=%d!", pstRpContext->ucUsmState);
        return;
    }

    /*设置去活原因值的时候获取上报SNMP告警值*/
    GETPPPINFOPTRBYRP(pstPppInfo, pstRpContext->ulRpIndex);
    if (NULL == pstPppInfo)
    {
        PPPC_ERROR_LOG1(
                     "\r\n User ppp %d doesn't exist!",
                     pstRpContext->ulRpIndex);
        return;
    }
    /* 按照去活原因值获取 告警原因值 */
    SNMP_GetFailReasonByReleaseCode(pstRpContext->ulReleaseCode, &eAlarmCode);
    /* 设置性能统计去活原因 */
    if ( FSM_ALARM_NULL != eAlarmCode )
    {
        SNMP_SetFailReason(pstPppInfo, (FSM_ALARM_CODE_E)eAlarmCode);
    }

    return;
}


VOID SNMP_SetFailReasonForEhrpd(PPPINFO_S * pstPppInfo, FSM_ALARM_CODE_E enFailType)
{
    if (NULL == pstPppInfo)
    {
        return;
    }

    if ((PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
        && (FSM_ALARM_LCP_NEGOFAIL != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if ((PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
            && (FSM_ALARM_AUTH_OTHER != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if ((PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
            && (FSM_ALARM_EHRPD_VSNCP_NEGOFAIL != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if (PPP_SNMP_PERF_PHASE_SUCCESS== pstPppInfo->bPhaseFlag)
    {
        if (FSM_ALARM_NULL != enFailType)
        {
            return;
        }
    }

    if (VOS_OK != SNMP_CheckPhaseAndFailType(pstPppInfo->bPhaseFlag, enFailType))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_546);
        return;
    }

    pstPppInfo->ucFSMFailType = (UCHAR)enFailType;
    return;
}


#define ___PPP_PDSN___

VOID SNMP_LCPPhaseProc(PPPINFO_S *pstPppInfo)
{

    if (NULL == pstPppInfo)
    {
        return;
    }

    if (PDSN_PPP_IPTYE_IPV6 == pstPppInfo->ucIpCapability)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_547);
        return;
    }

    if (g_aulDoStatiscTime[0] + g_aulNoStatiscTime[0] >= 10)
    {
        g_aulDoStatiscTime[0] = 0;
        g_aulNoStatiscTime[0] = 0;
    }

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_LCP_NEGOFAIL:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_DISAGREEMENT,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_DISAGREEMENT,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_LCP_NEGOFAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1238);
            break;
        }

        case FSM_ALARM_LCP_MS_NO_RSP:
        {
            if (VOS_TRUE != pstPppInfo->bRecvLcpMsgFlag)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1239);
                return;
            }

            /*增加标志判断，如果未收到过LCP消息，则不统计失败*/
            if (0 == g_ulSoftPara585)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
                                  PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1240);
            }
            else
            {
                if (g_aulNoStatiscTime[0] < g_ulSoftPara585)
                {
                    g_aulNoStatiscTime[0]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                      PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1241);
                }
                else
                {
                    g_aulDoStatiscTime[0]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
                                      PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1242);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_LCP_MS_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1243);
            break;
        }

        case FSM_ALARM_LCP_PCF_RELEASE:
        {
            if (0 == g_ulSoftPara585)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
                                  PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1244);
            }
            else
            {
                if (g_aulNoStatiscTime[0] < g_ulSoftPara585)
                {
                    g_aulNoStatiscTime[0]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                      PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1245);
                }
                else
                {
                    g_aulDoStatiscTime[0]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
                                  PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1246);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_LCP_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1247);
            break;
        }

        case FSM_ALARM_LCP_MS_RELEASE:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt, \
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE, \
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_LCP_MS_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1248);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_548);

            if (0 == g_ulPppDBGStatisc[PPP_PHERR_548]%100)
            {
                PPPC_INFO_LOG4("\r\n[SNMP_LCPPhaseProc]:LCP failtype = %u, bReNego = %u, bIpcpSucFlag = %u, bIPTech = %u, ",
                    pstPppInfo->ucFSMFailType,
                    pstPppInfo->bReNego,
                    pstPppInfo->bIpcpSucFlag,
                    pstPppInfo->bIPTech);
                PPPC_INFO_LOG3("bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                    pstPppInfo->bAuthClient,
                    pstPppInfo->bAuthServer,
                    pstPppInfo->bPppMode);
            }
            /*End of liushuang*/
            break;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1249);

    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                          PERF_TYPE_1X_PPP_NEGOTIATIONS,
                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS, PERF_ADD);
    if (VOS_TRUE != pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1250);
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                              PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,
                              PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS, PERF_ADD);
    }

    return;
}

VOID SNMP_AuthPhaseProc(PPPINFO_S *pstPppInfo)
{

    if (NULL == pstPppInfo)
    {
        return;
    }

    if (PDSN_PPP_IPTYE_IPV6 == pstPppInfo->ucIpCapability)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_549);
        return;
    }

    if (g_aulDoStatiscTime[1] + g_aulNoStatiscTime[1] >= 10)
    {
        g_aulDoStatiscTime[1] = 0;
        g_aulNoStatiscTime[1] = 0;
    }

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_AUTH_PCF_RELEASE:
        {
            if (0 == g_ulSoftPara586)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE, PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1251);
            }
            else
            {
                if (g_aulNoStatiscTime[1] < g_ulSoftPara586)
                {
                    g_aulNoStatiscTime[1]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1252);
                }
                else
                {
                    g_aulDoStatiscTime[1]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE, PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1253);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1254);
            break;
        }

        case FSM_ALARM_AUTH_MS_NO_RSP:
        {
            if (0 == g_ulSoftPara586)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP, PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1255);
            }
            else
            {
                if (g_aulNoStatiscTime[1] < g_ulSoftPara586)
                {
                    g_aulNoStatiscTime[1]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1256);
                }
                else
                {
                    g_aulDoStatiscTime[1]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP, PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1257);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_MS_NO_RSP);

            PPP_DBG_OK_CNT(PPP_PHOK_1258);
            break;
        }

        case FSM_ALARM_AUTH_MS_RELEASE:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt, \
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE, \
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_MS_RELEASE);

            PPP_DBG_OK_CNT(PPP_PHOK_1259);
            break;
        }

        case FSM_ALARM_AUTH_ERROR_ACCOUNT:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_ERROR_ACCOUNT,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_ERROR_ACCOUNT,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            PPP_DBG_OK_CNT(PPP_PHOK_1260);
            break;
        }

        case FSM_ALARM_AUTH_AAA_NO_RSP:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_AAA_NO_RSP,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_AAA_NO_RSP,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1261);
            break;
        }
        case FSM_ALARM_AUTH_OTHER:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_OTHER,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_OTHER,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1262);
            break;
        }

        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_550);

            if (0 == g_ulPppDBGStatisc[PPP_PHERR_550]%100)
            {
                PPPC_INFO_LOG4("\r\n[ppp_patch]:AUTH failtype = %u, bReNego = %u, bIpcpSucFlag = %u, bIPTech = %u, ",
                                 pstPppInfo->ucFSMFailType,
                                 pstPppInfo->bReNego,
                                 pstPppInfo->bIpcpSucFlag,
                                 pstPppInfo->bIPTech);
                PPPC_INFO_LOG3("bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                                 pstPppInfo->bAuthClient,
                                 pstPppInfo->bAuthServer,
                                 pstPppInfo->bPppMode);
            }
            return;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1263);

    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                          PERF_TYPE_1X_PPP_NEGOTIATIONS,
                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS, PERF_ADD);
    if (VOS_TRUE !=  pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1264);
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                              PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,
                              PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS, PERF_ADD);
    }


    return;
}
VOID SNMP_IPCPPhaseProc(PPPINFO_S *pstPppInfo)
{


    if(NULL == pstPppInfo)
    {
        PPPC_INFO_LOG(
                     "\r\n [ppp]SNMP_IPCPPhaseProc:  pstPppInfo=NULL!");
        PPPC_INFO_LOG(
                     "\r\n [ppp]SNMP_IPCPPhaseProc:  pstPppInfo=NULL!");
        return;
    }

    PPPC_INFO_LOG1("\r\n [ppp]SNMP_IPCPPhaseProc:   Enter!ucFSMFailType[%u]", pstPppInfo->ucFSMFailType);

    if (PDSN_PPP_IPTYE_IPV6 == pstPppInfo->ucIpCapability)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_551);
        PPPC_INFO_LOG(
                     "\r\n [ppp]SNMP_IPCPPhaseProc:  pstPppInfo->ucIpCapability is single ipv6 !");
        return;
    }

    if (g_aulDoStatiscTime[2] + g_aulNoStatiscTime[2] >= 10)
    {
        g_aulDoStatiscTime[2] = 0;
        g_aulNoStatiscTime[2] = 0;
    }

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_IPCP_MS_NO_RSP:
        {
            if (0 == g_ulSoftPara587)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
                                      PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1265);
            }
            else
            {
                if (g_aulNoStatiscTime[2] < g_ulSoftPara587)
                {
                    g_aulNoStatiscTime[2]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1266);
                }
                else
                {
                    g_aulDoStatiscTime[2]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1267);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_MS_NO_RSP);

            PPP_DBG_OK_CNT(PPP_PHOK_1268);
            break;
        }

        case FSM_ALARM_IPCP_PCF_RELEASE:
        {
            if (0 == g_ulSoftPara587)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE, PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1269);
            }
            else
            {
                if (g_aulNoStatiscTime[2] < g_ulSoftPara587)
                {
                    g_aulNoStatiscTime[2]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1270);
                }
                else
                {
                    g_aulDoStatiscTime[2]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE, PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1271);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_PCF_RELEASE);

            PPP_DBG_OK_CNT(PPP_PHOK_1272);
            break;
        }

        case FSM_ALARM_IPCP_MS_RELEASE:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_MS_RELEASE);

            PPP_DBG_OK_CNT(PPP_PHOK_1273);
            break;
        }
        case FSM_ALARM_IPCP_NEGOFAIL:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_DISAGREEMENT,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_DISAGREEMENT,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_NEGOFAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1274);
            break;
        }
        case FSM_ALARM_IPCP_ALLOC_IP_FAIL:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_IP,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_IP,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_ALLOC_IP_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1275);

            break;
        }
        case FSM_ALARM_IPCP_OTHER:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_OTHER,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_OTHER,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1276);
            break;
        }

        case FSM_ALARM_IPCP_PCRF_FAIL:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt, \
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE, \
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_PCRF_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1277);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_552);

            if (0 == g_ulPppDBGStatisc[PPP_PHERR_552]%100)
            {
                PPPC_INFO_LOG4(
                             "\r\n[SNMP_IPCPPhaseProc]:IPCP failtype = %u, bReNego = %u, bIpcpSucFlag = %u"
                             ", bIPTech = %u, ",
                             pstPppInfo->ucFSMFailType,
                             pstPppInfo->bReNego,
                             pstPppInfo->bIpcpSucFlag,
                             pstPppInfo->bIPTech);
                PPPC_INFO_LOG3("bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                             pstPppInfo->bAuthClient,
                             pstPppInfo->bAuthServer,
                             pstPppInfo->bPppMode);
            }
            /*End of liushuang*/
            break;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1278);

    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                          PERF_TYPE_1X_PPP_NEGOTIATIONS,
                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS, PERF_ADD);
    if (VOS_TRUE !=  pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1279);
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                              PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,
                              PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS, PERF_ADD);
    }

    return;
}

VOID SNMP_TerminatePhaseProc(PPPINFO_S *pstPppInfo)
{
    PPPC_INFO_LOG("\r\n [ppp]SNMP_TerminatePhaseProc:  Enter!");

    if (NULL == pstPppInfo)
    {
        PPPC_ERROR_LOG(
                     "\r\n [ppp]SNMP_TerminatePhaseProc:  pstPppInfo=NULL!");
        return;
    }
    if (pstPppInfo->bEhrpdUser)
    {
        if (PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
        {
            SNMP_LCPPhaseProcForEhrpd(pstPppInfo);
        }
        else if (PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
        {
            SNMP_AuthPhaseProcForEhrpd(pstPppInfo);
        }
        else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
        {
            SNMP_VSNCPPhaseProc(pstPppInfo);
        }
    }
    else
    {
        if (PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
        {
            SNMP_LCPPhaseProc(pstPppInfo);
        }
        else if (PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
        {
            SNMP_AuthPhaseProc(pstPppInfo);
        }
        else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
        {
            SNMP_IPCPPhaseProc(pstPppInfo);
        }
    }
    return;
}


VOS_UINT32 SNMP_CheckPhaseAndFailType(UCHAR ucPhase, UCHAR ucFailType)
{
    VOS_UINT32 ulResult = VOS_ERR;

    if (0 == ucPhase)
    {
        switch (ucFailType)
        {
            case FSM_ALARM_LCP_MS_NO_RSP:
            case FSM_ALARM_LCP_MS_RELEASE:
            case FSM_ALARM_LCP_PCF_RELEASE:
            case FSM_ALARM_LCP_NEGOFAIL:
            case FSM_ALARM_LCP_OTHER:
            case FSM_ALARM_EHRPD_LCP_MS_NO_RSP:
            case FSM_ALARM_EHRPD_LCP_MS_RELEASE:
            case FSM_ALARM_EHRPD_LCP_PCF_RELEASE:
            case FSM_ALARM_EHRPD_LCP_NEGOFAIL:
            case FSM_ALARM_EHRPD_LCP_OTHER:
                ulResult = VOS_OK;
                break;
            default:
                break;
        }
    }
    else if (1 == ucPhase)
    {
        switch (ucFailType)
        {
            case FSM_ALARM_AUTH_ERROR_ACCOUNT:
            case FSM_ALARM_AUTH_AAA_NO_RSP:
            case FSM_ALARM_AUTH_MS_NO_RSP:
            case FSM_ALARM_AUTH_MS_RELEASE:
            case FSM_ALARM_AUTH_PCF_RELEASE:
            case FSM_ALARM_AUTH_OTHER:
            case FSM_ALARM_EHRPD_AUTH_AAA_NO_RSP:
            case FSM_ALARM_EHRPD_AUTH_MS_NO_RSP:
            case FSM_ALARM_EHRPD_AUTH_MS_RELEASE:
            case FSM_ALARM_EHRPD_AUTH_PCF_RELEASE:
            case FSM_ALARM_EHRPD_AUTH_OTHER:
                ulResult = VOS_OK;
                break;
            default:
                break;
        }
    }
    else if (2 == ucPhase)
    {
        switch (ucFailType)
        {
            case FSM_ALARM_IPCP_MS_NO_RSP:
            case FSM_ALARM_IPCP_MS_RELEASE:
            case FSM_ALARM_IPCP_PCF_RELEASE:
            case FSM_ALARM_IPCP_NEGOFAIL:
            case FSM_ALARM_IPCP_ALLOC_IP_FAIL:
            case FSM_ALARM_IPCP_OTHER:
            case FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP:
            case FSM_ALARM_EHRPD_VSNCP_MS_RELEASE:
            case FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE:
            case FSM_ALARM_EHRPD_VSNCP_NEGOFAIL:
            case FSM_ALARM_EHRPD_VSNCP_OTHER:
            case FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL:
            case FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP:
            case FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER:
            case FSM_ALARM_EHRPD_VSNCP_PGW_FAIL:
            case FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP:
            case FSM_ALARM_EHRPD_VSNCP_PGW_OTHER:
                ulResult = VOS_OK;
                break;
            default:
                break;
        }
    }

    return ulResult;
}



VOID SNMP_SetFailReason(PPPINFO_S * pstPppInfo, FSM_ALARM_CODE_E enFailType)
{
    if (NULL == pstPppInfo)
    {
        return;
    }

    if (pstPppInfo->bEhrpdUser)
    {
        SNMP_SetFailReasonForEhrpd(pstPppInfo, enFailType);
        return;
    }

    PPPC_INFO_LOG3(
                 "\r\nSNMP_SetFailReason: bPhaseFlag = %u, old FailType = %u, new FailType = %u",
                 pstPppInfo->bPhaseFlag,
                 pstPppInfo->ucFSMFailType,
                 enFailType);

    if ((PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
        && (FSM_ALARM_LCP_NEGOFAIL != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if ((PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
            && (FSM_ALARM_AUTH_OTHER != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if ((PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
            && (FSM_ALARM_IPCP_NEGOFAIL != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if (PPP_SNMP_PERF_PHASE_SUCCESS == pstPppInfo->bPhaseFlag)
    {
        if (FSM_ALARM_NULL != enFailType)
        {
            return;
        }
    }

    if (VOS_OK != SNMP_CheckPhaseAndFailType(pstPppInfo->bPhaseFlag, enFailType))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_553);
        return;
    }

    pstPppInfo->ucFSMFailType = (UCHAR)enFailType;
    return;
}

VOID SNMP_SetDefaultFailTypeByPhase(PPPINFO_S * pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        return;
    }

    PPPC_INFO_LOG1(
                 "\r\nSNMP_SetDefaultFailTypeByPhase: bPhaseFlag = %u",
                 pstPppInfo->bPhaseFlag);

    if  (PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
    {
        pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_LCP_NEGOFAIL;
    }
    else if (PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
    {
        pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_AUTH_OTHER;
    }
    else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
    {
        if (pstPppInfo->bEhrpdUser)
        {
            pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_EHRPD_VSNCP_NEGOFAIL;
        }
        else
        {
            pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_IPCP_NEGOFAIL;
        }
    }
    else
    {
        pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_NULL;
    }

    return;
}
/*lint -e774*/
VOS_UINT32 PerfSetFamPerfCounterByAddress(VOS_UINT32 *pCounterAddress, VOS_UINT32 udwOpType, VOS_UINT32 udwValue)
{
    if ((PPP_PERF_ADD == udwOpType) || (IPV6_ADD == udwOpType))
    {
        *pCounterAddress += udwValue;
    }
    else if ((IPV6_SUB == udwOpType) || (PPP_PERF_SUB == udwOpType))
    {
        *pCounterAddress -= udwValue;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
/*lint +e774*/
/*****************************************************************************
 函 数 名  : PPP_PerfInc
 功能描述  : PPP性能统计增加
 输入参数  : VOS_SIZE_T ulPerfCounter
             VOS_UINT32 ulPerfType
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月6日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_PerfInc(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType, UCHAR ucEhrpdMode)
{
    VOS_UINT32 ulRet = 0;

    if (VOS_TRUE == ucEhrpdMode)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1280);
        return;
    }

    ulRet = (VOS_UINT32)PerfSetFamPerfCounterByAddress(pulPerfCounter, PPP_PERF_ADD, 1);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_554);
        PPPC_WARNING_LOG3(
                      "\r\n[PERF] %s: set fam perf counter fail! ulPerfType is %lu, ulPerfCounter is %lx.",
                      (CHAR *)(__FUNCTION__), ulPerfType, *pulPerfCounter);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_PerfDec
 功能描述  : PPP性能统计
 输入参数  : VOS_SIZE_T ulPerfCounter
             VOS_UINT32 ulPerfType
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月6日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_PerfDec(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType, UCHAR ucEhrpdMode)
{
    VOS_UINT32 ulRet = 0;

    if (VOS_TRUE == ucEhrpdMode)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1281);
        return;
    }

    ulRet = (VOS_UINT32)PerfSetFamPerfCounterByAddress(pulPerfCounter, PPP_PERF_SUB, 1);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_555);
        PPPC_INFO_LOG3(
                      "\r\n[PERF] %s: set fam perf counter fail! ulPerfType is %lu, ulPerfCounter is %lx.",
                      (CHAR *)(__FUNCTION__), ulPerfType, *pulPerfCounter);
    }

    return;
}

/*****************************************************************************
 函 数 名  : IPV6_PerfInc
 功能描述  : IPV6性能统计,加一操作
 输入参数  : VOS_UINT32* pulPerfCounter
             VOS_UINT32 ulPerfType
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : y00202564
    修改内容   : 新生成函数

*****************************************************************************/
VOID IPV6_PerfInc(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType)
{
    (VOS_VOID)PerfSetFamPerfCounterByAddress(pulPerfCounter, IPV6_ADD, 1);

    return;
}

/*****************************************************************************
 函 数 名  : IPV6_PerfDec
 功能描述  : IPV6性能统计，减一操作
 输入参数  : VOS_UINT32* pulPerfCounter
             VOS_UINT32 ulPerfType
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月11日
    作    者   : y00202564
    修改内容   : 新生成函数

*****************************************************************************/
VOID IPV6_PerfDec(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType)
{
    (VOS_VOID)PerfSetFamPerfCounterByAddress(pulPerfCounter, IPV6_SUB, 1);

    return;
}

/* Added start by c00127007 at 2010-04-24 PDSNV9R7C05 for 同步C02 */
VOID A11_ReqNumSubProc(PPPINFO_S *pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        return;
    }

    if (pstPppInfo->bEhrpdUser)
    {
        return;
    }

    if ((0 == pstPppInfo->bPppSuccess)) /* 该标志用来表示是否需要减1:若PPP成功后不需要再减；若已经减过不需要再减 */
    {
#if 0
        A11_OM_PerfStatisticCMUnit((VOS_UINT32)PERF_TYPE_PDSN_SESSION_ACTIV_REQ, A11_PERF_OPERATOR_SUB);
        A11_OM_PerfStatisticVPDSNUnit((VOS_UINT32)PERF_TYPE_VPDSN_SM_ACTIV_REQ, A11_PERF_OPERATOR_SUB);
#endif
        pstPppInfo->bPppSuccess = 1;
        PPP_DBG_OK_CNT(PPP_PHOK_1282);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1283);
    }

    return;
}


#define ___PPP_SNMP_ALARM____
/*****************************************************************************
函 数 名  : InsertAlarmLink
功能描述  : 插入到告警链表尾
输入参数  : PPPA11_AlarmLink_S *pstAlarmLink
输出参数  : VOS_OK;VOS_ERR
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2010-02-23
 作    者   : c00127007 PDSNV9R7C05 for PPP_A11_Alarm
 修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 InsertAlarmLink(PPPA11_AlarmLink_S *pstAlarmLink)
{
    PPPA11_AlarmLink_NODE_S *pstNode = NULL;

    if (g_stPppA11AlarmLink.ulAlarmCount >= PPP_A11_ALARM_MAX_NUM)
    {
        PPPC_WARNING_LOG1(
                     "\r\n [ppp]InsertAlarmLink:  g_stPppA11AlarmLink.ulAlarmCount=%d is over 500!",
                     g_stPppA11AlarmLink.ulAlarmCount);
        PPP_DBG_OK_CNT(PPP_PHOK_1284);
        return VOS_OK;
    }

    pstNode = (PPPA11_AlarmLink_NODE_S *)PPP_Malloc(sizeof(PPPA11_AlarmLink_NODE_S));
    if (NULL == pstNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_556);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]InsertAlarmLink:  call PPP_Malloc failed!");
        return VOS_ERR;
    }

    VOS_MemSet(pstNode, 0, sizeof(PPPA11_AlarmLink_NODE_S));
    /* 赋值给pstNode */
    (VOID)VOS_MemCpy(&(pstNode->stNodeInfo), pstAlarmLink, sizeof(PPPA11_AlarmLink_S));
    pstNode->pNext = NULL;

    if (NULL == g_stPppA11AlarmLink.pHead)
    {
        /*插入第一个结点*/
        g_stPppA11AlarmLink.pHead = pstNode;
        g_stPppA11AlarmLink.pEnd = pstNode;
    }
    else
    {
        /*将黑名单结点插入到第一个位置*/
        (g_stPppA11AlarmLink.pEnd)->pNext = pstNode;
        g_stPppA11AlarmLink.pEnd = pstNode;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1285);
    g_stPppA11AlarmLink.ulAlarmCount++;

    return VOS_OK;
}
/*****************************************************************************
函 数 名  : DeleteAlarmLink
功能描述  : 从告警链表中删除头节点，进行告警
输入参数  : 无
输出参数  : PPPA11_AlarmLink_S *pstNodeInfo
返 回 值  : VOS_OK;VOS_ERR
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2010-02-23
作    者   : c00127007 PDSNV9R7C05 for PPP_A11_Alarm
修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 DeleteAlarmLink(PPPA11_AlarmLink_S *pstNodeInfo)
{
    PPPA11_AlarmLink_NODE_S *pstNode = NULL;

    if (NULL == pstNodeInfo)
    {
        PPPC_WARNING_LOG(
                     "\r\n [ppp]DeleteAlarmLink:  pstNodeInfo=NULL!");
        PPP_DBG_ERR_CNT(PPP_PHERR_557);
        return VOS_ERR;
    }

    pstNode = g_stPppA11AlarmLink.pHead;
    if(NULL == pstNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_558);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]DeleteAlarmLink:  g_stPppA11AlarmLink.ulAlarmCount=!0 but g_stPppA11AlarmLink.pHead=NULL!");
        return VOS_ERR;
    }

    if (pstNode == g_stPppA11AlarmLink.pEnd)
    {
        g_stPppA11AlarmLink.pHead = NULL;
        g_stPppA11AlarmLink.pEnd = NULL;
    }
    else
    {
        g_stPppA11AlarmLink.pHead = pstNode->pNext;
    }
    if (g_stPppA11AlarmLink.ulAlarmCount > 0)
    {
        g_stPppA11AlarmLink.ulAlarmCount--;
    }

    pstNode->pNext = NULL;

    (VOID)VOS_MemCpy(pstNodeInfo, &(pstNode->stNodeInfo), sizeof(PPPA11_AlarmLink_S));
    (VOID)PPP_Free(pstNode);
    pstNode = NULL;
    (VOS_VOID)pstNode;

    PPP_DBG_OK_CNT(PPP_PHOK_1286);
    return VOS_OK;
}

VOID PPP_A11_GetBSIDFromBCD(UCHAR *pucDst, const UCHAR *pucSrc, VOS_UINT32 ulLength)
{
    UCHAR aucTmp[PPP_A11_ALARM_BSID_LENGTH + 1] = {0};
    VOS_UINT32 i = 0;

    if ( NULL == pucSrc || NULL == pucDst )
    {
        return;
    }

    if (ulLength > PPP_A11_ALARM_BSID_BCD_LEN)
    {
        ulLength = PPP_A11_ALARM_BSID_BCD_LEN;
    }

    for (i = 0; i < ulLength; i++)
    {
        if ( i * 2 <= PPP_A11_ALARM_BSID_LENGTH  )
        {
            VOS_sprintf((VOS_CHAR *)(aucTmp + i * 2), "%02X\0", *(pucSrc + i));
        }
    }

    VOS_MemCpy(pucDst, aucTmp, PPP_A11_ALARM_BSID_LENGTH);

    return;
}

/*****************************************************************************
函 数 名  : PPP_InsertAlarm
功能描述  : PPP的SNMP告警
输入参数  : PPPINFO_S *pstPppInfo, UCHAR enRetType
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2010-02-23
作    者   : c00127007 PDSNV9R7C05 for PPP_A11_Alarm
修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_InsertAlarm(PPPINFO_S *pstPppInfo, UCHAR enRetType)
{
    PPPA11_AlarmLink_S stAlarmLink = {0};
    VOS_UINT32 ulRetVal = VOS_OK;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL;
    UCHAR aucSubnet[A11_SUBNET_LENGTH + 1] = {0};
    

    /*lint -e{506,774}*/
    if (0 == M_SPM_PDSN_SNMP_ACCESS_FUNCTION)  /* 软参未开启*/
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1288);
        PPPC_INFO_LOG(
                     "\r\n [ppp]PPP_InsertAlarm:  M_SPM_PDSN_SNMP_ACCESS_FUNCTION=0");
        return;
    }
    /*lint -restore*/

    if(NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_561);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_InsertAlarm:  pstPppInfo=NULL!");
        return;
    }

    ulRetVal = SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOS_VOID **)&pstRpContext);
    if ((VOS_OK != ulRetVal) || (NULL == pstRpContext))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_562);
        PPPC_WARNING_LOG2(
                     "\r\n [ppp]PPP_InsertAlarm:  SDB_GetRpContextByIndex fail[%u][%u]!",
                     pstPppInfo->ulRPIndex, ulRetVal);
        return;
    }

    stAlarmLink.ulPDSNIP = g_ulA11RpifIp;
    stAlarmLink.ulPcfIP = pstPppInfo->ulPcfIP;
#if 0
    /* 安全红线 IMSI 加密 */
    A11_EncryptImsiToString(&(pstPppInfo->stIMSI), stAlarmLink.ucIMSI);
    if (VOS_OK == A11_TmSince1970(&ulTimeInSecHigh, &ulTimeInSecLow))
    {
        stAlarmLink.ulTimestamp = ulTimeInSecLow;
    }
    else
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_InsertAlarm: VOS_TmSince1970 error.");
    }
#endif
    stAlarmLink.ucErrorCode = (UCHAR)enRetType;
    if (VOS_TRUE == pstRpContext->bBsidFlag)
    {
        PPP_A11_GetBSIDFromBCD(stAlarmLink.ucBSID, pstRpContext->ucBsId, PPP_A11_ALARM_BSID_BCD_LEN);
    }
    else
    {
        (VOID)VOS_MemCpy(stAlarmLink.ucBSID, "NULL", sizeof("NULL"));
    }

    if (0 != pstRpContext->aucSubnet[0])
    {
        (VOID)VOS_MemCpy(aucSubnet, pstRpContext->aucSubnet, A11_SUBNET_LENGTH);
        A11_4BitsToString((UCHAR *)aucSubnet, stAlarmLink.aucSubnet, PPP_A11_ALARM_SUBNET_LENGTH);
    }
    else
    {
        (VOID)VOS_MemCpy(stAlarmLink.aucSubnet, "NULL", sizeof("NULL"));
    }

    ulRetVal = InsertAlarmLink(&stAlarmLink);
    if (ulRetVal != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_563);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_InsertAlarm:  InsertAlarmLink return err");
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1289);

    return;
}

/*****************************************************************************
函 数 名  : PPP_A11_AlarmToFamEx
功能描述  : PPP_A11的SNMP告警
输入参数  : PPPA11_AlarmLink_S stAlarmReport
输出参数  :
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2010-02-23
作    者   : c00127007 PDSNV9R7C05 for PPP_A11_Alarm
修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_A11_AlarmToFamEx(PPPA11_AlarmLink_S stAlarmReport)
{
    VOS_UINT32 ulRetCode = VOS_ERR;
    VOID* pPara[7] = {0};
    UCHAR ParaLength[7] = {0};

    /*设置参数长度*/
    ParaLength[0] = 4;
    ParaLength[1] = 4;
    ParaLength[2] = sizeof(stAlarmReport.ucIMSI);
    ParaLength[3] = 1;
    ParaLength[4] = 4;
    ParaLength[5] = sizeof(stAlarmReport.ucBSID);
    ParaLength[6] = sizeof(stAlarmReport.aucSubnet);

    /*设置参数值*/
    pPara[0] = (VOID*)(&(stAlarmReport.ulPDSNIP));
    pPara[1] = (VOID*)(&(stAlarmReport.ulPcfIP));
    pPara[2] = (VOID*)(stAlarmReport.ucIMSI);
    pPara[3] = (VOID*)(&(stAlarmReport.ucErrorCode));
    pPara[4] = (VOID*)(&(stAlarmReport.ulTimestamp));
    pPara[5] = (VOID*)(stAlarmReport.ucBSID);
    pPara[6] = (VOID*)(stAlarmReport.aucSubnet);

    ulRetCode = (VOS_UINT32)AlarmToFamEx(ALM_GetAlmSlotCpuID(),
                                    (VOS_UINT32)MID_PPPC,
                                    (VOS_UINT32)M_ALM_USERACCESS_FAILURE_ALARM,
                                    M_ALM_TYPE_EVENT,
                                    7,
                                    ParaLength,
                                    pPara);
    if (VOS_OK != ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_564);
        PPPC_WARNING_LOG1(
                     "\r\n [ppp]PPP_A11_AlarmToFamEx:  call AlarmToFamEx err: %d!",
                     ulRetCode);
        return VOS_ERR;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1290);

    return VOS_OK;
}
/*****************************************************************************
函 数 名  : PPP_A11_AlarmProc
功能描述  : 新增的PPP和A11的告警处理函数，每1秒读出一个告警消息,进行告警
输入参数  : 无
输出参数  : 无
返 回 值  :
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2010-02-23
作    者   : c00127007 PDSNV9R7C05 for PPP_A11_Alarm
修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_A11_AlarmProc(VOID)
{
    PPPA11_AlarmLink_S stAlarmReport = {0};
    VOS_UINT32 ulRetCode  = VOS_ERR;

    VOS_MemSet(&stAlarmReport, 0, sizeof(PPPA11_AlarmLink_S));
    if (0 == g_stPppA11AlarmLink.ulAlarmCount)
    {
        return;
    }

    ulRetCode = DeleteAlarmLink(&stAlarmReport);
    if (VOS_ERR == ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_565);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_A11_AlarmProc:  DeleteAlarmLink return err!");
        return;
    }

    ulRetCode = PPP_A11_AlarmToFamEx(stAlarmReport);
    if (VOS_ERR == ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_566);
        PPPC_WARNING_LOG(
                     "\r\n [ppp]PPP_A11_AlarmProc:  PPP_A11_AlarmToFamEx return err!");
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1291);

    return;
}

 /*=======================================================================
  *  函数名称:       IPV6_PerfStatistic
  *  初稿完成:       2012/02/01
  *  作    者:       yangxiangkun 00202564
  *  函数功能:       性能统计,ipv6cp协商成功次数
  *  输入参数:       VOS_UINT32 ulMsgType
  *  输出参数:       无
  *  返回类型:       无
  *  其他说明:       无
  *  调用函数:
  *  主调函数:       IPV6_MainTask
  *=======================================================================*/
 VOS_VOID IPV6_PerfStatistic(VOS_UINT32 ulMsgType)
 {
     switch (ulMsgType)
     {
         /*ipv6cp协商尝试次数*/
         case IPV6_IPV6CP_ATTEMPT:
         {
             g_aulIpv6Cnt[E_IPV6_PERF_STATIC_NEGO_ATTEMPT]++;
             break;
         }

         /*ipv6cp协商成功次数*/
         case IPV6_IPV6CP_SUCC:
         {
             g_aulIpv6Cnt[E_IPV6_PERF_STATIC_NEGO_SUCCESS]++;
             break;
         }

         default:
             break;

     }

     return;

 }


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
