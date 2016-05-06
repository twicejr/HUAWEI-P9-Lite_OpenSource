/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssPublic.c
  Description     : 该C文件实现公共的函数，如消息打印等
  History           :
     1.wangchen 00209181    2015-05-14  Draft Enact

******************************************************************************/



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasCommPrint.h"
#include "CssPublic.h"
#include "CssOmInterface.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPUBLIC_C

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
CSS_LPHY_FREQ_RANGE_INFO_STRU    g_ausCssLteBandFreq[] =
{{21100,21700}, {19300,19900}, {18050,18800}, {21100,21550}, {8690,8940},       /* Band1 ~Band5  */
 {8750,8850},   {26200,26900}, {9250,9600},   {18449,18799}, {21100,21700},     /* Band6 ~Band10 */
 {14759,14959}, {7290,7460},   {7460,7560},   {7580,7680},   {65535,65535},     /* Band11~Band15 */
 {65535,65535}, {7340,7460},   {8600,8750},   {8750,8900},   {7910,8210},       /* Band16~Band20 */
 {14959,15109}, {35100,35900}, {21800,22000}, {15250,15590}, {19300,19950},     /* Band21~Band25 */
 {8590,8940},   {8520,8690},   {7580,8030},   {7170,7280},   {23500,23600},     /* Band26~Band30 */
 {4625,4675},   {65535,65535}, {19000,19200}, {20100,20250}, {18500,19100},     /* Band31~Band35 */
 {19300,19900}, {19100,19300}, {25700,26200}, {18800,19200}, {23000,24000},     /* Band36~Band40 */
 {24960,26900}, {34000,36000}, {36000,38000}, {7030,8030}                       /* Band41~Band44 */
};

/* c00285307 add for 多制式和重叠频段BAND优化 Begin */

CSS_OVERLAP_BAND_STRU            g_aucOverLapBand[] =
{
 {1,4},{1,10},{2,25},{2,36},{3,9},
 {3,35},{4,10},{5,6},{5,18},{5,19},
 {5,26},{6,19},{6,26},{7,41},{9,35},
 {12,17},{13,44},{14,28},{14,44},{17,44},
 {18,26},{18,27},{19,26},{20,28},{20,44},
 {25,36},{26,27},{28,44},{29,44},{30,40},
 {33,35},{33,39},{33,37},{35,39},{37,39},
 {38,41}
};
const VOS_UINT32 g_aucOverLapBandSize = (sizeof(g_aucOverLapBand)/sizeof(CSS_OVERLAP_BAND_STRU));

/* c00285307 add for 多制式和重叠频段BAND优化 End */

CSS_LPHY_FREQ_RANGE_INFO_STRU    g_ausCssWcdmaBandFreq[] =
{{21124,21676}, {19324,19876}, {18074,18776}, {21124,21526}, {8714,8916},            /* Band1 ~Band5  */
 {8774,8826}, {26224,26876}, {9274,9576}, {18474,18774}, {21124,21676},              /* Band6 ~Band10 */
 {14784,14934}, {7314,7436}, {7484,7536}, {7604,7656}, {65535,65535},                /* Band11 ~Band15 */
 {65535,65535}, {65535,65535}, {65535,65535}, {8774,8876}, {7934,8186},              /* Band16 ~Band20 */
 {14984,15084} , {35124,35876}, {65535,65535} , {65535,65535}, {19324,19926},        /* Band21 ~Band25 */
 {8614,8916}                                                                         /* Band26*/
};

CSS_LPHY_FREQ_RANGE_INFO_STRU    g_ausCssGsmBandFreq[] =
{{65535,65535}, {19302,19898}, {18052,18798}, {65535,65535}, {8692,8938},       /* Band1 ~Band5  */
 {65535,65535}, {65535,65535}, {9212,9598}                                      /* Band6 ~Band8 */
};










VOS_CHAR                                g_acCssPrintBuf[CSS_PRINT_BUFF_LEN] = "";

NAS_COMM_PRINT_LIST_STRU g_astCssCommMsgIdArray[] =
{
    {   ID_CSS_MULTI_BAND_SCAN_REQ                 ,
            "MSG:  ID_CSS_MULTI_BAND_SCAN_REQ                           ",
        VOS_NULL_PTR},
    {   ID_CSS_STOP_BAND_SCAN_REQ                  ,
            "MSG:  ID_CSS_STOP_BAND_SCAN_REQ                            ",
        VOS_NULL_PTR},
    {   ID_CSS_MULTI_BAND_SCAN_CNF                    ,
            "MSG:  ID_CSS_MULTI_BAND_SCAN_CNF                              ",
        VOS_NULL_PTR},
    {   ID_CSS_STOP_BAND_SCAN_CNF                    ,
            "MSG:  ID_CSS_STOP_BAND_SCAN_CNF                              ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_LIST_STRU g_astCssLphyMsgIdArray[] =
{
    {   ID_CSS_LPHY_BAND_SCAN_REQ                 ,
            "MSG:  ID_CSS_LPHY_BAND_SCAN_REQ                           ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_STOP_BAND_SCAN_REQ                  ,
            "MSG:  ID_CSS_LPHY_STOP_BAND_SCAN_REQ                            ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_SET_WORK_MODE_REQ                    ,
            "MSG:  ID_CSS_LPHY_SET_WORK_MODE_REQ                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_BAND_SCAN_IND                    ,
            "MSG:  ID_CSS_LPHY_BAND_SCAN_IND                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_STOP_BAND_SCAN_CNF                    ,
            "MSG:  ID_CSS_LPHY_STOP_BAND_SCAN_CNF                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_SET_WORK_MODE_CNF                    ,
            "MSG:  ID_CSS_LPHY_SET_WORK_MODE_CNF                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_START_BG_SEARCH_REQ                    ,
            "MSG:  ID_CSS_LPHY_START_BG_SEARCH_REQ                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_STOP_BG_SEARCH_REQ                    ,
            "MSG:  ID_CSS_LPHY_STOP_BG_SEARCH_REQ                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_START_BG_SEARCH_CNF                    ,
            "MSG:  ID_CSS_LPHY_START_BG_SEARCH_CNF                              ",
        VOS_NULL_PTR},
    {   ID_CSS_LPHY_STOP_BG_SEARCH_CNF                    ,
            "MSG:  ID_CSS_LPHY_STOP_BG_SEARCH_CNF                              ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_LIST_STRU g_astCssLmmMsgIdArray[] =
{
    {   ID_LMM_CSS_START_IND                 ,
            "MSG:  ID_LMM_CSS_START_IND                           ",
        VOS_NULL_PTR},
    {   ID_LMM_CSS_STOP_IND                  ,
            "MSG:  ID_LMM_CSS_STOP_IND                            ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astCssTimerArray[] =
{
    {   TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF,
            "STATE TI:  TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF           "},
    {   TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF     ,
            "STATE TI:  TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF                  "},
    {   TI_CSS_WAIT_FOR_SCAN_IND     ,
            "STATE TI:  TI_CSS_WAIT_FOR_SCAN_IND                  "},
    {   TI_CSS_WAIT_FOR_STOP_SCAN_CNF               ,
            "STATE TI:  TI_CSS_WAIT_FOR_STOP_SCAN_CNF                  "},
    {   TI_CSS_WAIT_START_BG_SERACH_CNF               ,
            "STATE TI:  TI_CSS_WAIT_START_BG_SERACH_CNF                  "},
};


#if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
VOS_CHAR g_acCssCloudFreqMemory[CSS_CLOUD_MEM_TOTAL_LEN];
#endif

/*****************************************************************************
  3 Function
*****************************************************************************/


/*****************************************************************************
 Function Name   : CSS_SendOmOnePlmnPrefFreqInd
 Description     : 将接入层调用预置频点结果中的一条pLMN勾出来
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    chengmin 00285307 2015-11-5  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_SendOmGetOnePlmnPrefFreqRslt
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnInNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                    ulRslt,
    CSS_PREF_FREQ_INFO_STRU                      *pstPrefFreq
)
{
    CSS_OM_GET_ONE_PLMN_PREF_FREQ_RSLT_STRU      *pstMsg;


    /*分配空间并检验分配是否成功*/
    pstMsg = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_OM_GET_ONE_PLMN_PREF_FREQ_RSLT_STRU));

    if ( VOS_NULL_PTR == pstMsg )
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SendOmOnePlmnPrefFreqInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    CSS_MEM_SET_S(CSS_GET_MSG_ENTITY(pstMsg), CSS_GET_MSG_LENGTH(pstMsg), 0, CSS_GET_MSG_LENGTH(pstMsg));

    /*填写消息头*/
    CSS_WRITE_OM_MSG_HEAD(pstMsg,ID_CSS_OM_GET_ONE_PLMN_PREF_FREQ_RSLT);
    pstMsg->enRat = enRat;
    pstMsg->ucPlmnInNum = (VOS_UINT8)ulPlmnInNum;
    pstMsg->ucRslt= (VOS_UINT8)ulRslt;
    CSS_MEM_CPY_S(pstMsg->astPlmn, sizeof(CSS_PLMN_ID_STRU)*CSS_MAX_PREF_PLMN_NUM, astPlmn, sizeof(CSS_PLMN_ID_STRU)*CSS_MAX_PREF_PLMN_NUM);

    CSS_MEM_CPY_S(  &(pstMsg->stPrefFreq),
                    sizeof(CSS_PREF_FREQ_INFO_STRU),
                    pstPrefFreq,
                    sizeof(CSS_PREF_FREQ_INFO_STRU));

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    CSS_SND_MSG(pstMsg);
#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsg);
    /*释放消息空间*/
    CSS_FREE_MSG(pstMsg);
#endif

    return;
}

/*****************************************************************************
 Function Name   : CSS_SendOmGetPrefBandRslt
 Description     : 将接入层调用预置BAND结果勾出来
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    chengmin 00285307 2015-11-5  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_SendOmGetPrefBandRslt
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnInNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                    aulResult[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                    ulRslt,
    VOS_UINT32                                    ulPlmnOutNum,
    CSS_PREF_BAND_INFO_STRU                      *pstPrefBand
)
{
    CSS_OM_GET_PREF_BAND_RSLT_STRU               *pstMsg;


    /*分配空间并检验分配是否成功*/
    pstMsg = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_OM_GET_PREF_BAND_RSLT_STRU));

    if ( VOS_NULL_PTR == pstMsg )
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SendOmGetPrefBandRslt:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    CSS_MEM_SET_S(CSS_GET_MSG_ENTITY(pstMsg), CSS_GET_MSG_LENGTH(pstMsg), 0, CSS_GET_MSG_LENGTH(pstMsg));

    /*填写消息头*/
    CSS_WRITE_OM_MSG_HEAD(pstMsg,ID_CSS_OM_GET_PREF_BAND_RSLT);

    pstMsg->enRat = enRat;
    pstMsg->ucPlmnInNum = (VOS_UINT8)ulPlmnInNum;
    pstMsg->ucRslt= (VOS_UINT8)ulRslt;
    CSS_MEM_CPY_S(pstMsg->astPlmn, sizeof(CSS_PLMN_ID_STRU)*CSS_MAX_PREF_PLMN_NUM, astPlmn, sizeof(CSS_PLMN_ID_STRU)*CSS_MAX_PREF_PLMN_NUM);
    CSS_MEM_CPY_S(pstMsg->aulResult, sizeof(VOS_UINT32)*CSS_MAX_PREF_PLMN_NUM, aulResult, sizeof(VOS_UINT32)*CSS_MAX_PREF_PLMN_NUM);

    pstMsg->ulPlmnOutNum = ulPlmnOutNum;

    CSS_MEM_CPY_S(  pstMsg->astPrefBand,
                    sizeof(CSS_PREF_BAND_INFO_STRU) * CSS_MAX_PREF_PLMN_NUM,
                    pstPrefBand,
                    sizeof(CSS_PREF_BAND_INFO_STRU)*ulPlmnOutNum);

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    CSS_SND_MSG(pstMsg);
#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsg);
    /*释放消息空间*/
    CSS_FREE_MSG(pstMsg);
#endif

    return;
}


/*****************************************************************************
 Function Name   : CSS_PrintLocalPrefFreqInfo
 Description     : 将本地存的预置频点信息打印出来
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    chengmin 00285307 2015-11-5  Draft Enact
*****************************************************************************/
VOS_VOID CSS_PrintLocalPrefFreqInfo(VOS_VOID)
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    CSS_PUB_PREF_MNC_STRU              *pMncNode;
    CSS_PUB_PREF_BAND_STRU             *pBandNode;
    CSS_PUB_PREF_FREQ_STRU             *pFreqNode;

    TLPS_PRINT2LAYER_INFO1(CSS_PrintLocalPrefFreqInfo_ENUM, LNAS_ENTRY, CSS_GetPrefMccNodeNum());
    CSS_INFO_LOG1("CSS_PrintLocalPrefFreqInfo LNAS_ENTRY: ",CSS_GetPrefMccNodeNum());

    /* 直接删除该MCC节点 */
    pMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pMccNode)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_PrintLocalPrefFreqInfo_ENUM, LNAS_CSS_PREF_MCC, pMccNode->aucMccId[0], pMccNode->aucMccId[1]);
        TLPS_PRINT2LAYER_INFO1(CSS_PrintLocalPrefFreqInfo_ENUM, LNAS_CSS_PREF_MCC, pMccNode->ucMncNum);
        CSS_INFO_LOG2("LNAS_CSS_PREF_MCC: ",pMccNode->aucMccId[0], pMccNode->aucMccId[1]);
        CSS_INFO_LOG1("LNAS_CSS_PREF_MCC: ",pMccNode->ucMncNum);

        pMncNode = pMccNode->pstMncHead;
        while (CSS_NULL_PTR != pMncNode)
        {
            TLPS_PRINT2LAYER_INFO2(CSS_PrintLocalPrefFreqInfo_ENUM, LNAS_CSS_PREF_MNC, pMncNode->aucMncId[0], pMncNode->aucMncId[1]);
            TLPS_PRINT2LAYER_INFO2(CSS_PrintLocalPrefFreqInfo_ENUM, LNAS_CSS_PREF_MNC, pMncNode->ucBandNum, pMncNode->ucNoPrefBandFlg);
            CSS_INFO_LOG2("LNAS_CSS_PREF_MNC: ",pMncNode->aucMncId[0], pMncNode->aucMncId[1]);
            CSS_INFO_LOG2("LNAS_CSS_PREF_MNC: ",pMncNode->ucBandNum, pMncNode->ucNoPrefBandFlg);

            pBandNode = pMncNode->pstBandHead;
            while (CSS_NULL_PTR != pBandNode)
            {
                TLPS_PRINT2LAYER_INFO1(CSS_PrintLocalPrefFreqInfo_ENUM, LNAS_CSS_PREF_BAND, pBandNode->ucBandInd);
                TLPS_PRINT2LAYER_INFO2(CSS_PrintLocalPrefFreqInfo_ENUM, LNAS_CSS_PREF_BAND, pBandNode->ucFreqNum, pBandNode->ucRatSupport);

                CSS_INFO_LOG1("LNAS_CSS_PREF_BAND: ",pBandNode->ucBandInd);
                CSS_INFO_LOG2("LNAS_CSS_PREF_BAND: ",pBandNode->ucFreqNum, pBandNode->ucRatSupport);

                pFreqNode = pBandNode->pstFreqHead;
                while (CSS_NULL_PTR != pFreqNode)
                {
                    TLPS_PRINT2LAYER_INFO2(CSS_PrintLocalPrefFreqInfo_ENUM, LNAS_CSS_PREF_FREQ, pFreqNode->ulFreqBegin, pFreqNode->ulFreqEnd);
                    TLPS_PRINT2LAYER_INFO1(CSS_PrintLocalPrefFreqInfo_ENUM, LNAS_CSS_PREF_FREQ, pFreqNode->ucRatSupport);
                    CSS_INFO_LOG2("LNAS_CSS_PREF_FREQ: ",pFreqNode->ulFreqBegin, pFreqNode->ulFreqEnd);
                    CSS_INFO_LOG1("LNAS_CSS_PREF_FREQ: ",pFreqNode->ucRatSupport);

                    pFreqNode = pFreqNode->pstNext;
                }
                pBandNode = pBandNode->pstNext;
            }

            pMncNode = pMncNode->pstNext;
        }
        pMccNode = pMccNode->pstNext;
    }
}

/*****************************************************************************
 Function Name   : CSS_SndOmPubCloudCtrlInd
 Description     : 将本地存的全局变量打印出来
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    chengmin 00285307 2015-11-5  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SndOmPubCloudCtrlInd(VOS_VOID)
{
    CSS_OM_PUB_CLOUD_CONTROL_IND_STRU            *pstMsg;


    /*分配空间并检验分配是否成功*/
    pstMsg = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_OM_PUB_CLOUD_CONTROL_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg )
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SndOmPubCloudCtrlInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstMsg),
                    CSS_GET_MSG_LENGTH(pstMsg),
                    0,
                    CSS_GET_MSG_LENGTH(pstMsg));

    /*填写消息头*/
    CSS_WRITE_OM_MSG_HEAD(pstMsg,ID_CSS_OM_PUB_CLOUD_CONTROL_IND);

    CSS_MEM_CPY_S(  &(pstMsg->stPubCloudCtrl),
                    sizeof(CSS_OM_CLOUD_PUB_CONTROL_STRU),
                    CSS_GetCloudContrlAddr(),
                    sizeof(CSS_CLOUD_PUB_CONTROL_STRU));

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    CSS_SND_MSG(pstMsg);
#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstMsg);
    /*释放消息空间*/
    CSS_FREE_MSG(pstMsg);
#endif

    return;
}



/*****************************************************************************
 Function Name  : CSS_SndOmTimerStatus()
 Description    : 将定时器状态钩到HIDS上
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-25  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_SndOmTimerStatus(
    CSS_TIMER_RUN_STA_ENUM_UINT32          enTimerStatus,
    VOS_UINT16                          enTimerId,
    VOS_UINT32                          ulTimerRemainLen
)
{
    CSS_TIMER_INFO_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CSS_TIMER_INFO_STRU*)CSS_ALLOC_MSG(sizeof(CSS_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CSS_ERR_LOG("CSS_SndOmTimerStatus: mem alloc fail!.");
        return;
    }

    CSS_WRITE_OM_MSG_HEAD(  pstMsg, (enTimerId + CSS_TIMER_ID_TO_MSG_ID_BASE));

    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->usTimerId                   = enTimerId;
    pstMsg->usRsv                       = 0;

    pstMsg->ulTimerRemainLen            = ulTimerRemainLen;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    CSS_FREE_MSG(pstMsg);

}

/*****************************************************************************
 Function Name  : CSS_SndOmBandScanAbnormalInfo()
 Description    : 将异常信息钩到HIDS上
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-25  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_SndOmBandScanAbnormalInfo
(
    VOS_UINT32 ulFileName,
    VOS_UINT32 ulLineNo,
    VOS_UINT8 enBandScanFailReason,
    VOS_UINT8 ucPara1,
    VOS_UINT8 ucPara2
)
{
    CSS_BAND_SCAN_ABNORMAL_INFO_IND_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CSS_BAND_SCAN_ABNORMAL_INFO_IND_STRU*)CSS_ALLOC_MSG(sizeof(CSS_BAND_SCAN_ABNORMAL_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CSS_ERR_LOG("CSS_SndOmBandScanAbnormalInfo: mem alloc fail!.");
        return;
    }

    CSS_WRITE_OM_MSG_HEAD(  pstMsg, ID_CSS_BAND_SCAN_ABNORMAL_INFO_IND);

    pstMsg->enCurMainState              = CSS_GetCurMainStatus();
    pstMsg->enCurSubState               = CSS_GetCurSubStatus();
    pstMsg->enBandScanFailReason        = enBandScanFailReason;
    pstMsg->ucPara1                     = ucPara1;
    pstMsg->ucPara2                     = ucPara2;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    CSS_FREE_MSG(pstMsg);

}


/*****************************************************************************
 Function Name   : CSS_SendOmStateChangeInd
 Description     : 将状态变化钩到HIDS上
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    wangchen 00209181 2015-05-25  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_SendOmStateChangeInd
(
    CSS_MAIN_STATE_ENUM_UINT16                      enPreMainState,
    CSS_SUB_STATE_ENUM_UINT16                       enPreSubState,
    CSS_MAIN_STATE_ENUM_UINT16                      enCurMainState,
    CSS_SUB_STATE_ENUM_UINT16                       enCurSubState
)
{
    CSS_STATE_CHANGE_IND_STRU           *pstStateChangeInd;


    /*分配空间并检验分配是否成功*/
    pstStateChangeInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_STATE_CHANGE_IND_STRU));

    if ( VOS_NULL_PTR == pstStateChangeInd )
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SendOmStateChangeInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstStateChangeInd),
                    CSS_GET_MSG_LENGTH(pstStateChangeInd),
                    0,
                    CSS_GET_MSG_LENGTH(pstStateChangeInd));

    /*填写消息头*/
    CSS_WRITE_OM_MSG_HEAD(pstStateChangeInd,ID_CSS_STATE_CHANGE_IND);

    pstStateChangeInd->enPreMainState = enPreMainState;
    pstStateChangeInd->enPreSubState = enPreSubState;
    pstStateChangeInd->enCurMainState = enCurMainState;
    pstStateChangeInd->enCurSubState = enCurSubState;


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    CSS_SND_MSG(pstStateChangeInd);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstStateChangeInd);

    /*释放消息空间*/
    CSS_FREE_MSG(pstStateChangeInd);

#endif

    return;
}
/*****************************************************************************
 Function Name   : CSS_SendOmCommBandInfoInd
 Description     : 将COMM BAND的配置钩到HIDS上
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    wangchen 00209181 2015-05-25  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_SendOmCommBandInfoInd
(
    CSS_COMM_BAND_INFO_STRU  *pstCssCommBandConfig
)
{
    CSS_COMM_BAND_NV_INFO_IND_STRU           *pstCommBandInfoInd;


    /*分配空间并检验分配是否成功*/
    pstCommBandInfoInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_COMM_BAND_NV_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstCommBandInfoInd )
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SendOmCommBandInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCommBandInfoInd),
                    CSS_GET_MSG_LENGTH(pstCommBandInfoInd),
                    0,
                    CSS_GET_MSG_LENGTH(pstCommBandInfoInd));

    /*填写消息头*/
    CSS_WRITE_OM_MSG_HEAD(pstCommBandInfoInd,ID_CSS_COMM_BAND_NV_INFO_IND);

    CSS_MEM_CPY_S(  &pstCommBandInfoInd->stCommBandInfo,
                    sizeof(CSS_OM_COMM_BAND_CONFIG_STRU),
                    pstCssCommBandConfig,
                    sizeof(CSS_COMM_BAND_INFO_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    CSS_SND_MSG(pstCommBandInfoInd);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstCommBandInfoInd);

    /*释放消息空间*/
    CSS_FREE_MSG(pstCommBandInfoInd);

#endif

    return;
}

/*****************************************************************************
 Function Name   : CSS_SendOmRatThresholdInfoInd
 Description     : 将预置的配置钩到HIDS上
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    wangchen 00209181 2015-05-25  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_SendOmRatThresholdInfoInd
(
    CSS_RSSI_THRESHOLD_STRU  *pstCssRatThresholdConfig
)
{
    CSS_RAT_THRESHOLD_INFO_IND_STRU           *pstCssRatThresholdInfoInd;


    /*分配空间并检验分配是否成功*/
    pstCssRatThresholdInfoInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_RAT_THRESHOLD_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstCssRatThresholdInfoInd )
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SendOmRatThresholdInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssRatThresholdInfoInd),
                    CSS_GET_MSG_LENGTH(pstCssRatThresholdInfoInd),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssRatThresholdInfoInd));

    /*填写消息头*/
    CSS_WRITE_OM_MSG_HEAD(pstCssRatThresholdInfoInd,ID_CSS_RAT_THRESHOLD_INFO_IND);

    CSS_MEM_CPY_S(  &pstCssRatThresholdInfoInd->stBandThresholdInfo,
                    sizeof(CSS_OM_RSSI_THRESHOLD_STRU),
                    pstCssRatThresholdConfig,
                    sizeof(CSS_RSSI_THRESHOLD_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    CSS_SND_MSG(pstCssRatThresholdInfoInd);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstCssRatThresholdInfoInd);

    /*释放消息空间*/
    CSS_FREE_MSG(pstCssRatThresholdInfoInd);

#endif

    return;
}

/*****************************************************************************
 Function Name   : CSS_SendOmBandScanResultInfoInd
 Description     : 将存储的扫频结果钩到HIDS上
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    wangchen 00209181 2015-05-25  Draft Enact
    2.    chengmin 00285307 2015-12-14  mod for TDS plmn search
*****************************************************************************/
VOS_VOID  CSS_SendOmBandScanResultInfoInd
(
    CSS_COMM_SCAN_BAND_NODE_STRU       *pBandNode,
    VOS_UINT8                           ucInBandNum
)
{
    CSS_BAND_SCAN_RESULT_IND_STRU           *pstCssBandScanResultInd;
    VOS_UINT8                                ucBandNum     = 0;
    VOS_UINT8                                ucBandNodeNum = 0;
    VOS_UINT16                               usMemSize = 0;
    VOS_UINT8                                ucCopyNum;


    /*分配空间并检验分配是否成功*/
    pstCssBandScanResultInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_BAND_SCAN_RESULT_IND_STRU));

    if ( VOS_NULL_PTR == pstCssBandScanResultInd )
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SendOmBandScanResultInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssBandScanResultInd),
                    CSS_GET_MSG_LENGTH(pstCssBandScanResultInd),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssBandScanResultInd));

    /*填写消息头*/
    CSS_WRITE_OM_MSG_HEAD(pstCssBandScanResultInd,ID_CSS_BAND_SCAN_RESULT_IND);

    /* 填充扫频结果 */
    while (CSS_NULL_PTR != pBandNode && ucBandNodeNum < ucInBandNum)
    {
        pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].enBandInd          = pBandNode->stBandInfo.ucBandInd;
        pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].ucFreqNum          = pBandNode->stBandInfo.ucScanRsltArrayCount;

        ucCopyNum = ((pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].ucFreqNum < CSS_MAX_BAND_FREQ_RANGE_NUM)
                    ? pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].ucFreqNum
                    : CSS_MAX_BAND_FREQ_RANGE_NUM);

        CSS_MEM_CPY_S(  pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].astFreqScanResult,
                        sizeof(CSS_FREQ_RANGE_STRU) * CSS_MAX_BAND_FREQ_RANGE_NUM,
                        pBandNode->stBandInfo.pstScanRsltArray,
                        sizeof(CSS_FREQ_RANGE_STRU) * ucCopyNum);

        /*lint -e734*/
        pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].ucDynMemSize = sizeof(CSS_FREQ_RANGE_STRU)*(pBandNode->stBandInfo.ucScanRsltArrayCount)
                                                                                         + sizeof(CSS_LPHY_FREQ_RANGE_INFO_STRU)*(pBandNode->stBandInfo.ucScanReqCount);
        /*lint +e734*/
        usMemSize += (pstCssBandScanResultInd->stBandScanResult.astScanRange[ucBandNum].ucDynMemSize + sizeof(CSS_COMM_SCAN_BAND_NODE_STRU));

        ucBandNum ++;

        pBandNode       = pBandNode->pstNext;
        ucBandNodeNum  += 1;
    }

    pstCssBandScanResultInd->stBandScanResult.ucBandNum = ucBandNum;

    pstCssBandScanResultInd->stBandScanResult.usDynMemSize = usMemSize;

#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    CSS_SND_MSG(pstCssBandScanResultInd);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstCssBandScanResultInd);

    /*释放消息空间*/
    CSS_FREE_MSG(pstCssBandScanResultInd);

#endif

    return;
}


/*****************************************************************************
 Function Name   : CSS_SendOmBandApiInfoInd
 Description     : 将API信息钩到HIDS上
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    wangchen 00209181 2015-05-25  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_SendOmBandApiInfoInd
(
    CSS_RAT_COVERAGE_STRU                           *pstRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU                    *pstBandScanResult
)
{
    CSS_BAND_SCAN_API_INFO_IND_STRU           *pstCssBandApiInfoInd;


    /*分配空间并检验分配是否成功*/
    pstCssBandApiInfoInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_BAND_SCAN_API_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstCssBandApiInfoInd )
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SendOmBandApiInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssBandApiInfoInd),
                    CSS_GET_MSG_LENGTH(pstCssBandApiInfoInd),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssBandApiInfoInd));

    /*填写消息头*/
    CSS_WRITE_OM_MSG_HEAD(pstCssBandApiInfoInd,ID_CSS_BAND_SCAN_API_INFO_IND);

    CSS_MEM_CPY_S(  &pstCssBandApiInfoInd->stRatCoverage,
                    sizeof(CSS_RAT_COVERAGE_STRU),
                    pstRatCoverage,
                    sizeof(CSS_RAT_COVERAGE_STRU));
    CSS_MEM_CPY_S(  &pstCssBandApiInfoInd->stBandScanResult,
                    sizeof(CSS_BAND_SCAN_LIST_INFO_STRU),
                    pstBandScanResult,
                    sizeof(CSS_BAND_SCAN_LIST_INFO_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    CSS_SND_MSG(pstCssBandApiInfoInd);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstCssBandApiInfoInd);

    /*释放消息空间*/
    CSS_FREE_MSG(pstCssBandApiInfoInd);

#endif

    return;
}

/*****************************************************************************
 Function Name   : CSS_SendOmMmlUeSupportBandInfoInd
 Description     : 将从MML获取的BAND信息钩到HIDS上
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    wangchen 00209181 2015-05-25  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_SendOmMmlUeSupportBandInfoInd
(
    NAS_MML_MS_BAND_INFO_STRU   *pstUeSupportBand
)
{
    CSS_UE_SUPPORT_BAND_INFO_IND_STRU   *pstUeSupportBandInfoInd = CSS_NULL_PTR;


    /*分配空间并检验分配是否成功*/
    pstUeSupportBandInfoInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_BAND_SCAN_API_INFO_IND_STRU));

    if ( VOS_NULL_PTR == pstUeSupportBandInfoInd )
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_SendOmMmlUeSupportBandInfoInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*清空*/
    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstUeSupportBandInfoInd),
                    CSS_GET_MSG_LENGTH(pstUeSupportBandInfoInd),
                    0,
                    CSS_GET_MSG_LENGTH(pstUeSupportBandInfoInd));

    /*填写消息头*/
    CSS_WRITE_OM_MSG_HEAD(pstUeSupportBandInfoInd,ID_CSS_UE_SUPORT_BAND_INFO_IND);

    CSS_MEM_CPY_S(  &pstUeSupportBandInfoInd->stUeSupportBand,
                    sizeof(CSS_UE_SUPPORT_FREQ_BAND_STRU),
                    (CSS_UE_SUPPORT_FREQ_BAND_STRU*)pstUeSupportBand,
                    sizeof(CSS_UE_SUPPORT_FREQ_BAND_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC测试，将消息发送出去，用于ST验证*/
    CSS_SND_MSG(pstUeSupportBandInfoInd);

#else
    /*消息勾到HSO上*/
    (VOS_VOID)LTE_MsgHook(pstUeSupportBandInfoInd);

    /*释放消息空间*/
    CSS_FREE_MSG(pstUeSupportBandInfoInd);

#endif

    return;
}


/*****************************************************************************
 Function Name   : CSS_ReadNvCommBandPara
 Description     : 读取黄金BAND的BAND NV项
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT32  CSS_ReadNvCommBandConfig
(
    CSS_NV_COMM_BAND_CONFIG_STRU  *pstCssCommBandConfig
)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = CSS_FAIL;

    /* 读NV */
    ulDataLen = sizeof(CSS_NV_COMM_BAND_CONFIG_STRU);
    ulRslt = CSS_NV_Read(EN_NV_ID_PS_COMM_BAND_CONFIG,
                              (VOS_VOID *)pstCssCommBandConfig,
                              ulDataLen);

    if(CSS_RESULT_FAIL == ulRslt)
    {
        CSS_WARN_LOG("CSS_ReadNvCommBandConfig: read NV Fail.");
        TLPS_PRINT2LAYER_WARNING(CSS_ReadNvCommBandConfig_ENUM, LNAS_ReadNvFail);
        return CSS_FAIL;
    }


    return CSS_SUCC;
}

/*****************************************************************************
 Function Name   : CSS_ReadNvRssiThreshold
 Description     : 读取各模下的高能量和可驻留能量门限值
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT32  CSS_ReadNvRssiThreshold
(
    CSS_NV_RAT_RSSI_THRESHOLD_STRU  *pstCssRssiTH
)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = CSS_FAIL;

    /* 读NV */
    ulDataLen = sizeof(CSS_NV_RAT_RSSI_THRESHOLD_STRU);
    ulRslt = CSS_NV_Read(EN_NV_ID_PS_RAT_RSSI_THRESHOLD,
                              (VOS_VOID *)pstCssRssiTH,
                              ulDataLen);

    if(CSS_RESULT_FAIL == ulRslt)
    {
        CSS_WARN_LOG("CSS_ReadNvRssiThreshold: read NV Fail.");
        TLPS_PRINT2LAYER_WARNING(CSS_ReadNvRssiThreshold_ENUM, LNAS_ReadNvFail);

        return CSS_FAIL;
    }

    /* zhaochen 00308719 PCLINT认为乘以64后可能导致精度丢失，实际上阈值不会那么大，故屏蔽 begin 2015-06-29 */
    /*lint -e734*/
    pstCssRssiTH->sGHighRssiThresHold = pstCssRssiTH->sGHighRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sGLowRssiThresHold = pstCssRssiTH->sGLowRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sWHighRssiThresHold = pstCssRssiTH->sWHighRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sWLowRssiThresHold = pstCssRssiTH->sWLowRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sLHighRssiThresHold = pstCssRssiTH->sLHighRssiThresHold * CSS_RSSI_64DB;
    pstCssRssiTH->sLLowRssiThresHold = pstCssRssiTH->sLLowRssiThresHold * CSS_RSSI_64DB;
    /*lint +e734*/

    return CSS_SUCC;
}

VOS_VOID   CSS_FSMTranState
(
    CSS_MAIN_STATE_ENUM_UINT16  enMainState,
    CSS_SUB_STATE_ENUM_UINT16   enSubState
)
{
    /* 将转状态前的状态和转状态后的钩到HIDS上 */
    CSS_SendOmStateChangeInd(CSS_GetCurMainStatus(),
                            CSS_GetCurSubStatus(),
                            enMainState,
                            enSubState);

    TLPS_PRINT2LAYER_INFO1(CSS_FSMTranState_ENUM, LNAS_CSS_GetCurMainStatus, CSS_GetCurMainStatus());
    TLPS_PRINT2LAYER_INFO1(CSS_FSMTranState_ENUM, LNAS_CSS_GetCurSubStatus, CSS_GetCurSubStatus());

    TLPS_PRINT2LAYER_INFO1(CSS_FSMTranState_ENUM, LNAS_CSS_GetDstMainStatus, enMainState);
    TLPS_PRINT2LAYER_INFO1(CSS_FSMTranState_ENUM, LNAS_CSS_GetstSubStatus, enSubState);

    CSS_GetCurMainStatus()               = enMainState;
    CSS_GetCurSubStatus()                = enSubState;

    return;
}

/*****************************************************************************
 Function Name  : CSS_GetTimerLen
 Description    : 获取定时器时长
 Input          : enTimerId--------------定时器类型
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_GetTimerLen
(
    CSS_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    if (TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF == enTimerId)
    {
        return TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF_LEN;
    }

    if (TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF == enTimerId)
    {
        return TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF_LEN;
    }

    if (TI_CSS_WAIT_FOR_SCAN_IND == enTimerId)
    {
        return TI_CSS_WAIT_FOR_SCAN_IND_LEN;
    }

    if (TI_CSS_WAIT_FOR_STOP_SCAN_CNF == enTimerId)
    {
        return TI_CSS_WAIT_FOR_STOP_SCAN_CNF_LEN;
    }
    if (TI_CSS_WAIT_START_BG_SERACH_CNF == enTimerId)
    {
        return TI_CSS_WAIT_START_BG_SEARCH_CNF_LEN;
    }
    return 0;
}

/*****************************************************************************
 Function Name  : CSS_StartTimer()
 Description    : 启动定时器函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_StartTimer(CSS_TIMER_STRU *pstTimer)
{

    if(pstTimer == VOS_NULL_PTR)
    {
        return;
    }

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimer->phTimer)))
        {
            /*打印异常信息*/
            CSS_WARN_LOG("CSS_StartTimer:WARN: stop timer error!");
            TLPS_PRINT2LAYER_WARNING(CSS_StartTimer_ENUM, LNAS_StopTimerErr);
            return;
        }

        /*打印异常信息*/
        CSS_WARN_LOG1("(TimerType) Timer not close!",pstTimer->usName);
        TLPS_PRINT2LAYER_WARNING2(CSS_StartTimer_ENUM, LNAS_TimerNotClose,pstTimer->usName,1);
    }

    if (pstTimer->ulTimerLen == 0)
    {
        /*打印异常信息*/
        CSS_ERR_LOG("CSS_StartTimer:ERROR: start unreasonable timer.");
        TLPS_PRINT2LAYER_WARNING(CSS_StartTimer_ENUM, LNAS_StartUnreasonableTimer);
        return;
    }

    /*设定定时器NAME，打开失败则报警返回*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimer->phTimer),PS_PID_CSS,\
                                pstTimer->ulTimerLen,(VOS_UINT32)pstTimer->usName,\
                                pstTimer->usPara,pstTimer->ucMode))
    {
          /*打印异常信息*/
          CSS_WARN_LOG("CSS_StartTimer:WARN: start timer error!");
          TLPS_PRINT2LAYER_WARNING1(CSS_StartTimer_ENUM, LNAS_StopTimerErr,1);
          return;
    }

    CSS_SndOmTimerStatus(CSS_TIMER_RUNNING, pstTimer->usName, pstTimer->ulTimerLen);

}

/*****************************************************************************
 Function Name  : CSS_StopTimer()
 Description    : 停止定时器函数
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_StopTimer(CSS_TIMER_STRU *pstTimer)
{
    VOS_UINT32                          ulTimerRemainLen    =    0;

    if(pstTimer == VOS_NULL_PTR)
    {
        return;
    }

    /*判断定时器是否打开，已打开则关闭*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        /* 获取当前定时器的剩余时间 */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimer->phTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*关闭失败，则报警返回*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimer->phTimer)))
        {
            /*打印异常信息*/
            CSS_WARN_LOG("CSS_StopTimer:WARN: stop timer error!");
            TLPS_PRINT2LAYER_WARNING(CSS_StopTimer_ENUM, LNAS_StopTimerErr);
            return;
        }

        pstTimer->phTimer = VOS_NULL_PTR;

        CSS_INFO_LOG1("(TimerType) Timer closed!",pstTimer->usName);
        TLPS_PRINT2LAYER_WARNING1(CSS_StopTimer_ENUM, LNAS_TimerClosed,pstTimer->usName);
    }

    CSS_SndOmTimerStatus(CSS_TIMER_STOPED, pstTimer->usName, ulTimerRemainLen);

}
/*****************************************************************************
 Function Name   : CSS_FreeScanRsltMemory
 Description     : 收到COmm 扫频请求时，清空上一次扫频的存储结果；或者在关机时清除
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-05-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_FreeCommScanRsltMemory(VOS_VOID)
{
    CSS_COMM_SCAN_BAND_LIST_STRU         *pRsltList     = CSS_GetCommScanBandListAddr();

    CSS_COMM_SCAN_BAND_NODE_STRU         *pBandNode     = CSS_GetCommScanBandListHeadNode();
    CSS_COMM_SCAN_BAND_NODE_STRU         *ptmpNode;
    VOS_UINT8                             ucNum         = 0;

    while ((CSS_NULL_PTR != pBandNode) && (ucNum < pRsltList->ucBandCount))
    {
        ptmpNode = pBandNode->pstNext;

        if (CSS_NULL_PTR != pBandNode->stBandInfo.pstScanReqArray)
        {
            (VOS_VOID)CSS_MEM_FREE(pBandNode->stBandInfo.pstScanReqArray);
            pBandNode->stBandInfo.pstScanReqArray = CSS_NULL_PTR;
        }
        if (CSS_NULL_PTR != pBandNode->stBandInfo.pstScanRsltArray)
        {
            (VOS_VOID)CSS_MEM_FREE(pBandNode->stBandInfo.pstScanRsltArray);
            pBandNode->stBandInfo.pstScanRsltArray = CSS_NULL_PTR;
        }

        (VOS_VOID)CSS_MEM_FREE(pBandNode);
        pBandNode = CSS_NULL_PTR;

        ucNum += 1;

        pBandNode = ptmpNode;
    }

    pRsltList->ucBandCount           = 0;
    pRsltList->ucCurFreqRangeIdx     = 0;
    pRsltList->pstCurr               = CSS_NULL_PTR;
    pRsltList->pstHead               = CSS_NULL_PTR;
    pRsltList->pstTail               = CSS_NULL_PTR;
}


/*****************************************************************************
 Function Name   : CSS_FreeAsScanRsltMemory
 Description     : 收到as 扫频请求时，清空上一次扫频的存储结果；或者在关机时清除
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID CSS_FreeAsScanRsltMemory(VOS_VOID)
{
    CSS_COMM_SCAN_BAND_LIST_STRU         *pRsltList     = CSS_GetAsScanBandListAddr();

    CSS_COMM_SCAN_BAND_NODE_STRU         *pBandNode     = CSS_GetAsScanBandListHeadNode();
    CSS_COMM_SCAN_BAND_NODE_STRU         *ptmpNode;
    VOS_UINT8                             ucNum         = 0;

    while ((CSS_NULL_PTR != pBandNode) && (ucNum < pRsltList->ucBandCount))
    {
        ptmpNode = pBandNode->pstNext;

        if (CSS_NULL_PTR != pBandNode->stBandInfo.pstScanReqArray)
        {
            (VOS_VOID)CSS_MEM_FREE(pBandNode->stBandInfo.pstScanReqArray);
            pBandNode->stBandInfo.pstScanReqArray = CSS_NULL_PTR;
        }
        if (CSS_NULL_PTR != pBandNode->stBandInfo.pstScanRsltArray)
        {
            (VOS_VOID)CSS_MEM_FREE(pBandNode->stBandInfo.pstScanRsltArray);
            pBandNode->stBandInfo.pstScanRsltArray = CSS_NULL_PTR;
        }

        (VOS_VOID)CSS_MEM_FREE(pBandNode);
        pBandNode = CSS_NULL_PTR;

        ucNum += 1;

        pBandNode = ptmpNode;
    }

    pRsltList->ucBandCount           = 0;
    pRsltList->ucCurFreqRangeIdx     = 0;
    pRsltList->pstCurr               = CSS_NULL_PTR;
    pRsltList->pstHead               = CSS_NULL_PTR;
    pRsltList->pstTail               = CSS_NULL_PTR;
}



VOS_INT32  CSS_PrintCommMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulAtImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulAtImsaMsgNum = sizeof(g_astCssCommMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulAtImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astCssCommMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulAtImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astCssCommMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astCssCommMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astCssCommMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        CSS_WARN_LOG1("IMSA_PrintAtMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(CSS_PrintCommMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}

VOS_INT32  CSS_PrintLphyMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulAtImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulAtImsaMsgNum = sizeof(g_astCssLphyMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulAtImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astCssLphyMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulAtImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astCssLphyMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astCssLphyMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astCssLphyMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        CSS_WARN_LOG1("CSS_PrintLphyMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(CSS_PrintLphyMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}

VOS_INT32  CSS_PrintLmmMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulAtImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulAtImsaMsgNum = sizeof(g_astCssLmmMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* 查找对应的消息 */
    for (ulLoop = 0; ulLoop< ulAtImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astCssLmmMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulAtImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astCssLmmMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astCssLmmMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astCssLmmMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        CSS_WARN_LOG1("CSS_PrintLmmMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(CSS_PrintLmmMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}


VOS_INT32  CSS_PrintTimerMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulTimerType,
    VOS_UINT32                          ulTimerPara
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulCssTimerNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* 获得消息表的长度 */
    ulCssTimerNum = sizeof(g_astCssTimerArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulCssTimerNum; ulLoop++)
    {
        if (g_astCssTimerArray[ulLoop].ulId == ulTimerType)
        {
            break;
        }
    }

    /* 打印对应的消息 */
    if ( ulLoop < ulCssTimerNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astCssTimerArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        /* 打印消息的每个数据*/
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " ulPara = %d \r\n",
                           ulTimerPara,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        CSS_WARN_LOG1("CSS_PrintTimerMsg, Invalid Timer Type: ",ulTimerType);
        TLPS_PRINT2LAYER_WARNING1(CSS_PrintTimerMsg_ENUM, LNAS_InvalidTimerType, ulTimerType);
    }

    return (usTotalLen - usOffset);

}


VOS_VOID CSS_PrintCssRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "CSS Receive Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        CSS_WARN_LOG("CSS_PrintCssRevMsg, Print receive msg header exception.");
        TLPS_PRINT2LAYER_WARNING(CSS_PrintCssRevMsg_ENUM, LNAS_FUNCTION_LABEL1);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulSenderPid )
    {
        case PS_PID_HPA:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "LPHY-->CSS\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintLphyMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "LMM-->CSS\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintLmmMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case WUEPS_PID_MMC:
        case PS_PID_ERRC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "COMM-->CSS\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintCommMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case VOS_PID_TIMER:

            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TIMER-->IMSA\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintTimerMsg(pcBuff,
                                            usTotalLen,
                                            ((REL_TIMER_MSG *)(VOS_VOID *)pstMsg)->ulName,
                                            ((REL_TIMER_MSG *)(VOS_VOID *)pstMsg)->ulPara);
            break;

        default:
            CSS_WARN_LOG2("CSS_PrintCssRevMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulSenderPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_WARNING2(CSS_PrintCssRevMsg_ENUM, LNAS_InvalidPid, pstMsg->ulSenderPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        CSS_WARN_LOG2("CSS_PrintCssRevMsg, print return zero length.SenderPid, MsgId: ",
                      pstMsg->ulSenderPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING2(CSS_PrintCssRevMsg_ENUM, LNAS_FUNCTION_LABEL2, pstMsg->ulSenderPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}

VOS_VOID CSS_PrintCssSendMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "CSS SEND Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        CSS_WARN_LOG("CSS_PrintCssSendMsg, Print send msg header exception.");
        TLPS_PRINT2LAYER_WARNING(CSS_PrintCssSendMsg_ENUM, LNAS_FUNCTION_LABEL1);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* 打印各个PID的消息 */
    switch ( pstMsg->ulReceiverPid )
    {
        case PS_PID_HPA:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "CSS-->LPHY\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintLphyMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case PS_PID_MM:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "CSS-->LMM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintLmmMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case WUEPS_PID_MMC:
        case PS_PID_ERRC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "CSS-->COMM\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = CSS_PrintCommMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        default:
            CSS_WARN_LOG2("CSS_PrintCssRevMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulReceiverPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_WARNING2(CSS_PrintCssSendMsg_ENUM, LNAS_InvalidPid, pstMsg->ulReceiverPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        CSS_WARN_LOG2("CSS_PrintCssRevMsg, print return zero length.ReceiverPid, MsgId: ",
                      pstMsg->ulReceiverPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING2(CSS_PrintCssSendMsg_ENUM, LNAS_FUNCTION_LABEL2, pstMsg->ulReceiverPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}


VOS_VOID CSS_ClearLocalResource(VOS_VOID)
{

    /* 存储COMM扫频结果的空间释放 */
    CSS_FreeCommScanRsltMemory();

    /* 存储AS扫频结果的空间释放 */
    CSS_FreeAsScanRsltMemory();

    /* 全局变量初始化 */
    CSS_MEM_SET_S(&g_stCssControl, sizeof(CSS_CONTROL_STRU), 0, sizeof(CSS_CONTROL_STRU));
}

VOS_VOID CSS_Send_Msg(VOS_VOID* pMsg)
{
    CSS_PrintCssSendMsg((const PS_MSG_HEADER_STRU *)pMsg,CSS_GET_CSS_PRINT_BUF());
    if(VOS_OK != PS_SND_MSG_ALL_CHECK(PS_PID_CSS , pMsg))
    {
        CSS_ERR_LOG("CSS_Send_Msg:Msg Snd Err!");
        TLPS_PRINT2LAYER_ERROR(CSS_Send_Msg_ENUM, LNAS_MsgSndErr);
    }

}

/*****************************************************************************
 Function Name   : CSS_SecuMemCpy
 Description     : 安全memcpy
 Input           : VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_VOID* pSrc,
                   VOS_UINT32  ulLength, VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID
 Output          : None
 Return          : VOS_INT32

 History         :
    1.z00297373    2015-12-28  Draft Enact
*****************************************************************************/
VOS_INT32 CSS_SecuMemCpy
(
    VOS_VOID           *pDst,
    VOS_UINT32          ulMaxBuffer,
    const VOS_VOID     *pSrc,
    VOS_UINT32          ulLength,
    VOS_UINT32          ulLineNO,
    VOS_UINT32          ulFileID
)
{
    /*如果源地址和目的地址重叠，需改用TLPS_MEM_MOVE_S，否则安全拷贝失败 */
    if(( (pSrc > pDst) && ((VOS_UINT8 *)pSrc <= ((VOS_UINT8 *)pDst + ulMaxBuffer)) )
        ||((pDst> pSrc) && ((VOS_UINT8 *)pDst <= ((VOS_UINT8 *)pSrc + ulLength)))
        || (pSrc == pDst))
    {
        return TLPS_MEM_MOVE_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
    else
    {
        return TLPS_MEM_CPY_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
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



