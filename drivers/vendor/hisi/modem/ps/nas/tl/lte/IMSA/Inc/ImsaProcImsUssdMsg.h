/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

******************************************************************************
    File name   : ImsaProcImsUssdMsg.h
    Description : ImsaProcImsUssdMsg.c头文件
    History     :
      1.leili 00132387    2013-12-27  Draft Enact


******************************************************************************/

#ifndef __IMSAPROCIMSUSSDMSG_H__
#define __IMSAPROCIMSUSSDMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "ImsaImsEvent.h"
#include    "TafAppSsa.h"

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
extern VOS_VOID IMSA_ProcImsMsgUssdReasonOk(IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt);
extern VOS_VOID IMSA_ProcImsMsgUssdReasonNotify(const IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt);
extern VOS_VOID IMSA_ProcImsMsgUssdReasonRequest(const IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt);
extern VOS_VOID IMSA_ProcImsMsgUssdReasonDisconnect(IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt);
extern VOS_VOID IMSA_ProcImsMsgUssdReasonError(const IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt);
extern VOS_VOID IMSA_ImsMsgUssdEvent(VOS_VOID *pUssdEvent);


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

#endif /* end of ImsaProcImsSmsMsg.h */









