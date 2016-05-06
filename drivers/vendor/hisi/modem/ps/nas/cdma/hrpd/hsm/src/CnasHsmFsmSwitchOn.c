

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmFsmSwitchOn.h"
#include "CnasHsmProcUsim.h"
#include "PsCommonDef.h"
#include "CnasHsmCtx.h"
#include "CnasHsmComFunc.h"
#include "CnasHsmSndHsd.h"
#include "CnasHsmProcNvim.h"
#include "CnasHsmComFunc.h"
#include "CnasHsmFsmMain.h"
#include "CnasHsmFsmTbl.h"
#include "CnasMntn.h"
#include "CnasHsmMntn.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_FSM_SWITCH_ON_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/

VOS_UINT32 CNAS_HSM_RcvInterSwitchOnReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enUsimCardStatus;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus;

    enUsimCardStatus = CNAS_CCB_GetUsimCardStatus();
    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    /* read the NV info */
    CNAS_HSM_ReadNvim();

    if ((CNAS_CCB_CARD_STATUS_ABSENT == enUsimCardStatus)
     && (CNAS_CCB_CARD_STATUS_ABSENT == enCsimCardStatus))
    {
        /* 读取ESN 和 MEID NV, 无卡时，读取后直接退去 */
        CNAS_HSM_ReadEsnAndMeidNvim();

        CNAS_HSM_QuitFsmSwitchOnReq();
    }
    else
    {
        CNAS_HSM_SndUsimmReadFileReq_SwithcOn();

        CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_SWITCH_ON_WAIT_CARD_READ_CNF);

        CNAS_HSM_StartTimer(TI_CNAS_HSM_WAIT_CARD_READ_CNF,
                            TI_CNAS_HSM_WAIT_CARD_READ_CNF_LEN);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_VOID CNAS_HSM_QuitFsmSwitchOnReq(VOS_VOID)
{
    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_VACANT);

    CNAS_HSM_SndInternalSwitchOnResultInd();

    return;
}


VOS_VOID CNAS_HSM_SndUsimmReadFileReq_SwithcOn(VOS_VOID)
{
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus;

    enCsimCardStatus = CNAS_CCB_GetCsimCardStatus();

    /* 读取卡文件2fe2 */
    CNAS_HSM_SndReadUsimmFileReq(USIMM_GUTL_APP, USIMM_ICCID_ID);
    CNAS_HSM_SetWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ICCID);

    if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
    {
        /* 读取卡文件6f31 */
        CNAS_HSM_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFRUIMID_ID);
        CNAS_HSM_SetWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_UIMID);

        /* 读取卡文件6f38 */
        CNAS_HSM_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFESNMEID_ID);
        CNAS_HSM_SetWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ESNMEIDME);

        /* 读取卡文件6f57 */
        CNAS_HSM_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFHRPDUPP_ID);
        CNAS_HSM_SetWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_HRPD_ACCESS_AUTH_USERNAME);
    }

    if (CNAS_CCB_CARD_STATUS_UIM_PRESENT == enCsimCardStatus)
    {
        /* 读取卡文件6f31 */
        CNAS_HSM_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFRUIMID_ID);
        CNAS_HSM_SetWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_UIMID);

        /* 读取卡文件6f38 */
        CNAS_HSM_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFESNMEIDME_ID);
        CNAS_HSM_SetWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ESNMEIDME);

        /* 读取卡文件6f57 */
        CNAS_HSM_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFHRPDUPP_ID);
        CNAS_HSM_SetWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_HRPD_ACCESS_AUTH_USERNAME);
    }

    return;
}


VOS_UINT32 CNAS_HSM_RcvCardGetFileCnf_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstUsimmReadCnfMsg;
    VOS_UINT32                          enEfId;

    pstUsimmReadCnfMsg = (USIMM_READFILE_CNF_STRU*)pstMsg;

    if (VOS_OK != USIMM_ChangePathToDefFileID(pstUsimmReadCnfMsg->stCmdResult.enApptype,
                                              pstUsimmReadCnfMsg->stFilePath.ulPathLen,
                                              pstUsimmReadCnfMsg->stFilePath.acPath,
                                              &enEfId))
    {
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_RcvUsimmReadFileCnf(pstUsimmReadCnfMsg, enEfId);

    CNAS_HSM_ClearWaitCardReadCnfFlg_SwitchOn(enEfId);

    if (CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_NULL == CNAS_HSM_GetWaitCardReadCnfFlag())
    {
        /* 读取ESN 和 MEID NV, 因为该NV与卡相关，故在读完卡读该NV */
        CNAS_HSM_ReadEsnAndMeidNvim();

        CNAS_HSM_StopTimer(TI_CNAS_HSM_WAIT_CARD_READ_CNF);

        /* quit switch on fsm */
        CNAS_HSM_QuitFsmSwitchOnReq();
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvTiCardGetFileCnfExpired_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                              *pucCardIccId            = VOS_NULL_PTR;
    CNAS_CCB_UIMID_STRU                                    *pstUIMID                = VOS_NULL_PTR;
    CNAS_CCB_ESNMEIDME_INFO_STRU                           *pstEsnMeidMe            = VOS_NULL_PTR;
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstHrpdAccessAuthInfo   = VOS_NULL_PTR;
    CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32            enFlag;
    VOS_UINT8                                               i;

    pucCardIccId            = CNAS_CCB_GetCardIccIdAddr();
    pstUIMID                = CNAS_CCB_GetUIMID();
    pstEsnMeidMe            = CNAS_CCB_GetEsnMeidMeInfoAddr();
    pstHrpdAccessAuthInfo   = CNAS_CCB_GetHrpdAccesAuthInfoAddr();
    enFlag                  = CNAS_HSM_GetWaitCardReadCnfFlag();

    CNAS_HSM_LogReadCardInfo(enFlag);

    /* 定时器超时前，未能读取ICCID */
    if (CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ICCID == (enFlag & CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ICCID))
    {
        for (i = 0; i < CNAS_CCB_ICCID_OCTET_LEN; i++)
        {
            pucCardIccId[i] = 0xFF;
        }
    }

    /* 定时器超时前，未能读取UIMID */
    if (CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_UIMID == (enFlag & CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_UIMID))
    {

        for (i = 0; i < CNAS_CCB_EFRUIMID_OCTET_LEN_EIGHT; i++)
        {
            pstUIMID->aucEFRUIMID[i] = 0xFF;
        }
        /* the first byte EFRUIMID indicates the byte num of UIMID value,if read fail,
            set the UIMID length to 0, namely invalid UIMID */
        pstUIMID->aucEFRUIMID[0] = 0;
    }

    /* 定时器超时前，未能读取ESNMEIDME */
    if (CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ESNMEIDME == (enFlag & CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ESNMEIDME))
    {
        pstEsnMeidMe->enEsnMeidType = CNAS_CCB_ESN_MEID_TYPE_BUTT;
    }

    /* 定时器超时前，未能读取HRPDUPP */
    if (CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_HRPD_ACCESS_AUTH_USERNAME == (enFlag & CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_HRPD_ACCESS_AUTH_USERNAME))
    {
        pstHrpdAccessAuthInfo->ucAccessAuthAvailFlag = VOS_FALSE;
    }

    CNAS_HSM_ResetWaitCardReadCnfFlag();

    /* 读取ESN 和 MEID NV, 因为该NV与卡相关，故在读完卡读该NV */
    CNAS_HSM_ReadEsnAndMeidNvim();

    /* quit switch on fsm */
    CNAS_HSM_QuitFsmSwitchOnReq();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_SwitchOn_WaitCardFileCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_ProcPowerOffReq();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_VOID CNAS_HSM_ClearWaitCardReadCnfFlg_SwitchOn(
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId
)
{
    switch (enEfId)
    {
        case USIMM_ICCID_ID:
            CNAS_HSM_ClearWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ICCID);
            break;
        case USIMM_CSIM_EFRUIMID_ID:
        case USIMM_CDMA_EFRUIMID_ID:
            CNAS_HSM_ClearWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_UIMID);
            break;

        case USIMM_CSIM_EFESNMEID_ID:
        case USIMM_CDMA_EFESNMEIDME_ID:
            CNAS_HSM_ClearWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_ESNMEIDME);
            break;

        case USIMM_CSIM_EFHRPDUPP_ID:
        case USIMM_CDMA_EFHRPDUPP_ID:
            CNAS_HSM_ClearWaitCardReadCnfFlag(CNAS_HSM_WAIT_CARD_READ_CNF_FLAG_HRPD_ACCESS_AUTH_USERNAME);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_ClearWaitCardReadCnfFlg_SwitchOn:WARNING: File Id Abnormal");
            break;
    }

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

