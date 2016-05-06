/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: HPAGlobalVar.h                                                  */
/*                                                                           */
/* Author: Xu cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: Announcement of HPA Global Var.                              */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-02                                                          */
/*    Author: Xu cheng                                                       */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _HPA_GLOBAL_VAR_H
#define _HPA_GLOBAL_VAR_H

#include "hparingbuffer.h"
#include "product_config.h"
#include "omnvinterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

enum HPA_MB_TYPE
{
    HPA_DSP_MB_DL = 0,
    HPA_DSP_MB_UL,
    HPA_HIFI_MB_DL,
    HPA_HIFI_MB_UL,
    HPA_MB_BUTT
};

typedef VOS_UINT32 HPA_MB_TYPE_ENUM_UINT32;

typedef struct
{
    VOS_UINT32      ulHeadAddr;
    VOS_UINT32      ulQueueAddr;
    VOS_UINT32      ulQueueSize;
    HPA_RING_ID     rngInnerBuffer;
    HPA_RING_ID     rngAhbBuffer;
    VOS_UINT32      ulSn;
}HPA_AHB_ENTITY_STRU;

typedef struct
{
    VOS_UINT32 ulULMailBoxMsgLenErrCount;
    VOS_UINT32 ulULMailBoxMsgLenErrSlice;
    VOS_UINT32 ulULMailBoxPartitionErrCount;
    VOS_UINT32 ulULMailBoxPartitionErrSlice;
    VOS_UINT32 ulULMailBoxMsgLostCount;
    VOS_UINT32 ulULMailBoxMsgLostSlice;
    VOS_UINT32 ulDLMailBoxFullCount;
    VOS_UINT32 ulDLMailBoxFullSlice;
    VOS_UINT32 ulRcvMsgLenErrCount;
    VOS_UINT32 ulRcvMsgLenErrSlice;
    VOS_UINT32 ulULRBufMsgLenErrCount;
    VOS_UINT32 ulULRBufMsgLenErrSlice;
    VOS_UINT32 ulMailBoxMsgNotMatchCount;
    VOS_UINT32 ulMailBoxMsgNotMatchSlice;
    VOS_UINT32 ulDLRBufFullErrCount;
    VOS_UINT32 ulDLRBufFullErrSlice;
    VOS_UINT32 ulULAHBMemoryErrCount;
    VOS_UINT32 ulULAHBMemoryErrSlice;
    VOS_UINT32 ulDLAHBMemoryErrCount;
    VOS_UINT32 ulDLAHBMemoryErrSlice;
    VOS_UINT32 ulDLRecvErrMsgCount;
    VOS_UINT32 ulDLRecvErrMsgSlice;

    VOS_UINT32 ulDLMailBoxMaxUsedLen;
    VOS_UINT32 ulULMailBoxMaxUsedLen;

    VOS_UINT32 ulAhbMailBoxAddr;
    VOS_INT32  lFrontAddr;
    VOS_INT32  lRearAddr;
}HPA_ERROR_COUNT_STRU;

/*Record HPA frame interrupt count*/
typedef struct
{
    VOS_UINT32 ul0msIntNum;
    VOS_UINT32 ul0msIntSlice;
    VOS_UINT32 aulPpIntNum[MODEM_ID_BUTT];
    VOS_UINT32 aulPpIntSlice[MODEM_ID_BUTT];
    VOS_UINT32 ulNppIntNum;
    VOS_UINT32 ulNppIntSlice;
    VOS_UINT32 ulBBPSwitchIsrErrorCount[MODEM_ID_BUTT];
    VOS_UINT32 ulBBPSwitchIsrErrorSlice[MODEM_ID_BUTT];
    VOS_UINT32 ulSOCStatRecord[10];
}HPA_INT_COUNT_STRU;

/* Copy from Linux */
typedef struct { volatile unsigned int counter; } hpa_atomic_t;

#if (OSA_CPU_CCPU == VOS_OSA_CPU)

#define atomic_set(v,i) (((v)->counter) = (i))

#define atomic_read(v)  ((v)->counter)

#endif

extern hpa_atomic_t                 g_stDspMailBoxCount;

extern VOS_SEM                      g_ulHpaDeliverSem;

extern VOS_SEM                      g_ulHpaTransferSem;

extern VOS_SEM                      g_ulHpaLoadHifiSem;

extern VOS_UCHAR                    g_ucHpaCfnRead;
extern VOS_UINT16                   g_usHpaSfnRead;

/*extern PHY_MAC_INFO_IND_STRU    g_stMacFnInfoInd;*/

/* g_ucMsgIdReceiverPidMap's size */
#define HPA_MSG_ID_PID_MAP_SIZE     256

extern HPA_ERROR_COUNT_STRU         g_astHpaErrorCount[HPA_MB_BUTT/2];

extern OM_MAX_REG_CNT_GSM_STRU  g_stGhpaRegCnt;

#ifdef HPA_ITT
typedef VOS_VOID (* HPA_DSP_INT_ISR_FUNC_HOOK)(VOS_VOID);

typedef VOS_UINT32 (* HPA_ITT_MSG_FILTER_FUNC_HOOK)(MsgBlock *pstMsgBlock);

extern HPA_DSP_INT_ISR_FUNC_HOOK g_pfnHpaDspIsrStub;

extern HPA_ITT_MSG_FILTER_FUNC_HOOK g_pfnHpaIttMsgFilterFunc;


extern VOS_VOID HPA_Send3GIttMsg(MsgBlock *pMsgBlock);
extern VOS_VOID HPA_Send2GIttMsg(MsgBlock *pMsgBlock);

#if 0
extern VOS_VOID RTT_HpaHandleMsgToGrm(MsgBlock *pMsgBlock);
#endif
extern VOS_VOID RTT_HpaHandleMsgToLapdm(MsgBlock *pMsgBlock);

/*extern VOS_VOID HPA_RttTestRegPnt(VOS_VOID);
 */
/*extern VOS_VOID HPA_RttTestCfgHandle(VOS_VOID *pMsg);
 */
extern VOS_VOID HPA_RttTestCfgHandle(VOS_VOID *pMsg);
extern VOS_VOID HPA_RttTestRegPnt(VOS_VOID);

#endif

extern HPA_INT_COUNT_STRU   g_stHpaIntCount;
extern MsgBlock*            g_pstZspWdgInt;

/* GBBPµØÖ·Ë÷ÒýÖµ */
enum BBP_REG_ADDR
{
    INT_STA,
    INT_MASK,
    INT_CLR,
    BLER_ERR,
    BLER_TOTAL,
    GTC_FN,
    DRX_INT_STA,
    DRX_INT_MASK,
    DRX_INT_CLR,
    BBP_ADDR_BUTT,
};

extern VOS_UINT32                      g_aulGUCBBPRegAddr[BBP_ADDR_BUTT][MODEM_ID_BUTT][VOS_RATMODE_BUTT];

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _HPA_GLOBAL_VAR_H */

