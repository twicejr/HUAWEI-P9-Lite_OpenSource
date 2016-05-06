/************************************************************************
*                                                                      *
*                             ppp_perf.h                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2013/04/17                                      *
*  Author:             wangyong                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP模块性能统计宏定义                           *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*                                                                      *
************************************************************************/
#ifndef      _PPP_PERF_H_
#define      _PPP_PERF_H_

#ifdef      __cplusplus
    extern "C" {
#endif      /* end of __cplusplus */


#define PPP_SNMP_PERF_PHASE_LCP        0
#define PPP_SNMP_PERF_PHASE_AUTH       1
#define PPP_SNMP_PERF_PHASE_NET        2
#define PPP_SNMP_PERF_PHASE_SUCCESS    3


enum E_PERF_ENTITY
{
    PERF_ENTITY_BEGIN = 10000,
    PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL,
    PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL,
    PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL,
    PERF_TYPE_PPPC_LCP_NEGO_SUCC_NUM,
    PERF_TYPE_PPPC_IPCP_NEGO_SUCC_NUM,
    PERF_TYPE_PPPC_PPP_NEGO_NUM,
    PERF_TYPE_PPPC_CCP_NEGO_SUCC,
    PERF_TYPE_PPPC_SEND_NEGO_PKT_NUM,
    PERF_TYPE_PPPC_RCV_ERR_NEGO_PKT_NUM,
    PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM,
    PERF_TYPE_PPPC_PAP_AUTHEN_SUCC_NUM,
    PERF_TYPE_PPPC_IPCP_NEGO_REQ_NUM,
    PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_REQ_NUM,
    PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM,
    PERF_TYPE_EHRPD_PCF_PPP_CONNCET_SUC_NUM,
    PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM,
    PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_SUC_NUM,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_SUC,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_SUC,
    PERF_TYPE_1X_PPP_NEGOTIATIONS,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS,
    PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS_SUC,
    PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS_SUC,
    PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,
    PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS,
    PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_SUCC_NUM,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_DISAGREEMENT,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_DISAGREEMENT,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_ERROR_ACCOUNT,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_ERROR_ACCOUNT,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_AAA_NO_RSP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_AAA_NO_RSP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_OTHER,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_OTHER,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_DISAGREEMENT,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_DISAGREEMENT,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_IP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_IP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_OTHER,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_OTHER,
    PERF_TYPE_PPPC_IPV6CP_NEGO_REQ_NUM,
    PERF_TYPE_PPPC_IPV6CP_NEGO_SUCC_NUM,
    PERF_TYPE_PPPC_LCP_NEGO_REQ_NUM,
    PERF_TYPE_PPPC_CCP_NEGO_ATTEMP,
    PERF_TYPE_EHRPD_PCF_PPP_TOTAL_TIME,
    PERF_TYPE_EHRPD_PCF_PPP_NEGO_NUM,
    PERF_TYPE_PPPC_PAP_AUTHEN_NUM,
    PERF_TYPE_PPPC_CHAP_AUTHEN_NUM,



    PERF_ENTITY_BUTT
};

typedef enum
{
    /*消息数统计*/
    E_IPV6_IPV6_MSG,
    E_IPV6_ICMP_MSG,
    E_IPV6_UDP_MSG,
    E_IPV6_NS_MSG,
    E_IPV6_RS_MSG,
    E_IPV6_MSG_LEN_ERR,
    E_IPV6_MSG_LIMIT_ERR,
    E_IPV6_MSG_NOT_SUPPORT,
    E_IPV6_MSG_CHECKSUM_ERR,
    E_IPV6_TARGET_ERR,
    E_IPV6_DEST_ERR,
    E_IPV6_OPT_LEN_ERR,
    E_IPV6_OPT_DUP_ERR,
    E_IPV6_OPT_UNKOWN,
    E_IPV6_OPT_NOT_SUPPORT,
    E_IPV6_RS_NO_CONTEXT,
    E_IPV6_UDP_PORT_ERR,
    E_IPV6_DHCP_TYPE_ERR,
    E_IPV6_DHCP_IA_ERR,
    E_IPV6_DHCP_ORO_ERR,
    E_IPV6_MBUF_ERR,
    E_IPV6_PPP_INFO_ERR,
    E_IPV6_PPP_ENCAP_ERR,
    E_IPV6_INVALID_RPINDEX,
    E_IPV6_RS_IP_TYPE_ERR,

    /*流程统计*/
    E_IPV6_START_TIMER,
    E_IPV6_STOP_TIMER,
    E_IPV6_TIMER_NOCONTEXT,
    E_IPV6_RESTART_TIMER,
    E_IPV6_A11_NOTIFY_NOCONTEXT,
    E_IPV6_PERF_STATIC_NEGO_ATTEMPT,
    E_IPV6_PERF_STATIC_NEGO_SUCCESS,
    E_IPV6_USER_PERF_STATIC_V6_ADD,
    E_IPV6_USER_PERF_STATIC_V4V6_ADD,
    E_IPV6_USER_PERF_STATIC_V6_SUB,
    E_IPV6_USER_PERF_STATIC_V4V6_SUB,
    E_IPV6_A11_NOTIFY_SEND_RA_ERR,
    E_IPV6_SEND_RA_MSG_ERR,
    E_IPV6_SEND_DHCP_GET_CONTEXT_FAIL,
    E_IPV6_SEND_DHCP_PPP_MSG_ERR,


    E_IPV6_CNT_END,
}IPV6_CNT_E;


/* 性能统计结构 */
typedef struct tagPppPerfStatistic
{
    VOS_SIZE_T  ulReceiveNego;          /* PPPC收到的协商报文总数 */
    VOS_SIZE_T  ulReceiveNegoErr;       /* PPPC收到无效的报文数 */
    VOS_SIZE_T  ulSendNego;             /* PPPC发送的协商报文总数 */
    VOS_SIZE_T  ulLcpTotal;             /* LCP协商尝试次数 */
    VOS_SIZE_T  ulLcpSuccess;           /* LCP协商成功次数 */
    VOS_SIZE_T  ulIpcpTotal;            /* IPCP协商尝试次数 */
    VOS_SIZE_T  ulIpcpSuccess;          /* IPCP协商成功次数 */
    VOS_SIZE_T  ulPppNegoTotalTime;     /* PPP协商总时间 */
    VOS_SIZE_T  ulPppNegoTime;          /* PPP平均协商时间 */
    VOS_SIZE_T  ulPppNegoNum;           /* PPP协商次数 */
    VOS_SIZE_T  ulPapTotal;            /* 认证尝试次数 */
    VOS_SIZE_T  ulPapSuccess;          /* 认证成功次数 */
    VOS_SIZE_T  ulChapTotal;            /* 认证尝试次数 */
    VOS_SIZE_T  ulChapSuccess;          /* 认证成功次数 */
    VOS_SIZE_T  ulCcpTotal;            /* CCP协商尝试次数 */
    VOS_SIZE_T  ulCcpSuccess;          /* CCP协商成功次数 */
    VOS_SIZE_T  ulReceiveStac;         /* PPPC收到的STAC压缩报文数 */
    VOS_SIZE_T  ulSendStac;            /* PPPC发送的STAC压缩报文数 */
    VOS_SIZE_T  ulReceiveMppc;         /* PPPC收到的MPPC压缩报文数 */
    VOS_SIZE_T  ulSendMppc;            /* PPPC发送的MPPC压缩报文数 */

    /* BEGIN: M by h50774 for 增加压缩用户数统计, 2010/7/17 */
    VOS_SIZE_T  ulCurVjUser;           /* 当前VJ用户数 */
    VOS_SIZE_T  ulCurMppcUser;         /* 当前Mppc用户数 */
    VOS_SIZE_T  ulCurMppcVjUser;       /* 当前MppcVJ用户数 */
    /* END  : M by h50774 for 增加压缩用户数统计, 2010/7/17 */


    VOS_SIZE_T  ulHSGWPppNegoTime;     /* ehrpd: PPP平均协商时间 */
} PPPPERFSTATISTIC_S;

/*性能统计结构*/
typedef struct tagIpv6PerfStatistic
{
    VOS_SIZE_T  ulIpv6CpNegoSucc ;           /* IPv6CP协商成功次数 */
    VOS_SIZE_T  ulIpv6CpNegoAttempt;         /* IPv6CP协商尝试次数 */
    VOS_SIZE_T  ulSipIpv6UserActNum ;       /* 当前激活的简单IPv6单栈用户数 */
    VOS_SIZE_T  ulMipIpv4v6UserActNum;      /* 当前激活的简单IPv4/IPv6双栈用户数 */
}IPV6PERFSTATISTIC_S;

typedef enum
{
    FSM_ALARM_NULL = 0,    /*不代表任何告警，为PPP控制块中的初始值*/

    FSM_ALARM_LCP_MS_NO_RSP = 0x81, /*129. LCP协商阶段终端无响应 */
    FSM_ALARM_LCP_MS_RELEASE,       /*130. LCP协商阶段终端主动发起去活 */
    FSM_ALARM_LCP_PCF_RELEASE,      /*131. LCP协商阶段PCF拆除A10 */
    FSM_ALARM_LCP_NEGOFAIL,         /*132. LCP协商阶段协商失败 */


    FSM_ALARM_AUTH_ERROR_ACCOUNT,   /*133. AUTH阶段用户名密码错 */
    FSM_ALARM_AUTH_AAA_NO_RSP,      /*134. AUTH阶段AAA无响应*/
    FSM_ALARM_AUTH_MS_NO_RSP,       /*135. AUTH阶段终端无响应*/
    FSM_ALARM_AUTH_MS_RELEASE,      /*136. AUTH阶段终端主动发起去活*/
    FSM_ALARM_AUTH_PCF_RELEASE,     /*137. AUTH阶段PCF拆除A10*/
    FSM_ALARM_AUTH_ERROR_OTHER,     /*138. AUTH阶段其他原因 */

    FSM_ALARM_IPCP_MS_NO_RSP,       /*139. IPCP阶段终端无响应*/
    FSM_ALARM_IPCP_MS_RELEASE,      /*140. IPCP协商阶段终端主动发起去活 */
    FSM_ALARM_IPCP_PCF_RELEASE,     /*141. IPCP协商阶段PCF拆除A10 */
    FSM_ALARM_IPCP_NEGOFAIL,        /*142. IPCP协商阶段协商失败 */
    FSM_ALARM_IPCP_ALLOC_IP_FAIL,   /*143. IPCP协商阶段IP地址申请失败 */

    FSM_ALARM_LCP_OTHER,            /*144. LCP协商阶段其它原因失败*/
    FSM_ALARM_AUTH_OTHER,           /*145. AUTH阶段其它原因失败*/
    FSM_ALARM_IPCP_OTHER,           /*146. IPCP阶段其它原因失败*/

    FSM_ALARM_IPCP_PCRF_FAIL,       /*147. C06新增IPCP阶段PCRF失败*/

    /*以下为HSGW新增的LCP、EAP、VSNCP接入失败错误码 CR-0000060209 */
    FSM_ALARM_EHRPD_LCP_MS_NO_RSP = 0xA1,   /*161. eHRPD用户LCP协商阶段终端无响应 */
    FSM_ALARM_EHRPD_LCP_MS_RELEASE,         /*162. eHRPD用户LCP协商阶段终端主动发起去活 */
    FSM_ALARM_EHRPD_LCP_PCF_RELEASE,        /*163. eHRPD用户LCP协商阶段PCF拆除A10 */
    FSM_ALARM_EHRPD_LCP_NEGOFAIL,           /*164. eHRPD用户LCP协商阶段协商失败 */


    FSM_ALARM_EHRPD_AUTH_AAA_NO_RSP,        /*165. eHRPD用户AUTH阶段AAA无响应*/
    FSM_ALARM_EHRPD_AUTH_MS_NO_RSP,         /*166. eHRPD用户AUTH阶段终端无响应*/
    FSM_ALARM_EHRPD_AUTH_MS_RELEASE,        /*167. eHRPD用户AUTH阶段终端主动发起去活*/
    FSM_ALARM_EHRPD_AUTH_PCF_RELEASE,       /*168. eHRPD用户AUTH阶段PCF拆除A10*/


    FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP,        /*169. eHRPD用户VSNCP阶段终端无响应*/
    FSM_ALARM_EHRPD_VSNCP_MS_RELEASE,  /*170. eHRPD用户VSNCP协商阶段终端主动发起去活 */
    FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE,      /*171. eHRPD用户VSNCP协商阶段PCF拆除A10 */
    FSM_ALARM_EHRPD_VSNCP_NEGOFAIL,         /*172. eHRPD用户VSNCP协商阶段协商失败 */

    FSM_ALARM_EHRPD_LCP_OTHER,              /*173. eHRPD用户LCP协商阶段其它原因失败*/
    FSM_ALARM_EHRPD_AUTH_OTHER,             /*174. eHRPD用户AUTH阶段其它原因失败*/
    FSM_ALARM_EHRPD_VSNCP_OTHER,            /*175. eHRPD用户VSNCP阶段其它原因失败*/

    FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL,        /*176. eHRPD用户VSNCP阶段PCRF失败*/
    FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP,      /*177. eHRPD用户VSNCP阶段PCRF无响应*/
    FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER,    /*178. eHRPD用户VSNCP阶段PCRF其他原因失败*/

    FSM_ALARM_EHRPD_VSNCP_PGW_FAIL,         /*179. eHRPD用户VSNCP阶段PGW失败 */
    FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP,       /*180. eHRPD用户VSNCP阶段PGW无响应 */
    FSM_ALARM_EHRPD_VSNCP_PGW_OTHER,      /*181. eHRPD用户VSNCP阶段PGW其他原因失败 */
}FSM_ALARM_CODE_E;

typedef struct tagAlarmLinkNode
{
    struct tagAlarmLink stNodeInfo;
    struct tagAlarmLinkNode *pNext;
}PPPA11_AlarmLink_NODE_S;

typedef struct tagAlarmLinkHead
{
    struct tagAlarmLinkNode *pHead;
    struct tagAlarmLinkNode *pEnd;
    VOS_UINT32  ulAlarmCount;
    VOS_UINT32  ulReserved;         /* luofang--八字节对齐 */
}PPPA11_AlarmLink_HEAD_S;


#define M_SET_NEWPHASE(pstPppInfoT, NewPhase) \
{\
    ((PPPINFO_S *)pstPppInfoT)->bPhaseFlag = NewPhase; \
    SNMP_SetDefaultFailTypeByPhase(pstPppInfoT); \
}


/* PPP连接成功次数 */
#define PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo) \
{ \
    if (pstPppInfo->bEhrpdUser) \
    { \
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM, \
                                        pstPppInfo->ulPcfIP, \
                                        A11_PERF_OPERATOR_PLUS, \
                                        1);     \
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_SUC_NUM, \
                                        pstPppInfo->ulPcfIP,  \
                                        A11_PERF_OPERATOR_PLUS, \
                                        1); \
        if (VOS_FALSE == pstPppInfo->bIpcpSucFlag) \
        {   \
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM, \
                                            pstPppInfo->ulPcfIP, \
                                            A11_PERF_OPERATOR_PLUS, \
                                            1);     \
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_SUC_NUM, \
                                            pstPppInfo->ulPcfIP, \
                                            A11_PERF_OPERATOR_PLUS, \
                                            1); \
        } \
    } \
    else \
    { \
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,  \
                              PERF_TYPE_1X_PPP_NEGOTIATIONS_SUC, \
                              PERF_TYPE_EVDO_PPP_NEGOTIATIONS_SUC, PERF_ADD); \
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,  \
                              PERF_TYPE_1X_PPP_NEGOTIATIONS,  \
                              PERF_TYPE_EVDO_PPP_NEGOTIATIONS, PERF_ADD); \
        if (VOS_FALSE == pstPppInfo->bIpcpSucFlag) \
        {   \
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,  \
                                  PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS_SUC,  \
                                  PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS_SUC, PERF_ADD);  \
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt, \
                                  PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,  \
                                  PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS, PERF_ADD); \
        } \
    } \
    \
    pstPppInfo->bIpcpSucFlag = VOS_TRUE; \
    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_SUCCESS); \
    \
}

/* ms主动去活 */
#define PPP_SNMP_PERF_SET_FAILREASON_MS_RELEASE(pstPppInfo, pstFsm) \
{ \
/*Modified by liushuang for DTS2012033006941 . 单栈V4、双栈v6协商失败或者V6未协商时置终端主动退网原因值*/ \
    if ((PPP_LCP == pstFsm->usProtocol) \
                    || (PPP_VSNCP == pstFsm->usProtocol) \
                    || ((PPP_IPCP == pstFsm->usProtocol) \
                        && (PDSN_PPP_IPTYE_IPV6 != pstPppInfo->ucIpCapability))) \
    { \
        if (PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_LCP_MS_RELEASE); /* LCP阶段终端主动拆线 */ \
        } \
        else if (PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_MS_RELEASE); /* 认证阶段终端主动拆线 */ \
            /* 收到到LCP termate req后，如果用户处于PPP协商阶段，则将“分组会话激活请求数”减1*/ \
            A11_ReqNumSubProc(pstPppInfo); \
        } \
        else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag) \
        { \
            if (VOS_TRUE == pstPppInfo->bEhrpdUser) \
            { \
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_MS_RELEASE); /* IPCP阶段终端主动拆线 */  \
            } \
            else \
            { \
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_MS_RELEASE); /* IPCP阶段终端主动拆线 */  \
                /* 收到到LCP termate req后，如果用户处于PPP协商阶段，则将“分组会话激活请求数”减1*/ \
                A11_ReqNumSubProc(pstPppInfo); \
            } \
        } \
    }  \
}


/* ms无响应 */
#define PPP_SNMP_PERF_SET_FAILREASON_MS_NO_RSP(pstPppInfo, pstFsm) \
{ \
    if ((pstFsm->ucState != PPP_STATE_CLOSING)  \
        && (pstFsm->ucState != PPP_STATE_STOPPING)) \
    { \
        if (PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_LCP_MS_NO_RSP); \
        } \
        else if ((PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag) \
            && (PPP_IPCP == pstFsm->usProtocol)) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_MS_NO_RSP);  \
        } \
        else if ((PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag) \
            &&  (VOS_TRUE == pstPppInfo->bEhrpdUser)) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP);  \
        } \
    } \
}

/* pcf主动去活 */
#define PPP_SNMP_PERF_SET_FAILREASON_PCF_RELEASE(pstPppInfo, pstFsm) \
{ \
    if(PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag) \
    { \
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_LCP_PCF_RELEASE); \
    } \
    else if(PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag) \
    { \
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_PCF_RELEASE); \
    }  \
    else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag) \
    { \
        if (VOS_TRUE == pstPppInfo->bEhrpdUser) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE); \
        } \
        else if (PDSN_PPP_IPTYE_IPV6 != pstPppInfo->ucIpCapability) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_PCF_RELEASE); \
        } \
    } \
}

extern VOS_UINT32 SNMP_CheckPhaseAndFailType(UCHAR ucPhase, UCHAR ucFailType);
extern VOID SNMP_SetFailReason(PPPINFO_S * pstPppInfo, FSM_ALARM_CODE_E enFailType);
extern VOID SNMP_SetDefaultFailTypeByPhase(PPPINFO_S * pstPppInfo);
extern VOID SNMP_TerminatePhaseProc(PPPINFO_S *pstPppInfo);


extern VOS_UINT32 DeleteAlarmLink(PPPA11_AlarmLink_S *pstNodeInfo);
extern VOID PPP_InsertAlarm(PPPINFO_S *pstPppInfo, UCHAR enRetType);
VOID SNMP_EhrpdUserDeaProc(SDB_PDSN_RP_CONTEXT_S * pstRpContext);
VOID SNMP_GetFailReasonByReleaseCode(VOS_UINT32 ulReleaseCode, UCHAR *pucFailType);
extern VOS_UINT32 PPP_A11_AlarmToFamEx(PPPA11_AlarmLink_S stAlarmReport);
extern VOID PPP_PerfStatisticByReleaseCode(PPPINFO_S *pstPppInfo);
extern VOID PPP_A11_AlarmProc(VOID);

#ifdef      __cplusplus
    }
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_DEF_H_ */

