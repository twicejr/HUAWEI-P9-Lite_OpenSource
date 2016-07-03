

#ifndef _GMMINCLUDE_H_
#define _GMMINCLUDE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*#define VOS_PID_TIMER   100
 */
/*#define WUEPS_PID_OM    101
 */
/*#define WUEPS_PID_ADMIN 102
 */
/*#define WUEPS_PID_GAS   140
 */
/*#define WUEPS_PID_TTF   141
 */
/*#define LLC_GMM_PID     142
 */

#include "product_config.h"
#include "Nasrrcinterface.h"
#include "tracelevel.h"
#include "asnasapi.h"
#include "NasOmInterface.h"

#include "NasOmTrans.h"

#include "PSAgentInterface.h"
#include "UsimPsApi.h"
#include "UsimPsInterface.h"

#include "GmmApi.h"
#include "NVIM_Interface.h"

#include "MM_Global.h"


#include "MM_Share_inc.h"

#include "MmcGmmInterface.h"
#include "NasGmmInterface.h"
#include "SmGmmInterface.h"
#include "SmsGmmInterface.h"
#include "GmmCcInterface.h"

#include "MsccMmcInterface.h"

/* É¾³ýExtAppMmcInterface.h*/

#include "MmcMmInterface.h"

#include "GmmMmInterface.h"

#include "TcNasinterface.h"




#include "LLInterface.h"

#include "GmmDef.h"
#include "GmmStru.h"
#include "PsCommonDef.h"
#include "GmmExt.h"

#include "NasMmlCtx.h"

#include "NasMmlLib.h"

#include "NasMmlMsgProc.h"

#if (FEATURE_ON == FEATURE_LTE)
  #include "GmmLmmInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif /* _GMMINCLUDE_H_ */
