/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasRabmmMsgProc.c
  版 本 号   : 初稿
  作    者   : anhuiqing / 00165503
  生成日期   : 2011年03月30日
  最近修改   :
  功能描述   :
  函数列表   :

  修改历史   :
  1.日    期   : 2011年03月30日
    作    者   : anhuiqing / 00165503
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"
#include "rabminclude.h"
#include "NasRabmMain.h"
#include "NasRabmMsgProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_RABM_MSG_PROC_C



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* WCDMA系统模式的函数处理表 */
NAS_RABM_PROC_FUNC_TBL_STRU             g_stNasRabmWProcFuncTbl;

/* GPRS系统模式的函数处理表 */
NAS_RABM_PROC_FUNC_TBL_STRU             g_stNasRabmGProcFuncTbl;

#if (FEATURE_ON == FEATURE_LTE)
/* LTE系统模式的函数处理表 */
NAS_RABM_PROC_FUNC_TBL_STRU             g_stNasRabmLProcFuncTbl;
#endif

/* 数据业务挂起标志 */
VOS_BOOL                                g_bNasRabmDataSuspendFlg;

/* 系统模式改变处理函数表 */
NAS_RABM_SYS_CHG_TBL_STRU               g_astRabmSysModeChgTbl[] =
{
    {NAS_MML_NET_RAT_TYPE_GSM   ,   NAS_MML_NET_RAT_TYPE_GSM    ,   VOS_NULL_PTR                        },
    {NAS_MML_NET_RAT_TYPE_GSM   ,   NAS_MML_NET_RAT_TYPE_WCDMA  ,   NAS_RABM_GProcSysModeChangeToWcdma  },
#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MML_NET_RAT_TYPE_GSM   ,   NAS_MML_NET_RAT_TYPE_LTE    ,   NAS_RABM_GProcSysModeChangeToLte    },
#endif
    {NAS_MML_NET_RAT_TYPE_WCDMA ,   NAS_MML_NET_RAT_TYPE_GSM    ,   NAS_RABM_WProcSysModeChangeToGprs   },
    {NAS_MML_NET_RAT_TYPE_WCDMA ,   NAS_MML_NET_RAT_TYPE_WCDMA  ,   VOS_NULL_PTR                        },
#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MML_NET_RAT_TYPE_WCDMA ,   NAS_MML_NET_RAT_TYPE_LTE    ,   NAS_RABM_WProcSysModeChangeToLte    },
    {NAS_MML_NET_RAT_TYPE_LTE   ,   NAS_MML_NET_RAT_TYPE_GSM    ,   NAS_RABM_LProcSysModeChangeToGprs   },
    {NAS_MML_NET_RAT_TYPE_LTE   ,   NAS_MML_NET_RAT_TYPE_WCDMA  ,   NAS_RABM_LProcSysModeChangeToWcdma  },
    {NAS_MML_NET_RAT_TYPE_LTE   ,   NAS_MML_NET_RAT_TYPE_LTE    ,   VOS_NULL_PTR                        }
#endif
};


/*****************************************************************************
  3 函数、变量声明
*****************************************************************************/


/*****************************************************************************
  4 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : NAS_RABM_ProcSysModeChgInd
 功能描述  : WCDMA系统模式处理系统模式改变指示
 输入参数  : enOldSysMode   - RABM旧的系统模式
             enNewSysMode   - RABM新的系统模式
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_ProcSysModeChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode,
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
)
{
    NAS_RABM_SYS_MODE_CHG_PROC_FUNC     pSysModeChgProcFunc;
    VOS_UINT32                          ulIndex;

    NAS_NORMAL_LOG2(WUEPS_PID_RABM,
        "NAS_RABM_ProcSysModeChgInd: OldMode, NewMode:",
        enOldSysMode, enNewSysMode);

    /* 初始化系统模式处理函数指针 */
    pSysModeChgProcFunc = VOS_NULL_PTR;

    /* 根据旧系统模式和新系统模式查找处理函数 */
    for (ulIndex = 0; ulIndex < NAS_RABM_GetSysModeChgTblSize(); ulIndex++)
    {
        if ( (enOldSysMode == NAS_RABM_GetSysModeChgTblOldMode(ulIndex))
          && (enNewSysMode == NAS_RABM_GetSysModeChgTblNewMode(ulIndex)) )
        {
            pSysModeChgProcFunc = NAS_RABM_GetSysModeChgTblProcFunc(ulIndex);
            break;
        }
    }

    if (VOS_NULL_PTR != pSysModeChgProcFunc)
    {
        pSysModeChgProcFunc();
    }
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
            "NAS_RABM_ProcSysModeChgInd: pSysModeChgProcFunc is NULL.");
    }

}

/*****************************************************************************
 函 数 名  : NAS_RABM_WProcSysModeChgToGprs
 功能描述  : 处理W模切换至G模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月24日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年6月01日
    作    者   : y00213812
    修改内容   : 解决问题单DTS2012052903196，清除W实体的信息

*****************************************************************************/
VOS_VOID NAS_RABM_WProcSysModeChangeToGprs(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_WProcSysModeChangeToGprs: Build GPRS state machine.");

    /* 清除RAB重建标志:　停止RAB重建定时器, 清除实体的RAB重建标志 */
    NAS_RABM_ClearRabReestFlg();

    /* RABM实体状态转换处理 */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetWPsEntState(ucEntId))
        {
            case RABM_NULL:
                /* G实体状态置为RABM_2G_NULL */
                RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_2G_NULL);

                /* 清除W实体信息 */
                NAS_RABM_ClearRabmWPsEnt(ucEntId);
                break;

            case RABM_NSAPI_ACTIVE_WITH_RAB:
            case RABM_NSAPI_ACTIVE_NO_RAB:
            case RABM_DATA_TRANSFER_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: State change to RABM_DATA_TRANS_STOP. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* G实体状态置为RABM_DATA_TRANS_STOP */
                RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_DATA_TRANS_STOP);
                NAS_RABM_UpdateGPsEntFromWPsEnt(ucEntId);

                /* W实体状态置为RABM_NULL */
                RABM_SetWState(ucEntId, RABM_NULL);

                /* 清除W实体信息 */
                NAS_RABM_ClearRabmWPsEnt(ucEntId);
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: This NSAPI's state is WRONG! NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_RABM_WProcSysModeChgToLte
 功能描述  : 处理W模切换至L模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月24日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2012年6月01日
    作    者   : y00213812
    修改内容   : 解决问题单DTS2012052903196，清除W实体的RAB信息

*****************************************************************************/
VOS_VOID NAS_RABM_WProcSysModeChangeToLte(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_WProcSysModeChangeToLte: Proc system mode change W->L.");

    /* 清除RAB重建标志: 关闭RAB重建定时器, 清除实体的RAB重建标志 */
    NAS_RABM_ClearRabReestFlg();

    /* RABM实体状态转换处理 */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetWPsEntState(ucEntId))
        {
            case RABM_NULL:
                break;

            case RABM_NSAPI_ACTIVE_PENDING:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: State change to RABM_DATA_TRANS_STOP. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* W实体状态置为RABM_NULL */
                RABM_SetWState(ucEntId, RABM_NULL);

                /* 清除W实体RAB信息 */
                NAS_RABM_ClearRabmWPsEnt(ucEntId);
                break;

            case RABM_NSAPI_ACTIVE_WITH_RAB:
            case RABM_NSAPI_ACTIVE_NO_RAB:
            case RABM_DATA_TRANSFER_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: State change to RABM_DATA_TRANS_STOP. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* W实体状态置为RABM_DATA_TRANSFER_STOP */
                RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);

                /* 清除W模的RAB信息 */
                NAS_RABM_ClearRabInfo(ucEntId);
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: This NSAPI's state is WRONG! NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }
}
#endif

/*****************************************************************************
 函 数 名  : NAS_RABM_WProcDataSuspendInd
 功能描述  : WCDMA系统模式下处理挂起指示
 输入参数  : bRatChangeFlg  - 异系统切换标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_WProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
)
{
    if (VOS_TRUE == bRatChangeFlg)
    {
        /* 向PDCP发送RABM_PDCP_SAVE_DATA_IND_STRU消息 */
        if (VOS_OK == NAS_RabmSndPdcpSaveDataInd())
        {
            /* 保存NSAPI和RB的对应关系 */
            NAS_RabmSaveNsapiMapRbInfo();
        }
    }

    /* 检查挂起标志是否已设置为TRUE */
    if (VOS_TRUE == NAS_RABM_GetDataSuspendFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
            "NAS_RABM_WProcDataSuspendInd: DataSupendFlg is TRUE, do nothing.");
        return;
    }

    /* 设置挂起标志为TRUE */
    NAS_RABM_SetDataSuspendFlg();

    /* 继承原有W2G处理流程 */
    NAS_RabmDeal3GTo2GSuspendIndMsg();

}

/*****************************************************************************
 函 数 名  : NAS_RABM_WProcDataResumeInd
 功能描述  : WCDMA系统模式下处理恢复指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建

  3.日    期   : 2011年12月19日
    作    者   : o00132663
    修改内容   : PS融合项目，挂起恢复后，通知CDS

  4.日    期   : 2012年1月3日
    作    者   : A00165503
    修改内容   : PS Projec: 删除上报APS系统模式切换指示消息

  5.日    期   : 2012年3月5日
    作    者   : A00165503
    修改内容   : DTS2012022302899, 网络侧信号衰减直至丢网, PC继续向网络进行
                 灌包, 单板必然出现复位

  6.日    期   : 2012年3月29日
    作    者   : f00179208
    修改内容   : DTS2012032804992: G2W重选，概率性出现1分钟才恢复PING包

  7.日    期   : 2012年5月6日
    作    者   : A00165503
    修改内容   : DTS2012050600216: 网侧释放RRC连接后, 数传无法恢复

  8.日    期   : 2013年04月12日
    作    者   : l65478
    修改内容   : DTS2013031901654:彩信并发发送失败
*****************************************************************************/
VOS_VOID NAS_RABM_WProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;
    VOS_UINT8                           ucEntId;

    /* 检查挂起标志是否已设置为FALSE */
    if (VOS_FALSE == NAS_RABM_GetDataSuspendFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
            "NAS_RABM_WProcDataResumeInd: DataSupendFlg is FALSE, do nothing.");
        return;
    }

    /*-----------------------------------------------------
       用户指定搜网和^SYSCFG命令导致系统模式切换, 不会有
       挂起流程, 恢复流程处理不需要检查挂起标志
    -----------------------------------------------------*/
    NAS_RABM_ClearDataSuspendFlg();

    /* 释放在3G向2G切换开始时PDCP缓存的数据 */
    SN_RabmClear3G2Share();

    /* 处理处于挂起状态的实体 */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);

        switch (pstWPsEnt->ucState)
        {
            case RABM_NULL:
                /* 判断SM的状态是否处于SM_PDP_ACTIVE_PENDING */
                if (VOS_OK == SM_IsActivePending(ucEntId + RABM_2G_NSAPI_OFFSET))
                {
                    if (VOS_OK == RABM_ResumeFirstActIndStatus(RABM_3G_ENUM, ucEntId))
                    {
                        NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                            "NAS_RABM_WProcDataResumeInd: State RABM_2G_NULL change to RABM_NSAPI_ACTIVE_PENDING. NSAPI, STATE:",
                            ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                        /* 建立3G中的对应NSAPI的状态机 */
                        if (0 != pstWPsEnt->RabInfo.ucRbNum)
                        {
                            RABM_SetWState(ucEntId, RABM_ACT_PENDING_WITH_RAB);
                        }
                        else
                        {
                            RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_PENDING);
                        }
                    }
                }
                break;

            case RABM_DATA_TRANSFER_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcDataResumeInd: State change to RABM_NSAPI_ACTIVE_NO_RAB. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* 建立3G中的对应NSAPI的状态机 */
                if (0 != pstWPsEnt->RabInfo.ucRbNum)
                {
                    RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_WITH_RAB);

                    /* 通知CDS发送缓存数据, 如果CDS的模式还是NULL:
                       需要等待MMC通知CDS模式切换至GU后再发送缓存
                    */
                    NAS_RABM_SndCdsSendBuffDataInd(ucEntId + RABM_NSAPI_OFFSET,
                                                   CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
                }
                else
                {
                    RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_NO_RAB);

                    /* 如果不需要进行RAB重建，启动RB建立保护定时器,
                       等待接入层上报RB信息
                    */
                    if (VOS_FALSE == ucRebuildRabFlag)
                    {
                        NAS_RABM_SetWPsEntRabReestFlg(ucEntId);
                        NAS_RABM_StartReestRabPendingTmr(ucEntId + RABM_NSAPI_OFFSET);
                    }
                    else
                    {
                        NAS_RABM_SndCdsSendBuffDataInd(ucEntId + RABM_NSAPI_OFFSET,
                                                       CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
                    }
                }
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcDataResumeInd: This NSAPI's state is WRONG! NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }


}


/*****************************************************************************
 函 数 名  : NAS_RABM_GProcSysModeChgToWcdma
 功能描述  : 处理G模切换至W模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月24日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年3月26日
    作    者   : A00165503
    修改内容   : DTS2012032604109: L->G(确认模式)后, 数传无法恢复
*****************************************************************************/
VOS_VOID NAS_RABM_GProcSysModeChangeToWcdma(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_GProcSysModeChangeToWcdma: Build WCDMA state machine.");

    /* 关闭rout.area.update.T1定时器 */
    NAS_RABM_StopGprsRaT1Timer();

    /* 关闭Rabm.sys.3To2.T3定时器 */
    NAS_RABM_Stop3GTo2GT3Timer();

    /* 清除W模CS域实体信息 */
    NAS_RABM_ClearRabmCsEnt();

    for (ucEntId = 0; ucEntId < RABM_2G_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetGPsEntState(ucEntId))
        {
            case RABM_2G_NULL:
                /* W实体状态置为RABM_NULL */
                RABM_SetWState(ucEntId, RABM_NULL);
                break;

            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_ROUT_AREA_UPDATE:
            case RABM_DATA_TRANS_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcSysModeChangeToWcdma: State RABM_DATA_TRANS_STOP change to RABM_NSAPI_ACTIVE_NO_RAB. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* W实体状态置为RABM_DATA_TRANSFER_STOP */
                RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);
                NAS_RABM_UpdateWPsEntFromGPsEnt(ucEntId);

                /* G实体状态置为RABM_2G_NULL */
                RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_2G_NULL);

                /* 清除G实体信息 */
                NAS_RABM_ClearRabmGPsEnt(ucEntId);
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcSysModeChangeToWcdma: ERROR:This NSAPI's state is WRONG!: NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* 清除L->G流程标记 */
    NAS_RABM_ClearL2GFlg();
#endif

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_RABM_GProcSysModeChgToLte
 功能描述  : 处理G模切换至L模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月24日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年3月26日
    作    者   : A00165503
    修改内容   : DTS2012032604109: L->G(确认模式)后, 数传无法恢复
  3.日    期   : 2012年6月01日
    作    者   : y00213812
    修改内容   : 解决问题单DTS2012052903196，为W模申请实体消息

*****************************************************************************/
VOS_VOID NAS_RABM_GProcSysModeChangeToLte(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_GProcSysModeChangeToLte: Build WCDMA state machine.");

    /* 关闭rout.area.update.T1定时器 */
    NAS_RABM_StopGprsRaT1Timer();

    /* 关闭Rabm.sys.3To2.T3定时器 */
    NAS_RABM_Stop3GTo2GT3Timer();

    /* 清除W模CS域实体信息 */
    NAS_RABM_ClearRabmCsEnt();

    for (ucEntId = 0; ucEntId < RABM_2G_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetGPsEntState(ucEntId))
        {
            case RABM_2G_NULL:
                /* W实体状态置为RABM_NULL */
                RABM_SetWState(ucEntId, RABM_NULL);
                break;

            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_ROUT_AREA_UPDATE:
            case RABM_DATA_TRANS_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcSysModeChangeToLte: State RABM_DATA_TRANS_STOP change to RABM_NSAPI_ACTIVE_NO_RAB. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* W实体状态置为RABM_DATA_TRANSFER_STOP */
                RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);
				/* 为W模申请实体消息 */
                NAS_RABM_UpdateWPsEntFromGPsEnt(ucEntId);

                /* G实体状态置为RABM_2G_NULL */
                RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_2G_NULL);

                /* 清除G实体信息 */
                NAS_RABM_ClearRabmGPsEnt(ucEntId);
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcSysModeChangeToLte: ERROR:This NSAPI's state is WRONG!: NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }

    /* 清除L->G流程标记 */
    NAS_RABM_ClearL2GFlg();

}
#endif

/*****************************************************************************
 函 数 名  : NAS_RABM_GProcDataSuspendInd
 功能描述  : GPRS系统模式下处理挂起指示
 输入参数  : bRatChangeFlg  - 异系统切换标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_GProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
)
{
    if (VOS_TRUE == bRatChangeFlg)
    {
        /* 向SNDCP发送RABM_SNDCP_SAVE_DATA_IND消息 */
        NAS_RabmSndSnSaveDataInd();
    }

    /* 检查挂起标志是否已设置为TRUE */
    if (VOS_TRUE == NAS_RABM_GetDataSuspendFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
            "NAS_RABM_GProcDataSuspendInd: DataSupendFlg is TRUE, do nothing.");
        return;
    }

    /* 设置挂起标志为TRUE */
    NAS_RABM_SetDataSuspendFlg();

    /* 继承原有G2W处理流程 */
    NAS_RabmDeal2GTo3GSuspendIndMsg();

}

/*****************************************************************************
 函 数 名  : NAS_RABM_GProcDataResumeInd
 功能描述  : GPRS系统模式下处理恢复指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建

  3.日    期   : 2011年12月19日
    作    者   : o00132663
    修改内容   : PS融合项目，挂起恢复后，通知CDS

  4.日    期   : 2012年3月5日
    作    者   : A00165503
    修改内容   : DTS2012022302899, 网络侧信号衰减直至丢网, PC继续向网络进行
                 灌包, 单板必然出现复位

  5.日    期   : 2012年3月19日
    作    者   : A00165503
    修改内容   : DTS2012031404116: G模数传过程中LU, LU结束后1分钟数传才恢复

  6.日    期   : 2013年04月12日
    作    者   : l65478
    修改内容   : DTS2013031901654:彩信并发发送失败

  7.日    期   : 2013年09月23日
    作    者   : z60575
    修改内容   : DTS2013092205675, 获取模式

*****************************************************************************/
VOS_VOID NAS_RABM_GProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
)
{
    VOS_UINT8                           ucEntId;
    RABM_TRANS_MODE_ENUM                enTransMode;

    enTransMode     = RABM_ADM_ENUM;

    /* 设置挂起标志为FALSE */
    NAS_RABM_ClearDataSuspendFlg();

    /* 复位G2W使用的数传恢复标志 */
    NAS_RABM_ClearG2WDataResumeFlg();

    /* 释放在2G向3G切换开始时SNDCP缓存的数据 */
    SN_RabmClear2G3Share();

    /* 处理处于挂起状态的实体 */
    for (ucEntId = 0; ucEntId < RABM_2G_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetGPsEntState(ucEntId))
        {
            case RABM_2G_NULL:
                break;

            case RABM_DATA_TRANS_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcDataResumeInd: State change to RABM_NSAPI_OK_TRANSMODE_NO. NSAPI, STATE:",
                    ucEntId + RABM_2G_NSAPI_OFFSET, NAS_RABM_GetGPsEntState(ucEntId));

                if (VOS_TRUE == Taf_ApsIsSndcpActive(ucEntId + RABM_2G_NSAPI_OFFSET, &enTransMode))
                {
                    gastRabm2GEntity[ucEntId].TransMode = enTransMode;

                    /* G模重选回退的场景下, 状态置为RABM_DATA_TRANS_READY */
                    RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_DATA_TRANS_READY);

                    /* 通知CDS发送缓存数据, 如果CDS的模式还是NULL:
                       需要等待MMC通知CDS模式切换至GU后再发送缓存
                    */
                    NAS_RABM_SndCdsSendBuffDataInd(ucEntId + RABM_NSAPI_OFFSET,
                                                   CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
                }
                else
                {
                    /* 状态置为RABM_NSAPI_OK_TRANSMODE_NO */
                    RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_NSAPI_OK_TRANSMODE_NO);
                }
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcDataResumeInd: This NSAPI's state is WRONG! NSAPI, STATE:",
                    ucEntId + RABM_2G_NSAPI_OFFSET, NAS_RABM_GetGPsEntState(ucEntId));
                break;
        }
    }

    /* 发送ID_RABM_APS_SYS_CHG_TO_GPRS消息至APS, 激活SNDCP */
    NAS_RABM_SendApsSysChgInd(ID_RABM_APS_SYS_CHG_TO_GPRS_IND);

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_RABM_LProcSysModeChgToGprs
 功能描述  : 处理W模切换至G模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月24日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_LProcSysModeChangeToWcdma(VOS_VOID)
{
    /* 系统模式切换至L模时, RABM已经处于挂起状态, 再切换回W模时, 无需处理 */
    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_LProcSysModeChangeToWcdma: Build WCDMA state machine.");

}

/*****************************************************************************
 函 数 名  : NAS_RABM_LProcSysModeChgToLte
 功能描述  : 处理L模切换至G模的RABM实体状态转换
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月24日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年3月26日
    作    者   : A00165503
    修改内容   : DTS2012032604109: L->G(确认模式)后, 数传无法恢复
*****************************************************************************/
VOS_VOID NAS_RABM_LProcSysModeChangeToGprs(VOS_VOID)
{
    /* 系统模式由L模切换至G模时, 处理同W模切换之G模 */
    NAS_RABM_WProcSysModeChangeToGprs();

    /* 设置L->G流程标志为TRUE */
    NAS_RABM_SetL2GFlg();

}

/*****************************************************************************
 函 数 名  : NAS_RABM_LProcDataSuspendInd
 功能描述  : LTE系统模式下处理挂起指示
 输入参数  : bRatChangeFlg  - 异系统切换标志
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年5月17日
    作    者   : A00165503
    修改内容   : DTS2012051707907: L下开机后L2U重定向后, PING包无法恢复
*****************************************************************************/
VOS_VOID NAS_RABM_LProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
)
{
    /* 设置挂起标志为TRUE: L模工作时, GU模的数据面业务处于挂起状态 */
    NAS_RABM_SetDataSuspendFlg();

    /* 释放在2G向3G切换开始时SNDCP缓存的数据 */
    SN_RabmClear2G3Share();

    /* 释放在3G向2G切换开始时PDCP缓存的数据 */
    SN_RabmClear3G2Share();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_LProcDataResumeInd
 功能描述  : LTE系统模式下处理恢复指示
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建

  3.日    期   : 2012年1月3日
    作    者   : A00165503
    修改内容   : PS Projec: 删除上报APS系统模式切换指示消息

*****************************************************************************/
VOS_VOID NAS_RABM_LProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
)
{
    /* 设置挂起标志为TRUE: L模工作时, GU模的数据面业务处于挂起状态 */
    NAS_RABM_SetDataSuspendFlg();

    /* 释放在2G向3G切换开始时SNDCP缓存的数据 */
    SN_RabmClear2G3Share();

    /* 释放在3G向2G切换开始时PDCP缓存的数据 */
    SN_RabmClear3G2Share();

}

/*****************************************************************************
 函 数 名  : NAS_RABM_LProcCommMsg
 功能描述  : LTE模式下处理WRR的消息
 输入参数  : struct MsgCB                       *pMsg
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月6日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_LProcCommMsg(
    struct MsgCB                       *pMsg
)
{
    MSG_HEADER_STRU                    *pstHeader;

    pstHeader = (MSG_HEADER_STRU*)pMsg;

    switch (pstHeader->ulSenderPid)
    {
        case  WUEPS_PID_WRR:
            if (RRRABM_HANDOVER_RAB_IND == pstHeader->ulMsgName)
            {
                NAS_RabmDealHandoverRabInd((RRRABM_HANDOVER_RAB_IND_STRU *)pMsg);
            }
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_LProcCommMsg: Wrong message received in LTE mode.");
            break;
    }
}
#endif

/*****************************************************************************
 函 数 名  : NAS_RABM_InitWProcFuncTbl
 功能描述  : 初始化WCDMA处理函数列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_InitWProcFuncTbl(VOS_VOID)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstWProcFuncTbl;

    pstWProcFuncTbl = NAS_RABM_GetWProFuncTblAddr();

    PS_MEM_SET(pstWProcFuncTbl, 0x00, sizeof(NAS_RABM_PROC_FUNC_TBL_STRU));

    pstWProcFuncTbl->pSmActivateIndProcFunc     = RABM_RcvSmActInd;
    pstWProcFuncTbl->pSmDeactivateIndProcFunc   = RABM_RcvSmDeactInd;
    pstWProcFuncTbl->pSmModifyIndProcFunc       = RABM_RcvSmModInd;

    pstWProcFuncTbl->pGmmReestablishCnfProcFunc = RABM_RcvGmmReestCnf;

    pstWProcFuncTbl->pDataSuspendIndProcFunc    = NAS_RABM_WProcDataSuspendInd;
    pstWProcFuncTbl->pDataResumeIndProcFunc     = NAS_RABM_WProcDataResumeInd;
    pstWProcFuncTbl->pSysModeChgIndProcFunc     = NAS_RABM_ProcSysModeChgInd;

    pstWProcFuncTbl->pTaskEntry                 = Rabm_3GTaskEntry;

}

/*****************************************************************************
 函 数 名  : NAS_RABM_InitGProcFuncTbl
 功能描述  : 初始化GPRS处理函数列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_InitGProcFuncTbl(VOS_VOID)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstGProcFuncTbl;

    pstGProcFuncTbl = NAS_RABM_GetGProFuncTblAddr();

    PS_MEM_SET(pstGProcFuncTbl, 0x00, sizeof(NAS_RABM_PROC_FUNC_TBL_STRU));

    pstGProcFuncTbl->pSmActivateIndProcFunc     = NAS_RabmSmPdpActivateIndMsg;
    pstGProcFuncTbl->pSmDeactivateIndProcFunc   = NAS_RabmSmPdpDeactivateIndMsg;
    pstGProcFuncTbl->pSmModifyIndProcFunc       = NAS_RabmSmPdpModifyIndMsg;

    pstGProcFuncTbl->pGmmReestablishCnfProcFunc = VOS_NULL_PTR;

    pstGProcFuncTbl->pDataSuspendIndProcFunc    = NAS_RABM_GProcDataSuspendInd;
    pstGProcFuncTbl->pDataResumeIndProcFunc     = NAS_RABM_GProcDataResumeInd;
    pstGProcFuncTbl->pSysModeChgIndProcFunc     = NAS_RABM_ProcSysModeChgInd;

    pstGProcFuncTbl->pTaskEntry                 = NAS_Rabm2GMsgDispatch;

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_RABM_InitLProcFuncTbl
 功能描述  : 初始化LTE处理函数列表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月1日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_InitLProcFuncTbl(VOS_VOID)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstLProcFuncTbl;

    pstLProcFuncTbl = NAS_RABM_GetLProFuncTblAddr();

    PS_MEM_SET(pstLProcFuncTbl, 0x00, sizeof(NAS_RABM_PROC_FUNC_TBL_STRU));

    pstLProcFuncTbl->pSmActivateIndProcFunc     = VOS_NULL_PTR;
    pstLProcFuncTbl->pSmDeactivateIndProcFunc   = VOS_NULL_PTR;
    pstLProcFuncTbl->pSmModifyIndProcFunc       = VOS_NULL_PTR;

    pstLProcFuncTbl->pGmmReestablishCnfProcFunc = VOS_NULL_PTR;

    pstLProcFuncTbl->pDataSuspendIndProcFunc    = NAS_RABM_LProcDataSuspendInd;
    pstLProcFuncTbl->pDataResumeIndProcFunc     = NAS_RABM_LProcDataResumeInd;
    pstLProcFuncTbl->pSysModeChgIndProcFunc     = NAS_RABM_ProcSysModeChgInd;

    pstLProcFuncTbl->pTaskEntry                 = NAS_RABM_LProcCommMsg;

}
#endif

/*****************************************************************************
 函 数 名  : NAS_RABM_InitProcFuncTbl
 功能描述  : 初始化和注册各个系统模式的处理函数表
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_InitProcFuncTbl(VOS_VOID)
{
    /* 初始化和注册WCDMA系统模式处理函数表 */
    NAS_RABM_InitWProcFuncTbl();
    NAS_RABM_RegProcFuncTbl(NAS_MML_NET_RAT_TYPE_WCDMA,
                            NAS_RABM_GetWProFuncTblAddr());

    /* 初始化和注册GPRS系统模式处理函数表 */
    NAS_RABM_InitGProcFuncTbl();
    NAS_RABM_RegProcFuncTbl(NAS_MML_NET_RAT_TYPE_GSM,
                            NAS_RABM_GetGProFuncTblAddr());

#if (FEATURE_ON == FEATURE_LTE)
    /* 初始化和注册LTE系统模式处理函数表 */
    NAS_RABM_InitLProcFuncTbl();
    NAS_RABM_RegProcFuncTbl(NAS_MML_NET_RAT_TYPE_LTE,
                            NAS_RABM_GetLProFuncTblAddr());
#endif

}

/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabInfo
 功能描述  : 清除指定实体ID的W模RAB信息
 输入参数  : ucEntId    - 实体ID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月31日
    作    者   : y00213812
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabInfo(
    VOS_UINT8                           ucEntId
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);

    /* 初始化RAB, PDP类型, 以及QOS */
    pstWPsEnt->RabInfo.ucRbNum  = 0;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabmWPsEnt
 功能描述  : 清除指定实体ID的W模PS域实体信息
 输入参数  : VOS_UINT8                           ucEntId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月01日
    作    者   : y00213812
    修改内容   : 解决问题单DTS2012052903196，清除W模实体信息时释放Qos申请的内存

  3.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM保存的QOS由动态内存改为静态数组
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmWPsEnt(
    VOS_UINT8                           ucEntId
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);

    /* 初始化RAB, PPP标识, 以及QOS信息 */
    pstWPsEnt->RabInfo.ucRbNum = 0;
    pstWPsEnt->ucPppFlg        = RABM_SM_IP_PROT;
    pstWPsEnt->QoS.ulQosLength = 0;
    PS_MEM_SET(pstWPsEnt->QoS.aucQosValue, 0x00, sizeof(pstWPsEnt->QoS.aucQosValue));

    /* 释放缓存的上下行数据 */
    RABM_RelSaveData(&pstWPsEnt->DlDataSave, RABM_DOWNLINK);
    RABM_RelSaveData(&pstWPsEnt->UlDataSave, RABM_UPLINK);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabmGPsEnt
 功能描述  : 清除指定实体ID的G模PS域实体信息
 输入参数  : VOS_UINT8                           ucEntId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月01日
    作    者   : y00213812
    修改内容   : 解决问题单DTS2012052903196，清除G模实体信息时释放Qos申请的内存

  3.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM保存的QOS由动态内存改为静态数组
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmGPsEnt(
    VOS_UINT8                           ucEntId
)
{
    RABM_2G_ENTITY_ST                  *pstGPsEnt;

    pstGPsEnt = NAS_RABM_GetGPsEntAddr(ucEntId);

    /* 初始化STATE, NSAPI, 传输模式, 以及QOS等信息 */
    pstGPsEnt->ucNsapi           = ucEntId + RABM_2G_NSAPI_OFFSET;
    pstGPsEnt->TransMode         = RABM_ADM_ENUM;
    pstGPsEnt->RAUpdateCause     = RABM_RA_UPDATE_CAUSE_BUTT;
    pstGPsEnt->stQos.ulQosLength = 0;
    PS_MEM_SET(pstGPsEnt->stQos.aucQosValue, 0x00, sizeof(pstGPsEnt->stQos.aucQosValue));

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabmCsEnt
 功能描述  : 清除CS域相关实体信息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmCsEnt(VOS_VOID)
{
    RABM_ENTITY_CS_STRU                *pstCsEnt;
    VOS_UINT8                           ucEntId;

    /* 清除SI和RABM实体的映射关系 */
    NAS_RABM_ClearSiMapEnt();

    /* 清除CS域实体信息 */
    for (ucEntId = 0; ucEntId < RABM_CS_MAX_ENT_NUM; ucEntId++)
    {
        pstCsEnt = NAS_RABM_GetCsEntAddr(ucEntId);

        pstCsEnt->ucState           = RABM_NULL;
        pstCsEnt->RabInfo.ucRbNum   = 0;
        pstCsEnt->RabInfo.ucRabId   = NAS_RABM_INVALID_RAB_ID;
    }
}

/*****************************************************************************
 函 数 名  : NAS_RABM_ClearRabReestFlg
 功能描述  : 停止RAB重建定时器, 清除RAB重建标志
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月13日
    作    者   : A00165503
    修改内容   : DTS2012061302495: 修改调用宏的名称
  3.日    期   : 2013年04月12日
    作    者   : l65478
    修改内容   : DTS2013031901654:彩信并发发送失败
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabReestFlg(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    /* 停止RAB重建定时器 */
    if (VOS_TRUE == NAS_RABM_GetRabRsestTimerFlg())
    {
        RABM_TimerStop(0);
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_RESEND_EST_REQ);
        NAS_RABM_ClearRabRsestTimerFlg();
    }

    /* 清除RABM实体的RAB重建标志 */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        NAS_RABM_StopReestRabPendingTmr(ucEntId + RABM_NSAPI_OFFSET);
        NAS_RABM_ClearWPsEntRabReestFlg(ucEntId);
    }
}

/*****************************************************************************
 函 数 名  : NAS_RABM_StopGprsRaT1Timer
 功能描述  : 停止rout.area.update.T1定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_StopGprsRaT1Timer(VOS_VOID)
{
    if (RABM_ROUTING_AREA_UPDATE_T1_ON == NAS_RABM_GetRauT1Flg())
    {
        /* 停止rout.area.update.T1定时器 */
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1);
    }
}

/*****************************************************************************
 函 数 名  : NAS_RABM_Stop3GTo2GT3Timer
 功能描述  : 停止Rabm.sys.3To2.T3定时器
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_RABM_Stop3GTo2GT3Timer(VOS_VOID)
{
    if (RABM_3G_TO_2G_T3_ON == NAS_RABM_GetW2GT3Flg())
    {
        /* 停止Rabm.sys.3To2.T3定时器 */
        NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3);
    }
}

/*****************************************************************************
 函 数 名  : NAS_RABM_UpdateWPsEntFromGPsEnt
 功能描述  : PS域实体信息转换, G->W
 输入参数  : VOS_UINT8                           ucEntId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月01日
    作    者   : y00213812
    修改内容   : 解决问题单DTS2012052903196，更新W模实体信息时，为Qos申请内存，不再与G模共用

  3.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM保存的QOS由动态内存改为静态数组
*****************************************************************************/
VOS_VOID NAS_RABM_UpdateWPsEntFromGPsEnt(
    VOS_UINT8                           ucEntId
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;
    RABM_2G_ENTITY_ST                  *pstGPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);
    pstGPsEnt = NAS_RABM_GetGPsEntAddr(ucEntId);

    pstWPsEnt->ucPppFlg              = pstGPsEnt->ucPppFlg;
    pstWPsEnt->ucReEstFlg            = VOS_FALSE;
    pstWPsEnt->RabInfo.ucRbNum       = 0;

    pstWPsEnt->QoS.ulQosLength       = pstGPsEnt->stQos.ulQosLength;

    PS_MEM_CPY(pstWPsEnt->QoS.aucQosValue,
               pstGPsEnt->stQos.aucQosValue,
               NAS_RABM_MAX_QOS_LEN);

    pstWPsEnt->ucStpFlg              = VOS_TRUE;
    pstWPsEnt->DlDataSave.ucNum      = 0;
    pstWPsEnt->DlDataSave.Data.pData = VOS_NULL_PTR;
    pstWPsEnt->DlDataSave.Data.pNxt  = VOS_NULL_PTR;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_RABM_UpdateGPsEntFromWPsEnt
 功能描述  : PS域实体信息转换, W->G
 输入参数  : VOS_UINT8                           ucEntId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月27日
    作    者   : A00165503
    修改内容   : 新生成函数

  2.日    期   : 2012年6月01日
    作    者   : y00213812
    修改内容   : 解决问题单DTS2012052903196，更新G模实体信息时，为Qos申请内存，不再与G模共用

  3.日    期   : 2012年8月22日
    作    者   : A00165503
    修改内容   : RABM保存的QOS由动态内存改为静态数组
*****************************************************************************/
VOS_VOID NAS_RABM_UpdateGPsEntFromWPsEnt(
    VOS_UINT8                           ucEntId
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;
    RABM_2G_ENTITY_ST                  *pstGPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);
    pstGPsEnt = NAS_RABM_GetGPsEntAddr(ucEntId);

    pstGPsEnt->ucNsapi             = ucEntId + RABM_2G_NSAPI_OFFSET;
    pstGPsEnt->TransMode           = RABM_ADM_ENUM;

    pstGPsEnt->stQos.ulQosLength   = pstWPsEnt->QoS.ulQosLength;

    PS_MEM_CPY(pstGPsEnt->stQos.aucQosValue,
               pstWPsEnt->QoS.aucQosValue,
               NAS_RABM_MAX_QOS_LEN);

    pstGPsEnt->RAUpdateCause       = RABM_RA_UPDATE_CAUSE_BUTT;
    pstGPsEnt->ucPppFlg            = pstWPsEnt->ucPppFlg;

    return;
}

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


