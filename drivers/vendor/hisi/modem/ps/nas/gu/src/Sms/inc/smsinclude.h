/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : SmsInclude.h
  Description :
  History     :
      1.  张志勇      2004.03.09   新版作成
 2.日    期   : 2010年2月20日
   作    者   : f62575
   修改内容   : AT2D17029，增加短信任意点回放功能
*******************************************************************************/
#include "PsTypeDef.h"
#include "TafTypeDef.h"
#include "pscfg.h"
#include "psprimitive.h"
#include "product_config.h"
#include "ExtAppCmInterface.h"
#include "NasComm.h"
#include "Nasrrcinterface.h"
#include "SmsMmInterface.h"
#include "SmsGmmInterface.h"
#include "smsencap.h"
#include "smsdef.h"
#include "smsext.h"
#include "smrent.h"
#include "smcent.h"
#include "smcsmrapi.h"
#include "NasSms.h"
#include "tracelevel.h"

#include "NasOmInterface.h"

#include "MnComm.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "LmmSmsInterface.h"
#endif

