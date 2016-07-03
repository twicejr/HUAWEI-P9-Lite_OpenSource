
#ifndef __MNMSGINCLUDE_H__
#define __MNMSGINCLUDE_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"
#include  "Ps.h"
#include  "NasSms.h"
#include  "NasOmInterface.h"
#include  "NasOmTrans.h"
#include  "MnComm.h"
#include  "MnErrorCode.h"
/* 删除ExtAppMmcInterface.h*/

#include  "TafMmcInterface.h"
#include  "MnMsgExt.h"
#include  "MnMsgApi.h"
#include  "MnMsgSmCommProc.h"
#include  "MnMsgSendSms.h"
#include  "MnMsgTimerProc.h"
#include  "UsimPsInterface.h"
#include  "NVIM_Interface.h"
#include  "MnMsgUsimProc.h"
#include  "MnMsgTs.h"
#include  "MnMsgReport.h"
#include  "UsimPsApi.h"
#include  "NasComm.h"

#include  "TafCbsInterface.h"

#if (FEATURE_IMS == FEATURE_ON)
#include  "MsgImsaInterface.h"
#endif

#endif /* __MNMSGINCLUDE_H__ */

