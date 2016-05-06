/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPAComm.h                                                     */
/*                                                                           */
/* Author: Xu cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: implement HPA subroutine                                     */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 200802-02                                                        */
/*    Author: Xu cheng                                                       */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/
#ifndef _HPA_COMM_H__
#define _HPA_COMM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include "vos.h"
#include "pamom.h"
#include "hpamailboxdef.h"
#include "hpaglobalvar.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*****************************************************************************
  2 STRUCT定义
*****************************************************************************/
typedef struct
{
    VOS_UINT_PTR          ulAHBBaseAddr;
    VOS_UINT_PTR          ulWBBPBaseAddr;
    VOS_UINT_PTR          ulWBBPDRXBaseAddr;
    VOS_UINT_PTR          ulGBBPBaseAddr;
    VOS_UINT_PTR          ulGBBPDRXBaseAddr;
    VOS_UINT_PTR          ulSYSCTRLBaseAddr;
    VOS_UINT_PTR          ulHIFIAXIBaseAddr;
    VOS_UINT_PTR          ulDSPTempBaseAddr;
    VOS_UINT_PTR          ulGBBP1BaseAddr;
    VOS_UINT_PTR          ulGBBP1DRXBaseAddr;
    VOS_UINT_PTR          ulBBPCommBaseAddr;
    VOS_UINT_PTR          ulBBPCommOnBaseAddr;
    VOS_UINT_PTR          ulCDMABBPBaseAddr;
    VOS_UINT_PTR          ulCDMABBPDRXBaseAddr;
    VOS_UINT_PTR          ulCDMABBP2DRXBaseAddr;
}PLATFORM_SYSADDR_STRU;

/*****************************************************************************
  3 全局变量声明
*****************************************************************************/
extern PLATFORM_SYSADDR_STRU           g_stSysAddr;

extern VOS_UINT32                      g_ulOmNosigEnable;
extern VOS_UINT32                      g_ulListmodeEnable;
extern VOS_UINT16                      g_usListModeCurrentMode;
extern MODEM_ID_ENUM_UINT16            g_enListModeWorkModem;

/*****************************************************************************
  4 宏定义
*****************************************************************************/

#define HPA_MATCH_MSGID_RECEIVER_PID_ERR    0xff

/* SYSCTRL 地址 */
#define SOC_SYS_CTRL_BASE_ADDR          (g_stSysAddr.ulSYSCTRLBaseAddr)

/* HIFI和ARM定义的邮箱地址 */
#define HIFI_AXI_BASE_ADDR              (g_stSysAddr.ulHIFIAXIBaseAddr)

/* 写入DSP温度补偿的地址 */
#define DSP_TEMP_BASE_ADDR              (g_stSysAddr.ulDSPTempBaseAddr)

/* 写入当前HIFI DSP状态地址，在温度补偿区域中划分 */
#define HIFI_STATUS_BASE_ADDR           (DSP_TEMP_BASE_ADDR+sizeof(CPHY_TEMP_INFO_STRU))

/* GBBP寄存器BIT位标示 */
#if (FEATURE_GUDRX_NEWVERSION == FEATURE_ON)
#define OAM_GBBP_FRAME_INT_BIT                      BIT_N(0)
#define OAM_GBBP_WAKE_UP_INT_BIT                    BIT_N(0)

#define OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT         BIT_N(1)
#define OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT         BIT_N(2)
#else
#define OAM_GBBP_FRAME_INT_BIT                      BIT_N(0)
#define OAM_GBBP_WAKE_UP_INT_BIT                    BIT_N(24)

#define OAM_GBBP_DRX_CLK_SWITCH_32K_INT_BIT         BIT_N(25)
#define OAM_GBBP_DRX_CLK_SWITCH_52M_INT_BIT         BIT_N(27)
#endif

/*****************************************************************************
  5 函数声明
*****************************************************************************/

extern VOS_UINT32 HPA_AhbMailBoxInit(HPA_MB_TYPE_ENUM_UINT32 enMbType);

extern VOS_VOID HPA_HifiTransferEntry(VOS_VOID);

extern VOS_VOID HPA_ApmMsgPIDProc( MsgBlock *pRcvMsg );

extern VOS_VOID HPA_PpMsgPIDProc( MsgBlock *pRcvMsg );

extern VOS_VOID HPA_NppMsgPIDProc( MsgBlock *pRcvMsg );

extern VOS_VOID HPA_R99MsgPIDProc(MsgBlock *pMsgBlock);

extern VOS_VOID HPA_RBufDeliverEntry(HPA_MB_TYPE_ENUM_UINT32 enMbType);

extern VOS_VOID HPA_Conncet2GISR0(VOS_VOID);

extern VOS_VOID HPA_Conncet2GISR1(VOS_VOID);

extern VOS_VOID HPA_Conncet2GISR2( VOS_VOID );

extern VOS_VOID HPA_ConncetAPMISR(VOS_VOID);

extern VOS_VOID HPA_Conncet3GISR(VOS_VOID);

extern VOS_VOID HPA_ReadCfnSfn(VOS_VOID);

extern VOS_VOID HPA_PutAhbToRBuf(HPA_MB_TYPE_ENUM_UINT32 enMbType);

extern VOS_VOID HPA_PutRBufToAhb(HPA_MB_TYPE_ENUM_UINT32 enMbType,
                                            VOS_UINT32 ulTriggerType);

extern VOS_VOID HPA_3GIsrEnable(MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID HPA_3GIsrDisable(MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID HPA_2GIsrEnable(MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID HPA_2GIsrDisable(MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID HPA_3GAwakeIsr(VOS_VOID);

extern VOS_BOOL HPA_DLBufferIsEmpty(HPA_MB_TYPE_ENUM_UINT32 enMbType);

extern void atomic_inc(hpa_atomic_t *v);

extern void atomic_dec( hpa_atomic_t *v );

VOS_UINT32 APM_InitSystemAddr(VOS_VOID);

extern VOS_VOID HPA_2GAwakeIsr(MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID HPA_2GFrameClockIsr(MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID HPA_2GFrameClockIsr0(VOS_VOID);

extern VOS_VOID HPA_2GFrameClockIsr1(VOS_VOID);

extern VOS_VOID HPA_2GAwakeIsr0(VOS_VOID);

extern VOS_VOID HPA_2GAwakeIsr1(VOS_VOID);

extern VOS_VOID HPA_HifiIpcIsr(VOS_VOID);

extern VOS_VOID HPA_3GSwitchClockIsr(VOS_VOID);

extern VOS_VOID HPA_ShowINTNo(VOS_VOID);

extern VOS_UINT32 HPA_Init(VOS_VOID);

extern VOS_VOID HPA_TransferTaskEntry(VOS_VOID);

extern VOS_VOID HPA_MsgToAhbProc(HPA_MB_TYPE_ENUM_UINT32 enMbType,
                                MsgBlock *pMsgBlock, VOS_UINT32 ulPriority);

extern VOS_UINT32 HPA_SendDspMsg(VOS_PID Pid, VOS_VOID **ppMsg,
            VOS_UINT32 ulFileID, VOS_INT32 lLineNo);

extern VOS_UINT32 HPA_SendDspUrgentMsg(VOS_PID Pid, VOS_VOID **ppMsg,
            VOS_UINT32 ulFileID, VOS_INT32 lLineNo);

extern VOS_VOID APM_InitAPMGlobal(VOS_VOID);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_VOID HPA_ConnectCdmaISR(VOS_VOID);

extern VOS_VOID HPA_CdmaAwakeIsr( VOS_VOID );

extern VOS_VOID HPA_Cdma1XAwakeIsr( VOS_VOID );

extern VOS_VOID HPA_CdmaHrpdAwakeIsr( VOS_VOID );

extern VOS_VOID HPA_Cdma1XHaltIsr( VOS_VOID );

extern VOS_VOID HPA_CdmaHrpdHaltIsr( VOS_VOID );

extern VOS_VOID HPA_Cdma1XResumeIsr( VOS_VOID );

extern VOS_VOID HPA_CdmaHrpdResumeIsr( VOS_VOID );
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

