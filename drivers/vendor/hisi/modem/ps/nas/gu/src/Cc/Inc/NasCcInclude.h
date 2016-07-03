
#ifndef __NASCCINCLUDE_H__
#define __NASCCINCLUDE_H__


#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "product_config.h"
#include "vos.h"
#include "Ps.h"
#include "NasCommDef.h"
#include "NasCcCommon.h"
#include "NasMncc.h"
#include "NasCcAirMsgProc.h"
#include "NasCcAirMsgSend.h"
#include "NasCcMnccProc.h"
#include "NasCcMnccSend.h"
#include "NasCcMmccProc.h"
#include "NasCcMmccSend.h"
#include "NasCcCtx.h"
#include "NasCcEntityMgmt.h"
#include "NasCcTimer.h"
#include "NasCcUserConn.h"
#include "NasCcMsgEncDec.h"
#include "NasCc.h"
#include "NasIeUtil.h"
#include "RabmCcInterface.h"
#include "NVIM_Interface.h"
#include "NasComm.h"
#include "MmCcInterface.h"
#include "GmmCcInterface.h"
#include "NasCcProcNvim.h"

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#endif /* __NASCCINCLUDE_H__ */

