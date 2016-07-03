

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "CnasXsdSndMscc.h"
#include  "PsCommonDef.h"
#include  "CnasMntn.h"

#include "CnasXsdComFunc.h"
#include "CnasCcb.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_SND_MSCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID CNAS_XSD_SndMsccStartCnf(
    XSD_MSCC_START_RESULT_ENUM_UINT32    enRslt
)
{
    XSD_MSCC_START_CNF_STRU            *pstStartCnf  = VOS_NULL_PTR;

    /* 分配消息 */
    pstStartCnf = (XSD_MSCC_START_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_START_CNF_STRU));
    if (VOS_NULL_PTR == pstStartCnf)
    {
        return;
    }

    /* 填充消息 */
    pstStartCnf->stMsgHeader.ulReceiverPid  = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstStartCnf->stMsgHeader.ulMsgName      = ID_XSD_MSCC_START_CNF;
    pstStartCnf->enRslt                     = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStartCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstStartCnf);

}


VOS_VOID CNAS_XSD_SndMsccPowerOffCnf(VOS_VOID)
{
    XSD_MSCC_POWER_OFF_CNF_STRU        *pstPowerOffCnf  = VOS_NULL_PTR;

    /* 分配消息 */
    pstPowerOffCnf = (XSD_MSCC_POWER_OFF_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_POWER_OFF_CNF_STRU));
    if (VOS_NULL_PTR == pstPowerOffCnf)
    {
        return;
    }

    /* 填充消息 */
    pstPowerOffCnf->MsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstPowerOffCnf->MsgHeader.ulMsgName           = ID_XSD_MSCC_POWER_OFF_CNF;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPowerOffCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstPowerOffCnf);

}


VOS_VOID CNAS_XSD_SndMsccSysAcqCnf(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32    enRslt
)
{
    XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU    *pstSysAcqCnf  = VOS_NULL_PTR;

    /* 分配消息 */
    pstSysAcqCnf = (XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU));
    if (VOS_NULL_PTR == pstSysAcqCnf)
    {
        return;
    }

    /* 填充消息 */
    pstSysAcqCnf->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysAcqCnf->stMsgHeader.ulMsgName         = ID_XSD_MSCC_SYSTEM_ACQUIRE_CNF;
    pstSysAcqCnf->enRslt                        = enRslt;



    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysAcqCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysAcqCnf);

}


VOS_VOID CNAS_XSD_SndMsccSysAcqInd(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32    enRslt
)
{
    XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU    *pstSysAcqInd  = VOS_NULL_PTR;

    /* 分配消息 */
    pstSysAcqInd = (XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU));
    if (VOS_NULL_PTR == pstSysAcqInd)
    {
        return;
    }

    /* 填充消息 */
    pstSysAcqInd->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysAcqInd->stMsgHeader.ulMsgName         = ID_XSD_MSCC_SYSTEM_ACQUIRE_IND;
    pstSysAcqInd->enRslt                        = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysAcqInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysAcqInd);

}


VOS_VOID CNAS_XSD_SndMsccSysSrvInfoInd(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU         *pstSysInfo
)
{
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU           *pstSysInfoInd  = VOS_NULL_PTR;

    /* 分配消息 */
    pstSysInfoInd = (XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSysInfoInd)
    {
        return;
    }

    /* 填充消息 */
    pstSysInfoInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysInfoInd->stMsgHeader.ulMsgName        = ID_XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND;

    /* 填充系统消息 */
    NAS_MEM_CPY_S(&(pstSysInfoInd->stSysSrvInfo), sizeof(pstSysInfoInd->stSysSrvInfo), pstSysInfo, sizeof(NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysInfoInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysInfoInd);
}


VOS_VOID CNAS_XSD_SndMsccSysAcqStartInd(VOS_VOID)
{
    XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU                     *pstSysAcqStartInd  = VOS_NULL_PTR;

    /* 分配消息 */
    pstSysAcqStartInd = (XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU));
    if (VOS_NULL_PTR == pstSysAcqStartInd)
    {
        return;
    }

    /* 填充消息 */
    pstSysAcqStartInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysAcqStartInd->stMsgHeader.ulMsgName        = ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysAcqStartInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysAcqStartInd);

}



VOS_VOID CNAS_XSD_BuildMsccSysInfoInd(
    CAS_CNAS_1X_OHM_IND_STRU           *pstCasCnas1xOhmInd,
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstXsdMmaSysInfo
)
{
    pstXsdMmaSysInfo->usBandClass = pstCasCnas1xOhmInd->usBandClass;
    pstXsdMmaSysInfo->usFreq      = pstCasCnas1xOhmInd->usFreq;
    pstXsdMmaSysInfo->usSid       = pstCasCnas1xOhmInd->usSid;
    pstXsdMmaSysInfo->usNid       = pstCasCnas1xOhmInd->usNid;
    pstXsdMmaSysInfo->ucPzid      = pstCasCnas1xOhmInd->ucPacketZoneId;
    pstXsdMmaSysInfo->ucPrevInUse = pstCasCnas1xOhmInd->ucPRevInUse;


    pstXsdMmaSysInfo->enRegInfoIncl            = pstCasCnas1xOhmInd->enRegInfoIncl;
    pstXsdMmaSysInfo->enBaseStationInfoIncl    = pstCasCnas1xOhmInd->enBaseStationInfoIncl;
    pstXsdMmaSysInfo->enServiceInfoIncl        = pstCasCnas1xOhmInd->enServiceInfoIncl;
    pstXsdMmaSysInfo->stRegInfo.usRegZone      = pstCasCnas1xOhmInd->stRegInfo.usRegZone;
    pstXsdMmaSysInfo->stRegInfo.ucRegZoneNum   = pstCasCnas1xOhmInd->stRegInfo.ucRegZoneNum;
    pstXsdMmaSysInfo->stRegInfo.ucZoneTimer    = pstCasCnas1xOhmInd->stRegInfo.ucZoneTimer;
    pstXsdMmaSysInfo->stRegInfo.ucMultiSidFlg  = pstCasCnas1xOhmInd->stRegInfo.ucMultiSidFlg;
    pstXsdMmaSysInfo->stRegInfo.ucMultiNidFlg  = pstCasCnas1xOhmInd->stRegInfo.ucMultiNidFlg;
    pstXsdMmaSysInfo->stRegInfo.usRegDistance  = pstCasCnas1xOhmInd->stRegInfo.usRegDistance;
    pstXsdMmaSysInfo->stRegInfo.ucRegPeriod    = pstCasCnas1xOhmInd->stRegInfo.ucRegPeriod;
    pstXsdMmaSysInfo->stRegInfo.ucHomeReg      = pstCasCnas1xOhmInd->stRegInfo.ucHomeReg;
    pstXsdMmaSysInfo->stRegInfo.ucSidRoamReg   = pstCasCnas1xOhmInd->stRegInfo.ucSidRoamReg;
    pstXsdMmaSysInfo->stRegInfo.ucNidRoamReg   = pstCasCnas1xOhmInd->stRegInfo.ucNidRoamReg;
    pstXsdMmaSysInfo->stRegInfo.ucPowerUpReg   = pstCasCnas1xOhmInd->stRegInfo.ucPowerUpReg;
    pstXsdMmaSysInfo->stRegInfo.ucPowerDownReg = pstCasCnas1xOhmInd->stRegInfo.ucPowerDownReg;
    pstXsdMmaSysInfo->stRegInfo.ucParameterReg = pstCasCnas1xOhmInd->stRegInfo.ucParameterReg;


    pstXsdMmaSysInfo->stBaseStationInfo.usBaseId        = pstCasCnas1xOhmInd->stBaseStationInfo.usBaseId;
    pstXsdMmaSysInfo->stBaseStationInfo.ucBaseClass     = pstCasCnas1xOhmInd->stBaseStationInfo.ucBaseClass;
    pstXsdMmaSysInfo->stBaseStationInfo.lBaseLatitude   = pstCasCnas1xOhmInd->stBaseStationInfo.lBaseLatitude;
    pstXsdMmaSysInfo->stBaseStationInfo.lBaseLongitude  = pstCasCnas1xOhmInd->stBaseStationInfo.lBaseLongitude;

    pstXsdMmaSysInfo->stServiceInfo.ucMaxAltSo            = pstCasCnas1xOhmInd->stServiceInfo.ucMaxAltSo;
    pstXsdMmaSysInfo->stServiceInfo.ucSDBSupported        = pstCasCnas1xOhmInd->stServiceInfo.ucSDBSupported;
    pstXsdMmaSysInfo->stServiceInfo.ucMoQos               = pstCasCnas1xOhmInd->stServiceInfo.ucMoQos;
    pstXsdMmaSysInfo->stServiceInfo.ucConcurrentSupported = pstCasCnas1xOhmInd->stServiceInfo.ucConcurrentSupported;
    pstXsdMmaSysInfo->stServiceInfo.ucMoPosSupported      = pstCasCnas1xOhmInd->stServiceInfo.ucMoPosSupported;


    pstXsdMmaSysInfo->stServiceInfo.ulMcc        = CNAS_XSD_TransformMccToBcd(pstCasCnas1xOhmInd->stServiceInfo.usMcc);
    pstXsdMmaSysInfo->stServiceInfo.usImsi11_12  = CNAS_XSD_TransformImsiToBcd(pstCasCnas1xOhmInd->stServiceInfo.ucImsi11_12);

    /* 目前接入层无法上报MNC，因此这里默认将MNC的值设置为无效值 */
    pstXsdMmaSysInfo->stServiceInfo.usMnc        = pstXsdMmaSysInfo->stServiceInfo.usImsi11_12;


    return;
}


VOS_VOID CNAS_XSD_SndMscc1xSysTimeInd(
    NAS_MSCC_PIF_1X_SYS_TIME_STRU      *pst1xSysTimeInfo
)
{
    XSD_MSCC_1X_SYSTEM_TIME_IND_STRU   *pst1xSysTimeInd  = VOS_NULL_PTR;

    /* 分配消息 */
    pst1xSysTimeInd = (XSD_MSCC_1X_SYSTEM_TIME_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_1X_SYSTEM_TIME_IND_STRU));
    if (VOS_NULL_PTR == pst1xSysTimeInd)
    {
        return;
    }

    /* 填充消息 */
    pst1xSysTimeInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pst1xSysTimeInd->stMsgHeader.ulMsgName        = ID_XSD_MSCC_1X_SYSTEM_TIME_IND;

    /* 填充系统消息 */
    NAS_MEM_CPY_S(&(pst1xSysTimeInd->stSysTime), sizeof(pst1xSysTimeInd->stSysTime), pst1xSysTimeInfo, sizeof(NAS_MSCC_PIF_1X_SYS_TIME_STRU));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pst1xSysTimeInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pst1xSysTimeInd);

    return;
}


VOS_VOID CNAS_XSD_SndCdmaCsqSetCnf(
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8      enRslt
)
{
    XSD_MSCC_CDMACSQ_SET_CNF_STRU    *pstCdmaCsqCnf  = VOS_NULL_PTR;

    /* 分配消息 */
    pstCdmaCsqCnf = (XSD_MSCC_CDMACSQ_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_CDMACSQ_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstCdmaCsqCnf)
    {
        return;
    }

    /* 填充消息 */
    pstCdmaCsqCnf->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstCdmaCsqCnf->stMsgHeader.ulMsgName        = ID_XSD_MSCC_CDMACSQ_SET_CNF;
    pstCdmaCsqCnf->enRslt                       = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCdmaCsqCnf);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCdmaCsqCnf);

    return;
}

VOS_VOID CNAS_XSD_SndCdmaCsqInd(
    VOS_INT16                           sCdmaRssi,
    VOS_INT16                           sCdmaEcIo
)
{
    XSD_MSCC_CDMACSQ_IND_STRU    *pstCdmaCsqInd  = VOS_NULL_PTR;

    /* 分配消息 */
    pstCdmaCsqInd = (XSD_MSCC_CDMACSQ_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_CDMACSQ_IND_STRU));
    if (VOS_NULL_PTR == pstCdmaCsqInd)
    {
        return;
    }

    /* 填充消息 */
    pstCdmaCsqInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstCdmaCsqInd->stMsgHeader.ulMsgName        = ID_XSD_MSCC_CDMACSQ_SIGNAL_QUALITY_IND;
    pstCdmaCsqInd->sCdmaRssi                    = sCdmaRssi;
    pstCdmaCsqInd->sCdmaEcIo                    = sCdmaEcIo;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCdmaCsqInd);


    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCdmaCsqInd);

    return;

}



VOS_VOID CNAS_XSD_SndMsccSysCfgCnf(
    CAS_CNAS_1X_SYS_CFG_CNF_STRU       *pstRcvMsg
)
{
    XSD_MSCC_SYS_CFG_CNF_STRU          *pstSysCfgCnfMsg = VOS_NULL_PTR;

    /* 分配消息 */
    pstSysCfgCnfMsg = (XSD_MSCC_SYS_CFG_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_SYS_CFG_CNF_STRU));
    if (VOS_NULL_PTR == pstSysCfgCnfMsg)
    {
        return;
    }

    /* 填充消息 */
    pstSysCfgCnfMsg->MsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysCfgCnfMsg->MsgHeader.ulMsgName        = ID_XSD_MSCC_SYS_CFG_CNF;
    pstSysCfgCnfMsg->enRst                      = NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS;
    pstSysCfgCnfMsg->usOpId                     = pstRcvMsg->usOpId;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysCfgCnfMsg);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSysCfgCnfMsg);

    return;
}




VOS_VOID CNAS_XSD_SndMsccPowerSaveCnf(
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enResult
)
{
    XSD_MSCC_POWER_SAVE_CNF_STRU        *pstPowerSaveCnf  = VOS_NULL_PTR;

    pstPowerSaveCnf = (XSD_MSCC_POWER_SAVE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                      sizeof(XSD_MSCC_POWER_SAVE_CNF_STRU));
    if (VOS_NULL_PTR == pstPowerSaveCnf)
    {
        return;
    }

    /* Constructing the Power Save Cnf message */
    pstPowerSaveCnf->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstPowerSaveCnf->stMsgHeader.ulSenderPid         = UEPS_PID_XSD;
    pstPowerSaveCnf->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPowerSaveCnf->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstPowerSaveCnf->stMsgHeader.ulLength            = sizeof(XSD_MSCC_POWER_SAVE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPowerSaveCnf->stMsgHeader.ulMsgName           = ID_XSD_MSCC_POWER_SAVE_CNF;
    pstPowerSaveCnf->enResult                        = enResult;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPowerSaveCnf);

    /* Send the message */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstPowerSaveCnf);

}


VOS_VOID CNAS_XSD_SndMsccHandSetInfoCnf(
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *pstHandSetInfo
)
{
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *pstInfoCnf  = VOS_NULL_PTR;

    pstInfoCnf = (XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                        sizeof(XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstInfoCnf)
    {
        return;
    }

    /* Constructing the Power Save Cnf message */
    pstInfoCnf->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstInfoCnf->stMsgHeader.ulSenderPid         = UEPS_PID_XSD;
    pstInfoCnf->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstInfoCnf->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstInfoCnf->stMsgHeader.ulLength            = sizeof(XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInfoCnf->stMsgHeader.ulMsgName           = ID_XSD_MSCC_HANDSET_INFO_QRY_CNF;

    pstInfoCnf->ulInfoType                      = pstHandSetInfo->ulInfoType;
    pstInfoCnf->ucCasState                      = pstHandSetInfo->ucCasState;
    pstInfoCnf->ucCasSubSta                     = pstHandSetInfo->ucCasSubSta;
    pstInfoCnf->ucHighVer                       = pstHandSetInfo->ucHighVer;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstInfoCnf);

    /* Send the message */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstInfoCnf);

    return;
}


VOS_VOID CNAS_XSD_SndMsccRfAvailInd(
    VOS_UINT8                           ucRfAvail
)
{
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU *pstRfAvailInd = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength     = sizeof(NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstRfAvailInd   = (NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstRfAvailInd)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8 *)pstRfAvailInd) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstRfAvailInd->stMsgHeader.ulMsgName           = ID_XSD_MSCC_RF_AVAILABLE_IND;
    pstRfAvailInd->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulSenderPid         = UEPS_PID_XSD;
    pstRfAvailInd->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstRfAvailInd->stMsgHeader.ulLength            = ulMsgLength;
    pstRfAvailInd->ucRfAvailFlg                    = ucRfAvail;
    pstRfAvailInd->enRatType                       = NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_1X;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstRfAvailInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstRfAvailInd);

    return;
}


VOS_VOID CNAS_XSD_SndMsccSrvAcqCnf(
    NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8                  enResult
)
{
    XSD_MSCC_SRV_ACQ_CNF_STRU                              *pstSrvAcqCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength     = sizeof(XSD_MSCC_SRV_ACQ_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSrvAcqCnf    = (XSD_MSCC_SRV_ACQ_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstSrvAcqCnf)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8*)pstSrvAcqCnf) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstSrvAcqCnf->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSrvAcqCnf->stMsgHeader.ulSenderPid       = UEPS_PID_XSD;
    pstSrvAcqCnf->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSrvAcqCnf->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSrvAcqCnf->stMsgHeader.ulLength          = ulMsgLength;
    pstSrvAcqCnf->stMsgHeader.ulMsgName         = ID_XSD_MSCC_SRV_ACQ_CNF;

    pstSrvAcqCnf->enResult                      = enResult;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSrvAcqCnf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSrvAcqCnf);

    return;
}




VOS_VOID CNAS_XSD_SndMsccSidNidInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid
)
{
    MSCC_XSD_SID_NID_IND_STRU              *pstSidNidInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstSidNidInd = (MSCC_XSD_SID_NID_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD, sizeof(MSCC_XSD_SID_NID_IND_STRU));

    if (VOS_NULL_PTR == pstSidNidInd)
    {
        return;
    }

    NAS_MEM_SET_S(pstSidNidInd, sizeof(MSCC_XSD_SID_NID_IND_STRU), 0, sizeof(MSCC_XSD_SID_NID_IND_STRU));

    /* 填充消息 */
    pstSidNidInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSidNidInd->stMsgHeader.ulSenderPid     = UEPS_PID_XSD;
    pstSidNidInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSidNidInd->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSidNidInd->stMsgHeader.ulLength        = sizeof(MSCC_XSD_SID_NID_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSidNidInd->stMsgHeader.ulMsgName       = ID_XSD_MSCC_SID_NID_IND;

    pstSidNidInd->usSid                       = usSid;
    pstSidNidInd->usNid                       = usNid;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSidNidInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSidNidInd);
}


VOS_VOID CNAS_XSD_SndMsccEmcCallBackInd(
    MSCC_XSD_EMC_CALLBACK_MODE_ENUM_UINT32                  enCallBackState
)
{
    XSD_MSCC_EMC_CALLBACK_IND_STRU                         *pstCallBackInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength     = sizeof(XSD_MSCC_EMC_CALLBACK_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCallBackInd    = (XSD_MSCC_EMC_CALLBACK_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstCallBackInd)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8*)pstCallBackInd) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstCallBackInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCallBackInd->stMsgHeader.ulSenderPid       = UEPS_PID_XSD;
    pstCallBackInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCallBackInd->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstCallBackInd->stMsgHeader.ulLength          = ulMsgLength;
    pstCallBackInd->stMsgHeader.ulMsgName         = ID_XSD_MSCC_EMC_CALLBACK_IND;

    pstCallBackInd->enCallBackState               = enCallBackState;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCallBackInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCallBackInd);

    return;
}


VOS_VOID CNAS_XSD_SndMsccSetCSidListCnf(
    VOS_UINT32                                              ulResult
)
{
    XSD_MSCC_SET_CSIDLIST_CNF_STRU                         *pstCSidListCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength                         = sizeof(XSD_MSCC_SET_CSIDLIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCSidListCnf                      = (XSD_MSCC_SET_CSIDLIST_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstCSidListCnf)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8*)pstCSidListCnf) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstCSidListCnf->stMsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstCSidListCnf->stMsgHeader.ulSenderPid                 = UEPS_PID_XSD;
    pstCSidListCnf->stMsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstCSidListCnf->stMsgHeader.ulReceiverPid               = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstCSidListCnf->stMsgHeader.ulLength                    = ulMsgLength;
    pstCSidListCnf->stMsgHeader.ulMsgName                   = ID_XSD_MSCC_SET_CSIDLIST_CNF;

    pstCSidListCnf->ulRslt                                  = ulResult;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCSidListCnf);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstCSidListCnf);

    return;
}


VOS_VOID CNAS_XSD_SndMsccSyncServiceAvailableInd(
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU               *pstSrvAvailInd
)
{
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU               *pstSrvAvailableInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength        = sizeof(XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSrvAvailableInd = (XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_XSD, ulMsgLength);

    if (VOS_NULL_PTR == pstSrvAvailableInd)
    {
        return;
    }

    NAS_MEM_SET_S(((VOS_UINT8*)pstSrvAvailableInd) + VOS_MSG_HEAD_LENGTH, ulMsgLength, 0x00, ulMsgLength);

    pstSrvAvailableInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSrvAvailableInd->stMsgHeader.ulSenderPid     = UEPS_PID_XSD;
    pstSrvAvailableInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSrvAvailableInd->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSrvAvailableInd->stMsgHeader.ulLength        = ulMsgLength;
    pstSrvAvailableInd->stMsgHeader.ulMsgName       = ID_XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND;

    pstSrvAvailableInd->usFreq                      = pstSrvAvailInd->usFreq;
    pstSrvAvailableInd->usBandClass                 = pstSrvAvailInd->usBandClass;
    pstSrvAvailableInd->usSid                       = pstSrvAvailInd->usSid;
    pstSrvAvailableInd->usNid                       = pstSrvAvailInd->usNid;
    pstSrvAvailableInd->enServiceStatus             = pstSrvAvailInd->enServiceStatus;
    pstSrvAvailableInd->ucRoamingInd                = pstSrvAvailInd->ucRoamingInd;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSrvAvailableInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstSrvAvailableInd);

    return;
}



VOS_VOID CNAS_XSD_SndMsccUeStatusInd(
    VOS_UINT8                           ucUeMainState,
    VOS_UINT8                           ucUeSubState
)
{
    XSD_MSCC_UE_STATE_IND_STRU         *pstUeStatus  = VOS_NULL_PTR;

    /* 分配消息 */
    pstUeStatus = (XSD_MSCC_UE_STATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                                                    sizeof(XSD_MSCC_UE_STATE_IND_STRU));
    if (VOS_NULL_PTR == pstUeStatus)
    {
        return;
    }

    /* 填充消息 */
    pstUeStatus->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstUeStatus->ulSenderPid        = UEPS_PID_XSD;
    pstUeStatus->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstUeStatus->ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstUeStatus->ulLength           = sizeof(XSD_MSCC_UE_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstUeStatus->enMsgId            = ID_XSD_MSCC_CDMA_UE_STATUS_IND;
    pstUeStatus->ucUeMainState      = ucUeMainState;
    pstUeStatus->ucUeSubState       = ucUeSubState;

    pstUeStatus->aucReserve[0]      = 0;
    pstUeStatus->aucReserve[1]      = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstUeStatus);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pstUeStatus);

    return;

}


VOS_VOID CNAS_XSD_SndMscc1xNoSrvInd(VOS_VOID)
{
    XSD_MSCC_1X_NO_SERVICE_IND_STRU    *pst1xNoSrvInd  = VOS_NULL_PTR;

    /* 分配消息 */
    pst1xNoSrvInd = (XSD_MSCC_1X_NO_SERVICE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XSD,
                                                    sizeof(XSD_MSCC_1X_NO_SERVICE_IND_STRU));
    if (VOS_NULL_PTR == pst1xNoSrvInd)
    {
        return;
    }

    /* 填充消息 */
    pst1xNoSrvInd->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pst1xNoSrvInd->stMsgHeader.ulSenderPid       = UEPS_PID_XSD;
    pst1xNoSrvInd->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pst1xNoSrvInd->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pst1xNoSrvInd->stMsgHeader.ulLength          = sizeof(XSD_MSCC_1X_NO_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH;;
    pst1xNoSrvInd->stMsgHeader.ulMsgName         = ID_XSD_MSCC_1X_NO_SERVICE_IND;

    NAS_MEM_SET_S(pst1xNoSrvInd->aucReserve, sizeof(pst1xNoSrvInd->aucReserve), 0, sizeof(pst1xNoSrvInd->aucReserve));


    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pst1xNoSrvInd);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XSD, pst1xNoSrvInd);

    return;

}

#endif





/*lint -restore*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

