/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmCtx.c
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年5月8日
  最近修改   :
  功能描述   : TafSpmCtx.C文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月8日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafSpmFsmMainTbl.h"
#include "TafSpmMain.h"
#include "TafSpmCtx.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafLog.h"
#include "MnComm.h"
#include "UsimPsInterface.h"
#include "TafSpmSndInternalMsg.h"
#include "TafSpmMntn.h"
#include "NasUsimmApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 常量定义
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_CTX_C

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
/* 保存共用的CTX */
TAF_SPM_CONTEXT_STRU                    g_stTafSpmCtx;

/*****************************************************************************
 全局变量名    : gastSpmGetClientIdList
 全局变量说明  : 获取当前消息所对应的client ID的处理函数列表
 1.日    期   : 2013年5月8日
   作    者   : w00176964
   修改内容   : 新建
 2.日    期   : 2013年6月26日
   作    者   : f62575
   修改内容   : V9R1 STK升级
*****************************************************************************/
TAF_SPM_GET_MSG_CLIENT_ID_LIST_STRU gastSpmGetClientIdList[] =
{
    {WUEPS_PID_AT,      TAF_SPM_GetClientIdWithAppMsg},
    {MAPS_STK_PID,      TAF_SPM_GetClientIdWithStkMsg},
    {WUEPS_PID_USIM,    TAF_SPM_GetClientIdWithUsimMsg},
    {MAPS_PB_PID,       TAF_SPM_GetClientIdWithPbMsg},
    {WUEPS_PID_TAF,     TAF_SPM_GetClientIdWithTafMsg},
    {VOS_PID_TIMER,     TAF_SPM_GetClientIdWithVosTimerMsg},
};

/*****************************************************************************
  6 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_SPM_GetSpmCtxAddr
 功能描述  : 获取当前spm的CTX
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前spm的CTX
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月8日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_CONTEXT_STRU* TAF_SPM_GetSpmCtxAddr( VOS_VOID )
{
    return &(g_stTafSpmCtx);
}


/*****************************************************************************
 函 数 名  : TAF_SPM_SetCurrEntityFsmState
 功能描述  : 设置当前client ID实体所对应的状态机状态
 输入参数  : ulState:状态机状态
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_SetCurrEntityFsmState(
    VOS_UINT32                          ulState
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx.ulState = ulState;

    TAF_SPM_LogFsmInfo();
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrEntityFsmState
 功能描述  : 获取当前client ID实体所对应的状态机状态
 输入参数  : 无
 输出参数  : ulState:当前client ID实体所对应的状态机状态
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_SPM_GetCurrEntityFsmState( VOS_VOID )
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx.ulState);
}


/*****************************************************************************
 函 数 名  : TAF_SPM_SetCurrEntityFsmClientId
 功能描述  : 设置当前client ID实体所对应的client ID
 输入参数  : usClientId:client ID
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_SetCurrEntityFsmClientId(
    VOS_UINT16                          usClientId
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->usClientId = usClientId;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrEntityFsmClientId
 功能描述  : 获取当前client ID实体所对应的client ID
 输入参数  : 无
 输出参数  : usClientId:client ID
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT16  TAF_SPM_GetCurrEntityFsmClientId( VOS_VOID )
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->usClientId);
}



/*****************************************************************************
 函 数 名  : TAF_SPM_SetCurrEntityFsmAddr
 功能描述  : 设置当前client id实体所对应的状态机地址
 输入参数  : ucFsmIndex:client id的状态机数组索引
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月14日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SPM_SetCurrEntityFsmAddr(
    VOS_UINT8                           ucFsmIndex
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm = &(TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex]);
}



/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrEntityFsmAddr
 功能描述  : 获取当前client id实体所对应的状态机地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前client id实体所对应的状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月14日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmAddr(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetCurrEntityFsmRunFlg
 功能描述  : 设置当前client id实体所对应的状态机运行标记
 输入参数  : ucRunFlg:当前client id的实体对应的状态机运行标记
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_SetCurrEntityFsmRunFlg(
    VOS_UINT8                           ucRunFlg
)
{
    TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->ucRunFlg = ucRunFlg;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrEntityFsmRunFlg
 功能描述  : 获取当前client id实体所对应的状态机运行标记
 输入参数  : 无
 输出参数  : 当前client id实体所对应的状态机运行标记
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8  TAF_SPM_GetCurrEntityFsmRunFlg(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->ucRunFlg);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrEntityFsmId
 功能描述  : 获取当前client id实体所对应的状态机ID
 输入参数  : 无
 输出参数  : 当前client id实体所对应的状态机ID
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月16日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_FSM_ID_ENUM_UINT32  TAF_SPM_GetCurrEntityFsmId(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx.enFsmId);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrEntityFsmCtxAddr
 功能描述  : 获取当前client Id实体所对应的状态机上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前CLIENT ID实体所对应的状态机上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetCurrEntityFsmCtxAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->pstCurrEntityFsm->stFsmCtx);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrMainFsmAddr
 功能描述  : 获取当前主状态机地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前主状态机地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SPM_MAIN_FSM_CTX_STRU* TAF_SPM_GetCurrMainFsmAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stCurMainFsm);
}


/*****************************************************************************
 函 数 名  : TAF_SPM_GetEntityFsmRunFlgByFsmIndex
 功能描述  : 获取指定索引的CLIENT ID实体状态机运行标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 指定索引的client ID实体状态机运行标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetEntityFsmRunFlgByFsmIndex(
    VOS_UINT8                           ucFsmIndex
)
{
    return (TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex].ucRunFlg);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetEntityFsmCtxAddrByFsmIndex
 功能描述  : 获取指定索引的client ID实体所对应的状态机上下文地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 指定索引的client ID实体所对应的状态机上下文地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SPM_FSM_CTX_STRU* TAF_SPM_GetEntityFsmCtxAddrByFsmIndex(
    VOS_UINT8                           ucFsmIndex
)
{
    return &(TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex].stFsmCtx);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitEntityFsmCtx
 功能描述  : 初始化CLIENT ID实体状态机上下文
 输入参数  : 无
 输出参数  : pstCurrFsmCtx:当前client ID实体状态机上下文信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月15日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_SPM_InitEntityFsmCtx(
    TAF_SPM_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId    = TAF_SPM_FSM_BUTT;
    pstCurrFsmCtx->pstFsmDesc = VOS_NULL_PTR;
    pstCurrFsmCtx->ulState    = TAF_SPM_SERVICE_CTRL_STA_BUTT;

    PS_MEM_SET(&pstCurrFsmCtx->stEntryMsg,
               0,
               sizeof(pstCurrFsmCtx->stEntryMsg));
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitMainCtrlInfo
 功能描述  : 初始化当前SPM模块的主控信息
 输入参数  : 无
 输出参数  : pstMainCtrl:当前SPM模块的主控信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_InitMainCtrlInfo(
    TAF_SPM_MAIN_CTRL_INFO_STRU        *pstMainCtrl
)
{
    /* 初始化当前主控信息 */
    pstMainCtrl->ucUpdateEntryMsgFlg     = VOS_FALSE;

    PS_MEM_SET( pstMainCtrl->aucRsv,
                (VOS_UINT8)0x00,
                sizeof(pstMainCtrl->aucRsv) );

    PS_MEM_SET( &(pstMainCtrl->stServiceCtrlEntryMsg),
                (VOS_UINT8)0x00,
                sizeof(TAF_SPM_ENTRY_MSG_STRU) );

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitServiceCtrlCfgInfo
 功能描述  : 初始化当前SPM模块的service ctrl的配置信息
 输入参数  : 无
 输出参数  : pstServiceCtrlCfg:service ctrl的配置信息
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数
 2.日    期   : 2013年6月5日
   作    者   : z00161729
   修改内容   : SVLTE 和usim接口调整修改

*****************************************************************************/
VOS_VOID  TAF_SPM_InitServiceCtrlCfgInfo(
    TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU *pstServiceCtrlCfg
)
{
    pstServiceCtrlCfg->ulMeStatus                               = TAF_FDN_CHECK_FEATURE_OFF;
    pstServiceCtrlCfg->ucSimCallCtrlSupportFlg                  = VOS_FALSE;

    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
    pstServiceCtrlCfg->enVpCfgState                             = TAF_SPM_VP_MO_MT_BOTH;
    /* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */


    
    pstServiceCtrlCfg->stBufferServiceReqProtectTimerInfo.ulBufferCcProtectTimerLen 
                                        = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;
    pstServiceCtrlCfg->stBufferServiceReqProtectTimerInfo.ulBufferSmsProtectTimerLen
                                        = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;
    pstServiceCtrlCfg->stBufferServiceReqProtectTimerInfo.ulBufferSsProtectTimerLen
                                        = TI_TAF_SPM_CC_SMS_SS_SRV_REQ_PROTECT_TIMER_DEFAULT_VAL;

    
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitFsmCtx_Main
 功能描述  : 初始化主状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月8日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  TAF_SPM_InitFsmCtx_Main(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitFsmCtx_ServiceCtrl
 功能描述  : 初始化service ctrl状态机上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月7日
    作    者   : w00176964
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID  TAF_SPM_InitFsmCtx_ServiceCtrl(VOS_VOID)
{
    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_FSM_InitEntityFsm
 功能描述  : 启动client ID实体状态机
 输入参数  : enFsmId:状态机ID
             pstFsmDesc:状态机描述表
             ulState:状态机启动状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : W00176964
   修改内容   : 新生成函数
****************************************************************************/
VOS_VOID TAF_SPM_FSM_InitEntityFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
)
{
    TAF_SPM_FSM_CTX_STRU               *pstCurrEntityFsmCtx         = VOS_NULL_PTR;

    /*  获取当前client ID实体状态机上下文 */
    pstCurrEntityFsmCtx                 = TAF_SPM_GetCurrEntityFsmCtxAddr();

    pstCurrEntityFsmCtx->enFsmId      = enFsmId;
    pstCurrEntityFsmCtx->pstFsmDesc   = pstFsmDesc;
    pstCurrEntityFsmCtx->ulState      = ulState;

    TAF_SPM_SetCurrEntityFsmRunFlg(VOS_TRUE);

    /* 初始化状态机上下文 */
    pstCurrEntityFsmCtx->pstFsmDesc->pfInitHandle();

    TAF_SPM_LogFsmInfo();
}

/*****************************************************************************
 函 数 名  : TAF_SPM_FSM_InitMainFsm
 功能描述  : 启动主状态机
 输入参数  : enFsmId:状态机ID
             pstFsmDesc:状态机描述表
             ulState:状态机启动状态
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月15日
   作    者   : W00176964
   修改内容   : 新生成函数
****************************************************************************/
VOS_VOID TAF_SPM_FSM_InitMainFsm(
    TAF_SPM_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_FSM_DESC_STRU                  *pstFsmDesc,
    VOS_UINT32                          ulState
)
{
    TAF_SPM_MAIN_FSM_CTX_STRU          *pstCurrMainFsm  = VOS_NULL_PTR;

    /*  获取当前main状态机信息 */
    pstCurrMainFsm               = TAF_SPM_GetCurrMainFsmAddr();

    pstCurrMainFsm->stFsmCtx.enFsmId      = enFsmId;
    pstCurrMainFsm->stFsmCtx.pstFsmDesc   = pstFsmDesc;
    pstCurrMainFsm->stFsmCtx.ulState      = ulState;

    /* 初始化状态机上下文 */
    pstCurrMainFsm->stFsmCtx.pstFsmDesc->pfInitHandle();
}


/*****************************************************************************
 函 数 名  : TAF_SPM_FSM_QuitCurrEntityFsm
 功能描述  : 退出当前client ID实体状态机
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013-5-15
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_FSM_QuitCurrEntityFsm(VOS_VOID)
{
    TAF_SPM_FSM_CTX_STRU               *pstCurrFsmCtx = VOS_NULL_PTR;

    /*  获取当前的client ID实体状态机上下文 */
    pstCurrFsmCtx               = TAF_SPM_GetCurrEntityFsmCtxAddr();

    /* 清空状态机描述表和状态机ID */
    pstCurrFsmCtx->pstFsmDesc   = VOS_NULL_PTR;
    pstCurrFsmCtx->enFsmId      = TAF_SPM_FSM_BUTT;
    pstCurrFsmCtx->ulState      = TAF_SPM_SERVICE_CTRL_STA_BUTT;

    TAF_SPM_SetCurrEntityFsmClientId(TAF_SPM_INVALID_CLIENT_ID);
    TAF_SPM_SetCurrEntityFsmRunFlg(VOS_FALSE);

    TAF_SPM_LogFsmInfo();
}


/*****************************************************************************
 函 数 名  : TAF_SPM_InitEntityFsm
 功能描述  : client ID实体状态机的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_InitEntityFsm(VOS_VOID)
{
    VOS_UINT8                           i;

    /* for 循环，初始化所有实体状态机上下文 */
    for (i = 0; i < TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM; i++)
    {
        /* 根据设置当前的实体状态机 */
        TAF_SPM_SetCurrEntityFsmAddr(i);

        /* 初始化实体上下文 */
        TAF_SPM_InitEntityFsmCtx(TAF_SPM_GetCurrEntityFsmCtxAddr());

        TAF_SPM_SetCurrEntityFsmRunFlg(VOS_FALSE);

        TAF_SPM_SetCurrEntityFsmClientId(TAF_SPM_INVALID_CLIENT_ID);
    }
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitMainFsm
 功能描述  : 主状态机的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_InitMainFsm(VOS_VOID)
{
    TAF_SPM_MAIN_FSM_CTX_STRU          *pstMainFsmCtx = VOS_NULL_PTR;

    pstMainFsmCtx = TAF_SPM_GetCurrMainFsmAddr();

    pstMainFsmCtx->stFsmCtx.enFsmId         = TAF_SPM_FSM_BUTT;
    pstMainFsmCtx->stFsmCtx.ulState         = TAF_SPM_MAIN_STA_BUTT;
    pstMainFsmCtx->stFsmCtx.pstFsmDesc      = VOS_NULL_PTR;

    PS_MEM_SET(&pstMainFsmCtx->stFsmCtx.stEntryMsg,
               0,
               sizeof(pstMainFsmCtx->stFsmCtx.stEntryMsg));

}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrEntityFsmEntryMsgAddr
 功能描述  : 获取当前client id实体的状态机的入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前client id实体状态机入口消息的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetCurrEntityFsmEntryMsgAddr(VOS_VOID)
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurEntityFsmCtx = VOS_NULL_PTR;

    /*  获取当前的client ID状态机上下文地址 */
    pstCurEntityFsmCtx = TAF_SPM_GetCurrEntityFsmAddr();

    return &(pstCurEntityFsmCtx->stFsmCtx.stEntryMsg);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrEntityFsmEntryMsgSndPid
 功能描述  : 获取当前client id实体的状态机的入口消息的发送PID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前client id实体状态机入口消息的发送pid
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月19日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_GetCurrEntityFsmEntryMsgSndPid(VOS_VOID)
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurEntityFsmCtx = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg                = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                                    *pstAppMsg                  = VOS_NULL_PTR;
    VOS_UINT32                                              ulSndPid;

    /*  获取当前的client ID状态机上下文地址 */
    pstCurEntityFsmCtx = TAF_SPM_GetCurrEntityFsmAddr();

    pstEntryMsg  = &(pstCurEntityFsmCtx->stFsmCtx.stEntryMsg);
    pstAppMsg    = (MN_APP_REQ_MSG_STRU*)pstEntryMsg->aucEntryMsgBuffer;
    ulSndPid     = pstAppMsg->ulSenderPid;

    return ulSndPid;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCurrEntityFsmEntryMsgName
 功能描述  : 获取当前client id实体的状态机的入口消息的消息名
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 当前client id实体状态机入口消息的消息名
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月19日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TAF_SPM_GetCurrEntityFsmEntryMsgName(VOS_VOID)
{
    TAF_SPM_CLIENT_ID_ENTITY_FSM_CTX_STRU                  *pstCurEntityFsmCtx = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg                = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                                    *pstAppMsg                  = VOS_NULL_PTR;
    VOS_UINT16                                              usMsgName;

    /*  获取当前的client ID状态机上下文地址 */
    pstCurEntityFsmCtx = TAF_SPM_GetCurrEntityFsmAddr();

    pstEntryMsg  = &(pstCurEntityFsmCtx->stFsmCtx.stEntryMsg);
    pstAppMsg    = (MN_APP_REQ_MSG_STRU*)pstEntryMsg->aucEntryMsgBuffer;
    usMsgName    = pstAppMsg->usMsgName;

    return usMsgName;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetEntityFsmClientIdByFsmIndex
 功能描述  : 根据状态机数组的索引获取状态机的client ID
 输入参数  : ucFsmIndex:状态机数组的索引
 输出参数  : 无
 返 回 值  : 当前状态机对应的client ID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT16 TAF_SPM_GetEntityFsmClientIdByFsmIndex(
    VOS_UINT8                           ucFsmIndex
)
{
    return (TAF_SPM_GetSpmCtxAddr()->astEntityFsm[ucFsmIndex].usClientId);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetEntityFsmIndexByClientId
 功能描述  : 根据状态机的client ID获取状态机数组的索引
 输入参数  : usClientId:状态机的client ID
 输出参数  : 无
 返 回 值  : 状态机数组的索引
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetEntityFsmIndexByClientId(
    VOS_UINT16                          usClientId
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucFsmIndex;
    VOS_UINT16                          usCurClientId;
    VOS_UINT8                           ucRunFlg;

    ucFsmIndex = TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX;

    /* client ID无效不进行查找直接返回 */
    if (TAF_SPM_INVALID_CLIENT_ID == usClientId)
    {
        return ucFsmIndex;
    }

    for (i = 0; i < TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM; i++)
    {
        usCurClientId   = TAF_SPM_GetEntityFsmClientIdByFsmIndex(i);
        ucRunFlg        = TAF_SPM_GetEntityFsmRunFlgByFsmIndex(i);

        if ((usClientId == usCurClientId)
         && (VOS_TRUE   == ucRunFlg))
        {
            ucFsmIndex = i;
            break;
        }
    }

    return ucFsmIndex;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_GetIdleEntityFsmIndex
 功能描述  : 从client ID实体状态机数组中获取空闲的状态机的索引
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 空闲状态机索引 无效表示无空闲状态机在运行
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetIdleEntityFsmIndex(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucRunFlg;
    VOS_UINT8                           ucIndex;

    ucIndex = TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX;

    for (i = 0; i < TAF_SPM_MAX_CLIENT_ID_ENTITY_FSM_ID_NUM; i++)
    {
        ucRunFlg = TAF_SPM_GetEntityFsmRunFlgByFsmIndex(i);

        if (VOS_FALSE == ucRunFlg)
        {
            ucIndex = i;
            break;
        }
    }

    return ucIndex;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_SaveCurrEntityFsmEntryMsg
 功能描述  : 保存当前client ID实体状态机的子状态机的入口消息
 输入参数  : ulEventType            :入口消息类型
             pstMsg                 :入口消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013-5-9
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SaveCurrEntityFsmEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前处理入口消息的缓冲区地址 */
    /* 获得当前处理SPM入口消息的缓冲区地址 */
    pstEntryMsg                 =   TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;
    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}



/*****************************************************************************
 函 数 名  : TAF_SPM_GetTimerCtxAddr
 功能描述  : 获取spm CTX模块中定时器的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : spm CTX模块中定时器的上下文指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_TIMER_CTX_STRU*  TAF_SPM_GetTimerCtxAddr( VOS_VOID )
{
    return TAF_SPM_GetSpmCtxAddr()->astSpmTimerCtx;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetServiceCtrlCfgInfoAddr
 功能描述  : 获取spm CTX模块中service ctrl的CFG信息的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : spm CTX模块中service ctrl的CFG信息的上下文指针
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_SERVICE_CTRL_CFG_INFO_STRU*  TAF_SPM_GetServiceCtrlCfgInfoAddr( VOS_VOID )
{
    return &(TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetBufferServiceReqProtectTimerInfo
 功能描述  : 获取缓存cc sms ss 服务请求保护定时器信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU:缓存服务请求时保护定时器信息
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年10月9日
   作    者   : c00318887
   修改内容   : 新建函数
*****************************************************************************/
TAF_SPM_BUFFER_SERVICE_REQ_PROTECT_TIMER_STRU* TAF_SPM_GetBufferServiceReqProtectTimerInfo(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo);
}

/*****************************************************************************
 函 数 名  : TAF_Spm_GetBufferCcProtectTimerLen
 功能描述  : 获取缓存cc 服务请求时保护定时器时长，单位 ms
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 保护定时器时长，单位 ms
 调用函数  :
 被调函数  :

 修改历史      :

  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32   TAF_Spm_GetBufferCcProtectTimerLen(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo.ulBufferCcProtectTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetBufferSmsProtectTimerLen
 功能描述  : 获取缓存Sms 服务请求时保护定时器时长，单位 ms
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 保护定时器时长，单位 ms
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32   TAF_SPM_GetBufferSmsProtectTimerLen(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo.ulBufferSmsProtectTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetBufferSsProtectTimerLen
 功能描述  : 获取缓存Ss 服务请求时保护定时器时长，单位 ms
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 保护定时器时长，单位 ms
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年10月9日
    作    者   : c00318887
    修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32   TAF_SPM_GetBufferSsProtectTimerLen(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->stServiceCtrlCfgInfo.stBufferServiceReqProtectTimerInfo.ulBufferSsProtectTimerLen;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetUpdateEntryMsgFlg
 功能描述  : 设置SPM模块中替换APP向发送SS消息的标记
 输入参数  : ucReplaceFlg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月9日
   作    者   : w00176964
   修改内容   : 新建函数

*****************************************************************************/
VOS_VOID TAF_SPM_SetUpdateEntryMsgFlg(
    VOS_UINT8                           ucReplaceFlg
)
{
    TAF_SPM_GetSpmCtxAddr()->stMainCtrlInfo.ucUpdateEntryMsgFlg = ucReplaceFlg;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetUpdateEntryMsgFlg
 功能描述  : 获取SPM模块中更新service ctrl入口消息的标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SPM模块中更新service ctrl入口消息的标记
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年5月8日
   作    者   : w00176964
   修改内容   : 新建函数

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetUpdateEntryMsgFlg(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stMainCtrlInfo.ucUpdateEntryMsgFlg);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_UpdateServiceCtrlEntryMsg
 功能描述  : 更新service ctrl的入口消息
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013-05-8
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_UpdateServiceCtrlEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 获得当前缓存的发送给SS的请求消息的缓冲区地址 */
    pstEntryMsg                 =   TAF_SPM_GetServiceCtrlEntryMsgAddr();
    pstMsgHeader                =   (MSG_HEADER_STRU*)pstMsg;
    ulLen                       =   pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* 消息长度超过了缓存的长度，则不保存, 防止数组越界 */
    if ( ulLen > TAF_SPM_MAX_MSG_BUFFER_LEN )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_UpdateServiceCtrlEntryMsg:Msg too big to save ");
        return ;
    }

    /* 将当前处理的入口消息拷贝到Context对应的缓冲区 */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* 填写Context中的参数 */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetServiceCtrlEntryMsgAddr
 功能描述  : 获取SPM模块中更新service ctrl入口消息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SPM模块中更新service ctrl入口消息的地址
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2013-05-8
    作    者   : W00176964
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_ENTRY_MSG_STRU* TAF_SPM_GetServiceCtrlEntryMsgAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stMainCtrlInfo.stServiceCtrlEntryMsg);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetClientIdWithAppMsg
 功能描述  : 获取AT或STK消息对应的CLIENT ID
 输入参数  : pstMsg:传入的消息
 输出参数  : pusClientId - client ID
 返 回 值  : VOS_TRUE:获取client ID成功
             VOS_FALS:获取client ID失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    *pusClientId =  pstAppMsg->clientId;

    return VOS_TRUE;
}

/* Added by f62575 for V9R1 STK升级, 2013-6-26, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_GetClientIdWithStkMsg
 功能描述  : 获取STK消息对应的CLIENT ID
 输入参数  : pstMsg:传入的消息
 输出参数  : pusClientId - client ID
 返 回 值  : VOS_TRUE:获取client ID成功
             VOS_FALS:获取client ID失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月26日
    作    者   : f62575
    修改内容   : V9R1 STK升级
  2.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithStkMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg       = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader    = VOS_NULL_PTR;
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope     = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;
    if (SI_STK_ENVELOPE_CNF == pstMsgHeader->ulMsgName)
    {
        pstEnvelope  = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
		/* 低16位为CliendId */
        *pusClientId = (VOS_UINT16)(pstEnvelope->stCmdResult.ulSendPara  & 0x0000ffff);
    }
    else
    {
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)pstMsg;

        *pusClientId =  pstAppMsg->clientId;
    }

    return VOS_TRUE;
}
/* Added by f62575 for V9R1 STK升级, 2013-6-26, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_GetOpIdWithAppMsg
 功能描述  : 获取AT或STK消息对应的OP ID
 输入参数  : pstMsg:传入的消息
 输出参数  : pucOpId - OP ID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月16日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_GetOpIdWithAppMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucOpId
)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    *pucOpId =  pstAppMsg->opId;

    return;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_GetClientIdWithVosTimerMsg
 功能描述  : 获取OSA timer消息对应的CLIENT ID
 输入参数  : pstMsg:传入的消息
 输出参数  : pusClientId - client ID
 返 回 值  : VOS_TRUE:获取client ID成功
             VOS_FALS:获取client ID失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithVosTimerMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    REL_TIMER_MSG                      *pstRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    switch (pstRcvTimerMsg->ulName)
    {
        case TI_TAF_SPM_WAIT_PB_FDN_CHECK_CNF:
        case TI_TAF_SPM_WAIT_USIM_CALL_CTRL_CNF:

            *pusClientId = (VOS_UINT16)pstRcvTimerMsg->ulPara;
            ulRet = VOS_TRUE;

            break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}


/*****************************************************************************
 函 数 名  : TAF_SPM_GetClientIdWithUsimMsg
 功能描述  : 获取USIM消息对应的CLIENT ID
 输入参数  : pstMsg:传入的消息
 输出参数  : pusClientId - client ID
 返 回 值  : VOS_TRUE:获取client ID成功
             VOS_FALS:获取client ID失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
  2.日    期   : 2015年02月06日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithUsimMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    VOS_UINT32                          ulRet;
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope = VOS_NULL_PTR;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case SI_STK_ENVELOPE_CNF:
             pstEnvelope  = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
            *pusClientId  = (VOS_UINT16)pstEnvelope->stCmdResult.ulSendPara;
             ulRet        = VOS_TRUE;
             break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetClientIdWithPbMsg
 功能描述  : 获取PB消息对应的CLIENT ID
 输入参数  : pstMsg:传入的消息
 输出参数  : pusClientId - client ID
 返 回 值  : VOS_TRUE:获取client ID成功
             VOS_FALS:获取client ID失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithPbMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    PB_FDN_CHECK_CNF_STRU              *pstCheckCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case SI_PB_EVENT_FDNCHECK_CNF:

            pstCheckCnf     = (PB_FDN_CHECK_CNF_STRU*)pstMsg;
            /* 低16位为CliendId */
           *pusClientId     = (VOS_UINT16)(pstCheckCnf->ulSendPara & 0x0000ffff);
            ulRet           = VOS_TRUE;
            break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetClientIdWithTafMsg
 功能描述  : 获取TAF消息对应的CLIENT ID
 输入参数  : pstMsg:传入的消息
 输出参数  : pusClientId - client ID
 返 回 值  : VOS_TRUE:获取client ID成功
             VOS_FALS:获取client ID失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_GetClientIdWithTafMsg(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU     *pstServiceCtrlRsltInd = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND:

             pstServiceCtrlRsltInd  = (TAF_SPM_SERVICE_CTRL_RSLT_STRU*)pstMsg;
            *pusClientId            = pstServiceCtrlRsltInd->usClientId;
             ulRet                  = VOS_TRUE;
             break;

        default:

            ulRet = VOS_FALSE;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetClientId
 功能描述  : 根据消息转出client ID
 输入参数  : pstMsg
 输出参数  : pusClientId
 返 回 值  : VOS_TRUE :获取CLIENT ID成功
             VOS_FALSE:获取client ID失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月9日
    作    者   : w00176964
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32  TAF_SPM_GetClientId(
    struct MsgCB                       *pstMsg,
    VOS_UINT16                         *pusClientId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    VOS_UINT32                          ulSndPid;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    TAF_SPM_GET_MSG_CLIENT_ID_FUNC_PTR  pCurFuncProc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    ulTblSize       = sizeof(gastSpmGetClientIdList)/sizeof(gastSpmGetClientIdList[0]);
    pstMsgHeader    = (MSG_HEADER_STRU *)pstMsg;
    ulSndPid        = pstMsgHeader->ulSenderPid;

     /* 先根据消息的发送PID映射出对应的client ID */
    for (i = 0; i < ulTblSize; i++)
    {
        if (ulSndPid == gastSpmGetClientIdList[i].ulSndPid)
        {
            pCurFuncProc = gastSpmGetClientIdList[i].pGetMsgClientIdProcFunc;
            break;
        }
    }


    if (VOS_NULL_PTR != pCurFuncProc)
    {
        ulRet = pCurFuncProc(pstMsg, pusClientId);

        return ulRet;
    }

    /* 找不到对应的处理函数 */
    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitServiceReqBufferMsgQueue
 功能描述  : 初始化缓存消息队列

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_InitServiceReqBufferMsgQueue(VOS_VOID)
{
    TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU  *pstBufferMsgQueue = VOS_NULL_PTR;

    /* get address of buffer message queue */
    pstBufferMsgQueue = TAF_SPM_GetBufferMsgQueueAddr();

    /* init buffer CC message queue */
    TAF_SPM_InitBufferCcMsgQueue(&(pstBufferMsgQueue->stCcMsgQueue));

    /* init buffer SMS message queue */
    TAF_SPM_InitBufferSmsMsgQueue(&(pstBufferMsgQueue->stSmsMsgQueue));

    /* init buffer SS message queue */
    TAF_SPM_InitBufferSsMsgQueue(&(pstBufferMsgQueue->stSsMsgQueue));
}

#if (FEATURE_IMS == FEATURE_ON)
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_InitDomainSelCtx
 功能描述  : 初始化域选择相关上下文

 输入参数  : pstDomainSelCtx -- 域选择上下文指针
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_InitDomainSelCtx(TAF_SPM_DOMAIN_SEL_CTX_STRU *pstDomainSelCtx)
{
    /* 删除IMS注册状态，移到SDC中 */

    /* 初始化IMS短信发送标志 */
    pstDomainSelCtx->ucImsSmsSendingFlg  = VOS_FALSE;

    /* 初始化上次PS服务状态 */
    pstDomainSelCtx->enLastPsStatus      = TAF_SPM_SERVICE_STATUS_NO_SERVICE;

    /* set IMS SMS supported to TRUE by server */
    TAF_SPM_SetImsSmsSupportedOnImsServer(VOS_TRUE);

    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-28, begin */
    /* 业务请求消息队列初始化移到函数TAF_SPM_InitServiceReqBufferMsgQueue中实现 */
    /* Deleted by y00245242 for V3R3C60_eCall项目, 2014-4-28, end */

    /* 初始化呼叫换域重拨缓存 */
    TAF_SPM_InitCallRedialBuffer(&(pstDomainSelCtx->stRedialMsgQueue.stCcMsgQueue));

    /* 初始化短信换域重拨缓存 */
    TAF_SPM_InitSmsRedialBuffer(&(pstDomainSelCtx->stRedialMsgQueue.stSmsMsgQueue));

    /* subscript IMS register status */
    pstDomainSelCtx->ulSubscriptId = 0;
    (VOS_VOID)IMSA_AddSubscription(WUEPS_PID_TAF, IMSA_SUBCRIBE_TYPE_NORMAL_REG, 0, &(pstDomainSelCtx->ulSubscriptId));
}
/* Modified by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, begin */
/* 删除IMS注册状态相关函数，移到SDC中 */

/*****************************************************************************
 函 数 名  : TAF_SPM_SetImsSmsSupportedOnImsServer
 功能描述  : 设置IMS服务器是否支持IMS短信
 输入参数  : IMS服务器是否支持IMS短信:VOS_TRUE:支持；VOS_FALSE:不支持
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新建函数

*****************************************************************************/
VOS_VOID TAF_SPM_SetImsSmsSupportedOnImsServer(
    VOS_UINT8                           ucImsSmsSupported
)
{
    TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSupported = ucImsSmsSupported;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetImsSmsSupportedOnImsServer
 功能描述  : 获取IMS服务器是否支持IMS短信
 输入参数  : 无
 输出参数  : 无
 返 回 值  : IMS服务器是否支持IMS短信:VOS_TRUE:支持；VOS_FALSE:不支持
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年9月22日
   作    者   : s00217060
   修改内容   : 新建函数

*****************************************************************************/
VOS_UINT8 TAF_SPM_GetImsSmsSupportedOnImsServer(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSupported);
}

/* Added by s00217060 for VoLTE_PhaseII  项目, 2013-09-22, end */

/*****************************************************************************
 函 数 名  : TAF_SPM_GetImsSmsSendingFlg
 功能描述  : 获取IMS短信正在发送标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  -- IMS短信在发送
             VOS_FALSE -- 无IMS短信在发送
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月31日
   作    者   : y00245242
   修改内容   : 新建函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetImsSmsSendingFlg(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSendingFlg);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetImsSmsSendingFlg
 功能描述  : 设置IMS短信正在发送标志
 输入参数  : ucImsSmsSendingFlg －－ IMS短信正在发送标志
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月31日
   作    者   : y00245242
   修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_SPM_SetImsSmsSendingFlg(VOS_UINT8 ucImsSmsSendingFlg)
{
    TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.ucImsSmsSendingFlg = ucImsSmsSendingFlg;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetLastPsServiceStatus
 功能描述  : 获取上次PS服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回上次PS服务状态

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月2日
   作    者   : y00245242
   修改内容   : 新建函数
*****************************************************************************/
TAF_SPM_SERVICE_STATUS_ENUM_UINT8 TAF_SPM_GetLastPsServiceStatus(VOS_VOID)
{
    return (TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.enLastPsStatus);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetImsSmsSendingFlg
 功能描述  : 设置当前的PS服务状态
 输入参数  : enCurrPsStatus －－ 当前的PS服务状态
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年1月2日
   作    者   : y00245242
   修改内容   : 新建函数
*****************************************************************************/
VOS_VOID TAF_SPM_SetLastPsServiceStatus(TAF_SPM_SERVICE_STATUS_ENUM_UINT8 enCurrPsStatus)
{
    TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.enLastPsStatus = enCurrPsStatus;
}
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
#endif /* end of FEATURE_IMS */
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */


/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-23, begin */
/*****************************************************************************
 函 数 名  : TAF_SPM_GetBufferMsgQueueAddr
 功能描述  : 获取buffer消息队列首地址


 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回buffer消息队列首地址

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_DOMAIN_SEL_MSG_QUEUE_STRU *TAF_SPM_GetBufferMsgQueueAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.stBufferMsgQueue);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitBufferCcMsgQueue
 功能描述  : 初始化CC 缓存message队列

 输入参数  :
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_InitBufferCcMsgQueue(
    TAF_SPM_MSG_CC_QUEUE_STRU          *pstCcMsgQueue
)
{
    VOS_UINT8                           i;

    pstCcMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < TAF_SPM_MAX_CC_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstCcMsgQueue->astMsgQueue[i]), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }

    PS_MEM_SET(&(pstCcMsgQueue->aucReserve[0]), 0, sizeof(VOS_UINT8)*3);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitBufferSmsMsgQueue
 功能描述  : 初始化SMS 缓存message队列

 输入参数  :
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_InitBufferSmsMsgQueue(
    TAF_SPM_MSG_SMS_QUEUE_STRU              *pstSmsMsgQueue
)
{
    VOS_UINT8                           i;

    pstSmsMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < TAF_SPM_MAX_SMS_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstSmsMsgQueue->astMsgQueue[i]), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }

    PS_MEM_SET(&(pstSmsMsgQueue->aucReserve[0]), 0, sizeof(VOS_UINT8)*3);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitBufferSmsMsgQueue
 功能描述  : 初始化SS 缓存message队列

 输入参数  :
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_InitBufferSsMsgQueue(
TAF_SPM_MSG_SS_QUEUE_STRU              *pstSsMsgQueue)
{
    VOS_UINT8                           i;

    pstSsMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < TAF_SPM_MAX_SS_MSG_QUEUE_NUM; i++)
    {
        PS_MEM_SET(&(pstSsMsgQueue->astMsgQueue[i]), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }

    PS_MEM_SET(&(pstSsMsgQueue->aucReserve[0]), 0, sizeof(VOS_UINT8)*3);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCcMsgQueueNum
 功能描述  : 获取当前队列中缓存CC消息的数目


 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回当前队列中缓存的CC消息数目

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetCcMsgQueueNum(VOS_VOID)
{
    return (TAF_SPM_GetBufferMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetCcMsgQueueNum
 功能描述  : 更新队列中缓存的CC消息数目


 输入参数  : ucCacheMsgNum -- 当前缓存的消息数目
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SetCcMsgQueueNum(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetBufferMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsCcMsgQueueFull
 功能描述  : 返回CC消息queue是否为full


 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
             VOS_TRUE -- queue full
             VOS_FALSE -- queue not full

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsCcMsgQueueFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_CC_MSG_QUEUE_NUM == TAF_SPM_GetCcMsgQueueNum())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue
 功能描述  : 从CC消息缓存队列中获取指定位置的缓存消息地址

 输入参数  : ucIndex －－ 消息索引
 输出参数  : 无
 返 回 值  : 返回CC消息缓存队列中指定位置的消息地址

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(
    VOS_UINT8                           ucIndex
)
{
    return &(TAF_SPM_GetBufferMsgQueueAddr()->stCcMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_PutMessageToCcQueue
 功能描述  : 存放消息到CC缓存消息队列中

 输入参数  : ulEventType -- 消息事件类型
             pstMsg -- 消息地址

 输出参数  : 无
 返 回 值  : 返回缓存消息结果
             VOS_TRUE  -- 消息已放到缓存队列中
             VOS_FALSE -- 存放消息失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMessageToCcQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* check the incoming message length */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* get the number of cached message */
    ucCacheMsgNum   = TAF_SPM_GetCcMsgQueueNum();

    /* get address of free message queue */
    pstCacheMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(ucCacheMsgNum);

    /* cache message */
    pstCacheMsgInfo->stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]), pstMsg, pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetCcMsgQueueNum(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : TAF_SPM_FreeSpecificedIndexMessageInCcQueue
 功能描述  : 释放queue中指定索引缓存的消息，更新缓存消息数目，附带前移队列中缓存的消息，
             方便后续操作

 输入参数  : ucIndex －－ 消息索引
 输出参数  : 无
 返 回 值  : 无


 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInCcQueue(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the specified index message address */
    pstCachedMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetCcMsgQueueNum();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetCcMsgQueueNum(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetSmsMsgQueueNum
 功能描述  : 获取当前缓存SMS消息队列的消息数目

 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回缓存SMS消息队列的消息数目

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetSmsMsgQueueNum(VOS_VOID)
{
    return (TAF_SPM_GetBufferMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetSmsMsgQueueNum
 功能描述  : 更新队列中缓存的SMS消息数目


 输入参数  : ucCacheMsgNum -- 当前缓存的消息数目
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SetSmsMsgQueueNum(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetBufferMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsSmsMsgQueueFull
 功能描述  : 返回SMS消息queue是否为full


 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
             VOS_TRUE -- queue full
             VOS_FALSE -- queue not full

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsSmsMsgQueueFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_SMS_MSG_QUEUE_NUM == TAF_SPM_GetSmsMsgQueueNum())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue
 功能描述  : 从SMS消息缓存队列中获取指定位置的缓存消息地址

 输入参数  : ucIndex －－ 消息索引
 输出参数  : 无
 返 回 值  : 返回SMS消息缓存队列中指定位置的消息地址

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(
    VOS_UINT8                           ucIndex
)
{
    return &(TAF_SPM_GetBufferMsgQueueAddr()->stSmsMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_PutMessageToSmsQueue
 功能描述  : 放消息到SMS缓存消息队列中

 输入参数  : ulEventType -- 消息事件类型
             pstMsg －－ 请求消息地址

 输出参数  : 无
 返 回 值  : 返回缓存消息结果
             VOS_TRUE  -- 消息已放到缓存队列中
             VOS_FALSE -- 存放消息失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数

  2.日    期   : 2014年2月14日
    作    者   : j00174725
    修改内容   : TQE
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMessageToSmsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* check the incoming message length */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* get the number of cached message */
    ucCacheMsgNum   = TAF_SPM_GetSmsMsgQueueNum();

    if (ucCacheMsgNum >= TAF_SPM_MAX_SMS_MSG_QUEUE_NUM)
    {
        return VOS_FALSE;
    }

    /* get address of free message queue */
    pstCacheMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(ucCacheMsgNum);

    /* cache message */
    pstCacheMsgInfo->stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]), pstMsg, pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetSmsMsgQueueNum(ucCacheMsgNum);

    return (VOS_TRUE);
}


/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : TAF_SPM_FreeSpecificedIndexMessageInSmsQueue
 功能描述  : 释放queue中指定索引的缓存消息，更新缓存消息数目，附带前移队列中缓存的消息，
             方便后续操作

 输入参数  : ucIndex －－ 消息索引
 输出参数  : 无
 返 回 值  : 无


 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the first cached message in queue */
    pstCachedMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetSmsMsgQueueNum();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetSmsMsgQueueNum(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }
}
/*lint -restore */


/*****************************************************************************
 函 数 名  : TAF_SPM_GetSsMsgQueueNum
 功能描述  : 获取当前缓存SS消息队列的消息数目


 输入参数  : 无
 输出参数  :
 返 回 值  : 返回缓存SS消息队列的消息数目

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetSsMsgQueueNum(VOS_VOID)
{
    return (TAF_SPM_GetBufferMsgQueueAddr()->stSsMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetSsMsgQueueNum
 功能描述  : 更新队列中缓存的SS消息数目


 输入参数  : ucCacheMsgNum -- 当前缓存的消息数目
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SetSsMsgQueueNum(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetBufferMsgQueueAddr()->stSsMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SsMsgQueueIsFull
 功能描述  : 返回SS消息queue是否为full


 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
             VOS_TRUE -- queue full
             VOS_FALSE -- queue not full

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月10日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsSsMsgQueueFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_SS_MSG_QUEUE_NUM == TAF_SPM_GetSsMsgQueueNum())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue
 功能描述  : 从SS消息缓存队列中获取指定位置的缓存消息地址

 输入参数  : ucIndex －－ 消息索引
 输出参数  : 无
 返 回 值  : 返回SS消息缓存队列中指定位置的消息地址

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_CACHE_MSG_INFO_STRU *TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(
    VOS_UINT8                           ucIndex
)
{
    return &(TAF_SPM_GetBufferMsgQueueAddr()->stSsMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_PutMessageToSsQueue
 功能描述  : 放消息到SS缓存消息队列中

 输入参数  : ulEventType －－ 消息事件类型
             pstMsg －－ 请求消息地址

 输出参数  : 无
 返 回 值  : 返回缓存消息结果
             VOS_TRUE  -- 消息已放到缓存队列中
             VOS_FALSE -- 存放消息失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMessageToSsQueue(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* check the incoming message length */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* get the number of cached message */
    ucCacheMsgNum   = TAF_SPM_GetSsMsgQueueNum();

    if (ucCacheMsgNum >= TAF_SPM_MAX_SS_MSG_QUEUE_NUM)
    {
        return VOS_FALSE;
    }
    /* get address of free message queue */
    pstCacheMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(ucCacheMsgNum);

    /* cache message */
    pstCacheMsgInfo->stMsgEntry.ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]), pstMsg, pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetSsMsgQueueNum(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*lint -save -e958 */
/*****************************************************************************
 函 数 名  : TAF_SPM_FreeFirstCachedMessagesInSsQueue
 功能描述  : 释放queue中指定索引的缓存消息，更新缓存消息数目，附带前移队列中缓存的消息，
             方便后续操作

 输入参数  : ucIndex －－ 消息索引
 输出参数  : 无
 返 回 值  : 无


 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexMessageInSsQueue(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the first cached message in queue */
    pstCachedMsgInfo = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetSsMsgQueueNum();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetSsMsgQueueNum(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_CACHE_MSG_INFO_STRU));
    }
}
/* Added by y00245242 for VoLTE_PhaseII 项目, 2013-9-23, end */
/*lint -restore */

/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-23, begin */
#if (FEATURE_IMS == FEATURE_ON)
/* Added by y00245242 for V3R3C60_eCall项目, 2014-4-23, end */
/*****************************************************************************
 函 数 名  : TAF_SPM_GetRedialMsgQueueAddr
 功能描述  : 获取重拨缓存消息队列首地址


 输入参数  : 无
 输出参数  : 无
 返 回 值  : 返回buffer消息队列首地址

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月15日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_REDIAL_MSG_CTX_STRU *TAF_SPM_GetRedialMsgQueueAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stDomainSelCtx.stRedialMsgQueue);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitCallRedialBuffer
 功能描述  : 初始化重拨缓存

 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_InitCallRedialBuffer(
    TAF_SPM_CC_REDIAL_QUEUE_STRU       *pstCallRedialQueue
)
{
    PS_MEM_SET(pstCallRedialQueue, 0, sizeof(TAF_SPM_CC_REDIAL_QUEUE_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetNumberOfCallRedialBuffer
 功能描述  : 获取呼叫重拨缓存数目

 输入参数  : 无

 输出参数  : 无
 返 回 值  : 返回呼叫重拨缓存中消息数目

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月25日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetNumberOfCallRedialBuffer(VOS_VOID)
{
    return (TAF_SPM_GetRedialMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsCallRedialBufferEmpty
 功能描述  : check呼叫重拨缓存是否为空

 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 重拨缓存为空
             VOS_FALSE -- 重拨缓存不为空

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsCallRedialBufferEmpty(VOS_VOID)
{
    return (VOS_UINT8)((0 == TAF_SPM_GetNumberOfCallRedialBuffer())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsCallRedialBufferFull
 功能描述  : 检查呼叫重拨缓存是否为满

 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 重拨缓存为满
             VOS_FALSE -- 重拨缓存不满

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsCallRedialBufferFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_CC_REDIAL_QUEUE_NUM == TAF_SPM_GetNumberOfCallRedialBuffer())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetNumberOfCallRedialBuffer
 功能描述  : 设置呼叫重拨缓存队列数目


 输入参数  : ucCacheMsgNum －－ 缓存消息数目
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SetNumberOfCallRedialBuffer(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetRedialMsgQueueAddr()->stCcMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetSpecificedIndexFromCallRedialBuffer
 功能描述  : 获取指定索引的呼叫重拨缓存

 输入参数  : ucIndex －－ 消息在重拨缓存中的索引号

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(VOS_UINT8 ucIndex)
{
    return &(TAF_SPM_GetRedialMsgQueueAddr()->stCcMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_PutMsgIntoCallRedialBuffer
 功能描述  : 获取指定索引的呼叫重拨缓存

 输入参数  : ulEventType －－ 消息事件类型
             pstMsg      －－ 消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMsgIntoCallRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* 检查消息长度，避免越界 */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* 获取重拨呼叫缓存数目 */
    ucCacheMsgNum   = TAF_SPM_GetNumberOfCallRedialBuffer();

    /* 获取指定重拨缓存地址 */
    pstCacheMsgInfo = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(ucCacheMsgNum);

    /* 缓存消息 */
    pstCacheMsgInfo->ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->aucEntryMsgBuffer[0]),
               pstMsg,
               pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetNumberOfCallRedialBuffer(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_FreeSpecificedIndexCallRedialBuffer
 功能描述  : 清除指定索引的呼叫重拨缓存

 输入参数  : ucIndex －－ 消息在重拨缓存中的索引号

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexCallRedialBuffer(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the specified index message address */
    pstCachedMsgInfo = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetNumberOfCallRedialBuffer();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetNumberOfCallRedialBuffer(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_ENTRY_MSG_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_ENTRY_MSG_STRU));
    }
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitSmsRedialBuffer
 功能描述  : 初始化重拨缓存

 输入参数  : 无

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_InitSmsRedialBuffer(
    TAF_SPM_SMS_REDIAL_QUEUE_STRU      *pstSmsRedialQueue
)
{
    PS_MEM_SET(pstSmsRedialQueue, 0, sizeof(TAF_SPM_SMS_REDIAL_QUEUE_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetNumberOfSmsRedialBuffer
 功能描述  : 获取呼叫重拨缓存数目

 输入参数  : 无

 输出参数  : 无
 返 回 值  : 返回呼叫重拨缓存中消息数目

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetNumberOfSmsRedialBuffer(VOS_VOID)
{
    return (TAF_SPM_GetRedialMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetNumberOfSmsRedialBuffer
 功能描述  : 设置呼叫重拨缓存队列数目


 输入参数  : ucCacheMsgNum －－ 缓存消息数目
 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月22日
    作    者   : y00245242
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_SetNumberOfSmsRedialBuffer(VOS_UINT8 ucCacheMsgNum)
{
    TAF_SPM_GetRedialMsgQueueAddr()->stSmsMsgQueue.ucCacheMsgNum = ucCacheMsgNum;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsSmsRedialBufferEmpty
 功能描述  : check呼叫重拨缓存是否为空

 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 重拨缓存为空
             VOS_FALSE -- 重拨缓存不为空

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月12日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsSmsRedialBufferEmpty(VOS_VOID)
{
    return (VOS_UINT8)((0 == TAF_SPM_GetNumberOfSmsRedialBuffer())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_IsSmsRedialBufferFull
 功能描述  : 检查呼叫重拨缓存是否为满

 输入参数  : 无

 输出参数  : 无
 返 回 值  : VOS_TRUE  -- 重拨缓存为满
             VOS_FALSE -- 重拨缓存不满

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_IsSmsRedialBufferFull(VOS_VOID)
{
    return (VOS_UINT8)((TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM == TAF_SPM_GetNumberOfSmsRedialBuffer())? VOS_TRUE : VOS_FALSE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer
 功能描述  : 获取指定索引的呼叫重拨缓存

 输入参数  : ucIndex －－ 消息在重拨缓存中的索引号

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
TAF_SPM_ENTRY_MSG_STRU *TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(VOS_UINT8 ucIndex)
{
    return &(TAF_SPM_GetRedialMsgQueueAddr()->stSmsMsgQueue.astMsgQueue[ucIndex]);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_PutMsgIntoSmsRedialBuffer
 功能描述  : 获取指定索引的呼叫重拨缓存

 输入参数  : ulEventType －－ 消息事件类型
             pstMsg      －－ 消息地址

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_SPM_PutMsgIntoSmsRedialBuffer(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheMsgInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucCacheMsgNum;

    /* 检查消息长度，避免越界 */
    if (TAF_SPM_MAX_MSG_BUFFER_LEN < (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH))
    {
        return VOS_FALSE;
    }

    /* 获取重拨呼叫缓存数目 */
    ucCacheMsgNum   = TAF_SPM_GetNumberOfSmsRedialBuffer();
    if (ucCacheMsgNum >= TAF_SPM_MAX_SMS_REDIAL_QUEUE_NUM)
    {
        return VOS_FALSE;
    }
    /* 获取指定重拨缓存地址 */
    pstCacheMsgInfo = TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(ucCacheMsgNum);

    /* 缓存消息 */
    pstCacheMsgInfo->ulEventType = ulEventType;
    PS_MEM_CPY(&(pstCacheMsgInfo->aucEntryMsgBuffer[0]),
               pstMsg,
               pstMsg->ulLength + VOS_MSG_HEAD_LENGTH);

    /* update number of cached messages */
    ucCacheMsgNum++;
    TAF_SPM_SetNumberOfSmsRedialBuffer(ucCacheMsgNum);

    return (VOS_TRUE);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_FreeSpecificedIndexSmsRedialBuffer
 功能描述  : 清除指定索引的呼叫重拨缓存

 输入参数  : ucIndex －－ 消息在重拨缓存中的索引号

 输出参数  : 无
 返 回 值  : 无

 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月13日
   作    者   : y00245242
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCacheMsgNum;
    TAF_SPM_ENTRY_MSG_STRU             *pstCachedMsgInfo = VOS_NULL_PTR;

    /* get the specified index message address */
    pstCachedMsgInfo = TAF_SPM_GetSpecificedIndexFromSmsRedialBuffer(ucIndex);

    /* get the cached message number */
    ucCacheMsgNum = TAF_SPM_GetNumberOfSmsRedialBuffer();

    if (0 < ucCacheMsgNum)
    {
        /* update the cached message number */
        ucCacheMsgNum--;
        TAF_SPM_SetNumberOfSmsRedialBuffer(ucCacheMsgNum);

        /* by the way, move the cached messages forward */
        (VOS_VOID)PS_MEM_MOVE(pstCachedMsgInfo,
                    (pstCachedMsgInfo+1),
                    (ucCacheMsgNum - ucIndex) * sizeof(TAF_SPM_ENTRY_MSG_STRU));

        PS_MEM_SET((pstCachedMsgInfo + ucCacheMsgNum), 0, sizeof(TAF_SPM_ENTRY_MSG_STRU));
    }
}

/*lint -restore */

/*****************************************************************************
 函 数 名  : TAF_SPM_GetCallEconfInfoAddr
 功能描述  : 获取增强型多方通话信息的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_SPM_CALL_ECONF_INFO_STRU  上下文中记录增强型多方通话信息的地址
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 新生成函数

*****************************************************************************/
TAF_SPM_CALL_ECONF_INFO_STRU* TAF_SPM_GetCallEconfInfoAddr(VOS_VOID)
{
    return &(TAF_SPM_GetSpmCtxAddr()->stEconfInfo);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_InitEconfInfo
 功能描述  : 初始化Call Econf 信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_SPM_InitEconfInfo(VOS_VOID)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstCallEconfAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstCallEconfAddr = TAF_SPM_GetCallEconfInfoAddr();

    PS_MEM_SET(pstCallEconfAddr, 0x0, sizeof(TAF_SPM_CALL_ECONF_INFO_STRU));

    for (ulIndex = 0; ulIndex < TAF_CALL_MAX_ECONF_CALLED_NUM; ulIndex++)
    {
        pstCallEconfAddr->astEconfCheckInfo[ulIndex].enCheckRslt    = TAF_CS_CAUSE_SUCCESS;
        pstCallEconfAddr->astEconfCheckInfo[ulIndex].ulCheckCnfFlag = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg
 功能描述  : 获取当前消息的EventType
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2014年11月28日
   作    者   : j00174725
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_SPM_GetEventTypeFromCurrEntityFsmEntryMsg(VOS_VOID)
{
    MN_APP_REQ_MSG_STRU                *pstAppMsg   = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg         = TAF_SPM_GetCurrEntityFsmEntryMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    return TAF_BuildEventType(pstAppMsg->ulSenderPid, pstAppMsg->usMsgName);
}

/*****************************************************************************
 函 数 名  : TAF_SPM_SetEcallHangUpImsFlag
 功能描述  : 设置是否下发过释放IMS call
 输入参数  : ucFlag
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月04日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID  TAF_SPM_SetEcallHangUpImsFlag(
    VOS_UINT8                           ucFlag
)
{
    TAF_SPM_GetSpmCtxAddr()->ucEcallHangUpImsFlag = ucFlag;
}

/*****************************************************************************
 函 数 名  : TAF_SPM_GetEcallHangUpImsFlag
 功能描述  : 获取是否下发过释放IMS call
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月04日
    作    者   : j00174725
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT8 TAF_SPM_GetEcallHangUpImsFlag(VOS_VOID)
{
    return TAF_SPM_GetSpmCtxAddr()->ucEcallHangUpImsFlag;
}




#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

