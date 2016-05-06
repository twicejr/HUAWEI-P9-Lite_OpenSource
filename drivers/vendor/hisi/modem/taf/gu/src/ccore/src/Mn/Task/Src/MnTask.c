/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnTask.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2008年1月10日
  最近修改   : 2008年1月10日
  功能描述   : TAF FID入口，执行FID初始化和消息分发操作
  函数列表   :
  修改历史   :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年10月10日
    作    者   : f62575
    修改内容   : 问题单号：AT2D06152（AT2D06151）, USIMM优化合入后，SMSP文件相关读写操作失败
  3.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : AT2D16304, STK PP DOWN功能完善和SMS相关的(U)SIM文件REFRESH
  4.日    期   : 2010年2月21日
    作    者   : f62575
    修改内容   : 问题单号: AT2D16941,短信功能任意点回放

  5.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级
******************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "product_config.h"
#include "vos.h"
#include "Taf_Tafm_Remote.h"
#include "UsimPsInterface.h"
#include "Ssa_Define.h"
#include "MnCall.h"
#include "Taf_Aps.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
#include "TafMmcInterface.h"
#include "MnMsgExt.h"
#include "UsimPsInterface.h"
#include "MnComm.h"
#include "siapppih.h"
#include "MnCallTimer.h"
#include "RabmTafInterface.h"
#include "MmaAppLocal.h"
/* Added by L60609 for AT Project，2011-10-05,  Begin*/
#include "TafDrvAgentMain.h"
/* Added by L60609 for AT Project，2011-10-05,  End*/
#include "MnCallReqProc.h"
#include "TafApsMain.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"

#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlInterface.h"

#include "TafMtaMain.h"

#include "TafSdcCtx.h"
#include "TafSpmMain.h"
#include "MnMsgSmCommProc.h"

#include "NasUsimmApi.h"

 /* Added by l00208543 for V9R1 STK升级, 2013-07-10, begin */
#include "TafCbaProcUsim.h"
 /* Added by l00208543 for V9R1 STK升级, 2013-07-10, end */

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-05, begin */
#include "MnCallImsaProc.h"
#include "TafMntn.h"
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-10-05, end */

#include "TafCsCallMain.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_taf_pif.h"
#include "TafXCallMain.h"
#include "TafXpdsMain.h"
#endif


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

extern VOS_VOID R_ITF_InitFlowCtrl(VOS_VOID);


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_TASK_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

VOS_VOID MN_MSG_RecurDataRestore(
    struct MsgCB                        *pstAppMsg
);

extern VOS_UINT32 TAF_XSMS_PidInit(enum VOS_INIT_PHASE_DEFINE  ip);
extern VOS_VOID TAF_XSMS_PidMsgProc(MsgBlock* pstMsg);

VOS_UINT8                               g_ucMnOmConnectFlg       = VOS_FALSE;   /* UE与PC工具的连接标志, VOS_TRUE: 已连接; VOS_FALSE: 未连接 */
VOS_UINT8                               g_ucMnOmPcRecurEnableFlg = VOS_FALSE;   /* PC工具配置的发送NAS PC回放消息的使能标志 */
/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
MN_STK_MSG_FUNC_MAP_STRU                g_astTafStkMsgFuncMap[] =
{
    {STK_MSG_SEND_REQ,         MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT, MN_MSG_ProcAppSend},
    {STK_CALL_START_DTMF_REQ,  MN_CALL_APP_START_DTMF_REQ,        TAF_CALL_RcvStartDtmfReq},
    {STK_CALL_STOP_DTMF_REQ,   MN_CALL_APP_STOP_DTMF_REQ,         TAF_CALL_RcvStopDtmfReq},
    {STK_CALL_CALLORIG_REQ,    MN_CALL_APP_ORIG_REQ,              MN_CALL_StkCallOrigReqProc},
    {STK_CALL_SUPS_CMD_REQ,    MN_CALL_APP_SUPS_CMD_REQ,          MN_CALL_CallSupsCmdReqProc},
    {STK_SS_REGISTERSS_REQ,    TAF_MSG_REGISTERSS_MSG,            MN_SndAppMsgToSs},
    {STK_SS_ERASESS_REQ,       TAF_MSG_ERASESS_MSG,               MN_SndAppMsgToSs},
    {STK_SS_ACTIVATESS_REQ,    TAF_MSG_ACTIVATESS_MSG,            MN_SndAppMsgToSs},
    {STK_SS_DEACTIVATESS_REQ,  TAF_MSG_DEACTIVATESS_MSG,          MN_SndAppMsgToSs},
    {STK_SS_INTERROGATESS_REQ, TAF_MSG_INTERROGATESS_MSG,         MN_SndAppMsgToSs},
    {STK_SS_REGPWD_REQ,        TAF_MSG_REGPWD_MSG,                MN_SndAppMsgToSs},
    {STK_SS_USSD_REQ,          TAF_MSG_PROCESS_USS_MSG,           MN_SndAppMsgToSs},
    {SI_STK_ENVELOPE_CNF,    SI_STK_ENVELOPE_CNF,              TAF_ProcStkEnvelopeCnf}
};
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
   2 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_Init
 功能描述  : 初始化TAF的各个模块
 输入参数  : 略
 返 回 值  : 略
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年4月20日
    作    者   : z00161729
    修改内容   : 修改问题单AT2D18405
  3.日    期   : 2011年12月2日
    作    者   : L00171473
    修改内容   : 补上流控初始化For DTS2011120201716
  4.日    期   : 2012年12月26日
    作    者   : s46746
    修改内容   : DSDA GUNAS C CORE项目，增加SDC初始化
  5.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:增加SPM的初始化
  6.日    期   : 2013年6月17日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
*****************************************************************************/
VOS_UINT32  MN_Init(enum VOS_INIT_PHASE_DEFINE  ip)
{
    TAF_SDC_CTX_STRU                    *pstSdcCtx = VOS_NULL_PTR;

    switch( ip )
    {
    case VOS_IP_INITIAL:

        NAS_PIHAPI_RegCardRefreshIndMsg(WUEPS_PID_TAF);

        pstSdcCtx = TAF_SDC_GetSdcCtx();
        TAF_SDC_InitCtx(TAF_SDC_INIT_CTX_STARTUP, pstSdcCtx);

        /* 初始化CCA */
        MN_CALL_Init(MN_CALL_POWER_STATE_ON);

        /* 初始化SMA */
        MN_MSG_Init();

        /* 初始化APS */
        Aps_Init();

        TAF_SPM_Init();

        /* 初始化SSA */
        SSA_Init();
        /* 初始化GNA */

        /* 已经与lijun,hefeng,xiamiaofang确认，可以删除流控初始化 */

        TAF_CSCALL_Init(TAF_CSCALL_INIT_TYPE_STARTUP);

        break;

    default:
        break;
    }

    return VOS_OK;
}

VOS_VOID Taf_ProcCallCtrlAllowNoModification(struct MsgCB * pstMsg)
{
/*
    switch 操作类型
        case 呼叫:
        if (找到处于CCA_CALL_CTRL_PROCEEDING状态的呼叫实体)
        {
            将Call Control状态更新为CCA_CALL_CTRL_END
            调用Cca_CallOrigReqProc
        }
        break;

        #if 0
        case 补充业务:
        暂略
        break;

        case 数传:
        暂略
        break;
        #endif

        default:
        break;
*/
}


VOS_VOID Taf_ProcCallCtrlNotAllow(struct MsgCB * pstMsg)
{
/*
    switch 操作类型
        case 呼叫:
            清除对应的CCA状态机:
            上报事件，错误值为TAF_ERR_CALL_CONTROL_REJECTED
            break;

        case 补充业务:
        case USSD业务:
            清除对应的SSA状态机
            上报事件，错误值为TAF_ERR_CALL_CONTROL_REJECTED
            break;

        case 数传:
            清除对应的APS状态机
            上报事件，错误值为TAF_ERR_CALL_CONTROL_REJECTED
            break;

        default:
            break;

*/

}

VOS_VOID Taf_ProcCallCtrlAllowWithModification(struct MsgCB * pstMsg)
{

/*
    调用数据转换函数

    switch 操作类型
        case 呼叫:
            if (找到处于CCA_CALL_CTRL_PROCEEDING状态的呼叫实体)
            {
                更新对应实体的状态信息
                调用Cca_CallOrigReqProc
            }
            break;

        case 补充业务:
        case USSD业务:
            if (之前的操作是并不是SSA发起的Call control操作)
            {
                清空对应发起操作实体的状态(CCA或者APS)
            }

            调用公共处理函数(MMI字串解析函数，该函数的实现方式待定,
                             等CCA编码完成后，再行确定)
            调用SSA的接口(此处还需要依据新版的SSA的实现方式来确定)
            break;

        case 数传:
            调用APS的PDP激活接口(此处还需要依据新版的APS的实现方式来确定)
            break;

        default:
            break;

    上报事件，告知应用由于call control的原因，呼叫发生了改变

*/
}

/*****************************************************************************
 函 数 名  : Taf_ProcSimaMsg
 功能描述  : 处理来自Sima的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  Taf_ProcSimaMsg (struct MsgCB * pstMsg)
{
/*
    switch (命令类型)
        #ifdef hw_feature_call_control
        case 类型为call control:
        {
            switch (result)
            {
                case 允许无修改:
                    调用Taf_ProcCallCtrlAllowNoModification
                    break;

                case 不允许:
                    调用Taf_ProcCallCtrlNotAllow
                    break;

                case 允许但修改:
                    调用Taf_ProcCallCtrlAllowWithModification
                    break;

                default:
                    break;
            }
        }
        break;
        #endif

        default:
        break;

*/
}

/*****************************************************************************
 函 数 名  : MN_ProcTimerMsg
 功能描述  : 处理定时器消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2008年1月10日
   作    者   : 丁庆 49431
   修改内容   : 新生成函数
 2.日    期   : 2011年12月19日
   作    者   : h44270
   修改内容   : modified by PS Project，修改消息入口函数
 3.日    期   : 2014年11月17日
   作    者   : w00176964
   修改内容   : CDMA 1x项目迭代5修改
*****************************************************************************/
VOS_VOID  MN_ProcTimerMsg (struct MsgCB * pstMsg)
{
    REL_TIMER_MSG * pstTmrMsg = (REL_TIMER_MSG *)pstMsg;

    switch (pstTmrMsg->ulName & MN_TIMER_CLASS_MASK)
    {
    case MN_TIMER_CLASS_CCA:
    case MN_TIMER_CLASS_XCALL:
        TAF_CSCALL_ProcTimerOutMsg((REL_TIMER_MSG *)pstMsg);
        break;

    case MN_TIMER_CLASS_MSG:
        /* 调用SMA的定时器消息处理函数 */
        MN_MSG_ProcTimeoutMsg((REL_TIMER_MSG *)pstMsg);
        break;

    case MN_TIMER_CLASS_SSA:
        /* 调用SSA的定时器消息处理函数 */
        break;

    case MN_TIMER_CLASS_MMA:
        /* 调用MMA的定时器消息处理函数 */
        break;

    case MN_TIMER_CLASS_APS:
        TAF_APS_ProcMsg(pstMsg);
        break;

    default:
        MN_ERR_LOG("MN_ProcTimerMsg: Unknown timer class.");
        break;
    }
}

/* 删除原 MN_GetUsimMsgClient接口函数 */

/*****************************************************************************
 函 数 名  : MN_GetUsimMsgServerType
 功能描述  : 从USIM过来的消息中抽取业务类型
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期  : 2012年12月26日
    作    者  : 张鹏 id:00214637
    修改内容  : 参考 MN_GetUsimMsgClient 重写，提取消息业务类型
  2.日    期  : 2013年5月15日
    作    者  : w00176964
    修改内容  : SS FDN&Call Control项目:fdn回复结果统一使用client ID,后续CALL/MSG的
                FDN检查放到SPM中可以统一在SPM中处理
  3.日    期   : 2013年6月5日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  4.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改
  5.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_UINT32 MN_GetUsimMsgServerType(struct MsgCB * pstMsg)
{
    VOS_UINT32                          ulServerType;
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope;

    /*从USIM过来的消息中抽取业务类型,其中FDN IND消息需要 MSG 和 CALL模块处理*/
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        /* 修改了FDN检查回复的结构,SS使用client ID,CALL/MSG需要使用client ID判断 */
        case SI_PB_EVENT_FDNCHECK_CNF:
            ulServerType  = TAF_SERVICE_TYPE_UNASSIGNED;
            break;

        case USIMM_READFILE_CNF:
            ulServerType  = TAF_SERVICE_TYPE_UNASSIGNED;
            break;

        case SI_STK_ENVELOPE_CNF:
            pstEnvelope = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
            if (SI_STK_ENVELOPE_CALLCRTL == pstEnvelope->enEnvelopeType)
            {
                ulServerType  = TAF_SERVICE_TYPE_CALL;
            }
            else
            {
                ulServerType  = TAF_SERVICE_TYPE_MSG;
            }
            break;
        default:
            ulServerType  = TAF_SERVICE_TYPE_MSG;
            break;
    }
    return ulServerType;
}

/*****************************************************************************
 函 数 名  : MN_ProcUsimMsg
 功能描述  : 处理来自USIM的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2009年12月16日
    作    者   : f62575
    修改内容   : 增加对PS_USIM_REFRESH_FILE_IND事件 的处理
  3.日    期   : 2011年6月24日
    作    者   : 傅映君/f62575
    修改内容   : DTS2011062201273 MO SMS CONTROL
  4.日    期   : 2012年02月24日
    作    者   : 傅映君/f62575
    修改内容   : C50_IPC Project    为适配FDN业务USIM消息处理过程按客户分类处理
  5.日    期   : 2012年12月26日
    作    者   : 张鹏 id:00214637
    修改内容   : USIM 上报消息的分发处理
  6.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改
*****************************************************************************/
VOS_VOID  MN_ProcUsimMsg (struct MsgCB * pstMsg)
{
    VOS_UINT32                          ulServerType;

    ulServerType = MN_GetUsimMsgServerType(pstMsg);

    /* 根据ulClient将USIM消息分发到各业务处理，目前有两个业务处理模块 */
    switch(ulServerType)
    {
        case TAF_SERVICE_TYPE_MSG:
            MN_MSG_DispatchUsimMsg(pstMsg);
            break;

        case TAF_SERVICE_TYPE_CALL:
            TAF_CSCALL_ProcUsimMsg(pstMsg);
            break;

        case TAF_SERVICE_TYPE_UNASSIGNED:
            MN_MSG_DispatchUsimMsg(pstMsg);
            TAF_CSCALL_ProcUsimMsg(pstMsg);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            TAF_APS_ProcMsg(pstMsg);

#endif

            break;

        default:
            MN_WARN_LOG("MN_ProcUsimMsg: Rcv Invalid ulClient.");
            break;

    }
    return;
}

/*****************************************************************************
 函 数 名  : MN_ProcPihMsg
 功能描述  : 处理来自Pih的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  2.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID  MN_ProcPihMsg (struct MsgCB * pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    if (USIMM_STKREFRESH_IND == pstMsgHeader->ulMsgName)
    {
        TAF_CBA_ProcRefreshInd((USIMM_STKREFRESH_IND_STRU *)pstMsgHeader);
        MN_MSG_RcvUsimRefreshInd((USIMM_STKREFRESH_IND_STRU *)pstMsgHeader);
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_ProcMmcMsg
 功能描述  : 处理来自Mmc的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月10日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数

  2.日    期   : 2010年3月1日
    作    者   : zhoujun /z40661
    修改内容   : 支持ALS特性
  3. 日    期   : 2010年12月27日
     作    者   : h44270
     修改内容   : Modified by PS Project, 增加新的消息处理函数入口，删除来自SPY的消息
  4.日    期   : 2012年4月5日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
VOS_VOID  MN_ProcMmcMsg (struct MsgCB * pstMsg)
{
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
        case TAFMMC_CBS_NO_NETWORK_IND:
        case TAFMMC_CBS_CURR_NET_MODE_IND:
            TAF_CBA_MsgProc(pstMsg);
            break;
#endif

        case TAFMMC_APS_SERVICE_STATE_IND:
            TAF_APS_ProcMsg(pstMsg);
            break;

        default:
            MN_WARN_LOG("MN_ProcMmcMsg:Rcv Invalid Msg Type");
            break;
    }
}

/*****************************************************************************
 函 数 名  : MN_ProcOmMsg
 功能描述  : 处理来自Mmc的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目新增函数
*****************************************************************************/
VOS_VOID  MN_ProcOmMsg (struct MsgCB * pstMsg)
{
    ID_NAS_OM_INQUIRE_STRU              *pstOmInquire;

    pstOmInquire = (ID_NAS_OM_INQUIRE_STRU *)pstMsg;

    switch ( pstOmInquire->ulMsgId)
    {
        case ID_NAS_OM_SET_CODEC_TYPE_REQUIRE :
        case ID_NAS_OM_CODEC_TYPE_INQUIRE :
            MN_CALL_ProcOmMsg(pstMsg);
            break;
        case ID_NAS_OM_SET_DSFLOW_RPT_REQ :
            TAF_APS_ProcMsg(pstMsg);
            break;
        default:
            MN_NORM_LOG("MN_CALL_ProcOmMsg:wrong PrimId!");
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : MN_ProcUsimStatus
 功能描述  : 处理来自MMA发送的卡在位消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月28日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  3.日    期   : 2012年4月5日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  4.日    期   : 2013年7月9日
    作    者   : l00208543
    修改内容   : for V9R1 STK升级项目
  5.日    期   : 2013年8月30日
    作    者   : l00208543
    修改内容   : DTS2013082902121
  6.日    期   : 2013年9月10日
    作    者   : z00161729
    修改内容   : 支持ss重发
  7.日    期   : 2015年03月14日
    作    者   : y00245242
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID MN_ProcUsimStatus(
    struct MsgCB                        * pstMsg
)
{
    MNPH_USIM_STATUS_IND_STRU           *pstUsimStatus;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* Added by l00208543 for V9R1 STK升级, 2013-07-09, begin */
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSP_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSR_ID, VOS_TRUE);
    /* Added by l00208543 for V9R1 STK升级, 2013-07-09, end */

    pstUsimStatus = (MNPH_USIM_STATUS_IND_STRU *)pstMsg;
    MN_MSG_CfgDataInit(pstUsimStatus->enUsimStatus);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    TAF_CBA_MsgProc(pstMsg);

#endif

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
    {
        MN_CALL_LineInfo(pstUsimStatus->enUsimStatus);
    }
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    /* 在PID init读取呼叫重建nv的时候判断是否是测试卡，但可能由于时序问题导致判断结果错误，
       因此在运行时再读调用一次读取NV的函数，在函数中判断是否是测试卡 */
    MN_CALL_ReadCallRedialCfgNvim();

    MN_CALL_ReadCallRedialCmSrvRejCfgNvim();

    /* 在PID init读取ss重建nv的时候判断是否是测试卡，但可能由于时序问题usim未初始化结束调用usim接口
       获取是否是测试卡返回不准导致判断结果错误，因此在运行时再读调用一次读取NV的函数，
       在函数中判断是否是测试卡 */
    TAF_SSA_ReadSsRetryCfgNvim();

    TAF_SSA_ReadSsRetryCmSrvRejCfgNvim();

}

#ifndef __PS_WIN32_RECUR__
/*****************************************************************************
 函 数 名  : TAF_RcvMmaOmMaintainInfoInd
 功能描述  : 处理来自MMA的PC工具可谓可测配置信息
 输入参数  : pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月24日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_RcvMmaOmMaintainInfoInd(
    struct MsgCB                       *pstMsg
)
{
    MMCM_OM_MAINTAIN_INFO_IND_STRU     *pstOmMaintainInfo;

    pstOmMaintainInfo = (MMCM_OM_MAINTAIN_INFO_IND_STRU*)pstMsg;

    /* 保存全局变量的值 */
    g_ucMnOmConnectFlg       = pstOmMaintainInfo->ucOmConnectFlg;
    g_ucMnOmPcRecurEnableFlg = pstOmMaintainInfo->ucOmPcRecurEnableFlg;

    if ( (VOS_TRUE == g_ucMnOmConnectFlg)
      && (VOS_TRUE == g_ucMnOmPcRecurEnableFlg) )
    {
        NAS_MSG_SndOutsideContextData_Part1();
        NAS_MSG_SndOutsideContextData_Part2();
        NAS_MSG_SndOutsideContextData_Part3();
    }
}
#endif
/*****************************************************************************
 函 数 名  : MN_ProcMmaMsg
 功能描述  : 处理来自Mma的消息
 输入参数  : pstMsg - 收到的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年2月11日
    作    者   : f62575
    修改内容   : 新生成函数

  2.日    期   : 2010年5月13日
    作    者   : zhoujun /z40661
    修改内容   : NAS支持CBS

  3.日    期   : 2011年3月28日
    作    者   : zhoujun /40661
    修改内容   : USIM的状态通知修改为由MMA模块通知
  4.日    期   : 2012年4月24日
    作    者   : l00171473
    修改内容   : DTS2012041805606
  5.日    期   : 2013年6月4日
    作    者   : s00217060
    修改内容   : for V9R1_SVLTE:MSG收到MMA CS域服务能力变更消息的处理
  6.日    期   : 2014年04月26日
    作    者   : y00245242
    修改内容   : 为eCall feature增加

  7.日    期   : 2014年10月17日
    作    者   : y00218312
    修改内容   : 增加MMA通知APS服务变化的处理
  8.日    期   : 2014年11月17日
    作    者   : w00176964
    修改内容   : CDMA 1x项目迭代5修改
*****************************************************************************/
VOS_VOID  MN_ProcMmaMsg (
    struct MsgCB                        *pstMsg
)
{
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
    case MN_USIM_STATUS_IND:
        MN_ProcUsimStatus(pstMsg);
        break;

#ifndef __PS_WIN32_RECUR__
        case MMCM_OM_MAINTAIN_INFO_IND:
            TAF_RcvMmaOmMaintainInfoInd(pstMsg);

            break;
#endif

        case ID_MMA_MSG_CS_SERVICE_CHANGE_NOTIFY:
            TAF_MSG_RcvMmaCsServiceChangeNotify(pstMsg);
            break;

        case MMA_TAF_POWER_OFF_IND:
            Aps_PowerOff();
            /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
            TAF_CSCALL_ProcMmaMsg(pstMsg);
            /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */
            break;

        case ID_MMA_TAF_POWER_ON_IND:

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            TAF_APS_ProcMsg(pstMsg);
#endif

            TAF_CSCALL_ProcMmaMsg(pstMsg);
            break;

        case ID_MMA_APS_EPDSZID_INFO_IND:

            TAF_APS_ProcMsg(pstMsg);
            break;

        case ID_MMA_TAF_1X_SERVICE_STATUS_IND:
            TAF_CSCALL_ProcMmaMsg(pstMsg);
            TAF_APS_ProcMsg(pstMsg);

            break;

        case ID_MMA_APS_CL_SERVICE_STATUS_IND:
            TAF_APS_ProcMsg(pstMsg);
            break;

        case ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND:
            TAF_APS_ProcMsg(pstMsg);
            break;

        case ID_MMA_TAF_SYS_CFG_INFO_IND:
            TAF_CSCALL_ProcMmaMsg(pstMsg);
            TAF_APS_ProcMsg(pstMsg);
            break;

        default:
            MN_WARN_LOG("MN_ProcMmaMsg:Rcv Invalid Msg Type");
            break;
    }
}

/*****************************************************************************
 函 数 名  : MN_SndAppMsgToSs
 功能描述  : 将AT或STK来的消息发给SS
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月17日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，修改函数入口参数
*****************************************************************************/
VOS_VOID  MN_SndAppMsgToSs (struct MsgCB *pstMsg)
{
    MN_APP_REQ_MSG_STRU                *pstSsMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLen;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg   = (MN_APP_REQ_MSG_STRU *)pstMsg;
    ulMsgLen    = pstAppMsg->ulLength;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    /* 申请消息 */
    pstSsMsg = (MN_APP_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);

    if (VOS_NULL_PTR == pstSsMsg)
    {
        MN_WARN_LOG("MN_SndAppMsgToSs: alloc msg fail!");

        return;
    }

    PS_MEM_CPY( ((VOS_UINT8 *)pstSsMsg + VOS_MSG_HEAD_LENGTH), ((VOS_UINT8 *)pstAppMsg+ VOS_MSG_HEAD_LENGTH), ulMsgLen);

    /* 填充消息头 */
    pstSsMsg->ulReceiverPid = WUEPS_PID_SS;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSsMsg);

    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_SndAppMsgToSs: send msg fail!");
        return;
    }

    return;
}


/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 函 数 名  : TAF_ProcStkEnvelopeCnf
 功能描述  : 分发来自STK的
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，新增
  2.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_VOID TAF_ProcStkEnvelopeCnf(struct MsgCB * pstMsg)
{
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope = VOS_NULL_PTR;

    pstEnvelope = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;

    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */
    if (SI_STK_ENVELOPE_CALLCRTL != pstEnvelope->enEnvelopeType)
    {
        MN_MSG_RcvUsimEnvelopeCnf(pstMsg);
    }
    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

    return;
}
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : MN_DispatchStkMsg
 功能描述  : 分发来自STK的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年11月10日
    作    者   : f62575
    修改内容   : 新生成函数
                 DTS2011111004869AT PROJECT 处理来自STK的业务请求消息
                 由原来的虚拟TAF过来修改为实际的STK模块发过来
  2.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
  3.日    期   : 2013年05月06日
    作    者   : f62575
    修改内容   : SS FDN&Call Control项目
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级，修改消息分发机制
*****************************************************************************/

VOS_VOID MN_DispatchStkMsg(struct MsgCB * pstMsg)
{
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulFuncNum;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    TAF_STK_MSG_FUNC_MAP                pStkMsgFunc = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    ulFuncNum = sizeof(g_astTafStkMsgFuncMap) / sizeof(g_astTafStkMsgFuncMap[0]);

    for (ulLoop = 0; ulLoop < ulFuncNum; ulLoop ++ )
    {
        if (pstMsgHeader->ulMsgName == g_astTafStkMsgFuncMap[ulLoop].ulMsgName)
        {
            pStkMsgFunc             = g_astTafStkMsgFuncMap[ulLoop].pStkMsgFunc;

            /*
                 处理函数不区分请求的源PID，而STK的业务请求结构与AT的一致，消息名不一致，
                 因为处理函数判断的消息名都是AT的消息名，这里将STK的消息名更新为APP的消息名
              */
            pstMsgHeader->ulMsgName = g_astTafStkMsgFuncMap[ulLoop].ulAppMsgName;
            break;
        }
    }

    if (VOS_NULL_PTR == pStkMsgFunc)
    {
        MN_WARN_LOG("MN_DispatchStkMsg: Invalid Msg Name");
        return;
    }

    pStkMsgFunc(pstMsg);

    return;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
/*****************************************************************************
 函 数 名  : MN_DispatchTafMsg
 功能描述  : 分发来自TAF的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月25日
    作    者   : s00217060
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_DispatchTafMsg (struct MsgCB * pstMsg)
{
    /* TAF->TAF的消息定义一个统一的结构体,取出消息分段 */
    TAF_INTERNAL_MSG_STRU              *pstTafMsg = VOS_NULL_PTR;

    pstTafMsg = (TAF_INTERNAL_MSG_STRU *)pstMsg;

    switch (pstTafMsg->ulMsgId & ID_TAF_MNTN_MSG_MASK)
    {
        /* 来自APS API的消息交给APS处理 */
        case ID_TAF_APS_INTERNAL_BASE:
            TAF_APS_ProcMsg(pstMsg);
            break;

        /* 发送给MSG的消息到MSG处理 */
        /* 目前只有ID_TAF_SPM_SMMA_REQ,MSG先发送到SPM进行域选择,域选择之后再到MSG处理 */
        case ID_TAF_MSG_INTERNAL_BASE:
            TAF_MSG_ProcTafMsg(pstMsg);
            break;

        /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, begin */
        case ID_TAF_CALL_INTERNAL_BASE:
            TAF_CALL_ProcTafMsg(pstMsg);
            break;
        /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, end */

        /* 其他消息不需要处理 */
        default:
            MN_NORM_LOG("MN_DispatchTafMsg: Unknown message type.");
            break;
    }

    return;
}
/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */

/*****************************************************************************
 函 数 名  : MN_DispatchAppMsg
 功能描述  : 分发来自应用层的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2011年11月07日
    作    者   : f00179208
    修改内容   : AT Project, 删除了MN_APP_MSG_CLASS_QRY分支中的处理
  3.日    期   : 2011年12月19日
    作    者   : h44270
    修改内容   : PS Project, 修改MN_APP_MSG_CLASS_PS分支的处理，调用新的处理函数
  4.日    期   : 2013年5月19日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:SPM处理完的输出消息需要发送到SSA继续处理
  5.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  6.日    期   : 2013年10月05日
    作    者   : s00217060
    修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
VOS_VOID  MN_DispatchAppMsg (struct MsgCB * pstMsg)
{
    MN_APP_REQ_MSG_STRU * pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    switch (pstAppMsg->usMsgName & MN_APP_MSG_CLASS_MASK)
    {
    case MN_APP_MSG_CLASS_CALL:
        TAF_CSCALL_ProcAppReqMsg(pstMsg);
        break;

    case MN_APP_MSG_CLASS_MSG:
        /* 来自SMA API的消息，交给SMA处理 */
        MN_MSG_ProcAppReqMsg(pstAppMsg);
        break;

    case MN_APP_MSG_CLASS_SSA:
        /* 来自SSA API的消息，交给SSA处理 */
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
        MN_SndAppMsgToSs(pstMsg);
        /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */
        break;

    case MN_APP_MSG_CLASS_MMA:
        /* 来自MMA API的消息，交给MMA处理 */
        break;

    /* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-10-05, begin */
    /* 移到MN_DispatchTafMsg中处理 */
    /* Deleted by s00217060 for VoLTE_PhaseII  项目, 2013-10-05, end */

    case MN_APP_MSG_CLASS_QRY:
        /* AT与MN模块间查询操作相关消息 */

        break;

    default:
        MN_ERR_LOG("MN_DispatchAppMsg: Unknown message type.");
        break;
    }
}



/*****************************************************************************
 函 数 名  : MN_DispatchAppMsg
 功能描述  : 分发来自应用层的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2008年1月10日
   作    者   : 丁庆 49431
   修改内容   : 新生成函数
 2.日    期   : 2011年12月24日
   作    者   : h44270
   修改内容   : modified by PS Project,修改消息入口函数，此处不能直接替换
*****************************************************************************/
VOS_VOID  MN_DispatchRabmMsg (
    VOS_VOID                            *pstMsg
)
{
    MN_RABM_IND_MSG_STRU                *pstRabmMsg;

    pstRabmMsg = (MN_RABM_IND_MSG_STRU *)pstMsg;

    /* 由于RABM发的消息给APS和CALL两个模块进行处理，当MsgName的取值范围
       在RABM和CALL之间的定义的时候，由新增函数处理，否则由原有函数处理 */
    if (pstRabmMsg->usMsgName > RABM_CALL_MSG_CLASS_BASE)
    {
        MN_CALL_ProcRabmCallPrimitive(pstRabmMsg);
        return;
    }

    TAF_APS_ProcMsg((struct MsgCB *)pstMsg);

}

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 函 数 名  : MN_DispatchImsaMsg
 功能描述  : 分发来自IMSA的消息
 输入参数  : pMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月11日
   作    者   : y00245242
   修改内容   : 新生成函数
 2.日    期   : 2013年9月24日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseII 项目修改:增加SRVCC相关消息的处理
*****************************************************************************/
VOS_VOID MN_DispatchImsaMsg (
    VOS_VOID                           *pMsg
)
{
    MSG_HEADER_STRU                   *pstImsaMsg = VOS_NULL_PTR;

    pstImsaMsg = (MSG_HEADER_STRU *)pMsg;

    switch (pstImsaMsg->ulMsgName & TAF_IMSA_MSG_MASK)
    {
        case TAF_MSG_IMSA_MSG_BASE:
            /* 处理来自IMSA的SMS的MSG */
            TAF_MSG_ProcImsaMsg(pstImsaMsg);
            break;

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, begin */
        case TAF_CALL_IMSA_MSG_BASE:
            TAF_CALL_ProcImsaMsg(pstImsaMsg);
            break;
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, end */

        default:
            break;
    }
}
#endif
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : MN_DispatchXccMsg
 功能描述  : 把XCC的消息进行分发处理
 输入参数  : struct MsgCB * pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年9月25日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  MN_DispatchXccMsg (struct MsgCB * pstMsg)
{
    /* XCC->TAF的消息定义一个统一的结构体,取出消息分段 */
    MSG_HEADER_STRU                    *pstTafMsg = VOS_NULL_PTR;

    pstTafMsg = (MSG_HEADER_STRU *)pstMsg;

    switch (pstTafMsg->ulMsgName & TAF_XCC_TAF_MSG_MASK)
    {
        /* 来自APS API的消息交给APS处理 */
        case TAF_XCC_APS_MSG_BASE:
            TAF_APS_ProcMsg(pstMsg);
            break;

        case TAF_XCC_XCALL_MSG_BASE:
            TAF_XCALL_ProcXccMsg(pstMsg);
            break;

        /* 其他消息不需要处理 */
        default:
            MN_NORM_LOG("MN_DispatchXccMsg: Unknown message type.");
            break;
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : MN_DispatchMsg
 功能描述  : 分发TAF FID收到的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年2月23日
    作    者   : f62575
    修改内容   : 问题单号AT2D17029：增加短信功能任意点回放功能
  3.日    期   : 2011年11月07日
    作    者   : f00179208
    修改内容   : AT Project, 修改AT虚拟的WUEPS_PID_TAF为WUEPS_PID_AT
  4.日    期   : 2011年11月10日
    作    者   : f62575
    修改内容   : DTS2011111004869 STK业务请求消息源PID由原来的TAF变更为MAPS_STK_PID，
                 增加MAPS_STK_PID事件处理分支
  5. 日    期   : 2010年12月27日
     作    者   : h44270
     修改内容   : Modified by PS Project, 增加新的消息处理函数入口，删除来自SPY的消息
  6.日    期   : 2012年4月5日
    作    者   : l00171473
    修改内容   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  7.日    期   : 2012年7月13日
    作    者   : w00167002
    修改内容   : V7R1C50_GUTL_PhaseI:支持TD-SCDMA特性时，需对消息进行适配处理
  8.日    期   : 2012年11月09日
    作    者   : l00198894
    修改内容   : Probe路测工具对接项目扩展OM消息的处理
  9.日    期   : 2013年5月08日
    作    者   : w00176964
    修改内容   : SS FDN&Call Control项目:发送到MN的消息都先经过SPM模块先处理
  10.日    期   : 2013年6月4日
     作    者   : z00161729
     修改内容   : SVLTE 和usim接口调整修改
  11.日    期   : 2013年6月26日
     作    者   : f62575
     修改内容   : V9R1 STK升级
  12.日    期 : 2013年07月08日
     作    者 : Y00213812
     修改内容 : VoLTE_PhaseI 项目，增加TAF模块的消息处理
  13.日    期   : 2013年09月24日
     作    者   : s00217060
     修改内容   : VoLTE_PhaseII项目
*****************************************************************************/
VOS_VOID  MN_DispatchMsg (struct MsgCB * pstMsg)
{
    struct MsgCB                      *pstSrcMsg = VOS_NULL_PTR;
    struct MsgCB                      *pstDestMsg = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        /* svlte特性开启时，modem1可能收到usim0的消息，需要将消息中send pid进行转换 */
        pstMsg->ulSenderPid = TAF_SDC_ConvertOamSendPid(pstMsg->ulSenderPid);
    }


    /* 支持TD-SCDMA特性时，需对消息进行适配处理 */
    if ( VOS_TRUE == NAS_UTRANCTRL_MsgProc(pstMsg, &pstDestMsg) )
    {
        /* 消息在UTRANCTRL模块处理完成，直接返回，不进入后续处理 */
        return;
    }

    pstSrcMsg = pstDestMsg;

    if (VOS_TRUE == TAF_SPM_MsgProc(pstSrcMsg, &pstDestMsg))
    {
        /* 消息在SPM模块处理完成,直接返回,不需要进入后续处理 */
        return;
    }

    /* 替换消息指针 */
    switch (pstDestMsg->ulSenderPid)
    {
    case VOS_PID_TIMER:
        MN_ProcTimerMsg(pstDestMsg);
        break;

    case UEPS_PID_CST:
        MN_CALL_ProcCstCallPrimitive(pstDestMsg);
        break;

    case MAPS_STK_PID:
        MN_DispatchStkMsg(pstDestMsg);
        break;

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    case WUEPS_PID_TAF:
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */
        /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, begin */
        MN_DispatchTafMsg(pstDestMsg);
        break;
        /* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-24, end */

    case WUEPS_PID_AT:
        MN_DispatchAppMsg(pstDestMsg);
        break;

    case WUEPS_PID_CC:
        MN_CALL_ProcMnccPrimMsg(pstDestMsg);
        break;

    case WUEPS_PID_MMC:
        MN_ProcMmcMsg(pstDestMsg);
        break;

    case WUEPS_PID_MMA:
        MN_ProcMmaMsg(pstDestMsg);
        break;

    case WUEPS_PID_MM:
        break;

    case WUEPS_PID_SS:
        break;

    case WUEPS_PID_SMS:
        MN_MSG_ProcSmsMsg((VOS_VOID*)pstDestMsg);
        break;

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, begin */
#if (FEATURE_IMS == FEATURE_ON)
    case PS_PID_IMSA:
        MN_DispatchImsaMsg((VOS_VOID*)pstDestMsg);
        break;
#endif
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-11, end */

    case WUEPS_PID_SM:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

#if (FEATURE_ON == FEATURE_LTE)
    case PS_PID_ESM:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case MSP_L4_L4A_PID:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

#endif

    case WUEPS_PID_RABM:
        MN_DispatchRabmMsg(pstDestMsg);
        break;

    case UEPS_PID_SN:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case WUEPS_PID_USIM:
    case MAPS_PB_PID:
        MN_ProcUsimMsg(pstDestMsg);
        break;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    case MAPS_PIH_PID:
        MN_ProcPihMsg(pstDestMsg);
        break;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    case MSP_PID_DIAG_APP_AGENT:
        MN_ProcOmMsg(pstDestMsg);
        break;

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    case WUEPS_PID_VC:
         TAF_CSCALL_ProcVcMsg(pstDestMsg);
        break;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */


#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    case UEPS_PID_GAS:
    case WUEPS_PID_BMC:
#if (FEATURE_ON == FEATURE_LTE)
    case PS_PID_ERRC:
#endif
    case WUEPS_PID_WRR:
        TAF_CBA_MsgProc(pstDestMsg);
        break;

#endif

    case UEPS_PID_NDCLIENT:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
    case ACPU_PID_TAFAGENT:
        TAF_APS_ProcMsg(pstDestMsg);
        break;
    /* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    case UEPS_PID_XCC:
        MN_DispatchXccMsg(pstMsg);
        break;

    case MSPS_PID_PPPC:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case UEPS_PID_CDS:
        TAF_APS_ProcMsg(pstDestMsg);
        break;


    case UEPS_PID_XREG:
        TAF_APS_ProcMsg(pstDestMsg);
        break;
    case UEPS_PID_HSM:
        TAF_APS_ProcMsg(pstMsg);
        break;

    case UEPS_PID_DHCP:
        TAF_APS_ProcMsg(pstMsg);
        break;

    case UEPS_PID_EHSM:
        TAF_APS_ProcMsg(pstMsg);
        break;

    case UEPS_PID_XSMS:
        TAF_CSCALL_ProcXsmsMsg(pstMsg);
        break;

    case MSPS_PID_1X_RMAC:
    case MSPS_PID_1X_FMAC:
        TAF_CSCALL_ProcCttfMsg(pstMsg);
        break;
#endif
    default:
        MN_ERR_LOG1("MN_DispatchMsg: Unknown message sender, SenderPid, ", (VOS_INT32)pstMsg->ulSenderPid);
        break;
    }
}


/*****************************************************************************
 函 数 名  : WuepsTafFidInit
 功能描述  : 初始化TAF FID
 输入参数  : 略
 返 回 值  : 略
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
*****************************************************************************/
/* Deleted by wx270776 for OM融合, 2015-7-16, begin */
/* Deleted by wx270776 for OM融合, 2015-7-16, end */

extern VOS_UINT32 WuepsVCPidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID  APP_VC_MsgProc(MsgBlock* pMsg);

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_VOID   At_MsgProc(MsgBlock* pMsg);
extern VOS_UINT32 At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
#endif

/*****************************************************************************
 函 数 名  : WuepsTafFidInit
 功能描述  : TAF FID初始化函数
 输入参数  : ip - 初始化阶段
 输出参数  : 无
 返 回 值  : 初始化结果
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月26日
    作    者   : o00132663
    修改内容   : AT2D19540, 将信号量g_ATCtrSendSem提前到TAF_FID初始化函数中
                 创建，防止出现未创建先使用导致系统挂死的问题。

  2.日    期   : 2010年7月20日
    作    者   : s62952
    修改内容   : DTS2010071302886

  3.日    期   : 2011年10月3日
    作    者   : 鲁琳/l60609
    修改内容   : AT Project: AT PID注册从TAF FID中删除，并将自处理任务删除；增加AT AGENT pid
  4.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目
  5.日    期   : 2012年5月9日
    作    者   : z60575
    修改内容   : DTS2012050905268, C核任务优先级调整

  6.日    期   : 2012年6月30日
    作    者   : y00213812
    修改内容   : V7R1C50 A-GPS项目增加MTA模块的初始化和消息处理注册

*****************************************************************************/
VOS_UINT32 WuepsTafFidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{

    VOS_UINT32 ulRslt = VOS_OK;

    switch( ip )
    {
        case   VOS_IP_LOAD_CONFIG:
            /* Deleted by wx270776 for OM融合, 2015-7-16, begin */

            /* Deleted by wx270776 for OM融合, 2015-7-16, end */

            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_TAF,
                                        (Init_Fun_Type) MN_Init,
                                        (Msg_Fun_Type) MN_DispatchMsg  );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_VC,
                                         (Init_Fun_Type)WuepsVCPidInit,
                                         (Msg_Fun_Type)APP_VC_MsgProc  );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            /* Added by l60609 for AT Project，2011-10-03,  Begin*/
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_DRV_AGENT,
                                         (Init_Fun_Type)DRVAGENT_Init,
                                         (Msg_Fun_Type)DRVAGENT_DispatchMsg  );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            /* Added by l60609 for AT Project，2011-10-03,  End*/
            #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            /* Added by h00300778 for 1XSMS Project，2014-11-02,  Begin*/
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_XSMS,
                                         (Init_Fun_Type)TAF_XSMS_PidInit,
                                         (Msg_Fun_Type)TAF_XSMS_PidMsgProc);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }
            #endif
            /* Added by h00300778 for 1XSMS Project，2014-11-02,  End*/

            /* Added by L60609 for AT Project，2011-10-20,  Begin*/
            #if (VOS_WIN32 == VOS_OS_VER)
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_AT,
                                         (Init_Fun_Type)At_PidInit,
                                         (Msg_Fun_Type)At_MsgProc);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }
            #endif
            /* Added by L60609 for AT Project，2011-10-20,  Begin*/


            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_TAF, VOS_PRIORITY_M5);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_MTA,
                                        (Init_Fun_Type)TAF_MTA_InitPid,
                                        (Msg_Fun_Type)TAF_MTA_ProcMsg );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_XPDS,
                                        (Init_Fun_Type)TAF_XPDS_InitPid,
                                        (Msg_Fun_Type)TAF_XPDS_MsgProc );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }
#endif
            break;

        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
    }

    return VOS_OK;
}


#ifdef  __cplusplus
#if  __cplusplus
}
#endif
#endif

