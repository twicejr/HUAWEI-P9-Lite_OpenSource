

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasCcb.h"
#include  "cas_1x_control_initialstate_nas_pif.h"
#include  "NasMntn.h"
#include  "msp_diag_comm.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_CCB_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
CNAS_CCB_MODEM_PID_TAB_STRU        g_astCnasCcbModemPidTab[] = {{I0_UEPS_PID_MSCC,           I1_UEPS_PID_MSCC},
                                                                {I0_WUEPS_PID_TAF,           I1_WUEPS_PID_TAF},
                                                                {I0_UEPS_PID_XSMS,           I1_UEPS_PID_XSMS},
                                                                {I0_WUEPS_PID_USIM,          I1_WUEPS_PID_USIM}
                                                               };
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
CNAS_CCB_CTX_STRU                       g_stCnasCcbCtx;




/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958 */

CNAS_CCB_CTX_STRU*  CNAS_CCB_GetCcbCtxAddr( VOS_VOID )
{
    return &(g_stCnasCcbCtx);
}



VOS_VOID CNAS_CCB_InitUIMID(VOS_VOID)
{
    CNAS_CCB_UIMID_STRU                 *pstUIMID = VOS_NULL_PTR;
    VOS_UINT32                           i;

    pstUIMID = CNAS_CCB_GetUIMID();

    for (i = 0; i < CNAS_CCB_EFRUIMID_OCTET_LEN_EIGHT; i++)
    {
        pstUIMID->aucEFRUIMID[i] = 0xff;
    }

    /* the first byte EFRUIMID indicates the byte num of UIMID value,if read length fail,
        set the UIMID length to 0, namely invalid UIMID */
    pstUIMID->aucEFRUIMID[0] = 0;

    return;
}


VOS_VOID CNAS_CCB_InitEsnMeidMeInfo(VOS_VOID)
{
    CNAS_CCB_ESNMEIDME_INFO_STRU       *pstEsnMeidMeInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEsnMeidMeInfo = CNAS_CCB_GetEsnMeidMeInfoAddr();

    for (i = 0; i < CNAS_CCB_ESN_OCTET_LEN; i++)
    {
        pstEsnMeidMeInfo->u.aucEsn[i] = 0xFF;
    }

    for (i = 0; i < CNAS_CCB_MEID_OCTET_LEN; i++)
    {
        pstEsnMeidMeInfo->u.aucMeid[i] = 0xFF;
    }

    pstEsnMeidMeInfo->enEsnMeidType = CNAS_CCB_ESN_MEID_TYPE_BUTT;

    return;
}


VOS_VOID CNAS_CCB_InitHrpdAccessAuthInfo(VOS_VOID)
{
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstHrpdAccessAuthInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstHrpdAccessAuthInfo     = CNAS_CCB_GetHrpdAccesAuthInfoAddr();

    NAS_MEM_SET_S(pstHrpdAccessAuthInfo, sizeof(CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU), 0, sizeof(CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU));

    for (i = 0; i < CNAS_CCB_MAX_AUTHDATA_USERNAME_LEN; i++)
    {
        pstHrpdAccessAuthInfo->aucAccessAuthUserName[i] = 0xFF;
    }

    pstHrpdAccessAuthInfo->ucAccessAuthAvailFlag  = VOS_FALSE;
    pstHrpdAccessAuthInfo->ucAccessAuthUserNameLen = 0;

    return;
}


VOS_VOID CNAS_CCB_InitCcbCtx(VOS_VOID)
{
    CNAS_CCB_CTX_STRU                   *pstCcbCtx = VOS_NULL_PTR;

    pstCcbCtx = CNAS_CCB_GetCcbCtxAddr();

    NAS_MEM_SET_S(pstCcbCtx, sizeof(CNAS_CCB_CTX_STRU), 0, sizeof(CNAS_CCB_CTX_STRU));

    /* To Do: 这里暂时初始化为与AS相同值6，后续待AS增加NV后，使用NV配置值 */
    pstCcbCtx->stNwInfo.ucPRevInUse                 = P_REV_IN_USE_6;

    pstCcbCtx->stCallInfoCfg.ucIsMtCallInRoamingAcc = VOS_TRUE;

    pstCcbCtx->stNwInfo.enCasSta    = CNAS_CCB_1X_CAS_STATE_BUTT;

    pstCcbCtx->stNwInfo.enCasSubSta    = CNAS_CCB_1X_CAS_SUB_STATE_ENUM_BUTT;
    pstCcbCtx->stNwInfo.enProtocolRev  = CNAS_CCB_1X_CAS_P_REV_ENUM_BUTT;

    pstCcbCtx->stCustomCfg.ucPowerOffCampOnCtrlFlg = VOS_FALSE;

    CNAS_CCB_InitHomeSidNidList(&(pstCcbCtx->stHomeSidNidList));

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_LOOPBACK);
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_VOICE);
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_PS);
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_SMS);

    CNAS_CCB_Set1XRfAvailFlg(VOS_TRUE);

    CNAS_CCB_InitUIMID();

    CNAS_CCB_InitIccId();

    CNAS_CCB_SetCurrPsRatType(CNAS_CCB_PS_RATTYPE_NULL);
    CNAS_CCB_SetPrevRatType(CNAS_CCB_PS_RATTYPE_NULL);

    CNAS_CCB_InitMntnInfo(&(pstCcbCtx->stMntnInfo));

    /* 设置当前计数器数量为0 */
    CNAS_CCB_Set1XCallExistCount((VOS_UINT8)VOS_FALSE);

    CNAS_CCB_SetHomeSidNidDependOnPrlFlg(VOS_FALSE);

    CNAS_CCB_InitCdmaStandardChannels(&(pstCcbCtx->stCdmaStandardChan));

    CNAS_CCB_InitEsnMeidMeInfo();
    CNAS_CCB_InitHrpdAccessAuthInfo();

    CNAS_CCB_SetCur1XSrvStatus(CNAS_CCB_SERVICE_STATUS_NO_SERVICE);
}


VOS_VOID CNAS_CCB_SetCsimCardStatus(
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enCsimCardStatus = enCsimCardStatus;
}


CNAS_CCB_CARD_STATUS_ENUM_UINT8 CNAS_CCB_GetCsimCardStatus( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enCsimCardStatus;
}


VOS_UINT16  CNAS_CCB_GetCasCardStatus(VOS_VOID)
{
    CNASITF_CARD_STATUS_ENUM_UINT16      enCardStatus;

    /* UIM卡存在 */
    if (CNAS_CCB_CARD_STATUS_UIM_PRESENT  == CNAS_CCB_GetCsimCardStatus())
    {
        enCardStatus = CNASITF_CARD_STATUS_UIM_PRESENT;
    }
    /* CSIM卡存在 */
    else if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT  == CNAS_CCB_GetCsimCardStatus())
    {
        enCardStatus = CNASITF_CARD_STATUS_CSIM_PRESENT;
    }
    else
    {
        enCardStatus = CNASITF_CARD_STATUS_ABSENT;
    }

    return enCardStatus;
}


CNAS_CCB_NW_INFO_STRU* CNAS_CCB_GetCcbNwInfoAddr(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stNwInfo);
}


VOS_UINT8 CNAS_CCB_GetConcurrentSupportedFlag(VOS_VOID)
{
    /* 获取并发业务支持标志 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->ucConcurrentSupported);
}


VOS_VOID CNAS_CCB_SetConcurrentSupportedFlag(
    VOS_UINT8                           ucConcurrentSupported
)
{
    /* 更新基站并发业务支持标志 */
    CNAS_CCB_GetCcbNwInfoAddr()->ucConcurrentSupported = ucConcurrentSupported;
}


VOS_UINT8 CNAS_CCB_GetPRevInUse(VOS_VOID)
{
    /* 获取协议使用版本 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->ucPRevInUse);
}


VOS_VOID CNAS_CCB_SetPRevInUse(
    VOS_UINT8                           ucPRevInUse
)
{
    /* 更新当前使用的协议版本号 */
    CNAS_CCB_GetCcbNwInfoAddr()->ucPRevInUse = ucPRevInUse;
}


CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 CNAS_CCB_GetCasState(VOS_VOID)
{
    /* 获取协议使用版本 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->enCasSta);
}


VOS_VOID CNAS_CCB_SetCasState(
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enSta
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->enCasSta = enSta;
}




VOS_VOID CNAS_CCB_SetMtCallInRoamingAccFlg(
    VOS_UINT8                           ucIsMtCallInRoamingAcc
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCallInfoCfg.ucIsMtCallInRoamingAcc = ucIsMtCallInRoamingAcc;
}


VOS_UINT8 CNAS_CCB_GetMtCallInRoamingAccFlg( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCallInfoCfg.ucIsMtCallInRoamingAcc;
}



VOS_VOID CNAS_CCB_SetPowerOffCampOnCtrlFlg(
    VOS_UINT8                           ucPowerOffCampOnFlg
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCustomCfg.ucPowerOffCampOnCtrlFlg = ucPowerOffCampOnFlg;
}


VOS_UINT8 CNAS_CCB_GetPowerOffCampOnCtrlFlg( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCustomCfg.ucPowerOffCampOnCtrlFlg;
}



VOS_VOID CNAS_CCB_InitHomeSidNidList(
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNidList
)
{
    pstHomeSidNidList->ucSysNum = 0;

    NAS_MEM_SET_S(&pstHomeSidNidList->astHomeSidNid[0],
                  CNAS_CCB_MAX_HOME_SID_NID_LIST * sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU),
                  0,
                  CNAS_CCB_MAX_HOME_SID_NID_LIST * sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU));
}


CNAS_CCB_1X_HOME_SID_NID_LIST_STRU* CNAS_CCB_GetHomeSidNidList(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stHomeSidNidList);
}


CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8 CNAS_CCB_GetCasSubState(VOS_VOID)
{
    /* 获取CAS子状态 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->enCasSubSta);
}


VOS_VOID CNAS_CCB_SetCasSubState(
    CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8                    enSubSta
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->enCasSubSta = enSubSta;
}


CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8 CNAS_CCB_GetHighProRev(VOS_VOID)
{
    /* 获取CAS子状态 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->enProtocolRev);
}


VOS_VOID CNAS_CCB_SetHighProRev(
    CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8    enProtocolRev
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->enProtocolRev = enProtocolRev;
}


CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8 CNAS_CCB_Get1xReturnCause(VOS_VOID)
{
    return CNAS_CCB_GetCcbCtxAddr()->en1xReturnCause;
}


VOS_VOID CNAS_CCB_Set1xReturnCause(
    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8                     en1xReturnCause
)
{
    CNAS_CCB_GetCcbCtxAddr()->en1xReturnCause = en1xReturnCause;
}



CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xVoiceCallState(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_SO_TYPE_VOICE == CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xSoType)
        {
            return CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xCallState;
        }
    }
    return CNAS_CCB_1X_CALL_STATE_IDLE;
}

CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xPsCallState(
    VOS_VOID
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_SO_TYPE_PS == CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xSoType)
        {
            return CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xCallState;
        }
    }
    return CNAS_CCB_1X_CALL_STATE_IDLE;
}

CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xSmsCallState(
    VOS_VOID
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_SO_TYPE_SMS== CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xSoType)
        {
            return CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xCallState;
        }
    }
    return CNAS_CCB_1X_CALL_STATE_IDLE;
}

VOS_VOID CNAS_CCB_Set1xCallState(
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8                       en1xCallState,
    CNAS_CCB_1X_SO_TYPE_ENUM_UINT8                          en1xSoType
)
{
    switch (en1xSoType)
    {
        case CNAS_CCB_1X_SO_TYPE_VOICE:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[0].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[0].en1xCallState = en1xCallState;
            break;
        case CNAS_CCB_1X_SO_TYPE_SMS:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[1].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[1].en1xCallState = en1xCallState;
            break;
        case CNAS_CCB_1X_SO_TYPE_PS:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[2].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[2].en1xCallState = en1xCallState;
            break;
        case CNAS_CCB_1X_SO_TYPE_LOOPBACK:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xCallState = en1xCallState;
            break;
        default :
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xCallState = en1xCallState;
    }


}





VOS_VOID CNAS_CCB_Set1XRfAvailFlg(
    VOS_UINT8                           uc1XRfAvailFlg
)
{
    CNAS_CCB_GetCcbCtxAddr()->stNwInfo.uc1XRfAvailFlg = uc1XRfAvailFlg;

    return;
}


VOS_UINT8 CNAS_CCB_Get1XRfAvailFlg( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stNwInfo.uc1XRfAvailFlg;
}


CNAS_CCB_UIMID_STRU* CNAS_CCB_GetUIMID(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCardInfo.stUIMID);
}


CNAS_CCB_ESNMEIDME_INFO_STRU* CNAS_CCB_GetEsnMeidMeInfoAddr(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCardInfo.stEsnMeidMe);
}


CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU* CNAS_CCB_GetHrpdAccesAuthInfoAddr(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCardInfo.stHrpdAccessAuthInfo);
}



VOS_VOID CNAS_CCB_SetCdmaModeModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    CNAS_CCB_GetCcbCtxAddr()->stModemInfo.enCdmaModeModemId = enModemId;

    return;
}


MODEM_ID_ENUM_UINT16 CNAS_CCB_GetCdmaModeModemId( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stModemInfo.enCdmaModeModemId;
}


VOS_UINT32 CNAS_CCB_ConvertPidBasedOnModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT32                          ulRcvPid
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          i;

    /* modem 1上ulRcvPid对应的pid */
    if (MODEM_ID_0 != enModemId)
    {
        for (i = 0; i < (sizeof(g_astCnasCcbModemPidTab)/sizeof(CNAS_CCB_MODEM_PID_TAB_STRU)); i++)
        {
            if (ulRcvPid == g_astCnasCcbModemPidTab[i].ulModem0Pid)
            {
                return g_astCnasCcbModemPidTab[i].ulModem1Pid;
            }
        }

        /* 如果出现找不到对应的PID时，有可能是X模内部模块间发消息 */
    }
#endif

    return ulRcvPid;
}


VOS_UINT32 CNAS_CCB_GetModem0Pid(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT32                          ulSenderPid
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          i;

    /* modem 1上ulRcvPid对应的pid */
    if (MODEM_ID_0 != enModemId)
    {
        for (i = 0; i < (sizeof(g_astCnasCcbModemPidTab)/sizeof(CNAS_CCB_MODEM_PID_TAB_STRU)); i++)
        {
            if (ulSenderPid == g_astCnasCcbModemPidTab[i].ulModem1Pid)
            {
                return g_astCnasCcbModemPidTab[i].ulModem0Pid;
            }
        }

        /* 如果出现找不到对应的PID时，有可能是X模内部模块间发消息 */
    }
#endif

    return ulSenderPid;
}


VOS_UINT8* CNAS_CCB_GetCardIccIdAddr(VOS_VOID)
{
    return CNAS_CCB_GetCcbCtxAddr()->stCardInfo.aucCardIccId;
}




VOS_VOID CNAS_CCB_InitIccId(VOS_VOID)
{
    VOS_UINT8                           *pucCardIccId    = VOS_NULL_PTR;
    VOS_UINT32                           i;

    pucCardIccId = CNAS_CCB_GetCardIccIdAddr();

    for (i = 0; i < CNAS_CCB_ICCID_OCTET_LEN; i++)
    {
        pucCardIccId[i] = 0xFF;
    }

    return;
}


VOS_VOID CNAS_CCB_SetUsimCardStatus(
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enUsimCardStatus
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enUsimCardStatus = enUsimCardStatus;
}


CNAS_CCB_CARD_STATUS_ENUM_UINT8 CNAS_CCB_GetUsimCardStatus( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enUsimCardStatus;
}


CNAS_CCB_PS_RATTYPE_ENUM_UINT32 CNAS_CCB_GetCurrPsRatType(VOS_VOID)
{
    /* 获取PS rat type */
    return (CNAS_CCB_GetCcbCtxAddr()->enCurrPsRatType);
}


VOS_VOID CNAS_CCB_SetCurrPsRatType(
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32    enPsRatType
)
{
    /* 更新当前使用的ps rat type */
    CNAS_CCB_GetCcbCtxAddr()->enCurrPsRatType = enPsRatType;
}

CNAS_CCB_PS_RATTYPE_ENUM_UINT32 CNAS_CCB_GetPrevPsRatType(VOS_VOID)
{
    /* 获取PS rat type */
    return (CNAS_CCB_GetCcbCtxAddr()->enPrevPsRatType);
}


VOS_VOID CNAS_CCB_SetPrevRatType(
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enPsRatType
)
{
    /* 更新当前使用的ps rat type */
    CNAS_CCB_GetCcbCtxAddr()->enPrevPsRatType = enPsRatType;
}


CNAS_CAS_1X_RETURN_CAUSE_ENUM_UINT8 CNAS_CCB_CovertReturnCause(
    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8   enCnas1xReturnCause
)
{
    CNAS_CAS_1X_RETURN_CAUSE_ENUM_UINT8   enCasReturnCause;

    switch (enCnas1xReturnCause)
    {
        case CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_NORMAL_ACCESS;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_SYSTEM_NOT_ACQ :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_SYSTEM_NOT_FOUND;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_PROTOCOL_MISMATCH :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_PROTOCOL_MISMATCH;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_REG_REJ :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_REGISTRATION_REJECTION;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_WRONG_SID :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_WRONG_SID;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_WRONG_NID :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_WRONG_NID;
            break;

        default:
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_BUTT;
            break;
    }

    return enCasReturnCause;
}


VOS_VOID CNAS_CCB_Set1XCallExistCount(
    VOS_UINT8                           uc1XCallExistCount
)
{
    CNAS_CCB_GetCcbCtxAddr()->uc1XCallExistCount = uc1XCallExistCount;

    return;
}


VOS_UINT8 CNAS_CCB_Get1XCallExistCount( VOS_VOID )
{
    return (CNAS_CCB_GetCcbCtxAddr()->uc1XCallExistCount);
}



VOS_UINT8 CNAS_CCB_GetHomeSidNidDependOnPrlFlg(VOS_VOID)
{
    return CNAS_CCB_GetCcbCtxAddr()->ucHomeSidNidDependOnPrlFlg;
}


VOS_VOID CNAS_CCB_SetHomeSidNidDependOnPrlFlg(
    VOS_UINT8                           ucFlg
)
{
    CNAS_CCB_GetCcbCtxAddr()->ucHomeSidNidDependOnPrlFlg = ucFlg;
}



CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU* CNAS_CCB_GetOperLockSysWhiteList(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stOperLockSysWhiteList);
}


CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU* CNAS_CCB_GetCTCCCustomizeFreqList(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCTCCCustInfo.stCustFreqList);
}



VOS_VOID CNAS_CCB_InitMntnInfo(
    CNAS_CCB_MNTN_CTX_STRU             *pstMntnInfo
)
{
    NAS_MEM_SET_S(pstMntnInfo, sizeof(CNAS_CCB_MNTN_CTX_STRU), 0x00, sizeof(CNAS_CCB_MNTN_CTX_STRU));
    return;
}


CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU* CNAS_CCB_GetCdmaStandardChannels(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCdmaStandardChan);
}


VOS_VOID CNAS_CCB_InitCdmaStandardChannels(
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan
)
{
    /* 初始化默认频点为协议定义的频点 */
    /* 参考CDG 130 4.4.3章节Table 4-8中的定义 */
    pstCdmaStandardChan->usPrimaryA   = 283;

    pstCdmaStandardChan->usSecondaryA = 691;

    pstCdmaStandardChan->usPrimaryB   = 384;

    pstCdmaStandardChan->usSecondaryB = 777;
}


CNAS_CCB_1X_SO_TYPE_ENUM_UINT8 CNAS_CCB_ConvertSoToServiceType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  en1xSo
)
{
    CNAS_CCB_1X_SO_TYPE_ENUM_UINT8      en1xSoType;

    switch (en1xSo)
    {
        case CAS_CNAS_1X_SO_3_EVRC:
        case CAS_CNAS_1X_SO_17_VOICE_13K:
        case CAS_CNAS_1X_SO_68_EVRC_B:
        case CAS_CNAS_1X_SO_73_EVRC_NW:
        case CAS_CNAS_1X_SO_18_OTASP:
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        case CAS_CNAS_1X_SO_32944_VOICE_ENCRYPT:
#endif
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_VOICE;
            break;
        case CAS_CNAS_1X_SO_7_PPP_PKT_DATA:
        case CAS_CNAS_1X_SO_33_PPP_PKT_DATA_CDMA2K:
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_PS;
            break;
        case CAS_CNAS_1X_SO_6_SMS_RS1:
        case CAS_CNAS_1X_SO_14_SMS_RS2:
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_SMS;
            break;
        case CAS_CNAS_1X_SO_2_LOOPBACK:
        case CAS_CNAS_1X_SO_9_LOOPBACK:
        case CAS_CNAS_1X_SO_54_MARKOV:
        case CAS_CNAS_1X_SO_55_LOOPBACK:
        case CAS_CNAS_1X_SO_74_LOOPBACK:
        case CAS_CNAS_1X_SO_75_LOOPBACK:
            en1xSoType = CNAS_CCB_1X_SO_TYPE_LOOPBACK;
            break;

        case CAS_CNAS_1X_SO_35_LOC_SERV:
        case CAS_CNAS_1X_SO_36_LOC_SERV:
            en1xSoType = CNAS_CCB_1X_SO_TYPE_AGPS;
            break;

        default :
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_LOOPBACK;
    }
    return en1xSoType;
}


CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_CCB_GetCdmaOhmFreq(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stOhmFreq);
}


VOS_VOID CNAS_CCB_SetCdmaOhmFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstOhmFreq
)
{
    CNAS_CCB_GetCcbCtxAddr()->stOhmFreq = *pstOhmFreq;
}


VOS_VOID CNAS_CCB_ClearCdmaOhmFreq(VOS_VOID)
{
    CNAS_CCB_GetCcbCtxAddr()->stOhmFreq.enBandClass = 0;

    CNAS_CCB_GetCcbCtxAddr()->stOhmFreq.usChannel   = 0;
}


VOS_VOID CNAS_CCB_Set1xSysInfo(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT16                          usBandClass,
    VOS_UINT16                          usChannel
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usSid       = usSid;
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usNid       = usNid;
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usBandClass = usBandClass;
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usChannel   = usChannel;

    return;
}


CNAS_CCB_1X_SYS_INFO_STRU* CNAS_CCB_Get1xSysInfo(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo);
}



VOS_UINT32 CNAS_CCB_IsCurCallStateIdle( VOS_VOID )
{
    VOS_UINT32                          ulIndex;
    CNAS_CCB_CTX_STRU                  *pstCcbCtx   = VOS_NULL_PTR;

    pstCcbCtx                           = CNAS_CCB_GetCcbCtxAddr();

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_CALL_STATE_IDLE != pstCcbCtx->astMntn1xCallState[ulIndex].en1xCallState)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

CNAS_CCB_1X_SRV_INFO_STRU* CNAS_CCB_GetCur1XSrvInfo(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->st1XSrvInfo);
}


CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 CNAS_CCB_GetCur1XSrvStatus(VOS_VOID)
{
    CNAS_CCB_1X_SRV_INFO_STRU          *pst1XSrvInfo = VOS_NULL_PTR;

    pst1XSrvInfo = CNAS_CCB_GetCur1XSrvInfo();

    return pst1XSrvInfo->enCurSrvStatus;
}


VOS_VOID CNAS_CCB_SetCur1XSrvStatus(
    CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 enSrvStatus
)
{
    CNAS_CCB_1X_SRV_INFO_STRU          *pst1XSrvInfo = VOS_NULL_PTR;

    pst1XSrvInfo = CNAS_CCB_GetCur1XSrvInfo();

    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_CCB_SetCur1XSrvStatus:Cur SrvStatus: ", (VOS_UINT32)pst1XSrvInfo->enCurSrvStatus);

    pst1XSrvInfo->enCurSrvStatus = enSrvStatus;

    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_CCB_SetCur1XSrvStatus:Set SrvStatus To: ", (VOS_UINT32)pst1XSrvInfo->enCurSrvStatus);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



