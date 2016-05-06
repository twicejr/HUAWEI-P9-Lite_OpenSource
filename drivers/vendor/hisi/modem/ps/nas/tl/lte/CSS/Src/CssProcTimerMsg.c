/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssProcTimerMsg.c
  Description     : 该C文件给出了CSS模块初始化和消息处理入口的实现
  History           :
     1.wangchen 00209181    2015-05-14  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "CssProcTimerMsg.h"
#include    "CssProcLphyMsg.h"
#include    "CssProcCommMsg.h"
#include    "CssCloudStrategyPublic.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCTIMERMSG_C

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
 Function Name  : CSS_ProcSetInactiveModeTimerExp()
 Description    : TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF定时器超时处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcSetInactiveModeTimerExp
(
    VOS_VOID
)
{
    TLPS_PRINT2LAYER_INFO(CSS_ProcSetInactiveModeTimerExp_ENUM, LNAS_ENTRY);

    CSS_ClearLocalResource();

    /* 设置从模失败，调用底软接口，直接复位 */
    (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_TIMEOUT, (__LINE__), (THIS_FILE_ID) );
    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcSetActiveModeTimerExp()
 Description    : TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF定时器超时处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcSetActiveModeTimerExp
(
    VOS_VOID
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    TLPS_PRINT2LAYER_INFO(CSS_ProcSetActiveModeTimerExp_ENUM, LNAS_TIMER_EXPIRED);

    pstCssControl = CSS_GetControlAddr();

    /* 将状态迁移至等待停止扫频扫频状态 */
    CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

    /* 启动定时器 */
    CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

     /* 需要通知LPHY设置从模，收到回复后，回复扫频失败 */
    CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    return ;
}
/*****************************************************************************
 Function Name  : CSS_ProcBandScanTimerExp()
 Description    : TI_CSS_WAIT_FOR_SCAN_IND定时器超时处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcBandScanTimerExp
(
    VOS_VOID
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    TLPS_PRINT2LAYER_INFO(CSS_ProcBandScanTimerExp_ENUM, LNAS_TIMER_EXPIRED);

    pstCssControl = CSS_GetControlAddr();

    /* 将状态迁移至等待停止扫频扫频状态 */
    CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_STOP_SCAN_CNF);

    /* 启动定时器 */
    CSS_StartTimer(&pstCssControl->stStopBandScanTimer);

    /* 需要通知LPHY停止扫频，并设置从模，收到回复后，回复扫频失败 */
    CSS_SndLphyMsgStopBandScanReq();

    return ;
}
/*****************************************************************************
 Function Name  : CSS_ProcStopBandScanTimerExp()
 Description    : TI_CSS_WAIT_FOR_STOP_SCAN_CNF定时器超时处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcStopBandScanTimerExp
(
    VOS_VOID
)
{
    TLPS_PRINT2LAYER_INFO(CSS_ProcStopBandScanTimerExp_ENUM, LNAS_TIMER_EXPIRED);

    CSS_ClearLocalResource();

    /* 停止扫频失败，调用底软接口，直接复位 */
    (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_TIMEOUT, (__LINE__), (THIS_FILE_ID) );

    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcApUpdateWaitMccSetReqTimerExp()
 Description    : TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ定时器超时处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcApUpdateWaitMccSetReqTimerExp(VOS_VOID)
{
    /* 终止AP更新流程 */
    CSS_EndApUpdateProcedure();
}


/*****************************************************************************
 Function Name  : CSS_ProcMmcOrAsUpdateWaitMccSetReqTimerExp()
 Description    : TI_CSS_WAIT_MMC_OR_AS_UPDATE_MCC_SET_REQ定时器超时处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcMmcOrAsUpdateWaitMccSetReqTimerExp(const REL_TIMER_MSG *pRcvMsg)
{
    VOS_UINT32                          ulLoop;
    CSS_MCC_UPDATE_STRU                *pstUpdate;

    CSS_SndCurrGeoRsp(pRcvMsg->ulPara, CSS_RESULT_FAIL);

    CSS_PrintLocalPrefFreqInfo();

    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        pstUpdate = &(CSS_GetCloudContrlAddr()->astMccUpdate[ulLoop]);
        /* 找到该PID */
        if (pRcvMsg->ulPara == pstUpdate->ulPid
            && CSS_TRUE == pstUpdate->ucIsUpdating)
        {
            /* 终止MMC或AS更新流程 */
            CSS_EndMmcOrAsUpdateProcedure(pstUpdate);
            break;
        }
    }

}

/*****************************************************************************
 Function Name  : CSS_ProcWaitStartBgsTimerExp()
 Description    : TI_CSS_WAIT_START_BG_SERACH_CNF定时器超时处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcWaitStartBgsTimerExp(const REL_TIMER_MSG *pRcvMsg)
{
    CSS_CONTROL_STRU                   *pstCssControl = CSS_GetControlAddr();

    TLPS_PRINT2LAYER_INFO(CSS_ProcWaitStartBgsTimerExp_ENUM, LNAS_ENTRY);

    /* 通知物理层停止背景搜 */
    CSS_SndLphyMsgStopBgSearchReq();

    /* 转到STOP_SCAN+WAIT_INACTIVE_CNF状态 */
    CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

    /* 启动定时器 */
    CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

     /* 需要通知LPHY设置从模，收到回复后，回复扫频失败 */
    CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);
}


/*****************************************************************************
 Function Name  : CSS_ProcLphyMsg()
 Description    : LPHY消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcTimerMsg(const REL_TIMER_MSG *pRcvMsg)
{
    CSS_TIMER_ID_ENUM_UINT16            enTimerName;

    enTimerName = (VOS_UINT16)PS_GET_REL_TIMER_NAME(pRcvMsg);

    switch(enTimerName)
    {
        case TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF:
            CSS_ProcSetInactiveModeTimerExp();
            break;

        case TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF:
            CSS_ProcSetActiveModeTimerExp();
            break;

        case TI_CSS_WAIT_FOR_SCAN_IND:
            CSS_ProcBandScanTimerExp();
            break;

        case TI_CSS_WAIT_FOR_STOP_SCAN_CNF:
            CSS_ProcStopBandScanTimerExp();
            break;
        case TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ:
            CSS_ProcApUpdateWaitMccSetReqTimerExp();
            break;
        case TI_CSS_WAIT_MMC_OR_AS_UPDATE_MCC_SET_REQ:
            CSS_ProcMmcOrAsUpdateWaitMccSetReqTimerExp(pRcvMsg);
            break;
        case TI_CSS_WAIT_START_BG_SERACH_CNF:
            CSS_ProcWaitStartBgsTimerExp(pRcvMsg);
            break;
        default:
            break;
    }
}

#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif





