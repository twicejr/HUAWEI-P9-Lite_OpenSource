

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafApsSndRlp.h"
#include  "cttf_1x_rlp_nas_sig_pif.h"
#include  "Taf_Aps.h"
#include  "MnApsComm.h"
#include  "TafLog.h"
#include  "TafApsComFunc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_RLP_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_VOID  TAF_APS_SndRlpInitReq(
    VOS_UINT8                           ucPdpId
)
{
    CNAS_CTTF_1X_RLP_INIT_NOTIFY_STRU  *pstRlpInitNtf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstRlpInitNtf = (CNAS_CTTF_1X_RLP_INIT_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(CNAS_CTTF_1X_RLP_INIT_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstRlpInitNtf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndRlpInitReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstRlpInitNtf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(CNAS_CTTF_1X_RLP_INIT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstRlpInitNtf->ulReceiverPid    = MSPS_PID_1X_RRLP;
    pstRlpInitNtf->enMsgId          = ID_CNAS_CTTF_1X_RLP_INIT_NOTIFY;

    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstRlpInitNtf->ucConnReference  = pstPdpEntity->stCdataInfo.ucConRef;
    pstRlpInitNtf->ucPdnId          = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
    pstRlpInitNtf->enModemId        = VOS_GetModemIDFromPid(WUEPS_PID_TAF);

    if (MODEM_ID_BUTT == pstRlpInitNtf->enModemId)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndRlpInitReq:Get Modem Id fail");
    }

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_TAF, pstRlpInitNtf);

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
