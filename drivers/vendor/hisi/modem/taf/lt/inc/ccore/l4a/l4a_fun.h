

#ifndef __L4A_FUN_H__
#define __L4A_FUN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "gen_msg.h"
#include  "l4a_proc.h"

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
typedef enum _L4A_RSSI_IND_TYPE_NUM
{
    EN_L4A_RSSI_STOP_IND      = 0x0,
    EN_L4A_RSSI_INQ_NOT_IND   = 0x1,
    EN_L4A_RSSI_IND           = 0x2,
    EN_L4A_RSSI_IND_BUTT
}EN_L4A_RSSI_IND_TYPE_NUM;

typedef enum
{
    EN_L4A_AUTO_ANSWER = 0x00,
    EN_L4A_MANU_ANSWER = 0x01,
    EN_L4A_ANSWER_BUTT
}EN_L4A_CGAUTO_ENUM;



/*****************************************************************************
   5 STRUCT
*****************************************************************************/

typedef APS_L4A_SET_CGEQOSRDP_REQ_STRU L4A_ONLY_CID_COMM_REQ_STRU;
typedef APS_L4A_SET_CGEQOS_CNF_STRU L4A_NO_CID_COMM_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    APS_L4A_MSG_ID_ENUM_UINT32          enMsgId;                                /* _H2ASN_Skip */

    APS_L4A_APPCTRL_STRU                stCtrl;

}APS_L4A_SET_COMMON_REQ_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32 l4a_FunCsqInd(L4A_PS_MSG_STRU* pData);
extern VOS_UINT32 l4a_FunIndCfgSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunLwclashInd(L4A_PS_MSG_STRU* pData);
extern VOS_UINT32 l4a_FunLcacellInd(L4A_PS_MSG_STRU* pData);
extern VOS_UINT32 l4a_FunPsAbortSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsAuthDataSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsAuthDataSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCellInfoReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCellIDReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCellInfoReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCellIDReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCemodeReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCemodeReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCgautoSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCgautoSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCgcontrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCgcontrdpSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCgdcontSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCgdcontSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCgscontrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCgdscontSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCgdscontSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCgeqosrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCgeqosSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCgeqosSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCgtftrdpSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCgtftSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCgtftSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCnmrReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCnmrReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsCsqReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsCsqReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsFastDormReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsIpv6SetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsL2IdleSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsLtecsReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsLtecsReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsLwclashReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsLwclashReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsNoCidCommSetCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);
extern VOS_UINT32 l4a_FunPsOnlyCidCommSetReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunPsThresholdReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_AddCmdToListEx(L4A_DATA_MSG_STRU * pstReq, VOS_UINT32 ulATReqMsgId, VOS_UINT32 ulPSCnfMsgId);

VOS_UINT32 l4a_FunPsLcacellReadReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
VOS_UINT32 l4a_FunPsLcacellReadCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);



extern VOS_VOID mntn_UpdateMsgInfo(L4A_MNTN_MSG_INFO_STRU *pstMsg, VOS_UINT32 ulMsgId);
extern L4A_IND_MSG_FUN_TABLE_STRU * FwProGetPsIndFunTbl(VOS_UINT32 * pulTableLenth);
extern L4A_FW_MSG_FUN_TABLE_STRU* l4a_FwProGetMsgFun(VOS_UINT32 ulMsgId,VOS_UINT32 flag);
extern HI_LIST_S* l4a_GetNodeHead(VOS_VOID);
extern L4A_RX_INFO_STRU* l4a_GetExeCmdNode(VOS_UINT32 ulMsgId,VOS_UINT32 ulFlag);
extern VOS_VOID l4a_DelCmdNode(L4A_RX_INFO_STRU* pstCmdNode);
extern VOS_UINT32 l4a_AddCmdToList(L4A_DATA_MSG_STRU * pstReq, L4A_FW_MSG_FUN_TABLE_STRU* pstFunTable);
extern VOS_UINT32 l4a_SendMsg(VOS_UINT32 ulSendId, VOS_UINT32 ulRecverId, VOS_VOID* pDta, VOS_UINT32 dtaSize);
extern VOS_UINT32 l4a_DealTimeOutCmdEntry(L4A_RX_INFO_STRU* pData);
extern VOS_UINT32 l4a_DealPsIndCnfEntry(L4A_PS_MSG_STRU* pData);
extern VOS_UINT32 l4a_DealAtTafReqEntry(L4A_DATA_MSG_STRU* pData);
extern VOS_UINT32 l4a_TaskInit(VOS_VOID);
extern VOS_UINT32 L4aPktSdfInfo(APS_L4A_SDF_PARA_STRU* pstSdfParaInfo,APP_ESM_SDF_PARA_STRU* pstSdfPara);
extern L4A_FW_MSG_FUN_TABLE_STRU* mntn_GetInfo(VOS_UINT32 ulMsgId, VOS_UINT32 *pulStep);
extern VOS_UINT32 l4a_GetValidCidIndex(VOS_UINT8 *pData, VOS_UINT32 x);
extern VOS_UINT32 l4a_GetUlValidCidIndex(VOS_UINT32 *pData, VOS_UINT32 x);
extern VOS_UINT32 l4a_GetValidCidNum(VOS_UINT8 *pData);
extern VOS_UINT32 l4a_GetUlValidCidNum(VOS_UINT32 *pData);
extern VOS_VOID l4a_help(VOS_VOID);
extern VOS_VOID l4a_FunSetTftInfo(APP_ESM_SET_TFT_REQ_STRU* pstPsCgtftReq, APS_L4A_SET_CGTFT_REQ_STRU* pstCgtftReq);
extern VOS_VOID l4a_FunCgtftrdpPkj(APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU* pstPsInqTftCnf, APS_L4A_SDF_PF_TFT_STRU *psttft);
extern VOS_VOID l4a_GetPLMNInfo(L4A_PLMN_ID_STRU * pMspPlmn, APP_PLMN_ID_STRU * pPsPlmn);
extern VOS_UINT32 l4a_FunRDPCidIndexReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid, VOS_UINT32 x);
extern VOS_VOID l4a_FunCgcontrdpPkj(APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU* pstPsPdpContCnf, APS_L4A_PRIM_PDP_DYNAMIC_EXT_STRU *pstPrim);

extern VOS_UINT32 l4a_FunLteWifiReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunLteWifiCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);

extern VOS_UINT32 l4a_FunRadverReq(L4A_DATA_MSG_STRU* pData,VOS_UINT32 ulPsReqMsgId,VOS_UINT32 ulPsReqPid);
extern VOS_UINT32 l4a_FunRadverCnf(L4A_PS_MSG_STRU* pData,L4A_FW_MSG_FUN_TABLE_STRU* pstTable,VOS_UINT16 usClientId);

extern VOS_UINT32 l4a_FunCgdcontChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunCgdscontChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunCgeqosChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunCgtftChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunAuthdataChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunCgautoChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunCgcontrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunCgscontrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunCgtftrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunCgeqosrdpChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunLtecsChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);
extern VOS_UINT32 l4a_FunCemodChk(L4A_PS_MSG_STRU* pData, L4A_RX_INFO_STRU* pNode);

extern VOS_UINT32 l4a_IsmcoexTimeout(VOS_UINT16 usClientId);


/*****************************************************************************
  9 OTHERS
*****************************************************************************/

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of l4a_fun.h */

