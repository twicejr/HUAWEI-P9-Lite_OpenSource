/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : GmmCasComm.h
  Author      : Roger Leo
  Version     : V200R001
  Date        : 2005-11-17
  Description : GmmCasComm模块的内部头文件
  History     :
  1. Date:2005-11-17
     Author: Roger Leo
     Modification:update
  2. l40632 2006.05.20 根据问题单A32D03865修改
  3.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
  4.日    期   : 2009年7月23日
    作    者   : s46746
    修改内容   : 根据问题单号：AT2D12878，GSM下HPLMN搜索时接收到GPRS寻呼或PDP激活(W下PDP激活相同处理)请求需要能及时响应
  5.日    期   : 2011年12月29日
    作    者   : l00130025
    修改内容   : DTS2011082201679/DTS2011121504358,删除LTE的模式判断函数
************************************************************************/

#ifndef _GMM_CAS_COMM_H_
#define _GMM_CAS_COMM_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#pragma pack(4)         /* 1字节对齐，数据结构定义保证4字节对齐 */
                        /* 放在include后，不影响其他头文件的pack参数 */
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 消息头定义
*****************************************************************************/

/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

VOS_UINT8   GMM_IsCasGsmMode (VOS_VOID);
VOS_UINT8   GMM_IsLastRand(VOS_VOID);
VOS_VOID    GMM_InitCasGlobalVariable (VOS_VOID);
VOS_UINT8   GMM_CheckNasMsgIntegrity(RRMM_DATA_IND_STRU *pDataInd);
VOS_UINT8   GMM_CheckNasMsgIntegrityGsm(VOS_VOID);

/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, begin */
VOS_VOID GMM_CasRcvUsimCnfUmtsSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf);
VOS_VOID GMM_CasRcvUsimCnfGsmSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf);
VOS_VOID GMM_CasRcvUsimCnfFailGsm(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf);
VOS_VOID GMM_CasRcvUsimCnfFailUmts(
    USIMM_TELECOM_AUTH_CNF_STRU        *pAuthCnf,
    USIMM_AUTH_RESULT_ENUM_UINT32       enResult
);
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, end */

VOS_UINT32  GMM_SaveEstCnfMsgPara(RRMM_EST_CNF_STRU *pEstCnf);
VOS_UINT32  GMM_SaveRelIndMsgPara(RRMM_REL_IND_STRU *pRelInd);
VOS_UINT8   GMM_CheckMsgIeT3302(VOS_UINT8 *pIeAddr);
VOS_VOID    GMM_ExecAttachRejectCause(VOS_UINT8 ucRejCause);
VOS_UINT32  GMM_ExecRauAcceptMsgIe(NAS_MSG_STRU *pNasMsg);
GMM_RAU_REJ_RESULT_TYPE GMM_ExecRauRejCause(VOS_UINT8 ucRejCause);
VOS_VOID    GMM_ExecRauRejectMsg(VOS_UINT8 *pMsg, VOS_UINT32 ulSize);
VOS_VOID    GMM_ExecSrvRejectMsg(NAS_MSG_STRU *pNasMsg);
VOS_VOID    GMM_ExecLlgmmStatusIndCause(VOS_UINT16 usCause);
VOS_UINT32  GMM_SaveGsmSysInfoIndMsgPara(MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo);
VOS_UINT8   GMM_CheckAuthMsgIeRand(VOS_UINT8 *pucIeAddr);
VOS_UINT32  GMM_CheckAuthMsgIeCksn(VOS_UINT8 *pucIeAddr);
VOS_UINT32  GMM_CheckAuthMsgIeAutn(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckPtmsiReCmdMsgIeFixed(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckPtmsiReCmdMsgIeRai(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckPtmsiReCmdMsgIePtmsi(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckPtmsiReCmdMsgIePtmsiSig(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckGmmInfoMsgIeFullNameNet(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckGmmInfoMsgIeShortNameNet(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckGmmInfoMsgIeLocalTime(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckGmmInfoMsgIeUniTime(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckGmmInfoMsgIeLsaId(VOS_UINT8 *pucIeAddr);
VOS_UINT8   GMM_CheckGmmInfoMsgIeNdsTime(VOS_UINT8 *pucIeAddr);
VOS_UINT32  GMM_ParsGmmInforMsgIeOpt(VOS_UINT8 *pData, VOS_UINT8 ucLen);
VOS_VOID    GMM_CharToUlong(VOS_UINT32 *ulDst, VOS_UINT8 *pucSrc);
VOS_VOID    GMM_CharToUlong(VOS_UINT32 *ulDst, VOS_UINT8 *pucSrc);
VOS_UINT32  GMM_GetPtmsiFromMsgIe(VOS_UINT8 *pData);

VOS_VOID    GMM_FillReadyTimerParaIe (VOS_UINT8 *pAddr);
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, begin */
VOS_VOID GMM_SaveAuthenResult(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf);
/* Modified by y00245242 for VoLTE_PhaseI  项目, 2013-7-23, end */
VOS_UINT32  GMM_PowerOffNoSig(VOS_VOID *pPowerOffMsg);
VOS_VOID    GMM_ClearBeforePowerOffCnf(VOS_VOID);
VOS_UINT32  GMM_IsReadyForPowerOffCnf(VOS_VOID);
VOS_VOID    GMM_UpdateAuthenCtrlFlg(VOS_VOID);
VOS_UINT32  GMM_UpdateMsgHoldInRauAccept(VOS_VOID);
VOS_VOID    GMM_UpdateMsgHoldInSrvAccept(VOS_VOID);
VOS_UINT32  GMM_UpdateCasMsgHoldInRauAccept(VOS_VOID);
VOS_UINT32  GMM_CheckDetachReqMsgCause( MMCGMM_DETACH_REQ_STRU *pMsg,
                                        VOS_UINT32             *pulType);
VOS_VOID GMM_RcvGsmPagingAtRegNmlServ(GRRMM_PAGING_IND_ST *pMsg);
VOS_VOID GMM_RcvGsmPagingAtDeregInit(GRRMM_PAGING_IND_ST *pMsg);
VOS_VOID GMM_RcvGsmPagingAtRauInit(GRRMM_PAGING_IND_ST *pMsg);
VOS_VOID GMM_RcvGsmPaging_RegPlmnSrch(GRRMM_PAGING_IND_ST *pMsg);

VOS_UINT8   GMM_AuthType(VOS_UINT8 ucAutnFlag);

VOS_VOID GMM_CreateNewTlli(VOS_UINT32 *pulTmsi, VOS_UINT8 ucType);
VOS_VOID GMM_FreeOldTlli(VOS_VOID);
VOS_VOID GMM_FreeSysTlli(VOS_VOID);
VOS_UINT32 GMM_AssignNewTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType);
VOS_VOID GMM_AssignSysTlli(VOS_VOID);
VOS_VOID GMM_AssignGsmKc(VOS_VOID);
VOS_VOID GMM_UpdateSysTlli(GMM_TLLI_TYPE TlliType);

VOS_UINT32 NAS_GMM_GetPTmsiForTLLI(
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN]
);

GMM_CAS_CTRL_STRU* NAS_GMM_GetGmmCasGlobalCtrl(VOS_VOID);
VOS_UINT16         NAS_GMM_GetMui(VOS_VOID);
VOS_UINT16         NAS_GMM_IncreaseMui(VOS_VOID);
VOS_UINT16         NAS_GMM_GetPowerOffDetachPsMui(VOS_VOID);
VOS_VOID           NAS_GMM_SetPowerOffDetachPsMui(VOS_UINT16 usMui);

VOS_VOID GMM_SndLlcDataReq (
    NAS_MSG_STRU                       *pMsg,
    LL_NAS_UNITDATA_REQ_ST             *pstUnitDataReq
);
VOS_UINT32 NAS_GMM_IsPowerOffPsDetachMsg(
    NAS_MSG_STRU                       *pMsg
);
VOS_UINT8  NAS_GMM_GetCiphInd(
    NAS_MSG_STRU                       *pMsg
);

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_GMM_UseGutiDerivedPtmsi ( VOS_VOID );

#endif

VOS_UINT32 GMM_AssignModifyTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType);

extern  VOS_VOID NAS_GMM_RauCompleteHandling( VOS_VOID );

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of GmmCasComm.h*/
