

#ifndef __CNAS_HSM_PROC_NVIM_H__
#define __CNAS_HSM_PROC_NVIM_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasHsmCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/



/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/




/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID CNAS_HSM_ReadNvim(VOS_VOID);
VOS_VOID CNAS_HSM_ReadEsnAndMeidNvim(VOS_VOID);

VOS_VOID CNAS_HSM_ReadSessionRetryCfgNvim(VOS_VOID);


VOS_VOID CNAS_HSM_ReadSessionKeepAliveInfoNvim(VOS_VOID);

VOS_VOID CNAS_HSM_WriteSessionKeepAliveInfoNvim(
    CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU                  *pstSessionKeepAliveInfo
);

VOS_VOID CNAS_HSM_ReadHrpdSessionInfoNvim(VOS_VOID);

VOS_VOID CNAS_HSM_WriteHrpdSessionInfoNvim(VOS_VOID);
VOS_VOID CNAS_HSM_ReadHrpdSessionInfoExNvim(VOS_VOID);
VOS_VOID CNAS_HSM_WriteHrpdSessionInfoExNvim(VOS_VOID);

VOS_VOID CNAS_HSM_ReadHrpdUERevInfoNvim(VOS_VOID);

VOS_VOID CNAS_HSM_ReadHrpdSessionCtrlCfgNvim(VOS_VOID);

VOS_VOID CNAS_HSM_ReadHrpdAccessAuthInfoNvim(VOS_VOID);

VOS_VOID CNAS_HSM_WriteHrpdAccessAuthInfoNvim(VOS_VOID);
#endif


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

#endif /* end of CnasHsmMain.h */









