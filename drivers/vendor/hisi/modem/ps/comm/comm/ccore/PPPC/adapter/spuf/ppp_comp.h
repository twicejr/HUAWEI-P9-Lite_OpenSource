/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ppp_comp.h
  版 本 号   : 初稿
  作    者   : 骆方
  生成日期   : 2012年9月20日
  最近修改   :
  功能描述   : PPP_comp的头文件
  函数列表   :
*
*

  修改历史   :
  1.日    期   : 2012年9月20日
    作    者   : 骆方
    修改内容   : 创建文件

******************************************************************************/





#ifndef __PPP_COMP_H_H_H_
#define __PPP_COMP_H_H_H_

enum ePPP_INNER_MYG_TYPE
{
    PPP_INNER_LAP_BATCH_RELEASE,
    PPP_INNER_LAP_REPORT,
    PPP_INNER_LAP_RELEASE,
};


#define PPP_SNMP_PERF_DO_STATISC_TIME  "PPP_SNMP_PERF_DO_STATISC_TIME"
#define PPP_SNMP_PERF_NO_STATISC_TIME  "PPP_SNMP_PERF_NO_STATISC_TIME"

#define PPP_DDU_QUE_FLOWCTRL  g_ulPPPNegoFlowctrl*2

#define PPP_SELF_CSI           g_stPppCompInfo.ullSelfCsi
#define PPP_SELF_SGID          g_stPppCompInfo.ullSelfSgId
#define PPP_SELF_CMPIDX        g_stPppCompInfo.ulSelfCmpIdx
#define PPP_HANDLE             g_stPppCompInfo.ulHandle
#define PPP_SELF_CMPIDXINSG    g_stPppCompInfo.ulSelfCmpIdxInSG

#define PMBUF_FOR_HW_RELEASED           0x5a78a587

#define PPP_MSG_PRINT_INFO  \
        "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x" \

#define PPP_MSG_PRINT_DATA  \
    pucData[0],pucData[1],pucData[2], \
    pucData[3],pucData[4],pucData[5], \
    pucData[6],pucData[7],pucData[8], \
    pucData[9],pucData[10],pucData[11], \
    pucData[12],pucData[13],pucData[14], \
    pucData[15],pucData[16],pucData[17], \
    pucData[18],pucData[19],pucData[20], \
    pucData[21],pucData[22],pucData[23], \
    pucData[24],pucData[25],pucData[26], \
    pucData[27],pucData[28],pucData[29], \
    pucData[30],pucData[31],pucData[32], \
    pucData[33],pucData[34],pucData[35], \
    pucData[36],pucData[37],pucData[38], \
    pucData[39],pucData[40],pucData[41], \
    pucData[42],pucData[43],pucData[44], \
    pucData[45],pucData[46],pucData[47] \



 VOID PPP_GetSelfCompInfo(DMS_COMMID_T myCSI );
VOS_VOID PPP_InitRand(VOS_VOID);
 VOS_UINT32 PPP_LocalMemInit(VOS_VOID);
 VOS_UINT32 PPP_ShareMemInit(VOS_VOID);
 VOS_VOID PPP_GlobalMemInit(VOS_VOID);
 VOS_UINT32 PPP_CompInit1(VOS_VOID);
 VOS_UINT32 PPP_CompInit2(VOS_VOID);
 VOS_UINT32 PPP_CompInit3(VOS_VOID);
 VOS_UINT32 PPP_StartNegoTimer(VOS_UINT8 ucPppId);
 VOS_UINT32 PPP_StopNegoTimer(VOS_UINT8 ucPppId);
 VOS_UINT32 PPP_MsgDispatch(VOS_UINT32 ulMsgType, VOID *pMsg );
 VOS_VOID PPP_A11MsgProc(VOS_VOID * pMsg);
 VOS_VOID PPP_AAAMsgProc(AAA_AUTHRSP_S * pMsg);
 VOS_UINT32 PPP_NegoMsgProc(UCHAR *pMsg);

 VOS_UINT32 PPP_CompConstruct( RTF_COMP_CONSTRUCT_STAGE_E eConstructStage,
                                   DMS_COMMID_T myCSI, DMS_COMMID_T myCPI, VOID* pThis );
 ULONG PPP_CompDestruct( DMS_COMMID_T myPid, VOID* pThis );

extern VOID CDB_PppCfgModNotify( CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*     pNewValue, UCHAR*     pOldValue);
extern VOID CDB_PppCfgAddNotify(      CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*    pValue);
extern VOS_VOID PPP_VSNCP_OptionEncodeReg(VOS_VOID);
extern VOS_VOID PPP_VSNCP_OptionDecodeReg(VOS_VOID);

extern VOID PPP_SoftParaInit(VOS_VOID);
extern VOS_UINT32 PPP_InitDebugInfo(VOS_VOID);
extern VOS_UINT32 PDN_LapMsgProc( USM_LAP2_MSG_S* pstMsg );
extern VOS_UINT32 PPP_L2tpIpcpMsgProc(PMBUF_S *pMbuf );



#endif /* __PPP_COMP_H_H_H_ */
