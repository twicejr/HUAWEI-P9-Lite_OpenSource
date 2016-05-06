/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEsmMain.h
  Description     : NasEsmMain.c header file
  History           :
     1.¶¡Àö 00128736      2008-09-01  Draft Enact
     2.ÑîÜç»Ý 00135146    2009-03-06  Modify  BA8D01127
******************************************************************************/

#ifndef __NASESMMAIN_H__
#define __NASESMMAIN_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "NasEsmPublic.h"
/*#include "NasEsmFsm.h"
 */
#include "NasEsmAppMsgParaProc.h"
#include "NasEsmAppMsgProc.h"
#include "NasEsmEmmMsgProc.h"
#include "NasEsmRabmMsgProc.h"

#include "OmEsmInterface.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    ÉèÖÃ×Ö½Ú¶ÔÆë·½Ê½
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
extern OM_ESM_STATE_INFO_STRU   g_stEsmOmInfo[APP_ESM_MAX_EPSB_NUM];
extern VOS_VOID NAS_ESM_InitAttachBearerReestInfo();
extern VOS_UINT32 NAS_PTT_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID  NAS_PTT_TaskEntry( MsgBlock* pMsg );
extern VOS_VOID  IP_TaskEntry
(
    MsgBlock                           *pstMsg
);
extern VOS_UINT32 IP_PidInit
(
    enum VOS_INIT_PHASE_DEFINE ip
);


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


extern VOS_VOID NAS_ESM_Init(VOS_VOID);
extern VOS_VOID NAS_ESM_InitEpsbCntxtInfo(VOS_UINT32 ulEpsbId);
extern VOS_UINT32 NAS_ESM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID  NAS_ESM_TaskEntry(MsgBlock * pMsg);



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

#endif /* end of NasEsmMain.h */
