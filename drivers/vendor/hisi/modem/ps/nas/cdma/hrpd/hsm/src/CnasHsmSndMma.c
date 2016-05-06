

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmSndMma.h"
#include "vos.h"
#include "CnasCcb.h"
#include "CnasMntn.h"
#include "CnasHsmCtx.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_MMA_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  3 Function Define
*****************************************************************************/

/*****************************************************************************
 函 数 名  : CNAS_HSM_SndMmaHrpdInfo
 功能描述  : HSM上报mma关于HRPD 的信息
 输入参数  : pstCasOhmMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月3日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSM_SndMmaHrpdInfo(
    VOS_UINT32                          ulSessionSeed,         /*RATI*/
    VOS_UINT8                          *pucCurUATI, /*UATI*/
    HSM_MMA_SESSION_STATUS_ENUM_UINT8   ucSessionStatus
)
{
    HSM_MMA_HRPD_SYS_INFO_IND_STRU      *pstHrpdSysInfoInd = VOS_NULL_PTR;

    /* 分配消息 */
    pstHrpdSysInfoInd = (HSM_MMA_HRPD_SYS_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSM,
                    sizeof(HSM_MMA_HRPD_SYS_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstHrpdSysInfoInd)
    {
        return;
    }
    NAS_MEM_SET_S( ((VOS_UINT8 *)pstHrpdSysInfoInd + VOS_MSG_HEAD_LENGTH),
                   (VOS_SIZE_T)(sizeof(HSM_MMA_HRPD_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                   0x00,
                   (VOS_SIZE_T)(sizeof(HSM_MMA_HRPD_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH) );
    /* 填充消息 */

    CNAS_CFG_MSG_HDR(pstHrpdSysInfoInd,
                     UEPS_PID_HSM,
                     WUEPS_PID_MMA,
                     ID_HSM_MMA_HRPD_SYS_INFO_IND,
                     sizeof(HSM_MMA_HRPD_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstHrpdSysInfoInd->ulSessionSeed             = ulSessionSeed;
    pstHrpdSysInfoInd->enSessionStatus           = ucSessionStatus;
    NAS_MEM_CPY_S(pstHrpdSysInfoInd->aucCurUATI, sizeof(pstHrpdSysInfoInd->aucCurUATI), pucCurUATI, HSM_MMA_UATI_OCTET_LENGTH);

    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstHrpdSysInfoInd);

}

/*****************************************************************************
 函 数 名  : CNAS_HSM_SndMmaHardWareInfo
 功能描述  : hsm吧硬件消息ESN和MEID发给MMA用于可维可测
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月6日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CNAS_HSM_SndMmaHardWareInfo(  VOS_VOID )
{
    HSM_MMA_HARDWARE_SYS_INFO_IND_STRU  *pstSndMsg = VOS_NULL_PTR;

    CNAS_CCB_UIMID_STRU                *pstUIMID    = VOS_NULL_PTR;

    pstUIMID         = CNAS_CCB_GetUIMID();

    /* 分配消息 */
    pstSndMsg = (HSM_MMA_HARDWARE_SYS_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSM,
                    sizeof(HSM_MMA_HARDWARE_SYS_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }
    NAS_MEM_SET_S( ((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
                   (VOS_SIZE_T)(sizeof(HSM_MMA_HARDWARE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH),
                   0x00,
                   (VOS_SIZE_T)(sizeof(HSM_MMA_HARDWARE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* 填充消息 */

    CNAS_CFG_MSG_HDR(pstSndMsg,
                     UEPS_PID_HSM,
                     WUEPS_PID_MMA,
                     ID_HSM_MMA_HARDWARE_SYS_INFO_IND,
                     sizeof(HSM_MMA_HARDWARE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->ulEsn         = CNAS_HSM_GetHardwareIdInfo()->ulEsn;
    pstSndMsg->enModemId     = CNAS_CCB_GetCcbCtxAddr()->stModemInfo.enCdmaModeModemId;
    NAS_MEM_CPY_S(pstSndMsg->aucMeId, sizeof(pstSndMsg->aucMeId), CNAS_HSM_GetHardwareIdInfo()->aucMeId, HSM_MMA_MEID_OCTET_NUM);

    NAS_MEM_CPY_S(pstSndMsg->aucRuimid, sizeof(pstSndMsg->aucRuimid), pstUIMID, CNAS_HSM_EFRUIMID_OCTET_LEN_EIGHT);


    /* 发送消息 */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSM, pstSndMsg);
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */











