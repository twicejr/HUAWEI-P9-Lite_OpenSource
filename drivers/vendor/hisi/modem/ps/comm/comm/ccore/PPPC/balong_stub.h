
#ifndef      _PPP_STUB_H_
#define      _PPP_STUB_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */



#define VOS_iscntrl(c)      ((((c)>=0)&&((c)<=0x1f))?1:0)
#define VOS_isupper(c)      ((c) >= 'A' && (c) <= 'Z')
#define VOS_islower(c)      ((c) >= 'a' && (c) <= 'z')
#define VOS_isalpha(c)      ((VOS_isupper(c)) || ((VOS_islower(c))))

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (VOS_UINT32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (VOS_UINT32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (VOS_UINT32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (VOS_UINT32)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

  #define A11_SNMP_PERFSTATISCS(PcfIndex, ucServiceOpt, ul1xStatType, ulDoStatType, ulOperator) \
{ \
    /*lint -e774*/ \
    MEAOBJINDEX_STRU stMeaObj; \
    PPP_MemSet(&stMeaObj, 0, sizeof(MEAOBJINDEX_STRU)); \
    stMeaObj.ulRpIndex = A11_INVALID_RPINDEX; \
    stMeaObj.usPcfIndex = (VOS_UINT16)(PcfIndex); \
    if ((A11_SO_33 == (ucServiceOpt)) || (0 == (ucServiceOpt))) \
    { \
        Snmp_Perf(stMeaObj, ul1xStatType, ulOperator); \
    } \
    else \
    { \
        Snmp_Perf(stMeaObj, ulDoStatType, ulOperator); \
    } \
    /*lint +e774*/ \
}
#define M_GET_STR(str)      #str
#define GTP_INST_GETINSTNO(ulInstIndex)       ((((ulInstIndex) & 0xffff0000) >> 16) & 0xffff)
#define IN
#define OUT




extern VOS_UINT32 g_ulA11RpifIp;

extern VOS_UINT32 g_ulPtmHashGene;



extern VOS_UINT32 L2TP_SeparateUserName(CHAR *szUserName, CHAR *szDomain, CHAR *szUserAbbr);
extern VOS_VOID A11_PPP_TermTag(VOS_UINT32 ulPdpIndex, UCHAR ucFlag);
extern VOS_SIZE_T PerfGetFamPerfCounterAddress(VOS_UINT32 enMeasureUnit, VOS_UINT32 enMeasureEntity, VOS_UINT8 *pucObjectData);
extern VOS_UINT32 PerfSetFamPerfCounterByAddress(VOS_UINT32 *pCounterAddress, VOS_UINT32 udwOpType, VOS_UINT32 udwValue);
extern VOS_UINT32 DVM_GetSelfCpuId(VOS_VOID);

extern VOS_UINT32 SDB_GetRpContextByIndex(VOS_UINT32 ulIndex, VOS_VOID **ppucContext);
extern VOS_VOID HSGW_EmsTraceByRpIndex(VOS_UINT32 ulRpIndex, VOS_UINT32 ulModule, VOS_UINT32 ulCode);
extern VOS_VOID HSGW_EmsTraceByPdnIndex(VOS_UINT32 ulPdnIndex, VOS_UINT32 ulModule, VOS_UINT32 ulCode);
extern VOS_UINT32 A11_GetCompStatNum(SC_COMPRESS_STATE_S * pstCompStatInfo);
extern VOS_VOID A11_OM_HSGWPerfStatisticPCFUnit(VOS_UINT32 ulStatisticType, VOS_UINT32 ulPcfIp, VOS_UINT32 ulOperType, VOS_UINT32 ulValue);

extern VOS_VOID A11_OM_PerfStatisticPCFUnit(VOS_UINT32 ulStatisticType, VOS_UINT32 ulPcfIp);
extern VOS_UINT32 USM_NotifyPhaseResultFunc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulMsgtype, VOS_VOID *pResultInfo);
extern VOS_VOID AM_RegCntStrDiscription(VOS_UINT32 ulCounter, UCHAR *pucStr);
extern VOS_UINT32 A11_VirtualDomainMapping(VOS_UINT16 usVirtualDomainIndex,
                               A11_IMSI_S stIMSI,
                               VOS_UINT16 *pusRealDomainIndex);
extern VOS_UINT32 A11_GetVirtualDomainStatusByIndex(VOS_UINT16 usAPNIndex);
extern VOS_UINT32 SDB_GetPdnContextByIndex(VOS_UINT32 ulIndex, VOS_VOID **ppucContext);
extern VOS_UINT32 A11_A10GlobalIndexToA10ScIndex(VOS_UINT32 ulA10GlobalIndex);
extern VOS_UINT32 A11_PPPC_SendUsrInfor(VOS_UINT32                 ulRpIndex,
                            A11_PPPC_USR_INFOR_S* pstUsrInfor,
                            VOS_UINT32                 ulFlag);
extern VOS_UINT32 ALM_GetAlmSlotCpuID(VOS_VOID);
extern VOS_VOID  A11_4BitsToString( UCHAR *strSrc, UCHAR DstArr[], UCHAR ucMaxNum );
extern VOS_BOOL Trc_IsTraceTaskEnabled(VOS_UINT8 ucTrcType);
extern VOS_UINT32 USM_NotifyReleaseUserFunc(VOS_UINT32 ulRpIndex, VOS_UINT32 ulReleaseCode, UCHAR* pucMsg);
extern VOS_UINT32 Diam_AUTHHostRemoveByAAACBIndex(VOS_UINT16 usDynAAAIndex, VOS_UINT32 ulRpIndex);
extern VOS_UINT32 PPPC_CRYPT_random (UCHAR*  pBuf, VOS_UINT32 ulLen);
extern VOS_UINT32 AlarmToFamEx(VOS_UINT32  ucSlotNo,               /* 2???o? */
                        VOS_UINT32 udwMid,                 /* 2¨²¨¦¨²???¡¥?¡ê?¨¦PID*/
                        VOS_UINT32 udwAlarmICID,           /* ???¡¥???-ID */
                        VOS_UINT8  ucAlarmType,            /* ???¡¥¨¤¨¤D¨ª */
                        VOS_UINT8  ucParaNum,             /* ???¡¥2?¨ºy??¨ºy */
                        VOS_UINT8  ucValueLen[],          /* ???¡¥2?¨ºy3¡è?¨¨¨¢D¡À¨ª */
                        VOS_VOID      *pVarValue[]);          /* ???¡¥2?¨ºy¨¢D¡À¨ª */
extern VOS_VOID Snmp_Perf( MEAOBJINDEX_STRU stMeaObj, VOS_UINT32 ulMeaType, VOS_UINT32 ulOpType );
typedef VOS_VOID (*pfSPM_ByteCallBack)(VOS_UINT32 ulParaID, UCHAR ucOldValue, UCHAR ucNewValue);
extern VOS_UINT32 SPM_RegisterByte(VOS_UINT32  ulSoftparaNum,     pfSPM_ByteCallBack pfCallback);
extern VOS_UINT32 PSM_Inf_GetSGIndexBySGID(VOS_UINT64 SGID);
extern VOS_UINT32 CRM_GetSelfGroupId(VOS_VOID);
extern VOS_VOID PDN_FsmStopTimer(VOS_UINT32 ulTimerType, VOS_UINT32 ulTimerId);
extern VOS_UINT32 USM_GetApnIndexByApnName(UCHAR *pucApnName, VOS_UINT16 *pusApnIndex);
extern VOS_UINT32 PDN_VsncpNotifyGetPCO(PDN_CONTEXT_S *pstPdnContext, PDN_PPP_VSNCP_REQ_S *pstVsncpReq);
extern VOS_UINT32 PDN_VsncpNotifyReconnect(PDN_CONTEXT_S *pstPdnContext, PDN_PPP_VSNCP_REQ_S *pstVsncpReq);
extern VOS_UINT32 PDN_PppStartEhrpdPdn(VOS_UINT32 ulRpIndex, PDN_PPP_VSNCP_REQ_S *pstVsncpReq);
extern VOS_UINT32 USM_GetApnCfgByApnIndex(VOS_UINT16 usApnIndex, HSGW_APN_INFO_S **ppstHsgwApn);
extern VOS_BOOL USM_IsDefaultApn(VOS_UINT32 ulRpIndex, VOS_UINT16 usApnIndex);
extern VOS_UINT32 IPV6_StopTimer(VOS_UINT32 ulTimerId);
extern VOS_UINT32 INST_GetSelfInstanceId(VOS_VOID);
extern VOS_UINT32 Diam_AUTHGetDynAAAInfoByIndex(VOS_UINT16 usDynAAAIndex, UCHAR *pucHost, UCHAR *pucRealm, VOS_UINT16 *pusDynPeerId);
extern VOS_UINT32 PDN_GetPdnType( VOS_UINT32 ulPdnIndex, VOS_UINT32 *pulPdnType);
extern VOS_UINT32 PDN_JudgeSubPDNStateActive(VOS_UINT32 ulRpIndex, VOS_UINT32 ulSubPdnType);
extern VOS_UINT32  RDA_GetApnDNSCfg(VOS_UINT16 usApnIndex, APNDNS_S *pstApn);
extern VOS_UINT16 GetDomainIndexByName( UCHAR*   szDomainName);
extern VOS_UINT32 Ipv6_A11NotifySendRa(VOS_UINT32 ulPdnIndex);
extern VOS_UINT32 PGP_RTDistributeSend(VOS_UINT64 ul64SrcCSI,VOS_UINT64 ul64DstCSI, VOS_VOID* pMsg, VOS_UINT32 ulLen, VOS_UINT32 ulMode, VOS_UINT32 ulMsgType);
extern VOS_UINT32 PSM_Inf_GetCmpSameTIndexInSGByCSI(VOS_UINT64 CSI);
extern VOS_UINT64 PSM_Inf_GetSelfSGID(VOS_VOID);
extern VOS_UINT32 PSM_Inf_GetCmpIndexInOSByCSI(VOS_UINT64 CSI);
extern VOS_UINT64 PSM_Inf_GetSelfCSI(VOS_UINT32 CompType);
extern VOS_UINT32 *PGP_ShrMemAllocByName(VOS_CHAR* name, UCHAR ShareMemType, VOS_UINT32 ullInfo, VOS_UINT32 uiSize);
extern VOS_UINT64 PSM_Inf_GetCSIByOSIDCmpTypeAndInstIdInOS(IN VOS_UINT32 uiChasisNo,IN VOS_UINT32 uiSlot,IN VOS_UINT32 OSID,
 IN VOS_UINT32 CmpType, IN VOS_UINT32 InstIdInOS);
extern VOS_UINT32 CRM_GetSelfGroupBoardType( CRM_SPU_BOARD_TYPE_ENUM* pMode);
extern VOS_UINT32 PDN_LapMsgProc( USM_LAP2_MSG_S* pstMsg );
extern VOS_UINT32 DBG_LogRecordReg(CHAR szSystemName[DBG_LOG_SYSTEM_NAME_LEN],
    CHAR szModuleName[DBG_LOG_MODULE_NAME_LEN], CHAR szSubmoduleName[DBG_LOG_SUB_MODULE_NAME_LEN],
    VOS_UINT32 *ulDBGLogRegID);
typedef VOS_VOID ( *pAmDbgModuleCallBackFunc ) ( VOS_UINT32 ulArg1);
typedef VOS_VOID ( *pUgwClearCntCallBackFunc ) ( VOS_VOID);
extern VOS_UINT32 PTM_CommandsRegister ( LPCommand_Group_S pCommand_Group, CHAR *cpCommand, CHAR *cpHelp , UINT64 ul64Csi);
extern VOS_VOID PGP_RTDistributeFreeMsg(VOS_VOID *pMsg);
extern VOS_VOID* PGP_RTDistributeAllocMsg(VOS_UINT64 selfCSI, VOS_UINT32 ulMsgLen);
extern VOS_UINT32 g_ulUsmPrintLevel;
extern VOS_UINT32 PSM_Inf_GetCSINumByOSIDAndCmpType(VOS_UINT32 uiChasisNo, VOS_UINT32 uiSlot, VOS_UINT32 OSID, VOS_UINT32 CmpType);
extern VOS_UINT32 VOS_Que_Read( VOS_UINT32 ulQueID, VOS_UINT32 ulRetMsg[4],
                VOS_UINT32 ulFlags, VOS_UINT32 ulTimeOutInMillSec );
extern VOS_UINT32 VOS_Ev_Write( VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents );

extern VOS_UINT32 VOS_MCReadQue(VOS_VOID* pstQueId,VOS_VOID** ppMsg,VOS_UINT32 *pulMsgLen,
                         VOS_UINT32 ulFlag,VOS_UINT32 ulMillsec);
extern VOS_UINT32 PTM_CreateQueue(PTM_QUEUE_INFO_S *pstQueInfo, VOS_UINT32* pulQueID);

typedef VOS_VOID (*DVM_BOARD_STATUS_CHG_HOOK)(  CPU_STATUS_PKG_S  *pstBoradStatusPkg);





#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_VAR_H_ */



