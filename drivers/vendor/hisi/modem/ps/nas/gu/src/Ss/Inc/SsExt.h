/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SsExt.h
  Description : 声明文件
  History     :
      1.  张志勇 2004.03.09   新版作成
      2.  丁  庆 2006.11.07   问题单A32D07063
*******************************************************************************/
#ifndef _SS_EXT_H_
#define _SS_EXT_H_

#include "ExtAppCmInterface.h"
#include "MmCmInterface.h"

#include "MmSsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */
/*-----------------------------------------------------------------------------*/
/*----------------------------全局变量声明-------------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  SS_ENTITY_STRU                  g_SsEntity[SS_MAX_ENTITY_NUM];
extern  SS_SAVE_MSG_STRU                g_SsSaveMsg[SS_MO_ENTITY_NUM];
/*=>A32D07063*/
#if 0
extern  SS_TIMER_MNG_STRU               g_SsTimerMng[SS_MAX_ENTITY_NUM];
#endif
/*<=A32D07063*/

/*-----------------------------------------------------------------------------*/
/*----------------------------【SsDummy.c】------------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_UINT8   per_encoder_ss(VOS_UINT16 msg_id, VOS_UINT8 *msg_data,VOS_UINT32 msg_data_size,
                            VOS_UINT8 *enc_data_adr,VOS_UINT32 *data_size,VOS_UINT8 *pad_bits);
extern  VOS_UINT8   per_decoder_ss(VOS_UINT16 msg_id, VOS_UINT8 *msg_data,VOS_UINT32 *msg_data_size,
                            VOS_UINT8 *dec_data_adr,VOS_UINT32 data_size);
extern  VOS_UINT8   per_enc_size_calculation_ss(VOS_UINT16 msg_id,VOS_UINT8 *msg_data,
                            VOS_UINT32 msg_data_size,VOS_UINT8 *enc_data_adr,VOS_UINT32 *data_size);
extern  VOS_UINT8   per_dec_size_calculation_ss(VOS_UINT16 msg_id,VOS_UINT8 *msg_data,
                            VOS_UINT32 *msg_data_size,VOS_UINT8 *dec_data_adr,VOS_UINT32 data_size);
extern  VOS_VOID    PS_C_DataInd_Func_Ss( VOS_UINT32 ulEncLen , VOS_UINT8 * pucMsg );

/*-----------------------------------------------------------------------------*/
/*----------------------------【SsDecode.c】-----------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_UINT8   Ss_Decode( VOS_VOID *pSrc, VOS_VOID *pDest, VOS_UINT32 ulMsgLen );

/*-----------------------------------------------------------------------------*/
/*----------------------------【SsEncode.c】-----------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_UINT32   Ss_Encode( VOS_VOID *pSrc, VOS_VOID *pDest, VOS_UINT8 ucMsgType, VOS_UINT8 ucTi );

/*-----------------------------------------------------------------------------*/
/*----------------------------【SsEntityMng.c】--------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_UINT8   Ss_EntityBuildTi( VOS_UINT8 ucCr );
extern  VOS_UINT8   Ss_EntityBuildCr( VOS_UINT8 ucTi );
extern  VOS_VOID    Ss_EntityCreat( VOS_UINT8 ucTi, VOS_UINT8 ucCr );
extern  VOS_VOID    Ss_EntityClear( VOS_UINT8 ucTi );
extern  VOS_UINT8   Ss_EntitySelectTi( VOS_UINT8 ucCr);
extern  VOS_VOID    *Ss_AribMalloc( VOS_UINT32 ulSize );
extern  VOS_UINT8   Ss_GetSsTi(VOS_UINT8  ucCr);

extern VOS_VOID NAS_SS_ChangeSsState(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucNewState
);
extern VOS_UINT8 NAS_SS_IsOnlyMtSs(
    VOS_UINT8                           ucTi
);
extern VOS_UINT8 NAS_SS_IsOnlyMoSs(
    VOS_UINT8                           ucTi
);


/*-----------------------------------------------------------------------------*/
/*----------------------------【SsRcvAir.c】-----------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_VOID    Ss_RcvRegister( VOS_VOID *pMsg, VOS_UINT32 ulMsgLen, VOS_UINT8 ucTi );
extern  VOS_VOID    Ss_RcvFacility( VOS_VOID *pMsg, VOS_UINT32 ulMsgLen, VOS_UINT8 ucTi );
extern  VOS_VOID    Ss_RcvRelCmpl( VOS_VOID *pMsg, VOS_UINT32 ulMsgLen, VOS_UINT8 ucTi );
extern  VOS_VOID    Ss_RcvUnknownAirMsg( VOS_UINT8 ucTi );

/*-----------------------------------------------------------------------------*/
/*----------------------------【SsRcvMm.c】------------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_VOID    Ss_RcvMmMsg( VOS_VOID *pMsg );
extern  VOS_VOID    Ss_RcvMmssEstCnf( VOS_VOID *pMsg );

VOS_VOID TAF_SS_ConvertMmssRelCauseToSsassCause(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmssRelCause,
    SSA_SS_REL_CAUSE_ENUM_UINT32       *penSsCause
    );
extern VOS_UINT8 Ss_CheckAirMsg(VOS_VOID *pMsg);
extern VOS_UINT32 LCS_RcvMmlcsMsg(
    VOS_UINT8                           ucTi,
    VOS_VOID                           *pAirMsg
);

extern VOS_VOID Ss_RcvMmssDataInd(
                       VOS_VOID *pMsg
                       );
extern VOS_VOID Ss_RcvMmssRelInd(
                      VOS_VOID *pMsg
                      );

/*-----------------------------------------------------------------------------*/
/*----------------------------【SsRcvSsa.c】-----------------------------------*/
/*-----------------------------------------------------------------------------*/
VOS_VOID    Ss_RcvSsaMsg(
    VOS_VOID                            *pMsg
);
VOS_VOID Ss_RcvMnssSsStatusNty(
    ST_SSP_MSG                         *pSspMsg
);

/*-----------------------------------------------------------------------------*/
/*----------------------------【SsSndAir.c】-----------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_VOID    Ss_SaveRegister( VOS_VOID *pSspMsg, VOS_UINT8 ucTi );
extern  VOS_VOID    Ss_SndRegister( VOS_UINT8 ucTi );
extern  VOS_VOID    Ss_SndFacility( VOS_VOID *pSspMsg, VOS_UINT8 ucTi );
extern  VOS_VOID    Ss_SndRelCmpl( VOS_VOID *pSspMsg, VOS_UINT8 ucTi, VOS_UINT8 ucCause );

extern  VOS_VOID Ss_DeleteRegister(VOS_UINT8 ucTi);

/*-----------------------------------------------------------------------------*/
/*----------------------------【SsSndMm.c】------------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_VOID    Ss_SndMmssEstReq(
    VOS_UINT8                           ucTi,                                   /* 对应的MM连接的TI                         */
    VOS_UINT8                           ucRedialFlg
);
extern  VOS_VOID    Ss_SndMmssDataReq( VOS_UINT8 ucTi, VOS_UINT8 *pucSsMsg, VOS_UINT32 ulSsMsgSize );
extern  VOS_VOID    Ss_SndMmssRelReq( VOS_UINT8 ucTi );
extern  VOS_VOID    Ss_SndMmssAbortReq( VOS_UINT8 ucTi );

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_SS_SndMmBeginSessionNotify(
    MMSS_SESSION_TYPE_ENUM_UINT8        enSessionType
);
VOS_VOID NAS_SS_SndMmEndSessionNotify(
    MMSS_SESSION_TYPE_ENUM_UINT8        enSessionType
);
#endif
VOS_VOID Ss_SndMmssSsStatusNty(
    MMSS_STATUS_ENUM_UINT8              enSsStatus
);

/*=>A32D07063*/
#if 0
/*-----------------------------------------------------------------------------*/
/*----------------------------【SsSndTimer.c】---------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_VOID    Ss_TimerStart( VOS_UINT8 ucTi );
extern  VOS_VOID    Ss_TimerStop( VOS_UINT8 ucTi );
#endif
/*<=A32D07063*/

/*-----------------------------------------------------------------------------*/
/*----------------------------【SsTaskEntry.c】--------------------------------*/
/*-----------------------------------------------------------------------------*/
extern  VOS_VOID    Ss_TaskInit(VOS_VOID);
extern  VOS_VOID    Ss_RcvTimerOut(VOS_UINT8 ucTi,VOS_UINT8 ucTimerId);
extern  VOS_VOID    Ss_Init(VOS_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
