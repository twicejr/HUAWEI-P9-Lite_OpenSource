/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name:          SmsMain.c
  Description:        SMS的入口，初始化及消息分发函数
  Function List:
               1. SMS_TaskEntry
               2. SMS_InitEntity
               3. SMS_SmrRcvTafMsgDistr
               4. SMC_RcvGmmMsgDistr
               5. SMC_RcvMmMsgDistr
               6. SMS_TimerMsgDistr
               7. SMS_TimerStop
               8. SMS_TimerStart
               9. Nas_Sms_Print

  History:
  1.  张志勇      2004.03.09   新规作成
  2.  郜东东   2005-10-19   根据问题单A32D00636修改
  3. Date         : 2007-04-06
     Author       : h44270
     Modification : 问题单号:A32D10113
  4. Date:          2007-06-11'
     Author:        z40661
     Modification:  A32D11581
  5. Date         : 2007-08-20
     Author       : z40661
     Modification : A32D12705
  6.日    期   : 2007年8月28日
    作    者   : l60022475
    修改内容   : 问题单号：A32D12744,初始化SMS Timer句柄
  7.日    期   : 2008年09月08日
    作    者   : f62575
    修改内容   : 问题单AT2D05583,CBS功能模块代码PC-lint错误
  8.日    期   : 2009年02月12日
    作    者   : f62575
    修改内容   : 问题单A32D08966，参考V1R1版本的清除PC-LINT告警方式清除V2R1版本和V1R2版本告警
  9.日    期   : 2009年3月23日
    作    者   : f62575
    修改内容   : AT2D08752, W接入方式下，信号较弱时连续发送多条短信会概率性出现发送操作失败；
 10.日    期   : 2009年6月29日
    作    者   : f62575
    修改内容   : AT2D12568, 短信收发过程中软关机会导致SMS和TAF模块短信收发相关状态错误；
 11.日    期   : 2010年2月20日
    作    者   : f62575
    修改内容   : AT2D16941，增加短信任意点回放功能
*******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "smsinclude.h"
#include "LLInterface.h"
#include "NasGmmInterface.h"
#include "TafCbsInterface.h"
#if   (FEATURE_ON == FEATURE_LTE)
#include "LmmSmsInterface.h"
#endif
#include "SysNvId.h"
#include "NVIM_Interface.h"

/* Added by l00167671 for NV拆分项目 , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV拆分项目 , 2013-05-17, end*/

#include "TafMmaInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_SMS_MAIN_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

NAS_SMS_PS_CONCATENATE_ENUM_UINT8   g_enNasSmsPsConcatencateFlag = NAS_SMS_PS_CONCATENATE_DISABLE;

VOS_UINT32                          g_ulNasSmsFilterEnableFlg   = VOS_FALSE;


/*****************************************************************************
  3 类型定义
*****************************************************************************/
/*****************************************************************************
 Structure      : NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST
 Description    : PC回放工程，存储所有AT相关的全局变量，目前仅有短信相关全局变量
 Message origin :
 Note:
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           g_ucPsServiceStatus;                 /* GMM的PS域是否注册标志                    */
    VOS_UINT8                           g_ucCsRegFlg;                         /* MM的CS域是否注册标志                    */
    VOS_UINT8                           g_ucSmsMR;                            /* SMR层维护的短消息标识0～255              */
    VOS_UINT8                           g_SndDomain;                          /* 发送域 */
    SMR_ENTITY_STRU                     g_SmrEnt;                              /* smr的实体定义                            */
    SMC_ENTITY_STRU                     g_SmcPsEnt;                           /* sms ps域的实体定义                       */
    SMC_ENTITY_STRU                     g_SmcCsEnt;                           /* sms cs域的实体定义                       */
}NAS_SMS_OUTSIDE_RUNNING_CONTEXT_PART_ST;

/*****************************************************************************
 Structure      : NAS_AT_SDT_AT_PART_ST
 Description    : PC回放工程，所有AT相关的全局变量通过以下消息结构发送
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                   ulMsgName;
    NAS_SMS_OUTSIDE_RUNNING_CONTEXT_PART_ST      stOutsideCtx;
}NAS_SMS_SDT_SMS_PART_ST;

/*****************************************************************************
 结构名    : NAS_SMS_LOG_STATE_INFO_STRU
 结构说明  : 勾SMS的状态的结构

 修改记录  :
 1.日    期   : 2014年06月30日
   作    者   : w00242748
   修改内容   : 新增

*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头 */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucSmsState;
    VOS_UINT8                           aucRsv3[3];
}NAS_SMS_LOG_STATE_INFO_STRU;

#define SMS_PC_REPLAY_MSG               0xffffffff          /* 为PC工程回放定义的消息 */
LOCAL SMS_TIMER_LENGTH_STRU                      f_stNasSmsTimerLength;
LOCAL VOS_UINT8                                  f_ucNasSmsTc1mMaxExpTimes;

/*lint -save -e958 */

/*****************************************************************************
  5 函数实现
*****************************************************************************/

#ifdef __PS_WIN32_RECUR__
/*****************************************************************************
 函 数 名  : NAS_SMS_RestoreContextData
 功能描述  : 恢复SMS全局变量。
 输入参数  : struct MsgCB *pstMsg
 输出参数  : 无
 返 回 值  : VOS_OK 数据恢复成功,否则,失败;
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年02月12日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_SMS_RestoreContextData(
    struct MsgCB                        *pstMsg
)
{
    NAS_SMS_SDT_SMS_PART_ST                       *pstRcvMsgCB;
    NAS_SMS_OUTSIDE_RUNNING_CONTEXT_PART_ST       *pstOutsideCtx;

    pstRcvMsgCB     = (NAS_SMS_SDT_SMS_PART_ST *)pstMsg;

    if (SMS_PC_REPLAY_MSG == pstRcvMsgCB->ulMsgName)
    {
        pstOutsideCtx = &pstRcvMsgCB->stOutsideCtx;

        PS_MEM_CPY(&g_SmcPsEnt,&pstOutsideCtx->g_SmcPsEnt,sizeof(g_SmcPsEnt));
        PS_MEM_CPY(&g_SmcCsEnt,&pstOutsideCtx->g_SmcCsEnt, sizeof(g_SmcCsEnt));
        PS_MEM_CPY(&g_SmrEnt, &pstOutsideCtx->g_SmrEnt, sizeof(g_SmrEnt));
        g_ucPsServiceStatus = pstOutsideCtx->g_ucPsServiceStatus;
        g_ucCsRegFlg = pstOutsideCtx->g_ucCsRegFlg;
        g_ucSmsMR = pstOutsideCtx->g_ucSmsMR;
        g_SndDomain = pstOutsideCtx->g_SndDomain;

        SMS_LOG(PS_LOG_LEVEL_INFO, "MSG: NAS_SMS_RestoreContextData data is restored.");
    }

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_SMS_SndOutsideContextData
 功能描述  : 把SMS外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2010年02月12日
    作    者   : 傅映君 62575
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_SMS_SndOutsideContextData()
{
    NAS_SMS_SDT_SMS_PART_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_SMS_OUTSIDE_RUNNING_CONTEXT_PART_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_SMS_SDT_SMS_PART_ST *)PS_ALLOC_MSG(WUEPS_PID_SMS,
                                            sizeof(NAS_SMS_SDT_SMS_PART_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        SMS_LOG(PS_LOG_LEVEL_ERROR, "NAS_SMS_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pSndMsgCB->ulReceiverPid = WUEPS_PID_SMS;
    pSndMsgCB->ulSenderPid   = WUEPS_PID_SMS;
    pSndMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength = sizeof(NAS_SMS_OUTSIDE_RUNNING_CONTEXT_PART_ST) + 4;
    pSndMsgCB->ulMsgName = SMS_PC_REPLAY_MSG;

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    PS_MEM_CPY(&pstOutsideCtx->g_SmcPsEnt, &g_SmcPsEnt, sizeof(g_SmcPsEnt));
    PS_MEM_CPY(&pstOutsideCtx->g_SmcCsEnt, &g_SmcCsEnt, sizeof(g_SmcCsEnt));
    PS_MEM_CPY(&pstOutsideCtx->g_SmrEnt, &g_SmrEnt, sizeof(g_SmrEnt));
    pstOutsideCtx->g_ucPsServiceStatus  = g_ucPsServiceStatus;
    pstOutsideCtx->g_ucCsRegFlg         = g_ucCsRegFlg;
    pstOutsideCtx->g_ucSmsMR            = g_ucSmsMR;
    pstOutsideCtx->g_SndDomain          = g_SndDomain;

    DIAG_TraceReport(pSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_SMS, pSndMsgCB);

    return;
}


/*******************************************************************************
  Module:   SMS_TaskEntry
  Function: SMS模块TASK入口处理
  Input:    struct MsgCB* pMsg-----------消息指针
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2005.01.28   新规作成
      2.  张志勇  2005.03.08   使用PID进行分发处理
*******************************************************************************/

#define     SMS_TASK_NOT_START       0                                          /* TASK SMS 没有启动                        */
#define     SMS_TASK_START           1                                          /* TASK SMS 已经启动                        */
VOS_UINT8   g_SmsStartFlg = SMS_TASK_NOT_START;                                 /* TASK SMS 启动标志                        */

/*******************************************************************************
  Module:      SMS_ReportN2MOtaMsg
  Function:    在trace中勾取SMS的空口消息
  Input:       NAS_MSG_STRU*   pNasMsg     SMS空口消息
  NOTE:
  Return:      VOS_VOID
  History:
      1. 鲁琳    2009.07.11   新规作成
*******************************************************************************/
VOS_VOID SMS_ReportN2MOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMS_ReportN2MOtaMsg:NORMAL: msg type is ", pNasMsg->aucNasMsg[1]);

    switch(pNasMsg->aucNasMsg[1])
    {
        case SMC_DATA_TYPE_CP_DATA:
          	usNasOtaMsyId = NAS_OTA_MSG_SMS_DATA_TYPE_CP_DATA_DOWN;
            break;

        case SMC_DATA_TYPE_CP_ACK:
           	usNasOtaMsyId = NAS_OTA_MSG_SMS_DATA_TYPE_CP_ACK_DOWN;
            break;

        case SMC_DATA_TYPE_CP_ERR:
            usNasOtaMsyId = NAS_OTA_MSG_SMS_DATA_TYPE_CP_ERROR_DOWN;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMS_ReportN2MOtaMsg:WARNING: invalid msg id");
            /*不属于SMS的空口消息，不在trace中显示*/
            return;
    }

    if (VOS_FALSE == g_ulNasSmsFilterEnableFlg)
    {
        NAS_SendAirMsgToOM(WUEPS_PID_SMS, usNasOtaMsyId, NAS_OTA_DIRECTION_DOWN, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
    }
}


/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */

/*****************************************************************************
 函 数 名  : NAS_SMS_BuildSmsOmInfo
 功能描述  : 构造填写给OM查询SMS的消息内容
 输入参数  : 无
 输出参数  : pstMsg:待填写的消息内容
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年06月28日
   作    者   : luokaihui 00167671
   修改内容   : 新生成函数
 2.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目
*****************************************************************************/

VOS_VOID NAS_SMS_BuildSmsOmInfo(
    NAS_OM_SMS_IND_STRU                *pstMsg
)
{
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    pstMsg->enSmcCsMoState = g_SmcCsEnt.SmcMo.ucState;
    pstMsg->enSmcCsMtState = g_SmcCsEnt.SmcMt.ucState;
    pstMsg->enSmcPsMoState = g_SmcPsEnt.SmcMo.ucState;
    pstMsg->enSmcPsMtState = g_SmcPsEnt.SmcMt.ucState;
    pstMsg->enSmrMoState   = g_SmrEnt.SmrMo.ucState;
    pstMsg->enSmrMtState   = g_SmrEnt.SmrMt.ucState;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
}

/* Added by wx270776 for OM融合, 2015-7-21, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmSmsIndMsg
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
VOS_UINT32 NAS_MMC_SndOmSmsIndMsg(VOS_VOID)
{
    NAS_OM_SMS_IND_STRU                 stNasOmSmsInd;
    DIAG_TRANS_IND_STRU                 stDiagTransInd;
    VOS_UINT32                          ulRet;

    /* 初始化 */
    PS_MEM_SET(&stNasOmSmsInd, 0x00, sizeof(NAS_OM_SMS_IND_STRU));

    /* 填充消息内容 */
    NAS_SMS_BuildSmsOmInfo(&stNasOmSmsInd);
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    stNasOmSmsInd.enPrimId          = ID_NAS_OM_SMS_CONFIRM;
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */
    stNasOmSmsInd.usToolsId         = 0;

    stDiagTransInd.ulModule         = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_SMS), DIAG_MODE_UMTS);;
    stDiagTransInd.ulPid            = WUEPS_PID_SMS;
    /* Modified by zwx247453 for 寄存器上报, 2015-11-09, begin */
    stDiagTransInd.ulMsgId          = ((VOS_UINT32)(VOS_GetModemIDFromPid(WUEPS_PID_SMS)) << 16) + ID_NAS_OM_SMS_CONFIRM;
    /* Modified by zwx247453 for 寄存器上报, 2015-11-09, end */
    stDiagTransInd.ulLength         = sizeof(NAS_OM_SMS_IND_STRU);
    stDiagTransInd.pData            = &stNasOmSmsInd;

    /* 发送消息 */
    ulRet = DIAG_TransReport(&stDiagTransInd);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_MMC_SndOmSmsIndMsg:WARNING: Send msg fail.");
    }

    return ulRet;
}
/* Added by wx270776 for OM融合, 2015-7-21, end */

/*****************************************************************************
 函 数 名  : NAS_SMS_SndOmInquireCnfMsg
 功能描述  : 发送OM的查询消息回复
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : luokaihui l00167671
   修改内容   : 新生成函数

 2.日    期   : 2015年07月01日
   作    者   : wx270776
   修改内容   : OM融合

*****************************************************************************/
VOS_VOID NAS_SMS_SndOmInquireCnfMsg(
    ID_NAS_OM_INQUIRE_STRU             *pstOmInquireMsg
)
{
    /* Modified by wx270776 for OM融合, 2015-7-1, begin */
    VOS_UINT32                          ulMsgLen;
    NAS_OM_SMS_CONFIRM_STRU            *pstNasOmSmsCnf;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSndOmRet;

    /* 1. 向OM发送IND消息 */
    ulSndOmRet = NAS_MMC_SndOmSmsIndMsg();

    /* 2. 向工具侧回复CNF消息 */
    /* 申请消息 */
    ulMsgLen       = sizeof(NAS_OM_SMS_CONFIRM_STRU) - VOS_MSG_HEAD_LENGTH;

    pstNasOmSmsCnf = (NAS_OM_SMS_CONFIRM_STRU*)PS_ALLOC_MSG(WUEPS_PID_SMS, ulMsgLen);
    if (VOS_NULL_PTR == pstNasOmSmsCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_SMS, "NAS_MMC_SndOmInquireCnfMsg:Memory Allocate fail!");
        return;
    }

    /* 初始化 */
    PS_MEM_SET((VOS_UINT8*)pstNasOmSmsCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    /* 填写消息内容 */
    pstNasOmSmsCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstNasOmSmsCnf->ulMsgId          = ID_NAS_OM_SMS_CONFIRM;
    pstNasOmSmsCnf->usOriginalId     = pstOmInquireMsg->usOriginalId;
    pstNasOmSmsCnf->usTerminalId     = pstOmInquireMsg->usTerminalId;
    pstNasOmSmsCnf->ulTimeStamp      = pstOmInquireMsg->ulTimeStamp;
    pstNasOmSmsCnf->ulSN             = pstOmInquireMsg->ulSN;
    pstNasOmSmsCnf->enResult         = (NAS_OM_RESULT_ENUM_UINT32)ulSndOmRet;


    /* 发送消息 */
    ulRet = PS_SEND_MSG(WUEPS_PID_SMS, pstNasOmSmsCnf);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");
    }

    return;
    /* Modified by wx270776 for OM融合, 2015-7-1, end */



}

/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

/*****************************************************************************
 函 数 名  : NAS_SMS_RcvOmMaintainInfoInd
 功能描述  : 处理来自MMA的PC工具可谓可测配置信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月24日
    作    者   : l00171473
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_SMS_RcvOmMaintainInfoInd(
    struct MsgCB                       *pstMsg
)
{
    MMCM_OM_MAINTAIN_INFO_IND_STRU     *pstOmMaintainInfo;

    pstOmMaintainInfo = (MMCM_OM_MAINTAIN_INFO_IND_STRU*)pstMsg;

    if ( (VOS_TRUE == pstOmMaintainInfo->ucOmConnectFlg)
      && (VOS_TRUE == pstOmMaintainInfo->ucOmPcRecurEnableFlg) )
    {
        NAS_SMS_SndOutsideContextData();
    }

}

/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
/*****************************************************************************
 函 数 名  : NAS_SMS_RcvOmInquireReq
 功能描述  : 处理来自OM的查询消息
 输入参数  :
             pstMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : luokaihui l00167671
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_SMS_RcvOmInquireReq(
    struct MsgCB                       *pstMsg
)
{
    ID_NAS_OM_INQUIRE_STRU             *pstOmMsg = VOS_NULL_PTR;

    pstOmMsg = (ID_NAS_OM_INQUIRE_STRU *)pstMsg;

    NAS_INFO_LOG(WUEPS_PID_SMS, "NAS_SMS_RcvOmInquireReq:  ");

    NAS_SMS_SndOmInquireCnfMsg(pstOmMsg);

    return;

}
/*****************************************************************************
 函 数 名  : SMC_RcvOmMsgDistr
 功能描述  : 处理来自OM的查询消息
 输入参数  :
             pRcvMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月23日
   作    者   : luokaihui l00167671
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID SMC_RcvOmMsgDistr(
                       VOS_VOID     *pRcvMsg                                        /* 收到的消息                               */
                       )
{
    switch(((MSG_HEADER_STRU *)pRcvMsg)->ulMsgName)
    {
        case ID_NAS_OM_SMS_INQUIRE:
            NAS_SMS_RcvOmInquireReq(pRcvMsg);
            break;
        default:
            break;
    }
}

/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

VOS_VOID SMS_TaskEntry(struct MsgCB* pMsg )
{
    MSG_HEADER_STRU         *pHeader;                                           /* 定义消息头指针                           */
    REL_TIMER_MSG           *pTimer;                                            /* 定义TIMER消息指针                        */

    pHeader = (MSG_HEADER_STRU *) pMsg;                                         /* 获取消息头指针                           */
    pTimer  = (REL_TIMER_MSG *) pMsg;                                           /* 获取TIMER消息指针                        */

    if (SMS_TASK_START == g_SmsStartFlg)
    {                                                                           /* TASK SMS已经启动的场合                   */
        if ( VOS_PID_TIMER == pMsg->ulSenderPid)
        {                                                                       /* 如果是TIMER消息                          */
            SMS_TimerMsgDistr( (VOS_UINT8)pTimer->ulName );                         /* TIMER溢出分发函数                        */
        }
        else
        {
            switch( pHeader->ulSenderPid )
            {                                                                   /* 根据Src Tsk Id分发消息                   */
            case WUEPS_PID_GMM:
                SMC_RcvGmmMsgDistr(pMsg);
                break;

#if (FEATURE_ON == FEATURE_LTE)
            case PS_PID_MM:
                NAS_SMS_RcvLmmMsgDistr(pMsg);
                break;
#endif
            case WUEPS_PID_MM:
                SMC_RcvMmMsgDistr(pMsg);
                break;
            case UEPS_PID_LL:
                SMC_RcvLlcMsgDistr(pMsg);
                break;
            case WUEPS_PID_TAF:
                NAS_SMS_ProcMnMsg(pMsg);
                break;
            case WUEPS_PID_ADMIN:
                if (WUEPS_RESET_REQ == pHeader->ulMsgName)
                {
                    g_SmsStartFlg = SMS_TASK_NOT_START;                         /* 等待ADMIN发送启动原语                    */
                }
                break;
            #ifdef __PS_WIN32_RECUR__
            case WUEPS_PID_SMS:
                NAS_SMS_RestoreContextData(pMsg);
                break;
            #endif
            #ifndef __PS_WIN32_RECUR__
            case WUEPS_PID_MMA:
                if (MMCM_OM_MAINTAIN_INFO_IND == pHeader->ulMsgName)
                {
                    NAS_SMS_RcvOmMaintainInfoInd(pMsg);
                }
                break;
            #endif
            /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
            case MSP_PID_DIAG_APP_AGENT:
                SMC_RcvOmMsgDistr(pMsg);
                break;
            /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
            default :
                PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "LogRecord_Timer_HW:WARNING:Rcv Msg PID Error!");
                break;
            }
        }
    }
}
/*******************************************************************************
  Module:   SMS_InitEntity
  Function: 初始化SMS实体
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇      2004.03.09   新规作成
      2. 日    期   : 2007年8月28日
         作    者   : l60022475
         修改内容   : 问题单号：A32D12744,初始化SMS Timer句柄
*******************************************************************************/
VOS_VOID SMS_InitEntity()
{
/* 全局量MR初始化为零 */
    g_ucSmsMR = 0;

/* SMC实体的初始化 */

    g_SmcPsEnt.SmcMo.ucTi                = 0;
    g_SmcPsEnt.SmcMo.ucState             = SMC_MO_IDLE;
    g_SmcPsEnt.SmcMo.ucMr                = 0;
    g_SmcPsEnt.SmcMo.ucCpAckFlg          = SMS_FALSE;
    g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
    g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg     = SMS_POINTER_NULL;
    g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
    g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;
    g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg     = SMS_POINTER_NULL;

    g_SmcPsEnt.SmcMt.ucTi                = 0;
    g_SmcPsEnt.SmcMt.ucState             = SMC_MT_IDLE;
    g_SmcPsEnt.SmcMt.ucMr                = 0;
    g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;
    g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg     = SMS_POINTER_NULL;
    g_SmcPsEnt.SmcMt.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;



    g_SmcCsEnt.SmcMo.ucTi                = 0;
    g_SmcCsEnt.SmcMo.ucState             = SMC_MO_IDLE;
    g_SmcCsEnt.SmcMo.ucMr                = 0;
    g_SmcCsEnt.SmcMo.ucCpAckFlg          = SMS_FALSE;
    g_SmcCsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
    g_SmcCsEnt.SmcMo.HoldSndMsg.pMsg     = SMS_POINTER_NULL;
    g_SmcCsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;
    g_SmcCsEnt.SmcMo.HoldRcvMsg.pMsg     = SMS_POINTER_NULL;

    g_SmcCsEnt.SmcMt.ucTi                = 0;
    g_SmcCsEnt.SmcMt.ucState             = SMC_MT_IDLE;
    g_SmcCsEnt.SmcMt.ucMr                = 0;
    g_SmcCsEnt.SmcMt.HoldSndMsg.ulMsgLen = 0;
    g_SmcCsEnt.SmcMt.HoldSndMsg.pMsg     = SMS_POINTER_NULL;
    /* ==>A32D12744 */
    g_SmcPsEnt.SmcMo.TimerInfo.TimerId   = SMS_POINTER_NULL;
    g_SmcPsEnt.SmcMt.TimerInfo.TimerId   = SMS_POINTER_NULL;
    g_SmcCsEnt.SmcMo.TimerInfo.TimerId   = SMS_POINTER_NULL;
    g_SmcCsEnt.SmcMt.TimerInfo.TimerId   = SMS_POINTER_NULL;
    /* ==>A32D12744 */

    g_SmcPsEnt.SmcMo.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP;
    g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

    g_SmcPsEnt.SmcMt.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP;
    g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;

    g_SmcCsEnt.SmcMo.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP;
    g_SmcCsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

    g_SmcCsEnt.SmcMt.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_STOP;
    g_SmcCsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;

/* SMR实体的初始化 */
    g_SmrEnt.SmrMo.ucState       = SMR_IDLE;
    g_SmrEnt.SmrMo.ucRetransFlg  = SMR_RETRANS_PERMIT;
    g_SmrEnt.SmrMo.ucMr          = 0;
    g_SmrEnt.SmrMo.ucMemAvailFlg = SMS_FALSE;
    g_SmrEnt.SmrMt.ucState  = SMR_IDLE;
    g_SmrEnt.SmrMt.ucMr     = 0;

    /* ==>A32D12744 */
    g_SmrEnt.SmrMo.aTimerInfo[0].TimerId = SMS_POINTER_NULL;
    g_SmrEnt.SmrMo.aTimerInfo[1].TimerId = SMS_POINTER_NULL;
    g_SmrEnt.SmrMo.aTimerInfo[2].TimerId = SMS_POINTER_NULL;
    g_SmrEnt.SmrMt.TimerInfo.TimerId = SMS_POINTER_NULL;
    g_SmrEnt.SmrMt.RelTimerInfo.TimerId = SMS_POINTER_NULL;
    /* <==A32D12744 */
    g_SmrEnt.SmrMo.aTimerInfo[0].ucTimerSta = SMS_TIMER_STATUS_STOP;

    g_SmrEnt.SmrMo.aTimerInfo[1].ucTimerSta = SMS_TIMER_STATUS_STOP;

    g_SmrEnt.SmrMo.aTimerInfo[2].ucTimerSta = SMS_TIMER_STATUS_STOP;

    g_SmrEnt.SmrMt.TimerInfo.ucTimerSta = SMS_TIMER_STATUS_STOP;

    g_SmrEnt.SmrMt.RelTimerInfo.ucTimerSta = SMS_TIMER_STATUS_STOP;
}
/*******************************************************************************
Prototype       : SMS_Poweroff()
Description     : 关闭计时器
Input           : 无
Output          : 无
Calls           :
Called          :供TAFM模块调用。
Return          :无
History         : ---
  1.Date        : 2007-08-29
    Author      : z40661
    Modification: Create SMS_Poweroff for A32D12744
  2.日    期   : 2012年8月29日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改

  3.日    期   : 2013年4月23日
    作    者   : z00234330
    修改内容   : DMT测试需要关机时将TI值清除

  4.日    期   : 2013年07月11日
    作    者   : f62575
    修改内容   : V9R1 STK升级项目
*******************************************************************************/
VOS_VOID SMS_Poweroff(VOS_VOID)
{
    /*停止所有定时器*/
    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_PS_TC1M_MO ) )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMS_Poweroff: SMC_TIMER_ID_PS_TC1M_MO Timer stop fails" );
    }

    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_PS_TC1M_MT ) )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMS_Poweroff: SMC_TIMER_ID_PS_TC1M_MT Timer stop fails" );
    }


    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMS_Poweroff: SMC_TIMER_ID_CS_TC1M_MO Timer stop fails" );
    }


    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MT ) )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMS_Poweroff: SMC_TIMER_ID_CS_TC1M_MO Timer stop fails" );
    }

    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMS_Poweroff: SMC_TIMER_ID_TR1M Timer stop fails" );
    }


    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR2M ) )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMS_Poweroff: SMC_TIMER_ID_TR2M Timer stop fails" );
    }


    if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TRAM ) )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMS_Poweroff: SMC_TIMER_ID_TRAM Timer stop fails" );
    }

    /*释放所有正在进行的短信发送或接受过程*/
    g_ucCsRegFlg = SMS_FALSE;                                                   /* 记录此状态                               */

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    SMC_ComCsMtErr(SMR_SMT_ERROR_NO_SERVICE, g_SmcCsEnt.SmcMt.ucTi);                                   /* 调用CS域MT实体的处理                     */

    SMC_ComCsMoErr(SMR_SMT_ERROR_NO_SERVICE, g_SmcCsEnt.SmcMo.ucTi);                         /* 调用CS域MO实体的处理                     */
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    if (SMS_TRUE == g_SmcCsEnt.SmcMo.ucCpAckFlg)
    {                                                                   /* TI相等                                   */
        g_SmcCsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
        SMS_SendMnMoLinkCloseInd();
    }

    g_ucPsServiceStatus = SMS_FALSE;                                            /* 记录此状态                               */

    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, begin */
    SMC_ComPsMtErr(SMR_SMT_ERROR_NO_SERVICE);                                  /* 调用PS域MT实体的处理                     */
    SMC_ComPsMoErr(SMR_SMT_ERROR_NO_SERVICE);                                  /* 调用PS域MO实体的处理                     */
    /* Modified by f62575 for V9R1 STK升级, 2013-6-26, end */

    if (SMS_TRUE == g_SmcPsEnt.SmcMo.ucCpAckFlg)
    {                                                                   /* TI相等                                   */
        g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
        SMS_SendMnMoLinkCloseInd();
    }


    /* Modified by z40661 for DMT工程修改, 2013-2-01, begin */
#ifdef DMT
    SMS_InitEntity();
#endif
    /* Modified by z40661 for DMT工程修改, 2013-2-01, end */

    return;
}

/*lint -e438 -e830*/

/*******************************************************************************
  Module:   SMC_RcvLlcMsgDistr
  Function: 根据消息类型，调用不同的LLC消息处理
  Input:    VOS_VOID     *pRcvMsg     消息首地址
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   郜东东   2006.02.22   新规作成
      2.日    期   : 2011年12月05日
        作    者   : z00161729
        修改内容   : V7R1 phaseIV修改
      3.日    期  : 2013年03月13日
        作    者  : z00214637
        修改内容  : BodySAR项目

*******************************************************************************/
VOS_VOID SMC_RcvLlcMsgDistr(
                       VOS_VOID     *pRcvMsg                                        /* 收到的消息                               */
                       )
{
    LL_SMS_UNITDATA_IND_MSG             *pMsg;
    /*调用NAS_EventReport需要构造NAS_MSG_STRU*/
    NAS_MSG_STRU       *pNasMsg = VOS_NULL_PTR;
    VOS_UINT32          ulNasMsgLen;
    VOS_UINT32          ulMsgLen;

    if ( NAS_GMM_NET_RAT_TYPE_WCDMA == GMM_GetCurNetwork() )
    {
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "SMC_RcvLlcMsgDistr:WARNING:In 3G mode, Message from LLC shouldn't be received");
        return;
    }

    pMsg = (LL_SMS_UNITDATA_IND_MSG *)pRcvMsg;

    switch(((LL_SMS_UNITDATA_IND_MSG *)pRcvMsg)->usMsgType)
    {
    case ID_LL_UNITDATA_IND:
    	/*Report event begin*/
        ulMsgLen = ((LL_SMS_UNITDATA_IND_MSG *)pRcvMsg)->stUnitDataInd.usPduLen;

        if(ulMsgLen > 4)
        {
            ulNasMsgLen = (sizeof(NAS_MSG_STRU) + ulMsgLen) - 4;
        }
        else
        {
            ulNasMsgLen = sizeof(NAS_MSG_STRU);
        }

        pNasMsg = (NAS_MSG_STRU *)SMS_Malloc(ulNasMsgLen);

        if(VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_ERROR, "SMC_ReportM2NEvent:ERROR: pNasMsg is NULL");
        }
        else
        {
            pNasMsg->ulNasMsgSize = ulMsgLen;

            SMS_Memcpy(pNasMsg->aucNasMsg, ((LL_SMS_UNITDATA_IND_MSG *)pRcvMsg)->stUnitDataInd.aucPdu, pNasMsg->ulNasMsgSize);

            SMS_ReportN2MOtaMsg(pNasMsg);


            SMS_Free(pNasMsg);
        }
        /*Report event end*/

        if((((LL_SMS_UNITDATA_IND_MSG *)pRcvMsg)->stUnitDataInd.aucPdu[0]>>4)< 8)
        {                                                                       /* 是mt过程                                 */
            if(SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState)
            {                                                                   /* 同时有两个mt过程                         */
                SMC_SndGmmDataReq(
                        SMC_DATA_TYPE_CP_ERR,
                        SMS_CP_ERR_CONGEST,
                        (VOS_UINT8)((((LL_SMS_UNITDATA_IND_MSG *)pRcvMsg)->stUnitDataInd.
                              aucPdu[0]>>4) )                                   /* 向网侧发送CP_ERROR  TI取接收到消息的TI   */
                                );                                              /* 向网侧报错                               */
            }
            else
            {
                /* 调用mt的处理过程 */
                SMC_RcvPsMtData((VOS_UINT8 *)(VOS_UINT32)pMsg->stUnitDataInd.aucPdu,
                                pMsg->stUnitDataInd.usPduLen);
            }
        }
        else
        {   /* 是mo过程 */
            SMC_RcvPsMoData((VOS_UINT8 *)(VOS_UINT32)pMsg->stUnitDataInd.aucPdu,
                            pMsg->stUnitDataInd.usPduLen);
        }
        break;
    default:
        SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                           SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                  (VOS_UINT8)((((LL_SMS_UNITDATA_IND_MSG *)pRcvMsg)->stUnitDataInd.
                              aucPdu[0] & 0xf0) >> 4));                         /* 向上层报错                               */
        break;
    }

}
/*lint +e438 +e830*/


/*******************************************************************************
  Module:   SMC_RcvGmmMsgDistr
  Function: 根据消息类型，调用不同的GMM消息处理
  Input:    VOS_VOID     *pRcvMsg     消息首地址
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. Date         : 2004-03-09
     Author       : g41091
     Modification : 新规作成
  2. Date         : 2006-02-22
     Author       : g41091
     Modification : 增加了通过GPRS发送短信的功能,问题单号:A32D02833
  3.日    期  : 2013年03月13日
    作    者  : z00214637
    修改内容  : BodySAR项目

*******************************************************************************/
VOS_VOID SMC_RcvGmmMsgDistr(
                       VOS_VOID     *pRcvMsg                                        /* 收到的消息                               */
                       )
{
    switch(((MSG_HEADER_STRU *)pRcvMsg)->ulMsgName)
    {
    case GMMSMS_REG_STATE_IND:
        /* 注册状态仅供 CBS 使用 */
        /* SMC_RcvGmmStaInd ((GMMSMS_REG_STATE_IND_STRU *)pRcvMsg);               调用注册状态消息的处理                   */
        break;
    case GMMSMS_SERVICE_STATUS_IND:
        SMC_RcvGmmServStatusInd((GMMSMS_SERVICE_STATUS_IND_STRU *)pRcvMsg);    /* 调用服务状态的处理                        */
        break;
    case PMMSMS_EST_CNF:
        SMC_RcvGmmEstCnf ();                                                    /* 调用建立确认原语的处理                   */
        break;
    case PMMSMS_ERROR_IND:
        SMC_RcvGmmErrInd ((PMMSMS_ERROR_IND_STRU *)pRcvMsg);                    /* 调用错误处理                             */
        break;
    case PMMSMS_UNITDATA_IND:
        SMS_ReportN2MOtaMsg(&(((PMMSMS_UNITDATA_IND_STRU *)pRcvMsg)->SmsMsg));


        if((((PMMSMS_UNITDATA_IND_STRU *)pRcvMsg)->SmsMsg.aucNasMsg[0]>>4)< 8)
        {                                                                       /* 是mt过程                                 */
            if(SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState)
            {                                                                   /* 同时有两个mt过程                         */
                SMC_SndGmmDataReq(
                        SMC_DATA_TYPE_CP_ERR,
                        SMS_CP_ERR_CONGEST,
                        (VOS_UINT8)((((PMMSMS_UNITDATA_IND_STRU *)pRcvMsg)->SmsMsg.
                              aucNasMsg[0]>>4) )                                /* 向网侧发送CP_ERROR  TI取接收到消息的TI   */
                                );                                              /* 向网侧报错                               */
            }
            else
            {
                /* 调用mt的处理过程 */
                SMC_RcvPsMtData(((PMMSMS_UNITDATA_IND_TEMP_STRU *)pRcvMsg)->SmsMsg.aucNasMsg,
                                ((PMMSMS_UNITDATA_IND_TEMP_STRU *)pRcvMsg)->SmsMsg.ulNasMsgSize);
            }
        }
        else
        {   /* 是mo过程，调用mo的处理过程 */
            SMC_RcvPsMoData(((PMMSMS_UNITDATA_IND_TEMP_STRU *)pRcvMsg)->SmsMsg.aucNasMsg,
                            ((PMMSMS_UNITDATA_IND_TEMP_STRU *)pRcvMsg)->SmsMsg.ulNasMsgSize);
        }
        break;
    default:
        SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                           SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                  (VOS_UINT8)((((PMMSMS_UNITDATA_IND_STRU *)pRcvMsg)->SmsMsg.
                              aucNasMsg[0] & 0xf0) >> 4));                      /* 向上层报错                               */
        break;
    }
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_SMS_RcvLmmMsgDistr
 功能描述  : 根据消息类型，调用不同的LMM消息处理
 输入参数  : pRcvMsg - 消息首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年11月28日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年8月14日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改,删除ID_LMM_SMS_SERVICE_STATUS_IND消息处理

*****************************************************************************/
VOS_VOID NAS_SMS_RcvLmmMsgDistr(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT32                          ulMsgId;

    ulMsgId = 0;
    /* 获取消息类型 */
    PS_MEM_CPY(&ulMsgId, (VOS_INT8*)pRcvMsg + VOS_MSG_HEAD_LENGTH, sizeof(VOS_UINT32));

    switch ( ulMsgId )
    {
        case ID_LMM_SMS_EST_CNF:
            NAS_SMS_ProcLmmEstCnf(pRcvMsg);
            break;

        case ID_LMM_SMS_DATA_IND:
            NAS_SMS_ProcLmmDataInd(pRcvMsg);
            break;

        case ID_LMM_SMS_ERR_IND:
            NAS_SMS_ProcLmmErrInd(pRcvMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_RcvLmmMsgDistr():Invalid SMS MsgId");
            break;
    }
}
#endif


/*******************************************************************************
  Module:   SMC_RcvMmMsgDistr
  Function: 根据消息类型，调用不同的MM消息处理
  Input:    VOS_VOID     *pRcvMsg     消息首地址
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. Date         : 2004-03-09
     Author       : g41091
     Modification : 新规作成
  2. Date         : 2006-02-22
     Author       : g41091
     Modification : 增加了通过GPRS发送短信的功能,问题单号:A32D02833
  3.日    期  : 2013年03月13日
    作    者  : z00214637
    修改内容  : BodySAR项目
  4.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级

*******************************************************************************/
VOS_VOID SMC_RcvMmMsgDistr(
                       VOS_VOID     *pRcvMsg                                        /* 收到的消息                               */
                       )
{
    switch(((MSG_HEADER_STRU *)pRcvMsg)->ulMsgName)
    {
    case MMSMS_REG_STATE_IND:
        SMC_RcvMmRegStaInd((MMSMS_REG_STATE_IND_STRU *)pRcvMsg);                /* 调用注册状态消息的处理                   */
        break;
    case MMSMS_EST_CNF:
        SMC_RcvMmEstCnf((MMSMS_EST_CNF_STRU *)pRcvMsg);                         /* 调用建立确认原语的处理                   */
        break;
    case MMSMS_EST_IND:
        SMS_ReportN2MOtaMsg(&(((MMSMS_EST_IND_STRU *)pRcvMsg)->SmsMsg));


        /* 调用建立指示原语的处理                   */
        SMC_RcvMmEstInd(((MMSMS_EST_IND_STRU *)pRcvMsg)->SmsMsg.aucNasMsg,
                        ((MMSMS_EST_IND_STRU *)pRcvMsg)->SmsMsg.ulNasMsgSize );
        break;
    case MMSMS_REL_IND:
        SMC_RcvMmRelInd((MMSMS_REL_IND_STRU *)pRcvMsg);                         /* 调用错误处理                             */
        break;
    case MMSMS_DATA_IND:
        SMS_ReportN2MOtaMsg(&(((MMSMS_DATA_IND_STRU *)pRcvMsg)->SmsMsg));


        if((((MMSMS_DATA_IND_STRU *)pRcvMsg)->SmsMsg.aucNasMsg[0] >> 4) < 8)
        {                                                                       /* 是mt过程                                 */
            if(SMC_MT_IDLE != g_SmcPsEnt.SmcMt.ucState)
            {                                                                   /* 同时有两个mt过程                         */
                SMC_SndMmDataReq(
                        SMC_DATA_TYPE_CP_ERR,
                        SMS_CP_ERR_CONGEST,
                        (VOS_UINT8)((((MMSMS_DATA_IND_STRU *)pRcvMsg)->SmsMsg.
                                                        aucNasMsg[0]) >> 4));   /* 向网侧发送CP_ERROR  TI取接收到消息的TI   */
            }
            else
            {   /* 调用mt的处理过程                         */
                SMC_RcvNwCsMtData(((MMSMS_DATA_IND_STRU *)pRcvMsg)->SmsMsg.aucNasMsg,
                                  ((MMSMS_DATA_IND_STRU *)pRcvMsg)->SmsMsg.ulNasMsgSize );
            }
        }
        else
        {   /* 是mo过程                                 */
            SMC_RcvNwCsMoData(((MMSMS_DATA_IND_STRU *)pRcvMsg)->SmsMsg.aucNasMsg,
                              ((MMSMS_DATA_IND_STRU *)pRcvMsg)->SmsMsg.ulNasMsgSize );
        }
        break;
    /* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
    case MMSMS_NACK_DATA_IND:
        NAS_SMS_RcvNackMsg((MMSMS_NACK_DATA_IND_STRU *)pRcvMsg);
        break;
    /* Added by f62575 for V9R1 STK升级, 2013-6-26, end */
    default:
        break;
    }
}
/*******************************************************************************
  Module:   SMS_TimerMsgDistr
  Function: 根据消息类型，调用不同的TIMER溢出处理
  Input:    VOS_VOID     *pRcvMsg     消息首地址
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇      2004.03.09   新规作成
      2. 日    期   : 2013年06月28日
         作    者   : l00167671
         修改内容   : DCM LOGGER项目定时器事件上报
*******************************************************************************/
VOS_VOID SMS_TimerMsgDistr(VOS_UINT32 ulTimerId)
{
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    NAS_TIMER_EventReport(ulTimerId, WUEPS_PID_SMS, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

    switch(ulTimerId)
    {
    case SMC_TIMER_ID_PS_TC1M_MT:
    case SMC_TIMER_ID_PS_TC1M_MO:
    case SMC_TIMER_ID_CS_TC1M_MT:
    case SMC_TIMER_ID_CS_TC1M_MO:
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "SMS_TimerMsgDistr:INFO:SMS TIMER EXPIRED: TC1M");
        SMC_TimerTc1mExp((VOS_UINT8)ulTimerId);                                     /* 调用定时器TC1M溢出的处理                 */
        break;
    case SMC_TIMER_ID_TR1M:
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "SMS_TimerMsgDistr:INFO:SMS TIMER EXPIRED: TR1M");
        SMR_TimerTr1mExpire();                                                  /* 调用定时器TR1M溢出的处理                 */
        break;
    case SMC_TIMER_ID_TR2M:
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "SMS_TimerMsgDistr:INFO:SMS TIMER EXPIRED: TR2M");
        SMR_TimerTr2mExpire();                                                  /* 调用定时器TR2M溢出的处理                 */
        break;
    case SMC_TIMER_ID_TRAM:
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "SMS_TimerMsgDistr:INFO:SMS TIMER EXPIRED: TCAM");
        SMR_TimerTramExpire();                                                  /* 调用定时器TRAM溢出的处理                 */
        break;

    default:
        break;
    }
    return;
}
/*******************************************************************************
  Module:   SMS_TimerStop
  Function: 停止TIMER
  Input:    HTIMER    TimerId     定时器id
            VOS_UINT8       ucState     TIMER状态
  Output:   VOS_VOID
  NOTE:
  RETURN   : VOS_UINT8
             SMS_TRUE  --- 成功
             SMS_FALSE --- 失败
  History:
      1.  张志勇      2004.03.09   新规作成
      2.  张志勇   2004-7-8     修改参数TimerId
      3.  郜东东   2005-12-26   修改函数返回值类型
4. Date:          2006-08-19
   Author:        郜东东
   Modification:  OSA优化整改,问题单号:A32D05312
  5.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  6.日    期   : 2012年12月13日
    作    者   : L00171473
    修改内容   : DTS2012121802573, TQE清理
*******************************************************************************/
VOS_UINT8 SMS_TimerStop(
                        VOS_UINT8       ucTimerId
                   )
{
    HTIMER*     pTimer;
    VOS_UINT32  ulTimerLength;
    VOS_UINT8*  pucTimerSta;
    VOS_UINT32  ulRet;


    pucTimerSta = VOS_NULL_PTR;



    pTimer = VOS_NULL_PTR;
    /*lint -e961*/
    SMC_GetTimerInfo( ucTimerId,
                      &pTimer,
                      &ulTimerLength,
                      &pucTimerSta );
    /*lint +e961*/
    if( SMS_TIMER_STATUS_RUN == *pucTimerSta )
    {
        *pucTimerSta = SMS_TIMER_STATUS_STOP;
        ulRet = NAS_StopRelTimer(WUEPS_PID_SMS, ucTimerId, pTimer );                                               /* 启动定时器 */
        if( VOS_OK != ulRet )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMS:SMS_TimerStop: Timer stop fails" );
            return SMS_FALSE;
        }
    }

    return SMS_TRUE;
}
/*******************************************************************************
  Module:   SMS_TimerStart
  Function: 启动TIMER
  Input:    HTIMER    TimerId     定时器id
  Output:   VOS_VOID
  NOTE:
  RETURN   : VOS_UINT8
             SMS_TRUE  --- 成功
             SMS_FALSE --- 失败
  History:
      1.  张志勇      2004.03.09   新规作成
      2.  张志勇   2004-7-8     修改参数TimerId
      3.  郜东东   2005-12-26   修改函数返回值类型
4. Date:          2006-08-19
   Author:        郜东东
   Modification:  OSA优化整改,问题单号:A32D05312
5. Date:          2007-06-11'
   Author:        z40661
   Modification:  A32D11581
6. 日    期   : 2012年8月10日
   作    者   : L00171473
   修改内容   : DTS2012082204471, TQE清理
7.日    期   : 2012年12月13日
  作    者   : L00171473
  修改内容   : DTS2012121802573, TQE清理

8.日    期   : 2013年9月4日
  作    者   : w00167002
  修改内容   : DTS2013090403562:NAS定时器清理，需要启动32K定时器。将MM/MMA/SMS
                模块的循环定时器修改为非循环定时器。
*******************************************************************************/
VOS_UINT8 SMS_TimerStart(
                    VOS_UINT8               ucTimerId
                    )
{
    HTIMER*     pTimer;
    VOS_UINT32  ulTimerLength;
    VOS_UINT8*  pucTimerSta;
    VOS_UINT32  ulRet;


    pucTimerSta = VOS_NULL_PTR;



    ulTimerLength = 0;
    pTimer        = VOS_NULL_PTR;
    /*lint -e961*/
    SMC_GetTimerInfo( ucTimerId,
                      &pTimer,
                      &ulTimerLength,
                      &pucTimerSta );
    /*lint +e961*/
    if( SMS_TIMER_STATUS_STOP == *pucTimerSta )
    {
        *pucTimerSta = SMS_TIMER_STATUS_RUN;
        ulRet = NAS_StartRelTimer( pTimer,
                                   WUEPS_PID_SMS,
                                   ulTimerLength,
                                   ucTimerId,
                                   0,
                                   VOS_RELTIMER_NOLOOP
                                   );                                               /* 启动定时器 */
        if( VOS_OK != ulRet )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMS:SMS_TimerStart: Timer start fails" );
            return SMS_FALSE;
        }
    }

    return SMS_TRUE;
}

/*****************************************************************************
 函 数 名  : SMS_GetTimerLength
 功能描述  : 获取短信定时器时长
 输入参数  : 无
 输出参数  : SMS_TIMER_LENGTH_STRU              *pstTimerLength 定制的定时器时长
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    作    者   : f62575
    修改内容   : 新生成函数 DTS2012122406218, 短信正向质量发现问题: 短信发送流程部分
  2.日    期   : 2013年02月04日
    作    者   : f62575
    修改内容   : DTS2013013104268, TC1M定时器超时重传次数自适应；
  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID SMS_GetTimerLength(
    SMS_TIMER_LENGTH_STRU              *pstTimerLength
)
{
    VOS_UINT32                          ulRet;
    SMS_NVIM_TIMER_LENGTH_STRU          stTimerLength;

    PS_MEM_SET(pstTimerLength, 0, sizeof(SMS_TIMER_LENGTH_STRU));
    PS_MEM_SET(&stTimerLength, 0, sizeof(stTimerLength));

    ulRet = NV_Read(en_NV_Item_SMS_TIMER_LENGTH,
                    &stTimerLength,
                    sizeof(stTimerLength));
    if ((NV_OK != ulRet)
     || (0 == stTimerLength.usTc1mLength))
    {
        pstTimerLength->usTc1mLength = SMC_TIMER_TC1M_LENGTH;
        pstTimerLength->usTr1mLength = SMR_TIMER_TR1M_LENGTH;
        pstTimerLength->usTr2mLength = SMR_TIMER_TR2M_LENGTH;
        pstTimerLength->usTramLength = SMR_TIMER_TRAM_LENGTH;
    }
    else
    {
        pstTimerLength->usTc1mLength = stTimerLength.usTc1mLength;
        pstTimerLength->usTr1mLength = stTimerLength.usTr1mLength;
        pstTimerLength->usTr2mLength = stTimerLength.usTr2mLength;
        pstTimerLength->usTramLength = stTimerLength.usTramLength;
    }

    return;
}

/*****************************************************************************
 函 数 名  : SMS_GetCustomizedPara
 功能描述  : 初始化短信定制参数
 输入参数  : 无
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年02月04日
    作    者   : f62575
    修改内容   : 新生成函数 DTS2013013104268, TC1M定时器超时重传次数自适应；

*****************************************************************************/
VOS_VOID SMS_GetCustomizedPara(VOS_VOID)
{
    SMS_TIMER_LENGTH_STRU               stTimerLength;
    VOS_UINT16                          usWaitRpAckTime;
    VOS_UINT16                          usCpDataTimes;

    SMS_GetTimerLength(&stTimerLength);

    usCpDataTimes    = stTimerLength.usTr1mLength/stTimerLength.usTc1mLength;

    /* 等待RP-ACK消息的时间: 重传的CP-DATA发送后需要预留时间给网络回复RP-ACK */
    usWaitRpAckTime  = stTimerLength.usTr1mLength%stTimerLength.usTc1mLength;

    /* 定制参数有效性检查: 定制参数无效则恢复到默认配置 */
    if ((0 == usWaitRpAckTime)
     || (usCpDataTimes < SMC_CP_DATA_MIN_TIMES)
     || (usCpDataTimes > SMC_CP_DATA_MAX_TIMES))
    {
        f_ucNasSmsTc1mMaxExpTimes           = SMC_TC1M_EXP_PROTOCOL_MIN_TIMES;
        f_stNasSmsTimerLength.usTc1mLength  = SMC_TIMER_TC1M_LENGTH;
        f_stNasSmsTimerLength.usTr1mLength  = SMR_TIMER_TR1M_LENGTH;
        f_stNasSmsTimerLength.usTr2mLength  = SMR_TIMER_TR2M_LENGTH;
        f_stNasSmsTimerLength.usTramLength  = SMR_TIMER_TRAM_LENGTH;
        return;
    }

    /* 重传次数 = 发送CP-DATA次数 - 首次发送的一个CP-DATA */
    f_ucNasSmsTc1mMaxExpTimes = (VOS_UINT8)(usCpDataTimes - 1);
    PS_MEM_CPY(&f_stNasSmsTimerLength, &stTimerLength, sizeof(f_stNasSmsTimerLength));

    /* 从NV 中获取ps域短信发送控制 */
    SMS_GetPsConcatenateFlagFromNV();

    /* 获取并设置短信过滤是否使能标识 */
    SMS_GetSmsFilterEnableFlgFromNV();

    return;
}

/*****************************************************************************
 函 数 名  : SMS_GetTc1mTimeOutRetryFlag
 功能描述  : 获取TC1M定时器超时后是否重发标志
 输入参数  : VOS_UINT8                           ucExpireTimes  已经重发的次数
 输出参数  : VOS_BOOL                           *pbRetryFlag    是否需要重发
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年02月04日
    作    者   : f62575
    修改内容   : 新生成函数 DTS2013013104268, 获取TC1M定时器超时后是否重发标志；

*****************************************************************************/
VOS_VOID SMS_GetTc1mTimeOutRetryFlag(
    VOS_UINT8                           ucExpireTimes,
    VOS_BOOL                           *pbRetryFlag
)
{
    if (ucExpireTimes < f_ucNasSmsTc1mMaxExpTimes)
    {
        *pbRetryFlag = VOS_TRUE;
    }
    else
    {
        *pbRetryFlag = VOS_FALSE;
    }

    return;
}

/*lint -e961*/

/*******************************************************************************
  Module:   SMC_GetTimerInfo
  Function: 根据TimerId获得Timer的相应信息
  Input:    VOS_UINT8    ucTimerId
  Output:   HTIMER**     ppTimer
            VOS_UINT32*  pulTimerLength
            VOS_UINT8**  ppucTimerSta
  NOTE:
  RETURN   : VOS_VOID
  History:
      1.  郜东东   2006-08-19   因OSA优化整改而创建,问题单号:A32D05312
    2.日    期   : 2012年12月28日
      作    者   : 傅映君/f62575
      修改内容   : DTS2012122406218, 短信正向质量发现问题: 短信发送流程部分
*******************************************************************************/
VOS_VOID SMC_GetTimerInfo( VOS_UINT8    ucTimerId,
                           HTIMER**     ppTimer,
                           VOS_UINT32*  pulTimerLength,
                           VOS_UINT8**  ppucTimerSta )
{

    switch( ucTimerId )
    {
        /* SMC的定时器 */
        case SMC_TIMER_ID_PS_TC1M_MO:
            *ppTimer = &g_SmcPsEnt.SmcMo.TimerInfo.TimerId;
            *pulTimerLength = f_stNasSmsTimerLength.usTc1mLength;
            *ppucTimerSta = &g_SmcPsEnt.SmcMo.TimerInfo.ucTimerSta;
            break;
        case SMC_TIMER_ID_PS_TC1M_MT:
            *ppTimer = &g_SmcPsEnt.SmcMt.TimerInfo.TimerId;
            *pulTimerLength = f_stNasSmsTimerLength.usTc1mLength;
            *ppucTimerSta = &g_SmcPsEnt.SmcMt.TimerInfo.ucTimerSta;
            break;
        case SMC_TIMER_ID_CS_TC1M_MO:
            *ppTimer = &g_SmcCsEnt.SmcMo.TimerInfo.TimerId;
            *pulTimerLength = f_stNasSmsTimerLength.usTc1mLength;
            *ppucTimerSta = &g_SmcCsEnt.SmcMo.TimerInfo.ucTimerSta;
            break;
        case SMC_TIMER_ID_CS_TC1M_MT:
            *ppTimer = &g_SmcCsEnt.SmcMt.TimerInfo.TimerId;
            *pulTimerLength = f_stNasSmsTimerLength.usTc1mLength;
            *ppucTimerSta = &g_SmcCsEnt.SmcMt.TimerInfo.ucTimerSta;
            break;

        /* SMR的定时器 */
        case SMC_TIMER_ID_TR1M:
            *ppTimer = &g_SmrEnt.SmrMo.aTimerInfo[0].TimerId;
            *pulTimerLength = f_stNasSmsTimerLength.usTr1mLength;
            *ppucTimerSta = &g_SmrEnt.SmrMo.aTimerInfo[0].ucTimerSta;
            break;
        case SMC_TIMER_ID_TR2M:
            *ppTimer = &g_SmrEnt.SmrMt.TimerInfo.TimerId;
            *pulTimerLength = f_stNasSmsTimerLength.usTr2mLength;
            *ppucTimerSta = &g_SmrEnt.SmrMt.TimerInfo.ucTimerSta;
            break;
        case SMC_TIMER_ID_TRAM:
            *ppTimer = &g_SmrEnt.SmrMo.aTimerInfo[1].TimerId;
            *pulTimerLength = f_stNasSmsTimerLength.usTramLength;
            *ppucTimerSta = &g_SmrEnt.SmrMo.aTimerInfo[1].ucTimerSta;
            break;

        default:
            SMS_LOG( PS_LOG_LEVEL_WARNING,
                     "SMS:SMC_GetTimerInfo: Not valid timer" );
            break;
    }
}
/*lint +e961*/

/******************************************************************************
 * 函数名称 ： WuepsSmsPidInit
 * 功能描述 ： WUEPS SMS PID的初始化函数
 * 参数说明 ： 无
 * 备    注 ：
 * 返 回 值 ： VOS_UINT32 初始化结果：
 *             0  : 成功
 *             非0: 失败
 *
 * 变更历史 ：
 *           No.  姓名      变更                                    日   期
 *           1    张志勇    新建                                   2005.02.24
 2.日    期   : 2012年12月28日
   作    者   : f62575
   修改内容   : 新生成函数 DTS2012122406218, 短信正向质量发现问题: 短信发送流程部分
 3.日    期   : 2013年02月04日
   作    者   : f62575
   修改内容   : DTS2013013104268, TC1M定时器超时重传次数自适应；
 *****************************************************************************/
VOS_UINT32 WuepsSmsPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
    case VOS_IP_LOAD_CONFIG:
        g_SmsStartFlg = SMS_TASK_START;                                     /* 设置TASK SMS启动标志未已经启动           */
        SMS_InitEntity();                                                   /* SMC SMR 实体初始化                       */

        SMS_GetCustomizedPara();
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
 函 数 名  : NAS_SMS_LogSmsStateInfo
 功能描述  : 勾SMS的状态
 输入参数  : ucSmsState: SMS的当前状态
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年06月30日
    作    者   : w00242748
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_SMS_LogSmsStateInfo(
    VOS_UINT8                           ucSmsState
)
{
    NAS_SMS_LOG_STATE_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_SMS_LOG_STATE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_SMS,
                                         sizeof(NAS_SMS_LOG_STATE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_SMS, "NAS_CC_LogMmStateInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_SMS_LOG_STATE_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_SMS;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_SMS_LOG_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = SMSOM_LOG_STATE_INFO_IND;
    pstMsg->ucSmsState                  = ucSmsState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_SMS, pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : SMS_GetPsConcatenateFlagFromNV
 功能描述  : 读PS域短信控制NV设置连续发送标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月18日
    作    者   : j00174725
    修改内容   : DTS2015051106584
*****************************************************************************/
VOS_VOID  SMS_GetPsConcatenateFlagFromNV(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    NAS_NV_SMS_PS_CTRL_STRU             stPsCtrl;

    /* 初始化 */
    PS_MEM_SET(&stPsCtrl, 0x0, sizeof(NAS_NV_SMS_PS_CTRL_STRU));

    /* 读取NV项 */
    ulRet = NV_Read(en_NV_Item_SMS_PS_CTRL,
                    &stPsCtrl,
                    sizeof(NAS_NV_SMS_PS_CTRL_STRU));
    if (NV_OK != ulRet)
    {
        /* 默认设置来不支持 */
        SMS_SetSmsPsConcatenateFlag(NAS_SMS_PS_CONCATENATE_DISABLE);

        return;
    }

    if (stPsCtrl.enSmsConcatenateFlag < NAS_SMS_PS_CONCATENATE_BUTT)
    {
        SMS_SetSmsPsConcatenateFlag(stPsCtrl.enSmsConcatenateFlag);
    }
    else
    {
        SMS_SetSmsPsConcatenateFlag(NAS_SMS_PS_CONCATENATE_DISABLE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : SMS_GetSmsFilterEnableFlgFromNV
 功能描述  : 从Nv中读取SMS短信过滤功能是否使能的标识
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID SMS_GetSmsFilterEnableFlgFromNV( VOS_VOID )
{
    NAS_NV_SMS_FILTER_CFG_STRU          stSmsFilterCfg;

    /* 初始化 */
    PS_MEM_SET(&stSmsFilterCfg, 0x00, sizeof(NAS_NV_SMS_FILTER_CFG_STRU));

    /* 读取NV项 */
    if (NV_OK != NV_Read(en_NV_Item_Sms_Log_Filter_Cfg,
                        &stSmsFilterCfg,
                         sizeof(NAS_NV_SMS_FILTER_CFG_STRU)))
    {
        /* 默认设置来不开启 */
        g_ulNasSmsFilterEnableFlg   = VOS_FALSE;

        return;
    }

    /* NV读取值保护 */
    if (VOS_FALSE != stSmsFilterCfg.ucSmsFilterEnableFlg)
    {
        stSmsFilterCfg.ucSmsFilterEnableFlg = VOS_TRUE;
    }

    g_ulNasSmsFilterEnableFlg       = (VOS_UINT32)stSmsFilterCfg.ucSmsFilterEnableFlg;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetSmsFilterFlg
 功能描述  : 提供给接入层获取过滤功能是否打开的Nv
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要进行过滤
             VOS_FALSE:不需要进行过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MM_GetSmsFilterFlg( VOS_VOID )
{
    return g_ulNasSmsFilterEnableFlg;
}

/*****************************************************************************
 函 数 名  : NAS_MML_GetSmsFilterFlg
 功能描述  : 提供给接入层获取过滤功能是否打开的Nv
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要进行过滤
             VOS_FALSE:不需要进行过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MML_GetSmsFilterFlg( VOS_VOID )
{
    return g_ulNasSmsFilterEnableFlg;
}

/*****************************************************************************
 函 数 名  : GUNAS_GetSmsFilterFlg
 功能描述  : 提供给GUNAS获取过滤功能是否打开的Nv
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要进行过滤
             VOS_FALSE:不需要进行过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_GetSmsFilterFlg( VOS_VOID )
{
    return g_ulNasSmsFilterEnableFlg;
}

/*****************************************************************************
 函 数 名  : SMS_SetSmsPsConcatenateFlag
 功能描述  : 设置PS域短信是否连续发送
 输入参数  : enFlag
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月18日
    作    者   : j00174725
    修改内容   : DTS2015051106584
*****************************************************************************/
VOS_VOID SMS_SetSmsPsConcatenateFlag(
    NAS_SMS_PS_CONCATENATE_ENUM_UINT8 enFlag
)
{
    g_enNasSmsPsConcatencateFlag = enFlag;
}

/*****************************************************************************
 函 数 名  : SMS_GetSmsPsConcatenateFlag
 功能描述  : 获取PS域短信是否连续发送
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月18日
    作    者   : j00174725
    修改内容   : DTS2015051106584
*****************************************************************************/
NAS_SMS_PS_CONCATENATE_ENUM_UINT8 SMS_GetSmsPsConcatenateFlag(VOS_VOID)
{
    return g_enNasSmsPsConcatencateFlag;
}



/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

