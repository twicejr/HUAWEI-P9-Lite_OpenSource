

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include  "CnasHsmProcNvim.h"
#include  "CnasHsmCtx.h"
#include  "NVIM_Interface.h"
#include  "NasNvInterface.h"
#include  "CnasMntn.h"
#include  "CnasHsmMntn.h"
#include  "omnvinterface.h"
#include  "PsLib.h"
#include  "CnasHsmComFunc.h"

#include  "CnasHsmSndMma.h"
#include  "CnasHsmFsmUatiRequest.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_PROC_NVIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/
/*****************************************************************************
Function Name   :   CNAS_HSM_ReadNvim
Description     :   Read NV proc
Input parameters:   None
Outout parameters:  None
Return Value    :   None

Modify History  :
1)  Date           : 2015-02-07
    Author         : s00250401
    Modify content : Create
2)  Date           : 2015-05-30
    Author         : y00174758
    Modify content : Iteration 12: Read session act and retry NV
3)  Date           : 2015-05-30
    Author         : t00323010
    Modify content : Iteration 12: add EHRPD Support NVIM read
4)  Date           : 2015-09-18
    Author         : m00312079
    Modify content : DTS2015091604029:读取SessionInfoEx中的session seed
5)  Date           : 2015-09-23
    Author         : m00312079
    Modify content : DTS2015091705555:读取ucStartUatiReqAfterSectorIdChgFlg
*****************************************************************************/
VOS_VOID CNAS_HSM_ReadNvim(VOS_VOID)
{
    CNAS_HSM_ReadSessionRetryCfgNvim();

    CNAS_HSM_ReadHrpdUERevInfoNvim();

    CNAS_HSM_ReadHrpdSessionInfoNvim();
    CNAS_HSM_ReadSessionKeepAliveInfoNvim();
    CNAS_HSM_ReadHrpdSessionInfoExNvim();

    CNAS_HSM_ReadHrpdSessionCtrlCfgNvim();

    CNAS_HSM_ReadHrpdAccessAuthInfoNvim();
}


VOS_VOID CNAS_HSM_ReadEsnAndMeidNvim(VOS_VOID)
{
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstHwIdInfo = VOS_NULL_PTR;
    VOS_INT32                           lIndex;
    NV_PESN_STRU                        stPesn;
    NV_MEID_STRU                        stMeid;
    VOS_UINT8                           ucPesnValidityFlag;
    VOS_UINT8                           ucMeidValidityFlag;
    VOS_UINT32                          ucReadEsnRslt;
    VOS_UINT32                          ucReadMeidRslt;
    CNAS_CCB_UIMID_STRU                *pstUIMID    = VOS_NULL_PTR;

    ucPesnValidityFlag  = VOS_FALSE;
    ucMeidValidityFlag  = VOS_FALSE;
    ucReadEsnRslt       = NV_ID_NOT_EXIST;
    ucReadMeidRslt      = NV_ID_NOT_EXIST;

    pstUIMID         = CNAS_CCB_GetUIMID();
    pstHwIdInfo      = CNAS_HSM_GetHardwareIdInfo();

    NAS_MEM_SET_S(&stPesn, sizeof(stPesn), 0, sizeof(NV_PESN_STRU));
    NAS_MEM_SET_S(&stMeid, sizeof(stMeid), 0, sizeof(NV_MEID_STRU));

    ucReadEsnRslt    = NV_Read(en_NV_Item_PESN, &stPesn, sizeof(NV_PESN_STRU));
    ucReadMeidRslt   = NV_Read(en_NV_Item_MEID, &stMeid, sizeof(NV_MEID_STRU));
    if ((NV_OK != ucReadEsnRslt) && (NV_OK != ucReadMeidRslt))
    {

        if (VOS_TRUE == CNAS_HSM_IsUIMIDValid(pstUIMID->aucEFRUIMID))
        {
            CNAS_HSM_SetUIMIDAsHardwareIdInfo();
        }
        else
        {
            CNAS_HSM_SetRandEsnAsHardwareIdInfo();
        }

        /* 可维可测信息 */
        CNAS_HSM_SndMmaHardWareInfo();

        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ReadEsnAndMeidNvim:Read Nvim Failed");
        return;
    }

    if (NV_OK == ucReadEsnRslt)
    {
        CNAS_MNTN_LogReadNVInfo(en_NV_Item_PESN,
                                sizeof(NV_PESN_STRU),
                                UEPS_PID_HSM,
                                (VOS_UINT8 *)&stPesn);

        ucPesnValidityFlag = CNAS_HSM_IsPesnValid(&stPesn);
    }

    if (NV_OK == ucReadMeidRslt)
    {
        CNAS_MNTN_LogReadNVInfo(en_NV_Item_MEID,
                                sizeof(NV_MEID_STRU),
                                UEPS_PID_HSM,
                                (VOS_UINT8 *)&stMeid);

        ucMeidValidityFlag = CNAS_HSM_IsMeidValid(&stMeid);
    }

    if ((VOS_FALSE == ucPesnValidityFlag) && (VOS_FALSE == ucMeidValidityFlag))
    {
        if (VOS_TRUE == CNAS_HSM_IsUIMIDValid(pstUIMID->aucEFRUIMID))
        {
            CNAS_HSM_SetUIMIDAsHardwareIdInfo();
        }
        else
        {
            CNAS_HSM_SetRandEsnAsHardwareIdInfo();
        }

        /* 可维可测信息 */
        CNAS_HSM_SndMmaHardWareInfo();

        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ReadEsnAndMeidNvim: read Nvim succ, but nvim is invalid");
        return;
    }

    if (VOS_TRUE == ucPesnValidityFlag)
    {
        pstHwIdInfo->enHwidType    = CNAS_HSM_HARDWARE_ID_TYPE_ESN;
        pstHwIdInfo->enHwidSrcType = CNAS_HSM_HARDWARE_ID_SRC_TYPE_NVIM;

        /* Read from high to low */
        for (lIndex = (PESN_NV_DATA_LEN - 1); lIndex >= 0; lIndex--)
        {
            /* Update the current value */
            pstHwIdInfo->ulEsn <<= sizeof(stPesn.aucPEsn[0]) * 8;

            /* Add lower bits */
            pstHwIdInfo->ulEsn |= stPesn.aucPEsn[lIndex];
        }
    }

    if (VOS_TRUE == ucMeidValidityFlag)
    {
        /* for esn and meid enable both case,we use meid prefered */
        pstHwIdInfo->enHwidType    = CNAS_HSM_HARDWARE_ID_TYPE_MEID;
        pstHwIdInfo->enHwidSrcType = CNAS_HSM_HARDWARE_ID_SRC_TYPE_NVIM;

        NAS_MEM_CPY_S(pstHwIdInfo->aucMeId, sizeof(pstHwIdInfo->aucMeId), stMeid.aucMeID, MEID_NV_DATA_LEN_NEW);
    }

    /* 可维可测信息 */
    CNAS_HSM_SndMmaHardWareInfo();
    CNAS_HSM_LogHwIdInfo(pstHwIdInfo);
}


VOS_VOID CNAS_HSM_ReadSessionRetryCfgNvim(VOS_VOID)
{
    CNAS_HSM_NVIM_SESSION_RETRY_CFG_STRU   stSessionRetryCfg;

    NAS_MEM_SET_S(&stSessionRetryCfg, sizeof(stSessionRetryCfg), 0, sizeof(CNAS_HSM_NVIM_SESSION_RETRY_CFG_STRU));

    /* 在开机初始化时设置成了默认值，所以在NV读取失败或者NV值无效时不再设置成默认值 */
    if (NV_OK != NV_Read(en_NV_Item_CNAS_HRPD_Session_Retry_Cfg, &stSessionRetryCfg,
                         sizeof(CNAS_HSM_NVIM_SESSION_RETRY_CFG_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ReadSessionActCfgNvim: Read Nvim Failed");
        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_CNAS_HRPD_Session_Retry_Cfg,
                            sizeof(CNAS_HSM_NVIM_SESSION_RETRY_CFG_STRU),
                            UEPS_PID_HSM,
                            (VOS_UINT8 *)&stSessionRetryCfg);

    if (VOS_FALSE == stSessionRetryCfg.ucActiveFlag)
    {
        return;
    }

    if (stSessionRetryCfg.ucMaxActCountConnFail > 0)
    {
        CNAS_HSM_SetSessionActMaxCntConnFail(stSessionRetryCfg.ucMaxActCountConnFail);
    }

    if (stSessionRetryCfg.ucMaxActCountOtherFail > 0)
    {
        CNAS_HSM_SetSessionActMaxCntOtherFail(stSessionRetryCfg.ucMaxActCountOtherFail);
    }

    if (stSessionRetryCfg.usActTimerLen > 0)
    {
        CNAS_HSM_SetSessionActTimerLen(stSessionRetryCfg.usActTimerLen * 1000);
    }
}




VOS_VOID CNAS_HSM_ReadSessionKeepAliveInfoNvim(VOS_VOID)
{
    CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU              stNvimKeepAliveInfo;

    NAS_MEM_SET_S(&stNvimKeepAliveInfo, sizeof(stNvimKeepAliveInfo), 0, sizeof(CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU));

    if (NV_OK != NV_Read(en_Nv_Item_CNAS_HRPD_Session_Keep_Alive_Info, &stNvimKeepAliveInfo,
                         sizeof(CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ReadSessionKeepAliveInfoNvim: Error in NV_Read");
        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_Nv_Item_CNAS_HRPD_Session_Keep_Alive_Info,
                            sizeof(CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU),
                            UEPS_PID_HSM,
                            (VOS_UINT8 *)&stNvimKeepAliveInfo);

    /* invalid keep alive info,directly return */
    if (VOS_FALSE == stNvimKeepAliveInfo.ucIsKeepAliveInfoValid)
    {
        return;
    }

    /* Copy the values from the NV to the Keep alive timer context */
    CNAS_HSM_SetTsmpClose(stNvimKeepAliveInfo.usTsmpClose);
    CNAS_HSM_SetKeepAliveInfoValidFlag(stNvimKeepAliveInfo.ucIsKeepAliveInfoValid);
    CNAS_HSM_SetTsmpCloseRemainTime(stNvimKeepAliveInfo.ulTsmpCloseRemainTime);
    CNAS_HSM_SetLastPowerOffSysTime(stNvimKeepAliveInfo.aulLastPowerOffSysTime);
}




VOS_VOID CNAS_HSM_WriteSessionKeepAliveInfoNvim(
    CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU                  *pstSessionKeepAliveInfo
)
{
    CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU              stNvimKeepAliveInfo;

    NAS_MEM_SET_S(&stNvimKeepAliveInfo, sizeof(stNvimKeepAliveInfo), 0, sizeof(CNAS_HSM_NVIM_SESSION_KEEP_ALIVE_INFO_STRU));

    /* Update the values from Keep Alive Timer context to NV */
    stNvimKeepAliveInfo.usTsmpClose                  = pstSessionKeepAliveInfo->usTsmpClose;
    stNvimKeepAliveInfo.ucIsKeepAliveInfoValid       = pstSessionKeepAliveInfo->ucIsKeepAliveInfoValid;
    stNvimKeepAliveInfo.ulTsmpCloseRemainTime        = pstSessionKeepAliveInfo->ulTsmpCloseRemainTime;

    NAS_MEM_CPY_S(stNvimKeepAliveInfo.aulLastPowerOffSysTime,
                  sizeof(stNvimKeepAliveInfo.aulLastPowerOffSysTime),
                  pstSessionKeepAliveInfo->aulPowerOffSysTime,
                  sizeof(stNvimKeepAliveInfo.aulLastPowerOffSysTime));

    if (NV_OK != NV_Write(en_Nv_Item_CNAS_HRPD_Session_Keep_Alive_Info,
                         &stNvimKeepAliveInfo, sizeof(CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU)))
    {
        /* Make Error log is NV Write Fails */
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_WriteSessionKeepAliveInfoNvim: Error in NV Write!");

        return;
    }

    CNAS_MNTN_LogWriteNVInfo(en_Nv_Item_CNAS_HRPD_Session_Keep_Alive_Info,
                             sizeof(CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU),
                             UEPS_PID_HSM,
                             (VOS_UINT8 *)&stNvimKeepAliveInfo);
}

/*****************************************************************************
Function Name   :   CNAS_HSM_ReadHrpdSessionInfoNvim
Description     :   Read en_Nv_Item_HRPD_Session_Info proc
Input parameters:   None
Outout parameters:  None
Return Value    :   None

Modify History  :
1)  Date           : 2015-06-03
    Author         : y00307564
    Modify content : Create
2)  Date           : 2015-09-18
    Author         : m00312079
    Modify content : DTS2015091604029:session有效则读取uati assigngment的sequence number
*****************************************************************************/
VOS_VOID CNAS_HSM_ReadHrpdSessionInfoNvim(VOS_VOID)
{
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstHwid;
    CNAS_HSM_UATI_INFO_STRU            *pstCurUatiInfo;
    CNAS_HSM_LOC_INFO_STRU             *pstLocInfo;
    CNAS_NVIM_HRPD_SESSION_INFO_STRU    stHrpdSessionInfo;

    NAS_MEM_SET_S(&stHrpdSessionInfo, sizeof(stHrpdSessionInfo), 0, sizeof(CNAS_NVIM_HRPD_SESSION_INFO_STRU));

    if (NV_OK != NV_Read(en_Nv_Item_CNAS_HRPD_Session_Info, &stHrpdSessionInfo,
                         sizeof(CNAS_NVIM_HRPD_SESSION_INFO_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ReadHrpdSessionInfoNvim: Read Nvim Failed");

        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_Nv_Item_CNAS_HRPD_Session_Info,
                            sizeof(CNAS_NVIM_HRPD_SESSION_INFO_STRU),
                            UEPS_PID_HSM,
                            (VOS_UINT8 *)&stHrpdSessionInfo);

    /* session status is close,directly return */
    if (CNAS_NVIM_HRPD_SESSION_STATUS_CLOSE == stHrpdSessionInfo.enSessionStatus)
    {
        return;
    }

    CNAS_HSM_SetLastHrpdSessionStatus(CNAS_HSM_SESSION_STATUS_OPEN);

    CNAS_HSM_SetLastSessionType((CNAS_HSM_SESSION_TYPE_ENUM_UINT8)stHrpdSessionInfo.enSessionType);

    CNAS_CCB_SetLastIccId(stHrpdSessionInfo.aucIccid);

    pstHwid                = CNAS_HSM_GetLastSessionHwidCtxAddr();
    pstHwid->enHwidType    = (CNAS_HSM_HARDWARE_ID_TYPE_ENUM_UINT32)stHrpdSessionInfo.stHwid.enHwidType;
    pstHwid->enHwidSrcType = (CNAS_HSM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32)stHrpdSessionInfo.stHwid.enHwidSrcType;
    pstHwid->ulEsn         = stHrpdSessionInfo.stHwid.ulEsn;

    NAS_MEM_CPY_S(pstHwid->aucMeId,
                  sizeof(pstHwid->aucMeId),
                  stHrpdSessionInfo.stHwid.aucMeId,
                  sizeof(VOS_UINT8) * CNAS_HSM_MEID_OCTET_NUM);

    /* 这里直接将上次驻留的UATI信息以及LOC info保存到全局变量中,如果session recovery fail,进入inactive
       状态会清空当前UATI信息和loc info;否则recovery succ后可以直接使用 */
    pstCurUatiInfo = CNAS_HSM_GetUatiInfoAddr();

    NAS_MEM_CPY_S(pstCurUatiInfo->aucCurUATI,
                  sizeof(pstCurUatiInfo->aucCurUATI),
                  stHrpdSessionInfo.stUatiInfo.aucCurUATI,
                  sizeof(VOS_UINT8) * CNAS_HSM_UATI_OCTET_LENGTH);

    pstCurUatiInfo->ucUATIColorCode  = stHrpdSessionInfo.stUatiInfo.ucUATIColorCode;
    pstCurUatiInfo->ucUATISubnetMask = stHrpdSessionInfo.stUatiInfo.ucUATISubnetMask;

    CNAS_HSM_SetCurrUATIAssignMsgSeqNum(stHrpdSessionInfo.stUatiInfo.ucUATIAssignMsgSeq);
    pstLocInfo             = CNAS_HSM_GetLocInfoAddr();
    pstLocInfo->lLatitude  = stHrpdSessionInfo.stLocInfo.lLatitude;
    pstLocInfo->lLongitude = stHrpdSessionInfo.stLocInfo.lLongitude;

    return;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_WriteHrpdSessionInfoNvim
Description     :   Write en_Nv_Item_HRPD_Session_Info
Input parameters:   None

Outout parameters:  None
Return Value    :   None

Modify History  :
1)  Date           : 2015-06-03
    Author         : y00307564
    Modify content : Create
2)  Date           : 2015-09-18
    Author         : m00312079
    Modify content : DTS2015091604029:nv中保存有效uati assigngment的sequence number
3)  Date           : 2015-09-23
    Author         : t00323010
    Modify content : HSM MNTN(DTS2015092201636): log write session info Nvim
*****************************************************************************/
VOS_VOID CNAS_HSM_WriteHrpdSessionInfoNvim(VOS_VOID)
{
    VOS_UINT8                          *pucIccid;
    CNAS_HSM_HARDWARE_ID_INFO_STRU     *pstHwid;
    CNAS_HSM_UATI_INFO_STRU            *pstUatiInfo;
    CNAS_HSM_LOC_INFO_STRU             *pstLocInfo;
    CNAS_NVIM_HRPD_SESSION_INFO_STRU    stHrpdSessionInfo;

    NAS_MEM_SET_S(&stHrpdSessionInfo, sizeof(stHrpdSessionInfo), 0, sizeof(CNAS_NVIM_HRPD_SESSION_INFO_STRU));

    /* Update the values ucIsSessionOpen */
    if (CNAS_HSM_SESSION_STATUS_CLOSE == CNAS_HSM_GetSessionStatus())
    {
        stHrpdSessionInfo.enSessionStatus = CNAS_NVIM_HRPD_SESSION_STATUS_CLOSE;
    }
    else
    {
        stHrpdSessionInfo.enSessionStatus = CNAS_NVIM_HRPD_SESSION_STATUS_OPEN;
    }

    /* Update the values sesstype */
    stHrpdSessionInfo.enSessionType = (CNAS_NVIM_HRPD_SESSION_TYPE_ENUM_UINT8)CNAS_HSM_GetNegoSessionType();

    /* Update the values ICCID to NV */
    pucIccid = CNAS_CCB_GetCardIccIdAddr();

    NAS_MEM_CPY_S(stHrpdSessionInfo.aucIccid,
                  sizeof(stHrpdSessionInfo.aucIccid),
                  pucIccid,
                  sizeof(stHrpdSessionInfo.aucIccid));

    /* Update the values hardware id to NV */
    pstHwid = CNAS_HSM_GetHardwareIdInfo();

    stHrpdSessionInfo.stHwid.enHwidType    = (CNAS_NVIM_HARDWARE_ID_TYPE_ENUM_UINT32)pstHwid->enHwidType;
    stHrpdSessionInfo.stHwid.enHwidSrcType = (CNAS_NVIM_HARDWARE_ID_SRC_TYPE_ENUM_UINT32)pstHwid->enHwidSrcType;
    stHrpdSessionInfo.stHwid.ulEsn         = pstHwid->ulEsn;

    NAS_MEM_CPY_S(stHrpdSessionInfo.stHwid.aucMeId,
                  sizeof(stHrpdSessionInfo.stHwid.aucMeId),
                  pstHwid->aucMeId,
                  sizeof(VOS_UINT8) * CNAS_NVIM_MEID_OCTET_NUM);

    /* Update the uata values to nv */
    pstUatiInfo = CNAS_HSM_GetUatiInfoAddr();
    stHrpdSessionInfo.stUatiInfo.ucUATISubnetMask = pstUatiInfo->ucUATISubnetMask;
    stHrpdSessionInfo.stUatiInfo.ucUATIColorCode  = pstUatiInfo->ucUATIColorCode;

    stHrpdSessionInfo.stUatiInfo.ucUATIAssignMsgSeq = CNAS_HSM_GetCurrUATIAssignMsgSeqNum();
    NAS_MEM_CPY_S(stHrpdSessionInfo.stUatiInfo.aucCurUATI,
                  sizeof(stHrpdSessionInfo.stUatiInfo.aucCurUATI),
                  pstUatiInfo->aucCurUATI,
                  sizeof(VOS_UINT8) * CNAS_NVIM_UATI_OCTET_LENGTH);

    /* Update the loc info values to nv */
    pstLocInfo     = CNAS_HSM_GetLocInfoAddr();

    stHrpdSessionInfo.stLocInfo.lLatitude  = pstLocInfo->lLatitude;
    stHrpdSessionInfo.stLocInfo.lLongitude = pstLocInfo->lLongitude;

    if (NV_OK != NV_Write(en_Nv_Item_CNAS_HRPD_Session_Info,
                          &stHrpdSessionInfo, sizeof(CNAS_NVIM_HRPD_SESSION_INFO_STRU)))
    {
        /* Make Error log is NV Write Fails */
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_WriteHrpdSessionInfoNvim: Error in NV Write!");

        return;
    }

    CNAS_MNTN_LogWriteNVInfo(en_Nv_Item_CNAS_HRPD_Session_Info,
                             sizeof(CNAS_NVIM_HRPD_SESSION_INFO_STRU),
                             UEPS_PID_HSM,
                             (VOS_UINT8 *)&stHrpdSessionInfo);
}
/*****************************************************************************
Function Name   :   CNAS_HSM_ReadHrpdSessionInfoExNvim
Description     :   Read en_Nv_Item_HRPD_Session_Info_Ex proc
Input parameters:   None
Outout parameters:  None
Return Value    :   None

Modify History  :
1)  Date           : 2015-09-18
    Author         : m00312079
    Modify content : Create
2)  Date           : 2015-12-21
    Author         : m00312079
    Modify content : DTS2015120208895,增加读取与session关联的UE的版本信息
*****************************************************************************/
VOS_VOID CNAS_HSM_ReadHrpdSessionInfoExNvim(VOS_VOID)
{
    CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU                     stHrpdSessionInfoEx;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                        *pstLastHrpdUERevInfo;

    NAS_MEM_SET_S(&stHrpdSessionInfoEx, sizeof(stHrpdSessionInfoEx), 0, sizeof(CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU));

    if (NV_OK != NV_Read(en_NV_Item_CNAS_HRPD_Session_Info_Ex, &stHrpdSessionInfoEx,
                         sizeof(CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ReadHrpdSessionInfoExNvim: Read Nvim Failed");

        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_CNAS_HRPD_Session_Info_Ex,
                            sizeof(CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU),
                            UEPS_PID_HSM,
                            (VOS_UINT8 *)&stHrpdSessionInfoEx);

    CNAS_HSM_SetSessionSeed(stHrpdSessionInfoEx.ulSessionSeed);

    pstLastHrpdUERevInfo = CNAS_HSM_GetLastHrpdUERevInfoCtxAddr();

    NAS_MEM_CPY_S(pstLastHrpdUERevInfo,
                  sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU),
                  &(stHrpdSessionInfoEx.stUERevInfo),
                  sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU));
}

/*****************************************************************************
Function Name   :   CNAS_HSM_WriteHrpdSessionInfoExNvim
Description     :   Write en_Nv_Item_HRPD_Session_Info_Ex
Input parameters:   None

Outout parameters:  None
Return Value    :   None

Modify History  :
1)  Date           : 2015-09-18
    Author         : m00312079
    Modify content : Create
2)  Date           : 2015-09-23
    Author         : t00323010
    Modify content : HSM MNTN(DTS2015092201636): log write NV
3)  Date           : 2015-12-21
    Author         : m00312079
    Modify content : DTS2015120208895: 增加UE的版本信息
*****************************************************************************/
VOS_VOID CNAS_HSM_WriteHrpdSessionInfoExNvim(VOS_VOID)
{
    CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU                     stHrpdSessionInfoEx;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                        *pstHrpdUERevInfo;

    NAS_MEM_SET_S(&stHrpdSessionInfoEx, sizeof(stHrpdSessionInfoEx), 0, sizeof(CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU));

    stHrpdSessionInfoEx.ulSessionSeed = CNAS_HSM_GetSessionSeed();

    pstHrpdUERevInfo = CNAS_HSM_GetHrpdUERevInfoCtxAddr();

    NAS_MEM_CPY_S(&(stHrpdSessionInfoEx.stUERevInfo),
                  sizeof(stHrpdSessionInfoEx.stUERevInfo),
                  pstHrpdUERevInfo,
                  sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU));

    if (NV_OK != NV_Write(en_NV_Item_CNAS_HRPD_Session_Info_Ex,
                          &stHrpdSessionInfoEx, sizeof(CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU)))
    {
        /* Make Error log is NV Write Fails */
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_WriteHrpdSessionInfoNvimEx: Error in NV Write!");

        return;
    }

    CNAS_MNTN_LogWriteNVInfo(en_NV_Item_CNAS_HRPD_Session_Info_Ex,
                            sizeof(CNAS_NVIM_HRPD_SESSION_INFO_EX_STRU),
                            UEPS_PID_HSM,
                            (VOS_UINT8 *)&stHrpdSessionInfoEx);
}


VOS_VOID CNAS_HSM_ReadHrpdUERevInfoNvim(VOS_VOID)
{
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                        *pstHrpdUERevInfo;
    CNAS_NVIM_HRPD_UE_REV_INFO_STRU                         stHrpdUERevInfo;

    NAS_MEM_SET_S(&stHrpdUERevInfo, sizeof(stHrpdUERevInfo), 0, sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_CAS_HRPD_NVIM_AT_REV, &stHrpdUERevInfo,
                         sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ReadHrpdUERevInfoNvim: Read Nvim Failed");

        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_CAS_HRPD_NVIM_AT_REV,
                            sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU),
                            UEPS_PID_HSM,
                            (VOS_UINT8 *)&stHrpdUERevInfo);

    pstHrpdUERevInfo = CNAS_HSM_GetHrpdUERevInfoCtxAddr();

    NAS_MEM_CPY_S(pstHrpdUERevInfo, sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU), &stHrpdUERevInfo, sizeof(CNAS_NVIM_HRPD_UE_REV_INFO_STRU));

}




VOS_VOID CNAS_HSM_ReadHrpdSessionCtrlCfgNvim(VOS_VOID)
{
    CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU                     stHrpdSessionCtrlCfg;
    CNAS_HSM_WAIT_UATI_ASSIGN_TIMER_LEN_INFO_STRU          *pstWaitUatiAssignTimerLenInfoAddr;
    VOS_UINT8                                               ucWaitUatiAssignTimerLen;
    VOS_UINT8                                               ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen;

    NAS_MEM_SET_S(&stHrpdSessionCtrlCfg, sizeof(stHrpdSessionCtrlCfg), 0, sizeof(CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU));

    ucWaitUatiAssignTimerLen = 0;

    if (NV_OK != NV_Read(en_NV_Item_CNAS_HRPD_Session_Ctrl_Cfg, &stHrpdSessionCtrlCfg,
                         sizeof(CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ReadHrpdSessionCtrlCfgNvim: Read Nvim Failed");

        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_CNAS_HRPD_Session_Ctrl_Cfg,
                            sizeof(CNAS_HSM_NVIM_SESSION_CTRL_CFG_STRU),
                            UEPS_PID_HSM,
                            (VOS_UINT8 *)&stHrpdSessionCtrlCfg);

    CNAS_HSM_SetStartUatiReqAfterSectorIdChgFlg(stHrpdSessionCtrlCfg.ucStartUatiReqAfterSectorIdChgFlg);

    pstWaitUatiAssignTimerLenInfoAddr = CNAS_HSM_GetWaitUatiAssignTimerLenInfoAddr();

    CNAS_HSM_ProcWaitUaitAssignTimerLen(stHrpdSessionCtrlCfg.ucWaitUatiAssignTimerLenInAmpSetup,&ucWaitUatiAssignTimerLen);
    pstWaitUatiAssignTimerLenInfoAddr->ucWaitUatiAssignTimerLenInAmpSetup = ucWaitUatiAssignTimerLen;

    CNAS_HSM_ProcWaitUaitAssignTimerLen(stHrpdSessionCtrlCfg.ucWaitUatiAssignTimerLenInAmpOpen,&ucWaitUatiAssignTimerLen);
    pstWaitUatiAssignTimerLenInfoAddr->ucWaitUatiAssignTimerLenInAmpOpen  = ucWaitUatiAssignTimerLen;

    ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen = stHrpdSessionCtrlCfg.ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen;

    if (ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen > (CNAS_HSM_UATI_ASSIGN_TIMEOUT_MAX_CNT - 1))
    {
        /* uati req 最大重试4次 */
        ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen = CNAS_HSM_UATI_ASSIGN_TIMEOUT_MAX_CNT - 1;
    }

    CNAS_HSM_SetUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen(ucUatiReqRetryTimesWhenUatiAssignTimerExpireInAmpOpen);
}



VOS_VOID CNAS_HSM_ReadHrpdAccessAuthInfoNvim(VOS_VOID)
{
    CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU                    stHrpdAccessAuthInfo;
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstLastHrpdAccessAuthInfo;

    pstLastHrpdAccessAuthInfo = CNAS_HSM_GetLastHrpdAccessAuthInfoCtxAddr();

    NAS_MEM_SET_S(&stHrpdAccessAuthInfo, sizeof(stHrpdAccessAuthInfo), 0, sizeof(CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU));

    if (NV_OK != NV_Read(en_Nv_Item_CNAS_HRPD_ACCESS_AUTH_INFO, &stHrpdAccessAuthInfo,
                         sizeof(CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_ReadHrpdAccessAuthInfoNvim: Read Nvim Failed");

        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_Nv_Item_CNAS_HRPD_ACCESS_AUTH_INFO,
                            sizeof(CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU),
                            UEPS_PID_HSM,
                            (VOS_UINT8 *)&stHrpdAccessAuthInfo);

    pstLastHrpdAccessAuthInfo->ucAccessAuthAvailFlag   = stHrpdAccessAuthInfo.ucAccessAuthAvailFlag;

    if (VOS_TRUE == stHrpdAccessAuthInfo.ucAccessAuthAvailFlag)
    {
        pstLastHrpdAccessAuthInfo->ucAccessAuthUserNameLen = stHrpdAccessAuthInfo.ucAccessAuthUserNameLen;
        NAS_MEM_CPY_S(pstLastHrpdAccessAuthInfo->aucAccessAuthUserName,
                      sizeof(pstLastHrpdAccessAuthInfo->aucAccessAuthUserName),
                      stHrpdAccessAuthInfo.aucAccessAuthUserName,
                      stHrpdAccessAuthInfo.ucAccessAuthUserNameLen);
    }
}


VOS_VOID CNAS_HSM_WriteHrpdAccessAuthInfoNvim(VOS_VOID)
{
    CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU                    stHrpdAccessAuthInfo;
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstCurAccessAuthInfo = VOS_NULL_PTR;

    NAS_MEM_SET_S(&stHrpdAccessAuthInfo, sizeof(stHrpdAccessAuthInfo), 0, sizeof(CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU));

    pstCurAccessAuthInfo = CNAS_CCB_GetHrpdAccesAuthInfoAddr();
    if ((CNAS_HSM_SESSION_STATUS_OPEN == CNAS_HSM_GetSessionStatus())
     && (VOS_TRUE == pstCurAccessAuthInfo->ucAccessAuthAvailFlag))
    {
        stHrpdAccessAuthInfo.ucAccessAuthAvailFlag   = VOS_TRUE;
        stHrpdAccessAuthInfo.ucAccessAuthUserNameLen = pstCurAccessAuthInfo->ucAccessAuthUserNameLen;
        NAS_MEM_CPY_S(stHrpdAccessAuthInfo.aucAccessAuthUserName,
                      sizeof(stHrpdAccessAuthInfo.aucAccessAuthUserName),
                      pstCurAccessAuthInfo->aucAccessAuthUserName,
                      pstCurAccessAuthInfo->ucAccessAuthUserNameLen);
    }
    else
    {
        stHrpdAccessAuthInfo.ucAccessAuthAvailFlag   = VOS_FALSE;
    }

    if (NV_OK != NV_Write(en_Nv_Item_CNAS_HRPD_ACCESS_AUTH_INFO,
                          &stHrpdAccessAuthInfo, sizeof(CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU)))
    {
        /* Make Error log is NV Write Fails */
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_WriteHrpdAccessAuthInfoNvim: Error in NV Write!");

        return;
    }

    CNAS_MNTN_LogWriteNVInfo(en_Nv_Item_CNAS_HRPD_ACCESS_AUTH_INFO,
                            sizeof(CNAS_NVIM_HRPD_ACCESS_AUTH_INFO_STRU),
                            UEPS_PID_HSM,
                            (VOS_UINT8 *)&stHrpdAccessAuthInfo);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

