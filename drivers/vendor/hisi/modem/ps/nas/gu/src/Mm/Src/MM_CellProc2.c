/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_CellProc2.c
  Description  : MM公共处理
  Function List:

  History:
      1. 日    期   : 2006年11月25日
         作    者   : s46746
         修改内容   : 问题单号：A32D07666
      2. 日    期   : 2007年01月12日
         作    者   : luojian id:60022475
         修改内容   : 问题单号：A32D08357
      3. 日    期   : 2007年3月5日
         作    者   : liurui id:40632
         修改内容   : 根据问题单号：A32D09094
      4. 日    期   : 2007年03月24日
         作    者   : luojian id:60022475
         修改内容   : 问题单号：A32D09756
      5. 日    期   : 2007年04月20日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单号：A32D10235
      6. 日    期   : 2007年05月14日
         作    者   : s46746
         修改内容   : 问题单号：A32D10820
      7. 日    期   : 2007年06月04日
         作    者   : luojian id:60022475
         修改内容   : 问题单号:A32D11456
      8. 日    期   : 2007年08月19日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单号：A32D12706
      9. 日    期   : 2007年09月05日
         作    者   : luojian id:60022475
         修改内容   : 根据问题单号：AT2D01490,MM收到系统消息需要判断LAI是否
                    发生改变来决定是否停T3211
      10.日    期   : 2007年9月21日
         作    者   : luojian id:107747
         修改内容   : 问题单号：AT2D01703,MMCMM_COMBINED_RAU_ACCEPTED消息增加
                      RealFlag标志
      11.日    期   : 2007年10月23日
         作    者   : l39007
         修改内容   : 问题单号：A32D13044,Mm_Cell_S17_E18,Mm_Cell_S17_E7修改
                      在RauAttCounter大于等于5时发起一次LAU的处理
      12.日    期   : 2007年11月12日
         作    者   : l39007
         修改内容   : 根据问题单A32D13044,ATTACH失败5次,通知MM发起一次LAU,
                      如果此时MM已经注册,则不发起
      13.日    期   : 2007年12月27日
         作    者   : l39007
         修改内容   : 根据问题单A32D13044,GPRS only Attached(#16),如果小于5次，
                      MM状态恢复前状态，如果大于5次，且CS域没有注册，发起一次LAU
      19.日    期   : 2008年05月13日
         作    者   : luojian id:107747
         修改内容   : 根据问题单号：AT2D03371,MM IDLE ATTEMPTING TO UPDATE状态下
                      LAI改变立刻发起LAU.
      20.日    期   : 2008年7月23日
         作    者   : luojian id:107747
         修改内容   : 根据问题单：AT2D04627/AT2D04237,
                      ATTEMPT TO UPDATE/ATTACH 状态对CM服务处理
      21.日    期   : 2008年7月25日
         作    者   : luojian 00107747
         修改内容   : 根据问题单号AT2D04142/AT2D04677,修改RAU ATTEMPT次数等于5次的处理
      22.日    期   : 2008年7月28日
         作    者   : s46746
         修改内容   : 问题单号:AT2D03915,修改联合RAU类型,CS如果已经单独LAU成功，需要
                      发起with IMSI Attach的RAU
      23.日    期   : 2008年7月31日
         作    者   : s46746
         修改内容   : 问题单号:AT2D04800,修改联合RAU类型,连续五次RAU失败后，单独
                      进行位置更新流程
      24.日    期   : 2008年8月13日
         作    者   : l0010747
         修改内容   : 问题单号:AT2D04996/AT2D05037,IDLE ATTEMPT TO UPDATE状态只发起Normal LAU.
      25.日    期   : 2008年8月21日
         作    者   : o00132663
         修改内容   : 问题单号:AT2D04652,当小区改变时，停止定时器 T3211
      26.日    期   : 2008年8月22日
         作    者   : ouyangfei 00132663
         修改内容   : 根据问题单号AT2D05087,对于网络的发起的业务，不检查手机的状态。
      27.日    期   : 2008年8月23日
         作    者   : l00130025
         修改内容   : 问题单号:At2D05016,MM注册状态修改
      28.日    期   : 2008年8月26日
         作    者   : o00132663
         修改内容   : 问题单号:AT2D05317,MM连接管理增强
      29.日    期   : 2008年09月03日
         作    者   : l00130025
         修改内容   : 问题单号：AT2D05403,mm状态修改
      30.日    期   : 2008年11月22日
         作    者   : o00132663
         修改内容   : 问题单号：AT2D06931, 清除标志位ucT3212ExpiredFlg
      31.日    期   : 2009年03月19日
         作    者   : s46746
         修改内容   : 问题单号：AT2D09167, 关机后后台显示为注册到2G
      32.日    期   : 2009年04月03日
         作    者   : s46746
         修改内容   : 问题单号：AT2D10632,TA认证，需要上报服务状态事件以及EPLMN、FPLMN和IMSI Detach事件
      33.日    期   : 2009年04月17日
         作    者   : s46746
         修改内容   : 问题单号：AT2D11062,MM在location update pend状态发生重选网络模式变更，
                      进行位置更新失败后没有重新再次发起位置更新
      34.日    期   : 2009年05月11日
         作    者   : h44270
         修改内容   : AT2D11661/AT2D11804,发起手动搜网打断LAU过程，导致搜网成功后发起两次LAU
      35.日    期   : 2009年06月24日
         作    者   : x00115505
         修改内容   : AT2D12550,W模式下联合注册成功，用户发起联合detach，未得到网络结果之前发生系统重选，
                      到G下，网络模式变为II，MM收到GSM系统消息后，先通知上层detach成功，然后发起了Lu?
      36.日    期   : 2009年07月03日
         作    者   : x00115505
         修改内容   : AT2D12716,MM在Limited Service状态下T3212超时，之后又回到
                      之前驻留的小区，发起的Lu类型是Normal，不是周期的
      37.日    期   : 2009年07月18日
         作    者   : s46746
         修改内容   : AT2D12943，CS Detach后，查询注册状态仍然为注册漫游网络

      38.日    期   : 2009年07月24日
         作    者   : z40661
         修改内容   : 异系统重选后，紧急呼叫不能接通
      39.日    期   : 2009年09月28日
         作    者   : x00115505
         修改内容   : 设置单板仅支持PS域，发送CS短信后接收不到
      40.日    期   : 2009年10月31日
         作    者   : x00115505
         修改内容   : AT2D15027,仅PS注册，短信发送走CS域时没有发起注册
      41.日    期   : 2009年11月26日
         作    者   : x00115505
         修改内容   : 设置服务域为PS ONLY，群发短信，仅第一条成功
      42.日    期   : 2009年12月24日
         作    者   : x00115505
         修改内容   : 问题单号:AT2D16025,2G下，detach过程中接入阻塞，detach失败

      43.日    期   : 2010年3月2日
        作    者   : zhoujun /z40661
        修改内容   : NAS R7协议升级
*******************************************************************************/

#include        "MM_Inc.h"
#include        "GmmMmInterface.h"
#include        "NasMmcProcNvim.h"
#include        "MM_Ext.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-10, begin */
#include        "NasMmEcall.h"
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-10, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_CELLPROC2_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

/*lint -save -e958 */

/*******************************************************************************
  Module:   Mm_Cell_S3_E13
  Function: 在MM IDLE NORMAL SERVICE状态下收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.09  新版做成
  2.  s46746  2006.02.28  A32D03324
  3.  s46746  2006-06-24  根据问题单A32D04439修改
  4. s46746  2006-07-27 根据问题单A32D03975修改
  5. x51137 2006/11/3 A32D06511
  6.日    期   : 2008年09月03日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D05403,mm注册状态修改
  7.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  8.日    期   : 2011年05月16日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011051005812，网络模式I,相同RAI,T3312超时时,
    从支持GPRS的3G小区重选到不支持GPRS的2G小区再重选回原来的3G小区,做联合RAU.
  9.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 10.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 11.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
 12.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*******************************************************************************/

VOS_VOID Mm_Cell_S3_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;

    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
        {
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);       /* 记录流程和原因值                         */

            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* 清除标志位                               */
            NAS_MML_InitUeIdTmsiInvalid();
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             MM_CKSN_INVALID);
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

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

            Mm_ComProcCauseClear();
        }
        else
        {
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);                     /* 调用DETACH原因值的公共处理               */
        }
    }
    else
    {                                                                           /* 如果为非A+I模式                          */
        if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
        {
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        }
        else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
        {
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                 /* 记录流程和原因值                         */

            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S3_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* 清除标志位                               */
            NAS_MML_InitUeIdTmsiInvalid();
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                             MM_CKSN_INVALID);

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


            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            Mm_ComProcCauseClear();
        }
        else
        {
            Mm_ComNetDetachCauseHandle(
                (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);                     /* 调用DETACH原因值的公共处理               */
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E15
  Function: 在MM IDLE NORMAL SERVICE状态下收到GMMMM_LU_INITIATION的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2.  张志勇     2005.01.27  007005 for MM
      3.日    期   : 2009年05月07日
        作    者   : l00130025
        修改内容   : 问题单号AT2D11351/AT2D11735,网络模式I,GPRS不支持时,MM注册成功后,在相同位置区反复发起LU
      4.日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;
    }

    pstMmcLuIni = (GMMMM_LU_INITIATION_STRU*)pMsg;

    if(  (GMMMM_NO_TIMER_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)
       &&(VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
    {
        return;                                                              /*非定时器超时引起的LU请求都是当LAI没改变时为了去除Gs关联。 */
    }

    if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
     && ((GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)
      || (GMMMM_T3412OrT3423_EXPIRED == pstMmcLuIni->enTimerExpiredFlg)))
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;        /* 设置LU类型为周期                         */
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                /* 设置LU类型为NORMAL                       */
    }

    Mm_ComLuOnly();                                                          /* 进行LU过程                               */

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E16
  Function: 在MM IDLE NORMAL SERVICE状态下收到
            GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E16(VOS_VOID *pMsg)
{
    VOS_UINT8 ucCause;

    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    if (LOCATION_UPDATING_INITIATED == g_MmGlobalInfo.ucState)
    {
        ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;
        NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_LOCATION_UPDATE_FAILURE,
                        &ucCause, NAS_OM_EVENT_LAU_FAIL_LEN);
    }
    Mm_ComAuthenRcvAuthenRej();                                                 /* 调用鉴权失败的公共处理                   */

    NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
}

/*******************************************************************************
  Module:   Mm_Cell_S3_E17
  Function: 在MM IDLE NORMAL SERVICE状态下收到GMMMM_COMBINED_RAU_INITIATION的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇      2003.12.09   新版做成
      2.  日    期   : 2008年8月21日
          作    者   : l00130025
          修改内容   : 问题单号:At2D05016,MM注册状态修改
      3.  日    期   : 2008年11月22日
          作    者   : o00132663
          修改内容   : 问题单号：AT2D06931, 清除标志位ucT3212ExpiredFlg
      4.  日    期   : 2011年07月15日
          作    者   : l65478
          修改内容   : 问题单号：DTS2011071101580, 系统间重选挂起失败
      5.  日    期   : 2012年06月1日
          作    者   : z00161729
          修改内容   : V7R1C50 GUL背景搜修改，L下开机联合注册eps only成功，cs处于未attach态，
                       bg搜高优先级网络成功，快速指定搜成功，网络注册过程syscfg设置ps
                       only,mm直接回复detach cnf和cs reg result ind迁到limit service状态，
                       后面再收到联合注册init消息不应迁状态
     6.日    期   : 2012年12月22日
       作    者   : l65478
       修改内容   : DTS2012122103936 发起紧急呼叫时MM状态迁移错误
     7.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
    8.日    期   : 2013年7月25日
      作    者    : w00242748
      修改内容    : DTS2013072200933:vodafone r8网络csfb mt到w，cs ps链接释放后1.5s内重选回l，
                    网络后续2s左右会重新下发paging消息，存在丢寻呼被叫打不通，参考标杆实现，
                    rau req中带follow on标志,无明确协议依据
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E17(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmCombinedRauInitiation(pMsg))
    {
        return;
    }
    NAS_MML_SetDelayedCsfbLauFlg(VOS_FALSE);

    if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
    {
        return;
    }

    /* 因为MM_WAIT_FOR_ATTACH为暂态,如果此时保存,当联合注册失败时,
       会恢复到注册前的状态,此时恢复到MM_WAIT_FOR_ATTACH会影响业务 */
    if (MM_WAIT_FOR_ATTACH != g_MmGlobalInfo.ucState)
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    }
    Mm_ComSetMmState(LOCATION_UPDATING_PENDING);

    g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;


    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E17:NORMAL: STATUS is  LOCATION_UPDATING_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E17
  Function: 在LOCATION UPDATING PENDING状态下收到GMMMM_COMBINED_RAU_INITIATION的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  欧阳飞      2009.03.11   新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S17_E17(VOS_VOID *pMsg)
{
    /* 在GSM下，如果原来收到COMBINED_RAU_ACCEPTED with PS ONLY ACCEPTED, 5次失败后MM会启定时器MM_TIMER_DELAY_LU_GSM
       延迟1秒发起LU, 如果此时又收到GMM的联合注册开始消息，需先停掉该定时器，避免同时发起RAU和LU */
    Mm_TimerStop(MM_TIMER_DELAY_LU_GSM);
}

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */

/* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */

/*******************************************************************************
  Module:   Mm_Cell_S4_E5
  Function: 在MM IDLE LIMITED SERVICE状态下收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.11  新版做成
      2.  s46746     2006.07.26  根据问题单A32D03975修改
      3.日    期   : 2006年10月6日
        作    者   : s46746
        修改内容   : 问题单号：A32D05960
      4.日    期   : 2007年04月20日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号：A32D10235
      5.日    期   : 2010年11月09日
        作    者   : 欧阳飞
        修改内容   : 根据问题单号：DTS2010111500211, GCF 9.4.3.3，LAU失败4次后发起列表搜期间，用户发起紧急呼，
                     中止列表搜，在原小区进行呼叫，呼叫结束后后，MM收到原小区的系统消息后发起了
                     不期望的LAU，应该在T3212超时后再发起LAU.
      6.日    期   : 2011年7月16日
        作    者   : h44270
        修改内容   : V7R1 PhaseII阶段调整，注册结果简化
      7.日    期   : 2011年06月02日
        作    者   : l65478
        修改内容   : DTS2011060103515 GCF测试，当限制服务下，用户指定当前驻留的网络进行指定搜索时，协议栈不会发起注册
      8.日    期   : 2011年6月3日
        作    者   : c00173809
        修改内容   : 根据问题单号：问题单号:DTS2011060102833,从禁止PLMN切换到非禁止PLMN时，非禁止网络的网络模式为I时，没有发起联合RAU，不符合协议 。
      8.日    期   : 2011年10月15日
        作    者   : h44270
        修改内容   : GUL NAS2阶段，当配置成PS ONLY时，当处于limit service，不回复注册结果结果
      9.日    期   : 2011年11月22日
        作    者   : w00166186
        修改内容   : DTS2011110902856,网络模式I下CS去注册，改为网络模式II后，发起CS ATTACH，不发起注册
      10.日    期   : 2011年10月27日
        作    者   : s46746
        修改内容   : V7R1 PhaseIII,支持L模联合注册
     11.日    期   : 2012年02月29日
        作    者   : l00130025
        修改内容   : DTS2012022206186:不发起LAU,而注册成功时，需要同步注册状态给AS
     12.日    期   : 2012年03月17日
        作    者   : s46746
        修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
     13.日    期   : 2012年2月20日
         作    者   : z00161729
         修改内容   : V7R1C50 支持CSFB特性修改
     14.日    期   : 2012年3月09日
         作    者   : w00167002
         修改内容   : V7R1C50 支持CSFB特性修改:当CSFB标志存在时，发起单独的LAU
     15.日    期   : 2012年3月09日
        作    者   : z00161729
        修改内容   : V7R1C50 支持ISR特性修改
     16.日    期   : 2012年05月21日
        作    者   : z40661
        修改内容   : DTS2012052308001:从L重选到G后反复进行LAU
     17.日    期   : 2012年10月22日
        作    者   : t00212959
        修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
     18.日    期   : 2012年11月13日
        作    者   : l00167671
        修改内容   : DTS2012111204799:L->W csfb,搜网从L到W时是PS域被拒11，电话挂断后没有发起搜网
     19.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
     20.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

     21.日    期   : 2013年12月5日
        作    者   : w00167002
        修改内容   : DTS2013113006231:W下，开机在LAC1上注册成功，重选到LAC2上，CS注册成功
                     PS注册被拒#13,重选回LAC1上，注册成功。丢网后任意小区驻留在LAC2
                     上，不发起注册，重选回LAC1上，检测不发起注册。
                     修改为在收到系统消息时候，不进行UPDATE状态的更新。
     22.日    期   : 2014年04月1日
        作    者   : w00176964
        修改内容   : V3R3C60_eCall项目:系统消息处理优化以及使用MML中的替换MM全局变量
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E5(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucLaChgFlg = VOS_FALSE;
    VOS_UINT8                           ucUserSpecificSearchFLg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag         = NAS_MML_IsCsfbServiceStatusExist();
#endif

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
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

    ucUserSpecificSearchFLg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);

    ucLaChgFlg = NAS_MML_IsCsLaiChanged();

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
     )
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S4_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            if ((VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
             || (VOS_TRUE == ucUserSpecificSearchFLg))
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            {
                /* LAI改变,或者用户发起的指定搜网时,发起LU过程 */
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
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

        if (g_MmGlobalInfo.ucNtMod == g_MmGlobalInfo.ucNewNtMod)
        {
            if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                && (VOS_FALSE == ucLaChgFlg))
            {
                g_MmGlobalInfo.LuInfo.ucLuType =
                                MM_IE_LUT_PERIODIC_UPDATING;            /* 设置LU类型                               */
                Mm_ComLuOnly();                                         /* 发送LU REQ                               */
            }
            else if ( (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                   && (VOS_FALSE == ucLaChgFlg))
            {
                if ((MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
                 && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg))
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;
                    Mm_ComLuOnly();
                }
                else if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                {
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                           "Mm_Cell_S4_E5:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");


                    Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);
                }
                else
                {
                }
            }
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            else if ((VOS_FALSE        == NAS_MML_IsCampLaiInfoChanged())
                  && (MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3212].ucTimerStatus)
                  && (VOS_FALSE        == ucUserSpecificSearchFLg))
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            {
                /* 当前驻留小区与上次驻留小区相同，并且T3212正在运行，此时不需要发起LAU，等T3212超时后发起 */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-30, begin */
                /* 上报注册失败,保证服务状态的正确性 */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-30, end */
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                Mm_ComLuOnly();                                         /* 发送LU REQ                               */
            }
        }
        else
        {
            Mm_ComNetModeChange();
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
    }

}

/*******************************************************************************
  Module:   Mm_Cell_S4_E15
  Function: 在MM IDLE LIMITED SERVICE状态下收到GMMMM_LU_INITIATION的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2. 日    期   : 2012年3月31日
         作    者   : z00161729
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU            *pstLuIniMsg;

    pstLuIniMsg  = (GMMMM_LU_INITIATION_STRU *)pMsg;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;

    }

    if (GMMMM_T3412OrT3423_EXPIRED == pstLuIniMsg->enTimerExpiredFlg)
    {
        /* 设置LU类型为周期 */
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    }
    else
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                       /* 设置LU类型为NORMAL                       */
    }

    Mm_ComLuOnly();                                                             /* 进行LU过程                               */
}

/*******************************************************************************
  Module:   Mm_Cell_S6_E15
  Function: 在MM IDLE LOCATION UPDATE NEEDED状态下收到GMMMM_LU_INITIATION的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  欧阳飞     2009.05.22  新版做成
      4. 日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;

    if (MM_FALSE == Mm_RcvGmmLuIni(pMsg))
    {
        return;

    }

    pstMmcLuIni = (GMMMM_LU_INITIATION_STRU*)pMsg;

    if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
        && (GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg) )
    {
        g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_TRUE;
    }

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S5_E5
  Function: 在MM IDLE ATTEMPTING TO UPDATE状态下收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.11  新版做成
      2.  s46746     2006.07.27  根据问题单A32D03975修改
      3.日    期   : 2006年10月6日
        作    者   : s46746
        修改内容   : 问题单号：A32D05960
      4.日    期   : 2006年10月22日
        作    者   : l60022475
        修改内容   : 问题单号：A32D07582
      5.日    期   : 2006年10月22日
        作    者   : l60022475
        修改内容   : 问题单号：A32D07583
      6.日    期   : 2007年3月5日
        作    者   : liurui id:40632
        修改内容   : 根据问题单号：A32D09094
      7.日    期   : 2007年04月20日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号：A32D10235
      8.日    期   : 2008年05月13日
        作    者   : luojian id:107747
        修改内容   : 根据问题单号：AT2D03371
      9.日    期   : 2008年8月13日
        作    者   : l0010747
        修改内容   : 问题单号:AT2D04996/AT2D05037
     10.日    期   : 2009年01月15日
        作    者   : l00130025
        修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
     11.日    期   : 2009年05月11日
        作    者   : h44270
        修改内容   : AT2D11661/AT2D11804,发起手动搜网打断LAU过程，导致搜网成功后发起两次LAU
     12.日    期   : 2009年08月6日
        作    者   : l65478
        修改内容   : 在重新回到原来的LA后，不应该发起LU
     13.日    期   : 2010年11月21日
        作    者   : z00161729
        修改内容  : 问题单号：DTS2010111602266:G下CS注册失败原因立即指派拒绝,MM在收到
                    RRMM_AC_INFORMATION_CHANGE_IND T3122超时消息后反复尝试LU,导致PS反复挂起恢复,影响数传性能
     14.日    期   : 2011年7月16日
        作    者   : h44270
        修改内容   : V7R1 PhaseII阶段调整，注册结果简化
     15.日    期   : 2011年06月02日
        作    者   : l65478
        修改内容   : DTS2011060103515 GCF测试，当限制服务下，用户指定当前驻留的网络进行指定搜索时，协议栈不会发起注册
     16.日    期   : 2011年6月3日
        作    者   : c00173809
        修改内容   : 根据问题单号：问题单号:DTS2011060102833,从禁止PLMN切换到非禁止PLMN时，非禁止网络的网络模式为I时，没有发起联合RAU，不符合协议 。
     17.日    期   : 2011年10月27日
        作    者   : s46746
        修改内容   : V7R1 PhaseIII,支持L模联合注册
     18.日    期   : 2012年1月30日
        作    者   : l00130025
        修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
     19.日    期   : 2012年03月17日
        作    者   : s46746
        修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
     20.日    期   : 2012年2月15日
         作    者   : z00161729
         修改内容   : V7R1C50 支持CSFB特性修改
     21.日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
     22.日    期   : 2012年3月09日
        作    者   : w00167002
        修改内容   : V7R1C50 支持CSFB特性修改:当CSFB标志存在时，发起单独的LAU
     23.日    期   : 2012年05月21日
        作    者   :  z40661
        修改内容   :  DTS2012052308001:从L重选到G后反复进行LAU
     24.日    期   : 2012年10月22日
        作    者   : t00212959
        修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
     25.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
     26.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
     27.日    期   : 2013年07月05日
        作    者   : l65478
        修改内容   : DTS2013070408274:MM进入NORMAL SERVICE后没有处理缓冲的CC消息
     28.日    期   :2013年10月8日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     29.日    期   : 2013年12月5日
        作    者   : w00167002
        修改内容   : DTS2013113006231:W下，开机在LAC1上注册成功，重选到LAC2上，CS注册成功
                  PS注册被拒#13,重选回LAC1上，注册成功。丢网后任意小区驻留在LAC2
                  上，不发起注册，重选回LAC1上，检测不发起注册。
                  修改为在收到系统消息时候，不进行UPDATE状态的更新。
     30.日    期   : 2014年04月1日
        作    者   : w00176964
        修改内容   : V3R3C60_eCall项目:系统消息处理优化以及使用MML中的替换MM的全局变量
     31.日    期   : 2015年5月27日
        作    者   : b00269685
        修改内容   : LAC变化则清除3213定时器
     32.日    期   : 2015年8月13日
        作    者   : l00289540
        修改内容   : User_Exp_Improve修改
*******************************************************************************/
VOS_VOID Mm_Cell_S5_E5(VOS_VOID *pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    VOS_UINT32                          ucLaChgFlg;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    VOS_UINT8                           ucUserSpecificSearchFlg;
    VOS_UINT32                          ul3211Status;

    VOS_UINT32                          ulT3213Status;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsfbExistFlag;
    VOS_UINT32                          ulIsTestCard;

    ulIsTestCard    = NAS_USIMMAPI_IsTestCard();

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();

#endif

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-17, begin */
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
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-17, end */



    ul3211Status = NAS_MM_QryTimerStatus(MM_TIMER_T3211);


    ulT3213Status = NAS_MM_QryTimerStatus(MM_TIMER_T3213);

    ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    ucLaChgFlg   = NAS_MML_IsCsLaiChanged();

    if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    {
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
        g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
        g_MmGlobalInfo.LuInfo.ucT3213AttmptCnt = 0;
    }

    if ( (MM_TIMER_RUNNING == NAS_MM_QryTimerStatus(MM_TIMER_T3213))
      && (MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg) )
    {
        /* 如果小区信息改变，则清除建链失败原因值，在T3213定时器超时时，发起LAU */
        NAS_MM_SetEstCnfResult(RRC_NAS_EST_RESULT_BUTT);
    }

    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
     && (MM_FALSE == g_MmGlobalInfo.ucLikeNetmode2)
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
        if ( (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
          || (MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
          || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {                                                                       /* RAC为0的场合                             */
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S5_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
            if ((VOS_TRUE       == NAS_MML_IsCampLaiInfoChanged())
             || ((VOS_TRUE      == ucUserSpecificSearchFlg)
              && (MM_TIMER_STOP == ul3211Status)))
            {
                /* LAI发生改变,或者用户指定搜网时,强制执行LU过程 */
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)
                   &&(MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* 发送LU REQ                               */
                g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;
            }
            else if (VOS_TRUE == NAS_MML_GetDelayedCsfbLauFlg())
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                if (VOS_FALSE == g_MmGlobalInfo.ucRetryLauFlg)
                {
                    /* 向MMC发送CS注册结果,当PS注册失败，假流程需要给MMC上报原因值为OTHER CAUSE */
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);          /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
                }

            }
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        else
        {                                                                       /* RAC不等于零                              */
            /*stop T3211*/
            Mm_TimerStop(MM_TIMER_T3211);
            g_MmGlobalInfo.LuInfo.ucImmAccRejLuAttmptCnt = 0;
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt          = 0;
        }
    }
    else
    {                                                                           /* 非A+I                                    */
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
#if (FEATURE_ON == FEATURE_LTE)
        if (VOS_TRUE == NAS_MM_RcvSysInfoSurpportLte_PreProc())
        {
            return;
        }
#endif

        if (g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod)
        {
            Mm_TimerStop(MM_TIMER_T3211);
            Mm_ComNetModeChange();
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        else if((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
             && (VOS_FALSE                              == ucLaChgFlg))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        {
            Mm_ComSysInfoHandleWithLaiNoChange(0);
            if (VOS_TRUE == ulIsTestCard)
            {
                Mm_TimerStop(MM_TIMER_T3213);
            }
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        else if ((VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
              || ((VOS_TRUE      == ucUserSpecificSearchFlg)
               && (MM_TIMER_STOP == ul3211Status)))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        {
            /* LAI发生改变,或者用户指定搜网时,强制执行LU过程 */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
        }
        else if ((MM_TRUE == g_MmGlobalInfo.LuInfo.ucRetryFlg)
            && (MM_TRUE == g_MmGlobalInfo.MsCsInfo.ucCellChgFlg))
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
            Mm_ComLuOnly();                                                 /* 发送LU REQ                               */
            g_MmGlobalInfo.MsCsInfo.ucCellChgFlg = MM_FALSE;
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;

            if (VOS_FALSE == g_MmGlobalInfo.ucRetryLauFlg)
            {
                /* 向MMC发送CS注册结果,当PS注册失败，假流程需要给MMC上报原因值为OTHER CAUSE */
                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);                 /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
                NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND,使MMC迁移状态 */
            }

        }

        /* 链路释放后需重新发起LAU,并且在收到sysinfo后没有发起LAU */
        if ((VOS_TRUE == g_MmGlobalInfo.ucRetryLauFlg)
            && (WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING != g_MmGlobalInfo.ucState))
        {
            Mm_ComLuOnly();
        }

    }
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */

    NAS_MM_ProcT3213AttemptCounter(ulT3213Status);

    /* 标志复位 */
    g_MmGlobalInfo.ucRetryLauFlg = VOS_FALSE;

    Mm_DealWithBuffMsg();

}

/*******************************************************************************
  Module:   Mm_Cell_S6_E5
  Function: 在MM_IDLE_LOCATION_UPDATE_NEEDED状态下收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2004.04.09  新版做成
  2.  s46746     2006.07.26  根据问题单A32D03975修改
  3.日    期   : 2006年10月6日
    作    者   : s46746
    修改内容   : 问题单号：A32D05960
  4.日    期   : 2006年11月22日
    作    者   : l60022475
    修改内容   : 问题单号：A32D07582
  5.日    期   : 2007年04月20日
    作    者   : luojian id:60022475
    修改内容   : 问题单号：A32D10235
  6.日    期   : 2007年09月05日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：AT2D01490
  7.日    期   : 2008年08月21日
    作    者   : ouyangfei id:00132663
    修改内容   : 问题单号：AT2D04652,当小区改变时，停止定时器 T3211
  8.日    期   : 2009年08月21日
    作    者   : ouyangfei id:00132663
    修改内容   : 问题单号：AT2D13967,当小区未改变且服务状态为U1时，MM迁回IDLE_NORMAL_SERVICE。
  9.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  10.日    期   : 2011年7月25日
     作    者   : h44270
     修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  11.日    期   : 2011年6月3日
     作    者   : c00173809
     修改内容   : 根据问题单号：问题单号:DTS2011060102833,从禁止PLMN切换到非禁止PLMN时，非禁止网络的网络模式为I时，没有发起联合RAU，不符合协议 。
  12.日    期   : 2012年2月15日
     作    者   : w00166186
     修改内容   : CSFB&PPAC&ETWS&ISR 开发
  13.日    期   : 2012年3月09日
     作    者   : w00167002
     修改内容   : V7R1C50 支持CSFB特性修改:当CSFB标志存在时，发起单独的LAU
  14.日    期   : 2012年10月22日
     作    者   : t00212959
     修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
  15.日    期   : 2013年2月4日
     作    者   : w00176964
     修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  16.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  17.日    期   : 2013年07月05日
     作    者   : l65478
     修改内容   : DTS2013070408274:MM进入NORMAL SERVICE后没有处理缓冲的CC消息
  18.日    期   : 2013年12月02日
     作    者   : w00242748
     修改内容   : DTS2013112712538:W NMOI cs上次在某位置区注册成功，再次开机后
                  收到系统消息指示该位置CS/PS被bar，此时不发起LAU或联合RAU；接着，
                  又收到系统消息，指示该位置区CS不被bar，PS被bar，此时不发起LAU
  19.日    期   : 2013年12月5日
     作    者   : w00167002
     修改内容   : DTS2013113006231:W下，开机在LAC1上注册成功，重选到LAC2上，CS注册成功
                  PS注册被拒#13,重选回LAC1上，注册成功。丢网后任意小区驻留在LAC2
                  上，不发起注册，重选回LAC1上，检测不发起注册。
                  修改为在收到系统消息时候，不进行UPDATE状态的更新。
  20.日    期   : 2014年3月21日
     作    者   : z00161729
     修改内容   : DTS2014031906506:GCF 8.1.2.16,w下联合注册成功，后上报系统消息cs注册禁止，后上报cs注册不禁止，ps注册被禁，mm收到系统
                 消息发起lau，用例期望不发起lau
  21.日    期   : 2014年04月1日
     作    者   : w00176964
     修改内容   : V3R3C60_eCall项目:系统消息处理优化
  22.日    期   : 2015年3月20日
     作    者   : w00167002
     修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                  进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S6_E5(VOS_VOID *pMsg)
{
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-17, begin */
    VOS_UINT32                          ulLaiChangeFlag;
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-17, end */

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

    /* ==>AT2D01490 */
    ulLaiChangeFlag =  NAS_MML_IsCsLaiChanged();
    if ((VOS_TRUE == ulLaiChangeFlag)
        || (g_MmGlobalInfo.MsCsInfo.ucCellChgFlg == MM_TRUE))
    {
        Mm_TimerStop(MM_TIMER_T3211);
    }
    /* <==AT2D01490 */

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
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
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
       )
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS             == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S6_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
            if (VOS_FALSE == ulLaiChangeFlag)
            {                                                               /* 如果LAI不变,更新状态为U1                 */
                if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;            /* 设置LU类型                               */
                    Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                }
                else if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED !=
                    NAS_MML_GetCsUpdateStatus())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                    Mm_ComLuOnly();                                         /* 发送LU REQ                               */
                }
                else
                {
                    Mm_ComNasInfoSav(
                             MM_STATUS_ATTACHED,
                             NAS_MML_GetSimCsSecurityCksn()
                             );
                    g_MmGlobalInfo.ucMmServiceState =
                        MM_NORMAL_SERVICE;                          /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S6_E5:INFO: MmServiceState is MM_NORMAL_SERVICE");
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);        /* 向MMC发送MMCMM_LU_RESULT_IND             */


                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S6_E5:NORMAL: STATUS is  MM_IDLE_NORMAL_SERVICE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                Mm_TimerStop(MM_TIMER_T3213);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* 发送LU REQ                               */
            }
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        else if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
        {
            if (VOS_FALSE == ulLaiChangeFlag)
            {                                                                   /* 如果LAI不变,更新状态为U1                 */
                if (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType =
                                    MM_IE_LUT_PERIODIC_UPDATING;                /* 设置LU类型                               */
                    Mm_ComLuOnly();                                             /* 发送LU REQ                               */
                }
                else if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED !=
                    NAS_MML_GetCsUpdateStatus())
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                    Mm_ComLuOnly();                                             /* 发送LU REQ                               */
                }
                else
                {
                    NAS_MM_RcvSysInfoPsRestrictRegLaiNoChangeU1();
                }
            }
            else
            {
                Mm_TimerStop(MM_TIMER_T3213);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* 发送LU REQ                               */
            }
        }
        else
        {                                                                       /* RAC不等于零                              */
            ;
        }
    }
    else
    {
        ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);
        Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                       /* 调用在系统信息的公共处理                 */
    }


    Mm_DealWithBuffMsg();
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E13
  Function: 在WAIT FOR OUTGOING MM CONNECTION状态下
            收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
      3.日    期   : 2013年9月12日
        作    者   : w00242748
        修改内容   : DTS2013090308589:MM处于重建状态时，收到CC REL REQ请求，迁回
                     原状态(IDLE NORMAL SERVICE)，未启动T3212定时器，导致搜网重回
                     G下原小区时做LAU
      4.日    期   : 2013年9月14日
        作    者   : z00161729
        修改内容   : DTS2013082903019:支持ss重发功能
      5.日    期   : 2014年4月2日
        作    者   : w00176964
        修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
      6.日    期   :2014年9月24日
        作    者   :s00217060
        修改内容   :for cs_err_log
      2.日    期   : 2015年3月20日
        作    者   : w00167002
        修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                    进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }
    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if (GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType)
    {
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if (GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType)
    {
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                     /* 记录流程和原因值                         */
    }
    else
    {
        switch (pstNetWkDetachInd->ulDetachCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
            Mm_TimerStop(MM_TIMER_T3230);                                       /* 停止T3230                                */
            if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
            {
                /* 释放除紧急呼外所有存在和正在建立的MM连接 */
                Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
            }
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* 调用删除IMSI的公共处理                   */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            if ((MM_FALSE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                ucEstingCallTypeFlg)
                && (MMCC_EMERGENCY_CALL !=
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                RcvXXEstReq.ulCallType))
            {
                Mm_TimerStart(MM_TIMER_T3240);                                  /* 启动T3240                                */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E14
  Function: 在WAIT FOR OUTGOING MM CONNECTION状态下,
                收到GMMMM_GMM_ACTION_RESULT_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2.  张志勇        2005.01.27  007037 for MM
      3.日    期   : 2011年03月31日
        作    者   : c00173809
        修改内容   : 问题单号:DTS2011032802664,UE驻留VPLMN发起BG搜,驻留高优先级
                     网络,COMBINED RAU PS成功,CS拒绝原因15,没搜当前网络.
      4.日    期   : 2012年10月29日
        作    者   : z00161729
        修改内容   : DTS2012083102536:支持cc呼叫重建
      5.日    期   : 2013年1月16日
        作    者   : w00176964
        修改内容   : DTS2013011508939:A+I模式,PS注册失败达到最大次数需要记录LIKEB标记
      6.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
      7.日    期   : 2013年9月14日
        作    者   : z00161729
        修改内容   : DTS2013082903019:支持ss重发功能
      8.日    期   : 2014年4月2日
        作    者   : w00176964
        修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
      9.日    期   :2014年9月24日
        作    者   :s00217060
        修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                               ucActionType;
    GMMMM_GMM_ACTION_RESULT_IND_STRU       *pstGmmActionRstInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {                                                                           /* 结果为失败的场合                         */
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:                                                 /* 类型为RAU的场合                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* 类型为ATTACH的场合                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* 类型为SR的场合                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            ucActionType = MM_NULL_PROC;
            break;
        }
        if (MM_NULL_PROC != ucActionType)
        {                                                                       /* 如果类型不为空的场合                     */
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_T3230);                                   /* 停止T3230                                */
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                Mm_TimerStop(MM_TIMER_T3210);                               /* 停止T3210                                */
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                       (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmServiceState is MM_NO_IMSI");
                /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

                /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                {
                    /* 释放除紧急呼外所有存在和正在建立的MM连接 */
                    Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
                }
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                if ((MM_FALSE ==
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    ucEstingCallTypeFlg)
                    && (MMCC_EMERGENCY_CALL !=
                    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                    RcvXXEstReq.ulCallType))
                {
                    Mm_TimerStart(MM_TIMER_T3240);                          /* 启动T3240                                */
                    Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                    Mm_TimerStop(MM_TIMER_T3210);                               /* 停止T3210                                */
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                           (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmServiceState is MM_NO_IMSI");
                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                    {
                        /* 释放除紧急呼外所有存在和正在建立的MM连接 */
                        Mm_ComRelAllMmConnExcEmergencyCall(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);
                    }
                    Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

                    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                    if ((MM_FALSE ==
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        ucEstingCallTypeFlg)
                        && (MMCC_EMERGENCY_CALL !=
                        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                        RcvXXEstReq.ulCallType))
                    {
                        Mm_TimerStart(MM_TIMER_T3240);                          /* 启动T3240                                */
                        Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E14:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                    }
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 类似于B模式的全局量                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                           (VOS_UINT8)pstGmmActionRstInd->enCause);   /* 记录流程和原因值                         */
                break;
            case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
            case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
            case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
                break;
            default:

                /* A+I下,PS注册失败达到最大次数,MM正在进行紧急呼叫,此时需要通知MMC当前CS继续尝试注册
                   等待RRC重新驻留后发起LAU或联合attach */
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }

                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S9_E44
  Function: 在WAIT FOR OUTGOING MM CONNECTION状态下
            收到RRMM_DATA_IND(MM STATUS)的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
        1.  张志勇     2003.12.09  新版做成
*******************************************************************************/

VOS_VOID Mm_Cell_S9_E44(VOS_VOID *pMsg)
{
    if (MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState)
    {
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
    }
}
/*******************************************************************************
  Module:   Mm_Cell_S11_E9
  Function: 在WAIT_FOR_NETWORK_COMMAND状态下
            收到GMMMM_IMSI_DETACH_INITIATION的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2.日    期   : 2008年09月03日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05403,mm注册状态修改
      3.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/

VOS_VOID Mm_Cell_S11_E9(VOS_VOID *pMsg)
{

    if ( MM_FALSE == Mm_RcvGmmImsiDetechIni(pMsg) )
    {
        return;

    }

    Mm_TimerStop(MM_TIMER_T3240);                                               /* 停T3240                                  */

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E9:NORMAL: STATUS is IMSI_DETACH_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E11
  Function: 在WAIT_FOR_NETWORK_COMMAND状态下
            收到GMMMM_GPRS_DETACH_INITIATION的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E11(VOS_VOID *pMsg)
{
    if (MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3240);                                               /* 停T3240                                  */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
}


/*******************************************************************************
  Module:   Mm_Cell_S11_E13
  Function: 在WAIT_FOR_NETWORK_COMMAND状态下收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2.日    期   : 2014年4月2日
        作    者   : w00176964
        修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
      3.日    期   : 2015年3月20日
        作    者   : w00167002
        修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                     进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if (MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg))
    {
        return;

    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* 记录流程和原因值                         */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
            g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* 调用删除IMSI的公共处理                   */
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                      (VOS_UINT8)pstNetWkDetachInd->ulDetachCause);   /* 记录流程和原因值                         */
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E14
  Function: 在WAIT_FOR_NETWORK_COMMAND状态下
            收到GMMMM_GMM_ACTION_RESULT_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2.日    期   : 2011年03月31日
        作    者   : c00173809
        修改内容   : 问题单号:DTS2011032802664,UE驻留VPLMN发起BG搜,驻留高优先级
                     网络,COMBINED RAU PS成功,CS拒绝原因15,没搜当前网络.
      3.日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
      4.日    期   : 2014年4月2日
        作    者   : w00176964
        修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E14(VOS_VOID* pMsg)
{
    VOS_UINT8                                   ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if ( MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg) )
    {
        return;

    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult )
    {                                                                           /* 结果为失败的场合                         */
        switch ( pstGmmActionRstInd->enGmmActionType )
        {
        case GMMMM_ACTION_RAU:                                                 /* 类型为RAU的场合                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* 类型为ATTACH的场合                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* 类型为SR的场合                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }
        if ( MM_NULL_PROC != ucActionType )
        {                                                                       /* 如果类型为空的场合                       */
            switch ( pstGmmActionRstInd->enCause )
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                Mm_ComSaveProcAndCauseVal(ucActionType,
                                  (VOS_UINT8)pstGmmActionRstInd->enCause);        /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmServiceState is MM_NO_IMSI");
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_AGENT);
                    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                      (VOS_UINT8)pstGmmActionRstInd->enCause);        /* 记录流程和原因值                         */
                    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;               /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmServiceState is MM_NO_IMSI");
                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                    Mm_ComToNoImsiHandle();                                     /* 调用删除IMSI的公共处理                   */
                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 类似于B模式的全局量                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                    Mm_ComSaveProcAndCauseVal(ucActionType,
                                      (VOS_UINT8)pstGmmActionRstInd->enCause);        /* 记录流程和原因值                         */
                break;
            case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
            case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
            case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
                break;
            default:
                /* A+I下,PS注册失败达到最大次数,MM正在进行紧急呼叫,此时需要通知MMC当前CS继续尝试注册
                   等待RRC重新驻留后发起LAU或联合attach */
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }
                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S11_E16
  Function: 在WAIT_FOR_NETWORK_COMMAND状态下
            收到GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E16(VOS_VOID *pMsg)
{
    if ( MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg) )
    {
        return;

    }
    Mm_ComSaveProcAndCauseVal(MM_AUTH_FAIL_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);            /* 记录流程和原因值                         */
    g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                               /* 设置服务状态                             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S11_E16:INFO: MmServiceState is MM_NO_IMSI");
    Mm_ComToNoImsiHandle();                                                     /* 调用删除IMSI的公共处理                   */
}

/*******************************************************************************
  Module:   Mm_Cell_S12_E13
  Function: 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下,
                收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇     2003.12.09  新版做成
  2.张志勇        2005.01.27  007037 for MM
  3.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年9月14日
    作    者   : z00161729
    修改内容   : DTS2013082903019:支持ss重发功能
  6.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
  7.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
  8.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstNetWkDetachInd;
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg) )
    {
        return;
    }

    if (NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
    {
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    g_MmGlobalInfo.ucProc = MM_NET_DETACH_PROC;                                 /* 记录当前的流程                           */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmServiceState is MM_NET_DETACH_PROC");
    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
        g_MmGlobalInfo.ucLikeB = MM_TRUE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
    }
    else if ( GMMMM_NET_DETACH_IMSI == pstNetWkDetachInd->enDetachType )
    {
        Mm_TimerStop(MM_TIMER_T3230);                                           /* 停止T3230                                */
        Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

        Mm_ComSaveProcAndCauseVal(MM_NET_DETACH_PROC,
                                                    NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);   /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;              /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        Mm_ComToU2Handle();                                                     /* 调用MM进U2的处理                         */
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        Mm_SndRrRelReq(RRC_CELL_UNBARRED);
        /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
        /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
        /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        Mm_TimerStop(MM_TIMER_T3218);                                           /* 停T3218                                  */
        Mm_ComDelRandRes();                                                     /* 删除RAND和RES                            */
    }
    else
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_T3230);                                       /* 停止T3230                                */
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);

            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 类似于B模式的全局量                      */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
            Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

            /* 网络发起 DETACH后MS不再ATTACH:这个地方回复cs detach更合适，不应该回复forb other */
            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

            Mm_ComNetDetachCauseHandle((VOS_UINT8)pstNetWkDetachInd->ulDetachCause);
            Mm_SndRrRelReq(RRC_CELL_UNBARRED);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                            /* 通知MMC，CS域的业务已经停止              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
            break;
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
            {
                Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                /* 网络发起 DETACH后MS不再ATTACH:这个地方回复cs detach更合适，不应该回复forb other */
                Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);

                Mm_ComNetDetachCauseHandle(
                                    (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                        /* 通知MMC，CS域的业务已经停止              */
                NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S12_E14
  Function: 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下,
                收到GMMMM_GMM_ACTION_RESULT_IND的处理
  Input:    VOS_VOID* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇     2003.12.09  新版做成
  2.张志勇        2005.01.27  007037 for MM
  3.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  5.日    期   : 2013年1月16日
    作    者   : w00176964
    修改内容   : DTS2013011508939:A+I模式,PS注册失败达到最大次数需要记录LIKEB标记
  6.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  7.日    期   :2013年9月14日
   作    者   :z00161729
   修改内容  :DTS2013082903019:支持ss重发功能
  8.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E14(VOS_VOID* pMsg)
{

    VOS_UINT8                                ucActionType = MM_NULL_PROC;
    GMMMM_GMM_ACTION_RESULT_IND_STRU        *pstGmmActionRstInd;
    VOS_UINT32                               ulCsServExist;

    if (MM_FALSE == Mm_RcvGmmGmmActionResultInd(pMsg))
    {
        return;

    }

    ulCsServExist  = Mm_ComJudgeCsServExist();
    if (MM_CS_SERV_EMERGENCY_CALL_EXIST == ulCsServExist)
    {
        return;
    }

    pstGmmActionRstInd = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)pMsg;

    if (GMMMM_ACTION_FAILURE == pstGmmActionRstInd->enActionResult)
    {                                                                           /* 结果为失败的场合                         */
        switch (pstGmmActionRstInd->enGmmActionType)
        {
        case GMMMM_ACTION_RAU:                                                 /* 类型为RAU的场合                          */
            ucActionType = MM_GMM_RAU_PROC;
            break;
        case GMMMM_ACTION_ATTACH:                                              /* 类型为ATTACH的场合                       */
            ucActionType = MM_GMM_ATTACH_PROC;
            break;
        case GMMMM_ACTION_SR:                                                  /* 类型为SR的场合                           */
            ucActionType = MM_GMM_SR_PROC;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E14:WARNING: ulGmmActionType Abnormal");
            break;
        }

        if (MM_NULL_PROC != ucActionType)
        {
            switch (pstGmmActionRstInd->enCause)
            {
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
            case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
                Mm_TimerStop(MM_TIMER_T3230);                                   /* 停止T3230                                */
                if ( ( MM_GMM_SR_PROC == ucActionType ) ||
                    ( ( MM_GMM_ATTACH_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                            g_MmSubLyrShare.MmShare.ucCsAttachState ) ) ||
                    ( ( MM_GMM_RAU_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
                    /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
                    /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
                if ( MM_GMM_ATTACH_PROC == ucActionType )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
                g_MmGlobalInfo.ucLikeB = MM_TRUE;                               /* 类似于B模式的全局量                      */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S12_E14:INFO: MmLikeB is MM_TRUE");
                break;
            case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
                if ( ( MM_GMM_SR_PROC == ucActionType ) ||
                    ( ( MM_GMM_ATTACH_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) ||
                    ( ( MM_GMM_RAU_PROC == ucActionType ) &&
                    ( MM_STATUS_ATTACHED ==
                                g_MmSubLyrShare.MmShare.ucCsAttachState ) ) )
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;
            case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
            case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
                if (MM_STATUS_ATTACHED ==
                                    g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

                        /* 原因值12被拒不触发搜网待着不动不再尝试重播，服务状态是MM_COM_SRVST_LIMITED_SERVICE_REGION,*/
                        if (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == pstGmmActionRstInd->enCause)
                        {
                            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_LA);
                        }
                        else
                        {
                            Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_FORB_OTHER);
                        }

                    Mm_ComCauseHandleAllProc(
                                            ucActionType,
                                            pstGmmActionRstInd->enCause);
                    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
                    Mm_SndMmcCmSvcInd(MM_CS_SERV_NOT_EXIST);                    /* 通知MMC，CS域的业务已经停止              */
                    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);

                }
                break;

            default:
                /* A+I下,PS注册失败达到最大次数,MM正在进行紧急呼叫,此时需要通知MMC当前CS继续尝试注册
                   等待RRC重新驻留后发起LAU或联合attach */
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
                if ((VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNewNtMod))
                 && (pstGmmActionRstInd->ucAttCounter >= 5)
                 && (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstGmmActionRstInd->enCause))
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
                {
                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_FAILURE,
                                                NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU);

                    g_MmGlobalInfo.ucLikeB = MM_TRUE;
                }
                break;
            }
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S12_E16
  Function: 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下,
                收到GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇     2003.12.09  新版做成
  2.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
  4.日    期   :2013年9月14日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  5.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/

VOS_VOID Mm_Cell_S12_E16(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmAuthFailInd(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_STOP_ALL);                                            /* 停保护定时器                             */

    Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

    Mm_ComAuthenRcvAuthenRej();                                                 /* 调用鉴权失败的公共处理                   */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);
    /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, begin */
    /* Mm_SndMmcCmSvcInd在Mm_ComRelAllMmConn中上报 */
    /* Deleted by s00217060 for K3V3 多模多天线特性, 2014-07-22, end */
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

}
/*******************************************************************************
  Module:   Mm_Cell_S14_E13
  Function: 在WAIT FOR REESTABLISH（WAIT FOR EST_CNF）状态下,
                收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.11  根据二期接口改造,新版做成
*******************************************************************************/

VOS_VOID Mm_Cell_S14_E13(VOS_VOID *pMsg)
{
    if (MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg)
    {
        Mm_Cell_S9_E13(pMsg);
        Mm_TimerStop(MM_TIMER_T3230);                                           /* 停止T3230                                */
    }
    else
    {
        Mm_Cell_S12_E13(pMsg);
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S14_E14
  Function: 在WAIT FOR REESTABLISH（WAIT FOR EST_CNF）状态下,
                收到GMMMM_GMM_ACTION_RESULT_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.11  根据二期接口改造,新版做成
*******************************************************************************/

VOS_VOID Mm_Cell_S14_E14(VOS_VOID *pMsg)
{
    if ( MM_CS_SIG_CONN_PRESENT == g_MmGlobalInfo.ucCsSigConnFlg )
    {
        Mm_Cell_S9_E14(pMsg);
    }
    else
    {
        Mm_Cell_S12_E14(pMsg);
    }
}


/*******************************************************************************
  Module:   Mm_Cell_S14_E16
  Function: 在WAIT FOR REESTABLISH（WAIT FOR EST_CNF）状态下,
                收到GMMMM_AUTHENTICATON_FAILURE_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2004.03.11  根据二期接口改造,新版做成
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E16(VOS_VOID *pMsg)
{
    Mm_ComAuthenRcvAuthenRej();
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E5
  Function: 在LOCATION UPDATING PENDING状态下收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.11  新版做成
  2.  s46746     2006.07.26  根据问题单A32D03975修改
  3.日    期   : 2006年10月6日
    作    者   : s46746
    修改内容   : 问题单号：A32D05960
  4.日    期   : 2007年04月20日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D10235
  5.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  6.日    期   : 2011年05月16日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011051005812，网络模式I,相同RAI,T3312超时时,从支持GPRS的3G小区重选到不支持GPRS的2G小区再重选回原来的3G小区,做联合RAU.
  7.日    期   : 2011年6月3日
    作    者   : c00173809
    修改内容   : 根据问题单号：问题单号:DTS2011060102833,从禁止PLMN切换到非禁止PLMN时，非禁止网络的网络模式为I时，没有发起联合RAU，不符合协议 。
  8.日    期  : 2012年2月15日
    作    者  : w00167002
    修改内容  : V7R1C50 支持CSFB特性修改，增加对存在CSFB标志时的处理
  9.日    期  : 2012年2月15日
    作    者  : w00176964
    修改内容  : DTS2012111301625:Pending状态不需要判断like B标记
 10.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 11.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 12.日    期   : 2013年07月05日
    作    者   : l65478
    修改内容   : DTS2013070408274:MM进入NORMAL SERVICE后没有处理缓冲的CC消息

 13.日    期   : 2013年12月5日
    作    者   : w00167002
    修改内容   : DTS2013113006231:W下，开机在LAC1上注册成功，重选到LAC2上，CS注册成功
                  PS注册被拒#13,重选回LAC1上，注册成功。丢网后任意小区驻留在LAC2
                  上，不发起注册，重选回LAC1上，检测不发起注册。
                  修改为在收到系统消息时候，不进行UPDATE状态的更新
 14.日    期   : 2014年04月1日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目:系统消息处理优化
*******************************************************************************/
VOS_VOID Mm_Cell_S17_E5(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucUserSpecificSearchFlg = 0;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCsfbExistFlag;

    /* 取得CSFB是否存在的标志 */
    ulCsfbExistFlag     = NAS_MML_IsCsfbServiceStatusExist();
#endif

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

    /* CS ONLY或PS ONLY，nmo1下GMM进行联合注册 */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNewNtMod)
     /* pending状态不需要判断like B标记 */
#if  (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsfbExistFlag)
#endif
    )
    {                                                                           /* 如果为A+I,且不是类似B或A+II处理的场合    */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
        /* RAC为0的场合 */
        if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
         || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            NAS_MM_SetLikeBFlg();

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E5:INFO: MmLikeB is MM_TRUE");

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, begin */
            if (VOS_TRUE == NAS_MML_IsCampLaiInfoChanged())
            {                                                               /* LAI变化的场合                            */
                Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
                PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E5:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;       /* 设置LU类型                               */
                Mm_ComLuOnly();                                             /* LU REQ                                   */
            }
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
        }
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-2, end */
    }
    else
    {                                                                           /* 非A+I模式                                */
        if ( g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod )
        {
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E5:NORMAL: ucState = ", g_MmGlobalInfo.ucState);
            Mm_ComNetModeChange();
        }
        else
        {   /* A+II或者B模式                            */
            ucUserSpecificSearchFlg = Mm_Get_UserSpecificSearchFlg_From_SysInfo(pMsg);
            Mm_ComRcvSysHandle(ucUserSpecificSearchFlg);                                               /* 调用在系统信息的公共处理                 */
        }
    }

    Mm_DealWithBuffMsg();
}


/*******************************************************************************
  Module:   Mm_Cell_S17_E7
  Function: 在LOCATION UPDATING PENDING状态下,
                收到GMMMM_COMBINED_ATTACH_ACCEPTED的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
      2.  x51137  2006/4/14 A32D02955
      3.  s46746  2006-06-24  根据问题单A32D04439修改
      4.日    期   : 2007年10月23日
        作    者   : l39007
        修改内容   : 问题单号：A32D13044
      5.日    期   : 2007年11月12日
        作    者   : l39007
        修改内容   : 根据问题单A32D13044,ATTACH失败5次,通知MM发起一次LAU,
                     如果此时MM已经注册,则不发起
      6.日    期   : 2007年12月27日
        作    者   : l39007
        修改内容   : 根据问题单A32D13044,GPRS only Attached(#16),如果小于5次，
                     MM状态恢复前状态，如果大于5次，且CS域没有注册，发起一次LAU
      7.日    期   : 2008年7月25日
        作    者   : luojian 00107747
        修改内容   : 根据问题单号AT2D04142/AT2D04677,修改RAU ATTEMPT次数等于5次的处理
      8.日    期   : 2010年9月30日
        作    者   : 欧阳飞 00132663
        修改内容   : 根据问题单号DTS2010092902368,TMSI只在等效PLMN内有效
      9.日    期   : 2010年11月24日
        作    者   : 王毛 00166186
        修改内容   : 根据问题单号DTS2010112205253,联合ATTACH成功的分支，清除LAU记数器
    10. 日    期   : 2010年12月24日
        作    者   : s46746
        修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
    11.日    期   : 2011年7月25日
       作    者   : h44270
       修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
    12.日    期   : 2011年12月25日
       作    者   : w00166186
       修改内容   : DT2011121903902,重选L后，回W后联合注册被16拒5次后，不发起LAU
    13.日    期   : 2012年3月1日
       作    者   : w00176964
       修改内容   : DTS2012022407450:GMM进行联合注册时，通知给MM,MM记录下来
    14.日    期   : 2012年03月17日
       作    者   : s46746
       修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
    15.日    期   : 2013年05月15日
       作    者   : s46746
       修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
    16.日    期   : 2013年07月5日
       作    者   : w00176964
       修改内容   : DTS2013062503351:LAU成功时更新当前的RAC信息
    17.日    期   : 2014年2月18日
       作    者   : l00215384
       修改内容   : DTS2014021006453，注册成功后鉴权拒绝计数清零
    18.日    期   : 2014年4月2日
       作    者   : w00176964
       修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
    19.日    期   : 2015年3月20日
       作    者   : w00167002
       修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                    进行封装。
    20.日    期   : 2015年8月13日
       作    者   : l00289540
       修改内容   : User_Exp_Improve修改
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E7(VOS_VOID *pMsg)
{

    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU     *pCombinedAttatchAccpt;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );


    if ( MM_FALSE == Mm_RcvGmmCombinedAttachAccept(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    pCombinedAttatchAccpt = (GMMMM_COMBINED_ATTACH_ACCEPTED_STRU*)pMsg;
    if ( GMMMM_ATTACH_RESLUT_COMBINED ==
                        pCombinedAttatchAccpt->enAttachResult )
    {
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
        g_MmGlobalInfo.ucLikeB = MM_FALSE;                                      /* 设置类似于B模式的全局量                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmLikeB is MM_FALSE");
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
        Mm_TimerStop( MM_TIMER_T3211 );                                         /* 停T3211                                  */
        Mm_ComSaveProcAndCauseVal(MM_COMB_ATTACH_PROC, NAS_MML_REG_FAIL_CAUSE_NULL);      /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                    /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmServiceState is MM_NORMAL_SERVICE");
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

        /* 记录注册成功的RAC，用于网络模式改变,比较RAI是否发生改变 */
        g_MmGlobalInfo.MsCsInfo.ucOldRac = NAS_MML_GetCurrCampRac();

        /* 由于网络模式改变,RAI不改变时,MM没有更新网络模式,而GMM模块可能会
           进行联合过程，为保证后续流程与GMM一致，此处需要更新网络模式 */
        g_MmGlobalInfo.ucNtMod           = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        pstCsSuccLai->stPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        pstCsSuccLai->aucLac[0] = NAS_MML_GetCurrCampLai()->aucLac[0];
        pstCsSuccLai->aucLac[1] = NAS_MML_GetCurrCampLai()->aucLac[1];
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

        pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);

        g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

        if ( GMMMM_MS_ID_TYPE_IMSI ==
                                pCombinedAttatchAccpt->stMsIdentity.enMsIdType )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                    ~MM_MS_ID_TMSI_PRESENT;     /* 设置TMSI无效                             */
            NAS_MML_InitUeIdTmsiInvalid();
        }
        else if ( GMMMM_MS_ID_TYPE_TMSI ==
                            pCombinedAttatchAccpt->stMsIdentity.enMsIdType )
        {
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |=
                                                    MM_MS_ID_TMSI_PRESENT;      /* 设置TMSI无效                             */
            PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                       pCombinedAttatchAccpt->stMsIdentity.aucTmsi,
                       NAS_MML_MAX_TMSI_LEN);
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
            g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        }
        else
        {

        }
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {/* 3G USIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
        }
        else
        {/* 2G SIM */
            Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
        }

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

        if (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg)
        {
            g_MmGlobalInfo.ucPowerOnFlg = MM_FALSE;
        }

        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /* LAU 记数器清零 */

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        pstAuthRejInfo = NAS_MML_GetAuthRejInfo();
        pstAuthRejInfo->ucHplmnCsAuthRejCounter = 0;


        /* 标示MM正在进行联合注册 */
        g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E7:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
    }
    else
    {
        switch(pCombinedAttatchAccpt->enCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
            g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
            Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
            Mm_TimerStop( MM_TIMER_T3211 );                                         /* 停T3211                                  */
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_ATTACH_PROC,
                                      (VOS_UINT8)pCombinedAttatchAccpt->enCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E7:INFO: MmServiceState is MM_NO_IMSI");
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* 调用进NO IMSI的公共处理                  */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E7:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        case NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE:
        case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:
            if ( pCombinedAttatchAccpt->ulAttachAttCounter < MM_RAU_ATTACH_COUNTER_MAX)
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() )
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
                {

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                }

                if( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                }
            }
            else
            {
                /**************************************************************
                The MM sublayer shall act as in network operation mode II or III
                (depending whether a PCCCH is present) as long as the combined
                GMM procedures are not successful and no new RA is entered. The
                new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
                ***************************************************************/
                g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
                g_MmGlobalInfo.ucLikeB        = MM_TRUE;

                /*if CS is already attached,don't LAU any more*/
                if(MM_STATUS_ATTACHED != g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    if(( MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg ) && ( MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg ))
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;             /* 设置LU类型                               */
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;              /* 设置LU类型                               */
                    }
                    Mm_ComLuOnly();                                                                     /* 发送LU REQ                               */
                }
                else
                {
                    Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);

                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S17_E7:WARNING: Cause Abnormal");
            /* WUEPS_ASSERT(0); */                                                    /* 异常错误处理                             */
            break;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttatchAccpt->enCause);
    }
    Mm_ComProcCauseClear();
    Mm_ComCheckDelayMmConn( MM_TRUE );
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E8
  Function: 在LOCATION UPDATING PENDING状态下
            收到GMMMM_COMBINED_ATTACH_REJECTED的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.10  新版做成
  2.  s46746  2006.02.28  A32D03324
  3 . x51137  2006/4/14 A32D02955
  4.日    期   : 2008年7月25日
    作    者   : luojian 00107747
    修改内容   : 根据问题单号AT2D04142/AT2D04677
  5.日    期   : 2008年8月21日
    作    者   : l00130025
    修改内容   : 问题单号:At2D05016,MM注册状态修改
  6.日    期   : 2008年9月3日
    作    者   : l00130025
    修改内容   : 问题单号:At2D05403
  7.日    期   : 2010年12月24日
    作    者   : s46746
    修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
  8.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  9.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 10.日    期   : 2011年11月8日
    作    者   : s46746
    修改内容   : V7R1 PhaseII阶段解决关机慢问题
 11.日    期   : 2011年11月15日
    作    者   : w00166186
    修改内容   : DTS201111402055,网络模式I下被17号原因值拒绝5次后，MM不停的发起注册
 12.日    期   : 2012年02月23日
    作    者   : l65478
    修改内容   : DTS2012021302593,GCF测试，PS注册失败后立刻发起CS注册导致PS上行数据没有发送成功
 13.日    期   : 2012年02月29日
    作    者   : l00130025
    修改内容   : DTS2012022206186:不发起LAU,而注册成功时，需要同步注册状态给AS
 14.日    期   : 2012年3月1日
    作    者   : w00176964
    修改内容   : DTS2012022407450:GMM进行联合注册时，通知给MM,MM记录下来
 15.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 16.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
 17.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                进行封装。
 18.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E8(VOS_VOID *pMsg)
{
    GMMMM_COMBINED_ATTACH_REJECTED_STRU        *pCombinedAttachRjct;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    VOS_UINT8                                   ucState;                           /* MM状态                                   */

    if ( MM_FALSE == NAS_MM_RcvGmmCombinedAttachRej(pMsg) )
    {
        return;
    }

    pCombinedAttachRjct = (GMMMM_COMBINED_ATTACH_REJECTED_STRU*)pMsg;

    /* 标示MM正在进行联合注册 */
    g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

    NAS_MM_ComProcPsRandomAccessFailCnt(pCombinedAttachRjct->enCause,pCombinedAttachRjct->ulAttachAttCounter);

    switch(pCombinedAttachRjct->enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);     /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NO_IMSI");

        Mm_ComToNoImsiHandle();                                                 /* 调用进NO IMSI的公共处理                  */

        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        NAS_MML_SetSimCsRegStatus(VOS_FALSE);

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NO_IMSI");

        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                                       /* 设置类似于B模式的全局量                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmLikeB is MM_TRUE");
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            if ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
            {
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);


                Mm_SndRrNasInfoChgReq(MM_NAS_INFO_SYNC_AS_FLG);


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() ) &&
                (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* 如果LAI不变,更新状态为U1的场合           */
                if ( MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg )
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;     /* 设置LU类型                               */
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
                else
                {
                    Mm_ComNasInfoSav(
                                     MM_STATUS_ATTACHED,
                                     NAS_MML_GetSimCsSecurityCksn()
                                     );
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;        /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NORMAL_SERVICE");


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* 记录流程和原因值                         */
        Mm_ComRejectCause11(MM_ATTACH);                                         /* 调用原因值为#11的处理                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_ATTACH_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* 记录流程和原因值                         */
        Mm_ComRejectCause13(MM_ATTACH);                                         /* 调用原因值为#13的处理                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pCombinedAttachRjct->enCause);         /* 记录流程和原因值                         */


        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pCombinedAttachRjct->enCause);


        break;
    default:

        if (pCombinedAttachRjct->ulAttachAttCounter == 0x0)
        {
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                            MM_MMC_LU_RESULT_FAILURE,
                            pCombinedAttachRjct->enCause);
        }

        else if ( pCombinedAttachRjct->ulAttachAttCounter < 5)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged() )
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus) )
            {                                                                   /* 如果LAI不变,更新状态为U1的场合           */
                Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;            /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_NORMAL_SERVICE");
                Mm_ComNasInfoSav(
                                 MM_STATUS_ATTACHED,
                                 NAS_MML_GetSimCsSecurityCksn()
                                 );
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_SUCCESS,
                                            NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;      /* 设置服务状态                             */


                NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                            MM_MMC_LU_RESULT_FAILURE,
                                            pCombinedAttachRjct->enCause);


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);

                NAS_MM_UpdateEquPlmnInfo(pCombinedAttachRjct->enCause);

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );                                              /* 设置MM信息                               */
                Mm_ComDelLai();                                                 /* 删除LAI                                  */
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                    ~MM_MS_ID_TMSI_PRESENT;
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

                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
        }
        else if (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pCombinedAttachRjct->enCause)
        {
            Mm_ComSaveProcAndCauseVal(
                                        MM_COMB_ATTACH_PROC,
                                        (VOS_UINT8)pCombinedAttachRjct->enCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E8:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                ~MM_MS_ID_TMSI_PRESENT;
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


            /**************************************************************
            The MM sublayer shall act as in network operation mode II or III
            (depending whether a PCCCH is present) as long as the combined
            GMM procedures are not successful and no new RA is entered. The
            new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
            ***************************************************************/
            g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
            g_MmGlobalInfo.ucLikeB        = MM_TRUE;

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E8:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");

            /*PS尝试失败后，CS尝试单独进行一次位置更新A32D10820==>*/
            Mm_ComProcCauseClear();
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                Mm_ComLuOnly();
            }
            else
            {
                /* G下，GAS同时处理CELL UPDATE和LU有问题，GCF 44.2.1.2.8 FAIL, 此处特殊处理
                   延迟1秒再发起 LU 过程。 */
                /* 此时状态不变，仍为: LOCATION UPDATING PENDING */
                Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
            }
            return;
        }
        else
        {
            ucState = g_MmGlobalInfo.ucState;
            Mm_ComSetMmState(g_MmGlobalInfo.ucPreState);
            g_MmGlobalInfo.ucPreState = ucState;                 /* 记录前状态                               */
        }
        break;
    }

    g_MmGlobalInfo.ucProc     = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_TRUE );
    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;
}


/*******************************************************************************
  Module:   Mm_Cell_S17_E11
  Function: 在LOCATION UPDATING PENDING状态下
            收到GMMMM_GPRS_DETACH_INITIATION的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
      2.日    期   : 2008年9月3日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05403,MM注册状态修改
      3.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E11(VOS_VOID *pMsg)
{
    if ( MM_FALSE == NAS_MM_RcvGmmGprsDetechIni(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录前状态                               */
    Mm_ComSetMmState(IMSI_DETACH_PENDING);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E11:NORMAL: STATUS is IMSI_DETACH_PENDING");
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E13
  Function: 在LOCATION UPDATING PENDING状态下收到GMMMM_NETWORK_DETACH_IND的处理
  Input:    VOS_VOID *pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.09  新版做成
      2.日    期   : 2008年9月3日
        作    者   : l00130025
        修改内容   : 问题单号：AT2D05403,MM注册状态修改
      3.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
      4.日    期   : 2015年3月20日
        作    者   : w00167002
        修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                     进行封装。
      5.日    期   : 2015年6月29日
        作    者   : z00161729
        修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E13(VOS_VOID *pMsg)
{
    GMMMM_NETWORK_DETACH_IND_STRU       *pstNetWkDetachInd;

    if ( MM_FALSE == NAS_MM_RcvGmmNetworkDetechInd(pMsg) )
    {
        return;
    }

    pstNetWkDetachInd = (GMMMM_NETWORK_DETACH_IND_STRU*)pMsg;

    if ( GMMMM_NET_DETACH_REATTACH == pstNetWkDetachInd->enDetachType )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
    }
    else if ( GMMMM_NET_DETACH_NOATTACH == pstNetWkDetachInd->enDetachType )
    {
        switch ( pstNetWkDetachInd->ulDetachCause )
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
            Mm_ComNetDetachCauseHandle(
                            (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );        /* 调用Net Detach的处理                     */
            NAS_MM_UpdateEquPlmnInfo(NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
            break;
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            g_MmGlobalInfo.ucLikeB = MM_TRUE;                                   /* 设置类似于B模式的全局量                  */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E13:INFO: MmLikeB is MM_TRUE");
            switch(g_MmGlobalInfo.ucMmServiceState)
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;

            case MM_NO_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    /* gsm下tbf释放后不会再上系统消息，需要启动MM_TIMER_DELAY_LU_GSM定时器做lau */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
                break;

            default:
                break;
            }
            break;
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
            Mm_ComNetDetachCauseHandle(
                            (VOS_UINT8)pstNetWkDetachInd->ulDetachCause );        /* 调用Net Detach的处理                     */
            NAS_MM_UpdateEquPlmnInfo(pstNetWkDetachInd->ulDetachCause);

            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstNetWkDetachInd->ulDetachCause);
            break;
        case NAS_MML_REG_FAIL_CAUSE_NULL:
            switch(g_MmGlobalInfo.ucMmServiceState)
            {
            case MM_NORMAL_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_LIMITED_SERVICE:
                Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
                break;
            case MM_ATTEMPTING_TO_UPDATE:
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                break;
            case MM_NO_IMSI:
                Mm_ComSetMmState(MM_IDLE_NO_IMSI);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E13:NORMAL: STATUS is MM_IDLE_NO_IMSI");
                break;

            case MM_NO_SERVICE:
                Mm_ComSetMmState(MM_IDLE_NO_CELL_AVAILABLE);

                if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
                {
                    /* gsm下tbf释放后不会再上系统消息，需要启动MM_TIMER_DELAY_LU_GSM定时器做lau */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
                break;

            default:
                break;
            }

            g_MmGlobalInfo.ucLikeB = MM_TRUE;
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E13:INFO: MmLikeB is MM_TRUE");
            break;
        default:
            break;
        }
    }
    else
    {

    }
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E15
  Function: 在LOCATION UPDATING PENDING状态下收到GMMMM_LU_INITIATION的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇     2003.12.10  新版做成
      2.  张志勇     2005.01.27  007005 for MM
      3.日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
      4.日    期   : 2012年3月31日
        作    者   : z00161729
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
*******************************************************************************/
VOS_VOID Mm_Cell_S17_E15(VOS_VOID *pMsg)
{
    GMMMM_LU_INITIATION_STRU    *pstMmcLuIni;
    VOS_UINT8                    ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    if ( MM_FALSE == Mm_RcvGmmLuIni(pMsg) )
    {
        return;
    }

    pstMmcLuIni = ( GMMMM_LU_INITIATION_STRU* )pMsg;

    if ( GMMMM_NO_TIMER_EXPIRED == pstMmcLuIni->enTimerExpiredFlg )
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;                   /* 设置LU类型为NORMAL                       */
    }
    else
    {
        if (((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus() )
           && (VOS_FALSE == ucPsRestrictionFlg)
           && (GMMMM_T3312_EXPIRED == pstMmcLuIni->enTimerExpiredFlg))
          || (GMMMM_T3412OrT3423_EXPIRED == pstMmcLuIni->enTimerExpiredFlg))
        {                                                                       /* 如果更新状态为U1的场合                   */
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;       /* 设置LU类型为周期                         */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;               /* 设置LU类型为NORMAL                       */
        }
    }
    Mm_ComLuOnly();                                                             /* 进行LU过程                               */
}


/*******************************************************************************
  Module:   Mm_Cell_S17_E18
            收到GMMMM_COMBINED_RAU_ACCEPTED的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
   1.  张志勇     2003.12.10  新版做成
   2.  s46746  2006-02-28  A32D03324

   3.日    期   : 2006年4月10日
     作    者   : liuyang id:48197
     修改内容   : 问题单号：A32D02352
   4.日    期   : 2007年9月21日
     作    者   : luojian id:107747
     修改内容   : 问题单号：AT2D01703
   5.日    期   : 2007年10月23日
     作    者   : l39007
     修改内容   : 问题单号：A32D13044
   6.日    期   : 2007年11月12日
     作    者   : l39007
     修改内容   : 根据问题单A32D13044,ATTACH失败5次,通知MM发起一次LAU,
                  如果此时MM已经注册,则不发起
   7.日    期   : 2007年12月27日
     作    者   : l39007
     修改内容   : 根据问题单A32D13044,GPRS only Attached(#16),如果小于5次，
                  MM状态恢复前状态，如果大于5次，且CS域没有注册，发起一次LAU
   8.日    期   : 2008年7月25日
     作    者   : luojian 00107747
     修改内容   : 根据问题单号AT2D04142/AT2D04677
   9.日    期   : 2009年8月18日
     作    者   : 欧阳飞 00132663
     修改内容   : AT2D13774,正常呼建链过程中发生异系统重选，W->G,NMOII->NMOI，LAI改变，
                  联合RAU成功后，未发起缓存的CS业务。
  10.日    期   : 2010年9月30日
     作    者   : 欧阳飞 00132663
     修改内容   : 根据问题单号DTS2010092902368,TMSI只在等效PLMN内有效
  11.日    期   : 2010年11月24日
     作    者   : 王毛 00166186
     修改内容   : 根据问题单号DTS2010112205253,RAU成功的分支，清除LAU记数器
  12.日    期   : 2010年12月21日
     作    者   : 欧阳飞 00132663
     修改内容   : 根据问题单号DTS2010121602598,PS ONLY，发起CS SMS业务，触发GMM联合注册，注册成功后，
                  未发起缓存的SMS业务。
  13. 日    期   : 2011年01月7日
      作    者   : s46746
      修改内容   : 问题单号:DTS2011010403819,网络模式I接收到接入层系统消息会进行Loci文件写操作，
                     连接态如果支持location status event，接入层上报系统消息也会向卡发送此事件
  14.日    期   : 2011年7月25日
     作    者   : h44270
     修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  15.日    期   : 2011年11月26日
     作    者   : w00167002
     修改内容   : DTS2011111605875:网络模式I,在背景搜注册时,发生PS成功，CS被拒
                   #16,此时收到SUSPEND_IND,则会迁移到先前的搜网状态，导致MM模块不给
                   MMC模块回复SUSPEND_RSP。
  16.日    期   : 2012年1月18日
     作    者   : s46746
     修改内容   : 问题单号：DTS2012011601544,网络模式I 联合注册仅PS成功,紧急呼叫后CS指示正常服务
  17.日    期   : 2012年3月1日
     作    者   : w00176964
     修改内容   : DTS2012022407450:GMM进行联合注册时，通知给MM,MM记录下来
  18.日    期   : 2012年3月16日
     作    者   : s46746
     修改内容   : DTS2012030603347:GSM下,GMM进行联合注册,仅PS成功,5次触发CS注册,CS单独注册失败,
                  接入层恢复GPRS失败导致又进行联合RAU,形成注册循环
  19.日    期   : 2012年03月17日
     作    者   : s46746
     修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
  20.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
  21.日    期   : 2013年07月5日
     作    者   : w00176964
     修改内容   : DTS2013062503351:LAU成功时更新当前的RAC信息
  22.日    期   : 2013年7月4日
     作    者   : w00167002
     修改内容   : SVLTE_bbit:W下，II,在46002上注册成功,用户指定搜24005上，I,PS/CS注册失败
                 原因为建链失败(7)=>
                 1.收到系统消息后，PS注册状态迁移到了5(因为GMM给MMC上报了注册成功)；
                    -->GMM通知MMC注册状态失败，CAUSE401;
                 2. MMC发起了搜网(因为在ON PLMN状态，GMM给MMC上报401原因，给MM上报
                 原因410，MM给MMC通知410后，触发了搜网)；
                    -->MM收到GMM当前被拒原因410时候，转换给401原因通知MMC;
                 3.搜网成功后，在原小区收到系统消息后，MMC重复发起搜网(GMM通知MM当前
                   PS当前注册成功，CS原因16，导致MM给MMC上报16原因值，触发循环搜网)。
                   -->GMM在ATTEMPT TO UPDATE状态，通知MM被拒原因410；

  23.日    期   : 2013年7月20日
     作    者   : w00167002
     修改内容   : DTS2013071900098:MM状态迁移不正确；
  24.日    期   : 2014年4月2日
     作    者   : w00176964
     修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E18(VOS_VOID *pMsg)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    VOS_UINT32                              ulCsServExist;
    NAS_MML_LAI_STRU                       *pstCsSuccLai        = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_ACCEPTED_STRU       *pstCombinedRauAccpt = VOS_NULL_PTR;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;

    pstCsSuccLai    = NAS_MML_GetCsLastSuccLai(  );

    if ( MM_FALSE == Mm_RcvGmmCombinedRauAccepted(pMsg) )
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucPsRandomAccessFailCnt = 0;

    pstCombinedRauAccpt = (GMMMM_COMBINED_RAU_ACCEPTED_STRU*)pMsg;

    if ( GMMMM_RAU_RESULT_COMBINED == pstCombinedRauAccpt->enRauResult )
    {
        g_MmGlobalInfo.ucLikeB = MM_FALSE;                                      /* 设置类似于B模式的全局量                  */
        g_MmGlobalInfo.ucLikeNetmode2 = MM_FALSE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmLikeB is MM_FALSE");
        Mm_TimerStop( MM_TIMER_T3212 );                                         /* 停T3212                                  */
        Mm_TimerStop( MM_TIMER_T3211 );                                         /* 停T3211                                  */
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);                           /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;                    /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmServiceState is MM_NORMAL_SERVICE");
        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        /* 记录注册成功的RAC，用于网络模式改变,比较RAI是否发生改变 */
        g_MmGlobalInfo.MsCsInfo.ucOldRac = NAS_MML_GetCurrCampRac();

        /* 由于网络模式改变,RAI不改变时,MM没有更新网络模式,而GMM模块可能会
           进行联合过程，为保证后续流程与GMM一致，此处需要更新网络模式 */
        g_MmGlobalInfo.ucNtMod           = g_MmGlobalInfo.ucNewNtMod;

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
        pstCsSuccLai->stPlmnId.ulMcc = NAS_MML_GetCurrCampPlmnId()->ulMcc;
        pstCsSuccLai->stPlmnId.ulMnc = NAS_MML_GetCurrCampPlmnId()->ulMnc;
        pstCsSuccLai->aucLac[0] = NAS_MML_GetCurrCampLai()->aucLac[0];
        pstCsSuccLai->aucLac[1] = NAS_MML_GetCurrCampLai()->aucLac[1];
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

        pstCsSuccLai->ucRac = g_MmGlobalInfo.MsCsInfo.ucOldRac;

        NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_UPDATED);              /* 设置更新状态                             */
        g_MmSubLyrShare.MmShare.ucSpecProFlg =  MM_NOT_UPDATED_SPECIFIC_PROCEDURE;

        /* ==>AT2D01703 */
        if (GMMMM_REAL_PROCEDURE == pstCombinedRauAccpt->enRealProFlg)
        {
            if ( GMMMM_MS_ID_TYPE_IMSI == pstCombinedRauAccpt->stMsIdentity.enMsIdType )
            {
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                                                        ~MM_MS_ID_TMSI_PRESENT; /* 设置TMSI无效                             */
                NAS_MML_InitUeIdTmsiInvalid();
            }
            else if ( GMMMM_MS_ID_TYPE_TMSI ==
                                pstCombinedRauAccpt->stMsIdentity.enMsIdType )
            {
                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg |=
                                                        MM_MS_ID_TMSI_PRESENT;
                PS_MEM_CPY(NAS_MML_GetUeIdTmsi(),
                           pstCombinedRauAccpt->stMsIdentity.aucTmsi,
                           NAS_MML_MAX_TMSI_LEN);

                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
                g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMcc = NAS_MML_GetCsLastSuccMcc();
                g_MmGlobalInfo.MsCsInfo.stPlmnId.ulMnc = NAS_MML_GetCsLastSuccMnc();
                /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
            }
            else
            {

            }
        }
        /* <==AT2D01703 */
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );

        if (GMMMM_REAL_PROCEDURE == pstCombinedRauAccpt->enRealProFlg)
        {
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {/* 3G USIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFLOCI_ID);
            }
            else
            {/* 2G SIM */
                Mm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCI_ID);
            }
        }
        else
        {
            NAS_MM_NotifyAsInfoChgReq();
        }

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */

        /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;                   /*LAU 记数器清零 */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);

        /* 标示MM正在进行联合注册 */
        g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_SUCCESS,
                                    NAS_MML_REG_FAIL_CAUSE_NULL);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E18:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
    }
    else
    {
        switch(pstCombinedRauAccpt->enCause)
        {
        case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_RAU_PROC,
                                      (VOS_UINT8)pstCombinedRauAccpt->enCause);   /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                       /* 设置服务状态                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E18:INFO: MmServiceState is MM_NO_IMSI");

            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
            Mm_ComToNoImsiHandle();                                             /* 调用进NO IMSI的公共处理                  */
            Mm_ComSetMmState(MM_IDLE_NO_IMSI);
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */

            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E18:NORMAL: STATUS is MM_IDLE_NO_IMSI");
            break;
        case NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE:
        case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
        case NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION:


            /* 此处协议未明确给出具体的描述，进行如下处理，
               注册失败次数小于5，则若LAI不变且当前MM的状态为UPDATED,则更新为
               NORMAL SERVICE,否则当前状态为MM_IDLE_ATTEMPTING_TO_UPDATE，
               参考协议24008:4.7.5.2.6 */
            if ( (pstCombinedRauAccpt->ulRauAttCounter < MM_RAU_ATTACH_COUNTER_MAX)
              || (GMMMM_REAL_PROCEDURE != pstCombinedRauAccpt->enRealProFlg))
            {
                enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
                  && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
                {                                                               /* 如果LAI不变,更新状态为U1的场合 */
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;
                    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录前状态 */

                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                }
                else
                {
                    g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;  /* 设置服务状态 */

                    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录前状态 */

                    Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                }
            }

            else if ((NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
                  || (MM_FALSE == g_MmGlobalInfo.ucLikeB))
            {
                /**************************************************************
                The MM sublayer shall act as in network operation mode II or III
                (depending whether a PCCCH is present) as long as the combined
                GMM procedures are not successful and no new RA is entered. The
                new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
                ***************************************************************/
                g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
                g_MmGlobalInfo.ucLikeB        = MM_TRUE;

                /*if CS is already attached,don't LAU any more*/
                if(MM_STATUS_ATTACHED != g_MmSubLyrShare.MmShare.ucCsAttachState)
                {
                    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-12, begin */
                    if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                     && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
                     && (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
                     && (MM_TRUE == g_MmGlobalInfo.ucPowerOnFlg))
                    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-12, end */
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH; /* 设置LU类型                               */
                    }
                    else
                    {
                        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
                    }
                }
                else
                {

                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
                }
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
                {
                    Mm_ComLuOnly();
                }
                else
                {
                    /* G下，GAS同时处理CELL UPDATE和LU有问题，GCF 44.2.3.2.3-2 FAIL, 此处特殊处理
                       延迟1秒再发起 LU 过程。 */
                    /* 此时状态不变，仍为: LOCATION UPDATING PENDING */
                    Mm_TimerStart(MM_TIMER_DELAY_LU_GSM);
                }
            }
            else
            {
                NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

                g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            }
            break;


        /* GMM收到系统消息时候通知MM的假流程原因值，不会触发MMC发起搜网 */
        case NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE:
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            break;

        default:
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
            break;
        }

        NAS_MM_SndMmcCsRegResultInd(pstCombinedRauAccpt->enRealProFlg,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pstCombinedRauAccpt->enCause);
    }
    Mm_ComProcCauseClear();

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        Mm_ComCheckDelayMmConn( MM_TRUE );
        Mm_ComCheckDelayDetach();
    }
    else
    {
        /* G下，当收到GMM 联合RAU成功消息后，不能马上发起缓存的CS业务，因为此时GMM的RAU流程还未完全结束,
           可能还有RAU COMPLETE消息需要回复，还有TLLI 指派等等，如果此时马上发起MM的建链请求，GAS可能挂起
           GMM，导致RAU流程不能正常结束
           目前的解决方案是启个1秒定时器，延迟发起CS业务 */
        ulCsServExist = Mm_ComJudgeCsServExist();

        if ((MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState) && (MM_CS_SERV_NONE_EXIST != ulCsServExist))
        {
            Mm_TimerStart(MM_TIMER_DELAY_CS_SERVICE_GSM);
        }
        else
        {
            Mm_ComCheckDelayMmConn( MM_TRUE );
            Mm_ComCheckDelayDetach();
        }
    }
}

/*******************************************************************************
  Module:   Mm_Cell_S17_E19
  Function: 在LOCATION UPDATING PENDING状态下
            收到GMMMM_COMBINED_RAU_REJECTED的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.10  新版做成
  2.  s46746  2006.02.28  A32D03324
  3. 日    期   : 2008年07月22日
     作    者   : luojian id:107747
     修改内容   : 根据问题单号：AT2D04163
  4. 日    期   : 2008年7月25日
     作    者   : luojian 00107747
     修改内容   : 根据问题单号AT2D04142/AT2D04677
  5. 日    期   : 2008年9月3日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05403,MM注册状态修改
  6. 日    期   : 2010年11月24日
     作    者   : 王毛 00166186
     修改内容   : 根据问题单号DTS2010112205253,NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED
                  分支不需要进行专题更新
  7.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  8.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  9.日    期   : 2011年7月26日
    作    者   : l00130025
    修改内容   : V7R1 PhaseII阶段调整，删除UserDelay标志，由MMC处理
 10.日    期   : 2011年11月15日
    作    者   : w00166186
    修改内容   : DTS201111402055,网络模式I下被17号原因值拒绝5次后，MM不停的发起注册
 11.日    期   : 2012年3月1日
    作    者   : w00176964
    修改内容   : DTS2012022407450:GMM进行联合注册时，通知给MM,MM记录下来
 12.日    期   : 2012年10月29日
    作    者   : z00161729
    修改内容   : DTS2012083102536:支持cc呼叫重建
 13.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态

 14.日    期   : 2013年7月4日
    作    者   : w00167002
    修改内容   : SVLTE_bbit:W下，II,在46002上注册成功,用户指定搜24005上，I,PS/CS注册失败
                 原因为建链失败(7)=>
                 1.收到系统消息后，PS注册状态迁移到了5(因为GMM给MMC上报了注册成功)；
                    -->GMM通知MMC注册状态失败，CAUSE401;
                 2. MMC发起了搜网(因为在ON PLMN状态，GMM给MMC上报401原因，给MM上报
                 原因410，MM给MMC通知410后，触发了搜网)；
                    -->MM收到GMM当前被拒原因410时候，转换给401原因通知MMC;
                 3.搜网成功后，在原小区收到系统消息后，MMC重复发起搜网(GMM通知MM当前
                   PS当前注册成功，CS原因16，导致MM给MMC上报16原因值，触发循环搜网)。
                   -->GMM在ATTEMPT TO UPDATE状态，通知MM被拒原因410；
 15.日    期   : 2013年7月19日
    作    者   : w00167002
    修改内容   : DTS2013071900239:W下网络模式I,联合注册PS only成功，CS失败原因
                  #17,网络模式由I--->II,此时不应发起联合ATTACH.
                  如果此时依然是网络模式I,但用户设置为PS ONLY,则也不用发起
                  联合ATTACH.
 16.日    期   : 2013年7月20日
    作    者   : w00167002
    修改内容   : DTS2013071900098:MM状态迁移不正确；

 17.日    期   : 2014年5月12日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目调整
 18.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
 19.日    期   : 2015年3月20日
    作    者   : w00167002
    修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                 进行封装。
 20.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改
*******************************************************************************/

VOS_VOID Mm_Cell_S17_E19(VOS_VOID *pMsg)
{
    GMMMM_COMBINED_RAU_REJECTED_STRU           *pstCombinedRauRjct;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;


    if ( MM_FALSE == Mm_RcvGmmCombinedRauRejected(pMsg) )
    {
        return;
    }

    pstCombinedRauRjct = (GMMMM_COMBINED_RAU_REJECTED_STRU*)pMsg;

    /* 标示MM正在进行联合注册 */
    g_MmGlobalInfo.ucIsComBined = VOS_TRUE;

    NAS_MM_ComProcPsRandomAccessFailCnt(pstCombinedRauRjct->enCause,pstCombinedRauRjct->ulRauAttCounter);

    switch(pstCombinedRauRjct->enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);            /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_NO_IMSI;                           /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NO_IMSI");


        Mm_ComToNoImsiHandle();                                                 /* 调用进NO IMSI的公共处理                  */

        Mm_ComSetMmState(MM_IDLE_NO_IMSI);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NO_IMSI");
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        g_MmGlobalInfo.ucLikeB = MM_TRUE;                                       /* 设置类似于B模式的全局量                  */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmLikeB is MM_TRUE");
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {
            if ( VOS_FALSE == NAS_MML_IsCsLaiChanged() )
            {
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        else
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            if ((VOS_FALSE == NAS_MML_IsCsLaiChanged())
                && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* 如果LAI不变,更新状态为U1的场合           */
                if (MM_ATT_NEED == g_MmGlobalInfo.ucAttFlg)
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_IMSI_ATTACH;     /* 设置LU类型                               */
                    Mm_ComLuOnly();                                             /* LU REQ                                   */
                }
                else
                {
                    Mm_ComNasInfoSav(
                                     MM_STATUS_ATTACHED,
                                     NAS_MML_GetSimCsSecurityCksn()
                                     );
                    g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;        /* 设置服务状态                             */
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");


                    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                                MM_MMC_LU_RESULT_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
                    NAS_MM_SndGmmLuResultInd(MMGMM_LU_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);                    /* 向MMC发送MMCMM_LU_RESULT_IND             */
                    Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                    NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);
                }
            }
            else
            {
                g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                Mm_ComLuOnly();                                                 /* LU REQ                                   */
            }
        }
        break;
    case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                    /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
        Mm_ComNasInfoSav(
                        MM_STATUS_ATTACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        break;
    case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;                   /* 设置服务状态                             */


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_LIMITED_SERVICE");
        Mm_ComNasInfoSav(
                        MM_STATUS_DETACHED,
                        NAS_MML_GetSimCsSecurityCksn()
                        );                                                      /* 设置MM信息                               */
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录前状态                               */
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        Mm_ComRejectCause11(MM_RAU);                                            /* 调用原因值为#11的处理                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        Mm_ComRejectCause13(MM_RAU);                                            /* 调用原因值为#13的处理                    */
        g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = MM_CONST_NUM_0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED:
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_LOCATION_UPDATE_NEEDED");
        Mm_ComSaveProcAndCauseVal(
                                  MM_COMB_RAU_PROC,
                                  (VOS_UINT8)pstCombinedRauRjct->enCause);        /* 记录流程和原因值                         */
        break;
    default:
        if (pstCombinedRauRjct->ulRauAttCounter == 0x0)
        {
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                            MM_MMC_LU_RESULT_FAILURE,
                            pstCombinedRauRjct->enCause);
        }
        if ( pstCombinedRauRjct->ulRauAttCounter < 5)
        {
            enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-12, begin */
            if ( (VOS_FALSE == NAS_MML_IsCsLaiChanged())
            /* Modified by w00176964 for V3R3C60_eCall项目, 2014-5-12, end */
              && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus))
            {                                                                   /* 如果LAI不变,更新状态为U1的场合           */
                Mm_ComSaveProcAndCauseVal(
                                          MM_COMB_RAU_PROC,
                                          (VOS_UINT8)pstCombinedRauRjct->enCause);/* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_NORMAL_SERVICE;            /* 设置服务状态                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_NORMAL_SERVICE");
                Mm_ComNasInfoSav(
                                MM_STATUS_ATTACHED,
                                NAS_MML_GetSimCsSecurityCksn()
                                );                                              /* 设置MM信息                               */
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_NORMAL_SERVICE);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");
            }
            else
            {
                Mm_ComSaveProcAndCauseVal(
                                          MM_COMB_RAU_PROC,
                                          (VOS_UINT8)pstCombinedRauRjct->enCause);    /* 记录流程和原因值                         */
                g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;      /* 设置服务状态                             */


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

                NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
                g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;             /* 记录前状态                               */
                Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

                Mm_ComNasInfoSav(
                                MM_STATUS_DETACHED,
                                MM_CKSN_INVALID
                                );                                              /* 设置MM信息                               */

                Mm_ComDelLai();                                                 /* 删除LAI                                  */

                g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                    ~MM_MS_ID_TMSI_PRESENT;
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


                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is MM_IDLE_ATTEMPTING_TO_UPDATE");
            }
        }
        else if(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != pstCombinedRauRjct->enCause)
        {
            Mm_ComSaveProcAndCauseVal(
                                      MM_COMB_RAU_PROC,
                                      (VOS_UINT8)pstCombinedRauRjct->enCause);    /* 记录流程和原因值                         */
            g_MmGlobalInfo.ucMmServiceState = MM_ATTEMPTING_TO_UPDATE;          /* 设置服务状态                             */


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S17_E19:INFO: MmServiceState is MM_ATTEMPTING_TO_UPDATE");

            NAS_MML_SetCsUpdateStatus(NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录前状态                               */
            Mm_ComSetMmState(MM_IDLE_ATTEMPTING_TO_UPDATE);

            Mm_ComNasInfoSav(
                            MM_STATUS_DETACHED,
                            MM_CKSN_INVALID
                            );                                                  /* 设置MM信息                               */
            Mm_ComDelLai();                                                     /* 删除LAI                                  */
            g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg &=
                ~MM_MS_ID_TMSI_PRESENT;
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


            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S17_E19:NORMAL: STATUS is  MM_IDLE_ATTEMPTING_TO_UPDATE");

            /**************************************************************
            The MM sublayer shall act as in network operation mode II or III
            (depending whether a PCCCH is present) as long as the combined
            GMM procedures are not successful and no new RA is entered. The
            new MM state is MM IDLE. 3gpp 24.008 4.7.3.2.3.2
            ***************************************************************/
            g_MmGlobalInfo.ucLikeNetmode2 = MM_TRUE;
            g_MmGlobalInfo.ucLikeB        = MM_TRUE;

            /*PS尝试失败后，CS尝试单独进行一次位置更新A32D10820==>*/
            Mm_ComProcCauseClear();
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
            Mm_ComLuOnly();
            NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                        MM_MMC_LU_RESULT_FAILURE,
                                        pstCombinedRauRjct->enCause);
            return;
        }
        else
        {
            NAS_MM_ResumeMmStateToPreState_LocationUpdatingPending();

            g_MmGlobalInfo.ucPreState = LOCATION_UPDATING_PENDING;
        }
        break;
    }


    /* 通知MM的状态为401， */
    if ( NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES == pstCombinedRauRjct->enCause )
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
    }
    else
    {
        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_TRUE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    pstCombinedRauRjct->enCause);
    }

    NAS_MM_UpdateEquPlmnInfo(pstCombinedRauRjct->enCause);

    g_MmGlobalInfo.ucProc    = MM_NULL_PROC;
    Mm_ComCheckDelayMmConn( MM_TRUE );

    g_MmGlobalInfo.usCauseVal = NAS_MML_REG_FAIL_CAUSE_NULL;

    Mm_ComCheckDelayDetach();
}


/*******************************************************************************
  Module:   Mm_Cell_S18_E5
  Function: 在IMSI DETACH PENDING状态下收到MMCMM_SYS_INFO_IND的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇     2003.12.11  新版做成
  2.日    期   : 2011年7月16日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  4.日    期   : 2011年12月23日
    作    者   : w00167002
    修改内容   : DTS2011111901055:假流程上报原因值由NAS_MML_REG_FAIL_CAUSE_NULL
                  修改为NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE.
                  修改原因:在ON PLMN状态，收到此假流程消息，若原因值小于
                  NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE，则可能发起搜网。
  5. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
   6.日    期   : 2013年05月15日
     作    者   : s46746
     修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
   7.日    期   : 2014年04月1日
     作    者   : w00176964
     修改内容   : V3R3C60_eCall项目:系统消息处理优化
 *******************************************************************************/

VOS_VOID Mm_Cell_S18_E5(VOS_VOID *pMsg)
{
    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, begin */

    /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-1, end */

    if (g_MmGlobalInfo.ucNtMod != g_MmGlobalInfo.ucNewNtMod)
    {
        /* 该状态下网络模式变化后不做Lu，直接向上层回复Detach成功 */
        g_MmGlobalInfo.ucNtMod = g_MmGlobalInfo.ucNewNtMod;                     /* 更新网络模式                             */
        g_MmGlobalInfo.ucMmServiceState = MM_DETACHED;                          /* 设置服务状态                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S18_E5:INFO: MmServiceState is MM_DETACHED");

        Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                         NAS_MML_GetSimCsSecurityCksn());                 /* 设置MM信息                               */

        /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_NO_IMSI);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);


        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E5:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }


    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

    NAS_MM_SndGmmLuResultInd(MMGMM_LU_FAILURE,
                             NAS_MML_REG_FAIL_CAUSE_NULL);
    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S18_E10
  Function: 在IMSI DETACH PENDING状态下收到GMMMM_IMSI_DETACH_COMPLETED的处理
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.10  新版做成
  2.  s46746  2005-11-14  修改
  3.  s46746  2006-05-24  根据问题单A32D03784修改
  4. 日    期   : 2007年01月12日
     作    者   : luojian id:60022475
     修改内容   : 问题单号：A32D08357
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
  7.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/

VOS_VOID Mm_Cell_S18_E10(VOS_VOID *pMsg)
{
    if (MM_FALSE == Mm_RcvGmmImsiDetechComplete(pMsg))
    {
        return;
    }

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    NAS_MML_GetSimCsSecurityCksn());

    /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                MM_MMC_LU_RESULT_FAILURE,
                                NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    if (MM_IDLE_LOCATION_UPDATE_NEEDED != g_MmGlobalInfo.ucState)
    {
        Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
    }


    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E10:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
}

/*******************************************************************************
  Module:   Mm_Cell_S18_E12
  Function: 在IMSI DETACH PENDING状态下收到GMMMM_GPRS_DETACH_COMPLETED的处理
  Input:    VOS_VOID*  pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.  张志勇     2003.12.10  新版做成
  2.  s46746  2005-11-14  修改
  3.  s46746  2006-05-24  根据问题单A32D03784修改
  4. 日    期   : 2008年9月3日
     作    者   : l00130025
     修改内容   : 问题单号：AT2D05487,MM注册状态修改
  5.日    期   : 2011年7月26日
    作    者   : h44270
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  6. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持MM需要将服务域不支持信息通知给MMC.
  7.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/
VOS_VOID Mm_Cell_S18_E12(VOS_VOID *pMsg)
{

    if (MM_FALSE == Mm_RcvGmmGprsDetechCmpl(pMsg))
    {
        return;
    }

    NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);

    Mm_TimerStop(MM_TIMER_T3218);                                               /* 停T3218                                  */
    Mm_ComDelRandRes();                                                         /* 删除RAND和RES                            */
    Mm_ComNasInfoSav(
                    MM_STATUS_DETACHED,
                    NAS_MML_GetSimCsSecurityCksn());
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {                                                                           /* 关机的场合                               */
        Mm_SndMmcPowerOffCnf();
        Mm_ComSetMmState(MM_STATE_NULL);

        g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E12:NORMAL: STATUS is MM_STATE_NULL");
    }
    else
    {
        /* 判断等待标志是否存在，如果存在则发送MMCGMM_DETACH CNF */
        if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                     & MM_WAIT_CS_DETACH))
        {
            NAS_MM_SndMmcDetachCnf(MMC_MM_LIMITED_SERVICE);
            /* 清除等待标志 */
            g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
        }

        NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE,
                                    MM_MMC_LU_RESULT_FAILURE,
                                    NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        if (MM_IDLE_LOCATION_UPDATE_NEEDED != g_MmGlobalInfo.ucState)
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
        }
        g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S18_E12:NORMAL: STATUS is MM_IDLE_LIMITED_SERVICE");
    }

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

}

/*******************************************************************************
  Module:   Mm_Cell_S9_E48
  Function: WAIT FOR OUTGOING MM CONNECTION状态接收到
            AGENT_USIM_AUTHENTICATION_CNF的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
  1.张志勇   2003.12.12   新版作成
  2.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  3.日    期  : 2013年11月30日
    作    者  : l65478
    修改内容  : DTS2013121919477,连续收到网络的两条鉴权消息,网络把第一条消息的响应作为第二条请求的响应,导致鉴权失败
  4.日    期  : 2013年7月22日
    作    者  : y00245242
    修改内容  : VoIP开发，适配新的USIM接口
  5.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E48(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    USIMM_AUTHENTICATION_CNF_STRU     *pstUsimAuthCnf = VOS_NULL_PTR;

    pstUsimAuthCnf = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;

    /* 当前不在等待此消息,丢弃 */
    NAS_MM_LogAuthInfo((VOS_UINT8)(pstUsimAuthCnf->stCmdResult.ulSendPara), g_MmGlobalInfo.AuthenCtrlInfo.ucOpId);

    if ((VOS_UINT8)(pstUsimAuthCnf->stCmdResult.ulSendPara) != g_MmGlobalInfo.AuthenCtrlInfo.ucOpId)
    {
        return;
    }

    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-24, begin */
    if ((USIMM_3G_AUTH != pstUsimAuthCnf->enAuthType )
     && (USIMM_2G_AUTH != pstUsimAuthCnf->enAuthType ))
    {
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E48:ERROR: authentication type is not expected!");

        return;
    }
    /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-24, end */

    /* SIM 卡 || USIM 卡但鉴权请求中不包含 AUTN */
    if ((NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        || (MM_IE_AUTN_PRESENT != g_MmMsgAuthReq.ucAutnFlg))
    {
        MM_RcvSimAuthCnf(pMsg);
        return;

    }

    if (MM_TRUE == Mm_RcvAgntUsimAuthenticationCnf(pMsg))
    {                                                                           /* 接收成功                                 */
        Mm_ComAuthenRcvUsimCnf();                                               /* 调用鉴权结束公共处理 */
    }
    else
    {                                                                           /* 接收失败                                 */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E55
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到T3214_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E55(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    Mm_ComT3214orT3216Expired();                                                /* 调用T3214或者T3216溢出的处理             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E55:INFO: RECEIVE MM T3214 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E56
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到T3216_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E56(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    Mm_ComT3214orT3216Expired();                                                /* 调用T3214或者T3216溢出的处理             */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E56:INFO: RECEIVE MM T3216 EXPIRED");
    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E57
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到T3218_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E57(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    Mm_ComT3218Expired();                                                       /* T3218溢出的处理                          */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E57:INFO: RECEIVE MM T3218 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E59
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到T3230_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E59(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    Mm_T3230Expire();                                                           /* T3230溢出的处理                          */
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Cell_S9_E59:INFO: RECEIVE MM T3230 EXPIRED");
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S11_E60
  FUNCTION : 在WAIT FOR NETWORK COMMAND状态下
             收到T3240_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E60(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

    Mm_T3240Expire();                                                           /* T3230溢出的处理                          */
    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S0_E61
  FUNCTION : 在MM_NULL状态下收到TIMER_PROTECT_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.  张志勇       2004.05.20  MM_IT_BUG_027对应
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E61(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{

}
/*******************************************************************************
  MODULE   : Mm_Cell_S1_E61
  FUNCTION : 在MM IDLE NO CELL AVAILABLE状态下收到TIMER_PROTECT_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S1_E61(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E61
  FUNCTION : 在WAIT FOR RR CONNECTION (MM CONNECTION)状态下
             收到TIMER_PROTECT_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E61(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
}
/*******************************************************************************
  MODULE   : Mm_Cell_S13_E61
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR REEST REQ)状态下
             收到TIMER_PROTECT_EXPIRED的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      03-12-22  新版作成
     2.
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S13_E61(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
}

/*******************************************************************************
  MODULE   : NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand
  FUNCTION : 在WAIT FOR NETWORK COMMAND状态下收到setup消息处理呼叫缓存
  INPUT    : VOS_UINT8 *pucCMMsg
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.卞尹      15-6-15    新版作成

*******************************************************************************/
VOS_VOID NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(VOS_UINT8 *pucCMMsg)
{
    if (MM_CC_MSG_SETUP == (pucCMMsg[MM_CC_MSG_TYPE_POS] & 0x3f))
    {
        if (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg)
        {
            Mm_SndCcRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ulTransactionId,
                                NAS_MMCM_REL_CAUSE_CM_SRV_REJ_CONGESTION);

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;
        }
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E50
  FUNCTION : 在WAIT FOR NETWORK COMMAND状态下
             收到RRMM_DATA_IND( CM Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      03-12-12    新版作成

  2.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 更新MML_CTX中的链接存在状态
  3.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
  5.日    期   :2015年6月15日
    作    者   :b00269685
    修改内容   :被叫情况下处理主叫缓存

*******************************************************************************/
VOS_VOID Mm_Cell_S11_E50(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8            ucTI = 0;                                              /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU  *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;            /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8           *pucCMMsg = VOS_NULL_PTR;                               /* 指针类型转换                             */
    VOS_UINT8           *pucBakCMMsg = VOS_NULL_PTR;

    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* 申请内存                                 */
    if(VOS_NULL_PTR == pucCMMsg)
    {                                                                           /* 内存申请失败                             */

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S11_E50:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */

    PS_MEM_SET(pucCMMsg, 0,
        sizeof(VOS_UINT8) * pRrDataInd->RcvNasMsg.ulNasMsgSize);                /* 初始化内存                               */

    PS_MEM_CPY (pucCMMsg, &(pRrDataInd->RcvNasMsg.aucNasMsg[0]),
        pRrDataInd->RcvNasMsg.ulNasMsgSize);                                    /* 得到消息内容                             */

    ucTI = (VOS_UINT8)(((pucCMMsg[0] & 0xf0) >> 4));                           /* 得到CC消息中的TI                         */

    if (((MM_CONST_NUM_7 == ucTI) || (MM_CONST_NUM_15 == ucTI)))
    {                                                                           /* TIO = 111                                */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd (ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);    /* 向CC发送MMCC_EST_IND                     */
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }

    /*lint -e701*/
    if ((MM_CONST_NUM_7 > ucTI))
    {                                                                           /* 网侧建立的MM连接                         */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd(ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );    /* 向CC发送MMCC_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0] =
            (VOS_UINT8)(0x01 << ucTI);                                          /* 设置已经存在的MM连接的标志位             */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E50:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn(MM_FALSE);

    }
    else if (((MM_CONST_NUM_7 < ucTI) && (MM_CONST_NUM_15 > ucTI))
        && (MMC_MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState))
    {                                                                           /* CC建立的MM连接                           */
        NAS_MM_ProcConnCtrlInfo_WaitForNetworkCommand(pucCMMsg);
        Mm_SndCcEstInd(ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg);     /* 向CC发送MMCC_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] =
            (VOS_UINT8)(0x01 << (ucTI - 8));                                    /* 设置已经存在的MM连接的标志位             */
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                    /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_EXIST);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E50:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn(MM_FALSE);
    }
    else
    {

    }

    /*lint +e701*/
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* 释放申请的消息                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S14_E40
  FUNCTION : 在WAIT FOR REESTABLISH(WAIT FOR EST_CNF)状态下
             收到RRMM_DATA_IND(CM SERVICE ACCEPT)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-01-06  新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S14_E40(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8   i = 0;                                                          /* 循环计数变量                             */
    /*lint -e701*/
    Mm_TimerStop(MM_TIMER_T3230);                                               /* 停TIMER3230                              */
    for (i = 0; i < MM_CONST_NUM_7; i++)
    {                                                                           /* 重建的MM连接                             */
        if (MM_CONST_NUM_0 !=
        (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
            & (0x01 << i)))
        {                                                                       /* 该TI的MM连接正在等待重建                 */
            Mm_SndCcReestCnf( i, MMCC_REEST_SUCCESS);                           /* 通知CC,MM连接正在建                      */
        }
        if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & (0x01 << i)))
        {                                                                       /* 该TI的MM连接正在等待重建                 */
            Mm_SndCcReestCnf((i + 8), MMCC_REEST_SUCCESS);                      /* 通知CC,MM连接正在建                      */
        }
    }
    /*lint +e701*/
    g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                         /* 记录迁移之前的状态                       */
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S14_E40:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
    Mm_ComCheckDelayMmConn( MM_FALSE );                                         /* 检查是否有保留的需要建立的MM连接         */

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    /* 处理eCall定时器启动标识 */
    NAS_MM_RecordEcallTimerStartNeededFlag();
#endif
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-9, end */

    return;
}

/*******************************************************************************
  Module:   Mm_Cell_S0_E3
  Function: MM_NULL 状态,收到 MMCMM_PLMN_SEARCH_INITIATED
            原语的处理
  Input:    VOS_VOID     *pMsg,  当前处理的消息
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  张志勇    2004.02.11   新版作成
      2.日    期   : 2013年05月15日
        作    者   : s46746
        修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*******************************************************************************/
VOS_VOID Mm_Cell_S0_E3(
                    VOS_VOID     *pMsg                                          /* 当前处理的消息                           */
                    )
{
    if (MM_TRUE == Mm_RcvMmcPlmnSrchIni(pMsg))
    {
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 设置ucPreState                           */
        Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S0_E3:NORMAL: STATUS is MM_IDLE_PLMN_SEARCH");
    }
    else
    {
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  MODULE   : Mm_Cell_S3_E65
  FUNCTION : 在MM IDLE NORMAL SERVICE状态下收到MMSS_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      04-03-08  新版作成
  2.张志勇        2005.01.27  007037 for MM
  3.日    期   : 2009年05月25日
    作    者   : l65478
    修改内容   : 问题单:AT2D10870,在MM连接建立过程中发生LAI改变,没有发起LU,导致呼叫失败
  4.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  6. 日    期   : 2012年2月14日
     作    者   : z00161729
     修改内容   : V7R1C50 支持CSFB特性修改
  7. 日    期   : 2012年2月15日
     作    者   : w00166186
     修改内容   : CSFB&PPAC&ETWS&ISR 开发
   8.日    期   : 2012年12月11日
     作    者   : w00176964
     修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
   9.日    期   :2013年9月12日
     作    者   :z00161729
     修改内容   :DTS2013082903019:支持ss重发功能
  10.日    期   :2014年9月24日
     作    者   :s00217060
     修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E65(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                                  /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* 要发送的CM SERVICE REQ消息指针           */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
#endif

    if (MM_FALSE == Mm_RcvSsEstReq(pRcvMsg))
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 如果当前为L单模则直接回复ss失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
            return;
        }

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MM_RcvSsEstReq_CSFB();

            return;
        }
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */

        if ((MM_CONST_NUM_8 > g_MmSsEstReq.ulTi)
            || (MM_CONST_NUM_14 < g_MmSsEstReq.ulTi))
        {
            /* TI不合法 */

            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else
        {                                                                       /* TI合法                                   */
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

            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);/* 填充CM SERVICE REQUEST结构体             */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize ); /* 填充CM SERVICE REQUEST 消息              */
            if (VOS_NULL_PTR == pucCmSvcReq)
            {                                                                   /* 消息制作失败                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E65:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                         /* 返回                                     */
            }
            else
            {                                                                   /* 消息制作成功                             */
                Mm_SndRrEstReq(RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL,
                   MM_FALSE, usMsgSize, pucCmSvcReq);                           /* 发送消息                                 */
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);                /* 释放CM SERVICE REQUEST 消息结构体        */
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSsEstReq.ulTi;                                   /* 记录正在建立的MM连接的TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;     /* 记录正在建立的MM连接的PD                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                /* 通知MMC，CS域的业务已经启动              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E65:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
        }

        NAS_MM_UpdateCsServiceConnStatusFlg();

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S4_E65
  FUNCTION : 在WAIT_FOR_OUTGOING_MM_CONNECTION状态下收到MMSS_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08  新版作成
     2.日    期   : 2011年03月01日
       作    者   : A00165503
       修改内容   : 问题单号: DTS2011021202242/DTS2011021400322，添加宏开关判断
                    服务域为PS_ONLY时，CS域短信和呼叫业务是否能够发起
     3.日    期   : 2011年10月27日
       作    者   : s46746
       修改内容   : V7R1 PhaseIII,支持L模联合注册
     4.日    期   : 2012年03月03日
       作    者   : s62952
       修改内容   : BalongV300R002 Build优化项目:使用NV替换NAS_FEATURE_SUPPORT_H3G_REQ宏
     5.日    期   : 2012年2月15日
       作    者   : w00166186
       修改内容   : CSFB&PPAC&ETWS&ISR 开发
     6.日    期   : 2012年12月11日
       作    者   : w00176964
       修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
     7.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     8.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E65(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo               = NAS_MML_GetMiscellaneousCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前驻留LTE,则直接回复SS失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {        

            /* CS域卡无效，则不处理补充业务 */
            if (VOS_FALSE  == NAS_MML_GetSimCsRegStatus())
            {
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);

                return;
            }
            
            /* 如果当前PS ONLY时支持CS业务NV未激活，则SS失败 */
            if ( (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
              && (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg) )
            { 
                 Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                               NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
                
                 return;
            }
            
            /* 在LIMIT SRVICE状态放开SS业务的CSFB处理 */
            if (MM_IDLE_LIMITED_SERVICE == Mm_GetState())
            {
                NAS_MM_RcvSsEstReq_CSFB();

                return;
            }            

            
            /* LTE下UE在null、no imsi、wait for attach状态无法处理ss业务 */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

            return;
        }


        
#endif
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        if (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
        }
        else
        {
            /*状态不为limited service或者服务域不为PS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                /* UE在null、no imsi、wait for attach状态无法处理ss业务 */
                Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
            }
            else
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
                /*缓存该服务请求并进行CS注册*/
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
                if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
                 && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
                {
                    NAS_MM_SndGmmRegisterInit();                                        /* 通知GMM进行注册                          */
                }
                else
                {
                    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;           /* 设置LU类型                               */
                    g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
                    Mm_ComLuOnly();                                                 /* LU REQ                                   */
                }
            }

        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E65
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMSS_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08  新版作成
     2.  日    期   : 2011年05月11日
         作    者   : f00179208
         修改内容   : DTS2011042504198:在CS域发短信失败后，由于SMS与MM接口间有问题，无法再PS域重发短信
     3. 日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
     4.日    期   : 2012年12月11日
       作    者   : w00176964
       修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
     5.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     6.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E65(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU          CmSvcReq;                                   /* CM service request结构体                 */
    VOS_UINT8                       ucRst;

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }
        /*lint -e701*/
        ucRst = Mm_ComJudgeLimitSvc();
        if ( ( MM_CONST_NUM_8 > g_MmSsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSsEstReq.ulTi )
            || ( MM_TRUE == ucRst ) )
        {                                                                       /* TI不合法或者在受限服务状态               */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);
        }
        else if ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] &
            ( 0x01 << ( g_MmSsEstReq.ulTi - 8 ) ) ) )
        {                                                                       /* 要求建立的MM连接已经存在                 */
            Mm_SndSsEstCnf( g_MmSsEstReq.ulTi, MMSS_EST_SUCCESS );              /* 通知SS，MM连接建立成功                   */
        }
        else
        {                                                                       /* TI合法                                   */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SS_ACT, MM_FALSE, &CmSvcReq);/* 填充CM SERVICE REQUEST结构体             */
            Mm_ComMsgCmSvcReqSnd( &CmSvcReq );                                  /* 向网侧发送建立MM连接的请求               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSsEstReq.ulTi;                                           /* 记录重建MM连接的TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSsEstReq.ulTi;                                       /* 记录正在建立的MM连接的TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_NON_CALL_RLT_SS_MSG;     /* 记录正在建立的MM连接的PD                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();

            Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E65:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
        }
        /*lint +e701*/
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E65
  FUNCTION : 在WAIT FOR NETWORK COMMAND状态下收到MMSS_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      04-03-08    新版作成
  2.日    期   : 2006年11月25日
    作    者   : s46746
    修改内容   : 问题单号：A32D07666
  3.日    期   : 2010年09月12日
    作    者   : l00130025
    修改内容   : 问题单号：DTS2010090702204,Hplmn搜网中,PS Service发起或短信和SS业务发起先中断搜网, 注册Rplmn,发起业务
  4.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  6.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  7.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
  8.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
  9.日    期   :2014年2月22日
    作    者   :y00245242
    修改内容   :dts201412901179:CC与SS业务请求同时触发时，对网络的容错处理
 10.日    期   :2014年3月23日
    作    者   :y00245242
    修改内容   :移dts201412901179到函数Mm_IsMultiSrvCollisionAllow中统一处理
 11.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E65(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
#endif

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E65:WARNING: MMSS_EST_REQ check fail.");
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 如果当前为L单模则直接回复ss失败 */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        if ( VOS_TRUE == NAS_MML_IsLteOnlyMode(pstPrioRatList) )
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);
            return;
        }

        /* 如果当前驻留LTE,则直接回复SS失败 */
        /* L下在LOCATION_UPDATING_PENDING状态收到ss请求，mm需缓存 */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (MM_IDLE_PLMN_SEARCH != g_MmGlobalInfo.ucState)
         && (LOCATION_UPDATING_PENDING != g_MmGlobalInfo.ucState))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);

            return;
        }
#endif

        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg)
        {                                                                       /* 已经存在一个保留的MM连接建立请求         */
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
        }

        /* 检查多业务冲突是否允许 */
        if (VOS_FALSE == Mm_IsMultiSrvCollisionAllow(MM_CONN_CTRL_SS))
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);

            return;
        }

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_SEARCHING_NETWORK);
            return;
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg
            = MM_TRUE;

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulTransactionId
            = g_MmSsEstReq.ulTi;

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].ucRat = NAS_MML_GetCurrNetRatType();


    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S3_E62
  FUNCTION : 在MM IDLE NORMAL SERVICE状态下收到MMSMS_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      04-03-08  新版作成
  2.张志勇        2005.01.27  007037 for MM
  3.日    期   : 2007年06月04日
    作    者   : luojian id:60022475
    修改内容   : 问题单号:A32D11456
  4.日    期   : 2009年05月25日
    作    者   : l65478
    修改内容   : 问题单:AT2D10870,在MM连接建立过程中发生LAI改变,没有发起LU,导致呼叫失败
  5.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  6.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  7.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  8.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
  9.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容   :DTS2013082903019:支持ss重发功能
 10.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S3_E62(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU      CmSvcReq;                                       /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                  usMsgSize = 0;                                  /* 消息长度,以字节为单位                    */
    VOS_UINT8                  *pucCmSvcReq = 0;                                /* 要发送的CM SERVICE REQ消息指针           */


    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            /* 通知SMS建立失败 */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);
            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前驻留LTE,则直接回复SMS失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);/* 通知SMS建立失败                          */

            return;
        }
#endif

        g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;             /* 记录收到建立请求时的状态                 */
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi ) )
        {                                                                       /* TI不合法                                 */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* 通知SMS建立失败                          */
        }
        else
        {                                                                       /* TI合法                                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_TRUE;

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
                = 0;
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();


            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);   /* 填充CM SERVICE REQUEST结构体             */
            pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq( &CmSvcReq, &usMsgSize ); /* 填充CM SERVICE REQUEST 消息              */
            if ( VOS_NULL_PTR == pucCmSvcReq )
            {                                                                   /* 消息制作失败                             */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S3_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
                return;                                                         /* 返回                                     */
            }
            else
            {                                                                   /* 消息制作成功                             */
                Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                   MM_FALSE,
                   usMsgSize, pucCmSvcReq );                                    /* 发送消息                                 */
                MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq );               /* 释放CM SERVICE REQUEST 消息结构体        */
            }
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSmsEstReq.ulTi;                                  /* 记录正在建立的MM连接的TI                 */
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;                 /* 记录正在建立的MM连接的PD                 */
            Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                                /* 通知MMC，CS域的业务已经启动              */
            NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
            /*A32D11456==>*/
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
            /*<==A32D11456*/
        }
    }

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection
 功能描述  : 在WAIT_FOR_OUTGOING_MM_CONNECTION状态下收到MMSMS_EST_REQ的处理
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
VOS_VOID NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection(VOS_VOID)
{
    MM_MSG_CM_SVC_REQ_STRU                     CmSvcReq;                            /* 要发送的CM SERVICE REQ消息               */
    VOS_UINT16                                 usMsgSize = 0;                        /* 消息长度,以字节为单位                    */
    VOS_UINT8                                 *pucCmSvcReq = 0;
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8  enCsUpdateStatus;

    enCsUpdateStatus                      = NAS_MML_GetCsUpdateStatus();

    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
        = MM_TRUE;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
        = g_MmSmsEstReq.ulTi;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
        = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
        = 0;
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat
        = NAS_MML_GetCurrNetRatType();

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, begin */
    if ((VOS_FALSE                               == NAS_MML_IsCsLaiChanged())
     || (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED  != enCsUpdateStatus))
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-3, end */
    {
        NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);

        if ((MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
            && (MM_FALSE == g_MmGlobalInfo.ucLikeB))
        {
            NAS_MM_SndGmmRegisterInit();                                /* 通知GMM进行注册                          */
        }
        else
        {
            g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;   /* 设置LU类型                               */
            g_MmGlobalInfo.LuInfo.ucLuAttmptCnt = 0;
            Mm_ComLuOnly();                                         /* LU REQ                                   */
        }
    }
    else
    {
        Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq); /* 填充CM SERVICE REQUEST结构体             */

        pucCmSvcReq = Mm_ComMsgCmSvcReqOfRrEstReq(&CmSvcReq, &usMsgSize); /* 填充CM SERVICE REQUEST 消息              */

        if (VOS_NULL_PTR == pucCmSvcReq)
        {                                                           /* 消息制作失败                             */
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S4_E62:WARNING: MAKE MSG CM SERVICE REQUEST ERROR!");
            return;                                                 /* 返回                                     */
        }
        else
        {                                                           /* 消息制作成功                             */
            Mm_SndRrEstReq( RRC_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL,
                            MM_FALSE,
                            usMsgSize, pucCmSvcReq );                                /* 发送消息                                 */
            MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucCmSvcReq);        /* 释放CM SERVICE REQUEST 消息结构体        */
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI
            = (VOS_UINT8)g_MmSmsEstReq.ulTi;                        /* 记录正在建立的MM连接的TI                 */
        g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;         /* 记录正在建立的MM连接的PD                 */
        Mm_TimerStart(MM_TIMER_PROTECT_SIGNALLING);
        Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);                        /* 通知MMC，CS域的业务已经启动              */
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);
        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;         /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(WAIT_FOR_RR_CONNECTION_MM_CONNECTION);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S4_E62:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_MM_CONNECTION");
    }
}

/*******************************************************************************
  MODULE   : Mm_Cell_S4_E62
  FUNCTION : 在WAIT_FOR_OUTGOING_MM_CONNECTION状态下收到MMSMS_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      04-03-08  新版作成
  2.日    期   : 2011年03月01日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2011021202242/DTS2011021400322，添加宏开关判断
                 服务域为PS_ONLY时，CS域短信和呼叫业务是否能够发起
  3.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4.日    期   : 2011年10月27日
    作    者   : s46746
    修改内容   : V7R1 PhaseIII,支持L模联合注册
  6.日    期   : 2012年03月03日
    作    者   : s62952
    修改内容   : BalongV300R002 Build优化项目:使用NV替换NAS_FEATURE_SUPPORT_H3G_REQ宏
  7.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  8.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
  9.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
 10.日    期   : 2014年4月2日
    作    者   : w00176964
    修改内容   : V3R3C60_eCall项目修改:g_MmGlobalInfo.MsCsInfo.OldLai替换成MML中的
 11.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
 12.日    期   : 2014年12月29日
    作    者   : z00161729
    修改内容   : DSDS业务重拨时no rf未触发搜网导致业务失败，mm在no cell available状态no rf时给mmc发送cm service ind触发搜网
*******************************************************************************/
VOS_VOID Mm_Cell_S4_E62(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU       *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    VOS_UINT8                                  ucSimCsRegStatus;

    pstMiscellaneousCfgInfo               = NAS_MML_GetMiscellaneousCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */

    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            /* 通知SMS建立失败 */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

        /* 在MM_IDLE_NO_IMSI状态时收到短信业务请求直接回复CS_SIM_INVALID,
           其他状态一般是收到系统消息后还未注册时处理缓存,暂时无法提供CS服务，需要重拨 */
        if (MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState)
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                           NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID);    /* 通知CC建立失败                           */

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* 如果当前驻留LTE,则直接回复SMS失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);/* 通知SMS建立失败                          */

            return;
        }
#endif
        /* 如果no rf，先缓存业务请求，通知mmc触发搜网 */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         && (MM_IDLE_NO_CELL_AVAILABLE == g_MmGlobalInfo.ucState)
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SMS);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, begin */
        if (NAS_MMC_NV_ITEM_DEACTIVE == pstMiscellaneousCfgInfo->ucPsOnlyCsServiceSupportFlg)
        {
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
        }
        else
        {
            /*状态不为limited service或者服务域不为PS ONLY*/
            if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
             || (MM_IDLE_LIMITED_SERVICE != g_MmGlobalInfo.ucState))
            {
                /* UE在null、no cell available、no imsi、wait for attach、WAIT FOR RR CONNECTION (IMSI DETACH)、IMSI DETACH INITIATED
                   状态无法处理sms业务 */
                Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
            }
            else
            {
                g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState;         /* 记录收到建立请求时的状态                 */

                if ((MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi)
                    || (MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi))
                {                                                                   /* TI不合法                                 */
                    Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi,
                                    NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                /* 通知SMS建立失败                          */
                }
                else
                {
                    NAS_MM_ProcSmsEstReq_WaitForOutgoingMmConnection();
                }
            }

        }
        /* Modified by s62952 for BalongV300R002 Build优化项目 2012-02-28, end */
    }


    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E62
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMSMS_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08  新版作成
     2.  日    期   : 2011年05月11日
         作    者   : f00179208
         修改内容   : DTS2011042504198:在CS域发短信失败后，由于SMS与MM接口间有问题，无法再PS域重发短信
     3.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     4.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E62(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_CM_SVC_REQ_STRU              CmSvcReq;                               /* CM service request结构体                 */
    VOS_UINT8                           ucRst = MM_FALSE;
    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* ucRst = Mm_ComJudgeLimitSvc(); */
        if (MM_NO_IMSI == g_MmGlobalInfo.ucMmServiceState)
        {                                                                       /* 是受限服务                               */
            ucRst = MM_TRUE;                                                    /* 设置是受限服务                           */
        }

        if ((NAS_MML_MS_MODE_PS_ONLY != NAS_MML_GetMsMode())
         && ((MM_LIMITED_SERVICE == g_MmGlobalInfo.ucMmServiceState)
          || ( MM_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucMmServiceState )))
        {
            ucRst = MM_TRUE;                                                 /* 设置是受限服务                           */
        }
        /*lint -e701*/
        if ( ( MM_CONST_NUM_8 > g_MmSmsEstReq.ulTi )
            || ( MM_CONST_NUM_14 < g_MmSmsEstReq.ulTi )
            || ( MM_TRUE == ucRst ) )
        {                                                                       /* TI不合法或者在受限服务状态               */
            Mm_SndSmsRelInd( g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* 通知SMS建立失败                          */
        }
        else if (MM_CONST_NUM_0 !=
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &
            (0x01 << (g_MmSmsEstReq.ulTi - 8))))
        {                                                                       /* 要求建立的MM连接已经存在                 */
            Mm_SndSmsEstCnf( g_MmSmsEstReq.ulTi );                              /* 通知SMS，MM连接建立成功                  */
        }
        else
        {                                                                       /* TI合法                                   */
            Mm_ComFillInCMSncReq(MM_IE_CM_SVC_TYPE_SMS, MM_FALSE, &CmSvcReq);   /* 填充CM SERVICE REQUEST结构体             */
            Mm_ComMsgCmSvcReqSnd( &CmSvcReq );                                  /* 向网侧发送建立MM连接的请求               */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ulTransactionId
                = g_MmSmsEstReq.ulTi;                                           /* 记录重建MM连接的TI */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                (VOS_UINT8)g_MmSmsEstReq.ulTi;                                  /* 记录正在建立的MM连接的TI                 */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();
            g_MmGlobalInfo.ucMMConnEstingPD = MM_IE_PD_SMS_MSG;                 /* 记录正在建立的MM连接的PD                 */
            Mm_TimerStart(MM_TIMER_T3230);                                      /* 启动TIMER3230                            */
            g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                 /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E62:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
        }
        /*lint +e701*/
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E62
  FUNCTION : 在WAIT FOR NETWORK COMMAND状态下收到MMSMS_EST_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.张志勇      04-03-08    新版作成
  2.日    期   : 2006年11月25日
    作    者   : s46746
    修改内容   : 问题单号：A32D07666
  3.日    期   : 2010年09月12日
    作    者   : l00130025
    修改内容   : 问题单号：DTS2010090702204,Hplmn搜网中,PS Service发起或短信和SS业务发起先中断搜网, 注册Rplmn,发起业务
  4.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  6.日    期   : 2012年06月01日
    作    者   : f62575
    修改内容   : DTS2012052904375，解决搜网过程中接收到SMS的EST_REQ没有回复REL_IND问题
  7.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : 修改 NAS_MML_GetCsRestrictNormalServiceFlg函数名
  8.日    期   :2013年9月12日
    作    者   :z00161729
    修改内容  :DTS2013082903019:支持ss重发功能
  9.日    期   :2014年9月24日
    作    者   :s00217060
    修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E62(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    if ( MM_FALSE == Mm_RcvSmsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E62:WARNING: MMSMS_EST_REQ check fail.");
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            /* 通知SMS建立失败 */
            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if   (FEATURE_ON == FEATURE_LTE)
        if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
            {                                                                       /* 已经存在一个保留的MM连接建立请求         */
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
                Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                    RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
            }

            Mm_SndSmsRelInd(g_MmSmsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE);

            return;
        }
#endif

        if (MM_TRUE ==
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
        {                                                                       /* 已经存在一个保留的MM连接建立请求         */
            Mm_SndSmsRelInd(g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST);
        }

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
            = MM_TRUE;

        NAS_MML_SetCsServiceBufferStatusFlg(VOS_TRUE);

        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId
            = g_MmSmsEstReq.ulTi;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallType
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulCallPri
            = 0;
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat = NAS_MML_GetCurrNetRatType();

        if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
        {
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
        }

    }


    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E68
  FUNCTION : 在PROCESS CM SERVICE PROMPT状态下收到MMCC_PROMPT_REJ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08    新版作成
     3.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E68(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */

    if ( MM_FALSE == Mm_RcvCcPromptRej( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
        Mm_TimerStop(MM_TIMER_T3240);
        MsgMmStatus.MmIeRjctCause.ucRejCause = (VOS_UINT8)(g_MmCcPromptRej.ulRefuseCause);
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );

        g_MmGlobalInfo.ucPreState = g_MmGlobalInfo.ucState;                     /* 记录迁移之前的状态                       */
        if ( MM_FALSE == Mm_ComMmConnExist( ) )
        {                                                                       /* 没有存在的MM连接 */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd = g_MmGlobalInfo.
                ucStaOfRcvXXEstReq;                                             /* 进入空闲的状态                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E68:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
        else
        {                                                                       /* 有存在的MM连接 */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            Mm_ComCheckDelayMmConn(VOS_FALSE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E68:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        }
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E47
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到
                RRMM_DATA_IND(CM SERVICE PROMPT)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E47(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */

    if (MM_LIMITED_SERVICE != g_MmGlobalInfo.ucMmServiceState)
    {
        Mm_TimerStop(MM_TIMER_T3212);                                           /* 停T3212                                  */
    }
    MsgMmStatus.MmIeRjctCause.ucRejCause =
        NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE;                                   /* Service option not supported             */
    Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                       /* 填充并发送 MM STATUS 消息                */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E47
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到
                RRMM_DATA_IND(CM SERVICE PROMPT)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08    新版作成
     4.  张志勇        2005.01.27  007037 for MM
     5.日    期   : 2012年8月10日
       作    者   : L00171473
       修改内容   : DTS2012082204471, TQE清理
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E47(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MM_MSG_MM_STATUS_STRU          MsgMmStatus;                                 /* MM STATUS 消息结构体                     */
    VOS_UINT8                      aucClassmark2[4];


    PS_MEM_SET(aucClassmark2, 0x00, sizeof(aucClassmark2));

    MM_Fill_IE_ClassMark2(aucClassmark2);

    if ( MM_CONST_NUM_0 == ( aucClassmark2[3] & 0x04 ) )
    {                                                                           /* 不支持CCBS                               */
        MsgMmStatus.MmIeRjctCause.ucRejCause =
            NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE;                            /* Msg type non-existent or not implemented */
        Mm_ComMsgMmStatusSnd( &MsgMmStatus );                                   /* 填充并发送 MM STATUS 消息                */
    }
    else
    {                                                                           /* 支持CCBS                                 */
        Mm_SndCcPromptInd();                                                    /* 向CC发送MMCC_PROMPT_IND                  */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(PROCESS_CM_SERVICE_PROMPT);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E47:NORMAL: STATUS is PROCESS_CM_SERVICE_PROMPT");
        Mm_TimerStart(MM_TIMER_PROTECT_CCBS);
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E27
  FUNCTION : 在PROCESS CM SERVICE PROMPT状态下收到MMCC_DATA_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-08    新版作成
     6.  张志勇        2005.01.27  007037 for MM
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E27(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MMCC_DATA_REQ_STRU      *pMmCcDataReq;
    pMmCcDataReq = (MMCC_DATA_REQ_STRU*)pRcvMsg;

    if ( MM_FALSE == Mm_RcvCcDataReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > pMmCcDataReq->ulTransactionId)
           && ( MM_CONST_NUM_0 ==
           ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[0]
           & ( 0x01 << pMmCcDataReq->ulTransactionId ) ) ) )
        {                                                                       /* 该消息中的TI小于7不存在并且TIO !=111     */
        }
        else if(((MM_CONST_NUM_7  < pMmCcDataReq->ulTransactionId)
            &&(MM_CONST_NUM_15 > pMmCcDataReq->ulTransactionId))
            && (MM_CONST_NUM_0 ==
            (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
            & (0x01 << (pMmCcDataReq->ulTransactionId - 8)))))
        {                                                                       /* 该消息中的TI大于7不存在并且TIO !=111     */
            Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1] |=
                (VOS_UINT8)( 0x01 << ( pMmCcDataReq->ulTransactionId - 8 ) );   /* 设置该TI存在                             */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S27_E27:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        }
        else
        {

        }
        Mm_SndRrDataReq(pMmCcDataReq->SendCcMsg.ulCcMsgSize,
                        &pMmCcDataReq->SendCcMsg.aucCcMsg[0],
                        RRC_NAS_MSG_PRIORTY_HIGH);                              /* 将CC的消息传送下去                       */

        /*lint +e701*/
    }

    return;

}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E69
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND( SS Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E69(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                ucTI = 0;                                          /* CC消息中的TI                             */
    RRMM_DATA_IND_STRU      *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;        /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8               *pucCMMsg = VOS_NULL_PTR;                                                   /* 指针类型转换                             */
    VOS_UINT8               *pucBakCMMsg = VOS_NULL_PTR;

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

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E69:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到SS消息中的TI                         */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndSsDataInd (
                (VOS_UINT32 )ucTI,
                pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向SS发送MMSS_DATA_IND                    */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向SS发送MMSS_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* 设置已经存在的MM连接的标志位             */

            /* BEGIN: Modified by 欧阳飞  ID: 00132663, 2008/8/26   PN:AT2D05263*/
            /* 目前有三种状态会调用该函数
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                MM_CONNECTION_ACTIVE
                其它两种状态保持不变。*/
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E69:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */
            /* END:   Modified by 欧阳飞  ID: 00132663, 2008/8/26 */
        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SS建立的MM连接                           */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndSsDataInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向SS发送MMSS_DATA_IND                    */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向SS发送MMSS_EST_IND                     */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* 设置已经存在的MM连接的标志位             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
        /*lint +e701*/
    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg );                                /* 释放申请的消息                           */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S9_E70
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下
             收到RRMM_DATA_IND( SMS Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11    新版作成
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E70(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    VOS_UINT8                ucTI = 0;                                          /* SMS消息中的TI                            */
    RRMM_DATA_IND_STRU      *pRrDataInd = (RRMM_DATA_IND_STRU *)pRcvMsg;        /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8               *pucCMMsg = VOS_NULL_PTR;                           /* 指针类型转换                             */
    VOS_UINT8               *pucBakCMMsg = VOS_NULL_PTR;

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

        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mm_Cell_S9_E70:ERROR: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到SMS消息中的TI                        */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << ucTI ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndSmsDataInd(
                (VOS_UINT32 )ucTI,
                pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向SMS发送MMSMS_DATA_IND                  */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向SMS发送MMSMS_EST_IND                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
                ( VOS_UINT8 )( 0x01 << ucTI );                                      /* 设置已经存在的MM连接的标志位             */

            /* BEGIN: Modified by 欧阳飞  ID: 00132663, 2008/8/26   PN:AT2D05263*/
            /* 目前有三种状态会调用该函数
                WAIT_FOR_OUTGOING_MM_CONNECTION
                WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION
                MM_CONNECTION_ACTIVE
                其它两种状态保持不变。*/
            if ( g_MmGlobalInfo.ucState == WAIT_FOR_OUTGOING_MM_CONNECTION )
            {
                g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                          /* 记录迁移之前的状态                       */
                Mm_ComSetMmState(WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION);
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E70:NORMAL: STATUS is WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION");
            }

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, begin */

            /* Deleted by w00176964 for V3R3C60_eCall项目, 2014-4-8, end */
            /* END:   Modified by 欧阳飞  ID: 00132663, 2008/8/26 */
        }
        /*lint +e701*/
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SMS建立的MM连接                          */
        /*lint -e701*/
        if ( MM_CONST_NUM_0 != (
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( ucTI - 8 ) ) ) )
        {                                                                       /* 该连接存在                               */
            Mm_SndSmsDataInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
                pucCMMsg );                                                     /* 向SMS发送MMSMS_DATA_IND                  */
        }
        else
        {                                                                       /* 该连接不存在                             */
            Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
            pucCMMsg );                                                         /* 向SMS发送MMSMS_EST_IND                   */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
                ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                              /* 设置已经存在的MM连接的标志位             */
            Mm_TimerStop( MM_TIMER_T3230 );                                     /* 停T3230                                  */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
            Mm_ComCheckDelayMmConn( MM_FALSE );
        }
        /*lint +e701*/
    }
    else
    {

    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* 释放申请的消息                           */

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E69
  FUNCTION : 在WAIT_FOR_NETWORK_COMMAND 状态下
             收到RRMM_DATA_IND( SS Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E69(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    VOS_UINT8   ucTI = 0;                                                           /* SS消息中的TI                             */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                                   /* 指针类型转换                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* 申请内存                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* 内存申请失败                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E69:WARNING: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    /*lint -e701*/
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到SS消息中的TI                         */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* 向SS发送MMSS_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0] |=
        ( VOS_UINT8 )( 0x01 << ucTI );                                              /* 设置已经存在的MM连接的标志位             */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );

    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SS建立的MM连接                           */
        Mm_SndSsEstInd ( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize, pucCMMsg );  /* 向SS发送MMSS_EST_IND                     */
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1] |=
            ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                                  /* 设置已经存在的MM连接的标志位             */
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E69:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
    }
    /*lint +e701*/
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                                /* 释放申请的消息                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S11_E70
  FUNCTION : 在WAIT_FOR_NETWORK_COMMAND 状态下
             收到RRMM_DATA_IND( SMS Message)的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
*******************************************************************************/
VOS_VOID Mm_Cell_S11_E70(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{

    VOS_UINT8   ucTI = 0;                                                           /* SMS消息中的TI                            */
    RRMM_DATA_IND_STRU *pRrDataInd = ( RRMM_DATA_IND_STRU *) pRcvMsg;           /* 消息RRMM_DATA_IND的结构体指针            */
    VOS_UINT8   *pucCMMsg = VOS_NULL_PTR;                                       /* 指针类型转换                             */
    VOS_UINT8   *pucBakCMMsg = VOS_NULL_PTR;

    Mm_TimerStop( MM_TIMER_T3240 );                                             /* 停TIMER3240                              */
    pucCMMsg = (VOS_UINT8 *)MM_MEM_ALLOC(
                           VOS_MEMPOOL_INDEX_MM,
                           pRrDataInd->RcvNasMsg.ulNasMsgSize,
                           WUEPS_MEM_NO_WAIT);                                  /* 申请内存                                 */
    if( VOS_NULL_PTR == pucCMMsg )
    {                                                                           /* 内存申请失败                             */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S11_E70:WARNING: MALLOC ERROR!");
        return;                                                                 /* 返回                                     */
    }
    pucBakCMMsg = pucCMMsg;
    PS_MEM_SET(pucCMMsg, 0, pRrDataInd->RcvNasMsg.ulNasMsgSize );              /* 初始化内存                               */
    PS_MEM_CPY (pucCMMsg, & ( pRrDataInd->RcvNasMsg.aucNasMsg[0] ),
        pRrDataInd->RcvNasMsg.ulNasMsgSize );                                   /* 得到消息内容                             */
    ucTI = ( VOS_UINT8 )( ( ( pucCMMsg[0] & 0xf0 ) >> 4 ) );                        /* 得到SMS消息中的TI                        */
    if ( MM_CONST_NUM_7 > ucTI )
    {                                                                           /* 网侧建立的MM连接                         */
        Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
        pucCMMsg );                                                             /* 向SMS发送MMSMS_EST_IND                   */

        /*lint -e701*/
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] |=
            ( VOS_UINT8 )( 0x01 << ucTI );                                          /* 设置已经存在的MM连接的标志位             */
        /*lint +e701*/
        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else if ( ( MM_CONST_NUM_7 < ucTI ) && ( MM_CONST_NUM_15 > ucTI ) )
    {                                                                           /* SMS建立的MM连接                          */
        Mm_SndSmsEstInd( ucTI, pRrDataInd->RcvNasMsg.ulNasMsgSize,
        pucCMMsg );                                                             /* 向SMS发送MMSMS_EST_IND                   */

        /*lint -e701*/
        g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] |=
            ( VOS_UINT8 )( 0x01 << ( ucTI - 8 ) );                                  /* 设置已经存在的MM连接的标志位             */
        /*lint +e701*/

        g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;                   /* 记录迁移之前的状态                       */
        Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E70:NORMAL: STATUS is MM_CONNECTION_ACTIVE");
        Mm_ComCheckDelayMmConn( MM_FALSE );
    }
    else
    {
    }
    MM_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pucBakCMMsg);                            /* 释放申请的消息                           */

    NAS_MM_UpdateCsServiceConnStatusFlg();


    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S10_E67
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMSS_DATA_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11  新版作成
     2.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容   :DTS2013082903019:支持ss重发功能
     3.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E67(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MMSS_DATA_REQ_STRU      *pMmSsDataReq;
    pMmSsDataReq = ( MMSS_DATA_REQ_STRU* )pRcvMsg;

    if ( MM_FALSE == Mm_RcvSsDataReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( ( MM_CONST_NUM_7 > pMmSsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[0]
            & ( 0x01 << pMmSsDataReq->ulTi ) ) ) )
            || ( ( MM_CONST_NUM_7 < pMmSsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].aucMMConnExtFlg[1]
            & ( 0x01 << ( pMmSsDataReq->ulTi - 8 ) ) ) ) ) )
        {                                                                       /* 该TI的MM连接存在                         */
            Mm_SndRrDataReq( pMmSsDataReq->SsMsg.ulSsMsgSize,
                &pMmSsDataReq->SsMsg.aucSsMsg[0],
                RRC_NAS_MSG_PRIORTY_HIGH);                                      /* 将SS的消息传送下去                       */
        }
        else
        {                                                                       /* 该TI的MM连接不存在                       */
            Mm_SndSsRelInd( pMmSsDataReq->ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);                               /* 通知SS建立失败                           */
        }

        /*lint +e701*/
    }

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S10_E64
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMSMS_DATA_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-11  新版作成
     2.日    期   :2013年9月12日
       作    者   :z00161729
       修改内容  :DTS2013082903019:支持ss重发功能
     3.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E64(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    MMSMS_DATA_REQ_STRU      *pMmSmsDataReq;
    pMmSmsDataReq = ( MMSMS_DATA_REQ_STRU* )pRcvMsg;

    if ( MM_FALSE == Mm_RcvSmsDataReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( ( MM_CONST_NUM_7 > pMmSmsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << pMmSmsDataReq->ulTi ) ) ) )
            || ( ( MM_CONST_NUM_7 < pMmSmsDataReq->ulTi )
            && ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( pMmSmsDataReq->ulTi - 8 ) ) ) ) ) )
        {                                                                       /* 该TI的MM连接存在                         */
            Mm_SndRrDataReq( pMmSmsDataReq->SmsMsg.ulNasMsgSize,
                &pMmSmsDataReq->SmsMsg.aucNasMsg[0],
                RRC_NAS_MSG_PRIORTY_LOW);                                       /* 将SMS的消息传送下去                      */
        }
        else
        {                                                                       /* 该TI的MM连接不存在                       */
            Mm_SndSmsRelInd(pMmSmsDataReq->ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_TI_INVALID);/* 通知SMS建立失败                          */
        }

        /*lint +e701*/
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S9_E25
  FUNCTION : 在WAIT FOR OUTGOING MM CONNECTION状态下收到MMCC_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-15  新版作成
     2.日    期   : 2012年10月29日
       作    者   : z00161729
       修改内容   : DTS2012083102536:支持cc呼叫重建
     3.日    期   :2014年9月24日
       作    者   :s00217060
       修改内容   :for cs_err_log
*******************************************************************************/
VOS_VOID Mm_Cell_S9_E25(
    VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
)
{
    if ( MM_FALSE == Mm_RcvCcRelReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
          && ( ( ( MMCC_RELEASE_SPECIFIC == g_MmCcRelReq.ulReleaseType )
              && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].
                                                RcvXXEstReq.ulTransactionId
            == g_MmCcRelReq.ulTransactionId ) )
            || ( MMCC_RELEASE_ALL == g_MmCcRelReq.ulReleaseType ) ) )
        {                                                                       /* 要求释放的MM连接是被缓存的       */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg = MM_FALSE;                                                     /* 设置不存在缓存的MM连接 */
        }
        else
        {
            /* 这个值不会报上去，因为CC在发MMCC_REL_REQ时，主叫时CC会给CALL发MNCC_REL_IND,MNCC_REL_CNF,MNCC_REJ_IND
               如果是被叫，setup检查失败，ring还没报上去，不会有CEND上报 */
            Mm_SndCcRelInd( g_MmCcRelReq.ulTransactionId, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ);/* 通知CC指定释放的MM连接不存在             */
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();

     }

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S12_E25
 功能描述  : 在WAIT FOR RR CONNECTION (MM CONNECTION)  收到cc rel req消息处理
 输入参数  : pRcvMsg - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   :2013年8月13日
    作    者  :z00161729
    修改内容  :DTS2013081207431:mm挂起状态收到cc的t303超时abort消息，需要缓存，收到resume ind时再处理
 2.日    期   : 2014年6月13日
   作    者   : w00242748
   修改内容   : DSDS 新特性
*****************************************************************************/
VOS_VOID Mm_Cell_S12_E25(VOS_VOID  *pRcvMsg)
{
    if ( MM_FALSE == Mm_RcvCcRelReq( pRcvMsg ) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].ucMMConnEstingTI ==
                g_MmCcRelReq.ulTransactionId )
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
             && (g_MmCcRelReq.ulTransactionId ==
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



/*****************************************************************************
 函 数 名  : Mm_Cell_S1_E63
 功能描述  : 在MM IDLE NO CELL AVAILABLE状态收到MMSMS_REL_REQ的处理
 输入参数  : VOS_VOID    *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月27日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S1_E63(VOS_VOID    *pRcvMsg)
{
    if (MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg))
    {
    }
    else
    {
        /*如果存在SMS或者SS的缓存，需要清除*/
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S32_E63
 功能描述  : 在MM_INTER_RAT_CHANGE状态收到MMSMS_REL_REQ的处理
 输入参数  : VOS_VOID    *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月27日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S32_E63(
    VOS_VOID                           *pRcvMsg
)
{
    if (WAIT_FOR_OUTGOING_MM_CONNECTION == g_MmGlobalInfo.ucSuspendPreState)
    {
        Mm_Cell_S32_DataTransfer(pRcvMsg);
        return;
    }

    if (MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg))
    {
    }
    else
    {
        /*如果存在SMS或者SS的缓存，需要清除*/
        if ( (MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg)
          && (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
        }

        NAS_MM_SndRrMmServiceAbortNotify(WUEPS_PID_WRR);
        NAS_MM_SndRrMmServiceAbortNotify(UEPS_PID_GAS);

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }
}





/*******************************************************************************
  MODULE   : Mm_Cell_S10_E63
  FUNCTION : 在MM CONNECTION ACTIVE状态下收到MMSMS_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇      04-03-24  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
*******************************************************************************/
VOS_VOID Mm_Cell_S10_E63(
                        VOS_VOID            *pRcvMsg                                /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSmsRelReq.ulTi ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT8)( 0x01 << g_MmSmsRelReq.ulTi );                         /* 清除该标志位                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT8)( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) );                 /* 清除该标志位                             */
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
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]) )
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 进入空闲的状态                           */
            Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E63:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
            Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S12_E63
  FUNCTION : 在 WAIT FOR RR CONNECTION (MM CONNECTION)状态下收到MMSMS_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1. 日    期   : 2007年03月24日
        作    者   : luojian id:60022475
        修改内容   : 问题单号：A32D09756
     2.日    期   :2013年8月13日
       作    者   :z00161729
       修改内容   :DTS2013081207431:mm挂起状态收到cc的t303超时abort消息，需要缓存，收到resume ind时再处理
*******************************************************************************/
VOS_VOID Mm_Cell_S12_E63(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Cell_S12_E63:WARNING:  CHECK PRIMITIVE ERROR!");
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        if ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI ==
            g_MmSmsRelReq.ulTi )
        {
            if (g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucRat == NAS_MML_GetCurrNetRatType())
            {
                /* 终止的MM连接建立是正在建立的             */
                Mm_SndRrRelReq(RRC_CELL_UNBARRED);

                g_MmGlobalInfo.ucStaAfterWaitForNwkCmd =
                    g_MmGlobalInfo.ucStaOfRcvXXEstReq;                              /* 返回到接收到建立MM连接请求时的状态       */
                Mm_ComSetMmState(WAIT_FOR_NETWORK_COMMAND);
                Mm_ComSaveProcAndCauseVal( MM_MM_CONN_PROC, NAS_MML_REG_FAIL_CAUSE_NULL );    /* MM连接流程                               */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E63:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");
                Mm_TimerStart(MM_TIMER_T3240);                                      /* 启动TIMER3240                            */
            }
            else
            {
                Mm_ComSetMmState(g_MmGlobalInfo.ucStaOfRcvXXEstReq);
            }

            Mm_TimerStop( MM_TIMER_PROTECT_SIGNALLING );
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].ucMMConnEstingTI =
                NO_MM_CONN_ESTING;                                              /* 清除正在建立的MM连接的标志               */

            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg = MM_FALSE;
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
        }
        else
        {
            if ( ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                          .RcvXXEstReq.ucFlg )
             && ( g_MmSsAbortReq.ulTransactionId ==
             g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.
                                                            ulTransactionId ) )
            {
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS]
                                                 .RcvXXEstReq.ucFlg = MM_FALSE;
            }
        }

        NAS_MM_UpdateCsServiceBufferStatusFlg();
    }

    return;
}
/*******************************************************************************
  MODULE   : Mm_Cell_S16_E63
  FUNCTION : 在WAIT FOR ADDITIONAL OUTGOING MM CONNECTION状态下收到MMSMS_REL_REQ的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
     1.  张志勇    2005.03.28  新版作成

     2.日    期   : 2011年7月14日
       作    者   : zhoujun 40661
       修改内容   : 更新MML_CTX中的业务存在状态
*******************************************************************************/
VOS_VOID Mm_Cell_S16_E63(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    if ( MM_FALSE == Mm_RcvSmsRelReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /*lint -e701*/
        if ( ( MM_CONST_NUM_7 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0]
            & ( 0x01 << g_MmSmsRelReq.ulTi ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[0] &=
                ~(VOS_UINT8)( 0x01 << g_MmSmsRelReq.ulTi );                     /* 清除该标志位                             */
        }
        if ( ( MM_CONST_NUM_7 < g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_15 > g_MmSmsRelReq.ulTi ) &&
            ( MM_CONST_NUM_0 !=
            ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]
            & ( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) ) ) ) )
        {                                                                       /* TI小于7并且该MM连接存在                  */
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1] &=
                ~(VOS_UINT8)( 0x01 << ( g_MmSmsRelReq.ulTi - 8 ) );             /* 清除该标志位                             */
        }
        /*lint +e701*/
        if ( ( MM_TRUE ==
                g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                                                    RcvXXEstReq.ucFlg )
                && ( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].
                RcvXXEstReq.ulTransactionId == g_MmSmsRelReq.ulTi ) )
        {
            g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg
                = MM_FALSE;                                                     /* 设置不存在缓存的MM连接 */
        }
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
          g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].aucMMConnExtFlg[1]) )
        {                                                                       /* 没有MM连接存在                           */
            g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;               /* 记录迁移之前的状态                       */
            Mm_ComSetMmState(WAIT_FOR_OUTGOING_MM_CONNECTION);
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S16_E63:NORMAL: STATUS is WAIT_FOR_OUTGOING_MM_CONNECTION");
        }
    }

    NAS_MM_UpdateCsServiceConnStatusFlg();

    NAS_MM_UpdateCsServiceBufferStatusFlg();

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S3_E49
 功能描述  : 在正常服务状态接收到MMC发送的释放请求处理
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S3_E49(
    VOS_VOID                           *pRcvMsg
)
{
    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S3_E49:NORMAL: STATUS is MM_IDLE_NORMAL_SERVICE");

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S11_E49
 功能描述  : 在等待连接释放状态接收到MMC发送的释放请求处理
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年2月12日
   作    者   : w00242748
   修改内容   : DTS2014021003925:en_NV_Item_User_Auto_Resel_Switch该NV打开时，CS域
                正常服务，PS域DEREGISTER LIMIT SERVICE状态，下发AT+COPS=0触发搜网，
                搜网过程中，由于未更新服务状态，所以在搜网过程中，下发AT+COPS?查询
                结果仍为正常服务。但在搜网过程中，MMC已将CS/PS注册状态设置成未注册
                需要搜网。
 3.日    期   : 2015年3月20日
   作    者   : w00167002
   修改内容   : DTS2015030305199:LAU建联失败达到最大次数后，使用NV中定制的T3212时长,T3212启动统一
                进行封装。

*****************************************************************************/
VOS_VOID Mm_Cell_S11_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */

    Mm_TimerStop(MM_TIMER_T3240);
    Mm_TimerStop(MM_TIMER_T3218);
    Mm_ComDelRandRes();

    if ( (MM_LU_PROC == g_MmGlobalInfo.ucProc)
      && (NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal) )
    {
        NAS_MM_StartT3212Timer(NAS_MM_T3212_START_SCENE_NORMAL_START);

        if (MM_DETACH_NEED_DELAY == g_MmGlobalInfo.ucDetachType)
        {
            Mm_TimerStop(MM_TIMER_PROTECT_DETACH);
            g_MmGlobalInfo.ucDetachType = MM_DETACH_TYPE_BUTT;
            Mm_Cell_S3_E23(VOS_NULL_PTR);
        }

        Mm_ComProcCauseClear();
    }
    else if ( (MM_MM_CONN_PROC == g_MmGlobalInfo.ucProc)
           && (NAS_MML_REG_FAIL_CAUSE_NULL == g_MmGlobalInfo.usCauseVal) )
    {
        Mm_ComProcCauseClear();
    }
    else
    {
        Mm_ComProcCauseProcess();
    }

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S11_E49:NORMAL: STATUS is WAIT_FOR_NETWORK_COMMAND");

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S9_E49
 功能描述  : 在WAIT FOR OUTGOING MM CONNECTION过程中收到MM的连接释放请求
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年06月23日
   作    者   : l65478
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S9_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */

    Mm_TimerStop(MM_TIMER_T3230);

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S9_E49:NORMAL: STATUS is WAIT FOR OUTGOING MM CONNECTION");

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S10_E49
 功能描述  : 在MM CONNECTION ACTIVE过程中收到MM的连接释放请求
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年06月23日
   作    者   : l65478
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S10_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S10_E49:NORMAL: STATUS is MM CONNECTION ACTIVE");

    return;
}


/*****************************************************************************
 函 数 名  : Mm_Cell_S12_E49
 功能描述  : 在WAIT FOR RR CONNECTION过程中收到MM的连接释放请求
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年06月23日
   作    者   : l65478
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S12_E49(
    VOS_VOID                           *pRcvMsg
)
{

    Mm_SndRrRelReq(RRC_CELL_UNBARRED);                                      /* 向RRC发送RRMM_REL_REQ(CS域)              */

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_ComDelRandRes();

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S12_E49:NORMAL: STATUS is WAIT FOR RR CONNECTION");

    return;
}


/*****************************************************************************
 函 数 名  : Mm_Cell_S22_E49
 功能描述  : 在等待连接建立状态接收到MMC发送的释放请求处理
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S22_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S22_E49:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING");

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S23_E49
 功能描述  : 在位置更新正在进行状态接收到MMC发送的释放请求处理
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年08月12日
   作    者   : w00166186
   修改内容   : 新生成函数
 3.日    期   : 2014年06月12日
   作    者   : s00217060
   修改内容   : DTS2014061003286:TD2G重选，G下RAU过程中，用户指定搜TD的网络，网络不回应数据业务accept
*****************************************************************************/
VOS_VOID Mm_Cell_S23_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3211);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);


    /* 回复MMCMM_ATTACH_CNF的操作,清除等待ATTACH结果标志位 */
    if (MM_WAIT_CS_ATTACH == (g_MmGlobalInfo.stAttachInfo.enAttachType
                            & MM_WAIT_CS_ATTACH))
    {
        NAS_MM_SndMmcAttachCnf();
    }
    g_MmGlobalInfo.stAttachInfo.enAttachType = MM_WAIT_NULL_ATTACH;

    NAS_MM_ClearAuthInfo();

    g_MmSubLyrShare.MmShare.ucCsIntegrityProtect  = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;

    /* 认为本次LAU失败 */
    NAS_MM_LocationUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);         /* 调用RAU attempt counter的处理            */

    g_MmGlobalInfo.LuInfo.ucRetryFlg = MM_FALSE;


    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S23_E49:NORMAL: STATUS is LOCATION_UPDATING_INITIATED");

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S24_E49
 功能描述  : 在位置更新被拒状态接收到MMC发送的释放请求处理
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Mm_Cell_S24_E49(
    VOS_VOID                           *pRcvMsg
)
{
    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3240);
    Mm_TimerStop(MM_TIMER_T3218);

    Mm_ComDelRandRes();
    Mm_ComProcCauseProcess();

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S24_E49:NORMAL: STATUS is LOCATION_UPDATE_REJECTED");

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S25_E49
 功能描述  : 在Detach等待连接建立状态接收到MMC发送的释放请求处理
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : V7R1 PHASE II ATTACH/DETACH调整
 3.日    期   : 2015年7月22日
   作    者   : z00161729
   修改内容   : DTS2015060807763:ap通过cgcatt下发imsi detach，建链失败后mm 本地detach，回复detach cnf时应该带limit service而不是normal service，at命令回复ok而不是error
*****************************************************************************/
VOS_VOID Mm_Cell_S25_E49(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {
        return;
    }

    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_PROTECT_SIGNALLING);

    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);

        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S25_E49:NORMAL: STATUS is WAIT_FOR_RR_CONNECTION_IMSI_DETACH");

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S26_E49
 功能描述  : 在正常服务状态接收到MMC发送的释放请求处理
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数
 2.日    期   : 2011年7月25日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整

*****************************************************************************/
VOS_VOID Mm_Cell_S26_E49(
    VOS_VOID                           *pRcvMsg
)
{
    if (MM_DETACH_CS_POWEROFF == g_MmGlobalInfo.ucDetachType)
    {
        return;
    }

    /* 向RRC发送RRMM_REL_REQ(CS域) */
    Mm_SndRrRelReq(RRC_CELL_UNBARRED);

    Mm_TimerStop(MM_TIMER_T3220);

    Mm_TimerStop(MM_TIMER_PROTECT_DETACH);

    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    /* 判断等待标志是否存在，如果存在则发送MMCMM_DETACH CNF */
    if (MM_WAIT_CS_DETACH== (g_MmGlobalInfo.stDetachInfo.enDetachType
                 & MM_WAIT_CS_DETACH))
    {
        NAS_MM_SndMmcDetachCnf(MM_DETACHED);
        /* 清除等待标志 */
        g_MmGlobalInfo.stDetachInfo.enDetachType = MM_WAIT_NULL_DETACH;
    }

    g_MmGlobalInfo.ucPowerOnFlg = MM_TRUE;

    NAS_EventReport(WUEPS_PID_MM, NAS_OM_EVENT_IMSI_DETACH_IND,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    Mm_TimerStart(MM_TIMER_WAIT_CONNECT_REL);

    g_MmGlobalInfo.ucPreState   = g_MmGlobalInfo.ucState;

    Mm_ComSetMmState(MM_IDLE_PLMN_SEARCH);

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Mm_Cell_S26_E49:NORMAL: STATUS is IMSI_DETACH_INITIATED");

    return;
}

/*******************************************************************************
  MODULE   : Mm_Cell_S27_E87
  FUNCTION : 在PROCESS CM SERVICE PROMPT状态下收到MMCC_START_CC的处理
  INPUT    : VOS_VOID            *pRcvMsg  收到的原语头指针
  OUTPUT   : VOS_VOID
  RETURN   : VOS_VOID
  NOTE     :
  HISTORY  :
  1.z40661      09-12-22    新版作成

  2.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 更新MML_CTX中的业务存在状态
  3.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
*******************************************************************************/
VOS_VOID Mm_Cell_S27_E87(
                        VOS_VOID            *pRcvMsg                            /* 接收消息的头地址                         */
                    )
{
    MMCC_DATA_REQ_STRU *pstMsg;
    VOS_UINT8                           ucTi;

    pstMsg = (MMCC_DATA_REQ_STRU *)pRcvMsg;

    ucTi = (VOS_UINT8)pstMsg->ulTransactionId;
    /*lint -e701*/
    g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]  =
    (VOS_UINT8)( g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].aucMMConnExtFlg[1]
               | (0x01 << (ucTi - 0x08)) );
    /*lint +e701*/
    Mm_TimerStop(MM_TIMER_PROTECT_CCBS);
    Mm_ComSetMmState(MM_CONNECTION_ACTIVE);
    Mm_SndRrDataReq(pstMsg->SendCcMsg.ulCcMsgSize,
                            &pstMsg->SendCcMsg.aucCcMsg[0],
                            RRC_NAS_MSG_PRIORTY_HIGH);

    Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
    NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_ESTING);

    Mm_ComCheckDelayMmConn(VOS_FALSE);

    NAS_MM_UpdateCsServiceConnStatusFlg();
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S3_E88
 功能描述  : 在正常服务状态接收到MMC发送的RRMM_W_AC_INFO_CHANGE_IND
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年2月15日
    作    者  : w00166186
    修改内容  : CSFB&PPAC&ETWS&ISR 开发

*****************************************************************************/
VOS_VOID Mm_Cell_S3_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* 当前小区变为注册受限，需要迁移MM状态 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        g_MmGlobalInfo.ucMmServiceState = NAS_MM_GetLauUptNeededCsSrvStatus();
        Mm_ComSetMmState(MM_IDLE_LOCATION_UPDATE_NEEDED);

    }
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S6_E88
 功能描述  : 在MM_IDLE_LIMITED_SERVICE接收到MMC发送的RRMM_W_AC_INFO_CHANGE_IND
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年2月15日
    作    者  : w00166186
    修改内容  : CSFB&PPAC&ETWS&ISR 开发
 2 .日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  3.日    期   : 2013年05月15日
    作    者   : s46746
    修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
*****************************************************************************/
VOS_VOID Mm_Cell_S6_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU    *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd  = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* 当前小区从CS注册受限变为不受限 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        /* 用户设置不支持CS */
        if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
        {
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            return;
        }

        /* 当前网络在禁止列表中 */
        if ((MMCMM_NO_FORBIDDEN != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg)
         && (MMCMM_FORBIDDEN_PLMN_FOR_GPRS != g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
        {
            g_MmGlobalInfo.ucMmServiceState = MM_LIMITED_SERVICE;               /* 设置服务状态                             */
            Mm_ComSetMmState(MM_IDLE_LIMITED_SERVICE);
            return;
        }

        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
        if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
        /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
        {
            /* 网络PS注册受限 */
            if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
            {                                                                   /* RAC为0的场合                             */
                NAS_MM_ProcCsAcChgRegisterNetModeII();
            }
            /* 网络GPRS不支持或GPRS禁止 */
            else if ((MM_UNSUPPORT_GPRS == g_MmGlobalInfo.usRac)
             || (MMCMM_FORBIDDEN_PLMN_FOR_GPRS == g_MmGlobalInfo.MsCsInfo.ulCurFobidnFlg))
            {
                NAS_MM_SetLikeBFlg();
                NAS_MM_ProcCsAcChgRegisterNetModeII();
            }
            else
            {
            }
        }
        else
        {
            NAS_MM_ProcCsAcChgRegisterNetModeII();
        }
    }
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S9_E88
 功能描述  : 连接态收到AC_INFO_CHANGE_IND的处理
 输入参数  : pRcvMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1. 日    期   : 2012年2月15日
    作    者  : w00166186
    修改内容  : CSFB&PPAC&ETWS&ISR 开发
 2. 日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册

*****************************************************************************/
VOS_VOID Mm_Cell_S9_E88(
    VOS_VOID                           *pRcvMsg
)
{
    MMCMM_W_AC_INFO_CHANGE_IND_STRU            *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd  = (MMCMM_W_AC_INFO_CHANGE_IND_STRU*)pRcvMsg;

    /* 如果当前CS注册变为受限，需要重新设置建链前状态 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        if (MM_IDLE_NO_IMSI != g_MmGlobalInfo.ucStaOfRcvXXEstReq)
        {
            g_MmGlobalInfo.ucStaOfRcvXXEstReq       = MM_IDLE_LOCATION_UPDATE_NEEDED;
            g_MmGlobalInfo.ucStaAfterWaitForNwkCmd  = MM_IDLE_LOCATION_UPDATE_NEEDED;
        }
    }

    /* 如果当前CS注册变为不受限，需要重新设置建链前状态 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
    {
        NAS_MM_UpdateMmStateCsRegRestrictBarToUnbar();
    }

    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, begin */
    if (VOS_TRUE == NAS_MM_IsClassAAndNmoIMode(g_MmGlobalInfo.ucNtMod))
    /* Modified by w00176964 for V3R3C60_eCall项目, 2014-4-29, end */
    {
        /* 网络模式I，手机模式A，PS注册从受限变为不受限 */
        if ((NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
         && (MM_TRUE == g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg ))
        {
            g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg = MM_FALSE;
        }
    }

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : Mm_Cell_S3_E89
 功能描述  : 在MM IDLE NORMAL SERVICE 状态下收到L的T3412定时器超时消息
 输入参数  : pRcvMsg - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年3月5日
    作    者  : z00161729
    修改内容  : V7R1 C50 ISR特性修改
 2.日    期   : 2012年10月22日
   作    者   : t00212959
   修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
 3.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*****************************************************************************/
VOS_VOID Mm_Cell_S3_E89(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulT3412ExpNeedRegFlg;

    enCurrNetRatType     = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3412Status());
    ucPsRestrictionFlg   = NAS_MML_GetPsRestrictRegisterFlg();

    /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((VOS_FALSE == ulT3412ExpNeedRegFlg)
     || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRatType))
    {
        return;
    }

    /* 网络模式I下，如果GMM已经注册或者正在进行注册，无需处理 */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod))
    {
        if (VOS_TRUE == NAS_GMM_IsRegisteredOrRegistering())
        {
            return;
        }
    }

    /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
       The normal location updating procedure shall also be started if the MS is
       configured to use CS fallback and SMS over SGs, or SMS over SGs only,
       and the TIN indicates "RAT-related TMSI",
       - when the periodic tracking area update timer T3412 expires and the
       network operates in network operation mode II or III
    */
    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    Mm_ComLuOnly();

    return;

}

/*****************************************************************************
 函 数 名  : Mm_Cell_S5_E89
 功能描述  : 在MM IDLE ATTEMPTING TO UPDATE 状态收到L的T3412定时器超时消息
 输入参数  : pRcvMsg - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年3月5日
    作    者  : z00161729
    修改内容  : V7R1 C50 ISR特性修改
 2.日    期   : 2012年10月22日
   作    者   : t00212959
   修改内容   : DTS2012101907218:NAS向接入层发送LAU请求时，Establishment cause按照协议写为Registration
 3.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*****************************************************************************/
VOS_VOID Mm_Cell_S5_E89(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT32                          ulT3412ExpNeedRegFlg;

    enCurrNetRatType     = NAS_MML_GetCurrNetRatType();
    ulT3412ExpNeedRegFlg = NAS_MM_IsT3412ExpiredNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                           NAS_MML_GetTinType(), NAS_MML_GetT3412Status());
    ucPsRestrictionFlg   = NAS_MML_GetPsRestrictRegisterFlg();

    /* 3GPP 24.008中4.4.1  Location updating procedure章节描述如下：
        The normal location updating procedure shall also be started if the MS is
        configured to use CS fallback and SMS over SGs, or SMS over SGs only,
        and the TIN indicates "RAT-related TMSI",
        - when the periodic tracking area update timer T3412 expires and the
        network operates in network operation mode II or III
    */
    if ((VOS_FALSE == ulT3412ExpNeedRegFlg)
     || (NAS_MML_NET_RAT_TYPE_LTE == enCurrNetRatType))
    {
        return;
    }

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (MM_NET_MODE_I == g_MmGlobalInfo.ucNtMod)
     && (VOS_FALSE == ucPsRestrictionFlg))
    {
        return;
    }

    g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_PERIODIC_UPDATING;
    Mm_ComLuOnly();
    return;
}

#endif

/*****************************************************************************
 函 数 名  : Mm_Cell_S1_E65
 功能描述  : 在mm no cell available 状态收到ss建链请求的处理
 输入参数  : pRcvMsg - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容   :DTS2013082903019:支持ss重发功能
 2.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log
 3.日    期   : 2014年12月29日
   作    者   : z00161729
   修改内容   : DSDS业务重拨时no rf未触发搜网导致业务失败，mm在no cell available状态no rf时给mmc发送cm service ind触发搜网
*****************************************************************************/
VOS_VOID Mm_Cell_S1_E65(VOS_VOID *pRcvMsg)
{
    VOS_UINT8                           ucSimCsRegStatus;

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {                                                                           /* 消息检查结果成功                         */
        /* 当前小区主叫业务受限则不处理 */
        if (VOS_TRUE == NAS_MML_GetCsRestrictNormalServiceFlg())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR);

            return;
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* 如果当前驻留LTE,则直接回复SS失败 */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY);

            return;
        }
#endif
        /* 如果当前no rf，需要缓存业务请求，通知mmc触发搜网 */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_FALSE == NAS_MML_GetRfAvailFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MM_UpdateConnCtrlInfo(MM_CONN_CTRL_SS);
            Mm_SndMmcCmSvcInd(MM_CS_SERV_EXIST);
            return;
        }

        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_OUT_OF_COVERAGE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : Mm_Cell_S25_E65
 功能描述  : mm在wait for rr connection(imsi detach)或imsi detach initiated状态收到ss建链请求的处理
 输入参数  : pRcvMsg - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   :2013年9月12日
   作    者   :z00161729
   修改内容   :DTS2013082903019:支持ss重发功能
 2.日    期   :2014年9月24日
   作    者   :s00217060
   修改内容   :for cs_err_log
*****************************************************************************/
VOS_VOID Mm_Cell_S25_E65(VOS_VOID  *pRcvMsg)
{

    if ( MM_FALSE == Mm_RcvSsEstReq(pRcvMsg) )
    {                                                                           /* 消息检查结果失败                         */
    }
    else
    {
        Mm_SndSsRelInd(g_MmSsEstReq.ulTi, NAS_MMCM_REL_CAUSE_MM_INTER_ERR_CS_DETACH);
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
