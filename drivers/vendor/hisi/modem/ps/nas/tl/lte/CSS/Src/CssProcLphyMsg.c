/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssProcLphyMsg.c
  Description     : 该C文件给出了CSS模块初始化和消息处理入口的实现
  History           :
     1.wangchen 00209181    2015-05-14  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "CssProcLphyMsg.h"
#include    "CssProcSrchRslt.h"
#include    "CssProcCommMsg.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCLPHYMSG_C

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
 Function Name  : CSS_AssignLphyOpid
 Description    : 分配CSS模块和LPHY模块间的OPID
 Input          :
 Output         : pulOpid-----------------分配的OPID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AssignLphyOpid
(
    VOS_UINT16                          *pusOpid
)
{
    VOS_UINT16                           usOpid = CSS_NULL;

    /*获取当前最大OPID*/
    usOpid = (VOS_UINT16)CSS_GetLphyCurOpid();

    /*如果还未到最大值，直接加1*/
    if( usOpid < CSS_MAX_OPID)
    {
        *pusOpid = usOpid + 1;
    }
    else/*如果已经是最大值，从初值开始分配*/
    {
        (*pusOpid) = CSS_MIN_OPID;
    }

    CSS_SetLphyCurOpid(*pusOpid);

    CSS_INFO_LOG1("CSS_AssignLphyOpid,normal,assin opid:", (*pusOpid));
    TLPS_PRINT2LAYER_INFO1(CSS_AssignLphyOpid_ENUM, LNAS_FUNCTION_LABEL1, (*pusOpid));
}

/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc()
 Description    : 等待物理层切模回复过程中收到切模回复成功消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-05-18  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl = CSS_GetControlAddr();

    /* 将状态迁移至等待启动背景搜状态 */
    CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_START_BG_SRCH_CNF);

    /* 启动定时器 */
    CSS_StartTimer(&pstCssControl->stStartBGSTimer);

    /* 通知LPHY启动背景搜 */
    CSS_SndLphyMsgStartBgSearchReq();
}

/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfSucc()
 Description    : 等待物理层启动背景搜回复过程中收到启动背景搜回复成功消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfSucc(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl;

    CSS_INFO_LOG("CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc ENTER");
    TLPS_PRINT2LAYER_INFO(CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc_ENUM, LNAS_ENTRY);

    pstCssControl = CSS_GetControlAddr();

    /* 如请求的是MCC扫频 目前不处理 */
    if (CSS_BAND_SCAN_MCC_BASED == pstCssControl->stCommMsg.enBandScanType)
    {
    }
    else
    {
        /* 启动等待物理层扫频定时器 */
        CSS_StartTimer(&pstCssControl->stBandScanIndTimer);

        /* 迁移状态 */
        CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_BAND_SCAN_IND);

        /* 如果是开机前的FFT扫 */
        if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
        {
            CSS_SndLphyMsgCommBandScanReq(  CSS_GetCommScanBandListCurrNode(),
                                            CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                            CSS_GetCommScanCurFreqRangeIdx());
        }
        else
        {
            CSS_SndLphyMsgCommBandScanReq(  CSS_GetAsScanBandListCurrNode(),
                                            CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                            CSS_GetAsScanCurFreqRangeIdx());
        }
    }
}

/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfFail()
 Description    : 等待物理层起背景搜收到起背景搜失败消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfFail()
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* 将状态迁移至等待停止扫频扫频状态 */
    CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

    /* 启动定时器 */
    CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

    /* 需要通知LPHY设置从模，收到回复后，回复扫频失败 */
    CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    /* 如果是开机前的FFT扫 */
    if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
    {
        /* 存储扫频结果的空间释放 */
        CSS_FreeCommScanRsltMemory();
    }
    else
    {
        /* 存储扫频结果的空间释放 */
        CSS_FreeAsScanRsltMemory();
    }

}

/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfFail()
 Description    : 等待物理层切模回复过程中收到切模回复失败消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfFail()
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* 转状态 */
    CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

    /* 如果是开机前的FFT扫 */
    if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
    {
        /* 存储扫频结果的空间释放 */
        CSS_FreeCommScanRsltMemory();

        /* 如果设置主模失败，则通知扫频失败，停止定时器，迁移状态 */
        CSS_SndCommMsgBandScanCnf(  pstCssControl->stCommMsg.ulReceiverPid,
                                    pstCssControl->stCommMsg.ulOpid,
                                    CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
    }
    else
    {
        /* 存储扫频结果的空间释放 */
        CSS_FreeAsScanRsltMemory();

        /* 如果设置主模失败，则通知扫频失败，停止定时器，迁移状态 */
        CSS_SndMsgAsBandScanCnf(pstCssControl->stAsMsg.ulReceiverPid,
                                pstCssControl->stAsMsg.ulOpid,
                                CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
    }

}


/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc()
 Description    : 等待物理层切从模回复过程中收到切从模回复成功消息
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-05-18  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* 如果是开机前的FFT扫 */
    if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
    {
        CSS_SndCommMsgBandScanCnf(  pstCssControl->stCommMsg.ulReceiverPid,
                                    pstCssControl->stCommMsg.ulOpid,
                                    CSS_MULTI_BAND_SCAN_RESULT_SUCC);

        /* 将本地保存的扫频结果钩到HIDS上 */
        CSS_SendOmBandScanResultInfoInd(CSS_GetCommScanBandListHeadNode(), CSS_GetCommScanBandListAddr()->ucBandCount);
    }
    else
    {
        CSS_SndMsgAsBandScanCnf(pstCssControl->stAsMsg.ulReceiverPid,
                                pstCssControl->stAsMsg.ulOpid,
                                CSS_MULTI_BAND_SCAN_RESULT_SUCC);

        /* 将本地保存的扫频结果钩到HIDS上 */
        CSS_SendOmBandScanResultInfoInd(CSS_GetAsScanBandListHeadNode(), CSS_GetAsScanBandListAddr()->ucBandCount);

        CSS_SndAsBandScanRslt(pstCssControl->stAsMsg.ulReceiverPid, pstCssControl->stAsMsg.ulOpid);

        /* 存储扫频结果的空间释放 */
        CSS_FreeAsScanRsltMemory();
    }

}




VOS_VOID CSS_SndLphyMsgStopBandScanReq
(
    VOS_VOID
)
{
    CSS_LPHY_STOP_BAND_SCAN_REQ_STRU *pstCssStopBandScanReq;
    VOS_UINT16                           usOpid = CSS_NULL;

    /*分配消息空间*/
    pstCssStopBandScanReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_STOP_BAND_SCAN_CNF_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssStopBandScanReq)
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssStopBandScanReq),
                    CSS_GET_MSG_LENGTH(pstCssStopBandScanReq),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssStopBandScanReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssStopBandScanReq,ID_CSS_LPHY_STOP_BAND_SCAN_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssStopBandScanReq->usOpId = usOpid;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssStopBandScanReq);

    return ;
}


VOS_VOID CSS_SndLphyMsgSetWorkModeReq
(
    CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16       enWorkModeType
)
{
    CSS_LPHY_SET_WORK_MODE_REQ_STRU     *pstCssSetModeInactive;
    VOS_UINT16                          usOpid = CSS_NULL;

    /*分配消息空间*/
    pstCssSetModeInactive = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_SET_WORK_MODE_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssSetModeInactive)
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssSetModeInactive),
                    CSS_GET_MSG_LENGTH(pstCssSetModeInactive),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssSetModeInactive));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssSetModeInactive,ID_CSS_LPHY_SET_WORK_MODE_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssSetModeInactive->usOpId = usOpid;
    pstCssSetModeInactive->enWorkModeType = enWorkModeType;

    pstCssSetModeInactive->enDsdsRfShardFlg = CSS_LPHY_DSDS_RFSHARED_ENABLE;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssSetModeInactive);

    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgSetWorkModeReq_EUM, LNAS_WorkModeType, pstCssSetModeInactive->enWorkModeType);

    return ;
}


/*****************************************************************************
 Function Name  : CSS_SndLphyMsgBandScanReq
 Description    : 向LPHY发送BandScan请求
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-05-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SndLphyMsgCommBandScanReq
(
    CSS_COMM_SCAN_BAND_NODE_STRU               *pstBandNode,
    CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16         enScanType,
    VOS_UINT8                                   ucCurFreqRangeIdx
)
{
    CSS_LPHY_BAND_SCAN_REQ_STRU        *pstCssBandScanReq;
    VOS_UINT16                          usOpid = CSS_NULL;

    if (VOS_NULL_PTR == pstBandNode)
    {
        /*打印异常信息*/
        TLPS_PRINT2LAYER_WARNING(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_BandNodeIsNULL);
        return ;
    }

    /*分配消息空间*/
    pstCssBandScanReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_BAND_SCAN_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssBandScanReq)
    {
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssBandScanReq),
                    CSS_GET_MSG_LENGTH(pstCssBandScanReq),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssBandScanReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssBandScanReq,ID_CSS_LPHY_BAND_SCAN_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssBandScanReq->usOpId                       = usOpid;
    pstCssBandScanReq->enBandScanType               = enScanType;
    pstCssBandScanReq->enBandInd                    = pstBandNode->stBandInfo.ucBandInd;
    pstCssBandScanReq->enLteModeType                = CSS_GetLteModeTypeByBandInd(pstBandNode->stBandInfo.ucBandInd);
    pstCssBandScanReq->stFreqRangeInfo.usFreqBegin  = pstBandNode->stBandInfo.pstScanReqArray[ucCurFreqRangeIdx].usFreqBegin;
    pstCssBandScanReq->stFreqRangeInfo.usFreqEnd    = pstBandNode->stBandInfo.pstScanReqArray[ucCurFreqRangeIdx].usFreqEnd;
    pstCssBandScanReq->bitOpLteSupport              = pstBandNode->stBandInfo.bitOpLteSupport;
    pstCssBandScanReq->bitOpWcdmaSupport            = pstBandNode->stBandInfo.bitOpWcdmaSupport;
    pstCssBandScanReq->bitOpGsmSupport              = pstBandNode->stBandInfo.bitOpGsmSupport;
    pstCssBandScanReq->bitOpTdsSupport              = pstBandNode->stBandInfo.bitOpTdsSupport;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssBandScanReq);

    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_BandInd, pstCssBandScanReq->enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_FreqRangeBegin, pstCssBandScanReq->stFreqRangeInfo.usFreqBegin);
    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_FreqRangeEnd, pstCssBandScanReq->stFreqRangeInfo.usFreqEnd);

    return ;
}


/*****************************************************************************
 Function Name  : CSS_SndLphyMsgStartBgSearchReq
 Description    : 向LPHY发送start bg search请求
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SndLphyMsgStartBgSearchReq(VOS_VOID)
{
    CSS_LPHY_START_BG_SEARCH_REQ_STRU            *pstCssStartBgsReq;
    VOS_UINT16                                    usOpid = CSS_NULL;

    TLPS_PRINT2LAYER_INFO(CSS_SndLphyMsgStartBgSearchReq_ENUM, LNAS_ENTRY);

    /*分配消息空间*/
    pstCssStartBgsReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_START_BG_SEARCH_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssStartBgsReq)
    {
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssStartBgsReq),
                    CSS_GET_MSG_LENGTH(pstCssStartBgsReq),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssStartBgsReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssStartBgsReq,ID_CSS_LPHY_START_BG_SEARCH_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssStartBgsReq->usOpId                       = usOpid;
    pstCssStartBgsReq->enStartBGSearchRat           = CSS_LPHY_RAT_TYPE_LTE;
    pstCssStartBgsReq->enBsgCfgType                 = CSS_LPHY_BGSCFG_TYPE_DSDS;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssStartBgsReq);

}

/*****************************************************************************
 Function Name  : CSS_SndLphyMsgStopBgSearchReq
 Description    : 向LPHY发送stop bg search请求
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SndLphyMsgStopBgSearchReq(VOS_VOID)
{
    CSS_LPHY_STOP_BG_SEARCH_REQ_STRU             *pstCssStopBgsReq;
    VOS_UINT16                                    usOpid = CSS_NULL;

    TLPS_PRINT2LAYER_INFO(CSS_SndLphyMsgStopBgSearchReq_ENUM, LNAS_ENTRY);

    /*分配消息空间*/
    pstCssStopBgsReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_STOP_BG_SEARCH_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstCssStopBgsReq)
    {
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssStopBgsReq),
                    CSS_GET_MSG_LENGTH(pstCssStopBgsReq),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssStopBgsReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssStopBgsReq,ID_CSS_LPHY_STOP_BG_SEARCH_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssStopBgsReq->usOpId                       = usOpid;

    /*调用消息发送函数 */
    CSS_SND_MSG(pstCssStopBgsReq);

}


/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgScanIndForCommScan
 Description    : ID_CSS_LPHY_BAND_SCAN_IND消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgScanIndForCommScan
(
    const CSS_LPHY_BAND_SCAN_IND_STRU *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /*检查上报的BAND是否和当前正在处理的BAND是否一致*/
    if (pRcvMsg->stBandScanResult.enBandInd != CSS_GetCommScanBandListCurrNode()->stBandInfo.ucBandInd)
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanIndForCommScan_ENUM, LNAS_WrongBand);
        return;
    }

    CSS_StopTimer(&pstCssControl->stBandScanIndTimer);

    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanIndForCommScan_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanIndForCommScan_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum);

    /*如果遇到异常错误则返回*/
    if (CSS_CAUSE_NULL_PTR == CSS_ProcLphyBandScanRsltForCommScan(&(pRcvMsg->stBandScanResult)))
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanIndForCommScan_ENUM, LNAS_BandNodeIsNULL);
        return;
    }

    /*判断是否需要进行下一次扫频*/
    if (CSS_TRUE == CSS_IsCommScanNeedSndLphyNextBandScanReq())
    {
        CSS_StartTimer(&pstCssControl->stBandScanIndTimer);
        CSS_SndLphyMsgCommBandScanReq(CSS_GetCommScanBandListCurrNode(),
                                          CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                          CSS_GetCommScanCurFreqRangeIdx());
    }
    /*所有的频点都扫完了，此处有后续处理，转状态或其他处理*/
    else
    {
        /* 通知物理层停止背景搜 */
        CSS_SndLphyMsgStopBgSearchReq();

        /* 将LPHY设置为从模 */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

        CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    }

    /* print */
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanInd_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd,1);
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanInd_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum,1);
}

/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgScanIndForAsScan
 Description    : ID_CSS_LPHY_BAND_SCAN_IND消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgScanIndForAsScan
(
    const CSS_LPHY_BAND_SCAN_IND_STRU *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /*检查上报的BAND是否和当前正在处理的BAND是否一致*/
    if (pRcvMsg->stBandScanResult.enBandInd != CSS_GetAsScanBandListCurrNode()->stBandInfo.ucBandInd)
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_WrongBand);
        return;
    }

    CSS_StopTimer(&pstCssControl->stBandScanIndTimer);

    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum);

    /*如果遇到异常错误则返回*/
    if (CSS_CAUSE_NULL_PTR == CSS_ProcLphyBandScanRsltForAsScan(&(pRcvMsg->stBandScanResult)))
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_BandNodeIsNULL);
        return;
    }

    /*判断是否需要进行下一次扫频*/
    if (CSS_TRUE == CSS_IsAsScanNeedSndLphyNextBandScanReq())
    {
        CSS_StartTimer(&pstCssControl->stBandScanIndTimer);
        CSS_SndLphyMsgCommBandScanReq(  CSS_GetAsScanBandListCurrNode(),
                                        CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                        CSS_GetAsScanCurFreqRangeIdx());
    }
    /*所有的频点都扫完了，此处有后续处理，转状态或其他处理*/
    else
    {
        /* 通知物理层停止背景搜 */
        CSS_SndLphyMsgStopBgSearchReq();

        /* 将LPHY设置为从模 */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

        CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    }

    /* print */
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd,1);
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum,1);
}


/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgScanInd()
 Description    : ID_CSS_LPHY_BAND_SCAN_IND消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgScanInd
(
    const CSS_LPHY_BAND_SCAN_IND_STRU *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* 如果OPID不匹配，则直接退出 */
    if (pstCssControl->ulCssLphyOpid != pRcvMsg->usOpId)
    {
        /*打印出错信息*/
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanInd_ENUM, LNAS_OpidMismatch);
        return;
    }

    /*检查状态是否匹配，若不匹配，退出*/
    if (CSS_MS_SCAN != CSS_GetCurMainStatus() || CSS_SS_WAIT_BAND_SCAN_IND != CSS_GetCurSubStatus())
    {
        /*打印出错信息*/
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanInd_ENUM, LNAS_STATE_ERR);
        return;
    }

    if (VOS_TRUE == pRcvMsg->usNoRfValid)
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcLphyMsgScanInd_ENUM, LNAS_CSS_SCAN_RSLT_NO_RF);

        CSS_StopTimer(&pstCssControl->stBandScanIndTimer);

        /* 通知物理层停止背景搜 */
        CSS_SndLphyMsgStopBgSearchReq();

        /* 转到STOP_SCAN+WAIT_INACTIVE_CNF状态 */
        CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        /* 启动定时器 */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

        /* 需要通知LPHY设置从模，收到回复后，回复扫频失败 */
        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

        /* 原因值置NO_RF */
        pstCssControl->ucBandScanRslt = CSS_MULTI_BAND_SCAN_RESULT_NO_RF;

        return;
    }

    /* 如果是开机前的FFT扫 */
    if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
    {
        CSS_ProcLphyMsgScanIndForCommScan(pRcvMsg);
    }
    else
    {
        CSS_ProcLphyMsgScanIndForAsScan(pRcvMsg);
    }

    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgStopScanCnf()
 Description    : ID_CSS_LPHY_STOP_BAND_SCAN_CNF消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgStopScanCnf
(
    const CSS_LPHY_STOP_BAND_SCAN_CNF_STRU  *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* 如果OPID匹配不成功，则直接丢弃 */
    if (CSS_GetLphyCurOpid() != pRcvMsg->usOpId)
    {
        CSS_WARN_LOG("CSS_ProcLphyMsgStopScanCnf opid mismatch ");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgStopScanCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* 停止定时器 */
    CSS_StopTimer(&pstCssControl->stStopBandScanTimer);

    /* 如果停止扫频失败，则直接调用底软接口复位 */
    if(CSS_LPHY_RESULT_FAIL == pRcvMsg->enStopBandScanRslt)
    {
        CSS_ClearLocalResource();

        /* 设置从模失败，调用底软接口，直接复位 */
        (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_STOP_SCAN_FAIL, (__LINE__), (THIS_FILE_ID) );

        return ;
    }

    /* 如果OPID匹配成功，且状态为STOP_SCAN+CSS_SS_WAIT_STOP_SCAN_CNF,则需要将LPHY设置为从模 */
    if ((CSS_MS_STOP_SCAN == CSS_GetCurMainStatus()) && (CSS_SS_WAIT_STOP_SCAN_CNF == CSS_GetCurSubStatus()))
    {
        /* 通知物理层停止背景搜 */
        CSS_SndLphyMsgStopBgSearchReq();

        /* 将LPHY设置为从模 */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);
        CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    }

    return ;
}
/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgSetModeCnf()
 Description    : ID_CSS_LPHY_SET_WORK_MODE_CNF消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanProcLphyMsgSetModeCnf
(
    const CSS_LPHY_SET_WORK_MODE_CNF_STRU   *pstSetModeCnf
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    if (CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF == CSS_GetCurSubStatus())
    {
        CSS_StopTimer(&pstCssControl->stSetactiveModeTimer);

        if (CSS_LPHY_RESULT_SUCC == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc();
        }
        else
        {
            CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfFail();
        }
    }
    else if (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == CSS_GetCurSubStatus())
    {
        CSS_StopTimer(&pstCssControl->stSetInactiveModeTimer);

        /* 如果是扫频结束，收到设置从模的回复后，需要给GUNAS/AS发送扫频结果 */
        /* 如果设置从模失败，则直接复位 */
        if (CSS_LPHY_RESULT_FAIL == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_ClearLocalResource();

            /* 设置从模失败，调用底软接口，直接复位 */
            (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL, (__LINE__), (THIS_FILE_ID) );

            return;
        }

        /* 给GUNSA/AS发送扫频结果 */
        CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);
        CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc();
    }
}
/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgSetModeCnf()
 Description    : ID_CSS_LPHY_SET_WORK_MODE_CNF消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgSetModeCnf
(
    const CSS_LPHY_SET_WORK_MODE_CNF_STRU   *pstSetModeCnf
)
{
    CSS_MAIN_STATE_ENUM_UINT16          enMainState;    /* 当前处于的主状态 */
    CSS_SUB_STATE_ENUM_UINT16           enSubState;     /* 当前处于的子状态 */
    CSS_CONTROL_STRU                   *pstCssControl;
    VOS_UINT8                           ucTmpFailRslt;

    pstCssControl = CSS_GetControlAddr();

    enMainState = CSS_GetCurMainStatus();
    enSubState = CSS_GetCurSubStatus();

    /* 如果OPID匹配不成功，则直接丢弃 */
    if (CSS_GetLphyCurOpid() != pstSetModeCnf->usOpId)
    {
        CSS_WARN_LOG("CSS_ProcLphyMsgSetModeCnf opid mismatch");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgSetModeCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* 如果主状态是扫频，且设置主模成功，则给LPHY发送扫频请求 */
    if (CSS_MS_SCAN == enMainState)
    {
        CSS_MsScanProcLphyMsgSetModeCnf(pstSetModeCnf);
    }
    else if ((CSS_MS_STOP_SCAN == enMainState) && (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == enSubState))
    {
        /* 停止定时器 */
        CSS_StopTimer(&pstCssControl->stSetInactiveModeTimer);

        /* 如果设置从模失败，则直接复位 */
        if (CSS_LPHY_RESULT_FAIL == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_ClearLocalResource();

            /* 设置从模失败，调用底软接口，直接复位 */
            (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL, (__LINE__), (THIS_FILE_ID) );

            return;
        }

        /* 进入该状态有两种情况: GUNAS/AS通知CSS模块停止扫频；或者是扫频过程中，出现异常，CSS模块主动通知LPHY停止扫频 */
        /* 如果保存的消息是停止扫频，则直接回复停止扫频成功 */
        /* 如果是扫频过程中出现异常，则回复扫频失败 */
        CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

        if (CSS_MULTI_BAND_SCAN_RESULT_NO_RF == pstCssControl->ucBandScanRslt)
        {
            ucTmpFailRslt = CSS_MULTI_BAND_SCAN_RESULT_NO_RF;
        }
        else
        {
            ucTmpFailRslt = CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS;
        }
        if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
        {
            if ((CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg)
                && (ID_CSS_MULTI_BAND_SCAN_REQ == pstCssControl->stCommMsg.enMsgId))
            {
                CSS_SndCommMsgBandScanCnf(  pstCssControl->stCommMsg.ulReceiverPid,
                                            pstCssControl->stCommMsg.ulOpid,
                                            ucTmpFailRslt);
            }

            if ((CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg)
                    && (ID_CSS_STOP_BAND_SCAN_REQ == pstCssControl->stCommMsg.enMsgId))
            {
                CSS_SndCommMsgStopBandScanCnf(  pstCssControl->stCommMsg.ulReceiverPid,
                                                CSS_RESULT_SUCC );
            }
            /* 停止扫频或者扫频过程中异常，需要将存储扫频结果的空间释放 */
            CSS_FreeCommScanRsltMemory();
        }
        else
        {
            if ((CSS_OP_TRUE == pstCssControl->stAsMsg.ulIsSaveMsg)
                && (ID_CSS_AS_BAND_SCAN_REQ == pstCssControl->stAsMsg.ulMsgId))
            {
                CSS_SndMsgAsBandScanCnf(pstCssControl->stAsMsg.ulReceiverPid,
                                        pstCssControl->stAsMsg.ulOpid,
                                        ucTmpFailRslt);
            }

            if ((CSS_OP_TRUE == pstCssControl->stAsMsg.ulIsSaveMsg)
                    && (ID_CSS_AS_STOP_BAND_SCAN_REQ == pstCssControl->stAsMsg.ulMsgId))
            {
                CSS_SndMsgAsStopBandScanCnf(pstCssControl->stAsMsg.ulReceiverPid,
                                            CSS_RESULT_SUCC );
            }
            /* 停止扫频或者扫频过程中异常，需要将存储扫频结果的空间释放 */
            CSS_FreeAsScanRsltMemory();
        }

        /* 原因值置0 */
        pstCssControl->ucBandScanRslt = CSS_MULTI_BAND_SCAN_RESULT_SUCC;
    }

    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgStartBgSearchCnf()
 Description    : ID_CSS_LPHY_START_BG_SEARCH_CNF消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgStartBgSearchCnf
(
    const CSS_LPHY_START_BG_SEARCH_CNF_STRU  *pRcvMsg
)
{
    CSS_MAIN_STATE_ENUM_UINT16                    enMainState;    /* 当前处于的主状态 */
    CSS_SUB_STATE_ENUM_UINT16                     enSubState;     /* 当前处于的子状态 */
    CSS_CONTROL_STRU                             *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    enMainState = CSS_GetCurMainStatus();
    enSubState = CSS_GetCurSubStatus();

    TLPS_PRINT2LAYER_INFO(CSS_ProcLphyMsgStartBgSearchCnf_ENUM, LNAS_ENTRY);

    /* 如果OPID匹配不成功，则直接丢弃 */
    if (CSS_GetLphyCurOpid() != pRcvMsg->usOpId)
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgStartBgSearchCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* 如果主状态是扫频，子状态是等待启背景搜回复 */
    if ((CSS_MS_SCAN == enMainState) && (CSS_SS_WAIT_START_BG_SRCH_CNF == enSubState))
    {
        /* 停止定时器 */
        CSS_StopTimer(&pstCssControl->stStartBGSTimer);

        if (CSS_LPHY_RESULT_SUCC == pRcvMsg->enResult)
        {
            CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfSucc();
        }
        else
        {
            CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfFail();
        }
    }
}
/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgStopBgSearchCnf()
 Description    : ID_CSS_LPHY_STOP_BG_SEARCH_CNF消息处理函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgStopBgSearchCnf
(
    const CSS_LPHY_STOP_BG_SEARCH_CNF_STRU  *pRcvMsg
)
{
    TLPS_PRINT2LAYER_INFO(CSS_ProcLphyMsgStopBgSearchCnf_ENUM, LNAS_ENTRY);

    /* 如果OPID匹配不成功，则直接丢弃 */
    if (CSS_GetLphyCurOpid() != pRcvMsg->usOpId)
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgStopBgSearchCnf_ENUM, LNAS_OpidMismatch);
        return;
    }
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
VOS_VOID CSS_ProcLphyMsg(const VOS_VOID *pRcvMsg )
{
    /* 定义消息头指针*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* 获取消息头指针*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_CSS_LPHY_BAND_SCAN_IND:
            CSS_ProcLphyMsgScanInd((const CSS_LPHY_BAND_SCAN_IND_STRU *)pRcvMsg);
            break;

        case ID_CSS_LPHY_STOP_BAND_SCAN_CNF:
            CSS_ProcLphyMsgStopScanCnf((const CSS_LPHY_STOP_BAND_SCAN_CNF_STRU *)pRcvMsg);
            break;

        case ID_CSS_LPHY_SET_WORK_MODE_CNF:
            CSS_ProcLphyMsgSetModeCnf((const CSS_LPHY_SET_WORK_MODE_CNF_STRU *)pRcvMsg);
            break;
        case ID_CSS_LPHY_START_BG_SEARCH_CNF:
            CSS_ProcLphyMsgStartBgSearchCnf((const CSS_LPHY_START_BG_SEARCH_CNF_STRU *)pRcvMsg);
            break;
        case ID_CSS_LPHY_STOP_BG_SEARCH_CNF:
            CSS_ProcLphyMsgStopBgSearchCnf((const CSS_LPHY_STOP_BG_SEARCH_CNF_STRU *)pRcvMsg);
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




