/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasCcInclude.h
  版 本 号   : 初稿
  作    者   : 丁庆 49431
  生成日期   : 2008年2月14日
  最近修改   : 2008年2月14日
  功能描述   : 该文件包含CC各子模块需要的所有头文件。CC所有C文件必须包含此头文件。
  函数列表   :
  修改历史   :
  1.日    期   : 2008年2月14日
    作    者   : 丁庆 49431
    修改内容   : 创建文件
  2.日    期   : 2008年10月20日
    作    者   : h44270
    修改内容   : 问题单号:A32D14153,来电时，用户尚未接听电话就打开了声码器,，AMR速率变换没有上报

******************************************************************************/
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

