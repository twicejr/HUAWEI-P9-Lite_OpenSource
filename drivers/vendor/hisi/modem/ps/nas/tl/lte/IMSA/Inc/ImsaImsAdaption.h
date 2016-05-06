/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaImsAdaption.h
    Description : ImsaImsAdaption.c头文件
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSAIMSADAPTION_H__
#define __IMSAIMSADAPTION_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include "vos.h"
#include "ImsaImsInterface.h"
#include "ImsaImsInterface.h"
#include "ImsCodecInterface.h"
#include "ImsaEntity.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/* 保护定时器时长为10ms */
#define IMSA_HIFI_ACK_PROTECT_LENGTH     10


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/




/*****************************************************************************
  4 Enum
*****************************************************************************/




/*****************************************************************************
  5 STRUCT
*****************************************************************************/





/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID IMSA_Snd2ImsaCallMsg(const IMSA_IMS_OUTPUT_CALL_EVENT_STRU *pstOutputCallEvent);
extern VOS_VOID IMSA_Snd2ImsaSmsMsg(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU *pstImsaImsOutputSms);
extern VOS_VOID IMSA_Snd2ImsaServiceMsg(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU *pstHicsmOutputService);
extern VOS_VOID IMSA_SndImsMsgStopReq(VOS_VOID  );
extern VOS_VOID IMSA_SndImsMsgStartReq(VOS_VOID  );
extern VOS_VOID IMSA_SndImsMsgServiceEvent(IMSA_IMS_INPUT_EVENT_STRU *pstHiInputEvent);
extern VOS_VOID IMSA_SndImsMsgCallEvent(const IMSA_IMS_INPUT_EVENT_STRU *pstHiInputEvent);
extern VOS_VOID IMSA_SndImsMsgSmsEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent);
extern VOS_VOID IMSA_SndImsMsgSystemEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent);
extern VOS_VOID IMSA_SndImsMsgParaEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent);
extern VOS_VOID IMSA_SndImsMsgUssdEvent(IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvent);
extern VOS_VOID IMSVA_ProcHifiMsg(const VOS_VOID *pRcvMsg );
extern VOS_VOID IMSVA_ProcHifiRtMsg(const VOS_VOID *pRcvMsg );
extern VOS_VOID IMSVA_TimerMsgDistr(const REL_TIMER_MSG *pRcvMsg );

extern VOS_VOID IMSA_Snd2ImsaParaMsg(const IMSA_IMS_OUTPUT_PARA_EVENT_STRU *pstOutputService);
extern VOS_VOID IMSA_Snd2ImsaSystemMsg(const IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU *pstOutputService);

extern VOS_VOID IMSA_SendImsVolteImpuQryReq(VOS_VOID);
extern VOS_VOID IMSA_ProcImsMsgQryVolteImpuCnf(const IMSA_IMS_OUTPUT_PARA_EVENT_STRU *pstOutPara);
extern VOS_VOID IMSA_SndImsMsgNvInfoEvent
(
    IMSA_IMS_INPUT_EVENT_STRU   *pstImsaImsInputEvent,
    VOS_UINT32                  ulNvInfoStruLen
);

extern VOS_UINT32 IMSA_ImsInputParaMsgSave(const IMSA_IMS_INPUT_PARA_EVENT_STRU *pstParaEvt);
extern VOS_VOID IMSA_ImsInputParaMsgClear(VOS_VOID);
extern VOS_VOID IMSA_SendImsCcwaiSetReq(VOS_UINT8 ucCallWaiting);
extern VOS_VOID IMSA_ProcImsMsgCcwaiSetCnf(const IMSA_IMS_OUTPUT_PARA_EVENT_STRU *pstOutPara);
extern VOS_VOID IMSA_SndLRrcHifiSyncSwtichInd( VOS_UINT8   ucHifiSyncEnalbed);

extern VOS_VOID IMSA_ImsAdaption_Init(VOS_VOID);
extern VOS_VOID IMSA_ClearHifiData(VOS_VOID);
extern VOS_VOID IMSA_ImsAdaption_ClearResource(VOS_VOID);
extern VOS_VOID IMSA_AddDataToBuffer(IMSA_VOICE_RX_DATA_IND_STRU *pstRxDataInd);
extern VOS_VOID IMSA_ProcTimerMsgHifiAckProtect(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_SendOneBufferData(VOS_UINT8 ulNeedAckFlag);
extern VOS_VOID IMSA_SndHifiDataInfo(VOS_VOID);
extern VOS_VOID IMSVA_StartTimer(IMSA_TIMER_STRU *pstTimer);
extern VOS_VOID IMSVA_StopTimer(IMSA_TIMER_STRU *pstTimer);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaImsAdaption.h */




