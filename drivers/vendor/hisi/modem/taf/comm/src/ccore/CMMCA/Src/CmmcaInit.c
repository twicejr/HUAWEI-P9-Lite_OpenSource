/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaInit.c
  版 本 号   : 初稿
  作    者   : l60609
  生成日期   : 2014年01月08日
  最近修改   :
  功能描述   : CMMCA模块的初始化
  函数列表   :
  修改历史   :
  1.日    期   : 2014年01月08日
    作    者   : l60609
    修改内容   : 新生成

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CmmcaInit.h"
#include "CmmcaMain.h"
#include "CmmcaCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人: l60609; */
#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_INIT_C
/*lint +e767 修改人: l60609; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 函 数 名  : CMMCA_PidInit
 功能描述  : CMMCA模块的Pid初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE enPhase
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月08日
    作    者   : L60609
    修改内容   : L-C互操作项目

*****************************************************************************/
VOS_UINT32 CMMCA_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* 初始化上下文 */
            CMMCA_InitCtx();
            break;

        default:
            break;
    }

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : CMMCA_FidInit
 功能描述  : CMMCA的FID初始化函数
 输入参数  : enum VOS_INIT_PHASE_DEFINE ip
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月10日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 CMMCA_FidInit (enum VOS_INIT_PHASE_DEFINE ip)
{
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                          ulRslt;

    ulRslt = VOS_OK;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_CMMCA,
                                         (Init_Fun_Type)CMMCA_PidInit,
                                         (Msg_Fun_Type)CMMCA_ProcMsg);
            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_CMMCA, VOS_PRIORITY_M5);
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
