

#ifndef __NASRABMMAIN_H__
#define __NASRABMMAIN_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasERabmPublic.h"
#include  "NasERabmTest.h"

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
#define NAS_ERABM_IP_HEADER_BUFFER_LEN           (36)
#define NAS_ERABM_GET_IP_HEADER_BUFFER()         (g_aucERabmIpData)

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
extern VOS_UINT8              g_aucERabmIpData[NAS_ERABM_IP_HEADER_BUFFER_LEN];

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/

extern VOS_VOID NAS_ERABM_TaskEntry(MsgBlock* pMsg);
extern VOS_VOID NAS_ERABM_EsmMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ERABM_EmmMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ERABM_RrcMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_VOID   NAS_ERABM_TimerMsgDistr(const VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ERABM_TimerStart
(
    VOS_UINT32                          ulTimerLen,
    NAS_ERABM_TIMER_NAME_ENUM_UINT8     enTimerName,
    VOS_UINT32                          ulTimerPara
);
extern VOS_VOID NAS_ERABM_TimerStop( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName );
extern VOS_VOID NAS_ERABM_Init(VOS_VOID);
extern VOS_VOID NAS_ERABM_ClearRabmResource( VOS_VOID );
extern VOS_VOID NAS_ERABM_ClearEpsbResource( VOS_UINT32 ulEpsbId );
extern VOS_VOID  NAS_ERABM_SetEmmSrState( NAS_ERABM_SERVICE_STATE_ENUM_UINT32 enSrState );
extern NAS_ERABM_SERVICE_STATE_ENUM_UINT32  NAS_ERABM_GetEmmSrState( VOS_VOID );
extern NAS_ERABM_TIMER_STATE_ENUM_UINT32  NAS_ERABM_IsTimerRunning( NAS_ERABM_TIMER_NAME_ENUM_UINT8 enTimerName );
extern VOS_INT32  NAS_ERABM_PrintRabmRrcStatusInd
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ERABM_PrintRabmRrcRabInd
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ERABM_PrintRabmAppMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    EMM_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId
);

extern VOS_INT32  NAS_ERABM_PrintRabmRrcMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);

extern VOS_INT32  NAS_ERABM_PrintRabmTimer
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    VOS_UINT32                           ulTimerType
);

extern VOS_VOID  NAS_ERABM_PrintRabmRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);

extern VOS_VOID  NAS_ERABM_PrintRabmSendMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);

extern VOS_UINT32 NAS_ERABM_GetActiveEpsBearerNum( VOS_VOID );
extern VOS_VOID NAS_REABM_RcvRabmRrmStatusInd();
extern VOS_VOID NAS_ERABM_RrmMsgDistr(VOS_VOID *pRcvMsg);
extern VOS_VOID NAS_ERABM_SndRabmEmmReestReq
(
    VOS_UINT32                          ulIsEmcType
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_VOID NAS_ERABM_InitEhrpdIdInfo(VOS_UINT32    ulEhrpdBearerId);
extern VOS_VOID NAS_ERABM_InitEhrpdEntity(VOS_VOID);
extern VOS_UINT32 NAS_ERABM_GetActiveEhrpdBearerNum(VOS_VOID);
#endif


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

#endif /* end of NasERabmMain.h */

