/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Test_AtInputProc.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : Test_AtInputProc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATINPUTPROC_H__
#define __TEST_ATINPUTPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "ATCmdProc.h"

#include "PppInterface.h"
#include "AtUsbComItf.h"
#include "MnCallApi.h"
#include "AtInputProc.h"
#include "AtCsdInterface.h"
#include "AtTafAgentInterface.h"
#include "TafAgentInterface.h"
#include "cpm.h"
#include "AtDataProc.h"
#include "TafAgentCtx.h"
#include "AtCmdMsgProc.h"
#include "ATCmdProc.h"
#include "AtAppVcomInterface.h"
#include "SysNv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_INPUTPROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern VOS_UINT32                              g_ulAtUsbDebugFlag;


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


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern VOS_VOID AT_InitPort(VOS_VOID);

extern int  App_VcomRecvCallbackRegister(unsigned char  uPortNo, pComRecv pCallback);
extern VOS_INT32 AT_AppSockComEst(VOS_UINT8 ucPortNo);
extern VOS_UINT32 AT_CheckHsicUser(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_CheckModemDataMode(VOS_VOID);
extern VOS_VOID AT_CleanAtChdataCfg(
           VOS_UINT16                          usClientId,
           VOS_UINT8                           ucCid
           );
extern VOS_UINT32 AT_MODEM_StopFlowCtrl(
           VOS_UINT32                          ulParam1,
           VOS_UINT32                          ulParam2
       );
extern VOS_VOID AT_CloseUsbNdis(VOS_VOID);
extern VOS_UINT32 At_CmdStreamPreProc(VOS_UINT8 ucIndex,VOS_UINT8* pData, VOS_UINT16 usLen);
extern VOS_UINT32  AT_CsdDataModeRcvModemMsc(
           VOS_UINT8                           ucIndex
       );
extern TAF_UINT32 At_DataStreamPreProc (TAF_UINT8 ucIndex,TAF_UINT8 DataMode,TAF_UINT8* pData, TAF_UINT16 usLen);
extern VOS_VOID AT_GetAtMsgStruMsgLength(
           VOS_UINT32                          ulInfoLength,
           VOS_UINT32                         *pulMsgLength
       );
extern VOS_VOID AT_GetUserTypeFromIndex(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pucUserType
       );
extern VOS_UINT32 AT_HsicEst ( VOS_UINT8   ucHsicAtCtxId );
extern VOS_UINT32 AT_HsicFreeUlDataBuf(
           UDI_HANDLE                          ulUdiHdl,
           VOS_UINT8                          *pucBuf,
           VOS_UINT32                          ulLen
       );
extern VOS_UINT32 AT_HsicGetUlDataBuf(
           UDI_HANDLE                           ulUdiHdl,
           VOS_UINT8                          **ppucBuf,
           VOS_UINT32                          *pulLen
       );
extern VOS_UINT32 AT_HsicInit( VOS_VOID );
extern VOS_UINT32 AT_HsicInitUlDataBuf(
           UDI_HANDLE                          ulUdiHdl,
           VOS_UINT32                          ulEachBuffSize,
           VOS_UINT32                          ulTotalBuffNum
       );
extern VOS_VOID AT_HsicOneFreeDlDataBuf(VOS_UINT8 *pucBuf);
extern VOS_VOID AT_HsicOneReadDataCB( VOS_VOID );
extern VOS_VOID AT_HsicThreeFreeDlDataBuf(VOS_UINT8 *pucBuf);
extern VOS_VOID AT_HsicThreeReadDataCB( VOS_VOID );
extern VOS_VOID AT_HsicTwoFreeDlDataBuf(VOS_UINT8 *pucBuf);
extern VOS_VOID AT_HsicTwoReadDataCB( VOS_VOID );
extern VOS_UINT32 AT_HsicWriteData(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pucBuf,
           VOS_UINT32                          ulLen
       );
extern TAF_VOID At_InitCom();
extern VOS_VOID    AT_InitFcMap(VOS_VOID);
extern VOS_VOID AT_InitUartLink(VOS_UINT8 ucIndex);
extern VOS_UINT32  AT_IpDataModeRcvModemMsc(
           VOS_UINT8                           ucIndex,
           AT_DCE_MSC_STRU                     *pMscStru
       );
extern VOS_VOID AT_MemFreeDataBuf(
           AT_MEM_SOURCE_TYPE_ENUM_UINT32      enSource,
           IMM_ZC_STRU                        *pstData
       );
extern VOS_VOID AT_MemFreeUartDataBuf(
           AT_MEM_SOURCE_TYPE_ENUM_UINT32      enSource,
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen
       );
extern VOS_UINT8 * AT_MemGetDataBuf(
           AT_MEM_SOURCE_TYPE_ENUM_UINT32      enSource,
           VOS_UINT16                          usLen
       );
extern VOS_VOID AT_MemSingleCopy(
           VOS_UINT8                          *pucDest,
           VOS_UINT8                          *pucSrc,
           VOS_UINT32                          ulLen
       );
VOS_VOID AT_ModemSetCtlStatus(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pMscStru
);
extern VOS_INT32 At_NotifyStatusChgFromUsbCom(VOS_UINT8 uStatus);
extern VOS_UINT32 At_OmDataProc (
           VOS_UINT8                           ucPortNo,
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen
       );
extern VOS_VOID AT_OpenUsbNdis(VOS_VOID);
extern VOS_UINT32  AT_PppDataModeRcvModemMsc(
           VOS_UINT8                           ucIndex,
           AT_DCE_MSC_STRU                     *pMscStru
       );
extern CPM_SEND_FUNC AT_QuerySndFunc(AT_PHY_PORT_ENUM_UINT32 ulPhyPort);
extern VOS_INT AT_RcvFromAppCom(
           VOS_UINT8                           ucPortNo,
           VOS_UINT8                          *pData,
           VOS_UINT16                          uslength
       );
extern VOS_INT AT_RcvFromAppSock(
           VOS_UINT8                           ucPortNo,
           VOS_UINT8                          *pData,
           VOS_UINT16                          uslength
       );
extern VOS_INT AT_RcvFromNdisCom(
           VOS_UINT8                           *pucData,
           VOS_UINT16                          uslength
       );
extern VOS_INT AT_RcvFromSock(
           VOS_UINT8                          *pData,
           VOS_UINT32                         uslength
       );
extern VOS_INT At_RcvFromUsbCom(
           VOS_UINT8                           ucPortNo,
           VOS_UINT8                          *pData,
           VOS_UINT16                          uslength
       );
extern TAF_UINT32 At_SendCmdMsg (TAF_UINT8 ucIndex,TAF_UINT8* pData, TAF_UINT16 usLen,TAF_UINT8 ucType);
extern VOS_UINT32 AT_SendCtrlDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLength
       );
extern VOS_UINT32 AT_SendPcuiDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLength
       );
extern VOS_UINT32 AT_SendDataToHsic(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pucDataBuf,
           VOS_UINT16                          usLen
       );
extern VOS_UINT32 AT_SendDataToModem(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pucDataBuf,
           VOS_UINT16                          usLen
       );
extern VOS_UINT32 AT_SendDiagCmdFromOm(
           VOS_UINT8                           ucPortNo,
           VOS_UINT8                           ucType,
           VOS_UINT8                          *pData,
           VOS_UINT16                          uslength
       );
VOS_UINT32 AT_UART_SendRawDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLen
);
extern VOS_UINT32 AT_SendZcDataToModem(
           VOS_UINT16                          usPppId,
           IMM_ZC_STRU                        *pstDataBuf
       );
extern VOS_VOID AT_SetAtChdataCidActStatus(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulIsCidAct
    );
extern VOS_UINT32 AT_MODEM_StartFlowCtrl(
           VOS_UINT32                          ulParam1,
           VOS_UINT32                          ulParam2
       );
extern VOS_UINT32 AT_SetModemStatus(
           VOS_UINT8                           ucIndex,
           AT_DCE_MSC_STRU                    *pstMsc
       );
extern VOS_VOID AT_SndDipcPdpActInd(
            VOS_UINT16                          usClientId,
            VOS_UINT8                           ucCid,
            VOS_UINT8                           ucRabId
            );
extern VOS_VOID  AT_SndDipcPdpDeactInd(
           VOS_UINT8                           ucRabId
       );
extern VOS_INT32 AT_SockComEst(VOS_UINT8 ucPortNo);
extern VOS_VOID AT_StopFlowCtrl(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_UsbCtrEst(VOS_UINT8 ucPortNo);
extern VOS_INT AT_UsbCtrlBrkReqCB(VOS_VOID);
extern VOS_UINT32 At_UsbGetWwanMode(VOS_VOID);
extern VOS_VOID AT_UsbModemClose(VOS_VOID);
extern VOS_UINT32 At_ModemDataInd(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                           ucDlci,
           IMM_ZC_STRU                        *pstData
       );
extern VOS_VOID AT_UsbModemEnableCB( PS_BOOL_ENUM_UINT8 ucEnable );
extern VOS_UINT32 At_ModemEst (
   VOS_UINT8                           ucIndex,
   AT_CLIENT_ID_ENUM_UINT16            usClientId,
   VOS_UINT8                           ucPortNo
);
extern VOS_VOID AT_ModemFreeDlDataBuf(
  IMM_ZC_STRU *pstBuf
);
extern VOS_UINT32 AT_ModemFreeUlDataBuf(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU *pstBuf
);
extern VOS_UINT32 AT_ModemGetUlDataBuf(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU **ppstBuf
);
extern VOS_VOID AT_UsbModemInit( VOS_VOID );
extern VOS_UINT32 AT_ModemInitUlDataBuf(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulEachBuffSize,
    VOS_UINT32                          ulTotalBuffNum
   );
extern VOS_UINT32 At_ModemMscInd (
           VOS_UINT8                           ucIndex,
           VOS_UINT8                           ucDlci,
           AT_DCE_MSC_STRU                    *pMscStru
       );
extern VOS_VOID AT_UsbModemReadDataCB( VOS_VOID );
extern VOS_VOID AT_UsbModemReadMscCB( AT_DCE_MSC_STRU *pstRcvedMsc );
extern VOS_UINT32 AT_ModemStatusPreProc (VOS_UINT8 ucIndex, AT_DCE_MSC_STRU *pMscStru);
extern VOS_UINT32 AT_ModemWriteData(VOS_UINT8 ucIndex, IMM_ZC_STRU *pstBuf);
extern VOS_UINT32 AT_UsbNdisEst(VOS_VOID);
extern VOS_UINT32 At_UsbPcuiEst(VOS_UINT8 ucPortNo);
extern VOS_VOID AT_UsbUartFreeDlDataBuf(VOS_UINT8 *pucBuf);
extern VOS_UINT32 AT_UsbUartFreeUlDataBuf(
           VOS_UINT8                          *pucBuf,
           VOS_UINT32                          ulLen
       );
extern VOS_UINT32 AT_UsbUartGetUlDataBuf(
           VOS_UINT8                           **ppucBuf,
           VOS_UINT32                          *pulLen
       );
extern VOS_UINT32 AT_UsbUartInit( VOS_VOID );
extern VOS_UINT8 * AT_UsbUdiGetDlDataBuf(VOS_UINT32 ulLen);
extern VOS_VOID AT_SetUsbDebugFlag(VOS_UINT32 ulFlag);

extern VOS_UINT32 CBTCPM_NotifyChangePort(AT_PHY_PORT_ENUM_UINT32 enPhyPort);

extern int  App_VcomSend (unsigned char  uPortNo, unsigned char  *pData, unsigned short  uslength);


extern void UT_STUB_INIT(void);
extern unsigned int UT_Ps_SendMsg(signed char *cFileName, unsigned int ulLine, unsigned int ulPid, void * pMsg);
extern unsigned int UT_Ps_SendMsgFail(signed char *cFileName, unsigned int ulLine, unsigned int ulPid, void * pMsg);



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

#endif /* end of Test_AtInputProc.h */
