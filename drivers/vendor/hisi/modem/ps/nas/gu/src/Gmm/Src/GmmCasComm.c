

/*****************************************************************************
   1 头文件包含
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasSuspend.h"
#include "GmmCasSend.h"
#include "GmmCasComm.h"
#include "GmmCasMain.h"
#include "GmmCasGsm.h"
#include "GmmMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasCommDef.h"
#include "NasGmmProcLResult.h"
#endif
#include "NasUsimmApi.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASCOMM_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/


/*****************************************************************************
   2 全局变量定义
*****************************************************************************/


/*lint -save -e958 */

/*****************************************************************************
   3 函数实现
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM CAS 通用过程处理   -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_IsCasGsmMode
 Description    : 判断当前接入模式是否GSM网络
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   : GMM_TRUE       GSM网络接入
                  GMM_FALSE      非GSM网络接入
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_IsCasGsmMode (VOS_VOID)
{
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return GMM_TRUE;
    }
    else
    {
        return GMM_FALSE;
    }
}

/*****************************************************************************
 Prototype      : GMM_IsLastRand
 Description    : 判断新存的RAND和上次记录值是否相等
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_IsLastRand(VOS_VOID)
{
    VOS_UINT8   i;
    VOS_UINT8   ucRel = GMM_TRUE;

    for (i=0; i<GMM_MAX_SIZE_RAND; i++)
    {
        if (g_GmmAuthenCtrl.aucRandSav[i]
           != g_GmmAuthenCtrl.aucRand[i])
        {
            ucRel = GMM_FALSE;
            break;
        }
    }

    return ucRel;
}


VOS_VOID GMM_InitCasGlobalVariable (VOS_VOID)
{
    /* GMM CAS全局结构变量清零 */
    Gmm_MemSet(&gstGmmCasGlobalCtrl, 0, sizeof(GMM_CAS_CTRL_STRU));
    Gmm_MemSet(&gstGmmCasMsgBuf,     0, sizeof(GMM_CAS_MSG_BUFFER_STRU));
    Gmm_MemSet(&gstGmmSuspendCtrl,   0, sizeof(GMM_SUSPEND_CTRL_STRU));


    /* 设定初始值 */
    gstGmmCasGlobalCtrl.ucGmmCasState       = GMM_CAS_WCDMA_AS;
    gstGmmCasGlobalCtrl.ucGmmCasPreState    = GMM_CAS_WCDMA_AS;
    gstGmmCasGlobalCtrl.GmmSrvState         = GMM_IU_PMM_DETACHED;
    gstGmmCasGlobalCtrl.ucBufMsgResFlg      = GMM_FALSE;             /* 标记没有需要恢复的挂起消息 */
    gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg  = GMM_FALSE;             /*标记可协商ready timer*/
    gstGmmCasGlobalCtrl.ucRauCmpFlg         = GMM_FALSE;             /*标记不能发送RAU CMP消息*/
    gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = GMM_FALSE;

    gstGmmCasGlobalCtrl.ucRabmResumeFlg     = GMM_TRUE;              /*标记RABM RAU更新已完成*/
    gstGmmCasGlobalCtrl.ulReadyTimerValue   = 44000;                 /* 44 s*/
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg  = VOS_FALSE;
    /* 初始化系统TLLI值 */
    gstGmmCasGlobalCtrl.ulTLLI              = 0xffffffff;            /* 无效TLLI值 */
    gstGmmCasGlobalCtrl.ulOldTLLI           = 0xffffffff;            /* 无效TLLI值 */
    gstGmmCasGlobalCtrl.ucflgTLLI           = GMM_INVALID_TLLI;      /* 置TLLI无效标志 */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg     = GMM_FALSE;             /* 未完成TLLI指配 */
    gstGmmCasGlobalCtrl.enRaPrioLevFosSms   = GMM_RA_PRIO_LEV_1;

    g_GmmGlobalCtrl.ulGmmAttachFlg          = GMM_FALSE;

    gstGmmSuspendCtrl.ucSuspendCause        = MMC_SUSPEND_CAUSE_BUTT;

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    return;
}


VOS_VOID GMM_CasRcvUsimCnfUmtsSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    NAS_MSG_STRU *pNasMsg;                                  /* 定义指向NAS消息的指针*/

    NAS_MML_SetSimPsSecurityCksn(g_GmmAuthenCtrl.ucCksnSav);            /* 暂存消息中的CKSN赋给全局变量中的CKSN                         */

    /* 记录CK值到全局变量中, 跳过首个长度字节 */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityUmtsCk(),
            &(pAuthCnf->aucCK[1]), 16 );                          /* 更新全局变量中的Ck*/

    /* 记录IK值到全局变量中，跳过首个长度字节 */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityUmtsIk(),
            &(pAuthCnf->aucIK[1]), 16 );                          /* 更新全局变量中的Ik*/

    /* 计算保存GSM Kc */
    if (0 == pAuthCnf->aucGsmKc[0]) /* check Kc length */
    {
        NAS_MML_SecContext3GTO2G(NAS_MML_GetSimPsSecurityUmtsIk(),
                                 NAS_MML_GetSimPsSecurityUmtsCk(),
                                 NAS_MML_GetSimPsSecurityGsmKc());
    }
    else
    {
        /* skip the first length byte */
        Gmm_MemCpy(NAS_MML_GetSimPsSecurityGsmKc(),
                &(pAuthCnf->aucGsmKc[1]), 8 );                        /* 更新全局变量中的GSM Kc*/
    }


    /* 保存CK,IK,Kc值到SIM中 */
    if (MMC_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);    /* 更新SIM中的CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }

    /* 记录RES */
    GMM_SaveAuthenResult(pAuthCnf);

    /* 通知MMC实体鉴权结果信息 */
    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY); /* 发送RRMM_NAS_INFO_CHANGE_REQ*/

    /* 修改鉴权过程的标志量 */
    Gmm_Start_StopedRetransmissionTimer();                  /* 存在被停止的retransmission timer将其启动 */
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                  /* GMM Authentication attempt counter清0    */
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

    /* 填写鉴权回应消息 */
    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
            GMM_AUTH_AND_CIPH_RES_NEEDED);                  /* 发送A&C RESPONSE*/

    /* 发送GMM消息 */
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    /* RAND值比较更新 */
    GMM_UpdateAuthenCtrlFlg();

    return;
}


VOS_VOID GMM_CasRcvUsimCnfGsmSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    NAS_MSG_STRU *pNasMsg;                                  /* 定义指向NAS消息的指针*/

    NAS_MML_SetSimPsSecurityCksn(g_GmmAuthenCtrl.ucCksnSav);            /* 暂存消息中的CKSN赋给全局变量中的CKSN                                 */


    /* 记录Kc值到全局变量中, 跳过首个长度字节COPY */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityGsmKc(),
            &(pAuthCnf->aucGsmKc[1]), 8 );                        /* 更新全局变量中的GSM Kc*/


    /* 计算IK,CK */
    NAS_MML_SecContext2GTO3G(NAS_MML_GetSimPsSecurityUmtsIk(),
                             NAS_MML_GetSimPsSecurityUmtsCk(),
                             NAS_MML_GetSimPsSecurityGsmKc());

    /*Gmm_MemCpy(g_GmmGlobalCtrl.PsSecutityInfo.aucCk,
            pAuthCnf->aucCK, 16 );*/                          /* 更新全局变量中的Ck*/

    /*Gmm_MemCpy(g_GmmGlobalCtrl.PsSecutityInfo.aucIk,
            pAuthCnf->aucIK, 16 );*/                          /* 更新全局变量中的Ik*/

    /* 保存Kc,IK,CK值到SIM中 */
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);    /* 更新SIM中的CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* 更新SIM中的GSM CKSN,Kc*/
    }

    /* 记录SRES */
    GMM_SaveAuthenResult(pAuthCnf);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY); /* 发送RRMM_NAS_INFO_CHANGE_REQ*/

    /* 填写鉴权回应消息 */
    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
            GMM_AUTH_AND_CIPH_RES_NEEDED);                  /* 发送A&C RESPONSE*/

    /* 发送GMM消息 */
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

    /* RAND值比较更新 */
    GMM_UpdateAuthenCtrlFlg();

    return;
}


VOS_VOID GMM_CasRcvUsimCnfFailUmts(
    USIMM_TELECOM_AUTH_CNF_STRU        *pAuthCnf,
    USIMM_AUTH_RESULT_ENUM_UINT32       enResult
)
{
    NAS_MSG_STRU    *pNasMsg;

    g_GmmAuthenCtrl.ucAuthenAttmptCnt++;                    /* GMM Authentication attempt counter＋1    */

    /* 判断鉴权尝试次数 */
    if (GMM_AUTHEN_ATTEMPT_MAX_CNT == g_GmmAuthenCtrl.ucAuthenAttmptCnt)
    {/* 超过最大次数 */

        if (USIMM_AUTH_MAC_FAILURE == enResult)
        {
            /*保存鉴权失败的错误码*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_MAC_FAILURE);
        }
        else
        {
            /*保存鉴权失败的错误码*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_SYNCH_FAILURE);
        }

        /* 鉴权失败处理，结束返回 */
        Gmm_AuCntFail();
        return;
    }

    /* Failure 处理过程 */
    if (USIMM_AUTH_MAC_FAILURE == enResult)
    {/* MAC failure */
        Gmm_Au_MacAutnWrong(NAS_MML_REG_FAIL_CAUSE_MAC_FAILURE);
    }
    else
    {/* SQN failure */
        /* AUTHENTICATION AND CIPHERING FAILURE作成 */
        pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(
                            NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE,
                            pAuthCnf->aucAuts[0],
                            &(pAuthCnf->aucAuts[1]));

        /* 调用发送函数 */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* 停止T3316                                */

        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                            /* 将"RES存在标志 "置为0                    */
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                            /* 将"RAND存在标志 "置为0                   */

        if (GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL == g_GmmAuthenCtrl.ucLastFailCause)
        {/* 上次鉴权失败原因值是同步失败 */
            g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;          /* GMM Authentication attempt counter清0 */
            g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

            Gmm_TimerStop(GMM_TIMER_T3320);                 /* 停T3320 */

            NAS_GMM_SndGasGprsAuthFailNotifyReq();

            Gmm_SndRrmmRelReq(RRC_CELL_BARRED);             /* 发送RRMM_ABORT_REQ(RRC connection) */

            Gmm_Start_StopedRetransmissionTimer();          /* 存在被停止的retransmission timer将其启动 */
        }
        else
        {/* 上次鉴权失败原因值不是同步失败 */
            g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL;
            Gmm_TimerStop(GMM_TIMER_T3318);                 /* 停T3318(如果在运行) */
            Gmm_TimerStart(GMM_TIMER_T3320);                /* 启T3320 */
            Gmm_Stop_RetransmissionTimer();                 /* 停止正在运行的retransmission timer */
        }
    }
    return;
}


VOS_VOID GMM_CasRcvUsimCnfFailGsm(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    /*NAS_MSG_STRU    *pNasMsg;*/

    GMM_LOG_WARN("GSM authentication failure for unacceptable reason by MS!");
    /* 直接发送鉴权回应消息到网络 */
    /*pNasMsg = GMM_MakeAuthenAndCipherResponseMsgGsm
                (GMM_AUTH_AND_CIPH_RES_UNNEEDED);*/
    /*pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(*/
    /*                                    NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR,*/
    /*                                    0,*/
    /*                                    VOS_NULL_PTR);*/
    /* 发送GMM消息 */
    /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);*/

    return;
}

/*****************************************************************************
 Prototype      : GMM_ExecLlgmmStatusIndCause
 Description    : 分析处理LL_GMM_STATUS_IND_MSG消息中的原因值
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_ExecLlgmmStatusIndCause(VOS_UINT16 usCause)
{
    switch (usCause)
    {
        case LL_GMM_STA_CAUSE_UNSOLICITED_UA_RSP:           /* unsolicited UA response */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_UNSOLICITED_DM_RSP:           /* unsolicited DM response */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_SABM_N200:            /* SABM命令重发N200次 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_DISC_N200:            /* DISC命令重发N200次 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_XID_CMD_N200:         /* XID命令重复N200次 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_INQUIRY_PEER_BUSY_N200:       /* 查询对方是否处于忙状态超过N200次 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_LLC_INIT_RE_EST:              /* LLC发起ABM重建 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_PEER_INIT_RE_EST:             /* 对端发起ABM重建 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_FRAME_REJ_CONDITION:          /* 检测到帧拒绝条件 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RECV_FRMR_RSP:                /* 接收到FRMR响应 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_GMM_ASSIGN_FAIL:              /* TLLI指配失败 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC ASSIGN command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_TRIGGER_FAIL:             /* LLC帧发送触发请求失败 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC TRIGGER command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_SUSPEND_FAIL:             /* LLC挂起失败 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC SUSPEND command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_RESUME_FAIL:              /* LLC恢复失败 */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC RESUME command failed!");
            break;

        default :
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status alert undefined!");
            break;
    }

    return;
}


VOS_UINT32 GMM_SaveGsmSysInfoIndMsgPara(MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo)
{
    GMM_RAI_STRU                *pRaiTemp  = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod  = g_GmmGlobalCtrl.ucNetMod;
    MMCGMM_GSM_SYS_INFO_IND_ST  *ptr;
    VOS_UINT8                   *pucRaiChgFlg;
    VOS_UINT16                   usCellIdNew;
    VOS_UINT8                    ucCsAttachAllow;

    GMM_RAI_STRU                 stAttempUpdateRaiInfo;
    GMM_RAI_STRU                 stOldRai;
    NAS_MML_RAI_STRU            *pstAttemptUpdateRaiInfo = VOS_NULL_PTR;

    gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg         = GMM_FALSE;
    gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg         = GMM_FALSE;
    gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg   = GMM_FALSE;

    pucRaiChgFlg = &gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));

    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "GMM_SaveGsmSysInfoIndMsgPara:ERROR: MALLOC FAIL!");
        return GMM_FAILURE;                                                     /* 返回                                     */
    }
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    /* 填写RAC */
    pRaiTemp->ucRac = pSysInfo->ucRac;
    /* 填写LAC */
    pRaiTemp->Lai.aucLac[1] = (VOS_UINT8)pSysInfo->usLac;                       /* LAC */
    pRaiTemp->Lai.aucLac[0] = (VOS_UINT8)(pSysInfo->usLac >> 8);
    /* 填写PLMN */
    pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pSysInfo->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pSysInfo->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */

    if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
    {
        pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }

    PS_MEM_SET(&stAttempUpdateRaiInfo, 0, sizeof(stAttempUpdateRaiInfo));
    pstAttemptUpdateRaiInfo = NAS_GMM_GetAttemptUpdateRaiInfo();

    NAS_GMM_ConvertPlmnIdToGmmFormat(&pstAttemptUpdateRaiInfo->stLai.stPlmnId, &stAttempUpdateRaiInfo.Lai.PlmnId);
    stAttempUpdateRaiInfo.Lai.aucLac[0] = pstAttemptUpdateRaiInfo->stLai.aucLac[0];
    stAttempUpdateRaiInfo.Lai.aucLac[1] = pstAttemptUpdateRaiInfo->stLai.aucLac[1];
    stAttempUpdateRaiInfo.ucRac         = pstAttemptUpdateRaiInfo->ucRac;

    stOldRai = g_GmmGlobalCtrl.SysInfo.Rai;
    if (VOS_TRUE == NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(pRaiTemp, &stAttempUpdateRaiInfo))
    {
        stOldRai = stAttempUpdateRaiInfo;
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &stOldRai, pSysInfo->ucNetworkOperationMode))
    {                                                                           /* 设置RAI是否变化标志                      */
        gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_TRUE;
        gstGmmCasGlobalCtrl.ucSysRauFlg             = GMM_TRUE;
    }
    if (GMM_FALSE == Gmm_Compare_Lai(&pRaiTemp->Lai, &stOldRai.Lai))
    {                                                                           /* 设置LAI是否变化标志                      */
        gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg = GMM_TRUE;
    }

    /* GPRS支持指示 */
    g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_SUPPORT_GPRS;

    if (0 == pSysInfo->ucGprsSupportInd)
    {
        g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;
    }

    usCellIdNew = pSysInfo->usCellId;

    if (usCellIdNew != g_GmmGlobalCtrl.SysInfo.usGsmCellId)
    {
        g_GmmGlobalCtrl.SysInfo.usGsmCellId = usCellIdNew;
        gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg = GMM_TRUE;             /* 新小区标志 */
    }
    else
    {
        gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg = GMM_FALSE;
    }

    if (0 != pSysInfo->ucNetworkOperationMode)
    {/* 网络模式有效 */
        ucNetMod = pSysInfo->ucNetworkOperationMode;
    }

    if ((g_GmmGlobalCtrl.SysInfo.ucNtType
        != NAS_MML_GetCurrNetRatType())
      &&(GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState))
    {/* 异系统的小区的系统消息的无效条件 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "GMM_SaveGsmSysInfoIndMsgPara:WARNING: Inter-System information cannot be handled in the GMM STATE!");
    }
    /* ==>A32D12706 */
    if ((g_GmmGlobalCtrl.SysInfo.ucNetMod != ucNetMod)
        && (0 != g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
    /* <==A32D12706 */
    {/* 网络模式变更 */

        if ((GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg)
         || (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg))
        {
            g_GmmRauCtrl.ucT3330outCnt = 0;

            if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode()))
            {                                                                       /* 用户模式为A,并且已经注册                 */
                if (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState)
                {
                    /* 非异系统挂起过程等待小区系统消息状态 */
                    /* 同系统的小区系统消息处理 */
                    Gmm_ComNetModeChangeGsm(pSysInfo);                              /* 调用网络模式变换的公共处理               */
                    Gmm_MemFree(pRaiTemp);

                    /*如果小区网络模式改变，GMM_RcvGasSysInfoInd函数不会走到处理恢复层二用户面的处理。
                      所以在此处增加处理。
                    */
                    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                    {
                        if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
                        {
                            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);
                            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
                        }
                        else
                        {
                            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_RAU;
                        }
                    }

                    if (0 == pSysInfo->ucGprsSupportInd)
                    {
                         NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
                    }

                    /* 收到G模系统消息, 指示RABM当前系统模式, 根据是否支持GPRS, 挂起或恢复RABM */
                    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
                     || (0 == pSysInfo->ucGprsSupportInd)
                     || (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
                    {
                        /* 不支持GPRS、PS bar或者没有指派层2, 挂起RABM, bRatChangeFlg为FALSE
                           没有指派层2时如果不挂起RABM，RABM会向SN发送数据，SN会发送到LLC，
                           而LLC在未指派情况下接收到数据会释放内存导致解除流控,后续数传小包会将消息队列灌满 */
                        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                                    VOS_FALSE,
                                                    VOS_TRUE,
                                                    VOS_TRUE);
                    }
                    else
                    {
                        /* 支持GPRS, 恢复RABM, bRatChangeFlg为FALSE */
                        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                                    VOS_FALSE,
                                                    VOS_FALSE,
                                                    VOS_TRUE);
                    }

                    return GMM_FAILURE;
                }
            }
        }

        gstGmmSuspendCtrl.ucNetModeChange = GMM_CasGetNetChgType(ucNetMod);
    }
    else
    {
        /* 网络模式没有变更，或者原来网络模式无效 */
        gstGmmSuspendCtrl.ucNetModeChange = GMM_NETMODE_CHG_NULL;
                    /*= GMM_CasGetNetChgTypeByGsm(ucNetMod);*/
    }

    /* 删除对2G系统消息ucDrxTimerMax赋值到DrxLen*/

    if (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg)
    {
        if (GMM_TRUE == *pucRaiChgFlg)
        {
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
        else
        {
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_TRUE;
        }
    }
    else
    {
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
    }

    if (GMM_TRUE == *pucRaiChgFlg)
    {/* RA改变 */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {/* 无信令且正在建立信令连接 */
            if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {/* GMM_REGISTERED_INITIATED状态 */
                ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                if (VOS_NULL_PTR == ptr)
                {
                    Gmm_MemFree(pRaiTemp);
                    return GMM_FAILURE;
                }
                Gmm_MemCpy(ptr, pSysInfo,
                           sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach = (VOS_UINT32)ptr;   /* 存储消息首地址到 ulMsgAddrForAttach      */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_ATTACH;/* 置消息保留标志                           */
                Gmm_MemFree(pRaiTemp);
                return GMM_FAILURE;
            }
            else if ((GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
                     || (GMM_ROUTING_AREA_UPDATING_INITIATED
                     == g_GmmGlobalCtrl.ucState)
                     || (GMM_SERVICE_REQUEST_INITIATED
                     == g_GmmGlobalCtrl.ucState)
                     || (GMM_REGISTERED_IMSI_DETACH_INITIATED
                     == g_GmmGlobalCtrl.ucState))
            {
                ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                if (VOS_NULL_PTR == ptr)
                {
                    Gmm_MemFree(pRaiTemp);
                    return GMM_FAILURE;
                }
                Gmm_MemCpy(ptr, pSysInfo,
                           sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;      /* 存储消息首地址到 ulMsgAddrForRau         */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;   /* 置消息保留标志                           */
                Gmm_MemFree(pRaiTemp);

                if (0 == pSysInfo->ucGprsSupportInd)
                {
                     NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
                }

                return GMM_FAILURE;
            }
            else
            {
            }
        }
    }

    if ((MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
        && (0 != pSysInfo->ucGprsSupportInd))
    {
        Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* 存储系统信息中的RAI                      */
        if (GMM_RAU_NORMAL_CS_UPDATED == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_TRUE;
        }
    }
    else
    {
        /* 获取CS ATTACH Allow标志 */
        ucCsAttachAllow                             = NAS_MML_GetCsAttachAllowFlg();
        gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucSysRauFlg             = GMM_FALSE;
        if ((MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            || (MMCGMM_GSM_FORBIDDEN_PLMN_FOR_GPRS == pSysInfo->ulForbiddenFlg))
        {
            if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
             && (VOS_TRUE == ucCsAttachAllow))
            {
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_RAU_NORMAL_CS_UPDATED;
            }
        }
    }

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    if (g_GmmGlobalCtrl.ucNetMod != ucNetMod)
    {
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* 网络模式                                 */
    }

    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfo->ulForbiddenFlg;   /* PLMN是否禁止                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */

    Gmm_MemFree(pRaiTemp);
    return GMM_SUCCESS;
}

/*****************************************************************************
 Prototype      : GMM_CharToUlong
 Description    : 字节数据转换成ULONG型
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_CharToUlong(VOS_UINT32 *ulDst, VOS_UINT8 *pucSrc)
{
    VOS_UINT32  ulResult;

    ulResult  = 0;
    /*lint -e701 -e961*/
    ulResult += (*(pucSrc++) << 24);
    ulResult += (*(pucSrc++) << 16);
    ulResult += (*(pucSrc++) << 8);
    ulResult += (*(pucSrc) );
    /*lint +e701 +e961*/
    *ulDst = ulResult;
    return;
}

/*****************************************************************************
 Prototype      : GMM_CreateNewTlli
 Description    : 创建新的TLLI值
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function

  2.Date        : 2015-07-23
    Author      : wx270776
    Modification: OM Migration
*****************************************************************************/
VOS_VOID GMM_CreateNewTlli(VOS_UINT32 *pulTmsi, VOS_UINT8 ucType)
{
    VOS_UINT32  ulTLLI;
    VOS_UINT32  ulHead5;

    ulTLLI   = *pulTmsi;                /* 得到PTMSI值 */
    ulHead5  = ulTLLI >> 27;            /* 取得TLLI的标志头 */
    ulHead5 &= 0x07;                    /* 清除无效的数位 */

    /*填写TLLI值的高5位值*/
    switch (ucType)
    {
        case GMM_RANDOM_TLLI:
            ulHead5  = 0x0f;            /* 5位值是 01111 */
            ulTLLI   = VOS_GetSlice();   /* 取系统时钟数作为伪随机数 */
            break;

        case GMM_LOCAL_TLLI:
            ulHead5 |= 0x18;            /* 5位值是 11XXX */
            break;

        case GMM_FOREIGN_TLLI:
            ulHead5 |= 0x10;            /* 5位值是 10XXX */
            break;

        case GMM_AUXILIARY_TLLI:
            ulHead5 = 0x0e;            /* 5位值是 01110 */
            break;

        default :                       /* 保留,参看3GPP TS23.003描述 */
            ulHead5  = 0x00;            /* 5位值是 00000 */
            break;
    }

    /*填写TLLI值的低27位值*/
    ulHead5 = ulHead5 << 27;
    ulTLLI &= 0x07ffffff;               /* 清除高5位 */
    ulTLLI += ulHead5;                  /* 新TTLLI值 */

    *pulTmsi = ulTLLI;                  /* 返回结果 */
    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_GMM_UseGutiDerivedPtmsi ( VOS_VOID )
{
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulGetGutiRst;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulRslt;

    /* 如下，协议描述，b)和d) 返回VOS_TRUE,其它返回 VOS_FALSE
    4.7.1.4.1   Radio resource sublayer address handling (A/Gb mode only)

    For an MS supporting S1 mode, the following five cases can be distinguished:
    a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI;
    b)  the TIN indicates "GUTI" and the MS holds a valid GUTI;
    c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI;
    d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; or
    e)  none of the previous cases is fulfilled.

    In case b), the MS shall derive a P-TMSI from the GUTI and
                then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case d) the MS shall derive a P-TMSI from the GUTI and then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.

    In case a) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case c) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case e) the MS shall proceed as as specified for case ii) above.
    */

    /* 获取当前GU的p-Tmsi的取值 */
    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* 获取当前的Tin值和Mapped P-Tmsi是否正确 */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    if (VOS_OK == ulGetGutiRst)
    {
        /* b)  the TIN indicates "GUTI" and the MS holds a valid GUTI; */
        if (NAS_MML_TIN_TYPE_GUTI == enTinType)
        {
            ulRslt = VOS_TRUE;
        }
        /* d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; */
        else if ( (NAS_MML_TIN_TYPE_INVALID == enTinType)
               && (GMM_UEID_P_TMSI != (ucUeIdMask & GMM_UEID_P_TMSI) ))
        {
            ulRslt = VOS_TRUE;
        }
        else
        {
            ulRslt = VOS_FALSE;
        }
    }
    else
    {
        ulRslt = VOS_FALSE;
    }

    return ulRslt;

}

#endif


VOS_UINT32 NAS_GMM_GetPTmsiForTLLI(
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN]
)
{
    VOS_UINT8                          *pucPtmsiAddr        = VOS_NULL_PTR;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulGetGutiRst;
    VOS_UINT8                          *pucMappedPtmsiAddr  = VOS_NULL_PTR;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulRslt;

    VOS_UINT32                          ulIsSupportLteCap;
#endif

    /*
    4.7.1.4.1   Radio resource sublayer address handling (A/Gb mode only)
    This subclause describes how the RR addressing is managed by GMM.
    For the detailed coding of the different TLLI types and how a TLLI can be derived from a P-TMSI, see 3GPP TS 23.003 [10].
    For an MS not supporting S1 mode, two cases can be distinguished:
    -   a valid P-TMSI is available in the MS; or
    -   no valid P-TMSI is available in the MS.
    i)   valid P-TMSI available
        If the MS has stored a valid P-TMSI, the MS shall derive a foreign TLLI from that P-TMSI and shall use it for transmission of the:
    -   ATTACH REQUEST message of any GPRS combined/non-combined attach procedure; other GMM messages sent during this procedure shall be transmitted using the same foreign TLLI until the ATTACH ACCEPT message or the ATTACH REJECT message is received; and
    -   ROUTING AREA UPDATE REQUEST message of a combined/non-combined RAU procedure if the MS has entered a new routing area, or if the GPRS update status is not equal to GU1 UPDATED. Other GMM messages sent during this procedure shall be transmitted using the same foreign TLLI, until the ROUTING AREA UPDATE ACCEPT message or the ROUTING AREA UPDATE REJECT message is received.
        After a successful GPRS attach or routing area update procedure, independent whether a new P-TMSI is assigned, if the MS has stored a valid P-TMSI then the MS shall derive a local TLLI from the stored P-TMSI and shall use it for addressing at lower layers.
    NOTE 1: Although the MS derives a local TLLI for addressing at lower layers, the network should not assume that it will receive only LLC frames using a local TLLI. Immediately after the successful GPRS attach or routing area update procedure, the network must be prepared to continue accepting LLC frames from the MS still using the foreign TLLI.
    ii) no valid P-TMSI available
        When the MS has not stored a valid P-TMSI, i.e. the MS is not attached to GPRS, the MS shall use a randomly selected random TLLI for transmission of the:
    -   ATTACH REQUEST message of any combined/non-combined GPRS attach procedure.
        The same randomly selected random TLLI value shall be used for all message retransmission attempts and for the cell updates within one attach attempt.
        Upon receipt of an ATTACH REQUEST message, the network shall assign a P-TMSI to the MS. The network derives a local TLLI from the assigned P-TMSI, and transmits the assigned P-TMSI to the MS.
        Upon receipt of the assigned P-TMSI, the MS shall derive the local TLLI from this P-TMSI and shall use it for addressing at lower layers.
    NOTE 2: Although the MS derives a local TLLI for addressing at lower layers, the network should not assume that it will receive only LLC frames using a local TLLI. Immediately after the successful GPRS attach, the network must be prepared to continue accepting LLC frames from the MS still using the random TLLI.
    In both cases the MS shall acknowledge the reception of the assigned P-TMSI to the network. After receipt of the acknowledgement, the network shall use the local TLLI for addressing at lower layers.


    For an MS supporting S1 mode, the following five cases can be distinguished:
    a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI;
    b)  the TIN indicates "GUTI" and the MS holds a valid GUTI;
    c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI;
    d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; or
    e)  none of the previous cases is fulfilled.

    In case a) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case b), the MS shall derive a P-TMSI from the GUTI and
                then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case c) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case d) the MS shall derive a P-TMSI from the GUTI and then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case e) the MS shall proceed as as specified for case ii) above.
    */

    /* 取得存储PTMSI数据的地址 */
    pucPtmsiAddr        = NAS_MML_GetUeIdPtmsi();

    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* 判断GUPTMSI是否有效，VOS_TRUE:有效;VOS_FALSE:无效; */
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);

        ulLocalPtmsiFlg = VOS_TRUE;
    }
    else
    {
        ulLocalPtmsiFlg = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* 初始化当前的P-Tmsi的存在标志 */
    ulRslt              = VOS_TRUE;

    /* 获取当前的Tin值和Mapped P-Tmsi */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    /* 取得存储PTMSI数据的地址 */
    pucMappedPtmsiAddr  = NAS_GMM_GetMappedPtmsiAddr();

    /* reference to 24.008 4.7.1.4.1 */
    ulIsSupportLteCap = NAS_MML_IsSupportLteCapability();

    /* syscfg设置不支持L或者L 已经disable则无需从guti中获取ptimsi */
    if (VOS_FALSE == ulIsSupportLteCap)
    {
        if (VOS_TRUE == ulLocalPtmsiFlg)
        {
            PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
        }
        else
        {
            ulRslt = VOS_FALSE;
        }

        return ulRslt;
    }

    /* a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI; */
    if ( ( (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
        || (NAS_MML_TIN_TYPE_PTMSI  == enTinType))
      && (VOS_TRUE == ulLocalPtmsiFlg))
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* b)  the TIN indicates "GUTI" and the MS holds a valid GUTI; */
    else if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
          && (VOS_OK == ulGetGutiRst) )
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI; */
    else if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
          && (VOS_TRUE == ulLocalPtmsiFlg))
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; */
    else if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
          && (VOS_FALSE == ulLocalPtmsiFlg)
          && (VOS_OK == ulGetGutiRst))
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /*e)  none of the previous cases is fulfilled.*/
    else
    {
        ulRslt = VOS_FALSE;
    }

    return ulRslt;

#else

    /* LTE不打开时，只需要判断 GU P-Tmsi是否有效 */
    return ulLocalPtmsiFlg;
#endif

}


VOS_VOID GMM_UpdateSysTlli(GMM_TLLI_TYPE TlliType)
{
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];

    /* 入口参数检查 */
    if ( (GMM_RANDOM_TLLI != TlliType)
      && (GMM_FOREIGN_TLLI != TlliType)
      && (GMM_LOCAL_TLLI != TlliType) )
    {
        GMM_LOG_ERR("GMM_UpdateSysTlli():Error: TlliType is not correct.");
        return;
    }

    /* 初始化 */
    PS_MEM_SET(aucPtmsi, 0, sizeof(aucPtmsi));

    /* 没有存贮有效的PTMSI, 计算RANDOM TLLI */
    if (VOS_FALSE == NAS_GMM_GetPTmsiForTLLI(aucPtmsi))
    {
        GMM_CreateNewTlli(&gstGmmCasGlobalCtrl.ulTLLI, GMM_RANDOM_TLLI);

        gstGmmCasGlobalCtrl.ucflgTLLI = GMM_RANDOM_TLLI;

        return;
    }

    /* 待更新的TLLI值 */
    GMM_CharToUlong(&gstGmmCasGlobalCtrl.ulTLLI, aucPtmsi);


    GMM_CreateNewTlli(&gstGmmCasGlobalCtrl.ulTLLI, TlliType);

    gstGmmCasGlobalCtrl.ucflgTLLI = TlliType;

    return;
}


VOS_UINT32 GMM_GetPtmsiFromMsgIe(VOS_UINT8 *pData)
{
    VOS_UINT32  ulNewTlli = 0;
    VOS_UINT32  ulRslt;

    /* 判断IE数据类型是否有效 */
    if ( (5 != *(pData))                                    /*长度值非法*/
      || (0x04 != (*(pData+1) & 0x07) )                     /*类型不匹配*/
        )
    {/* 类型无效 */
        GMM_LOG_WARN("GMM_GetPtmsiFromMsgIe:WARNING: Wrong length or type in IE data");
        return GMM_FALSE;
    }

    /* 更新GMM系统量存贮的PTMSI值 */
    NAS_MML_SetUeIdPtmsi((pData + 2));
    g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;

    GMM_CharToUlong(&ulNewTlli,
                    NAS_MML_GetUeIdPtmsi());  /*待更新的TLLI值*/

    /* 计算local TLLI值 */
    GMM_CreateNewTlli(&ulNewTlli, GMM_LOCAL_TLLI);          /*计算TLLI*/

    /* 指配new TLLI */
    ulRslt = GMM_AssignNewTlli(ulNewTlli, GMM_LOCAL_TLLI);
    if (GMM_FALSE == ulRslt)
    {
        GMM_LOG_WARN("GMM_GetPtmsiFromMsgIe():Error: new TLLI assigned failed!");
    }

#if (FEATURE_ON == FEATURE_PTM)
    /* 工程菜单打开后，PTMSI发生改变需要上报给OM */
    NAS_GMM_SndAcpuOmChangePtmsi();
#endif

    return GMM_TRUE;
}


VOS_VOID GMM_FreeOldTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* 通知LLC释放old TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_UNASSIGN);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_FreeOldTlli():Error: making LLC message wrongly!");
        return;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* 通知GRR释放old TLLI */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_OLD_TLLI);
        if (VOS_NULL_PTR == pGasAssignMsg)
        {
            GMM_LOG_ERR("GMM_FreeOldTlli():Error: making GAS message wrongly!");
            return;
        }
        /* 发送原语到GRR */
        ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
        if (VOS_OK != ulRet)
        {
            GMM_LOG_ERR("GMM_FreeOldTlli():Error: Send msg fail!");
        }
    }
    return;
}


VOS_VOID GMM_FreeSysTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    VOS_UINT32               ulRet;

    /* 通知LLC释放old TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_UNASSIGN_SYS);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_FreesSysTlli():Error: making LLC message wrongly!");
        return;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* 置TLLI未指配标志 */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;

    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
    {

        GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                               /* 恢复LLC数据传输 */
        gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
    }

    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_FreesSysTlli():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_AssignNewTlli
 Description    : 指配new TLLI
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_AssignNewTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* 替换系统默认TLLI */
    gstGmmCasGlobalCtrl.ulOldTLLI = gstGmmCasGlobalCtrl.ulTLLI;
    gstGmmCasGlobalCtrl.ulTLLI    = ulNewTlli;

    gstGmmCasGlobalCtrl.ucflgTLLI = ucType;             /* 修改TLLI类型标志 */

    /* 通知LLC指配new TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_MODIFY);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: making LLC message wrongly!");
        return GMM_FALSE;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* 通知GRR指配new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: making GAS message wrongly!");
        return GMM_FALSE;
    }
    /* 发送原语到GRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: Send msg fail!");
    }

    return GMM_TRUE;
}

/*****************************************************************************
 Prototype      : GMM_AssignModifyTlli
 Description    : 修改TLLI
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-05-20
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_AssignModifyTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* 替换系统默认TLLI */
    gstGmmCasGlobalCtrl.ulTLLI    = ulNewTlli;

    gstGmmCasGlobalCtrl.ucflgTLLI = ucType;             /* 修改TLLI类型标志 */

    /* 通知LLC指配new TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_MODIFY);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: making LLC message wrongly!");
        return GMM_FALSE;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* 通知GRR指配new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: making GAS message wrongly!");
        return GMM_FALSE;
    }
    /* 发送原语到GRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: Send msg fail!");
    }

    return GMM_TRUE;
}


VOS_VOID GMM_AssignSysTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    GMM_OP_TLLI              TlliOpMode;
    VOS_UINT32               ulRet;

    /* 判断TLLI操作类型 */
    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        TlliOpMode = GMM_OP_TLLI_ASSIGN;                    /* 重新指配TLLI */
    }
    else
    {
        TlliOpMode = GMM_OP_TLLI_SYNC;                      /* 同步当前TLLI */
    }

    /* 通知LLC同步系统TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(TlliOpMode);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: making LLC message wrongly!");
        return;
    }
    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);
    if (GMM_OP_TLLI_ASSIGN == TlliOpMode)
    {
        gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_TRUE;     /* TLLI指配完成标志 */

        /* 恢复RABM, bRatChangeFlg为FALSE */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    VOS_TRUE);
    }

    /* 通知GRR指配new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: making GAS message wrongly!");
        return;
    }
    /* 发送原语到GRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: Send msg fail!");
    }

    return;
}


VOS_VOID GMM_AssignGsmKc(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    VOS_UINT32               ulRet;

    /* 通知LLC指配Kc和加密算法 */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_KC);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignGsmKc():Error: making LLC message wrongly!");
        return;
    }
    /* 设置加密算法已经指配 */
    gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_TRUE;

    /* 发送原语到LLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignGsmKc():Error: Send msg fail!");
    }
    return;
}


VOS_VOID GMM_SaveAuthenResult(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    VOS_UINT8   i;
    VOS_UINT8  *pucAuthRes;

    pucAuthRes = &(pAuthCnf->aucAuthRes[0]);

    /* 保存GSM鉴权结果 */
    if (GMM_UMTS_AUTHEN_UNSUPPORTED == g_GmmAuthenCtrl.ucUmtsAuthFlg)
    {
        g_GmmAuthenCtrl.ucResExtLen = 0;                    /* 没有扩展部分 */
        for (i=1; i<5; i++)
        {
            if (i > *(pucAuthRes))
            {
                g_GmmAuthenCtrl.aucRes[i-1] = 0xFF;         /* 填充无效值 */
            }
            else
            {
                g_GmmAuthenCtrl.aucRes[i-1] = *((pucAuthRes + i));
            }
        }
        return;
    }

    /* 保存RES的基本内容 */
    if (4 > *(pucAuthRes))
    {
        Gmm_MemCpy(g_GmmAuthenCtrl.aucRes,
                   (pucAuthRes + 1),
                  *(pucAuthRes) );                          /* 保存RES */

        for ( i=*(pucAuthRes); i<4; i++ )
        {
            g_GmmAuthenCtrl.aucRes[i] = 0xFF;
        }

        g_GmmAuthenCtrl.ucResExtLen = 0;                    /* 存RES(EXTERN)的长度，0:aucResExt无意义   */
    }
    else
    {
        Gmm_MemCpy(g_GmmAuthenCtrl.aucRes,
                (pucAuthRes + 1), 4 );                      /* 保存RES */
        g_GmmAuthenCtrl.ucResExtLen =
               *(pucAuthRes) - 4;                           /* 存RES(EXTERN)的长度，0:aucResExt无意义   */
    }

    /* 保存RES扩展内容 */
    if (0 < g_GmmAuthenCtrl.ucResExtLen)
    {
        if (12 < g_GmmAuthenCtrl.ucResExtLen)
        {
            g_GmmAuthenCtrl.ucResExtLen = 12;               /* 修正无效的RES Extension长度 */
        }
        Gmm_MemCpy(g_GmmAuthenCtrl.aucResExt,
               (pucAuthRes + 5),
               g_GmmAuthenCtrl.ucResExtLen );               /* 保存RES Extension */
    }

    return;
}


VOS_VOID GMM_UpdateAuthenCtrlFlg(VOS_VOID)
{
    VOS_UINT8   i;

    if (GMM_FALSE == g_GmmAuthenCtrl.ucResStoredFlg)
    {                                                       /* 易失性内存为空*/
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_TRUE;
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_TRUE;         /* 设定易失性内存不为空*/

        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {                                                   /* 更新上一次的RAND值*/
            g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
        }
        Gmm_TimerStart(GMM_TIMER_T3316);                    /* 启动T3316*/
    }
    else
    {                                                       /* 易失性内存不为空*/
        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {                                                   /* 更新上一次的RAND值*/
            g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
        }

        Gmm_TimerStart(GMM_TIMER_T3316);                    /* 启动T3316*/
    }

    return;
}



VOS_VOID GMM_RcvGsmPagingAtRegNmlServ(GRRMM_PAGING_IND_ST *pMsg)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;


    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* 寻呼的类型为IMSI */
        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* 无信令连接                               */
            g_GmmAttachCtrl.ucPagingWithImsiFlg = GMM_TRUE;                     /* 标记由网侧的IMSI寻呼触发的ATTACH         */
        }
        Gmm_PagingInd_common();
    }
    else
    {
        /* 在收到PAGING IND时不进入READY状态，在收到LLC INFOM时进入 */

        if ( 0 == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }


        enRatType   = NAS_MML_GetCurrNetRatType();
        if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != enRatType)
#if (FEATURE_ON == FEATURE_LTE)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
         )
        {
            GMM_LOG_INFO("GMM_RcvGsmPagingAtRegNmlServ:Inter System change, Exec select RAU.");
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
            return;
        }

        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_PAG_RSP);
    /*}*/
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtDeregInit
 Description    : 在GMM_DEREGISTERED_INITIATED状态，
                   接收GRRMM_PAGING_IND消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtDeregInit(GRRMM_PAGING_IND_ST *pMsg)
{
    GRRMM_PAGING_IND_ST    *pMsgHold;

    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* 寻呼的类型为IMSI */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* 无信令且正在建立信令连接                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_PAGING;    /* 置消息被缓存的标志                       */
            pMsgHold = (GRRMM_PAGING_IND_ST *)Gmm_MemMalloc(sizeof(GRRMM_PAGING_IND_ST));
            if (VOS_NULL_PTR == pMsgHold)
            {
                return;
            }
            Gmm_MemCpy(pMsgHold, pMsg, sizeof(GRRMM_PAGING_IND_ST));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsgHold;  /* 保留RRMM_PAGING _IND首地址               */
        }
        else
        {                                                                       /* 有信令或没有信令且还没建信令             */
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask
                & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {                                                                   /* 等待鉴权响应                             */
                Gmm_TimerStop(GMM_TIMER_PROTECT);                               /* 停保护定时器                             */
                g_GmmReqCnfMng.ucCnfMask
                    &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                  /* 清除原语等待标志                         */
            }
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED); /* 更新状态变为GU2                          */
            Gmm_DelPsLocInfoUpdateUsim();
            Gmm_SndMmcLocalDetachInd(NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);

            if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                Gmm_RcvDetachAcceptMsg_DeregInit();
            }
            else
            {
                Gmm_RcvDetachAcceptMsg_RegImsiDtchInit();
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                Gmm_Attach_Prepare();                                           /* 全局变量的清理工作，为attach作好准备     */
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtRauInit
 Description    : 在GMM_ROUTING_AREA_UPDATING_INITIATED状态，
                   接收GRRMM_PAGING_IND消息
                  HSS 4100 V200R001 新增
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtRauInit(GRRMM_PAGING_IND_ST *pMsg)
{
    GRRMM_PAGING_IND_ST    *pMsgHold;

    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* 寻呼的类型为IMSI */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* 无信令且正在建立信令连接                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_PAGING;    /* 置消息被缓存的标志                       */
            pMsgHold = (GRRMM_PAGING_IND_ST *)Gmm_MemMalloc(sizeof(GRRMM_PAGING_IND_ST));
            if (VOS_NULL_PTR == pMsgHold)
            {
                  return;
            }
            Gmm_MemCpy(pMsgHold, pMsg, sizeof(GRRMM_PAGING_IND_ST));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsgHold;       /* 保留RRMM_PAGING _IND首地址              */
        }
        else
        {                                                                       /* 有信令或没有信令且还没建信令             */
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* 停T3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* 停止T3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* 停止T3320                                */

            Gmm_PagingInd_common();
        }
    }

    return;
}


VOS_VOID GMM_RcvGsmPaging_RegPlmnSrch(GRRMM_PAGING_IND_ST *pMsg)
{
    if (GAS_IMSI != pMsg->ucMSIDType)
    {
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_PAGING);

        g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_PAGING;
    }

    return;
}


VOS_UINT8 GMM_AuthType(VOS_UINT8 ucAutnFlag)
{
    VOS_UINT8                               usAuthTypeRet;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enCurRat;

    usAuthTypeRet = GMM_AUTH_FAILURE;
    enCurRat = NAS_MML_GetCurrNetRatType();
    switch (enCurRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:/*在UMTS网络中*/
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {   /*卡类型是USIM卡*/
                if (GMM_TRUE == ucAutnFlag)
                {
                    usAuthTypeRet = GMM_AUTH_UMTS;                      /*UMTS鉴权*/
                }
                else
                {
                    usAuthTypeRet = GMM_AUTH_GSM_AUTH_UNACCEPTABLE;     /*GSM authentication unacceptable*/
                }
            }
            else
            {
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {   /*卡类型是SIM卡*/
                    if (GMM_TRUE == ucAutnFlag)
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM鉴权*/
                    }
                    else
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM鉴权*/
                    }
                }
            }
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {   /*卡类型是USIM卡*/
                if (GMM_TRUE == ucAutnFlag)
                {
                    usAuthTypeRet = GMM_AUTH_UMTS;          /*UMTS鉴权*/
                }
                else
                {
                    usAuthTypeRet = GMM_AUTH_GSM;           /*GSM鉴权*/
                }
            }
            else
            {
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {   /*卡类型是SIM卡*/
                    if (GMM_TRUE == ucAutnFlag)
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM鉴权*/
                    }
                    else
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM鉴权*/
                    }
                }
            }
            break;

        default:
            break;
    }

    /* 系统不允许进行UMTS鉴权 */
    if ((GMM_FALSE == g_GmmAuthenCtrl.ucUmtsAuthFlg) && (GMM_AUTH_UMTS == usAuthTypeRet))
    {
        usAuthTypeRet = GMM_AUTH_FAILURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: perform the GSM authentication challenge");
    }

    return usAuthTypeRet;
}



VOS_VOID NAS_GMM_RauCompleteHandling( VOS_VOID )
{
    NAS_MSG_STRU                            *pSendNasMsg;
    GMM_MSG_RESOLVE_STRU                    stAttachAcceptIe;
    NAS_MSG_FOR_PCLINT_STRU                 stNasMsg;

    Gmm_MemSet(&stAttachAcceptIe, 0, sizeof(GMM_MSG_RESOLVE_STRU));
    Gmm_MemSet(&stNasMsg, 0, sizeof(NAS_MSG_STRU));

    /* 发送RAU complete消息 */
    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        gstGmmCasGlobalCtrl.ucRauCmpFlg = VOS_FALSE;
        pSendNasMsg = Gmm_RoutingAreaUpdateCompleteMsgMake();

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);



        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            /* 只有前面进行过RAU suspend，此处resume才有意义 */
            if (GMM_SUSPEND_LLC_FOR_RAU == (gstGmmCasGlobalCtrl.ucSuspendLlcCause & GMM_SUSPEND_LLC_FOR_RAU))
            {
                gstGmmCasGlobalCtrl.ucSuspendLlcCause &= ~GMM_SUSPEND_LLC_FOR_RAU;

                if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                {
                    GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                             /* 恢复LLC数据传输 */
                }
            }

            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
            GMM_InitCellUpdate(GMM_FALSE);                                                   /* 小区更新，生效新的READY TIMER */
        }


        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;
        NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RauCompleteHandling:INFO: specific procedure ended");
    }

    /* RABM发送RSP消息有如下几种情况:
       1、NORMAL RAU成功
       2、系统间重选/切换成功
       3、系统间重选/切换失败

       GMM在ATTEMP COUNTER大于5的情况有如下几种情况:
       1、RAU失败
       2、联合RAU失败
       3、联合RAU只有PS成功
       所以GMM在通知MM/MMC注册结果时,应该只有在第三种情况通知成功,
       其它两种情况应该通知失败,但是因为在收到注册结果时已经通知,所以此处代码冗余*/
    if (5 <= g_GmmRauCtrl.ucRauAttmptCnt)
    {
        if ((GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
         || ( (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
           && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == gstGmmSuspendCtrl.ucPreState)))
        {
            NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_PS_ONLY,
                                           NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE,
                                           &stNasMsg,
                                           &stAttachAcceptIe);

            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE);

            /*  事件上报 */
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_RAU_SUCC,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
    }

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_LOG_INFO("GMM_RauSuccessInterSys:Gmm rau success for intersystem change.");

        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

        GMM_ResumeSuccess();
    }

    /*处理follow on 或其他缓存的事件 */
    NAS_GMM_HandleDelayedEvent();
}



GMM_CAS_CTRL_STRU* NAS_GMM_GetGmmCasGlobalCtrl(VOS_VOID)
{
    return &(gstGmmCasGlobalCtrl);
}


VOS_UINT16 NAS_GMM_GetMui(VOS_VOID)
{
    return (NAS_GMM_GetGmmCasGlobalCtrl()->usMui);
}


VOS_UINT16 NAS_GMM_IncreaseMui(VOS_VOID)
{
    return ((NAS_GMM_GetGmmCasGlobalCtrl()->usMui)++);
}


VOS_UINT16 NAS_GMM_GetPowerOffDetachPsMui(VOS_VOID)
{
    return (NAS_GMM_GetGmmCasGlobalCtrl()->usPowerOffDetachPsMui);
}


VOS_VOID NAS_GMM_SetPowerOffDetachPsMui(
    VOS_UINT16                          usMui
)
{
    NAS_GMM_GetGmmCasGlobalCtrl()->usPowerOffDetachPsMui = usMui;

    return;
}


VOS_UINT32 NAS_GMM_IsPowerOffPsDetachMsg(
    NAS_MSG_STRU                       *pstNasL3Msg
)
{
    VOS_UINT32                          ulUsimMMApiIsTestCard;
    ulUsimMMApiIsTestCard             = NAS_USIMMAPI_IsTestCard();

    /* 如果当前是关机流程，则携带NeedCnf标志 */
    if ( (GMM_MSG_LEN_DETACH_REQUEST    <= pstNasL3Msg->ulNasMsgSize)
      && (GMM_PD_GMM                    == pstNasL3Msg->aucNasMsg[0])
      && (GMM_MSG_DETACH_REQUEST        == pstNasL3Msg->aucNasMsg[1])
      && ((GMM_GPRS_DETACH_POWEROFF     == pstNasL3Msg->aucNasMsg[2])
       || (GMM_COMBINED_DETACH_POWEROFF == pstNasL3Msg->aucNasMsg[2]))
      && (VOS_FALSE                     == ulUsimMMApiIsTestCard    ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 NAS_GMM_GetCiphInd(
    NAS_MSG_STRU                       *pstNasL3Msg
)
{
    VOS_UINT8                           ucCiphInd;

    if (VOS_FALSE == gstGmmCasGlobalCtrl.ucGprsCipher)
    {
        ucCiphInd = 0;
    }
    else
    {
        if (GMM_PD_GMM == pstNasL3Msg->aucNasMsg[0])
        {
            switch(pstNasL3Msg->aucNasMsg[1])
            {
                case 0x01:
                case 0x04:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x1c:
                case 0x15:
                case 0x16:
                case 0x08:
                case 0x0B:
                    ucCiphInd = 0;
                    break;

                default:
                    ucCiphInd = 1;
                    break;
            }
        }
        else
        {
             ucCiphInd = 1;
        }
    }

    return ucCiphInd;
}

/*lint -restore */
#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
