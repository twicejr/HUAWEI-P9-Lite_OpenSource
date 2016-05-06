/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssProcLmmMsg.c
  Description     : 该C文件给出了IMSA模块初始化和消息处理入口的实现
  History           :
     1.wangchen 00209181    2015-05-14  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "CssPublic.h"
#include "CssProcLmmMsg.h"
#include "CssCloudStrategyPublic.h"


#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCLMMMSG_C

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : CSS_TimerInit()
 Description    : 定时器初始化函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_TimerInit
(
    VOS_VOID
)
{
    /* 初始化定时器 */
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    pstCssControl->stSetInactiveModeTimer.phTimer     = VOS_NULL_PTR;
    pstCssControl->stSetInactiveModeTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCssControl->stSetInactiveModeTimer.usName      = TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF;
    pstCssControl->stSetInactiveModeTimer.ulTimerLen  = TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF_LEN;

    pstCssControl->stSetactiveModeTimer.phTimer     = VOS_NULL_PTR;
    pstCssControl->stSetactiveModeTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCssControl->stSetactiveModeTimer.usName      = TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF;
    pstCssControl->stSetactiveModeTimer.ulTimerLen  = TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF_LEN;

    pstCssControl->stBandScanIndTimer.phTimer     = VOS_NULL_PTR;
    pstCssControl->stBandScanIndTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCssControl->stBandScanIndTimer.usName      = TI_CSS_WAIT_FOR_SCAN_IND;
    pstCssControl->stBandScanIndTimer.ulTimerLen  = TI_CSS_WAIT_FOR_SCAN_IND_LEN;

    pstCssControl->stStopBandScanTimer.phTimer     = VOS_NULL_PTR;
    pstCssControl->stStopBandScanTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCssControl->stStopBandScanTimer.usName      = TI_CSS_WAIT_FOR_STOP_SCAN_CNF;
    pstCssControl->stStopBandScanTimer.ulTimerLen  = TI_CSS_WAIT_FOR_STOP_SCAN_CNF_LEN;

    pstCssControl->stStartBGSTimer.phTimer     = VOS_NULL_PTR;
    pstCssControl->stStartBGSTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCssControl->stStartBGSTimer.usName      = TI_CSS_WAIT_START_BG_SERACH_CNF;
    pstCssControl->stStartBGSTimer.ulTimerLen  = TI_CSS_WAIT_START_BG_SEARCH_CNF_LEN;


    return ;
}

/*****************************************************************************
 Function Name  : CSS_StopAllTimer
 Description    : 停止所有定时器
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-05-23  Draft Enact
*****************************************************************************/
VOS_VOID CSS_StopAllTimer(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    CSS_StopTimer(&pstCssControl->stSetInactiveModeTimer);
    CSS_StopTimer(&pstCssControl->stSetactiveModeTimer);
    CSS_StopTimer(&pstCssControl->stBandScanIndTimer);
    CSS_StopTimer(&pstCssControl->stStopBandScanTimer);
}





/*****************************************************************************
 Function Name  : CSS_ProcLmmMsgStartInd()
 Description    : ID_LMM_CSS_START_IND消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLmmMsgStartInd
(
    const VOS_VOID                     *pRcvMsg
)
{
    (VOS_VOID)pRcvMsg;

    /* 如果已开机，则直接丢弃 */
    if (CSS_SS_WAIT_START_IND != CSS_GetCurSubStatus())
    {
        return;
    }

    /* 全局变量初始化 */
    CSS_MEM_SET_S(&g_stCssControl, sizeof(CSS_CONTROL_STRU), 0, sizeof(CSS_CONTROL_STRU));

    /* 初始化定时器 */
    CSS_TimerInit();

    /* 获取NV中可驻留门限信息 */
    if (CSS_SUCC != CSS_ReadNvRssiThreshold(&(g_stCssControl.stRssiThreshold)))
    {
        g_stCssControl.stRssiThreshold.sGHighRssiThresHold = (CSS_GSM_HIGH_THRESHOLD * CSS_RSSI_64DB);
        g_stCssControl.stRssiThreshold.sGLowRssiThresHold = (CSS_GSM_LOW_THRESHOLD * CSS_RSSI_64DB);

        g_stCssControl.stRssiThreshold.sWHighRssiThresHold = (CSS_WCDMA_HIGH_THRESHOLD * CSS_RSSI_64DB);
        g_stCssControl.stRssiThreshold.sWLowRssiThresHold = (CSS_WCDMA_LOW_THRESHOLD * CSS_RSSI_64DB);

        g_stCssControl.stRssiThreshold.sLHighRssiThresHold = (CSS_LTE_HIGH_THRESHOLD * CSS_RSSI_64DB);
        g_stCssControl.stRssiThreshold.sLLowRssiThresHold = (CSS_LTE_LOW_THRESHOLD * CSS_RSSI_64DB);
    }

    CSS_SendOmRatThresholdInfoInd(&g_stCssControl.stRssiThreshold);

    /* 获取NV中COMM BAND信息 */
    if (CSS_SUCC != CSS_ReadNvCommBandConfig(&(g_stCssControl.stCommBandInfo)))
    {
        g_stCssControl.stCommBandInfo.ucBandNum = CSS_COMM_BAND_DEFAULT_NUM;

        g_stCssControl.stCommBandInfo.astBand[0].ucBandInd = CSS_BAND_IND_1;
        g_stCssControl.stCommBandInfo.astBand[0].bitOpWcdmaSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[0].bitOpLteSupport = CSS_OP_TRUE;

        g_stCssControl.stCommBandInfo.astBand[1].ucBandInd = CSS_BAND_IND_2;
        g_stCssControl.stCommBandInfo.astBand[1].bitOpGsmSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[1].bitOpWcdmaSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[1].bitOpLteSupport = CSS_OP_TRUE;

        g_stCssControl.stCommBandInfo.astBand[2].ucBandInd = CSS_BAND_IND_3;
        g_stCssControl.stCommBandInfo.astBand[2].bitOpGsmSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[2].bitOpWcdmaSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[2].bitOpLteSupport = CSS_OP_TRUE;

        g_stCssControl.stCommBandInfo.astBand[3].ucBandInd = CSS_BAND_IND_5;
        g_stCssControl.stCommBandInfo.astBand[3].bitOpGsmSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[3].bitOpWcdmaSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[3].bitOpLteSupport = CSS_OP_TRUE;

        g_stCssControl.stCommBandInfo.astBand[4].ucBandInd = CSS_BAND_IND_7;
        g_stCssControl.stCommBandInfo.astBand[4].bitOpWcdmaSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[4].bitOpLteSupport = CSS_OP_TRUE;

        g_stCssControl.stCommBandInfo.astBand[5].ucBandInd = CSS_BAND_IND_8;
        g_stCssControl.stCommBandInfo.astBand[5].bitOpGsmSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[5].bitOpWcdmaSupport = CSS_OP_TRUE;
        g_stCssControl.stCommBandInfo.astBand[5].bitOpLteSupport = CSS_OP_TRUE;

        g_stCssControl.stCommBandInfo.astBand[6].ucBandInd = CSS_BAND_IND_28;
        g_stCssControl.stCommBandInfo.astBand[6].bitOpLteSupport = CSS_OP_TRUE;

        g_stCssControl.stCommBandInfo.astBand[7].ucBandInd = CSS_BAND_IND_40;
        g_stCssControl.stCommBandInfo.astBand[7].bitOpLteSupport = CSS_OP_TRUE;

        g_stCssControl.stCommBandInfo.astBand[8].ucBandInd = CSS_BAND_IND_41;
        g_stCssControl.stCommBandInfo.astBand[8].bitOpLteSupport = CSS_OP_TRUE;
    }

    CSS_SendOmCommBandInfoInd(&g_stCssControl.stCommBandInfo);

    /*将子状态由等待开机转为IDLE*/
    CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

    return ;
}
/*****************************************************************************
 Function Name  : CSS_ProcLmmMsgStopInd()
 Description    : ID_LMM_CSS_STOP_IND消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLmmMsgStopInd
(
    const VOS_VOID                     *pRcvMsg
)
{
    (VOS_VOID)pRcvMsg;

    /* 如果已关机，则直接丢弃 */
    if (CSS_SS_WAIT_START_IND == CSS_GetCurSubStatus())
    {
        return;
    }

    /* 停止所有定时器 */
    CSS_StopAllTimer();

    /* 释放本地申请的内存, 并且初始化全局变量 */
    CSS_ClearLocalResource();

    /* 将本地MCC信息更新到NV中 */
    CSS_WriteNvMccPrefFreq();

    CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_WAIT_START_IND);

    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcLmmMsg()
 Description    : LPHY消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLmmMsg(const VOS_VOID *pRcvMsg)
{

    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_LMM_CSS_START_IND:
            CSS_ProcLmmMsgStartInd(pRcvMsg);
            break;

        case ID_LMM_CSS_STOP_IND:
            CSS_ProcLmmMsgStopInd(pRcvMsg);
            break;

        default:
            break;
    }
}


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaMain.c */


