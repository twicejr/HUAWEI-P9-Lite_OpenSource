/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MmAuth.c
  Author       : s46746
  Version      : V200R001
  Date         : 2005-08-16
  Description  : 该C文件给出了MM模块AuthProc子模块的实现
  Function List:
        1) MM_AuthProc
        2) MM_HandleGsmAuthenFail
        3) MM_RcvGsmAuthenticationCnf
        4) MM_RcvSimAuthCnf
        7) MM_SimAuth
        8) MM_SndGsmAuthenReq
        9) MM_UsimGsmAuth

  History      :
  1. Date:2005-04-19
     Author: ---
     Modification:Create
  2. s46746 2006-02-09 根据问题单A32D03324修改
  3. s46746 2006-03-07 根据问题单A32D02191修改
  4.日    期   : 2006年12月5日
    作    者   : s46746
    修改内容   : 问题单号:A32D07740
************************************************************************/

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
/*****************************************************************************
 Prototype      : MM_AuthProc
 Description    : 新增鉴权过程入口，对 SIM 卡和 USIM GSM 鉴权进行处理
 Input          :
 Output         :
 Return Value   : 无
 Calls          :

 Called By      :
 History        : ---
 1.Date        : 2005-08-16
   Author      : s46746
   Modification: Created function
 2.日    期   : 2006年12月5日
   作    者   : s46746
   修改内容   : 问题单号:A32D07740
 3.日    期   : 2010年11月19日
   作    者   : s46746
   修改内容   : 问题单号:DTS2010111604811,鉴权过程中接收到相同鉴权消息处理
 4.日    期   : 2011年7月25日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整

 5.日    期   : 2014年10月20日
   作    者   : w00167002
   修改内容   : DTS2014102000868:在鉴权成功后才更新CKSN
  6.日    期   : 2016年1月20日
    作    者   : c00318887
    修改内容   : DTS2015123110917: usim卡在GSM下做2G鉴权后，csfb到3G下鉴权错误
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

/*****************************************************************************
 Prototype      : MM_SimAuth
 Description    : SIM卡的对鉴权请求消息的处理
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      : AuthProc
 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
 2.日    期   : 2013年10月31日
   作    者   : l65478
   修改内容   : DTS2013103002259:SIM卡W下收到鉴权MM返回失败
*****************************************************************************/
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

/*****************************************************************************
 Prototype      : MM_SndGsmAuthenReq
 Description    : 向网络侧发送 GSM 鉴权请求
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-09-06
    Author      : s46746
    Modification: Created function
  2.日    期  : 2006年11月25日
    作    者  : luojian id:60022475
    修改内容  : 问题单号:A32D06583
  3.日    期  : 2012年12月26日
    作    者  : 张鹏 id:00214637
    修改内容  : USIM对外接口函数变更的处理 ，Client ID 到 PID的转换处理。
  4.日    期  : 2013年6月4日
    作    者  : w00242748
    修改内容  : USIMM_AuthReq修改为NAS_USIMMAPI_AuthReq，后者会根据当前模式自动
                适配
  5.日    期  : 2013年11月30日
    作    者  : l65478
    修改内容  : DTS2013121919477,连续收到网络的两条鉴权消息,网络把第一条消息的响应作为第二条请求的响应,导致鉴权失败

  6.日    期  : 2014年1月3日
    作    者  : s00261364
    修改内容  : mm模块Converity告警消除
*****************************************************************************/
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

/*****************************************************************************
 Prototype      : MM_RcvGsmAuthenticationCnf
 Description    : 接收到 USIM/SIM 卡对 GSM 类型鉴权请求的返回消息
 Input          : pMsg 指向接收到 USIM/SIM 卡的鉴权结果消息
 Output         :
 Return Value   : MM_TRUE  正确的鉴权回应
                  MM_FALSE 错误的鉴权回应
 Calls          :
 Called By      :
 History        : ---
 1.Date        : 2005-09-06
   Author      : s46746
   Modification: Created function
 2.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期  : 2013年7月22日
   作    者  : y00245242
   修改内容  : VoIP开发，适配新的USIM接口
 4.日    期   : 2014年4月175日
   作    者   : s00246516
   修改内容   : DTS2014041700472:使用2G SIM卡，PAD形态上出现鉴权被网络拒绝
 5.日    期   : 2014年10月20日
   作    者   : w00167002
   修改内容   : DTS2014102000868:在鉴权成功后才更新CKSN
*****************************************************************************/
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
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-24, begin */
    Mm_Com_UsimAuthenticationCnfChgFormat((USIMM_AUTHENTICATION_CNF_STRU *)pMsg);
    /* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-24, end */

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
