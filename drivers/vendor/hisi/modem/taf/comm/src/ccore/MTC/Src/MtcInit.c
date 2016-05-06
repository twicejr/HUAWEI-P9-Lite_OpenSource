/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcInit.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2013年07月30日
  最近修改   :
  功能描述   : MTC模块的初始化
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月30日
    作    者   : l60609
    修改内容   : 新生成

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcInit.h"
#include "MtcCtx.h"
#include "MtcMain.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_INIT_C
/*lint +e767 修改人: l00198894; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
/*****************************************************************************
 函 数 名  : MTC_PidInit
 功能描述  : MTC模块的Pid初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月12日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目

*****************************************************************************/
VOS_UINT32 MTC_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* 初始化上下文 */
            MTC_InitCtx();
            break;

        default:
            break;
    }

    return VOS_OK;
}
#endif
/*****************************************************************************
 函 数 名  : MTC_FidInit
 功能描述  : MTC的FID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ip
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月13日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目

*****************************************************************************/
VOS_UINT32 MTC_FidInit (enum VOS_INIT_PHASE_DEFINE ip)
{
#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_OK;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_MTC,
                                         (Init_Fun_Type)MTC_PidInit,
                                         (Msg_Fun_Type)MTC_ProcMsg);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(UEPS_FID_MTC, VOS_PRIORITY_M5);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            break;

        default:
            break;
    }
#endif

    return VOS_OK;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

