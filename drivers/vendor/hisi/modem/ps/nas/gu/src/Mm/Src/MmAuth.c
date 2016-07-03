

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MM_Inc.h"
#include "MmAuth.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_AUTH_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/

/*****************************************************************************
   3 函数实现
*****************************************************************************/

VOS_VOID MM_GsmAuthProc()
{

    /* 鉴权回应消息结构 */
    MM_MSG_AUTHENTICATION_RSP_STRU      stMsg;

    /* 将鉴权请求参数(Rand,Cksn)保存到全局变量中 */
    PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
               g_MmMsgAuthReq.MmIeRAND.aucRandValue,
               16 * sizeof(VOS_UINT8)
               );


    /* 初始化 Msg 变量 */
    PS_MEM_SET(&stMsg, 0, sizeof(MM_MSG_AUTHENTICATION_RSP_STRU));

    /* 旧的 Rand 有效 */
    if (MM_AUTHEN_RAND_PRESENT == g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg)
    {
        if ((MM_FALSE == Mm_ComRandJudge()))  /* 当前 RAND 与旧的相同 */
        {
            NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_NORMAL,
                    "MM_AuthProc: NORMAL: Rand same as the rand of last auth.");

            /* 判断前两次 RAND 是否相同 */
            if (MM_AUTHEN_RAND_DIFFER == g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat)
            {
                g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat  = MM_AUTHEN_RAND_REPEAT;
            }
            /* RES 或 SRES 存在,而且本次鉴权类型与上次相同 */
            else if ((MM_AUTHEN_RES_PRESENT == g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg)
                    && (AUTHENTICATION_REQ_GSM_CHALLENGE == g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType))
            {
                /* 直接将上次的 SRES 发送到网络侧 */
                PS_MEM_CPY(stMsg.MmIeAuthRspPara.aucSgnfcntRES,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 4);

                NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);

                /* 发送AUTHENTICATION RESPONSE */
                Mm_ComMsgAuthRspSnd(&stMsg);

                return;
            }
            else
            {

            }
        }
        else
        {
            /* 本次 RAND 与上次不同，设置相应标志 */
            g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat      = MM_AUTHEN_RAND_REPEAT;
        }
    }

    /* 保存当前 RAND */
    PS_MEM_CPY(
                g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand,
                g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                16 * sizeof(VOS_UINT8)
                );

    /* 设置 RAND 存在标识并清除RES存在标志 */
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg  = MM_AUTHEN_RAND_PRESENT;
    g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg   = MM_AUTHEN_RES_ABSENT;
    g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg  = MM_AUTHEN_RES_ABSENT;

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        
        /* 调用函数 MM_UsimGsmAuth 进行处理 */
        MM_UsimGsmAuth();
        
        if (VOS_TRUE == NAS_MML_IsNeedSetUsimDoneGsmAuthFlg())
        {
            NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_NORMAL,
                    "MM_AuthProc: SetUsimDoneGsmCsAuthFlg to ture");
        
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_TRUE);
        }
    }
    else if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {

        /* 调用函数 MM_SimAuth 进行处理 */
        MM_SimAuth();
    }
    else /* 异常情况, 鉴权请求被丢弃 */
    {
        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_AuthProc: ERROR: Sim type is unexpeted!");
    }

    return;
}

/*****************************************************************************
 Prototype      : MM_UsimGsmAuth
 Description    : USIM卡在2G网络下对 GSM 鉴权请求消息的处理
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_UsimGsmAuth()
{

    /* 发送 GSM 鉴权请求 */
    MM_SndGsmAuthenReq();

    return;
}


VOS_VOID MM_SimAuth()
{
    /* 24.008 If a SIM is inserted in the MS, the MS shall ignore
       the Authentication Parameter AUTN IE if included in the
       AUTHENTICATION REQUEST message and shall proceed as in
       case of a GSM authentication challenge */
    /* 发送 GSM 鉴权请求 */
    MM_SndGsmAuthenReq();

    return;
}


VOS_VOID MM_SndGsmAuthenReq()
{
    VOS_UINT8        ucTempOpId = 0;

    /* 设置全局标志,表示等待接收 USIM/SIM 卡鉴权回应 */
    g_MmGlobalInfo.ucRcvAgentFlg |= MM_RCV_AUTH_CNF_FLG;


    ucTempOpId = g_MmGlobalInfo.AuthenCtrlInfo.ucOpId;

    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId++;



    /* 向 SIM/USIM 卡发送 GSM 类型鉴权请求 */
    NAS_USIMMAPI_AuthReq(WUEPS_PID_MM,
                    AUTHENTICATION_REQ_GSM_CHALLENGE,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                    VOS_NULL,
                    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId
                    );

    NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_NORMAL,
                    "MM_SndGsmAuthenReq: NORMAL: Send GSM CHALLENGE Auth Req!");

    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_GSM_CHALLENGE;

    /* 启动保护 TIMER */
    Mm_TimerStart(MM_TIMER_PROTECT_AGENT);

    return;
}

/*****************************************************************************
 Prototype      : MM_RcvSimAuthCnf
 Description    : 接收到 USIM/SIM 卡对鉴权请求的返回消息
 Input          : Msg 指向接收到 USIM/SIM 卡的鉴权结果消息
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_RcvSimAuthCnf(VOS_VOID* pMsg)
{
    /* 接收 USIM/SIM 发送的鉴权回应 */
    if (MM_TRUE == MM_RcvGsmAuthenticationCnf(pMsg)) /* 接收鉴权回应参数 */
    {
        /* 停止保护定时器 */
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

        /* 对鉴权结果处理 */
        if (AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst)
        {
            /* 鉴权成功处理 */
            Mm_ComAuthenRcvUsimCnfSuccess();
        }
        else
        {
            /* 鉴权失败处理 */
            MM_HandleGsmAuthenFail();

        }
    }
    else /* 异常情况处理 */
    {
        MM_HandleGsmAuthenFail();

        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_RcvSimAuthCnf: ERROR: Rcv Gsm Auth cnf error!");
    }

    return;
}


VOS_UINT8 MM_RcvGsmAuthenticationCnf(VOS_VOID* pMsg)
{
    /* 清除鉴权前置的全局标志 ucRcvAgentFlg */
    if (MM_RCV_AUTH_CNF_FLG
        != ( MM_RCV_AUTH_CNF_FLG & g_MmGlobalInfo.ucRcvAgentFlg))
    {
        /* 返回上层处理 */
        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmAuthenticationCnf: ERROR: Auth cnf is unexpected!");

        return MM_FALSE;
    }
    else
    {
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    }

    /* 将 USIM/SIM 的鉴权消息写入全局变量 g_AgentUsimAuthCnf 中 */
    Mm_Com_UsimAuthenticationCnfChgFormat((USIMM_AUTHENTICATION_CNF_STRU *)pMsg);

    /* 处理 g_AgentUsimAuthCnf 中的鉴权结果 */
    if (AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst) /* 鉴权成功 */
    {
        /* 保存 SRES 参数 */
        PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucRes,
                    g_AgentUsimAuthCnf.aucResponse, 4);

        /* 设置 SRES 存在标志 */
        g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg = MM_AUTHEN_RES_PRESENT;

        g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = 0;

        /* g_AgentUsimAuthCnf.ucKcLength 为零 */
        if (MM_CONST_NUM_0 == g_AgentUsimAuthCnf.ucKcLength)
        {
            /* 异常情况，返回上层处理 */
            NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmAuthenticationCnf: ERROR: Sim didn't return Kc at GSM Auth!");

            return MM_FALSE;
        }
        else
        {
            /* 将 KC 保存到全局变量 */
            NAS_MML_SetSimCsSecurityGsmKc(g_AgentUsimAuthCnf.aucKc);
        }

        /* 调用函数 NAS_MML_SecContext2GTO3G 求得 IK、CK */
        NAS_MML_SecContext2GTO3G(g_AgentUsimAuthCnf.aucIntegrityKey, g_AgentUsimAuthCnf.aucCipheringKey,
                                 g_AgentUsimAuthCnf.aucKc);

        /* 将 IK、CK 存储到全局变量中 */
        NAS_MML_SetSimCsSecurityUmtsCk(g_AgentUsimAuthCnf.aucCipheringKey);
        NAS_MML_SetSimCsSecurityUmtsIk(g_AgentUsimAuthCnf.aucIntegrityKey);

        NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);

    }

    return MM_TRUE;
}

/*****************************************************************************
 Prototype      : MM_HandleGsmAuthenFail
 Description    : USIM/SIM 卡 GSM 类型鉴权失败的处理
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-09-06
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_HandleGsmAuthenFail()
{

    /*MM_MSG_AUTHENTICATION_FAIL_STRU     stMsg;

    VOS_MemSet(&stMsg, 0, sizeof(MM_MSG_AUTHENTICATION_FAIL_STRU));

    stMsg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR;

    Mm_ComMsgAuthFailSnd(&stMsg);*/     /* 发送 AUTHENTICATION FAILURE 消息 */

    NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_WARNING,
                    "MM_HandleGsmAuthenFail: WARNING: Gsm Auth Fail!");

    return;
}



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
