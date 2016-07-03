
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

