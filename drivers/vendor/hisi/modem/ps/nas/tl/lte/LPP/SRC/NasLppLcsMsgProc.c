

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "PsTypeDef.h"
#include    "LcsLppInterface.h"
#include    "NasLppPublic.h"
#include    "NasLppSendMsg.h"
#include    "LocCommonInterface.h"
#include    "LPPLRrcInterface.h"

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPLCSMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPLCSMSGPROC_C

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


VOS_VOID NAS_LPP_RcvGnssLocationInfo( LCS_LPP_LOCATION_INFO_NTF_STRU *pstLcsLppLocInfo )
{

    MTA_LPP_MEAS_REF_TIME_STRU                             *pstMtaLppMeasRefTime = NAS_LPP_NULL_PTR;
    LOC_COM_VELOCITY_STRU                                  *pstVelocityEstimate = NAS_LPP_NULL_PTR;
    LOC_COM_COORDINATE_STRU                                *pstLocationEstimate = NAS_LPP_NULL_PTR;
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                           enGnssDataFlag = LPP_LRRC_INFO_FLAG_VALID;

    /* 先停止位置信息的定时器 */
    NAS_LPP_TimerStop(NAS_LPP_TIMER_INVAILD_PARA,
                      NAS_LPP_TIMER_INVAILD_PARA,
                      TI_NAS_LPP_LOCATION_INVALID);

    /* 设置编码给LRRC的结构数据 */
    if (NAS_LPP_SLCT == pstLcsLppLocInfo->bitOpLocationEstimate)
    {
        pstLocationEstimate = &pstLcsLppLocInfo->stLocationEstimate;
    }

    if (NAS_LPP_SLCT == pstLcsLppLocInfo->bitOpVelocityEstimate)
    {
        pstVelocityEstimate = &pstLcsLppLocInfo->stVelocityEstimate;
    }

    NAS_LPP_SndLppLrrcLocationInfo( pstMtaLppMeasRefTime, pstVelocityEstimate,  pstLocationEstimate, enGnssDataFlag);

    /* 启动 GNSS LOC INFO 定时器 */
    NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                       NAS_LPP_TIMER_INVAILD_PARA,
                       TI_NAS_LPP_LOCATION_INVALID);
}


VOS_VOID NAS_LPP_RcvGnssAssistDataCnf( LCS_LPP_GNSS_ASSISTDATA_CNF_STRU *pstGnssAssistDataCnf )
{
    /*TODO: 根据最新的逻辑，MTA请求辅助数据，如果LPP存在Session实体，则直接发送上行的LPP辅助请求消息
            如果没有任何session正在running，则发送给LCS即可，所以LCS回复AssistDataCnf给LPP， LPP当前
            没有什么事情可以做。
    */
}


VOS_VOID NAS_LPP_LcsMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_LcsMsgDistr is entered!");
    TLPS_PRINT2LAYER_ERROR(NAS_LPP_LcsMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*根据消息名，调用相应的消息处理函数*/
    switch(pEmmMsg->ulMsgName)
    {
        case ID_LCS_LPP_LOCATION_INFO_NTF:
            NAS_LPP_RcvGnssLocationInfo((LCS_LPP_LOCATION_INFO_NTF_STRU *)pRcvMsg);
            break;

        case ID_LCS_LPP_GNSS_ASSISTDATA_CNF:
            NAS_LPP_RcvGnssAssistDataCnf((LCS_LPP_GNSS_ASSISTDATA_CNF_STRU*)pRcvMsg);
            break;

        default:
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
