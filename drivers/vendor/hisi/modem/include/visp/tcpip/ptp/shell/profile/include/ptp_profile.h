/******************************************************************************

                  版权所有 (C), 2008-2018, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Profile.h
  版 本 号   : 初稿
  作    者   : 谭强
  生成日期   : 2008年5月4日
  最近修改   :
  功能描述   : PTP 模版接口定义文件
  函数列表   :
  修改历史   :
  1.日    期   : 2008年6月4日
    作    者   :  谭强
    修改内容   :    PTP_Shell_Profile参数的定义
                                ULONG ulProfileType,  (原枚举类型参数改为ULONG 类型),
                                增加参数ULONG ulFsmMode(状态机模式)

******************************************************************************/
#ifndef _PTP_PROF_H_
#define _PTP_PROF_H_

/*addtional header files*/
#include "ptp/cbb/include/ptp_inc.h"
#ifdef __cplusplus
extern "C" {
#endif

/*定义模版类型枚举*/
typedef  enum  tagPTP_PROFILE_TYPE_E
{
    ETE_UC_F = 1,       /*端到端单播，频率同步*/
    ETE_MC_F,      /*端到端多播，频率同步*/
    ETE_UC_T,      /*端到端单播，时间同步*/
    ETE_MC_T,      /*端到端多播，时间同步*/
    PTP_MC_F,      /*点到点多播，频率同步*/
    PTP_MC_T       /*点到点多播，时间同步*/
}PTP_PROFILE_TYPE_E;

/*端到端单播，频率同步*/
ULONG PTP_Profile_ETE_UC_F(USHORT usPortNumber, ULONG ulFsmMode);

/*端到端多播，频率同步*/
ULONG PTP_Profile_ETE_MC_F(USHORT usPortNumber, ULONG ulFsmMode);

/*端到端单播，时间同步*/
ULONG PTP_Profile_ETE_UC_T(USHORT usPortNumber, ULONG ulFsmMode);

/*端到端多播，时间同步*/
ULONG PTP_Profile_ETE_MC_T(USHORT usPortNumber, ULONG ulFsmMode);

/*点到点多播，频率同步*/
ULONG PTP_Profile_PTP_MC_F(USHORT usPortNumber, ULONG ulFsmMode);

/*点到点多播，时间同步*/
ULONG PTP_Profile_PTP_MC_T(USHORT usPortNumber, ULONG ulFsmMode);

ULONG PTP_Profile_Type(USHORT usPortNumber, ULONG ulFsmMode, ULONG ulProfileType);

#ifdef __cplusplus
}
#endif
#endif /*_PTP_PROF_H_*/
