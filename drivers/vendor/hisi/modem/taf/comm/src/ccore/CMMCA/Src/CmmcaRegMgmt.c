/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CmmcaRegMgmt.c
  版 本 号   : 初稿
  作    者   : s00261364
  生成日期   : 2014年01月26日
  最近修改   :
  功能描述   : CMMCA模块搜网注册相关的处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年01月26日
    作    者   : s00261364
    修改内容   : 新生成

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "CmmcaRegMgmt.h"
#include "CmmcaCtx.h"

#include "CbpaPsInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人: l60609; */
#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_REG_MGMT_C
/*lint +e767 修改人: l60609; */

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* MMA消息处理函数 */
const CMMCA_REG_MMA_EVT_FUNC_TBL_STRU       g_astCmmcaRegEvtFuncTbl[] =
{
    {ID_TAF_MMA_SYS_CFG_SET_CNF,
        CMMCA_REG_RcvMmaSysCfgCnf},
    {ID_TAF_MMA_PHONE_MODE_SET_CNF,
        CMMCA_REG_RcvMmaPhoneModeSetcnf},
    {ID_TAF_MMA_ACQ_BEST_NETWORK_CNF,
        CMMCA_REG_RcvMmaAcqCnf},
    {ID_TAF_MMA_SERVICE_STATUS_IND,
        CMMCA_REG_RcvMmaServiceStateInd},
    {ID_TAF_MMA_ACQ_IND,
        CMMCA_REG_RcvMmaAcqInd},
    {ID_TAF_MMA_POWER_SAVE_CNF,
        CMMCA_REG_RcvMmaPowerSaveCnf},
    {ID_TAF_MMA_REG_CNF,
        CMMCA_REG_RcvMmaRegCnf},
    {ID_TAF_MMA_DETACH_CNF,
        CMMCA_REG_RcvMmaDetachCnf},
    {ID_TAF_MMA_SYS_INFO_IND,
        CMMCA_REG_RcvMmaSysInfoInd},
    {ID_TAF_MMA_SIM_STATUS_IND,
        CMMCA_REG_RcvMmaSimStatusInd}
};

/* g_astCmmcaRegEvtFuncTbl的Item个数 */
const VOS_UINT32 g_ulCmmcaRegEvtFuncTblSize  = sizeof(g_astCmmcaRegEvtFuncTbl) / sizeof(g_astCmmcaRegEvtFuncTbl[0]);

/*****************************************************************************
  3 函数定义
*****************************************************************************/


/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvRatModeReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_RAT_MODE_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数
  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_VOID CMMCA_REG_RcvRatModeReq(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfgPara;
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_REG_CTX_STRU                 *pstRegCtx    = VOS_NULL_PTR;
    CMMCA_MMC_RAT_MODE_REQ_STRU         stModeReq;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* 参考VIA接口文档，解析消息 */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stModeReq, 0, sizeof(CMMCA_MMC_RAT_MODE_REQ_STRU));

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParseModeReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                 pstDataInd->aucData,
                                 &stModeReq);
    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_FAIL);
        return;
    }

    /* 申请OPID,缓存pMsg到与OPID相应的buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* 打印错误信息 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvRatModeReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_FAIL);
        return;
    }

    /* 目前CL互操作，balong modem需要适配为PS only，因此此时设置ctx为PS */
    pstRegCtx = CMMCA_REG_GetCtxAddr();
    pstRegCtx->enSrvDomain = TAF_MMA_SERVICE_DOMAIN_PS;

    /* 调用API接口TAF_MMA_SysCfgReq */
    PS_MEM_SET(&stSysCfgPara, 0x00, sizeof(TAF_MMA_SYS_CFG_PARA_STRU));

    /* 用于国内版本，澳大利亚漫游特性NV8266关闭，2表示不改变 */
    stSysCfgPara.enRoam                    = TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON;

    /* 如果漫游特性NV8266开启，则设置为4，表示不改变 */
    if (VOS_TRUE == pstRegCtx->stUserCfgInfo.ucIsRoamActive)
    {
        stSysCfgPara.enRoam = TAF_MMA_ROAM_UNCHANGE;
    }

    stSysCfgPara.enSrvDomain               = TAF_MMA_SERVICE_DOMAIN_PS;
    stSysCfgPara.enUserPrio                = TAF_MMA_USER_SET_PRIO_NOCHANGE;
    stSysCfgPara.stRatOrder.ucRatOrderNum  = 1;
    stSysCfgPara.stRatOrder.aenRatOrder[0] = TAF_MMA_RAT_LTE;

    /* 频段不改变 */
    stSysCfgPara.stGuBand.ulBandLow        = TAF_PH_BAND_NO_CHANGE;
    stSysCfgPara.stGuBand.ulBandHigh       = 0;
    stSysCfgPara.stLBand.ulBandLow         = TAF_PH_BAND_NO_CHANGE;
    stSysCfgPara.stLBand.ulBandHigh        = 0;

    if (VOS_TRUE != TAF_MMA_SetSysCfgReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stSysCfgPara))
    {
        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_FAIL);

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvPowerUpReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_POWERUP_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvPowerUpReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_POWERUP_REQ_STRU      stPowerUpReq;
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* 参考VIA接口文档，解析消息 */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    ucOpId = 0;

    PS_MEM_SET(&stPowerUpReq, 0, sizeof(CMMCA_MMC_RAT_POWERUP_REQ_STRU));

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParsePowerUpReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stPowerUpReq);
    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_FAIL);

        return;
    }

    /* 申请OPID,缓存pMsg到与OPID相应的buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* 打印错误信息 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPowerUpReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_FAIL);

        return;
    }

    /* 调用API接口TAF_MMA_PhoneModeSetReq(full mode)发送开机消息到MMA */
    PS_MEM_SET(&stPhoneModePara, 0x00, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));
    stPhoneModePara.PhMode  = TAF_PH_MODE_FULL;
    stPhoneModePara.PhReset = TAF_PH_OP_MODE_UNRESET;
    if (VOS_TRUE != TAF_MMA_PhoneModeSetReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stPhoneModePara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPowerUpReq: PhoneModeSetReq SEND fail!");

        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_FAIL);

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvPowerDownReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_POWERDOWN_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvPowerDownReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd      = VOS_NULL_PTR;
    CMMCA_MMC_RAT_POWERDOWN_REQ_STRU    stPowerDownReq;
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* 参考VIA接口文档，解析消息 */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stPowerDownReq, 0, sizeof(CMMCA_MMC_RAT_POWERDOWN_REQ_STRU));

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParsePowerDownReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stPowerDownReq);
    if (VOS_OK != ulRslt)
    {
        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_POWERDOWN_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* 申请OPID,缓存pMsg到与OPID相应的buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* 打印错误信息 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPowerDownReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(stPowerDownReq.enRatId, ID_CMMCA_MMC_RAT_POWERDOWN_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* 调用API接口TAF_MMA_PhoneModeSetReq(mini mode)发送开机消息到MMA */
    PS_MEM_SET(&stPhoneModePara, 0x00, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));
    stPhoneModePara.PhMode  = TAF_PH_MODE_MINI;
    stPhoneModePara.PhReset = TAF_PH_OP_MODE_UNRESET;

    if (VOS_TRUE != TAF_MMA_PhoneModeSetReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stPhoneModePara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPowerDownReq: TAF_MMA_PhoneModeSetReq SEND fail!");

        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(stPowerDownReq.enRatId, ID_CMMCA_MMC_RAT_POWERDOWN_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvRatAcqReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_ACQ_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvRatAcqReq(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_ACQ_PARA_STRU               stAcqPara;
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_ACQ_REQ_STRU          stAcqReq;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* 参考VIA接口文档，解析消息 */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stAcqReq, 0, sizeof(CMMCA_MMC_RAT_ACQ_REQ_STRU));
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));
    PS_MEM_SET(&stAcqPara, 0, sizeof(TAF_MMA_ACQ_PARA_STRU));

    stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
    stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
    stRatInfo.enPriorityClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParseAcqReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                pstDataInd->aucData,
                                &stAcqReq);
    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndAcqRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_ACQ_RESULT_ACQFAILED, &stRatInfo);
        return;
    }

    /* 申请OPID,缓存pMsg到与OPID相应的buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* 打印错误信息 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvRatAcqReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndAcqRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_ACQ_RESULT_ACQFAILED, &stRatInfo);

        return;
    }

    /* 调用API接口TAF_MMA_AcqReq发起初始网络搜索*/
    if (CMMCA_RAT_ACQ_REQ_REASON_INIT_ACQ == stAcqReq.enCause)
    {
        stAcqPara.enAcqReason = TAF_MMA_ACQ_REASON_POWER_UP;
    }
    else if (CMMCA_RAT_ACQ_REQ_REASON_OOS_ACQ == stAcqReq.enCause)
    {
        stAcqPara.enAcqReason = TAF_MMA_ACQ_REASON_OOS;
    }
    else if (CMMCA_RAT_ACQ_REQ_REASON_BSR_ACQ == stAcqReq.enCause)
    {
        stAcqPara.enAcqReason = TAF_MMA_ACQ_REASON_HIGH_PRIO;
    }
    else
    {
        stAcqPara.enAcqReason = TAF_MMA_ACQ_REASON_OOS;
        CMMCA_WARNING_LOG("CMMCA_REG_RcvRatAcqReq: unkownn acq reason!");
    }

    if (VOS_TRUE != TAF_MMA_AcqBestNetworkReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stAcqPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvRatAcqReq: TAF_MMA_AcqBestNetworkReq SEND fail!");

        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndAcqRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_ACQ_RESULT_ACQFAILED, &stRatInfo);

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        return;
    }

    /* 设置Modem的状态为ACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_ACTIVE);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvMccSearchReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_MCC_SEARCH_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMccSearchReq(
    VOS_VOID                           *pMsg
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx = VOS_NULL_PTR;
    CMMCA_RAT_MMC_RAT_SYS_INFO_STRU     stSysInfo;

    PS_MEM_SET(&stSysInfo, 0, sizeof(CMMCA_RAT_MMC_RAT_SYS_INFO_STRU));

    /* 查询CMMCA本地保存的MCC信息*/
    pstRegCtx = CMMCA_REG_GetCtxAddr();

    /* 回复ID_CMMCA_RAT_MMC_MCC_SEARCH_RSP到RAT */
    stSysInfo.ulMcc = pstRegCtx->stPlmnId.Mcc;
    stSysInfo.ulMnc = pstRegCtx->stPlmnId.Mnc;

    stSysInfo.stEutran.usEarfcn = (VOS_UINT16)pstRegCtx->ulArfcn;

    CMMCA_REG_SndMccSearchRsp(CMMCA_MMC_RAT_ID_EUTRAN, &stSysInfo);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvPsRegReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_PS_REG_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvPsRegReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_PS_REG_REQ_STRU       stPsRegReq;
    TAF_MMA_REG_PARA_STRU               stRegPara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* 参考VIA接口文档，解析消息 */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stPsRegReq, 0, sizeof(CMMCA_MMC_RAT_PS_REG_REQ_STRU));
    PS_MEM_SET(&stRegPara, 0, sizeof(TAF_MMA_REG_PARA_STRU));

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParsePsRegReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stPsRegReq);
    if (VOS_OK != ulRslt)
    {
        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);
        return;
    }

    /* 申请OPID,缓存pMsg到与OPID相应的buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* 打印错误信息 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPsRegReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* 调用MMA模块API接口TAF_MMA_RegReq，触发指定条件的网络发起注册*/
    stRegPara.bitOpPrioClass       = 1;

    if (CMMCA_RAT_GMSS_PRIORITY_CLASS_HOME == stPsRegReq.enPriorityClass)
    {
        stRegPara.enPrioClass = TAF_MMA_PLMN_PRIORITY_HOME;
    }
    else if (CMMCA_RAT_GMSS_PRIORITY_CLASS_PREF == stPsRegReq.enPriorityClass)
    {
        stRegPara.enPrioClass = TAF_MMA_PLMN_PRIORITY_PREF;
    }
    else if (CMMCA_RAT_GMSS_PRIORITY_CLASS_ANY == stPsRegReq.enPriorityClass)
    {
        stRegPara.enPrioClass = TAF_MMA_PLMN_PRIORITY_ANY;
    }
    else
    {
        CMMCA_WARNING_LOG("CMMCA_REG_RcvPsRegReq: unkown enPriorityClass!");
        stRegPara.enPrioClass = TAF_MMA_PLMN_PRIORITY_ANY;
    }
    stRegPara.bitOpEpsAttachReason = 1;
    if (CMMCA_RAT_ATTACH_TYPE_HANDOVER == stPsRegReq.ucAttachType)
    {
        stRegPara.enEpsAttachReason    = TAF_MMA_ATTACH_REASON_HANDOVER;
    }
    else
    {
        stRegPara.enEpsAttachReason    = TAF_MMA_ATTACH_REASON_INITIAL;
    }

    stRegPara.enAttachDomain       = TAF_MMA_SERVICE_DOMAIN_PS;

    if (VOS_TRUE != TAF_MMA_RegReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stRegPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPsRegReq: TAF_MMA_RegReq SEND fail!");

        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        return;
    }

    /* 设置Modem的状态为ACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_ACTIVE);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvCellInfoPsRegReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvCellInfoPsRegReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU                                *pstDataInd           = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ_STRU                *pstCellInfoPsRegReq  = VOS_NULL_PTR;
    TAF_MMA_REG_PARA_STRU                                   stRegPara;
    VOS_UINT32                                              ulRslt;
    VOS_UINT8                                               ucOpId;
    VOS_UINT32                                              i;
    CMMCA_RAT_SYS_INFO_STRU                                 stRatInfo;

    /* 参考VIA接口文档，解析消息 */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));
    PS_MEM_SET(&stRegPara, 0, sizeof(TAF_MMA_REG_PARA_STRU));
    stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
    stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
    stRatInfo.enPriorityClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;

    /* 为解析的消息申请内存 */
    pstCellInfoPsRegReq = (CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_CMMCA, sizeof(CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ_STRU));
    if (VOS_NULL_PTR == pstCellInfoPsRegReq)
    {
        /* 异常打印 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvCellInfoPsRegReq: PS_MEM_ALLOC fail!");

        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParseCellInfoPsRegReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    pstCellInfoPsRegReq);
    if (VOS_OK != ulRslt)
    {
        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* 释放内存 */
        PS_MEM_FREE(WUEPS_PID_CMMCA, pstCellInfoPsRegReq);

        return;
    }

    /* 申请OPID,缓存pMsg到与OPID相应的buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* 打印错误信息 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvCellInfoPsRegReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* 释放内存 */
        PS_MEM_FREE(WUEPS_PID_CMMCA, pstCellInfoPsRegReq);

        return;
    }

    /* 调用MMA模块API接口TAF_MMA_RegReq，触发指定条件的网络发起注册*/
    stRegPara.bitOpCellInfo        = 1;
    stRegPara.bitOpEpsAttachReason = 1;
    stRegPara.enEpsAttachReason    = TAF_MMA_ATTACH_REASON_HANDOVER; /* C->L重选时填写该原因 */
    stRegPara.enAttachDomain       = TAF_MMA_SERVICE_DOMAIN_PS;
    stRegPara.stCellInfo.ulArfcn   = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.usEarfcn;
    stRegPara.stCellInfo.ucCellNum = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.usNumCell;
    stRegPara.stCellInfo.ucPlmnNum = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.ucNumPlmn;

    for ( i = 0; i < stRegPara.stCellInfo.ucCellNum; i++ )
    {
        stRegPara.stCellInfo.ausCellId[i] = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.ausCellId[i];
    }

    for ( i = 0; i < stRegPara.stCellInfo.ucPlmnNum; i++ )
    {
        stRegPara.stCellInfo.astPlmnId[i].Mcc = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.aulMcc[i];
        stRegPara.stCellInfo.astPlmnId[i].Mnc = pstCellInfoPsRegReq->stSystemChangeReq.stTargetSystemCarrierInfo.stCarrierInfoEutran.aulMnc[i];
    }

    /* 释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pstCellInfoPsRegReq);

    if (VOS_TRUE != TAF_MMA_RegReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stRegPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvCellInfoPsRegReq: TAF_MMA_RegReq SEND fail!");

        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        return;
    }

    /* 设置Modem的状态为ACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_ACTIVE);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvPktDataCmdReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvPktDataCmdReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    TAF_MMA_DETACH_PARA_STRU            stDetachPara;
    VOS_UINT8                           ucOpId;
    VOS_UINT32                          ulRslt;

    /* 参考VIA接口文档，解析消息 */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* 申请OPID,缓存pMsg到与OPID相应的buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* 打印错误信息 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPktDataCmdReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        return;
    }

    /* 执行Detach操作 */
    PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));
    stDetachPara.enDetachCause  = TAF_MMA_DETACH_CAUSE_3GPP2_ATTACHED;
    stDetachPara.enDetachDomain = TAF_MMA_SERVICE_DOMAIN_PS;
    if (VOS_TRUE != TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stDetachPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvPktDataCmdReq: TAF_MMA_DetachReq SEND fail!");

        /* 直接回REJ */
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvNoServiceReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_NO_SERVICE_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvNoServiceReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_NO_SERVICE_REQ_STRU   stNoServReq;
    TAF_MMA_DETACH_PARA_STRU            stDetachPara;
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* 参考VIA接口文档，解析消息 */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stNoServReq, 0 , sizeof(CMMCA_MMC_RAT_NO_SERVICE_REQ_STRU));

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParseNoServiceReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stNoServReq);
    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);

        return;
    }

    /* 申请OPID,缓存pMsg到与OPID相应的buffer */
    ucOpId = 0x0;
    CMMCA_AssignOpid(&ucOpId);
    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);
    if (VOS_OK != ulRslt)
    {
        /* 打印错误信息 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvNoServiceReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* 直接回RSP(FAIL) */
        CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);

        return;
    }

    /* 如果原因值非OOS调用MMA模块API接口TAF_MMA_DetachReq，触发LTE detach流程 */
    if (CMMCA_MMC_RAT_NOSVC_CAUSE_OOSA != stNoServReq.enCause)
    {
        /* 执行Detach操作 */
        PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));
        stDetachPara.enDetachCause  = TAF_MMA_DETACH_CAUSE_USER_DETACH;
        stDetachPara.enDetachDomain = TAF_MMA_SERVICE_DOMAIN_PS;
        if (VOS_TRUE != TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stDetachPara))
        {
            CMMCA_ERROR_LOG("CMMCA_REG_RcvNoServiceReq: TAF_MMA_DetachReq SEND fail!");

            /* 直接回RSP(FAIL) */
            CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);

            /* 释放opid,清空缓存 */
            CMMCA_DelItemInCmdBufferQueue(ucOpId);

            return ;
        }
    }
    /* 否则调用TAF_MMA_PowerSaveReq */
    else
    {
        /* 执行PowerSave操作 */
        PS_MEM_SET(&stPowerSavePara, 0, sizeof(TAF_MMA_POWER_SAVE_PARA_STRU));
        if (VOS_TRUE != TAF_MMA_PowerSaveReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stPowerSavePara))
        {
            CMMCA_ERROR_LOG("CMMCA_REG_RcvNoServiceReq: TAF_MMA_PowerSaveReq SEND fail!");

            /* 直接回RSP(FAIL) */
            CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);

            /* 释放opid,清空缓存 */
            CMMCA_DelItemInCmdBufferQueue(ucOpId);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvBearDetachReq
 功能描述  : 处理ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CMMCA_REG_RcvBearDetachReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd  = VOS_NULL_PTR;
    CMMCA_MMC_RAT_BEAR_DETACH_REQ_STRU  stBearDetachReq;
    TAF_MMA_DETACH_PARA_STRU            stDetachPara;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    /* 参考VIA接口文档，解析消息 */
    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stBearDetachReq, 0, sizeof(CMMCA_MMC_RAT_BEAR_DETACH_REQ_STRU));

    /* 调用解析函数将CMD码流解析成对应的数据结构，解析函数已保证参数的有效性 */
    ulRslt = CMMCA_ParseBearDetachReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                      pstDataInd->aucData,
                                      &stBearDetachReq);
    if (VOS_OK != ulRslt)
    {
        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_FAIL);

        return;
    }

    /* 申请OPID,缓存pMsg到与OPID相应的buffer */
    ucOpId = 0x0;

    CMMCA_AssignOpid(&ucOpId);

    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(pstDataInd->aucData), pstDataInd->ulDataLen);

    if (VOS_OK != ulRslt)
    {
        /* 打印错误信息 */
        CMMCA_ERROR_LOG("CMMCA_REG_RcvBearDetachReq: CMMCA_SaveItemInCmdBufferQueue fail!");

        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_FAIL);

        return;
    }

    /* 执行Detach操作 */
    PS_MEM_SET(&stDetachPara, 0, sizeof(TAF_MMA_DETACH_PARA_STRU));

    stDetachPara.enDetachCause  = TAF_MMA_DETACH_CAUSE_USER_DETACH;
    stDetachPara.enDetachDomain = TAF_MMA_SERVICE_DOMAIN_PS;

    if (VOS_TRUE != TAF_MMA_DetachReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stDetachPara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvBearDetachReq: TAF_MMA_DetachReq SEND fail!");

        /* 直接回RSP(FAIL) */
        CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_FAIL);

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        return ;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvMmaSysCfgCnf
 功能描述  : 处理来自MMA模块ID_TAF_MMA_SYS_CFG_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMmaSysCfgCnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer     = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid;

    /* 解析消息的opid,根据opid查找缓存的请求消息 */
    ucOpid       = ((TAF_MMA_SYS_CFG_CNF_STRU*)pMsg)->ucOpid;
    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaSysCfgCnf: CMMCA_GetItemFromCmdBufferQueue fail!");

        return;
    }

    /* 增加请求消息异常判断，如果不是ID_CMMCA_MMC_RAT_RAT_MODE_REQ ,则丢弃此cnf */
    if (ID_CMMCA_MMC_RAT_RAT_MODE_REQ != CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaSysCfgCnf: cmdId invalid!");

        return;
    }

    /* 回复ID_CMMCA_RAT_MMC_RAT_MODE_RSP到RAT */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS != ((TAF_MMA_SYS_CFG_CNF_STRU*)pMsg)->enRslt)
    {

        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_FAIL);
    }
    else
    {
        CMMCA_REG_SndModeRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_MODE_RSP_SUCC);
    }

    /* 释放opid,清空缓存 */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvPhoneModeSetcnf
 功能描述  : 处理ID_TAF_MMA_PHONE_MODE_SET_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMmaPhoneModeSetcnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer = VOS_NULL_PTR;
    CMMCA_REG_CTX_STRU                 *pstRegCtx    = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* 解析消息的opid,根据opid查找缓存的请求消息 */
    ucOpid       = ((TAF_MMA_PHONE_MODE_SET_CNF_STRU*)pMsg)->ucOpid;

    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaPhoneModeSetcnf: CMMCA_GetItemFromCmdBufferQueue fail!");

        return;
    }

    /* 增加请求消息异常判断，如果不是ID_CMMCA_MMC_RAT_POWERUP_REQ/ID_CMMCA_MMC_RAT_POWERDOWN_REQ ,则丢弃此cnf */
    usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo);

    if ((ID_CMMCA_MMC_RAT_POWERUP_REQ   != usCmdId)
     && (ID_CMMCA_MMC_RAT_POWERDOWN_REQ != usCmdId))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaPhoneModeSetcnf: cmdId invalid!");

        return;
    }

    /* 设置Modem的状态为INACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);

    /* 根据ID_TAF_MMA_PHONE_MODE_SET_CNF结果回复开机ID_CMMCA_RAT_MMC_POWERUP_RSP/ID_CMMCA_RAT_MMC_POWERDOWN_RSP关机响应到RAT */
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));
    stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
    stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
    stRatInfo.enPriorityClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;

    if (ID_CMMCA_MMC_RAT_POWERUP_REQ == usCmdId)
    {
        if (TAF_MMA_APP_OPER_RESULT_SUCCESS ==(((TAF_MMA_PHONE_MODE_SET_CNF_STRU*)pMsg)->enRslt))
        {
            CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_SUCCESS);  /* 开机成功 */
            pstRegCtx = CMMCA_REG_GetCtxAddr();
            if (VOS_FALSE == pstRegCtx->ucPsSimValid)/* 根据上下文中保存的卡状态信息，发送NTW指示到CBPCA */
            {
                CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_SUSPEND, CMMCA_RAT_CPST_INIT, &stRatInfo); /* 无卡 */
            }
        }
        else
        {
            CMMCA_REG_SndPowerUpRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_POWERUP_RSP_RESULT_FAIL); /* 开机失败 */
        }
    }
    else
    {
        CMMCA_REG_SndPowerDownRsp(CMMCA_MMC_RAT_ID_EUTRAN);  /* 关机成功 */

        /* Deleted by w00167002 for L-C互操作项目, 2014-3-15, begin */
        /* Deleted by w00167002 for L-C互操作项目, 2014-3-15, end */
    }

    /* 释放opid,清空缓存 */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvMmaAcqCnf
 功能描述  : 处理ID_TAF_MMA_ACQ_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMmaAcqCnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer    = VOS_NULL_PTR;
    CMMCA_REG_CTX_STRU                 *pstRegCtx       = VOS_NULL_PTR;
    TAF_MMA_ACQ_CNF_STRU               *pstAcqCnf       = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid;
    CMMCA_RAT_ACQ_RESULT_ENUM_UINT8     enRslt;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* 解析消息的opid,根据opid查找缓存的请求消息 */
    pstAcqCnf    = (TAF_MMA_ACQ_CNF_STRU*)pMsg;
    ucOpid       = pstAcqCnf->ucOpid;
    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaAcqCnf: CMMCA_GetItemFromCmdBufferQueue fail!");

        return;
    }

    /* 增加请求消息异常判断，如果不是ID_CMMCA_MMC_RAT_ACQ_REQ,则丢弃此cnf */
    if (ID_CMMCA_MMC_RAT_ACQ_REQ != CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaAcqCnf: cmdId invalid!");

        return;
    }

    if (TAF_MMA_APP_OPER_RESULT_REJECT == pstAcqCnf->enRslt)
    {
        CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_ACQ_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpid);

        return;
    }

    /* 如果获取成功，缓存收到的plmn id和频点 */
    pstRegCtx               = CMMCA_REG_GetCtxAddr();
    pstRegCtx->stPlmnId.Mcc = pstAcqCnf->stPlmnId.Mcc;
    pstRegCtx->stPlmnId.Mnc = pstAcqCnf->stPlmnId.Mnc;
    pstRegCtx->ulArfcn      = pstAcqCnf->ulArfcn;
    pstRegCtx->enPrioClass  = pstAcqCnf->enPrioClass;

    /* 回复ID_CMMCA_RAT_MMC_ACQ_RSP到CBPCA */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstAcqCnf->enRslt)
    {
        enRslt = CMMCA_RAT_ACQ_RESULT_ACQUIRED;
    }
    else
    {
        enRslt = CMMCA_RAT_ACQ_RESULT_ACQFAILED;
    }

    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstAcqCnf->enPrioClass);

    stRatInfo.ulMcc           = pstAcqCnf->stPlmnId.Mcc;
    stRatInfo.ulMnc           = pstAcqCnf->stPlmnId.Mnc;
    stRatInfo.usEarfcn        = (VOS_UINT16)pstAcqCnf->ulArfcn;

    CMMCA_REG_SndAcqRsp(CMMCA_MMC_RAT_ID_EUTRAN, enRslt, &stRatInfo);

    /* Deleted by w00167002 for L-C互操作项目, 2014-3-15, begin */
    /* Deleted by w00167002 for L-C互操作项目, 2014-3-15, end */

    /* 释放opid,清空缓存 */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvMmaServiceStateInd
 功能描述  : 处理MMA上报的服务指示消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMmaServiceStateInd(
    VOS_VOID                           *pMsg
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx         = VOS_NULL_PTR;
    TAF_MMA_SERVICE_STATUS_IND_STRU    *pstServStatusInd  = VOS_NULL_PTR;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;
    VOS_UINT32                          i;

    /* 获取最新的服务状态信息上下文 */
    pstServStatusInd        = (TAF_MMA_SERVICE_STATUS_IND_STRU*)pMsg;
    pstRegCtx               = CMMCA_REG_GetCtxAddr();

    /* 遍历队列, 如果当前存在有这6个消息对应的操作，不用报状态，返回 */
    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();
    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        if ((VOS_NULL_PTR != pstCmdBufferQueue[i].pucMsgInfo)
         && (CMMCA_OPID_INVILID_VALUE != pstCmdBufferQueue[i].ucOpId))
        {
            usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBufferQueue[i].pucMsgInfo);
            if ((ID_CMMCA_MMC_RAT_ACQ_REQ              == usCmdId)
             || (ID_CMMCA_MMC_RAT_PS_REG_REQ           == usCmdId)
             || (ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ == usCmdId)
             || (ID_CMMCA_MMC_RAT_POWERDOWN_REQ        == usCmdId)
             || (ID_CMMCA_MMC_RAT_NO_SERVICE_REQ       == usCmdId)
             || (ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ    == usCmdId))
            {
                pstRegCtx->ucPsSrvSta     = pstServStatusInd->PsSrvSta;
                pstRegCtx->ucPsSimValid   = pstServStatusInd->ucPsSimValid;
                pstRegCtx->ucCsSrvSta     = pstServStatusInd->CsSrvSta;
                pstRegCtx->ucCsSimValid   = pstServStatusInd->ucCsSimValid;

                return;
            }
        }
    }

    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    if (TAF_REPORT_SRVSTA_NO_SERVICE == pstServStatusInd->PsSrvSta)
    {
        stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
        stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
    }
    else
    {
        stRatInfo.ulMcc           = pstRegCtx->stPlmnId.Mcc;
        stRatInfo.ulMnc           = pstRegCtx->stPlmnId.Mnc;
        stRatInfo.usEarfcn        = (VOS_UINT16)pstRegCtx->ulArfcn;
    }

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstRegCtx->enPrioClass);

    /* 判断服务状态是否发生变化，如果变化需要报网络状态 */
    if (CMMCA_MODEM_STATUS_ACTIVE == CMMCA_GetModemStatus())
    {
        CMMCA_REG_SndNtwIndRpt(&stRatInfo, pstServStatusInd);
    }

    /* 保存最新的服务状态信息到上下文 */
    pstRegCtx->ucPsSrvSta   = pstServStatusInd->PsSrvSta;
    pstRegCtx->ucPsSimValid = pstServStatusInd->ucPsSimValid;
    pstRegCtx->ucCsSrvSta   = pstServStatusInd->CsSrvSta;
    pstRegCtx->ucCsSimValid = pstServStatusInd->ucCsSimValid;

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvMmaAcqInd
 功能描述  : 处理ID_TAF_MMA_ACQ_IND消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMmaAcqInd(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_ACQ_IND_STRU               *pstAcqInd   = VOS_NULL_PTR;
    CMMCA_REG_CTX_STRU                 *pstRegCtx   = VOS_NULL_PTR;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;


    /* 保存最新的服务状态信息到上下文 */
    pstAcqInd = (TAF_MMA_ACQ_IND_STRU*)pMsg;
    pstRegCtx = CMMCA_REG_GetCtxAddr();

    pstRegCtx->stPlmnId.Mcc     = pstAcqInd->stPlmnId.Mcc;
    pstRegCtx->stPlmnId.Mnc     = pstAcqInd->stPlmnId.Mnc;
    pstRegCtx->ulArfcn          = pstAcqInd->ulArfcn;
    pstRegCtx->enPrioClass      = pstAcqInd->enPrioClass;

    /* 回复ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND(RAT_ACQUIRE)到RAT */
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstAcqInd->enPrioClass);

    stRatInfo.ulMcc           = pstAcqInd->stPlmnId.Mcc;
    stRatInfo.ulMnc           = pstAcqInd->stPlmnId.Mnc;
    stRatInfo.usEarfcn        = (VOS_UINT16)pstAcqInd->ulArfcn;

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstAcqInd->enRslt)
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_ACQED, CMMCA_RAT_CPST_ACQUIRED, &stRatInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvMmaPowerSaveCnf
 功能描述  : 处理MMA模块的ID_TAF_MMA_POWER_SAVE_CNF消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMmaPowerSaveCnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer    = VOS_NULL_PTR;
    TAF_MMA_POWER_SAVE_CNF_STRU        *pstPowerSaveCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* 解析消息的opid,根据opid查找缓存的请求消息 */
    pstPowerSaveCnf = (TAF_MMA_POWER_SAVE_CNF_STRU*)pMsg;
    ucOpid          = pstPowerSaveCnf->ucOpid;
    pstCmdBuffer    = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaPowerSaveCnf: CMMCA_GetItemFromCmdBufferQueue fail!");
        return;
    }

    /* 增加请求消息异常判断，如果不是ID_CMMCA_MMC_RAT_NO_SERVICE_REQ/ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ/
        ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ,则丢弃此cnf */
    usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo);

    if ((ID_CMMCA_MMC_RAT_NO_SERVICE_REQ         != usCmdId)
     && (ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ != usCmdId)
     && (ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ      != usCmdId))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaPowerSaveCnf: cmdId invalid!");
        return;
    }

    if (ID_CMMCA_MMC_RAT_NO_SERVICE_REQ == usCmdId)
    {
        if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstPowerSaveCnf->enRslt)
        {
            /* 回复ID_CMMCA_RAT_MMC_NO_SERVICE_RSP到CBPCA */
            CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_SUCC);

            /* Deleted by w00167002 for L-C互操作项目, 2014-3-15, begin */
            /* Deleted by w00167002 for L-C互操作项目, 2014-3-15, end */


            /* 设置Modem的状态为INACTIVE */
            CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);
        }
        else
        {
            /* 回复ID_CMMCA_RAT_MMC_NO_SERVICE_RSP/ID_CMMCA_RAT_MMC_DATACONNECTION_CMD_RSP到CBPCA */
            CMMCA_REG_SndNoServiceRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_NO_SERV_RSP_FAIL);
        }
    }
    else if (ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ == usCmdId)
    {
        /* 回复ID_CMMCA_RAT_MMC_DATACONNECTION_CMD_RSP到CBPCA */
        CMMCA_REG_SndPktDataCmdRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_IRAT_DATA_CONNECT_CMD_RSP_PKT_DISABLED);

        /* Deleted by w00167002 for L-C互操作项目, 2014-3-15, begin */
        /* Deleted by w00167002 for L-C互操作项目, 2014-3-15, end */

        /* 设置Modem的状态为INACTIVE */
        CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);
    }
    else
    {
        if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstPowerSaveCnf->enRslt)
        {
            CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_SUCC);

            /* 回复ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND(RAT_ACQUIRE)到RAT */
            PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

            stRatInfo.ulMcc           = CMMCA_INVALID_MCC;
            stRatInfo.ulMnc           = CMMCA_INVALID_MNC;
            stRatInfo.enPriorityClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;

            CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_PS_DEREGED, CMMCA_RAT_CPST_SYSLOST, &stRatInfo);
        }
        else
        {
            CMMCA_PKT_SndBearDetachRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_MMC_BEAR_DETACH_RSP_FAIL);
        }
    }

    /* 释放opid,清空缓存 */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

    return;
}

 /*****************************************************************************
  函 数 名  : CMMCA_REG_RcvMmaRegCnf
  功能描述  : 处理MMA模块的ID_TAF_MMA_REG_CNF消息
  输入参数  : VOS_VOID *pMsg
  输出参数  : 无
  返 回 值  : VOS_VOID
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2014年1月24日
     作    者   : s00261364
     修改内容   : 新生成函数
   2.日    期   : 2015年4月22日
     作    者   : wx270776
     修改内容   : DTS2015031602665:将LMM ATTACH注册状态带给VIA
 *****************************************************************************/
 VOS_VOID CMMCA_REG_RcvMmaRegCnf(
     VOS_VOID                           *pMsg
 )
 {
     CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer = VOS_NULL_PTR;
     CMMCA_REG_CTX_STRU                 *pstRegCtx    = VOS_NULL_PTR;
     TAF_MMA_REG_CNF_STRU               *pstRegCnf    = VOS_NULL_PTR;
     VOS_UINT8                           ucOpid;
     CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
     CMMCA_RAT_SYS_INFO_STRU             stRatInfo;

    /* 解析消息的opid,根据opid查找缓存的请求消息 */
    pstRegCnf = (TAF_MMA_REG_CNF_STRU*)pMsg;
    ucOpid    = pstRegCnf->ucOpid;

    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaRegCnf: CMMCA_GetItemFromCmdBufferQueue fail!");
        return;
    }

    /* 增加请求消息异常判断，如果不是ID_CMMCA_MMC_RAT_PS_REG_REQ,则丢弃此cnf */
    usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo);

    if ((ID_CMMCA_MMC_RAT_PS_REG_REQ           != usCmdId)
     && (ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ != usCmdId))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaRegCnf: cmdId invalid!");
        return;
    }

    /* 保存最新的服务状态信息到上下文 */
    pstRegCtx = CMMCA_REG_GetCtxAddr();
    pstRegCtx->stPlmnId.Mcc     = pstRegCnf->stPlmnId.Mcc;
    pstRegCtx->stPlmnId.Mnc     = pstRegCnf->stPlmnId.Mnc;
    pstRegCtx->ulArfcn          = pstRegCnf->ulArfcn;
    pstRegCtx->enPrioClass      = pstRegCnf->enPrioClass;

    /* 回复ID_CMMCA_RAT_MMC_PS_REG_RSP/ID_CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP到CBPCA */
    /* 根据注册结果，更新CMMCA当前状态 */
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstRegCnf->enPrioClass);

    stRatInfo.ulMcc           = pstRegCnf->stPlmnId.Mcc;
    stRatInfo.ulMnc           = pstRegCnf->stPlmnId.Mnc;
    stRatInfo.usEarfcn        = (VOS_UINT16)pstRegCnf->ulArfcn;
    CMMCA_REG_SndRegRsp(pstRegCnf->enRslt, pstRegCnf->enLmmAttachRegStatus, usCmdId, &stRatInfo);

    /*回复ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND到CBPCA */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstRegCnf->enRslt)
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_AUTOMATIC, CMMCA_RAT_CPST_REGISTERED, &stRatInfo);
    }
    else
    {
        if (VOS_FALSE == pstRegCtx->ucPsSimValid)
        {
            CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_SUSPEND, CMMCA_RAT_CPST_SYSLOST, &stRatInfo);
        }
    }

    /* 释放opid,清空缓存 */
    CMMCA_DelItemInCmdBufferQueue(ucOpid);

     return;
 }

/*****************************************************************************
函 数 名  : CMMCA_REG_RcvMmaDetachCnf
功能描述  : 处理MMA模块的ID_TAF_MMA_DETACH_CNF消息
输入参数  : VOS_VOID *pMsg
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2014年1月24日
 作    者   : s00261364
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMmaDetachCnf(
    VOS_VOID                           *pMsg
)
{
    CMMCA_CMD_BUFFER_STRU              *pstCmdBuffer = VOS_NULL_PTR;
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;
    VOS_UINT8                           ucOpid;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;

    /* 解析消息的opid,根据opid查找缓存的请求消息 */
    ucOpid = ((TAF_MMA_DETACH_CNF_STRU*)pMsg)->ucOpid;

    pstCmdBuffer = CMMCA_GetItemFromCmdBufferQueue(ucOpid);
    if (VOS_NULL_PTR == pstCmdBuffer)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaDetachCnf: CMMCA_GetItemFromCmdBufferQueue fail!");
        return;
    }

    /* 增加请求消息异常判断，如果不是ID_CMMCA_MMC_RAT_NO_SERVICE_REQ/ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ/
        ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ,则丢弃此cnf */
    usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBuffer->pucMsgInfo);

    if ((ID_CMMCA_MMC_RAT_NO_SERVICE_REQ         != usCmdId)
     && (ID_CMMCA_MMC_RAT_DATACONNECTION_CMD_REQ != usCmdId)
     && (ID_CMMCA_MMC_RAT_BEARER_DETACH_REQ      != usCmdId))
    {

        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaDetachCnf:  cmdId invalid!");
        return;
    }

    /* 调用TAF_MMA_PowerSaveReq */
    PS_MEM_SET(&stPowerSavePara, 0, sizeof(TAF_MMA_POWER_SAVE_PARA_STRU));
    if (VOS_TRUE != TAF_MMA_PowerSaveReq(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpid, &stPowerSavePara))
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaDetachCnf: TAF_MMA_PowerSaveReq SEND fail!");

        /* 释放opid,清空缓存 */
        CMMCA_DelItemInCmdBufferQueue(ucOpid);
    }

    return;
}

/*****************************************************************************
函 数 名  : CMMCA_REG_RcvMmaSimStatusInd
功能描述  : 处理MMA模块的ID_TAF_MMA_SIM_STATUS_IND消息
输入参数  : VOS_VOID *pMsg
输出参数  : 无
返 回 值  : VOS_VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2014年1月24日
 作    者   : s00261364
 修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMmaSimStatusInd(
    VOS_VOID                           *pMsg
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx       = VOS_NULL_PTR;
    TAF_MMA_SIM_STATUS_IND_STRU        *pstSimStatusInd = VOS_NULL_PTR;

    /* 保存最新的服务状态信息到上下文 */
    pstSimStatusInd = (TAF_MMA_SIM_STATUS_IND_STRU*)pMsg;
    pstRegCtx = CMMCA_REG_GetCtxAddr();
    if (TAF_MMA_CARD_STATUS_AVAILABLE == pstSimStatusInd->enCardStatus)
    {
        pstRegCtx->ucPsSimValid     = VOS_TRUE;
        pstRegCtx->ucCsSimValid     = VOS_TRUE;
    }
    else
    {
        pstRegCtx->ucPsSimValid     = VOS_FALSE;
        pstRegCtx->ucCsSimValid     = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvMmaSysInfoInd
 功能描述  : 收到MMA的位置信息上报指示
 输入参数  :  pMsg:消息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月29日
    作    者   : s00246516
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  CMMCA_REG_RcvMmaSysInfoInd(
    VOS_VOID                           *pMsg
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx         = VOS_NULL_PTR;
    TAF_MMA_SYS_INFO_IND_STRU          *pstSysInfoInd     = VOS_NULL_PTR;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue = VOS_NULL_PTR;
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId;
    CMMCA_RAT_SYS_INFO_STRU             stRatInfo;
    VOS_UINT32                          i;

    /* 保存最新的位置信息到上下文 */
    pstSysInfoInd = (TAF_MMA_SYS_INFO_IND_STRU*)pMsg;

    pstRegCtx               = CMMCA_REG_GetCtxAddr();
    pstRegCtx->stPlmnId.Mcc = pstSysInfoInd->stPlmnId.Mcc;
    pstRegCtx->stPlmnId.Mnc = pstSysInfoInd->stPlmnId.Mnc;
    pstRegCtx->ulArfcn      = pstSysInfoInd->ulArfcn;

    /* 遍历队列, 如果当前存在有这5个消息对应的操作，不用报状态，返回 */
    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();
    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        if ((VOS_NULL_PTR != pstCmdBufferQueue[i].pucMsgInfo)
         && (CMMCA_OPID_INVILID_VALUE != pstCmdBufferQueue[i].ucOpId))
        {
            usCmdId = CMMCA_ConvertDoubleOctetStrToU16(pstCmdBufferQueue[i].pucMsgInfo);
            if ((ID_CMMCA_MMC_RAT_ACQ_REQ              == usCmdId)
             || (ID_CMMCA_MMC_RAT_PS_REG_REQ           == usCmdId)
             || (ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ == usCmdId)
             || (ID_CMMCA_MMC_RAT_POWERDOWN_REQ        == usCmdId)
             || (ID_CMMCA_MMC_RAT_NO_SERVICE_REQ       == usCmdId))
            {
                pstRegCtx->enPrioClass  = pstSysInfoInd->enPrioClass;

                return;
            }
        }
    }

    /* 如果当前正常服务且网络优先级发生了改变，上报ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND */
    PS_MEM_SET(&stRatInfo, 0, sizeof(CMMCA_RAT_SYS_INFO_STRU));

    stRatInfo.enPriorityClass = CMMCA_REG_ConvertTafPriToCmmcaPri(pstSysInfoInd->enPrioClass);

    stRatInfo.ulMcc           = pstSysInfoInd->stPlmnId.Mcc;
    stRatInfo.ulMnc           = pstSysInfoInd->stPlmnId.Mnc;
    stRatInfo.usEarfcn        = (VOS_UINT16)pstSysInfoInd->ulArfcn;

    if ((TAF_REPORT_SRVSTA_NORMAL_SERVICE == pstRegCtx->ucPsSrvSta)
     && (pstRegCtx->enPrioClass != pstSysInfoInd->enPrioClass))
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_PRI_CHG, CMMCA_RAT_CPST_REGISTERED, &stRatInfo);
    }

    pstRegCtx->enPrioClass  = pstSysInfoInd->enPrioClass;

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_RcvMmaMsg
 功能描述  : 处理MMA发来的消息
 输入参数  : struct MsgCB                     *pstEvt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月11日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_RcvMmaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulIndex;
    CMMCA_REG_MMA_EVT_FUNC              pMmaEvtFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstHeader  = VOS_NULL_PTR;  /* 定义消息头指针*/

    /* 获取消息头指针*/
    pstHeader = (MSG_HEADER_STRU *)pstMsg;

    /* 查表g_astCmmcaRegEvtFuncTbl */
    for (ulIndex = 0; ulIndex < g_ulCmmcaRegEvtFuncTblSize; ulIndex++)
    {
        if (pstHeader->ulMsgName == g_astCmmcaRegEvtFuncTbl[ulIndex].ulMsgId)
        {
            pMmaEvtFunc = g_astCmmcaRegEvtFuncTbl[ulIndex].pMmaEvtFunc;

            break;
        }
    }

    if (VOS_NULL_PTR == pMmaEvtFunc)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_RcvMmaMsg: Not find msg proc func");
        return;
    }
    else
    {
        pMmaEvtFunc(pstMsg);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndNtwIndRpt
 功能描述  : 发送ntw消息根据MMA上报的服务指示消息
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年1月24日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndNtwIndRpt(
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo,
    TAF_MMA_SERVICE_STATUS_IND_STRU    *pstServStatusInd
)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx         = VOS_NULL_PTR;

    /* 获取最新的服务状态信息上下文 */
    pstRegCtx               = CMMCA_REG_GetCtxAddr();

    /* 判断服务状态是否发生变化，如果变化 */
    /* 最新服务状态为卡无效，上报RAT_SUSPEND */
    if ((VOS_TRUE == pstRegCtx->ucPsSimValid)
     && (VOS_FALSE == pstServStatusInd->ucPsSimValid))
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_SUSPEND, CMMCA_RAT_CPST_SYSLOST, pstRatInfo);

        return;
    }

    /* 最新服务状态为无服务或限制服务，上报RAT_SYSLOST */
    if ((TAF_REPORT_SRVSTA_NORMAL_SERVICE == pstRegCtx->ucPsSrvSta)
     && (TAF_REPORT_SRVSTA_NORMAL_SERVICE != pstServStatusInd->PsSrvSta))
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_SYSLOST, CMMCA_RAT_CPST_SYSLOST, pstRatInfo);

        return;
    }

    /* 最新服务状态为正常服务，上报RAT_RECOVERY */
    if ((TAF_REPORT_SRVSTA_NORMAL_SERVICE != pstRegCtx->ucPsSrvSta)
     && (TAF_REPORT_SRVSTA_NORMAL_SERVICE == pstServStatusInd->PsSrvSta))
    {
        CMMCA_REG_SndNtwStChgInd(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_NOTIFY_CAUSE_RECOVERY, CMMCA_RAT_CPST_REGISTERED, pstRatInfo);
    }

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndPowerUpRsp
 功能描述  : 发送开机请求结果ID_CMMCA_RAT_MMC_POWERUP_RSP
 输入参数  : CMMCA_RAT_MMC_RAT_ID_ENUM_UINT8                         enRatId,
             CMMCA_RAT_POWERUP_RSP_RESULT_ENUM_UINT8                 enResult
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndPowerUpRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_RAT_POWERUP_RSP_RESULT_ENUM_UINT8                 enResult
)
{
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;

    /* 构造 CMMCA_RAT_MMC_RAT_MODE_RSP_STRU */
    CMMCA_RAT_MMC_POWERUP_RSP_STRU      stPowerUpRsp;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_POWERUP_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndPowerUpRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* 调用CMMCA_PackBearDiscRsp函数打包发送消息 */
    stPowerUpRsp.enRatId  = enRatId;
    stPowerUpRsp.enResult = enResult;

    ulRslt = CMMCA_PackPowerUpRsp(&stPowerUpRsp, CMMCA_CMD_RAT_POWERUP_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);
        CMMCA_ERROR_LOG("CMMCA_REG_SndPowerUpRsp:CMMCA_PackPowerUpRsp fail");

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_POWERUP_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndPowerDownRsp
 功能描述  : 发送模式请求结果ID_CMMCA_RAT_MMC_POWERDOWN_RSP
 输入参数  : CMMCA_RAT_MMC_RAT_ID_ENUM_UINT8     enRatId,
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndPowerDownRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8     enRatId
)
{
    /* 构造 CMMCA_RAT_MMC_RAT_MODE_RSP_STRU */
    CMMCA_RAT_MMC_POWERDOWN_RSP_STRU    stPowerDownRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_POWERDOWN_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndModeRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* 调用CMMCA_PackPowerDownRsp函数打包发送消息 */
    stPowerDownRsp.enRatId = enRatId;
    ulRslt = CMMCA_PackPowerDownRsp(&stPowerDownRsp, CMMCA_CMD_RAT_POWERDOWN_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_POWERDOWN_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndModeRsp
 功能描述  : 发送模式请求结果ID_CMMCA_RAT_MMC_RAT_MODE_RSP
 输入参数  : CMMCA_RAT_MMC_RAT_ID_ENUM_UINT8     enRatId,
             CMMCA_RAT_MMC_RESULT_ENUM_UINT8     enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndModeRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_MMC_MODE_RSP_RESULT_ENUM_UINT8                    enResult
)
{
    CMMCA_RAT_MMC_RAT_MODE_RSP_STRU     stModeCnf;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_MODE_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndModeRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* 构造 CMMCA_RAT_MMC_RAT_MODE_RSP_STRU */
    stModeCnf.enRatId  = enRatId;
    stModeCnf.enResult = enResult;

    /* 调用CMMCA_PackModeRsp函数打包发送消息 */
    ulRslt = CMMCA_PackModeRsp(&stModeCnf, CMMCA_CMD_RAT_MODE_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_MODE_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndAcqRsp
 功能描述  : 发送模式请求结果ID_CMMCA_RAT_MMC_ACQ_RSP
 输入参数  : CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
             CMMCA_RAT_ACQ_RESULT_ENUM_UINT8     enRslt,
            S CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndAcqRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_ACQ_RESULT_ENUM_UINT8     enRslt,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
)
{

    CMMCA_RAT_MMC_ACQ_RSP_STRU          stAcqCnf;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_ACQ_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndAcqRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* 构造 CMMCA_RAT_MMC_ACQ_RSP_STRU */
    stAcqCnf.enRatId                                  = enRatId;
    stAcqCnf.enResult                                 = enRslt;
    stAcqCnf.stRatSysInfo.ulMcc                       = pstRatInfo->ulMcc;
    stAcqCnf.stRatSysInfo.ulMnc                       = pstRatInfo->ulMnc;
    stAcqCnf.stRatSysInfo.enPriorityClass             = pstRatInfo->enPriorityClass;
    stAcqCnf.stRatSysInfo.stEutran.usEarfcn           = pstRatInfo->usEarfcn;

    if (CMMCA_RAT_ACQ_RESULT_ACQUIRED == enRslt)
    {
        stAcqCnf.stRatSysInfo.ucRatInfoValid          = VOS_TRUE;
    }
    else
    {
        stAcqCnf.stRatSysInfo.ucRatInfoValid          = VOS_FALSE;
    }

    /* 调用CMMCA_PackModeRsp函数打包发送消息 */
    ulRslt = CMMCA_PackAcqRsp(&stAcqCnf, CMMCA_CMD_RAT_ACQ_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_ACQ_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndMccSearchRsp
 功能描述  : 发送ID_CMMCA_RAT_MMC_MCC_SEARCH_RSP
 输入参数  : CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
             CMMCA_RAT_MMC_RESULT_ENUM_UINT8     enRslt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndMccSearchRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_MMC_RAT_SYS_INFO_STRU    *pstSysInfo
)
{

    CMMCA_RAT_MMC_MCC_SEARCH_RSP_STRU   stMccSearchRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_SEARCH_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndMccSearchRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* 构造 CMMCA_RAT_MMC_ACQ_RSP_STRU */
    stMccSearchRsp.enRatId        = enRatId;
    stMccSearchRsp.ulMcc          = pstSysInfo->ulMcc;
    stMccSearchRsp.ulMnc          = pstSysInfo->ulMnc;
    stMccSearchRsp.ucRatInfoValid = VOS_TRUE;

    stMccSearchRsp.stEutran.usEarfcn = pstSysInfo->stEutran.usEarfcn;
    stMccSearchRsp.stEutran.ulPlmn   = pstSysInfo->stEutran.ulPlmn;

    /* 调用CMMCA_PackMccSearchRsp函数打包发送消息 */
    ulRslt = CMMCA_PackMccSearchRsp(&stMccSearchRsp, CMMCA_CMD_RAT_SEARCH_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_SEARCH_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndRegRsp
 功能描述  : 发送ID_CMMCA_RAT_MMC_PS_REG_RSP/ID_CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP
 输入参数  : TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt
             CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数
  2.日    期   : 2015年4月22日
    作    者   : wx270776
    修改内容   : 增加VIA的消息增加CL ATTACH注册状态
*****************************************************************************/
VOS_VOID CMMCA_REG_SndRegRsp(
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_MMA_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachRegStatus,
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    usCmdId,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
)
{

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == enRslt)
    {
        if (ID_CMMCA_MMC_RAT_PS_REG_REQ == usCmdId)
        {
            CMMCA_REG_SndPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_REG_RESULT_REGISTERED, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
        else
        {
            CMMCA_REG_SndCellInfoPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_MMC_STATUS_SUCCESS, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }

    }
    /* 驻留网络，注册失败 */
    else if (TAF_MMA_APP_OPER_RESULT_FAILURE == enRslt)
    {
        if (ID_CMMCA_MMC_RAT_PS_REG_REQ == usCmdId)
        {
            CMMCA_REG_SndPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_REG_RESULT_ACQUIRED, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
        else
        {
            CMMCA_REG_SndCellInfoPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_MMC_STATUS_PS_REG_FAIL, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
    }
    /* 搜网失败 */
    else if (TAF_MMA_APP_OPER_RESULT_ACQUIRED_FAIL == enRslt)
    {
        if (ID_CMMCA_MMC_RAT_PS_REG_REQ == usCmdId)
        {
            CMMCA_REG_SndPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_REG_RESULT_ACQFAILED, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
        else
        {
            CMMCA_REG_SndCellInfoPsRegRsp(CMMCA_MMC_RAT_ID_EUTRAN, CMMCA_RAT_MMC_STATUS_ACQ_FAIL, CMMCA_ConvertLmmAttachRegStatus(enLmmAttachRegStatus), pstRatInfo);
        }
    }
    else
    {

        if (ID_CMMCA_MMC_RAT_PS_REG_REQ == usCmdId)
        {
            CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);
        }

        else
        {
            CMMCA_REG_SndMmcRejInd(CMMCA_MMC_RAT_ID_EUTRAN, ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ, CMMCA_RAT_CMD_REJ_REASON_NO_REASON);
        }
    }


    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndPsRegRsp
 功能描述  : 发送ID_CMMCA_RAT_MMC_PS_REG_RSP
 输入参数  : CMMCA_MMC_RAT_ID_ENUM_UINT8             enRatId,
             CMMCA_RAT_REG_RESULT_ENUM_UINT8         enResult
             CMMCA_RAT_SYS_INFO_STRU                *pstRatInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数
  2.日    期   : 2015年4月22日
    作    者   : wx270776
    修改内容   : 增加VIA的消息增加CL ATTACH注册状态
*****************************************************************************/
VOS_VOID CMMCA_REG_SndPsRegRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_RAT_REG_RESULT_ENUM_UINT8                         enResult,
    CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8                    enLmmAttachRegStatus,
    CMMCA_RAT_SYS_INFO_STRU                                *pstRatInfo
)
{

    CMMCA_RAT_MMC_PS_REG_RSP_STRU       stPsRegRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_PS_REG_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndPsRegRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* 构造 CMMCA_RAT_MMC_PS_REG_RSP_STRU */
    stPsRegRsp.enRatId                                  = enRatId;
    stPsRegRsp.enResult                                 = enResult;
    stPsRegRsp.enLmmAttachRegStatus                     = enLmmAttachRegStatus;
    stPsRegRsp.stRatSysInfo.ulMcc                       = pstRatInfo->ulMcc;
    stPsRegRsp.stRatSysInfo.ulMnc                       = pstRatInfo->ulMnc;
    stPsRegRsp.stRatSysInfo.enPriorityClass             = pstRatInfo->enPriorityClass;
    if ((CMMCA_RAT_REG_RESULT_REGISTERED == enResult)
     || (CMMCA_RAT_REG_RESULT_ACQUIRED   == enResult))
    {
        stPsRegRsp.stRatSysInfo.ucRatInfoValid          = VOS_TRUE;
    }
    else
    {
        stPsRegRsp.stRatSysInfo.ucRatInfoValid          = VOS_FALSE;
    }

    stPsRegRsp.stRatSysInfo.stEutran.usEarfcn           = pstRatInfo->usEarfcn;

    /* 调用CMMCA_PackModeRsp函数打包发送消息 */
    ulRslt = CMMCA_PackPsRegRsp(&stPsRegRsp, CMMCA_CMD_RAT_PS_REG_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_PS_REG_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndCellInfoPsRegRsp
 功能描述  : 发送ID_CMMCA_MMC_RAT_CELL_INFO_PS_REG_REQ
 输入参数  : CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
             CMMCA_RAT_REG_RESULT_ENUM_UINT8                         enResult,
             CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8                    enLmmAttachRegStatus,
             CMMCA_RAT_SYS_INFO_STRU                                *pstRatInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数
  2.日    期   : 2015年4月22日
    作    者   : wx270776
    修改内容   : 增加VIA的消息增加CL ATTACH注册状态
*****************************************************************************/
VOS_VOID CMMCA_REG_SndCellInfoPsRegRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_RAT_MMC_STATUS_ENUM_UINT8                         enResult,
    CMMCA_RAT_ATTACH_CL_REG_STATUS_ENUM8                    enLmmAttachRegStatus,
    CMMCA_RAT_SYS_INFO_STRU                                *pstRatInfo
)
{

    CMMCA_RAT_MMC_CELL_INFO_PS_REG_RSP_STRU                 stCellInfoPsRegRsp;
    VOS_UINT8                                              *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_CELL_INFO_PS_REG_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndCellInfoPsRegRsp: PS_MEM_ALLOC fail!");
        return;
    }
    /* 构造 CMMCA_RAT_MMC_PS_REG_RSP_STRU */
    stCellInfoPsRegRsp.enRatId                                               = enRatId;
    stCellInfoPsRegRsp.stIratRegRsp.enResult                                 = enResult;
    stCellInfoPsRegRsp.stIratRegRsp.enLmAttachRegStatus                      = enLmmAttachRegStatus;
    stCellInfoPsRegRsp.stIratRegRsp.enTargetSystemType                       = CMMCA_RAT_SYSTEM_TYPE_EUTRAN;
    stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.ulMcc                       = pstRatInfo->ulMcc;
    stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.ulMnc                       = pstRatInfo->ulMnc;
    stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.enPriorityClass             = pstRatInfo->enPriorityClass;
    if ((CMMCA_RAT_MMC_STATUS_SUCCESS == enResult)
     || (CMMCA_RAT_MMC_STATUS_PS_REG_FAIL == enResult))
    {
         stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.ucRatInfoValid         = VOS_TRUE;
    }
    else
    {
         stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.ucRatInfoValid         = VOS_FALSE;
    }
    stCellInfoPsRegRsp.stIratRegRsp.stRatSysInfo.stEutran.usEarfcn           = pstRatInfo->usEarfcn;

    /* 调用CMMCA_PackCellInfoPsRegRsp函数打包发送消息 */
    ulRslt = CMMCA_PackCellInfoPsRegRsp(&stCellInfoPsRegRsp, CMMCA_CMD_RAT_CELL_INFO_PS_REG_RSP_LEN, pucCmdData);
    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_CELL_INFO_PS_REG_RSP_LEN);
    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndNoServiceRsp
 功能描述  : 发送ID_CMMCA_RAT_MMC_NO_SERVICE_RSP
 输入参数  : CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
             VOS_UINT8                           ucStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndNoServiceRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    VOS_UINT8                           ucStatus
)
{

    CMMCA_RAT_MMC_NO_SERVICE_RSP_STRU   stNoServRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_NO_SERVICE_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndNoServiceRsp: PS_MEM_ALLOC fail!");
        return;
    }
    /* 构造 CMMCA_RAT_MMC_NO_SERVICE_RSP_STRU */
    stNoServRsp.enRatId  = enRatId;
    stNoServRsp.ucStatus = ucStatus;

    /* 调用CMMCA_PackNoServiceRsp函数打包发送消息 */
    ulRslt = CMMCA_PackNoServiceRsp(&stNoServRsp, CMMCA_CMD_RAT_NO_SERVICE_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_NO_SERVICE_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndNtwStChgInd
 功能描述  : 发送ID_CMMCA_RAT_MMC_NWT_ST_CHG_IND
 输入参数  : CMMCA_MMC_RAT_ID_ENUM_UINT8           enRatId,
             CMMCA_RAT_NOTIFY_CAUSE_ENUM_UINT8     enCause,
             CMMCA_RAT_CPST_ENUM_UINT8             enStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndNtwStChgInd(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    CMMCA_RAT_NOTIFY_CAUSE_ENUM_UINT8   enCause,
    CMMCA_RAT_CPST_ENUM_UINT8           enStatus,
    CMMCA_RAT_SYS_INFO_STRU            *pstRatInfo
)
{

    CMMCA_RAT_MMC_NTW_ST_CHG_IND_STRU   stNtwStChgInd;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_NTW_ST_CHG_IND_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndNtwStChgInd: PS_MEM_ALLOC fail!");
        return;
    }

    /* 初始化stNtwStChgInd */
    PS_MEM_SET(&stNtwStChgInd, 0, sizeof(CMMCA_RAT_MMC_NTW_ST_CHG_IND_STRU));

    /* 构造 CMMCA_RAT_MMC_NTW_ST_CHG_IND_STRU */
    stNtwStChgInd.enRatId                     = enRatId;
    stNtwStChgInd.enStatus                    = enStatus;
    stNtwStChgInd.enCause                     = enCause;
    stNtwStChgInd.enSysPri                    = pstRatInfo->enPriorityClass;
    if (CMMCA_RAT_CPST_REGISTERED == enStatus)
    {
        stNtwStChgInd.enPsType                = CMMCA_RAT_PS_TYPE_LTE;
    }
    else
    {
        stNtwStChgInd.enPsType                = CMMCA_RAT_PS_TYPE_NO_PS;
    }
    stNtwStChgInd.ulMcc                       = pstRatInfo->ulMcc;
    stNtwStChgInd.ulMnc                       = pstRatInfo->ulMnc;
    stNtwStChgInd.stEutran.usEarfcn           = pstRatInfo->usEarfcn;

    /* 调用CMMCA_PackModeRsp函数打包发送消息 */
    ulRslt = CMMCA_PackNtwStateChangeInd(&stNtwStChgInd, CMMCA_CMD_RAT_NTW_ST_CHG_IND_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);
        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_NTW_ST_CHG_IND_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);
        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndMmcRejInd
 功能描述  : 发送拒绝指示消息ID_CMMCA_RAT_MMC_CMD_REJ_IND
 输入参数  : CMMCA_RAT_MMC_RAT_ID_ENUM_UINT8     enSourceRat,
             CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enApiID
             CMMCA_RAT_CMD_REJ_REASON_ENUM_UINT8 enCause
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndMmcRejInd(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enSourceRat,
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enApiID,
    CMMCA_RAT_CMD_REJ_REASON_ENUM_UINT8 enCause
)
{
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    CMMCA_MMC_CMD_REJ_IND_STRU          stRegInd;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_REJ_IND_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndMmcRejInd: PS_MEM_ALLOC fail!");
        return;
    }

    /* 构造 CMMCA_MMC_CMD_REJ_IND_STRU */
    stRegInd.enSourceRat  = enSourceRat;
    stRegInd.enApiID      = enApiID;
    stRegInd.enCause      = enCause;

    /* 调用CMMCA_PackModeRsp函数打包发送消息 */
    ulRslt = CMMCA_PackCmdRejInd(&stRegInd, CMMCA_CMD_RAT_REJ_IND_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);
        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_REJ_IND_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_SndPktDataCmdRsp
 功能描述  : 发送ID_CMMCA_RAT_MMC_DATACONNECTION_CMD_RSP
 输入参数  : CMMCA_MMC_RAT_ID_ENUM_UINT8                enRatId,
             CMMCA_IRAT_DATA_CONNECT_CMD_RSP_ENUM_UINT8 enCmdRsp
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月12日
    作    者   : s00261364
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID CMMCA_REG_SndPktDataCmdRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8                             enRatId,
    CMMCA_IRAT_DATA_CONNECT_CMD_RSP_ENUM_UINT8              enCmdRsp
)
{

    CMMCA_RAT_MMC_PKT_DATA_CMD_RSP_STRU stPktDataCmdRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_PKT_DATA_CMD_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_REG_SndPktDataCmdRsp: PS_MEM_ALLOC fail!");
        return;
    }
    /* 构造 CMMCA_RAT_MMC_PKT_DATA_CMD_RSP_STRU */
    stPktDataCmdRsp.enRatId  = enRatId;
    stPktDataCmdRsp.enCmdRsp = enCmdRsp;

    /* 调用CMMCA_PackPktDataCmdRsp函数打包发送消息 */
    ulRslt = CMMCA_PackPktDataCmdRsp(&stPktDataCmdRsp, CMMCA_CMD_RAT_PKT_DATA_CMD_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_PKT_DATA_CMD_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_PKT_SndBearDetachRsp
 功能描述  : 发送ID_CMMCA_RAT_MMC_BEARER_DETACH_RSP
 输入参数  : CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
             VOS_UINT8                           ucStatus
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年7月7日
    作    者   : g00261581
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID CMMCA_PKT_SndBearDetachRsp(
    CMMCA_MMC_RAT_ID_ENUM_UINT8         enRatId,
    VOS_UINT8                           ucStatus
)
{
    CMMCA_RAT_MMC_BEAR_DETACH_RSP_STRU  stBearDetachRsp;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_RAT_BEAR_DETACH_RSP_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        CMMCA_ERROR_LOG("CMMCA_PKT_SndBearDetachRsp: PS_MEM_ALLOC fail!");
        return;
    }

    /* 构造 CMMCA_RAT_MMC_BEARER_DETACH_RSP_STRU */
    stBearDetachRsp.enRatId  = enRatId;
    stBearDetachRsp.ucStatus = ucStatus;

    /* 调用CMMCA_PackBearDetachRsp函数打包发送消息 */
    ulRslt = CMMCA_PackBearDetachRsp(&stBearDetachRsp, CMMCA_CMD_RAT_BEAR_DETACH_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 调用CBPCA_SndDataToCbpca函数发数据给CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_RAT_BEAR_DETACH_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* 消息发送结束，释放内存 */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}

/*****************************************************************************
 函 数 名  : CMMCA_REG_ConvertTafPriToCmmcaPri
 功能描述  : 将TAF定义的PRI转换为CMMCA的PRI
 输入参数  : TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8       enTafPriClass
 输出参数  : 无
 返 回 值  : CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年2月24日
    作    者   : l60609
    修改内容   : 新生成函数

*****************************************************************************/
CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8 CMMCA_REG_ConvertTafPriToCmmcaPri(
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8      enTafPriClass
)
{
    CMMCA_RAT_GMSS_PRIORITY_CLASS_ENUM_UINT8    enCmmcaPriClass;

    if (TAF_MMA_PLMN_PRIORITY_HOME == enTafPriClass)
    {
        enCmmcaPriClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_HOME;
    }
    else if (TAF_MMA_PLMN_PRIORITY_PREF == enTafPriClass)
    {
        enCmmcaPriClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_PREF;
    }
    else if (TAF_MMA_PLMN_PRIORITY_ANY == enTafPriClass)
    {
        enCmmcaPriClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_ANY;
    }
    else
    {
        enCmmcaPriClass = CMMCA_RAT_GMSS_PRIORITY_CLASS_UNAVL;
    }

    return enCmmcaPriClass;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

