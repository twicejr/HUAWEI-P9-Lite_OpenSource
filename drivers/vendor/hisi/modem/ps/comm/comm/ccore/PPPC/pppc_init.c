/************************************************************************
*                                                                      *
*                             ppp_init.c                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/03/27                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP模块初始化流程                               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了PPP模块的初始化函数                                  *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"
#include "pppc_ctrl.h"
#include "ppp_func.h"

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
#include "hdlc_hardware.h"
#endif



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_INIT_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
VOS_UINT32 g_ulHsgwPppPerfInitOkFlg = VOS_FALSE;

extern volatile HTIMER                  g_hRestartTimer;
extern PS_BOOL_ENUM_UINT8               g_ucLcpTermMask;
extern PPPC_CONTEXT_INFO_STRU           g_stPppContext;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */
/*lint -e572*/
/*****************************************************************************
 函 数 名  : PPPC_MsgTimerProc
 功能描述  : PPP模块中的定时器消息处理函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014-10-30
    作    者   : c00184031
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_MsgTimerProc( struct MsgCB * pMsg )
{
    REL_TIMER_MSG                      *pPsMsg  = (REL_TIMER_MSG  *)pMsg;
    VOS_UINT32                          ulPppId = pPsMsg->ulName;
    PPPC_ACCESS_AUTH_ACT_MODE_ENUM_UINT16 enActMode;
    VOS_VOID                           *pFsm;


    /*判断是那个阶段启动的定时器*/
    switch(pPsMsg->ulPara)
    {
        /* CHAP Challenge重传定时器 */
        case PPPC_CHAP_CHALLENGE_RESEND_TIMER:

            PPP_CHAP_ChallengeTimeout(ulPppId);

            break;

        /* CHAP Response重传定时器 */
        case PPPC_CHAP_RESPONSE_RESEND_TIMER:

            PPP_CHAP_ResponseTimeout(ulPppId);


            break;

/* EAP-dev */
        /* Vendor Specific能力发送超时定时器 */
        case PPPC_VENDOR_SPECIFIC_SEND_CAPABILITY_TIMER:

            PPP_FSM_VSTimeOut((VOS_VOID *)ulPppId);

            break;

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
        /* EAP发送EAP REQ定时器 */
        case PPPC_EAP_RCV_EAP_REQ_TIMER:

            PPPC_EAP_RcvReqTimeout(ulPppId);

            break;
#endif

        /* LCP启动Echo Req定时器 */
        case PPPC_LCP_SEND_ECHO_REQ_TIMER:

            pFsm    = (VOS_VOID *)pPsMsg->ulName;
            PPP_LCP_EchoTimeOut(pFsm);

            break;

        /* PAP等待对端发出认证请求定时器 */
        case PPPC_PAP_WAIT_FOR_REQ_TIMER:

            PPP_PAP_WaitReqTimeout(ulPppId);

            break;

        /* PAP设置等待验证超时定时器 */
        case PPPC_PAP_SEND_AUTH_REQ_TIMER:

            PPP_PAP_SendAuthReqTimeout(ulPppId);

            break;

        case PPPC_NEGO_TIMEOUT_TIMER:

            PPP_NegoListProc(VOS_NULL_PTR);

            break;

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
        /* CCP超时定时器 */
        case PPPC_CCP_TIMEOUT_TIMER:

            PPP_CCP_Timeout(ulPppId);

            break;
#endif

        /* FSM重传定时器 */
        case PPPC_FSM_RETRANSMIT_TIMER:

            pFsm    = (VOS_VOID *)pPsMsg->ulName;
            PPP_FSM_TimeOut(pFsm);

            break;

        /* PA的TRLPResponse定时器 */
        case PPPC_HRPD_PA_AGENT_RLP_RSP_TIMER:

            PPPC_HRPD_PaAgentRlpTimeout(pPsMsg->ulName);

            break;

        case PPPC_AWAKE_SELF_REACH_MAX_PROC_TIMER:

            PPPC_AwakeSelfReachMaxProcTimeoutProc();

            break;

        /* PPP 发送 deact notify 的定时器 */
        case PPPC_LINK_RESTART_TIMER:

            PPPC_ReceiveLCPTermReq((VOS_UINT8)ulPppId);
            g_hRestartTimer = VOS_NULL_PTR;

            break;

        /* MAX PPP Inactive Timer */
        case PPPC_MAX_PPP_INACTIVE_TIMER:

            PPPC_InactivePppTimeoutProc((VOS_UINT8)ulPppId);
            break;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
        /* HDLC申请封装目的空间失败定时器 */
        case PPPC_HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL:

            if (VOS_NULL_PTR != g_stHdlcConfigInfo.stHdlcFrmTimerHandle)
            {
                VOS_StopRelTimer((HTIMER*)&g_stHdlcConfigInfo.stHdlcFrmTimerHandle);
                g_stHdlcConfigInfo.stHdlcFrmTimerHandle = VOS_NULL_PTR;
            }

            PPPC_AwakeSelfProcUlDataTimeoutProc();
            break;
#endif

        case PPPC_ACCESS_AUTH_ACT_HRPD_DELAY_PROC_TIMER:

            enActMode   = (PPPC_ACCESS_AUTH_ACT_MODE_ENUM_UINT16)pPsMsg->ulName;
            PPPC_AccessAuthDelayProcTimeoutProc(enActMode);

            break;

        /* 读卡文件定时器 */
        case PPPC_HRPD_UIMREAD_DELAY_PROC_TIMER:

            PPPC_HRPD_UimClearnReadTimer();
            PPPC_ReadFixedData();
            break;

        /* PPPC收到PA的接入鉴权通知延时处理 */
        case PPPC_ACCESS_AUTH_DELAY_PROC_TIMER:

            PPPC_AccessAuthDelayTimeoutproc();

            break;

        default:
        {
            PPPC_WARNING_LOG1("unknow timer!\r\n", pPsMsg->ulPara);
        }
    }


    return;
}

/*****************************************************************************
 函 数 名  : PPP_SoftPara18_CallBack
 功能描述  : 回调函数, 本软参控制L2TP隧道建立消息中携带的IMSI信息格式
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012-10-14
    作    者   : zhaichao
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara534_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1146);
    g_ulSoftPara534 = ucNewValue;
    return ;
}

/*****************************************************************************
 函 数 名  : PPP_SoftPara89_CallBack
 功能描述  : 回调函数, 本软参控制lcp协商时是否进行地址域与协议域压缩的协商
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012-10-14
    作    者   : zhaichao
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_SoftPara89_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1147);
    g_ulSoftPara577 = ucNewValue;
    g_ulACompressOnoff = g_ulSoftPara577 & 0x01;
    g_ulPCompressOnoff = (g_ulSoftPara577 & 0x02) >> 1;
    return ;
}

/*****************************************************************************
 函 数 名  : PPP_SoftPara20_CallBack
 功能描述  : 回调函数, 本软参控制允许压缩协商的CPU门限
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012-10-14
    作    者   : zhaichao
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara20_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1148);
    g_ulDmpuCpuThreshold = ucNewValue;
    g_ulDmpuCpuThreshold = ((g_ulDmpuCpuThreshold > 0) && (g_ulDmpuCpuThreshold <= 100))?g_ulDmpuCpuThreshold:80;
    return ;
}


/*****************************************************************************
 函 数 名  : PPP_SoftPara21_CallBack
 功能描述  : 回调函数, 本软参控制允许压缩协商的VJ用户数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012-10-14
    作    者   : zhaichao
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara21_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1149);
    g_ulSoftPara537 = ucNewValue;
    g_ulMaxVJNum = ((50<=g_ulSoftPara537)&&(80>=g_ulSoftPara537))
                                ?(g_ulSoftPara537 * 100):6000;
    return ;
}

/*****************************************************************************
 函 数 名  : PPP_SoftPara99_CallBack
 功能描述  : 回调函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012-10-14
    作    者   : zhaichao
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara99_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1150);
    g_ulSoftPara585 = ucNewValue;
    if (g_ulSoftPara585 > 10)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1151);
        g_ulSoftPara585 = 0;
    }
    return ;
}

/*****************************************************************************
 函 数 名  : PPP_SoftPara100_CallBack
 功能描述  : 回调函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012-10-14
    作    者   : zhaichao
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara100_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1152);
    g_ulSoftPara586 = ucNewValue;

    if (g_ulSoftPara586 > 10)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1153);
        g_ulSoftPara586 = 0;
    }

    return ;
}
/*****************************************************************************
 函 数 名  : PPP_SoftPara569_CallBack
 功能描述  : 回调函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013-01-31
    作    者   : zhaichao
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara569_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1154);
    g_ucUdpCheckSumFlag = ucNewValue;
    return ;
}

/*****************************************************************************
 函 数 名  : PPP_SoftPara101_CallBack
 功能描述  : 回调函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012-10-14
    作    者   : zhaichao
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara101_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1155);
    g_ulSoftPara587 = ucNewValue;

    if (g_ulSoftPara587 > 10)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1156);
        g_ulSoftPara587 = 0;
    }

    return ;
}

/*****************************************************************************
 函 数 名  : PPP_SoftPara66_CallBack
 功能描述  : 回调函数, 用户名中不携带域信息时是否需要匹配到PDSN构造域,软参值为0时,不匹配构造域;否则,匹配
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012-10-14
    作    者   : zhaichao
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara66_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1157);
    g_ulSoftPara562 = ucNewValue;
    return ;
}

/*****************************************************************************
 函 数 名  : PPP_SoftPara71_CallBack
 功能描述  : 回调函数, Chap Response消息中是否允许不带用户属性,软参值为0时,不允许不带;否则,允许不带
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
1.日    期   : 2012-10-14
  作    者   : zhaichao
  修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara71_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1158);
    g_ulSoftPara567 = ucNewValue;
    return ;
}

/*****************************************************************************
 函 数 名  : PPP_SoftPara76_CallBack
 功能描述  : 回调函数, IPCP协商阶段PDSN发送的Request消息中携带的IP地址是2.2.2.2还是RP逻辑口地址
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012-10-14
    作    者   : zhaichao
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_SoftPara76_CallBack(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1159);
    g_ulSoftPara571 = ucNewValue;
    return ;
}

VOS_UINT32 SPM_GetByteValue(VOS_UINT32 ulSoftparaNum, UCHAR* ucByteValue)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_SoftParaInit
 功能描述  : 初始化PPP模块软参
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月8日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_SoftParaInit()
{
    VOS_UINT32 ulRet = VOS_OK;
    UCHAR ucSoftParaValue = 0;

    /*byte 18*/
    ulRet = SPM_GetByteValue(M_SPM_L2TP_IMSI_FORMAT, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara534 = ucSoftParaValue;
    }

    /*byte 66*/
    ulRet = SPM_GetByteValue(M_SPM_PDSN_MATCH_CONSTRUCTDOMAIN, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara562 = ucSoftParaValue;
    }

    /*byte 71*/
    ulRet = SPM_GetByteValue(M_SPM_PDSN_CHAPRESPONSE_USERNAME, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara567 = ucSoftParaValue;
    }

    /*byte 76*/
    ulRet = SPM_GetByteValue(M_SPM_PDSN_IPCP_IPADDR, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara571 = ucSoftParaValue;
    }

    /*byte 89*/
    ulRet = SPM_GetByteValue(M_SPM_PPPCOMPRESS_FLAG, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara577 = 0x3;//ucSoftParaValue;
    }

    /*byte 20*/
    ulRet = SPM_GetByteValue(M_SPM_PPPCOMPRESS_LIMIT, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulDmpuCpuThreshold = ucSoftParaValue;
    }

    /*byte 21*/
    ulRet = SPM_GetByteValue(M_SPM_PPPVJ_LIMIT, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara537 = ucSoftParaValue;
    }

    /*byte 99*/
    ulRet = SPM_GetByteValue(M_SPM_LCP_TRANSFER, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara585 = ucSoftParaValue;
    }

    /*byte 100*/
    ulRet = SPM_GetByteValue(M_SPM_AUTH_TRANSFER, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara586 = ucSoftParaValue;
    }

        /*byte 101*/
    ulRet = SPM_GetByteValue(M_SPM_IPCP_TRANSFER, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ulSoftPara587 = ucSoftParaValue;
    }

    /*byte 569*/
    ulRet = SPM_GetByteValue(M_SPM_PDSN_UDP_CHECKSUM, &ucSoftParaValue);
    if (VOS_OK == ulRet)
    {
        g_ucUdpCheckSumFlag = ucSoftParaValue;
    }

    g_ulDmpuCpuThreshold = ((g_ulDmpuCpuThreshold > 0) && (g_ulDmpuCpuThreshold <= 100))?g_ulDmpuCpuThreshold:80;
    g_ulMaxVJNum = ((50<=g_ulSoftPara537)&&(80>=g_ulSoftPara537))
                                ?(g_ulSoftPara537 * 100):6000;

    if (g_ulSoftPara585 > 10)
    {
        g_ulSoftPara585 = 0;
    }

    if (g_ulSoftPara586 > 10)
    {
        g_ulSoftPara586 = 0;
    }

    if (g_ulSoftPara587 > 10)
    {
        g_ulSoftPara587 = 0;
    }

    g_ulACompressOnoff = g_ulSoftPara577 & 0x01;
    g_ulPCompressOnoff = (g_ulSoftPara577 & 0x02) >> 1;


    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：创建PPP控制块,并链接到PPP控制块链表中                      *
* MODIFY DATE  ：modified by gxf for GGSN80 20030212                        *
* 输入参数     : VOS_UINT32 ulRpIndex                                            *
*                VOS_UINT16 usDomainIndex                                       *
*                VOS_UINT16 usVpnId                                             *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK:成功;VOS_ERR:失败                                   *
* CALLED BY    ：PPP封装函数                                                *
****************************************************************************/
VOS_UINT32 PPP_CreateCB(VOS_UINT32 ulRPIndex, PPP_LUPPARA_S *pstUpPara)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    VOS_UINT16 usIpv6addr[IPV6_ADDR_LEN] = {0XFE80,0,0,0,0,0,0,0};

    PPPC_INFO_LOG1("\r\n---Into PPP_CreateCB: ulRPIndex %u---\r\n", ulRPIndex);
    if (!((ulRPIndex <= PPP_MAX_USER_NUM)) || !pstUpPara)
    {
        PPPC_INFO_LOG("\r\n PPP_CreateCB: Parameter error!");
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1160);

    if (PPP_CB_STATE_USED == g_astPppPool[ulRPIndex].usState)
    {
        PPPC_INFO_LOG1("\r\n The user %u is already exist!", ulRPIndex);
        g_astPppPool[ulRPIndex].ulRPIndex = ulRPIndex;
        PPP_DBG_ERR_CNT(PPP_PHERR_490);
        (VOID)PPP_ClearCB(&g_astPppPool[ulRPIndex]);
    }

    pstPppInfo = &g_astPppPool[ulRPIndex];
    PPP_MemSet((VOID *)pstPppInfo, 0, sizeof(PPPINFO_S));

    /* 初始化LCP控制块时需要用到ulRPIndex，需先进行初始化 */
    pstPppInfo->ulRPIndex = ulRPIndex;

    if (VOS_OK != PPP_InitCB(pstPppInfo))
    {
        (VOID)PPP_ClearCB(pstPppInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_491);
        /* 返回失败 */
        PPPC_INFO_LOG("\r\n PPP_CreateCB: PPP_InitCB failed!");

        return VOS_ERR;
    }
    pstPppInfo->bEhrpdUser = pstUpPara->beHRPDMode;
    pstPppInfo->usTokenId = pstUpPara->usTokenId;

    pstPppInfo->usState = PPP_CB_STATE_USED;
    pstPppInfo->stIMSI = pstUpPara->stIMSI;
    pstPppInfo->ucServiceOpt = pstUpPara->ucServiceOpt;
    pstPppInfo->usPcfIndex = pstUpPara->usPcfIndex;
    pstPppInfo->ulPcfIP = pstUpPara->ulPcfIP;
    pstPppInfo->ulNegoStartTime = VOS_GetTick();
    pstPppInfo->usPeerId = VOS_NULL_WORD;
    pstPppInfo->ucAAAType = VOS_NULL_BYTE;
    pstPppInfo->ulNowUTCInSec = VOS_GetTick();
    pstPppInfo->bIPCPNakHandFlag = VOS_TRUE;

    /* 初始态置为无效,因为重协商时会置ip类型 */
    pstPppInfo->bIPTech = PPP_USERTYPE_NULL;

    /* 先把子卡和DPEID都置为无效 */
    pstPppInfo->ucDmpuId = 0xFF;
    pstPppInfo->ucDpeId  = 0xFF;

    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_LCP);

    if (0 == (g_ulSoftPara571 & 0x01))
    {
        pstPppInfo->ulIPAddr = g_ulA11RpifIp;
    }
    else
    {
        pstPppInfo->ulIPAddr = 0x2020202;  /* IPCP协商中本地地址采用固定地址2.2.2.2 */
    }

    pstPppInfo->usCDBIndex = VOS_NULL_WORD;
    pstPppInfo->usVirtualDomainIdx = VOS_NULL_WORD;

    /* IPV6CP协商中本地地址采用固定地址FE80::rp口v4地址*/
    VOS_MemCpy((void *)(&usIpv6addr[6]), (void *)&(g_ulA11RpifIp),sizeof(VOS_UINT32));
    VOS_MemCpy(pstPppInfo->usIpv6Addr, usIpv6addr, IPV6_ADDR_LEN*2);

    /* 初始化配置信息 */
    if (VOS_OK != PPP_InitConfigInfo(pstPppInfo) )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_492);
        (VOID)PPP_ClearCB(pstPppInfo);
        pstPppInfo->usState = PPP_CB_STATE_FREE;
        PPPC_WARNING_LOG("\r\n PPP_CreateCB: PPP_InitConfigInfo failed!");

        return VOS_ERR;
    }

    pstPppInfo->ulPppInactTimerLen      = g_stPppContext.stHrpdContext.ulPppInactTimerLen;
    pstPppInfo->enInactiveTimerEnable   = PS_FALSE;
    pstPppInfo->hPppInactiveTimer       = VOS_NULL_PTR;

    (VOID)PPP_NodeAdd(ulRPIndex, 0, PPP_NEGO_LIST_NODE_LCP_START);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_DeleteCB
 功能描述  : 删除PPP控制块,并从PPP控制块链表中删除它
 输入参数  : PPPINFO_S *pstPppInfo
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_DeleteCB(PPPINFO_S *pstPppInfo, PS_BOOL_ENUM_UINT8 enNeedCnf)
{
    VOS_UINT8                           ucPppId;
    VOS_UINT32                          ulRet;


    if ((VOS_NULL_PTR == pstPppInfo) || (PPP_CB_STATE_FREE == pstPppInfo->usState))
    {
        return VOS_ERR;
    }

    ucPppId = (VOS_UINT8)pstPppInfo->ulRPIndex;

    PPPC_WARNING_LOG2("Into Delete PPP Info", ucPppId, enNeedCnf);

    if (PS_TRUE == enNeedCnf)
    {
        PPPC_JudgeCmdRseultWhenDeleteCB(ucPppId);
    }

    ulRet = PPP_StopNegoTimer((VOS_UINT8)pstPppInfo->ulRPIndex);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("stop nego timer fail!\r\n", ulRet);
    }

    /* 停MAX PPP Inactive Timer定时器 */
    pstPppInfo->enInactiveTimerEnable = PS_FALSE;
    if (VOS_NULL_PTR != pstPppInfo->hPppInactiveTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstPppInfo->hPppInactiveTimer));
        pstPppInfo->hPppInactiveTimer = VOS_NULL_PTR;
    }

    PPP_INNER_COUNTER(PPP_INNER_COUTNER_040);
    PPP_DBG_OK_CNT(PPP_PHOK_1161);

    PPPC_INFO_LOG1("\r\n---Into PPP_DeleteCB: ulRPIndex %u---\r\n", pstPppInfo->ulRPIndex);

    /* 删除PPP控制块时需要清空消息队列 */
    PPPC_ClearUlDataQ();
    PPPC_ClearDlDataQ();

    /* 清除控制块内部数据 */
    (VOID)PPP_ClearCB(pstPppInfo);

    g_astPppPool[pstPppInfo->ulRPIndex].usState = PPP_CB_STATE_FREE;

    (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);

    /* 清除ppp id和Pdn id之间的映射关系 */
    PPPC_ClearMappingByPppId((VOS_UINT8)pstPppInfo->ulRPIndex);

    PPP_MemSet(&g_astPppPool[pstPppInfo->ulRPIndex], 0, sizeof(PPPINFO_S));



    /* 初始化PA AGENT上下文 */
    PPPC_HRPD_PaAgentInit();

    /* 清除上行数据内存 */
    PPPC_ClearUlEncapMem();

    /* 清除分片重组状态 */
    FWD_PppRebuildIncompleteSliceStatInit();

    g_ucLcpTermMask = PS_FALSE;

    return VOS_OK;
}



/****************************************************************************
* CREATE DATE  ：2009-02-25                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     ：PPP_ClearCB_LCP清除PPP控制块LCP数据                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：PPPLCPINFO_S *pstPppLcpInfo                                *
* OUTPUT       ：无                                                         *
* RETURN       ：无                                                         *
* CALLED BY    ：PPP_ClearCB                                                *
****************************************************************************/
VOID PPP_ClearCB_LCP(PPPLCPINFO_S *pstPppLcpInfo)
{
    PPPLCPINFO_S * pstLcpInfo = (PPPLCPINFO_S *)pstPppLcpInfo;
    /*添加对于定时器的保护*/
    if (pstLcpInfo->stFsm.ulTimeOutID)
    {
        /*modified by huzhiyong 去掉断言，在这里删除重传定时器属正常流程2002/03/08*/

        /*
            VOS_DBGASSERT(0);
         */
        (VOID)VOS_StopRelTimer(&(pstLcpInfo->stFsm.ulTimeOutID));
        pstLcpInfo->stFsm.ulTimeOutID = 0;
    }

    if (pstLcpInfo->stFsm.ulEchoTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstLcpInfo->stFsm.ulEchoTimeoutID));
        pstLcpInfo->stFsm.ulEchoTimeoutID = 0;
    }
    pstLcpInfo->ucUsedFlag = 0;
    return;
}

/****************************************************************************
* CREATE DATE  ：2009-03-17                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     ：PPP_ClearCB_PAP清除PPP控制块PAP数据                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：PPPPAPINFO_S *pstPppPapInfo                                *
* OUTPUT       ：无                                                         *
* RETURN       ：无                                                         *
* CALLED BY    ：PPP_ClearCB                                                *
****************************************************************************/
VOID PPP_ClearCB_PAP(PPPPAPINFO_S *pstPppPapInfo)
{
    PPPPAPINFO_S * pstPapInfo = pstPppPapInfo;
    PPPC_INFO_LOG("\r\n PPP_ClearCB_PAP: Delete PAPINFO!");

    /*添加对于定时器的保护*/
    if (pstPapInfo->ulServerTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulServerTimeoutID));
        pstPapInfo->ulServerTimeoutID = 0;
    }

    if (pstPapInfo->ulClientTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstPapInfo->ulClientTimeoutID));
        pstPapInfo->ulClientTimeoutID = 0;
    }

    if (VOS_NULL_PTR != pstPapInfo->pstAAAAuthReqMsg)
    {
        (VOID)PPP_Free(pstPapInfo->pstAAAAuthReqMsg);
        pstPapInfo->pstAAAAuthReqMsg = VOS_NULL_PTR;
    }
    pstPapInfo->ucUsed = 0;
    return;
}

/****************************************************************************
* CREATE DATE  ：2009-03-17                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     ：PPP_ClearCB_CHAP清除PPP控制块CHAP数据                      *
* MODIFY DATE  ：                                                           *
* INPUT        ：PPPCHAPINFO_S *pstPppChapInfo                              *
* OUTPUT       ：无                                                         *
* RETURN       ：无                                                         *
* CALLED BY    ：PPP_ClearCB                                                *
****************************************************************************/
VOID PPP_ClearCB_CHAP(PPPCHAPINFO_S *pstPppChapInfo)
{
    PPPCHAPINFO_S * pstChapInfo = pstPppChapInfo;
    PPPC_INFO_LOG("\r\n PPP_ClearCB_CHAP: Delete CHAPINFO!");

    /*添加对于定时器的保护*/
    if (pstChapInfo->ulRespTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    if (pstChapInfo->ulChalTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (VOS_NULL_PTR != pstChapInfo->pstAAAAuthReqMsg)
    {
        (VOID)PPP_Free(pstChapInfo->pstAAAAuthReqMsg);
        pstChapInfo->pstAAAAuthReqMsg = VOS_NULL_PTR;
    }
    pstChapInfo->ucUsed = 0;
    return;
}

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
/****************************************************************************
* CREATE DATE  ：2010-07-17                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：PPP_ClearCB_EAP清除PPP控制块EAP数据                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：PPPC_EAP_INFO_STRU *pstPppEapInfo                                *
* OUTPUT       ：无                                                         *
* RETURN       ：无                                                         *
* CALLED BY    ：PPP_ClearCB                                                *
****************************************************************************/
VOID PPP_ClearCB_EAP(PPPC_EAP_INFO_STRU *pstPppEapInfo)
{
    PPPC_EAP_INFO_STRU *pstEapInfo = pstPppEapInfo;
    PPPC_INFO_LOG("\r\n PPP_ClearCB_EAP: Delete EAPINFO!");

    /*添加对于定时器的保护*/
    if (VOS_NULL_PTR != pstEapInfo->hReqTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&pstEapInfo->hReqTimeoutID);
        pstEapInfo->hReqTimeoutID = 0;
    }

    PPPC_EAP_Init(pstEapInfo->pstPppInfo);

    return;
}
#endif

/*****************************************************************************
 函 数 名  : PPP_ClearCB_IPCP
 功能描述  : PPP_ClearCB_IPCP清除PPP控制块IPCP数据
 输入参数  : PPPIPCPINFO_S *pstIpcpInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_ClearCB_IPCP(PPPIPCPINFO_S *pstIpcpInfo)
{
    if (VOS_NULL_PTR == pstIpcpInfo)
    {
        return ;
    }

    /*添加对于定时器的保护*/
    if (pstIpcpInfo->stFsm.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstIpcpInfo->stFsm.ulTimeOutID));
        pstIpcpInfo->stFsm.ulTimeOutID = 0;
    }

    if (pstIpcpInfo->pstPppInfo && pstIpcpInfo->pstPppInfo->bVjFlag)
    {
        PPP_CompUserNumDel(pstIpcpInfo->pstPppInfo, PPP_USERSTAT_VJ);
    }

    /* 增加缓存消息保护释放 */
    if ( pstIpcpInfo->pucIpv4cpMsg )
    {
        (VOID)PPP_Free(pstIpcpInfo->pucIpv4cpMsg);
        pstIpcpInfo->pucIpv4cpMsg = VOS_NULL_PTR;
        pstIpcpInfo->ulIpv4cpLen = 0;
    }

    pstIpcpInfo->ucUsedFlag = 0;
    return;
}

/*****************************************************************************
 函 数 名  : PPP_ClearCB_IPV6CP
 功能描述  : 清除PPP控制块IPV6CP数据
 输入参数  : PPPIPV6CPINFO_S *pstPppIpv6cpInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_ClearCB_IPV6CP(PPPIPV6CPINFO_S *pstPppIpv6cpInfo)
{
    PPPIPV6CPINFO_S * pstIpv6cpInfo = pstPppIpv6cpInfo;

    if (VOS_NULL_PTR == pstPppIpv6cpInfo)
    {
        return ;
    }

    /*添加对于定时器的保护*/
    if (pstIpv6cpInfo->stFsm.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstIpv6cpInfo->stFsm.ulTimeOutID));
        pstIpv6cpInfo->stFsm.ulTimeOutID = 0;
    }

    /* 增加缓存消息保护释放 */
    if ( pstIpv6cpInfo->pucIpv6cpMsg )
    {
        (VOID)PPP_Free(pstIpv6cpInfo->pucIpv6cpMsg);
        pstIpv6cpInfo->pucIpv6cpMsg = VOS_NULL_PTR;
        pstIpv6cpInfo->ulIpv6cpLen = 0;
    }

    if (0 != pstIpv6cpInfo->ucUsedFlag)
    {
        pstIpv6cpInfo->ucUsedFlag = 0;
        PPP_DBG_OK_CNT(PPP_PHOK_1166);
    }

    return;
}

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
/****************************************************************************
* CREATE DATE  ：2009-03-17                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     ：PPP_ClearCB_CCP清除PPP控制块CCP数据                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：PPPMSIDINFO_S *pstPppCcpInfo                               *
* OUTPUT       ：无                                                         *
* RETURN       ：无                                                         *
* CALLED BY    ：PPP_ClearCB                                                *
****************************************************************************/
VOID PPP_ClearCB_CCP(PPP_CCP_INFO_S *pstCcpInfo)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_ClearCB_CCP: Delete CCPINFO!");

    if (VOS_NULL_PTR == pstCcpInfo)
    {
        return;
    }

    /*添加对于定时器的保护*/
    if (pstCcpInfo->stFsm.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstCcpInfo->stFsm.ulTimeOutID));
        pstCcpInfo->stFsm.ulTimeOutID = 0;
    }

    if (pstCcpInfo->ulCcpTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstCcpInfo->ulCcpTimeoutID));
        pstCcpInfo->ulCcpTimeoutID = 0;
    }

    pstCcpInfo->ucPppCompType = 0;
    pstCcpInfo->ucUsed = 0;

    /* 清除压缩用户数统计 */
    pstPppInfo = pstCcpInfo->pstPppInfo;
    if (pstPppInfo)
    {
        if (pstPppInfo->bMppcFlag)
        {
            PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_MPPC);
        }
        if (pstPppInfo->bLzs0Flag)
        {
            PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS0);
        }
        if (pstPppInfo->bLzs1Flag)
        {
            PPP_CompUserNumDel(pstPppInfo, PPP_USERSTAT_ZLS1);
        }
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2009-03-17                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     ：PPP_ClearCB_STAC清除PPP控制块STAC数据                      *
* MODIFY DATE  ：                                                           *
* INPUT        ：STAC_COMPRESSINFO_S *pstPppStacCompressInfo                *
*                STAC_DECOMPRESSINFO_S *pstPppStacDecompressInfo            *
* OUTPUT       ：无                                                         *
* RETURN       ：无                                                         *
* CALLED BY    ：PPP_ClearCB                                                *
****************************************************************************/
VOID PPP_ClearCB_STAC(STAC_COMPRESSINFO_S *pstPppStacCompressInfo, STAC_DECOMPRESSINFO_S* pstPppStacDecompressInfo)
{
    if (pstPppStacCompressInfo)
    {
        (VOID)PPP_Free(pstPppStacCompressInfo);
    }

    if (pstPppStacDecompressInfo)
    {
        STAC_DECOMPRESSINFO_S* pstStacDecompressInfo = pstPppStacDecompressInfo;

        /*添加对于定时器的保护*/
        if (pstStacDecompressInfo->ulTimeoutID)
        {
            (VOID)VOS_StopRelTimer(&(pstStacDecompressInfo->ulTimeoutID));
            pstStacDecompressInfo->ulTimeoutID = 0;
        }
        (VOID)PPP_Free(pstPppStacDecompressInfo);
    }

    return;
}
#endif

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：清除PPP控制块内部数据                                      *
* MODIFY DATE  ：modified by gxf 20030317                                   *
* INPUT        ：pstPppInfo:PPP控制块                                       *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK:成功;VOS_ERR:失败                                   *
* CALLED BY    ：PPP_DeleteCB、PPP_CreateCB                                 *
****************************************************************************/
VOS_UINT32 PPP_ClearCB_TestStub(PPPINFO_S *pstPppInfo)
{
    if (!pstPppInfo)
    {
        return VOS_ERR;
    }

    /* 清除配置信息 */
    PPP_ClearConfigInfo(pstPppInfo);

    /*
      在删除PPP控制块以前一定有一个LOW DOWN事件，所以所有的NCP控制块应该为NULL
      如果，程序执行到断言的时候，或者是低层或者是IPC出现了问题
      而PPP自身加以保护，不会影响PPP本身,该断言仅有提示的作用
      shiyong 2001/04/27
     */

    /* 清除子协议控制块 */
    PPP_ClearLCPCB(pstPppInfo->pstLcpInfo);


    PPP_ClearPAPCB(pstPppInfo->pstPapInfo);

    PPP_ClearCHAPCB(pstPppInfo->pstChapInfo);

    PPP_ClearIPCPCB(pstPppInfo->pstIpcpInfo);

    PPP_ClearIPV6CPCB(pstPppInfo->pstIpV6cpInfo);

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
#endif

    /* L2TP需要的参数 */
    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    if (pstPppInfo->pstPppRenegoInfo)
    {
        (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
        pstPppInfo->pstPppRenegoInfo = VOS_NULL_PTR;
    }

    if (pstPppInfo->bEhrpdUser)
    {
        PPP_VSNCP_ClearALL(pstPppInfo);
    }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    PPP_ClearEAPCB(pstPppInfo->pstEapInfo);
#endif

    pstPppInfo->usState = PPP_CB_STATE_FREE;

    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：清除PPP控制块内部数据                                      *
* MODIFY DATE  ：modified by gxf 20030317                                   *
* INPUT        ：pstPppInfo:PPP控制块                                       *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK:成功;VOS_ERR:失败                                   *
* CALLED BY    ：PPP_DeleteCB、PPP_CreateCB                                 *
****************************************************************************/
VOS_UINT32 PPP_ClearCB(PPPINFO_S *pstPppInfo)
{
    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
        return PPP_ClearCB_TestStub(pstPppInfo);
    }

    if (!pstPppInfo)
    {
        return VOS_ERR;
    }

    /* 删除老的hash */
    if ((pstPppInfo->usPeerId != VOS_NULL_WORD)
        && (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1167);
        if (VOS_OK != Diam_AUTHHostRemoveByAAACBIndex(pstPppInfo->usPeerId, pstPppInfo->ulRPIndex))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_493);
        }
        pstPppInfo->usPeerId = VOS_NULL_WORD;
        pstPppInfo->ucAAAType = VOS_NULL_BYTE;
    }
    /* 清除配置信息 */
    PPP_ClearConfigInfo(pstPppInfo);

    /*
      在删除PPP控制块以前一定有一个LOW DOWN事件，所以所有的NCP控制块应该为NULL
      如果，程序执行到断言的时候，或者是低层或者是IPC出现了问题
      而PPP自身加以保护，不会影响PPP本身,该断言仅有提示的作用
      shiyong 2001/04/27
     */

    /* 清除子协议控制块 */
    PPP_ClearLCPCB(pstPppInfo->pstLcpInfo);


    PPP_ClearPAPCB(pstPppInfo->pstPapInfo);

    PPP_ClearCHAPCB(pstPppInfo->pstChapInfo);

    PPP_ClearIPCPCB(pstPppInfo->pstIpcpInfo);

    PPP_ClearIPV6CPCB(pstPppInfo->pstIpV6cpInfo);

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)
    PPP_ClearCCPCB(pstPppInfo->pstCcpInfo);
#endif

    /* L2TP需要的参数 */
    if (pstPppInfo->pL2tpPara != VOS_NULL_PTR)
    {
        (VOID)PPP_Free(pstPppInfo->pL2tpPara);
        pstPppInfo->pL2tpPara = VOS_NULL_PTR;
    }

    if (pstPppInfo->pstPppRenegoInfo)
    {
        (VOID)PPP_Free(pstPppInfo->pstPppRenegoInfo);
        pstPppInfo->pstPppRenegoInfo = VOS_NULL_PTR;
    }

    PPPC_WARNING_LOG1("Clearn VSNCP INFO", pstPppInfo->bEhrpdUser);
    if (pstPppInfo->bEhrpdUser)
    {
        PPP_VSNCP_ClearALL(pstPppInfo);
    }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    PPP_ClearEAPCB(pstPppInfo->pstEapInfo);
#endif

    pstPppInfo->usState = PPP_CB_STATE_FREE;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_DelAllResource
 功能描述  : 删除ppp控制块资源
 被调函数  :
 调用函数  :
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  :
 返 回 值  : VOID

 修改历史      :
  1.日    期   : 2013年8月19日
    作    者   : w00138171
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_DelAllResource(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    /* 根据 RPIndex 获取 PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if(VOS_NULL_PTR == pstPppInfo)
    {
        return;
    }

    /* 如果是ehrpd用户, 需要通知diam auth发送STR消息, 但是不需要等待响应 */
    if ((VOS_TRUE == pstPppInfo->bEhrpdUser)
       && (VOS_NULL_WORD != pstPppInfo->usPeerId))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1168);
#if 0
        PPP_EAP_NotifyDiamAuthRelease(pstPppInfo);
#endif
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1169);

    (VOID)PPP_ClearCB(pstPppInfo);

    PPP_MemSet(pstPppInfo, 0, sizeof(PPPINFO_S));

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：初始化PPP控制块                                            *
* MODIFY DATE  ：modified by gxf for GGSN80 20030212                        *
* INPUT        ：pstPppInfo:PPP控制块                                       *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK:成功;VOS_ERR:失败                                   *
* CALLED BY    ：PPP_CreateCB                                               *
****************************************************************************/
VOS_UINT32 PPP_InitCB(PPPINFO_S *pstPppInfo)
{
    if (!pstPppInfo)
    {
        return VOS_ERR;
    }

    /* 初始化接口的debug开关状态为当前全局开关状态 */
    pstPppInfo->stPppDebugInfo = g_stPppDebugInfo;

    PPP_GETLCPADDR(pstPppInfo->pstLcpInfo, pstPppInfo->ulRPIndex);

    /* 初始化LCP控制块
       如果申请内存失败在PPP_Core_ReceiveEventFromShell中会再次申请 */
    if (pstPppInfo->pstLcpInfo)
    {
        PPP_MemSet((void *)pstPppInfo->pstLcpInfo, 0, sizeof(PPPLCPINFO_S));
        PPP_LCP_Init(pstPppInfo);
    }

    /*初始化子协议控制块*/
    pstPppInfo->pstIpcpInfo = VOS_NULL_PTR;       /* IPCP 控制块指针 */
    pstPppInfo->pstIpV6cpInfo = VOS_NULL_PTR;     /* IPV6CP 控制块指针 */
    pstPppInfo->pstCcpInfo = VOS_NULL_PTR;        /* CCP  控制块指针 */
    pstPppInfo->pL2tpPara = VOS_NULL_PTR;         /* L2TP 参数 */

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

    PPP_GETHDLCADDR(pstPppInfo->pstHdlcInfo, pstPppInfo->ulRPIndex);

    /* 初始化HDLC控制块 */
    if (pstPppInfo->pstHdlcInfo)
    {
        PPP_MemSet((void *)pstPppInfo->pstHdlcInfo, 0, sizeof(PPPC_HDLC_STRU));
    }

#endif
    /* 初始化其他信息 */
    /*pstPppInfo->ulResetTimerId = 0 ;*/
    pstPppInfo->usPhase = (UCHAR)PPP_PHASE_DEAD;

    pstPppInfo->bAuthServer = VRP_NO;
    pstPppInfo->bAuthClient = VRP_NO;

 #ifdef __PRODUCT_TYPE_PDSN80
    pstPppInfo->bIsAsync = 1;
    pstPppInfo->bSynAsyConvert = 1;

    /* 缺省同/异步转换字符集
       lcp opened前采用0xffffffff，lcp opened后采用ulLocalAccm | ulRemoteAccm进行转换
     */
 #else
    pstPppInfo->bIsAsync = 1;
    pstPppInfo->bSynAsyConvert = 1;
 #endif
    pstPppInfo->ulRemoteAccm = VOS_HTONL(0xffffffff);
    pstPppInfo->ulLocalAccm = VOS_HTONL(PPP_DEFAULT_ACCM);

    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2009-03-16                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     ：压缩配置值初始化                                           *
* MODIFY DATE  ：modified by c00127007 for AP8D06810                        *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_InitConfigInfo                                         *
****************************************************************************/
VOID PPP_CompInitInfo(PPPCONFIGINFO_S *pstConfigInfo)
{
 #ifdef    __PRODUCT_TYPE_PDSN80
    /* Modified start by liutao 38563 at 2004-10-29 V800R002 for PPPC移植 */
    if (g_ucPppCcpType & M_PPPCOMPRESS_MPPC_FLAG)
    {
        pstConfigInfo->bMppcCompress = 1;
    }
    else
    {
        pstConfigInfo->bMppcCompress = 0;
    }

    if (g_ucPppCcpType & M_PPPCOMPRESS_STAC_FLAG)
    {
        pstConfigInfo->bStacCompress = 1;
    }
    else
    {
        pstConfigInfo->bStacCompress = 0;
    }

    /* Modified end by liutao 38563 at 2004-10-29 V800R002 for PPPC移植 */
 #endif
}

/*****************************************************************************
 函 数 名  : PPP_GetUserMru
 功能描述  : 根据用户角色获取mru
 输入参数  : VOS_UINT32 ulEhrpdFlg
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月6日
    作    者   : y00138047
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 PPP_GetUserMru(VOS_UINT32 ulEhrpdFlg)
{
    /* (CR-0000050651---MRU长度变化)
       如果配置的mru不等于1501时，PDSN、HSGW均使用配置的mru进行协商；如果配
       置的mru为1501时，PDSN按照1500协商，HSGW按照1501协商 */

    if ( (PPP_MRU_MAX_HSGW == g_stPppCfgInfo.usMru)
         && VOS_TRUE != ulEhrpdFlg )
    {
        return PPP_MRU_MAX_PDSN;
    }

    return g_stPppCfgInfo.usMru;
}
/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：初始化PPP配置信息                                          *
* MODIFY DATE  ：modified by gxf for GGSN80 20030212                        *
* INPUT        ：pstPppInfo:PPP控制块                                       *
* OUTPUT       ：                                                           *
* RETURN       ：VOS_OK:成功;VOS_ERR:失败                                   *
* CALLED BY    ：PPP_InitCB                                                 *
****************************************************************************/
VOS_UINT32 PPP_InitConfigInfo(PPPINFO_S *pstPppInfo)
{
    PPPCONFIGINFO_S *pstConfigInfo = VOS_NULL_PTR;
    DOMAINDNS_S stApnDns = { 0 };  /* DNS配置 */

    if (!pstPppInfo)
    {
        return VOS_ERR;
    }

    PPP_GETCONFIGADDR(pstConfigInfo,pstPppInfo->ulRPIndex);
    if (!pstConfigInfo)
    {
        /* 失败 */
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Config Info: Malloc Err!!");
        return VOS_ERR;
    }

    PPP_MemSet((VOID *)pstConfigInfo, 0, sizeof(PPPCONFIGINFO_S));
    pstConfigInfo->bUsedFlag = 1;

    if (pstPppInfo->bEhrpdUser)
    {
        pstConfigInfo->bAuthMethod = 1;
        pstConfigInfo->bAuthRmtPap = 0;
        pstConfigInfo->bAuthRmtChap = 0;
        pstConfigInfo->bAuthRmtEap = 1;
    }
    else
    {
        pstConfigInfo->bAuthMethod = g_stPppCfgInfo.ucAuthmod;
        pstConfigInfo->bAuthRmtEap= 0;

        /* 如果配置为对用户鉴权，允许对用户进行PAP或CHAP验证 */
        if (0 != pstConfigInfo->bAuthMethod)
        {
            /* 认证方式优先级 0:both pap and chap 1:only pap 2:only chap */
            if (g_stPppCfgInfo.ucAuthoption != 2)
            {
                pstConfigInfo->bAuthRmtPap = 1;
            }

            if (g_stPppCfgInfo.ucAuthoption != 1)
            {
                pstConfigInfo->bAuthRmtChap = 1;
            }
        }

    }

    /* mod begin by y00138047 for (CR-0000050651---MRU长度变化) */
    pstConfigInfo->usMru = PPP_GetUserMru(pstPppInfo->bEhrpdUser);
    /* mod end by y00138047 for (CR-0000050651---MRU长度变化) */

    VOS_StrCpy((CHAR*)pstConfigInfo->cChapHostName, (CHAR*)g_stPppCfgInfo.aucHostname);
    if ((g_stPppCfgInfo.ucTimeout > 0) && (g_stPppCfgInfo.ucTimeout <= (PPP_MAXTIMEOUTTIME / 1000)))
    {
        pstConfigInfo->ulNegTimeOut = g_stPppCfgInfo.ucTimeout * 1000;
    }
    else
    {
        pstConfigInfo->ulNegTimeOut = PPP_DEFTIMEOUTTIME;
        PPPC_INFO_LOG("\r\n PPP NegoTimeouttime configure error!");
    }

    /* 从CDB中获取DNS */
    if (VOS_OK == (RDA_GetApnDNSCfg(pstPppInfo->usCDBIndex, (APNDNS_S *)&stApnDns)))
    {
        pstPppInfo->ulDNSAddr1 = stApnDns.ulMainDNSServer;
        pstPppInfo->ulDNSAddr2 = stApnDns.ulBackupDNSServer;
    }
    /* Modified by hyj for B02 */
    else if (VOS_OK == (RDA_GetApnDNSCfg(AAA_DEFAULT_DOMAIN_INDEX, (APNDNS_S *)&stApnDns)))
    {
        pstPppInfo->ulDNSAddr1 = stApnDns.ulMainDNSServer;
        pstPppInfo->ulDNSAddr2 = stApnDns.ulBackupDNSServer;
    }
    else
    {
        PPPC_INFO_LOG("\r\n PPP_InitConfigInfo: Get DNS configure information failed!");
    }

    /* 不对用户鉴权 */
    if (!pstConfigInfo->bAuthMethod)
    {
        /* 缺省域配置信息 */
        pstPppInfo->usCDBIndex = 0;
        pstPppInfo->usVirtualDomainIdx = 0;
        VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR*)g_pstApnByIndex[0].aucAPN);
    }

    if (g_stPppCfgInfo.ucVSNCPFlag & PPP_VSNCP_APN_AMBR_FLAG)
    {
        pstConfigInfo->bVsncpAPNAmbrFlag = VOS_TRUE;

    }
    if (g_stPppCfgInfo.ucVSNCPFlag & PPP_VSNCP_DEFUALT_APN_INDICATIOR_FLAG)
    {
        pstConfigInfo->bVsncpDefApnIndFlag = VOS_TRUE;

    }

    /* 压缩配置值初始化 */
    PPP_CompInitInfo(pstConfigInfo);

    pstPppInfo->pstUsedConfigInfo = pstConfigInfo;
    pstPppInfo->pstConfigInfo = pstConfigInfo;



    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2000/04/04                                                 *
* CREATED BY   ：Deng Yi Ou                                                 *
* FUNCTION     ：清除PPP配置信息                                            *
* MODIFY DATE  ：modified by gxf for GGSN80 20030212                        *
* INPUT        ：pstPppInfo:PPP控制块                                       *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_ClearCB                                                *
****************************************************************************/
VOID PPP_ClearConfigInfo(PPPINFO_S *pstPppInfo)
{
    if (!pstPppInfo)
    {
        return;
    }

    if (pstPppInfo->pstUsedConfigInfo)
    {
        ((PPPCONFIGINFO_S *)pstPppInfo->pstUsedConfigInfo)->bUsedFlag = 0;
        pstPppInfo->pstUsedConfigInfo = VOS_NULL_PTR;
    }

    pstPppInfo->pstConfigInfo = VOS_NULL_PTR;
    pstPppInfo->pstUsedConfigInfo = VOS_NULL_PTR;

    return;
}


/*****************************************************************************
 函 数 名  : PPP_UP
 功能描述  : PPP模块提供给A11的接口函数，当A10链路建好后，直接通知PPP，避免任务切换
 输入参数  : VOS_UINT32 ulRPIndex
             PPP_LUPPARA_S*pstUpPara
 输出参数  : 无
 返 回 值  : VOS_UINT32 VOS_OK/VOS_ERR
 调用函数  : PPP_A11_IoCtl
 被调函数  :

 修改历史      :
  1.日    期   : 2005年9月24日
    作    者   : ZhangJun HT04406
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_UP(VOS_UINT32 ulRPIndex, PPP_LUPPARA_S*pstUpPara)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    /* 参数检查 */
    if (VOS_NULL_PTR == pstUpPara)
    {
        return VOS_ERR;
    }

    /* 参数ulRPIndex会在PPP_CreateCB中检查,故此处不检查 */

    /* 创建PPP控制块 */
    if (VOS_OK != PPP_CreateCB(ulRPIndex, pstUpPara))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_494);
        /* 创建ppp控制块失败 */
        return VOS_ERR;
    }

    /* 根据 RPIndex 获取 PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);

    /* 此处无需检查 PPP控制块 是否有效 */

    /* 如果不进行鉴权，则提前发出DHCP请求 */

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_495);
        PPPC_INFO_LOG("\r\n PPP_UP: GETPPPINFOPTRBYRP failed!");
        return VOS_ERR;
    }

    PPP_Core_ReceiveEventFromShell(pstPppInfo, (VOS_UINT32)PPPISLUP, VOS_NULL_PTR);/* Added by l61463 at 2008-07-14 PDSN V9 for PPP协商 */

    /* 处理成功 */
    return VOS_OK;
}

/* Added End by ZhangJun HT04406 at 2005/09/24 for PDSN激活优化 */

/*****************************************************************************
 函 数 名  : PPP_A11_IsLupProc
 功能描述  : 激活用户时，PPP的处理函数
 输入参数  : VOS_UINT32 ulRPIndex
             CHAR *pPara
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-03-17
    作    者   : c00127007
    修改内容   : 新生成函数 for reduce CC

*****************************************************************************/
VOS_UINT32 PPP_A11_IsLupProc(VOS_UINT32 ulRPIndex, CHAR *pPara)
{
    if (!pPara)
    {
        PPPC_INFO_LOG("\r\n PPP_A11_IsLupProc: UPPara is VOS_NULL_PTR!");
        return VOS_ERR;
    }

    if (VOS_OK != PPP_UP(ulRPIndex, (PPP_LUPPARA_S*)pPara))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_496);
        PPPC_INFO_LOG("\r\n PPP_A11_IsLupProc: Call PPP_UP() Failed!");
        return VOS_ERR;
    }

    return VOS_OK;       /* Added by l61463 at 2008-07-14 PDSN V9 for PPP协商 */
}


/*****************************************************************************
 函 数 名  : PPP_UsmIsLdownProc
 功能描述  :PPP模块提供给USM的 去活通知函数(写PPP的消息队列)
 输入参数  : VOS_UINT32 ulRPIndex
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009-03-17
    作    者   : c00127007
    修改内容   : 新生成函数 for reduce CC
   zhaichao for pdsn 切平台 mod
*****************************************************************************/
VOS_UINT32 PPP_UsmIsLdownProc(VOS_UINT32 ulRPIndex, UCHAR* pucPara)
{
    PPP_A11MSG_S stMsg = {0};
    VOS_UINT32 ulRet = VOS_OK;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    SDB_RETURNCODE_E enSdbReturn = SDB_SUCCESS;
    PppLDownPara *pstDownPara = (PppLDownPara *)pucPara;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    PPPC_INFO_LOG1("\r\n PPP_UsmIsLdownProc: Lower notify user %u down", ulRPIndex);

    GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_497);
        return VOS_ERR;
    }

    enSdbReturn = (SDB_RETURNCODE_E)SDB_GetRpContextByIndex(ulRPIndex,
                                                            (VOS_VOID **)&pstRpContext);
    if ((SDB_SUCCESS != enSdbReturn) || (VOS_NULL_PTR == pstRpContext))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_498);
        PPPC_INFO_LOG("\r\n PPP_UsmIsLdownProc: Failed to Query SDB!");

        return VOS_ERR;
    }

    stMsg.ulRPIndex = ulRPIndex;
    stMsg.ulMsgCode = PPP_MSG_CODE_LINK_DOWN;

    if (pstDownPara != VOS_NULL_PTR)
    {
        stMsg.ulLcpSendFlag = pstDownPara->ulLcpSendFlag;
        PPPC_INFO_LOG1(
                                "\r\n PPP_UsmIsLdownProc: LCP flag = %u",
                                pstDownPara->ulLcpSendFlag);
    }

    if (VOS_FALSE == stMsg.ulLcpSendFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1170);
        (VOID)PPP_USMNotifyRelease(&stMsg);
        PPPC_INFO_LOG1("\r\n PPP_USMNotifyRelease: notify ppp %u down; no need send LCP", ulRPIndex);
        return VOS_OK;
    }

    ulRet = PPP_SendRtMsg(g_ullPppA11Csi,
                         PPP_SELF_CSI,
                         PPP_MSG_TYPE_USM,
                         PPP_MSG_CODE_LINK_DOWN,
                         (UCHAR *)&stMsg,
                         sizeof( PPP_A11MSG_S ));
    if ( VOS_OK != ulRet )
    {

        PPP_DBG_ERR_CNT(PPP_PHERR_499);
        PPPC_INFO_LOG("\r\n PPP_UsmIsLdownProc: PPP_SendRtMsg failed!");
        return VOS_ERR;

    }
    PPP_DBG_OK_CNT(PPP_PHOK_1171);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Ppp_UsmIoCtl
 功能描述  : USM通知PPP底层UP和底层DOWN
 输入参数  : VOS_UINT32 ulRPIndex
             VOS_UINT32 ulCmd
             CHAR *pPara
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Ppp_UsmIoCtl(VOS_UINT32 ulRPIndex, VOS_UINT32 ulCmd, CHAR *pPara)
{
    VOS_UINT32 ulRet = VOS_OK;

    if (!((ulRPIndex <= PPP_MAX_USER_NUM)) || (ulCmd >= ISLTUEND))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_500);
        PPPC_INFO_LOG1("\r\nPpp_UsmIoCtl Input para error ulRPIndex %d!", ulRPIndex);
        return VOS_ERR;
    }

    switch ( ulCmd )
    {
        case PPP_ISLUP :
        {
            /*处理USM通知的底层链路建立OK消息、开始LCP协商*/;
            PPP_DBG_OK_CNT(PPP_PHOK_1172);
            ulRet = PPP_A11_IsLupProc(ulRPIndex, pPara);
            break;
        }
        case PPP_ISLDOWN :
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1173);
            /*处理USM通知的去活消息*/;
            ulRet = PPP_UsmIsLdownProc(ulRPIndex, (UCHAR *)pPara);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_501);
            PPPC_WARNING_LOG1("\r\nPpp_UsmIoCtl enter default branch %d!", ulCmd);
            ulRet = VOS_ERR;
            break;
        }
    }

    PPPC_INFO_LOG("\r\nPpp_UsmIoCtl success !");
    return ulRet;
}




VOS_UINT32 PPP_ModDomainInfoForCMIP(VOS_UINT32 ulRpIndex, VOS_UINT16 usDomainIdx)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    VOS_UINT32 ulvjModFlag = VOS_FALSE;
    VOS_UINT32 ulMppcModFlag = VOS_FALSE;
    VOS_UINT32 ulLzs0Flag = VOS_FALSE;
    VOS_UINT32 ulLzs1Flag = VOS_FALSE;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        /* 性能统计:无效协商报文数*/
        PPPC_INFO_LOG2(
                      "\r\n [ppp]PPP_ModDomainInfoForCMIP: User[%u] pppinfo isn't exist! domainindex[%u]",
                      ulRpIndex, usDomainIdx);
        PPP_DBG_ERR_CNT(PPP_PHERR_502);
        return VOS_ERR;
    }

    /* mode for DTS2012062600952 cmip用户支持压缩特性时需要将压缩用户数进行重新统计，
    此类型用户ipcp协商成功后的域不一定是用户真正所在的域*/
    if (pstPppInfo->usCDBIndex != usDomainIdx)
    {
        if (VOS_TRUE == pstPppInfo->bVjFlag)
        {
            PPP_CompUserNumDel( pstPppInfo, PPP_USERSTAT_VJ);
            ulvjModFlag = VOS_TRUE;
        }

        if (VOS_TRUE == pstPppInfo->bMppcFlag)
        {
            PPP_CompUserNumDel( pstPppInfo, PPP_USERSTAT_MPPC);
            ulMppcModFlag  = VOS_TRUE;
        }

        if (VOS_TRUE == pstPppInfo->bLzs0Flag)
        {
            PPP_CompUserNumDel( pstPppInfo, PPP_USERSTAT_ZLS0);
            ulLzs0Flag = VOS_TRUE;
        }

        if (VOS_TRUE == pstPppInfo->bLzs1Flag)
        {
            PPP_CompUserNumDel( pstPppInfo, PPP_USERSTAT_ZLS1);
            ulLzs1Flag = VOS_TRUE;
        }
    }

    pstPppInfo->usCDBIndex = usDomainIdx;
    pstPppInfo->usVirtualDomainIdx = usDomainIdx;

    if (VOS_TRUE == ulvjModFlag)
    {
        PPP_CompUserNumAdd( pstPppInfo, PPP_USERSTAT_VJ);
    }

    if (VOS_TRUE == ulMppcModFlag)
    {
        PPP_CompUserNumAdd( pstPppInfo, PPP_USERSTAT_MPPC);
    }

    if (VOS_TRUE == ulLzs0Flag)
    {
        PPP_CompUserNumAdd( pstPppInfo, PPP_USERSTAT_ZLS0);
    }

    if (VOS_TRUE == ulLzs1Flag)
    {
        PPP_CompUserNumAdd( pstPppInfo, PPP_USERSTAT_ZLS1);
    }

    /* 修改控制块中的内容，通知备份 */

    return VOS_OK;
}

VOS_UINT32 PPP_GetDomainInfoByName(PPPINFO_S *pstPppInfo, UCHAR* pucName)
{
    VOS_UINT32 ulRet = 0;
    VOS_UINT32 ulMapRet = 0;
    VOS_UINT16 usRealDomainIndex = 0;
    VOS_UINT16 usVirtualDomainIdx = 0;
    PPPCONFIGINFO_S *pstConfigInfo = pstPppInfo->pstConfigInfo;
    UCHAR szDomain[L2TP_DOMAINNAME_MAXLEN + 1];
    UCHAR szUserTemp[L2TP_USER_NAME_LEN + 1];
    UCHAR szUsername[A11_MAX_NAI_LENGTH + 1]; /* 用户名 */

    PPP_MemSet((void *)szUsername, 0, A11_MAX_NAI_LENGTH + 1);
    VOS_StrCpy((CHAR*)szUsername, (CHAR *)pucName);

    /* Modified start by l61463 at 2007-11-12 PDSNR5C2B018SP01 for 取消域名匹配用户名功能 */
    if(0 == (g_ulSoftPara562 & 0x01))
    {
        /* Modified start by lvyanfang 00110869 at 2009-10-24 PDSN V9R7C02SPC201 for 大写的用户名被PDSN该成小写问题 */
        usVirtualDomainIdx = (VOS_UINT16)GetDomainIndexByName(szUsername);

        if ((usVirtualDomainIdx > 0) && (usVirtualDomainIdx < RM_MAX_APN_NUM))
        {
            ulRet = (VOS_UINT32)A11_GetVirtualDomainStatusByIndex(usVirtualDomainIdx);
            if (VOS_OK == ulRet)
            {
                ulMapRet = (VOS_UINT32)A11_VirtualDomainMapping(usVirtualDomainIdx, pstPppInfo->stIMSI, &usRealDomainIndex);
                if (VOS_OK == ulMapRet)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1174);
                }
                else
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1175);
                    usRealDomainIndex = usVirtualDomainIdx;
                }
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1176);
                usRealDomainIndex = usVirtualDomainIdx;
            }
            pstPppInfo->usVirtualDomainIdx = usVirtualDomainIdx;
            pstPppInfo->usCDBIndex = usRealDomainIndex;
            VOS_StrCpy((CHAR *)pstConfigInfo->ucDomainName, (CHAR *)szUsername);
            return VOS_OK;
        }
    }

    PPP_MemSet((void *)szDomain, 0, sizeof(szDomain));
    PPP_MemSet((void *)szUserTemp, 0, sizeof(szUserTemp));

    if (L2TP_SeparateUserName((CHAR*)pucName, (CHAR*)szDomain, (CHAR*)szUserTemp))
    {
        usVirtualDomainIdx = (VOS_UINT16)GetDomainIndexByName(szDomain);

        if ((usVirtualDomainIdx > 0) && (usVirtualDomainIdx < RM_MAX_APN_NUM))
        {
            ulRet = (VOS_UINT32)A11_GetVirtualDomainStatusByIndex(usVirtualDomainIdx);
            if (VOS_OK == ulRet)
            {
                ulMapRet = (VOS_UINT32)A11_VirtualDomainMapping(usVirtualDomainIdx, pstPppInfo->stIMSI, &usRealDomainIndex);
                if (VOS_OK == ulMapRet)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1177);
                    PPPC_INFO_LOG2(
                                 "\r\n PPP_GetDomainInfoByName1: virtual_domain(%d)realdomain(%d)",
                                 usVirtualDomainIdx,
                                 usRealDomainIndex);
                }
                else
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1178);
                    usRealDomainIndex = usVirtualDomainIdx;
                }
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1179);
                usRealDomainIndex = usVirtualDomainIdx;
            }
            pstPppInfo->usVirtualDomainIdx = usVirtualDomainIdx;
            pstPppInfo->usCDBIndex = usRealDomainIndex;
            VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR *)pucName);
            PPPC_INFO_LOG2(
                         "\r\n PPP_GetDomainInfoByName1: usVirtualDomainIdx[%u] usCDBIndex[%u]",
                         pstPppInfo->usVirtualDomainIdx,
                         pstPppInfo->usCDBIndex);
        }
        else    /* 用户名无效或者该域名没有配置, 取缺省值 */
        {
            usVirtualDomainIdx = 0;
            if (VOS_TRUE == g_pstApnByIndex[0].ucVirtualApn)
            {
                ulMapRet = (VOS_UINT32)A11_VirtualDomainMapping(usVirtualDomainIdx, pstPppInfo->stIMSI, &usRealDomainIndex);
                if (VOS_OK == ulMapRet)
                {
                    PPPC_INFO_LOG2(
                                 "\r\n PPP_GetDomainInfoByName2: virtual_domain(%d)realdomain(%d)",
                                 usVirtualDomainIdx,
                                 usRealDomainIndex);
                    PPP_DBG_OK_CNT(PPP_PHOK_1180);
                }
                else
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_1181);
                    usRealDomainIndex = usVirtualDomainIdx;
                }
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1182);
                usRealDomainIndex = usVirtualDomainIdx;
            }
            pstPppInfo->usVirtualDomainIdx = usVirtualDomainIdx;
            pstPppInfo->usCDBIndex = usRealDomainIndex;
            VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR *)(g_pstApnByIndex[usRealDomainIndex].aucAPN));
            PPPC_INFO_LOG2(
                         "\r\n PPP_GetDomainInfoByName2: usVirtualDomainIdx[%u] usCDBIndex[%u]",
                         pstPppInfo->usVirtualDomainIdx,
                         pstPppInfo->usCDBIndex);
        }
    }
    else
    {
        usVirtualDomainIdx = 0;
        if (VOS_TRUE == g_pstApnByIndex[0].ucVirtualApn)
        {
            ulMapRet = (VOS_UINT32)A11_VirtualDomainMapping(usVirtualDomainIdx, pstPppInfo->stIMSI, &usRealDomainIndex);
            if (VOS_OK == ulMapRet)
            {
                PPPC_INFO_LOG2("\r\n PPP_GetDomainInfoByName3: virtual_domain(%d)realdomain(%d)",
                             usVirtualDomainIdx,
                             usRealDomainIndex);
                PPP_DBG_OK_CNT(PPP_PHOK_1183);
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1184);
                usRealDomainIndex = usVirtualDomainIdx;
            }
        }
        else
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1185);
            usRealDomainIndex = usVirtualDomainIdx;
        }
        pstPppInfo->usVirtualDomainIdx = usVirtualDomainIdx;
        pstPppInfo->usCDBIndex = usRealDomainIndex;
        VOS_StrCpy((CHAR*)pstConfigInfo->ucDomainName, (CHAR *)(g_pstApnByIndex[usRealDomainIndex].aucAPN));
        PPPC_INFO_LOG2(
                     "\r\n PPP_GetDomainInfoByName3: usVirtualDomainIdx[%u] usCDBIndex[%u]",
                     pstPppInfo->usVirtualDomainIdx,
                     pstPppInfo->usCDBIndex);
    }

    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2009-03-16                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     ：创建与鉴权相关的统计信息                                   *
* MODIFY DATE  ：modified by c00127007 for AP8D06810                        *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_OmInitial                                              *
****************************************************************************/
VOS_UINT32 PPP_OmAuthInitial()
{
    /* PAP认证尝试次数 */
    g_stPppPerfStatistic.ulPapTotal = 0;

    /* PAP认证成功次数 */
    g_stPppPerfStatistic.ulPapSuccess = 0;

    /* CHAP认证尝试次数 */
    g_stPppPerfStatistic.ulChapTotal = 0;

    /* CHAP认证成功次数 */
    g_stPppPerfStatistic.ulChapSuccess = 0;

    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2009-03-17                                                 *
* CREATED BY   ：c00127007                                                  *
* FUNCTION     ：创建与压缩相关的统计信息                                   *
* MODIFY DATE  ：modified by c00127007 for AP8D06810                        *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_OmInitial                                              *
****************************************************************************/
VOS_UINT32 PPP_OmCompInitial()
{
    return VOS_OK;
}

VOS_UINT32 PPP_OmInitial()
{
    VOS_UINT32 ulRet = VOS_OK;

    if ( VOS_TRUE == g_ulHsgwPppPerfInitOkFlg )
    {
        return VOS_OK;
    }

    /* BEGIN: Deleted for PN:切平台 by wangyong 00138171, 2012/9/26 */
    /* 注册性能统计 */
    /* 收到的协商报文数 */
    g_stPppPerfStatistic.ulReceiveNego = 0;

    /* 收到无效的报文数 */
    g_stPppPerfStatistic.ulReceiveNegoErr = 0;

    /* 发送的协商报文总数 */
    g_stPppPerfStatistic.ulSendNego = 0;

    /* LCP协商尝试次数 */
    g_stPppPerfStatistic.ulLcpTotal = 0;

    /* LCP协商成功次数 */
    g_stPppPerfStatistic.ulLcpSuccess = 0;

    /* IPCP协商尝试次数 */
    g_stPppPerfStatistic.ulIpcpTotal = 0;

    /* IPCP协商成功次数 */
    g_stPppPerfStatistic.ulIpcpSuccess = 0;

    /* PPP协商时间总和 */
    g_stPppPerfStatistic.ulPppNegoTotalTime = 0;
    /* PPP协商次数 */
    g_stPppPerfStatistic.ulPppNegoNum = 0;
    /* 平均PPP协商时间 */
    g_stPppPerfStatistic.ulPppNegoTime = 0;

    ulRet = PPP_OmAuthInitial();
    if (VOS_ERR == ulRet)
    {
        return VOS_ERR;
    }

    ulRet = PPP_OmCompInitial();
    if (VOS_ERR == ulRet)
    {
        return VOS_ERR;
    }

    /* CCP协商尝试次数 */
    g_stPppPerfStatistic.ulCcpTotal = 0;

    /* CCP协商成功次数 */
    g_stPppPerfStatistic.ulCcpSuccess = 0;


    /* BEGIN: Add by h50774 for 增加压缩用户数统计, 2010/7/17 */
    g_stPppPerfStatistic.ulCurVjUser = 0;

    g_stPppPerfStatistic.ulCurMppcUser = 0;

    g_stPppPerfStatistic.ulCurMppcVjUser = 0;

    g_stIpv6PerfStatistic.ulIpv6CpNegoAttempt   = 0;

    g_stIpv6PerfStatistic.ulIpv6CpNegoSucc      = 0;

    g_stIpv6PerfStatistic.ulMipIpv4v6UserActNum = 0;

    g_stIpv6PerfStatistic.ulSipIpv6UserActNum   = 0;

    /* HSGW 性能统计 */

    /* 内部调试全局变量初始化 */
    PPP_MemSet((VOID *)&g_stPppDebugImsi, 0, sizeof(IMSI_S));

    g_ulHsgwPppPerfInitOkFlg = VOS_TRUE;

    return VOS_OK;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsg_LCP
 *  初稿完成:  2009-02-25
 *  作    者:  c00127007
 *  函数功能:  LCP消息跟踪
 *  输入参数:  UCHAR uccode
 *             VOS_UINT32 *pulGiMsgType
 *             UCHAR ucflag
 *             VOS_UINT32 ulIndex
 *  输出参数:  无
 *  返回类型:  VOID
 *  其他说明:  在CONFREQ分支中, 删除 AM_PPP_ST_1 相关消息 for reduce CC
 *  调用函数:  PPP_OmMsgTrc
 *  主调函数:
 *=======================================================================*/
VOID PPP_OmMsg_LCP(UCHAR uccode, VOS_UINT32 *pulGiMsgType, UCHAR ucflag, VOS_UINT32 ulIndex)
{
    switch (uccode)
    {
        case VEDRSPEC:
            *pulGiMsgType = PPP_TRC_LCP_VERSION_CAP;
            break;
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_LCP_CONFREQ;
            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_LCP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_LCP_CONFNAK;
            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_LCP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_LCP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_LCP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_LCP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_LCP_PROTREJ;
            break;
        case ECHOREQ:
            *pulGiMsgType = PPP_TRC_LCP_ECHOREQ;
            break;
        case ECHOREP:
            *pulGiMsgType = PPP_TRC_LCP_ECHOREP;
            break;
        case IDENTIFIC:
            *pulGiMsgType = PPP_TRC_LCP_INDENTI;
            break;
        case DISCREQ:
            *pulGiMsgType = PPP_TRC_LCP_DISCREQ;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsg_IPV6CP
 *  初稿完成:  2010-02-28
 *  作    者:  yangxiangkun 00202564
 *  函数功能:  IPV6CP消息跟踪
 *  输入参数:  UCHAR uccode
 *             VOS_UINT32 *pulGiMsgType
 *             UCHAR ucflag
 *             VOS_UINT32 ulIndex
 *  输出参数:  无
 *  返回类型:  VOID
 *  其他说明:
 *  调用函数:  PPP_OmMsgTrc
 *  主调函数:
 *=======================================================================*/
VOID PPP_OmMsg_IPV6CP(UCHAR uccode, VOS_UINT32 *pulGiMsgType, UCHAR ucflag, VOS_UINT32 ulIndex)
{
    switch (uccode)
    {
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_IPV6CP_CONFREQ;
            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_IPV6CP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_IPV6CP_CONFNAK;
            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_IPV6CP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_IPV6CP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_IPV6CP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_IPV6CP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_IPV6CP_PROTREJ;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsg_IPCP
 *  初稿完成:  2009-02-25
 *  作    者:  c00127007
 *  函数功能:  IPCP消息跟踪
 *  输入参数:  UCHAR uccode
 *             VOS_UINT32 *pulGiMsgType
 *             UCHAR ucflag
 *             VOS_UINT32 ulIndex
 *  输出参数:  无
 *  返回类型:  VOID
 *  其他说明:
 *  调用函数:  PPP_OmMsgTrc
 *  主调函数:
 *=======================================================================*/
VOID PPP_OmMsg_IPCP(UCHAR uccode, VOS_UINT32 *pulGiMsgType, UCHAR ucflag, VOS_UINT32 ulIndex)
{
    switch (uccode)
    {
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_IPCP_CONFREQ;

            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_IPCP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_IPCP_CONFNAK;


            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_IPCP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_IPCP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_IPCP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_IPCP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_IPCP_PROTREJ;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsg_SCCP
 *  初稿完成:  2009-02-25
 *  作    者:  c00127007
 *  函数功能:  SCCP消息跟踪
 *  输入参数:  UCHAR uccode
               VOS_UINT32 *pulGiMsgType
 *  输出参数:  无
 *  返回类型:  VOID
 *  其他说明:
 *  调用函数:  PPP_OmMsgTrc
 *  主调函数:
 *=======================================================================*/
VOID PPP_OmMsg_SCCP(UCHAR uccode, VOS_UINT32 *pulGiMsgType)
{
    switch (uccode)
    {
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_SCP_CONFREQ;
            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_SCP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_SCP_CONFNAK;
            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_SCP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_SCP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_SCP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_SCP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_SCP_PROTREJ;
            break;
        case RESETREQ:
            *pulGiMsgType = PPP_TRC_SCP_RESETREQ;
            break;
        case RESETACK:
            *pulGiMsgType = PPP_TRC_SCP_RESETACK;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsg_PAP
 *  初稿完成:  2009-02-25
 *  作    者:  c00127007
 *  函数功能:  PAP消息跟踪
 *  输入参数:  UCHAR uccode
               VOS_UINT32 *pulGiMsgType
 *  输出参数:  无
 *  返回类型:  VOID
 *  其他说明:
 *  调用函数:  PPP_OmMsgTrc
 *  主调函数:
 *=======================================================================*/
VOID PPP_OmMsg_PAP(UCHAR uccode, VOS_UINT32 *pulGiMsgType)
{
    switch (uccode)
    {
        case PAP_AUTHREQ:
            *pulGiMsgType = PPP_TRC_PAP_AUTHREQ;
            break;
        case PAP_AUTHACK:
            *pulGiMsgType = PPP_TRC_PAP_AUTHACK;
            break;
        case PAP_AUTHNAK:
            *pulGiMsgType = PPP_TRC_PAP_AUTHNAK;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsg_CHAP
 *  初稿完成:  2009-02-25
 *  作    者:  c00127007
 *  函数功能:  CHAP消息跟踪
 *  输入参数:  UCHAR uccode
               VOS_UINT32 *pulGiMsgType
               VOS_UINT32 ulIndex
 *  输出参数:  无
 *  返回类型:  VOID
 *  其他说明:
 *  调用函数:  PPP_OmMsgTrc
 *  主调函数:
 *=======================================================================*/
VOID PPP_OmMsg_CHAP(UCHAR uccode, VOS_UINT32 *pulGiMsgType, VOS_UINT32 ulIndex)
{
    switch (uccode)
    {
        case CHAP_PACKET_CODE_CHALLENGE:
            *pulGiMsgType = PPP_TRC_CHAP_CHALLENGE;


            break;
        case CHAP_PACKET_CODE_RESPONSE:
            *pulGiMsgType = PPP_TRC_CHAP_RESPONSE;
            break;
        case CHAP_PACKET_CODE_FAILURE:
            *pulGiMsgType = PPP_TRC_CHAP_FAILURE;
            break;
        case CHAP_PACKET_CODE_SUCCESS:
            *pulGiMsgType = PPP_TRC_CHAP_SUCCSSS;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsg_EAP
 *  初稿完成:  2012-02-25
 *  作    者:  w00138171
 *  函数功能:  EAP消息跟踪
 *  输入参数:  UCHAR uccode
               VOS_UINT32 *pulGiMsgType
               VOS_UINT32 ulIndex
 *  输出参数:  无
 *  返回类型:  VOID
 *  其他说明:
 *  调用函数:  PPP_OmMsgTrc
 *  主调函数:
 *=======================================================================*/
VOID PPP_OmMsg_EAP(UCHAR uccode, VOS_UINT32 *pulGiMsgType)
{
    switch (uccode)
    {
        case EAP_PACKET_CODE_REQUEST:
            *pulGiMsgType = PPP_TRC_EAP_REQUEST;
            break;
        case EAP_PACKET_CODE_RESPONSE:
            *pulGiMsgType = PPP_TRC_EAP_RESPONSE;
            break;
        case EAP_PACKET_CODE_SUCCESS:
            *pulGiMsgType = PPP_TRC_EAP_SUCCSSS;
            break;
        case EAP_PACKET_CODE_FAILURE:
            *pulGiMsgType = PPP_TRC_EAP_FAILURE;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsg_VSNCP
 *  初稿完成:  2009-02-25
 *  作    者:  c00127007
 *  函数功能:  IPCP消息跟踪
 *  输入参数:  UCHAR uccode
 *             VOS_UINT32 *pulGiMsgType
 *             UCHAR ucflag
 *             VOS_UINT32 ulIndex
 *  输出参数:  无
 *  返回类型:  VOID
 *  其他说明:
 *  调用函数:  PPP_OmMsgTrc
 *  主调函数:
 *=======================================================================*/
VOID PPP_OmMsg_VSNCP(UCHAR uccode, VOS_UINT32 *pulGiMsgType)
{
    switch (uccode)
    {
        case CONFREQ:
            *pulGiMsgType = PPP_TRC_VSNCP_CONFREQ;
            break;
        case CONFACK:
            *pulGiMsgType = PPP_TRC_VSNCP_CONFACK;
            break;
        case CONFNAK:
            *pulGiMsgType = PPP_TRC_VSNCP_CONFNAK;
            break;
        case CONFREJ:
            *pulGiMsgType = PPP_TRC_VSNCP_CONFREJ;
            break;
        case TERMREQ:
            *pulGiMsgType = PPP_TRC_VSNCP_TERMREQ;
            break;
        case TERMACK:
            *pulGiMsgType = PPP_TRC_VSNCP_TERMACK;
            break;
        case CODEREJ:
            *pulGiMsgType = PPP_TRC_VSNCP_CODEREJ;
            break;
        case PROTREJ:
            *pulGiMsgType = PPP_TRC_VSNCP_PROTREJ;
            break;
        default:
            *pulGiMsgType = PPP_TRC_INVALIDPACKET;
            break;
    }

    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsgUserCheck
 *  初稿完成:  2009-03-16
 *  作    者:  c00127007
 *  函数功能:  Rp消息跟踪检查
 *  输入参数:  UCHAR ulCheckRpFlg
               VOS_UINT32 ulIndex
 *  输出参数:  VOS_UINT32 *pulIP
 *  返回类型:  VOID
 *  全局变量:
 *  其他说明:
 *  调用函数:
 *  主调函数: PPP_OmMsgTrc
 *=======================================================================*/
VOS_UINT32 PPP_OmMsgUserCheck(UCHAR ulCheckRpFlg, VOS_UINT32 ulIndex, VOS_UINT32 *pulIP)
{
    VOS_UINT32 ulResult = VOS_ERR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    SDB_PDSN_RP_CONTEXT_S* pstRpContext = VOS_NULL_PTR;

    PPPC_INFO_LOG("\r\n PPP_OmMsgUserCheck: Rp or Gn message trace.");

    if (VOS_TRUE == ulCheckRpFlg)
    {
        ulResult = (VOS_UINT32)SDB_GetRpContextByIndex(ulIndex, (VOS_VOID **)&pstRpContext);
        if ((VOS_OK != ulResult) || (VOS_NULL_PTR == pstRpContext))
        {
            PPPC_INFO_LOG("\r\n PPP_OmMsgUserCheck: Get PcfIP failed.");
            PPP_DBG_ERR_CNT(PPP_PHERR_503);

            return VOS_ERR;
        }

        *pulIP = pstRpContext->ulPcfIP;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_504);
        PPPC_INFO_LOG("\r\n PPP_OmMsgUserCheck: Rp or Gn message trace pstPppInfo is VOS_NULL_PTR.");
        return VOS_ERR;
    }

    /* BEGIN: Added by longsirui 41291, 2008/3/1   问题单号:AX4D00767 */
    /*客户端模式ppp不会有GN口跟踪*/
    if (1 == pstPppInfo->bPppClient)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_505);
        PPPC_INFO_LOG1(
                     "\r\n PPP_OmMsgUserCheck: Client mode have no Rp or Gn message trace.bPppClient = %d",
                     pstPppInfo->bPppClient);
        return VOS_ERR;
    }


    if (VOS_FALSE == ulCheckRpFlg)
    {
        *pulIP = pstPppInfo->ulPeerIPAddr;
    }

    return VOS_OK;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsgRpTrc
 *  初稿完成:  2009-03-16
 *  作    者:  c00127007
 *  函数功能:  Rp接口跟踪
 *  输入参数:  VOS_UINT32 ulIndex
               VOS_UINT32 ulGiMsgType
               VOS_UINT32 ulLen
               UCHAR *pMsg
 *  输出参数:  无
 *  返回类型:  VOID
 *  全局变量:
 *  其他说明:
 *  调用函数:
 *  主调函数: PPP_OmMsgTrc
 *=======================================================================*/
VOID PPP_OmMsgRpTrc(VOS_UINT32 ulIndex, VOS_UINT32 ulGiMsgType, VOS_UINT32 ulLen, UCHAR *pMsg, IMSI_S *pstImsi)
{

    VOS_UINT32 ulPcfIP = 0;
    VOS_UINT32 ulRet = VOS_OK;
    A11_S_IFTRC_FILTER stRpIfFilter;  /* PR跟踪消息 */
    VOS_UINT32 ulTreLen = 0;

    /* 软参bit1408打开, 软参flag+protocol+imsilen+imsi */
    ulTreLen = ulLen + 2+1;

    PPP_MemSet((void *)&stRpIfFilter, 0, sizeof(A11_S_IFTRC_FILTER));

    if ((VOS_TRUE == Trc_IsTraceTaskEnabled((VOS_UINT8)TRC_TYPE_RPCSN)) && (ulIndex != 0))
    {
        ulRet = PPP_OmMsgUserCheck(VOS_TRUE, ulIndex, &ulPcfIP);
        if (VOS_ERR == ulRet)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_506);
            return;
        }

        /* 填充过滤参数 */
        stRpIfFilter.ulMsgType = RP_MSGTYPE_PPP;
        stRpIfFilter.ulLogicIp = g_ulA11RpifIp;
        stRpIfFilter.ulPeerIp = ulPcfIP;

    }

    (VOS_VOID)ulTreLen;
    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsgUserTrc
 *  初稿完成:  2009-03-16
 *  作    者:  c00127007
 *  函数功能:  用户跟踪
 *  输入参数:  IMSI_S *pstImsi
               VOS_UINT32 ulGiMsgType
               VOS_UINT32 ulLen
               UCHAR *pMsg
 *  输出参数:  无
 *  返回类型:  VOID
 *  全局变量:
 *  其他说明:
 *  调用函数:
 *  主调函数: PPP_OmMsgTrc
 *=======================================================================*/
VOID PPP_OmMsgUserTrc(IMSI_S *pstImsi, VOS_UINT32 ulGiMsgType, VOS_UINT32 ulLen, UCHAR *pMsg)
{

    IMSI_S stImsiTemp;
    UCHAR aucImsiTemp[M_IMSI_LEN];
    /* S_FAM_BAM_TRC_TIME_DATA stTrcTime = {0};
    VOS_UINT32 ulMillSecs = 0; */
    A11_S_USERTRC_FILTER stUserFilter;  /* PDSN用户跟踪 */

    if (VOS_NULL_PTR == pstImsi)
    {
        return ;
    }

    PPP_MemSet((void *)&stImsiTemp, 0, sizeof(IMSI_S));
    PPP_MemSet((void *)aucImsiTemp, 0,  M_IMSI_LEN);

    PPP_MemSet((void *)&stUserFilter, 0, sizeof(A11_S_USERTRC_FILTER));
    VOS_MemCpy((VOID *)&stImsiTemp, (VOID *)pstImsi, sizeof(IMSI_S));

#if 0
    if (VOS_TRUE == A11_CheckIsEnableUserTrce(stImsiTemp))
    {
        /* 填充消息类型 */
        stUserFilter.ulMsgType = PUSER_MSGTYPE_PPP;

        ImsiToString(stImsiTemp, aucImsiTemp);
        (VOID)VOS_MemCpy(stUserFilter.aucImsi, aucImsiTemp, IMSI_ASCII_LEN);

        if (VOS_OK != VOS_TmGet(&(stTrcTime.stDate), &(stTrcTime.stTime), &ulMillSecs))
        {
            PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_INFO,"\r\n VOS_TmGet failed.");
        }

        stTrcTime.ulTick = (VOS_UINT32)PGP_getTimeByTicksInMisc();

        /* 调用跟踪接口函数 */
        FamTrcSendTrcMsgWithTime(TRC_TYPE_PDSN_USER,
                         (VOS_UINT8 *)&stUserFilter,
                         ulGiMsgType + ((VOS_UINT32)PUSER_MSGTYPE_PPP << 24),
                         (VOS_UINT16)(ulLen + 3),
                         pMsg,
                         stTrcTime);
    }
#endif
    return;
}

/*=======================================================================
 *  函数名称:  PPP_OmMsgTrc
 *  初稿完成:  2003年7月
 *  作    者:  KF1199 heyajun
 *  函数功能:  消息跟踪
 *  输入参数:  pstPppInfo       控制块指针
 *             usProtocol       协议类型
 *             pMsg             被跟踪的消息指针
 *             usMsgLen         消息长度
 *  输出参数:  无
 *  返回类型:  VOID
 *  全局变量:  g_struTrcTraceFlag  接口跟踪标志
 *  其他说明:
 *  调用函数:  FamTrcSendTrcMsg
 *  主调函数:
 *=======================================================================*/
VOID PPP_OmMsgTrc(VOS_UINT32 ulIndex, VOS_UINT16 usProtocol, UCHAR* pPacket, VOS_UINT32 ulLen, UCHAR ucflag, VOS_UINT32 ulLnsIP,
                  IMSI_S *pstImsi, UCHAR ucEhrpdMode)
{

    VOS_UINT32 ulGiMsgType = 0;        /* 跟踪消息类型 */
    UCHAR uccode = 0;             /* 报文类型*/
    UCHAR pTraceMsg[1024] = {0};
    UCHAR *pMsg = VOS_NULL_PTR;

    if (ulLen >= (1024 - sizeof(VOS_UINT16) - sizeof(UCHAR)))
    {
        ulLen = 1024 - sizeof(VOS_UINT16) - sizeof(UCHAR);
    }

    /* 获取协议包类型 */
    uccode = *pPacket;

    /* 判断跟踪消息类型 */
    switch (usProtocol)
    {
        case PPP_LCP:

            PPP_OmMsg_LCP(uccode, &ulGiMsgType, ucflag, ulIndex);
            break;

        case PPP_IPCP:

            PPP_OmMsg_IPCP(uccode, &ulGiMsgType, ucflag, ulIndex);
            break;

        /* BEGIN: Added for  IPV6CP消息跟踪 by yangxiangkun 00202564, 2012/02/28 */
        case PPP_IPV6CP:

            PPP_OmMsg_IPV6CP(uccode, &ulGiMsgType, ucflag, ulIndex);
            break;
        /* END:   Added for IPV6CP消息跟踪 by yangxiangkun 00202564, 2012/02/28 */
        case PPP_SCCP:

            PPP_OmMsg_SCCP(uccode, &ulGiMsgType);
            break;

        case PPP_PAP:

            PPP_OmMsg_PAP(uccode, &ulGiMsgType);
            break;
        case PPP_EAP:
            PPP_OmMsg_EAP(uccode, &ulGiMsgType);
            break;
        case PPP_VSNCP:
            PPP_OmMsg_VSNCP(uccode, &ulGiMsgType);
            break;
        case PPP_CHAP:

            PPP_OmMsg_CHAP(uccode, &ulGiMsgType, ulIndex);
            break;
        case PPP_SCP:
            return;
        default:
            ulGiMsgType = PPP_TRC_INVALIDPACKET;
            PPPC_INFO_LOG1("\r\n PPP_OmMsgTrc:  invalid msg type ulMsgType = %d!", ulGiMsgType);
            (VOS_VOID)ulGiMsgType;
            return;
    }

    if (PPP_TRACE_OUT == ucflag)
    {
        ulGiMsgType += 256;
    }
    if (VOS_TRUE == ucEhrpdMode)
    {
        ulGiMsgType += 0x00001000;
    }

    pMsg = pTraceMsg;
    PPP_PUTCHAR(0,pMsg);
    PPP_PUTSHORT(usProtocol, pMsg);
    VOS_MemCpy((VOID*)pMsg, (VOID*)pPacket, ulLen);
    pMsg -= 3;

    /* 用户跟踪 */
    PPP_OmMsgUserTrc(pstImsi, ulGiMsgType, ulLen, pMsg);

    /* Rp接口跟踪 */
    PPP_OmMsgRpTrc(ulIndex, ulGiMsgType, ulLen, pMsg, pstImsi);
    return;
}

/*=======================================================================
 *  函数名称:  PPP_IpcCallback
 *  初稿完成:  2003年7月
 *  作    者:  KF1199 heyajun
 *  函数功能:  IPC消息回调函数
 *  输入参数:
 *  输出参数:  无
 *  返回类型:  VOID
 *  全局变量:
 *  其他说明:
 *  调用函数:
 *  主调函数:
 *=======================================================================*/
VOS_UINT32 PPP_NodeAdd(VOS_UINT32 ulRpIndex, VOS_UINT32 ulPDNIndex, UCHAR ucNodeType)
{
    PPP_NEGO_NODE_S* pNode;
/*    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    VOS_UINT32 ulReturn = 0; */

    /* BEGIN: Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */
    (VOID)PPP_NodeDelete(ulRpIndex);
    /* END:   Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */
    /* modified by luofang  切平台 20120925 */
    pNode = (PPP_NEGO_NODE_S*)PPP_Malloc(sizeof(PPP_NEGO_NODE_S));
    if (!pNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_507);
        /* 内存申请失败,返回失败 */
        PPPC_INFO_LOG1("\r\n PPP_NodeAdd: PPP_Malloc failed for user %u", ulRpIndex);
        return VOS_ERR;
    }
    VOS_MemSet(pNode, 0, (sizeof(PPP_NEGO_NODE_S)));
    pNode->ulRpIndex = ulRpIndex;
    pNode->ucNodeType = ucNodeType;
    if (PPP_NEGO_LIST_NODE_LCP_START == pNode->ucNodeType)
    {
        pNode->ucCounter = 12;/*g34667:D00850*/
    }
    else
    {
        pNode->ucCounter = 6;/*g34667:D00850*/
    }
    pNode->pNext = g_pstPppNegoList;  /* 挂到队列头 */
    g_pstPppNegoList = pNode;
    PPP_DBG_OK_CNT(PPP_PHOK_1468);

    /* check with liukai */
#if 0
    /* BEGIN: Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */
    ulReturn = (VOS_UINT32)SDB_GetRpContextByIndex(ulRpIndex, (UCHAR **)&pstRpContext);
    if (VOS_OK != ulReturn)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_770);
        return VOS_OK;
    }

    if (pstRpContext->beHRPDMode)
    {
        for (i = 0; i < A11_MAX_PDN_NUM; i++)
        {
            if (pstRpContext->ausPdnIndexArray[i] != 0)
            {
                (VOID)PPP_PDNNodeDelete((VOS_UINT32)pstRpContext->ausPdnIndexArray[i]);
            }
        }
    }
    /* END:   Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */
#endif
    return VOS_OK;
}

VOS_UINT32 PPP_NodeDelete(VOS_UINT32 ulRpIndex)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;

    while (pstNode)
    {
        if (pstNode->ulRpIndex == ulRpIndex)
        {
            if (VOS_NULL_PTR == pstPreNode)
            {
                g_pstPppNegoList = pstNode->pNext;
            }
            else
            {
                pstPreNode->pNext = pstNode->pNext;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1469);

            (VOID)PPP_Free(pstNode);
            return VOS_OK;
        }

        pstPreNode = pstNode;
        pstNode = pstNode->pNext;
    }

    return VOS_ERR;
}

VOID PPP_NegoListProc(VOID* pPara)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    /*lint -e746*/
    PPP_CompRescSyn();
    /*lint +e746*/

    (VOID)PPP_OmInitial();

    ulOneSecondTimer++;

    /* 三秒上报一次PPP告警 */
    if (0 == ulOneSecondTimer % 3)
    {
        PPP_A11_AlarmProc();
    }

    if(0 == ulOneSecondTimer % 10)
    {
        while (pstNode)
        {
            pstNode->ucCounter--;

            if (pstNode->ucCounter == 0)
            {
                VOS_UINT32 ulIndex = pstNode->ulRpIndex;
                VOS_UINT32 ucNodeType = pstNode->ucNodeType;

                /* 删除节点, 修改链表 */
                if (VOS_NULL_PTR == pstPreNode)
                {
                    g_pstPppNegoList = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = g_pstPppNegoList;
                }
                else
                {
                    pstPreNode->pNext = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = pstPreNode->pNext;
                }

                /* 通知协商结束。若用户协商失败，控制块已经删除, 不用再通知 */
                if (PPP_CB_STATE_USED == g_astPppPool[ulIndex].usState)
                {
                    PPPC_INFO_LOG1("\r\n PPP nego timeout delete user %u", ulIndex);

                    GETPPPINFOPTRBYRP(pstPppInfo, ulIndex);
                    if ((VOS_NULL_PTR == pstPppInfo)
                        || (VOS_NULL_PTR == pstPppInfo->pstLcpInfo))
                    {
                        continue;
                    }
                    if (PPP_NEGO_LIST_NODE_LCP_START == ucNodeType)
                    {
                        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_14);
                        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_TOTAL_TIMEOUT);
                        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
                        //(VOID)PPP_Shell_ISLIoCtl(ulIndex, PPP_ISLDOWN, VOS_NULL_PTR);
                        /*End of liushuang*/
                        A11_PPP_TermTag(ulIndex, PPP_Negotiation_Fail);
                        PPP_DBG_ERR_CNT(PPP_PHERR_508);
                    }
                    else
                    {
                        PPP_DBG_ERR_CNT(PPP_PHERR_771);
                        (VOID)PPP_DeleteCB(pstPppInfo, PS_TRUE);

                        PPPC_DeletePppId((VOS_UINT8)pstPppInfo->ulRPIndex);
                    }
                }
            }
            else
            {
                pstPreNode = pstNode;
                pstNode = pstNode->pNext;
            }
        }
    }
    /* BEGIN: Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/23 */
    PPP_PDNNegoListProc(pPara);
    PPP_RPNegoListProc(pPara);
    /* END:   Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/23 */
}


/* BEGIN: Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */

/*=======================================================================
 *  函数名称:  PPP_IpcCallback
 *  初稿完成:  2003年7月
 *  作    者:  KF1199 heyajun
 *  函数功能:  IPC消息回调函数
 *  输入参数:
 *  输出参数:  无
 *  返回类型:  VOID
 *  全局变量:
 *  其他说明:
 *  调用函数:
 *  主调函数:
 *=======================================================================*/
VOS_UINT32 PPP_PDNNodeAdd(VOS_UINT32 ulRpIndex, VOS_UINT32 ulPDNIndex, UCHAR ucNodeType)
{
    PPP_NEGO_NODE_S* pNode = VOS_NULL_PTR;

    (VOID)PPP_PDNNodeDelete(ulPDNIndex);

    pNode = (PPP_NEGO_NODE_S*)PPP_Malloc(sizeof(PPP_NEGO_NODE_S));
    if (!pNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_767);
        /* 内存申请失败,返回失败 */
        PPPC_INFO_LOG1("\r\n PPP_PDNNodeAdd: PPP_Malloc failed for user %u", ulRpIndex);
        return VOS_ERR;
    }
    VOS_MemSet(pNode, 0, (sizeof(PPP_NEGO_NODE_S)));

    pNode->ulRpIndex = ulRpIndex;
    pNode->ulPDNIndex = ulPDNIndex;
    pNode->ucNodeType = ucNodeType;
    pNode->ucCounter = 30;     /* 2s一个刻度，总共60s */
    pNode->pNext = g_pstPppPDNNegoList;  /* 挂到队列头 */
    g_pstPppPDNNegoList = pNode;

    PPP_DBG_OK_CNT(PPP_PHOK_1466);
    return VOS_OK;
}

VOS_UINT32 PPP_PDNNodeDelete(VOS_UINT32 ulPDNIndex)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppPDNNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;

    while (pstNode)
    {
        if (pstNode->ulPDNIndex == ulPDNIndex)
        {
            if (VOS_NULL_PTR == pstPreNode)
            {
                g_pstPppPDNNegoList = pstNode->pNext;
            }
            else
            {
                pstPreNode->pNext = pstNode->pNext;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1467);

            (VOID)PPP_Free(pstNode);
            return VOS_OK;
        }

        pstPreNode = pstNode;
        pstNode = pstNode->pNext;
    }

    return VOS_ERR;
}

VOID PPP_PDNNegoListProc(VOID* pPara)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppPDNNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    VOS_UINT32 ulPDNIndex = 0;
    VOS_UINT32 ulRpIndex = 0;
    VOS_UINT32 ulRet = 0;

    if(0 == ulOneSecondTimer % 2)
    {
        while (pstNode)
        {
            pstNode->ucCounter--;

            if (pstNode->ucCounter == 0)
            {
                ulPDNIndex = pstNode->ulPDNIndex;
                ulRpIndex = pstNode->ulRpIndex;

                /* 删除节点, 修改链表 */
                if (VOS_NULL_PTR == pstPreNode)
                {
                    g_pstPppPDNNegoList = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = g_pstPppPDNNegoList;
                }
                else
                {
                    pstPreNode->pNext = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = pstPreNode->pNext;
                }

                /* 获取PPPC控制块指针*/
                GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
                if (VOS_NULL_PTR == pstPppInfo)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_768);
                    continue;
                }
                ulRet = SDB_GetPdnContextByIndex(ulPDNIndex, (VOS_VOID **)&pstPDNContext);
                if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_769);
                    continue;
                }

                PPP_DBG_ERR_CNT(PPP_PHERR_775);
                /* 初始化VSNCP控制块 */
                PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, pstPDNContext->stEhrpd.ucPdnId);
                stVSNCPInfo.ulPDNRleaseCode = AM_RELCODE_PDN_HSGW_IDLETIMEOUT;
                /* 通知PDN去活 */
                PPP_CORE_VSNCPFinishProc(pstPppInfo);
                /* vsncp状态机处理完毕后刷新pdn上下文中的状态信息 */
                PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

            }
            else
            {
                pstPreNode = pstNode;
                pstNode = pstNode->pNext;
            }
        }
    }

}


/*=======================================================================
 *  函数名称:  PPP_RPNodeAdd
 *  初稿完成:  2003年7月
 *  作    者:  KF1199 heyajun
 *  函数功能:  IPC消息回调函数
 *  输入参数:
 *  输出参数:  无
 *  返回类型:  VOID
 *  全局变量:
 *  其他说明:
 *  调用函数:
 *  主调函数:
 *=======================================================================*/
VOS_UINT32 PPP_RPNodeAdd(VOS_UINT32 ulRpIndex, VOS_UINT32 ulReleaseCode, UCHAR ucNodeType)
{
    PPP_NEGO_NODE_S* pNode = VOS_NULL_PTR;

    (VOID)PPP_RPNodeDelete(ulRpIndex);

    pNode = (PPP_NEGO_NODE_S*)PPP_Malloc(sizeof(PPP_NEGO_NODE_S));
    if (!pNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_776);
        /* 内存申请失败,返回失败 */
        PPPC_INFO_LOG1("\r\n PPP_RPNodeAdd: PPP_Malloc failed for user %u",
                     ulRpIndex);
        return VOS_ERR;
    }
    VOS_MemSet(pNode, 0, (sizeof(PPP_NEGO_NODE_S)));

    pNode->ulRpIndex = ulRpIndex;
    pNode->ulPDNIndex = ulReleaseCode;  /* 使用此字段保存release code */
    pNode->ucNodeType = ucNodeType;
    pNode->ucCounter = 60;     /* 2s一个刻度，总共60s */
    pNode->pNext = g_pstPppRPNegoList;  /* 挂到队列头 */
    g_pstPppRPNegoList = pNode;

    PPP_DBG_OK_CNT(PPP_PHOK_1473);
    return VOS_OK;
}

VOS_UINT32 PPP_RPNodeDelete(VOS_UINT32 ulRPIndex)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppRPNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;

    while (pstNode)
    {
        if (pstNode->ulRpIndex == ulRPIndex)
        {
            if (VOS_NULL_PTR == pstPreNode)
            {
                g_pstPppRPNegoList = pstNode->pNext;
            }
            else
            {
                pstPreNode->pNext = pstNode->pNext;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1474);

            (VOID)PPP_Free(pstNode);
            return VOS_OK;
        }

        pstPreNode = pstNode;
        pstNode = pstNode->pNext;
    }

    return VOS_ERR;
}

VOID PPP_RPNegoListProc(VOID* pPara)
{
    PPP_NEGO_NODE_S* pstNode = g_pstPppRPNegoList;
    PPP_NEGO_NODE_S* pstPreNode = VOS_NULL_PTR;
    VOS_UINT32 ulRpIndex = 0;
    VOS_UINT32 ulReleaseCode = 0;

    if(0 == ulOneSecondTimer % 2)
    {
        while (pstNode)
        {
            pstNode->ucCounter--;

            if (pstNode->ucCounter == 0)
            {
                ulRpIndex = pstNode->ulRpIndex;
                ulReleaseCode = pstNode->ulPDNIndex;
                /* 删除节点, 修改链表 */
                if (VOS_NULL_PTR == pstPreNode)
                {
                    g_pstPppRPNegoList = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = g_pstPppRPNegoList;
                }
                else
                {
                    pstPreNode->pNext = pstNode->pNext;
                    (VOID)PPP_Free(pstNode);
                    pstNode = pstPreNode->pNext;
                }

                (VOID)USM_NotifyReleaseUserFunc(ulRpIndex, ulReleaseCode, VOS_NULL_PTR);

                PPP_DBG_ERR_CNT(PPP_PHERR_777);
            }
            else
            {
                pstPreNode = pstNode;
                pstNode = pstNode->pNext;
            }
        }
    }

}

/* END:   Added for PN:解决ppp协商定时器资源挂死问题 by wangyong 00138171, 2013/12/21 */


/************************************************************
函数名:     PPPGetPPPConfig
描述:       CDB中得到ppp的配置
调用:       CDB核心函数
被调用:
输入:
输出:
返回:       PPP_OK,PPP_ERROR
其他:
 **************************************************************/
VOID PPPGetPPPConfig(VOID)
{
    PPP_CFG_INFO_REC_S stPppCfgRec;

    (VOID)VOS_MemSet(&stPppCfgRec, 0, sizeof(stPppCfgRec));     /* 初始化PPP_CFG_INFO_REC_S */

    g_stPppCfgInfo.ucAuthmod = PPPCFG_AUTHMODE_NONE; /*mod by chenmin 00265046,控制是否主动鉴权的参数,不主动鉴权时设置为PPPCFG_AUTHMODE_NONE,chap鉴权时手机被动接受鉴权,要设置为none*/
    VOS_StrCpy((CHAR*)g_stPppCfgInfo.aucHostname, PPPCFG_HOSTNAME_DEFAULT_PDSN);
    g_stPppCfgInfo.usMru = PPP_GetDefaultMru();      /* mod by w00316385, 使用默认的MRU，从NV项中读取 */
    g_stPppCfgInfo.ucTimeout = PPPCFG_TIMEOUT_DEFAULT;
    g_stPppCfgInfo.ucAuthoption = PPPCFG_AUTHOPTION_DEFAULT;
    g_stPppCfgInfo.ucIpv6Flag = 1;
    g_stPppCfgInfo.ucVSNCPFlag = (PPP_VSNCP_APN_AMBR_FLAG | PPP_VSNCP_DEFUALT_APN_INDICATIOR_FLAG);

    return;
}

/************************************************************
函数名:            CDB_PppCfgModNotify
描述:              ppp 配置改变时notify函数
调用:               CDB核心函数
被调用:            CDB 回调
输入:
输出:
返回:               无
其他:
 **************************************************************/
VOID CDB_PppCfgModNotify( CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*     pNewValue, UCHAR*     pOldValue)
{
    /*如果参数非法*/
    if ((M_OS_PPPCFG_TBL_ID != nTbl) || (VOS_NULL_PTR == pNewValue) || (VOS_NULL_PTR == pOldValue))
    {
        PPPC_INFO_LOG("CDB_PppCfgModNotify: ERROR INPUT PARA");
        return;
    }

    g_stPppCfgInfo.ucAuthmod = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucAuthmod;
    VOS_StrCpy((CHAR *) (g_stPppCfgInfo.aucHostname), (CHAR *)((PPP_CFG_INFO_REC_S*)pNewValue)->aucHostname);
    g_stPppCfgInfo.usMru = ((PPP_CFG_INFO_REC_S*)pNewValue)->usMru;
    g_stPppCfgInfo.ucTimeout = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucTimeout;
    g_stPppCfgInfo.ucAuthoption = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucAuthoption;
    g_stPppCfgInfo.ucIpv6Flag = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucIpv6Flag;
    g_stPppCfgInfo.ucVSNCPFlag = ((PPP_CFG_INFO_REC_S*)pNewValue)->ucVSNCPFlag;
    return;
}

/************************************************************
函数名:     CDB_PppCfgAddNotify
描述:           ppp 配置改变时notify函数
调用:           CDB核心函数
被调用:      CDB 回调
输入:
输出:
返回:           无
其他:
 **************************************************************/
VOID CDB_PppCfgAddNotify(      CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*    pValue)
{
    /*如果参数非法*/
    if ((M_OS_PPPCFG_TBL_ID != nTbl) || (VOS_NULL_PTR == pValue))
    {
        PPPC_INFO_LOG("CDB_PppCfgAddNotify: ERROR INPUT PARA");
        return;
    }

    g_stPppCfgInfo.ucAuthmod = ((PPP_CFG_INFO_REC_S*)pValue)->ucAuthmod;
    VOS_StrCpy((CHAR *) (g_stPppCfgInfo.aucHostname), (CHAR *)(((PPP_CFG_INFO_REC_S*)pValue)->aucHostname));
    g_stPppCfgInfo.usMru = ((PPP_CFG_INFO_REC_S*)pValue)->usMru;
    g_stPppCfgInfo.ucTimeout = ((PPP_CFG_INFO_REC_S*)pValue)->ucTimeout;
    g_stPppCfgInfo.ucAuthoption = ((PPP_CFG_INFO_REC_S*)pValue)->ucAuthoption;
    g_stPppCfgInfo.ucIpv6Flag = ((PPP_CFG_INFO_REC_S*)pValue)->ucIpv6Flag;
    g_stPppCfgInfo.ucVSNCPFlag = ((PPP_CFG_INFO_REC_S*)pValue)->ucVSNCPFlag;

    return;
}

/************************************************************
函数名:     CDB_PppCompressGetGlobalVar
描述:       给压缩全局变量置值
调用:
被调用:
输入:
输出:
返回:       PPP_OK,PPP_ERROR
其他:
 **************************************************************/

VOID CDB_PppCompressGetGlobalVar(PPP_COMPRESS_CFG *pstCompCfg)
{
   if (pstCompCfg->ucCompressFlag & M_PPPCOMPRESS_VJ_FLAG)
   {
       g_ucPppVjSwitch = 1;
   }
   else
   {
       g_ucPppVjSwitch = 0;

       /* Modified start by liutao 38563 at 2004-10-29 V800R002 for PPPC移植 */
   }

   g_ucPppCcpSwitch = 0;
   if (pstCompCfg->ucCompressFlag & M_PPPCOMPRESS_MPPC_FLAG)
   {
       g_ucPppCcpSwitch = 1;
       g_ucPppCcpType |= M_PPPCOMPRESS_MPPC_FLAG;
   }
   else
   {
       g_ucPppCcpType &= ~M_PPPCOMPRESS_MPPC_FLAG;
   }

   if (pstCompCfg->ucCompressFlag & M_PPPCOMPRESS_STAC_FLAG)
   {
       g_ucPppCcpSwitch = 1;
       g_ucPppCcpType |= M_PPPCOMPRESS_STAC_FLAG;
   }
   else
   {
       g_ucPppCcpType &= ~M_PPPCOMPRESS_STAC_FLAG;
   }
}

VOS_UINT32 DBApiQuerySingle(CDB_TBLID nTableId,
                            VOS_INT32 dwCondNum,
                            S_CFG_CDB_CONDITION *pCond,
                            VOS_INT8 *pTuple)
{
    return 0;
}

/************************************************************
函数名:     PPPGetCompressConfig
描述:       CDB中得到压缩的配置
调用:       CDB核心函数
被调用:
输入:
输出:
返回:       PPP_OK,PPP_ERROR
其他:
 **************************************************************/
VOID PPPGetCompressConfig(VOID)
{
    VOS_UINT32 ulRetCode = M_CFG_DB_API_DBERROR;
    S_CFG_CDB_CONDITION stCdbCon[2];
    PPP_COMPRESS_CFG stCompCfg = { 0 };
    UCHAR ucGroupId  = 0;
    UCHAR ucInstanceId = 0;


    ucGroupId = (UCHAR)CRM_GetSelfGroupId();
    ucInstanceId = (UCHAR)GTP_INST_GETINSTNO(INST_GetSelfInstanceId());

    stCdbCon[0].ucOper = M_CFG_CDB_EQUAL;
    stCdbCon[0].udwFieldId = M_OS_PPPCOMPRESS_FLD_GROUPNUMBER;
    *(UCHAR*)stCdbCon[0].aValue = (UCHAR)ucGroupId;


    stCdbCon[1].ucOper = M_CFG_CDB_EQUAL;
    stCdbCon[1].udwFieldId = M_OS_PPPCOMPRESS_FLD_INSTANCEID;
    *(UCHAR*)stCdbCon[1].aValue = (UCHAR)ucInstanceId;

    ulRetCode = DBApiQuerySingle(M_OS_PPPCOMPRESS_TBL_ID,
                                2,
                                stCdbCon,
                                (VOS_INT8 *)(&stCompCfg));

    if (M_CFG_DB_API_SUCCESS == ulRetCode)
    {
        CDB_PppCompressGetGlobalVar(&stCompCfg);
        return;
    }

    stCdbCon[0].ucOper = M_CFG_CDB_EQUAL;
    stCdbCon[0].udwFieldId = M_OS_PPPCOMPRESS_FLD_GROUPNUMBER;
    *(UCHAR*)stCdbCon[0].aValue = (UCHAR)ucGroupId;

    stCdbCon[1].ucOper = M_CFG_CDB_EQUAL;
    stCdbCon[1].udwFieldId = M_OS_PPPCOMPRESS_FLD_INSTANCEID;
    *(UCHAR*)stCdbCon[1].aValue = 0;

    ulRetCode = DBApiQuerySingle(M_OS_PPPCOMPRESS_TBL_ID,
                                2,
                                stCdbCon,
                                (VOS_INT8 *)(&stCompCfg));

    if (M_CFG_DB_API_SUCCESS == ulRetCode)
    {
        CDB_PppCompressGetGlobalVar(&stCompCfg);
        return;
    }

    g_ucPppVjSwitch  = 0;
    g_ucPppCcpSwitch = 0;

    return;
}

/************************************************************
函数名:            CDB_PppCompressCfgModNotify
描述:              compress配置改变时notify函数
调用:              CDB核心函数
被调用:            CDB 回调
输入:
输出:
返回:               无
其他:
 **************************************************************/
VOID CDB_PppCompressCfgModNotify(CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR* pNewValue, UCHAR* pOldValue)
{
    UCHAR ucGroupId  = 0;
    UCHAR ucInstanceId = 0;
    PPP_COMPRESS_CFG *pstCompCfg = VOS_NULL;


    PPPC_INFO_LOG("CDB_PppCompressCfgModNotify: ENTER");

    /*如果参数非法*/
    if ((M_OS_PPPCOMPRESS_TBL_ID != nTbl) || (VOS_NULL_PTR == pNewValue) || (VOS_NULL_PTR == pOldValue))
    {
        PPPC_INFO_LOG("CDB_PppCompressCfgModNotify: ERROR INPUT PARA");
        return;
    }

    ucGroupId = (UCHAR)CRM_GetSelfGroupId();
    ucInstanceId = (UCHAR)GTP_INST_GETINSTNO(INST_GetSelfInstanceId());
    pstCompCfg = (PPP_COMPRESS_CFG *)pNewValue;

    PPPC_INFO_LOG3("CDB_PppCompressCfgModNotify: pstCompCfg->ucCompressFlag = %d, pstCompCfg->ucGroupNumber = %d. pstCompCfg->ucInstanceId = %d",
                 pstCompCfg->ucCompressFlag,pstCompCfg->ucGroupNumber,pstCompCfg->ucInstanceId);

    if (pstCompCfg->ucGroupNumber != ucGroupId)
    {
         return;
    }

    if((0 != ucInstanceId) && (pstCompCfg->ucInstanceId != ucInstanceId))
    {
        return;
    }

    CDB_PppCompressGetGlobalVar(pstCompCfg);

    return;
}

/************************************************************
函数名:     CDB_PppCompressCfgAddNotify
描述:       compress配置改变时notify函数
调用:       CDB核心函数
被调用:     CDB 回调
输入:
输出:
返回:       无
其他:
 **************************************************************/
VOID CDB_PppCompressCfgAddNotify(CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*  pValue)
{

    UCHAR ucGroupId  = 0;
    UCHAR ucInstanceId = 0;
    PPP_COMPRESS_CFG *pstCompCfg = VOS_NULL;


    PPPC_INFO_LOG("CDB_PppCompressCfgAddNotify: ENTER");

    /*如果参数非法*/
    if ((M_OS_PPPCOMPRESS_TBL_ID != nTbl) || (VOS_NULL_PTR == pValue))
    {
        PPPC_INFO_LOG("CDB_PppCompressCfgAddNotify: ERROR INPUT PARA");
        return;
    }

    ucGroupId = (UCHAR)CRM_GetSelfGroupId();
    ucInstanceId = (UCHAR)GTP_INST_GETINSTNO(INST_GetSelfInstanceId());
    pstCompCfg = (PPP_COMPRESS_CFG *)pValue;

    PPPC_INFO_LOG3("CDB_PppCompressCfgAddNotify: pstCompCfg->ucCompressFlag = %d, pstCompCfg->ucGroupNumber = %d. pstCompCfg->ucInstanceId = %d",
                 pstCompCfg->ucCompressFlag,pstCompCfg->ucGroupNumber,pstCompCfg->ucInstanceId);

    if (pstCompCfg->ucGroupNumber != ucGroupId)
    {
         return;
    }

    if((0 != ucInstanceId) && (pstCompCfg->ucInstanceId != ucInstanceId))
    {
        return;
    }

    CDB_PppCompressGetGlobalVar(pstCompCfg);

    return;
}

VOS_UINT32 PPP_A11_GetDnsAddress(VOS_UINT32 ulRpIndex, VOS_UINT32 * pulDNSAddress1, VOS_UINT32 * pulDNSAddress2)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    if ((VOS_NULL == pulDNSAddress1)
        || (VOS_NULL == pulDNSAddress2))
    {
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_510);
        return VOS_ERR;
    }

    *pulDNSAddress1 = pstPppInfo->ulDNSAddr1;
    *pulDNSAddress2 = pstPppInfo->ulDNSAddr2;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_GetIpV6Capbility
 功能描述  : 获取IPv6能力配置
 输入参数  :
 输出参数  :
 返 回 值  : VOS_OK 使能IPv6
             VOS_ERR 未使能IPv6
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月8日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_GetIpV6Capbility(VOID)
{
    /* 是否支持ipv6,0表示支持*/
    if (0 == g_stPppCfgInfo.ucIpv6Flag)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPP_GetRetryInterval
 功能描述  : 获取PPP发送消息间隔时长配置
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月8日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_GetRetryInterval(VOID)
{
    return (VOS_UINT32)g_stPppCfgInfo.ucTimeout;
}



/*****************************************************************************
 函 数 名  : PPP_CheckVjLimit
 功能描述  : 决策是否允许VJ压缩
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CheckVjLimit()
{
    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        /* 满足以下条件时允许协商VJ压缩:1.开关打开;2.子卡在位且子卡用户数未超限;3.有子卡DPE的CPU未超限; 4.License未受限 */
        if ((1 == g_ucPppVjSwitch)
            && (((PPP_CPU_ONLINE == g_ulPppSubBordStat[0]) && (HSGW_PRODUCT_VJ_USER_NUMBER > g_ulDmpuVjUser[0]))
               || ((PPP_CPU_ONLINE == g_ulPppSubBordStat[1]) && (HSGW_PRODUCT_VJ_USER_NUMBER > g_ulDmpuVjUser[1])))
            && (g_ulMinDmpuDpeCpuRate < g_ulDmpuCpuThreshold))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1187);
            return VOS_OK;
        }

        PPPC_INFO_LOG4(
            "\r\nPPP_CheckVjLimit: g_ucPppVjSwitch = %lu, g_ulPppSubBordStat[0] = %lu, g_ulDmpuVjUser[0] = %lu, g_ulMinDmpuDpeCpuRate = %lu",
            g_ucPppVjSwitch, g_ulPppSubBordStat[0], g_ulDmpuVjUser[0], g_ulMinDmpuDpeCpuRate);
    }
    else
    {
        if ((1 == g_ucPppVjSwitch)
            && (HSGW_PRODUCT_VJ_USER_NUMBER_PER_SC > g_ulDmpuVjUser[0])
#ifdef __LINUX_PLATFORM__
            && (CMP_CHECK_CPU_USAGE > MON_CpuUsage_MaxCpuOrTidUsage())
#endif
            )
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1188);
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPP_CheckCcpLimit
 功能描述  : 决策是否允许CCP压缩
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CheckCcpLimit( )
{
    /* 目前只支持MPPC压缩 */
    /*lint -e746*/
    return PPP_CheckMppcLimit();
    /*lint +e746*/
}
/*****************************************************************************
 函 数 名  : PPP_CheckMppcLimit
 功能描述  : 决策是否允许MPPC压缩
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CheckMppcLimit( )
{
    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        /* 满足以下条件时允许协商MPPC压缩:1.开关打开;2.子卡在位且子卡用户数未超限;3.有子卡DPE的CPU未超限; 4.License未受限 */
        if ((1 == g_ucPppCcpSwitch) &&(g_ucPppCcpType & M_PPPCOMPRESS_MPPC_FLAG)
            && (((PPP_CPU_ONLINE == g_ulPppSubBordStat[0]) && (HSGW_PRODUCT_MPPC_PDP_NUMBER > g_ulDmpuMppcUser[0]))
                || ((PPP_CPU_ONLINE == g_ulPppSubBordStat[1]) && (HSGW_PRODUCT_MPPC_PDP_NUMBER > g_ulDmpuMppcUser[1])))
            && (g_ulMinDmpuDpeCpuRate < g_ulDmpuCpuThreshold))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1189);
            return VOS_OK;
        }
    }
    else
    {
       if ((1 == g_ucPppCcpSwitch)
            && (HSGW_PRODUCT_MPPC_PDP_NUMBER_PER_SC > g_ulDmpuMppcUser[0])
 #ifdef __LINUX_PLATFORM__
            && (CMP_CHECK_CPU_USAGE > MON_CpuUsage_MaxCpuOrTidUsage())
 #endif
        )
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1190);
            return VOS_OK;
        }
    }
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPP_CheckStacLimit
 功能描述  : 决策是否允许STAC压缩
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月14日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CheckStacLimit( )
{
    return VOS_ERR;
}



/*****************************************************************************
 函 数 名  : PPP_CompUserNumAdd
 功能描述  : 压缩用户数统计
 输入参数  :
 输出参数  :
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月15日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_CompUserNumAdd(PPPINFO_S *pstPppInfo, VOS_UINT32 ulCompType)
{
#if 0
    VOS_UINT32 usDomainIndex = 0;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;

    PPP_INNER_COUNTER(PPP_INNER_COUTNER_022);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER051);
        return;
    }

    usDomainIndex = pstPppInfo->usCDBIndex;
    if (MAX_DOMAIN_NUM <= usDomainIndex)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_511);
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER025);
        return;
    }

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        ucDmpuId = pstPppInfo->ucDmpuId;
        ucDpeId  = pstPppInfo->ucDpeId;
        if ((MAX_DMPU_NUM <= ucDmpuId) || (MAX_DPE_NUM_PDSN <= ucDpeId))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_512);
            PPP_ERROR_COUNTER(PPP_ERROR_COUNTER026);
            return;
        }
    }

    switch(ulCompType)
    {
        case PPP_USERSTAT_VJ:
        {
            if (pstPppInfo->bVjFlag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_513);
                return;
            }

            /* VJ用户统计增加 */
            pstPppInfo->bVjFlag = VOS_TRUE;

            /* License和子卡用户数统计 */
            //A11_LicenseStatistic(1, LICE_PDSN_ITEM_TCPIP_PPP_NUM, SC_GRM_ADD);
            (VOID)A11_CompressStatistic(1, E_GRM_VJ_USERNUM, ucDmpuId, ucDpeId, SC_GRM_ADD);

            /* 调试计数 */
            g_ulDmpuVjUser[ucDmpuId]++;
            g_usPppVjUserNUm[ucDmpuId][ucDpeId]++;

            /* 性能统计，如果同时协商了MPPC压缩 */
            if (pstPppInfo->bMppcFlag)
            {
                PPP_PerfInc(&g_stPppPerfStatistic.ulCurMppcVjUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL, pstPppInfo->bEhrpdUser);


                PPP_PerfDec(&g_stPppPerfStatistic.ulCurMppcUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1191);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_056);
            }
            else
            {
                PPP_PerfInc(&g_stPppPerfStatistic.ulCurVjUser,PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1192);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_023);
            }

            break;
        }
        case PPP_USERSTAT_MPPC:
        {
            if (pstPppInfo->bMppcFlag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_514);
                return;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1193);
            /* MPPC用户统计增加 */
            pstPppInfo->bMppcFlag = VOS_TRUE;


            /* 调试计数 */
            g_ulDmpuMppcUser[ucDmpuId]++;
            g_usPppMppcUserNum[ucDmpuId][ucDpeId]++;

            /* 性能统计，如果同时协商了VJ压缩 */
            if (pstPppInfo->bVjFlag)
            {

                PPP_PerfInc(&g_stPppPerfStatistic.ulCurMppcVjUser, PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL, pstPppInfo->bEhrpdUser);

                PPP_PerfDec(&g_stPppPerfStatistic.ulCurVjUser,PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1194);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_057);
            }
            else
            {
                PPP_PerfInc(&g_stPppPerfStatistic.ulCurMppcUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL, pstPppInfo->bEhrpdUser);
                PPP_DBG_OK_CNT(PPP_PHOK_1195);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_024);
            }
            break;
        }
        case PPP_USERSTAT_ZLS0:
        {
            if (pstPppInfo->bLzs0Flag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_515);
                return;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1196);
            pstPppInfo->bLzs0Flag = VOS_TRUE;
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_025);
            g_usPppLzs0UserNum++;
            break;
        }
        case PPP_USERSTAT_ZLS1:
        {
            if (pstPppInfo->bLzs1Flag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_516);
                return;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1197);
            pstPppInfo->bLzs1Flag = VOS_TRUE;
            PPP_INNER_COUNTER(PPP_INNER_COUTNER_026);
            g_usPppLzs1UserNum++;
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_517);
            PPP_ERROR_COUNTER(PPP_ERROR_COUNTER027);
            break;
        }
    }
#endif
    return;
}

/*****************************************************************************
 函 数 名  : PPP_CompUserNumDel
 功能描述  : 压缩用户数统计
 输入参数  :
 输出参数  :
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月15日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_CompUserNumDel(PPPINFO_S *pstPppInfo, VOS_UINT32 ulCompType)
{

    VOS_UINT32 usDomainIndex = 0;
    UCHAR ucDmpuId = 0;
    UCHAR ucDpeId = 0;

    PPP_DBG_OK_CNT(PPP_PHOK_1198);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        return;
    }

    usDomainIndex = pstPppInfo->usCDBIndex;
    if (MAX_DOMAIN_NUM <= usDomainIndex)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_518);
        return;
    }

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        ucDmpuId = pstPppInfo->ucDmpuId;
        ucDpeId  = pstPppInfo->ucDpeId;
        if ((MAX_DMPU_NUM <= ucDmpuId) || (MAX_DPE_NUM_PDSN <= ucDpeId))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_519);
            return;
        }
    }

    switch(ulCompType)
    {
        case PPP_USERSTAT_VJ:
        {
         /*It is not supported currently*/
    #if 0
            if (VOS_TRUE != pstPppInfo->bVjFlag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_520);
                PPP_ERROR_COUNTER(PPP_ERROR_COUNTER030);
                return;
            }

            pstPppInfo->bVjFlag = VOS_FALSE;

            /* 调试计数 */
            PPP_SUBCOUNT(g_ulDmpuVjUser[ucDmpuId]);
            PPP_SUBCOUNT(g_usPppVjUserNUm[ucDmpuId][ucDpeId]);

            /* 性能统计，如果同时协商了MPPC压缩 */
            if (pstPppInfo->bMppcFlag)
            {
                PPP_PerfDec(&g_stPppPerfStatistic.ulCurMppcVjUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL, pstPppInfo->bEhrpdUser);

                PPP_DBG_OK_CNT(PPP_PHOK_1199);
                PPP_PerfInc(&g_stPppPerfStatistic.ulCurMppcUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL, pstPppInfo->bEhrpdUser);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_059);
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1200);
                PPP_PerfDec(&g_stPppPerfStatistic.ulCurVjUser,PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL, pstPppInfo->bEhrpdUser);
                PPP_INNER_COUNTER(PPP_INNER_COUTNER_058);
            }
    #endif
            break;
        }
        case PPP_USERSTAT_MPPC:
        {
            if (VOS_TRUE != pstPppInfo->bMppcFlag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_521);
                return;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_1201);
            pstPppInfo->bMppcFlag = VOS_FALSE;

            PPP_SUBCOUNT(g_ulDmpuMppcUser[ucDmpuId]);
            PPP_SUBCOUNT(g_usPppMppcUserNum[ucDmpuId][ucDpeId]);

            /* 性能统计，如果同时协商了VJ压缩 */
            if (pstPppInfo->bVjFlag)
            {
                PPP_PerfDec(&g_stPppPerfStatistic.ulCurMppcVjUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL, pstPppInfo->bEhrpdUser);

                PPP_DBG_OK_CNT(PPP_PHOK_1202);
                PPP_PerfInc(&g_stPppPerfStatistic.ulCurVjUser,PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL, pstPppInfo->bEhrpdUser);
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1203);
                PPP_PerfDec(&g_stPppPerfStatistic.ulCurMppcUser,PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL, pstPppInfo->bEhrpdUser);
            }
            break;
        }
        case PPP_USERSTAT_ZLS0:
        {
            if (VOS_TRUE != pstPppInfo->bLzs0Flag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_522);
                return;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1204);

            pstPppInfo->bLzs0Flag = VOS_FALSE;
            PPP_SUBCOUNT(g_usPppLzs0UserNum);
            break;
        }
        case PPP_USERSTAT_ZLS1:
        {
            if (VOS_TRUE != pstPppInfo->bLzs1Flag)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_523);
                return;
            }
            PPP_DBG_OK_CNT(PPP_PHOK_1205);

            pstPppInfo->bLzs1Flag = VOS_FALSE;
            PPP_SUBCOUNT(g_usPppLzs1UserNum);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_524);
            break;
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : PPP_CompUserClear
 功能描述  : 将压缩统计数清零
 输入参数  :
 输出参数  :
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月16日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_CompUserClear(  )
{
    return ;
}

/*****************************************************************************
 函 数 名  : PPP_CompRescSyn
 功能描述  : 定时同步压缩资源使用情况
 输入参数  : VOID* pPara
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月7日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_CompRescSyn()
{
    VOS_UINT32 ulRmiIndex = 0;
    VOS_UINT32 ulDmpuIndex = 0;
    VOS_UINT32 ulDpeIndex = 0;
    VOS_UINT32 ulTotalDpeNum = 0;
    VOS_UINT32 ulCpuRate = 0;
    VOS_UINT32 ulResult = 0;
    SC_COMPRESS_STATE_S stDmpuStat[MAX_DMPU_NUM] = { {0},{0} };

    if (CRM_BOARD_TYPE_SPUD != g_enPppBoardType)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1206);
        return ;
    }

    ulResult = A11_GetCompStatNum(&stDmpuStat[0]);
    if (VOS_OK != ulResult)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_525);
        return;
    }

    /* 得到各子卡所有DPE的最大和最小负荷, */
    g_ulMaxDmpuDpeCpuRate = 0;
    g_ulMinDmpuDpeCpuRate = 100;
    VOS_MemSet(g_ulDmpuDpeCpuRate, 0, sizeof(g_ulDmpuDpeCpuRate));
    VOS_MemSet(g_ulDmpuMppcUser, 0, sizeof(g_ulDmpuMppcUser));
    VOS_MemSet(g_ulDmpuVjUser, 0, sizeof(g_ulDmpuVjUser));

    for( ulDmpuIndex = 0; ulDmpuIndex < MAX_DMPU_NUM; ulDmpuIndex++ )
    {
        g_ulDmpuDpeNumber[ulDmpuIndex] = 0;
        if ((PPP_CPU_ONLINE != g_ulPppSubBordStat[ulDmpuIndex])
            || (MAX_DPE_NUM_PDSN < stDmpuStat[ulDmpuIndex].ulDmpuDpeNum))
        {
            continue;
        }

        g_ulDmpuDpeNumber[ulDmpuIndex] = stDmpuStat[ulDmpuIndex].ulDmpuDpeNum;

        /* 得到各DPE的CPU占用率，以及最大和最小负荷 */
        for (ulDpeIndex = 0; ulDpeIndex < g_ulDmpuDpeNumber[ulDmpuIndex]; ulDpeIndex++)
        {
            ulCpuRate = stDmpuStat[ulDmpuIndex].ucDpeCpuRate[ulDpeIndex];
            if (ulCpuRate > g_ulMaxDmpuDpeCpuRate)
            {
                g_ulMaxDmpuDpeCpuRate = ulCpuRate;
            }
            if (ulCpuRate < g_ulMinDmpuDpeCpuRate)
            {
                g_ulMinDmpuDpeCpuRate = ulCpuRate;
            }

            g_ulDmpuDpeCpuRate[ulTotalDpeNum++] = ulCpuRate;
        }
    }

    /*计算出各DPE的CPU占用率和最大占用率之间的差值，并记录差值累计和 */
    ulCpuRate = 0;
    for ( ulDpeIndex = 0; ulDpeIndex < ulTotalDpeNum; ulDpeIndex++)
    {
        ulCpuRate += g_ulMaxDmpuDpeCpuRate - g_ulDmpuDpeCpuRate[ulDpeIndex] + 1;
        g_ulDmpuDpeCpuRate[ulDpeIndex] = ulCpuRate;
    }

    /* 统计压缩用户数 */
    for (ulRmiIndex = 0; ulRmiIndex < MAX_DMPU_NUM; ulRmiIndex++)
    {
        for (ulDmpuIndex = 0; ulDmpuIndex < MAX_DMPU_NUM; ulDmpuIndex++ )
        {
            if (PPP_CPU_ONLINE != g_ulPppSubBordStat[ulDmpuIndex])
            {
                continue;
            }

            /* 得到各子卡总用户数，包括本RMI和其它RMI激活的和 */
            for (ulDpeIndex = 0; ulDpeIndex < g_ulDmpuDpeNumber[ulDmpuIndex]; ulDpeIndex++)
            {
                g_ulDmpuMppcUser[ulDmpuIndex] += stDmpuStat[ulRmiIndex].ulMppcUserNum[ulDmpuIndex][ulDpeIndex];
                g_ulDmpuVjUser[ulDmpuIndex]   += stDmpuStat[ulRmiIndex].ulVjUserNum[ulDmpuIndex][ulDpeIndex];
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_CompCheckVjUserNum
 功能描述  : 判断vj用户数
 输入参数  :
 输出参数  : UCHAR *pucDmpuId

 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : y00225787
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 PPP_CompCheckVjUserNum(UCHAR *pucDmpuId)
{
    UCHAR ucDmpuId = 0;
    UCHAR ucAnotherDmpu = 0;


    if(VOS_NULL_PTR == pucDmpuId)
    {
        return VOS_ERR;
    }

    ucDmpuId = *pucDmpuId;

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        /* 选中的子卡VJ用户数已经达到最大值 */
        if (g_ulMaxVJNum <= g_ulDmpuVjUser[ucDmpuId])
        {
            /*看另一个子卡用户数是否达到最大 */
            ucAnotherDmpu = (ucDmpuId == 0 ? 1 : 0);
            if ((PPP_CPU_OFFLINE == g_ulPppSubBordStat[ucAnotherDmpu])
                || (g_ulMaxVJNum <= g_ulDmpuVjUser[ucAnotherDmpu]))
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_780);
                return VOS_ERR;
            }

            /* 没有达到最大则直接选择另一个子卡，DPE不变 */
            *pucDmpuId = ucAnotherDmpu;
        }
    }
    else
    {
        /*判断当前sg用户数是否达到最大值*/
        if (HSGW_PRODUCT_VJ_USER_NUMBER <= g_ulDmpuVjUser[0])
        {
              /* 用户数已经达到上限，则终止ipcp */
              PPP_DBG_ERR_CNT(PPP_PHERR_781);
              return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_CompCheckMppcUserNum
 功能描述  : 判断vj用户数
 输入参数  :
 输出参数  : UCHAR *pucDmpuId

 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月16日
    作    者   : y00225787
    修改内容   : 新生成函数

*****************************************************************************/

VOS_UINT32 PPP_CompCheckMppcUserNum(UCHAR *pucDmpuId)
{
    UCHAR ucDmpuId = 0;
    UCHAR ucAnotherDmpu = 0;


    if(VOS_NULL_PTR == pucDmpuId)
    {
        return VOS_ERR;
    }

    ucDmpuId = *pucDmpuId;

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {
        /* 选中的子卡MPPC用户数已经达到最大值 */
        if (HSGW_PRODUCT_MPPC_PDP_NUMBER <= g_ulDmpuMppcUser[ucDmpuId])
        {
            /*看另一个子卡用户数是否达到最大 */
            ucAnotherDmpu = (ucDmpuId == 0 ? 1 : 0);
            if ((PPP_CPU_OFFLINE == g_ulPppSubBordStat[ucAnotherDmpu])
                || (HSGW_PRODUCT_MPPC_PDP_NUMBER <= g_ulDmpuMppcUser[ucAnotherDmpu]))
            {
                /* 子卡不在位，或用户数也已经达到上限，则终止CCP */
                PPP_DBG_ERR_CNT(PPP_PHERR_782);
                return VOS_ERR;
            }

            /* 没有达到最大则直接选择另一个子卡，DPE不变 */
            *pucDmpuId = ucAnotherDmpu;
        }
    }
    else
    {
        /*判断当前sg用户数是否达到最大值*/
        if (HSGW_PRODUCT_MPPC_PDP_NUMBER <= g_ulDmpuMppcUser[0])
        {
              /* 用户数已经达到上限，则终止ccp */
              PPP_DBG_ERR_CNT(PPP_PHERR_783);
              return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_CompSelectDmpuDpe
 功能描述  : 选择子卡及子卡的DPE
 输入参数  :
 输出参数  : UCHAR *pucDmpuId 子卡
             UCHAR* pucDpeId DPEID
 返 回 值  : VOS_OK/VOS_ERR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月7日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CompSelectDmpuDpe(UCHAR *pucDmpuId, UCHAR* pucDpeId)
{
    VOS_UINT32 ulRand = 0;

    if ((VOS_NULL_PTR == pucDmpuId ) || (VOS_NULL_PTR == pucDpeId))
    {
        return VOS_ERR;
    }

    if (VOS_TRUE == g_ulStubDpeNo)
    {
        *pucDmpuId = g_ucStubDmpuId;
        *pucDpeId = 0;
        return VOS_OK;
    }

    if (CRM_BOARD_TYPE_SPUD == g_enPppBoardType)
    {

        if ((0 == g_ulDmpuDpeNumber[0]) && (0 == g_ulDmpuDpeNumber[1]))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_526);
            return VOS_ERR;
        }

        /*最大负荷大于70%，且负荷差异大于5%，则采用按负荷选择 */
        if ((70 < g_ulMaxDmpuDpeCpuRate) && (5 + g_ulMinDmpuDpeCpuRate < g_ulMaxDmpuDpeCpuRate ))
        {
            /* 根据随机数落入窗口决定选择哪个DPE */
            (VOID)PPPC_CRYPT_random((UCHAR*)&ulRand, (SEC_UINT32)sizeof(VOS_UINT32));
            ulRand = ulRand % (g_ulDmpuDpeCpuRate[(g_ulDmpuDpeNumber[0]+g_ulDmpuDpeNumber[1] - 1)]);

             /* 选择0号子卡 */
            if ((0 != g_ulDmpuDpeNumber[0]) && (ulRand < g_ulDmpuDpeCpuRate[g_ulDmpuDpeNumber[0]-1]))
            {
                *pucDmpuId = 0;
                *pucDpeId = (UCHAR)PPP_CompBinSelectDpe(0,
                                            (LONG)(g_ulDmpuDpeNumber[0] - 1),
                                            ulRand);
            }
            else /* 选择1号子卡 */
            {
                *pucDmpuId = 1;
                *pucDpeId = (UCHAR)PPP_CompBinSelectDpe((LONG)g_ulDmpuDpeNumber[0],
                                            (LONG)(g_ulDmpuDpeNumber[0] + g_ulDmpuDpeNumber[1] - 1),
                                            ulRand);
                *pucDpeId -= (UCHAR)g_ulDmpuDpeNumber[0];
            }
        }
        else
        {
            /* 采用轮询方式 */
            g_ulLastSelDmpuDpe = (g_ulLastSelDmpuDpe + 1) % (g_ulDmpuDpeNumber[0] + g_ulDmpuDpeNumber[1]);
            if (g_ulLastSelDmpuDpe < g_ulDmpuDpeNumber[0])
            {
                *pucDmpuId = 0;
                *pucDpeId = (UCHAR)g_ulLastSelDmpuDpe;
            }
            else
            {
                *pucDmpuId = 1;
                *pucDpeId = (UCHAR)(g_ulLastSelDmpuDpe - g_ulDmpuDpeNumber[0]);
            }
        }
    }
    else
    {
        /* F板选本SG */
        *pucDmpuId = (UCHAR)DVM_GetSelfCpuId();
        *pucDpeId  = (UCHAR)PSM_Inf_GetSGIndexBySGID(PPP_SELF_SGID);
    }

    return VOS_OK;
}

LONG PPP_CompBinSelectDpe(LONG llow, LONG lhigh, VOS_UINT32 ulSearchData)
{
    LONG lmid = 0;  /* 此处要使用有符号数，处理小于下标0的情况 */

    while (llow <= lhigh)
    {
        lmid = (llow + lhigh) / 2;
        if (g_ulDmpuDpeCpuRate[lmid] == ulSearchData)
        {
           return lmid + 1;
        }
        else if (ulSearchData < g_ulDmpuDpeCpuRate[lmid])
        {
            lhigh = lmid - 1;
        }
        else
        {
            llow = lmid + 1;
        }
    }
    return llow;
}

/*****************************************************************************
 函 数 名  : PPP_CheckRenegoFlag
 功能描述  : 检查重协商标致
 输入参数  : VOS_UINT32 ulRpIndex


 输出参数  : UCHAR * pucRegoFlag
 返 回 值  : VOS_UINT32
 调用函数  : 该函数提供给AUTH模块鉴权后使用
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月20日
    作    者   : y00125257
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_CheckRenegoFlag
(       VOS_UINT32 ulRpIndex,
        UCHAR * pucRegoFlag)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pucRegoFlag)
    {
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);

    if (VOS_NULL_PTR == pstPppInfo)
    {
        return VOS_ERR;
    }

    if (VOS_TRUE == pstPppInfo->bPpcAAAFlag)
    {
        *pucRegoFlag = VOS_TRUE;
    }
    else
    {
        *pucRegoFlag = VOS_FALSE;
    }

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : PPP_L2tpIpcpMsgProc
 功能描述  : 处理转发截取的L2TP用户的IPCP消息，更新到RP上下文中
 输入参数  : MBUF_S *pMbuf
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月18日
    作    者   : h50774
    修改内容   : 新生成函数，台湾ATP需求
 2.日    期   : 2013年3月4日
    作    者   : zhaichao 00129699
    修改内容   : 新架构下重新适配
*****************************************************************************/
VOS_UINT32 PPP_L2tpIpcpMsgProc(PMBUF_S *pMbuf )
{
#if 0
    VOS_UINT32 ulLen = 0;
    VOS_UINT32 ulReturn = 0;
    VOS_UINT32 ulA10Index = 0;
    VOS_UINT32 ulIpAddr = 0;
    UCHAR *pPacket = VOS_NULL_PTR;
    PDN_CONTEXT_S   *pstPdnRec = VOS_NULL;
    FWD_TO_CTRL_HDR *pstCtrl   = VOS_NULL;

    if (VOS_NULL_PTR == pMbuf)
    {
        return VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1207);

    /*底层上报的PPP协商报文中是A10Index，需要转换成RpIndex*/
    pstCtrl = PMBUF_MTOD(pMbuf, FWD_TO_CTRL_HDR *);

    ulA10Index = pstCtrl->ulPdpIndex;
    ulA10Index = (VOS_UINT32)A11_A10GlobalIndexToA10ScIndex(ulA10Index);
    if (0 == ulA10Index)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_527);
        PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: ulA10Index IS INVALID!");
        return VOS_ERR;
    }

    ulReturn = (VOS_UINT32)SDB_GetPdnContextByA10IndexForPdsn(ulA10Index, (UCHAR **)&pstPdnRec);
    if ((ulReturn != SDB_SUCCESS) || (VOS_NULL_PTR == pstPdnRec))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_528);
        PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: Return Error,A10Index[%d]", ulA10Index);
        return VOS_ERR;
    }

    if (E_PDNTYPE_L2TP != pstPdnRec->ucPdnType)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_529);
        PPPC_INFO_LOG((VOS_UINT32)FSU_TID_PPPC, PDSN_DBGLVL_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: It is not L2TP user! pdnindex = %d pdntype %d",
                      pstPdnRec->ulPdnIndex, pstPdnRec->ucPdnType);
        return VOS_ERR;
    }

    ulLen = PMBUF_GET_TOTAL_DATA_LENGTH(pMbuf) - sizeof(FWD_TO_CTRL_HDR);
    if (ulLen > PPP_DEFAULT_NEGO_PACKET_LEN)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_530);
        PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: Msg is too long! len = %d", ulLen);
        return VOS_ERR;
    }

    pPacket = g_ucPppRcvPacketHead;
    PGP_MemZero((void *)pPacket,  PPP_DEFAULT_NEGO_PACKET_LEN + PPP_RESERVED_PACKET_HEADER);

    (VOID)PMBUF_CopyDataFromPMBufToBuffer(pMbuf, sizeof(FWD_TO_CTRL_HDR), ulLen, pPacket);

    ulReturn = PPP_GetIpAddrFromPacket(pPacket, ulLen, &ulIpAddr);
    if (VOS_OK != ulReturn)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_531);
        PPPC_INFO_LOG(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_L2tpIpcpMsgProc: Get IpAddr faild!");
        return VOS_ERR;
    }

    if ((0 != ulIpAddr) && (0xFFFFFFFF != ulIpAddr)
        && (pstPdnRec->ulIpV4Addr != ulIpAddr))
    {
        pstPdnRec->ulIpV4Addr = ulIpAddr;
    }
#endif
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_GetIpAddrFromPacket
 功能描述  : 从报文中解出IP地址
 输入参数  : UCHAR *pHend
             VOS_UINT32 ulLen
             VOS_UINT32 ulIpAddr
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月18日
    作    者   : h50774
    修改内容   : 新生成函数，台湾ATP需求

*****************************************************************************/
VOS_UINT32 PPP_GetIpAddrFromPacket(UCHAR *pPacket, VOS_UINT32 ulLen, VOS_UINT32 *pulIpAddr )
{
    VOS_UINT32 ulOffset = 0;
    VOS_UINT32 ulIpAddr = 0;
    VOS_UINT32  lCiLen  = 0;
    VOS_UINT16 usProtocol = 0;
    UCHAR ucCode = 0;
    UCHAR cilen  = 0;
    UCHAR citype = 0;

    /* 获得协议号,并返回PPP头长度 */
    ulOffset = PPP_Core_GetProtocol(VOS_NULL_PTR, pPacket, &usProtocol);
    if (((ulOffset == 0) || (ulLen < ulOffset))
        || (PPP_IPCP != usProtocol))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_532);
        PPPC_INFO_LOG2(
                      "\r\n [ppp]PPP_GetIpAddrFromPacket: Wrong Msg! Offset = %d, Protocol = %d",
                      ulOffset, usProtocol);
        return VOS_ERR;
    }

    /* 移动指针 */
    pPacket += ulOffset;
    ulLen   -= ulOffset;

    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(cilen, pPacket);  /* ID无用，临时存放一下 */
    PPP_GETSHORT(lCiLen, pPacket);

    if ((lCiLen > ulLen) || (lCiLen < FSM_HDRLEN)
        || ((CONFREQ != ucCode) && (CONFACK != ucCode)))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_533);
        return VOS_ERR;
    }

    /* 报文长度减去FSM头的长度 */
    lCiLen -= FSM_HDRLEN;

    while (lCiLen >= IPCP_CILEN_ADDR)
    {
        PPP_GETCHAR(citype, pPacket);
        PPP_GETCHAR(cilen, pPacket);

        if (IPCP_CILEN_VOID > cilen)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_534);
            return VOS_ERR;
        }

        if ((IPCP_CI_ADDR == citype) && (IPCP_CILEN_ADDR == cilen))
        {
             PPP_GETADDR(ulIpAddr, pPacket);
             *pulIpAddr = ulIpAddr;
             (VOS_VOID)pPacket;
             return VOS_OK;
        }

        pPacket += (cilen - IPCP_CILEN_VOID);
        lCiLen  -= cilen;
    }

    PPP_DBG_ERR_CNT(PPP_PHERR_535);
    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPP_GetIpAddrByBufReq
 功能描述  : 从缓存的IPCP消息中获取用户请求的地址,PMIPv6支持静态地址
 输入参数  : VOS_UINT32 ulRpIndex
             VOS_UINT32 *pulReqIpAddr
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月26日
    作    者   : h50774
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPP_GetIpAddrByBufReq( VOS_UINT32 ulRpIndex, VOS_UINT32 *pulReqIpAddr )
{
    VOS_UINT32 ulRet = VOS_OK;
    UCHAR *pucPacket = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstIpcpInfo = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pulReqIpAddr)
    {
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_536);
        return VOS_ERR;
    }

    pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
    if ((VOS_NULL_PTR == pstIpcpInfo) || (VOS_NULL_PTR == pstIpcpInfo->pucIpv4cpMsg))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_537);
        return VOS_ERR;
    }

    pucPacket = pstIpcpInfo->pucIpv4cpMsg + PPP_RESERVED_PACKET_HEADER;

    /* 缓存的时候已经把protocol偏移掉了，需要重新补上 */
    pucPacket -= sizeof(VOS_UINT16);
    *(VOS_UINT16*)pucPacket = VOS_HTONS(PPP_IPCP);

    ulRet = PPP_GetIpAddrFromPacket(pucPacket,
                                    pstIpcpInfo->ulIpv4cpLen + sizeof(VOS_UINT16),
                                    pulReqIpAddr);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : PPP_SendInnerMsg
 功能描述  : 发送消息到内部队列处理
 输入参数  : VOS_UINT32 ulPara
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月13日
    作    者   : y00225787
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID PPP_SendInnerMsg(VOS_UINT32 ulPara)
{
    PPP_INNER_MSG_S             stInnerMsg = {0};
    VOS_UINT32                  ulReturn = 0;

    stInnerMsg.ulCurRenegoIndex = ulPara;

    /* 使用RTD发送内部消息到PPP任务处理 */
    ulReturn = PPP_SendRtMsg(PPP_SELF_CSI, PPP_SELF_CSI,PPP_MSG_TYPE_INNER, PPP_INNER_MSG_CODE_RENEGO,
                             (UCHAR *)&stInnerMsg, sizeof(PPP_INNER_MSG_S));
    if (VOS_OK != ulReturn)
    {
        PPPC_WARNING_LOG1("PPP_SendInnerMsg fail.%u",ulReturn);
        return;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_ClearVjFlag
 功能描述  : 清除rp上下文中的vj压缩标记
 输入参数  : VOS_UINT32 ulPara
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月13日
    作    者   : y00225787
    修改内容   : 新生成函数

*****************************************************************************/

VOID PPP_ClearVjFlag(VOS_UINT32  ulRpIndex)
{
    SDB_PDSN_RP_CONTEXT_S *pstRPContext = VOS_NULL_PTR;    /* A10 上下文指针*/
    SDB_RETURNCODE_E enSdbRet = SDB_SYSTEM_FAILURE;

    enSdbRet = (SDB_RETURNCODE_E)SDB_GetRpContextByIndex(ulRpIndex,
                                     (VOS_VOID **)&pstRPContext);
    if ((enSdbRet != SDB_SUCCESS) || (VOS_NULL_PTR == pstRPContext))
    {
        PPPC_WARNING_LOG("PPP_ClearVjFlag fail");
        PPP_DBG_ERR_CNT(PPP_PHERR_538);
        return ;
    }

    pstRPContext->bVjFlag = VOS_FALSE;
    return;
}

/*****************************************************************************
 函 数 名  : PPP_A11_GetSubBoardStat
 功能描述  : PPP模块提供给A11获取子卡在位信息
 输入参数  : UCHAR ucDmpuId, VOS_UINT32 *pulSubBoardStat
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 20014-01-10
    作    者   : y00225787
    修改内容   : 新生成函数
*****************************************************************************/

VOS_UINT32 PPP_A11_GetSubBoardStat( UCHAR ucDmpuId )
{
    if(CRM_BOARD_TYPE_SPUD != g_enPppBoardType)
    {
        return VOS_OK;
    }

    ucDmpuId = ucDmpuId - PPP_CPU_2_ON_SPU;

    /*dmpuID取值为0或者1*/
    if(ucDmpuId > 1)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_778);
        return VOS_ERR;
    }

    if(PPP_CPU_OFFLINE == g_ulPppSubBordStat[ucDmpuId])
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_779);
        return VOS_ERR;
    }
    return VOS_OK;
}

#define __PPP__BACKUP__PROC__

/*****************************************************************************
 函 数 名  : PPP_EncapL2tpPppcUpInfo
 功能描述  : l2tp用户激活备板处理,由ppp从pdn上下文中获取相关信息封装l2tp所需备份数据
 被调函数  :
 调用函数  :
 输入参数  : PDN_CONTEXT_S *pstPdnContext, L2TP_NOTIFY_PPPC_UP_INFO *pstL2tpUpInfo
 输出参数  :
 返 回 值  : VOID

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_EncapL2tpPppcUpInfo(PDN_CONTEXT_S *pstPdnContext, L2TP_NOTIFY_PPPC_UP_INFO *pstL2tpUpInfo)
{
#if 0
    VOS_UINT32 ulRet = 0;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;


    CKP_DBG_INC_COUTER(CKP_SUCC_99);


    /* 首先查找rp上下文是否存在不存在则创建否则直接更新上下文 */
    ulRet = (VOS_UINT32)SDB_GetRpContextByIndex(pstPdnContext->ulRpIndex, (UCHAR **)&pstRpContext);
    if (VOS_OK != ulRet || VOS_NULL == pstRpContext)
    {

        CKP_DBG_INC_COUTER(CKP_ERR_40);

        return VOS_ERR;
    }

    pstL2tpUpInfo->ucDpeId              = pstRpContext->ucDpeId;
    pstL2tpUpInfo->ulGtpuIndex          = pstRpContext->ausA10IndexArray[0] + (SDB_MAX_PDSN_A10_CONTEXT_NUM * PPP_SELF_CMPIDXINSG);
    //pstL2tpUpInfo->ulFilterTableIndex   = pstPdnContext->ulPdnIndex;
    pstL2tpUpInfo->ulTeidc              = pstPdnContext->ulTeidc;
    pstL2tpUpInfo->ulPdpindex           = PDN_PDNScIndexToPDNGlobalIndex(pstPdnContext->ulPdnIndex);
    pstL2tpUpInfo->usApnIndex           = pstPdnContext->usDomainIdx;
    pstL2tpUpInfo->ulIFIndex            = pstPdnContext->stL2tp.ulIfIndex;
    pstL2tpUpInfo->ulLocalIP            = pstPdnContext->stL2tp.ulLacAddr;
    pstL2tpUpInfo->ulPeerIP             = pstPdnContext->stL2tp.ulLnsAddr;
    pstL2tpUpInfo->usLocalTunnelId      = pstPdnContext->stL2tp.usLocalTid;
    pstL2tpUpInfo->usLocalSessionId     = pstPdnContext->stL2tp.usLocalSid;
    pstL2tpUpInfo->usPeerTunnelId       = pstPdnContext->stL2tp.usPeerTid;
    pstL2tpUpInfo->usPeerSessionId      = pstPdnContext->stL2tp.usPeerSid;
    pstL2tpUpInfo->ucCompInstIdx        = (UCHAR)PPP_SELF_CMPIDX;
    VOS_MemCpy(pstL2tpUpInfo->szImsi, &pstRpContext->stImsi, sizeof(A11_IMSI_S));
    VOS_MemCpy(pstL2tpUpInfo->szMsisdn, pstRpContext->szMsisdn, sizeof(GTP_MSISDN));
#endif
    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : PPP_BackupUpdateData
 功能描述  : 备板更新ppp控制块,以ppp备份信息数据更新到ppp控制块中
 被调函数  :
 调用函数  :
 输入参数  : PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstPppInfobkp
 输出参数  :
 返 回 值  : VOID

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_BackupUpdateData(PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstPppInfobkp)
{
    PPPLCPINFO_S* pstLcpInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S* pstIpcpInfo = VOS_NULL_PTR;
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL_PTR;
    //PPPDHCPINFO_S* pstDhcpInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S* pstIpv6cpInfo = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_100);
#endif
    /* LCP */
    if (pstPppInfo->pstLcpInfo)
    {
        pstLcpInfo = pstPppInfo->pstLcpInfo;
        VOS_MemCpy((VOID*)&(pstLcpInfo->stGotOptions),
                     (VOID*)&(pstPppInfobkp->stLcpGotOptions),
                     sizeof(PPP_LCP_OPTION_S));
        pstLcpInfo->stFsm.ucPktId = pstPppInfobkp->ucLcpPktId;
        pstLcpInfo->stFsm.ucEchoState = pstPppInfobkp->ucEchoState;        /*r002*/
    }

    /* LCP IPCP DHCP有待整改为函数 */
    /* ipv4 ipcp */
    if (PPP_STATE_SUCCESS == pstPppInfobkp->bPppStateFlg)
    {
        if (pstPppInfo->pstIpcpInfo)
        {
            pstIpcpInfo = pstPppInfo->pstIpcpInfo;
            VOS_MemCpy((VOID*)&(pstIpcpInfo->stGotOptions),
                         (VOID*)&(pstPppInfobkp->stIpcpGotOptions),
                         sizeof(PPP_IPCP_OPTION_S));
            pstIpcpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
            if (1 == pstIpcpInfo->stGotOptions.neg_vj)
            {
                pstPppInfo->pstConfigInfo->bEnableVJComp = 1;        /* Added by liutao 38563 at 2004-11-02 V800R002 for PPPC移植 */
            }
        }
        /* 无控制块则需要新建 */
        else
        {
            /* 为IPCP子控制块申请内存 */
            PPP_GETIPCPADDR(pstIpcpInfo,pstPppInfo->ulRPIndex);
            if (VOS_NULL_PTR == pstIpcpInfo)
            {
#if 0
                CKP_DBG_INC_COUTER(CKP_ERR_41);
#endif
                PPPC_INFO_LOG("\r\n PPP_BkpPppDataUpdate: get ipcp addr failed.");
                (VOID)PPP_ClearCB(pstPppInfo);

                return;
            }
            else
            {
                PPP_MemSet((VOID *)pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

                pstPppInfo->pstIpcpInfo = pstIpcpInfo;
                PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);

                /* 更新State状态值为success */
                pstPppInfo->bPppStateFlg = PPP_STATE_SUCCESS;

                PPP_IPCP_resetci(&pstIpcpInfo->stFsm);

                pstIpcpInfo->stFsm.ucState = PPP_STATE_OPENED;
                VOS_MemCpy((VOID*)&(pstIpcpInfo->stGotOptions),
                             (VOID*)&(pstPppInfobkp->stIpcpGotOptions),
                             sizeof(PPP_IPCP_OPTION_S));
                pstIpcpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
                pstPppInfo->bVjFlag = VOS_FALSE;
                if (1 == pstIpcpInfo->stGotOptions.neg_vj)
                {
                    pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
                }
            }
        }
    }
    else
    {
        /* 单栈ipv4删除 */
        if(pstPppInfo->pstIpcpInfo != VOS_NULL_PTR)
        {
            PPP_ClearCB_IPCP(pstPppInfo->pstIpcpInfo);
            pstPppInfo->pstIpcpInfo = VOS_NULL_PTR;
        }
    }

    /* ipv6 ipcp */
    if (PPP_STATE_SUCCESS == pstPppInfobkp->bPppStateFlgV6)
    {
        if(VOS_NULL_PTR != ((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo)))
        {
            (VOID)VOS_MemCpy((VOID*)&(((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->stGotOptions),
                               (VOID*)&(pstPppInfobkp->stIpv6cpGotOptions),
                               sizeof(PPP_IPV6CP_OPTION_S));
            ((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
        }
        /* 无控制块则需要新建 */
        else
        {
            PPP_GETIPV6CPADDR(pstIpv6cpInfo,pstPppInfo->ulRPIndex);
            if (VOS_NULL_PTR == pstIpv6cpInfo)
            {
#if 0
                CKP_DBG_INC_COUTER(CKP_ERR_42);
#endif
                PPPC_INFO_LOG("\r\n PPP_BkpPppDataCreate: get ipv6 ipcp addr failed.");
                (VOID)PPP_ClearCB(pstPppInfo);

                return;
            }

            PPP_MemSet((VOID *)pstIpv6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

            pstPppInfo->pstIpV6cpInfo = pstIpv6cpInfo;
            PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

            /* 更新State状态值为success */
            pstPppInfo->bPppStateFlgV6 = PPP_STATE_SUCCESS;

            PPP_IPV6CP_resetci(&pstIpv6cpInfo->stFsm);

            pstIpv6cpInfo->stFsm.ucState = PPP_STATE_OPENED;
            VOS_MemCpy((VOID*)&(pstIpv6cpInfo->stGotOptions),
                         (VOID*)&(pstPppInfobkp->stIpv6cpGotOptions),
                         sizeof(PPP_IPV6CP_OPTION_S));
            pstIpv6cpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
        }
    }
    else
    {
        /* 单栈ipv6删除 */
        if(pstPppInfo->pstIpV6cpInfo != VOS_NULL_PTR)
        {
            PPP_ClearCB_IPV6CP(pstPppInfo->pstIpV6cpInfo);
            pstPppInfo->pstIpV6cpInfo = VOS_NULL_PTR;
        }
    }

    if (VOS_NULL_PTR != pstPppInfo->pstCcpInfo)
    {
        pstCcpInfo = (PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo;
        pstCcpInfo->ucUsed = VOS_FALSE;
        pstPppInfo->pstCcpInfo = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_BackupCreateData
 功能描述  : 备板新建ppp控制块从ppp备份信息恢复数据到ppp控制块中
 被调函数  :
 调用函数  :
 输入参数  : PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstPppInfobkp
 输出参数  :
 返 回 值  : VOID

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_BackupCreateData(PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstPppInfobkp)
{
    PPPLCPINFO_S *pstPppLcpInfo = VOS_NULL_PTR;
    PPPIPV6CPINFO_S* pstIpv6cpInfo = VOS_NULL_PTR;
    PPPIPCPINFO_S *pstPppIpcpInfo = VOS_NULL_PTR;
#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    PPPC_EAP_INFO_STRU *pstEapInfo = VOS_NULL_PTR;
#endif
    pstPppInfo->usPhase = PPP_PHASE_NETWORK;

    pstPppInfo->ulIPAddr = pstPppInfobkp->ulIPAddr;

    /* IPV6CP协商中本地地址采用固定地址FE80::rp口v4地址*/
    //VOS_Mem_Copy((void *)(&usIpv6addr[6]), (void *)&g_ulA11RpifIp,sizeof(VOS_UINT32));
    //VOS_Mem_Copy(pstPppInfo->usIpv6Addr, usIpv6addr, IPV6_ADDR_LEN*2);

    VOS_MemCpy(pstPppInfo->usIpv6Addr, pstPppInfobkp->usIpv6Addr, IPV6_ADDR_LEN*2);

    /* LCP数据恢复 */
    /* 为LCP子控制块申请内存 */
    PPP_GETLCPADDR(pstPppLcpInfo, pstPppInfo->ulRPIndex);
    if (!pstPppLcpInfo)
    {
        PPPC_INFO_LOG(
                "\r\n PPP_BkpRestore: get lcp addr failed");
        return VOS_ERR;
    }

    PPP_MemSet((VOID*)pstPppLcpInfo, 0, sizeof(PPPLCPINFO_S));

    if (PPP_InitConfigInfo(pstPppInfo) == VOS_ERR)
    {
        (VOID)PPP_ClearCB(pstPppInfo);
        return VOS_ERR;
    }

    pstPppInfo->ulNegoEndTime = VOS_GetTick();

    pstPppInfo->pstLcpInfo = pstPppLcpInfo;
    PPP_LCP_Init(pstPppInfo);
    PPP_LCP_resetci(&pstPppLcpInfo->stFsm);
    pstPppLcpInfo->stFsm.ucState = PPP_STATE_OPENED;
    VOS_MemCpy((VOID*)&(pstPppLcpInfo->stGotOptions),
                 (VOID*)&(pstPppInfobkp->stLcpGotOptions),
                 sizeof(PPP_LCP_OPTION_S));
    pstPppLcpInfo->stFsm.ucPktId = pstPppInfobkp->ucLcpPktId;
    pstPppLcpInfo->stFsm.ucEchoState = pstPppInfobkp->ucEchoState;        /*r002*/

    /* ipv4 IPCP数据恢复 */
    if (PPP_STATE_SUCCESS == pstPppInfobkp->bPppStateFlg)
    {
        /* 为IPCP子控制块申请内存 */
        PPP_GETIPCPADDR(pstPppIpcpInfo,pstPppInfo->ulRPIndex);
        if (!pstPppIpcpInfo)
        {
            PPPC_INFO_LOG("\r\n PPP_BkpPppDataCreate: get ipcp addr failed.");
            (VOID)PPP_ClearCB(pstPppInfo);

            return VOS_ERR;
        }

        PPP_MemSet((VOID *)pstPppIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

        pstPppInfo->pstIpcpInfo = pstPppIpcpInfo;
        PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);

        /* 更新state为success */
        pstPppInfo->bPppStateFlg = PPP_STATE_SUCCESS;

        /* Added start by g00127633 at 2010-02-27 PDSNC03SPC200 for 问题单号为：AP8D09259 */
        PPP_IPCP_resetci(&pstPppIpcpInfo->stFsm);
        /* Added end by g00127633 at 2010-02-27 PDSNC03SPC200 for 问题单号为：AP8D09259 */

        pstPppIpcpInfo->stFsm.ucState = PPP_STATE_OPENED;
        VOS_MemCpy((VOID*)&(pstPppIpcpInfo->stGotOptions),
                     (VOID*)&(pstPppInfobkp->stIpcpGotOptions),
                     sizeof(PPP_IPCP_OPTION_S));
        pstPppIpcpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
        pstPppInfo->bVjFlag = VOS_FALSE;
        if (1 == pstPppIpcpInfo->stGotOptions.neg_vj)
        {
            /* Added start by liutao 38563 at 2004-11-03 V800R002 for PPPC移植 */
            pstPppInfo->pstConfigInfo->bEnableVJComp = 1;
            /* Added end by liutao 38563 at 2004-11-03 V800R002 for PPPC移植 */
        }
    }

    /* LCP IPCP DHCP有待整改为函数 */
    if (PPP_STATE_SUCCESS == pstPppInfobkp->bPppStateFlgV6)
    {
        /* ipv6 IPCP数据恢复 */
        PPP_GETIPV6CPADDR(pstIpv6cpInfo,pstPppInfo->ulRPIndex);
        if (!pstIpv6cpInfo)
        {
            PPPC_INFO_LOG("\r\n PPP_BkpPppDataCreate: get ipv6 ipcp addr failed.");
            /* pstPppInfo->pstLcpInfo = VOS_NULL_PTR; */
            (VOID)PPP_ClearCB(pstPppInfo);

            return VOS_ERR;
        }

        PPP_MemSet((VOID *)pstIpv6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));

        pstPppInfo->pstIpV6cpInfo = pstIpv6cpInfo;
        PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

        /* 更新state为success */
        pstPppInfo->bPppStateFlgV6 = PPP_STATE_SUCCESS;

        PPP_IPV6CP_resetci(&pstIpv6cpInfo->stFsm);

        pstIpv6cpInfo->stFsm.ucState = PPP_STATE_OPENED;
        VOS_MemCpy((VOID*)&(pstIpv6cpInfo->stGotOptions),
                     (VOID*)&(pstPppInfobkp->stIpv6cpGotOptions),
                     sizeof(PPP_IPV6CP_OPTION_S));
        pstIpv6cpInfo->stFsm.ucPktId = pstPppInfobkp->ucIpcpPktId;
    }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
    /* eap */
    if (pstPppInfo->bEhrpdUser)
    {
        /*申请EAP控制块*/
        PPP_GETEAPADDR(pstPppInfo->pstEapInfo, pstPppInfo->ulRPIndex);
        if (pstPppInfo->pstEapInfo != VOS_NULL_PTR)
        {
            /* 初始化EAP控制块 */
            PPPC_EAP_Init(pstPppInfo);
            pstEapInfo = pstPppInfo->pstEapInfo;
        }
        else
        {



            PPPC_INFO_LOG("PPP_BkpPppDataCreate: get eap addr failed.");
            (VOID)PPP_ClearCB(pstPppInfo);
            return VOS_ERR;
        }
    }
    /* VSNCP恢复 待完成*/
#endif

    pstPppInfo->pstPapInfo   = VOS_NULL_PTR;
    pstPppInfo->pstChapInfo  = VOS_NULL_PTR;
    pstPppInfo->pL2tpPara    = VOS_NULL_PTR;
    pstPppInfo->pstVsncpInfo = VOS_NULL_PTR;

    (VOS_VOID)pstEapInfo;
    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_BackupRestoreVsncp
 功能描述  : ehrpd用户pdn模块备板恢复数据调用此接口恢复pdn上下文中的vsncp信息
 被调函数  : PDN_BackupDecapEhrpdInfo
 调用函数  :
 输入参数  : PDN_CONTEXT_S *pstPdnContext, UCHAR ucPDNID, UCHAR ucPktId
 输出参数  :
 返 回 值  : VOID

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_BackupRestoreVsncp(PDN_CONTEXT_S *pstPdnContext, UCHAR ucPDNID, UCHAR ucPktId)
{
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_102);
#endif
    pstPdnContext->stEhrpd.stVSNCP.ucPktId       = ucPktId;
    pstPdnContext->stEhrpd.stVSNCP.ucPDNID       = ucPDNID;
    pstPdnContext->stEhrpd.stVSNCP.ucState       = PPP_STATE_OPENED;
    pstPdnContext->stEhrpd.stVSNCP.ucUsedFlag    = VOS_TRUE;

    return;
}

/*****************************************************************************
 函 数 名  : PPP_BackupRestoreCompData
 功能描述  : 备板解封装ppp的备份结构体信息，恢复压缩相关数据
 被调函数  :
 调用函数  :
 输入参数  : PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstPppInfobkp
 输出参数  :
 返 回 值  : VOID

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_BackupRestoreCompData(PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstPppInfobkp)
{
    PPP_CCP_INFO_S* pstCcpInfo = VOS_NULL;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_103);
#endif
    pstPppInfo->bMppcFlag = VOS_FALSE;

    if (pstPppInfobkp->bMppc)
    {
        PPP_GETCCPADDR(pstCcpInfo, pstPppInfo->ulRPIndex);
        pstPppInfo->pstCcpInfo = pstCcpInfo;
        if (pstCcpInfo)
        {
            PPP_MemSet(pstCcpInfo, 0, sizeof(PPP_CCP_INFO_S));

            /* 初始化CCP控制块 */
            PPP_CCP_init(pstPppInfo);
            pstCcpInfo->stFsm.ucState = PPP_STATE_OPENED;
            pstCcpInfo->stGotOptions.bMppc_compress = 1;
            pstCcpInfo->stGotOptions.bStac_compress = 0;

            pstCcpInfo->ucPppCompType   = PPPCOMP_MPPC;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_BackupEncapUpdatePppInfo
 功能描述  : 主板封装ppp控制块对应的备份结构体信息
 被调函数  :
 调用函数  :
 输入参数  : PPPINFO_S *pstPppInfo, UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen
 输出参数  :
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_BackupEncapUpdatePppInfo(PPPINFO_S *pstPppInfo, UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen)
{
    VOS_UINT32                     ulEncapLen      = 0;
    CKP_BACKUP_PPPALLINFO_S  *pstCkpPppBkInfo = VOS_NULL_PTR;
    CKP_BACKUP_MSGTLV_HEAD_S *pstMsgTlvHead   = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_104);
#endif
    ulEncapLen = sizeof(CKP_BACKUP_PPPALLINFO_S);

    /* 设置TLV头 */
    pstMsgTlvHead = (CKP_BACKUP_MSGTLV_HEAD_S*)(*ppucCurrent);
    pstMsgTlvHead->ulSdbIndex = pstPppInfo->ulRPIndex;
    pstMsgTlvHead->ulType     = CKP_BACKUP_TYPE_UPDATE_PPP;
    pstMsgTlvHead->usStrLen   = (VOS_UINT16)ulEncapLen;
    pstMsgTlvHead->ucNum      = 1;

    /* 设置TLV数据体 */
    pstCkpPppBkInfo = (CKP_BACKUP_PPPALLINFO_S *)pstMsgTlvHead->ucValue;

    pstCkpPppBkInfo->bIsAsync        = pstPppInfo->bIsAsync;
    pstCkpPppBkInfo->bSynAsyConvert  = pstPppInfo->bSynAsyConvert;
    pstCkpPppBkInfo->bLoopBacked     = pstPppInfo->bLoopBacked;
    pstCkpPppBkInfo->bLowerIsUp      = pstPppInfo->bLowerIsUp;
    pstCkpPppBkInfo->bIPReleaseFlg   = pstPppInfo->bIPReleaseFlg;
    pstCkpPppBkInfo->bIPTech         = pstPppInfo->bIPTech;
    pstCkpPppBkInfo->bAuthServer     = pstPppInfo->bAuthServer;
    pstCkpPppBkInfo->bAuthClient     = pstPppInfo->bAuthClient;
    pstCkpPppBkInfo->bReNego         = pstPppInfo->bReNego;
    pstCkpPppBkInfo->bReNegoV6       = pstPppInfo->bReNegoV6;
    pstCkpPppBkInfo->bEAPAuthFlag    = pstPppInfo->bEAPAuthFlag;

    pstCkpPppBkInfo->bIPCPNakHandFlag = pstPppInfo->bIPCPNakHandFlag;
    pstCkpPppBkInfo->ucAAAType       = pstPppInfo->ucAAAType;

    pstCkpPppBkInfo->bPppStateFlg = 0;
    pstCkpPppBkInfo->bPppStateFlgV6 = 0;
    if (VOS_OK == PDN_JudgeSubPDNStateActive(pstPppInfo->ulRPIndex, E_PDN_STACK_TYPE_IPV4))
    {
        pstCkpPppBkInfo->bPppStateFlg = PPP_STATE_SUCCESS;
    }
    if (VOS_OK == PDN_JudgeSubPDNStateActive(pstPppInfo->ulRPIndex, E_PDN_STACK_TYPE_IPV6))
    {
        pstCkpPppBkInfo->bPppStateFlgV6 = PPP_STATE_SUCCESS;
    }
    pstCkpPppBkInfo->bPppMode        = pstPppInfo->bPppMode;
    pstCkpPppBkInfo->bPppClient      = pstPppInfo->bPppClient;
    pstCkpPppBkInfo->bPhaseFlag      = pstPppInfo->bPhaseFlag;
    pstCkpPppBkInfo->bPpcAAAFlag     = pstPppInfo->bPpcAAAFlag;
    pstCkpPppBkInfo->bPppSuccess     = pstPppInfo->bPppSuccess;
    pstCkpPppBkInfo->bAuthFlag       = pstPppInfo->bAuthFlag;
    pstCkpPppBkInfo->bIpcpSucFlag    = pstPppInfo->bIpcpSucFlag;
    pstCkpPppBkInfo->bRecvLcpMsgFlag = pstPppInfo->bRecvLcpMsgFlag;
   // pstCkpPppBkInfo->bBit328SoftPara = pstPppInfo->bBit328SoftPara;
    pstCkpPppBkInfo->bIpv6cpNoToPDN  = pstPppInfo->bIpv6cpNoToPDN;
    pstCkpPppBkInfo->bIpcpNoToPDN    = pstPppInfo->bIpcpNoToPDN;
    pstCkpPppBkInfo->bEhrpdUser      = pstPppInfo->bEhrpdUser;
    pstCkpPppBkInfo->ulRemoteAccm    = pstPppInfo->ulRemoteAccm;
    pstCkpPppBkInfo->ulLocalAccm     = pstPppInfo->ulLocalAccm;

    pstCkpPppBkInfo->ulPcfIP         = pstPppInfo->ulPcfIP;
    pstCkpPppBkInfo->ulIPAddr        = pstPppInfo->ulIPAddr;

    if (PPP_STATE_SUCCESS == pstCkpPppBkInfo->bPppStateFlg)
    {
        pstCkpPppBkInfo->ulPeerIPAddr = pstPppInfo->ulPeerIPAddr;
    }

    /* 双栈新增DNS AND POOLNAME 备份 */
    pstCkpPppBkInfo->ulDNSAddr1         = pstPppInfo->ulDNSAddr1;
    pstCkpPppBkInfo->ulDNSAddr2         = pstPppInfo->ulDNSAddr2;
    pstCkpPppBkInfo->ulNowUTCInSec      = pstPppInfo->ulNowUTCInSec;
    pstCkpPppBkInfo->usPeerId           = pstPppInfo->usPeerId;
    pstCkpPppBkInfo->usCDBIndex         = pstPppInfo->usCDBIndex;
    pstCkpPppBkInfo->usVirtualDomainIdx = pstPppInfo->usVirtualDomainIdx;
    pstCkpPppBkInfo->usMtu              = pstPppInfo->usMtu;
    pstCkpPppBkInfo->usPcfIndex         = pstPppInfo->usPcfIndex;

    /* 如果是动态aaa，需要填充host，realm */
    if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
    {
        if (VOS_OK != Diam_AUTHGetDynAAAInfoByIndex(pstPppInfo->usPeerId,
                                                    pstCkpPppBkInfo->aucAAAHost,
                                                    pstCkpPppBkInfo->aucAAARealm,
                                                    &pstCkpPppBkInfo->usDynPeerId))
        {
            PPPC_WARNING_LOG1("PPP_BackupEncapUpdatePppInfo: Diam_AUTHGetDynAAAInfoByIndex Err!! dynaaacbindex[%u]",
                         pstPppInfo->usPeerId);
            PPP_DBG_ERR_CNT(PPP_PHERR_539);
            pstCkpPppBkInfo->usPeerId           = VOS_NULL_WORD;
            pstCkpPppBkInfo->ucAAAType          = VOS_NULL_BYTE;
            pstCkpPppBkInfo->usDynPeerId        = VOS_NULL_WORD;
        }
    }



    VOS_MemCpy(pstCkpPppBkInfo->usIpv6Addr, pstPppInfo->usIpv6Addr, sizeof(pstCkpPppBkInfo->usIpv6Addr));

    if (PPP_STATE_SUCCESS == pstCkpPppBkInfo->bPppStateFlgV6 )
    {
        VOS_MemCpy(pstCkpPppBkInfo->usPeerIPv6Addr,
                     pstPppInfo->usPeerIPv6Addr, sizeof(pstCkpPppBkInfo->usPeerIPv6Addr));
    }

    //VOS_Mem_Copy(pstCkpPppBkInfo->ucNAI, pstPppInfo->ucNAI, NAI_NAME_LEN + 1);

    pstCkpPppBkInfo->ucServiceOpt   = pstPppInfo->ucServiceOpt;
    pstCkpPppBkInfo->ucFSMFailType  = pstPppInfo->ucFSMFailType;
    pstCkpPppBkInfo->ucDmpuId       = pstPppInfo->ucDmpuId;
    pstCkpPppBkInfo->ucDpeId        = pstPppInfo->ucDpeId;
    pstCkpPppBkInfo->ucIpCapability = pstPppInfo->ucIpCapability;

    if(VOS_NULL_PTR != ((PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo)))
    {
        (VOID)VOS_MemCpy((VOID*)&(pstCkpPppBkInfo->stLcpGotOptions),
                                       (VOID*)&(((PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo))->stGotOptions),
                                       sizeof(PPP_LCP_OPTION_S));
        pstCkpPppBkInfo->ucLcpPktId  = ((PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo))->stFsm.ucPktId;
        pstCkpPppBkInfo->ucEchoState =
                 ((PPPLCPINFO_S*)(pstPppInfo->pstLcpInfo))->stFsm.ucEchoState;                                             /*r002*/
    }

    if(VOS_NULL_PTR != ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo)))
    {
        (VOID)VOS_MemCpy((VOID*)&(pstCkpPppBkInfo->stIpcpGotOptions),
                           (VOID*)&(((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->stGotOptions),
                           sizeof(PPP_IPCP_OPTION_S));
        pstCkpPppBkInfo->ucIpcpPktId =
                      ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->stFsm.ucPktId;
    }
    if(VOS_NULL_PTR != ((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo)))
    {
        (VOID)VOS_MemCpy((VOID*)&(pstCkpPppBkInfo->stIpv6cpGotOptions),
                           (VOID*)&(((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->stGotOptions),
                           sizeof(PPP_IPV6CP_OPTION_S));
        pstCkpPppBkInfo->ucIpcpPktId =
                      ((PPPIPV6CPINFO_S*)(pstPppInfo->pstIpV6cpInfo))->stFsm.ucPktId;
    }

    if (pstPppInfo->pstCcpInfo
        && (PPP_STATE_OPENED == ((PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo)->stFsm.ucState)
        && (1 == ((PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo)->stGotOptions.bStac_compress))
    {
        //pstCkpPppBkInfo->bStac = 1;
        pstCkpPppBkInfo->usStac_historys
            = ((PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo))->stGotOptions.usStac_historys;
    }

    if (pstPppInfo->pstCcpInfo
        && (PPP_STATE_OPENED == ((PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo)->stFsm.ucState)
        && (1 == ((PPP_CCP_INFO_S*)pstPppInfo->pstCcpInfo)->stGotOptions.bMppc_compress))
    {
        pstCkpPppBkInfo->bMppc = 1;
    }

    *pulEncapLen += ulEncapLen + CKP_BACKUP_TLV_SIZE;
    *ppucCurrent += ulEncapLen + CKP_BACKUP_TLV_SIZE;

    return;
}

/*****************************************************************************
 函 数 名  : PPP_BackupDecapUpdatePppInfo
 功能描述  : 备板解封装ppp的备份结构体信息，恢复到ppp控制块中
 被调函数  :
 调用函数  :
 输入参数  : SDB_PDSN_RP_CONTEXT_S *pstRpContext,
             PPPINFO_S *pstPppInfo, UCHAR *pucCurrent
 输出参数  :
 返 回 值  : VOID

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_BackupDecapUpdatePppInfo(SDB_PDSN_RP_CONTEXT_S *pstRpContext,
                                                PPPINFO_S *pstPppInfo, UCHAR *pucCurrent)
{
    CKP_BACKUP_PPPALLINFO_S *pstCkpPppBkInfo = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_105);
#endif
    pstCkpPppBkInfo = (CKP_BACKUP_PPPALLINFO_S *)pucCurrent;

    pstPppInfo->ulRPIndex       = pstRpContext->ulRpIndex;
    pstPppInfo->usTokenId       = pstRpContext->usTokenId;
    VOS_MemCpy(&(pstPppInfo->stIMSI), &(pstRpContext->stImsi), sizeof(IMSI_S));
    pstPppInfo->bIsAsync        = pstCkpPppBkInfo->bIsAsync;
    pstPppInfo->bSynAsyConvert  = pstCkpPppBkInfo->bSynAsyConvert;
    pstPppInfo->bLoopBacked     = pstCkpPppBkInfo->bLoopBacked;
    pstPppInfo->bLowerIsUp      = pstCkpPppBkInfo->bLowerIsUp;
    pstPppInfo->bIPReleaseFlg   = pstCkpPppBkInfo->bIPReleaseFlg;
    pstPppInfo->bIPTech         = pstCkpPppBkInfo->bIPTech;
    pstPppInfo->bAuthServer     = pstCkpPppBkInfo->bAuthServer;
    pstPppInfo->bAuthClient     = pstCkpPppBkInfo->bAuthClient;
    pstPppInfo->bReNego         = pstCkpPppBkInfo->bReNego;
    pstPppInfo->bReNegoV6       = pstCkpPppBkInfo->bReNegoV6;
    pstPppInfo->bPppStateFlg    = pstCkpPppBkInfo->bPppStateFlg;
    pstPppInfo->bPppMode        = pstCkpPppBkInfo->bPppMode;
    pstPppInfo->bPppClient      = pstCkpPppBkInfo->bPppClient;
    pstPppInfo->bPhaseFlag      = pstCkpPppBkInfo->bPhaseFlag;
    pstPppInfo->bPpcAAAFlag     = pstCkpPppBkInfo->bPpcAAAFlag;
    pstPppInfo->bPppSuccess     = pstCkpPppBkInfo->bPppSuccess;
    pstPppInfo->bAuthFlag       = pstCkpPppBkInfo->bAuthFlag;
    pstPppInfo->bIpcpSucFlag    = pstCkpPppBkInfo->bIpcpSucFlag;
    pstPppInfo->bPppStateFlgV6  = pstCkpPppBkInfo->bPppStateFlgV6;
    pstPppInfo->bRecvLcpMsgFlag = pstCkpPppBkInfo->bRecvLcpMsgFlag;
    //pstPppInfo->bBit328SoftPara = pstCkpPppBkInfo->bBit328SoftPara;
    pstPppInfo->bIpv6cpNoToPDN  = pstCkpPppBkInfo->bIpv6cpNoToPDN;
    pstPppInfo->bIpcpNoToPDN    = pstCkpPppBkInfo->bIpcpNoToPDN;
    pstPppInfo->bEhrpdUser      = pstCkpPppBkInfo->bEhrpdUser;
    pstPppInfo->ulRemoteAccm    = pstCkpPppBkInfo->ulRemoteAccm;
    pstPppInfo->ulLocalAccm     = pstCkpPppBkInfo->ulLocalAccm;
    pstPppInfo->bEAPAuthFlag    = pstCkpPppBkInfo->bEAPAuthFlag;

    pstPppInfo->bIPCPNakHandFlag= pstCkpPppBkInfo->bIPCPNakHandFlag;
    pstPppInfo->ulPcfIP         = pstCkpPppBkInfo->ulPcfIP;
    pstPppInfo->ulIPAddr        = pstCkpPppBkInfo->ulIPAddr;
    pstPppInfo->ulPeerIPAddr    = pstCkpPppBkInfo->ulPeerIPAddr;

    /* 双栈新增DNS AND POOLNAME 备份 */
    pstPppInfo->ulNowUTCInSec      = pstCkpPppBkInfo->ulNowUTCInSec;
    pstPppInfo->usPeerId           = pstCkpPppBkInfo->usPeerId;
    pstPppInfo->ucAAAType          = pstCkpPppBkInfo->ucAAAType;
    pstPppInfo->usCDBIndex         = pstCkpPppBkInfo->usCDBIndex;
    pstPppInfo->usVirtualDomainIdx = pstCkpPppBkInfo->usVirtualDomainIdx;
    pstPppInfo->usMtu              = pstCkpPppBkInfo->usMtu;
    pstPppInfo->usPcfIndex         = pstCkpPppBkInfo->usPcfIndex;

    VOS_MemCpy(pstPppInfo->usIpv6Addr, pstCkpPppBkInfo->usIpv6Addr, sizeof(pstPppInfo->usIpv6Addr));

    if (PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlgV6 )
    {
        VOS_MemCpy(pstPppInfo->usPeerIPv6Addr,
                     pstCkpPppBkInfo->usPeerIPv6Addr, sizeof(pstPppInfo->usPeerIPv6Addr));
    }

    VOS_MemCpy(pstPppInfo->ucNAI, pstRpContext->pucNAI, sizeof(pstPppInfo->ucNAI));

    pstPppInfo->ucServiceOpt   = pstCkpPppBkInfo->ucServiceOpt;
    pstPppInfo->ucFSMFailType  = pstCkpPppBkInfo->ucFSMFailType;
    pstPppInfo->ucDmpuId       = pstCkpPppBkInfo->ucDmpuId;
    pstPppInfo->ucDpeId        = pstCkpPppBkInfo->ucDpeId;
    pstPppInfo->ucIpCapability = pstCkpPppBkInfo->ucIpCapability;

    if (PPP_CB_STATE_USED == pstPppInfo->usState)   /* 表示更新PPP控制块 */
    {
        PPP_BackupUpdateData(pstPppInfo, pstCkpPppBkInfo);
    }
    else  /* 表示新建PPP控制块 */
    {
        (VOID)PPP_BackupCreateData(pstPppInfo, pstCkpPppBkInfo);
    }

    /* DNS必须在控制块后面填值,否则会有问题.如果在之前填,PPP_BackupCreateData里给赋值成初始值了 */
    pstPppInfo->ulDNSAddr1     = pstCkpPppBkInfo->ulDNSAddr1;
    pstPppInfo->ulDNSAddr2     = pstCkpPppBkInfo->ulDNSAddr2;

    PPP_BackupRestoreCompData(pstPppInfo, pstCkpPppBkInfo);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_BackupMasterCreUpdPppProc
 功能描述  : 主板ppp控制块备份处理函数，注册到ckp模块
             用户激活或者ppp自己的更新都会触发该函数
 被调函数  :
 调用函数  :
 输入参数  : VOS_UINT32 ulRpIndex, VOS_UINT32 ulOperType,
             UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen
 输出参数  :
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_BackupMasterCreUpdPppProc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulOperType,
                                                  UCHAR **ppucCurrent, VOS_UINT32 *pulEncapLen)
{
    VOS_UINT32 ulRet = 0;
    VOS_UINT32 ulPdnType = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_106);
#endif
    if (VOS_NULL_PTR == ppucCurrent || VOS_NULL_PTR == *ppucCurrent || VOS_NULL_PTR == pulEncapLen)
    {
        return VOS_ERR;
    }

    /* 查RP上下文 */
    ulRet = SDB_GetRpContextByIndex(ulRpIndex, (VOS_VOID **)&pstRpContext);
    if (VOS_OK != ulRet || VOS_NULL == pstRpContext)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_48);
#endif
        return VOS_ERR;
    }

    /* l2tp用户没有ppp控制块 */
    if (VOS_TRUE != pstRpContext->beHRPDMode)
    {
        (VOID)PDN_GetPdnType((VOS_UINT32)pstRpContext->ausPdnIndexArray[0], &ulPdnType);
        if (E_PDNTYPE_L2TP == ulPdnType)
        {
            return VOS_OK;
        }
    }

    /* 根据 RPIndex 获取 PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, pstRpContext->ulRpIndex);
    if(VOS_NULL_PTR == pstPppInfo)
    {
        /* 时序问题有可能出现这样的场景，直接返回OK即可 */
        PPPC_INFO_LOG1("\r\n PPP_BackupMasterCreUpdPppProc:get ppp cb fail %u", ulRpIndex);
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_49_GetPppNull);
#endif
        return VOS_OK;
    }

    /* 封装CKP_BACKUP_PPPALLINFO_S */
    PPP_BackupEncapUpdatePppInfo(pstPppInfo, ppucCurrent, pulEncapLen);
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_107);
#endif
    return VOS_OK;

}



/*****************************************************************************
 函 数 名  : PPP_BackupRebuildDynAAACB
 功能描述  : 备板重建dyn aaa cb
 被调函数  :
 调用函数  :
 输入参数  :
 输出参数  :
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2013年10月22日
    作    者   : wangyong 00138171
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_BackupRebuildDynAAACB(PPPINFO_S *pstPppInfo, CKP_BACKUP_PPPALLINFO_S *pstCkpPppBkInfo)
{
    VOS_UINT32 ulRet = 0;

    if ((pstCkpPppBkInfo->ucAAAType == pstPppInfo->ucAAAType)
        && (pstCkpPppBkInfo->usPeerId == pstPppInfo->usPeerId))
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_SUCC_178);
#endif
        return VOS_OK;
    }


    if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
    {
        /* 删除老的hash */
        ulRet = Diam_AUTHHostRemoveByAAACBIndex(pstPppInfo->usPeerId, pstPppInfo->ulRPIndex);
        if (ulRet != VOS_OK)
        {
#if 0
            CKP_DBG_INC_COUTER(CKP_ERR_95);
#endif
            return VOS_ERR;
        }

#if 0
        CKP_DBG_INC_COUTER(CKP_SUCC_179);
#endif
    }

    if (M_DIAMAUTH_DYNAAA_AAA == pstCkpPppBkInfo->ucAAAType)
    {
        ulRet = Diam_AUTHBackupRebuildDynAAACB(pstCkpPppBkInfo->usPeerId,
                                               pstCkpPppBkInfo->usDynPeerId,
                                               pstCkpPppBkInfo->aucAAAHost,
                                               pstCkpPppBkInfo->aucAAARealm);
        if (VOS_OK != ulRet)
        {
#if 0
            CKP_DBG_INC_COUTER(CKP_ERR_96);
#endif
            return VOS_ERR;
        }
#if 0
        CKP_DBG_INC_COUTER(CKP_SUCC_180);
#endif
    }

#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_181);
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_BackupSlaveCreUpdPppProc
 功能描述  : 备板ppp控制块备份处理函数，注册到ckp模块,完成创建更新ppp控制块等操作
 被调函数  :
 调用函数  :
 输入参数  : UCHAR *pucCurrent
 输出参数  :
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_BackupSlaveCreUpdPppProc(UCHAR *pucCurrent)
{
    VOS_UINT32 ulRet = 0;
    VOS_UINT32 ulRpIndex = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    CKP_BACKUP_MSGTLV_HEAD_S *pstMsgTlvHead = VOS_NULL_PTR;

#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_108);
#endif

    if (VOS_NULL_PTR == pucCurrent)
    {
        return VOS_ERR;
    }

    pstMsgTlvHead = (CKP_BACKUP_MSGTLV_HEAD_S*)pucCurrent;

    ulRpIndex = pstMsgTlvHead->ulSdbIndex;

    /* 首先查找rp上下文是否存在不存在则创建否则直接更新上下文 */
    ulRet = (VOS_UINT32)SDB_GetRpContextByIndex(ulRpIndex, (VOS_VOID **)&pstRpContext);
    if (VOS_OK != ulRet || VOS_NULL == pstRpContext)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_50);
#endif
        return VOS_ERR;
    }

    if ( ulRpIndex > PPP_MAX_USER_NUM )
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_51);
#endif
        PPPC_WARNING_LOG1("\r\n PPP_BackupSlaveCreUpdPppProc:rp index err %u", ulRpIndex);
        return VOS_ERR;
    }

    /* 根据 RPIndex 获取 PPP控制块 */
    pstPppInfo = &g_astPppPool[ulRpIndex];

    if (PPP_CB_STATE_USED != pstPppInfo->usState)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_SUCC_109);
#endif
        PPP_MemSet(pstPppInfo, 0, sizeof(PPPINFO_S));
        pstPppInfo->ucAAAType = VOS_NULL_BYTE;
        pstPppInfo->usPeerId = VOS_NULL_WORD;
    }

    ulRet = PPP_BackupRebuildDynAAACB(pstPppInfo, (CKP_BACKUP_PPPALLINFO_S *)pstMsgTlvHead->ucValue);
    if (ulRet != VOS_OK)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_97);
#endif
        return VOS_ERR;
    }

    /* 解封装CKP_BACKUP_PPPALLINFO_S */
    PPP_BackupDecapUpdatePppInfo(pstRpContext, pstPppInfo, pstMsgTlvHead->ucValue);



    pstPppInfo->usState = PPP_CB_STATE_USED;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_BackupSlaveDelResource
 功能描述  : 备板删除ppp控制块资源
 被调函数  :
 调用函数  :
 输入参数  : VOS_UINT32 ulRpIndex
 输出参数  :
 返 回 值  : VOID

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_BackupSlaveDelResource(VOS_UINT32 ulRpIndex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_110);
#endif
    /* 根据 RPIndex 获取 PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex);
    if(VOS_NULL_PTR == pstPppInfo)
    {
        return;
    }

    (VOID)PPP_ClearCB(pstPppInfo);

    PPP_MemSet(pstPppInfo, 0, sizeof(PPPINFO_S));

    return;
}

/*****************************************************************************
 函 数 名  : PPP_BackupSmoothPppInfo
 功能描述  : 平滑时完成ppp控制块的平滑处理
 被调函数  :
 调用函数  :
 输入参数  : SDB_PDSN_RP_CONTEXT_S *pstRpContext
 输出参数  :
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPP_BackupSmoothPppInfo(SDB_PDSN_RP_CONTEXT_S *pstRpContext)
{
    VOS_UINT32 ulPdnType = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_116);
#endif
    /* l2tp用户没有ppp控制块直接返回成功 */
    if (VOS_TRUE != pstRpContext->beHRPDMode)
    {
        (VOID)PDN_GetPdnType((VOS_UINT32)pstRpContext->ausPdnIndexArray[0], &ulPdnType);
        if (E_PDNTYPE_L2TP == ulPdnType)
        {
#if 0
            CKP_DBG_INC_COUTER(CKP_SUCC_117);
#endif
            return VOS_OK;
        }
    }

    /* 根据 RPIndex 获取 PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, pstRpContext->ulRpIndex);
    if(VOS_NULL_PTR == pstPppInfo)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_262_RP_SMOOTH_PPP_NOT_EXSIT);
#endif
        PPPC_WARNING_LOG1("\r\n PPP_BackupSmoothPppInfo: ppp not used %u",
                     pstRpContext->ulRpIndex);
        return VOS_ERR;
    }

    /* 比较RP索引是否一致 */
    if (pstPppInfo->ulRPIndex != pstRpContext->ulRpIndex)
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_263_RP_SMOOTH_PPP_RP_NOT_SAME);
#endif
        PPPC_WARNING_LOG2("\r\n PPP_BackupSmoothPppInfo: rp not equal %u,%u",
                     pstPppInfo->ulRPIndex, pstRpContext->ulRpIndex);
        return VOS_ERR;
    }

    /* 比较IMSI是否一致 */
    if (0 != VOS_MemCmp(&pstRpContext->stImsi, &pstPppInfo->stIMSI, sizeof(A11_IMSI_S)))
    {
#if 0
        CKP_DBG_INC_COUTER(CKP_ERR_264_RP_SMOOTH_PPP_IMSI_NOT_SAME);
#endif
        PPPC_WARNING_LOG("\r\n PPP_BackupSmoothPppInfo: imsi not equal");
        return VOS_ERR;
    }

    /* 平滑压缩用户数 */
    if ((VOS_NULL_PTR != pstPppInfo->pstIpcpInfo)
        && (1 == ((PPPIPCPINFO_S*)(pstPppInfo->pstIpcpInfo))->stGotOptions.neg_vj))
    {
        PPP_CompUserNumAdd((PPPINFO_S*)pstPppInfo, PPP_USERSTAT_VJ);
    }

    if ((VOS_NULL_PTR != pstPppInfo->pstCcpInfo)
        &&(PPPCOMP_MPPC == ((PPP_CCP_INFO_S*)(pstPppInfo->pstCcpInfo))->ucPppCompType))
    {
        PPP_CompUserNumAdd((PPPINFO_S*)pstPppInfo, PPP_USERSTAT_MPPC);
    }

#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_163);
#endif

    return VOS_OK;
}

VOID PPP_BackupSmoothSubBoardDown()
{
#ifdef __VXWORKS_PLATFORM__
    PPP_SubBoardDown();
#endif
    return;
}
/*****************************************************************************
 函 数 名  : PPP_LI_SetAuInfo
 功能描述  : 设置监听上报时的ppp鉴权信息
 被调函数  :
 调用函数  :
 输入参数  : LI_CDMA2000_PDPINFO_S *pstLiContextInfo
 输出参数  :
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : z00136627
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_LI_SetAuInfo(LI_CDMA2000_PDPINFO_S *pstLiContextInfo, VOS_UINT32 ulRpindex)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPPAPINFO_S *pstPapInfo   = VOS_NULL_PTR;
    PPPCHAPINFO_S *pstChapInfo = VOS_NULL_PTR;

#if 0
    CKP_DBG_INC_COUTER(CKP_SUCC_118);
#endif

    if (VOS_NULL_PTR == pstLiContextInfo)
    {
        return ;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpindex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG1(
                     "\r\n PPP_LI_SetAuInfo: Find PPP CB is wrong, ulRpIndex:%u", ulRpindex);
        return ;
    }

    pstPapInfo = (PPPPAPINFO_S*)pstPppInfo->pstPapInfo;

    pstChapInfo = (PPPCHAPINFO_S*)pstPppInfo->pstChapInfo;

    /* neither pap nor chap  consider whether return err !!!!!!!!!!!!!!!!!!!!!*/
    if ((!pstPapInfo) && (!pstChapInfo))
    {
        PPPC_WARNING_LOG("\r\nPPP PPP_LI_SetAuInfo : auth info err or no auth struct!");
        return ;
    }

    pstLiContextInfo->ucAuFlag = 1;

    if (pstPapInfo)/* if it is pap */
    {
        pstLiContextInfo->ucAuType = AUTH_PAP_PPP;
        pstLiContextInfo->ucSubPasswordLen = (UCHAR)VOS_StrLen((CHAR *)pstPapInfo->szPapUsrPwd);
        VOS_MemCpy((VOID *)pstLiContextInfo->szSubPassword, (VOID *) pstPapInfo->szPapUsrPwd,
                     (VOS_UINT32 )pstLiContextInfo->ucSubPasswordLen);
    }
    else if (pstChapInfo)/* if it is chap */
    {
        pstLiContextInfo->ucAuType = AUTH_CHAP_PPP;
        pstLiContextInfo->ucChapChallengeLen = pstChapInfo->ucChalLen;
        VOS_MemCpy((VOID *)pstLiContextInfo->szChapChallenge, (VOID *) pstChapInfo->szChallenge,
                     (VOS_UINT32 )pstChapInfo->ucChalLen);
    }

    return ;
}

/*lint +e572*/
/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
