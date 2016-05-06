

#ifndef __CNAS_HSM_PROC_CARD_H__
#define __CNAS_HSM_PROC_CARD_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "UsimPsInterface.h"

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
VOS_VOID CNAS_HSM_SndReadUsimmFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enCardApp,
    USIMM_DEF_FILEID_ENUM_UINT32        enFileId
);

VOS_VOID  CNAS_HSM_RcvUsimmReadIccidFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
);

VOS_VOID  CNAS_HSM_RcvUsimmReadUimidFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
);

VOS_VOID  CNAS_HSM_RcvUsimmReadEsnMeidMeFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
);

VOS_VOID  CNAS_HSM_RcvUsimmReadHrpdAccessAuthUserNameFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg
);

VOS_VOID CNAS_HSM_SndReadUsimmStoreEsnMeidRsltReq(VOS_VOID);

VOS_VOID  CNAS_HSM_RcvUsimmReadFileCnf(
    USIMM_READFILE_CNF_STRU                                *pstUsimmReadCnfMsg,
    USIMM_DEF_FILEID_ENUM_UINT32                            enEfId
);
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

#endif /* end of CnasHsmProcUsim.h */

