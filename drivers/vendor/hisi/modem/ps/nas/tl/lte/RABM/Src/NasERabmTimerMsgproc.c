/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : RabmTimerMsgproc.c
  Description     : 该c文件给出了TIMER_MSG模块的实现
  History         :
     1.杨茜惠 00135146       2008-09-04  Draft Enact
     2.杨茜惠 00135146       2009-09-18  BN8D01065  Modify
                             修改内容:增加RB REEST定时器超时处理

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmTimerMsgProc.h"
#include  "NasERabmRrcMsgProc.h"
#include  "NasERabmCdsMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMTIMERMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMTIMERMSGPROC_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ERABM_WaitEpsbActTimerExpire
 Description     : RB建立等待定时器超时
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yangqianhui 00135146      2008-10-11  Draft Enact
    2.lihong00150010            2009-12-24  Modify

*****************************************************************************/
/*lint -e960*/
VOS_VOID NAS_ERABM_WaitEpsbActTimerExpire( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    (VOS_VOID)enTimerName;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_WaitEpsbActTimerExpire is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitEpsbActTimerExpire_ENUM, LNAS_ENTRY);

    if (NAS_ERABM_WAIT_EPSB_ACT_MSG == NAS_ERABM_GetWaitEpsbActSign())
    {
        /* 向ESM发承载状态消息 */
        NAS_ERABM_InformEsmBearerStatus(0);

        /*清除等待EPS承载激活标识*/
        NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);

        /*通知后台NAS_ERABM_RB_WAIT_EPSB_ACT_TIMER定时器超时*/
        NAS_ERABM_NORM_LOG("NAS_ERABM_WaitEpsbActTimerExpire: NAS_ERABM_RB_WAIT_EPSB_ACT_TIMER expire!");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitEpsbActTimerExpire_ENUM, LNAS_FUNCTION_LABEL1);
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_WaitRbReestTimerExpier
 Description     : 触发EMM发起服务请求定时器超时处理函数
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.y00135146      2009-9-17  Draft Enact
    2.l00150010      2012-12-14 Modify:Emergency

*****************************************************************************/
VOS_VOID NAS_ERABM_WaitRbReestTimerExpier
(
    NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName,
    VOS_UINT32                      ulTimerPara
)
{
    NAS_ERABM_START_TIMER_STRU           *pstTimerInfo       = VOS_NULL_PTR;

    pstTimerInfo = NAS_ERABM_GetRbTimer(enTimerName);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_WaitRbReestTimerExpier: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_WaitRbReestTimerExpier_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return ;
    }
    if(NAS_ERABM_TIMER_STATE_STOPED == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
    {
        /* NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER停止时更新计数，否则不更新,
           NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER运行时持续尝试重建,使UE和网侧状态一至*/
        /*更新定时器超时次数*/
        pstTimerInfo->ucExpireTimes++;
    }
    /*lint -e961*/
    NAS_ERABM_LOG1("NAS_ERABM_WaitRbReestTimerExpier:data pending = ",NAS_ERABM_GetUpDataPending());
    TLPS_PRINT2LAYER_INFO1(NAS_ERABM_WaitRbReestTimerExpier_ENUM, LNAS_UpDataPendingValue, NAS_ERABM_GetUpDataPending());
    /*lint +e961*/
    /* 若超时次数在9次以内，并且承载没有对应的DRB，
       则向EMM发送EMM_ERABM_REEST_REQ消息，请求建链，并重新启动
       定时器，否则不再启动定时器，且释放缓存消息*/
    if (( pstTimerInfo->ucExpireTimes < TI_NAS_ERABM_WAIT_RB_REEST_TIMER_MAX_EXP_NUM)
        &&(NAS_ERABM_SUCCESS== NAS_ERABM_IsAllActtiveBearerWithoutDrb())
        &&(NAS_ERABM_SERVICE_STATE_INIT == NAS_ERABM_GetEmmSrState()) )
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_EMM_RB_ReestTimerExpire:INFO:Expire times less than 9!");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitRbReestTimerExpier_ENUM, LNAS_FUNCTION_LABEL1);
        NAS_ERABM_SndRabmEmmReestReq(ulTimerPara);
        NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_RB_REEST_LENGTH,
                                NAS_ERABM_WAIT_RB_REEST_TIMER,
                                ulTimerPara);
    }
    else
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_EMM_RB_ReestTimerExpire:INFO:Expire times is 9!");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitRbReestTimerExpier_ENUM, LNAS_FUNCTION_LABEL2);

        /*更新定时器超时次数*/
        pstTimerInfo->ucExpireTimes = 0;

        /*SERVICE流程停止*/
        NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

        /* 通知L2释放缓存的数据包 */
        /*APPITF_FreeAllofRabmBuf();*/

        /* 通知CDS释放缓存的数据包 */
        NAS_ERABM_SndErabmCdsFreeBuffDataInd();

        /* 清除上行数据阻塞标志*/
        NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);
    }
}


/*****************************************************************************
 Function Name   : NAS_ERABM_WaitRbResumeTimerExpier
 Description     : DRB挂起定时器超时处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing      2010-12-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_WaitRbResumeTimerExpier( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    VOS_UINT32                          ulEpsbId = NAS_ERABM_NULL;

    (VOS_VOID)enTimerName;

    NAS_ERABM_INFO_LOG("NAS_ERABM_WaitRbResumeTimerExpier is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_WaitRbResumeTimerExpier_ENUM, LNAS_ENTRY);

    /*RRC链路异常，通知EMM释放链路*/
    NAS_ERABM_SndRabmEmmRelReq();

    /* 释放所有RB */
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId<= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        NAS_ERABM_RcvRbRelease(ulEpsbId);
    }

    /* 通知L2释放缓存的数据包 */
    /*APPITF_FreeAllofRabmBuf();*/

    /* 通知CDS释放缓存的数据包 */
    NAS_ERABM_SndErabmCdsFreeBuffDataInd();

    /* 清除上行数据阻塞标志*/
    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

}


VOS_VOID  NAS_ERABM_WaitTcFreeBufferTimer( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName )
{
    (VOS_VOID)enTimerName;

    /*APPITF_FreeAllofRabmBuf();*/

    /* 通知CDS释放缓存的数据包 */
    NAS_ERABM_SndErabmCdsFreeBuffDataInd();

    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_TimerMsgDistr
 Description     : RABM模块RB建立等待计时器超时
 Input           : VOS_UNIT8 ucName
 Output          : VOS_VOID
 Return          : VOS_VOID

  History        :
     1.杨茜惠 00135146         2008-9-4  Draft Enact
     2.杨茜惠 00135146         2009-09-18  BN8D01065  Modify
*****************************************************************************/
VOS_VOID   NAS_ERABM_TimerMsgDistr(const VOS_VOID *pRcvMsg )
{

    VOS_UINT32                           ulTimerIndex  = 0;
    NAS_ERABM_START_TIMER_STRU           *pstTimerInfo = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_TimerMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_TimerMsgDistr_ENUM, LNAS_ENTRY);

    ulTimerIndex = PS_GET_REL_TIMER_NAME(pRcvMsg);

    pstTimerInfo = NAS_ERABM_GetRbTimer(ulTimerIndex);

    if ( VOS_NULL_PTR == pstTimerInfo )
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerMsgDistr: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerMsgDistr_ENUM, LNAS_ERABM_StateTimerIsNULL);
        return ;
    }

    if (PS_GET_REL_TIMER_NAME(pRcvMsg) == pstTimerInfo->enName)
    {
        switch (pstTimerInfo->enName)
        {
            case NAS_ERABM_WAIT_EPSB_ACT_TIMER:
                NAS_ERABM_WaitEpsbActTimerExpire(NAS_ERABM_WAIT_EPSB_ACT_TIMER);
                break;

            case NAS_ERABM_WAIT_RB_REEST_TIMER:
                NAS_ERABM_WaitRbReestTimerExpier(NAS_ERABM_WAIT_RB_REEST_TIMER,PS_GET_REL_TIMER_PARA(pRcvMsg));
                break;
            case NAS_ERABM_WAIT_RB_RESUME_TIMER:
                NAS_ERABM_WaitRbResumeTimerExpier(NAS_ERABM_WAIT_RB_RESUME_TIMER);
                break;

            case NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER:
                NAS_ERABM_WaitTcFreeBufferTimer(NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER);
                break;
            case NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER:
                /* 去注册RF资源通知 */
                NAS_ERABM_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_LTE_PS_BACKGROUND_CALL);
                break;
            default:
                NAS_ERABM_WARN_LOG("NAS_ERABM_TimerMsgDistr:RB TimerExpire: unreasonable Timer expire");
                TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerMsgDistr_ENUM, LNAS_ERABM_UnreasonableTimerExpire);
                break;
        }
    }
    else
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_TimerMsgDistr: RBSETUP Timer Expire info err!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TimerMsgDistr_ENUM, LNAS_ERABM_RBSETUPTimerExpireInfoErr);
    }
}
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

