/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MnCall.c
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2007年9月20日
  最近修改   : 2007年9月20日
  功能描述   : 实现CCA向TAF其它模块提供的外部接口
  函数列表   :
  修改历史   :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 创建文件

  2.日    期   : 2010年3月2日
    作    者   : zhoujun /z40661
    修改内容   : NAS R7协议升级

  3.日    期   : 2010年4月8日
    作    者   : zhoujun /z40661
    修改内容   : 可配置当前CODEC类型

  4.日    期   : 2010年8月9日
    作    者   : zhoujun /40661
    修改内容   : 支持UUS1
  2.日    期   : 2010年11月11日
    作    者   : h44270
    修改内容   : 问题单号：DTS2010102202190/DTS2010110600922，出现ERROR打印
******************************************************************************/
/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MnCallProcNvim.h"
#include "MnCall.h"
#include "MnCallReqProc.h"
#include "MnCallMnccProc.h"
#include "MnCallMgmt.h"
#include "MnCallApi.h"
#include "MnCallBcProc.h"
#include "NasCc.h"
#include "PsNvId.h"
#include "NVIM_Interface.h"
#include "VcCallInterface.h"
#include "UsimPsInterface.h"
#include "MnCallCstProc.h"
#include "MnCallTimer.h"
#include "CstNasInterface.h"
#include "RabmTafInterface.h"
#include "NasOmInterface.h"

#include "MnCallSendCc.h"
#include "MnComm.h"
#include "MnCallMgmt.h"
#include "NVIM_Interface.h"
#include "MnCallCtx.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/
#include "NasUsimmApi.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasComm.h"
#endif
#include "TafSdcCtx.h"
#include "TafSdcLib.h"

/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-2, begin */
#include "MnCallProcVc.h"
#include "MnCallMnccProc.h"
#include "MnCallProcTaf.h"
#include "MnCallProcMma.h"
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-2, end */

#include "TafMmaInterface.h"
#include "TafInternalInterface.h"

#include "TafCsCallMain.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/* Deleted by z00234330 for pclint 清理  项目, 2014-07-03, begin */
/* Deleted by z00234330 for pclint 清理  项目, 2014-07-03, end */

/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-16, end */

/*****************************************************************************
   2 变量定义
*****************************************************************************/
/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

extern    VOS_VOID MN_CALL_SetTchStatus(
    VOS_BOOL                            bAvailable
);
/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2014-2-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2014-2-11, end */

/*lint -save -e958 */


/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : MN_CALL_Init
 功能描述  : 执行CCA模块的初始化，包括所有呼叫状态的复位和全局资源的初始化
             TAF应该在系统启动时和Reset时调用该接口
 输入参数  : enPowerState - 开机或关机
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2010年4月20日
    作    者   : z00161729
    修改内容   : 问题单AT2D18405
  3.日    期   : 2010年8月22日
    作    者   : z00161729
    修改内容   : 问题单ATD2010081901568:软关机情况未停之前启动过的定时器
  4.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目 :nvim初始化
  4.日    期   : 2012年3月2日
    作    者   : 傅映君/f62575
    修改内容   : C50_IPC Project, CS 呼叫初始化过程增加FDN本地配置获取

  5.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目
  6.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  7.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  8.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  9.日    期   : 2013年07月11日
    作    者   : l00198894
    修改内容   : V9R1 STK升级项目
 10.日    期   : 2014年04月18日
    作    者   : y00245242
    修改内容   : 为eCall feature修改

  12.日    期   : 2014年7月2日
    作    者   : z00234330
    修改内容   : PCLINT清理
*****************************************************************************/
VOS_VOID  MN_CALL_Init(MN_CALL_POWER_STATE_ENUM_U8 enPowerState)
{

    MN_CALL_InitCtx();

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    /*读取NIM信息*/
    MN_CALL_ReadNvimInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    MN_CALL_InitAllTimers(enPowerState);

    MN_CALL_CapaProcInit();

    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
    /* 移该处实现到power off 处理 */
    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */

    MN_CALL_ResetAllCalls(enPowerState);
    MN_CALL_SetTchStatus(VOS_FALSE);

    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-18, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  项目, 2013-12-18, end */

    /* Deleted by z00234330 for pclint 清理  项目, 2014-07-03, begin */
    /* Deleted by z00234330 for pclint 清理  项目, 2014-07-03, end */


    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    TAF_CALL_InitDtmfCtx();
    /* Added by l00198894 for V9R1 STK升级, 2013/07/11, end */

    return;
}


/*****************************************************************************
 函 数 名  : MN_CALL_LineInfo
 功能描述  : 收到卡在位信息后从NVIM中获取当前选择的线路
 输入参数  : enUsimStatus:当前卡是否在位
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月25日
    作    者   : z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
  4.日    期   : 2013年6月5日
    作    者   : w00242748
    修改内容   : SVLTE和USIM接口整合
*****************************************************************************/
VOS_VOID MN_CALL_LineInfo(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
)
{
    MN_CALL_ALS_LINE_INFO_STRU          stAlsInfo;
    VOS_UINT8                           aucMmaImsi[9];
    VOS_BOOL                            bWriteNvim;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    ulLength = 0;
    stAlsInfo.enAlsLine = MN_CALL_ALS_LINE_NO_BUTT;
    PS_MEM_SET(stAlsInfo.aucMmaImsi, 0x00, sizeof(stAlsInfo.aucMmaImsi));

    if ( MNPH_USIM_STATUS_AVILABLE == enUsimStatus )
    {
        bWriteNvim = VOS_FALSE;

        if ( NV_OK != NV_Read(en_NV_Item_ALS_LINE_Config,&stAlsInfo,sizeof(stAlsInfo)))
        {
            return;
        }

        ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(aucMmaImsi);
        if ( USIMM_API_SUCCESS !=  ulGetCardImsiRslt)
        {
            if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
            {

#if (FEATURE_ON == FEATURE_PTM)
                /* 记录获取卡IMSI异常log */
                TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, aucMmaImsi);
#endif
            }

            return ;
        }

        /*线路号值不在取值范围内*/
        if  ( ( MN_CALL_ALS_LINE_NO_1 != stAlsInfo.enAlsLine )
           && ( MN_CALL_ALS_LINE_NO_2 != stAlsInfo.enAlsLine ) )
        {
            stAlsInfo.enAlsLine = MN_CALL_ALS_LINE_NO_1;
            bWriteNvim = VOS_TRUE;
        }

        /*判断NV中当前使用线路号对应的IMSI和SIM卡中IMSI是否相同，若不同则清NV
          项，并填入默认线路号1*/
        if ( 0 != VOS_StrCmp( (VOS_CHAR *)aucMmaImsi,
                               (VOS_CHAR *)stAlsInfo.aucMmaImsi) )
        {
            stAlsInfo.enAlsLine = MN_CALL_ALS_LINE_NO_1;
            PS_MEM_CPY(stAlsInfo.aucMmaImsi,aucMmaImsi,9);
            bWriteNvim = VOS_TRUE;
        }

        /*需要更新NVIM*/
        if ( VOS_TRUE == bWriteNvim )
        {
            (VOS_VOID)NV_GetLength(en_NV_Item_ALS_LINE_Config, &ulLength);
            if (NV_OK != NV_Write(en_NV_Item_ALS_LINE_Config,
                     &stAlsInfo,
                     ulLength) )
            {
                TAF_WARNING_LOG(WUEPS_PID_TAF, "MN_CALL_LineInfo: en_NV_Item_ALS_LINE_Config NV Write Fail!");
            }
        }

        (VOS_VOID)MN_CALL_UpdateAlsLineInfo(stAlsInfo.enAlsLine,VOS_FALSE);
    }
}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcAppReqMsg
 功能描述  : 处理来自应用层的请求消息
             该函数根据请求的类型将消息分发到相应的请求处理函数去处理
 输入参数  : pstMsg - 应用层调用TAF API时由API函数打包发出的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2011年10月06日
    作    者   : f00179208
    修改内容   : AT移植项目,增加消息处理分支
  3.日    期   : 2012年06月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM增加紧急呼号码上报
  4.日    期   : 2012年09月18日
    作    者   : y00213812
    修改内容   : STK&DCM项目： 增加事件处理
  5.日    期   : 2013年4月8日
    作    者   : s00217060
    修改内容   : 主动上报AT命令控制下移至C核及mma和mmc接口调整
  6.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  7.日    期   : 2014年04月15日
    作    者   : y00245242
    修改内容   : 为eCall feature功能修改
*****************************************************************************/
VOS_VOID  MN_CALL_ProcAppReqMsg(
    const VOS_VOID                      *pstMsg
)
{

    MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg;

    pstCallMsg = (MN_CALL_APP_REQ_MSG_STRU*)pstMsg;

    MN_NORM_LOG1("MN_CALL_ProcAppReqMsg: enAppReq:", (VOS_INT32)pstCallMsg->enReq);
    /* 根据消息中的应用请求类型，将消息交给相应的请求处理函数处理 */

/*回放工程恢复全局变量*/
#ifdef __PS_WIN32_RECUR__
    if ( VOS_TRUE == NAS_CALL_RestoreContextData((struct MsgCB*)pstMsg))
    {
        return;
    }
#endif

    switch (pstCallMsg->enReq)
    {
    case MN_CALL_APP_ORIG_REQ:
/*PC回放导出全局变量使用*/
#ifndef __PS_WIN32_RECUR__
        NAS_CALL_SndOutsideContextData();
#endif
        MN_CALL_CallOrigReqProc(pstCallMsg->clientId,
                                pstCallMsg->opId,
                                pstCallMsg->callId,
                                (MN_CALL_ORIG_PARAM_STRU*)&pstCallMsg->unParm);
        break;

    case MN_CALL_APP_END_REQ:
        MN_CALL_CallEndReqProc(pstCallMsg->clientId,
                               pstCallMsg->opId,
                               pstCallMsg->callId,
                               (MN_CALL_END_PARAM_STRU*)&pstCallMsg->unParm);
        break;

    case MN_CALL_APP_ANSWER_REQ:
        MN_CALL_CallAnswerReqProc(pstCallMsg->clientId,
                                  pstCallMsg->opId,
                                  pstCallMsg->callId,
                                  (MN_CALL_ANS_PARAM_STRU*)&pstCallMsg->unParm);
        break;

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    case MN_CALL_APP_START_DTMF_REQ:
        TAF_CALL_RcvStartDtmfReq((struct MsgCB *)pstCallMsg);
        break;

    case MN_CALL_APP_STOP_DTMF_REQ:
        TAF_CALL_RcvStopDtmfReq((struct MsgCB *)pstCallMsg);
        break;

    case MN_CALL_APP_SUPS_CMD_REQ:
        MN_CALL_CallSupsCmdReqProc((struct MsgCB *)pstCallMsg);
        break;
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    case MN_CALL_APP_GET_INFO_REQ:
        MN_CALL_CallInfoReqProc(pstCallMsg->clientId,
                                pstCallMsg->opId);
        break;

    case MN_CALL_APP_GET_CDUR_REQ:
        MN_CALL_GetCdur(pstCallMsg->clientId,
                        pstCallMsg->opId,
                        pstCallMsg->callId);
        break;
    case MN_CALL_APP_SET_UUSINFO_REQ:
        MN_CALL_SetUus1Info(pstCallMsg->clientId,
                            pstCallMsg->opId,
                            (MN_CALL_UUS1_PARAM_STRU*)&pstCallMsg->unParm);
        break;
    case MN_CALL_APP_QRY_UUSINFO_REQ:
        MN_CALL_QryUus1Info(pstCallMsg->clientId,
                            pstCallMsg->opId);
        break;
    case MN_CALL_APP_SET_ALS_REQ:
        MN_CALL_SetAls(pstCallMsg->clientId,
                       pstCallMsg->opId,
                       (MN_CALL_SET_ALS_PARAM_STRU*)&pstCallMsg->unParm);
        break;
    case MN_CALL_APP_QRY_ALS_REQ:
        MN_CALL_QryAls(pstCallMsg->clientId,
                       pstCallMsg->opId);
        break;

    /* Added by w00199382 for PS Project，2011-12-06,  Begin*/

    /*AT获取CALLINFO的同步API消息处理*/
    case ID_TAFAGENT_MN_GET_CALL_INFO_REQ:
        MN_CALL_RcvTafAgentGetCallInfo();
        break;

    /* Added by w00199382 for PS Project，2011-12-06,  End*/

    case MN_CALL_APP_CUSTOM_ECC_NUM_REQ:
        MN_CALL_RcvTafEccNumReq((MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*)&pstCallMsg->unParm);
        break;

    case MN_CALL_APP_CLPR_GET_REQ:
        MN_CALL_RcvAtClprGetReq(pstCallMsg);
        break;

    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */
    case MN_CALL_APP_SET_CSSN_REQ:
        MN_CALL_RcvAtCssnSetReq(pstCallMsg->clientId,
                                pstCallMsg->opId,
                                (MN_CALL_SET_CSSN_REQ_STRU*)&pstCallMsg->unParm);
        break;
    /* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */

    case MN_CALL_APP_XLEMA_REQ:
        MN_CALL_RcvAtXlemaReq(pstCallMsg);
        break;

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    case MN_CALL_QRY_ECALL_INFO_REQ:
        TAF_CALL_RcvQryEcallInfoReq((MN_CALL_QRY_ECALL_INFO_REQ_STRU *)pstCallMsg);
        break;
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-3-29, end */

    default:
        MN_WARN_LOG("MN_CALL_ProcAppReqMsg:Invalid Msg Name");
        break;

    }


}

/*****************************************************************************
 函 数 名  : MN_CALL_ModifyCallId
 功能描述  : 更新INCOMING状态接收到的CC消息的CALLID
             解决CC接收到CALL CONFIRM消息前，CC与CALL模块CALL ID不同步问题
 输入参数  : MNCC_IND_PRIM_MSG_STRU           *pstMsg
 输出参数  : MNCC_IND_PRIM_MSG_STRU           *pstMsg
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月15日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_ModifyCallId(MNCC_IND_PRIM_MSG_STRU           *pstMsg)
{
    VOS_UINT32                          ulLoop;
    MN_CALL_MGMT_STRU                  *pstMgmtEntity;

    /* 消息中CALL ID在有效范围不需要修改 */
    if ((pstMsg->ucCallId > 0)
     && (pstMsg->ucCallId <= MN_CALL_MAX_NUM))
    {
        return;
    }

    pstMgmtEntity = PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_MGMT_STRU));
    if (VOS_NULL_PTR == pstMgmtEntity)
    {
        return;
    }

    /*
       获取CALL本地与消息TI匹配的实体，更新CALL ID到消息中
       使用过程中的呼叫实体，状态在INCOMING状态，且TI相同，更新实体的CALL ID到消息
    */
    for (ulLoop = 0; ulLoop < MN_CALL_MAX_NUM; ulLoop++)
    {
        MN_CALL_GetMgmtEntityInfoByCallId((VOS_UINT8)(ulLoop + 1), pstMgmtEntity);
        if (VOS_TRUE != pstMgmtEntity->bUsed)
        {
            continue;
        }

        if (MN_CALL_S_INCOMING != pstMgmtEntity->stCallInfo.enCallState)
        {
            continue;
        }

        if ((VOS_UINT8)pstMgmtEntity->ulTi == pstMsg->ucTi)
        {
            pstMsg->ucCallId = (VOS_UINT8)pstMgmtEntity->stCallInfo.callId;
            break;
        }
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstMgmtEntity);

    return;
}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcMnccPrimMsg
 功能描述  : 处理来自CC的MNCC原语消息
             该函数根据原语名将消息分发到相应的MNCC原语处理函数去处理
 输入参数  : pMsg - 来自CC的MNCC原语消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月20日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年6月11日
    作    者   : w00166186
    修改内容   : AT&T&DCM项目
  3.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
  4.日    期   : 2013年01月29日
    作    者   : Y00213812
    修改内容   : DTS2013012909872,记录CALL挂断的方向
  5.日    期   : 2013年03月18日
    作    者   : f62575
    修改内容   : DTS2013031502471,解决CC接收到CALL CONFIRM消息前，CC与CALL模块CALL ID不同步问题
  6.日    期   : 2013年04月12日
    作    者   : f62575
    修改内容   : DTS2013041503184,解决3G下RADIO LINK FAILURE没有按协议要求输出近端释放事件问题
                 仅在呼叫重建失败后上报给UICC，此处删除MNCC_RADIO_LINK_FAILURE分支
  7.日    期   : 2013年09月24日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseII 项目修改:增加SRVCC的状态通知消息的处理
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccPrimMsg(
    const VOS_VOID                      *pMsg
)
{
    MNCC_IND_PRIM_MSG_STRU              *pstMnccMsg;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* 获取特性控制NV地址 */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    pstMnccMsg = (MNCC_IND_PRIM_MSG_STRU*)pMsg;
    MN_NORM_LOG1("MN_CALL_ProcAppReqMsg: enPrimName:", pstMnccMsg->enPrimName);

    /* 根据消息中的原语名，将消息交给相应的MNCC原语处理函数处理 */
    switch(pstMnccMsg->enPrimName)
    {
    case MNCC_SETUP_IND:
/*PC回放导出全局变量使用*/
#ifndef __PS_WIN32_RECUR__
        NAS_CALL_SndOutsideContextData();
#endif
        MN_CALL_ProcMnccSetupInd(pstMnccMsg);
        break;

    case MNCC_SETUP_CNF:
        MN_CALL_ProcMnccSetupCnf(pstMnccMsg);
        break;

    case MNCC_SETUP_COMPL_IND:
        MN_CALL_ProcMnccSetupComplInd(pstMnccMsg);
        break;

    case MNCC_CALL_PROC_IND:
        MN_CALL_ProcMnccCallProcInd(pstMnccMsg);
        break;

    case MNCC_ALERT_IND:
        MN_CALL_ProcMnccAlertInd(pstMnccMsg);
        break;

    case MNCC_DISC_IND:
        MN_CALL_ProcMnccDiscInd(pstMnccMsg);
        break;

    case MNCC_REL_IND:
        MN_CALL_ProcMnccRelInd(pstMnccMsg);
        break;

    case MNCC_REL_CNF:
        MN_CALL_ModifyCallId(pstMnccMsg);
        MN_CALL_ProcMnccRelCnf(pstMnccMsg);
        break;

    case MNCC_REJ_IND:
        MN_CALL_ProcMnccRejInd(pstMnccMsg);
        break;

    case MNCC_FACILITY_IND:
        MN_CALL_ProcMnccFacilityInd(pstMnccMsg);
        break;

    case MNCC_FACILITY_LOCAL_REJ:
        MN_CALL_ProcMnccFacilityLocalRej(pstMnccMsg);
        break;

    case MNCC_HOLD_CNF:
        MN_CALL_ProcMnccHoldCnf(pstMnccMsg);
        break;

    case MNCC_HOLD_REJ:
        MN_CALL_ProcMnccHoldRej(pstMnccMsg);
        break;

    case MNCC_RETRIEVE_CNF:
        MN_CALL_ProcMnccRetrieveCnf(pstMnccMsg);
        break;

    case MNCC_RETRIEVE_REJ:
        MN_CALL_ProcMnccRetrieveRej(pstMnccMsg);
        break;

    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, begin */
    case MNCC_START_DTMF_CNF:
        TAF_CALL_RcvCcStartDtmfCnf(pstMnccMsg);
        break;

    case MNCC_START_DTMF_REJ:
        TAF_CALL_RcvCcStartDtmfRej(pstMnccMsg);
        break;

    case MNCC_STOP_DTMF_CNF:
        TAF_CALL_RcvCcStopDtmfCnf(pstMnccMsg);
        break;
    /* Modified by l00198894 for V9R1 STK升级, 2013/07/11, end */

    case MNCC_MODIFY_IND:
        /* in-call modification, CC暂不支持 */
        break;

    case MNCC_MODIFY_CNF:
        /* in-call modification, CC暂不支持 */
        break;

    case MNCC_MODIFY_REJ_IND:
        /* in-call modification, CC暂不支持 */
        break;

    case MNCC_SYNC_IND:
        MN_CALL_ProcMnccSyncInd(pstMnccMsg);
        break;

    case MNCC_PROGRESS_IND:
        MN_CALL_ProcMnccProgressInd(pstMnccMsg);
        break;

    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    case MNCC_CC_EST_IND:

        /*如果控制CCBS的NV打开，则处理*/
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            MN_CALL_ProcMnccEstInd(pstMnccMsg);
        }
        break;

    case MNCC_RECALL_IND:

        /*如果控制CCBS的NV打开，则处理*/
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            MN_CALL_ProcMnccRecallInd(pstMnccMsg);
        }
        break;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    case MNCC_UUSINFO_IND:
        MN_CALL_ProcUusInfoInd(pstMnccMsg);
        break;

    case MNCC_EMERGENCY_LIST_IND:
        MN_CALL_ProcEmergencyListInd(pstMnccMsg);
        break;

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, begin */
#if (FEATURE_ON == FEATURE_IMS)
    case MNCC_SRVCC_STATUS_IND:
        TAF_CALL_ProcMnccSrvccStatusInd((MNCC_SRVCC_STATUS_IND_STRU*)&(pstMnccMsg->unParam.stSrvccStaInd));
        break;
#endif
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, end */

    default:
        MN_WARN_LOG("MN_CALL_ProcAppReqMsg:Invalid Msg Name");
        break;
    }

}

/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
/* 删除该函数 */
/* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */

/*****************************************************************************
 函 数 名  : MN_CALL_ProcVCMsg
 功能描述  : 处理来自VC模块的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年1月10日
    作    者   : 丁庆 49431
    修改内容   : 新生成函数
  2.日    期   : 2012年09月18日
    作    者   : y00213812
    修改内容   : STK&DCM 项目CS域错误码上报，修改上报初始值
  3.日    期   : 2013年9月17日
    作    者   : f62575
    修改内容   : DTS2013091104858，挂机前结束完成的用户请求
  4.日    期   : 2014年04月15日
    作    者   : y00245242
    修改内容   : 为eCall feature功能修改
*****************************************************************************/
VOS_VOID  MN_CALL_ProcVCMsg (VOS_VOID * pstMsg)
{
    VC_CALL_MSG_STRU                    *pstTmpMsg;
    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-4, end */

    pstTmpMsg = (VC_CALL_MSG_STRU*)pstMsg;

    switch(pstTmpMsg->enMsgName)
    {
        case VC_CALL_END_CALL:
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-4, begin */
            TAF_CALL_RcvVcCallEndCall(pstTmpMsg);
            /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-4, end */
            break;

        /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-1, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        case VC_CALL_ECALL_TRANS_STATUS_NTF:
            TAF_CALL_RcvVcEcallTransStatusNtf((VC_CALL_ECALL_TRANS_STATUS_NTF_STRU *)pstMsg);
            break;
#endif
        /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-1, end */

        default:
            MN_WARN_LOG1("MN_CALL_ProcVCMsg:Wrong Msg.", pstTmpMsg->enMsgName);
            break;
    }
}

/* Deleted by wx270776 for OM融合, 2015-7-10, begin */


/* Deleted by wx270776 for OM融合, 2015-7-10, end */
/*****************************************************************************
 函 数 名  : MN_CALL_ProcOmConfigGsmCodec
 功能描述  : 处理并回复OM发送过来的配置GSM CODEC类型的请求
 输入参数  : pstMsg - OM 发送过来的设置消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月9日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2015年07月24日
    作    者   : wx270776
    修改内容   : OM融合
*****************************************************************************/
VOS_VOID MN_CALL_ProcOmConfigGsmCodec(
    ID_NAS_OM_INQUIRE_STRU              *pstMsg
)
{
    /* Modified by wx270776 for OM融合, 2015-7-25, begin */
    NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU *pstCodecConfigReq = VOS_NULL_PTR;
    NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU *pstCodecConfigCnf = VOS_NULL_PTR;
    VOS_UINT32                            ulMsgLen;
    VOS_UINT32                            ulRet;

    /* 申请消息 */
    ulMsgLen          = sizeof(NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCodecConfigCnf = (NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU*)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pstCodecConfigCnf)
    {
         MN_ERR_LOG("MN_CALL_ProcOmConfigGsmCodec:Error: Memory Alloc fail");
         return;
    }

    /* 初始化 */
    PS_MEM_SET((VOS_UINT8*)pstCodecConfigCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    pstCodecConfigReq = (NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU*)pstMsg;

    /* 填写消息内容 */
    pstCodecConfigCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstCodecConfigCnf->ulMsgId          = ID_NAS_OM_SET_CODEC_TYPE_CONFIRM;
    pstCodecConfigCnf->usOriginalId     = pstMsg->usOriginalId;
    pstCodecConfigCnf->usTerminalId     = pstMsg->usTerminalId;
    pstCodecConfigCnf->ulTimeStamp      = pstMsg->ulTimeStamp;
    pstCodecConfigCnf->ulSN             = pstMsg->ulSN;

    /* 商用版本防止误配置，当只配置支持部分语音编码模式时直接返回失败 */
    if (NAS_OM_GSM_CODEC_FR_EFR_HR_AMR != pstCodecConfigReq->enGsmCodec)
    {
        MN_WARN_LOG("MN_CALL_ProcOmConfigGsmCodec:GsmCodec is not NAS_OM_GSM_CODEC_FR_EFR_HR_AMR");

        pstCodecConfigCnf->ulRet = VOS_ERR;

        /* 发送消息 */
        PS_SEND_MSG(WUEPS_PID_TAF, pstCodecConfigCnf);

        return;
    }

    ulRet = MN_CALL_ConfigGsmCapaProc(pstCodecConfigReq->enGsmCodec);
    if ( VOS_OK ==  ulRet)
    {
        pstCodecConfigCnf->ulRet = VOS_OK;
    }
    else
    {
        pstCodecConfigCnf->ulRet = VOS_ERR;
    }

    /* 发送消息 */
    PS_SEND_MSG(WUEPS_PID_TAF, pstCodecConfigCnf);

    return;
    /* Modified by wx270776 for OM融合, 2015-7-25, end */
}

/*****************************************************************************
 函 数 名  : MN_CALL_ProcOmCodecRpt
 功能描述  : 处理OM发送过来的查询当前CODEC类型和配置的GSM的CODEC类型
 输入参数  : pstMsg - OM 发送过来的查询消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月9日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数
  2.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2015年7月13日
    作    者   : wx270776
    修改内容   : OM融合
*****************************************************************************/
VOS_VOID MN_CALL_ProcOmCodecRpt(
    ID_NAS_OM_INQUIRE_STRU              *pstMsg
)
{
    /* Modified by wx270776 for OM融合, 2015-7-13, begin */
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulRet;
    NAS_OM_CODEC_TYPE_CNF_STRU         *pstCodecTypeCnf = VOS_NULL_PTR;
    MN_CALL_CHANNEL_PARAM_STRU          stChannParm;



    /* 申请内存 */
    ulMsgLen        = sizeof(NAS_OM_CODEC_TYPE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCodecTypeCnf = (NAS_OM_CODEC_TYPE_CNF_STRU*)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pstCodecTypeCnf)
    {
        MN_ERR_LOG("MN_CALL_ProcOmCodecRpt:Error: Memory Alloc fail");
        return;
    }

    /* 初始化 */
    PS_MEM_SET((VOS_UINT8*)pstCodecTypeCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    /* 填充消息 */
    pstCodecTypeCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstCodecTypeCnf->ulMsgId          = ID_NAS_OM_CODEC_TYPE_CONFIRM;
    pstCodecTypeCnf->usOriginalId     = pstMsg->usOriginalId;
    pstCodecTypeCnf->usTerminalId     = pstMsg->usTerminalId;
    pstCodecTypeCnf->ulTimeStamp      = pstMsg->ulTimeStamp;
    pstCodecTypeCnf->ulSN             = pstMsg->ulSN;

    ulRet = MN_CALL_GetTchParm(&stChannParm);
    if( VOS_OK == ulRet )
    {
        pstCodecTypeCnf->enCurrCodec = MN_CALL_ConvertMnCodecToOmCodec(stChannParm.enCodecType);
    }
    else
    {
        pstCodecTypeCnf->enCurrCodec  = NAS_OM_CODEC_TYPE_BUTT;
    }

    pstCodecTypeCnf->enGsmCodecConfig = MN_CALL_ConvertSpeechVers();

    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstCodecTypeCnf);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_CALL_ProcOmCodecRpt:Warning Send msg fail.");
    }

    return;
    /* Modified by wx270776 for OM融合, 2015-7-13, end */
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcOmMsg
 功能描述  : CALL模块处理来自OM的请求
 输入参数  : pstMsg     - OM发送过来的消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月8日
    作    者   : zhoujun /z40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_CALL_ProcOmMsg(
    VOS_VOID                            *pstMsg
)
{
    ID_NAS_OM_INQUIRE_STRU              *pstOmInquire;

    pstOmInquire = (ID_NAS_OM_INQUIRE_STRU *)pstMsg;

    switch ( pstOmInquire->ulMsgId)
    {
        case ID_NAS_OM_SET_CODEC_TYPE_REQUIRE :
            MN_CALL_ProcOmConfigGsmCodec(pstOmInquire);
            break;

        case ID_NAS_OM_CODEC_TYPE_INQUIRE :
            MN_CALL_ProcOmCodecRpt(pstOmInquire);
            break;

        default:
            MN_NORM_LOG("MN_CALL_ProcOmMsg:wrong PrimId!");
            break;
    }

}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcCstCcPrimitive
 功能描述  : 处理CST模块发来的消息原语
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月19日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcCstCallPrimitive(
    const VOS_VOID                      *pMsg
)
{
    VOS_UINT16                           usMsgType;

    usMsgType =  *((VOS_UINT16*)((VOS_UINT8*)pMsg + VOS_MSG_HEAD_LENGTH));

    MN_INFO_LOG1("MN_CALL_ProcCstCcPrimitive: primitive:", (VOS_INT32)(usMsgType));

    switch ( usMsgType )
    {
        case ID_CST_CALL_ERROR_IND :
            MN_CALL_ProcCstErrorInd(pMsg);
            break;

        case ID_CST_CALL_SETUP_CNF :
            MN_CALL_ProcCstSetupCnf(pMsg);
            break;

        default:
            MN_WARN_LOG1("MN_CALL_ProcCstCcPrimitive: wrong enMsgID:",  (VOS_INT32)(usMsgType));
            break;
    }
}





/*****************************************************************************
 函 数 名  : MN_CALL_ProcRabmCallSyncInd
 功能描述  : 处理来自Rabm的消息RABM_CALL_SYNC_IND。
 输入参数  : pMsg  - 消息内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月19日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2010年11月11日
    作    者   : h44270
    修改内容   : 问题单号：DTS2010102202190/DTS2010110600922，出现ERROR打印
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2014年6月11日
    作    者   : y00245242
    修改内容   : DTS2014060306029
*****************************************************************************/
VOS_VOID  MN_CALL_ProcRabmCallSyncInd(
    const VOS_VOID                      *pMsg
)
{
    RABM_CALL_SYNC_IND_STRU             *pstSyncMsg;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           ucCallId;
    VOS_BOOL                            bWaitSendAlertStatus;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    pstSyncMsg = (RABM_CALL_SYNC_IND_STRU*)pMsg;

    /*
       当指示rab激活，有RB存在，并且当前有呼叫，并且呼叫类型是video call
       的时候，刷新呼叫模块管理实体中对应rb值
       由于VP下CC不会有sync_ind上报，因此增加alerting的发送
    */
    if (RABMCALL_RAB_ACTIVE == pstSyncMsg->ulRabState)
    {
        if (0 != pstSyncMsg->ulRbNum)
        {
            MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
            for (i = 0; i < ulNumOfCalls; i++)
            {
                enCallType = MN_CALL_GetCallType(aCallIds[i]);
                if ( MN_CALL_TYPE_VIDEO == enCallType )
                {
                    MN_CALL_UpdateRbId(aCallIds[i], pstSyncMsg->aulRbId[0]);
                    MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &ucCallId);
                    if ((MN_CALL_DIR_MT == MN_CALL_GetCcCallDir(aCallIds[i]))
                      &&(VOS_TRUE == bWaitSendAlertStatus)
                      &&(aCallIds[i] == ucCallId))
                    {
                        (VOS_VOID)MN_CALL_SendCcAlertReq(aCallIds[i]);
                        MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, ucCallId);

                        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_INCOMING);

                        MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_NOLOOP);
                    }

                    return;
                }
            }
        }
    }
}


/*****************************************************************************
 函 数 名  : MN_CALL_ProcRabmCallPrimitive
 功能描述  : 处理来自Rabm的消息。
 输入参数  : pMsg  - 消息内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月19日
    作    者   : h44270
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  MN_CALL_ProcRabmCallPrimitive(
    const VOS_VOID                      *pMsg
)
{
    MSG_HEADER_STRU                     *pstTmpMsg;

    pstTmpMsg = (MSG_HEADER_STRU*)pMsg;

    switch ( pstTmpMsg->ulMsgName)
    {
        case RABM_CALL_SYNC_IND:
            MN_CALL_ProcRabmCallSyncInd(pMsg);
            break;

        default:
            /*异常打印*/
            MN_WARN_LOG1( "MN_CALL_ProcRabmCallPrimitive: wrong MsgName:",
                          (VOS_INT32)(pstTmpMsg->ulMsgName));
            break;
    }

}

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */


/* MN_CALL_ProcUsimFdnInd */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, begin */
/*****************************************************************************
 函 数 名  : TAF_CALL_ProcTafMsg
 功能描述  : 处理来自TAF内部发起的CALL请求消息
 输入参数  : pMsg  - 消息内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月26日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_ProcTafMsg (
    const VOS_VOID                      *pMsg
)
{
    MSG_HEADER_STRU                     *pstTmpMsg = VOS_NULL_PTR;

    pstTmpMsg = (MSG_HEADER_STRU*)pMsg;

    switch (pstTmpMsg->ulMsgName)
    {
        case TAF_CALL_TAF_REL_CALL_REQ:
#if (FEATURE_ON == FEATURE_ECALL)
            TAF_CALL_RcvTafRelCallReq((TAF_CALL_TAF_REL_CALL_REQ_STRU *)pMsg);
#endif
            break;

        default:
            TAF_CSCALL_ProcAppReqMsg((struct MsgCB *)pMsg);
            break;
    }
}

/*****************************************************************************
 函 数 名  : TAF_CALL_ProcMmaMsg
 功能描述  : 处理来自MMA的消息
 输入参数  : pMsg  - 消息内容
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年4月26日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_CALL_ProcMmaMsg (
    const VOS_VOID                      *pMsg
)
{
    MSG_HEADER_STRU                    *pstTmpMsg = VOS_NULL_PTR;

    pstTmpMsg = (MSG_HEADER_STRU*)pMsg;

    switch (pstTmpMsg->ulMsgName)
    {
        case MMA_TAF_POWER_OFF_IND:
            TAF_CALL_RcvMmaPowerOffInd((TAF_MMA_POWER_OFF_IND_STRU *)pMsg);
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case ID_MMA_TAF_SYS_CFG_INFO_IND:
            TAF_CALL_RcvMmaSyscfgInfoInd((MMA_TAF_SYS_CFG_INFO_IND_STRU *)pMsg);
            break;
#endif
        default:
            break;
    }

}

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-26, end */

/*****************************************************************************
 函 数 名  : MN_CALL_DispatchUsimMsg
 功能描述  : 处理从USIM过来的消息
 输入参数  : pstMsg - 收到的消息
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年02月23日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数
  2.日    期   : 2012年09月20日
    作    者   : f62575
    修改内容   : STK&DCM 项目
  3.日    期   : 2013年6月5日
    作    者   : z00161729
    修改内容   : SVLTE 和usim接口调整修改
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级 Deleted PS_USIM_ENVELOPE_CNF
*****************************************************************************/
VOS_VOID MN_CALL_DispatchUsimMsg(struct MsgCB * pstMsg)
{

    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */
    /* 预留后续使用 */
    /* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

    return;
}




/*****************************************************************************
 函 数 名  : MN_CALL_SupportMoCallType
 功能描述  : 获取UE对指定呼叫类型的支持状态
 输入参数  : MN_CALL_TYPE_ENUM_U8                enCallType  呼叫类型
 输出参数  : VOS_BOOL                           *pSupported  UE是否支持指定的呼叫类型
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    作    者   : f62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_SupportMoCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    VOS_BOOL                           *pSupported
)
{
    if ((MN_CALL_TYPE_VOICE == enCallType)
     || (MN_CALL_TYPE_EMERGENCY == enCallType))
    {
        *pSupported = VOS_TRUE;
    }
    else
    {
        *pSupported = VOS_FALSE;
    }
}


/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII 项目, 2013-12-14, end */

/*****************************************************************************
 函 数 名  : MN_CALL_ReportErrCauseInd
 功能描述  : CS域原因值上报
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月18日
    作    者   : y00213812
    修改内容   : STK&DCM 项目新增函数

*****************************************************************************/


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 函 数 名  : MN_CALL_CsCallErrRecord
 功能描述  : 记录CS呼叫异常事件
 输入参数  : MN_CALL_ID_T                        ucCallId,
             TAF_CS_CAUSE_ENUM_UINT32            enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月23日
    作    者   : s00190137
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID MN_CALL_CsCallErrRecord(
    MN_CALL_ID_T                        ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    NAS_ERR_LOG_CS_CALL_FAIL_EVENT_STRU                     stCsCallFailEvent;
    MN_CALL_INFO_STRU                                       stCallInfo;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CS_CALL_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 不需要记录或没有异常时，不保存异常信息 */
    if ((VOS_FALSE == ulIsLogRecord)
     || (TAF_CS_CAUSE_SUCCESS == enCause)
     || (TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING == enCause))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CS_CALL_FAIL_EVENT_STRU);

    /* 填充Cs呼叫失败异常信息 */
    PS_MEM_SET(&stCsCallFailEvent, 0x00, ulLength);
    PS_MEM_SET(&stCallInfo, 0x00, sizeof(stCallInfo));

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsCallFailEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_CS_CALL_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stCsCallFailEvent.ulCcCause = enCause;

    if (0 == ucCallId)
    {
        /* ucCallId为0说明为本地异常，无法在全局变量中获取信息 */
        stCsCallFailEvent.ucCallId            = ucCallId;
        stCsCallFailEvent.enCallState         = NAS_ERR_LOG_CALL_S_IDLE;
        stCsCallFailEvent.stDiscDir.ucIsUser  = VOS_TRUE;
    }
    else
    {
        MN_CALL_GetCallInfoByCallId(ucCallId, &stCallInfo);

        stCsCallFailEvent.ucCallId    = stCallInfo.callId;
        stCsCallFailEvent.enCallState = stCallInfo.enCallState;
        PS_MEM_CPY(&stCsCallFailEvent.stDiscDir, &stCallInfo.stDiscDir, sizeof(NAS_ERR_LOG_MN_CALL_DISC_DIR_STRU) );
    }

    stCsCallFailEvent.enRat = TAF_SDC_GetSysMode();

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stCsCallFailEvent.stPositionInfo);

    /* 获取当前Usim信息 */
    NAS_MMA_OutputUsimInfo(&stCsCallFailEvent.stUsimInfo);

    stCsCallFailEvent.usCellDlFreq = TAF_SDC_GetAppCellDlFreq();
    stCsCallFailEvent.usCellUlFreq = TAF_SDC_GetAppCellUlFreq();

    /* 如果当前为被叫，且不是active状态，则主动上报给上层该次异常 */
    if ((MN_CALL_S_INCOMING       == stCallInfo.enCallState)
     || (MN_CALL_S_WAITING        == stCallInfo.enCallState)
     || (MN_CALL_S_WAITING_ACCEPT == stCallInfo.enCallState))
    {
        TAF_SndAcpuOmFaultErrLogInd(&stCsCallFailEvent, ulLength, NAS_ERR_LOG_ALM_CS_CALL_FAIL);
    }

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stCsCallFailEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CsCallErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CS_CALL_FAIL,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stCsCallFailEvent,
                           sizeof(stCsCallFailEvent));
    return;
}

/*****************************************************************************
 函 数 名  : MN_CALL_CsMtCallFailRecord
 功能描述  : 记录CS MT CALL FAIL异常事件
 输入参数  : enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年09月22日
   作    者   : f00179208
   修改内容   : 新生成函数
 2.日    期   : 2015年07月06日
   作    者   : n00269697
   修改内容   : ERR LOG上报类型分为故障上报和告警上报
*****************************************************************************/
VOS_VOID MN_CALL_CsMtCallFailRecord(
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
)
{
    NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU  stCsMtCallFailEvt;
    VOS_UINT32                              ulLength;
    VOS_UINT16                              usLevel;
    VOS_UINT32                              ulIsLogRecord;
    VOS_UINT32                              ulResult;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU);

    /* 填充CS PAGING失败异常信息 */
    PS_MEM_SET(&stCsMtCallFailEvt, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsMtCallFailEvt.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stCsMtCallFailEvt.stPositionInfo);

    /* 填写错误原因值 */
    stCsMtCallFailEvt.enCause = enCause;

    /* 将CS MT CALL失败信息发送给ACPU OM模块 */
    TAF_SndAcpuOmFaultErrLogInd(&stCsMtCallFailEvt, ulLength, NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL);

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stCsMtCallFailEvt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_SndAcpuOmCsMtCallFailInd(): Push buffer error.");
    }

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stCsMtCallFailEvt,
                           sizeof(stCsMtCallFailEvt));

    return;
}

/*****************************************************************************
 函 数 名  : MN_CALL_CsCallDiscInfoRecord
 功能描述  : 记录NAS_ERR_LOG_ALM_PORCESS_INFO_IND异常事件
 输入参数  : ucCallId
             enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年09月18日
   作    者   : f00179208
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID MN_CALL_CsCallDiscInfoRecord(
    MN_CALL_ID_T                            ucCallId,
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
)
{
    NAS_ERR_LOG_PROCESS_INFO_IND_EVENT_STRU stProcInfoEvent;
    VOS_UINT32                              ulLength;
    VOS_UINT16                              usLevel;
    VOS_UINT32                              ulIsLogRecord;
    VOS_UINT32                              ulResult;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PORCESS_INFO_IND);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PROCESS_INFO_IND_EVENT_STRU);

    /* 填充过程信息 */
    PS_MEM_SET(&stProcInfoEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stProcInfoEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_PORCESS_INFO_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stProcInfoEvent.enInfoType          = NAS_ERR_LOG_PROCESS_INFO_TYPE_CS_CALL_DISC;
    stProcInfoEvent.stDiscInfo.ucCallId = ucCallId;
    stProcInfoEvent.stDiscInfo.ulCause  = enCause;

    /*
       将异常信息写入Buffer中
       实际写入的字符数与需要写入的不等则打印异常
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stProcInfoEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CsCallDiscInfoRecord(): Push buffer error.");
    }

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PORCESS_INFO_IND,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stProcInfoEvent,
                           sizeof(stProcInfoEvent));

    return;
}

#endif
/*lint -restore */


/*****************************************************************************
函 数 名  : TAF_CALL_GetTTYMode
功能描述  : 获取当前TTY MODE
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2015年02月07日
    作    者   : w00316404
    修改内容   : 新增函数
*****************************************************************************/
TAF_VC_TTYMODE_ENUM_UINT8 TAF_CALL_GetTTYMode(VOS_VOID)
{
    TAF_NV_TTY_CFG_STRU                 stTTYCfgStru;

    /* 参数初始化 */
    PS_MEM_SET(&stTTYCfgStru, 0x00, sizeof(TAF_NV_TTY_CFG_STRU));

    /* 读取NV项 */
    if (NV_OK != NV_Read(en_NV_Item_TTY_Mode,
                         &stTTYCfgStru,
                         sizeof(TAF_NV_TTY_CFG_STRU)))
    {
        return TAF_VC_TTYMODE_BUTT;
    }

    if ( stTTYCfgStru.ucTTYMode >= TAF_VC_TTYMODE_BUTT )
    {
        return TAF_VC_TTYMODE_BUTT;
    }

    return (TAF_VC_TTYMODE_ENUM_UINT8)stTTYCfgStru.ucTTYMode;
}

/*****************************************************************************
函 数 名  : TAF_CALL_IsSupportTTYMode
功能描述  : 判断是否支持TTY模式
输入参数  : 无
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :
修订记录  :
1.  日    期   : 2015年02月07日
    作    者   : l00198894
    修改内容   : 新增函数
*****************************************************************************/
VOS_BOOL TAF_CALL_IsSupportTTYMode(VOID)
{
    TAF_VC_TTYMODE_ENUM_UINT8           enTTYMode;

    enTTYMode = TAF_CALL_GetTTYMode();

    if (TAF_VC_TTY_OFF == enTTYMode || TAF_VC_TTYMODE_BUTT <= enTTYMode)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
