/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLppMtaMsgProc.c
    Description : 处理EMM发给SM的消息
    History     :
    1. lifuxin 00253982 2015-7-7 新开发
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "PsTypeDef.h"
#include    "NasLppMtaMsgProc.h"
#include    "LppMtaInterface.h"
#include    "NasLppPublic.h"
#include    "OmCommon.h"
#include    "NasLppOm.h"
#include    "NasLppEncode.h"
#include    "NasLppLrrcMsgProc.h"
#include    "NasLppSendMsg.h"
#include    "NasLppEmmMsgProc.h"
#include    "NasLppIntraMsgProc.h"
#include    "LcsLppInterface.h"

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPMTAMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPMTAMSGPROC_C

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
#if (FEATURE_LPP == FEATURE_ON)



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_LPP_GetOneRunningTransWaitGnssCapCnf
 Description    : 得到一个transaction正在running 等待GNSS能力回复
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
    1. lifuxin 00253982 2015-10-24 新开发
*****************************************************************************/
 VOS_BOOL   NAS_LPP_GetOneRunningTransWaitGnssCapCnf( VOS_UINT8  *pucTransIndx)
 {
    VOS_UINT8                                  ucLoop              = 0;
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU       *psTransEntityPool   = NAS_LPP_NULL_PTR;

    psTransEntityPool = NAS_LPP_GetLppTransEntityPool();

    for(ucLoop = 0; ucLoop < NAS_LPP_MAX_TRANS_POOL_COUNT; ucLoop++)
    {
        /*lint -e701*/
        if(0 != ( psTransEntityPool->ulTransBitmap & (0x01<<ucLoop) ) )
        /*lint +e701*/
        {
            if((LPP_MS_CAPABILITY == psTransEntityPool->astTransElementEntity[ucLoop].enLppMainState)
               && (LPP_SS_CAP_REQ_WAIT_CNF == psTransEntityPool->astTransElementEntity[ucLoop].enLppSubState))
            {
                *pucTransIndx  = ucLoop;
                return PS_TRUE;
            }
        }
    }

    return PS_FALSE;
 }

/*****************************************************************************
 Function Name  : NAS_LPP_GetSessionIndxAndSesssionTransIndxByTransIndx
 Description    : 通过transactionIndx找到对应的sessionIndx以及SessionTransaIndx
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
    1. lifuxin 00253982 2015-10-24 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_GetSessionIndxAndSesssionTransIndxByTransIndx
(
    VOS_UINT8                           ucTransIndx,
    VOS_UINT8                          *pucSessionIndx,
    VOS_UINT8                          *pucSessionTransIndx
)
{
    VOS_UINT8                                   ucLoopSession       = 0;
    VOS_UINT8                                   ucLoopTrans         = 0;
    NAS_LPP_SESSION_ENTITY_POOL_STRU           *pstSessionEntityPool= NAS_LPP_NULL_PTR;


    *pucSessionIndx         = PS_NULL_UINT8;
    *pucSessionTransIndx    = PS_NULL_UINT8;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    for(ucLoopSession = 0; ucLoopSession < NAS_LPP_MAX_SESSION_COUNT; ucLoopSession++)
    {
    /*lint -e701*/
        if(0 != ( (pstSessionEntityPool->ulSessionActiveBitmap) & (0x01 <<  ucLoopSession) ) )
    /*lint +e701*/
        {
            for(ucLoopTrans = 0; ucLoopTrans < NAS_LPP_MAX_TRANS_COUNT; ucLoopTrans++)
            {
                if(ucTransIndx == pstSessionEntityPool->astLppSessionEntity[ucLoopSession].stLppTrans.aucTransElementIdx[ucLoopTrans])
                {
                    *pucSessionIndx         = ucLoopSession;
                    *pucSessionTransIndx    = ucLoopTrans;
                     return;
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_RcvMtaLppGnssCapCnf
 Description    : LPP模块Mta消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
    1. wangensheng 00324863 2015-10-19 新开发
*****************************************************************************/
 VOS_VOID   NAS_LPP_RcvMtaLppGnssCapCnf
 (
    MTA_LPP_GNSS_PROVIDE_CAPABITY_CNF_STRU                *pstMtaLppGnssProvideCap
 )
 {
    VOS_UINT8                                   ucSessionIndx       = 0;
    VOS_UINT8                                   ucTransIndx         = 0;
    VOS_UINT8                                   ucSessionTransIndx  = 0;
    VOS_BOOL                                    bHaveWaitGnssCapTrans = PS_FALSE;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity      = NAS_LPP_NULL_PTR;
    NAS_LPP_ENTITY_STRU                        *pstLppEntity        = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_HEAD_STRU                       stLppMsgHead        = {0};
    VOS_UINT32                                  ulSessionId         = 0;
    VOS_UINT8                                   ucRslt              = 0;
    NAS_LPP_TRANS_ID_STRU                       stTransId          = {0};

    NAS_LPP_NORM_LOG("NAS_LPP_RcvMtaLppGnssCapCnf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaLppGnssCapCnf_ENUM, LNAS_RCV_MTA_GNSS_CAP_CNF);

    /* TODO:MEM */
    /* 将接收到的数据存储到LPP ENTITY中 */
    pstLppEntity = NAS_LPP_GetLppEntityCtx();
    NAS_LPP_MEM_CPY_S(  &pstLppEntity->stStructDataForGnss.stMtaLppGnssCap,
                        sizeof(MTA_LPP_AGNSS_PROVIDE_CAP_STRU),
                        &pstMtaLppGnssProvideCap->stGnssProvideCap,
                        sizeof(MTA_LPP_AGNSS_PROVIDE_CAP_STRU));
    pstLppEntity->stStructDataForGnss.bGnssCapbilityFlag = PS_TRUE;

    bHaveWaitGnssCapTrans = NAS_LPP_GetOneRunningTransWaitGnssCapCnf(&ucTransIndx);
    if(PS_TRUE == bHaveWaitGnssCapTrans)
    {
        /*进入这个分支表示当前有一个transaction正在等待GNSS的能力回复, 则开始组织provide能力消息*/
        NAS_LPP_GetSessionIndxAndSesssionTransIndxByTransIndx(ucTransIndx,
                                                              &ucSessionIndx,
                                                              &ucSessionTransIndx);
        if((PS_NULL_UINT8 != ucSessionIndx) && (PS_NULL_UINT8 != ucSessionTransIndx))
        {
            stLppMsgHead.stTransactionId.enInitiator =
                pstLppEntity->stTransEntityPool.astTransElementEntity[ucTransIndx].stTransId.enInitiator;
            stLppMsgHead.stTransactionId.ucTransactionNumber =
                pstLppEntity->stTransEntityPool.astTransElementEntity[ucTransIndx].stTransId.ucTransactionNumber;
            ulSessionId = pstLppEntity->stSessionEntityPool.astLppSessionEntity[ucSessionIndx].ulSessionId;

            /*回复ProvideCapbility消息*/
            ucRslt = NAS_LPP_SndUplinkProvideCapbilityMsg(&stLppMsgHead, ulSessionId,ucTransIndx);
            if(NAS_LPP_SUCCESS != ucRslt)
            {
                stTransId.enInitiator = stLppMsgHead.stTransactionId.enInitiator;
                stTransId.ucTransactionNumber = stLppMsgHead.stTransactionId.ucTransactionNumber;
                NAS_LPP_ReleaseTransactionOrSession(ucSessionIndx,
                                                    ucSessionTransIndx,
                                                    &stTransId);
                return;
            }

            pstTransEntity = &(NAS_LPP_GetLppTransEntityPool()->astTransElementEntity[ucTransIndx]);

            /*表示当前transaction如果收到网络侧的ACK之后，就可以结束了*/
            pstTransEntity->ucTransEndFlag   = PS_TRUE;

            /*记录当前发送的空口消息，用于收到网络侧的消息之后决定转到什么状态*/
            pstTransEntity->enLastUpMsgId    = NAS_LPP_AIR_MSG_PROVIDE_CAP;

            /*转状态,转到能力交互，子状态等内部的data cnf，也就是确认把空口消息发送到了基站, 同时启动等待相应的定时器*/
            NAS_LPP_ChangeTransFsmState(ucSessionIndx,
                                        ucSessionTransIndx,
                                        LPP_MS_CAPABILITY,
                                        LPP_SS_WAIT_INTRA_DATA_CNF);
        }
    }
    else
    {
        /*表示当前没有GNSS的能力请求，为开机主动请求GNSS能力的回复*/
        /* 停止定时器 */
        NAS_LPP_TimerStop(NAS_LPP_TIMER_INVAILD_PARA,
                          NAS_LPP_TIMER_INVAILD_PARA,
                          TI_NAS_LPP_WAIT_GNSS_CAP_CNF);
    }
 }

/*****************************************************************************
Function Name  : NAS_LPP_ResetGnssMeasRslt
Description    : 清空当前GNSS的测量信息
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_ResetGnssMeasRslt
(
    NAS_LPP_GNSS_MEAS_RESLT_STRU           *pstGnssMeasRslt
)
{
    VOS_UINT32                  ulLoop = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_ResetGnssMeasRslt is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ResetGnssMeasRslt_ENUM, LNAS_LPP_Func_Enter);

    /*没有来过GNSS的测量ind*/
    if(pstGnssMeasRslt->bHaveGnssMeasFlag == PS_FALSE)
    {
        NAS_LPP_MEM_SET_S(pstGnssMeasRslt,sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU), 0, sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU));
        for(ulLoop = 0; ulLoop < LPP_MAX_VALID_GNSS_POSITION_TECH; ulLoop++)
        {
            pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.pastGNSSMeasListArray[ulLoop] = NAS_LPP_NULL_PTR;
        }

        return;
    }

    /*已经有了GNSS的测量ind*/
    /*循环释放的内存是MTA申请的，在存储本地的GNSS的测量信息的时候复用了这段内存, free的时机:
      1. 当有新的GNSS meas ind来的时候需要释放
      2. 当transaction，session释放的时候需要释放
    */
    if (LPP_MAX_VALID_GNSS_POSITION_TECH <= pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.ulGNSSMeasListCnt)
    {
        pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.ulGNSSMeasListCnt = LPP_MAX_VALID_GNSS_POSITION_TECH;
    }

    for(ulLoop = 0; ulLoop < pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.ulGNSSMeasListCnt; ulLoop++)
    {
        NAS_LPP_MEM_FREE(pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.pastGNSSMeasListArray[ulLoop]);
    }
    NAS_LPP_MEM_SET_S(pstGnssMeasRslt,sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU), 0, sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU));

    return;
}
/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppGnssLocInfoInd
Description    : LPP模块Mta消息处理函数位置测量IND消息
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. wangensheng 00324863 2015-10-20 新开发
*****************************************************************************/
VOS_VOID NAS_LPP_SndRrcMtaGnssLocInfo
(
     MTA_LPP_GNSS_RROVIDE_LOCATION_INFO_IND_STRU          *pstMtaLppGnssProvideLocInfoInd
)
{

    MTA_LPP_MEAS_REF_TIME_STRU             *pstMtaLppMeasRefTime    = NAS_LPP_NULL_PTR;
    LOC_COM_VELOCITY_STRU                  *pstVelocityEstimate     = NAS_LPP_NULL_PTR;
    LOC_COM_COORDINATE_STRU                *pstLocationEstimate     = NAS_LPP_NULL_PTR;
    LPP_LRRC_INFO_FLAG_ENUM_UINT8           ucGnssDataFlag          = LPP_LRRC_INFO_FLAG_VALID;

    /* 停止位置信息失效定时器 */
    NAS_LPP_TimerStop(NAS_LPP_TIMER_INVAILD_PARA,
                      NAS_LPP_TIMER_INVAILD_PARA,
                      TI_NAS_LPP_LOCATION_INVALID);

    /* 发给RRC的位置信息组织数据 */
    if (NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->bitCommonInfo)
    {
        if ( NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo.bitOpLocationEstimate)
        {
            pstLocationEstimate = &pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo.stLocationEstimate;
        }

        if ( NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo.bitOpVelocityEstimate)
        {
            pstVelocityEstimate= &pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo.stVelocityEstimate;
        }
    }

    if (NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->bitAgnssInfo)
    {
        if ( NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->stGnssReqLocationInfo.bitOpGNSSLocationInfo)
        {
            pstMtaLppMeasRefTime = &pstMtaLppGnssProvideLocInfoInd->stGnssReqLocationInfo.stGNSSLocationInfo.stMeasRefTime;
        }
    }

    NAS_LPP_SndLppLrrcLocationInfo(pstMtaLppMeasRefTime, pstVelocityEstimate, pstLocationEstimate, ucGnssDataFlag);
    /* 启动 GNSS LOC INFO 定时器 */
    NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                       NAS_LPP_TIMER_INVAILD_PARA,
                       TI_NAS_LPP_LOCATION_INVALID);
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppGnssLocInfoInd
Description    : LPP模块Mta消息处理函数位置测量IND消息
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_RcvMtaLppGnssLocInfoInd
(
    MTA_LPP_GNSS_RROVIDE_LOCATION_INFO_IND_STRU          *pstMtaLppGnssProvideLocInfoInd
)
{
    NAS_LPP_GNSS_MEAS_RESLT_STRU           *pstGnssMeasRslt         = NAS_LPP_NULL_PTR;
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLocTechMap           = NAS_LPP_NULL_PTR;
    VOS_UINT8                               ucCfgTableIndex         = PS_NULL_UINT8;
    NAS_LPP_COMM_CONFIG_INFO_STRU          *pstCommCfgInfo          = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaLppGnssLocInfoInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaLppGnssLocInfoInd_ENUM, LNAS_LPP_Func_Enter);

    /*获取存储的测量结果的地址*/
    pstGnssMeasRslt = NAS_LPP_GetGnssMeasRsltAddr();

    /*清空测量结果*/
    NAS_LPP_ResetGnssMeasRslt(pstGnssMeasRslt);

    /*保存GNSS 测量IND消息到全局结构*/
    pstGnssMeasRslt->bHaveGnssMeasFlag = PS_TRUE;
    pstGnssMeasRslt->bitCommonInfo  = pstMtaLppGnssProvideLocInfoInd->bitCommonInfo;
    pstGnssMeasRslt->bitAgnssInfo   = pstMtaLppGnssProvideLocInfoInd->bitAgnssInfo;
    if(NAS_LPP_SLCT == pstGnssMeasRslt->bitCommonInfo)
    {
        NAS_LPP_MEM_CPY_S(&(pstGnssMeasRslt->stCommonProvideLocInfo),
                        sizeof(MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU),
                        &(pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo),
                        sizeof(MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU));
    }

    if(NAS_LPP_SLCT == pstGnssMeasRslt->bitAgnssInfo)
    {
        NAS_LPP_MEM_CPY_S(&(pstGnssMeasRslt->stGnssReqLocationInfo),
                        sizeof(MTA_LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU),
                        &(pstMtaLppGnssProvideLocInfoInd->stGnssReqLocationInfo),
                        sizeof(MTA_LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU));
    }

    /* 发送给RRC MTA的位置信息 */
    NAS_LPP_SndRrcMtaGnssLocInfo(pstMtaLppGnssProvideLocInfoInd);

    /*如果是上报一次的场景，而且当前transaction只有一种定位场景或者
    多种定位技术，除开GNSS之外的其他测量值已经有了，都需要主动上报位置信息*/
    /*获取running表*/
    pstLocTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_GNSS);
    if(NAS_LPP_NULL_PTR == pstLocTechMap)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvMtaLppGnssLocInfoInd: Can't find the running table of GNSS");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvMtaLppGnssLocInfoInd_ENUM, LNAS_LPP_CannotFindGnssRunningTable);

        return;
    }

    /*获取公共配置池*/
    ucCfgTableIndex = NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[pstLocTechMap->ucTransIndx].ucCommCfgIndex;
    pstCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(ucCfgTableIndex);
    if(NAS_LPP_NULL_PTR == pstCommCfgInfo)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvMtaLppGnssLocInfoInd: Can't find the Comm Cfg Pool");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvMtaLppGnssLocInfoInd_ENUM, LNAS_LPP_CannotFindCommCfgPool);
        return;
    }

    /*对于GNSS的定位技术有两种上报方式， 一是once， 一是周期性上报，上报once场景
    有两种情况在这个地方需要上报位置测量信息， 一是只有一种定位技术，另外一个是
    有多种定位技术在同一个transaction的场景，如果测量信息都来了则需要上报， 对于
    周期性上报的场景，不再这里上报，同一等待周期性定时器超时的时候处理。
    */
    if(NAS_LPP_REPORT_LOCATION_TYPE_ONCE == pstCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ReportOnceProcess(pstLocTechMap->ucSessionIndx,
                                  pstLocTechMap->ucSessionTranIndx,
                                  pstLocTechMap->ucTransIndx);
    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_GetOneSessionIndx
Description    : 找到一个正在running的session，返回sessionIndx
Input          :
Output         : VOS_VOID
Return Value   : sessionIndx

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_UINT8   NAS_LPP_GetOneRunningSessionIndx( VOS_VOID )
{
    VOS_UINT8                   ucLoop      = 0;
    NAS_LPP_ENTITY_STRU        *pstLppCtx   = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_GetOneRunningSessionIndx is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_GetOneRunningSessionIndx_ENUM, LNAS_LPP_Func_Enter);

    pstLppCtx = NAS_LPP_GetLppEntityCtx();
    for(ucLoop = 0; ucLoop < NAS_LPP_MAX_SESSION_COUNT; ucLoop++)
    {
        /*lint -e701*/
        if((0 != ((pstLppCtx->stSessionEntityPool.ulSessionActiveBitmap) & (0x01<<ucLoop)))
        /*lint +e701*/
         &&(NAS_LPP_MAX_TRANS_COUNT >= pstLppCtx->stSessionEntityPool.astLppSessionEntity[0].stLppTrans.ucTransIdCount))
        {
            return ucLoop;
        }
    }

    return PS_NULL_UINT8;
}

/*****************************************************************************
Function Name  : NAS_LPP_SndLcsGnssAssistDataReq
Description    : 发送GNSS辅助数据的码流到LCS
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-22 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_SndLcsGnssAssistDataReq
(
    VOS_UINT8                                  *pucEncodeOutMsg,
    VOS_UINT32                                  ulLppMsgLen
)
{
    VOS_UINT32                          ulTmpLength     = 0;
    LPP_LCS_GNSS_ASSISTDATA_REQ_STRU   *pstLcsAssistDataReq   = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SndLcsGnssAssistDataReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndLcsGnssAssistDataReq_ENUM, LNAS_LPP_Func_Enter);

    /*根据空口消息的长度分配空间*/
    if( 0 == ulLppMsgLen)
    {
        NAS_LPP_WARN_LOG("NAS_LPP_SndLcsGnssAssistDataReq: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndLcsGnssAssistDataReq_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }
    else if(ulLppMsgLen > NAS_LPP_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLppMsgLen - NAS_LPP_MIN_SND_MSG_LEN ;
        pstLcsAssistDataReq = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_LCS_GNSS_ASSISTDATA_REQ_STRU) + ulTmpLength);
    }
    else/*如果长度小于NAS_LPP_MIN_SND_MSG_LEN，分配的空间等于NAS_LPP_MIN_SND_MSG_LEN*/
    {
        pstLcsAssistDataReq = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_LCS_GNSS_ASSISTDATA_REQ_STRU));
    }

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstLcsAssistDataReq)
    {
        /*打印异常信息*/
        NAS_LPP_ERR_LOG("NAS_LPP_SndLcsGnssAssistDataReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndLcsGnssAssistDataReq_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }

    /*填写空口消息头长度*/
    pstLcsAssistDataReq->ulLppMsgSize = ulLppMsgLen;

    /*将空口消息存放到ID_LPP_LCS_GNSS_ASSISTDATA_REQ结构中*/
    /*lint -e669*/
    NAS_LPP_MEM_CPY_S(pstLcsAssistDataReq->aucLppMsg,ulLppMsgLen, pucEncodeOutMsg, ulLppMsgLen);
    /*lint +e669*/

    /*填写消息头*/
    NAS_LPP_WRITE_LCS_MSG_HEAD(pstLcsAssistDataReq, ID_LPP_LCS_GNSS_ASSISTDATA_REQ);

    /*调用消息发送函数 */
    NAS_LPP_SND_MSG(pstLcsAssistDataReq);
}

/*****************************************************************************
Function Name  : NAS_LPP_EncodeGnssAssistReq
Description    : 产生辅助数据的码流
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-22 新开发
*****************************************************************************/
VOS_UINT32   NAS_LPP_EncodeGnssAssistDataReq
(
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU          *pstMtaLppGnssAssistDataReq,
    VOS_UINT8                                  *pucEncodeOutMsg,
    VOS_UINT32                                 *pulLppMsglen
)
{
    LPP_MESSAGE_STRU                       *pstReqAssistData        = NAS_LPP_NULL_PTR;
    LPP_REQUEST_ASSIST_DATA_R9_IES_STRU    *pstRequestAsisstDataR9  = NAS_LPP_NULL_PTR;
    NAS_LPP_SERVING_CELL_STRU              *pstServingCell          = NAS_LPP_NULL_PTR;
    VOS_UINT16                              usRslt                  = 0;
    VOS_UINT16                              usBitPos                = 0;
    VOS_UINT32                              ulLppMsgLen             = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_EncodeGnssAssistDataReq is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeGnssAssistDataReq_ENUM, LNAS_LPP_Func_Enter);

    /*获取LPP MSG BUFF*/
    pstReqAssistData = NAS_LPP_GetLppMsgBuff();
    NAS_LPP_MEM_SET_S(pstReqAssistData,sizeof(LPP_MESSAGE_STRU), 0, sizeof(LPP_MESSAGE_STRU));

    pstServingCell = NAS_LPP_GetServingCell();
    pstReqAssistData->bitOpLppTransactionId = NAS_LPP_NO_SLCT;
    pstReqAssistData->bitOpSequenceNumber   = NAS_LPP_SLCT;
    pstReqAssistData->bitOpLppMessageBody   = NAS_LPP_SLCT;
    pstReqAssistData->bitOpAcknowledgement  = NAS_LPP_SLCT;

    pstReqAssistData->stAcknowledgement.bAckRequested = VOS_FALSE;

    pstReqAssistData->bEndTransaction = VOS_FALSE;

    pstReqAssistData->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();

    pstReqAssistData->stLppMessageBody.ulChoice = LPP_C1_MESSAGE_BODY_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.ulChoice = LPP_SUPPORT_MESSAGE_BODY_PEQUEST_ASSISTANCE_DATA_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.ulChoice = LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.u.stC1.ulChoice = LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_R9_CHOSEN;
    pstRequestAsisstDataR9 = &pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.u.stC1.u.stRequestAssitDataR9;

    pstRequestAsisstDataR9->bitOpCommonIEsRequestAssitData = NAS_LPP_SLCT;
    pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.bitOpPrimaryCellID = NAS_LPP_SLCT;
    pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.stPrimaryCellID.ulCellIdentity = pstServingCell->ulCellIdentity;
    NAS_LPP_NasPlmn2LppPlmn(pstServingCell->aucPlmnId,
                         &pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.stPrimaryCellID.stPlmnIdentity);

     NAS_LPP_PreGnssAssistDataParameter(pstMtaLppGnssAssistDataReq, pstRequestAsisstDataR9);

    /*开始编码*/
    usRslt = NAS_LPP_EncodeMessage(pstReqAssistData,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
         NAS_LPP_ERR_LOG(" Encode assist data msg Fail!");
         TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeGnssAssistDataReq_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
         return NAS_LPP_FAILURE;
    }

    /*HIDS air msg */
    NAS_LPP_SendOmtAirMsg(NAS_LPP_OMT_AIR_MSG_UP,
                          LNAS_LPP_REQ_ASSIST_DATA,
                          ulLppMsgLen,
                          pucEncodeOutMsg);

    ulLppMsgLen     = usBitPos/8;
    *pulLppMsglen   = ulLppMsgLen;

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle
Description    : LPP模块MtaGnssAssistDataReq的处理，当前没有正在running的Session
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-22 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle
(
        MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU          *pstMtaLppGnssAssistDataReq
)
{
    VOS_UINT8                               *pucEncodeOutMsg  = NAS_LPP_NULL_PTR;
    VOS_UINT32                               ulLppMsgLen      = 0;
    VOS_UINT32                               ulRslt           = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle_ENUM, LNAS_LPP_Func_Enter);

    /*分配编码之后码流的存储空间*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(NAS_LPP_MAX_LCS_ASSIST_DATA_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        NAS_LPP_ERR_LOG("enocde up error  Alloc Mem Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    /*清空*/
    NAS_LPP_MEM_SET_S(pucEncodeOutMsg,NAS_LPP_MAX_LCS_ASSIST_DATA_BUFF_MSG_LEN, 0, NAS_LPP_MAX_LCS_ASSIST_DATA_BUFF_MSG_LEN);

    /*得到GNSS请求辅助数据的码流*/
    ulRslt = NAS_LPP_EncodeGnssAssistDataReq(pstMtaLppGnssAssistDataReq, pucEncodeOutMsg, &ulLppMsgLen);
    if(NAS_LPP_FAILURE == ulRslt)
    {
        NAS_LPP_MEM_FREE(pucEncodeOutMsg);
        return;
    }

    /*发送辅助数据请求给LCS*/
    NAS_LPP_SndLcsGnssAssistDataReq(pucEncodeOutMsg, ulLppMsgLen);

    NAS_LPP_MEM_FREE(pucEncodeOutMsg);

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppGnssAssistDataReq
Description    : LPP模块MtaGnssAssistDataReq的处理
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 新开发
*****************************************************************************/
VOS_VOID   NAS_LPP_RcvMtaLppGnssAssistDataReq
(
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU          *pstMtaLppGnssAssistDataReq
)
{
    VOS_UINT8                       ucSessionIndx   = 0;
    NAS_LPP_CONFIG_PARA_STRU       *pstCfgPara      = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaLppGnssAssistDataReq is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaLppGnssAssistDataReq_ENUM, LNAS_LPP_Func_Enter);

    pstCfgPara = NAS_LPP_GetCfgPara();

    ucSessionIndx = NAS_LPP_GetOneRunningSessionIndx();
    if(PS_NULL_UINT8 != ucSessionIndx)
    {
        /* 对冲处理，MTA即将要请求辅助数据的时候，已经有一个transaction正在下发GNSS的辅助数据流程,
          直接return，不用发送辅助数据请求 */
        if(pstCfgPara->bitGnssAssisChng)
        {
            NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaLppGnssAssistDataReq: Have Gnss AssistData Process");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvMtaLppGnssAssistDataReq_ENUM, LNAS_LPP_HaveGnssAssistDataProcess);
            return;
        }

        /*能找到正在running的session,直接发送上行的辅助数据请求消息*/
        NAS_LPP_CreatNewTransAndReqAssistData(ucSessionIndx, VOS_FALSE, VOS_TRUE, pstMtaLppGnssAssistDataReq);
    }
    else
    {
        /* 不能找到正在running的session，则将辅助数据请求消息发送给LCS */
        NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle(pstMtaLppGnssAssistDataReq);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_MtaMsgDistr
 Description    : LPP模块Mta消息处理函数
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
    1. lifuxin 00253982 2015-7-7 新开发
*****************************************************************************/
VOS_VOID NAS_LPP_MtaMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pMtaMsg  = VOS_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_MtaMsgDistr is entered!");
    TLPS_PRINT2LAYER_ERROR(NAS_LPP_MtaMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    pMtaMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pMtaMsg->ulMsgName)
    {
        /*信令面*/
        case ID_MTA_LPP_GNSS_CAP_CNF:
            NAS_LPP_RcvMtaLppGnssCapCnf( (MTA_LPP_GNSS_PROVIDE_CAPABITY_CNF_STRU *)pMtaMsg);
            break;

        case ID_MTA_LPP_GNSS_LOC_INFO_IND:
            NAS_LPP_RcvMtaLppGnssLocInfoInd( (MTA_LPP_GNSS_RROVIDE_LOCATION_INFO_IND_STRU *)pMtaMsg);
            break;

        case ID_MTA_LPP_GNSS_ASSISTDATA_REQ:
            NAS_LPP_RcvMtaLppGnssAssistDataReq((MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU*)pMtaMsg);
            break;

        /*用户面*/
        case ID_MTA_LPP_UP_CAP_REQ:
            NAS_LPP_RcvMtaLppUpCapReq((MTA_LPP_UP_CAPABILITY_REQ_STRU*)pMtaMsg);
            break;

        case ID_MTA_LPP_UP_MEAS_NTY:
            NAS_LPP_RcvMtaLppUpMeasNotify((MTA_LPP_UP_MEAS_NTY_STRU*)pMtaMsg);
            break;

        case ID_MTA_LPP_UP_OTDOA_ASSIST_DATA_NTY:
            NAS_LPP_UpRcvMtaOtdoaAssistData((MTA_LPP_UP_OTDOA_ASSIST_DATA_NTY_STRU*)pMtaMsg);
            break;

        case ID_MTA_LPP_UP_MEAS_ABORT_NTY:
            NAS_LPP_RcvMtaLppUpAbortMeas((MTA_LPP_UP_MEAS_ABORT_NTY_STRU *)pMtaMsg);
            break;

        default:
            NAS_LPP_INFO_LOG("NAS_LPP_MtaMsgDistr: Msg Id Error");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_MtaMsgDistr_ENUM, LNAS_LPP_TaskEntryNoThisMsg);
            break;
    }
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasLppMtaMsgProc.c */
