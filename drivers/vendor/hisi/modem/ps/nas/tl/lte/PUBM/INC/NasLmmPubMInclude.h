/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLmmPubMInclude.h
  Description     : NasMmPubMEntry.c header file
  History         :
      1.h41410       2008-10-27   Draft Enact
      2.z00148421    2011-05-28   文件名由 NasMmPubMInclude.h修改为NasLmmPubMInclude.h
******************************************************************************/

#ifndef __NASLMMPUBMINCLUDE_H__
#define __NASLMMPUBMINCLUDE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LRrcLNasInterface.h"
#include    "NasLmmPubMOsa.h"

#include    "LNasNvInterface.h"
#include    "NasLmmPubMFsm.h"
#include    "NasLmmPubMIntraMsg.h"
#include    "NasLmmPubMMsgBuf.h"
#include    "NasLmmPubMStack.h"
#include    "NasLmmPubMEntry.h"
#include    "NasLmmPubMPrint.h"
#include    "NasLmmPubMTimer.h"
#include    "NasLmmPubMOm.h"
#include    "NasLmmPubMNvim.h"

#include    "NasEmmPubUGlobal.h"
#include    "NasLmmPublic.h"
#include    "NasEmmPubUEntry.h"

#include    "NasEmmGutiPubInterface.h"
#include    "NasEmmIdenPubInterface.h"
#include    "NasEmmMrrcPubInterface.h"
#include    "NasEmmAttDetInterface.h"
#include    "NasEmmTauSerInclude.h"
#include    "NasEmmPlmnInterface.h"
#include    "NasEmmSecuInterface.h"
#include    "NasEmmPlmn.h"
#include    "NasEmmPubUSuspend.h"
#include    "NasEmmPubUResume.h"


#include    "MmcLmmInterface.h"
#include    "GmmLmmInterface.h"
#include    "LmmSmsInterface.h"
#include    "OmEmmInterface.h"

#if (FEATURE_LPP == FEATURE_ON)
#include    "EmmLppInterface.h"
#include    "NasEmmLppMsgProc.h"
#endif


#ifdef      PS_ITT_PC_TEST_NAS_EMM_ST
#include    "NasMmPubMTest.h"
#endif

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

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
extern NAS_LMM_COMM_ACT_STRU               g_astMmPreProcMap[];


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


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

#endif /* end of NasLmmPubMInclude.h */
