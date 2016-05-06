/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasETcMain.h
  Description     : NasRabmMain.c header file
  History         :
      1.李洪 00150010       2009-10-13  Draft Enact

******************************************************************************/

#ifndef __NASTCMAIN_H__
#define __NASTCMAIN_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasETcPublic.h"
#include  "EmmRabmInterface.h"
#include  "MtcNasInterface.h"

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
  2 Macro
*****************************************************************************/


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
extern VOS_VOID NAS_ETC_Init(VOS_VOID);
extern VOS_UINT32 NAS_ETC_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID  NAS_ETC_TaskEntry( MsgBlock* pMsg );
extern VOS_INT32  NAS_ETC_PrintTcPdcpMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    EMM_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId
);

extern VOS_VOID NAS_ETC_PrintTcRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);

extern VOS_VOID NAS_ETC_PrintTcSendMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);

extern VOS_INT32  NAS_COMM_PrintEtcCdsMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    EMM_ERABM_MSG_TYPE_ENUM_UINT32        enMsgId
);
extern VOS_INT32  NAS_COMM_PrintEtcMtcMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    MTC_NAS_MSG_ID_ENUM_UINT32           enMsgId
);

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

#endif /* end of NasETcMain.h */
