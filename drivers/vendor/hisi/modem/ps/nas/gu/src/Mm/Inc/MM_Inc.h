
#include            "PsTypeDef.h"
#include            "primitive.h"
#include            "product_config.h"
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
/* 删除ExtAppMmcInterface.h*/
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include            "Nasrrcinterface.h"
#include            "NasOmInterface.h"

#include            "NasOmTrans.h"

#include            "MmcGmmInterface.h"
#include            "MmcMmInterface.h"
#include            "MmCcInterface.h"
#include            "MmSsInterface.h"
#include            "SmsMmInterface.h"

#include            "tracelevel.h"

#include            "TcNasinterface.h"

#include            "asnasapi.h"
#include            "pscfg.h"
#include            "PSAgentInterface.h"
#include            "UsimPsApi.h"
#include            "UsimPsInterface.h"
#include            "NVIM_Interface.h"


#include            "MM_Share_inc.h"
#include            "psprimitive.h"

#include            "MM_Def.h"
#include            "MM_Global.h"
#include            "MM_Message.h"
#include            "GmmMmInterface.h"
#include            "MM_Ext.h"
#include            "MmSelf.h"
#include            "MmGsmDifMsg.h"
#include            "MmAuth.h"
#include            "MmSuspend.h"
#include            "PsCommonDef.h"
#include            "Nas_Mem.h"
#include            "NasCommDef.h"
#include            "NasMmlCtx.h"

#include            "NasMmlLib.h"

#include            "NasMmlMsgProc.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


#define MM_LOG(ModulePID, SubMod, Level, String) \
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, Level, String)

#define MM_ERR_LOG(String) \
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_ERROR, String)

#define MM_WARN_LOG(String) \
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, String)

#define MM_NORM_LOG(String) \
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, String)

#define MM_INFO_LOG(String) \
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, String)

#define MM_NORM_LOG1(String, Para1) \
            PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_NORMAL, String, Para1)



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

