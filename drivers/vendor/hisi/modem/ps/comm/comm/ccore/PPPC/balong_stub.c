/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "v_lib.h"
#include "v_typdef.h"
#include "vrpcfg.h"

#include "PsCommonDef.h"

#include "vrpcfg.h"
#include "balong_stub.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
VOS_UINT32 g_ulA11RpifIp = 0;


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

VOS_UINT32 L2TP_SeparateUserName(CHAR *szUserName, CHAR *szDomain, CHAR *szUserAbbr)
{
    return 0;
}

VOS_VOID A11_PPP_TermTag(VOS_UINT32 ulPdpIndex, UCHAR ucFlag)
{
    return;
}

VOS_UINT32 DVM_GetSelfCpuId(VOS_VOID)
{
    return 0;
}

VOS_UINT32 SDB_GetRpContextByIndex(VOS_UINT32 ulIndex, VOS_VOID **ppucContext)
{
    return SDB_SUCCESS;
}


VOID HSGW_EmsTraceByRpIndex(VOS_UINT32 ulRpIndex, VOS_UINT32 ulModule, VOS_UINT32 ulCode)
{
    return;
}

VOS_VOID HSGW_EmsTraceByPdnIndex(VOS_UINT32 ulPdnIndex, VOS_UINT32 ulModule, VOS_UINT32 ulCode)
{
    return;
}

VOS_UINT32 A11_GetCompStatNum(SC_COMPRESS_STATE_S * pstCompStatInfo)
{
    return VOS_OK;
}

VOS_VOID A11_OM_HSGWPerfStatisticPCFUnit(VOS_UINT32 ulStatisticType, VOS_UINT32 ulPcfIp, VOS_UINT32 ulOperType, VOS_UINT32 ulValue)
{
    return;
}

VOS_VOID A11_OM_PerfStatisticPCFUnit(VOS_UINT32 ulStatisticType, VOS_UINT32 ulPcfIp)
{
    return;
}

VOS_UINT32 USM_NotifyPhaseResultFunc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulMsgtype,
                                            VOS_VOID *pResultInfo)
{
    return VOS_OK;
}

VOS_UINT32 A11_VirtualDomainMapping(VOS_UINT16 usVirtualDomainIndex,
                               A11_IMSI_S stIMSI,
                               VOS_UINT16 *pusRealDomainIndex)
{
    return VOS_OK;
}

VOS_UINT32 A11_GetVirtualDomainStatusByIndex(VOS_UINT16 usAPNIndex)
{
    return VOS_OK;
}

VOS_UINT32 SDB_GetPdnContextByIndex(VOS_UINT32 ulIndex, VOID **ppucContext)
{
    return VOS_OK;
}

VOS_UINT32 A11_A10GlobalIndexToA10ScIndex(VOS_UINT32 ulA10GlobalIndex)
{
    return VOS_OK;
}

VOS_UINT32 A11_PPPC_SendUsrInfor(VOS_UINT32                 ulRpIndex,
                            A11_PPPC_USR_INFOR_S* pstUsrInfor,
                            VOS_UINT32                 ulFlag)
{
    return VOS_OK;
}

VOS_UINT32 ALM_GetAlmSlotCpuID(VOS_VOID)
{
    return 0;
}

VOID  A11_4BitsToString( UCHAR *strSrc, UCHAR DstArr[], UCHAR ucMaxNum )
{
    return;
}

VOS_BOOL Trc_IsTraceTaskEnabled(VOS_UINT8 ucTrcType)
{
    return VOS_FALSE;
}

VOS_UINT32 USM_NotifyReleaseUserFunc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulReleaseCode, UCHAR* pucMsg)
{
    return VOS_OK;
}

VOS_UINT32 Diam_AUTHHostRemoveByAAACBIndex(VOS_UINT16 usDynAAAIndex, VOS_UINT32 ulRpIndex)
{
    return VOS_OK;
}

VOS_UINT32 PPPC_CRYPT_random (UCHAR*  pBuf, VOS_UINT32 ulLen)
{
    return VOS_OK;
}

VOS_UINT32 AlarmToFamEx(VOS_UINT32  ucSlotNo,               /* 2???o? */
                        VOS_UINT32 udwMid,                 /* 2úéú???ˉ?￡?éPID*/
                        VOS_UINT32 udwAlarmICID,           /* ???ˉ???-ID */
                        VOS_UINT8  ucAlarmType,            /* ???ˉààDí */
                        VOS_UINT8  ucParaNum,             /* ???ˉ2?êy??êy */
                        VOS_UINT8  ucValueLen[],          /* ???ˉ2?êy3¤?èáD±í */
                        VOID      *pVarValue[])            /* ???ˉ2?êyáD±í */
{
    return 0;
}

VOID Snmp_Perf( MEAOBJINDEX_STRU stMeaObj, VOS_UINT32 ulMeaType, VOS_UINT32 ulOpType )
{
    return;
}

VOS_UINT32 SPM_RegisterByte(VOS_UINT32  ulSoftparaNum,     pfSPM_ByteCallBack pfCallback)
{
    return VOS_OK;
}

VOS_UINT32 PSM_Inf_GetSGIndexBySGID(VOS_UINT64 SGID)
{
    return VOS_OK;
}

VOS_UINT32 CRM_GetSelfGroupId(VOS_VOID)
{
    return 1;
}

VOS_UINT32 PDN_PppVsncpSucc(VOS_UINT32 ulRpIndex, UCHAR ucPdnId )
{
    return 0;
}

VOS_VOID PDN_FsmStopTimer(VOS_UINT32 ulTimerType, VOS_UINT32 ulTimerId)
{
    return;
}

VOS_UINT32 USM_GetApnIndexByApnName(UCHAR *pucApnName, VOS_UINT16 *pusApnIndex)
{
    return 0;
}

VOS_UINT32 PDN_VsncpNotifyGetPCO(PDN_CONTEXT_S *pstPdnContext, PDN_PPP_VSNCP_REQ_S *pstVsncpReq)
{
    return 0;
}

VOS_UINT32 PDN_VsncpNotifyReconnect(PDN_CONTEXT_S *pstPdnContext, PDN_PPP_VSNCP_REQ_S *pstVsncpReq)
{
    return 0;
}

VOS_UINT32 PDN_PppStartEhrpdPdn(VOS_UINT32 ulRpIndex, PDN_PPP_VSNCP_REQ_S *pstVsncpReq)
{
    return 0;
}

VOS_UINT32 USM_GetApnCfgByApnIndex(VOS_UINT16 usApnIndex, HSGW_APN_INFO_S **ppstHsgwApn)
{
    return 0;
}

VOS_BOOL USM_IsDefaultApn(VOS_UINT32 ulRpIndex, VOS_UINT16 usApnIndex)
{
   return 0;
}

VOS_UINT32 IPV6_StopTimer(VOS_UINT32 ulTimerId)
{
    return 0;
}


VOS_UINT32 INST_GetSelfInstanceId(VOS_VOID)
{
    return 0;
}

VOS_UINT32 Diam_AUTHGetDynAAAInfoByIndex(VOS_UINT16 usDynAAAIndex, UCHAR *pucHost, UCHAR *pucRealm, VOS_UINT16 *pusDynPeerId)
{
    return 0;
}

VOS_UINT32 PDN_GetPdnType( VOS_UINT32 ulPdnIndex, VOS_UINT32 *pulPdnType)
{
    return 0;
}

VOS_UINT32 PDN_JudgeSubPDNStateActive(VOS_UINT32 ulRpIndex, VOS_UINT32 ulSubPdnType)
{
    return 0;
}

VOS_UINT32  RDA_GetApnDNSCfg(VOS_UINT16 usApnIndex, APNDNS_S *pstApn)
{
    return 0;
}

VOS_UINT32 Diam_AUTHBackupRebuildDynAAACB(VOS_UINT16 usNewPeerId, VOS_UINT16 usDynPeerId,
                                     UCHAR *pucAAAHost, UCHAR *pucAAARealm)
{
    return 0;
}

VOS_UINT16 GetDomainIndexByName( UCHAR*   szDomainName)
{
    return 0;
}

VOS_UINT32 Ipv6_A11NotifySendRa(VOS_UINT32 ulPdnIndex)
{
    return 0;
}

VOS_UINT32 PGP_RTDistributeSend(VOS_UINT64 ul64SrcCSI,VOS_UINT64 ul64DstCSI, VOS_VOID* pMsg, VOS_UINT32 ulLen, VOS_UINT32 ulMode, VOS_UINT32 ulMsgType)
{
    return 0;
}

VOS_UINT32 PSM_Inf_GetCmpSameTIndexInSGByCSI(VOS_UINT64 CSI)
{
    return 0;
}

VOS_UINT64 PSM_Inf_GetSelfSGID()
{
    return 1;
}

VOS_UINT32 PSM_Inf_GetCmpIndexInOSByCSI(VOS_UINT64 CSI)
{
    return 0;
}

VOS_UINT64 PSM_Inf_GetSelfCSI(VOS_UINT32 CompType)
{
    return 0;
}

VOS_UINT32 *PGP_ShrMemAllocByName(VOS_CHAR* name, UCHAR ShareMemType, VOS_UINT32 ullInfo, VOS_UINT32 uiSize)
{
    return VOS_OK;
}


VOS_UINT64 PSM_Inf_GetCSIByOSIDCmpTypeAndInstIdInOS(IN VOS_UINT32 uiChasisNo,IN VOS_UINT32 uiSlot,IN VOS_UINT32 OSID,
 IN VOS_UINT32 CmpType, IN VOS_UINT32 InstIdInOS)
{
    return 0;
}

VOS_UINT32 CRM_GetSelfGroupBoardType( CRM_SPU_BOARD_TYPE_ENUM* pMode)
{
    *pMode = CRM_BOARD_TYPE_SPUE;
    return VOS_OK;
}

VOS_UINT32 DBG_LogRecordReg(CHAR szSystemName[DBG_LOG_SYSTEM_NAME_LEN],
    CHAR szModuleName[DBG_LOG_MODULE_NAME_LEN], CHAR szSubmoduleName[DBG_LOG_SUB_MODULE_NAME_LEN],
    VOS_UINT32 *ulDBGLogRegID)
{
    return VOS_OK;

}

VOS_UINT32 PTM_CommandsRegister ( LPCommand_Group_S pCommand_Group, CHAR *cpCommand, CHAR *cpHelp , UINT64 ul64Csi)
{
    return 0;
}

VOS_VOID PGP_RTDistributeFreeMsg(VOS_VOID *pMsg)
{
    return;
}

VOS_VOID* PGP_RTDistributeAllocMsg(VOS_UINT64 selfCSI, VOS_UINT32 ulMsgLen)
{
    return VOS_NULL_PTR;
}

VOS_UINT32 VOS_Que_Read( VOS_UINT32 ulQueID, VOS_UINT32 ulRetMsg[4],
                VOS_UINT32 ulFlags, VOS_UINT32 ulTimeOutInMillSec )
{
    return 0;
}


VOS_UINT32 VOS_Ev_Write( VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents )
{
    return VOS_OK;
}

VOS_UINT32 VOS_MCReadQue(VOS_VOID* pstQueId,VOS_VOID** ppMsg,VOS_UINT32 *pulMsgLen,
                         VOS_UINT32 ulFlag,VOS_UINT32 ulMillsec)
{
    return 0;
}

VOS_UINT32 PTM_CreateQueue(PTM_QUEUE_INFO_S *pstQueInfo, VOS_UINT32* pulQueID)
{
    VOS_UINT32 ulRet = VOS_OK;

    return ulRet;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

