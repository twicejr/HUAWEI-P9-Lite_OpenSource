/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLmmPubMPrint.h
  Description     : NasLmmPubMPrint.c header file
  History         :
      1.lining 00141619       2008-10-24   Draft Enact
      2.zhengjunyan 00148421  2011-05-28   文件名由NasMmPubMPrint.h修改为
                                           NasLmmPubMPrint.h
******************************************************************************/

#ifndef __NASLMMPUBMPRINT_H__
#define __NASLMMPUBMPRINT_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "AppMmInterface.h"
#include  "LRrcLNasInterface.h"
#include  "EmmEsmInterface.h"
#include  "EmmRabmInterface.h"
#include  "NasEmmPubUCnMsgDecode.h"
#include  "NasLmmPubMIntraMsg.h"
#include  "NasLmmPubMFsm.h"
#include  "MmcLmmInterface.h"


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
#define NAS_EMM_LEN_VOS_MSG_HEADER          20




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
extern  NAS_COMM_PRINT_LIST_STRU g_astMmLppMsgIdArray[];


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID    NAS_LMM_PrintAuxFsm( VOS_VOID );
extern VOS_VOID    NAS_LMM_PrintCnMsgAndData(
                           LRRC_LNAS_MSG_STRU                        *pstCnMsg );
extern VOS_VOID    NAS_LMM_PrintFsmState(
                           NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId );
extern VOS_VOID    NAS_LMM_PrintFsmStateStack(
                           NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId );

extern VOS_INT32   NAS_LMM_PUBM_PrintAppMsg(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           APP_MM_MSG_TYPE_ENUM_UINT32             enMsgId );
extern VOS_INT32   NAS_LMM_PUBM_PrintMmcMsg(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           MMC_LMM_MSG_ID_ENUM_UINT32              enMsgId );

extern VOS_INT32   NAS_LMM_PUBM_PrintGmmMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    MMC_LMM_MSG_ID_ENUM_UINT32          enMsgId
);
extern VOS_INT32   NAS_LMM_PUBM_PrintAuxFsm(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           const NAS_LMM_AUXILIARY_FSM_STRU               *pstAuxFsm );
extern VOS_INT32   NAS_LMM_PUBM_PrintCnMsg(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_EMM_CN_MSG_TYPE_ENUM_UINT8          enMsgId );
extern VOS_INT32   NAS_LMM_PUBM_PrintData(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           LRRC_LNAS_MSG_STRU                        *pstMsg );
extern VOS_INT32   NAS_LMM_PUBM_PrintFsmState(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           const NAS_LMM_FSM_STATE_STRU                   *pstFsmState );
extern VOS_INT32   NAS_LMM_PUBM_PrintEmmUpState(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_EMM_UPDATE_STATE_ENUM_UINT8         enEmmUpState );
extern VOS_INT32   NAS_LMM_PUBM_PrintMainState(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_LMM_MAIN_STATE_ENUM_UINT16           enMainState );
extern VOS_INT32   NAS_LMM_PUBM_PrintMmIntraMsg(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_LMM_INTRA_MSG_ID_ENUM_UINT32         enMsgId );
extern VOS_VOID NAS_LMM_PUBM_PrintRevMsg
(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
);

extern VOS_VOID NAS_LMM_PUBM_PrintSendMsg(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
);

extern VOS_INT32   NAS_LMM_PUBM_PrintParallelFsm(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId );
extern VOS_INT32   NAS_LMM_PUBM_PrintPtlTimer(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTId );

extern VOS_INT32   NAS_LMM_PUBM_PrintRrcConnState(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_EMM_RRC_CONN_STATE_ENUM_UINT8       enRrcConnState );
extern VOS_INT32   NAS_LMM_PUBM_PrintRrcMsg(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           LRRC_LNAS_MSG_ID_ENUM_UINT32              enMsgId );


extern VOS_INT32   NAS_LMM_PUBM_PrintStateTimer(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStaTId );
extern VOS_INT32   NAS_LMM_PUBM_PrintSubState(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_LMM_SUB_STATE_ENUM_UINT16            enSubState );
extern VOS_INT32   NAS_LMM_PUBM_PrintTimer(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           const REL_TIMER_MSG                           *pRelTimerMsg);
extern VOS_INT32   NAS_LMM_PUBM_PrintUsimState(
                           VOS_CHAR                                *pcBuff,
                           VOS_UINT16                              usOffset,
                           NAS_EMM_USIM_STATE_ENUM_UINT8           enUsimState );


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

#endif /* end of NasLmmPubMPrint.h */
