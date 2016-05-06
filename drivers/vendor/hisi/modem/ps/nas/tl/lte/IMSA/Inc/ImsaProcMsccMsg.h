/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaProcMmaMsg.h
    Description : ImsaProcMmaMsg.c头文件
    History     :
      1.sunbing 00049683    2013-06-19  Draft Enact


******************************************************************************/

#ifndef __IMSAPROCMSCCMSG_H__
#define __IMSAPROCMSCCMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "ImsaMsccInterface.h"

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


extern VOS_VOID IMSA_ProcMsccMsg(const VOS_VOID *pRcvMsg );

extern VOS_VOID IMSA_ProcMsccMsgStartReq(VOS_VOID  );

extern VOS_VOID IMSA_SndMsccMsgStartCnf(VOS_VOID  );

extern VOS_VOID IMSA_ProcMsccMsgStopReq(const VOS_VOID *pRcvMsg  );

extern VOS_VOID IMSA_SndMsccMsgStopCnf(VOS_VOID  );

extern VOS_VOID IMSA_ProcMsccMsgDeregReq(VOS_VOID );

extern VOS_VOID IMSA_SndMsccMsgDeregCnf(VOS_VOID );

extern VOS_VOID IMSA_ProcMsccMsgServiceChangeInd(const VOS_VOID *pRcvMsg  );
extern VOS_VOID IMSA_ProcMsccMsgCampInfoChangeInd
(
    const VOS_VOID                     *pRcvMsg
);
extern VOS_VOID IMSA_ProcImsMsgStartOrStopCnf(VOS_VOID);
extern VOS_VOID IMSA_SndMsccMsgImsVoiceCapNotify
(
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8   enImsVoiceCap,
    VOS_UINT32                           ucIsExistPersistentBearer
);
extern VOS_VOID IMSA_ProcMsccMsgVoiceDomainChangeInd
(
    const VOS_VOID                     *pRcvMsg
);
#if (FEATURE_ON == FEATURE_DSDS)
extern VOS_VOID IMSA_ProcTimerMsgWaitPowerOffRfExp(const VOS_VOID *pRcvMsg);
#endif

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

#endif /* end of ImsaProcMmaMsg.h */




