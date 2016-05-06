/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_CellProc.c
  Description  : MM状态迁移表对应CELL处理
  Function List:
History:
      1.  s46746    2006-04-14  根据问题单A32D03088修改
      2.  s46746    2006-04-17  根据问题单A32D02829修改
      3.  s46746  2006-06-24  根据问题单A32D04439修改
      4.  s46746  2006-07-25  根据问题单A32D05058修改
      5. s46746  2006-07-27 根据问题单A32D03975修改
      6. 日    期   : 2006年10月8日
         作    者   : luojian id:60022475
         修改内容   : OSA优化过程中遗漏了A32D05845问题单的修改,现补上
                      问题单号:A32D06583
      7.日    期   : 2006年10月6日
        作    者   : s46746
        修改内容   : 问题单号：A32D05960
      8.x51137 2006/11/3 A32D06511
      8.x51137 2006/11/3 A32D06821
      9.日    期   : 2006年11月25日
        作    者   : s46746
        修改内容   : 问题单号：A32D07666
     10.日    期   : 2007年03月09日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单A32D09099修改
     11.日    期   : 2007年04月20日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号：A32D10235
     12.日    期   : 2007年07月31日
        作    者   : s46746
        修改内容   : 问题单号:A32D12629,在此期间可能发起频率重定义，
                     时间为50秒，因此增加定时器长度
     13.日    期   : 2007年09月05日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号：AT2D01490,MM收到系统消息需要判断LAI是否
                     发生改变来决定是否停T3211
     14.日    期   : 2007年9月29日
        作    者   : luojian id:107747
        修改内容   : 根据问题单号：A32D12966,增加部分状态对RRMM_REL_IND的处理
     15.日    期   : 2007年10月06日
        作    者   : l65478
        修改内容   : 根据问题单号：A32D12977
     16.日    期   : 2007年11月20日
        作    者   : s46746
        修改内容   : 根据问题单号：A32D13510,在搜网状态指示接入层P/TMSI
     17.日    期   : 2007年12月11日
        作    者   : s46746
        修改内容   : 根据问题单号：A32D13845,出服务区后，MMC立即启动异系统相同PLMN
                     搜索
     18.日    期   : 2007年12月29日
        作    者   : l0010747
        修改内容   : 问题单号:A32D13958,部分状态下对RRMM_REL_IND处理修改
     19.日    期   : 2008年5月27日
        作    者   : s46746
        修改内容   : 问题单号:AT2D03209,增加列表搜索时响应寻呼处理
     20.日    期   : 2008年8月20日
        作    者   : s46746
        修改内容   : 问题单号:AT2D05154,呼叫重建过程中位置区改变，不能通知GMM连接不存在
     21.日    期   : 2008年8月21日
        作    者   : o00132663
        修改内容   : 问题单号:AT2D04652,当小区改变时，停止定时器 T3211
     22.日    期   : 2008年8月22日
        作    者   : o00132663
        修改内容   : 问题单号:AT2D05087,增加函数 Mm_Cell_S4_E31
     23.日    期   : 2008年8月23日
        作    者   : l00130025
        修改内容   : 问题单号:At2D05016,MM注册状态修改
     24.日    期   : 2008年8月25日
        作    者   : o00132663
        修改内容   : 问题单号:AT2D05268,在函数 Mm_Cell_S14_E32中，删除发送MMCC_REEST_CNF(ESTING)的相关代码
     25.日    期   : 2008年8月26日
        作    者   : o00132663
        修改内容   : 问题单号:AT2D05317,MM连接管理增强
     26.日    期   : 2008年09月03日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05403,mm状态修改
     27.日    期   : 2008年10月08日
        作    者   : o00132663
        修改内容   : 问题单号：AT2D06064,如果手机已经发起了detach,那么即使收到了IMSI Paging，也不响应寻呼。
     28.日    期   : 2008年11月22日
        作    者   : o00132663
        修改内容   : 问题单号：AT2D06931, 清除标志位ucT3212ExpiredFlg
     29.日    期   : 2008年12月1日
        作    者   : o00132663
        修改内容   : AT2D07041, 在用户发起的LIST搜网，或者HPLMN搜网时，CREG,CGREG暂停上报。
     30.日    期   : 2009年02月28日
        作    者   : o00132663
        修改内容   : AT2D09507, 在丢网时，CREG,CGREG上报2:没有注册，但MT正在搜寻要注册的新的运营商。
     31.日    期   : 2009年04月29日
        作    者   : x00115505
        修改内容   : AT2D11365,2G下MM建立信令链接保护定时器的长度过长，从190s修改为15s。
     32.日    期   : 2009年05月11日
        作    者   : h44270
        修改内容   : AT2D11661/AT2D11804,发起手动搜网打断LAU过程，导致搜网成功后发起两次LAU
     33.日    期   : 2009年07月24日
        作    者   : z40661
        修改内容   : 异系统重选后，紧急呼叫不能接通
     34.日    期   : 2009年07月31日
        作    者   : x00115505
        修改内容   : AT2D13428,2G下联合注册后，去注册PS域，之后发起语音呼叫，网络回复Cm Service Reject（#4），呼叫失败。
     35.日    期   : 2009年9月7日
        作    者   : s46746
        修改内容   : 根据问题单号：AT2D14311，出服务区后，GMM存在连接时先进行了连接释放，会导致服务状态临时更新为Normal service
     36.日    期   : 2009年09月28日
        作    者   : x00115505
        修改内容   : 设置单板仅支持PS域，发送CS短信后接收不到
     37.日    期   : 2009年11月26日
        作    者   : x00115505
        修改内容   : 设置服务域为PS ONLY，群发短信，仅第一条成功
     38.日    期   : 2010年04月21日
        作    者   : x00115505
        修改内容   : 问题单号:AT2D17739,单板特定场景下闪灯与要求不一致
     39.日    期   : 2010年11月30日
        作    者   : h44270
        修改内容   : 问题单号：DTS2010112905048/DTS201011270072,CS域IMSI无效时，没有向MMC回复消息收到消息
*******************************************************************************/
#include        "MM_Inc.h"
#include        "NasCommDef.h"
#include        "GmmMmInterface.h"
#include        "NasMmcProcNvim.h"
#include        "MM_Ext.h"

#include        "NasMmSndOm.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-10, begin */
#include        "NasMmEcall.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-10, end */
#include        "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC1_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/*****************************************************************************
 函 数 名  : NAS_MM_StoreCsUnavailableInfo
 功能描述  : CS域不可用信息存储
 输入参数  : VOS_UINT8   ucCause            RAU或LAU被网络拒绝的原因值
 输出参数  : NAS_MNTN_CS_UNAVAILABLE_INFO_STRU  *pstCsUnavailableInfo
                                            CS域不可用信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年9月16日
    作    者   : 傅映君/f62575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_StoreCsUnavailableInfo(
    VOS_UINT16                          usCause,
    NAS_MNTN_CS_UNAVAILABLE_INFO_STRU  *pstCsUnavailableInfo
)
{
    VOS_UINT32                          ulPos;

    /* 事件记录标志设置一: 尝试次数达上限 */
    if (NAS_MNTN_CS_ATTEMPT_MAX == pstCsUnavailableInfo->ucTimes)
    {
        pstCsUnavailableInfo->bRecordRequired = VOS_TRUE;
    }

    /* 事件记录标志设置二: 注册失败原因值指示当前驻留位无法提供服务，重选后再尝试注册 */
    NAS_MNTN_ServiceUnavailableType(usCause, &pstCsUnavailableInfo->bRecordRequired);

    /* 异常数据直接退出一: 注册失败原因值没有指示当前驻留位无法提供服务，
       且注册失败计数器值为0 */
    if ((VOS_TRUE != pstCsUnavailableInfo->bRecordRequired)
     && (0 == g_MmGlobalInfo.LuInfo.ucLuAttmptCnt))
    {
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_StoreCsUnavailableInfo: Error Counter.");
        return;
    }

    /* 异常数据直接退出二: 注册失败计数器值超过最大值 */
    if (g_MmGlobalInfo.LuInfo.ucLuAttmptCnt > NAS_MNTN_CS_ATTEMPT_MAX)
    {
        return;
    }

    /* 记录注册失败原因值到全局变量 */
    if (0 != g_MmGlobalInfo.LuInfo.ucLuAttmptCnt)
    {
        ulPos = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt - 1;

    }
    else
    {
        ulPos = 0;
    }

    pstCsUnavailableInfo->aulCause[ulPos]= usCause;
    pstCsUnavailableInfo->ucTimes = g_MmGlobalInfo.LuInfo.ucLuAttmptCnt;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_MM_RcvCcEstReq_CSFB
 功能描述  : 驻留L下CC MO CSFB的处理
 输入参数  : 无
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
 3.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
 4.日    期   : 2013年11月14日
   作    者   : z00161729
   修改内容   : DTS2013111308141:cc csfb L建链过程中，mm在idle normal service未迁到interrat change之前发起ss业务失败未启动重发定时器，mm rel ind释放原因值不应为other cause
 5.日    期   : 2014年6月13日
   作    者   : w00242748
   修改内容   : DSDS 新特性
 6.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log

*****************************************************************************/
VOS_VOID NAS_MM_RcvCcEstReq_CSFB(VOS_VOID)
{
    VOS_UINT32                          ulCsfbExistFlg;
    ulCsfbExistFlg = NAS_MML_IsCsfbServiceStatusExist();

    if ((MM_CONST_NUM_8  > g_MmCcEstReq.ulTransactionId)
     || (MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId)
     || (VOS_TRUE == ulCsfbExistFlg))
    {
        if (VOS_TRUE == ulCsfbExistFlg)
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS);
        }
        else
        {
            /* ti非法，回复NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }

        /* Mm_RcvCcEstReq函数判断如果是紧急呼设置了ucEstingCallTypeFlg，需要清除 */
        if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg = MM_FALSE;
            NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
        }

        return;
    }

    /* 缓存建立请求 */
    NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

    /* 更新CSFB状态 */
    if (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST);

        /* 记录CSFB业务建立开始 */
        NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_EMC_CALL_SETUP_START);
    }
    else
    {
        NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST);

        NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST);

        /* 记录CSFB业务建立开始 */
        NAS_MML_SetMoCallStatus(NAS_MML_CSFB_MO_NORMAL_CALL_SETUP_START);
    }

    /* 向L发送CSFB流程开始请求,CSFB是否可以发起的判断由LMM负责，如果不允许发起,
       L会回复LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    return;

}

/*****************************************************************************
 函 数 名  : NAS_MM_RcvSsEstReq_CSFB
 功能描述  : 驻留L下SS MO CSFB的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月14日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   :2013年9月14日
   作    者   :z00161729
   修改内容   :DTS2013082903019:支持ss重发功能
 3.日    期   : 2013年11月14日
   作    者   : z00161729
   修改内容   : DTS2013111308141:cc csfb L建链过程中，mm在idle normal service未迁到interrat change之前发起ss业务失败未启动重发定时器，mm rel ind释放原因值不应为other cause
 4.日    期   : 2014年6月13日
   作    者   : w00242748
   修改内容   : DSDS 新特性
 5.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log

*****************************************************************************/
VOS_VOID NAS_MM_RcvSsEstReq_CSFB(VOS_VOID)
{
    /* 已经在CSFB流程，如已在主被叫CSFB，无需响应，回复SS建立失败 */
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CSFB_ALREADY_EXISTS);

        return;
    }

    if ((MM_CONST_NUM_8 > g_MmSsEstReq.ulTi)
     || (MM_CONST_NUM_14 < g_MmSsEstReq.ulTi))
    {                                                                       /* TI不合法 */
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);

        return;
    }

    /* 缓存建立请求 */
    NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SS);

    NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST);

    /* 更新CSFB状态 */
    NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST);

    /* 向L发送CSFB流程开始请求,CSFB是否可以发起的判断由LMM负责，如果不允许发起,
       L会回复LMM_MM_CSFB_SERVICE_END_IND */
    NAS_MM_SndLmmCsfbServiceStartNotify();

    NAS_MML_SetMoSsStatus(NAS_MML_CSFB_MO_SS_SETUP_START);

    return;

}
#endif
/*******************************************************************************
  MODULE   : Mm_Cell_S3_E24
  FUNCTION : 在MM IDLE NORMAL SERVICE状态下收到MMCC_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-09  新版作成
     2.  张志勇        2005.01.27  007037 for MM
     3.  日    期   : 2009年05月25日
         作    者   : l65478
         修改内容   : 问题单:AT2D10870,在MM连接建立过程中发生LAI改变,没有发起LU,导致呼叫失败
     4.  日    期   : 2011年10月27日
         作    者   : s46746
         修改内容   : V7R1 PhaseIII,支持L模联合注册
     5.  日    期   : 2012年2月14日
         作    者   : z00161729
         修改内容   : V7R1C50 支持CSFB特性修改
     6.  日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
     7. 日    期    : 2012年10月29日
        作    者    : z00161729
        修改内容    : DTS2012083102536:支持cc呼叫重建
     8. 日    期    : 2012年12月11日
        作    者    : w00176964
        修改内容    : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
     9 .日    期   : 2012年12月21日
        作    者   : L00171473
        修改内容   : DTS2012122007141:L单模时收到呼叫请求直接向CC回复失败
    10.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
    11.日    期   :2014年6月27日
       作    者   :s00217060
       修改内容   :K3V3 多模多天线特性
    12.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif


    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* 通知CC建立失败                           */
            return;
        }

        /* 如果当前驻留LTE,则直接回复CC失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvCcEstReq_CSFB();
            return;
        }
#endif

        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);      /* 通知CC建立失败                           */
        }
        else
        {                                                                       /* TI合法                                   */
            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
        }
    }

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, end */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcCcEstReq_IdleLimitedService
 功能描述  : 在MM IDLE LIMITED SERVICE状态下收到MMCC_EST_REQ的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月25日
    作    者   : n00269697
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ProcCcEstReq_IdleLimitedService(VOS_VOID)
{
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
    {                                                                   /* 是紧急呼叫                               */
        NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
    }
    else
    {                                                                   /* 不是紧急呼叫                             */
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        if (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);      /* 通知CC建立失败                           */
        }
        else
        {
            /*状态为NO IMSI或者服务域不为PS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                /* cs only limited service, cs+ps limited service, no imsi时，普通呼叫回cs detach更合适 */
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);                      /* 通知CC建立失败                           */
            }
            else
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }

                /*缓存该服务请求并进行CS注册*/
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

                if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
                 && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
                {
                    NAS_MM_SndGmmRegisterInit();
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();
                }
            }

        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end*/

    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S4_E24
  FUNCTION : 在MM IDLE LIMITED SERVICE状态下收到MMCC_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-09  新版作成
     2.  张志勇        2005.01.27  007037 for MM
     3.日    期   : 2011年03月01日
       作    者   : A00165503
       修改内容   : 问题单号: DTS2011021202242/DTS2011021400322，添加宏开关判断
                    服务域为PS_ONLY时，CS域短信和呼叫业务是否能够发起

     4.日    期   : 2011年8月12日
       作    者   : zhoujun 40661
       修改内容   : MML模块划分，全局变量调整
     5.日    期   : 2011年10月27日
       作    者   : s46746
       修改内容   : V7R1 PhaseIII,支持L模联合注册
     6.日    期   : 2012年03月03日
      作    者   : s62952
      修改内容   : BalongV300R002 Build优化项目:使用NV替换NAS_FEATURE_SUPPORT_H3G_REQ宏
     7.日    期   : 2012年2月15日
       作    者   : w00166186
       修改内容   : CSFB&PPAC&ETWS&ISR 开发
     8.日    期   : 2012年8月14日
       作    者   : z00161729
       修改内容   : DCM定制需求和遗留问题修改
     9.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
   10. 日    期    : 2012年12月11日
       作    者    : w00176964
       修改内容    : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
   11 .日    期   : 2012年12月21日
       作    者   : L00171473
       修改内容   : DTS2012122007141:L单模时收到呼叫请求直接向CC回复失败
   12.日    期   :2013年9月12日
      作    者   :z00161729
      修改内容  :DTS2013082903019:支持ss重发功能
   13.日    期   :2014年9月24日
      作    者   :s00217060
      修改内容   :for cs_err_log

   14.日    期   : 2015年8月27日
      作    者   : w00167002
      修改内容   : DTS2015082401001:放开LIMIT SERVICE场景下得MO CALL。如果到GU下搜网
                   成功，可以提高主叫呼通率。
                   在L下注册失败后，L会通知MMC当前注册假流程，MM会迁移到LIMIT SERVICE.
                   这个时候发起电话，其实是有可能成功的。跟LNAS的lihong交流，当前CSFB
                   都可以发到LNAS处理，由LNAS来判别是否可以执行。
                   如在L下#12，MM进入LIMIT service,后续如果搜网到GU，也是可能成功的。
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;


    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
#endif


    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
           /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        /* 在MM_IDLE_NO_IMSI状态时收到普通呼叫请求直接回复CS_SIM_INVALID,
           其他状态一般是收到系统消息后还未注册时处理缓存,暂时无法提供CS服务，需要重拨 */
        if ( (VOS_FALSE           == NAS_MML_GetSimCsRegStatus())
          && (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);    /* 通知CC建立失败                           */

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)


        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                        /* 通知CC建立失败                           */
            return;
        }

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {

            /* 如果当前PS ONLY时支持CS业务NV未激活，则主叫失败 */
            if ( (NAS_MML_MS_MODE_PS_ONLY  == NAS_MML_GetMsMode())
              && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
              && (MMCC_MO_NORMAL_CALL      == g_MmCcEstReq.ulCallType) )
            {
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                              NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);       /* 通知CC建立失败                           */

                return;
            }

            NAS_MM_RcvCcEstReq_CSFB();

            return;
        }
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
        if (VOS_FALSE == NAS_MM_IsCcTiValid())
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */
        {
            /* TI不合法                                 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);            /* 通知CC建立失败                           */
        }
        else
        {
            NAS_MM_ProcCcEstReq_IdleLimitedService();
        }
    }

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E24
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到MMCC_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      03-12-09  新版作成
  2.日    期   : 2007年10月06日
    作    者   : l65478
    修改内容   : 问题单号：A32D12977
  3.日    期   : 2009年02月21日
    作    者   : l65478
    修改内容   : AT2D09308,在限制服务下，如果是紧急呼叫，直接拒绝
  4.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  7.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  8.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  9.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
  10.日    期   : 2012年12月15日
    作    者   : l65478
    修改内容   : DTS2012120508936:在发起紧急呼叫时需要disable LTE
 11.日    期   : 2012年12月21日
    作    者   : L00171473
    修改内容   : DTS2012122007141:L单模时收到呼叫请求直接向CC回复失败
 12.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
 13.日    期   :2014年2月22日
    作    者   :y00245242
    修改内容   :dts201412901179:CC与SS业务请求同时触发时，对网络的容错处理
 14.日    期   :2014年3月23日
    作    者   :y00245242
    修改内容   :dts2014031406746:处理MT call正在建立过程中，收到MO call冲突处理
                并移dts201412901179到函数Mm_IsMultiSrvCollisionAllow中统一处理
 15.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E24(
                        VOS_VOID            *pRcvMsg                           /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

#endif

    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 非紧急呼，且不再搜网状态，当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType)
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState))
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前为L单模则直接回复CC失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);                              /* 通知CC建立失败                           */
            return;
        }

        /* 如果当前驻留LTE,则直接回复CC失败 */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE);                              /* 通知CC建立失败                           */

            return;
        }
#endif

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-13, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-5-13, end */
        if(VOS_FALSE == NAS_MML_GetSimCsRegStatus())
        {
            if(MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType)
            {
                Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);                          /* 通知CC建立失败                           */

                return;
            }
        }

        if ((MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK);                          /* 通知CC建立失败                           */
            return;
        }

        /* 检查多业务冲突是否允许 */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_CC))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
            return;
        }

        /*缓存该服务请求 */
        NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }
    }
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E24
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMCC_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-09    新版作成
     2.  张志勇          2004.03.12  二期改造
     3.  张志勇      04-03-22    MM_MT_二期_BUG_003
     4.  日    期   : 2011年05月11日
         作    者   : f00179208
         修改内容   : DTS2011042504198:在CS域发短信失败后，由于SMS与MM接口间有问题，无法再PS域重发短信
     5. 日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
     6.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
    7.日    期   : 2012年12月11日
      作    者   : w00176964
      修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
    8.日    期   :2013年9月12日
      作    者   :z00161729
      修改内容  :DTS2013082903019:支持ss重发功能
    9.日    期   : 2014年5月28日
      作    者   : z00234330
      修改内容   : covertity修改
   10.日    期   :2014年9月24日
      作    者   :s00217060
      修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* CM service request结构体                 */
    VOS_UINT8                           ucRst;

    /* modified by z00234330 for coverity修改 2014-05-28 begin */
    PS_MEM_SET(&CmSvcReq,0x00,sizeof(CmSvcReq));
    /* modified by z00234330 for coverity修改 2014-05-28 end */

    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        ucRst = Mm_ComJudgeLimitSvc();
        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            || (MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId)
            || (MM_TRUE == ucRst))
        {                                                                       /* TI不合法或者在受限服务状态               */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                   /* 通知CC建立失败                           */
        }
        /*lint -e701*/
        else if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] &
            (0x01 << (g_MmCcEstReq.ulTransactionId - 8))))
        /*lint +e701*/
        {                                                                       /* 要求建立的MM连接已经存在                 */
        }
        else
        {                                                                       /* TI合法                                   */
            if (MMCC_MO_NORMAL_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* 主叫正常呼叫                             */
                Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_MO_CALL_EST,
                    MM_FALSE, &CmSvcReq);                                       /* 填充CM SERVICE REQUEST结构体             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                    = MM_FALSE;                                                 /* 不是紧急呼叫                             */
                NAS_MML_SetCsEmergencyServiceFlg( VOS_FALSE );
            }
            else if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* 主叫紧急呼叫                             */
                Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_EMG_CALL_EST,
                    MM_FALSE, &CmSvcReq);                                       /* 填充CM SERVICE REQUEST结构体             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucEstingCallTypeFlg
                    = MM_TRUE;                                                  /* 是紧急呼叫                               */
                NAS_MML_SetCsEmergencyServiceFlg( VOS_TRUE );
            }
            else
            {
            }
            Mm_ComMsgCmSvcReqSnd(&CmSvcReq);                                    /* 向网侧发送建立MM连接的请求               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmCcEstReq.ulTransactionId;                                           /* 记录重建MM连接的TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                (VOS_UINT8)g_MmCcEstReq.ulTransactionId;                        /* 记录正在建立的MM连接                     */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_CALL_CONTROL;            /* 记录正在建立的MM连接的PD                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat = NAS_MML_GetCurrNetRatType();
            Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E24:NORMAL: STATUS is  WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }

        /*lint +e701*/
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S11_E24
  FUNCTION : 在WAIT FOR NETWORK COMMAND状态下收到MMCC_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-10  新版作成
     2. 日    期   : 2006年11月25日
        作    者   : s46746
        修改内容   : 问题单号：A32D07666
     3. 日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
     4. 日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
     5 .日    期   : 2012年12月11日
        作    者   : w00176964
        修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
     6.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     7.日    期   :2014年3月23日
       作    者   :y00245242
       修改内容   :dts2014031406746:处理MT call正在建立过程中，收到MO call冲突处理
     8.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S10_E24:WARNING: MMCC_EST_REQ check fail.");;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            /* 已经存在一个保留的MM连接建立请求         */
            Mm_SndCcRelInd(
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                             /* 通知CC建立失败                           */
        }

        /* 检查多业务冲突是否允许 */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_CC))
        {
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
            return;
        }

        /* 缓存消息 */
        NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
      }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S19_E24
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到MMCC_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  s46746   2005-11-05
     2. 日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
     3.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     4.日    期   : 2012年12月11日
       作    者   : w00176964
       修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
     5.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     6.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S19_E24(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if (MM_FALSE == Mm_RcvCcEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        MM_WARN_LOG(" \nMM:Recieve CC EST REQUEST ERROR!\r " );
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 非紧急呼，当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
         && (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))
        {
            /* 通知CC建立失败                           */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        if ((MM_CONST_NUM_8 > g_MmCcEstReq.ulTransactionId)
            ||(MM_CONST_NUM_14 < g_MmCcEstReq.ulTransactionId))
        {
            /* TI不合法,通知CC建立失败 */
            Mm_SndCcRelInd(g_MmCcEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else
        {                                                                       /* TI合法                                   */
            if (MMCC_EMERGENCY_CALL == g_MmCcEstReq.ulCallType)
            {                                                                   /* 是紧急呼叫                               */
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;     /* 记录收到建立请求时的状态                 */

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
            }
            else
            {
                if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
                {
                    /* 已经存在一个保留的MM连接建立请求,通知CC建立失败 */
                    Mm_SndCcRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }

                /* 缓存消息 */
                NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_CC);
            }
        }
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E25
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMCC_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-10  新版作成

     3.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
     3.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     4.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     5.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E25(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if (MM_FALSE == Mm_RcvCcRelReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if (MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType)
        {                                                                       /* 释放类型为释放指定的MM连接               */
            /*lint -e701*/
            if ((MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId)
                && (MM_CONST_NUM_0 !=
               (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & (0x01 << g_MmCcRelReq.ulTransactionId))))
            {                                                                   /* 释放网侧建立的MM连接并且存在             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    = (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0]
                    & (~(VOS_UINT8)(0x01 << g_MmCcRelReq.ulTransactionId)));    /* 清除MM连接存在标志                       */
            }
            else if ((MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId)
                    && (MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId)
                    && (MM_CONST_NUM_0 != (g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & (0x01 << (g_MmCcRelReq.ulTransactionId - 8)))))
            {                                                                   /* 释放CC建立的MM连接并且存在               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    = (VOS_UINT8)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1]
                    & (~(VOS_UINT8)(0x01 <<
                    (g_MmCcRelReq.ulTransactionId - 8))));                      /* 清除MM连接存在标志                       */
            }
            else
            {
                /* 指定释放的MM连接不存在, 通知CC指定释放的MM连接不存在 */
                Mm_SndCcRelInd(g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
            }
            /*lint +e701*/
            if ( ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
            {                                                                   /* 没有MM连接存在                           */
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
                    ucStaOfRcvXXEstReq;                                         /* 进入空闲的状态                           */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E25:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */

                NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
            }
        }
        else
        {                                                                       /* 释放类型为释放所有的MM连接               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;/* 本地释放网侧建立的MM连接                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;/* 本地释放CC建立的MM连接                   */
            if ( ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
              && ( MM_CONST_NUM_0 ==
              g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]))
            {                                                                   /* 没有MM连接存在                           */
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                          /* 进入空闲的状态                           */
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E25:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */

                NAS_MML_SetCsServiceConnStatusFlg(VOS_FALSE);
            }
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S13_E25
  FUNCTION : 在WAIT FOR REESTABLISH (WAIT FOR REEST REQ) 状态下
             收到MMCC_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-10  新版作成
     2.  张志勇        2005.01.27  007037 for MM

     3.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的CS域的业务存在状态
     4.日    期   : 2011年7月28日
       作    者   : w00167002
       修改内容   : V7R1 PHASEII 重构: PC_LINT修改
     5.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     6.日    期   : 2013年9月12日
       作    者   : w00242748
       修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                    原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                    G下原小区时做LAU
     7.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     8.日    期   : 2014年4月2日
       作    者   : w00176964
       修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
     9.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
    10.日    期   : 2015年3月20日
       作    者   : w00167002
       修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                    进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E25(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_RE_EST_REQ_STRU      MsgReEstReq;
    PS_MEM_SET(&MsgReEstReq,0,sizeof(MM_MSG_RE_EST_REQ_STRU));

    if ( MM_FALSE == Mm_RcvCcRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
        {                                                                       /* 释放类型为释放指定的MM连接               */
            if (   ( MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId )
                && ( MM_CONST_NUM_0 != ( g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                & ( 0x01 << g_MmCcRelReq.ulTransactionId ) ) ) )
            {                                                                   /* 释放网侧重建的MM连接并且存在             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[0] = ( VOS_UINT8 )( g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                    & ( ~(VOS_UINT8)( 0x01 << g_MmCcRelReq.ulTransactionId ) ) );   /* 清除MM连接重建标志                       */
            }
            else if ( ( MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnReestFlg[1] & ( 0x01 <<
                ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) ) )
            {                                                                   /* 释放CC重建的MM连接并且存在               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[1] = ( VOS_UINT8 )( g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
                    & ( ~(VOS_UINT8)( 0x01 <<
                    ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) );                 /* 清除MM连接重建标志                       */
            }
            else
            {
                /* 指定释放的MM连接不存在                   */
                Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC指定释放的MM连接不存在             */
            }
            if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
                && (MM_CONST_NUM_0 == g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]) )
            {                                                                   /* 没有等待重建的MM连接存在                 */
                Mm_TimerStop(MM_TIMER_PROTECT_CC);                              /* 启动保护TIMER                            */
                if ( ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
                    && ( MM_CONST_NUM_0 == g_MmGlobalInfo.
                    ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] ) )
                {                                                               /* 全部释放，没有要求重建的MM连接           */
                    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* 记录迁移之前的状态                       */
                    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

                    if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
                    {
                        if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
                         || ((MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
                          && (MM_TIMER_STOP == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)))
                        {
                            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        }


                    }
                }
                else
                {
                    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;       /* 记录迁移之前的状态                       */
                    Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: ucState is WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF");
                    Mm_TimerStart(MM_TIMER_T3230);                              /* 启动保护TIMER                            */

                    MsgReEstReq.MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();

                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                    MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMcc
                        = NAS_MML_GetCsLastSuccMcc();
                    MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMnc
                        = NAS_MML_GetCsLastSuccMnc();
                    MsgReEstReq.MmIeLai.IeLai.ulLac
                        = NAS_MML_GetCsLastSuccLac();
                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

                    NAS_MM_FillMobileID(&(MsgReEstReq.MmIeMobileId.MobileID));

                    Mm_ComMsgCmReEstReqSnd(&MsgReEstReq);
                }
            }
        }
        else
        {                                                                       /* 释放类型为释放所有的MM连接               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
                = 0;                                                            /* 本地释放网侧建立的MM连接                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
                = 0;                                                            /* 本地释放CC建立的MM连接                   */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 进入空闲的状态                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E25:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }

        /*lint +e701*/
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E25
  FUNCTION : 在WAIT FOR ADDITIONAL OUTGOING MM CONNECTION状态下
             收到MMCC_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-10    新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的链接存在状态
     3.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     4.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     5.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E25(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/

        if ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
        {                                                                       /* 释放类型为释放指定的MM连接               */
            if (   ( MM_CONST_NUM_7 > g_MmCcRelReq.ulTransactionId )
                && ( MM_CONST_NUM_0 != ( g_MmGlobalInfo.
                ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & ( 0x01 << g_MmCcRelReq.ulTransactionId ) ) ) )
            {                                                                   /* 释放网侧建立的MM连接并且存在             */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]=
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0]
                    & ( ~(VOS_UINT8)( 0x01 << g_MmCcRelReq.ulTransactionId ) ) );   /* 清除MM连接存在标志                       */
            }
            else if ( ( MM_CONST_NUM_7 < g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_15 > g_MmCcRelReq.ulTransactionId )
                    && ( MM_CONST_NUM_0 !=
               ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & ( 0x01 << ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) ) )
            {                                                                   /* 释放CC建立的MM连接并且存在               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1]
                    & ( ~(VOS_UINT8)( 0x01 <<
                    ( g_MmCcRelReq.ulTransactionId - 8 ) ) ) );                 /* 清除MM连接存在标志                       */
            }
            else if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulTransactionId == g_MmCcRelReq.ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                    = MM_FALSE;                                                 /* 设置不存在缓存的MM连接 */

            }
            else
            {
                /* 指定释放的MM连接不存在                   */
                Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC指定释放的MM连接不存在             */
            }
        }
        else
        {                                                                       /* 释放类型为释放所有的MM连接               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] = 0;/* 本地释放网侧建立的MM连接                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] = 0;/* 本地释放CC建立的MM连接                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* 设置不存在缓存的MM连接                   */
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();


        /*lint +e701*/
    }

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S32_E26
 功能描述  : 在MM_INTER_RAT_CHANGE状态收到MMCC_ABORT_REQ的处理
 输入参数  : pRcvMsg - 收到的原语头指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
   1.日    期   : 2012年2月15日
     作    者   : z00161729
     修改内容   : 新生成函数
   2.日    期   : 2013年4月02日
     作    者   : y00176023
     修改内容   : DSDS GUNAS II项目:增加CSFB过程中abort后通知目标RAT
   3.日    期   : 2014年5月22日
     作    者   : z00161729
     修改内容   : DTS2014050601476:L打电话重定向到g过程中电话挂断，mm缓存cc abort，g查询csfb状态是存在，
                  lau结束后没有启动自主FR流程到L
   4.日    期   :2014年9月24日
     作    者   :s00217060
     修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S32_E26(
    VOS_VOID                            *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {
        /* 消息检查结果失败 */
        ;
    }
    else
    {
        /* 消息检查结果成功*/
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

            /* 处理MMCC_ABORT_REQ，应该需要将MM正在建立的链接标记清除。
               如果MM正在建立的链接标记没有清除，当回退到LTE时，发现有业务标记存在，就会触发释放业务的流程
            */
            if (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }

            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
            NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);


#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* 通知L CSFB 流程终止 */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }
            }
#endif
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S2_E26
  FUNCTION : 在 MM IDLE PLMN SEARCH,
                MM IDLE ATTEMPTING TO UPDATE,
                WAIT FOR OUTGOING MM CONNECTION,
                WAIT FOR NETWORK COMMAND,
                WAIT FOR RR CONNECTION (MM CONNECTION),
                WAIT FOR REESTABLISH(WAIT FOR REEST REQ),
                WAIT FOR REESTABLISH(WAIT FOR EST_CNF),
                WAIT FOR ADDITIONAL OUTGOING MM CONNECTION,
                LOCATION UPDATING PENDING,
                IMSI DETACH PENDING,
                WAIT FOR ATTACH,
                WAIT FOR RR CONNECTION (LOCATION UPDATING),
                LOCATION UPDATING INITIATED,
                LOCATION UPDATE REJECTED,
                WAIT FOR RR CONNECTION (IMSI DETACH),
                IMSI DETACH INITIATED
             状态下收到MMCC_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.日    期   : 2007年03月09日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单A32D09099创建
  2.日    期   : 2007年10月06日
    作    者   : l65478
    修改内容   : 问题单号：A32D12977
  3.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4.日    期   : 2012年2月15日
    作    者   : z00161729
    修改内容   : V7R1C50 支持CSFB特性修改
  5.日    期   : 2014年6月10日
    作    者   : w00242748
    修改内容   : DTS2014061001560:L下主叫，CSFB到NMOI W下，做LAU/RAU，LAU过程中，
                 挂断电话，但此时信令链接未释放，MM给GMM发送MMGMM_CS_CONNECT_NOT_EXIST，
                 导致GMM在链路存在的情况下一直进行RAU。
  6.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
  7.日    期   : 2014年9月23日
    作    者   : z00161729
    修改内容   : DTS2014092302846:L下拨打电话搜网到w下被#12拒绝的小区，电话失败后重选回l，mm会给cc多发一次mmcc rel ind
  8.日    期   : 2016年2月2日
    作    者   : z00359541
    修改内容   : DTS2016011809099:不需要发送CSFB ABORT消息打断状态机，CSFB电话结束后收到CALL STARTUS NOTIFY消息时会打断
*******************************************************************************/
VOS_VOID Mm_Cell_S2_E26(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                           ucCsSigConnStatusFlg;

    ucCsSigConnStatusFlg = NAS_MML_GetCsSigConnStatusFlg();

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        ;
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                      .RcvXXEstReq.ucFlg)
         && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                             .RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

            if (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI)
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }


            if ( VOS_FALSE == ucCsSigConnStatusFlg )
            {
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

#if (FEATURE_ON == FEATURE_LTE)
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
            {
                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
                {
                    /* 通知L CSFB 流程终止 */
                    NAS_MM_SndLmmCsfbServiceAbortNotify();
                }
            }
#endif
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E26
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到MMCC_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-10  新版作成
     2.日    期   : 2012年1月21日
       作    者   : s46746
       修改内容   : 更新MML_CTX中的链接业务状态
     3.日    期   : 2012年1月30日
       作    者   : s46746
       修改内容   : 业务建立过程中主动终止业务时需要清除CS业务标志
     4.日    期   : 2012年2月15日
       作    者   : z00161729
       修改内容   : V7R1C50 支持CSFB特性修改
     5.日    期   : 2014年6月13日
       作    者   : w00242748
       修改内容   : DSDS 新特性
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E26(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
            g_MmCcAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            Mm_ComMsgCmSvcAbortSnd();
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;

            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E26:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceBufferStatusFlg();

        NAS_MM_UpdateCsServiceConnStatusFlg();
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E26
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMCC_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇   05-02-01  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的链接业务状态
     3.日    期   : 2012年2月15日
       作    者   : z00161729
       修改内容   : V7R1C50 支持CSFB特性修改
     4.日    期   : 2014年6月13日
       作    者   : w00242748
       修改内容   : DSDS 新特性
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E26(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    /*lint -e701*/
    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( 0 != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
        .aucMMConnExtFlg[1]
            & (0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ))))
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            if (((0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ))
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[1])
                &&(0 == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[0]))
            {
                Mm_ComMsgCmSvcAbortSnd();
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                               g_MmGlobalInfo.ucStaOfRcvXXEstReq;               /* 返回到接收到建立MM连接请求时的状态       */

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;           /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E26:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动TIMER3240                            */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnExtFlg[1] = 0;
            }
            else
            {
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );/* MM连接流程                               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    &= ~(VOS_UINT8)(0x01 << ( g_MmCcAbortReq.ulTransactionId - 8 ));
            }
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
    /*lint +e701*/
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E26
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下收到MMCC_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇   05-02-01  新版作成

  2.日    期   : 2007年10月06日
    作    者   : l65478
    修改内容   : 问题单号：A32D12977

  3.日    期   : 2010年4月15日
    作    者   : o00132663
    修改内容   : AT2D18449,MM 未清除相关全局变量，导致CC中断呼叫后，MM仍然发
                 起业务建链请求
  4.日    期   :2013年8月13日
    作    者   :z00161729
    修改内容   :DTS2013081207431:mm挂起状态收到cc的t303超时abort消息，需要缓存，收到resume ind时再处理
  5.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E26(
    VOS_VOID                            *pRcvMsg
)
{
    if ( MM_FALSE == Mm_RcvCcAbortReq( pRcvMsg ) )
    {
        return;
    }
    else
    {
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
                g_MmCcAbortReq.ulTransactionId )
        {
            /* 终止的MM连接建立是正在建立的,如果接入技术相同则发送rel req */
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucRat == NAS_MML_GetCurrNetRatType())
            {
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                g_MmGlobalInfo.bWaitingEstCnf = VOS_FALSE;
                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);
                NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S12_E26:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);

                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );

            /* 清除MM相关全局变量 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI  = NO_MM_CONN_ESTING;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId ==
                     g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E26
  FUNCTION : 在WAIT FOR ADDITIONAL OUTGOING MM CONNECTION状态下
             收到MMCC_ABORT_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-10  新版作成
     2.日    期   : 2012年2月15日
       作    者   : z00161729
       修改内容   : V7R1C50 支持CSFB特性修改
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E26(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvCcAbortReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
            g_MmCcAbortReq.ulTransactionId )
        {                                                                       /* 终止的MM连接建立是正在建立的             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E26:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }
        else
        {
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                          .RcvXXEstReq.ucFlg)
             && (g_MmCcAbortReq.ulTransactionId == g_MmGlobalInfo
                    .ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId))
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
#endif

        NAS_MM_UpdateCsServiceBufferStatusFlg();

    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E27
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMCC_DATA_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-10  新版作成
     2.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     3.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     4.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E27(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;
    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvCcDataReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( ( MM_CONST_NUM_7 == pMmCcDataReq->ulTransactionId )
            || ( MM_CONST_NUM_15 == pMmCcDataReq->ulTransactionId ) )
        {                                                                       /* TIO 等于111                              */
            Mm_SndRrDataReq(
                pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* 将CC的消息传送下去                       */
        }
        else
        {                                                                       /* TIO 不等于111                            */
            /*lint -e701*/
            if ( ( ( MM_CONST_NUM_7 > pMmCcDataReq->ulTransactionId)
                && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0]
                & ( 0x01 << pMmCcDataReq->ulTransactionId ) ) ) )
                || ( ( MM_CONST_NUM_7 < pMmCcDataReq->ulTransactionId)
                && ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1]
                & ( 0x01 << ( pMmCcDataReq->ulTransactionId - 8 ) ) ) ) ) )
            {                                                                   /* 该TI的MM连接存在                         */
                Mm_SndRrDataReq(
                pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* 将CC的消息传送下去                       */
            }
            else
            {
                /* 该TI的MM连接不存在                       */
                Mm_SndCcRelInd(pMmCcDataReq->ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                              /* 通知CC建立失败                           */
            }

            /*lint +e701*/
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S13_E28
  FUNCTION : 在WAIT FOR REESTABLISH ( WAIT FOR REEST REQ )状态下
             收到MMCC_REEST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-10  新版作成
     2.  张志勇        2005.01.27  007037 for MM
     3.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     4.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     5.日    期   : 2014年4月2日
       作    者   : w00176964
       修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
     6.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E28(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_RE_EST_REQ_STRU      MsgReEstReq;
    PS_MEM_SET(&MsgReEstReq,0,sizeof(MM_MSG_RE_EST_REQ_STRU));

    if ( MM_FALSE == Mm_RcvCcReestReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmCcReestReq.ulTransactionId )
        {                                                                       /* 是网侧建立的MM连接重建                   */
            if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
            & ( 0x01 << g_MmCcReestReq.ulTransactionId ) ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0] |
                    ( 0x01 << g_MmCcReestReq.ulTransactionId ) );               /* 设置正在重建的MM连接的标志               */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                .aucMMConnReestFlg[0] =
                    ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnReestFlg[0] &
                    (~(VOS_UINT8)( 0x01 << g_MmCcReestReq.ulTransactionId ) ) );    /* 清除正在重建的MM连接的标志               */
            }
            else
            {
                Mm_SndCcRelInd(g_MmCcReestReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                        /* 通知CC重建立失败                         */
            }

        }
        else if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
            & ( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) ) )
        {                                                                       /* 是CC建立的MM连接重建                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] |
                ( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) );           /* 设置正在重建的MM连接的标志               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] =
                ( VOS_UINT8 )( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnReestFlg[1] &
                (~(VOS_UINT8)( 0x01 << ( g_MmCcReestReq.ulTransactionId - 8 ) ) ) );/* 清除正在重建的MM连接的标志               */
        }
        else
        {
            /* 要求重建的MM连接不存在                   */
            Mm_SndCcRelInd(g_MmCcReestReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                                  /* 通知CC重建立失败                         */
        }
        /*lint +e701*/
        if ( ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
            && (MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]) )
        {                                                                       /* 没有等待重建的MM连接存在                 */
            Mm_TimerStop(MM_TIMER_PROTECT_CC);
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E28:NORMAL: STATUS is WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF");
            MsgReEstReq.MmIeCKSN.ucCksn = NAS_MML_GetSimCsSecurityCksn();

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMcc
                = NAS_MML_GetCsLastSuccMcc();
            MsgReEstReq.MmIeLai.IeLai.PlmnId.ulMnc
                = NAS_MML_GetCsLastSuccMnc();
            MsgReEstReq.MmIeLai.IeLai.ulLac
                = NAS_MML_GetCsLastSuccLac();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

            NAS_MM_FillMobileID(&(MsgReEstReq.MmIeMobileId.MobileID));

            Mm_ComMsgCmReEstReqSnd(&MsgReEstReq);
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
        }
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S2_E31
  FUNCTION : 在MM IDLE PLMN SEARCH状态下收到RRMM_PAGING_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.s46746      08-05-02  新版作成
  2.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Mm_Cell_S2_E31(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    if (MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING,
               "Mm_Cell_S2_E31:WARNING: Msg is invalid.");
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_TRUE;

    /* 通知MMC CS服务要发起，需要停止搜网 */
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO,
           "Mm_Cell_S2_E31:INFO: Rcv Paging in Plmn Search, Wait camping.");

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S3_E31
  FUNCTION : 在MM IDLE NORMAL SERVICE状态下收到RRMM_PAGING_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      03-12-10  新版作成
  6.张志勇        2005.01.27  007037 for MM
  3.s46746     2005.09.27  modify for HSS 4100 V200R001
  4.s46746     2006.01.17  modify for A32D01587
  5.s46746     2006.02.28  modify for A32D03324
  6.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  7.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E31(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_PAGING_RSP_STRU      CmRspRsp;                                       /* 要发送的PAGING RSP消息                   */

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
    {
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    }

    CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();            /* 存储CKSN                                 */
    g_MmGlobalInfo.ucStaOfRcvXXEstReq
        = g_MmGlobalInfo.ucState;

    NAS_MM_FillMobileID(&(CmRspRsp.MmIeMobileId.MobileID));

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* 当前处于 GSM 网中 */
    {
        /* 向 GAS 发送建立 RR 请求 */
        Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                       MM_CONST_NUM_0, VOS_NULL_PTR);
    }
    else /* UMTS 网中 */
    {
        Mm_ComMsgPagingRspSnd( &CmRspRsp );                                     /* 填充并发送 PAGING RESPONSE 消息          */
    }

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* 通知MMC，CS域的业务已经启动              */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                                 /* 启动保护TIMER                            */

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    return;
}
/*****************************************************************************
 函 数 名  : Mm_Cell_S4_E31
 功能描述  : MM IDLE LIMITED SERVICE状态下收到RRMM_PAGING_IND的处理
 输入参数  : VOS_VOID            *pRcvMsg  收到的原语头指针
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年8月19日
    作    者   : 欧阳飞  ID: 00132663
    修改内容   : 新生成函数 for AT2D05087
  2.日    期   : 2008年10月08日
    作    者   : o00132663
    修改内容   : 问题单号：AT2D06064,如果手机已经发起了detach,那么即使收到了IMSI Paging，也不响应寻呼。
  3.日    期   : 2011年03月01日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011021202242/DTS2011021400322，添加宏开关判断
                 服务域为PS_ONLY时，CS域短信和呼叫业务是否能够发起
  4.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
*****************************************************************************/
VOS_VOID Mm_Cell_S4_E31(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                        )
{
    MM_MSG_PAGING_RSP_STRU              CmRspRsp;                                       /* 要发送的PAGING RSP消息                   */
    VOS_UINT8                           ucCsAttachAllow;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */



    enMsMode        = NAS_MML_GetMsMode();

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* 24.008：4.2.2.3：it may respond to paging (with IMSI).*/
    if (( (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
       && (VOS_TRUE == ucCsAttachAllow))
       || ( (NAS_MML_MS_MODE_PS_ONLY == enMsMode)
          &&(NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)))
    {
        if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }
    
        CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();        /* 存储CKSN                                 */

        g_MmGlobalInfo.ucStaOfRcvXXEstReq
            = g_MmGlobalInfo.ucState;

        NAS_MM_FillMobileID(&CmRspRsp.MmIeMobileId.MobileID);

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())              /* 当前处于 GSM 网中 */
        {
            /* 向 GAS 发送建立 RR 请求 */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0, VOS_NULL_PTR);
        }
        else /* UMTS 网中 */
        {
            Mm_ComMsgPagingRspSnd( &CmRspRsp );                                 /* 填充并发送 PAGING RESPONSE 消息          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* 启动保护TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S5_E31
  FUNCTION : 在MM IDLE ATTEMPTING TO UPDATE状态下收到RRMM_PAGING_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      03-12-10  新版作成
  2.张志勇        2005.01.27  007037 for MM
  3.s46746     2005.09.08  modify for HSS 4100 V200R001
  4.s46746     2006.01.17  modify for A32D01587
  5.s46746     2006.01.17  modify for A32D03324
  6.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  7.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E31(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_PAGING_RSP_STRU      CmRspRsp;                                       /* 要发送的PAGING RSP消息                   */

    if ( MM_FALSE == Mm_RcvRrcPagingInd(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* 用 IMEI 寻呼的处理 */
    if (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }

        CmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();        /* 存储CKSN                                 */

        g_MmGlobalInfo.ucStaOfRcvXXEstReq
            = g_MmGlobalInfo.ucState;

        NAS_MM_FillMobileID(&(CmRspRsp.MmIeMobileId.MobileID));

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType()) /* 当前处于 GSM 网中 */
        {
            /* 向 GAS 发送建立 RR 请求 */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0, VOS_NULL_PTR);
        }
        else /* UMTS 网中 */
        {
            Mm_ComMsgPagingRspSnd( &CmRspRsp );                                     /* 填充并发送 PAGING RESPONSE 消息          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S5_E31:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* 启动保护TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    }

    return;
}
/*****************************************************************************
 函 数 名  : Mm_Cell_S6_E31
 功能描述  : MM在MM_IDLE_LOCATION_UPDATE_NEEDED状态收到寻呼消息的处理
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : 新生成函数
  2.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
*****************************************************************************/
VOS_VOID Mm_Cell_S6_E31(
    VOS_VOID                           *pstRcvMsg
)
{
    MM_MSG_PAGING_RSP_STRU              stCmRspRsp;                                       /* 要发送的PAGING RSP消息                   */
    VOS_UINT8                           ucCsAttachAllow;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    enMsMode                = NAS_MML_GetMsMode();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();

    if (MM_FALSE == Mm_RcvRrcPagingInd(pstRcvMsg))
    {
        return;
    }

    /* 当前小区PAGING受限则不处理 */
    if (VOS_TRUE == NAS_MML_GetCsRestrictPagingFlg())
    {
#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_MM_PAGING_BAR);
#endif
        return;
    }

    Mm_TimerStop(MM_TIMER_T3211);

    /* MM_IDLE_LOCATION_UPDATE_NEEDED状态如果当前CS 注册状态响应普通寻呼，
       否则只能响应 IMSI 寻呼 */
    if ((MM_COM_SRVST_NORMAL_SERVICE == NAS_MM_GetLauUptNeededCsSrvStatus())
     || (( (MM_IMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
        && (VOS_TRUE == ucCsAttachAllow))
      || ( (NAS_MML_MS_MODE_PS_ONLY == enMsMode)
        && (NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg))))
    {
        if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
        {
            NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
            NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
        }

        stCmRspRsp.MmIeCksn.ucCksn            = NAS_MML_GetSimCsSecurityCksn(); /* 存储CKSN                                 */
        g_MmGlobalInfo.ucStaOfRcvXXEstReq     = g_MmGlobalInfo.ucState;
        NAS_MM_FillMobileID(&(stCmRspRsp.MmIeMobileId.MobileID));

        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())            /* 当前处于 GSM 网中 */
        {
            /* 向 GAS 发送建立 RR 请求 */
            Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                           MM_CONST_NUM_0,
                           VOS_NULL_PTR);
        }
        else /* UMTS 网中 */
        {
            Mm_ComMsgPagingRspSnd(&stCmRspRsp);                                 /* 填充并发送 PAGING RESPONSE 消息          */
        }

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                             /* 启动保护TIMER                            */

        NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S12_E32
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下
             收到RRMM_EST_CNF的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
     2.  张志勇        2005.01.27  007037 for MM
     3.  日    期   : 2009年05月25日
         作    者   : l65478
         修改内容   : 问题单:AT2D10870,在MM连接建立过程中发生LAI改变,没有发起LU,导致呼叫失败
     4.  日    期   : 2010年01月08日
         作    者   : l65478
         修改内容   : 问题单:AT2D16252,在收到RRMM_EST_CNF时，把缓存的SS的消息清除了，导致SS业务无法发起
     5.  日    期   : 2010年5月17日
         作    者   : o00132663
         修改内容   : AT2D19083, 接入层立即回复建链失败，导致MM/WAS直接进行乒乓操
                      作，消息队列溢出。
     6.  日    期   : 2013年6月8日
         作    者   : w00167002
         修改内容   : V9R1_SVLTE:收到建链结果后，如果建链成功，发起cs域的DETACH.
                      否则直接本地DETACH;
     7.日    期   : 2014年8月14日
       作    者   : z00161729
       修改内容   : gas下lau建链失败原因值random access reject no valid information场景未按协议实现8s内不发起lau，t3213 4s超时就发起了lau
     8.日    期   :2015年3月13日
       作    者   :n00269697
       修改内容   :CHR 优化项目，添加CS PAGING FAIL异常记录
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E32(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    RRMM_EST_CNF_STRU       *pRrMmEstCnf;

    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        pRrMmEstCnf = (RRMM_EST_CNF_STRU*)pRcvMsg;
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */

        NAS_MM_SetEstCnfResult(pRrMmEstCnf->ulResult);


        /* 处理当前缓存的CS域去注册 */
        if ( MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH) )
        {
            NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrMmEstCnf);

            return;
        }

        /* 在进行CS呼叫建链过程中，如果接入层回复建链失败，原因值为: Conn_Fail，
             对比标杆，发现标杆会重新发起建链请求，直到CC T303超时后中断为止,
            这样可以提高电话接通率 */
        if (  (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
           && ((RRC_EST_EST_CONN_FAIL == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_NOT_ALLOW == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_TIME_OUT == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_RA_RESOURCE_FAIL == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID == pRrMmEstCnf->ulResult)
            || (RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL == pRrMmEstCnf->ulResult))
           && (MM_IE_PD_CALL_CONTROL == g_MmGlobalInfo.ucMMConnEstingPD))
        {
            g_MmGlobalInfo.ucCallRetryCount++;

            /* 为了防止MM/GAS反复进行乒乓操作，导致系统消息队列溢出，限制尝试次数 */
            if (g_MmGlobalInfo.ucCallRetryCount < MM_CALL_RETRY_MAX_TIMES)
            {
                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

                return;
            }
        }

#if (FEATURE_ON == FEATURE_PTM)
        NAS_MM_RecordCsPagingFail_WaitForRrConnection(pRrMmEstCnf->ulResult);
#endif

        /* 清除消息缓存标志               */
        NAS_MM_ClearConnCtrlInfo(g_MmGlobalInfo.ucMMConnEstingPD);

        /* 只有建链结果是RRC_EST_SUCCESS或者RRC_EST_PRESENT，才需要设置业务存在标志 */

        NAS_MM_ProcEstCnfCauseAtState12(pRrMmEstCnf->ulResult);
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E32
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR EST_CNF)状态下
             收到RRMM_EST_CNF的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
     2.  张志勇        2005.01.27  007037 for MM

     3.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的链接存在状态
     4.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建

     5.日    期   : 2013年6月11日
       作    者   : w00167002
       修改内容   : V9R1_SVLTE:处理当前缓存的CS域去注册
     6.日    期   : 2013年8月22日
       作    者   : w00167002
       修改内容   : DTS2013081604476:w重选到G下后，被立即指派拒绝，GAS启动T3122
                    定时器，接着用户发起电话，NAS发起LAU,GAS由于T3122运行，直接回复
                    建联失败。MM启动了T3211,在这种场景下，NAS不需要启动T3211定时器。
     7.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     8.日    期   : 2013年4月10日
       作    者   : y00176023
       修改内容   : DSDS GUNAS II项目:增加对RRC_EST_RJ_NO_RF的处理
     9.日    期   : 2014年8月14日
       作    者   : z00161729
       修改内容   : gas下lau建链失败原因值random access reject no valid information场景未按协议实现8s内不发起lau，t3213 4s超时就发起了lau
    10.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E32(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* 循环计数变量                             */
    RRMM_EST_CNF_STRU       *pRrMmEstCnf;
    VOS_UINT8                ucTiValidFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        pRrMmEstCnf = (RRMM_EST_CNF_STRU*)pRcvMsg;


        NAS_MM_SetEstCnfResult(pRrMmEstCnf->ulResult);

        /* 处理当前缓存的CS域去注册 */
        if ( MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH) )
        {
            NAS_MM_RcvRrMmEstCnf_ExistCsDetachBuffer(pRrMmEstCnf);

            return;
        }

        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */
        switch ( pRrMmEstCnf->ulResult)
        {
        case RRC_EST_SUCCESS:                                                   /* 信令连接建立成功                         */
        case RRC_EST_PRESENT:                                                   /* 该信令连接已经存在                       */
            if ( RRC_EST_PRESENT == pRrMmEstCnf->ulResult )
            {
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: RR CONNECTION PRESENT !");
            }
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ESTED );

            Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */
            g_MmGlobalInfo.ucCsSigConnFlg = MM_CS_SIG_CONN_PRESENT;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E32:INFO: MmCsSigConnFlg is MM_CS_SIG_CONN_PRESENT");
            break;
        /* case RRC_EST_DELING:  */                                                  /* 该信令连接正在释放                       */
        case RRC_EST_RJ_CONGEST:                                                /* RRC Connection Reject: Congestion        */
        case RRC_EST_RJ_UNSPEC:                                                 /* RRC Connection Reject: Unspecified       */
        case RRC_EST_EST_CONN_FAIL:                                             /* RR connection establish failure          */
        case RRC_EST_RJ_NOT_ALLOW:
        case RRC_EST_RJ_TIME_OUT:
        case RRC_EST_RJ_RA_RESOURCE_FAIL:
        case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
        case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
        case RRC_EST_RJ_AIRMSG_DECODE_ERR:
        case RRC_EST_RJ_FASTRETURN_LTE:
        case RRC_EST_RJ_RA_FAIL_NO_VALID_INFO:
        case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:

        case RRC_EST_RJ_SNW:

        case RRC_EST_RJ_NO_RF:

        case RRC_EST_RJ_T3122_RUNNING:

        case RRC_EST_OTHER_ACCESS_BARRED:
        case RRC_EST_ACCESS_BARRED:
        case RRC_EST_RJ_INTER_RAT:
        case RRC_EST_IMMEDIATE_ASSIGN_REJECT:
        case RRC_EST_RANDOM_ACCESS_REJECT:
        /* RRC_EST_RJ_RA_FAIL是从原来的RRC_EST_RANDOM_ACCESS_REJECT可拆出来的，与RRC_EST_RANDOM_ACCESS_REJECT的处理保持一致
           RRC_EST_RJ_CELL_BAR 是从原来的RRC_EST_ACCESS_BARRED中拆出来的，与RRC_EST_ACCESS_BARRED的处理保持一致 */
        case RRC_EST_RJ_RA_FAIL:
        case RRC_EST_RJ_CELL_BAR:

        case RRC_EST_RANDOM_ACCESS_REJECT_NO_VALID_INFO:
            /*lint -e701*/
            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* 重建的MM连接                             */
                if ( MM_CONST_NUM_0 !=
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                    & ( 0x01 << i ) ) )
                {
                    /* 该TI的MM连接正在等待重建 */
                    Mm_SndCcRelInd(i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                if ( MM_CONST_NUM_0 !=
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                    & ( 0x01 << i ) ) )
                {
                    /* 该TI的MM连接正在等待重建 */
                    Mm_SndCcRelInd( ( i + 8 ), NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);/* 通知CC,MM连接重建失败                    */
                }
            }

            /*lint +e701*/

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E32:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            if ( MM_FALSE == Mm_ComChkLu() )
            {
                if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                              .RcvXXEstReq.ucFlg)
                    ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                              .RcvXXEstReq.ucFlg)
                    ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                              .RcvXXEstReq.ucFlg))
                {
                    ucTiValidFlg = Mm_ComTiChk();
                    if ( MM_FALSE == ucTiValidFlg )
                    {
                        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
                        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                    }
                    else
                    {
                        Mm_ComSigRelForDelayMmConnRej();
                    }
                }
                else
                {
                    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );             /* RR连接不存在                             */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                  NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);   /* 通知CC建立失败                           */
                }
                if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSmsRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                        .RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
            }

            break;
        case RRC_EST_ESTING:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: RR CONNECTION ESTING !");
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E32:WARNING: ulResult Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();

    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E33
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
     2.  s46746     05-09-24  modify for HSS 4100 V200R001
     3.日    期   : 2012年9月07日
       作    者   : l00171473
       修改内容   : DTS2012081701006, 添加MM状态的可维可测消息
     4.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     5.日    期   : 2013年6月6日
       作    者   : w00167002
       修改内容   : V9R1_SVLTE:CS未注册下，当前有PS业务，紧急呼后接释放，需要发起LAU。
                    2. 如果当前的存在注册的缓存，在建链过程中收到REL IND，则直接
                       本地去注册。
     6.日    期   : 2013年8月28日
       作    者   : l65478
       修改内容   : DTS2013082607368:限制驻留在禁止的网络上,CS业务结束后发起了LU
     7.日    期   : 2013年9月12日
       作    者   : z00161729
       修改内容   : DTS2013082903019:支持ss重发功能
     8.日    期   : 2014年01月09日
       作    者   : l65478
       修改内容   : DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
     9.日    期   : 2014年04月03日
       作    者   : w00176964
       修改内容   : V3R3C60_eCall项目调整
    10.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
    11.日    期   : 2015年1月28日
       作    者   : w00167002
       修改内容   : DTS2015011400748:在G下RL FAILURE，后FR,导致上下配合异常。修改为
                    G上报RRC_REL_CAUSE_G_RL_FAIL原因值，这样NAS就不发起CC 重建。
    12.日    期   :2016年1月9日
       作    者   :z00359541
       修改内容   :DTS2015111402223:增加小区是否支持CSMO标识
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E33(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    RRMM_REL_IND_STRU                   *pRrmmRelInd;
    VOS_UINT8                           ucTiValidFlg = MM_TRUE;
    VOS_UINT8                           ucRrConnRelFlg = MM_TRUE;
    VOS_UINT8                           ucRst;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        NAS_NORMAL_LOG(WUEPS_PID_MM, "Mm_Cell_S9_E33: Rcv RR REL IND, Set CellNotSupportCsmoFlg to TRUE");
        NAS_MML_SetCellNotSupportCsmoFlg(VOS_TRUE);

        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        ucRst = NAS_MM_RetryCurrentProcedureCheck(pRrmmRelInd->ulRelCause,
                    pRrmmRelInd->ulRrcConnStatus);

        if (VOS_TRUE == ucRst)
        {
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停TIMER3230                              */

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */

            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

            /* 重新发起当前MM CONNECTION建链流程 */
            NAS_MM_RetryMmConnectionProc(g_MmGlobalInfo.ucMMConnEstingPD);
            return;
        }

        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停TIMER3230                              */

            /* 释放当前正在建立的MM连接的TI */
            NAS_MM_RelEstingMmConn(pRrmmRelInd->ulRelCause);

            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComProcCauseProcess();

            /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                   判断如果当前有PS业务，需要发起LAU */
            if ( VOS_TRUE == ucEmergencyLauFlg )
            {
                /* 发起LAU */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* 设置LU类型                               */
                Mm_ComLuOnly();

                return ;
            }

            if ( MM_FALSE == Mm_ComChkLu() )
            {
                if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                              .RcvXXEstReq.ucFlg)
                    ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                              .RcvXXEstReq.ucFlg)
                    ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                              .RcvXXEstReq.ucFlg))
                {
                    ucTiValidFlg = Mm_ComTiChk();
                    if ( MM_FALSE == ucTiValidFlg )
                    {
                        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
                        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                    }
                    else
                    {
                        Mm_ComSigRelForDelayMmConnRej();
                    }
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                          /* 通知CC建立失败                           */
                }
                if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSmsRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                        .RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E33:WARNING: ulRelCause Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_NotifyCcErrInd
 功能描述  : MM通知CC连接失效
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月4日
    作    者   : l60609
    修改内容   : 新生成函数
  2.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  3.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_NotifyCcErrInd(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enCause
)
{
    VOS_UINT8   i;

    i = 0;

    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                           /* 重建的MM连接                             */
        /*lint -e701*/
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndCcErrInd(i, enCause);                                         /* 通知CC,MM连接失效                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndCcErrInd(i + 8, enCause);                                              /* 通知CC,MM连接失效                        */
        }


        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndSsRelInd(i, enCause);                                                  /* 通知SS,MM连接失效                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndSsRelInd(i + 8, enCause);                                              /* 通知SS,MM连接失效                        */
        }

        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndSmsRelInd(i, enCause);                 /* 通知SS,MM连接失效                        */
        }
        if (MM_CONST_NUM_0
            != (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                & (0x01 << i)))
        {                                                                       /* 该TI的MM连接失效                         */
            Mm_SndSmsRelInd((i + 8), enCause);          /* 通知SS,MM连接失效                        */
        }
        /*lint +e701*/

    }
}

/*****************************************************************************
 函 数 名  : NAS_MM_HandleRelIndCause15AtS10
 功能描述  : 在MM CONNECTION ACTIVE状态下收到RRMM_REL_IND，原因值为15的处理
 输入参数  : VOS_UINT8    ucRrConnRelFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月4日
    作    者   : l60609
    修改内容   : 新生成函数

  2.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 更新MML_CTX中的链接存在状态
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
VOS_VOID NAS_MM_HandleRelIndCause15AtS10(VOS_UINT8    ucRrConnRelFlg)
{
    VOS_UINT8    ucTiValidFlg;

    ucTiValidFlg = MM_TRUE;

    NAS_MM_NotifyCcErrInd(NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0]
        = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0];      /* 记录需要重建的标志                       */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]
        = g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1];      /* 记录需要重建的标志                       */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */

    if ((MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0])
        || (MM_CONST_NUM_0 !=
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1]))
    {
        Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_HandleRelIndCause15AtS10:NORMAL: STATUS is WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ");
        Mm_TimerStart(MM_TIMER_PROTECT_CC);                             /* 启动保护TIMER                            */
    }
    else
    {
        if (MM_TRUE == ucRrConnRelFlg)
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_MM_HandleRelIndCause15AtS10:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        Mm_ComProcCauseProcess();

        if ( MM_FALSE == Mm_ComChkLu() )
        {
            if ((MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
                ||(MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
                ||(MM_TRUE
                    == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
            {
                ucTiValidFlg = Mm_ComTiChk();
                if ( MM_FALSE == ucTiValidFlg )
                {
                    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );     /* RR连接不存在                             */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                else
                {
                    Mm_ComSigRelForDelayMmConnRej();
                }
            }
            Mm_ComCheckDelayMmConn( MM_FALSE );

            Mm_ComCheckDelayDetach();
        }
        else
        {
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
            {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndCcRelInd(
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* 通知CC建立失败                           */
            }
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
            {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndSmsRelInd(
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
            }
            if (MM_TRUE
                == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
            {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                    = MM_FALSE;

                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
            }
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E33
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
     2.  张志勇        2005.01.27  007037 for MM
     3.  s46746    05-09-24  modify for HSS 4100 V200R001
     4.  s46746     2006.08.09  根据问题单A32D05269修改
     5.  日    期   : 2009年05月25日
         作    者   : l65478
         修改内容   : 问题单:AT2D10870,在MM连接建立过程中发生LAI改变,没有发起LU,导致呼叫失败
     6.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建

  3.日    期   : 2013年4月16日
    作    者   : z00234330
    修改内容   : DTS2013041604521:CSFB紧急呼叫,PS域链路存在,网络直接下发rel ind,mm 未进行Lau

  4.日    期   : 2013年6月6日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:CS未注册下，当前有PS业务，紧急呼后链接释放，需要发起LAU。
  5.日    期   : 2013年8月28日
    作    者   : l65478
    修改内容   : DTS2013082607368:限制驻留在禁止的网络上,CS业务结束后发起了LU
  6.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  7.日    期   :2014年01月09日
    作    者   :l65478
    修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
  8.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log

  9.日    期   : 2015年1月28日
    作    者   : w00167002
    修改内容   : DTS2015011400748:在G下RL FAILURE，后FR,导致上下配合异常。修改为
                 G上报RRC_REL_CAUSE_G_RL_FAIL原因值，这样NAS就不发起CC 重建。
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E33(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    RRMM_REL_IND_STRU                  *pRrmmRelInd;
    VOS_UINT8                           ucRrConnRelFlg;
    VOS_UINT32                          ucEmergencyLauFlg;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    ucRrConnRelFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        /* RRC_REL_CAUSE转换为MMCC_REL_CAUSE */
        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pRrmmRelInd->ulRelCause);

        if ((MM_TRUE == ucRrConnRelFlg)
         && (RRC_REL_CAUSE_RL_FAILURE != pRrmmRelInd->ulRelCause))
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }

        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
            case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
                NAS_MM_HandleRelIndCause15AtS10(ucRrConnRelFlg);
                break;

            case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
            case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
            case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
            case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
            case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
            case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
            case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
            case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
            case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
            case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
            case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
            case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
            case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
            case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
            case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
            case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
            case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
            case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
            case RRC_REL_CAUSE_RLC_ERROR:
            case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
            case RRC_REL_CAUSE_T314_EXPIRED:
            case RRC_REL_CAUSE_W_RL_FAIL:

            case RRC_REL_CAUSE_G_RL_FAIL:



                Mm_ComRelAllMmConn(enMmCcRelCause);

                                                              /* 释放所有mm连接                           */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                Mm_ComProcCauseProcess();

                Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);         /* RR连接不存在                             */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                /* added by z00234330 for DTS2013041604521CSFB紧急呼叫,PS域链路存在,网络直接下发rel ind,mm 未进行Lau 2013-04-11 begin */


                /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                   判断如果当前有PS业务，需要发起LAU */
                if ( VOS_TRUE == ucEmergencyLauFlg )
                {
                    /* 发起LAU */
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* 设置LU类型                               */
                    Mm_ComLuOnly();

                    return ;
                }

                if ( MM_FALSE == Mm_ComChkLu() )
                {
                    (VOS_VOID)NAS_MM_NotifyBufferedServiceRRConnNotExist();

                    Mm_ComCheckDelayMmConn( MM_FALSE );

                    Mm_ComCheckDelayDetach();
                }
                /* added by z00234330 for DTS2013041604521CSFB紧急呼叫,PS域链路存在,网络直接下发rel ind,mm 未进行Lau 2013-04-11 end */
                break;

            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S10_E33:WARNING: ulRelCause Abnormal");
                break;
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E33
  FUNCTION : 在WAIT FOR NETWORK COMMAND状态下收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
     2.  s46746     05-09-24  modify for HSS 4100 V200R001
     3.日    期   : 2013年01月23日
       作    者   : s00217060
       修改内容   : 问题单: DTS2013012106172,收到RRMM_REL_IND时，清除紧急呼标志
     4.日    期   : 2013年6月6日
       作    者   : w00167002
       修改内容   : V9R1_SVLTE:CS未注册下，当前有PS业务，紧急呼后链接释放，需要发起LAU。

     4.日    期   : 2013年7月27日
       作    者   : w00167002
       修改内容   : DTS2013072604691:w下II,PS attach失败原因11，cs注册成功；
                     CS域/ps发起循环注册.修改为CS不发起循环注册。

     6.日    期   : 2013年8月28日
       作    者   : l65478
       修改内容   : DTS2013082607368:限制驻留在禁止的网络上,CS业务结束后发起了LU
     7.日    期   :2014年01月09日
       作    者   :l65478
       修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
    8.日    期   : 2014年5月4日
      作    者   : z00161729
      修改内容   : DTS2014042816166:l csfb 到w，rau被12拒绝，lau成功没有清除forbidden信息，导致fast return到l后csfb到w相同小区电话失败
    9.日    期   :2014年9月24日
      作    者   :s00217060
      修改内容   :for cs_err_log
   10.日    期   : 2015年01月16日
      作    者   : f00179208
      修改内容   : DTS2015011311068:有些场景下没有将CS域的服务状态清除,导致CHR重复记录
   11.日    期   : 2015年1月28日
      作    者   : w00167002
      修改内容   : DTS2015011400748:在G下RL FAILURE，后FR,导致上下配合异常。修改为
                   G上报RRC_REL_CAUSE_G_RL_FAIL原因值，这样NAS就不发起CC 重建。
   12.日    期   : 2015年1月26日
      作    者   : z00161729
      修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E33(
    VOS_VOID                           *pRcvMsg                                /* 接收消息的头地址                         */
)
{
    RRMM_REL_IND_STRU                  *pRrmmRelInd;
    VOS_UINT8                           ucRrConnRelFlg;
    VOS_UINT32                          ucEmergencyLauFlg;
#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT8                           ucCsServiceConnStatusFlg;
#endif

    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    ucRrConnRelFlg = MM_TRUE;

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            NAS_MML_SetCsEmergencyServiceFlg(VOS_FALSE);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);

        }

#if (FEATURE_ON == FEATURE_PTM)
        ucCsServiceConnStatusFlg = NAS_MML_GetCsServiceConnStatusFlg();
        /* MT的场景且非CSFB MT则记录异常 */
        if ((NAS_ERR_LOG_CSFB_MT_STATE_NULL == NAS_MML_GetCsfbMtCurrState())
         && (VOS_TRUE == ucCsServiceConnStatusFlg))
        {
            /* 收到CS PAGING后连接建立成功，但还未收到业务消息，收到底层释放指示的异常记录 */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_RELEASED);
        }

        /* 在CSFB MT保护定时器超时状态下收到REL IND，清除CSFB的状态信息 */
        if (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_ClearErrorLogInfo();
        }
#endif

        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;
        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
            case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
            case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
            case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
            case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
            case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
            case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
            case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
            case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
            case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
            case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
            case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
            case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
            case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
            case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
            case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
            case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
            case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
            case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
            case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
            case RRC_REL_CAUSE_RLC_ERROR:
            case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
            case RRC_REL_CAUSE_T314_EXPIRED:
            case RRC_REL_CAUSE_W_RL_FAIL:

            case RRC_REL_CAUSE_G_RL_FAIL:



                Mm_TimerStop( MM_TIMER_T3240 );
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

                /*根据协议4.7.5.1.4，ATTACH或者RAU拒绝原因值为15不发起LAU*/
                if (( (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == g_MmGlobalInfo.usCauseVal)
                    || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == g_MmGlobalInfo.usCauseVal))
                 && (  (MM_GMM_RAU_PROC                       == g_MmGlobalInfo.ucProc)
                    || (MM_GMM_ATTACH_PROC                    == g_MmGlobalInfo.ucProc) )
                 && (MM_NORMAL_SERVICE                        == g_MmGlobalInfo.ucMmServiceState) )
                {
                    /* 对比标杆:在PS注册失败#15时,不影响CS的注册过程.
                       当PS先注册失败,CS注册成功时,MMC先删除禁止LAI,然后PS域再发起一次注册,最终结果是当前的LAI加入禁止LAI列表中 */
                    /*Mm_ComProcCauseProcess中将全局变量g_MmGlobalInfo.ucProc和
                      g_MmGlobalInfo.ucCauseVal清除*/
                    /* Mm_ComProcCauseProcess(); */
                    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
                    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
                    Mm_ComProcCauseProcess_Handling_LU_PROC();
                }
                else
                {
                    Mm_ComProcCauseProcess();

                    /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                       判断如果当前有PS业务，需要发起LAU */
                    if ( VOS_TRUE == ucEmergencyLauFlg )
                    {
                        /* 发起LAU */
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                        Mm_ComLuOnly();

                        NAS_MM_UpdateCsServiceConnStatusFlg();

                        return ;
                    }

                    if ((MM_TRUE == Mm_ComChkLu())
                      || (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING ==
                                                g_MmGlobalInfo.ucState))
                    {
                        NAS_MM_UpdateCsServiceConnStatusFlg();

                        return;
                    }
                }

                /*不做LAU或者已发起LAU进行如下处理:*/

                (VOS_VOID)NAS_MM_NotifyBufferedServiceRRConnNotExist();

                Mm_ComCheckDelayMmConn(MM_FALSE);

                NAS_MM_UpdateCsServiceConnStatusFlg();

                /*没有缓存业务存在时,如果服务域设置为PS ONLY需要Detach CS*/
                Mm_ComCheckDelayDetach();

                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E33:WARNING: ulRelCause Abnormal");
                break;
        }
    }

    return;
}
/*****************************************************************************
 函 数 名  :  Mm_Cell_S12_E33
 功能描述  : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下
             收到RRMM_REL_IND的处理,此种情况认为AS异常,释放掉所有的MM连接
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2007年9月29日
    作    者   : luojian id:107747
    修改内容   : 新生成函数,根据问题单号 A32D12966

  2.日    期   : 2010年4月30日
    作    者   : o00132663
    修改内容   : AT2D19011,G下在呼叫建链过程中，小区重选，网络模式I,MM未发送-

 3.日    期   : 2012年2月28日
   作    者   : w00176964
   修改内容   : DTS2012021405430:W下注册PS被拒15，CS注册未完成被网测释放RRC连接，
                后续在W下注册成功后，异常清除了LAC信息，导致在收到新的系统消息异
                常发起了LAU
 4.日    期   : 2012年10月29日
   作    者   : z00161729
   修改内容   : DTS2012083102536:支持cc呼叫重建
 5.日    期   : 2012年12月11日
   作    者   : l00167671
   修改内容   : DTS2012121802573, TQE清理

 6.日    期   : 2013年6月6日
   作    者   : w00167002
   修改内容   : V9R1_SVLTE:CS未注册下，当前有PS业务，紧急呼后链接释放，需要发起LAU。
 7.日    期   : 2013年8月28日
   作    者   : l65478
   修改内容   : DTS2013082607368:限制驻留在禁止的网络上,CS业务结束后发起了LU
 8.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容   :DTS2013082903019:支持ss重发功能
 9.日    期   :2014年01月09日
   作    者   :l65478
   修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
10.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log

*****************************************************************************/
VOS_VOID    Mm_Cell_S12_E33(VOS_VOID *pRcvMsg )
{
    VOS_UINT8                           ucValidFlg;

    RRMM_REL_IND_STRU                  *pstRelMsg  = VOS_NULL_PTR;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;

#if (FEATURE_ON == FEATURE_PTM)
    VOS_UINT8                           ucCsServiceConnStatusFlg;
#endif

    pstRelMsg = (RRMM_REL_IND_STRU *)pRcvMsg;

    ucValidFlg = Mm_RcvRrcRelInd(pRcvMsg);

    ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

    NAS_MM_ClearAuthInfo();

    enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pstRelMsg->ulRelCause);


    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if (MM_TRUE == ucValidFlg)
    {
        /* 停止保护定时器 */
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);
        /* 通知MMC连接不存在 */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

        /* 记录迁移之前的状态  */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;
        /* 状态迁移   */
        Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);

        /* 如果是在MM连接建立过程中发生LAI改变，不需要释放所有MM连接,正在建的MM连接 */
        if(VOS_FALSE == g_MmGlobalInfo.ucPendingLu)
        {
            Mm_ComRelAllMmConn(enMmCcRelCause);
        }

        /* 处理缓存的LU流程 */


        /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                   判断如果当前有PS业务，需要发起LAU */
        if ( VOS_TRUE == ucEmergencyLauFlg )
        {
            /* 发起LAU */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;    /* 设置LU类型                               */
            Mm_ComLuOnly();

            return ;
        }

        if (MM_FALSE == Mm_ComChkLu())
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E33:WARNING: Mm_ComChkLu return MM_FALSE\n");
        }

        g_MmGlobalInfo.ucPendingLu = VOS_FALSE;

#if (FEATURE_ON == FEATURE_PTM)
        ucCsServiceConnStatusFlg = NAS_MML_GetCsServiceConnStatusFlg();
        /* 收到CS PAGING后连接建立时收到底层释放指示的异常记录 */
        if ((NAS_ERR_LOG_CSFB_MT_STATE_NULL == NAS_MML_GetCsfbMtCurrState())
         && (VOS_TRUE == ucCsServiceConnStatusFlg))
        {
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_EST_RELEASED);
        }

        /* 在CSFB MT保护定时器超时状态下收到REL IND，清除CSFB的状态信息 */
        if (NAS_ERR_LOG_BASE_STATE_CSFB_MT_TI_TIME_OUT_RCV_REL_IND == NAS_MML_GetCsfbMtCurrState())
        {
            NAS_MM_ClearErrorLogInfo();
        }
#endif

        Mm_ComCheckDelayDetach();

        /* 需要清除MM保存的GMM的cause值 */
        Mm_ComProcCauseClear();

    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E33:WARNING: ulRelCause Abnormal");
    }
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E33
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR EST_CNF)状态下
             收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
     2.  s46746     05-09-24  modify for HSS 4100 V200R001

     3.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的链接存在状态
     4.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     5.日    期   : 2013年6月6日
       作    者   : w00167002
       修改内容   : V9R1_SVLTE:CS未注册下，当前有PS业务，紧急呼后链接释放，需要发起LAU。
     6.日    期   : 2013年8月28日
       作    者   : l65478
       修改内容   : DTS2013082607368:限制驻留在禁止的网络上,CS业务结束后发起了LU
     7.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     8.日    期   :2014年01月09日
       作    者   :l65478
       修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
     9.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
    10.日    期   : 2015年1月28日
       作    者   : w00167002
       修改内容   : DTS2015011400748:在G下RL FAILURE，后FR,导致上下配合异常。修改为
                    G上报RRC_REL_CAUSE_G_RL_FAIL原因值，这样NAS就不发起CC 重建。
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E33(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* 循环计数变量                             */
    RRMM_REL_IND_STRU       *pRrmmRelInd    = VOS_NULL_PTR;
    VOS_UINT8                ucTiValidFlg   = MM_TRUE;
    VOS_UINT8                ucRrConnRelFlg = MM_TRUE;

    VOS_UINT32                          ucEmergencyLauFlg;

    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        ucEmergencyLauFlg = NAS_MM_IsEmergencyCallEndTrigLau();

        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;

        Mm_TimerStop( MM_TIMER_T3230 );                                         /* 停TIMER3230                              */
        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* 重建的MM连接                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {
                    /* 该TI的MM连接失效                         */
                    Mm_SndCcRelInd( i, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);       /* 通知CC,MM连接建立失败                    */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                    aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {
                    /* 该TI的MM连接失效                         */
                    Mm_SndCcRelInd( ( i + 8 ), NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComProcCauseProcess();


            /* CS未注册下，紧急呼过程中收到attach cs请求先回复attach结果，紧急呼结束链接释放后，
                   判断如果当前有PS业务，需要发起LAU */
            if ( VOS_TRUE == ucEmergencyLauFlg )
            {
                /* 发起LAU */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();

                return ;
            }

            if ( MM_FALSE == Mm_ComChkLu() )
            {
                if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                              .RcvXXEstReq.ucFlg)
                    ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                              .RcvXXEstReq.ucFlg)
                    ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                              .RcvXXEstReq.ucFlg))
                {
                    ucTiValidFlg = Mm_ComTiChk();
                    if ( MM_FALSE == ucTiValidFlg )
                    {
                        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
                        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                    }
                    else
                    {
                        Mm_ComSigRelForDelayMmConnRej();
                    }
                }
                else
                {
                    Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                /* WAIT FOR REESTABLISH(WAIT FOR EST_CNF)收到rel ind不再重拨 */
                NAS_MM_RelBufferedServiceEstReq(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_REEST_FAIL);
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E33:WARNING: ulRelCause Abnormal");
            break;
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E33
  FUNCTION : 在WAIT FOR ADDITIONAL OUTGOING MM CONNECTION状态下
             收到RRMM_REL_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
     2.  张志勇        2005.01.27  007037 for MM
     3.  s46746     05-09-24  modify for HSS 4100 V200R001

     4.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
     5.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     6.日    期   : 2013年6月8日
       作    者   : w00167002
       修改内容   : V9R1_SVLTE:处理缓存的CS去注册操作；
                    降全复杂度；
     7.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     8.日    期   :2014年01月09日
       作    者   :l65478
       修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
     9.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
    10.日    期   : 2015年1月28日
       作    者   : w00167002
       修改内容   : DTS2015011400748:在G下RL FAILURE，后FR,导致上下配合异常。修改为
                    G上报RRC_REL_CAUSE_G_RL_FAIL原因值，这样NAS就不发起CC 重建。
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E33(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                i = 0;                                             /* 循环计数变量                             */
    RRMM_REL_IND_STRU       *pRrmmRelInd;
    VOS_UINT8                ucTiValidFlg = MM_TRUE;
    VOS_UINT8                ucRrConnRelFlg = MM_TRUE;
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmCcRelCause;


    NAS_MM_ClearAuthInfo();

    /* 处理当前缓存的CS域去注册 */
    if ( (VOS_FALSE         == NAS_MM_IsNeedGmmProcUserDetach())
      && (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType & MM_WAIT_CS_DETACH)) )
    {
        /* 建链不成功，直接本地DETACH */
        NAS_MM_LocalDetach();

        return;
    }

    if ( MM_FALSE == Mm_RcvRrcRelInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        ucRrConnRelFlg = Mm_ComRrConnRelChk();
        if ( MM_TRUE == ucRrConnRelFlg )
        {
            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );                     /* RR连接不存在                             */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        }
        pRrmmRelInd = (RRMM_REL_IND_STRU*)pRcvMsg;
        Mm_TimerStop( MM_TIMER_T3230 );                                         /* 停TIMER3230                              */

        enMmCcRelCause  = NAS_MM_ConvertRrcRelCauseToMmCcRelCause(pRrmmRelInd->ulRelCause);


        switch ( pRrmmRelInd->ulRelCause )
        {                                                                       /* 原因值                                   */
        case RRC_REL_CAUSE_RL_FAILURE:                                          /* Radio Link Failure                       */
            NAS_MM_RelEstingMmConn(pRrmmRelInd->ulRelCause);

            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* 重建的MM连接                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndCcErrInd( i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );                                        /* 通知CC,MM连接失效                        */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndCcErrInd( i + 8, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );                                    /* 通知CC,MM连接失效                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndSsRelInd(i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);                                        /* 通知SS,MM连接失效                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndSsRelInd( i + 8, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE);                                    /* 通知SS,MM连接失效                        */

                }
                if ( MM_CONST_NUM_0 !=
                    (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndSmsRelInd( i, NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE );        /* 通知SS,MM连接失效                        */
                }
                if ( MM_CONST_NUM_0 !=
                    ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    aucMMConnExtFlg[1]  & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接失效                         */
                    Mm_SndSmsRelInd( (i + 8), NAS_MMCM_REL_CAUSE_RR_REL_RL_FAILURE ); /* 通知SS,MM连接失效                        */
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[0] =
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0];/* 记录需要重建的标志                       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnReestFlg[1] =
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1];/* 记录需要重建的标志                       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
                = MM_CONST_NUM_0;                                               /* 清除存在的MM连接标志                     */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            if ( ( MM_CONST_NUM_0 !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        aucMMConnReestFlg[0] )
                || ( MM_CONST_NUM_0 !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        aucMMConnReestFlg[1] )
                )
            {
                Mm_ComSetMmState(WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: STATUS is  WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ");
                Mm_TimerStart(MM_TIMER_PROTECT_CC);                             /* 启动保护TIMER                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                Mm_ComProcCauseProcess();
                if ( MM_FALSE == Mm_ComChkLu() )
                {
                    if ( ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                        RcvXXEstReq.ucFlg)
                        ||( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                        RcvXXEstReq.ucFlg)
                        ||( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                        RcvXXEstReq.ucFlg ) )
                    {
                        ucTiValidFlg = Mm_ComTiChk();
                        if ( MM_FALSE == ucTiValidFlg )
                        {
                            Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );     /* RR连接不存在                             */
                            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                        }
                        else
                        {
                            Mm_ComSigRelForDelayMmConnRej();
                        }
                    }
                    Mm_ComCheckDelayMmConn( MM_FALSE );

                    Mm_ComCheckDelayDetach();
                }
                else
                {
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                 NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                      /* 通知CC建立失败                           */

                    }
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                    }
                    if ( MM_TRUE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ucFlg )
                    {                                                           /* 有等待的CC触发的需要建立的MM连接         */
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                RcvXXEstReq.ucFlg = MM_FALSE;

                        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
                    }
                }
            }
            break;
        case RRC_REL_CAUSE_CONN_FAIL:                                           /* RR Connection Failure                    */
        case RRC_REL_CAUSE_NAS_REL_SUCCESS:                                     /* NAS Release Connection：Successful       */
        case RRC_REL_CAUSE_NAS_REL_ABSENT:                                      /* NAS Release Connection: Absent           */
        case RRC_REL_CAUSE_NAS_ABORT:                                           /* NAS : Abort                              */
        case RRC_REL_CAUSE_RR_NORM_EVENT:                                       /* Normal event                             */
        case RRC_REL_CAUSE_RR_UNSPEC:                                           /* Unspecified                              */
        case RRC_REL_CAUSE_RR_PRE_EMPT_REL:                                     /* Pre-emptive release                      */
        case RRC_REL_CAUSE_RR_CONGEST:                                          /* Congedtion                               */
        case RRC_REL_CAUSE_RR_RE_EST_REJ:                                       /* Re-establishment reject                  */
        case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:                             /* Directed signal conn re-establish        */
        case RRC_REL_CAUSE_RR_USER_INACT:                                       /* User inactive                            */
        case RRC_REL_CAUSE_UTRAN_RELEASE:                                       /* Signaling Connection Release             */
        case RRC_REL_CAUSE_NAS_STOP_SETUP:                                      /* NAS Stop connection setup                */
        case RRC_REL_CAUSE_NAS_DATA_ABSENT:                                     /* NAS Data Request: Connection Absent      */
        case RRC_REL_CAUSE_RRC_ERROR:                                           /* RRC处理异常: RRC ERROR                   */
        case RRC_REL_CAUSE_GAS_TIMEOUT:                                         /* GAS 超时引起 RR 释放 */
        case RRC_REL_CAUSE_OTHER_REASON:                                        /* 其它原因                                 */
        case RRC_REL_CAUSE_NO_RF:                                               /* 没有射频资源 */
        case RRC_REL_CAUSE_RLC_ERROR:
        case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
        case RRC_REL_CAUSE_T314_EXPIRED:
        case RRC_REL_CAUSE_W_RL_FAIL:

        case RRC_REL_CAUSE_G_RL_FAIL:

            Mm_ComRelAllMmConn(enMmCcRelCause);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E33:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComProcCauseProcess();
            if ( MM_FALSE == Mm_ComChkLu() )
            {
                if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC]
                              .RcvXXEstReq.ucFlg)
                    ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS]
                              .RcvXXEstReq.ucFlg)
                    ||(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                              .RcvXXEstReq.ucFlg))
                {
                    ucTiValidFlg = Mm_ComTiChk();
                    if ( MM_FALSE == ucTiValidFlg )
                    {
                        Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );         /* RR连接不存在                             */
                        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                    }
                    else
                    {
                        Mm_ComSigRelForDelayMmConnRej();
                    }
                }
                Mm_ComCheckDelayMmConn( MM_FALSE );

                Mm_ComCheckDelayDetach();
            }
            else
            {
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                             NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);                          /* 通知CC建立失败                           */
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSmsRelInd(
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                        .RcvXXEstReq.ulTransactionId,
                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
                }
                if ( MM_TRUE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg )
                {                                                               /* 有等待的CC触发的需要建立的MM连接         */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                            RcvXXEstReq.ucFlg = MM_FALSE;

                    Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST );
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S16_E33:WARNING: ulRelCause Abnormal");
            break;
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E34
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_SECURITY_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11    新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
     3.日    期   :2013年9月14日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     4.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E34(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if (( RRC_SECURITY_CS_SMC_CMPL == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
            && ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState))
        {
            Mm_TimerStop( MM_TIMER_T3212 );                                     /* 停T3212                                  */
        }
        if ( RRC_SECURITY_CS_SMC_CMPL == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
        {                                                                       /* 完整性保护和安全模式启动                 */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停TIMER3230                              */
            switch ( g_MmGlobalInfo.ucMMConnEstingPD )
            {                                                                   /* 确定是哪个PD建立的MM连接                 */
            case MM_IE_PD_CALL_CONTROL:                                         /* CC要求建立的MM连接                       */
                Mm_SndCcEstCnf(
                    (VOS_UINT32)( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                        ucMMConnEstingTI), MMCC_EST_SUCCESS );  /* 该MM连接建立成功                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
                {                                                               /*TI小于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[0] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[0] |
                        (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucMMConnEstingTI ) );                                   /* 设置MM连接存在标志                       */
                }
                else
                {                                                               /*TI大于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    aucMMConnExtFlg[1] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[1] |
                        (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucMMConnEstingTI - 8 )) );                              /* 设置MM连接存在标志                       */
                }
                /*lint +e701*/
                /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
                /* 处理eCall定时器启动标识 */
                NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
                /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* 清除正在建立的MM连接的标志               */
                break;
            case MM_IE_PD_SMS_MSG:                                              /* SMS要求建立的MM连接                      */
                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())      /* 在GSM网络中短消息主叫需要建立SAPI3       */
                {
                    if (MM_MO_PAGING == g_MmGlobalInfo.ucPagingType)            /* 主叫 */
                    {
                        if (MM_FALSE == MM_SndSapi3EstReq())
                        {
                            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL);

                            Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                            NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                                        "Mm_Cell_S9_E34: ERROR: snd SAPI3 est fail.");

                            g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;       /* 设置没有正在建立的连接           */

                            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

                            g_MmGlobalInfo.ucPagingType     = MM_NO_PAGING;

                            return;
                        }

                        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

                        g_MmGlobalInfo.ucPagingType = MM_NO_PAGING;

                        return;
                    }
                }

                Mm_SndSmsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    ucMMConnEstingTI );                                         /* 该MM连接建立成功                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
                {                                                               /*TI小于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        aucMMConnExtFlg[0] |=
                        (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI );                                     /* 设置MM连接存在标志                       */
                }
                else
                {                                                               /*TI大于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        aucMMConnExtFlg[1] |= (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                        ucMMConnEstingTI - 8 ) );                               /* 设置MM连接存在标志                       */
                }
                /*lint +e701*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* 清除正在建立的MM连接的标志               */
                break;
            case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                  /* SS要求建立的MM连接                       */
                Mm_SndSsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI, MMSS_EST_SUCCESS );                       /* 该MM连接建立成功                         */
                /*lint -e701*/
                if ( MM_CONST_NUM_7 >
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
                {                                                               /*TI小于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        aucMMConnExtFlg[0]
                     |= (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        ucMMConnEstingTI );                                     /* 设置MM连接存在标志                       */
                }
                else
                {                                                               /*TI大于7                                   */
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        aucMMConnExtFlg[1] |= (VOS_UINT8)( 0x01 <<
                        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                        ucMMConnEstingTI - 8 ) );                               /* 设置MM连接存在标志                       */
                }
                /*lint +e701*/
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                    = NO_MM_CONN_ESTING;                                        /* 清除正在建立的MM连接的标志               */
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E34:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
                break;
            }
            g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                /* 设置没有正在建立的连接                   */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E34:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }
        else if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            && ((RR_SYN_TCH == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
                 ||(RR_SYN_TCH_MODIFY == g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)))
        {
            if (g_RrMmSyncInd.ulRabCnt > 0)
            {
                Mm_SndCcSyncInd();                                                      /* 向CC指示专有信道已经分配或改变           */
            }
        }
        else
        {
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E34
  FUNCTION : 在MM CONNECTION ACTIVE状态下
             收到RRMM_SECURITY_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E34(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        NAS_LOG(WUEPS_PID_MM, MM_ORIGIN, PS_LOG_LEVEL_WARNING,
                "Mm_Cell_S10_E34: WARNING: Receive RR Security false.");

        return;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        if ((MM_CONNECTION_ACTIVE == g_MmGlobalInfo.ucState) || (WAIT_FOR_NETWORK_COMMAND == g_MmGlobalInfo.ucState))
        {
            if (g_RrMmSyncInd.ulRabCnt > 0)
            {
                Mm_SndCcSyncInd();                                                      /* 向CC指示专有信道已经分配或改变           */
            }
        }
    }
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S14_E34
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR EST_CNF)状态下
             收到RRMM_SECURITY_IND的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
     2. 日    期   : 2006年12月5日
        作    者   : luojian 60022475
        修改内容   : Maps3000接口修改
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E34(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* 循环计数变量                             */

    if ( MM_FALSE == Mm_RcvRrcSecurityInd(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        /* WUEPS_ASSERT(0); */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if (RRC_SECURITY_CS_SMC_CMPL ==
                    g_MmGlobalInfo.CsSecutityInfo.ucSecurityType)
        {                                                                       /* 完整性保护和安全模式启动                 */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停TIMER3230                              */
            for ( i = 0; i < MM_CONST_NUM_7; i++ )
            {                                                                   /* 重建的MM连接                             */
                /*lint -e701*/
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[0] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接重建成功                     */
                    Mm_SndCcReestCnf( i, MMCC_REEST_SUCCESS );                  /* 通知CC,MM连接重建成功                    */
                }
                if ( MM_CONST_NUM_0 !=
                ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                aucMMConnExtFlg[1] & ( 0x01 << i ) ) )
                {                                                               /* 该TI的MM连接重建成功                     */
                    Mm_SndCcReestCnf( ( i + 8 ), MMCC_REEST_SUCCESS );          /* 通知CC,MM连接重建成功                    */
                }
                /*lint +e701*/
            }
            g_MmGlobalInfo.ucPreState  = g_MmGlobalInfo.ucState;                /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E34:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */

            /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            /* 处理eCall定时器启动标识 */
            NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
            /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
        }
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E35
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到RRMM_SYNC_IND的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
     2. 日    期   : 2007年02月16日
        作    者   : luojian 60022475
        修改内容   : 3000接口修改
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E35(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvRrcSyncInd(pRcvMsg) )
    {
        return;
    }

    Mm_SndCcSyncInd();                                                      /* 向CC指示专有信道已经分配或改变           */
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E36
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(AUTHENTICATION REQUEST)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E36(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REQ,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }
    Mm_ComAuthenRcvAuthenReq();                                                 /* 收到AUTHEN REQ的处理                     */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E37
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(AUTHENTICATION REJECT)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.  张志勇      03-12-11    新版作成
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2011年10月8日
    作    者   : z00161729
    修改内容   : V7R1 PhaseII EPLMN/RPLMN由MM/GMM维护修改
  4.日    期   : 2011年04月23日
    作    者   : f00179208
    修改内容   : 问题单号：DTS2011032903294,[出服务区】【非闪电卡】出服务区再回原小区，UE只是重启了T3212，但是没有发起LAU
  5.日    期   : 2015年6月8日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E37(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8       ucCause;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */

    /* 24008_CR1942R3_(Rel-11)_C1-114725 24008 4.3.2.5章节描述如下:
    If the AUTHENTICATION REJECT message is received in any other state the mobile station shall
    abort any MM specific, MM connection establishment or call re-establishment procedure,
    stop any of the timers T3210, or T3230, T3214 or T3216 (if they were running),
    release all MM connections (if any), start timer T3240 and enter the state WAIT FOR NETWORK COMMAND,
    expecting the release of the RR connection. */
    Mm_TimerStop(MM_TIMER_T3214);
    Mm_TimerStop(MM_TIMER_T3216);

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_AUTH_REJECT,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    if (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);    }

    Mm_ComAuthenRcvAuthenRej();                                                 /* 收到AUTHEN REJ的处理                     */

    NAS_MM_SndGmmAuthFailInd();

    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E38
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(IDENTITY REQUEST)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E38(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    Mm_ComIdentity();                                                           /* IDENTITY过程的处理                       */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E39
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(TMSI REALLOCATION COMMAND)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E39(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    Mm_ComTmsiReloc();                                                          /* TMSI RELOC过程                           */

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E40
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(CM SERVICE ACCEPT)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的链接存在状态
     3.日    期   :2013年9月14日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     4.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E40(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    Mm_TimerStop( MM_TIMER_T3230 );                                             /* 停TIMER3230                              */
    switch ( g_MmGlobalInfo.ucMMConnEstingPD )
    {                                                                           /* 确定是哪个PD建立的MM连接                 */
    case MM_IE_PD_CALL_CONTROL:                                                 /* CC要求建立的MM连接                       */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI )
        {                                                                       /*TI小于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
                        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        aucMMConnExtFlg[0] |
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI ) );                                           /* 设置MM连接存在标志                       */
        }
        else
        {                                                                       /*TI大于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
                (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
                 | (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucMMConnEstingTI - 8 ) ) );                                     /* 设置MM连接存在标志                       */
        }
        /*lint +e701*/
        Mm_SndCcEstCnf( (VOS_UINT32)(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
            ucMMConnEstingTI), MMCC_EST_SUCCESS );                               /* 该MM连接建立成功                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* 清除正在建立的MM连接的标志               */

        /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        /* 处理eCall定时器启动标识 */
        NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
        /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */
        break;
    case MM_IE_PD_SMS_MSG:                                                      /* SMS要求建立的MM连接                      */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())              /* 在GSM网络中短消息主叫需要建立SAPI3       */
        {
            if (MM_MO_PAGING == g_MmGlobalInfo.ucPagingType)                    /* 主叫 */
            {
                if (MM_FALSE == MM_SndSapi3EstReq())
                {
                    Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                        NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL);

                    Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
                    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                                        "Mm_Cell_S9_E40: ERROR: snd SAPI3 est fail.");

                    g_MmGlobalInfo.ucMMConnEstingPD         = NO_MM_CONN_ESTING; /* 设置没有正在建立的连接           */

                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                                        = NO_MM_CONN_ESTING;

                    g_MmGlobalInfo.ucPagingType             = MM_NO_PAGING;

                    return;
                }

                Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);

                g_MmGlobalInfo.ucPagingType = MM_NO_PAGING;

                return;
            }
        }
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI )
        {                                                                       /*TI小于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI ) ;                                            /* 设置MM连接存在标志                       */
        }
        else
        {                                                                       /*TI大于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                ucMMConnEstingTI - 8 ) );                                       /* 设置MM连接存在标志                       */
        }
        /*lint +e701*/
        Mm_SndSmsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
            ucMMConnEstingTI);                                                  /* 该MM连接建立成功                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* 清除正在建立的MM连接的标志               */
        break;
    case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SS要求建立的MM连接                       */
        /*lint -e701*/
        if ( MM_CONST_NUM_7 > g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI )
        {                                                                       /*TI小于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
                (VOS_UINT8)( 0x01 << g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                ucMMConnEstingTI );                                             /* 设置MM连接存在标志                       */
        }
        else
        {                                                                       /*TI大于7                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                ucMMConnEstingTI - 8 ) );                                       /* 设置MM连接存在标志                       */
        }
        /*lint +e701*/
        Mm_SndSsEstCnf( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
            ucMMConnEstingTI, MMSS_EST_SUCCESS );                               /* 该MM连接建立成功                         */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
            = NO_MM_CONN_ESTING;                                                /* 清除正在建立的MM连接的标志               */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E40:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
        break;
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* 设置没有正在建立的连接                   */
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                       /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E40:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
    Mm_ComCheckDelayMmConn( MM_FALSE );                                         /* 检查是否有保留的需要建立的MM连接         */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcCmServiceRej_CcExist
 功能描述  : CC业务存在时收到CM SERVICE REJ的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月19日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ProcCmServiceRej_CcExist( VOS_VOID )
{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* 原因值4时，缓存CM层业务，等待Lu完成后重新发起CM业务 */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* 原因值22时，通知CC业务失败，区分是否携带T3246，携带T3246时不需要重拨 */
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

            if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
            {
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

            }
            else
            {
                Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
            }


            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

            break;

        /* 其他原因值 */
        default:

            Mm_SndCcRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));                /* 通知CC,MM连接建立失败                    */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcCmServiceRej_SsExist
 功能描述  : SS业务存在时收到CM SERVICE REJ的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月19日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ProcCmServiceRej_SsExist( VOS_VOID )
{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* 原因值4时，缓存CM层业务，等待Lu完成后重新发起CM业务 */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* 原因值22时，通知CC业务失败，区分是否携带T3246，携带T3246时不需要重拨 */
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

            if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
            {
                Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

            }
            else
            {
                Mm_SndSsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                    ucMMConnEstingTI,
                    NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
            }


            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

            break;

         /* 其他原因值 */
         default:

            Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                           (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI           /* 清除正在建立MM连接的标志 */
                = NO_MM_CONN_ESTING;

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcCmServiceRej_SmsExist
 功能描述  : SMS业务存在时收到CM SERVICE REJ的处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月19日
    作    者   : n00355355
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_MM_ProcCmServiceRej_SmsExist( VOS_VOID )


{
    switch(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {
        /* 原因值4时，缓存CM层业务，等待Lu完成后重新发起CM业务 */
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            break;

        /* 原因值22时，通知CC业务失败，区分是否携带T3246，携带T3246时不需要重拨 */
         case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:

             if (VOS_TRUE == g_MmMsgCmSvcRjct.ucIsCmSrvRejCongestionWithT3246)
             {
                 Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                     NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246);           /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION_WITH_T3246 */

             }
             else
             {
                 Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                     NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);                      /* 通知CC,MM连接建立失败:NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION */
             }


             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                 = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

             break;

        /* 其他原因值 */
         default:

             Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));

             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
                = NO_MM_CONN_ESTING;                                                /* 清除正在建立MM连接的标志 */

             break;
    }

    return;
}


/*******************************************************************************
  MODULE   : Mm_Cell_S9_E41
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(CM SERVICE REJECT)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      03-12-11  新版作成
  2.日    期   : 2006年10月8日
    作    者   : luojian id:60022475
    修改内容   : OSA优化过程中遗漏了A32D05845问题单的修改,现补上
                 问题单号:A32D06583

  3.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 更新MML_CTX中的业务存在状态
  4.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  6.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  7.日    期   :2013年9月14日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  8.日    期   : 2014年4月1日
    作    者   : z00161729
    修改内容   : DTS2014040300125:service 被拒和网络detach ind被拒需要上报^rejinfo
  9.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log

*******************************************************************************/
VOS_VOID Mm_Cell_S9_E41(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                        /* 停T3212                                  */
    }
    Mm_TimerStop( MM_TIMER_T3230 );                                             /* 停MM_TIMER_T3230                         */

    switch ( g_MmGlobalInfo.ucMMConnEstingPD )
    {                                                                           /* 确定是哪个PD建立的MM连接                 */
    case MM_IE_PD_CALL_CONTROL:                                                 /* CC要求建立的MM连接                       */

        NAS_MM_ProcCmServiceRej_CcExist();

        break;

    case MM_IE_PD_NON_CALL_RLT_SS_MSG:                                          /* SS要求建立的MM连接                       */

        NAS_MM_ProcCmServiceRej_SsExist();

        break;

    case MM_IE_PD_SMS_MSG:                                                      /* SMS要求建立的MM连接                      */

        NAS_MM_ProcCmServiceRej_SmsExist();

        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S9_E41:WARNING: g_MmGlobalInfo.ucMMConnEstingPD Abnormal");
        break;
    }

    Mm_SndMmcCmSvcRejInd( g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause );

    switch (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {                                                                           /* 拒绝原因值                               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:                                      /* 拒绝原因值#4                             */
        Mm_ComRejectCause4();                                                   /* 拒绝原因值#4的公共处理                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* 拒绝原因值#6                             */
        Mm_ComRejectCause6();                                                   /* 拒绝原因值#6的公共处理                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_NOT_SUPPORT:
    case NAS_MML_REG_FAIL_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
        if ( ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 记录要进入的状态                         */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart( MM_TIMER_T3240 );                                    /* 启动TIMER3240                            */
        }
        else
        {
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }

        break;
    default:
        if ( ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] )
            && ( MM_CONST_NUM_0 ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] ) )
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 记录要进入的状态                         */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart( MM_TIMER_T3240 );                                    /* 启动TIMER3240                            */
        }
        else
        {
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E41:NORMAL: STATUS is  MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );                                 /* 检查是否有保留的需要建立的MM连接         */
        }

        break;
    }
    g_MmGlobalInfo.ucMMConnEstingPD = NO_MM_CONN_ESTING;                        /* 设置没有正在建立的连接                   */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S14_E41
  FUNCTION : 在WAIT FOR REESTABLISH（WAIT FOR EST_CNF）状态下
             收到RRMM_DATA_IND(CM SERVICE REJECT)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      03-12-11  新版作成

  2.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 更新MML_CTX中的链接存在状态
  3.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  6.日    期   :2013年9月14日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
  7.日    期   : 2014年4月1日
    作    者   : z00161729
    修改内容   : DTS2014040300125:service 被拒和网络detach ind被拒需要上报^rejinfo
  8.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E41(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* 循环计数变量                             */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    Mm_TimerStop( MM_TIMER_T3230 );                                             /* 停MM_TIMER_T3230                         */

    for ( i = 0; i < MM_CONST_NUM_7; i++ )
    {                                                                           /* 重建的MM连接                             */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << i ) ) )
        {
            Mm_SndCcRelInd( i, (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));             /* 通知CC,MM连接建立失败                    */
        }
        if ( MM_CONST_NUM_0 !=
        ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << i ) ) )
        {
            Mm_SndCcRelInd( ( i + 8 ), (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause + NAS_MMCM_REL_CAUSE_CM_SRV_REJ_BEGIN));                            /* 通知CC,MM连接建立失败                    */
        }
        /*lint +e701*/
    }

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
        = MM_CONST_NUM_0;                                                       /* 清除存在的MM连接标志                     */
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
        = MM_CONST_NUM_0;                                                       /* 清除存在的MM连接标志                     */

    Mm_SndMmcCmSvcRejInd(g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause);

    switch (g_MmMsgCmSvcRjct.MmIeRejCause.ucRejCause)
    {                                                                           /* 拒绝原因值                               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR:                                      /* 拒绝原因值#4                             */
        Mm_ComRejectCause4();                                                   /* 拒绝原因值#4的公共处理                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* 拒绝原因值#6                             */
        Mm_ComRejectCause6();                                                   /* 拒绝原因值#6的公共处理                   */


        if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
         && (NAS_MML_NET_MODE_I == pstCampPlmnInfo->enNetworkMode))
        {
            NAS_MM_SndGmmCmSvcRejInd(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR );
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_NOT_SUPPORT:
    case NAS_MML_REG_FAIL_CAUSE_REQ_SERV_OPT_NOT_SUBSCRIBE:
    case NAS_MML_REG_FAIL_CAUSE_SERV_OPT_OUT_OF_ORDER:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
        g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
            g_MmGlobalInfo.ucStaOfRcvXXEstReq;                                  /* 记录要进入的状态                         */
        Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );        /* MM连接流程                               */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E41:NORMAL: STATUS is  WAIT_FOR_NETWORK_COMMAND");
        Mm_TimerStart( MM_TIMER_T3240 );                                        /* 启动TIMER3240                            */
        break;
    default:
        break;
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E42
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(ABORT)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11    新版作成
     2.日    期   : 2012年7月12日
       作    者   : s00217060
       修改内容   : 拒绝原因值#6,#17时，通知MMC Abort消息

*******************************************************************************/
VOS_VOID Mm_Cell_S9_E42(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }
    Mm_TimerStop( MM_TIMER_T3230 );                                             /* 停T3212                                  */

    switch (g_MmMsgAbort.MmIeRejCause.ucRejCause )
    {                                                                           /* 拒绝原因值                               */
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* 拒绝原因值#6                             */
        Mm_ComAbortCause6();                                                    /* 拒绝原因值#6的公共处理                   */
        /* 通知MMC */
        NAS_MM_SndMmcAbortInd(NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME);
        break;
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:                                          /* 拒绝原因值#17                            */

#if (FEATURE_ON == FEATURE_PTM)
        /* MT的场景， 该标记为TRUE时为MT */
        if (VOS_TRUE == NAS_MML_GetCsServiceConnStatusFlg())
        {
            /* 收到CS PAGING后连接建立成功，但还未收到业务消息，收到网络ABORT的异常记录 */
            NAS_MM_CsPagingFailRecord(NAS_ERR_LOG_CS_PAGING_CAUSE_CONN_ABORT);
        }
#endif

        Mm_ComAbortCause17();                                                   /* 拒绝原因值#17的公共处理                  */
        /* 通知MMC */
        NAS_MM_SndMmcAbortInd(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE);
        break;
    default:
        break;
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E43
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND(MM INFORMATION)的处理
  INPUT    : VOS_VOID
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-11    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E43(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    Mm_ComInfo();                                                               /* MM INFO过程的处理                        */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E50
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND( CM Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-12  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的链接存在状态

*******************************************************************************/
VOS_VOID Mm_Cell_S9_E50(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8           ucTI = 0;                                               /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8          *pucCMMsg = VOS_NULL_PTR;                                /* 指针类型转换                             */
    VOS_UINT8          *pucBakCMMsg = VOS_NULL_PTR;

    if ( MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState )
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                               VOS_MEMPOOL_INDEX_MM,
                               pRrDataInd->RcvNasMsg.ulNasMsgSize,
                               WUEPS_MEM_NO_WAIT);                                  /* 申请内存                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0,
        sizeof( VOS_UINT8 ) * pRrDataInd->RcvNasMsg.ulNasMsgSize );                 /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到CC消息中的TI                         */
    if ( ( MM_CONST_NUM_7 == ucTI ) || ( MM_CONST_NUM_15 == ucTI ) )
    {                                                                           /* TIO = 111                                */
        Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* 向CC发送MMCC_EST_IND                     */
    }
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向CC发送MMCC_DATA_IND                    */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndCcEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向CC发送MMCC_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* 设置已经存在的MM连接的标志位             */

            /* BEGIN: Modified by 欧阳飞  ID: 00132663, 2008/8/26   PN:AT2D05317*/
            /* 目前有两种状态会调用该函数
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                统一状态变迁到 WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION */
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E50:NORMAL: STATUS is  WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */
            /* END:   Modified by 欧阳飞  ID: 00132663, 2008/8/26 */
        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* CC建立的MM连接                           */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndCcDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向CC发送MMCC_DATA_IND                    */
        }
        /*lint +e701*/

    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* 释放申请的消息                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S0_E1
  Function: MM_NULL 状态,收到 MMCMM_START_REQ 原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.09   新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}
/*******************************************************************************
  Module:   Mm_Cell_S1_E1
  Function: MM_IDLE_NO_CELL_AVAILABLE 状态,收到 MMCMM_START_REQ 原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇   2003.12.09   新版作成
  2.s46746     05-09-27  modify for HSS 4100 V200R001
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   :2013年9月14日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
  7.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}
/*******************************************************************************
  Module:   Mm_Cell_S1_E3
  Function: MM_IDLE_NO_CELL_AVAILABLE 状态,收到 MMCMM_PLMN_SEARCH_INITIATED
            原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇   2003.12.09   新版作成
      2.  s46746     05-09-27  modify for HSS 4100 V200R001
      3.日    期   : 2008年12月1日
        作    者   : o00132663
        修改内容   : AT2D07041, 在用户发起的LIST搜网，或者HPLMN搜网时，CREG,CGREG暂停上报。
      4.日    期   : 2011年12月7日
        作    者   : w00176964
        修改内容   : V7R1 PhaseIV 调整:RRC链接调整
      5.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
      6.日    期   : 2013年10月15日
        作    者   : l65478
        修改内容   : DTS2013102501008从收到搜网模式设置成自动搜网模式后没有发起注册
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E3(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    if (MM_TRUE == Mm_RcvMmcPlmnSrchIni(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */

        /* 保存出服务区前的状态,在搜网成功后用于判断LAI是否改变 */
        if ((MM_IDLE_NO_CELL_AVAILABLE != g_MmGlobalInfo.ucState)
         && (MM_IDLE_PLMN_SEARCH       != g_MmGlobalInfo.ucState))
        {
            g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;
        }

        Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E3:NORMAL: STATUS is MM_IDLE_PLMN_SEARCH");
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E6
  Function: MM_IDLE_NORMAL_SERVICE 状态,收到 GMMMM_COMBINED_ATTACH_INITIATION
            原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇   2003.12.09   新版作成
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  3.日    期   : 2008年11月22日
    作    者   : o00132663
    修改内容   : 问题单号：AT2D06931, 清除标志位ucT3212ExpiredFlg
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2012年2月15日
    作    者   : z00161729
    修改内容   : V7R1C50 支持CSFB/ISR特性修改
  6. 日    期   : 2012年06月1日
     作    者   : z00161729
     修改内容   : V7R1C50 GUL背景搜修改，L下开机联合注册eps only成功，cs处于未attach态，
                   bg搜高优先级网络成功，快速指定搜成功，网络注册过程syscfg设置ps
                   only,mm直接回复detach cnf和cs reg result ind迁到limit service状态，
                   后面再收到联合注册init消息不应迁状态

  7.日    期   : 2012年12月22日
    作    者   : l65478
    修改内容   : DTS2012122103936 发起紧急呼叫时MM状态迁移错误
  8.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  9.日    期   : 2013年7月25日
    作    者   : w00242748
    修改内容   : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                 网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                 rau req中带follow on标志,无明确协议依据
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E6(
                    VOS_VOID     *pMsg                                              /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvGmmCombinedAttachIni(pMsg))
    {

        NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);



        if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        {
            return;
        }

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(LOCATION_UPDATING_PENDING);

        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E6:NORMAL: STATUS is LOCATION_UPDATING_PENDING");
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E1
  Function: WAIT_FOR_OUTGOING_MM_CONNECTION 状态,收到 MMCMM_START_REQ 原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇   2003.12.09   新版作成
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   :2013年9月14日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
  7.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E1(
                    VOS_VOID     *pMsg                                              /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* 停timer 3230                             */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S9_E4 */


/*******************************************************************************
  Module:   Mm_Cell_S10_E1
  Function: MM_CONNECTION_ACTIVE 状态,收到 MMCMM_START_REQ 原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇   2003.12.09   新版作成
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   :2013年9月14日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  7.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E1(
                    VOS_VOID     *pMsg                                              /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S10_E4 */

/*******************************************************************************
  Module:   Mm_Cell_S11_E1
  Function: WAIT_FOR_NETWORK_COMMAND 状态,收到 MMCMM_START_REQ 原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇   2003.12.09   新版作成
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  2.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  3.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  4.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
  5.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3240].ucTimerStatus)
        {                                                                       /* 如果timer 3240正在运行,则停止            */
            Mm_TimerStop(MM_TIMER_T3240);                                       /* 停timer 3240                             */
        }
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S11_E4 */


/*******************************************************************************
  Module:   Mm_Cell_S12_E1
  Function: WAIT_FOR_RR_CONNECTION_MM_CONNECTION 状态,收到 MMCMM_START_REQ
            原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇   2003.12.09   新版作成
  2.  张志勇        2005.01.27  007037 for MM
  3.  s46746     05-09-27  modify for HSS 4100 V200R001
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  6.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  8.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E1:NORMAL: STATUS is  MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S12_E4 */

/*******************************************************************************
  Module:   Mm_Cell_S13_E1
  Function: WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ 状态,收到 MMCMM_START_REQ
            原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇   2003.12.09   新版作成
  2.  张志勇        2005.01.27  007037 for MM
  3.  s46746     05-09-27  modify for HSS 4100 V200R001
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  7.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  8.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  9.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S13_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}
/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S13_E4 */

/*******************************************************************************
  Module:   Mm_Cell_S14_E1
  Function: WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF 状态,收到 MMCMM_START_REQ 原语
            的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇   2003.12.09   新版作成
  2.  张志勇        2005.01.27  007037 for MM
  3.  s46746     05-09-27  modify for HSS 4100 V200R001
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  6.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  7.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  8.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                              /* 启动保护TIMER                            */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );
        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S14_E4 */

/*******************************************************************************
  Module:   Mm_Cell_S16_E1
  Function: WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION 状态,收到 MMCMM_START_REQ
            原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇   2003.12.09   新版作成
  2.  s46746     05-09-27  modify for HSS 4100 V200R001
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  6.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  7.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E1(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcStartReq(pMsg))
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* 停timer 3230                             */

        Mm_SndRrRelReq(RRC_CELL_UNBARRED);



        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_STATE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E1:NORMAL: STATUS is MM_STATE_NULL");

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComNasInfoSav(
                MM_STATUS_DETACHED,
                NAS_MML_GetSimCsSecurityCksn()
                );

        Mm_ComInit();                                                           /* 全局变量初始化                           */
        Mm_ComStart();                                                          /* 调用收到MMCMM_START_REQ的公共处理        */
    }
    else
    {
        /* WUEPS_ASSERT(0); */
    }
    return;                                                                     /* 返回                                     */
}

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S16_E4 */

/* MMCMM_PLMN_USER_SEL_REQ不再使用，删除Mm_Cell_S19_E4 */

/*******************************************************************************
  Module:   Mm_Get_UserSpecificSearchFlg_From_SysInfo
  Function: 从MMC传给MM的sys info消息中获取UserSpecificSearchFlg标志信息
  Input:    VOS_VOID * pRcvMsg   - sys info 消息指针
  Output:
  NOTE:
  Return:   VOS_UINT8  - UserSpecificSearchFlg 标志
  History:
      1.  欧阳飞    2009.1.22  新版做成
  2.日    期   : 2013年07月25日
    作    者   : l65478
    修改内容   : 当前限制驻留,在用户指定搜索当前的网络时,MM不发起注册,GCF失败
*******************************************************************************/

VOS_UINT8 Mm_Get_UserSpecificSearchFlg_From_SysInfo(
                   VOS_VOID *pRcvMsg
                   )
{
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;
    MMCMM_SYS_INFO_IND_STRU            *pSysInfoInd             = VOS_NULL_PTR;
    MMCMM_GSM_SYS_INFO_IND_ST          *pGsmSysInfoInd          = VOS_NULL_PTR;

    pSysInfoInd      = (MMCMM_SYS_INFO_IND_STRU *)pRcvMsg;
    pGsmSysInfoInd   = (MMCMM_GSM_SYS_INFO_IND_ST *)pRcvMsg;

    if (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState)
    {
        return VOS_FALSE;
    }

    if (MMCMM_SYS_INFO_IND == pSysInfoInd->MsgHeader.ulMsgName )
    {
        ucUserSpecificSearchFlg = pSysInfoInd->ucUserSpecificSearchFlg;
    }
    else
    {
        ucUserSpecificSearchFlg = pGsmSysInfoInd->ucUserSpecificSearchFlg;
    }

    return ucUserSpecificSearchFlg;
}

/*******************************************************************************
  Module:   Mm_Cell_S1_E5
  Function: 在MM IDLE NO CELL AVAILABLE状态下收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.10  新版做成
  2.  s46746  05-09-27  modify for HSS 4100 V200R001
  3.日    期   : 2006年10月6日
    作    者   : s46746
    修改内容   : 问题单号：A32D05960
  4.日    期   : 2007年04月20日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D10235
  5.日    期   : 2007年09月05日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：AT2D01490
  6.日    期   : 2008年08月21日
    作    者   : ouyangfei id:00132663
    修改内容   : 问题单号：AT2D04652,当小区改变时，停止定时器 T3211
  7.日    期   : 2008年09月03日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05403,mm注册状态修改
  8.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  9.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 10.日    期   : 2011年6月3日
    作    者   : c00173809
    修改内容   : 根据问题单号：问题单号:DTS2011060102833,从禁止PLMN切换到非禁止PLMN时，非禁止网络的网络模式为I时，没有发起联合RAU，不符合协议 。
 11.日    期   : 2011年10月8日
    作    者   : z00161729
    修改内容   : V7R1 PhaseII EPLMN/RPLMN由MM/GMM维护修改
 12.日    期   : 2012年02月29日
    作    者   : l00130025
    修改内容   : DTS2012022206186:不发起LAU,而注册成功时，需要同步注册状态给AS
 13.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
 14.日    期   : 2012年3月09日
    作    者   : w00167002
    修改内容   : V7R1C50 支持CSFB特性修改:当CSFB标志存在时，发起单独的LAU
 15.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 16.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 17.日    期   : 2013年12月5日
    作    者   : w00167002
    修改内容   : DTS2013113006231:W下，开机在LAC1上注册成功，重选到LAC2上，CS注册成功
                 PS注册被拒#13,重选回LAC1上，注册成功。丢网后任意小区驻留在LAC2
                 上，不发起注册，重选回LAC1上，检测不发起注册。
                 修改为在收到系统消息时候，不进行UPDATE状态的更新。
 18.日    期   : 2014年04月1日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目:系统消息处理优化以及全局变量替换成MML中的
 19.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*******************************************************************************/

VOS_VOID Mm_Cell_S1_E5(
                   VOS_VOID *pRcvMsg
                   )
{
    VOS_UINT32                                  ulLaiChangeFlag;
    VOS_UINT8                                   ucUserSpecificSearchFlg = 0;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag         = NAS_MML_IsCsfbServiceStatusExist();
#endif

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    if ((VOS_TRUE == ulLaiChangeFlag)
     || (MM_TRUE  == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
    {
        Mm_TimerStop(MM_TIMER_T3211);
    }

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
    /* CS ONLY或PS ONLY,在NMO1下需要进行联合注册 */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: mmLikeB is MM_TRUE");

            if (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( ( VOS_FALSE == ulLaiChangeFlag ) &&
                     ( NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus ) )
                {
                    if ( MM_TRUE
                     == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType =
                            MM_IE_LUT_PERIODIC_UPDATING;                /* 设置LU类型                               */
                        Mm_ComLuOnly();                                 /* 发送LU REQ                               */
                    }
                    else
                    {
                        Mm_ComNasInfoSav(MM_STATUS_ATTACHED,
                                         NAS_MML_GetSimCsSecurityCksn());

                        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;    /* 设置服务状态                             */

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_NORMAL_LU;                /* 设置LU类型                               */
                    Mm_ComLuOnly();                                     /* LU REQ                                   */
                }
            }
            else
            {
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_NORMAL_LU;                /* 设置LU类型                               */
                    Mm_ComLuOnly();                                     /* LU REQ                                   */
                }
                else
                {
                    switch ( NAS_MML_GetCsUpdateStatus() )
                    {
                    case NAS_MML_LOCATION_UPDATE_STATUS_UPDATED:
                         NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        g_MmGlobalInfo.ucMmServiceState =
                                            MM_NORMAL_SERVICE;
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");


                        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);    /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);    /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        g_MmGlobalInfo.ucPreState =
                                        g_MmGlobalInfo.ucState;         /* 记录前状态                               */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        break;
                    case NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED:
                         NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                        g_MmGlobalInfo.ucMmServiceState =
                                        MM_ATTEMPTING_TO_UPDATE;
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S1_E5:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_FAILURE,
                                                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);    /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);    /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        g_MmGlobalInfo.ucPreState =
                                        g_MmGlobalInfo.ucState;         /* 记录前状态                               */
                        Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        else
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S1_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
    }
    else
    {   /* A+II或者B模式                            */
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pRcvMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                       /* 调用在系统信息的公共处理                 */
    }
}

/*******************************************************************************
  Module:   Mm_MakeCcEstReq
  Function: 根据缓存的信息做成消息
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期   : 2007年09月29日
        作    者   : l65478
        修改内容   : creat function
*******************************************************************************/
VOS_VOID Mm_MakeCcEstReq(MMCC_EST_REQ_STRU *pMsg)
{
    pMsg->ulCallPri =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallPri;
    pMsg->ulCallType =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallType;
    pMsg->ulTransactionId =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId;
    pMsg->ulCallMode =
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulCallMode;

}
/*******************************************************************************
  Module:   Mm_MakeSmsEstReq
  Function: 根据缓存的信息做成消息
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期   : 2007年09月29日
        作    者   : l65478
        修改内容   : creat function
*******************************************************************************/
VOS_VOID Mm_MakeSmsEstReq(MMSMS_EST_REQ_STRU *pMsg)
{
    pMsg->ulTi=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId;
    pMsg->ulEstCause = g_MmSmsEstReq.ulEstCause;
}
/*******************************************************************************
  Module:   Mm_MakeSsEstReq
  Function: 根据缓存的信息做成消息
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期   : 2007年09月29日
        作    者   : l65478
        修改内容   : creat function
*******************************************************************************/
VOS_VOID Mm_MakeSsEstReq(MMSS_EST_REQ_STRU *pMsg)
{
    pMsg->ulTi=
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId;
}

/*******************************************************************************
  Module:   Mm_MakeGPagingInd
  Function: 根据缓存的信息做成消息
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期   : 2008年05月02日
        作    者   : s46746
        修改内容   : creat function
*******************************************************************************/
VOS_VOID Mm_MakeGPagingInd(GRRMM_PAGING_IND_ST *pMsg)
{
    pMsg->MsgHeader.ulMsgName           = GRRMM_PAGING_IND;
    pMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid         = UEPS_PID_GAS;
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pMsg->MsgHeader.ulLength            = sizeof(GRRMM_PAGING_IND_ST) - VOS_MSG_HEAD_LENGTH;
    if (MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        pMsg->ucMSIDType                = GAS_TMSI;
    }
    else
    {
        pMsg->ucMSIDType                = GAS_IMSI;
    }
    pMsg->ucPagingType                  = 0;

    return;
}

/*******************************************************************************
  Module:   Mm_MakeWPagingInd
  Function: 根据缓存的信息做成消息
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期   : 2008年05月02日
        作    者   : s46746
        修改内容   : creat function
      2.日    期   : 2012年09月01日
        作    者   : s46746
        修改内容  : DTS2012090405619 :DCM外场测试,联合RAU过程中响应寻呼被网络abort
*******************************************************************************/
VOS_VOID Mm_MakeWPagingInd(RRMM_PAGING_IND_STRU *pMsg)
{
    pMsg->MsgHeader.ulMsgName           = RRMM_PAGING_IND;
    pMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulSenderPid         = WUEPS_PID_WRR;
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pMsg->MsgHeader.ulLength            = sizeof(RRMM_PAGING_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pMsg->ulPagingCause                 = g_MmGlobalInfo.ucPagingCause;
    pMsg->ulCnDomainId                  = RRC_NAS_CS_DOMAIN;

    if (MM_TMSI_PAGING == g_MmGlobalInfo.ucPagingRecordTypeId)
    {
        pMsg->ulPagingUeId              = RRC_TMSI_GSM_MAP_P_TMSI;
    }
    else
    {
        pMsg->ulPagingUeId              = RRC_IMSI_GSM_MAP;
    }

    pMsg->ulPagingType                  = 0;
}

/*******************************************************************************
  Module:   Mm_DealWithBuffMsg
  Function: 处理缓存的消息
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.日    期   : 2007年09月29日
        作    者   : l65478
        修改内容   : creat function
      2.日    期   : 2010年11月23日
        作    者   : s46746
        修改内容   : 问题单号:DTS2010111604795，增加Attempt update状态的处理
      3.日    期   : 2012年12月27日
        作    者   : t00212959
        修改内容   : DTS2012122607665:紧急呼MM_WAIT_FOR_ATTACH状态需要发起
      4.日    期   : 2013年07月05日
        作    者   : l65478
        修改内容   : DTS2013070408274:MM进入NORMAL SERVICE后没有处理缓冲的CC消息
*******************************************************************************/
VOS_VOID Mm_DealWithBuffMsg(VOS_VOID)
{
    MMCC_EST_REQ_STRU                   CcEstReqMsg;
    MMSMS_EST_REQ_STRU                  SmsMsg;                                 /* 定义接收到的消息类型指针                 */
    MMSS_EST_REQ_STRU                   SsMsg;                                  /* 定义接收到的消息类型指针                 */
    RRMM_PAGING_IND_STRU                stWPagingMsg;
    GRRMM_PAGING_IND_ST                 stGPagingMsg;

    VOS_UINT32                          ulLaiChangeFlag;
    LAU_TYPE_ENUM_UINT8                 enLauType;
    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg             = Mm_ComJudgeCsServExist();

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();
    enLauType       = MM_IE_LUT_TYPE_BUTT;
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: deal with buffer message! ");
    if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
     || (MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState))
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: start CC message preceed! ");
            Mm_MakeCcEstReq(&CcEstReqMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[23][g_MmGlobalInfo.ucState](&CcEstReqMsg);
            /*lint +e961*/
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSmsEstReq(&SmsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[61][g_MmGlobalInfo.ucState](&SmsMsg);
            /*lint +e961*/
        }
        else if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSsEstReq(&SsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
            /*lint -e961*/
            gaMmStateTable[64][g_MmGlobalInfo.ucState](&SsMsg);
            /*lint +e961*/
        }
        else if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
        {
            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_MakeGPagingInd(&stGPagingMsg);
                /*lint -e961*/
                gaMmStateTable[30][g_MmGlobalInfo.ucState](&stGPagingMsg);
                /*lint +e961*/
            }
            else
            {
                Mm_MakeWPagingInd(&stWPagingMsg);
                /*lint -e961*/
                gaMmStateTable[30][g_MmGlobalInfo.ucState](&stWPagingMsg);
                /*lint +e961*/
            }
        }
        else
        {
        }
    }
    else if((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState )
        && (MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState )
        && (WAIT_FOR_RR_CONNECTION_MM_CONNECTION != g_MmGlobalInfo.ucState)
        && (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState ))
    {
        if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_DealWithBuffMsg: start EMC! ");
            Mm_MakeCcEstReq(&CcEstReqMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E24(&CcEstReqMsg);

        }
        else if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSmsEstReq(&SmsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E62(&SmsMsg);
        }
        else if(MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {
            Mm_MakeSsEstReq(&SsMsg);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg = MM_FALSE;
            Mm_Cell_S4_E65(&SsMsg);
        }
        else
        {
        }
    }
    else if (MM_WAIT_FOR_ATTACH == g_MmGlobalInfo.ucState)
    {
        if (MM_PAGING_PLMNSRCH_TRUE == g_MmSubLyrShare.MmShare.ucPagingPlmnSrch)
        {/* 此时小区肯定没有发生变化 */
            g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                Mm_MakeGPagingInd(&stGPagingMsg);
                Mm_Cell_S3_E31(&stGPagingMsg);
            }
            else
            {
                Mm_MakeWPagingInd(&stWPagingMsg);
                Mm_Cell_S3_E31(&stWPagingMsg);
            }
        }
        if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulEmergencyCallFlg)
        {
            /* 发起LAU流程 有紧急呼先进行紧急呼*/
            enLauType = NAS_MM_GetLuType();

            NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, enLauType);
        }

    }
    else
    {
    }

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    NAS_MM_UpdateCsServiceBufferStatusFlg();
}

/*******************************************************************************
  Module:   Mm_Cell_S2_E5
  Function: 在MM IDLE PLMN SEARCH状态下收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
   1.  张志勇     2003.12.10  新版做成
   2.  s46746  05-09-27  modify for HSS 4100 V200R001
   3.  s46746 2006-02-28 根据问题单A32D02503修改
   4.  s46746  2006-06-24  根据问题单A32D04439修改
   5.  s46746  2006-07-25  根据问题单A32D05058修改
   6.日    期   : 2006年10月6日
     作    者   : s46746
     修改内容   : 问题单号：A32D05960
   7.日    期   : 2007年04月20日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D10235
   8.日    期   : 2007年09月05日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：AT2D01490
   9.日    期   : 2007年10月06日
     作    者   : l65478
     修改内容   : 问题单号：A32D12977
  10.日    期   : 2008年08月21日
     作    者   : ouyangfei id:00132663
     修改内容   : 问题单号：AT2D04652,当小区改变时，停止定时器 T3211
  11.日    期   : 2008年09月03日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,mm注册状态修改
  12.日    期   : 2008年11月22日
     作    者   : l65478
     修改内容   : 问题单号：AT2D06900,mm注册状态修改
  13.日    期   : 2009年02月21日
     作    者   : l65478
     修改内容   : AT2D09308,在限制服务下，处理缓存的消息
  14.日    期   : 2009年05月11日
     作    者   : h44270
     修改内容   : AT2D11661/AT2D11804,发起手动搜网打断LAU过程，导致搜网成功后发起两次LAU
  15.日    期   : 2009年8月23日
     作    者   : l65478
     修改内容   : 问题单号：AT2D13980,在LU失败后，改变小区后，此后再不会发起LU,因为在收到系统信息时，把T3211停止了
  16.日    期   : 2010年03月20日
     作    者   : l65478
     修改内容   : 问题单号：AT2D17070,呼叫中止指定搜索时，MMC后续没有发起搜网
  17.日    期   : 2010年11月30日
     作    者   : h44270
     修改内容   : 问题单号：DTS2010112905048/DTS201011270072,CS域IMSI无效时，没有向MMC回复消息收到消息
  18.日    期   : 2011年7月16日
     作    者   : h44270
     修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  19.日    期   : 2011年7月25日
     作    者   : h44270
     修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  20.日    期   : 2011年6月3日
     作    者   : c00173809
     修改内容   : 根据问题单号：问题单号:DTS2011060102833,从禁止PLMN切换到非禁止PLMN时，非禁止网络的网络模式为I时，没有发起联合RAU，不符合协议 。
  21.日    期   : 2011年10月27日
     作    者   : s46746
     修改内容   : V7R1 PhaseIII,支持L模联合注册
  22.日    期   : 2011年12月2日
     作    者   : s46746
     修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
  23.日    期   : 2012年03月20日
     作    者   : l00130025
     修改内容   : DTS2012030105247,NAS只在网侧实际发起鉴权时,通知W SecurityKey，其它情况下由WAS调用对应接口获取
  24.日    期  : 2012年2月15日
     作    者  : w00167002
     修改内容  : V7R1C50 支持CSFB特性修改，增加对存在CSFB标志时的处理
  25.日    期   : 2012年8月22日
     作    者   : z00161729
     修改内容   : DCM定制需求和遗留问题修改
  26.日    期   : 2013年2月4日
     作    者   : w00176964
     修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  27.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  28.日    期   : 2013年12月5日
     作    者   : w00167002
     修改内容   : DTS2013113006231:W下，开机在LAC1上注册成功，重选到LAC2上，CS注册成功
                  PS注册被拒#13,重选回LAC1上，注册成功。丢网后任意小区驻留在LAC2
                  上，不发起注册，重选回LAC1上，检测不发起注册。
                  修改为在收到系统消息时候，不进行UPDATE状态的更新。
 21.日    期   : 2014年04月1日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目:系统消息处理优化
 22.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*******************************************************************************/

VOS_VOID Mm_Cell_S2_E5(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                                  ulLaiChangeFlag;
    VOS_UINT8                                   ucUserSpecificSearchFlg = 0;
    VOS_UINT8                                   ucPsRestrictionFlg;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enCurrentRatType;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif
    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();

    NAS_MM_NotifyAsInfoChgReq();


    enCurrentRatType = NAS_MML_GetCurrNetRatType();

    if (( MM_CKSN_INVALID != NAS_MML_GetSimCsSecurityCksn() )
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurrentRatType))
    {
        Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SK_FLG);
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
    /* 如果当前LAI与之前驻留的LAI相比发生变化,需要清除atttemp conter值 */
    if (VOS_TRUE == NAS_MM_IsNeedClearAttemptCounter())
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
    }

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
    /* CS ONLY,PS ONLY下NMO1下GMM需要进行联合注册 */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
        )
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
    {
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: LikeB is MM_TRUE");

            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();

            if ( ( VOS_FALSE == ulLaiChangeFlag )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus ) )
            {
                if ( MM_ATT_NOT_NEED == g_MmGlobalInfo.ucAttFlg )
                {
                    if ( MM_TRUE ==
                            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
                        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */
                    }
                    else
                    {
                        Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                        g_MmGlobalInfo.ucMmServiceState =
                            MM_NORMAL_SERVICE;                          /* 设置服务状态                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");

                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                        if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                        {
                            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
                        }

                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
                else
                {
                    if ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg )
                    {
                        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, begin */
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_IMSI_ATTACH);
                        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-23, end */

                    }
                    else if ( MM_TRUE ==
                            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg )
                    {
                        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
                        NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_PERIODIC_UPDATING);
                        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */
                    }
                    else
                    {
                        Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );

                        g_MmGlobalInfo.ucMmServiceState =
                            MM_NORMAL_SERVICE;                          /* 设置服务状态                             */
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");


                        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                    MM_MMC_LU_RESULT_SUCCESS,
                                                    NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */
                        NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */

                        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is  MM_IDLE_NORMAL_SERVICE");
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }
            }
            else
            {
                /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, begin */
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
                /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-22, end */
            }
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        }
        else
        {
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
            Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
        }
    }
    else
    {
        /* A+II或者B模式                            */
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pRcvMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                                               /* 调用在系统信息的公共处理                 */
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */

    Mm_DealWithBuffMsg();
}

/*******************************************************************************
  Module:   Mm_Cell_S2_E21
  Function: 在MM IDLE PLMN SEARCH状态下收到MMCMM_COVERAGE_LOST_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2.  s46746  05-09-27  modify for HSS 4100 V200R001
      3.日    期   : 2008年08月15日
        作    者   : l65478
        修改内容   : 问题单号：AT2D04830服务状态上报错误
      4.日    期   : 2009年01月14日
        作    者   : l65478
        修改内容   : 问题单号：AT2D07971,在搜网状态下上报的接入技术错误
      5.日    期   : 2011年10月11日
        作    者   : l00171473
        修改内容   : V7R1 phase II, TC环回调整，通知TC连接释放
      6.日    期   : 2012年9月24日
        作    者   : s46746
        修改内容   : 问题单号DTS2012092003660，无服务时发送短信，导致后续不再发起搜网
      7.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
      8.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
      9.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容   :DTS2013082903019:支持ss重发功能
     10.日    期   : 2013年10月15日
        作    者   : l65478
        修改内容   : DTS2013102501008从收到搜网模式设置成自动搜网模式后没有发起注册
     11.日    期   : 2014年05月31日
        作    者   : s00246516
        修改内容   : 路由区更新过程中出服务区，如果有缓存的Detach，没有回复
     12.日    期   : 2014年04月29日
        作    者   : y00245242
        修改内容   : eCall项目修改
     13.日    期   :2014年9月24日
        作    者   :s00217060
        修改内容   :for cs_err_log
     14.日    期   : 2014年12月29日
        作    者   : z00161729
        修改内容   : DSDS业务重拨时no rf未触发搜网导致业务失败，mm在no cell available状态no rf时给mmc发送cm service ind触发搜网
*******************************************************************************/

VOS_VOID Mm_Cell_S2_E21(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg) )
    {
        return;
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
    {
        /* 如果是EMC，继续等待上层的终止, 如果当前no rf直接给cc回复失败 */
        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         || (MMCC_EMERGENCY_CALL != g_MmCcEstReq.ulCallType))

        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        }
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSmsRelInd( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId,
                NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);                        /* 通知SMS建立失败                          */
    }

    if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
    {
        Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId,
                       NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }

    if (TEST_CONTROL_ACTIVE == g_MmGlobalInfo.ucState)
    {
        Mm_TimerResume(MM_TIMER_STOP_ALL);

        /* TC状态收到COVERAGE LOST消息时，通知TC连接释放 */
        NAS_MM_SndTcRrRelInd();
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* 保存出服务区前的状态,在搜网成功后用于判断LAI是否改变 */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */

    g_MmSubLyrShare.MmShare.ucPagingPlmnSrch = MM_PAGING_PLMNSRCH_FALSE;

    if (MM_WAIT_CS_DETACH == (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_NO_SERVICE);

        NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());             /* 设置MM信息                               */

        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S2_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S2_E21:INFO: MmServiceState is MM_NO_SERVICE");
}

/*******************************************************************************
  Module:   Mm_Cell_S14_E21
  Function: 在WAIT FOR REESTABLISH(WAIT FOR EST_CNF)状态下
            收到MMCMM_COVERAGE_LOST_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  s46746  06-05-20  Add for A32D03824
      2.日    期   : 2008年08月15日
        作    者   : l65478
        修改内容   : 问题单号：AT2D04830服务状态上报错误

      3.日    期   : 2011年7月14日
        作    者   : zhoujun 40661
        修改内容   : 更新MML_CTX中的链接存在状态
      4.日    期   : 2011年11月22日
        作    者   : w00166186
        修改内容   : DTS2011112101648,OOS等待系统消息超时后，信令链接标志没有清除，导致后续AVAILABLE
                     定时器超时后没有发起搜网
      5.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
      6.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
      7.日    期   : 2013年07月23日
        作    者   : l65478
        修改内容   : DTS2013071809030,MMC收到RRMM_SUSPEND_REL_CNF后没有立刻处理缓存的SYSCFG
      8.日    期   :2013年9月12日
        作    者   :z00161729
        修改内容  :DTS2013082903019:支持ss重发功能
      9.日    期   :2013年10月18日
        作    者   :z00161729
        修改内容   :DTS2013101900866:mm在wait for mm connection状态收到gas丢网消息没有给cc回复rel ind导致呼叫T303超时呼叫失败
     10.日    期   : 2013年10月15日
        作    者   : l65478
        修改内容   : DTS2013102501008从收到搜网模式设置成自动搜网模式后没有发起注册
     11.日    期   : 2014年04月29日
        作    者   : y00245242
        修改内容   : eCall项目修改
     12.日    期   :2014年9月24日
        作    者   :s00217060
        修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E21(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg) )
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S14_E21:WARNING: MMCMM_COVERAGE_LOST_IND is not correct.");
        return;
    }

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);                                  /* 启动保护TIMER                            */

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* 保存出服务区前的状态,在搜网成功后用于判断LAI是否改变 */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    if (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING == g_MmGlobalInfo.ucState)
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL);
        
        NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL); 
    }

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S14_E21:INFO: MmServiceState is MM_NO_SERVICE");




    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);


    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

    return;
}

/*******************************************************************************
  Module:   Mm_RcvRrmmRelInd
  Function:
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:

  1.日    期   : 2010年05月14日
    作    者   : l65478
    修改内容   : 问题单号:AT2D19292,MM在寻呼建立连接时，收到系统信息，把状态迁到NORMAL状态，导致GCF失败

*******************************************************************************/
VOS_VOID Mm_RcvRrmmRelInd()
{
    RRMM_REL_IND_STRU                   RrRelInd;

    /* 填写EST CNF消息内容 */
    RrRelInd.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrRelInd.MsgHeader.ulReceiverPid    = WUEPS_PID_MM;

    RrRelInd.MsgHeader.ulMsgName        = RRMM_REL_IND;

    RrRelInd.ulCnDomainId               = RRC_NAS_CS_DOMAIN;
    RrRelInd.ulRrcConnStatus            = RRC_RRC_CONN_STATUS_ABSENT;
    RrRelInd.ulRelCause                 = RRC_REL_CAUSE_RR_NORM_EVENT;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        RrRelInd.MsgHeader.ulSenderPid = WUEPS_PID_WRR;
    }
    else
    {
        RrRelInd.MsgHeader.ulSenderPid = UEPS_PID_GAS;
    }
    /*直接调用GMM处理消息RRMM_REL_IND的函数*/
    /*lint -e961*/
    gaMmStateTable[33 - 1][g_MmGlobalInfo.ucState](&RrRelInd);
    /*lint +e961*/
    return;
}
/*******************************************************************************
  Module:   Mm_RcvRrmmEstCnf
  Function:
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:

*******************************************************************************/
VOS_VOID Mm_RcvRrmmEstCnf()
{
    RRMM_EST_CNF_STRU                   RrEstCnf;

    /* 填写EST CNF消息内容 */
    RrEstCnf.MsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    RrEstCnf.MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    RrEstCnf.MsgHeader.ulReceiverPid    = WUEPS_PID_MM;

    RrEstCnf.MsgHeader.ulMsgName        = RRMM_EST_CNF;

    RrEstCnf.ulOpId                     = g_MmGlobalInfo.ucRrEstReqOpid;
    RrEstCnf.ulCnDomainId               = RRC_NAS_CS_DOMAIN;
    RrEstCnf.ulResult                   = RRC_EST_EST_CONN_FAIL;

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        RrEstCnf.MsgHeader.ulSenderPid = WUEPS_PID_WRR;
    }
    else
    {
        RrEstCnf.MsgHeader.ulSenderPid = UEPS_PID_GAS;
    }
    /*lint -e961*/
    gaMmStateTable[31][g_MmGlobalInfo.ucState](&RrEstCnf);
    /*lint +e961*/

    return;
}
/*******************************************************************************
  Module:   Mm_Cell_S9_E21
  Function: 在WAIT_FOR_OUTGOING_MM_CONNECTION状态下
            收到MMCMM_COVERAGE_LOST_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
 1.日    期   : 2008年8月21日
   作    者   : l00130025
   修改内容   : 问题单号:At2D05016,MM注册状态修改
 2.日    期   : 2011年7月25日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 3.日    期   : 2011年11月22日
   作    者   : w00166186
   修改内容   : DTS2011112101648,OOS等待系统消息超时后，信令链接标志没有清除，导致后续AVAILABLE
                定时器超时后没有发起搜网
 4. 日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 5 .日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  6.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 7. 日    期   : 2013年07月23日
    作    者   : l65478
    修改内容   : DTS2013071809030,MMC收到RRMM_SUSPEND_REL_CNF后没有立刻处理缓存的SYSCFG
 8. 日    期   : 2013年9月12日
    作    者   : w00242748
    修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                 原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                 G下原小区时做LAU
 9.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
10.日    期   : 2013年10月15日
   作    者   : l65478
   修改内容   : DTS2013102501008从收到搜网模式设置成自动搜网模式后没有发起注册
11.日    期   : 2014年04月29日
   作    者   : y00245242
   修改内容   : eCall项目修改
12.日    期   : 2014年6月4日
   作    者   : w00167002
   修改内容   : DTS2014052603967:CS only，在A小区注册失败17后迁移到B小区，在B小区
                是禁止PLMN小区，MM迁移到LIMIT service状态，后续搜网到A小区网络后，
                发起了LAU.
                在LAU失败迁移到U2状态时候记录当前的LAI信息；在开机，用户发起CS/CS_PS
                DETACH时候或或者重新发起LAU时候则清除该LAI信息；
                在后续搜索到该小区后，在U2状态，如果当前的LAI在记录的LAI里面，则
                不发起LAU
 13.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
 14.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E21(VOS_VOID *pMsg)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;
    MM_LAI_STRU                                            *pstAttLaiInfo   = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstCampLaiInfo  = VOS_NULL_PTR;

    if (MM_FALSE == Mm_RcvMmcCoverageLostInd(pMsg))
    {
        return;
    }

    switch (g_MmGlobalInfo.ucState)
    {
        case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        case WAIT_FOR_OUTGOING_MM_CONNECTION:

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
            break;
        case LOCATION_UPDATING_INITIATED:

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);

            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
             || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != enCsUpdateStatus))
            {
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;
                g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL;
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                /* 在U2状态，保存当前的LAI信息 */
                pstAttLaiInfo   = NAS_MM_GetAttemptUpdateLaiInfo();
                pstCampLaiInfo  = NAS_MML_GetCurrCampLai();

                pstAttLaiInfo->PlmnId.ulMcc = pstCampLaiInfo->stPlmnId.ulMcc;
                pstAttLaiInfo->PlmnId.ulMnc = pstCampLaiInfo->stPlmnId.ulMnc;
                pstAttLaiInfo->ulLac        = ((pstCampLaiInfo->aucLac[0] << 8)| (pstCampLaiInfo->aucLac[1]));

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );
                Mm_ComDelLai();
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &= ~MM_MS_ID_TMSI_PRESENT;

                NAS_MML_InitUeIdTmsiInvalid();

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

                Mm_TimerStart(MM_TIMER_T3211);
            }
            break;
        case LOCATION_UPDATE_REJECTED:
            Mm_TimerStop(MM_TIMER_T3240);
            Mm_TimerStop(MM_TIMER_T3218);                                       /* 停T3218                                  */
            Mm_ComDelRandRes();
            Mm_ComLuCauseHandle(g_MmGlobalInfo.usCauseVal);
            break;
        case WAIT_FOR_NETWORK_COMMAND:
            Mm_TimerStop(MM_TIMER_T3240);
            Mm_TimerStop(MM_TIMER_T3218);                                       /* 停T3218                                  */
            Mm_ComDelRandRes();
            break;
        case WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ:
            Mm_TimerStop(MM_TIMER_PROTECT_CC);
            break;
        default:
            break;
    }

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

    if ((VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
     && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    /* 保存出服务区前的状态,在搜网成功后用于判断LAI是否改变 */
    g_MmGlobalInfo.ucNotCampONPreState = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MM_ProcEcallTimerStartNeededFlg();
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-29, end */

    NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);

    Mm_ComProcCauseClear();

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E21:NORMAL: STATUS is MM_IDLE_NO_CELL_AVAILABLE");
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E21:INFO: MmServiceState is MM_NO_SERVICE");

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_GetStaOfRcvXXEstReq_CSFB
 功能描述  : CSFB流程中获取连接建立前的状态
 输入参数  : 无
 输出参数  : 连接建立前的MM状态
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年9月13日
   作    者   : s46746
   修改内容  : 新生成函数
 2.日    期   :2013年9月6日
    作    者   :z00161729
    修改内容  :DTS2013083007549:G fast return功能开启，ap连续4次下发补充业务查询第3次查询失败，mm状态为attempt to update维护不对

*****************************************************************************/
VOS_UINT8 NAS_MM_GetStaOfRcvXXEstReq_CSFB(VOS_VOID)
{
    VOS_UINT8                           ucState;
    VOS_UINT32                          ulLaiChangeFlag;

    ulLaiChangeFlag = NAS_MML_IsCsLaiChanged();

    switch (g_MmGlobalInfo.ucState)
    {
        case MM_IDLE_NO_CELL_AVAILABLE:
        case MM_IDLE_PLMN_SEARCH:
        case LOCATION_UPDATING_PENDING:
        case MM_IDLE_LOCATION_UPDATE_NEEDED:
        case MM_WAIT_FOR_ATTACH:
            if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
            {
                ucState = MM_IDLE_NO_IMSI;
            }
            else if ( ( MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
                   && ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg ) )
            {
                ucState = MM_IDLE_LIMITED_SERVICE;
            }
            else if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
            {
                ucState = MM_IDLE_LOCATION_UPDATE_NEEDED;
            }
            else if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
                  || (VOS_TRUE == ulLaiChangeFlag))
            {
                ucState = MM_IDLE_ATTEMPTING_TO_UPDATE;
            }
            else
            {
                ucState = MM_IDLE_NORMAL_SERVICE;
            }
            break;

        default:
            ucState = g_MmGlobalInfo.ucState;
            break;
    }

    return ucState;
}
#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_MM_ResponseLmmPagingInd_CSFB
 功能描述  : MT CSFB流程响应寻呼的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月14日
   作    者   : w00167002
   修改内容   : 新生成函数

 2.日    期   : 2012年09月01日
   作    者   : s46746
   修改内容   : DTS2012091304207:DCM外场测试,csfb搜网到w，挂断电话u2l切换，mm状态不对未响应suspend ind，导致切换失败

*****************************************************************************/
VOS_VOID NAS_MM_ResponseLmmPagingInd_CSFB(VOS_VOID)
{
    MM_MSG_PAGING_RSP_STRU              stCmRspRsp;

    Mm_TimerStop(MM_TIMER_T3211);

    if (VOS_TRUE == NAS_MML_IsNeedClearCsCksn_UsimDoneGsmCsAuth())
    {
        NAS_MML_SetSimCsSecurityCksn(MM_CKSN_INVALID);
        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_FALSE);
    }
    
    stCmRspRsp.MmIeCksn.ucCksn = NAS_MML_GetSimCsSecurityCksn();                /* 存储CKSN                                 */


    NAS_MM_FillMobileID(&(stCmRspRsp.MmIeMobileId.MobileID));

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())                /* 当前处于 GSM 网中 */
    {
        /* 向 GAS 发送建立 RR 请求 */
        Mm_SndRrEstReq(RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL, MM_TRUE,
                       MM_CONST_NUM_0, VOS_NULL_PTR);
    }
    else /* UMTS 网中 */
    {
        g_MmGlobalInfo.ucPagingCause = RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL;
        Mm_ComMsgPagingRspSnd( &stCmRspRsp );                                   /* 填充并发送 PAGING RESPONSE 消息          */
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* 通知MMC，CS域的业务已经启动              */

    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);                                 /* 启动保护TIMER                            */

    NAS_MML_SetCsServiceConnStatusFlg(VOS_TRUE);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_MM_PerformBufferedSsService
 功能描述  : 处理缓存的SS业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月14日
   作    者   : w00167002
   修改内容   : 新生成函数
 2.日    期   : 2012年09月01日
   作    者   : s46746
   修改内容   : DTS2012091304207:DCM外场测试,csfb搜网到w，挂断电话u2l切换，mm状态不对未响应suspend ind，导致切换失败

*****************************************************************************/
VOS_VOID NAS_MM_PerformBufferedSsService(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU              stCmSvcReq;                               /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                          usMsgSize = 0;                          /* 消息长度,以字节为单位                    */
    VOS_UINT8                          *pucCmSvcReq = 0;                        /* 要发送的CM SERVICE REQ消息指针           */


    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
        = MM_TRUE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                        RcvXXEstReq.ulTransactionId
        = g_MmSsEstReq.ulTi;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
        = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
        = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

    Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &stCmSvcReq);      /* 填充CM SERVICE REQUEST结构体             */
    pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &stCmSvcReq, &usMsgSize );       /* 填充CM SERVICE REQUEST 消息              */
    if (VOS_NULL_PTR == pucCmSvcReq)
    {                                                                           /* 消息制作失败                             */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_PerformBufferedSsService: MAKE MSG CM SERVICE REQUEST ERROR!");
        return;                                                                 /* 返回                                     */
    }
    else
    {                                                                           /* 消息制作成功                             */
        Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
           MM_FALSE, usMsgSize, pucCmSvcReq);                                   /* 发送消息                                 */
        MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);                        /* 释放CM SERVICE REQUEST 消息结构体        */
    }
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
        (VOS_UINT8)g_MmSsEstReq.ulTi;                                           /* 记录正在建立的MM连接的TI                 */
    g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;             /* 记录正在建立的MM连接的PD                 */
    Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                        /* 通知MMC，CS域的业务已经启动              */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}
/*****************************************************************************
 函 数 名  : NAS_MM_RcvSysInfo_CSFB
 功能描述  : CSFB流程收到系统消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年2月14日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年3月8日
   作    者   : w00167002
   修改内容   : V7R1C50 CSFB&PPAC&ETWS&ISR:TC根据日本测试用例，认为LAI未发生
                改变，则直接进行业务
 3.日    期   : 2012年4月7日
   作    者   : W00166186
   修改内容   : V7R1C50 CSFB&PPAC&ETWS&ISR EMERGENCY CALL 开发
 4.日    期   : 2012年8月14日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 5.日    期   : 2012年09月01日
   作    者   : s46746
   修改内容  : DTS2012091304207:DCM外场测试,csfb搜网到w，挂断电话u2l切换，mm状态不对未响应suspend ind，导致切换失败
 6.日    期   : 2012年10月22日
   作    者   : t00212959
   修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
 7.日    期   : 2012年10月25日
   作    者   : z00161729
   修改内容   : DTS2012102305986:csfb到gu access bar小区无法拨打紧急呼叫
 8.日    期   : 2012年12月10日
   作    者   : w00167002
   修改内容   : DTS2012112603831:L下注册成功后，发起ATD117,CSFB结果为SERVICE
                FAILURE后，搜网到W下收到系统消息后直接发起了电话业务，在电话
                业务过程中，提示当前的网络状态为不可用状态，信号个数为空。
                因此在电话业务时候，需要进行CREG状态上报通知给AP侧。
  9.日    期   : 2013年7月25日
    作    者   : w00242748
    修改内容   : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                 网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                 rau req中带follow on标志,无明确协议依据
 10.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性

  11.日    期   : 2014年12月2日
    作    者   : w00167002
    修改内容   : DTS2014092806342:CSFB到G后，LAU失败，则启动保护CSMT标志定时器，
                 增加呼通率。
  12.日    期   : 2015年6月8日
     作    者   : z00161729
     修改内容   : 24008 23122 R11 CR升级项目修改
  13.日    期   : 2015年10月16日
     作    者   : j00174725
     修改内容   : DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MM_RcvSysInfo_CSFB(VOS_VOID)
{
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    VOS_UINT32                                              ulLaiChangeFlag;

    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8               enCsUpdateStatus;

    enCsUpdateStatus  = NAS_MML_GetCsUpdateStatus();

    enCsfbServiceStatus = NAS_MML_GetCsfbServiceStatus();
    ulLaiChangeFlag     = NAS_MML_IsCsLaiChanged();

    /* CSFB 流程，如果LAI改变，做LAU, 如果LAI未变，可直接发起业务 */
    switch (enCsfbServiceStatus)
    {
        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_CC_EXIST:

            /* 3GPP 24008 4.4.1:
               indicating to the network that the MS, configured to use CS fallback
               and SMS over SGs, or SMS over SGs only, has entered a GERAN or UTRAN cell in
               NMO II or III, after intersystem change from S1 mode to Iu or A/Gb mode,
               the TIN indicates "GUTI" and the location area of the current cell is the
               same as the stored location area; NOTE1:The location updating procedure
               can be delayed when the intersystem change is due to CS fallback.
               In this case, the MS has to remember that it has to perform a
               location updating procedure after the RR connection is released,
               if the MS is still in GERAN/UTRAN.*/

            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {

                /* 当前存在缓存的CC业务，发起CC业务 */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
                {
                    /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();/* 记录收到建立请求时的状态                 */

                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);   /* 向MMC发送MMCMM_LU_RESULT_IND */

                    Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                    NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
                    return;
                }

                /* 无缓存的CC业务，进行异常处理 */
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:NORMAL CC BUFFER NOT EXIST ");

                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                return;
            }

            /* 发起LAU流程,LAU成功后进行CSFB的主叫 */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            Mm_ComLuOnly();

            return ;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_NORMAL_SS_EXIST:
            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {
                /* 当前存在缓存的SS业务，发起缓存的SS业务 */
                if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg )
                {
                    /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
                    NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                    g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* 记录收到建立请求时的状态                 */

                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);   /* 向MMC发送MMCMM_LU_RESULT_IND */

                    Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                    NAS_MM_PerformBufferedSsService();
                    return;
                }

                /* 无缓存的CC业务，进行异常处理 */
                NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:SS BUFFER SERVICE NOT EXIST ");

                NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

                NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
                return;
            }

            /* 发起LAU流程,LAU成功后进行CSFB的SS业务 */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;


            Mm_ComLuOnly();
            return;

        case NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST:

            if (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == NAS_MML_GetCsfbMtPagingTimerStatus())
            {
                /* 后续LAU携带CSMT标志 */
                NAS_MM_SetCsfbMtLauFlg(VOS_TRUE);
            }

            if ((VOS_FALSE == ulLaiChangeFlag)
             && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB();

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);       /* 向MMC发送MMCMM_LU_RESULT_IND */

                Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());            /* CREG状态迁移 */

                /* 在GU下，回复paging response */
                NAS_MM_ResponseLmmPagingInd_CSFB();

                /* 记录状态为CSFB MT已发送paging response */
                NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_PAGING_RSP_SEND,
                                          NAS_MML_REG_FAIL_CAUSE_NULL);

                /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
                NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                return;
            }

            /* 修改为在收到CSFB寻呼时候启动定时器 */

            /* 发起LAU流程 */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            /* 记录状态为CSFB MT触发LAU流程 */
            NAS_MM_RecordErrorLogInfo(NAS_ERR_LOG_BASE_STATE_TRAG_LAU,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);


            Mm_ComLuOnly();
            return;

        case NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST:
            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
            /* 如果lai不同但注册受限无需lau直接发起紧急呼叫 */
            if (VOS_TRUE == NAS_MM_IsNeedLauFirst_CsfbMoEmcExist())
            {
                /* NV配置lai改变先做lau再进行紧急呼叫，发起LAU流程 */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

                Mm_ComLuOnly();
                return;
            }

            /* 当前存在缓存的CC业务，发起CC业务 */
            if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
            {
                /* 记录delay lau标识，呼叫结束后收到系统消息需要做lau */
                NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);

                g_MmGlobalInfo.ucStaOfRcvXXEstReq = NAS_MM_GetStaOfRcvXXEstReq_CSFB(); /* 记录收到建立请求时的状态                 */

                /* 紧急呼CSFB到GU,不需要做LAU时，上报CS域注册状态 */
                NAS_MM_SndMmcCsRegResultInd_CsfbMoEmcExist();

                Mm_ComSetMmState(NAS_MM_GetStaOfRcvXXEstReq_CSFB());

                NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);

                return;
            }

            /* 无缓存的CC业务，进行异常处理 */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_RcvSysInfo_CSFB:NORMAL CC BUFFER NOT EXIST ");

            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
            /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */
            return;

         default:
            break;
    }

    return;
}
#endif

/*******************************************************************************
  Module:   Mm_Cell_S3_E5
  Function: 在MM IDLE NORMAL SERVICE状态下收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
      2.  s46746  05-09-27  modify for HSS 4100 V200R001
      3. s46746  2006-07-27 根据问题单A32D03975修改
      4.日    期   : 2006年10月6日
        作    者   : s46746
        修改内容   : 问题单号：A32D05960
      5.日    期   : 2007年1月26日
        作    者   : liurui id:40632
        修改内容   : 根据问题单号：A32D08577
      6.日    期   : 2007年04月20日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号：A32D10235
      7.日    期   : 2007年09月05日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号：AT2D01490
      8.日    期   : 2008年08月21日
        作    者   : ouyangfei id:00132663
        修改内容   : 问题单号：AT2D04652,当小区改变时，停止定时器 T3211
      9.日    期   : 2008年09月03日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05403,mm注册状态修改
      10.日    期   : 2008年11月22日
        作    者   : l65478
        修改内容   : 问题单号：AT2D06900,mm注册状态修改
      11.日    期   : 2009年10月03日
        作    者   : o00132663
        修改内容   : 问题单号：AT2D14942,异系统小区重选成功后，先上报受限服务，等注册结束后再更新服务状态。
      12.日    期   : 2011年7月16日
         作    者   : h44270
         修改内容   : V7R1 PhaseII阶段调整，注册结果简化
      13.日    期   : 2011年6月3日
         作    者   : c00173809
         修改内容   : 根据问题单号：问题单号:DTS2011060102833,从禁止PLMN切换到非禁止PLMN时，非禁止网络的网络模式为I时，没有发起联合RAU，不符合协议 。
      14.日    期   : 2011年10月27日
         作    者   : s46746
         修改内容   : V7R1 PhaseIII,支持L模联合注册
      15.日    期   : 2010年4月09日
         作    者   : z00161729
         修改内容   : 问题单号DTS2011032601795:网络模式II，MM周期性LAU过程随机接入失败,
                      T3211运行时发生小区重选后未发起LAU，而是等T3212超时后才发起
      16.日    期   : 2011年7月14日
         作    者   : k66584
         修改内容   : 问题单号:DTS2011070603156,系统消息指示PS域被bar,LAI没有变化,
                      启动T3212前增加判断条件,网络模式I下不启动;其他情况下启动T3212 。
      17.日    期   : 2012年02月29日
         作    者   : l00130025
         修改内容   : DTS2012022206186:不发起LAU,而注册成功时，需要同步注册状态给AS
      18.日    期   : 2012年03月17日
         作    者   : s46746
         修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
      19.日    期   : 2012年2月15日
         作    者   : z00161729
         修改内容   : V7R1C50 支持CSFB特性修改
      20.日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
      19.日    期   : 2012年05月21日
        作    者   :  z40661
        修改内容   : DTS2012052308001:从L重选到G后反复进行LAU
     22.日    期   : 2012年10月22日
        作    者   : t00212959
        修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
     23.日    期   : 2012年11月15日
        作    者   : t00212959
        修改内容   : DTS2012041801803:CFSB到FLA小区，紧急呼失败
     24.日    期   : 2012年12月24日
        作    者   : l65478
        修改内容   : DTS2012122402486:异系统重选过程中T3212超时重选结束后没有发起周期LU
     25.日    期   : 2013年1月23日
        作    者   : W00176964
        修改内容   : DTS2013012301238:GCF 26.7.4.3.4用例失败
     26.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
     27.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
     28.日    期   : 2013年9月12日
        作    者   : w00242748
        修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                    原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                    G下原小区时做LAU
     29.日    期   :2013年9月23日
        作    者   :w00242748
        修改内容   :DTS2013091407626:W下UE被叫，未收到网侧建联CNF前，发生重定向到G后，未发起LAU
     30.日    期   : 2014年04月1日
        作    者   : w00176964
        修改内容   : V3R3C60_eCall项目:系统消息处理优化
     31.日    期   : 2015年3月20日
        作    者   : w00167002
        修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                     进行封装。
     32.日    期   : 2015年5月21日
        作    者   : b00269685
        修改内容   : 若后续需要LAU，则不处理缓存
******************************************************************************/
VOS_VOID Mm_Cell_S3_E5(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrentNetRatType;
    VOS_UINT8                           ucT3211RunFlg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;
    VOS_UINT32                          ulEmergencyCallFlg;

    ulEmergencyCallFlg  = Mm_ComJudgeCsServExist();

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

    enCurrentNetRatType = NAS_MML_GetCurrNetRatType();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    ucT3211RunFlg       = VOS_FALSE;

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

    /* ==>AT2D01490 */
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();
    if ( (VOS_TRUE == ulLaiChangeFlag) ||
        ((g_MmGlobalInfo.MsCsInfo.ucCellChgFlg == MM_TRUE) && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)))
    {
        if (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3211].ucTimerStatus)
        {
            ucT3211RunFlg = VOS_TRUE;
            Mm_TimerStop(MM_TIMER_T3211);
        }
    }
    /* <==AT2D01490 */

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsAttachNotAllow();

        return;
    }

    if (VOS_TRUE == NAS_MM_IsCsForbidden())
    {
        NAS_MM_ProcCsForbidenFlg_RcvSysInfoInd(g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
    {
        NAS_MM_ProcMmcMmSysInfoInd_CsRegisterRestrict();

        return;
    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (VOS_FALSE == ucPsRestrictionFlg)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
      )
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else
            {
                if ( MMCMM_FORBIDDEN_PLMN_FOR_GPRS !=
                            g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg )
                {
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        else
        {                                                                       /* RAC不等于0                               */
            if ( VOS_TRUE == ulLaiChangeFlag )
            {
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_WAIT_FOR_ATTACH);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E5:NORMAL: STATUS is MM_WAIT_FOR_ATTACH");
            }
        }
    }
    else
    {                                                                           /* 非A+I模式                                */
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
        {
            return;
        }
#endif

        if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
        {
            Mm_ComNetModeChange();
        }
        else
        {
            if ( VOS_TRUE == ulLaiChangeFlag )
            {                                                               /* 如果LAI变                                */
                NAS_MM_ProcBufferedEmgCallOrLau_RcvSysinfo(ulLaiChangeFlag, MM_IE_LUT_NORMAL_LU);
            }
            else
            {
                if (VOS_TRUE == ucT3211RunFlg)
                {
                    Mm_ComLuOnly();
                }
                else
                {
                    /* A+0模式,PS不支持时,LAI不改变时,3212超时发起LAU不响应再次收到系统消息不应该
                       再次发起LAU */
                    if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                     && (MM_TIMER_RUNNING != gstMmTimer[MM_TIMER_T3211].ucTimerStatus))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType =
                                        MM_IE_LUT_PERIODIC_UPDATING;            /* 设置LU类型                               */
                        Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                        return;
                    }

                    if (VOS_TRUE == NAS_MM_IsDisableGprsCombineAttach())
                    {
                        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                    }
                }

                if (enCurrentNetRatType != g_MmGlobalInfo.enPreRatType)
                {
                    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-4, begin */

                    /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-4, end */

                    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
                    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                                            & MM_WAIT_CS_ATTACH))
                    {
                        NAS_MM_SndMmcAttachCnf();
                    }
                    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;
                }


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

            }
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
    }

    if ((WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState)
     && ((MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState)
      || (VOS_TRUE == ulEmergencyCallFlg)))
    {
        Mm_DealWithBuffMsg();
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S3_E9
  Function: 在MM IDLE NORMAL SERVICE状态下收到GMMMM_IMSI_DETACH_INITIATION的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2. 日    期   : 2008年09月03日
         作    者   : l00130025
         修改内容   : 问题单号：AT2D05403,mm注册状态修改
       3.日    期   : 2013年05月15日
         作    者   : s46746
         修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E9(VOS_VOID *pMsg)
{

    if ( MM_FALSE == Mm_RcvGmmImsiDetechIni(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E9:NORMAL: STATUS is IMSI_DETACH_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E11
  Function: 在MM IDLE NORMAL SERVICE状态下收到GMMMM_GPRS_DETACH_INITIATION的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2. 日    期   : 2008年09月03日
         作    者   : l00130025
         修改内容   : 问题单号：AT2D05403,mm注册状态修改
       3.日    期   : 2013年05月15日
         作    者   : s46746
         修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E11(VOS_VOID *pMsg)
{
    GMMMM_GPRS_DETACH_INITIATION_STRU   *pGprsDetachInit;

    if ( MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg) )
    {
        return;
    }

    pGprsDetachInit = (GMMMM_GPRS_DETACH_INITIATION_STRU*)pMsg;

    if ( GMMMM_GPRS_DETACH_NORMAL == pGprsDetachInit->enDetachType )
    {
        ;                                                                       /* 空处理                                   */
    }
    else
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(IMSI_DETACH_PENDING);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
    }
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S32_E32
 功能描述  : 挂起状态处理est cnf消息，出现在est req和接入层suspend ind消息对冲的场景
 输入参数  : pRcvMsg -消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年10月8日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log

*****************************************************************************/
VOS_VOID Mm_Cell_S32_E32(
    VOS_VOID                           *pRcvMsg
)
{
    if ( MM_FALSE == Mm_RcvRrcEstCnf(pRcvMsg) )
    {
        /* WUEPS_ASSERT(0); */
    }
    else
    {
        if (WAIT_FOR_RR_CONNECTION_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            if (NO_MM_CONN_ESTING != g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI )
            {
                /* CC发起的RR连接的建立, 通知CC建立失败             */
                Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else if ( NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI )
            {
                /* SS发起的RR连接的建立 ，通知SS,MM连接建立失败      */
                Mm_SndSsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);

                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else if ( NO_MM_CONN_ESTING !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI )
            {
                /* SMS发起的RR连接的建立 ,通知SMS,MM连接建立失败      */
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI,
                                   NAS_MMCM_REL_CAUSE_MM_INTER_ERR_INTER_RAT_SYSTEM_CHANGE);
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI = NO_MM_CONN_ESTING;
            }
            else
            {
                /* 没有正在建立的MM连接，即被叫 */
            }

            /* 业务触发的建链过程 */
            if ((MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
             || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
             || (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg))
            {

                Mm_SndMmcRrConnInfInd( MMC_MM_RR_CONN_ABSENT );
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            }

            /* 清除消息缓存标志 */
            NAS_MM_ClearConnCtrlInfo(g_MmGlobalInfo.ucMMConnEstingPD);

            g_MmGlobalInfo.ucSuspendPreState = g_MmGlobalInfo.ucStaOfRcvXXEstReq;
        }
    }

    return;
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

