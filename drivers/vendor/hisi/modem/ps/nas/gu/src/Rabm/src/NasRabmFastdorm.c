/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasRabmFastdorm.c
  版 本 号   : 初稿
  作    者   : marenkun / m00217266
  生成日期   : 2014年06月16日
  最近修改   :
  功能描述   :
  函数列表   :

  修改历史   :
  1.日    期   : 2014年06月16日
    作    者   : marenkun / m00217266
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "AtRabmInterface.h"
#include "NasRabmFastdorm.h"
#include "NasRabmMain.h"
#include "rabmdef.h"
#include "NasMmlCtx.h"
#include "TafNvInterface.h"
#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_RABM_FASTDORM_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

NAS_RABM_FASTDORM_CTX_STRU              g_stNasRabmFastDormCtx;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : NAS_RABM_RcvApsFastDormStartReq
 功能描述  : 处理APS发来的TAFRABM_FASTDORM_START_REQ消息
 输入参数  : pstMsg - NASRABM_FASTDORM_START_REQ消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2011年10月18日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2011年12月20日
    作    者   : o00132663
    修改内容   : PS融合项目，启动FD定时器时，将数据计数器清零

  3.日    期   : 2012年3月20日
    作    者   : l60609
    修改内容   : B070 Project:Fastdormancy增加NV项控制

  4.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容   : 添加查询GMM状态标志入参

  5.日    期   : 2013年09月09日
    作    者   : Y00213812
    修改内容   : DTS2013090403562,修改RABM_TIMER_FASTDORM_FLUX_DETECT的定时器

  6.日    期   : 2014年06月16日
    作    者   : m00217266
    修改内容   : modify for FD Optimize
*****************************************************************************/
VOS_VOID NAS_RABM_RcvAtFastDormStartReq(
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 获取当前所处网络 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();

    /* 设置FD激活标志 */
    NAS_RABM_SET_FD_ACT_FLG(VOS_TRUE);

    /* 由于FAST DORMANCY为W下特性，如果在W网络下，且存在PDP实体激活，则需要维护FD状态 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrentSysMode)
    {
        if (NAS_RABM_FASTDORM_INIT == NAS_RABM_GET_FD_STATUS())
        {
            /* 根据PDP RAB状态切换FD状态 */
            if (VOS_TRUE == NAS_RABM_CheckPdpRbStatus())
            {
                NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
                /* FD数据计数器清零 */
                NAS_RABM_CLR_FD_ULDATA_CNT();
                NAS_RABM_CLR_FD_DLDATA_CNT();
                /* 无流量时长计数清0 */
                NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

                /* 启动周期性流量检测定时器 */
                NAS_RabmStartTimer( RABM_TIMER_NAME_FD_FLUX_DETECT, RABM_TIMER_FASTDORM_FLUX_DETECT );
            }
        }
    }

    /* 回复给AT ID_RABM_AT_FASTDORM_START_CNF */
    NAS_RABM_SndAtSetFastDormParaCnf(pstFastDormPara->usClientId,
                                     pstFastDormPara->ucOpId,
                                     AT_RABM_PARA_SET_RSLT_SUCC);

    NAS_RABM_SndOmFastdormStatus();
}


/*****************************************************************************
 函 数 名  : NAS_RABM_RcvApsFastDormStopReq
 功能描述  : 处理APS发来的TAFRABM_FASTDORM_STOP_REQ消息
 输入参数  : pstMsg        - TAFRABM_FASTDORM_STOP_REQ消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2011年10月18日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年3月20日
    作    者   : l60609
    修改内容   : B070 Project:Fastdormancy增加NV项控制

  3.日    期   : 2013年06月19日
    作    者   : Y00213812
    修改内容   : DTS2013032204300,FASTDORM retry定时器精度改为32K

  4.日    期   : 2013年09月09日
    作    者   : Y00213812
    修改内容   : DTS2013090403562,修改RABM_TIMER_FASTDORM_FLUX_DETECT的定时器

  5.日    期   : 2014年06月16日
    作    者   : m00217266
    修改内容   : modify for FD Optimize
*****************************************************************************/
VOS_VOID NAS_RABM_RcvAtFastDormStopReq(
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
    {
        /* 还原fd的工作过程中使用的各种变量和定时器 */
        NAS_RABM_RevertFastDormEnv();

        /* 设置为FD功能没有激活 */
        NAS_RABM_SET_FD_ACT_FLG(VOS_FALSE);
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);

        NAS_RABM_SndOmFastdormStatus();
    }

    /* 回复给AT ID_RABM_AT_SET_FASTDORM_PARA_CNF */
    NAS_RABM_SndAtSetFastDormParaCnf(pstFastDormPara->usClientId,
                                     pstFastDormPara->ucOpId,
                                     AT_RABM_PARA_SET_RSLT_SUCC);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ProcSetFastDormParaReq
 功能描述  : AT触发，启动或者停止FAST DORMANCY
 输入参数  : pstFastDormPara - AT的设置消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年3月20日
    作    者   : l60609
    修改内容   : B070 Project:Fastdormancy增加NV项控制

  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSetFastDormParaReq(
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    /*lint -e958 */
    NAS_RABM_NVIM_FASTDORM_ENABLE_FLG_STRU                  stEnableFlg;
    VOS_UINT32                                              ulLength;

    ulLength                 = 0;
    stEnableFlg.ucEnableFlag = VOS_FALSE;

    /* 读NV失败，认为不允许Fastdormancy */
    (VOS_VOID)NV_GetLength(en_NV_Item_Fastdorm_Enable_Flag, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_Fastdorm_Enable_Flag, &stEnableFlg,
                          ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_RcvSetFastDormParaReq:WARNING:NV_Read faild!");
    }

    /* 不允许Fastdormancy */
    if (VOS_FALSE == stEnableFlg.ucEnableFlag)
    {
        /* 回复给AT ID_RABM_AT_FASTDORM_START_CNF */
        NAS_RABM_SndAtSetFastDormParaCnf(pstFastDormPara->usClientId,
                                         pstFastDormPara->ucOpId,
                                         AT_RABM_PARA_SET_RSLT_FAIL);

        return;
    }

    /* 保存用户设置的参数 */
    NAS_RABM_SET_FD_OPERATION_TYPE(pstFastDormPara->stFastDormPara.enFastDormOperationType);
    NAS_RABM_SET_FD_USER_DEF_NOFLUX_CNT(pstFastDormPara->stFastDormPara.ulTimeLen);

    if (AT_RABM_FASTDORM_STOP_FD_ASCR == pstFastDormPara->stFastDormPara.enFastDormOperationType)
    {
        /* 调用函数，停止FAST DORMANCY */
        NAS_RABM_RcvAtFastDormStopReq(pstFastDormPara);
    }
    else
    {
        /* 调用函数 启动或者设置FAST DORMANCY */
        NAS_RABM_RcvAtFastDormStartReq(pstFastDormPara);
    }
    /*lint +e958 */
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ProcGetFastDormParaReq
 功能描述  : AT触发，获取当前FAST DORMANCY参数
 输入参数  : pstFastDormPara - AT的设置消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年3月20日
    作    者   : l60609
    修改内容   : B070 Project:Fastdormancy增加NV项控制

  3.日    期   : 2013年5月17日
    作    者   : l00167671
    修改内容   : NV项拆分项目, 将NV项数据用结构体描述
*****************************************************************************/
VOS_VOID NAS_RABM_RcvGetFastDormParaReq(
    AT_RABM_QRY_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    /*lint -e958 */
    NAS_RABM_NVIM_FASTDORM_ENABLE_FLG_STRU                  stEnableFlag;
    VOS_UINT32                                              ulLength;

    ulLength                  = 0;
    stEnableFlag.ucEnableFlag = VOS_FALSE;

    /* 读NV失败，认为不允许Fastdormancy */
    (VOS_VOID)NV_GetLength(en_NV_Item_Fastdorm_Enable_Flag, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_Fastdorm_Enable_Flag, &stEnableFlag,
                          ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_RcvGetFastDormParaReq:WARNING:NV_Read faild!");
    }

    /* 回复查询结果 */
    NAS_RABM_SndAtQryFastDormParaCnf(pstFastDormPara->usClientId,
                                     pstFastDormPara->ucOpId,
                                     stEnableFlag.ucEnableFlag);

    /*lint +e958 */
}

/*****************************************************************************
 函 数 名  : NAS_RABM_SysModeChgProcFastDorm
 功能描述  : 系统模式发生变化时，FAST DORMANCY特性的处理
 输入参数  : struct MsgCB                       *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月19日
   作    者   : h44270
   修改内容   : 新生成函数

 2.日    期   : 2013年3月22日
   作    者   : z60575
   修改内容   : DTS2013032203256,W2L切换后无法进入FD
*****************************************************************************/
VOS_VOID NAS_RABM_SysModeChgProcFastDorm(
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode,
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
)
{
    /* 系统变化，判定如果当前从W模到其他模，挂起FAST DORMANCY */
    if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enOldSysMode)
      && (NAS_MML_NET_RAT_TYPE_WCDMA != enNewSysMode)
      && (NAS_MML_NET_RAT_TYPE_BUTT != enNewSysMode))
    {
        NAS_RABM_SuspendFastDorm();
    }

    /* 系统变化，判定如果当前从其他模到W模，恢复FAST DORMANCY */
    if ( (NAS_MML_NET_RAT_TYPE_WCDMA != enOldSysMode)
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enNewSysMode) )
    {
        NAS_RABM_ResumeFastDorm();
    }

}

/*****************************************************************************
 函 数 名  : NAS_RABM_SuspendFastDorm
 功能描述  : 当前FAST DORMANCY正在运行，挂起
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月19日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2013年06月19日
   作    者   : Y00213812
   修改内容   : DTS2013032204300,FASTDORM retry定时器精度改为32K
 3.日    期   : 2013年09月09日
   作    者   : Y00213812
   修改内容   : DTS2013090403562,修改RABM_TIMER_FASTDORM_FLUX_DETECT的定时器
 4.日    期   : 2014年06月16日
   作    者   : m00217266
   修改内容   : modify for FD optimize
*****************************************************************************/
VOS_VOID NAS_RABM_SuspendFastDorm(VOS_VOID)
{
    /* 如果当前FD功能没有激活则不处理 */
    if (VOS_TRUE != NAS_RABM_GET_FD_ACT_FLG())
    {
        return;
    }

    /* 还原fd的工作过程中使用的各种变量和定时器 */
    NAS_RABM_RevertFastDormEnv();

    /* 设置为NAS_RABM_FASTDORM_INIT状态 */
    NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);
    NAS_RABM_SndOmFastdormStatus();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ResumeFastDorm
 功能描述  : 当前FAST DORMANCY正挂起，恢复
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月19日
   作    者   : h44270
   修改内容   : 新生成函数

 2.日    期   : 2011年12月20日
   作    者   : o00132663
   修改内容   : PS融合项目，增加FD数据计数器清零

 3.日    期   : 2013年09月09日
   作    者   : Y00213812
   修改内容   : DTS2013090403562,修改RABM_TIMER_FASTDORM_FLUX_DETECT的定时器

 4.日    期   : 2014年06月16日
   作    者   : m00217266
   修改内容   : modify for FD optimize
*****************************************************************************/
VOS_VOID NAS_RABM_ResumeFastDorm(VOS_VOID)
{
    /* 如果当前FD功能没有激活则不处理 */
    if (VOS_TRUE != NAS_RABM_GET_FD_ACT_FLG())
    {
        return;
    }

    NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);

    /* 根据PDP RB状态切换FD状态 */
    if (VOS_TRUE == NAS_RABM_CheckPdpRbStatus())
    {
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
        /* FD数据计数器清零 */
        NAS_RABM_CLR_FD_ULDATA_CNT();
        NAS_RABM_CLR_FD_DLDATA_CNT();

        /* 启动周期性流量检测定时器 */
        NAS_RabmStartTimer( RABM_TIMER_NAME_FD_FLUX_DETECT, RABM_TIMER_FASTDORM_FLUX_DETECT );
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_CheckPdpRbStatus
 功能描述  : 检测各PDP实体是否有RB建立
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :  VOS_TRUE - 当前存在RB建立的PDP激活
              VOS_FALSE - 当前不存在RB建立的PDP激活
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月17日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_RABM_CheckPdpRbStatus(VOS_VOID)
{
    VOS_UINT8                               ucEntId;

    for ( ucEntId = 0; ucEntId < RABM_PS_MAX_ENT_NUM; ucEntId++ )
    {
        if (g_aRabmPsEnt[ucEntId].ucState == RABM_NSAPI_ACTIVE_WITH_RAB)
        {
            break;
        }
    }

    if (ucEntId >= RABM_PS_MAX_ENT_NUM)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_CheckGmmAndRabmStatus
 功能描述  : 检测发起FD的条件是否满足
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  :  VOS_TRUE - 可以发起fast dormancy功能
              VOS_FALSE - 不可以发起fast dormancy功能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月17日
    作    者   : m00217266
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_RABM_CheckGmmAndRabmStatus(
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus
)
{
    VOS_UINT8                               ucEntId;

    /* 检查GMM的状态 若存在短信、cs域信令面或者其他特殊的gmm流程，则不能发起FD*/
    if ( (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpGmmSpecificProcedure)
      || (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpPsSmsService)
      || (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpCsSignal) )
    {
        return VOS_FALSE;
    }

    /* 检查各PDP实体状态，只要存在pdp实体在做pdp激活或rb重建，则不能发起FD */
    for ( ucEntId = 0; ucEntId < RABM_PS_MAX_ENT_NUM; ucEntId++ )
    {
        if ((g_aRabmPsEnt[ucEntId].ucState == RABM_NSAPI_ACTIVE_PENDING)
         || (NAS_RABM_GetWPsEntRabReestFlg(ucEntId) == VOS_TRUE))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType
 功能描述  : 处理来自AT的消息
 输入参数  : enAtFastDormType   - AT的操作类型
              penWrrFastDormType - WRR的操作类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月19日
   作    者   : h44270
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(
    AT_RABM_FASTDORM_OPERATION_ENUM_UINT32                enAtFastDormType,
    RRC_FASTDORM_START_TYPE_ENUM_UINT32                 *penWrrFastDormType
)
{
    switch(enAtFastDormType)
    {
        case AT_RABM_FASTDORM_START_FD_ONLY:
            *penWrrFastDormType = RRC_FASTDORM_START_TYPE_FD;
            break;

        case AT_RABM_FASTDORM_START_ASCR_ONLY:
            *penWrrFastDormType = RRC_FASTDORM_START_TYPE_ASCR;
            break;

        case AT_RABM_FASTDORM_START_FD_ASCR:
            *penWrrFastDormType = RRC_FASTDORM_START_TYPE_FD_ASCR;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                        "NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType: Wrong Type.");

            break;

    }
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ProcWasFastDormInfoInd
 功能描述  : 处理WAS的
 输入参数  : struct MsgCB                       *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2013年02月25日
    作    者   : t00212959
    修改内容   : DTS2013022202832:增加保护，在存在RAB的时候收到retry才需要状态迁移并启动定时器
  3.日    期   : 2013年06月19日
    作    者   : Y00213812
    修改内容   : DTS2013032204300,FASTDORM retry定时器精度改为32K
  4.日    期   : 2014年6月17日
    作    者   : m00217266
    修改内容   : modify for FD optimize
*****************************************************************************/
VOS_VOID NAS_RABM_RcvWasFastDormInfoInd(
    struct MsgCB                       *pMsg
)
{
    RRRABM_FASTDORM_INFO_IND_STRU      *pstInfoInd;

    pstInfoInd = (RRRABM_FASTDORM_INFO_IND_STRU*)pMsg;

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        if (RRRABM_FASTDORM_INFO_NEED_RETRY == pstInfoInd->enInfoType)
        {
            /* 启动RABM_TIMER_FASTDORM_RETRY定时器 */
            NAS_RabmStartTimer( RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY );
            NAS_RABM_SndOmFastdormStatus();
        }
        else
        {
            /* 设置FD在NAS_RABM_FASTDORM_INIT状态 */;
            NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);
            NAS_RABM_SndOmFastdormStatus();
        }

        return;
    }

    /* 存在FD切换到INIT状态后，wrr又回复retry消息 */
    if ((NAS_RABM_FASTDORM_INIT == NAS_RABM_GET_FD_STATUS())
     && (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
     && (RRRABM_FASTDORM_INFO_NEED_RETRY == pstInfoInd->enInfoType))
    {
        /* 设置FD在NAS_RABM_FASTDORM_EXEC状态 */;
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_EXEC);
        NAS_RABM_SndOmFastdormStatus();

        /* 启动RABM_TIMER_FASTDORM_RETRY定时器 */
        NAS_RabmStartTimer( RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY );
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ProcFastDormStatusInUlTransfer
 功能描述  : 数据传输过程中，FD状态处理
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月18日
    作    者   : m00217266
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_RABM_ProcFastDormStatusInTransfer( VOS_VOID )
{
    if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
    {
        if (NAS_RABM_FASTDORM_DETECT != NAS_RABM_GET_FD_STATUS())
        {
            /* 还原fd的工作过程中使用的各种变量和定时器 */
            NAS_RABM_RevertFastDormEnv();

            /* 设置为NAS_RABM_FASTDORM_DETECT状态 */
            NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
            NAS_RabmStartTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);

            NAS_RABM_SndOmFastdormStatus();
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_RevertFastDormEnv
 功能描述  : 还原Fastdormancy的工作环境，主要是还原流量统计数据，无流量时长
             ，和相关定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月19日
    作    者   : m00217266
    修改内容   : 新生成函数

  2.日    期   : 2015年1月9日
    作    者   : A00165503
    修改内容   : DTS2014123000271: RRC释放流程增加停止控制
*****************************************************************************/
VOS_VOID NAS_RABM_RevertFastDormEnv(VOS_VOID)
{
    /* 向WAS发送RRRABM_FASTDORM_STOP_REQ */
    NAS_RABM_SndWasFastDormStopReq();

    /* 停止定时器RABM_TIMER_FASTDORM_FLUX_DETECT */
    /* 停止定时器RABM_TIMER_FASTDORM_RETRY */
    /* 停止定时器RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT*/
    NAS_RabmStopTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);
    NAS_RabmStopTimer(RABM_TIMER_NAME_FD_RETRY,RABM_TIMER_FASTDORM_RETRY);
    NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON,RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT);

    /* 清空上下行流量数据 */
    NAS_RABM_CLR_FD_ULDATA_CNT();
    NAS_RABM_CLR_FD_DLDATA_CNT();

    /* 无流量时长计数清0 */
    NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

    /* 清除释放RRC标识 */
    NAS_RABM_CLR_FD_REL_RRC_EXEC_FLG();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_AbortRelRrcProcedure
 功能描述  : 终止释放RRC流程
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年1月9日
    作    者   : A00165503
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_RABM_AbortRelRrcProcedure(VOS_VOID)
{
    /* FD功能开启时, 以FD的处理流程为准 */
    if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
    {
        return;
    }

    if (VOS_TRUE == NAS_RABM_GET_FD_REL_RRC_EXEC_FLG())
    {
        NAS_RABM_CLR_FD_REL_RRC_EXEC_FLG();
        NAS_RABM_SndWasFastDormStopReq();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_RcvReleaseRrcReq
 功能描述  : rabm处理快速拆除rrc连接at命令
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容   : Optimize RIL:
*****************************************************************************/
VOS_VOID NAS_RABM_RcvReleaseRrcReq(
    AT_RABM_RELEASE_RRC_REQ_STRU *pstMsg
)
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* 获取当前所处网络 */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();

    /* 如果不在W网络下，则不能释放RRC连接 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != enCurrentSysMode)
    {
        NAS_RABM_SndAtReleaseRrcCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR);
    }
    else
    {
        /* 直接回复rrc释放成功 */
        NAS_RABM_SndAtReleaseRrcCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_OK);

        /* 向GMM发送查询消息 */
        NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_RELEASE_RRC_ENUM);

    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_InitFastDormCtx
 功能描述  : 初始化FAST DORMANCY的上下文
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期   : 2011年10月18日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2011年12月20日
    作    者   : o00132663
    修改内容   : PS融合项目，增加新计数器变量初始化

  3.日    期   : 2015年1月9日
    作    者   : A00165503
    修改内容   : DTS2014123000271: RRC释放流程增加停止控制
*****************************************************************************/
VOS_VOID NAS_RABM_InitFastDormCtx(VOS_VOID)
{
    g_stNasRabmFastDormCtx.enCurrFastDormStatus    = NAS_RABM_FASTDORM_INIT;
    g_stNasRabmFastDormCtx.ulCurrNoFluxCnt         = 0;
    g_stNasRabmFastDormCtx.enFastDormOperationType = AT_RABM_FASTDORM_STOP_FD_ASCR;
    g_stNasRabmFastDormCtx.ulUserDefNoFluxCnt      = 0;

    g_stNasRabmFastDormCtx.ulDlDataCnt             = 0;
    g_stNasRabmFastDormCtx.ulUlDataCnt             = 0;

    g_stNasRabmFastDormCtx.ulRelRrcExecFlg         = VOS_FALSE;

    g_stNasRabmFastDormCtx.ulActiveFlg             = VOS_FALSE; /* 默认FD功能没有激活 */

    g_ulNasRabmFDFluxDetectTimer                   = NAS_RABM_TIMER_STATUS_STOP;
    g_ulNasRabmFDRetryTimer                        = NAS_RABM_TIMER_STATUS_STOP;
    g_ulNasRabmFDWaitGmmQryRsltTimer               = NAS_RABM_TIMER_STATUS_STOP;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_FastDormFluxDetectExpired
 功能描述  : 收到周期流量检测定时器RABM_TIMER_FASTDORM_FLUX_DETECT消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月18日
   作    者   : h44270
   修改内容   : 新生成函数

 2.日    期   : 2011年12月20日
   作    者   : o00132663
   修改内容   : PS融合项目，流量获取方式改为判断数据计数器值
 3.日    期   : 2013年1月30日
   作    者   : z60575
   修改内容   : DTS2013013004885修改，没有RAB时不做FD流程
 4.日    期   : 2013年06月19日
   作    者   : Y00213812
   修改内容   : DTS2013030104863,FASTDORM retry定时器精度改为32K
 5.日    期   : 2013年7月11日
   作    者   : M00217266
   修改内容   : 添加查询GMM状态入参
 6.日    期   : 2014年06月16日
   作    者   : m00217266
   修改内容   : modify for FD Optimize
*****************************************************************************/
VOS_VOID NAS_RABM_FastDormFluxDetectExpired(VOS_VOID)
{
    VOS_UINT32                              ulUserDefNoFluxCnt;
    VOS_UINT32                              ulCurrNoFluxCnt;
    VOS_UINT32                              ulUlDataCnt;
    VOS_UINT32                              ulDlDataCnt;

    if (NAS_RABM_FASTDORM_DETECT == NAS_RABM_GET_FD_STATUS())
    {
        ulUlDataCnt = NAS_RABM_GET_FD_ULDATA_CNT();
        ulDlDataCnt = NAS_RABM_GET_FD_DLDATA_CNT();

        /* 存在数据传输时清空无流量时长，继续等待流量统计定时器超时 */
        if ((ulUlDataCnt > 0) || (ulDlDataCnt > 0))
        {
            /*流量计数清零*/
            NAS_RABM_CLR_FD_ULDATA_CNT();
            NAS_RABM_CLR_FD_DLDATA_CNT();
            /* 无流量时长计数值清0 */
            NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

            return;
        }

        ulUserDefNoFluxCnt = NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT();
        ulCurrNoFluxCnt    = NAS_RABM_GET_FD_CURR_NOFLUX_CNT();

        ulCurrNoFluxCnt += 1;

        /* 无流量时长达到用户设置的无流量时长，切换FD状态为NAS_RABM_FASTDORM_EXEC，停止流量统计定时器 */
        if (ulCurrNoFluxCnt >= ulUserDefNoFluxCnt)
        {
            NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_EXEC);
            NAS_RabmStopTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);

            NAS_RABM_CLR_FD_ULDATA_CNT();
            NAS_RABM_CLR_FD_DLDATA_CNT();

            NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

            /* 向GMM发送查询消息 */
            NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_FASTDORM_ENUM);

            /* 启动定时器TI_NAS_RABM_FASTDORM_WAIT_GMM_QRY_RESULT */
            NAS_RabmStartTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT );
            NAS_RABM_SndOmFastdormStatus();

            return;
        }

        /* 存储当前的无流量计数值 */
        NAS_RABM_SET_FD_CURR_NOFLUX_CNT(ulCurrNoFluxCnt);
    }

    return;

}

/*****************************************************************************
 函 数 名  : NAS_RABM_FastDormRetryExpired
 功能描述  : 收到周期流量检测定时器RABM_TIMER_FASTDORM_FLUX_DETECT消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月18日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2013年1月6日
   作    者   : t00212959
   修改内容   : DTS2013010505101
 3.日    期   : 2013年7月11日
   作    者   : M00217266
   修改内容   : 增加GMM状态查询入参
 4.日    期   : 2014年06月16日
   作    者   : m00217266
   修改内容   : modify for FD Optimize
*****************************************************************************/
VOS_VOID NAS_RABM_FastDormRetryExpired(VOS_VOID)
{
    /* 把retry定时器的状态设置为stop */
    g_ulNasRabmFDRetryTimer = NAS_RABM_TIMER_STATUS_STOP;

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        /* 向GMM发送查询消息 */
        NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_FASTDORM_ENUM);
        /* 启动定时器RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT */
        NAS_RabmStartTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT );

        NAS_RABM_SndOmFastdormStatus();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_FastDormWaitGmmProcQryRsltExpired
 功能描述  : 收到周期流量检测定时器RABM_TIMER_FASTDORM_FLUX_DETECT消息的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月18日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2013年09月09日
   作    者   : Y00213812
   修改内容   : DTS2013090403562,修改RABM_TIMER_FASTDORM_FLUX_DETECT的定时器
 3.日    期   : 2014年06月16日
   作    者   : m00217266
   修改内容   : modify for FD Optimize
*****************************************************************************/
VOS_VOID NAS_RABM_FastDormWaitGmmProcQryRsltExpired(VOS_VOID)
{
    /* 把定时器状态置为stop */
    g_ulNasRabmFDWaitGmmQryRsltTimer = NAS_RABM_TIMER_STATUS_STOP;

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        /* 设置FD功能没有激活 */
        NAS_RABM_RevertFastDormEnv();
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);

        NAS_RABM_SndOmFastdormStatus();
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_RcvGmmFastDormMmlProcStatusQryCnf
 功能描述  : 处理GMM发来的ID_GMM_RABM_MML_PROC_STATUS_QRY_CNF消息
 输入参数  : pstMsg  - ID_GMM_RABM_MML_PROC_STATUS_QRY_CNF消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年10月18日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2013年06月18日
   作    者   : Y00213812
   修改内容   : DTS2013030104863，FASTDORM retry定时器精度改为32K
 3.日    期   : 2014年06月16日
   作    者   : m00217266
   修改内容   : modify for FD Optimize
*****************************************************************************/
VOS_VOID NAS_RABM_RcvGmmFastDormMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT );

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        /*if (当前可以给WAS发送FAST DORM)*/
        if (VOS_TRUE == NAS_RABM_CheckGmmAndRabmStatus(pstProcStatus))
        {
            /* 向WAS发送RRRABM_FASTDORM_START_REQ */
            NAS_RABM_SndWasFastDormStartReq(RABM_FASTDORM_ENUM);
        }
        else
        {
            /* 启动定时器RABM_TIMER_FASTDORM_RETRY */
            NAS_RabmStartTimer( RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY );
        }
    }

    NAS_RABM_SndOmFastdormStatus();
    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_RcvGmmMmlProcStatusQryCnf
 功能描述  : 快速拆除rrc连接
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容   : Optimize RIL:

*****************************************************************************/
VOS_VOID NAS_RABM_RcvGmmMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    if (RABM_RELEASE_RRC_ENUM == pstProcStatus->stMmlProcStatus.enOptFlag)
    {
        NAS_RABM_RcvGmmReleaseRrcMmlProcStatusQryCnf(pstMsg);
    }

    if (RABM_FASTDORM_ENUM == pstProcStatus->stMmlProcStatus.enOptFlag)
    {
        NAS_RABM_RcvGmmFastDormMmlProcStatusQryCnf(pstMsg);
    }

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    if (RABM_VOICEPREFER_ENUM == pstProcStatus->stMmlProcStatus.enOptFlag)
    {
        NAS_RABM_RcvGmmVoicePreferMmlProcStatusQryCnf(pstMsg);
    }
#endif

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_RcvGmmMmlProcStatusQryCnf
 功能描述  : 快速拆除rrc连接
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容   : Optimize RIL

  2.日    期   : 2015年1月9日
    作    者   : A00165503
    修改内容   : DTS2014123000271: RRC释放流程增加停止控制
*****************************************************************************/
VOS_VOID NAS_RABM_RcvGmmReleaseRrcMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    if (VOS_TRUE == NAS_RABM_CheckGmmAndRabmStatus(pstProcStatus))
    {
        /* 设置释放RRC标识 */
        NAS_RABM_SET_FD_REL_RRC_EXEC_FLG();

        /* 向WAS发送RRRABM_FASTDORM_START_REQ */
        NAS_RABM_SndWasFastDormStartReq(RABM_RELEASE_RRC_ENUM);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_SndWasFastDormStartReq
 功能描述  : 向WAS发送RRRABM_FASTDORM_START_REQ
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年7月14日
    作    者   : W00176964
    修改内容   : V7R1 C50 GUTL PhaseI调整:发送给WRR的消息统一用适配层函数替换
  3.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  4.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容   : 添加release rrc和fastdorm命令判断
*****************************************************************************/
VOS_VOID NAS_RABM_SndWasFastDormStartReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32     enOptFlag
)
{
    VOS_UINT32                              ulRet;                              /* 定义调用VOS发送函数的返回值 */
    RRRABM_FASTDORM_START_REQ_STRU         *pstMsg = VOS_NULL_PTR;              /* 定义原语类型指针 */
    RRC_FASTDORM_START_TYPE_ENUM_UINT32     enWrrFastDormStartType;


    enWrrFastDormStartType = RRC_FASTDORM_START_TYPE_BUTT;


    /* 申请内存  */
    pstMsg = (RRRABM_FASTDORM_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RRRABM_FASTDORM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStartReq:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulLength          = sizeof(RRRABM_FASTDORM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRRABM_FASTDORM_START_REQ;

    /* 将AT的操作类型转换成Wrr对应的操作类型 */
    if (RABM_FASTDORM_ENUM == enOptFlag)
    {
        NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(NAS_RABM_GET_FD_OPERATION_TYPE(),
                                                        &enWrrFastDormStartType);
    }
    else
    {
        /* release rrc 命令同时开启FD和ASCR */
        NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(AT_RABM_FASTDORM_START_FD_ASCR,
                                                        &enWrrFastDormStartType);
    }

    pstMsg->enStartType                 = enWrrFastDormStartType;

    /* 调用VOS发送原语 */
     ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStartReq:ERROR:PS_SEND_MSG ");
        return ;
    }

}


/*****************************************************************************
 函 数 名  : NAS_RABM_SndWasFastDormStopReq
 功能描述  : 向WAS发送RRRABM_FASTDORM_STOP_REQ
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2012年7月14日
    作    者   : W00176964
    修改内容   : V7R1 C50 GUTL PhaseI调整:发送给WRR的消息统一用适配层函数替换
*****************************************************************************/
VOS_VOID NAS_RABM_SndWasFastDormStopReq(VOS_VOID)
{
    VOS_UINT32                          ulRet;                                  /* 定义调用VOS发送函数的返回值 */
    RRRABM_FASTDORM_STOP_REQ_STRU     *pstMsg = VOS_NULL_PTR;                  /* 定义原语类型指针 */

    /* 申请内存  */
    pstMsg = (RRRABM_FASTDORM_STOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RRRABM_FASTDORM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStopReq:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulLength          = sizeof(RRRABM_FASTDORM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRRABM_FASTDORM_STOP_REQ;

    /* 调用VOS发送原语 */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pstMsg);

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStopReq:ERROR:PS_SEND_MSG ");
        return ;
    }

}


/*****************************************************************************
 函 数 名  : NAS_RABM_SndGmmMmlProcStatusQryReq
 功能描述  : 向WAS发送ID_RABM_GMM_MML_RPOC_STATUS_QRY_REQ
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : h44270
    修改内容   : 新生成函数
  2.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容   : 增加入参enOptFlag，区分RELEASERRC和FASTDORM操作
*****************************************************************************/
VOS_VOID NAS_RABM_SndGmmMmlProcStatusQryReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32     enOptFlag
)
{
    VOS_UINT32                                  ulRet;                                  /* 定义调用VOS发送函数的返回值 */
    RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU      *pstMsg = VOS_NULL_PTR;                  /* 定义原语类型指针 */

    /* 申请内存  */
    pstMsg = (RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndGmmMmlProcStatusQryReq:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ;

    pstMsg->enOptFlag                     = enOptFlag;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndGmmMmlProcStatusQryReq:ERROR:PS_SEND_MSG ");
        return ;
    }

}

/*lint -e958 */
/*****************************************************************************
 函 数 名  : NAS_RABM_SndAtSetFastDormParaCnf
 功能描述  : 向WAS发送ID_RABM_AT_SET_FASTDORM_PARA_CNF
 输入参数  : MN_CLIENT_ID_T                      usClientId
             MN_OPERATION_ID_T                   ucOpId
             AT_RABM_PARA_SET_RSLT_ENUM_UINT32   enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年3月20日
    作    者   : l60609
    修改内容   : B070 Project:Fastdormancy增加NV项控制
*****************************************************************************/
VOS_VOID NAS_RABM_SndAtSetFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,                             /* AT发消息给RABM所带的ClientId */
    MN_OPERATION_ID_T                   ucOpId,                                 /* AT发消息给RABM所带的OpId */
    AT_RABM_PARA_SET_RSLT_ENUM_UINT32   enRslt
)
{
    /* 向AT发送设置结果 */
    VOS_UINT32                          ulRet;                                  /* 定义调用VOS发送函数的返回值 */
    RABM_AT_SET_FASTDORM_PARA_CNF_STRU *pstMsg = VOS_NULL_PTR;                  /* 定义原语类型指针 */

    /* 申请内存  */
    pstMsg = (RABM_AT_SET_FASTDORM_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_AT_SET_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtSetFastDormParaCnf:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_SET_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_SET_FASTDORM_PARA_CNF;
    pstMsg->enRslt                        = enRslt;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = ucOpId;

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtSetFastDormParaCnf:ERROR:PS_SEND_MSG ");
        return ;
    }

    return ;
}
/*lint +e958 */

/*****************************************************************************
 函 数 名  : NAS_RABM_SndAtQryFastDormParaCnf
 功能描述  : 向AT发送ID_RABM_AT_QRY_FASTDORM_PARA_CNF
 输入参数  : MN_CLIENT_ID_T                      usClientId
             MN_OPERATION_ID_T                   ucOpId
             VOS_UINT8                           ucRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年10月19日
    作    者   : h44270
    修改内容   : 新生成函数

  2.日    期   : 2012年3月20日
    作    者   : l60609
    修改内容   : B070 Project:Fastdormancy增加NV项控制
*****************************************************************************/
VOS_VOID NAS_RABM_SndAtQryFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucRslt
)
{
    /* 向AT发送查询结果 */
    VOS_UINT32                          ulRet;                                  /* 定义调用VOS发送函数的返回值 */
    RABM_AT_QRY_FASTDORM_PARA_CNF_STRU *pstMsg = VOS_NULL_PTR;                  /* 定义原语类型指针 */

    /* 申请内存  */
    pstMsg = (RABM_AT_QRY_FASTDORM_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_AT_QRY_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* 内存申请失败 */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtQryFastDormParaCnf:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* 填写相关参数 */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_QRY_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_QRY_FASTDORM_PARA_CNF;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = ucOpId;
    pstMsg->ucRslt                        = ucRslt;

    pstMsg->stFastDormPara.enFastDormOperationType = NAS_RABM_GET_FD_OPERATION_TYPE();
    pstMsg->stFastDormPara.ulTimeLen               = NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT();

    /* 调用VOS发送原语 */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtQryFastDormParaCnf:ERROR:PS_SEND_MSG ");
        return ;
    }

    return ;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_SndOmFastdormStatus
 功能描述  : 发送消息给OM模块，当前RABM中FAST DORMANCY的运行状况
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年10月31日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2014年06月16日
   作    者   : m00217266
   修改内容   : modify for FD optimize
*****************************************************************************/
VOS_VOID  NAS_RABM_SndOmFastdormStatus(VOS_VOID)
{
    NAS_RABM_LOG_FASTDORM_INFO_STRU    *pstMsg;

    pstMsg = (NAS_RABM_LOG_FASTDORM_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_RABM,
                             sizeof(NAS_RABM_LOG_FASTDORM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_RABM_SndOmFastdormStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid               = WUEPS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverPid             = WUEPS_PID_RABM;

    pstMsg->stMsgHeader.ulLength                  = sizeof(NAS_RABM_LOG_FASTDORM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName                 = NAS_RABM_OM_MSG_FASTDORM_STATUS;
    pstMsg->stFastDormCtx.enCurrFastDormStatus    = NAS_RABM_GET_FD_STATUS();
    pstMsg->stFastDormCtx.enFastDormOperationType = NAS_RABM_GET_FD_OPERATION_TYPE();
    pstMsg->stFastDormCtx.ulUserDefNoFluxCnt      = NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT();
    pstMsg->stFastDormCtx.ulCurrNoFluxCnt         = NAS_RABM_GET_FD_CURR_NOFLUX_CNT();

    pstMsg->stFastDormCtx.ulActiveFlg             = NAS_RABM_GET_FD_ACT_FLG();
    pstMsg->stFastDormCtx.ulDlDataCnt             = NAS_RABM_GET_FD_DLDATA_CNT();
    pstMsg->stFastDormCtx.ulUlDataCnt             = NAS_RABM_GET_FD_ULDATA_CNT();

    pstMsg->aenTimerState[0]                      = NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);
    pstMsg->aenTimerState[1]                      = NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT);
    pstMsg->aenTimerState[2]                      = NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_FD_RETRY,RABM_TIMER_FASTDORM_RETRY);
    pstMsg->ucReserved                            = 0;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_RABM, pstMsg);

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

