/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXsmsTimer.c
  版 本 号   : 初稿
  作    者   : h00300778
  生成日期   : 2014年11月03日
  功能描述   : 1X SMS(Short Message Service)的定时器处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : h00300778
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafXsmsTimer.h"
#include  "TafXsmsCtx.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_TIMER_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
HTIMER                                  g_astXsmsTimer[TI_TAF_XSMS_TIMER_BUTT] = {VOS_NULL_PTR};
/*****************************************************************************
  3 函数定义
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_XSMS_StartTimer
 功能描述  : 打开XSMS模块使用的定时器
 输入参数  : ulTimerId:定时器ID
             ulTimerLen: 定时器时长
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_StartTimer(VOS_UINT32 ulTimerId, VOS_UINT32 ulTimerLen)
{
    if (TI_TAF_XSMS_TIMER_BUTT <= ulTimerId)
    {
        return;
    }

    TAF_XSMS_NORMAL_LOG1("TAF_XSMS_StartTimer: start timer id is", ulTimerId);
    TAF_XSMS_NORMAL_LOG1("TAF_XSMS_StartTimer: start timer len is", ulTimerLen);

    (VOS_VOID)VOS_StartRelTimer(&g_astXsmsTimer[ulTimerId], UEPS_PID_XSMS, ulTimerLen, ulTimerId, 0, VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_XSMS_StopTimer
 功能描述  : 停止XSMS模块使用的定时器
 输入参数  : ulTimerId:定时器ID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : C00299064
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_XSMS_StopTimer(VOS_UINT32 ulTimerId)
{
    if (TI_TAF_XSMS_TIMER_BUTT <= ulTimerId)
    {
        return;
    }

    if (VOS_NULL_PTR == g_astXsmsTimer[ulTimerId])
    {
        return;
    }

    TAF_XSMS_NORMAL_LOG1("TAF_XSMS_StartTimer: stop timer id is", ulTimerId);

    (VOS_VOID)VOS_StopRelTimer(&g_astXsmsTimer[ulTimerId]);

    return;
}




#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





