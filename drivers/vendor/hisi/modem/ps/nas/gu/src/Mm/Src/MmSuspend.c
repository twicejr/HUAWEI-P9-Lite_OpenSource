/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MmSuspend.c
  Author       : s46746
  Version      : V200R001
  Date         : 2005-08-16
  Description  : 该C文件给出了MM模块SuspendProc子模块的实现
  Function List:
        1) MM_GetConnectState
        2) MM_GetMsg
        3) MM_HandleCmMsg
        4) MM_HandleMsg
        5) MM_InsertMsg
        6) MM_RelMsgBuf
        7) MM_Restore
        8) MM_SaveMsg
        9) MM_SndMsgFuncChg
       10) MM_SuspendProc
       11) MM_SuspendTimeout

  History      :
  1. Date:2005-04-19
     Author: ---
     Modification:Create
  2.  s46746  2006.02.28  依据问题单A32D02234修改
  3.  s46746  2006.02.28  依据问题单A32D02235修改
  4.  s46746  2006.03.01  依据问题单A32D02192修改
  5.  s46746  2006.03.07  依据问题单A32D02356修改
  6.  s46746  2006-03-39  根据问题单A32D02486修改
  7.  s46746  2006-04-17  根据问题单A32D02829修改
  8.  x51137 2006/5/5 A32D03487
  9. 日    期   : 2006年9月9日
     作    者   : sunxibo id:46746
     修改内容   : 根据问题单号：A32D05803
  10.x51137 2006/11/3 A32D06511
  11.日    期  : 2006年12月4日
     作    者  : luojian id:60022475
     修改内容  : 问题单号:A32D07777
  12.日    期   : 2007年01月04日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D06408
  13.日    期   : 2007年01月25日
     作    者   : x51137
     修改内容   : 根据问题单号：A32D08545
  14.日    期   : 2007年07月31日
     作    者   : luojian id:60022475
     修改内容   : 问题单号:A32D12640,MM拒绝SS建连请求应该回EST_CNF消息
  15.日    期   : 2007年09月05日
     作    者   : s46746
     修改内容   : 根据问题单号：AT2D01456
  16.日    期  : 2008年9月4日
     作    者  : ouyangfei id:00132663
     修改内容  : 问题单号:AT2D05490,重建过程支持异系统切换
  17.日    期   : 2009年03月19日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D09743/AT2D10328,WAS的 D/F/P态下丢网处理
  18.日    期   : 2009年07月24日
     作    者   : z40661
     修改内容   : 异系统重选后，紧急呼叫不能接通
  19.日    期   : 2009年09月25日
     作    者   : s46746
     修改内容   : AT2D14760,异系统重选完成后立即上报出服务区，NAS上报服务状态不正确
************************************************************************/

/*****************************************************************************
   1 头文件包含
*****************************************************************************/
#include "MM_Inc.h"
#include "MmSuspend.h"
#include "MmGsmDifMsg.h"
#include "MM_Share.h"
#include "MmCmInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_SUSPEND_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/



/*****************************************************************************
   2 全局变量定义
*****************************************************************************/
/*****************************************************************************
功能：管理切换中保存的MM模块消息
取值范围：
存取它的函数或过程：MM_HandleMsg
                    MM_Restore
                    MM_InsertMsg
                    MM_GetMsg
存取时注意事项：
*****************************************************************************/
MM_SUSPEND_MSG_BUF_ST gstMmSuspendMsgQue;

MM_TIMER_ST  gstMmTimerSuspend;

extern VOS_UINT32   g_MmSuspendRspOpt;
extern VOS_UINT32   g_MmResumeRspOpt;

/* Deled by x51137 for A32D03487 at 2006/5/5 begin*/
/* extern VOS_UINT8 ucMmProcessFlg; */
/* Deled by x51137 for A32D03487 at 2006/5/5 end*/

/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_MM_SaveSuspendInfo
 功能描述  : 将RRMM_SUSPEND_IND_ST所带的全局变量信息缓存到MM的全局变量中
 输入参数  : pstMsg:MMC转发过来的挂起消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2013年4月1日
   作    者   : y00176023
   修改内容   : DSDS GUNAS II项目:增加对对目标RAT的保存
*****************************************************************************/
VOS_VOID NAS_MM_SaveSuspendInfo(
    MMCMM_SUSPEND_IND_STRU             *pstMsg
)
{
    /* 对g_MmGlobalInfo.stSuspendShare进行赋值 */
    g_MmGlobalInfo.stSuspendShare.enOldNetType      = pstMsg->ucSuspendOrigen;
    g_MmGlobalInfo.stSuspendShare.ucSuspendCause    = pstMsg->ucSuspendCause;
    g_MmGlobalInfo.stSuspendShare.ucSuspendFlg      = MM_SUSPEND_STATE;

    /*增加对目标RAT的保存*/
    g_MmGlobalInfo.stSuspendShare.enDestSuspendRat  = pstMsg->ucSuspendDestination;

    PS_MEM_CPY(g_MmGlobalInfo.stSuspendShare.astReTxMsg,
                pstMsg->astReTxMsg, sizeof(NAS_RRC_RE_TX_MSG_STRU));
}

/*****************************************************************************
 函 数 名  : NAS_MM_InitCcoFallbackCtx
 功能描述  : 对CCO 回退流程需要的MM上下文进行初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年1月9日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_InitCcoFallbackCtx(VOS_VOID)
{
    g_MmGlobalInfo.stBackupShare.ucState                    = MM_STATE_NULL;

    g_MmGlobalInfo.stBackupShare.ucPreState                 = MM_STATE_NULL;

    g_MmGlobalInfo.stBackupShare.enMmServiceState           = MM_NO_SERVICE;

    g_MmGlobalInfo.stBackupShare.ucNtMod                    = MM_NET_MODE_INVALID;

    g_MmGlobalInfo.stBackupShare.ucCsSigConnFlg             = VOS_FALSE;

    g_MmGlobalInfo.stBackupShare.enCsIntegrityProtect       = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    g_MmGlobalInfo.stBackupShare.usRac                      = 0;

    g_MmGlobalInfo.stBackupShare.ulT3212Value               = 0;

    /* 备份LU信息 */
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuType                  = MM_IE_LUT_TYPE_BUTT;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuAttmptCnt             = MM_CONST_NUM_0;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucRetryFlg                = MM_FALSE;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucEnterState              = MM_STATE_NULL;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3212ExpiredFlg         = MM_FALSE;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3213AttmptCnt          = MM_CONST_NUM_0;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucImmAccRejLuAttmptCnt    = MM_CONST_NUM_0;

    /* init CS域安全信息 */
    g_MmGlobalInfo.stBackupShare.stCsSecutityInfo = g_MmGlobalInfo.CsSecutityInfo;

    /* init MS CS域信息 */
    g_MmGlobalInfo.stBackupShare.stMsCsInfo = g_MmGlobalInfo.MsCsInfo;

    g_MmGlobalInfo.stBackupShare.enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    PS_MEM_CPY(g_MmGlobalInfo.stBackupShare.aucTmsi,
               NAS_MML_GetUeIdTmsi(), NAS_MML_MAX_TMSI_LEN);

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo),
               NAS_MML_GetSimCsSecurity(), sizeof(NAS_MML_SIM_CS_SECURITY_INFO_STRU));

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSuccLai),
               NAS_MML_GetCsLastSuccLai(), sizeof(NAS_MML_LAI_STRU));

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stBackupEquPlmnInfo),
               NAS_MML_GetEquPlmnList(), sizeof(NAS_MML_EQUPLMN_INFO_STRU));
}


/*****************************************************************************
 函 数 名  : NAS_MM_BackupCcoFallbackCtx
 功能描述  : 对CCO 回退流程需要的MM上下文进行备份，当CCO回退时，MM直接
              可以恢复到正常服务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2012年03月08日
   作    者   : l00130025
   修改内容   : DTS2012030107623: G->W Est_Rej_Cogest,CCO回退过程，Eplmn被删除，导致受限驻留
 3.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011082402748:EST CNF fail导致CCO回退时,3211不需要恢复启动
*****************************************************************************/
VOS_VOID NAS_MM_BackupCcoFallbackCtx(VOS_VOID)
{
    /* 对g_MmGlobalInfo.stBackupShare进行赋值，将g_MmGlobalInfo.stBackupShare
       的成员取值均来自g_MmGlobalInfo的其他成员变量 */

    g_MmGlobalInfo.stBackupShare.ucState                    = g_MmGlobalInfo.ucState;

    g_MmGlobalInfo.stBackupShare.ucPreState                 = g_MmGlobalInfo.ucPreState;

    g_MmGlobalInfo.stBackupShare.enMmServiceState           = g_MmGlobalInfo.ucMmServiceState;

    g_MmGlobalInfo.stBackupShare.ucNtMod                    = g_MmGlobalInfo.ucNtMod;

    g_MmGlobalInfo.stBackupShare.ucCsSigConnFlg             = g_MmGlobalInfo.ucCsSigConnFlg;

    g_MmGlobalInfo.stBackupShare.enCsIntegrityProtect       = g_MmSubLyrShare.MmShare.ucCsIntegrityProtect;

    g_MmGlobalInfo.stBackupShare.usRac                      = g_MmGlobalInfo.usRac;

    g_MmGlobalInfo.stBackupShare.ulT3212Value               = NAS_MM_GetNetworkT3212RandLen();

    /* 备份LU信息 */
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuType                  = g_MmGlobalInfo.LuInfo.ucLuType;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuAttmptCnt             = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucRetryFlg                = g_MmGlobalInfo.LuInfo.ucRetryFlg;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucEnterState              = g_MmGlobalInfo.LuInfo.ucEnterState;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3212ExpiredFlg         = g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3213AttmptCnt          = g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt;
    g_MmGlobalInfo.stBackupShare.stLuInfo.ucImmAccRejLuAttmptCnt    = g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt;

    /* 备份CS域安全信息 */
    g_MmGlobalInfo.stBackupShare.stCsSecutityInfo = g_MmGlobalInfo.CsSecutityInfo;

    /*备份MS CS域信息 */
    g_MmGlobalInfo.stBackupShare.stMsCsInfo = g_MmGlobalInfo.MsCsInfo;


    g_MmGlobalInfo.stBackupShare.enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

    PS_MEM_CPY(g_MmGlobalInfo.stBackupShare.aucTmsi,
               NAS_MML_GetUeIdTmsi(), NAS_MML_MAX_TMSI_LEN);

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo),
               NAS_MML_GetSimCsSecurity(), sizeof(NAS_MML_SIM_CS_SECURITY_INFO_STRU));

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSuccLai),
               NAS_MML_GetCsLastSuccLai(), sizeof(NAS_MML_LAI_STRU));

    PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stBackupEquPlmnInfo),
               NAS_MML_GetEquPlmnList(), sizeof(NAS_MML_EQUPLMN_INFO_STRU));


    /* 备份T3211的定时器状态 */
    g_MmGlobalInfo.stBackupShare.ucT3211Status = gstMmTimer[MM_TIMER_T3211].ucTimerStatus;


}

/*****************************************************************************
 函 数 名  : NAS_MM_ResumeCcoFallbackCtx
 功能描述  : 对CCO 回退流程，恢复CCO流程发起时的MM参数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月12日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2012年03月08日
   作    者   : l00130025
   修改内容   : DTS2012030107830: G->W Est_Rej_Cogest,CCO回退过程，T3211没有停止，导致错误发起LAU,LAU Type错误
 3.日    期   : 2012年03月08日
   作    者   : l00130025
   修改内容   : DTS2012030107623: G->W Est_Rej_Cogest,CCO回退过程，Eplmn被删除，导致受限驻留
 4.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011082402748:EST CNF fail导致CCO回退时,3211不需要恢复启动
*****************************************************************************/
VOS_VOID NAS_MM_ResumeCcoFallbackCtx(VOS_VOID)
{
    /* 对g_MmGlobalInfo的成员变量赋值，赋值的来源
       来自于g_MmGlobalInfo.stBackupShare */


    VOS_UINT32                                              i;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstBackupEplmnList;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstCurrentEplmnList;

    Mm_ComSetMmState(g_MmGlobalInfo.stBackupShare.ucState);


    g_MmGlobalInfo.ucPreState       = g_MmGlobalInfo.stBackupShare.ucPreState;

    g_MmGlobalInfo.ucMmServiceState = g_MmGlobalInfo.stBackupShare.enMmServiceState;

    g_MmGlobalInfo.ucNtMod          = g_MmGlobalInfo.stBackupShare.ucNtMod;

    g_MmGlobalInfo.ucCsSigConnFlg   = g_MmGlobalInfo.stBackupShare.ucCsSigConnFlg;

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect = g_MmGlobalInfo.stBackupShare.enCsIntegrityProtect;

    g_MmGlobalInfo.usRac            = g_MmGlobalInfo.stBackupShare.usRac;

    NAS_MM_SetNetworkT3212RandLen(g_MmGlobalInfo.stBackupShare.ulT3212Value);

    /* 还原 LU信息 */
    g_MmGlobalInfo.LuInfo.ucLuType                  = g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuType;
    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt             = g_MmGlobalInfo.stBackupShare.stLuInfo.ucLuAttmptCnt;
    g_MmGlobalInfo.LuInfo.ucRetryFlg                = g_MmGlobalInfo.stBackupShare.stLuInfo.ucRetryFlg;
    g_MmGlobalInfo.LuInfo.ucEnterState              = g_MmGlobalInfo.stBackupShare.stLuInfo.ucEnterState;
    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg         = g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3212ExpiredFlg;
    g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt          = g_MmGlobalInfo.stBackupShare.stLuInfo.ucT3213AttmptCnt;
    g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt    = g_MmGlobalInfo.stBackupShare.stLuInfo.ucImmAccRejLuAttmptCnt;

    /* 还原CS域安全信息 */
    g_MmGlobalInfo.CsSecutityInfo = g_MmGlobalInfo.stBackupShare.stCsSecutityInfo;

    /* 还原 MS CS域信息 */
    g_MmGlobalInfo.MsCsInfo = g_MmGlobalInfo.stBackupShare.stMsCsInfo;

    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
    for ( i = 0; i < MM_TIMER_MAX; i++ )
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
    {
        if ( MM_TIMER_PAUSE == gstMmTimer[i].ucTimerStatus)
        {
            gstMmTimer[i].ucTimerStatus = MM_TIMER_STOP;
        }
    }




    NAS_MML_SetUeIdTmsi(g_MmGlobalInfo.stBackupShare.aucTmsi);

    NAS_MML_SetSimCsSecurity(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo));

    PS_MEM_CPY(NAS_MML_GetCsLastSuccLai(),
               &(g_MmGlobalInfo.stBackupShare.stCsSuccLai), sizeof(NAS_MML_LAI_STRU));

    pstBackupEplmnList  = &(g_MmGlobalInfo.stBackupShare.stBackupEquPlmnInfo);

    pstCurrentEplmnList = NAS_MML_GetEquPlmnList();

    if (VOS_TRUE == NAS_MML_IsEquPlmnInfoChanged(pstBackupEplmnList))
    {
        /* 将EPLMN保存到MML全局变量 */
        PS_MEM_CPY(pstCurrentEplmnList, pstBackupEplmnList, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

        /* 将EPLMN更新到NV中 */
        NAS_MM_WriteEplmnNvim(pstCurrentEplmnList);
    }

    if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
    {
        NAS_MML_SetCsUpdateStatus(g_MmGlobalInfo.stBackupShare.enCsUpdateStatus);

        Mm_ComNasInfoSav(MM_STATUS_ATTACHED, NAS_MML_GetSimCsSecurityCksn());

        if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
        }
        else
        {
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
        }
    }


    /* cco之前T3211在启动CCO回退后恢复3211启动状态 */
    if (MM_TIMER_RUNNING == g_MmGlobalInfo.stBackupShare.ucT3211Status)
    {
        Mm_TimerResume(MM_TIMER_T3211);
    }
}



/*****************************************************************************
 Prototype      : MM_SaveMsg
 Description    : 存储消息
 Input          : pMsg 指向具体消息的指针
                  ucEventId 存储消息的 ID
                  ulLength 消息长度
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function

  2. x51137 2006/5/5 A32D03487
*****************************************************************************/
VOS_VOID MM_SaveMsg(const VOS_VOID* pMsg, VOS_UINT8 ucEventId, VOS_UINT32 ulLength)
{
    /* 记录存放消息的内存空间指针 */
    VOS_VOID       *pMsgBuf;

    VOS_VOID       *pMsgSnd;

    NAS_LOG1(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_NORMAL,
                    "STATE MM_SUSPEND_STATE RECEIVE Msg Id",ucEventId);

    /* 消息长度异常，丢弃此条消息 */
    if (ulLength > MM_MAX_MSG_LENGTH)
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                    "MM_SaveMsg: ERROR: Msg length is abnormal!");

        return;
    }

    pMsgBuf = PS_MEM_ALLOC(WUEPS_PID_MM, ulLength);

    if (VOS_NULL_PTR == pMsgBuf) /* 分配消息空间失败，此条消息被丢弃 */
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                "MM_SaveMsg : ERROR : Alloc Msg Memory Fail!");

        return;
    }
    pMsgSnd = pMsgBuf;

    /* 拷贝消息 */
    PS_MEM_CPY(pMsgSnd, pMsg, ulLength);

    /* 调用函数 MM_InsertMsg 缓存消息 */
    MM_InsertMsg(pMsgSnd, ucEventId);
    return;
}


/*****************************************************************************
 Prototype      : MM_SndMsgFuncChg
 Description    : 改变向接入层发送消息的函数指针
 Input          :
 Output         :
 Return Value   : 无
 Calls          :

 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
  2.日    期  : 2010年7月10日
    作    者  : l00130025
    修改内容  : 问题单号:DTS2010062601081,2G->3G重选后，Nsd被清零，导致网侧丢弃后续消息
  3.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,切换模式，回退后W/G下注册状态没有与NAS同步
*****************************************************************************/
VOS_VOID MM_SndMsgFuncChg()
{
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* 在 GSM 网络下 */
    {

        /* 将发送信令的函数指针指向 GSM 网络下的发送函数 */
        g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc          = MM_GasRrEstReq;
        g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc          = MM_GasRrRelReq;

        /* 将发送数据传输的函数指针指向 GSM 网络下的发送函数 */
        g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc     = MM_GasRrDataReq;

        g_NasMmImportFunc.ucFuncEnvironment                 = NAS_MML_NET_RAT_TYPE_GSM;

    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType()) /* 在 UMTS 网络下 */
    {
        g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc          = MM_WasRrEstReq;
        g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc          = As_RrRelReq;

        /* 将发送数据传输的函数指针指向 UMTS 网络下的发送函数 */
        g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc     = MM_WasRrDataReq;

        g_NasMmImportFunc.ucFuncEnvironment                 = NAS_MML_NET_RAT_TYPE_WCDMA;

        g_stMmNsd.ucNsdMod                                  = MM_NSD_MOD_R99_ONWARDS;
    }
    else
    {

    }

    return;
}

/*****************************************************************************
 Prototype      : MM_RetransferMsg
 Description    : MM模块在离开挂起状态后重新发送挂起前接入层未发送成功的消息
 Input          : 接入层未成功发送的消息
 Output         :
 Return Value   : 无
 Calls          :

 Called By      :

 History        : ---
  1.Date        : 2006-12-12
    Author      : s46746
    Modification: Created function
  2.日    期   : 2011年7月12日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，替换g_MmSubLyrShare.MmSuspendShare的全局变量
  3.日    期   : 2011年07月14日
    作    者   : z00161729
    修改内容   : V7R1 phase II全局变量调整修改,替换classmark2
  4.日    期   : 2014年04月03日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.CurLai替换成MML中的
  5.日    期   : 2015年08月04日
    作    者   : j00174725
    修改内容   :  DTS2015080400959
*****************************************************************************/
VOS_VOID MM_RetransferMsg()
{
    RRMM_EST_REQ_STRU  *pEstReqMsg;
    VOS_UINT8          *pData = VOS_NULL_PTR;
    RRMM_DATA_REQ_STRU *pDataReqMsg;
    IDNNS_STRU          stIdnnsInfo;
    VOS_INT32           Result = VOS_ERR;
    VOS_UINT8           i;
    VOS_UINT8           ucPd;

    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapability;

    pstMsCapability = NAS_MML_GetMsCapability();

    for (i = 0; i < NAS_RRC_MAX_RE_TX_MSG_NUM; i ++)
    {
        if ( NAS_RRC_NULL_RE_TX_MSG == g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType )
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,
                        "MM_RetransferMsg: INFO: Have not message retransfered.!");
            continue;
        }
        else if (NAS_RRC_RE_TX_EST_REQ_MSG == g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType)
        {
            pEstReqMsg = (RRMM_EST_REQ_STRU *)g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].aucNasReTxMsg;

            if (RRC_NAS_CS_DOMAIN != pEstReqMsg->ulCnDomainId)
            {
                continue;
            }
            stIdnnsInfo.ucEnterPara = (VOS_UINT8)pEstReqMsg->enSplmnSameRplmn;
            stIdnnsInfo.ucIdnnsType = (VOS_UINT8)pEstReqMsg->ulIdnnsType;
            switch (g_MmGlobalInfo.ucSuspendPreState)
            {
            case WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING :
                if (g_MmGlobalInfo.stSuspendShare.enOldNetType
                        != NAS_MML_GetCurrNetRatType())
                {
                    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                    {
                        if (MM_CONST_NUM_0 != pstMsCapability->aucClassmark2[0])
                        {
                            pEstReqMsg->FisrtNasMsg.ulNasMsgSize -= 5;
                        }
                    }
                    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                    {
                        /*补充classmark2*/
                        if (MM_CONST_NUM_0 != pstMsCapability->aucClassmark2[0])
                        {
                            pEstReqMsg->FisrtNasMsg.aucNasMsg[pEstReqMsg->FisrtNasMsg.ulNasMsgSize]
                                = 0x33;

                            MM_Fill_IE_ClassMark2(&pEstReqMsg->FisrtNasMsg.aucNasMsg[pEstReqMsg->FisrtNasMsg.ulNasMsgSize+1]);

                            pEstReqMsg->FisrtNasMsg.ulNasMsgSize += 5;
                        }
                    }
                    else
                    {
                    }
                }
                Result = g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc(pEstReqMsg->ulOpId,
                                                           RRC_NAS_CS_DOMAIN,
                                                           pEstReqMsg->ulEstCause,
                                                           &stIdnnsInfo,
                                                           /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                                                           (RRC_PLMN_ID_STRU *)NAS_MML_GetCurrCampPlmnId(),
                                                           /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                                                           pEstReqMsg->FisrtNasMsg.ulNasMsgSize,
                                                           (VOS_INT8*)pEstReqMsg->FisrtNasMsg.aucNasMsg);
                if (VOS_OK != Result)
                {
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "MM_RetransferMsg: Failed RrEstReqFunc.");
                }
                g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType
                    = NAS_RRC_NULL_RE_TX_MSG;
                Mm_ComSetMmState(g_MmGlobalInfo.ucSuspendPreState);
                break;
            case WAIT_FOR_RR_CONNECTION_MM_CONNECTION :
            case WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF :
            case WAIT_FOR_OUTGOING_MM_CONNECTION :
            case WAIT_FOR_RR_CONNECTION_IMSI_DETACH :
                Result = g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc(pEstReqMsg->ulOpId,
                                                           RRC_NAS_CS_DOMAIN,
                                                           pEstReqMsg->ulEstCause,
                                                           &stIdnnsInfo,
                                                           /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                                                           (RRC_PLMN_ID_STRU *)NAS_MML_GetCurrCampPlmnId(),
                                                           /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                                                           pEstReqMsg->FisrtNasMsg.ulNasMsgSize,
                                                           (VOS_INT8*)pEstReqMsg->FisrtNasMsg.aucNasMsg);
                if (VOS_OK != Result)
                {
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "MM_RetransferMsg: Failed RrEstReqFunc.");
                }
                g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType
                    = NAS_RRC_NULL_RE_TX_MSG;
                Mm_ComSetMmState(g_MmGlobalInfo.ucSuspendPreState);
                break;
            default:
                break;
            }
        }
        else if (NAS_RRC_RE_TX_DATA_REQ_MSG == g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType)
        {
            pDataReqMsg = (RRMM_DATA_REQ_STRU *)g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].aucNasReTxMsg;
            if (RRC_NAS_CS_DOMAIN != pDataReqMsg->ulCnDomainId)
            {
                continue;
            }

            pData = (VOS_UINT8 *)pDataReqMsg->SendNasMsg.aucNasMsg;
            ucPd = pData[0] & MM_IE_PD_MASK;
            if ((MM_IE_PD_MM_MSG == ucPd) || (MM_IE_PD_CALL_CONTROL == ucPd)
               || (MM_IE_PD_NON_CALL_RLT_SS_MSG == ucPd))
            {
                g_stMmNsd.ucNsd = (pData[1] >> 6) % g_stMmNsd.ucNsdMod;
            }

            Result = g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc(RRC_NAS_CS_DOMAIN,
                                                            (VOS_UINT8)pDataReqMsg->ulPriorityInd,
                                                            pDataReqMsg->SendNasMsg.ulNasMsgSize,
                                                            (VOS_INT8 *)pDataReqMsg->SendNasMsg.aucNasMsg);
            if (VOS_OK != Result)
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "MM_RetransferMsg: Failed RrEstReqFunc.");
            }
            g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType
                    = NAS_RRC_NULL_RE_TX_MSG;
        }
        else
        {
            g_MmGlobalInfo.stSuspendShare.astReTxMsg[i].enReTxMsgType
                    = NAS_RRC_NULL_RE_TX_MSG;
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
                        "MM_RetransferMsg: WARNING: Message retransfered type is error.!");
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : MM_Restore
 Description    : MM模块在离开挂起状态后对消息的恢复处理
 Input          : MsgQue 缓存的消息队列
 Output         :
 Return Value   : 无
 Calls          :

 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_Restore()
{
    /* 消息单元结构指针 */
    MM_SUSPEND_MSG_CELL_ST             *pstMsgCell;

    /* 循环变量 */
    VOS_UINT8                           i;

    /* 处理状态消息结构 */
    MM_MSG_MM_STATUS_STRU               stMsg;

    /* 更正消息索引的值 */
    if (gstMmSuspendMsgQue.ucMsgNum < MM_MAX_MSG_NUM)
    {
        /* 从第一条消息开始恢复 */
        gstMmSuspendMsgQue.ucIndex      = MM_CONST_NUM_0;
    }

    /* 逐条处理缓存消息队列中消息 */
    i = gstMmSuspendMsgQue.ucMsgNum;
    for ( ; i > MM_CONST_NUM_0; i --)
    {
        /* 获得一条消息单元 */
        pstMsgCell = MM_GetMsg();
        if (VOS_NULL_PTR == pstMsgCell)
        {
            /* 不处理此条消息 */
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                    "MM_Restore: ERROR: Msg got from Msg buf is NULL!");

            continue;
        }

        if (MM_EVENT_ID_STATUS_95 == pstMsgCell->ucEventId)/* 消息 ID 为 MM_EVENT_ID_STATUS_95 */
        {
            /* 处理与 HSS4100 V100R001 相同 */
            PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

            stMsg.MmIeRjctCause.ucRejCause
                                        = NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG;
            Mm_ComMsgMmStatusSnd(&stMsg);

            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
                    "MM_Restore: WARNING: Msg ID is MM_EVENT_ID_STATUS_95,send STATUS!");
        }
        else if (MM_EVENT_ID_STATUS_96 == pstMsgCell->ucEventId)/* 消息 ID 为 MM_EVENT_ID_STATUS_96 */
        {
            /* 处理与 HSS4100 V100R001 相同 */
            PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

            stMsg.MmIeRjctCause.ucRejCause
                                        = NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF;
            Mm_ComMsgMmStatusSnd(&stMsg);

            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
                    "MM_Restore: WARNING: Msg ID is MM_EVENT_ID_STATUS_96,send STATUS!");
        }
        else /* 正常消息 */
        {
            NAS_LOG1(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,
                    "MM_Restore: INFO: After suspend handle msg id.",pstMsgCell->ucEventId);

            /* 调用函数 aMmStateTable 进行处理 */
            /*lint -e961*/
            gaMmStateTable[pstMsgCell->ucEventId - 1][g_MmGlobalInfo.ucState]
                    (pstMsgCell->pstMsg);
            /*lint +e961*/
        }

        /* 释放此条消息资源 */
        /*VOS_FreeMsg(WUEPS_PID_MM, (MsgBlock* )pstMsgCell->pstMsg);*/
        PS_MEM_FREE(WUEPS_PID_MM, pstMsgCell->pstMsg);
        pstMsgCell->pstMsg              = VOS_NULL_PTR;
    }

    gstMmSuspendMsgQue.ucMsgNum         = 0;
    gstMmSuspendMsgQue.ucIndex          = 0;

    return;
}

/*****************************************************************************
 Prototype      : MM_InsertMsg
 Description    : 向缓存队列增加一条消息
 Input          : MsgQue 消息缓存队列的结构
                  pMsg 要增加的具体消息
                  ucEventId 增加消息对应的事件ID
 Output         :
 Return Value   : MM_TRUE  增加消息成功
                  MM_FALSE 增加消息失败
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_InsertMsg(VOS_VOID *pMsg, VOS_UINT8 ucEventId)
{
    /* 消息单元结构指针 */
    MM_SUSPEND_MSG_CELL_ST             *pstMsgCell;

    /* 依据消息索引找到此条消息保存在缓存队列中位置 */
    pstMsgCell = &(gstMmSuspendMsgQue.astMsg[gstMmSuspendMsgQue.ucIndex]);

    if (VOS_NULL_PTR != pstMsgCell->pstMsg)
    {
        /*VOS_FreeMsg(WUEPS_PID_MM, (MsgBlock* )pstMsgCell->pstMsg);*/
        PS_MEM_FREE(WUEPS_PID_MM, pstMsgCell->pstMsg);
        pstMsgCell->pstMsg              = VOS_NULL_PTR;
    }

    /* 将 pMsg 和 ucEvendId 保存到缓存队列相应的消息单元中 */
    pstMsgCell->pstMsg                  = pMsg;
    pstMsgCell->ucEventId               = ucEventId;

    /* 消息队列中消息数目增 1 */
    if (gstMmSuspendMsgQue.ucMsgNum < MM_MAX_MSG_NUM)
    {
        gstMmSuspendMsgQue.ucMsgNum    += MM_CONST_NUM_1;
    }

    /* 消息队列中消息索引增 1 */
    gstMmSuspendMsgQue.ucIndex         += MM_CONST_NUM_1;
    gstMmSuspendMsgQue.ucIndex          = gstMmSuspendMsgQue.ucIndex % MM_MAX_MSG_NUM;

    return;
}

/*****************************************************************************
 Prototype      : MM_GetMsg
 Description    : 从缓存队列中取出一条消息
 Input          : MsgQue 缓存消息的队列
 Output         :
 Return Value   : 取得的具体消息
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function
*****************************************************************************/
MM_SUSPEND_MSG_CELL_ST* MM_GetMsg()
{
    /* 消息单元结构指针 */
    MM_SUSPEND_MSG_CELL_ST  *pstMsgCell;

    if (gstMmSuspendMsgQue.ucMsgNum > MM_CONST_NUM_0) /* 缓存消息数目大于零 */
    {
        /* 依据消息索引找到当前被提取消息单元 */
        pstMsgCell = &(gstMmSuspendMsgQue.astMsg[gstMmSuspendMsgQue.ucIndex]);

        /* 消息索引增 1 */
        gstMmSuspendMsgQue.ucIndex     += 1;
        gstMmSuspendMsgQue.ucIndex      = gstMmSuspendMsgQue.ucIndex % MM_MAX_MSG_NUM;

        /* 消息队列中消息数目减 1 */
        gstMmSuspendMsgQue.ucMsgNum    -= 1;

        /* 返回 pstMsgCell */
        if (VOS_NULL_PTR == pstMsgCell->pstMsg)
        {
            /* 此消息为空，打印异常 */
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                    "MM_GetMsg: ERROR: Msg pointer in Msg buf is NULL!");

            return VOS_NULL_PTR;
        }
        return pstMsgCell;
    }
    else
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
                    "MM_GetMsg: WARNING: Msg buf is empty!");

        /* 返回空指针 */
        return VOS_NULL_PTR;
    }
}

/*****************************************************************************
 Prototype      : MM_RelMsgBuf
 Description    : 释放缓存队列消息
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
VOS_VOID MM_RelMsgBuf()
{
    /* 消息单元结构指针 */
    MM_SUSPEND_MSG_CELL_ST             *pstMsgCell;

    /* 更正消息索引的值 */
    if (gstMmSuspendMsgQue.ucMsgNum < MM_MAX_MSG_NUM)
    {
        /* 从第一条消息开始释放 */
        gstMmSuspendMsgQue.ucIndex      = MM_CONST_NUM_0;
    }

    /* 逐条释放消息队列中消息资源 */
    while (gstMmSuspendMsgQue.ucMsgNum > MM_CONST_NUM_0) /* 缓存队列非空 */
    {
        /* 调用函数 MM_GetMsg 获得一条消息单元 */
        pstMsgCell = MM_GetMsg();
        if (VOS_NULL_PTR == pstMsgCell)
        {
            /* 不处理此条消息 */
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,
                    "MM_Restore: ERROR: Msg got from Msg buf is NULL!");

            continue;
        }

        /* 释放此消息单元资源 */
        /*VOS_FreeMsg(WUEPS_PID_MM, (MsgBlock* )pstMsgCell->pstMsg);*/
        PS_MEM_FREE(WUEPS_PID_MM, pstMsgCell->pstMsg);
        pstMsgCell->pstMsg              = VOS_NULL_PTR;
    }

    gstMmSuspendMsgQue.ucIndex          = MM_CONST_NUM_0;
    return;
}

/*****************************************************************************
 Prototype      : MM_SuspendTimeout
 Description    : 缓存队列保护定时器超时的处理
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-16
    Author      : s46746
    Modification: Created function

  2. x51137 2006/5/5 A32D03487
  3.日    期  : 2006年12月4日
    作    者  : luojian id:60022475
    修改内容  : 问题单号:A32D07777
  4.日    期   : 2011年7月12日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，替换g_MmSubLyrShare.MmSuspendShare的全局变量
*****************************************************************************/
VOS_VOID MM_SuspendTimeout()
{
    MMCMM_RESUME_IND_STRU               stResumeInd;;

    NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
            "MM_SuspendTimeout: WARNING: Timer MM_TIMER_PROTECT_SUSPEND expire!");
    #if 0

    if ((MM_TIMER_STOPPED == gstMmTimerSuspend.ucTimerStatus) || (MM_TIMER_ERROR == gstMmTimerSuspend.ucTimerStatus))
    {
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,
            "MM_SuspendTimeout: WARNING: Timer MM_TIMER_PROTECT_SUSPEND have been stopped!");

        return;
    }

    gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;

    /* 当前处于挂起状态 */
    if (MM_SUSPEND_STATE == g_MmSubLyrShare.MmSuspendShare.ucSuspendFlg)
    {

        /* 释放缓存队列资源 */
        MM_RelMsgBuf();
    }
    else /* 非挂起状态，恢复缓存队列消息 */
    {

        /* 调用函数 MM_SndMsgFuncChg 切换向接入层发送消息的函数 */
        MM_SndMsgFuncChg();

        /* 该变记录 MM 连接的全局变量值 */
        g_MmSubLyrShare.MmShare.MmSuspendCause = MM_INVALID_SUSPEND_CAUSE;

        /* 调用函数 MM_Restore 处理缓存队列消息 */
        MM_Restore();
    }
    #endif

    /* 当前处于挂起状态 */
    if (MM_SUSPEND_STATE == g_MmGlobalInfo.stSuspendShare.ucSuspendFlg)
    {
        /* restart timer */
        if (VOS_OK != Mm_StartRelTimer(&(gstMmTimerSuspend.stTimer),
                                            WUEPS_PID_MM,
                                            gstMmTimerSuspend.ulTimerLength,
                                            MM_TIMER_PROTECT_SUSPEND,
                                            MM_CONST_NUM_0,
                                            VOS_RELTIMER_NOLOOP))
        {
            gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"restart MM_TIMER_PROTECT_SUSPEND fail");
        }
        else
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,"restart MM_TIMER_PROTECT_SUSPEND success");
        }
    }
    else /* 非挂起状态，恢复缓存队列消息 */
    {
        gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;

        /* 原有代码是传空指针进入，由于在Mm_Cell_S32_E85中，只判定了CS域和
           PS域的结果，因此这里做了个特殊处理，传入成功，原有代码判定也是
           存在问题的，后续MM优化时，再做处理*/
        stResumeInd.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
        stResumeInd.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
        Mm_Cell_S32_E85( &stResumeInd );
    }

    return;
}


/*****************************************************************************
 Prototype      : Mm_Cell_S3_E84
 Description    : process after MMCMM_SUSPEND_IND
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.日    期  : 2006年12月4日
    作    者  : luojian id:60022475
    修改内容  : 问题单号:A32D07777
  3.日    期  : 2008年9月4日
    作    者  : ouyangfei id:00132663
    修改内容  : 问题单号:AT2D05490,重建过程支持异系统切换
  4.日    期   : 2010年09月27日
    作    者   : z00161729
    修改内容   : 问题单号AT2D19560:问题单号AT2D19560:W重定向到G小特性NAS修改合入,异系统切换，当前处在建链请求状态，模拟发EST_CNF(fail)清除建链请求
  5.日    期   : 2011年7月12日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，用于缓存CCO流程中的MM全局变量
  6.日    期   : 2011年07月28日
    作    者   : w00167002
    修改内容   : v7r1_phaseII 内部消息发送调整
  7.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011082402748:EST CNF fail导致CCO回退时,3211不需要恢复启动
  8.日    期   : 2013年9月22日
    作    者   : w00176964
    修改内容   : VoLTE_PhaseII项目调整:增加CS安全上下文获取流程
  9.日    期   : 2015年1月4日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI HO定时器修改
*****************************************************************************/
VOS_VOID Mm_Cell_S3_E84( VOS_VOID* pMsg )
{
    VOS_UINT8                           i = 0;

    /* 停MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO或MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO的处理与原来相同:
       只有在CSFB标志存在时，才停定时器. 如果需要做LAU，等待LAU结果;如果不需要做LAU, MM报注册假流程
       其他情况下不停定时器，等定时器超时 */
    if ( MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_CS_HO_WAIT_SYSINFO) )
    {
        Mm_TimerStop(MM_TIMER_CS_HO_WAIT_SYSINFO);
    }

    /* 缓存当前SUSPEND消息中的信息到MM的全局变量中 */
    NAS_MM_SaveSuspendInfo((MMCMM_SUSPEND_IND_STRU*)pMsg);

    if ( ( MMC_SUSPEND_CAUSE_CELLCHANGE == ((MMCMM_SUSPEND_IND_STRU*)pMsg)->ucSuspendCause )
      && ( MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState ) )
    {
        /* 备份MM的全局变量，用于CCO回退时使用 */
        NAS_MM_BackupCcoFallbackCtx();
    }

    /* suspend timer except period timer */
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
    for ( i=0; i< MM_TIMER_MAX; i++ )
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
    {
        if ( MM_TIMER_RUNNING == gstMmTimer[i].ucTimerStatus )
        {
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-24, begin */
            /* T3242和T3243定时器不暂停,因为对应的INTRAT_CHANGE状态也进行了处理 */
            if ((MM_TIMER_T3212 != i)
             && (MM_TIMER_T3242 != i)
             && (MM_TIMER_T3243 != i)
             && (MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE != i))
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-24, end */
            {
                Mm_TimerPause(i);
            }
        }
    }

    g_MmGlobalInfo.ucSuspendPreState = g_MmGlobalInfo.ucState;
    Mm_ComSetMmState(MM_INTER_RAT_CHANGE);

    /* 更新消息缓存队列中索引值 */
    gstMmSuspendMsgQue.ucIndex  = MM_CONST_NUM_0;

    if (VOS_OK != Mm_StartRelTimer(&(gstMmTimerSuspend.stTimer),
                                            WUEPS_PID_MM,
                                            gstMmTimerSuspend.ulTimerLength,
                                            MM_TIMER_PROTECT_SUSPEND,
                                            MM_CONST_NUM_0,
                                            VOS_RELTIMER_NOLOOP))
    {
        gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"start MM_TIMER_PROTECT_SUSPEND fail");
    }
    else
    {
        gstMmTimerSuspend.ucTimerStatus = MM_TIMER_START;
        NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,"start MM_TIMER_PROTECT_SUSPEND success");
    }

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* L到GU的切换流程,增加CS安全上下文的获取流程 */
    if  ((MMC_SUSPEND_CAUSE_HANDOVER  == ((MMCMM_SUSPEND_IND_STRU*)pMsg)->ucSuspendCause)
      && (MMC_SUSPEND_ORIGEN_LTE      == ((MMCMM_SUSPEND_IND_STRU*)pMsg)->ucSuspendOrigen))
    {
        /* 备份MML的安全上下文用于失败回退 */
        PS_MEM_CPY(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo),
                   NAS_MML_GetSimCsSecurity(), sizeof(NAS_MML_SIM_CS_SECURITY_INFO_STRU));

        /* 发送ID_MM_LMM_HO_SECU_INFO_REQ消息到LMM */
        NAS_MM_SndLmmHoSecuInfoReq();

        /* 启动保护定时器MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF */
        Mm_TimerStart(MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

        return;
    }
#endif

    NAS_MM_SndMmcSuspendRsp();
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-9-22, end */

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_SUSPEND_IND_RECEIVED, 0);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MM_EndCsfbFlow
 功能描述  : 结束CSFB流程的处理
 输入参数  : enCsfbServiceStatus - CSFB状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月14日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : DTS2012083102536:支持cc呼叫重建
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
 4.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容   :DTS2013082903019:支持ss重发功能
 5.日    期   :2014年6月13日
   作    者   :w00242748
   修改内容   :DSDS III 新特性
 6.日    期   :2014年9月20日
   作    者   :s00217060
   修改内容   :cs_err_log原因值上报
 7.日    期   :2015年10月16日
   作    者   :j00174725
   修改内容   :DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MM_EndCsfbFlow(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8 enCsfbServiceStatus,
    NAS_MMCM_REL_CAUSE_ENUM_UINT32         enRelCause
)
{

    /* LAU携带CSMT标志，启动定时器进行保护 */
    NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);
    Mm_TimerStop(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

    NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);

    /* MO CSFB流程中在L下恢复，认为CSFB失败，向CC或SS回复建链失败，清缓存 */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST == enCsfbServiceStatus)
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                            enRelCause);     /* 通知CC建立失败 */

            NAS_MM_ClearConnCtrlInfo(MM_IE_PD_CALL_CONTROL);
        }

        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* 更新CSFB状态 */
        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        return;
    }

     /* MO CSFB流程中在L下恢复，认为CSFB失败，向CC或SS回复建链失败，清缓存 */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST == enCsfbServiceStatus)
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, enRelCause);

            NAS_MM_ClearConnCtrlInfo(MM_IE_PD_NON_CALL_RLT_SS_MSG);
        }

        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* 更新CSFB状态为不存在 */
        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        return;
    }

    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == enCsfbServiceStatus)
    {
        Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                      enRelCause);     /* 通知CC建立失败 */

        /* Mm_RcvCcEstReq函数判断如果是紧急呼设置了ucEstingCallTypeFlg，需要清除 */
        if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg = MM_FALSE;
            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
        }

        NAS_MM_ClearConnCtrlInfo(MM_IE_PD_CALL_CONTROL);

        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* 更新CSFB状态为不存在 */
        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        return;
    }

    /* 当前存在CSFB被叫 */
    if (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == enCsfbServiceStatus)
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* 更新CSFB状态为不存在 */
        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

        /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
        /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */
    }

    return;
}


/*****************************************************************************
函 数 名  : NAS_MM_ResumeBackToGU_CSFB
功能描述  : CSFB流程异系统变换到GU
输入参数  : enCsfbServiceStatus - CSFB状态
输出参数  : 无
返 回 值  : 无
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2012年2月14日
  作    者   : z00161729
  修改内容   : 新生成函数
2.日    期   : 2012年3月27日
  作    者   : w00166186
  修改内容   : CSFB&PPAC&ETWS&ISR 开发 ENERGENCY CALL
3.日    期   : 2014年05月30日
  作    者   : s00217060
  修改内容   : 支持ultra_flash_csfb时，收到resume_ind直接发cm_service_request,提升MO CSFB电话接通速度
*****************************************************************************/
VOS_VOID NAS_MM_ResumeBackToGU_CSFB(
    MMCMM_RESUME_IND_STRU                                  *pstResumeInd,
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus
)
{
    VOS_UINT8                                               ucUltraFlashCsfbFlg;

    ucUltraFlashCsfbFlg = NAS_MML_GetUltraFlashCsfbSupportFlg();

    if (MMC_RESUME_RESULT_SUCCESS != pstResumeInd->ucCsResumeResult)
    {
        NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_RESUME_TO_GU_FAIL,
                                  NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CSFB MT异常 */
        NAS_MM_CsfbMtFailRecord();
#endif

        /* 异系统失败，认为CSFB流程失败 */
        NAS_MM_EndCsfbFlow(enCsfbServiceStatus, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL);
        return;
    }

    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_GU_RESUME_IND_RECEIVED,
                              NAS_MML_REG_FAIL_CAUSE_NULL);

    /* 只有在CSFB标志存在时才会走到这里 */
    if (MMC_SUSPEND_CAUSE_HANDOVER == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
    {
        /* CSFB网络支持HO到GU,MM_CONNECTION_ACTIVE收到resume_ind直接发cm_service_request,提升MO CSFB电话接通速度 */
        /* MT时不需要发cm_service_request，直接等网络的setup_ind */
        if ((VOS_TRUE             == ucUltraFlashCsfbFlg)
         && (MM_CONNECTION_ACTIVE == g_MmGlobalInfo.ucState))
        {
            Mm_ComCheckDelayMmConn(MM_FALSE);

            NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_CS_HO_WAIT_SYSINFO);
        }
        else
        {
            if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == enCsfbServiceStatus)
            {
                /* 启动等系统消息的定时器 */
                NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO);
            }
            else
            {
                NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO);
            }
        }
    }

}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
/*****************************************************************************
 函 数 名  : NAS_MM_ProcResumeIndBackToLTE
 功能描述  : 处理异系统回到LTE后收到resume ind消息的处理
 输入参数  : pstResumeMsg----MMC的resume ind消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年10月12日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年1月18日
   作    者   : w00242748
   修改内容   : DTS2014011302424:L下主叫，CSFB失败，回退到L后，MM模块给CC模块发送
                释放链接请求，电话业务终止。为提高用户体验，如果回退到L的话，则需
                发送搜网。
 3.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
 4.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve修改
 5.日    期   : 2015年10月16日
   作    者   : j00174725
   修改内容   : DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndBackToLTE(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
    VOS_UINT8                           ucTimerId;

    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        /* 停止除了CSFB MT保护定时器以外的所有定时器 */
        ucTimerId = MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE;
        NAS_MM_TimerStopExceptSpecialTimers(1, &ucTimerId);
    }
    else
    {
        /* 停止除了T3212以外的所有定时器 */
        ucTimerId = MM_TIMER_T3212;
        NAS_MM_TimerStopExceptSpecialTimers(1, &ucTimerId);
    }


    g_MmGlobalInfo.enPreRatType = NAS_MML_NET_RAT_TYPE_LTE;


    /* W异系统到LTE后需清除联合注册建链失败次数 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;
    }

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
    /* LTE到GU的handover流程,回退到LTE时需要回退CS的安全上下文 */
    if ((MMC_SUSPEND_CAUSE_HANDOVER == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_LTE   == g_MmGlobalInfo.stSuspendShare.enOldNetType))
    {
        NAS_MML_SetSimCsSecurity(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo));
    }

#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_TRUE == NAS_MM_GetSrvccFlg())
    {
        NAS_MM_ProcResumeIndBackToLTE_Srvcc();
    }
#endif
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

    /* Modified by z00234330 for ISR测试发现问题, 2013-3-25, begin */
    NAS_MM_ChgStateIntoLMode();
    /* Modified by z00234330 for ISR测试发现问题, 2013-3-25, end */

    /* 清除MML中的CS连接相关信息 */
    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);

    if (MM_CS_SIG_CONN_ABSENT != g_MmGlobalInfo.ucCsSigConnFlg)
    {
        g_MmGlobalInfo.ucCsSigConnFlg  = MM_CS_SIG_CONN_ABSENT;

        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);


    /* 异系统失败回退到LTE时，记录异常状态为CSFB MT触发搜网 */
    NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_LTE_RESUME_IND_RECEIVED,
                              NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BACK_TO_LTE);


    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* 异系统重回LTE后，则需要让MMC继续搜网 */
        NAS_MM_SndMmcPlmnSearchInd(MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE);

    }
    else
    {
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_BACK_TO_LTE);

        NAS_MM_SetCsfbMtLauFlg(VOS_FALSE);

        Mm_TimerStop(MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE);

        NAS_MML_SetCsfbMtPagingTimerStatus(NAS_MML_MT_CSFB_PAGING_TIMER_STOP);

#if (FEATURE_ON == FEATURE_PTM)
        /* 记录CSFB MT异常 */
        NAS_MM_CsfbMtFailRecord();
#endif
    }

    MM_RelMsgBuf();

    return;
}

#endif

/* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 函 数 名  : NAS_MM_ProcResumeToHRPD
 功能描述  : 处理异系统到HRPD后收到resume ind消息的处理
 输入参数  : pstResumeMsg----MMC的resume ind消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2014年1月27日
   作    者   : s00246516
   修改内容   : 新生成函数
 2.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeToHRPD(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
    /* 停止所有的定时器 */
    Mm_TimerStop(MM_TIMER_STOP_ALL);

    /* 状态迁移到无服务状态 */
    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* 清除MML中的CS连接相关信息 */
    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    NAS_MML_SetCsServiceBufferStatusFlg(VOS_FALSE);

    if (MM_CS_SIG_CONN_ABSENT != g_MmGlobalInfo.ucCsSigConnFlg)
    {
       g_MmGlobalInfo.ucCsSigConnFlg  = MM_CS_SIG_CONN_ABSENT;

       NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

    /* 释放所有MM连接 */
    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_EHRPD);

    /* 释放挂起过程中的缓存 */
    MM_RelMsgBuf();

    return;
}
#endif
/* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

/*****************************************************************************
 函 数 名  : NAS_MM_ResumeSuspendInfo
 功能描述  : 恢复挂起信息
 输入参数  : pstResumeMsg--MMC转发过来的resume ind消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年10月12日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ResumeSuspendInfo(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
    VOS_UINT8                           i;

    /* 如果是CCO回退导致的挂起原因，则恢复上下文 */
    if ((MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
     && (MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.stBackupShare.ucState))
    {
        NAS_MM_ResumeCcoFallbackCtx();
    }
    else if (TEST_CONTROL_ACTIVE !=  g_MmGlobalInfo.ucSuspendPreState)
    {
        /* 因为当前为挂起状态,如果此时备份此状态,当需要恢复到原来的状态时,
           会导致MM状态错误,所以此时不能备份原来的状态 */
        /* g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState; */
        Mm_ComSetMmState(g_MmGlobalInfo.ucSuspendPreState);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_ResumeSuspendInfo:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
    }
    else
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    }

    /* resume timer  */
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
    for ( i = 0; i < MM_TIMER_MAX; i++ )
    /* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
    {
        if ( MM_TIMER_PAUSE == gstMmTimer[i].ucTimerStatus )
        {
            /* CCO回退时,接入模式变更,3211通过备份的状态恢复启动 */
            if ((g_MmGlobalInfo.stSuspendShare.enOldNetType != NAS_MML_GetCurrNetRatType())
             && (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK      == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
             && (MM_TIMER_T3211 == i))
            {
                continue;
            }

            Mm_TimerResume(i);
        }
    }

    /* 停止缓存队列保护定时器 */
    if ( MM_TIMER_START == gstMmTimerSuspend.ucTimerStatus )
    {
        if (VOS_OK != Mm_StopRelTimer(WUEPS_PID_MM, MM_TIMER_PROTECT_SUSPEND, &(gstMmTimerSuspend.stTimer)))
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"Stop MM_TIMER_PROTECT_SUSPEND fail.");
        }
        else
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,"Stop MM_TIMER_PROTECT_SUSPEND success");
        }
        gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcResumeIndInterSysChanged
 功能描述  : 处理异系统变换到GU后收到resume ind的消息处理
 输入参数  : pstResumeMsg--MMC转发过来的resume ind消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年10月12日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndInterRatChangedToGU(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
    RRMM_EST_CNF_STRU                  *pucNasMsg = VOS_NULL_PTR;

    /* 接入技术发生改变 删除RRC链接 */
    if (MMC_SUSPEND_CAUSE_HANDOVER != g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
    {
        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
    }

    if (WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucState)
    {
        /* MM 状态迁回到发起建链前的状态 */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    }

    /* 如果发生过系统间改变，需要通知接入层PTMSI信息 */
    NAS_MM_NotifyAsInfoChgReq();

    /* 异系统切换W到G */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        g_MmSubLyrShare.MmShare.ucCsIntegrityProtect  = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;
    }

    if ((g_MmGlobalInfo.ucState  == WAIT_FOR_RR_CONNECTION_IMSI_DETACH)
     || ((g_MmGlobalInfo.ucState == WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF)
      && (g_MmGlobalInfo.ucCsSigConnFlg != MM_CS_SIG_CONN_PRESENT)))
    {
        g_MmGlobalInfo.bWaitingEstCnf = VOS_FALSE;
        pucNasMsg  = (RRMM_EST_CNF_STRU *)MM_MEM_ALLOC(VOS_MEMPOOL_INDEX_MM,
                                  sizeof(RRMM_EST_CNF_STRU),WUEPS_MEM_NO_WAIT);
        if( VOS_NULL_PTR == pucNasMsg )
        {
            /* 内存申请失败                             */
             PS_NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR, "NAS_MM_ProcResumeIndInterRatChangedToGU:ERROR: MALLOC RRMM_EST_CNF_STRU ERROR!");
             return;
        }

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            pucNasMsg->MsgHeader.ulSenderPid = UEPS_PID_GAS;
        }
        else
        {
            pucNasMsg->MsgHeader.ulSenderPid = WUEPS_PID_WRR;
        }

        pucNasMsg->MsgHeader.ulReceiverPid = WUEPS_PID_MM;
        pucNasMsg->ulCnDomainId            = RRC_NAS_CS_DOMAIN;
        pucNasMsg->ulOpId                  = g_MmGlobalInfo.ucRrEstReqOpid;
        pucNasMsg->ulResult                = RRC_EST_RJ_UNSPEC;
        /*lint -e961*/
        gaMmStateTable[32 - 1][g_MmGlobalInfo.ucState](pucNasMsg);/* the event of RRMM_REL_IND is 32 */
        /*lint +e961*/
        MM_MEM_FREE( VOS_MEMPOOL_INDEX_MM, pucNasMsg );
    }
    else if ((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
          || (LOCATION_UPDATING_INITIATED              == g_MmGlobalInfo.ucState))
    {
        NAS_MM_ProcInterRatReselInLuProcedure();
    }
    else
    {
        if (g_MmGlobalInfo.ucCsSigConnFlg != MM_CS_SIG_CONN_PRESENT)
        {
            g_MmGlobalInfo.bWaitingEstCnf = VOS_FALSE;

            NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);
        }
    }

     /* W重选/CCO到G后，CS连接肯定不存在，需要上层主动释放 */
    if (((MMC_SUSPEND_CAUSE_CELLCHANGE   == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
      || (MMC_SUSPEND_CAUSE_CELLRESELECT == g_MmGlobalInfo.stSuspendShare.ucSuspendCause))
     && (MM_CS_SIG_CONN_PRESENT          == g_MmGlobalInfo.ucCsSigConnFlg))
    {
        /* 由于之前连接态可能会收到系统消息，异系统重选后接入层会重新上报系统消息，
        因此之前缓存的系统消息无需再触发LAU，需要清除 */
        g_MmGlobalInfo.ucConnRcvSysFlg = MM_FALSE;
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /*调用MM_RelMsgBuf释放缓存消息*/
        MM_RelMsgBuf();

        Mm_RcvRrmmRelInd();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcResumeIndBackToGU
 功能描述  : 处理异系统回到GU后收到resume ind消息的处理
 输入参数  : pstResumeMsg--MMC转发过来的resume ind消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年10月12日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年2月19日
   作    者   : s00217060
   修改内容   : coverity清理
 3.日    期   : 2014年4月08日
   作    者   : y00245242
   修改内容   : warning清理
 4.日    期   : 2014年12月13日
   作    者   : s00217060
   修改内容   : 服务状态显示优化PhaseI 异系统切换流程修改
 5.日    期   : 2015年8月13日
   作    者   : l00289540
   修改内容   : User_Exp_Improve修改
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndBackToGU(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8  enCsfbStatus;
#endif
    /* Modified by s00217060 for coverity清理, 2014-02-19, begin */
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT8                               ucSrvccFlg;
#endif
    /* Modified by s00217060 for coverity清理, 2014-02-19, end */
    /* W异系统到GSM后需清除联合注册建链失败次数 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;
    }

    /* 异系统切换，当前处在建链请求状态，模拟发EST_CNF(fail)清除建链请求 */
    if (NAS_MML_GetCurrNetRatType() != g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        NAS_MM_ProcResumeIndInterRatChangedToGU(pstResumeMsg);
    }

#if (FEATURE_ON == FEATURE_IMS)
    ucSrvccFlg      = NAS_MM_GetSrvccFlg();

    if (VOS_TRUE == ucSrvccFlg)
    {
        NAS_MM_ProcResumeIndBackToGU_Srvcc();
    }
#endif

#if (FEATURE_ON == FEATURE_LTE)
    enCsfbStatus    = NAS_MML_GetCsfbServiceStatus();

    if (NAS_MML_NET_RAT_TYPE_LTE == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        /* Modified by s00217060 for coverity清理, 2014-02-19, begin */
        if ( (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
          && (NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST != enCsfbStatus) )
        /* Modified by s00217060 for coverity清理, 2014-02-19, end */
        {
            NAS_MM_ResumeBackToGU_CSFB((MMCMM_RESUME_IND_STRU*)pstResumeMsg, enCsfbStatus);
        }

        /* 非SRVCC流程,LTE切换到GU后需要回退CS的安全上下文,保证RRC收到resume rsp获取CK/IK的正确性 */
        if ((MMC_SUSPEND_CAUSE_HANDOVER == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
#if (FEATURE_ON == FEATURE_IMS)
         && (VOS_FALSE                  == ucSrvccFlg)
#endif
            )
        {
            NAS_MML_SetSimCsSecurity(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo));
        }
    }
#endif

    /* GU之间的切换也要启定时器等系统消息，定时器超时之后，MMC构造系统消息通知MMA,并通知MMA服务状态 */
    /* GU之间的切换区分不出来是否为紧急呼了，统一用LTE下HO到GU的定时器时长，时长NV可配置 */
    if (VOS_TRUE == NAS_MM_IsHoBetweenGU(g_MmGlobalInfo.stSuspendShare.enOldNetType,
                                          NAS_MML_GetCurrNetRatType(),
                                          g_MmGlobalInfo.stSuspendShare.ucSuspendCause))
    {
        NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_CS_HO_WAIT_SYSINFO);
    }

    return;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 函 数 名  : NAS_MM_ProcSrvccSuccess
 功能描述  : SRVCC成功的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年10月12日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年01月10日
   作    者   : w00176964
   修改内容   : VoLTE_PhaseIII项目
 3.日    期   : 2014年05月30日
   作    者   : s00217060
   修改内容   : ultra flash csfb时不需要通知cc模块srvcc成功

 4.日    期   : 2014年12月16日
   作    者   : w00167002
   修改内容   : DTS2014120200900:在SRVCC后，对端发DISC，携带的TI异常，为8，认为当前
                还是主叫，CC通知TI 不合法后，通知MM REL, 后在ACTIVE状态收到REL处理，
                状态迁移到了MM NULL,需要设置释放后的原因值。
 5.日    期   : 2015年11月11日
   作    者   : c00318887
   修改内容   : DTS2015110909408 IMS电话接通从L handover 到W，电话结束没做LAU
****************************************************************************/
VOS_VOID NAS_MM_ProcSrvccSuccess(VOS_VOID)
{
    /* 3GPP.24008 协议中关于SRVCC过程中MM的处理:
    An MM connection can be established locally in the MS due to an SRVCC handover (see 3GPP TS 23.216 [126]), i.e.
    without dedicated MM signalling. That is the case when the MS has a voice media stream carried over the PS domain
    that is handed over to the CS domain in A/Gb mode or Iu mode via SRVCC.
    An MS in MM state MM IDLE shall establish the MM connection locally when it receives an indication from lower
    layers that a SRVCC handover was completed successfully.
    After completing MM connection establishment, MM layer shall indicate "MM connection establishment due to
    SRVCC handover" to upper layer and shall enter state MM CONNECTION ACTIVE. */

    if (VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* 通知CC模块SRVCC的成功结果 */
        NAS_MM_SndCcSrvccStatusInd(NAS_MMCC_SRVCC_STATUS_SUCCESS);

        /* 通过新增消息ID_MM_LMM_SRVCC_STATUS_NOTIFY通知LMM当前SRVCC 成功 */
        NAS_MM_SndLmmSrvccStatusNotify(NAS_MMCC_SRVCC_STATUS_SUCCESS);

        /* CS HO时(包括SRVCC)启动等系统消息的定时器，如果接入层不报系统消息，定时器超时后MMC构造系统消息让MMA感知接入技术变化 */
        NAS_MM_StartHoWaitSysInfoTimer(MM_TIMER_CS_HO_WAIT_SYSINFO);
    }

    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

    /* 记录当前MM的流程标记以及建链请求时MM的状态 */
    Mm_ComSaveProcAndCauseVal(MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);
    g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucSuspendPreState;


    /* 在SRVCC后，在ACTIVE状态收到REL处理，状态迁移到了MM NULL,需要设置释放后的原因值 */
    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;

    /* 迁移状态到MM CONNECTION ACTIVE */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);

    /* 设置RRC连接存在 */
    NAS_MML_SetRrcConnStatusFlg(VOS_TRUE);

    /* 设置MM信令连接存在 */
    NAS_MML_SetCsSigConnStatusFlg(VOS_TRUE);
    g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;

    /* 通知GMM和MMC当前CS信令连接存在 */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ESTED);

    /* 通知MMC当前CS业务已经建立 */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

    /* 更新CS业务连接状态 */
    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    /* 3GPP 24007 11.2.3.2.3.2 The  sequenced message transfer operation is initiated by establishing
    a RR connection.The send state variables V(SD) are set to 0.After successful completion of SRVCC
    handover (see 3GPP TS 23.216 [27]), the mobile station shall set the send state variable V(SD) to 0.*/
    g_stMmNsd.ucNsd = MM_NSD_INITAL_VALUE;

    /* 写卡文件 */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKC_ID);               /* 更新SIM卡更新状态                        */
    }
    else
    {
        Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYS_ID);            /* 更新SIM卡更新状态                        */
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcSrvccFail
 功能描述  : SRVCC失败的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年10月12日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2014年05月30日
   作    者   : s00217060
   修改内容   : ultra flash csfb时不需要通知cc模块srvcc成功
****************************************************************************/
VOS_VOID NAS_MM_ProcSrvccFail(VOS_VOID)
{
    /* 回退CS的安全上下文 */
    NAS_MML_SetSimCsSecurity(&(g_MmGlobalInfo.stBackupShare.stCsSimSecuInfo));

    if (VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
    {
        /* 清除同步过来的TI信息 */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = MM_CONST_NUM_0;

        /* 通知CC模块SRVCC的失败结果 */
        NAS_MM_SndCcSrvccStatusInd(NAS_MMCC_SRVCC_STATUS_FAIL);

#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_SrvccFailRecord(NAS_ERR_LOG_SRVCC_FAIL_RESUME_IND_BACK_TO_LTE);
#endif
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcSrvccNoCallNum
 功能描述  : SRVCC携带CALLNUM为0的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2015年10月10日
   作    者   : f00179208
   修改内容   : 新生成函数
****************************************************************************/
VOS_VOID NAS_MM_ProcSrvccNoCallNum(VOS_VOID)
{
    /* 释放RRC链接 */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucState;
    Mm_TimerStart(MM_TIMER_T3240);

    /* MM状态迁移 */
    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);

    /* 通知CC模块SRVCC的失败结果 */
    NAS_MM_SndCcSrvccStatusInd(NAS_MMCC_SRVCC_STATUS_FAIL);

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MM_SrvccFailRecord(NAS_ERR_LOG_SRVCC_FAIL_NO_CALL_NUM);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcResumeIndBackToGU_Srvcc
 功能描述  : SRVCC流程下收到resume ind切到GU下的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年9月24日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2015年10月10日
   作    者   : f00179208
   修改内容   : DTS2015100907818:BSRVCC的场景，IMSA不给TAF同步CALLINFO信息，导致MM/TAF层状态异常，
                如果IMSA不同步CALLINFO信息，则以SRVCC失败处理，释放RRC连接
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndBackToGU_Srvcc(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucRcvSrvccCallInfoFlg;

    ucRcvSrvccCallInfoFlg               = NAS_MM_GetRcvSrvccCallInfoFlg();
#endif

    /* 清除SRVCC过程标记 */
    NAS_MM_SetSrvccFlg(VOS_FALSE);

#if (FEATURE_ON == FEATURE_LTE)
    /* 挂起前接入技术为LTE,挂起后为GU,说明SRVCC成功 */
    if (NAS_MML_NET_RAT_TYPE_LTE == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
#if 0
        /* 如果MM未收到CC的同步TI信息,这个时序上有问题,认为异常,当做SRVCC失败处理 */
        if (MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
        {
            NAS_MM_ProcSrvccFail();

            return;
        }
#endif
        /* 清除SRVCC过程收到CALLINFO的标识 */
        NAS_MM_SetRcvSrvccCallInfoFlg(VOS_FALSE);

        /* 如果收到CC同步过来的CALLINFO且CALLNUM为0 */
        if ((VOS_TRUE       == ucRcvSrvccCallInfoFlg)
         && (MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0])
         && (MM_CONST_NUM_0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]))
        {
            NAS_MM_ProcSrvccNoCallNum();

            return;
        }

        NAS_MM_ProcSrvccSuccess();
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MM_ProcResumeIndBackToLTE_Srvcc
 功能描述  : SRVCC流程下收到resume ind切到LTE下的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
 1.日    期   : 2013年9月24日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_MM_ProcResumeIndBackToLTE_Srvcc(VOS_VOID)
{
    /* 清除SRVCC过程标记 */
    NAS_MM_SetSrvccFlg(VOS_FALSE);

    /* 挂起后的RAT与原始RAT不变(或者同步过来的MM的TI FLAG为0,认为未收到CC同步TI的消息,异常
       场景),当做L到GU的SRVCC失败,恢复CS安全上下文 */
    if (NAS_MML_NET_RAT_TYPE_LTE == g_MmGlobalInfo.stSuspendShare.enOldNetType)
    {
        NAS_MM_ProcSrvccFail();
    }

    return;
}

#endif
#endif
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-9-24, end */


/* Added by z00234330 for ISR测试发现问题,dts2013041604521 2013-3-25, begin */
/*****************************************************************************
 函 数 名  : NAS_MM_ChgStateIntoLMode
 功能描述  : 迁移到L模，MM迁移服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月25日
    作    者   : z00234330
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MM_ChgStateIntoLMode( VOS_VOID )
{
    if ( VOS_FALSE == NAS_MML_GetCsSigConnStatusFlg())
    {
        return;
    }

    switch ( g_MmGlobalInfo.ucState )
    {
        case WAIT_FOR_OUTGOING_MM_CONNECTION :
        case MM_CONNECTION_ACTIVE:
        case WAIT_FOR_RR_CONNECTION_MM_CONNECTION:
        case WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ:
        case WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF:
        case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        case PROCESS_CM_SERVICE_PROMPT:
        case TEST_CONTROL_ACTIVE:
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            break;
        case WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING :
        case LOCATION_UPDATING_INITIATED :
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            break;
        case LOCATION_UPDATE_REJECTED :
            Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);
            break;
        case WAIT_FOR_NETWORK_COMMAND :
            if ( MM_MM_CONN_PROC == g_MmGlobalInfo.ucProc )
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }
            else if ( MM_LU_PROC == g_MmGlobalInfo.ucProc )
            {
                Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);
            }
            else
            {
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            }
            break;
        default:
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            break;
    }

}

/* Added by z00234330 for ISR测试发现问题,dts2013041604521 2013-3-25, end */


/*****************************************************************************
 Prototype      : Mm_Cell_S32_E85
 Description    : process after MMCMM_RESUME_IND
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.日    期  : 2006年12月4日
    作    者  : luojian id:60022475
    修改内容  : 问题单号:A32D07777
  3.日    期   : 2007年01月04日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D06408
  4.日    期  : 2008年9月4日
    作    者  : ouyangfei id:00132663
    修改内容  : 问题单号:AT2D05490,重建过程支持异系统切换
  5.日    期   : 2009年03月19日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D09743/AT2D10328,WAS的 D/F/P态下丢网处理
  6.日    期   : 2009年9月18日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D14551,网络模式II下,从2G通过PCCO过程到3G后,在W下发起的RRC连接请求原因值不符合协议要求
  7.日    期   : 2010年05月14日
    作    者   : l65478
    修改内容   : 问题单号:AT2D19292,MM在寻呼建立连接时，收到系统信息，把状态迁到NORMAL状态，导致GCF失败
  8.日    期   : 2010年09月27日
    作    者   : z00161729
    修改内容   : 问题单号AT2D19560:W重定向到G小特性NAS修改合入,异系统切换，当前处在建链请求状态，模拟发EST_CNF(fail)清除建链请求
  9.日    期   : 2011年3月3日
    作    者   : z00161729
    修改内容   : DTS2011021201997:PS、CS完整性保护是否开启由GMM和MM分开维护,MMC不再维护
 10.日    期   : 2011年7月12日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，用于恢复CCO流程中的MM全局变量,替换g_MmSubLyrShare.MmSuspendShare的全局变量
 11.日    期   : 2011年07月15日
    作    者   : l65478
    修改内容   : 问题单号：DTS2011071101580, 系统间重选挂起失败
 12.日    期   : 2011年12月25日
    作    者   : l65478
    修改内容   : 问题单号：DTS2011122307328, 注册过程中重选，导致MMC挂死
 13.日    期   : 2011年12月1日
    作    者   : w00176964
    修改内容   : V7R1 PhaseIV 调整:RRC链接维护调整
 14.日    期   : 2012年03月08日
    作    者   : l00130025
    修改内容   : DTS2012030107830: G->W Est_Rej_Cogest,CCO回退过程，T3211没有停止，导致错误发起LAU,LAU Type错误
 15.日    期   : 2012年04月24日
    作    者   : w00166186
    修改内容   : DTS2012042303735，从L CCO到G后再重选会L，第一次TAU失败
 16. 日    期   : 2012年2月14日
     作    者   : z00161729
     修改内容   : V7R1C50 支持CSFB特性修改
 17.日    期   : 2012年04月11日
    作    者   : z00161729
    修改内容  : csfb mt L重定向到W失败回退到L，再csfb mt失败
 16.日    期   : 2012年05月21日
    作    者   :  z40661
    修改内容  :  DTS2012052308001:从L重选到G后反复进行LAU
 17.日    期   : 2012年06月13日
    作    者   : s46746
    修改内容   : For CS/PS mode 1，CS存在信令连接重选到L后，没有清除GMM的CS连接标志
 18.日    期   : 2012年10月22日
    作    者   : t00212959
    修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
 19.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 20.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011082402748:EST CNF fail导致CCO回退时,3211不需要恢复启动
 21.日    期   : 2013年3月25日
    作    者   : z00234330
    修改内容   : ISR测试发现问题,W链接态到L模，关机时，MM会通知WRR发送detach
 22.日    期   :2013年8月13日
    作    者   :z00161729
    修改内容   :DTS2013081207431:mm挂起状态收到cc的t303超时abort消息，需要缓存，收到resume ind时再处理
 22.日    期   :2013年9月23日
    作    者   :w00242748
    修改内容   :DTS2013091407626:W下UE被叫，未收到网侧建联CNF前，发生重定向到G后，未发起LAU
 23.日    期   :2013年10月18日
    作    者   :z00161729
    修改内容   :DTS2013101900866:mm在wait for mm connection状态收到gas丢网消息没有给cc回复rel ind导致呼叫T303超时呼叫失败
 24.日    期   : 2013年9月22日
    作    者   : w00176964
    修改内容   : Volte_phaseII 项目:增加SRVCC流程处理并重新整理该函数
 25.日    期   : 2014年1月27日
    作    者   : s00246516
    修改内容   : L-C互操作项目:增加异系统到HRPD的处理
 26.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_E85( VOS_VOID* pMsg )
{
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    MMCMM_RESUME_IND_STRU              *pstResumeIndMsg = VOS_NULL_PTR;
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

    NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,  "MM leave SUSPEND state");

    /* 恢复MM模块的状态以及定时器相关信息 */
    NAS_MM_ResumeSuspendInfo((MMCMM_RESUME_IND_STRU*)pMsg);

    /* MM向mmc发送resume rsp */
    NAS_MM_SndMmcResumeRsp();

    /* Added by s00246516 for L-C互操作项目, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    pstResumeIndMsg = (MMCMM_RESUME_IND_STRU*)pMsg;

    /* 异系统变换到EHRPD下的处理 */
    if ( MMC_RESUME_ORIGEN_HRPD == pstResumeIndMsg->ucResumeOrigen )
    {
        NAS_MM_ProcResumeToHRPD(pstResumeIndMsg);

        return;
    }
#endif
    /* Added by s00246516 for L-C互操作项目, 2014-01-27, End */

#if (FEATURE_ON == FEATURE_LTE)
    /* 异系统变换到LTE下的处理 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
       NAS_MM_ProcResumeIndBackToLTE((MMCMM_RESUME_IND_STRU*)pMsg);

       return;
    }
#endif

    /* 异系统变换到GU下的处理 */
    NAS_MM_ProcResumeIndBackToGU((MMCMM_RESUME_IND_STRU*)pMsg);

    /* 调用函数 MM_SndMsgFuncChg 切换向接入层发送消息的函数 */
    MM_SndMsgFuncChg();

    switch ( g_MmGlobalInfo.stSuspendShare.ucSuspendCause )
    {
        case MMC_SUSPEND_CAUSE_HANDOVER :
        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            if ( MM_RESUME_RESULT_FAILURE == (((MMCMM_RESUME_IND_STRU*)pMsg)->ucCsResumeResult) )
            {
                NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_NORMAL,"MM:HANDOVER Resume Failure.");

                /* 调用 MM_RelMsgBuf 释放缓存消息 */
                MM_RelMsgBuf();

                Mm_RcvRrmmRelInd();
            }
            else
            {
                NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_NORMAL,"Resume Success");

                /* 挂起前没有发送成功的消息重新发送 */
                MM_RetransferMsg();
                /* 调用函数 MM_Restore 处理缓存队列消息 */
                MM_Restore();
            }
            break;

        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            if ( MM_RESUME_RESULT_SUCCESS != (((MMCMM_RESUME_IND_STRU*)pMsg)->ucCsResumeResult) )
            {
                /* add by z40661 for AT2D12429,MMCMM_RESUME_IND失败, 如果当前有CS业务需要通知 */
                /* 停止保护定时器 */
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                /* 调用 MM_RelMsgBuf 释放缓存消息 */
                MM_RelMsgBuf();

                Mm_RcvRrmmRelInd();

               Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL);
            }
            else
            {
                /* 调用函数 MM_Restore 处理缓存队列消息 */
                MM_Restore();
            }

            break;

        default:
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_WARNING,"SUSPEND cause is error");
            break;
    }

    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_TimerExpire
 Description    : process after timer expire
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
*****************************************************************************/
VOS_VOID Mm_Cell_S32_TimerExpire( VOS_VOID* pMsg )
{
    /* 消息头结构，用于判断消息类型 */
    MSG_HEADER_STRU                    *pMsgHeader;

    /* 提取消息头 */
    pMsgHeader                          = (MSG_HEADER_STRU* )pMsg;

    /* 判断消息类型，并分别处理 */
    MM_SaveMsg(pMsg, g_MmSubLyrShare.MmShare.MmSuspendEvent, pMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    return;

}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_DataTransfer
 Description    : process after data req at SUSPEND state
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
*****************************************************************************/
VOS_VOID Mm_Cell_S32_DataTransfer( VOS_VOID* pMsg )
{
    /* 消息头结构，用于判断消息类型 */
    MSG_HEADER_STRU                    *pMsgHeader;

    /* 提取消息头 */
    pMsgHeader                          = (MSG_HEADER_STRU* )pMsg;

    /* 调用函数 MM_SaveMsg 进行处理 */
    MM_SaveMsg(pMsg, g_MmSubLyrShare.MmShare.MmSuspendEvent, pMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_CCEstREQ
 Description    : process after CC est req  at SUSPEND state
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  3.日    期   : 2013年8月17日
    作    者   : z00161729
    修改内容  : DTS2013062406563:EMO的卡在OOS时没有驻留到SBM的网络
  4.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_CCEstREQ( VOS_VOID* pMsg )
{
    /* MM refuse the est req of CC */
    if ( MM_FALSE == Mm_RcvCcEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /*WUEPS_ASSERT(0);
 */
    }
    else
    {
        if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == g_MmGlobalInfo.stSuspendShare.ucSuspendCause)
         && (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType))
        {
            /* oos流程比较长如果是紧急呼叫需要打断oos流程 */
            /*缓存该服务请求 */
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }
        else
        {
           Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
        }

    }
    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_SMSEstREQ
 Description    : process after SMS est req  at SUSPEND state
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  3.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_SMSEstREQ( VOS_VOID* pMsg )
{
    /* MM refuse the est req of SMS */
    if ( MM_FALSE == Mm_RcvSmsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /*WUEPS_ASSERT(0);
 */
    }
    else
    {
        Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
    }
    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_SSEstREQ
 Description    : process after SS est req  at SUSPEND state
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-05-05
    Author      : x51137
    Modification: Created function
  2.日    期   : 2007年07月31日
    作    者   : luojian id:60022475
    修改内容   : 问题单号:A32D12640
  3.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  4.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  5.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_SSEstREQ( VOS_VOID* pMsg )
{
    /* MM refuse the est req of SS */
    if ( MM_FALSE == Mm_RcvSsEstReq(pMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /*WUEPS_ASSERT(0);
 */
    }
    else
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
    }
    return;
}

/*****************************************************************************
 Prototype      : Mm_Cell_S32_E23
 Description    : process MMC_MM_POWER_OFF
 Input          :
 Output         :
 Return Value   : 无
 Calls          :
 Called By      :

 History        : ---
 1.Date        : 2006-05-05
   Author      : x51137
   Modification: Created function
 2.日    期   : 2006年9月9日
   作    者   : sunxibo id:46746
   修改内容   : 根据问题单号：A32D05803
 3.日    期   : 2011年7月25日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 4.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : DTS2012083102536:支持cc呼叫重建
 5.日    期   : 2013年05月15日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 6.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_E23( VOS_VOID* pMsg )
{
    if ( MM_FALSE == Mm_RcvMmcPowerOffReq(pMsg) )
    {
        return;
    }

    /* 停止缓存队列保护定时器 */
    if ( MM_TIMER_START == gstMmTimerSuspend.ucTimerStatus )
    {
        if (VOS_OK != Mm_StopRelTimer(WUEPS_PID_MM, MM_TIMER_PROTECT_SUSPEND, &(gstMmTimerSuspend.stTimer)))
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_ERROR,"Stop MM_TIMER_PROTECT_SUSPEND fail.");
        }
        else
        {
            NAS_LOG(WUEPS_PID_MM, MM_SUSPEND, PS_LOG_LEVEL_INFO,"Stop MM_TIMER_PROTECT_SUSPEND success.");
        }
    }

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

    MM_RelMsgBuf();

    Mm_TimerStop(MM_TIMER_STOP_ALL);

    g_MmGlobalInfo.ucDetachType = MM_DETACH_CS_POWEROFF;

    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    Mm_ComNasInfoSav(
                     MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    Mm_SndMmcPowerOffCnf();


    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);
    }

    Mm_ComSetMmState(MM_STATE_NULL);

}

/*****************************************************************************
 函 数 名  : Mm_Cell_S32_E22
 功能描述  : MM在挂起状态收到detach消息的处理
 输入参数  : VOS_VOID* pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年1月9日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年05月15日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

*****************************************************************************/
VOS_VOID Mm_Cell_S32_E22( VOS_VOID* pMsg )
{
    MMCMM_DETACH_REQ_STRU*          pMmcDetachReq;

    if (MM_FALSE == Mm_RcvMmcDetachReq(pMsg))
    {
        return;
    }

    pMmcDetachReq = (MMCMM_DETACH_REQ_STRU*)pMsg;

    if (MMC_MM_PS_DETACH != pMmcDetachReq->enDetachType)
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

        /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MM_DETACHED);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        /* 备份全局变量在CS域进行本地detach后需要进行删除 */
        if ( ( MMC_SUSPEND_CAUSE_CELLCHANGE == g_MmGlobalInfo.stSuspendShare.ucSuspendCause )
          && ( MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucSuspendPreState ) )
        {
            NAS_MM_InitCcoFallbackCtx();
        }

        /* 由于mm迁移了状态,3212在挂起状态未停止,此时需要停止 */
        Mm_TimerStop(MM_TIMER_T3212);


        if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucSuspendPreState)
        {
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;
            g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_NO_IMSI;
            g_MmGlobalInfo.ucPreState = MM_IDLE_NO_IMSI;

        }
        else
        {
            g_MmGlobalInfo.ucSuspendPreState = MM_IDLE_LIMITED_SERVICE;
            g_MmGlobalInfo.ucPreState = MM_IDLE_LIMITED_SERVICE;
            g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;

        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        g_MmGlobalInfo.stBackupShare.ucState                    = g_MmGlobalInfo.ucSuspendPreState;

        g_MmGlobalInfo.stBackupShare.ucPreState                 = g_MmGlobalInfo.ucSuspendPreState;

        g_MmGlobalInfo.stBackupShare.enMmServiceState           = g_MmGlobalInfo.ucMmServiceState;
    }
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
