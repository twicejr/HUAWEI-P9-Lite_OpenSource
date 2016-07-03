
#ifndef _SS_INCLUDE_H_
#define _SS_INCLUDE_H_


#include "PsTypeDef.h"
#include "psprimitive.h"
#include "pscfg.h"
#include "product_config.h"
#include "NasComm.h"
#include "MmSsInterface.h"
#include "SsDef.h"
#include "SsGlobal.h"
#include "SsExt.h"
#include "tracelevel.h"

#include "ExtAppCmInterface.h"
#include "Ssa_Define.h"
#include "Taf_Tafm_Local.h"
#include "Taf_Tafm_Remote.h"
#include "Taf_Common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */



#define SS_LOG(ModulePID, SubMod, Level, String) \
            PS_NAS_LOG(WUEPS_PID_SS, VOS_NULL, Level, String)

#define SS_ERR_LOG(String) \
            PS_NAS_LOG(WUEPS_PID_SS, VOS_NULL, PS_LOG_LEVEL_ERROR, String)

#define SS_WARN_LOG(String) \
            PS_NAS_LOG(WUEPS_PID_SS, VOS_NULL, PS_LOG_LEVEL_WARNING, String)

#define SS_NORM_LOG(String) \
            PS_NAS_LOG(WUEPS_PID_SS, VOS_NULL, PS_LOG_LEVEL_NORMAL, String)

#define SS_INFO_LOG(String) \
            PS_NAS_LOG(WUEPS_PID_SS, VOS_NULL, PS_LOG_LEVEL_INFO, String)

#define SS_WARN_LOG1(String, Para) \
            PS_NAS_LOG1(WUEPS_PID_SS, VOS_NULL, PS_LOG_LEVEL_WARNING, String, Para)

#define SS_NORM_LOG1(String, Para) \
            PS_NAS_LOG1(WUEPS_PID_SS, VOS_NULL, PS_LOG_LEVEL_NORMAL, String, Para)

/*******************************************************************************/
#define TAF_SSA_NVIM_ITEM_ACTIVE                               (1)                 /*NVIM项已激活*/
#define TAF_SSA_NVIM_ITEM_INACTIVE                           (0)                 /*NVIM项未激活*/


#define NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP               (150000)
#define NAS_SSA_TIMER_LENGTH_WAIT_APP_RSP                   (150000)


VOS_VOID SSA_ReportErrorEvent(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_SS_ERROR                        ErrorCode
);

VOS_UINT32 SSA_SendUnstructuredSSReq(VOS_UINT8 ucTi);

VOS_VOID SSA_ReportUssdDataSndEvent(VOS_UINT8 ucTi);

#if (VOS_WIN32 == VOS_OS_VER)
VOS_VOID Ss_TaskEntry_T( struct MsgCB* pMsg );
#endif

extern VOS_UINT16                  g_usTafSsaUssdTransMode;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif
