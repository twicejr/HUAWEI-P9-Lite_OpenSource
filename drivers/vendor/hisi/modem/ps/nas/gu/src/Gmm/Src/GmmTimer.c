/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmDetach.c
  Description   : GMM定时器功能相关处理用源文件
  Function List :
    01.   Gmm_RcvTimerExpired
    02.   Gmm_Tim3302Expired
    03.   Gmm_Tim3310Expired
    04.   Gmm_Tim3311Expired
    05.   Gmm_Tim3312Expired
    06.   Gmm_Tim3312Expired_RegNmlServ
    07.   Gmm_Tim3312Expired_RegNoCell
    08.   Gmm_Tim3316Expired
    09.   Gmm_Tim3317Expired
    10.   Gmm_Tim3318Expired
    11.   Gmm_Tim3320Expired
    12.   Gmm_Tim3321Expired
    13.   Gmm_Tim3321Expired_DeregInit
    14.   Gmm_Tim3321Expired_RegImsiDtchInit
    15.   Gmm_Tim3330Expired
    16.   Gmm_Tim5sExpired
    17.   Gmm_TimerCreat
    18.   Gmm_TimerDistroy
    19.   Gmm_TimerPause
    20.   Gmm_TimerPauseForTc
    21.   Gmm_TimerResume
    22.   Gmm_TimerResumeForTc
    23.   Gmm_TimerStart
    24.   Gmm_TimerStop
    25.   Gmm_TimProtectExpired
  History       :
    1.  张志勇  2003.12.05  新规作成
    2.  s46746  2006-03-08  根据问题单A32D02368修改
    3.  s46746  2006-03-27  根据问题单A32D02387修改
    4.  s46746  2006-04-18  根据问题单A32D03102修改
    5.  l40632   2006-04-17  根据问题单A32D03132修改
    6.  s46746  2006-05-08  根据问题单A32D03487修改
    7.  l40632  2006-06-08  根据问题单A32D04196修改
    8.  日    期   : 2006年9月23日
        作    者   : sunxibo id:46746
        修改内容   : 根据问题单号：A32D05848
    9.  日    期   : 2006年11月8日
        作    者   : s46746
        修改内容   : 问题单号:A32D06867
   10.  日    期   : 2006年11月20日
        作    者   : s46746
        修改内容   : 创建，根据问题单号：A32D07433
   11.  日    期   : 2006年12月07日
        作    者   : s46746
        修改内容   : 创建，根据问题单号：A32D07799
   12.  日    期   : 2007年01月04日
        作    者   : s46746
        修改内容   : 创建，根据问题单号：A32D08235
   13.  日    期   : 2007年03月20日
        作    者   : x51137
        修改内容   : A32D09192
   14.  日    期   : 2007年3月30日
        作    者   : s46746
        修改内容   : 问题单号:A32D09854
   15.  日    期   : 2007年05月11日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D10713
   16.  日    期   : 2007年7月14日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号：A32D12438
   17.  日    期   : 2007年11月12日
        作    者   : l39007
        修改内容   : 根据问题单A32D13044,VOS_GetRelTmRemainTime函数执行失败,
                     定时器剩余时间不清零,定时器继续运行
   18.  日    期   : 2007年11月22日
        作    者   : s46746
        修改内容   : 根据问题单号：A32D13475,修改异系统改变后指派的old TLLI和开机加密密钥为全0问题
   19.  日    期   : 2007年12月14日
        作    者   : s46746
        修改内容   : 问题单A32D13638，保证进行RAU之前不向网侧发送其它数据，并且RAU不成功，不恢复层2
   20.  日    期   : 2007年12月28日
        作    者   : s46746
        修改内容   : 根据问题单号：A32D13954,修改GMM在2G3过程中缓存消息机制
   21.  日    期   : 2008年7月2日
        作    者   : l00107747
        修改内容   : 根据问题单号：AT2D03900,FOLLOW ON标志清除排查
   22.  日    期   : 2008年10月2日
        作    者   : s46746
        修改内容   : 根据问题单号：AT2D05988,W下关机时，如果GPRS Detach过程网络
                     未释放连接导致GMM 5S定时器超时，GMM未向MMC指示连接不存在
   23.  日    期   : 2007年4月25日
        作    者   : h44270
        修改内容   : 问题单号:AT2D11404/AT2D10802
   24.  日    期   : 2009年04月25日
        作    者   : h44270
        修改内容   : 问题单号:AT2D08867
   25.  日    期   : 2009年07月30日
        作    者   : x00115505
        修改内容   : 问题单号:AT2D13363,接入被拒后，GAS不应该清除GRM数据，应该先STOP GRM，等待T3172/T3146超时后，再INIT GRM。
   26.  日    期   : 2009年08月24日
        作    者   : x00115505
        修改内容   : AT2D14023,测试GCF用例44.2.2.1.9失败
   27.  日    期   : 2009年08月25日
        作    者   : l60609
        修改内容   : AT2D14064,驻留在不支持GPRS的小区，T3312超时没发起LAU
   28.  日    期   : 2009年09月07日
        作    者   : x00115505
        修改内容   : AT2D14252,数传过程中，跨RNC迁移到新RNC下，MS发起RAU过程，没有设置Follow-on
   29.  日    期   : 2010年03月15日
        作    者   : x00115505
        修改内容   : AT2D17570,某些情况Rau发起时没有上报EVENT事件
   30.  日    期   : 2010年04月14日
        作    者   : x00115505
        修改内容   : AT2D18080,Direct Signalling Re-establish触发的Rau，Counter维护错误
*******************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasTimer.h"
#include "GmmCasSend.h"
#include "GmmCasComm.h"
#include "GmmCasSuspend.h"
#include "GmmMmInterface.h"
#include  "GmmCasGsm.h"

/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
#include "NasComm.h"
/* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, end */

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_TIMER_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

extern VOS_UINT32   g_ulGmmDelaySuspendRsp;

/*lint -save -e958 */

/* delete by z00234330 for PCLINT清理, 2014-06-24, begin */
/* delete by z00234330 for PCLINT清理, 2014-06-24, end */


/* extern VOS_UINT32 Mmc_IsPlmnSearching(VOS_VOID); */

/***********************************************************************
  Module   : Gmm_TimerStart
  Function : GMM使用的定时器启动
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 张志勇    2003.12.10  新版作成
     2.日    期   : 2012年3月3日
       作    者   : z00161729
       修改内容   : V7R1 C50 支持ISR修改,T3312启动停止超时均需通知L
     3.日    期   : 2015年6月4日
       作    者   : z00161729
       修改内容   : 24008 23122 R11 CR升级项目修改
     4.日    期   : 2015年9月26日
       作    者   : c00318887
       修改内容   : 扩展GMM定时器到64个
 ************************************************************************/
VOS_VOID Gmm_TimerStart(
                    VOS_UINT8 ucTimerId                                             /* Timer ID                                 */
                    )
{
    VOS_UINT32                          ulResult;                               /* 定义变量保存TIMER启动结果                */

    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId,&pulTimerSusMask, &ucTimerBitIndex);
    
    /*lint -e701*/
    if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
    /*lint +e701*/
    {                                                                           /* 该timer已经启动                          */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStart:WARNING: This Timer has been started");
        return;                                                                 /* 返回                                     */
    }

    if ((GMM_TIMER_T3302 == ucTimerId) || (GMM_TIMER_T3312 == ucTimerId))
    {                                                                           /* T3302或T3312                             */
        if (0 == g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal)
        {                                                                       /* T3302或T3312时长为0                      */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_TimerStart:NORMAL: Timer Length of T3302 or T3312 is 0");
            return;                                                             /* 返回                                     */
        }
    }


    ulResult = Mm_StartRelTimer(      &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer,        /* 存放TIMER ID的地址                       */
                                       WUEPS_PID_GMM,
                                       g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal,     /* 时长                                     */
                                       (VOS_UINT32)ucTimerId,                             /* 消息队列的ID                             */
                                       g_GmmTimerMng.aTimerInf[ucTimerId].ulParam,        /* 消息地址                                 */
                                       g_GmmTimerMng.aTimerInf[ucTimerId].ucMode          /* 消息优先级                               */
                                       );
    if (VOS_OK != ulResult)
    {                                                                                         /* 启动失败                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_TimerStart:ERROR: Start timer unsuccessfully");
        return;                                                                               /* 返回                                     */
    }


    /*lint -e701*/
    (*pulTimerRunMask) |= (0x00000001 << ucTimerBitIndex);                  /* 置Timer的启动标志                        */

    (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);     /* 清Timer的挂起标志                        */
    /*lint +e701*/

    if (GMM_TIMER_T3314 == ucTimerId)
    {
        /*lint -e701*/
        if ((g_GmmTimerMng.ulTimerRunMask) & (0x00000001 << GMM_TIMER_T3312))   /*T3312处于运行态*/
        /*lint +e701*/
        {
#if (FEATURE_LTE == FEATURE_ON)
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
        }

        /* 24008_CR1735R3_(Rel-10)_C1-111529 was 1470 was 1012 24008-a10 24008 4.7.5.1.5章节描述如下:
        If in addition the ROUTING AREA UPDATE REQUEST message indicated "periodic updating",
        -   in Iu mode, the timer T3311 may be stopped when the MS enters PMM-CONNECTED mode;
        -   in A/Gb mode, the timer T3311 may be stopped when the READY timer is started.*/
        if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3311);
        }

        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_READY_TIMER_START,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStart:INFO: StartTimer: ", ucTimerId);

}

/***********************************************************************
  Module   : Gmm_TimerStop
  Function : GMM使用的定时器停止
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2003.12.10  新版作成
     2.  日    期   : 2006年12月07日
         作    者   : s46746
         修改内容   : 创建，根据问题单号：A32D07799
     3.  日    期   : 2007年01月04日
         作    者   : s46746
         修改内容   : 创建，根据问题单号：A32D08235
     4.  日    期   : 2007年3月30日
         作    者   : s46746
         修改内容   : 问题单号:A32D09854
     5.  日    期   : 2009年5月9日
         作    者   : l00130025
         修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
     6.  日    期   : 2010年12月18日
         作    者   : o00132663
         修改内容   : 根据问题单号：问题单号:DTS2010121800152,GMM关机关不掉，状态挂死
     7.  日    期   : 2011年5月16日
         作    者   : c00173809
         修改内容   : 根据问题单号：问题单号:DTS2011050905176,从支持GPRS的小区异系统重选到不支持GPRS的
                      小区,异常停止了T3312定时器.
     8.  日    期   : 2012年4月3日
         作    者   : z00161729
         修改内容   : 支持 ISR修改

  9.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 扩展GMM定时器到64个
 ************************************************************************/
VOS_VOID Gmm_TimerStop(
                   VOS_UINT8       ucTimerId                                    /* Timer ID                                 */
                   )
{
    VOS_UINT8    i;                                                             /* 定义循环变量                             */

    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask             = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerSuspendCtrlRunMask  = VOS_NULL_PTR;    
    VOS_UINT8                           ucTimerBitIndex;

    switch (ucTimerId)
    {                                                                           /* 判断定时器类型                           */
        case GMM_TIMER_ALL:

            for (i = 0; i < GMM_TIMER_NUM; i ++)
            {
                /* 关机保护定时器必须显示停掉，TIMER_ALL不停止该定时器 */
                if ( GMM_TIMER_1S == i )
                {
                    continue;
                }

                NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
                NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);

                /*lint -e701*/
                if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
                /*lint +e701*/
                {                                                                   /* 该定时器已经启动                         */
                    if ((GMM_TIMER_T3314 == i)
                     || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

                        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                        NAS_EventReport(WUEPS_PID_GMM,
                                        NAS_OM_EVENT_READY_TIMER_STOP,
                                        VOS_NULL_PTR,
                                        NAS_OM_EVENT_NO_PARA);
                    }


                    if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                    {                                                               /* 停止失败：已经停止或Timer不存在          */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop all timer unsuccessfully");
                        return;                                                     /* 返回                                     */
                    }
                    /*lint -e701*/
                    (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);                  /* 置Timer的启动标志                        */

                    (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);         /* 清Timer的挂起标志                        */
                    /*lint +e701*/
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", i);

                }
            }
            gstGmmSuspendCtrl.ulTimerRunMask = 0x0;

            gstGmmSuspendCtrl.ulTimerRunMaskEx              = 0x0; 
                
            break;                                                                  /* 跳出                                     */
        case GMM_REGSTER_AND_SHUTDOWN_TIMER:
            for (i = 0; i < GMM_TIMER_NUM; i ++)
            {
                /* 不支持GPRS时,不需要停止这些定时器 */
                if ((GMM_TIMER_1S == i) || (GMM_TIMER_T3302 == i) || (GMM_TIMER_T3311 == i)
                 || (GMM_TIMER_T3312 == i) || (GMM_TIMER_T3314 == i))
                {
                    continue;
                }

                NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
                NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);
                NAS_GMM_GetTimerSuspendCtrlRunMask(i, &pulTimerSuspendCtrlRunMask, &ucTimerBitIndex);
                
                /*lint -e701*/
                if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
                /*lint +e701*/
                {                                                                   /* 该定时器已经启动                         */
                    if ((GMM_TIMER_T3314 == i)
                     || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                        NAS_EventReport(WUEPS_PID_GMM,
                                        NAS_OM_EVENT_READY_TIMER_STOP,
                                        VOS_NULL_PTR,
                                        NAS_OM_EVENT_NO_PARA);
                    }

                    if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                    {                                                               /* 停止失败：已经停止或Timer不存在          */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop all timer unsuccessfully");
                    }
                    /*lint -e701*/
                    (*pulTimerRunMask)              &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);          /* 置Timer的启动标志                        */

                    (*pulTimerSusMask)              &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);         /* 清Timer的挂起标志                        */
                    
                    (*pulTimerSuspendCtrlRunMask)   &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);
                    /*lint +e701*/
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", i);

                }
            }
            break;
        case GMM_TIMER_T3312:
            /*lint -e701*/
            if (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << ucTimerId)))
            /*lint +e701*/
            {                                                                       /* Timer在启动中                            */
                if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
                {                                                                   /* 停止失败：已经停止或Timer不存在          */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop timer unsuccessfully");
                    return;                                                         /* 返回                                     */
                }
                /*lint -e701*/
                g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << ucTimerId);         /* 清Timer的启动标志                        */

                g_GmmTimerMng.ulTimerSusMask &= ~(VOS_UINT32)(0x00000001 << ucTimerId); /* 清Timer的挂起标志                        */
                /*lint +e701*/
                PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", ucTimerId);

            }
            break;

        case GMM_TIMER_ALL_EXCEPT_T3312_T3323:

           for (i = 0; i < GMM_TIMER_NUM; i ++)
           {
               if ((GMM_TIMER_1S == i )
                || (GMM_TIMER_T3312 == i)
                || (GMM_TIMER_T3323 == i))
               {
                   continue;
               }

               NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
               NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);

               /*lint -e701*/
               if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
               /*lint +e701*/
               {                                                                   /* 该定时器已经启动                         */
                   if ((GMM_TIMER_T3314 == i)
                    || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
                   {
                       gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

                       NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                       NAS_EventReport(WUEPS_PID_GMM,
                                       NAS_OM_EVENT_READY_TIMER_STOP,
                                       VOS_NULL_PTR,
                                       NAS_OM_EVENT_NO_PARA);
                   }


                   if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                       Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                   {                                                               /* 停止失败：已经停止或Timer不存在          */
                       PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop all timer unsuccessfully");
                       return;                                                     /* 返回                                     */
                   }
                   /*lint -e701*/
                   (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);          /* 置Timer的启动标志                        */

                   (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);         /* 清Timer的挂起标志                        */
                   /*lint +e701*/
                   PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", i);

               }
           }
           gstGmmSuspendCtrl.ulTimerRunMask = 0x0;
           gstGmmSuspendCtrl.ulTimerRunMaskEx              = 0x0;
           
           break;

        default:                                                                    /* 其他情况                                 */
            NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
            
            /*lint -e701*/
            if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
            /*lint +e701*/
            {                                                                       /* Timer在启动中                            */
                if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
                {                                                                   /* 停止失败：已经停止或Timer不存在          */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop timer unsuccessfully");
                    return;                                                         /* 返回                                     */
                }
                /*lint -e701*/
                (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);                  /* 置Timer的启动标志                        */

                (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);     /* 清Timer的挂起标志                        */
                /*lint +e701*/
                PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", ucTimerId);
                if (GMM_TIMER_T3314 == ucTimerId)
                {
                    NAS_EventReport(WUEPS_PID_GMM,
                                    NAS_OM_EVENT_READY_TIMER_STOP,
                                    VOS_NULL_PTR,
                                    NAS_OM_EVENT_NO_PARA);
                }

            }
            break;                                                                  /* 跳出                                     */
    }
    return;                                                                     /* 返回                                     */
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsTimerIdInTimerList
 功能描述  : 判断某个定时器是否在定时器数组中
 输入参数  : ucTimerId   特定定时器
             ucTimerNum  定时器个数
             pucTimer    定时器数组
 输出参数  : 无
 返 回 值  : VOS_TRUE  表示在该数组中
             VOS_FALSE 表示不在该数组中

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : z00161729
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsTimerIdInTimerList(
    VOS_UINT8                           ucTimerId,
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           ucIndex;

    for ( ucIndex = 0 ; ucIndex < ucTimerNum; ucIndex++ )
    {
        if ( ucTimerId == *(pucTimer + ucIndex) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_TimerStopExceptSpecialTimers
 功能描述  : GMM模块停止所有除特定定时器外的所有定时器
 输入参数  : ucTimerNum  定时器个数
             pucTimer    定时器数组
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月6日
    作    者   : z00161729
    修改内容   : 新生成函数

  2.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 扩展GMM定时器到64个
*****************************************************************************/
VOS_VOID NAS_GMM_TimerStopExceptSpecialTimers(
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucTotalTimerNum;

    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    ucTotalTimerNum = ucTimerNum;

    if (ucTotalTimerNum > GMM_TIMER_NUM)
    {
        ucTotalTimerNum = GMM_TIMER_NUM;
    }

    for (i = 0; i < GMM_TIMER_NUM; i ++)
    {
        if ( VOS_TRUE == NAS_GMM_IsTimerIdInTimerList(i, ucTotalTimerNum, pucTimer) )
        {
            continue;
        }

        NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
        NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);

        /*lint -e701*/
        if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
        /*lint +e701*/
        {                                                                   /* 该定时器已经启动                         */
            if ((GMM_TIMER_T3314 == i)
             || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
            {
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                NAS_EventReport(WUEPS_PID_GMM,
                                NAS_OM_EVENT_READY_TIMER_STOP,
                                VOS_NULL_PTR,
                                NAS_OM_EVENT_NO_PARA);
            }


            if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
            {                                                               /* 停止失败：已经停止或Timer不存在          */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_TimerStopExceptSpecialTimers:WARNING: Stop all timer unsuccessfully");
                return;                                                     /* 返回                                     */
            }
            /*lint -e701*/
            (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);             /* 清Timer的启动标志                        */

            (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);             /* 清Timer的挂起标志                        */
            /*lint +e701*/
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_TimerStopExceptSpecialTimers:INFO: StopTimer: ", i);

        }
    }

    gstGmmSuspendCtrl.ulTimerRunMask    = 0x0;
    gstGmmSuspendCtrl.ulTimerRunMaskEx  = 0x0;
}

/***********************************************************************
  Module   : Gmm_TimerPause
  Function : GMM使用的定时器暂停
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 张志勇  2003.12.10  新版作成

  2.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 扩展GMM定时器到64个
 ************************************************************************/
VOS_VOID Gmm_TimerPause(
                    VOS_UINT8                   ucTimerId                           /* Timer ID                                 */
                    )
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
    

    /*lint -e701*/
    if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex)))
    /*lint +e701*/
    {                                                                           /* 该timer已经启动                          */


        if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
        {                                                                       /* 暂停失败                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPause:WARNING: Stop timer unsuccessfully");
            return;                                                             /* 返回                                     */
        }
        /*lint -e701*/
        (*pulTimerSusMask) |= (0x00000001 << ucTimerBitIndex);              /* 设置Timer的挂起标志                      */
        /*lint +e701*/
    }
    else
    {                                                                           /* 该timer未启动                            */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPause:WARNING: Timer is not running");
        return;                                                                 /* 返回                                     */
    }
}

/***********************************************************************
  Module   : Gmm_TimerResume
  Function : GMM使用的暂停后的定时器的恢复
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2003.12.10  新版作成

  2.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 扩展GMM定时器到64个
 ************************************************************************/
VOS_VOID Gmm_TimerResume (
                      VOS_UINT8                   ucTimerId                         /* Timer ID                                 */
                      )
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (0 != ( (*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
    {                                                                           /* 该timer启动                              */
        if (0 == ((*pulTimerSusMask) & (0x00000001 << ucTimerBitIndex)))
        {                                                                       /* 该Timer未被挂起                          */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResume:WARNING: This timer has been Stoped");
            return;                                                             /* 返回                                     */
        }


        if (VOS_OK != Mm_StartRelTimer(   &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_GMM,
                                           g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal,         /* 时长                                     */
                                           (VOS_UINT32)ucTimerId,            /* 消息队列的ID                             */
                                           g_GmmTimerMng.aTimerInf[ucTimerId].ulParam,               /* 消息地址                                 */
                                           g_GmmTimerMng.aTimerInf[ucTimerId].ucMode          /* 消息优先级                               */
                                           ))
        {                                                                       /* 恢复失败                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResume:WARNING: Start timer unsuccessfully");
            return;                                                             /* 返回                                     */
        }

        (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);     /* 清Timer的挂起标志                        */
    }
    else
    {                                                                           /* 该timer未启动                            */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResume:WARNING: Timer is not running");
        return;                                                                 /* 返回                                     */
    }
    /*lint +e701*/
}

/*****************************************************************************
 函 数 名  : NAS_GMM_QryTimerStatus
 功能描述  : 查询指定的GMM定时器的状态以及剩余时间
 输入参数  : ucTimerId  - 需要查询的定时器ID
 输出参数  : pusLeftLen - 定时器的剩余时间
 返 回 值  : VOS_TRUE - 定时器在运行
             VOS_FALSE - 定时器不在运行
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年9月27日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年1月30日
    作    者   : l00130025
    修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印

  3.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 扩展GMM定时器到64个
*****************************************************************************/
VOS_UINT32  NAS_GMM_QryTimerStatus(VOS_UINT8 ucTimerId)
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
    /*lint +e701*/
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


/***********************************************************************
  Module   : Gmm_SuspendTimer
  Function : GMM使用的定时器暂停
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. s46746  2006.05.07  新版作成
     2. 日    期   : 2007年11月12日
        作    者   : l39007
        修改内容   : 根据问题单A32D13044
     3. 日    期   : 2014年3月13日
        作    者   : w00176964
        修改内容   : DTS2014031207844:SYSCFG触发detach不停止detach定时器
     4.日    期   :2014年4月2日
       作    者   :w00242748
       修改内容   :DTS2014040310584:LTE下未与网络交互的ATTACH/TAU，不停止T3211/T3212/T3213;
                   只有与网络交互后，才将T3211/T3212/T3213停止。
     5.日    期   : 2015年4月15日
       作    者   : y00245242
       修改内容   : iteration 13开发
      6.日    期   : 2015年9月26日
        作    者   : c00318887
        修改内容   : 扩展GMM定时器到64个
 ************************************************************************/
VOS_VOID GMM_SuspendTimer(VOS_VOID)
{
    VOS_UINT8 i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;

    enCurRat = NAS_MML_GetCurrNetRatType();

    gstGmmSuspendCtrl.ulTimerRunMask    = g_GmmTimerMng.ulTimerRunMask;
    gstGmmSuspendCtrl.ulTimerRunMaskEx  = g_GmmTimerMng.ulTimerRunMaskEx;
        

    for (i = 0; i < GMM_TIMER_NUM; i ++)
    {
        if ((i == GMM_TIMER_T3312) || (GMM_TIMER_T3314 == i) || (GMM_TIMER_1S == i) || (GMM_TIMER_T3323 == i))
        {
            continue;
        }

        NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
        
        /*lint -e701*/
        if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
        /*lint +e701*/
        {
            /* MMA通过SYSCFGEX触发detach和attach流程，如果detach发出后网络未响应时,
               此时进入一个新的LA和RA需要触发LAU/RAU时,避免反复的GPRS挂起延长MMA等待
               detach回复的时长,导致MMA在detach超时进行attach后GMM的detach定时器超时
               触发本地detach,此时不停止GMM启动的detach定时器,超时后直接进行本地detach
            */
            if ((VOS_TRUE                    == g_GmmDetachCtrl.ucSysCfgDetachFlg)
             && (GMM_TIMER_PROTECT_PS_DETACH == i)
             && (NAS_MML_NET_RAT_TYPE_GSM    == enCurRat))
            {
                continue;
            }

            GMM_SuspendSingleTimer(i);
            /*g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << i);*/
        }
    }

}

/***********************************************************************
  Module   : Gmm_SuspendTimer
  Function : GMM使用的定时器暂停
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. s46746  2006.05.07  新版作成
     2. 日    期   : 2007年11月12日
        作    者   : l39007
        修改内容   : 根据问题单A32D13044
     3. 日    期   : 2012年1月30日
        作    者   : l00130025
        修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
 ************************************************************************/
VOS_VOID GMM_SuspendSingleTimer(VOS_UINT8 ucTimerId)
{
    VOS_UINT32                          ulRet;


    if (VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[ucTimerId].hTimer)
    {
        ulRet = VOS_GetRelTmRemainTime(&(g_GmmTimerMng.aTimerInf[ucTimerId].hTimer),
                                       &gstGmmSuspendCtrl.ulTimerValue[ucTimerId]);
        if (VOS_OK != ulRet)
        {
            gstGmmSuspendCtrl.ulTimerValue[ucTimerId] = MM_EXTRA_DELAY_TIME_LEN;
        }
        else
        {
            gstGmmSuspendCtrl.ulTimerValue[ucTimerId] = gstGmmSuspendCtrl.ulTimerValue[ucTimerId]*MM_TIMER_TICK;
            Gmm_TimerStop(ucTimerId);
        }
    }
    else
    {
        /*  g_GmmTimerMng.aTimerInf[ucTimerId].hTimer 为空时，说明此定时器已超时或停止 */
        gstGmmSuspendCtrl.ulTimerValue[ucTimerId] = MM_EXTRA_DELAY_TIME_LEN;
    }


    return;
}

/***********************************************************************
  Module   : Gmm_ResumeTimer
  Function : GMM定时器恢复
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. s46746  2006.05.07  新版作成
     2. 日    期   : 2013年2月4日
        作    者   : w00176964
        修改内容   : DTS2011082402748:EST CNF fail导致CCO回退时,3311不需要恢复启动
     3. 日    期   : 2014年3月13日
        作    者   : w00176964
        修改内容   : DTS2014031207844:SYSCFG触发detach不停止detach定时器
      4.日    期   : 2015年9月26日
        作    者   : c00318887
        修改内容   : 扩展GMM定时器到64个
 ************************************************************************/
VOS_VOID GMM_ResumeTimer(VOS_UINT8 ucResume)
{
    VOS_UINT8                           i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT32                         *pulTimerSuspendRunMask      = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (GMM_TIMER_NOT_RESUME == ucResume)
    {
        gstGmmSuspendCtrl.ulTimerRunMask                    = 0x0;

        gstGmmSuspendCtrl.ulTimerRunMaskEx                  = 0x0;
        
        return;
    }

    for (i = 0; i < GMM_TIMER_NUM; i ++)
    {
        if ((GMM_TIMER_T3312 == i) || (GMM_TIMER_T3314 == i) || (GMM_TIMER_SUSPENDED == i))
        {
            continue;
        }

        /* CCO由于EST CNF fail导致的回退,3311通过备份机制恢复启动 */
        if ((gstGmmSuspendCtrl.ucPreRat != NAS_MML_GetCurrNetRatType())
         && (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK == gstGmmSuspendCtrl.ucSuspendCause)
         && (GMM_TIMER_T3311 == i)
         && (GMM_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
         && (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState))
        {
            continue;
        }

        NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
        NAS_GMM_GetTimerSuspendCtrlRunMask(i, &pulTimerSuspendRunMask, &ucTimerBitIndex);
        
        /*lint -e701*/
        if (0 != ((*pulTimerSuspendRunMask) & (0x00000001 << ucTimerBitIndex)))
        /*lint +e701*/
        {
            /* MMA通过SYSCFGEX触发detach和attach流程，如果detach发出后网络未响应时,
               此时进入一个新的LA和RA需要触发LAU/RAU时,避免反复的GPRS挂起延长MMA等待
               detach回复的时长,导致MMA在detach超时进行attach后GMM的detach定时器超时
               触发本地detach,此时不停止GMM启动的detach定时器,超时后直接进行本地detach
            */
            if ((VOS_TRUE                    == g_GmmDetachCtrl.ucSysCfgDetachFlg)
             && (GMM_TIMER_PROTECT_PS_DETACH == i)
             && (NAS_MML_NET_RAT_TYPE_GSM    == enCurRat))
            {
                continue;
            }

            if (VOS_OK != Mm_StartRelTimer(&g_GmmTimerMng.aTimerInf[i].hTimer,
                                            WUEPS_PID_GMM,
                                            gstGmmSuspendCtrl.ulTimerValue[i],
                                            (VOS_UINT32)i,
                                            g_GmmTimerMng.aTimerInf[i].ulParam,
                                            VOS_RELTIMER_NOLOOP))
            {
                GMM_LOG_WARN("Gmm_ResumeTimer:Resume some timer fail.");
            }
            else
            {
                /*lint -e701*/
                (*pulTimerRunMask) |= (0x00000001 << ucTimerBitIndex);
                /*lint +e701*/
            }
        }
    }
    gstGmmSuspendCtrl.ulTimerRunMask = 0x0;
    gstGmmSuspendCtrl.ulTimerRunMaskEx = 0x0;
}


/***********************************************************************
  Module   : Gmm_Tim3302Expired
  Function : 定时器T3302溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 张志勇  2003.12.10  新版作成
     2.日    期   : 2012年2月15日
       作    者   : w00166186
       修改内容   : CSFB&PPAC&ETWS&ISR 开发
     3.日    期   : 2013年7月19日
       作    者   : w00167002
       修改内容   : DTS2013071900239:W下网络模式I,联合注册PS only成功，CS失败原因
                    #17,网络模式由I--->II,此时不应发起联合ATTACH.
                    如果此时依然是网络模式I,但用户设置为PS ONLY,则也不用发起
                    联合ATTACH.
     4.日    期   : 2015年1月5日
       作    者   : z00161729
       修改内容   : AT&T 支持DAM特性修改
 ************************************************************************/
VOS_VOID Gmm_Tim3302Expired(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;

    /* 当前驻留在LTE,不处理 */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        return;
    }

    ucCsRestrictionFlg  = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();
    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断GMM当前状态                          */
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:

        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* attach attempt counter清0                */

        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 调用函数触发ATTACH过程                   */
        break;                                                                  /* 跳出                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter 清0                  */

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 调用函数触发RAU过程                      */
        break;                                                                  /* 跳出                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:


        /* 如果当前只是PS ONLY， 或者网络模式II,则不需要进行联合ATTACH */
        if ((VOS_TRUE       == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
         && (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
         && (GMM_NET_MODE_I  == g_GmmGlobalCtrl.SysInfo.ucNetMod))

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH); /* 调用函数触发RAU过程                      */
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 调用函数触发RAU过程                      */
        }
        break;                                                                  /* 跳出                                     */
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_REGISTERED_UPDATE_NEEDED:
        if (  (VOS_TRUE == ucPsRestrictionFlg)
            &&(VOS_FALSE == ucCsRestrictionFlg)
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3302_EXPIRED);          /* 通知MM进行LU                             */
        }
        break;                                                                  /* 跳出                                     */
    default:                                                                    /* 其他情况                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Tim3302Expired:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;                                                                  /* 跳出                                     */
    }
}

/***********************************************************************
  Module   : Gmm_Tim3310Expired
  Function : 定时器T3310溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇    2003.12.10  新版作成

  2.日    期   : 2009年5月7日
    作    者   : l00130025
    修改内容   : 根据问题单号：AT2D11692/At2D11768,HPlmnTIMER和T3310,T3311同时超时的处理

  3.日    期   : 2009年09月25日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D14675,RAU/Attach过程中，list搜网失败

  4.日    期   : 2010年7月21日
    作    者   : 欧阳飞
    修改内容   : DTS2010071500036,当ATTACH或RAU失败后，未通知LL清除信令数据
                 ，导致UE仍然在反复重发数据
  5.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  6.日    期   : 2011年11月8日
    作    者   : s46746
    修改内容   : V7R1 PhaseII阶段解决关机慢问题
  7.日    期   : 2011年12月24日
    作    者   : w00166186
    修改内容   : DTS2011122104474,指定搜网不停LAU问题统一修改
  8.日    期   : 2012年08月24日
    作    者   : m00217266
    修改内容   : 修改Gmm_SndSmEstablishCnf接口，添加原因值
  9.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
 10.日    期   : 2014年05月22日
    作    者   : W00242748
    修改内容   : DTS2014050900899:将GMM的处理状态通知给WAS
 11.日    期   : 2015年4月21日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
************************************************************************/
VOS_VOID Gmm_Tim3310Expired(VOS_VOID)
{
    NAS_MSG_STRU                    *pNasMsg = VOS_NULL_PTR ;
    VOS_UINT8                        ucAttachType;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    /* 如果当前接入技术是G，给GAS发送GRRGMM_GPRS_PROC_IND,类型为ATTACH,标志为FINISH */
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA== enCurRat))
    {
        NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ATTACH, RRMM_GMM_PROC_FLAG_FINISH);

        NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_ATTACH);
        NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_FINISH);
    }
    /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断GMM状态是GMM_REGISTERED_INITIATED    */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_SIGNALLING);
        }

        g_GmmAttachCtrl.ucT3310outCnt++;                                        /* 变量T3310溢出次数加1                     */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }

        if (g_GmmAttachCtrl.ucT3310outCnt < GMM_TIMER_EXPIRED_MAX_CNT)
        {                                                                       /* 判断ucT3310OutCnt 小于 5                 */

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            /* 如果当前接入技术是G，给GAS发送GRRGMM_GPRS_PROC_IND,类型为ATTACH,标志为START */
            if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
              || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
            {
                NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ATTACH, RRMM_GMM_PROC_FLAG_START);

                NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_ATTACH);
                NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_START);
            }
            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if (FEATURE_ON == FEATURE_DSDS)

            if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
            {
                NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);
                NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);
            }
#endif

            pNasMsg = Gmm_AttachRequestMsgMake();                               /* 调用函数制作空口消息attach request       */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);              /* 使用RRMM_DATA_REQ原语发送attach request  */
            Gmm_TimerStart(GMM_TIMER_T3310);                                    /* 此函数内，会判断Timer是否运行。若正在运
                                                                                 * 行，不作操作                             */


            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         enCause);

            if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
              || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
            {
                ucAttachType = NAS_OM_GMM_GPRS_ATTACH;
            }
            else if (GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
            {
                ucAttachType = NAS_OM_GMM_COMBINED_GPRS_IMSI_ATTACH;

                NAS_GMM_SndMmCombinedAttachRejected(enCause);

                NAS_GMM_SndMmCombinedRauInitiation();

            }
            else
            {
                ucAttachType = NAS_OM_GMM_COMBINED_GPRS_IMSI_ATTACH;

                NAS_GMM_SndMmCombinedAttachRejected(enCause);

                NAS_GMM_SndMmCombinedRauInitiation();

            }
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_ATTACH_REQ,
                            (VOS_VOID *)&ucAttachType,
                            NAS_OM_EVENT_ATTACH_REQ_LEN);


        }
        else
        {                                                                       /* 判断ucT3310OutCnt 大于 5                 */
            g_GmmAttachCtrl.ucT3310outCnt = 0;                                  /* 变量T3310溢出次数清0                     */
            g_GmmAttachCtrl.ucRetryFlg = GMM_FALSE;                             /* 设置换小区不进行attach标志               */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                          /* 清除followon标志                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {                                                                   /* ATTACH过程是由SM触发的                   */
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_T3310_EXPIRED);/* 通知SM GMM注册失败                       */
                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                         /* 清ucSmCnfFlg标志                         */
            }
            if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
             && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

                Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);

                if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
                    || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
                {
                    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                                    enCause);
                }
                else
                {
                    NAS_GMM_SndMmCombinedAttachRejected(enCause);
                }


                /* 向MMC发送PS注册结果 */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             enCause);

                /* 事件上报 */
                NAS_EventReport(WUEPS_PID_GMM,
                                NAS_OM_EVENT_ATTACH_FAIL,
                                &enCause,
                                NAS_OM_EVENT_ATTACH_FAIL_LEN
                                );

            }
            else
            {
                Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);           /* 调用函数处理T3310溢出五次                */
            }
            g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                 /* 清除正在进行的specific过程标志           */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim3310Expired:INFO: specific procedure ended");
        }
    }
    return;                                                                     /* 返回                                     */
}

/***********************************************************************
  Module   : Gmm_Tim3311Expired
  Function : 定时器T3311溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2003.12.10  新版作成
     2.  日    期   : 2009年5月7日
         作    者   : l00130025
         修改内容   : 根据问题单号：AT2D11692/At2D11768,HPlmnTIMER和T3310,T3311同时超时的处理
     3.  日    期   : 2011年04月02日
         作    者   : f00179208
         修改内容   : 根据问题单号：DTS2011032604117,周期性RAU建链失败后，没有再发起周期性RAU
     4.  日    期   : 2013年06月18日
         作    者   : l65478
         修改内容   : 问题单号：DTS2013061406222,T3311超时时,发起RAU时应该判断 CS的业务状态

     5.日    期   : 2013年7月19日
       作    者   : w00167002
       修改内容   : DTS2013071900239:W下网络模式I,联合注册PS only成功，CS失败原因
                    #17,网络模式由I--->II,此时不应发起联合ATTACH.
                    如果此时依然是网络模式I,但用户设置为PS ONLY,则也不用发起
                    联合ATTACH.
     6.日    期   : 2014年6月17日
       作    者   : s00217060
       修改内容   : DTS2014061003286:记录T3311超时标志，在GMM_REGISTERED_NO_CELL_AVAILABLE/
                    GMM_REGISTERED_PLMN_SEARCH收到系统消息时作RAU
***********************************************************************/
VOS_VOID Gmm_Tim3311Expired(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;

    ucCsRestrictionFlg  = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断GMM当前状态                          */
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 调用函数触发ATTACH过程                   */
        break;                                                                  /* 跳出                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_NORMAL_SERVICE:
        if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
         && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);            /* 调用函数触发周期性RAU过程                      */
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* 调用函数触发RAU过程                      */
        }
        break;                                                                  /* 跳出                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        /*Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);*/           /* 调用函数触发RAU过程                      */


        /* 如果当前只是PS ONLY， 或者网络模式II,则不需要进行联合ATTACH */
        if ( VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm() )
        {

            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }

        break;                                                                  /* 跳出                                     */
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_REGISTERED_UPDATE_NEEDED:
        /* 记录T3311超时标志，在GMM_REGISTERED_NO_CELL_AVAILABLE状态收到系统消息之后触发RAU */
        g_GmmRauCtrl.ucT3311ExpiredFlg = GMM_TRUE;

        if (  (VOS_TRUE == ucPsRestrictionFlg)
            &&(VOS_FALSE == ucCsRestrictionFlg)
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3311_EXPIRED);          /* 通知MM进行LU                             */
        }
        break;                                                                  /* 跳出                                     */
    default:                                                                    /* 其他情况                                 */

        /* 记录T3311超时标志，在GMM_REGISTERED_PLMN_SEARCH状态收到系统消息之后触发RAU */
        g_GmmRauCtrl.ucT3311ExpiredFlg = GMM_TRUE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Tim3311Expired:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;                                                                  /* 跳出                                     */
    }
}

/***********************************************************************
  Module   : Gmm_Tim3312Expired
  Function : 定时器T3312溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2003.12.10  新版作成
     2. 日    期   : 2007年05月11日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D10713
     3. 日    期   : 2007年7月14日
        作    者   : luojian id:60022475
        修改内容   : 根据问题单号：A32D12438
     4. 日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
     5. 日    期   : 2012年3月3日
        作    者   : z00161729
        修改内容   : V7R1 C50 支持ISR修改,T3312启动停止超时均需通知L
     6. 日    期   : 2012年5月7日
        作    者   : l00171473
        修改内容   : DTS2012050204913, L模时不需要发起LU
     7. 日    期   : 2012年11月25日
        作    者   : l65478
        修改内容   : DTS2012112606482,GCF 9.2.3.3.2测试失败
     8. 日    期   : 2013年1月23日
        作    者   : w00176964
        修改内容   : DTS2013012290625:3312超时在L下驻留态清除GS口
 ************************************************************************/
VOS_VOID Gmm_Tim3312Expired(VOS_VOID)
{
    VOS_UINT32                  ucOldState;

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim3312Expired:INFO:T3312 Expire.");
    GMM_PrintState();

    ucOldState = g_GmmGlobalCtrl.ucState;
#if (FEATURE_LTE == FEATURE_ON)
     NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_EXP);

     if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     {
         g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
         if (VOS_TRUE == NAS_GMM_IsNeedStartT3323())
         {
             Gmm_TimerStart(GMM_TIMER_T3323);
         }

        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_Tim3312Expired: Clear ucGsAssociationFlg to VOS_FALSE");
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

         return;
     }
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态                             */
    case GMM_REGISTERED_NORMAL_SERVICE:
        Gmm_Tim3312Expired_RegNmlServ();                                        /* 调用状态GMM_REGISTERED_NORMAL_SERVICE下  *
                                                                                 * 的T3312溢出处理                          */
        break;                                                                  /* 跳出                                     */

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        Gmm_Tim3312Expired_RegNoCell();                                         /* 调用状态GMM_REGISTERED_NO_CELL_AVAILABLE *
                                                                                 * 下的T3312溢出处理                        */
        break;
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_REGISTERED_UPDATE_NEEDED:
        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;

        if (  (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* 通知MM进行LU                             */
        }

#if (FEATURE_LTE == FEATURE_ON)
        /* GMM处于注册被bar状态且ISR激活，需要启动T3323定时器 */
        if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
        {
            Gmm_TimerStart(GMM_TIMER_T3323);
        }
#endif
        break;                                                                  /* 跳出                                     */

    case GMM_REGISTERED_PLMN_SEARCH:
        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;

#if (FEATURE_LTE == FEATURE_ON)

        /* GMM丢网时处于GMM_REGISTERED_PLMN_SEARCH且ISR激活，需要启动T3323定时器，
           正常搜网如背景搜的快速指定搜状态ISR激活无需启动T3323  */
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {
            Gmm_TimerStart(GMM_TIMER_T3323);
        }
#endif
        break;

     default:                                                                    /* 其他情况                                 */
        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;                                                                            /* 跳出                                     */
        break;
    }

    /* 当前在LTE下并且GMM非REG_NORMAL_SERVICE态,清除GS口 */
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (GMM_REGISTERED_NORMAL_SERVICE != ucOldState)
     && (GMM_REGISTERED_PLMN_SEARCH    != ucOldState))
    {
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
    }

    return;
}

/***********************************************************************
  Module   : Gmm_Tim3312Expired_RegNmlServ
  Function : 定时器T3312在状态GMM_REGISTERED_NORMAL_SERVICE下的溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2003.12.10  新版作成
     2. 日    期   : 2007年05月11日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D10713
     3. 日    期   : 2009年04月25日
        作    者   : h44270
        修改内容   : 问题单号:AT2D08867
     4. 日    期   : 2010年12月08日
        作    者   : l00167671
        修改内容   : 问题单号:DTS2010111202717,重选过程中不做RAU,
                      等到SYS_INFO上报时再做
     5. 日    期   : 2012年2月02日
        作    者   : l00130025
        修改内容   : 问题单号:DTS2012011906061,只在G下需要判断gstGmmCasGlobalCtrl.ucCellReselFlg
************************************************************************/
VOS_VOID Gmm_Tim3312Expired_RegNmlServ(VOS_VOID)
{
    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;                                  /* 置3312溢出标志                           */


    /*当前G下不在重选或搜网中时，发起周期性RAU */
    if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
     && (VOS_FALSE == gstGmmCasGlobalCtrl.ucCellReselFlg))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {
    }


}


/***********************************************************************
  Module   : Gmm_Tim3312Expired_RegNoCell
  Function : 定时器T3312在状态GMM_REGISTERED_NO_CELL_AVAILABLE下的溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 张志勇 2003.12.10  新版作成
     2. 日    期   : 2007年05月11日
        作    者   : luojian id:60022475
        修改内容   : 问题单号:A32D10713
     3. 日    期   : 2011年03月24日
        作    者   : 欧阳飞
        修改内容   : 问题单号:DTS2011032400460，驻留成功后，用户指定不存在网络搜网，
                     受限驻留后，T3312超时后，MM发起了不期望的LAU
     4.日    期   : 2012年3月7日
       作    者   : z00161729
       修改内容   : V7R1 C50 支持ISR修改
     5.日    期   : 2013年2月4日
       作    者   : w00176964
       修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 ************************************************************************/
VOS_VOID Gmm_Tim3312Expired_RegNoCell(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType = NAS_MML_GetTinType();

    /* GMM处于GMM_REGISTERED_NO_CELL_AVAILABLE或GMM_REGISTERED_LIMITED_SERVICE且ISR激活，
       需要启动T3323定时器 */
    if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
    {
        Gmm_TimerStart(GMM_TIMER_T3323);
    }
#endif

    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;                                  /* 标记T3312已经溢出                        */

    if ((GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {                                                                           /* 当前小区不支持GPRS                       */
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* 用户模式A且网络模式I                     */
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* 通知MM进行LU                             */
        }
    }
    else
    {
    }
}


/***********************************************************************
  Module   : Gmm_Tim3316Expired
  Function : 定时器T3316溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2003.12.10  新版作成
    2.日    期  :2014年01月09日
      作    者  :l65478
      修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突

 ************************************************************************/
VOS_VOID Gmm_Tim3316Expired(VOS_VOID)
{
    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* 将RES存在标志置为FALSE                   */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* RAND存在标志置成FALSE                    */
}


/***********************************************************************
  Module   : Gmm_Tim3317Expired
  Function : 定时器T3317溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇    2003.12.10  新版作成
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2012年3月17日
    作    者   : w00176964
    修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加拨号被拒定制
  4.日    期   : 2012年08月24日
    作    者   : m00217266
    修改内容   : 修改GMM_SndSmServiceRej接口，添加原因值

************************************************************************/
VOS_VOID Gmm_Tim3317Expired(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态是SERVICE_REQUEST_INITIATED  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* 调用状态的公共处理                       */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                                        == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComCnfHandle();
        if ((GMM_SERVICE_REQUEST_DATA_IDLE
                        == g_GmmGlobalCtrl.ucSpecProc)
                 || (GMM_SERVICE_REQUEST_SIGNALLING
                        == g_GmmGlobalCtrl.ucSpecProc)
                 || (GMM_SERVICE_REQUEST_PAGING_RSP
                        == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* service request的类型为：PMM-IDLE下触发
                                                                                 * data,signalling,paging response三者之一  */
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                               /* 释放信令                                 */
        }
        else
        {
        }

        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
        }

        if (VOS_TRUE== NAS_MML_GetDailRejectCfg())
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_T3317_EXPIRED);

            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        enCause);                                     /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* 向MMC发送service request结果 */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                              enCause);
        /* 事件上报 */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REJ,
                        (VOS_VOID*)&enCause,
                        NAS_OM_EVENT_SERVICE_REJ_LEN);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim3317Expired:INFO: specific procedure ended");
    }
}

/***********************************************************************
  Module   : Gmm_Tim3318Expired
  Function : 定时器T3318溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 张志勇  2003.12.10  新版作成
     2.日    期   : 2009年03月31日
       作    者   : L65478
       修改内容   : 根据问题单号：AT2D10529两次鉴权失败后没有释放RRC连接
     3.日    期   : 2012年4月20日
       作    者   : l00130025
       修改内容   : DTS2012032004389，Netork连续3次被Ms Auth Rej或T3318/T3320超时时，没有通知GAS Bar掉当前小区
     4.日    期   : 2012年12月25日
       作    者   : L65478
       修改内容   : DTS2012122900226,G下定时器超时根据失败次数决定是否禁止当前小区
     5.日    期   : 2013年01月23日
       作    者   : L65478
       修改内容   : DTS2013012301527,GCF 12.6.1.3.3失败
 ************************************************************************/
VOS_VOID Gmm_Tim3318Expired(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* Authentication attempt counter清0 */
    /* 当前小区被barred */
    /* 当前的RAT是W，立刻终止当前的连接;当前的RAT是G，连续鉴权失败3次再终止当前的连接 */
    if (((g_GmmAuthenCtrl.ucAuthenAttmptCnt >= GMM_AUTHEN_ATTEMPT_MAX_CNT)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
     || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat))
    {
        g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;
        g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

        /* 当前小区被barred)                        */
        NAS_GMM_SndGasGprsAuthFailNotifyReq();

        Gmm_SndRrmmRelReq(RRC_CELL_BARRED);
    }

    /* 存在被停止的retransmission timer将其启动 */
    Gmm_Start_StopedRetransmissionTimer();
}
/***********************************************************************
  Module   : Gmm_Tim3319Expired
  Function : 定时器T3319溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
        1.  x00115505     2009.05.11  新版做成
 ************************************************************************/
VOS_VOID Gmm_Tim3319Expired(VOS_VOID)
{
    VOS_VOID                            *pMsg;
    GMMRABM_REESTABLISH_REQ_STRU        *pRabmReEst;

    if (GMM_MSG_HOLD_FOR_SERVICE ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的SR原语                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */

        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;

        /*构造分发消息*/
        pRabmReEst = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        if (VOS_NULL_PTR == pRabmReEst)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        Gmm_MemCpy(pRabmReEst, pMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        /*释放保存的RAMB消息*/
        Gmm_MemFree(pMsg);

        /*分发缓存的Service消息*/
        Gmm_MsgDistribute((VOS_VOID *)(pRabmReEst));

        /*释放新申请的内存*/
        Gmm_MemFree(pRabmReEst);
    }
}
/***********************************************************************
  Module   : Gmm_Tim3320Expired
  Function : 定时器T3320溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2003.12.10  新版作成
 ************************************************************************/
VOS_VOID Gmm_Tim3320Expired(VOS_VOID)
{
    Gmm_Tim3318Expired();
}

/***********************************************************************
  Module   : Gmm_Tim3321Expired
  Function : 定时器T3321溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2003.12.10  新版作成
 ************************************************************************/
VOS_VOID Gmm_Tim3321Expired(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态                             */
    case GMM_DEREGISTERED_INITIATED:
        Gmm_Tim3321Expired_DeregInit ();                                        /* 调用T3321在状态GMM_DEREGISTERED_INITIATE
                                                                                 * D下的溢出处理                            */
        break;                                                                  /* 跳出                                     */
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_Tim3321Expired_RegImsiDtchInit ();                                  /* 调用T3321在状态GMM_REGISTERED_IMSI_DETAC *
                                                                                 * H_INITIATED下的溢出处理                  */
        break;                                                                  /* 跳出                                     */
    default:                                                                    /* 其他情况                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Tim3321Expired:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;                                                                  /* 跳出                                     */
    }
}

/*****************************************************************************
 函 数 名  : VOS_VOID NAS_GMM_TimerProtectPsDetachExpired(VOS_VOID)
 功能描述  : GMM PS的Detach消息保护定时器超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_TimerProtectPsDetachExpired(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulGmmState;

    ulGmmState = g_GmmGlobalCtrl.ucState;

    /* 删除缓存的PS域DETACH原语 */
    ulRslt = NAS_GMM_DeleteSavedDetachMsg(GMM_WAIT_PS_DETACH);

    if ( VOS_TRUE == ulRslt )
    {
        /* 通知MMC/MM当前detach结果 */
        g_GmmGlobalCtrl.stDetachInfo.enDetachType = GMM_WAIT_PS_DETACH;

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        NAS_GMM_SndMmcMmDetachInfo();
    }

    switch ( ulGmmState )
    {
        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:

            /* 挂起状态进行本地detach，处理完毕，直接返回 */
            NAS_GMM_LocalDetach_GprsSuspension();
            return;

        case GMM_DEREGISTERED_INITIATED:

            /* GMM_DEREGISTERED_INITIATED状态进行本地detach，处理完毕，直接返回 */
            NAS_GMM_LocalDetach_GmmDeregisteredInitiated();
            return;

        case GMM_ROUTING_AREA_UPDATING_INITIATED:

            /* GMM_ROUTING_AREA_UPDATING_INITIATED状态进行本地detach，处理完毕，直接返回 */
            NAS_GMM_LocalDetach_GmmRauInitiated();
            return;

        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

            /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE状态进行本地detach，处理完毕，直接返回  */
            NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach();
            return;

        case GMM_REGISTERED_NO_CELL_AVAILABLE :
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
            break;

        case GMM_REGISTERED_PLMN_SEARCH :
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
            break;

        case GMM_REGISTERED_LIMITED_SERVICE :
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            break;

        case GMM_REGISTERED_UPDATE_NEEDED :
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            break;

        /* 如下状态不进行迁移 */
        case GMM_DEREGISTERED_NO_IMSI :
        case GMM_DEREGISTERED_PLMN_SEARCH :
        case GMM_DEREGISTERED_LIMITED_SERVICE :
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE :
        case GMM_NULL :
        case GMM_DEREGISTERED_ATTACH_NEEDED :

            break;

        /* 如下是否都可以迁移到GMM_DEREGISTERED_NORMAL_SERVICE */
        default:
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            break;
    }

    /* GMM进行本地PS域DETACH */
    NAS_GMM_GprsLocalDetach();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_Gmm_RcvMmT3211ExpiredNotify
 功能描述  : GMM收到MM的T3211定时器超时消息的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmT3211ExpiredNotify(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucPsAttachAllowFlg;
    NAS_MML_CONN_STATUS_INFO_STRU                          *pstConnStatus = VOS_NULL_PTR;
    MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU                  *pstT3211ExpiredNotify = VOS_NULL_PTR;
    VOS_UINT8                                               ucSimPsRegStatus;

    pstConnStatus         = NAS_MML_GetConnStatus();
    pstT3211ExpiredNotify = (MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU *)pstMsg;
    ucSimPsRegStatus      = NAS_MML_GetSimPsRegStatus();

    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        /* 当前驻留网络不在支持DAM特性网络列表中，不处理 */
        return;
    }

    /* 如果mm启动T3211定时器时lau被拒原因值不为#17则不处理，GSM-BTR-1-0644和
       GSM-BTR-1-0650和GSM-BTR-1-0652和GSM-BTR-1-0656测试用例都是lau被#17拒绝 */
    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstT3211ExpiredNotify->ucRejectCause)
    {
        return;
    }

    /* GAS下PS可以发起注册GMM才缓存该消息，后续收到GAS的gprs resume ind消息
       和cs信令连接不存消息时处理缓存的T3211定时器超时消息
       如果在register normal service状态也需触发rau，*/

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

        /* PS可以发起注册时才需要设置收到T3211定时器超时标识 */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (VOS_TRUE  == ucPsAttachAllowFlg)
         && (VOS_TRUE == ucSimPsRegStatus))
        {
            if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
            {
                /* RR连接不存在表示CS正在建立连接,需要设置收到T3211定时器超时标识*/
                if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
                {
                    NAS_GMM_SetMmT3211ExpiredDelayRauFlag(VOS_TRUE);
                }
                return;
            }
        }
        return;
    }

    /* AT&T GSM-BTR-1-0644和GSM-BTR-1-0650和GSM-BTR-1-0652和GSM-BTR-1-0656测试用例
      要求MM在attempting to update状态，T3211定时器超时，MM做lau的同时，
      通知GMM T3211定时器超时，W下GMM在register normal service状态也需触发rau*/
    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    /* 如果gmm在GMM_SERVICE_REQUEST_INITIATED状态，如rabm重建或pdp激活过程中，缓存*/
    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        NAS_GMM_SetMmT3211ExpiredDelayRauFlag(VOS_TRUE);
    }

    return;
}


/*****************************************************************************
 函 数 名  : VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd(VOS_VOID)
 功能描述  : GMM收到MM的CS域本地Detach消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd(
    VOS_VOID                           *pstMsg
)
{
    /* 删除缓存的CS域DETACH */
    (VOS_VOID)NAS_GMM_DeleteSavedDetachMsg(GMM_WAIT_CS_DETACH);

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态分发                             */
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit();
            break;

        case GMM_REGISTERED_INITIATED:
            NAS_Gmm_RcvMmCsLocalDetachInd_RegInit();
            break;

        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            NAS_Gmm_RcvMmCsLocalDetachInd_RauInit();
            break;

        default:
            break;
    }

    /* 网络模式I下,CS DETACH标志存在,则删除标志 */
    if (GMM_WAIT_CS_DETACH ==
        (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH) )
    {
        g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_CS_DETACH;
    }

    return;
}


/***********************************************************************
  Module   : Gmm_Tim3321Expired_DeregInit
  Function : 定时器T3321溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇    2003.12.10  新版作成
  2. 日    期   : 2006年9月23日
     作    者   : sunxibo id:46746
     修改内容   : 根据问题单号：A32D05848
  3. 日    期   : 2006年11月20日
     作    者   : s46746
     修改内容   : 创建，根据问题单号：A32D07433
  4. 日    期   : 2011年07月13日
     作    者   : w00166186
     修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  5.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持GMM需要将服务域不支持信息通知给MMC.
  7.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
************************************************************************/
VOS_VOID Gmm_Tim3321Expired_DeregInit(VOS_VOID)
{
    NAS_MSG_STRU         *pNasMsg = VOS_NULL_PTR ;                              /* 定义指针                                 */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }
    g_GmmDetachCtrl.ucT3321OutCnt ++;                                           /* T3321溢出次数加1                         */
    if (g_GmmDetachCtrl.ucT3321OutCnt < GMM_TIMER_EXPIRED_MAX_CNT)
    {                                                                           /* 判断溢出次数是否小于5                    */

#if (FEATURE_ON == FEATURE_DSDS)
        /* 在DSDS时，GSM下ATTACH/RAU/DETACH失败时，可能已经释放了资源，需要重新申请，否则主模一直获取不到资源 */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
        }
#endif

        pNasMsg = Gmm_DetachRequestMsgMake();                                   /* 调用detach request消息制作函数           */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                  /* 发送DETACH REQUEST消息                   */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* 启T3321                                  */
    }
    else
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */

        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);     /* 置PS域的attach禁止标志                   */
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;

        g_GmmDetachCtrl.ucT3321OutCnt = 0;                                      /* T3321溢出次数清0                         */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }



        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
        }

    }
    return;                                                                     /* 返回                                     */
}

/***********************************************************************
  Module   : Gmm_Tim3321Expired_RegImsiDtchInit
  Function : 定时器T3321溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 张志勇    2003.12.10  新版作成

************************************************************************/
VOS_VOID Gmm_Tim3321Expired_RegImsiDtchInit(VOS_VOID)
{
    NAS_MSG_STRU        *pNasMsg = VOS_NULL_PTR ;                               /* 定义指针                                 */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }
    g_GmmDetachCtrl.ucT3321OutCnt++;                                            /* T3321溢出次数加1                         */
    if (GMM_TIMER_EXPIRED_MAX_CNT > g_GmmDetachCtrl.ucT3321OutCnt)
    {                                                                           /* 判断溢出次数小于5                        */


#if (FEATURE_ON == FEATURE_DSDS)
        /* 在DSDS时，GSM下ATTACH/RAU/DETACH失败时，可能已经释放了资源，需要重新申请，否则主模一直获取不到资源 */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
        }
#endif

        pNasMsg = Gmm_DetachRequestMsgMake();                                   /* 调用detach request消息制作函数           */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                  /* 发送DETACH REQUEST消息                   */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* 起T3321                                  */
    }
    else
    {                                                                           /* 判断溢出次数大于5                        */
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                           /* 调用状态的公共处理                       */
        g_GmmDetachCtrl.ucT3321OutCnt = 0;                                      /* T3321溢出次数清0                         */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
    }
    return;                                                                     /* 返回                                     */
}

/***********************************************************************
  Module   : Gmm_Tim3330Expired
  Function : 定时器T3330溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇    2003.12.10  新版作成
  2.日    期   : 2008年9月18日
    作    者   : ouyangfei 00132663
    修改内容   : 根据问题单号：AT2D05816，在GMM过程中，来自CM层的SMS请求应该被缓存，等GMM过程结束再发起。
  3.日    期   : 2009年05月23日
    作    者   : L65478
    修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
  4.日    期   : 2009年06月30日
    作    者   : l65478
    修改内容   : 问题单：AT2D12655,增加清除LLC数据类型的处理
  5.日    期   : 2009年09月25日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D14675,RAU/Attach过程中，list搜网失败
  6.日    期   : 2009年10月3日
    作    者   : l00130025
    修改内容   : 根据问题单号：AT2D14889,G网络模式I下,Combined RAU过程中，
                 设置需要CS detach的SYSCFG失败
  7.日    期   : 2010年7月21日
    作    者   : 欧阳飞
    修改内容   : DTS2010071500036,当ATTACH或RAU失败后，未通知LL清除信令数据
                ，导致UE仍然在反复重发数据
  8.日    期   : 2011年7月10日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  9.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 10.日    期   : 2011年7月26日
    作    者   : l00130025
    修改内容   : V7R1 PhaseII阶段调整，删除UserDelay标志，由MMC处理
 11.日    期   : 2011年4月29日
    作    者   : c00173809
    修改内容   : DTS2011042804013,UE在网络模式I下,通过设置W单模搜网到W下相同RAI
                      的小区,先在W下发起电话,然后PDP激活,然后释放CS电话,UE进行的联合RAU
                      是通过EST_REQ而不是通过DATE_REQ发送的.
 12.日    期   : 2011年11月8日
    作    者   : s46746
    修改内容   : V7R1 PhaseII阶段解决关机慢问题
 13.日    期   : 2011年12月24日
    作    者   : w00166186
    修改内容   : DTS2011122104474,指定搜网不停LAU问题统一修改
 14.日    期   : 2012年2月15日
    作    者   : w00167002
    修改内容   : V7R1C50 CSFB&PPAC&ETWS&ISR:调整，若当前存在CSFB业务标志，则只做RAU
 15.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
 16.日    期   : 2013年3月30日
    作    者   : l00167671
    修改内容   : 主动上报AT命令控制下移至C核
 17.日    期   : 2013年7月22日
    作    者   : z00161729
    修改内容   : DTS2013071908566:rau init状态从w cco到g再回退到w，gmm不重新发起rau
 18.日    期   : 2014年05月22日
    作    者   : W00242748
    修改内容   : DTS2014050900899:将GMM的处理状态通知给WAS
 19.日    期   : 2015年4月21日
    作    者   : z00161729
    修改内容   : 24301 R11 CR升级项目修改
************************************************************************/
VOS_VOID Gmm_Tim3330Expired(VOS_VOID)
{
    VOS_UINT8            ucUpdateType = GMM_RA_UPDATING;                         /* 定义临时变量保存更新类型                 */
    NAS_MSG_STRU        *pNasMsg = VOS_NULL_PTR ;                                /* 定义局部变量                             */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    ucCsRestrictionFlg  = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    enCause  = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

    /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        if (GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {
            /* 给GAS发送GRRGMM_GPRS_PROC_IND,类型为PERIODIC RAU,标志为FINISH */;
            NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_PERIOD_RAU, RRMM_GMM_PROC_FLAG_FINISH);

            NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_PERIOD_RAU);
            NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_FINISH);
        }
        else
        {
            /* 给GAS发送GRRGMM_GPRS_PROC_IND,类型为NORMAL RAU,标志为FINISH */;
            NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_NORMAL_RAU, RRMM_GMM_PROC_FLAG_FINISH);

            NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_NORMAL_RAU);
            NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_FINISH);
        }
    }
    /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    if (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
    {
        /* 此标志记录的是系统间重选或者切换时,RAI相同时,当后续有上行数据时需要发送RAU.
           因为调用此函数时RAU已经完成,所以需要清除此标志 */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
    }

    if (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState)
    {
        if (  (VOS_TRUE == ucPsRestrictionFlg)
            &&(VOS_FALSE == ucCsRestrictionFlg)
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3330_EXPIRED);          /* 通知MM进行LU                             */
            Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
            return;
        }
    }

    if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "g_GmmGlobalCtrl.ucState:WARNING: g_GmmGlobalCtrl.ucState is not GMM_ROUTING_AREA_UPDATING_INITIATED");
        return;                                                                 /* 返回                                     */
    }

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_SIGNALLING);
    }

    /* 如果当前有缓存的短信请求，回复失败指示。*/
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }

    if (GMM_MSG_HOLD_FOR_SMS
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }


    g_GmmRauCtrl.ucT3330outCnt ++;                                              /* T3330溢出次数+1                          */
    if (GMM_TIMER_EXPIRED_MAX_CNT > g_GmmRauCtrl.ucT3330outCnt)
    {                                                                           /* 判断次数                                 */
        if (GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {                                                                       /* 当前RAU是否是周期RAU标志                 */
            ucUpdateType = GMM_PERIODC_UPDATING;                                /* RAU是周期RAU                             */

            /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            /* 如果当前接入技术是G，给GAS发送GRRGMM_GPRS_PROC_IND,类型为PERIODIC RAU,标志为START */;
            if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
              || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
            {
                NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_PERIOD_RAU, RRMM_GMM_PROC_FLAG_START);

                NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_PERIOD_RAU);
                NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_START);
            }
            /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

        }
        else
        {
        #if (FEATURE_ON == FEATURE_LTE)

            /* 存在CSFB业务时，进行RAU */
            if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
            }
        #endif

            if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;                         /* 置CS通信中为真                           */
            }

            if ((GMM_RAU_NORMAL != g_GmmGlobalCtrl.ucSpecProc)
             && (GMM_RAU_NORMAL_CS_TRANS != g_GmmGlobalCtrl.ucSpecProc)
             && (GMM_RAU_WITH_IMSI_ATTACH != g_GmmGlobalCtrl.ucSpecProc)
             && (GMM_RAU_COMBINED != g_GmmGlobalCtrl.ucSpecProc))
            {

                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "g_GmmGlobalCtrl:WARNING: g_GmmGlobalCtrl.ucSpecProc is Abnormal");
                return;                                                         /* 跳出                                     */
            }

            ucUpdateType = NAS_GMM_GetRoutingAreaUpdateType();

            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* 清除标志                                 */
            g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */


            /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            /* 如果当前接入技术是G，给GAS发送GRRGMM_GPRS_PROC_IND,类型为NORMAL RAU,标志为START */;
            if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
              || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
            {
                NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_NORMAL_RAU, RRMM_GMM_PROC_FLAG_START);

                NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_NORMAL_RAU);
                NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_START);
            }
            /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

        }

        /* 发起 Rau 时，判断是否有上层业务，如果有，则设置 Follow-On 标志 */
        if ((GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
            ||(GMM_MSG_HOLD_FOR_SM
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM)))
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);
        }

#if (FEATURE_ON == FEATURE_DSDS)

        if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
        {
            NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);
        }
#endif

        pNasMsg = Gmm_RoutingAreaUpdateRequestMsgMake(ucUpdateType);            /* 消息作成                                 */
           /* send DATA Req to delete the saved data */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pNasMsg);             /* 发送RAU REQUEST消息                      */
        Gmm_TimerStart(GMM_TIMER_T3330);                                    /* 启动T3330                                */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_RAU_REQ,
                        (VOS_VOID *)&ucUpdateType,
                        NAS_OM_EVENT_RAU_REQ_LEN);

        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);

        if ((GMM_COMBINED_RALA_UPDATING == ucUpdateType)
         || (GMM_COMBINED_RALAU_WITH_IMSI_ATTACH == ucUpdateType))
        {
            NAS_GMM_SndMmCombinedRauRejected(enCause);

            NAS_GMM_SndMmCombinedRauInitiation();
        }
    }
    else
    {
        if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
        {
            GMM_RauFailureInterSys();
        }
        else
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        }

        g_GmmRauCtrl.ucT3330outCnt = 0;                                         /* T3330溢出次数清0                         */
        g_GmmRauCtrl.ucRetryFlg = GMM_FALSE;                                    /* 设置换小区不进行RAU标志                  */
        Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);        /* 调用RAU attempt counter的公共处理        */
    }
    return;                                                                     /* 返回                                     */
}

/***********************************************************************
  Module   : NAS_GMM_Timer3340Expired
  Function : 定时器T3340溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 欧阳飞    2010.01.03  引入新定时器T3340
 ************************************************************************/
VOS_VOID NAS_GMM_Timer3340Expired(VOS_VOID)
{
    if ((GMM_FALSE == GMM_IsCasGsmMode()) && (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg))
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;                                                                     /* 返回                                     */
}

/*****************************************************************************
 函 数 名  : NAS_GMM_TimerDetachForPowerOffExpired
 功能描述  : GMM收到关机detach定时器超时消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月15日
   作    者   : w00176964
   修改内容   : 新生成函数
************************************************************************/
VOS_VOID NAS_GMM_TimerDetachForPowerOffExpired(VOS_VOID)
{
    /* 关机保护定时器超时，强制关机 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_TRUE != GMM_IsCasGsmMode())
    {
        /* W下如果有信令存在，释放链路 */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        }

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* 清除P_TMSI_SIGNATURE */
    if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    /* 给MMC及缓存的应用模块回复消息 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmGprsDetachComplete();
    }

    Gmm_SndMmcPowerOffCnf();
    Gmm_ComCnfHandle();
    NAS_GMM_FreeTlliForPowerOff();

    /* 清除全局变量 */
    if (GMM_MSG_HOLD_FOR_POWEROFF == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;
    }
    Gmm_HoldBufferFree();
    Gmm_ComVariantInit();
    GMM_BufferMsgDump();
    return;
}


/***********************************************************************
  Module   : Gmm_Tim5sExpired
  Function : 定时器 5s溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.10  新版作成
    2.  日    期   : 2009年5月9日
        作    者   : l00130025
        修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
    3. 日    期   : 2009年05月23日
       作    者   : L65478
       修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
    4. 日    期   : 2010年07月26日
       作    者   : L65478
       修改内容   : 问题单号:DTS2010072200479,开机注册过程中，关机，再开机时失败，因为GMM没有立刻处理关机消息，导致MMC保护定时器超时
    5. 日    期   : 2010年09月13日
       作    者   : L65478
       修改内容   : 问题单号:DTS2010091301310,WCDMA下关机，重新开机后，在GSM模式下无法注册成功
    6. 日    期   : 2010年12月18日
       作    者   : o00132663
       修改内容   : 问题单号:DTS2010121800152,清理关机流程，保证GMM在收到关机请求后8秒内关机
    7. 日    期   : 2011年11月8日
       作    者   : s46746
       修改内容   : V7R1 PhaseII阶段解决关机慢问题
    8. 日    期   : 2012年2月15日
       作    者   : w00166186
       修改内容   : CSFB&PPAC&ETWS&ISR 开发
    9. 日    期   : 2012年2月15日
       作    者   : w00166186
       修改内容   : CSFB&PPAC&ETWS&ISR 开发
   10. 日    期   : 2012年10月12日
       作    者   : w00176964
       修改内容   : DTS2012091400694:G模关机慢
   11. 日    期   : 2015年2月6日
       作    者   : h00313353
       修改内容   : USIMM卡接口调整
************************************************************************/
VOS_VOID Gmm_Tim5sExpired(VOS_VOID)
{
    NAS_MSG_STRU           *pNasMsg;                                            /* 定义指针 */
    VOS_UINT8               ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    if (g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt < GMM_MAX_DETACH_CNT_WHEN_POWER_OFF)
    {
        ++ g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt;

        Gmm_TimerStart(GMM_TIMER_1S);

        /* 如果接入阻塞或者GPRS不支持，不再尝试 */
        if (  (RRC_EST_OTHER_ACCESS_BARRED == g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult)
           || (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
           || (VOS_TRUE == ucPsRestrictionFlg))
        {
            g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt = GMM_MAX_DETACH_CNT_WHEN_POWER_OFF;
            return;
        }

        /* GMM挂起态，直接返回 */
        if ( (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
          || (GMM_SUSPENDED_GPRS_SUSPENSION  == g_GmmGlobalCtrl.ucState))
        {
            return;
        }

        /* RRC 连接建立过程中。。。 */
        if (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
        {
            return;
        }

        /* W下RRC连接还未建立 */
        if (GMM_TRUE != g_GmmGlobalCtrl.ucSigConFlg)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                       /* DETACH REQUEST消息作成                   */

            Gmm_SndRrmmEstReq (RRC_EST_CAUSE_DETACH,
                               GMM_RRC_IDNNS_UNKNOWN,
                               pNasMsg);                                /* 发送RRMM_EST_REQ                         */

            Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ESTING);      /* 通知MMC PS域信令连接正在建立             */

            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NORMAL_SERVICE);

            if ((GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
             || (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* 当前流程是combined sim remove或power off */
                g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;   /* 置标志位能作detach                       */
            }

            /* G下关机参考标杆做法:GMM启动5S定时器,这里detach发出后只需要尝试5次 */
            Gmm_TimerStart(GMM_TIMER_DETACH_FOR_POWER_OFF);
        }

        return;
    }

    /* 关机保护定时器超时，强制关机 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_TRUE != GMM_IsCasGsmMode())
    {
        /* W下如果有信令存在，释放链路 */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        }

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* 清除P_TMSI_SIGNATURE */
    if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    /* 给MMC及缓存的应用模块回复消息 */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmGprsDetachComplete();
    }

    Gmm_SndMmcPowerOffCnf();
    Gmm_ComCnfHandle();
    NAS_GMM_FreeTlliForPowerOff();

    /* 清除全局变量 */
    if (GMM_MSG_HOLD_FOR_POWEROFF == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;
    }
    Gmm_HoldBufferFree();

    GMM_BufferMsgDump();

    Gmm_ComVariantInit();

    return;
}

/***********************************************************************
  Module   : Gmm_TimProtectExpired
  Function : 保护定时器溢出处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 张志勇  2003.12.10  新版作成
     2.日    期  : 2011年03月30日
       作    者  : 欧阳飞
       修改内容  : DTS2011032802556,网络异常，连续发送鉴权请求消息，导致鉴权失败，卡无效。
    3.日    期  :2014年01月09日
      作    者  :l65478
      修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
 ************************************************************************/
VOS_VOID Gmm_TimProtectExpired(VOS_VOID)
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimProtectExpired:WARNING: Protected Timer is expired");

    /* 等待USIM卡鉴权计算结果处理 */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
       == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;


        g_GmmAuthenCtrl.ucAuthenAttmptCnt++;

        if (GMM_AUTHEN_ATTEMPT_MAX_CNT == g_GmmAuthenCtrl.ucAuthenAttmptCnt)
        {
            Gmm_AuCntFail();            /* 鉴权失败处理，结束返回 */
        }
    }
}

/***********************************************************************
  Module   : Gmm_RcvTimerExpired
  Function : 定时器溢出处理
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2003.12.10  新版作成
     2. 日    期   : 2006年11月8日
        作    者   : s46746
        修改内容   : 问题单号:A32D06867
     3. 日    期   : 2009年5月9日
        作    者   : l00130025
        修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
     4. 日    期   : 2011年7月11日
        作    者   : sunxibo 46746
        修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
     5. 日    期   : 2011年10月11日
        作    者   : l00171473
        修改内容   : V7R1 phase II, TC环回调整，延迟向MMC回复SUSPEND_RSP定时器超时处理
     6.日    期   : 2012年4月17日
       作    者   : z00161729
       修改内容  : DTS2012041402264：L小区下发起CS语音业务，通过重定向CS Fallback到W小区。激活PDP后释放CS语音，未上系统消息，UE不会发起联合RAU
     6. 日    期   : 2012年5月15日
        作    者   : l00130025
        修改内容   : DTS2012041002516: L下默认承载存在数据连接时设置W only失败
     7.日    期   : 2012年8月13日
       作    者   : z00161729
       修改内容   : DCM定制需求和遗留问题修改
     8.日    期   : 2012年10月12日
       作    者   : w00176964
       修改内容   : DTS2012091400694:G模关机慢
     9.日    期   : 2012年10月30日
       作    者   : s00217060
       修改内容   : DTS2012050301830:调整,收到MM的CsConnectInd时,如果RRC连接存在,立即发起RAU；
                    否则,收到接入层上报的系统消息后再做联合RAU.
    10.日    期   : 2013年6月6日
       作    者   : w00167002
       修改内容   : V9R1_SVLTE项目修改
    11.日    期   : 2013年06月28日
       作    者   : l00167671
       修改内容   : DCM LOGGER项目定时器事件上报
     2.日    期   : 2014年12月25日
       作    者   : w00167002
       修改内容   : DTS2014122201960:在L下SRVCC HO到G再HO到W,RABM触发重建，导致立即
                    触发RAU，后续收到系统消息又再次发起RAU,导致网络REL了链路，导致
                    掉话。修改为在HO后，启动保护定时器等系统消息。
    13.日    期   : 2015年9月26日
       作    者   : c00318887
       修改内容   : 扩展GMM定时器到64个
 ************************************************************************/
VOS_VOID Gmm_RcvTimerExpired(
    VOS_UINT8                           ucTimerId
)
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;
    
    NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:INFO: Timer Expired: ", ucTimerId);

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
 

    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */
    NAS_TIMER_EventReport(ucTimerId, WUEPS_PID_GMM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);
    /* added  by l00167671 for v9r1 dcm logger可维可测项目, 2013-06-27, begin */

    /*lint -e701*/
    if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex )))
    /*lint +e701*/
    {
        /* 指定Timer已经启动  */
        Gmm_TimerStop(ucTimerId);
    }
    else
    {
        /* 该定时器当前未运行 */
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:WARNING: The Timer hasn't been started: ", ucTimerId);
        return;
    }

    switch (ucTimerId)
    {
    case  GMM_TIMER_T3302:
        Gmm_Tim3302Expired();
        break;
    case  GMM_TIMER_T3310:
        Gmm_Tim3310Expired();
        break;
    case  GMM_TIMER_T3311:
        Gmm_Tim3311Expired();
        break;
    case  GMM_TIMER_T3312:
        Gmm_Tim3312Expired();
        break;
    case  GMM_TIMER_T3316:
        Gmm_Tim3316Expired();
        break;
    case  GMM_TIMER_T3317:
        Gmm_Tim3317Expired();
        break;
    case  GMM_TIMER_T3318:
        Gmm_Tim3318Expired();
        break;
    case  GMM_TIMER_T3319:
        Gmm_Tim3319Expired();
        break;
    case  GMM_TIMER_T3320:
        Gmm_Tim3320Expired();
        break;
    case  GMM_TIMER_T3321:
        Gmm_Tim3321Expired();
        break;
    case  GMM_TIMER_T3330:
        Gmm_Tim3330Expired();
        break;
    case  GMM_TIMER_1S:
        Gmm_Tim5sExpired();
        break;
    case  GMM_TIMER_PROTECT:
        Gmm_TimProtectExpired();
        break;
    case  GMM_TIMER_PROTECT_FOR_SIGNALING:
        Gmm_TimProtectForSignalingExpired();
        break;
    case  GMM_TIMER_SUSPENDED:
        GMM_LOG_WARN("GMM_TIMER_SUSPENDED expired.");
        GMM_TimSuspendedExpired();
        break;
    case  GMM_TIMER_T3314:
        GMM_TimReadyExpired();
        break;
    case  GMM_TIMER_RAU_RSP:
        GMM_TimRauRspExpired();
        break;
    case  GMM_TIMER_PROTECT_FOR_RR_REL:
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:WARNING: PROTECT_FOR_RR_REL Expired");
        GMM_TimProtectForRrRel();
        break;
    case  GMM_TIMER_PROTECT_OLD_TLLI:
        GMM_TimProtectForOldTlli();
        break;
    case  GMM_TIMER_T3340:
        NAS_GMM_Timer3340Expired();
        break;
    case  GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF:
        NAS_GMM_TimerWaitInterRatCnfExpired();
        break;

    case  GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF:
        NAS_GMM_TimerWaitReselSecuCnfExpired();
        break;

    case  GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF:
#if (FEATURE_ON == FEATURE_LTE)
        NAS_GMM_TimerWaitHoSecuCnfExpired();
#endif
        break;

    case GMM_TIMER_WAIT_CONNECT_REL:
        NAS_GMM_TimerWaitConnectRelExpired();
        break;

    case GMM_TIMER_TC_DELAY_SUSPEND_RSP:
        NAS_GMM_TimerTcDelaySuspendRspExpired();
        break;

    case GMM_TIMER_T3323:
#if (FEATURE_ON == FEATURE_LTE)
        NAS_GMM_Timer3323Expired();
#endif
        break;




#if (FEATURE_ON == FEATURE_LTE)
    case GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU:
        NAS_GMM_TimerDelayRadioCapaTrigedRauExpired();
        break;
#endif


    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    case GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO:
        NAS_GMM_TimerWaitAsMsRadioCapaInfoExpired();
        break;
#endif
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

    /* GMM 关机detach定时器超时 */
    case GMM_TIMER_DETACH_FOR_POWER_OFF:
        NAS_GMM_TimerDetachForPowerOffExpired();
        break;


    /* GMM的PS域detach流程保护定时器超时 */
    case GMM_TIMER_PROTECT_PS_DETACH:
        NAS_GMM_TimerProtectPsDetachExpired();
        break;



    /* GMM的GMM_TIMER_HO_WAIT_SYSINFO保护定时器超时 */
    case GMM_TIMER_HO_WAIT_SYSINFO:
        NAS_GMM_TimerHoWaitSysinfoExpired();
        break;

#if (FEATURE_ON == FEATURE_LTE)
    case GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU:
        NAS_GMM_TimerDelayVoiceDomainTrigRauExpired();
        break;
#endif


    case GMM_TIMER_DELAY_PS_SMS_CONN_REL:
        NAS_GMM_RcvTiDelayPsSmsConnRelExpired();
        break;

    default:
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:WARNING: Unhandled TimerId: ", ucTimerId);
        break;
    }
}


/***********************************************************************
  Module   : Gmm_TimerPauseForTc
  Function : GMM使用的定时器暂停(TC过程中)
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 张志勇  2004.06.18  新规作成(TC对应)
 ************************************************************************/
VOS_VOID Gmm_TimerPauseForTc(
                         VOS_UINT8                   ucTimerId                      /* Timer ID                                 */
                         )
{
    VOS_UINT8    i;
    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask             = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerSusTcMask           = VOS_NULL_PTR;    
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendTcMask(ucTimerId, &pulTimerSusTcMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (GMM_TIMER_ALL == ucTimerId)
    {
        for (i = 0; i < GMM_TIMER_NUM; i ++)
        {                                                                       /* 循环查找所有TIMER                        */
            NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendTcMask(i, &pulTimerSusTcMask, &ucTimerBitIndex);

            if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
            {                                                                   /* 该定时器已经启动                         */

                if (0 == ((*pulTimerSusMask) & (0x00000001 << ucTimerBitIndex)))
                {                                                               /* 该定时器没有被挂起                       */
                    if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                           Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                    {                                                           /* 停止失败：已经停止或Timer不存在          */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPauseForTc:WARNING: Stop all timer unsuccessfully");
                        return;                                                 /* 返回                                     */
                    }

                    (*pulTimerSusTcMask) |= (0x00000001 << ucTimerBitIndex);        /* 置Timer的挂起标志(TC)                    */
                    
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerPauseForTc:INFO: StopTimer: ",i);
                }
            }
        }
    }
    else if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex)))
    {                                                                           /* 该timer已经启动                          */
        if ((0 == ((*pulTimerSusTcMask) & (0x00000001 << ucTimerBitIndex)))
            &&(0 == ((*pulTimerSusMask) & (0x00000001 << ucTimerBitIndex))))
        {
            if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                 Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
            {                                                                   /* 暂停失败                                 */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPauseForTc:WARNING: Stop timer unsuccessfully");
                return;                                                         /* 返回                                     */
            }
            (*pulTimerSusTcMask) |= (0x00000001 << ucTimerBitIndex);        /* 设置Timer的挂起标志                      */
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerPauseForTc:INFO: StopTimer: ",ucTimerId);
        }
    }
    else
    {
    }
    /*lint +e701*/
    return;
}

/***********************************************************************
  Module   : Gmm_TimerResumeForTc
  Function : GMM使用的暂停后的定时器的恢复(TC过程中)
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1.  张志勇  2004.06.18  新规作成(TC对应)
 ************************************************************************/
VOS_VOID Gmm_TimerResumeForTc(
                          VOS_UINT8                   ucTimerId                     /* Timer ID                                 */
                          )
{
    VOS_UINT8    i;
    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask             = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerSusTcMask           = VOS_NULL_PTR;    
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendTcMask(ucTimerId, &pulTimerSusTcMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (GMM_TIMER_ALL == ucTimerId)
    {
        for (i = 0; i < GMM_TIMER_NUM; i ++)
        {                                                                       /* 循环查找所有TIMER                        */
            NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendTcMask(i, &pulTimerSusTcMask, &ucTimerBitIndex);

            if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
            {                                                                   /* 该定时器已经启动                         */
                if (0 != ((*pulTimerSusTcMask) & (0x00000001 << ucTimerBitIndex)))
                {                                                               /* 该定时器已经挂起                         */
                    if (VOS_OK != Mm_StartRelTimer(
                                           &g_GmmTimerMng.aTimerInf[i].hTimer,     /* 存放TIMER ID的地址                       */
                                           WUEPS_PID_GMM,
                                           g_GmmTimerMng.aTimerInf[i].ulTimerVal,         /* 时长                                     */
                                           (VOS_UINT32)i,            /* 消息队列的ID                             */
                                           g_GmmTimerMng.aTimerInf[i].ulParam,               /* 消息地址                                 */
                                           g_GmmTimerMng.aTimerInf[i].ucMode          /* 消息优先级                               */
                                           ))
                    {                                                           /* 恢复失败                                 */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResumeForTc:WARNING: Start all timer unsuccessfully");
                        return;                                                 /* 返回                                     */
                    }
                    
                    (*pulTimerSusTcMask)
                        &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);      /* 清Timer的挂起标志                        */
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerResumeForTc:INFO: StartTimer: ",i);
                }
            }
        }
    }
    else if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex)))
    {                                                                           /* 该timer已经启动                          */
        if (0 != ((*pulTimerSusTcMask) & (0x00000001 << ucTimerBitIndex)))
        {
            if( VOS_OK != Mm_StartRelTimer(
                                &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer,     /* 存放TIMER ID的地址                       */
                                WUEPS_PID_GMM,
                                g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal,         /* 时长                                     */
                                (VOS_UINT32)ucTimerId,            /* 消息队列的ID                             */
                                g_GmmTimerMng.aTimerInf[ucTimerId].ulParam,               /* 消息地址                                 */
                                g_GmmTimerMng.aTimerInf[ucTimerId].ucMode          /* 消息优先级                               */
                                ))
            {                                                                   /* 恢复失败                                 */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResumeForTc:WARNING: Start timer unsuccessfully");
                return;                                                         /* 返回                                     */
            }
            (*pulTimerSusTcMask)
                &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);      /* 设置Timer的挂起标志                      */
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerResumeForTc:INFO: StartTimer: ",ucTimerId);
        }
    }
    else
    {
    }
    /*lint +e701*/
    return;
}

/***********************************************************************
Module   : Gmm_TimProtectForSignalingExpired
Function : GMM_TIMER_PROTECT_FOR_SIGNALING 溢出处理
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
1. 张志勇  2005.01.10  新版作成
2. 日    期   : 2007年11月1日
   作    者   : l65478
   修改内容   : A32D13307, 增加SR过程超时后的处理
 3.日    期   : 2012年3月17日
   作    者   : w00176964
   修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加拨号被拒定制
 4.日    期   : 2012年08月24日
   作    者   : m00217266
   修改内容   : 修改GMM_SndSmServiceRej接口，添加原因值

************************************************************************/
VOS_VOID Gmm_TimProtectForSignalingExpired(VOS_VOID)
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimProtectForSignalingExpired:WARNING: Protected timer for signalling is expired");
    GMM_SndRrmmRelReqGsm();

    /* 获取拨号被拒定制是否使能 */
    if (VOS_TRUE == NAS_MML_GetDailRejectCfg())
    {
        GMM_SndSmServiceRej(GMM_SM_CAUSE_TIMER_SIGNALING_PROTECT_EXPIRED);

        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
    }
}

/***********************************************************************
Module   : GMM_TimProtectForRrRel
Function : GMM_TIMER_PROTECT_FOR_RR_REL 溢出处理
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
1. s46746  2006.03.27  Create
2. 日    期   : 2007年01月25日
   作    者   : s46746
   修改内容   : 创建，根据问题单号：A32D07433
3. 日    期   : 2007年03月20日
   作    者   : x51137
   修改内容   : A32D09192
4.日    期   : 2011年07月13日
  作    者   : w00166186
  修改内容   : V7R1 PHASE II ATTACH/DETACH调整
5. 日    期   : 2012年1月12日
   作    者   : w00166186
   修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                 PLMN状态，服务域被设置为不支持GMM需要将服务域不支持信息通知给MMC.
6.日    期   : 2013年8月7日
  作    者   : w00167002
  修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
7.日    期   : 2015年3月27日
  作    者   : wx270776
  修改内容   : DTS2015022804322: 保护定时器超时后W下存在信令链接时，通知PS域的链路释放
************************************************************************/
VOS_VOID GMM_TimProtectForRrRel()
{
    RRMM_REL_IND_STRU *prrmm_rel_ind;

    if ( GMM_ABORT_CURRENT_SERVICE == g_GmmGlobalCtrl.ucSpecProc )
    {
        prrmm_rel_ind = (RRMM_REL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM, sizeof(RRMM_REL_IND_STRU) );
        if ( VOS_NULL_PTR == prrmm_rel_ind )
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        }
        else
        {
            prrmm_rel_ind->MsgHeader.ulSenderPid = WUEPS_PID_WRR;
            prrmm_rel_ind->MsgHeader.ulMsgName = RRMM_REL_IND;
            prrmm_rel_ind->ulCnDomainId = RRC_NAS_PS_DOMAIN;
            prrmm_rel_ind->ulRelCause = RRC_REL_CAUSE_NAS_ABORT;
            prrmm_rel_ind->ulRrcConnStatus = RRC_RRC_CONN_STATUS_ABSENT;

            Gmm_RcvRrmmRelInd(prrmm_rel_ind);

            PS_FREE_MSG(WUEPS_PID_GMM, prrmm_rel_ind);

        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;

        return;
    }

    if (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_TimProtectForRrRel:WARNING: Gmm State is unexpected.");
        return;
    }

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */

    if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);          /* 设置PS域禁止注册标志                     */
    }

    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* 清除P_TMSI_SIGNATURE                     */

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }
    else
    {

    }


    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

	/* W下存在信令链接时，通知PS域的链路释放 */
	if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
		&& (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg) )
	{
		Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
	}
}

/***********************************************************************
Module   : GMM_TimSuspendedExpired
Function : GMM_TIMER_SUSPENDED 溢出处理
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
 1. s46746  2006.03.27  Create
 2.日    期   : 2011年7月12日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，全局变量调整，需要修改响应的超时处理
************************************************************************/
VOS_VOID GMM_TimSuspendedExpired()
{
    switch(g_GmmGlobalCtrl.ucState)
    {
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM_TimSuspendedExpired:MMC is still suspended.");
            Gmm_TimerStart(GMM_TIMER_SUSPENDED);
            break;

        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            GMM_LOG_WARN("GMM_TimSuspendedExpired:MMC have not get sys info.");
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
            }
            else
            {
#if 0
                GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                               GMM_RABM_IMMEDIATELY_RAU);
#endif

                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
            }
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            GMM_ResumeTimer(GMM_TIMER_RESUME);
            GMM_ResumeFailure();
            break;
        default:
            GMM_LOG_WARN("GMM_TimSuspendedExpired:Receive GMM_TIMER_SUSPENDED in abnormal state.");
            break;
    }
    return;
}

/***********************************************************************
Module   : GMM_TimProtectForOldTlli
Function : GMM_TIMER_PROTECT_FOR_OLD_TLLI 溢出处理
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
1. s46746  2006.11.08  Create for A32D06867
       10.  日    期   : 2006年11月20日
            作    者   : s46746
            修改内容   : 创建，根据问题单号：A32D07433
************************************************************************/
VOS_VOID GMM_TimProtectForOldTlli()
{
    Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
    GMM_FreeOldTlli();
    gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_TimerWaitInterRatCnfExpired
 功能描述  : 定时器GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF超时处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月27日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
  3.日    期   : 2014年7月18日
    作    者   : b00269685
    修改内容   : DSDS IV修改

*****************************************************************************/
VOS_VOID NAS_GMM_TimerWaitInterRatCnfExpired( VOS_VOID )
{
    NAS_MSG_STRU                            *pstSendNasMsg = VOS_NULL_PTR;

    g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg = VOS_TRUE;

    if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg)
    {
        if (VOS_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            /* ATTACH过程是由SM触发的,通知SM GMM注册成功,并清ucSmCnfFlg标志 */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
            g_GmmAttachCtrl.ucSmCnfFlg = VOS_FALSE;
        }

        /* 回复网络Attach Complete 消息 */
        pstSendNasMsg = Gmm_AttachCompleteMsgMake();

        if (VOS_NULL_PTR == pstSendNasMsg)
        {
            NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Make Attach Complete Msg Fail!");
            return;
        }
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pstSendNasMsg);

    }
    else if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
    {
        /* 不需要等待RABM的回复消息，或者已经收到RABM的回复消息，进行RAU流程结束的相应处理 */
        if (   (VOS_FALSE == gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg)
            || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg))
        {
            NAS_GMM_RauCompleteHandling();
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Not Expected Msg Received.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_TimerWaitReselSecuCnfExpired
 功能描述  : GMM获取LMM安全参数定时器超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月14日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数
  2.日    期   : 2011年12月2日
    作    者   : s46746
    修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
  3.日    期   : 2012年3月17日
    作    者   : w00176964
    修改内容   : DTS2012031308021:[GCF测试]L2U重选,携带RAU request的上行消息
                 中的RAU参数以及PTMSI类型错误。

*****************************************************************************/
VOS_VOID  NAS_GMM_TimerWaitReselSecuCnfExpired( VOS_VOID )
{
    if (NAS_GMM_SPEC_PROC_RAU == NAS_GMM_GetSpecProcNeedSecInfo())
    {
        Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
    }
    else
    {
        Gmm_SndAttachReq();
    }

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    g_GmmInterRatCellReselect = 0;

    /* 需要获取安全上下文时,挂起前的接入技术延迟更新 */
    gstGmmSuspendCtrl.ucPreRat = NAS_MML_GetCurrNetRatType();

    NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_BUTT);
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_TimerWaitHoSecuCnfExpired
 功能描述  : GMM获取LMM安全参数定时器超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月20日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2011年12月2日
    作    者   : s46746
    修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
*****************************************************************************/
VOS_VOID  NAS_GMM_TimerWaitHoSecuCnfExpired( VOS_VOID )
{
    /* 如果此时在GMM的挂起状态，而且挂起发起方为LTE，则向MMC回复挂起回复 */
    if ( (NAS_MML_NET_RAT_TYPE_LTE     == NAS_MML_GetCurrNetRatType())
      && (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();
    }

}

/*****************************************************************************
 函 数 名  : NAS_GMM_Timer3323Expired
 功能描述  : T3323定时器超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月7日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_Timer3323Expired(VOS_VOID)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 3GPP 24.008 4.7.2.2章节描述：
       After expiry of timer T3323 the MS shall deactivate ISR by setting
       its TIN to "GUTI". */
    if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == pstRplmnCfgInfo->enTinType)
    {
        NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }
    return;
}

#endif

/* 收到MM的CsConnectInd时,如果RRC连接存在,立即发起RAU；
   否则,收到接入层上报的系统消息后再做联合RAU */

/*****************************************************************************
 函 数 名  : NAS_GMM_TimerWaitConnectRelExpired
 功能描述  : 等待主动连接释放的保护定时器超时处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
    作    者  : s46746
    修改内容  : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_TimerWaitConnectRelExpired()
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_TimerWaitConnectRelExpired:WARNING: Wait connect rel expired.");

    if ((GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        return;
    }

    /* 如果当前驻留WCDMA，则向MMC指示连接不存在，否则向MMC指示TBF释放 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        /* 设置PS信令连接不存在 */
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        /* 向MMC发送连接不存在消息 */
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

        NAS_GMM_ClearGmmLinkCtrlStru();
    }
    else
    {
        /* 设置TBF连接不存在 */
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

        /* 向MMC发送连接不存在消息 */
        Gmm_SndMmcTBFRelInd();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_TimerTcDelaySuspendRspExpired
 功能描述  : 延迟向MMC回复SUSPEND_RSP的定时器超时的处理。
             用于TC状态的GCF测试中，以达到延迟向接入层回复SUSPEND_RSP。
             GMM延迟向MMC回复SUSPEND_RSP, 于是相应地向接入层回复SUSPEND_RSP也延迟了。
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年9月14日
   作    者   : L00171473
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_TimerTcDelaySuspendRspExpired(VOS_VOID)
{
#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
    if (1 == g_ulGmmDelaySuspendRsp)
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();

        return;
    }
#endif

    /* 由于此处状态已迁移，故使用切换之前GMM状态进行判断。 */
    if (GMM_TC_ACTIVE != gstGmmSuspendCtrl.ucPreState)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_TimerTcDelaySuspendRspExpired:WARNING: Expired NOT GMM_TC_ACTIVE STATE");
        return;
    }

    Gmm_TimerStart(GMM_TIMER_SUSPENDED);

    GMM_SndMmcSuspendRsp();
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_GMM_CheckRadioAccessCapaTrigedRAU
 功能描述  : 接收到Gas发来的RadioAccessCapability与上次不同时，判断前后的RAT变化是否需要触发RAU;
              目前只在模式增减L模时，做对应的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要触发RAU,VOS_FALSE:不需要触发RAUs
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月15日
    作    者   : l00130025
    修改内容   : DTS2012041002516: L下默认承载存在数据连接时设置W only失败,
                  GU下接入能力变化时，需要触发一次RAU过程
*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckRatTrigedRAU(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstOldRatList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstNewRatList
)
{
    VOS_UINT32                          ulLteExistInOldRatList;
    VOS_UINT32                          ulLteExistInNewRatList;
    VOS_UINT32                          ulWExistInNewRatLList;
    VOS_UINT32                          ulGExistInNewRatLList;

    /* 当前处于GU模，模式变化涉及到增加或减少L模时，触发RAU,其他情况下，不处理 */
    ulLteExistInOldRatList = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                        pstOldRatList);
    ulLteExistInNewRatList = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                        pstNewRatList);
    ulWExistInNewRatLList  = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                        pstNewRatList);
    ulGExistInNewRatLList  = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_GSM,
                                                        pstNewRatList);

    if (ulLteExistInOldRatList != ulLteExistInNewRatList)
    {
        if ((VOS_TRUE == ulWExistInNewRatLList)
         || (VOS_TRUE == ulGExistInNewRatLList))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_TimerDelayRadioCapaTrigedRauExpired
 功能描述  : SYSCFG设置后,检查RadioCapa改变是否需要触发RAU,需要时，触发RAU
             目前 RAU采用best Effort策略，尽量发起，不能发起时，放弃
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年5月15日
   作    者   : l00130025
   修改内容   : DTS2012041002516: L下默认承载存在数据连接时设置W only失败
 2.日    期   : 2012年8月15日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 3.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，lte能力改变非CS业务过程中立即发起RAU
*****************************************************************************/
VOS_VOID NAS_GMM_TimerDelayRadioCapaTrigedRauExpired(VOS_VOID)
{
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
    /* rau或attach中ms radio capa IE中携带的LTE能力与接入层最新上报的LTE能力不一致，需要触发rau */
    if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs == g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
    {
        return;
    }

    NAS_GMM_HandleMsRadioCapLteSupportChanged();

    return;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
/*****************************************************************************
 函 数 名  : NAS_GMM_TimerWaitAsMsRadioCapaInfoExpired
 功能描述  : GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO定时器超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年8月15日
   作    者   : z00161729
   修改内容   : 新增函数
 2.日    期   : 2013年9月2日
    作    者  : z00161729
    修改内容  : DTS2013082702039:syscfg不支持l或l disable时，gmm rau和attach不需携带ue network capability
 3.日    期   : 2014年02月25日
   作    者   : z00161729
   修改内容   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1失败disable lte时rau需要从L获取安全上下文

*****************************************************************************/
VOS_VOID NAS_GMM_TimerWaitAsMsRadioCapaInfoExpired(VOS_VOID)
{
    VOS_UINT32                          ulGetLmmSecInfoFlg;

    VOS_UINT32                          ucIsSupportLteCapaFlg;

    VOS_UINT8                           ucLDisabledUseLInfoFlag;

    ucLDisabledUseLInfoFlag = NAS_MML_GetLteDisabledRauUseLteInfoFlag();

    ucIsSupportLteCapaFlg  = NAS_MML_IsSupportLteCapability();

    ulGetLmmSecInfoFlg = NAS_GMM_GetLmmSecInfoFlg();

    /* l disabled attach 不从l获取安全上下文， l disabled rau nv控制是否需要从l获取安全上下文*/
    if ((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
     && (VOS_FALSE == gstGmmSuspendCtrl.ucGetLteSecContext)
     && (VOS_FALSE == ulGetLmmSecInfoFlg)
     && ((VOS_TRUE == ucIsSupportLteCapaFlg)
      || ((VOS_TRUE == ucLDisabledUseLInfoFlag)
       && (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState))))
    {
        NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_RAU);
        NAS_GMM_SetLmmSecInfoFlg(VOS_TRUE);

        if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_RAU);
        }

        if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_ATTACH);
        }

        /* 给L模发送GMM_LMM_RESEL_SECU_INFO_REQ */
        NAS_GMM_SndLmmReselSecuInfoReq();

        /* 启动定时器 */
        Gmm_TimerStart(GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF);

        return;
    }

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_SndAttachReq();
    }
    return;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedStartT3323
 功能描述  : 是否需要启动T3323定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年10月22日
   作    者   : z00161729
   修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedStartT3323(VOS_VOID)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT8                           ucIsNeedStartT3323;

    enTinType          = NAS_MML_GetTinType();
    ucIsNeedStartT3323 = VOS_FALSE;

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_REGISTERED_UPDATE_NEEDED:

             /* GMM处于GMM_REGISTERED_NO_CELL_AVAILABLE或GMM_REGISTERED_LIMITED_SERVICE且ISR激活，
                需要启动T3323定时器,GMM处于注册被bar状态且ISR激活，需要启动T3323定时器 */
            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
            {
                ucIsNeedStartT3323 = VOS_TRUE;
            }
            break;

        case GMM_REGISTERED_PLMN_SEARCH:

            /* GMM丢网时处于GMM_REGISTERED_PLMN_SEARCH且ISR激活，需要启动T3323定时器，
               正常搜网如背景搜的快速指定搜状态ISR激活无需启动T3323  */
            if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
             && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
            {
                ucIsNeedStartT3323 = VOS_TRUE;
            }
            break;

        default:
            break;
    }

    return ucIsNeedStartT3323;
}

#endif



/*****************************************************************************
 函 数 名  : NAS_GMM_TimerHoWaitSysinfoExpired
 功能描述  : GMM_TIMER_HO_WAIT_SYSINFO保护定时器超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : s00217060
   修改内容   : 新增函数
*****************************************************************************/
VOS_VOID NAS_GMM_TimerHoWaitSysinfoExpired(VOS_VOID)
{
    /* 切换流程一般是业务时才会有，PS域不报注册成功假流程，靠CS上报来保证驻留信息和信号强度更新，否则IMSA可能会提前去流程IMSA
       场景:L2G的SRVCC,CMCC要求电话结束之后，才能去注册IMSA，
       此时如果报假流程，MMC就会通知MMA注册状态和服务状态，MMA就会通知IMSA服务状态变化 */
    /* 当前不在GMM_SUSPENDED_WAIT_FOR_SYSINFO状态，则不需要处理  */
    if ( GMM_SUSPENDED_WAIT_FOR_SYSINFO != Gmm_GetState() )
    {
        return ;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return;
    }

    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_TimerDelayVoiceDomainTrigRauExpired
 功能描述  : GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU保护定时器超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月12日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改
*****************************************************************************/
VOS_VOID NAS_GMM_TimerDelayVoiceDomainTrigRauExpired(VOS_VOID)
{
    /* 相关协议章节:
    3GPP 24008:
    4.7.5.1 Normal and periodic routing area updating procedure

    The normal routing area updating procedure is initiated:
    ......
    -    when the UE's usage setting or the voice domain preference for E-UTRAN change in the MS;
    ......
    */

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    VOS_INT8                  cVersion;

    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    pstConnStatus   = NAS_MML_GetConnStatus();

    if (cVersion < PS_PTL_VER_R9)
    {
        return;
    }

    /* voice domain和上次发起注册时的相同，不需要再做RAU */
    if (g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq == NAS_MML_GetVoiceDomainPreference())
    {
        return;
    }

    /* 如果存在CS业务则直接返回 */
    if (VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return;
    }

    /* 如果正在发起CS业务则启动定时器，业务发起失败依靠定时器触发RAU，
       业务发起成功定时器超时时会直接返回 */
    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);

        return;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
    }

    return;
}
#endif


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvTiDelayPsSmsConnRelExpired
 功能描述  : GMM_TIMER_DELAY_PS_SMS_CONN_REL定时器超时的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月23日
    作    者   : c00318887
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_RcvTiDelayPsSmsConnRelExpired(VOS_VOID)
{
    if (VOS_TRUE == NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer())
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;    
}

/***********************************************************************
  Module   : NAS_GMM_GetTimerRunMask
  Function : GMM使用的定时器启动
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 
             VOS_UINT32    **pulTimerRunMask   该定时器RunMask 标示位的成员: g_GmmTimerMng.ulTimerRunMask 或 g_GmmTimerMng.ulTimerRunMaskEx
             VOS_UINT8      *pucTimerBitIndex  该定时器在标示位的索引
  NOTE     : 无
  Return   : 无
  History  :
  1.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 新建函数
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerRunMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerRunMask,  
    VOS_UINT8                          *pucTimerBitIndex
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerRunMask)              = &g_GmmTimerMng.ulTimerRunMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerRunMask)              = &g_GmmTimerMng.ulTimerRunMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}

/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendMask
  Function : GMM使用的定时器启动
  Input    : VOS_UINT8           ucTimerId     定时器ID
  Output   : 
             VOS_UINT32    **pulTimerSusMask   该定时器SusMask 标示位的成员: g_GmmTimerMng.ulTimerSusMask 或 g_GmmTimerMng.ulTimerSusMaskEx
             VOS_UINT8      *pucTimerIndex     该定时器在标示位的索引
  NOTE     : 无
  Return   : 无
  History  :
  1.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 新建函数
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerSuspendMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerSusMask,  
    VOS_UINT8                          *pucTimerBitIndex 
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerSusMask)              = &g_GmmTimerMng.ulTimerSusMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerSusMask)              = &g_GmmTimerMng.ulTimerSusMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}


/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendTcMask
  Function : GMM使用的定时器启动
  Input    : VOS_UINT8       ucTimerId     定时器ID
  Output   : 
             VOS_UINT32    **pulTimerSusTcMask   该定时器ulTimerSusTcMask 标示位的成员: g_GmmTimerMng.ulTimerSusTcMask 或 g_GmmTimerMng.ulTimerSusTcMaskEx
             VOS_UINT8      *pucTimerBitIndex    该定时器在标示位的索引
  NOTE     : 无
  Return   : 无
  History  :
  1.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 新建函数
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerSuspendTcMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerSusTcMask,  
    VOS_UINT8                          *pucTimerBitIndex 
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerSusTcMask)            = &g_GmmTimerMng.ulTimerSusTcMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerSusTcMask)            = &g_GmmTimerMng.ulTimerSusTcMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}

/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendTcMask
  Function : GMM使用的定时器启动
  Input    : VOS_UINT8       ucTimerId     定时器ID
  Output   : 
             VOS_UINT32    **pulTimerRunMask   该定时器ulTimerValMask 标示位的成员: g_GmmTimerMng.ulTimerValMask 或 g_GmmTimerMng.ulTimerValMaskEx
             VOS_UINT8      *pucTimerIndex     该定时器在标示位的索引
  NOTE     : 无
  Return   : 无
  History  :
  1.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 新建函数
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerValMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerValMask,  
    VOS_UINT8                          *pucTimerBitIndex
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerValMask)              = &g_GmmTimerMng.ulTimerValMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerValMask)              = &g_GmmTimerMng.ulTimerValMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}
/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendCtrlRunMask
  Function : GMM使用的定时器启动
  Input    : VOS_UINT8       ucTimerId     定时器ID
  Output   : 
             VOS_UINT32    **pulSuspendCtrlRunMask   该定时器TimerSusTcMask 标示位的成员: gstGmmSuspendCtrl.ulTimerRunMask 或 gstGmmSuspendCtrl.ulTimerRunMaskEx
             VOS_UINT8      *pucTimerBitIndex     该定时器在标示位的索引
  NOTE     : 无
  Return   : 无
  History  :
  1.日    期   : 2015年9月26日
    作    者   : c00318887
    修改内容   : 新建函数
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerSuspendCtrlRunMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulSuspendCtrlRunMask,  
    VOS_UINT8                          *pucTimerBitIndex 
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulSuspendCtrlRunMask)        = &gstGmmSuspendCtrl.ulTimerRunMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulSuspendCtrlRunMask)        = &gstGmmSuspendCtrl.ulTimerRunMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

