


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmSecuInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasLmmPubMStack.h"
#include    "NasEmmSerProc.h"
#include    "NasEmmAttDetInterface.h"
#include    "NasEmmTauInterface.h"
#include    "NasEmmAttach.h"
#include    "NasEmmTAUProc.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSECUAUTH_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSECUAUTH_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
NAS_LMM_SECU_CONTROL_STRU    g_NasEmmSecuControl;
VOS_UINT8                           *g_pucSecuSrcBuf;
VOS_UINT8                           *g_pucSecuDstBuf;
#if (VOS_WIN32 == VOS_OS_VER)
VOS_UINT8           aucSrcBuf[LRRC_LNAS_MAX_DATA_LENGTH];
VOS_UINT8           aucDstBuf[LRRC_LNAS_MAX_DATA_LENGTH];
#endif



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_EMM_SecuDmaMalloc
 Description     : 安全模块初始化非可cache内存
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin 00253982      2014-08-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SecuDmaMalloc(VOS_VOID)
{
    VOS_UINT_PTR            ulTempAddr  = VOS_NULL_PTR;

#if (VOS_WIN32 != VOS_OS_VER)
    NAS_EMM_GetSecuSrcSpace() = (VOS_UINT8*)LPS_CacheDmaMalloc(LRRC_LNAS_MAX_DATA_LENGTH,&ulTempAddr);
    if(VOS_NULL == NAS_EMM_GetSecuSrcSpace())
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuInit: SecuSrc Malloc not success.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuDmaMalloc_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }
    NAS_EMM_GetSecuDstSpace() = (VOS_UINT8*)LPS_CacheDmaMalloc(LRRC_LNAS_MAX_DATA_LENGTH,&ulTempAddr);
    if(VOS_NULL == NAS_EMM_GetSecuDstSpace())
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuInit: SecuDst Malloc not success.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuDmaMalloc_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }
#else
    NAS_EMM_GetSecuSrcSpace() = aucSrcBuf;
    NAS_EMM_GetSecuDstSpace() = aucDstBuf;
#endif
    (VOS_VOID)ulTempAddr;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DeriveKasme
 Description     : 从CK,IK生成Kasme
 Input           : pucCK                    -- cipher key from usim
                   pucIK                    -- integrety key from usim
                   current PLMN             -- Present Plmn
                   SQN&AK                   -- Autn from Auth Req Msg
 Output          : pucKasme                 -- Kasme to caculate Nas cipher
                                               key and Nas integrity key
 Return          : NAS_EMM_AUTH_RESULT_SUC  -- caculate key successful
                   NAS_EMM_AUTH_OP_False    -- caculate key unsuccessful
 History         :
    1.liuwenyu    143951      2008-12-25  Draft Enact
    2.zhengjunyan 148421      2009-09-08  BJ9D01868:计算Kasme使用Current PLMN
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_DeriveKasme(        const VOS_UINT8 *pucCK,
                                        const VOS_UINT8 *pucIK,
                                        VOS_UINT8 *pucKasme)
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex      = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;
    NAS_EMM_PLMN_ID_STRU           *pstSerPlmn = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveKasme is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveKasme_ENUM,LNAS_ENTRY);

    /*空指针*/
    if((VOS_NULL_PTR == pucCK) || (VOS_NULL_PTR == pucIK))
    {
         NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveKasme:-> Input Pointer Null!");
         TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveKasme_ENUM,LNAS_NULL_PTR);
         return NAS_EMM_SECU_FAIL;
    }

    /*获取 current PLMN作为计算Kasme的参数*/
    pstSerPlmn = NAS_LMM_GetEmmInfoPresentPlmnAddr();

    /* 编码KDF算法需要的参数 */

    /*encode FC*/
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_FC;

    /*encode PLMNID&Len*/
    aucAlgParam[ulIndex++] = pstSerPlmn->aucPlmnId[0];
    aucAlgParam[ulIndex++] = pstSerPlmn->aucPlmnId[1];
    aucAlgParam[ulIndex++] = pstSerPlmn->aucPlmnId[2];

    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PLMNID_LEN;

    /* encode SQN&AK */
    NAS_LMM_MEM_CPY_S(                  &aucAlgParam[ulIndex],
                                        NAS_EMM_SECU_SQN_LEN,
                                        NAS_EMM_AuthReqAutnAddr(),
                                        NAS_EMM_SECU_SQN_LEN);

    ulIndex                             += NAS_EMM_SECU_SQN_LEN;

    aucAlgParam[ulIndex++]              = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++]              = NAS_EMM_SECU_SQN_LEN;

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)aucKeyParam,
                        NAS_EMM_SECU_CKEY_LEN,
                        pucCK,
                        NAS_EMM_SECU_CKEY_LEN);

    NAS_LMM_MEM_CPY_S(  (VOS_VOID *)&aucKeyParam[NAS_EMM_SECU_CKEY_LEN],
                        NAS_EMM_SECU_IKEY_LEN,
                        pucIK,
                        NAS_EMM_SECU_IKEY_LEN);

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,aucKeyParam,pucKasme);

    return ulRslt;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SendAuthRsp
 Description     : 向MRRC发送NAS_EMM_MRRC_DATA_REQ(Authentication response)消息
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.liuwenyu 00143951         2008-12-20  Draft Enact
    2.zhuyiqiang 00138739       2009-08-11  MODIFY    BJ9D01672,上行编码优化
    3.zhengjunyan00148421       2010-03-19  AUTH重构
*****************************************************************************/
VOS_VOID NAS_EMM_SendAuthRsp(VOS_VOID)
{
     VOS_UINT32                         ulPos          = 0;
     NAS_EMM_MRRC_DATA_REQ_STRU        *pIntraMsg      = VOS_NULL_PTR;
     VOS_UINT32                         uldataReqMsgLenNoHeader;

     /* 打印进入该函数， INFO_LEVEL */
     NAS_EMM_SECU_LOG_INFO("NAS_EMM_SendAuthRsp entered.");
     TLPS_PRINT2LAYER_INFO(NAS_EMM_SendAuthRsp_ENUM,LNAS_ENTRY);

     /* 申请消息内存 */
     pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

     /* 判断申请结果，若失败退出 */
     if (NAS_EMM_NULL_PTR == pIntraMsg)
     {
         return;
     }

     /* 构造AUTH RSP消息 */
     pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = EMM_CN_MSG_PD_EMM;
     pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = NAS_EMM_CN_MT_AUTH_RSP;

     /* 拷贝 RES的长度和内容 */
     pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = NAS_EMM_GetSecuAuthResLen();
     NAS_LMM_MEM_CPY_S(     (VOS_VOID *)&(pIntraMsg->stNasMsg.aucNasMsg[ulPos]),
                            NAS_EMM_GetSecuAuthResLen(),
                            NAS_EMM_GetSecuAuthResVAddr(),
                            NAS_EMM_GetSecuAuthResLen());

     ulPos += NAS_EMM_GetSecuAuthResLen();

     /* 填充消息体 */
     pIntraMsg->ulMsgId                 = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
     pIntraMsg->enEstCaue               = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
     pIntraMsg->enCallType              = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
     pIntraMsg->enEmmMsgType            = NAS_EMM_MSG_AUTH_RSP;

     pIntraMsg->enDataCnf               = LRRC_LMM_DATA_CNF_NEED;

     /* 填充其中的NAS CN消息的长度 */
     pIntraMsg->stNasMsg.ulNasMsgSize   = ulPos;

     /*计算不包含消息头的消息长度*/
     uldataReqMsgLenNoHeader = NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(
                                        pIntraMsg->stNasMsg.ulNasMsgSize);

     /* 填充消息头 */
     NAS_EMM_SET_SECU_INTRA_MSG_HEADER(pIntraMsg, uldataReqMsgLenNoHeader);

    /*空口消息上报 AUTH RSP*/
    NAS_LMM_SendOmtAirMsg(              NAS_EMM_OMT_AIR_MSG_UP,
                                        NAS_EMM_AUTH_RSP,
                                        (NAS_MSG_STRU*)&(pIntraMsg->stNasMsg));

    /*关键事件上报 AUTH RSP*/
    NAS_LMM_SendOmtKeyEvent(            EMM_OMT_KE_AUTH_RSP);


    /*向MRRC发送AUTH RSP消息*/
    NAS_EMM_SndUplinkNasMsg(            pIntraMsg);

     NAS_LMM_MEM_FREE(pIntraMsg);

     return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendAuthFail
 Description     : 向MRRC发送NAS_EMM_MRRC_DATA_REQ(Authentication failure)消息
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.zhengjunyan 00148421        2010-03-22  Draft Enact

 *****************************************************************************/
VOS_VOID NAS_EMM_SendAuthFail(NAS_EMM_AUTH_FAIL_CAUSE_ENUM_UINT8 enAuthFailCause)
{
    VOS_UINT32                          uldataReqMsgLenNoHeader     = 0;
    VOS_UINT32                          ulPos                       = 0;
    VOS_UINT8                           aucNasMsg[NAS_EMM_AUTH_LEN_CN_MAX_FAIL_MSG];
    NAS_EMM_MRRC_DATA_REQ_STRU          *pIntraMsg                  = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SendAuthFail entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendAuthFail_ENUM,LNAS_ENTRY);

    /*申请消息内存*/
    pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*判断申请结果，若失败退出*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /* 构造Auth Fai消息 */
    aucNasMsg[ulPos++]                  = EMM_CN_MSG_PD_EMM;
    aucNasMsg[ulPos++]                  = NAS_EMM_CN_MT_AUTH_FAIl;
    aucNasMsg[ulPos++]                  = enAuthFailCause;

    if (NAS_EMM_AUTH_SYNC_FAILURE == enAuthFailCause)
    {
        aucNasMsg[ulPos++]              = NAS_EMM_AUTH_FAIl_PARAM_IEI;

        aucNasMsg[ulPos++]              = NAS_EMM_SECU_AUTH_AUTS_LEN;

        /* 获得 AUTS*/
        NAS_LMM_MEM_CPY_S(  (VOS_VOID *)&aucNasMsg[ulPos],
                            NAS_EMM_SECU_AUTH_AUTS_LEN,
                            NAS_EMM_GetSecuAuthAutsAddr(),
                            NAS_EMM_SECU_AUTH_AUTS_LEN);

        ulPos += NAS_EMM_SECU_AUTH_AUTS_LEN;

    }

    /*lint -e669*/
    NAS_LMM_MEM_CPY_S(pIntraMsg->stNasMsg.aucNasMsg, ulPos, aucNasMsg,ulPos);
    /*lint +e669*/

    /* 填充消息ID */
    pIntraMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pIntraMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enEmmMsgType             = NAS_EMM_MSG_AUTH_FAIL;

    pIntraMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NEED;

    /* 填充消息长度 */
    pIntraMsg->stNasMsg.ulNasMsgSize = ulPos;

    /*计算不包含消息头的消息长度*/
    uldataReqMsgLenNoHeader =
            NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(pIntraMsg->stNasMsg.ulNasMsgSize);

    /* 填充消息头 */
    NAS_EMM_SET_SECU_INTRA_MSG_HEADER(pIntraMsg, uldataReqMsgLenNoHeader);

    /*空口消息上报 AUTH FAIL*/
    NAS_LMM_SendOmtAirMsg(               NAS_EMM_OMT_AIR_MSG_UP,
                                        NAS_EMM_AUTH_FAIL,
                       (NAS_MSG_STRU*)&(pIntraMsg->stNasMsg));

    /*关键事件上报 AUTH FAIL*/
    NAS_LMM_SendOmtKeyEvent(             EMM_OMT_KE_AUTH_FAIL);

    /*向MRRC发送Auth Fai消息*/
    NAS_EMM_SndUplinkNasMsg(pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);

    return;

}

/*****************************************************************************
 Function Name  : NAS_EMM_SendUsimAuthenticationReq()
 Description    : 给USIM发送鉴权请求
 Input          : ulAppType     应用类型
                  enAuthType    鉴权类型
                  ulOpId
                  uAuth         鉴权数据
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719  2015-02-09   Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SendUsimAuthenticationReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    USIMM_AUTH_TYPE_ENUM_UINT32     enAuthType,
    VOS_UINT8                       ulOpId,
    USIMM_AUTH_DATA_UNION          *puAuth
)
{
    USIMM_AUTHENTICATION_REQ_STRU           *pstUsimAuthenticationReq;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SendUsimAuthenticationReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendUsimAuthenticationReq_ENUM,LNAS_ENTRY);

    /*分配空间并检验分配是否成功*/
    pstUsimAuthenticationReq = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(USIMM_AUTHENTICATION_REQ_STRU));

    /*检测是否分配成功*/
    if (VOS_NULL_PTR == pstUsimAuthenticationReq)
    {
        /*打印异常信息*/
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SendUsimAuthenticationReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendUsimAuthenticationReq_ENUM,LNAS_NULL_PTR);
        return ;
    }


    /*填写消息头*/
    /*消息结构体中的SendPara用来存储OpId*/
    NAS_EMM_SET_USIM_MSG_HEADER(pstUsimAuthenticationReq, USIMM_AUTHENTICATION_REQ, ulAppType, ulOpId);

    pstUsimAuthenticationReq->enAuthType = enAuthType;

    NAS_LMM_MEM_CPY_S(  &(pstUsimAuthenticationReq->uAuth),
                        sizeof(USIMM_AUTH_DATA_UNION),
                        puAuth,
                        sizeof(USIMM_AUTH_DATA_UNION));

    /*调用消息发送函数 */
    NAS_LMM_SEND_MSG(pstUsimAuthenticationReq);
}


/*****************************************************************************
 Function Name   : NAS_EMM_UsimAuthSucc
 Description     : USIM_AUTH_CNF结果为成功的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-22  Draft Enact
    2.zhengjunyan 00148421      2011-5-31  MOD:AUTH成功产生new native secu cntxt
                                           删除non-current native secu cntxt
*****************************************************************************/
VOS_VOID  NAS_EMM_UsimAuthSucc( const USIMM_AUTHENTICATION_CNF_STRU  *pstUsimAuthCnf  )
{
    VOS_UINT32                          ulDeriveKeyRslt;
    USIMM_TELECOM_AUTH_CNF_STRU        *pstAuthCnf;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_UsimAuthSucc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UsimAuthSucc_ENUM,LNAS_ENTRY);

    pstAuthCnf = (USIMM_TELECOM_AUTH_CNF_STRU*)&pstUsimAuthCnf->uCnfData.stTELECnf;

    /*1.更新新安全上下文:保存AuthReq消息携带的Ksi并计算新的Kasme*/
    NAS_EMM_ClearNonCurNativeSecuCntxt();
    NAS_EMM_SetSecuNewNativeKSIasme(NAS_EMM_AuthReqKsi());
    ulDeriveKeyRslt = NAS_EMM_DeriveKasme(&pstAuthCnf->aucCK[1],
                                          &pstAuthCnf->aucIK[1],
                                          NAS_EMM_GetSecuNewNativeKasmeAddr());
    if( NAS_EMM_SECU_FAIL == ulDeriveKeyRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_PreProcUsimAuthCnf: Caculate Kasme ERR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_UsimAuthSucc_ENUM,LNAS_FUNCTION_LABEL1);
    }

    /*安全上下文状态迁移*/
    NAS_EMM_SecuStateConvert(NAS_LMM_GetSecuCurFsmCS() ,EMM_NEW_SECU_EXIST);

    /*2. 启动T3416,保存Rand 和 Res*/
    /*启动T3416*/
    NAS_LMM_StartPtlTimer(                TI_NAS_EMM_PTL_T3416);

    /*保存Rand*/
    NAS_EMM_GetSecuAuthOpRand() = NAS_EMM_BIT_SLCT;

    NAS_LMM_MEM_CPY_S(                  NAS_EMM_GetSecuAuthRandAddr(),
                                        NAS_EMM_SECU_AUTH_RAND_LEN,
                                        NAS_EMM_AuthReqRandAddr(),
                                        NAS_EMM_SECU_AUTH_RAND_LEN);

    /*保存Res:pstUsimAuthCnf->u.aucAuthRes第一个字节为Res的长度*/
    NAS_EMM_GetSecuAuthResLen() = pstAuthCnf->aucAuthRes[NAS_EMM_USIM_CNF_RES_L_POS];

    NAS_LMM_MEM_CPY_S(  NAS_EMM_GetSecuAuthResVAddr(),
                        NAS_EMM_SECU_MAX_AUTH_RES_LEN,
                        &(pstAuthCnf->aucAuthRes[NAS_EMM_USIM_CNF_RES_V_POS]),
                        NAS_EMM_GetSecuAuthResLen());

    /*3. 如果AUTH失败次数不为零，出栈并将失败次数清零*/
    if(0 != NAS_EMM_GetAuthFailTimes())
    {
        NAS_EMM_FSM_PopState();
        NAS_EMM_GetAuthFailTimes() = 0;
    }

    /*4. 发送AUTH RSP*/
    NAS_EMM_SendAuthRsp();

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_UsimAuthFail
 Description     : USIM_AUTH_CNF结果为失败的处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_UsimAuthFail( NAS_EMM_AUTH_FAIL_CAUSE_ENUM_UINT8 enAuthFailCause )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_UsimAuthFail entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UsimAuthFail_ENUM,LNAS_ENTRY);

    /*1.鉴权失败的次数*/
    NAS_EMM_GetAuthFailTimes()++;

    if(NAS_EMM_FIRST_AUTH_FAIL == NAS_EMM_GetAuthFailTimes())
    {
        NAS_EMM_FSM_PushState();
    }

    /*连续鉴权失败达到三次，不再发送AUTH FAIL,释放连接，通知RRC当前小区被Bar*/
    if(NAS_EMM_MAX_AUTH_FAIL_TIMES == NAS_EMM_GetAuthFailTimes())
    {
        NAS_EMM_AuthCheckFail();
        return;
    }

    /*2.转换状态*/
    if(NAS_EMM_AUTH_SYNC_FAILURE == enAuthFailCause)
    {
        NAS_LMM_StartStateTimer(         TI_NAS_EMM_T3420);
        NAS_EMM_AuthStateConvert(       EMM_MS_AUTH_INIT,
                                        EMM_SS_AUTH_WAIT_CN_AUTH,
                                        TI_NAS_EMM_T3420);
    }
    else
    {
        NAS_LMM_StartStateTimer(         TI_NAS_EMM_T3418);
        NAS_EMM_AuthStateConvert(       EMM_MS_AUTH_INIT,
                                        EMM_SS_AUTH_WAIT_CN_AUTH,
                                        TI_NAS_EMM_T3418);
    }

    /*3.停止T3416，删除 Rand和Res*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

    /*4.发送AUTH FAIL消息*/
    NAS_EMM_SendAuthFail(enAuthFailCause);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_AuthCheckFail
 Description     : UE鉴权网络非法:
                   1)本地释放RRC连接
                   2)通知RRC当前小区被bar
 Input           : None
 Output          : None
 Return          : None
 History         :
    1.liuwenyu 00143951         2008-12-20  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_AuthCheckFail(VOS_VOID)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_AuthCheckFail entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AuthCheckFail_ENUM,LNAS_ENTRY);

    /* 修改状态：进入主状态EMM_MS_AUTH_INIT子状态EMM_SS_AUTH_WAIT_RRC_REL_IND */


    /*向MRRC发送NAS_EMM_MRRC_REL_REQ消息*/
    NAS_EMM_RelReq(                     NAS_LMM_BARRED);
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuClearRandRes
 Description     : 清空MEM中保存的RAND和RES
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-5  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuClearRandRes( VOS_VOID )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuClearRandRes entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuClearRandRes_ENUM,LNAS_ENTRY);

    /* 删除RAND and RES */
    NAS_EMM_GetSecuAuthOpRand() = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuAuthRandAddr(),
                        NAS_EMM_SECU_AUTH_RAND_LEN,
                        0,
                        NAS_EMM_SECU_AUTH_RAND_LEN);
    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuAuthResAddr(),
                        sizeof(NAS_EMM_SECU_AUTH_RES_STRU),
                        0,
                        sizeof(NAS_EMM_SECU_AUTH_RES_STRU));
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_AbortAuthProcedure
 Description     : 终止本次AUTH流程
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-5  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_AbortAuthProcedure(VOS_VOID)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_AbortAuthProcedure entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AbortAuthProcedure_ENUM,LNAS_ENTRY);

    /* 停T3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    return;
}

/*******************************************************************************
Module   : NAS_EMM_AuthStateConvert
Function : 系统状态机状态转换
Input    : ucMs                         -- 主状态
           ucSs                         -- 子状态
           ucStaTId                     -- 该状态的定时器
Output   : None
Return   : None
History  :
   1.liuwenyu 00143951         2008-12-20  Draft Enact
*******************************************************************************/
VOS_VOID  NAS_EMM_AuthStateConvert(NAS_EMM_MAIN_STATE_ENUM_UINT16 ucMs,
                                   NAS_EMM_SUB_STATE_ENUM_UINT16 ucSs,
                                   NAS_EMM_STATE_TI_ENUM_UINT16 ucStaTId)
{
    NAS_EMM_FSM_STATE_STRU              stDestState;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_AuthStateConvert is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AuthStateConvert_ENUM,LNAS_ENTRY);

    stDestState.enFsmId                 = NAS_LMM_PARALLEL_FSM_EMM;
    stDestState.enMainState             = ucMs;
    stDestState.enSubState              = ucSs;
    stDestState.enStaTId                = ucStaTId;
    NAS_LMM_StaTransProc(stDestState);

    return;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_TAU_SendEsmBearerStatusInd
  Input    : None
  Output   : None
  NOTE     : 给ESM发送EMM_ESM_DEACT_NON_EMC_BEAR_IND消息
  Return   : VOS_VOID
  History  :
    1.  lihong 00150010  2012.10.19  新规作成
*******************************************************************************/
VOS_VOID NAS_EMM_SendEsmDeactNonEmcBearInd( VOS_VOID )
{
    EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU *pstDeactNonEmerBearInd = NAS_EMM_NULL_PTR;

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_SendEsmDeactNonEmcBearInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendEsmDeactNonEmcBearInd_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    pstDeactNonEmerBearInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstDeactNonEmerBearInd)
    {
        return;
    }

    /* 填写DOPRA消息头 */
    NAS_EMM_SET_SECU_ESM_MSG_HEADER(pstDeactNonEmerBearInd, sizeof(EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU) -
                                        NAS_EMM_VOS_HEADER_LEN);

    /* 填写消息ID标识 */
    pstDeactNonEmerBearInd->ulMsgId    = ID_EMM_ESM_DEACT_NON_EMC_BEARER_IND;

    /* 发送消息*/
    NAS_LMM_SEND_MSG(pstDeactNonEmerBearInd);

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq
 Description     : RegInit.WtAttCnf,Reg.Normal_Service,TauInit.WtCnTauCnf,
                   SerInit.WtSerCnf,DeregInit.WtCnDetCnf五种
                   状态下处理AUTH_REQ消息
                   AUTN:
                   Separation Bit:AMF最高位
                   ----------------------------------------------------------
                   | SQN ^ AK |   AMF   |   MAC   |
                   ----------------------------------------------------------
                   |  6 Byte  | 2 Byte  |   8 Byte|
                   ----------------------------------------------------------
 Input           :
 Output          :
 Return          :
 History         :
    1.zhengjunyan 00148421 2010-03-18  New Draft
    2.lihong 00150010      2012-12-17  Modify:Emergency

*****************************************************************************/
VOS_UINT32 NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq(        VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsg )
{
    NAS_EMM_AUTH_REQ_STRU              *pstAuthReq = VOS_NULL_PTR;
    /*NAS_EMM_USIM_PARAM_STRU             stAuthVector;*/
    /*VOS_UINT32                          ulHardUsimAuthRslt;*/
    VOS_UINT8                           ucSepBitInAMF;
    VOS_UINT8                           ucKsiAuthReq = 0;
    USIMM_AUTH_DATA_UNION               uAuth;
    VOS_UINT8                           ulOpId;

    (VOS_VOID)ulMsgId;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_ENTRY);

    pstAuthReq                          = (NAS_EMM_AUTH_REQ_STRU *)pMsg;

    NAS_LMM_MEM_SET_S(  &uAuth,
                        sizeof(USIMM_AUTH_DATA_UNION),
                        0,
                        sizeof(USIMM_AUTH_DATA_UNION));

    if ((NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
        || (NAS_LMM_SIM_INVALID == NAS_LMM_GetPsSimValidity()))
    {
        NAS_EMM_SECU_LOG_WARN("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq: no USIM");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_EMM_NO_USIM);

        return NAS_LMM_MSG_HANDLED;
    }
    /* 判断AUTH REQ消息中AMF携带的 Separation BIT,是否 For E_UTRAN*/
    ucSepBitInAMF = ((pstAuthReq->aucAutn[NAS_EMM_AUTH_AMF_IN_AUTN_POS])&0x80) >> 7;
    if(NAS_EMM_AUTH_FOR_EUTRAN != ucSepBitInAMF)
    {
        NAS_EMM_SECU_LOG1_NORM("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq: ERR. AMF Separation BIT = ",
                                        ucSepBitInAMF);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_UsimAuthFail(NAS_EMM_AUTH_NON_EPS_AUTH_UNACCEPTABLE);
        return NAS_LMM_MSG_HANDLED;
    }

    /* 判断当前随机值是否有效，如果有效，判断AUTH REQ消息携带的 RAND与本次保存的 RAND,如果相同，直接回复AUTH RSP*/
    if((NAS_EMM_BIT_SLCT == NAS_EMM_GetSecuAuthOpRand())
       &&(NAS_EMM_SECU_MEM_CMP_EQUAL == NAS_LMM_MEM_CMP(pstAuthReq->aucRand,
                                                    NAS_EMM_GetSecuAuthRandAddr(),
                                                    NAS_EMM_SECU_AUTH_RAND_LEN)))
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq: New Rand == Old Rand!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_SendAuthRsp();
        return NAS_LMM_MSG_HANDLED;
    }

    /* AUTH REQ消息携带的Ksi不能与当前安全上下文的Ksi相同*/
    ucKsiAuthReq = pstAuthReq->ucKsi & NAS_EMM_LOW_HALF_BYTE_F;
    if(NAS_EMM_GetSecuCurKSIasme() == ucKsiAuthReq)
    {
        NAS_EMM_SECU_LOG_WARN("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq: Ksi Of AUTH REQ same as Cur Ksi!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_FUNCTION_LABEL3);
    }

    /*记录AUTH REQ消息携带的 KSI,Rand,Autn:AUTN
      USIM回复鉴权成功时，Ksi保存到stNewSecuContext,Rand保存到stNasUsimAuthParam*/
    NAS_EMM_AuthReqKsi()                = ucKsiAuthReq;

    NAS_LMM_MEM_CPY_S(                  NAS_EMM_AuthReqRandAddr(),
                                        NAS_EMM_SECU_AUTH_RAND_LEN,
                                        pstAuthReq->aucRand,
                                        NAS_EMM_SECU_AUTH_RAND_LEN);
    NAS_LMM_MEM_CPY_S(                  NAS_EMM_AuthReqAutnAddr(),
                                        NAS_EMM_SECU_AUTH_AUTN_LEN,
                                        pstAuthReq->aucAutn,
                                        NAS_EMM_SECU_AUTH_AUTN_LEN);

    /*调用硬USIM进行鉴权*/
    uAuth.st3GAuth.stAutn.ucDataLen = \
                     (VOS_UINT8)pstAuthReq->ulAutnLen;
    //uAuth.st3GAuth.stAutn.aucData = NAS_EMM_AuthReqAutnAddr();

    NAS_LMM_MEM_CPY_S(                  uAuth.st3GAuth.stAutn.aucData,
                                        NAS_EMM_SECU_AUTH_AUTN_LEN,
                                        NAS_EMM_AuthReqAutnAddr(),
                                        NAS_EMM_SECU_AUTH_AUTN_LEN);

    uAuth.st3GAuth.stRand.ucDataLen = \
                     NAS_EMM_SECU_AUTH_RAND_LEN;
    //uAuth.st3GAuth.stRand.aucData = NAS_EMM_AuthReqRandAddr();

    NAS_LMM_MEM_CPY_S(                  uAuth.st3GAuth.stRand.aucData,
                                        NAS_EMM_SECU_AUTH_RAND_LEN,
                                        NAS_EMM_AuthReqRandAddr(),
                                        NAS_EMM_SECU_AUTH_RAND_LEN);

    NAS_EMM_GetSecuAuthOpId()++;

    ulOpId = NAS_EMM_GetSecuAuthOpId();


    /* 发送USIM的鉴权消息，然后等待USIM的鉴权结果，但不启定时器和状态等待 */
    NAS_EMM_SendUsimAuthenticationReq(USIMM_GUTL_APP, USIMM_3G_AUTH, ulOpId, &uAuth);


    return NAS_LMM_MSG_HANDLED;

}
/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthReq
 Description     : AuthInit.WtCnAuth收到AUTH REQ消息，需要停止T3418 OR T3420
 Input           :
 Output          :
 Return          :
 History         :
    1.zhengjunyan 00148421 2010-03-18  New Draft

*****************************************************************************/
VOS_UINT32 NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthReq(        VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsg )
{
    VOS_UINT32                          ulAuthRslt;

    (VOS_VOID)ulMsgId;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthReq entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthReq_ENUM,LNAS_ENTRY);

    /*停止3418,T3420 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3420);

    ulAuthRslt = NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq(ulMsgId, pMsg);

    return ulAuthRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthRej
 Description     : AuthInit.WtCnAuth状态下收到AUTH REJ消息
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705           2009-09-29  处理AUTH REJ消息
    2.lifuxin 00253982  2014-09-10    逻辑重构

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{

    VOS_UINT32                          ulCurEmmStat;

    (VOS_VOID)(pMsgStru);
    (VOS_VOID)ulMsgId;

    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthRej entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthRej_ENUM,LNAS_ENTRY);

    /* 鉴权拒绝优化处理 */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_AuthCnFailErrRecord(EMM_OM_ERRLOG_AUTH_FAIL_CN_REJ);
    #endif

    /* 停T3420，T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
                NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
                NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
                NAS_EMM_ProcDetachAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
                NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        default:
                break;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachRej
 Description     : AuthInit.WtCnAuth状态下收到网侧回复ATTACH REJ消息，CAUSE #3
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-11-10  Draft Enact
    2.lifuxin 00253982          2014-09-09  逻辑重构，去掉内部消息

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachRej entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachRej_ENUM,LNAS_ENTRY);

    /* 停T3420，T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    /*状态出栈之后相当于在reg_init+wait_cn_attach_cnf状态下处理attach rej消息，
      如果有转义处理，则根据相应的分支进行处理即可
    */
    (VOS_VOID)NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject(ulMsgId, pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgTauRej
 Description     : AuthInit.WtCnAuth状态下收到网侧回复TAU REJ消息，CAUSE #3
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-11-10  Draft Enact
    2.lifuxin 00253982          2014-09-09  逻辑重构，去掉内部消息

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgTauRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);


    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_MsAuthInitSsWtCnAuthMsgTauRej entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauRej_ENUM,LNAS_ENTRY);

    /* 停T3420，T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    /*状态出栈之后相当于在tau_init+wait_cn_tau_cnf状态下处理tau rej消息，
      如果有转义处理，则根据相应的分支进行处理即可
    */
    (VOS_VOID)NAS_EMM_MsTauInitSsWaitCNCnfMsgTAURej(ulMsgId, pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgSerRej
 Description     : AuthInit.WtCnAuth状态下收到网侧回复SER REJ消息，CAUSE #3
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-11-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgSerRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);


    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_MsAuthInitSsWtCnAuthMsgSerRej entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgSerRej_ENUM,LNAS_ENTRY);
    /* 停T3420，T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    /*状态出栈之后相当于在ser_init+wait_cn_ser_cnf状态下处理ser rej消息，
      如果有转义处理，则根据相应的分支进行处理即可
    */
    (VOS_VOID)NAS_EMM_MsSerInitSsWaitCNSerCnfMsgServiceReject(ulMsgId, pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgT3418Exp
 Description     :处理因UE鉴权失败原因为"MAC failure",启动的T3418定时器超时.
 Input           : ulMsgId              -- 网侧消息ID
                   pMsg                 -- 需要处理的消息
 Output          : None
 Return          : 消息处理状态
 History         :
    1.liuwenyu 143951      2008-12-16  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgT3418Exp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgT3418Exp entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgT3418Exp_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* 如果当前没有正在建立紧急承载且没有紧急承载，则通知RRC释放链路，被BAR类型 */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        /*确定网侧不能通过本次鉴权*/
        NAS_EMM_AuthCheckFail();
        return NAS_LMM_MSG_HANDLED;
    }

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    /* 通知ESM去激活所有非紧急承载 */
    if ((EMM_MS_REG == NAS_EMM_CUR_MAIN_STAT)
        || (EMM_MS_TAU_INIT == NAS_EMM_CUR_MAIN_STAT)
        || (EMM_MS_SER_INIT == NAS_EMM_CUR_MAIN_STAT))
    {
        NAS_EMM_SendEsmDeactNonEmcBearInd();
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp
 Description     :处理因UE鉴权失败原因为"synch failure",启动的3420定时器超时.
 Input           : ulMsgId              -- 网侧消息ID
                   pMsg                 -- 需要处理的消息
 Output          : None
 Return          : 消息处理状态
 History         :
    1.liuwenyu 143951      2008-12-16  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* 如果当前没有正在建立紧急承载且没有紧急承载，则通知RRC释放链路，被BAR类型 */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        /*确定网侧不能通过本次鉴权*/
        NAS_EMM_AuthCheckFail();
        return NAS_LMM_MSG_HANDLED;
    }

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    /* 通知ESM去激活所有非紧急承载 */
    if ((EMM_MS_REG == NAS_EMM_CUR_MAIN_STAT)
        || (EMM_MS_TAU_INIT == NAS_EMM_CUR_MAIN_STAT)
        || (EMM_MS_SER_INIT == NAS_EMM_CUR_MAIN_STAT))
    {
        NAS_EMM_SendEsmDeactNonEmcBearInd();
    }

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNorOrUpdateMmMsgT3420Exp
 Description     : 仅针对GCF测试用例，由于鉴权失败导致的T3420定时器超时
 Input           : ulMsgId              -- 网侧消息ID
                   pMsg                 -- 需要处理的消息
 Output          : None
 Return          : 消息处理状态
 History         :
    1.wangchen 00209181 2015-12-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNorOrUpdateMmMsgT3420Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsRegSsNorOrUpdateMmMsgT3420Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* 仅针对GCF测试进行修改，实际网络下，在鉴权失败，收到网侧发送的DRB SETUP IND消息后，
    已经将T3420定时器停掉 */
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        /* 通知ESM去激活所有非紧急承载 */
        if ((EMM_MS_REG == NAS_EMM_CUR_MAIN_STAT)
            || (EMM_MS_TAU_INIT == NAS_EMM_CUR_MAIN_STAT)
            || (EMM_MS_SER_INIT == NAS_EMM_CUR_MAIN_STAT))
        {
            NAS_EMM_SendEsmDeactNonEmcBearInd();
        }
    }

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsNorOrUpdateMmMsgT3418Exp
 Description     : 仅针对GCF测试用例，由于鉴权失败导致的T3420定时器超时
 Input           : ulMsgId              -- 网侧消息ID
                   pMsg                 -- 需要处理的消息
 Output          : None
 Return          : 消息处理状态
 History         :
    1.wangchen 00209181 2015-12-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsNorOrUpdateMmMsgT3418Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsRegSsNorOrUpdateMmMsgT3420Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* 仅针对GCF测试进行修改，实际网络下，在鉴权失败，收到网侧发送的DRB SETUP IND消息后，
    已经将T3420定时器停掉 */
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        /* 通知ESM去激活所有非紧急承载 */
        if ((EMM_MS_REG == NAS_EMM_CUR_MAIN_STAT)
            || (EMM_MS_TAU_INIT == NAS_EMM_CUR_MAIN_STAT)
            || (EMM_MS_SER_INIT == NAS_EMM_CUR_MAIN_STAT))
        {
            NAS_EMM_SendEsmDeactNonEmcBearInd();
        }
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgRrcRelInd
 Description     : 在AuthInit等待CN消息时处理RRC_REL_IND消息
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705           2009-09-29  处理RRC_REL_IND消息
    2.Z00148421           2010-01-30  添加失败次数清零
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgRrcRelInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    LRRC_LMM_REL_IND_STRU                *pRrcRelInd =       VOS_NULL_PTR;
    VOS_UINT32                           ulCause;
    VOS_UINT32                          ulCurEmmStat;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgRrcRelInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgRrcRelInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    pRrcRelInd                          = (LRRC_LMM_REL_IND_STRU*)(pMsgStru);
    ulCause                             = pRrcRelInd->enRelCause;

    /* 停T3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);
    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
                NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
                NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
                NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
                NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
                NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd(ulCause);
                break;
        default:
                break;
    }

    return NAS_LMM_MSG_HANDLED;

}
/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify
 Description     : 在AuthInit等待CN消息时处理EIA0 ACT NOTIFY消息
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* 停T3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd
 Description     : 在AuthInit等待CN消息时处理DRB建立消息
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                     *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd_ENUM,LNAS_ENTRY);

    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }
    (VOS_VOID)ulMsgId;

    /* 栈顶的状态如果不为SERVICE_INIT态，则丢弃 */
    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);
    if (ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd:not service_init+wait_cn_ser_cnf state!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果当前没有正在建立紧急承载且没有紧急承载，则丢弃 */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd:no emergency bearer and not esting emergency bearer");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 仅针对GCF测试进行修改，实际网络下，收到DRB SETUP IND，表示网侧已经放弃了当前的鉴权
    流程，使用当前安全上下文，并且网侧会释放非紧急承载 */
    if(PS_SUCC != LPS_OM_IsTestMode())
    {
        /* 停T3420,T3418*/
        NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
        NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);
    }

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    NAS_EMM_SER_RcvRabmDrbSetupInd(pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept
 Description     : 在AuthInit等待CN消息时ATTACH ACCPET消息
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept_ENUM,LNAS_ENTRY);

    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 栈顶的状态如果不为REG_INIT态，则丢弃 */
    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);
    if (ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept:not reg_init+wait_cn_attach_cnf state!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果当前不是紧急注册过程中，则丢弃 */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGING))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept:not emergency attach");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 停T3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    return NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp(ulMsgId, pMsgStru);
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept
 Description     : 在AuthInit等待CN消息时TAU ACCPET消息
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept_ENUM,LNAS_ENTRY);

    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 栈顶的状态如果不为TAU_INIT态，则丢弃 */
    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);
    if (ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept:not tau_init+wait_cn_tau_cnf state!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果当前没有正在建立紧急承载且没有紧急承载，则丢弃 */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept:no emergency bearer and not esting emergency bearer");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 停T3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    return NAS_EMM_MsTauInitSsWaitCNCnfMsgTAUAcp(ulMsgId, pMsgStru);
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp
 Description     : 在AuthInit等待CN消息时DETACH ACCPET消息
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;
    VOS_UINT32                          ulCurEmmStat    = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp_ENUM,LNAS_ENTRY);

    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* 栈顶的状态如果不为TAU_INIT态，则丢弃 */
    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);
    if ((ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT,EMM_SS_DETACH_WAIT_CN_DETACH_CNF))
        && (ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF)))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp:not dereg_init+wait_cn_detach_cnf and not reg+wait_imsi_detach_cnf state!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 如果当前没有紧急承载，则丢弃 */
    if ((NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp:no emergency bearer");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_DISCARD;
    }

    /* 停T3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTH失败次数清零*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* 状态出栈*/
    NAS_EMM_FSM_PopState();

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);
    if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_DEREG_INIT,
                                                    EMM_SS_DETACH_WAIT_CN_DETACH_CNF))
    {
        return NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp(ulMsgId, pMsgStru);
    }
    else
    {
        return NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp(ulMsgId, pMsgStru);
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf
 Description     : RegInit.WtAttCnf,Reg.Normal_Service,TauInit.WtCnTauCnf,
                   SerInit.WtSerCnf,DeregInit.WtCnDetCnf五种
                   状态下处理PS_USIM_AUTHENTICATION_CNF消息
                   Auts的长度:在EPS系统中固定为14
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-19  Draft Enact
    2.zhaochen    00308719      2015-02-28 Modify for USIM Interface

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf(  VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsg )
{
    USIMM_AUTHENTICATION_CNF_STRU*pstUsimAuthCnf = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf_ENUM,LNAS_ENTRY);
    NAS_LMM_PrintFsmState(NAS_LMM_PARALLEL_FSM_EMM);

    pstUsimAuthCnf = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;
    /* 如果OpId不同，说明在这个鉴权CNF之前又收到了网侧的鉴权请求 ,继续等待USIM回复*/
    if((pstUsimAuthCnf->stCmdResult).ulSendPara!= NAS_EMM_GetSecuAuthOpId())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* 鉴权成功，清空OpId */
    NAS_EMM_GetSecuAuthOpId() = 0;
    /*根据 USIM_AUTH_CNF中的结果进行不同处理*/
    switch(pstUsimAuthCnf->enResult)
    {
             /*USIM鉴权成功*/
        case USIMM_AUTH_UMTS_SUCCESS:
             NAS_EMM_UsimAuthSucc(pstUsimAuthCnf);
             break;

             /*USIM鉴权失败:MAC FAIL*/
        case USIMM_AUTH_MAC_FAILURE:
             /* c00285307 向mmc发卡鉴权失败的消息 begin */
             NAS_EMM_SndMmcSimAuthFailInd(LMM_MMC_SIM_AUTH_FAIL_MAC_FAILURE);
             /* c00285307 向mmc发卡鉴权失败的消息 end */
             NAS_EMM_UsimAuthFail(NAS_EMM_AUTH_MAC_FAILURE);
             break;

             /*USIM鉴权失败:SYNCFAIL*/
        case USIMM_AUTH_SYNC_FAILURE:
             /* c00285307 向mmc发卡鉴权失败的消息 begin */
             NAS_EMM_SndMmcSimAuthFailInd(LMM_MMC_SIM_AUTH_FAIL_SYNC_FAILURE);
             /* c00285307 向mmc发卡鉴权失败的消息 end */

             /*获取USIM_AUTH_CNF携带的AUTS:pstUsimAuthCnf->u.aucAuts第一个字节为Auts的长度*/

             NAS_LMM_MEM_CPY_S( NAS_EMM_GetSecuAuthAutsAddr(),
                                NAS_EMM_SECU_AUTH_AUTS_LEN,
                                &(pstUsimAuthCnf->uCnfData.stTELECnf.aucAuts[NAS_EMM_USIM_CNF_AUTS_V_POS]),
                                pstUsimAuthCnf->uCnfData.stTELECnf.aucAuts[NAS_EMM_USIM_CNF_AUTS_L_POS]);

             /*调用失败处理函数*/
             NAS_EMM_UsimAuthFail(NAS_EMM_AUTH_SYNC_FAILURE);
             break;

        default:
             NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf: USIM CNF RSLT ERR.");
             TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf_ENUM,LNAS_FUNCTION_LABEL1);
             /* c00285307 向mmc发卡鉴权失败的消息 begin */
             NAS_EMM_SndMmcSimAuthFailInd(LMM_MMC_SIM_AUTH_FAIL_OTHER);
             /* c00285307 向mmc发卡鉴权失败的消息 end */
             break;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcAnyStateUsimAuthCnf
 Description     :对USIM返回的鉴权CNF进行预处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.jiqiang   00271914      2014-11-20 Draft Enact
    2.zhaochen  00308719      2015-02-10 Modify for USIM interface
*****************************************************************************/
VOS_VOID NAS_LMM_PreProcAnyStateUsimAuthCnf(const USIMM_AUTHENTICATION_CNF_STRU  *pstUsimAuthCnf)
{
    VOS_UINT32                          ulDeriveKeyRslt;
    USIMM_TELECOM_AUTH_CNF_STRU        *pstAuthCnf;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcAnyStateUsimAuthCnf is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcAnyStateUsimAuthCnf_ENUM,LNAS_ENTRY);

    pstAuthCnf = (USIMM_TELECOM_AUTH_CNF_STRU*)&pstUsimAuthCnf->uCnfData.stTELECnf;

    if( USIMM_AUTH_UMTS_SUCCESS == pstUsimAuthCnf->enResult)
    {
        /*1.更新新安全上下文:保存AuthReq消息携带的Ksi并计算新的Kasme*/
        NAS_EMM_ClearNonCurNativeSecuCntxt();
        NAS_EMM_SetSecuNewNativeKSIasme(NAS_EMM_AuthReqKsi());
        ulDeriveKeyRslt = NAS_EMM_DeriveKasme(&pstAuthCnf->aucCK[1],
                                                  &pstAuthCnf->aucIK[1],
                                                  NAS_EMM_GetSecuNewNativeKasmeAddr());

        if( NAS_EMM_SECU_FAIL == ulDeriveKeyRslt)
        {
            NAS_EMM_SECU_LOG_ERR("NAS_LMM_PreProcAnyStateUsimAuthCnf: Caculate Kasme ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcAnyStateUsimAuthCnf_ENUM,LNAS_ERROR);
        }

        /*安全上下文状态迁移*/
        NAS_EMM_SecuStateConvert(NAS_LMM_GetSecuCurFsmCS() ,EMM_NEW_SECU_EXIST);

        /*2. 启动T3416,保存Rand 和 Res*/
        /*启动T3416*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3416);

        /* 鉴权成功，清空OpId */
        NAS_EMM_GetSecuAuthOpId() = 0;

        /*保存Rand*/
        NAS_EMM_GetSecuAuthOpRand() = NAS_EMM_BIT_SLCT;

        NAS_LMM_MEM_CPY_S(  NAS_EMM_GetSecuAuthRandAddr(),
                            NAS_EMM_SECU_AUTH_RAND_LEN,
                            NAS_EMM_AuthReqRandAddr(),
                            NAS_EMM_SECU_AUTH_RAND_LEN);

        /*保存Res:pstUsimAuthCnf->u.aucAuthRes第一个字节为Res的长度*/
        NAS_EMM_GetSecuAuthResLen() = pstAuthCnf->aucAuthRes[NAS_EMM_USIM_CNF_RES_L_POS];

        NAS_LMM_MEM_CPY_S(  NAS_EMM_GetSecuAuthResVAddr(),
                            NAS_EMM_SECU_MAX_AUTH_RES_LEN,
                            &(pstAuthCnf->aucAuthRes[NAS_EMM_USIM_CNF_RES_V_POS]),
                             NAS_EMM_GetSecuAuthResLen());

    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PreProcUsimAuthCnf
 Description     :在某些场景下，USIM回复鉴权CNF之后，LMM不能成功向网侧发送錫uth_rsp，且
                  LMM不会存储USIM_AUTH_CNF的结果。这个会导致UE收到网侧重发的AUTH_REQ时，
                  LMM将相同的参数又发给USIM，导致USIM计算产生sync 错误。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.jiqiang   00271914      2014-11-11  Draft Enact
    2.zhaochen  00308719      2015-02-10  Modify for USIM interface
*****************************************************************************/
VOS_UINT32 NAS_LMM_PreProcUsimAuthCnf(MsgBlock  *pMsg)
{
    VOS_UINT32                          ulCurEmmStat;
    VOS_UINT32                          ulRslt;
    USIMM_AUTHENTICATION_CNF_STRU       *pstUsimAuthCnf;
    pstUsimAuthCnf = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;


    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ProcUsimAuthCnf is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcUsimAuthCnf_ENUM,LNAS_ENTRY);

    /* 如果OpId不同，说明在这个鉴权CNF之前又收到了网侧的鉴权请求 ,继续等待USIM回复*/
    /* 新的数据结构中，SendPara用来存储OpId */
    if(pstUsimAuthCnf->stCmdResult.ulSendPara != NAS_EMM_GetSecuAuthOpId())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    /* 部分状态下，LMM会对USIM的CNF进行处理，那么在这些状态下LMM不预处理，*/
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                ulRslt = NAS_LMM_MSG_DISCARD;
                break;
        default:
                NAS_LMM_PreProcAnyStateUsimAuthCnf(pstUsimAuthCnf);
                ulRslt = NAS_LMM_MSG_HANDLED;
                break;
    }

    return  ulRslt;
}



/*****************************************************************************
 Function Name   : NAS_EMM_SndMmcSimAuthFailInd
 Description     : 卡鉴权失败 通知MMC
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.chengmin 00285307      2014-11-03  Draft Enact

*****************************************************************************/

VOS_VOID NAS_EMM_SndMmcSimAuthFailInd(LMM_MMC_SIM_AUTH_FAIL_ENUM_UINT16  enSimAuthFailValue)
{
    LMM_MMC_SIM_AUTH_FAIL_IND_STRU    *pstSimAuthFailInd = NAS_EMM_NULL_PTR;
    VOS_UINT32                        ulCompStaOfStackBase;              /*栈底状态*/
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;                    /*主状态*/

    /* 打印进入该函数， INFO_LEVEL */
    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_SndMmcSimAuthFailInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndMmcSimAuthFailInd_ENUM,LNAS_ENTRY);

    /* 申请DOPRA消息 */
    pstSimAuthFailInd = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SIM_AUTH_FAIL_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstSimAuthFailInd)
    {
        NAS_EMM_SECU_LOG_ERR( "NAS_EMM_SndMmcSimAuthFailInd: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndMmcSimAuthFailInd_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 填写DOPRA消息头 */
    /*EMM_PUBU_COMP_MMC_MSG_HEADER(pstSimAuthFailInd, sizeof(LMM_MMC_SIM_AUTH_FAIL_IND_STRU) - EMM_LEN_VOS_MSG_HEADER);*/
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstSimAuthFailInd, NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_SIM_AUTH_FAIL_IND_STRU));

    /* 填写消息ID标识 */
    pstSimAuthFailInd->ulMsgId    = ID_LMM_MMC_SIM_AUTH_FAIL_IND;

    pstSimAuthFailInd->enSimAuthFailValue          = enSimAuthFailValue;
    pstSimAuthFailInd->enSrvDomain                 = LMM_MMC_SRV_DOMAIN_PS;

    enMainState = NAS_LMM_GetEmmCurFsmMS();

    /*卡鉴权失败时所处service domain默认为PS，下列情况下为CS_PS*/
    if ((EMM_MS_REG_INIT == enMainState && MMC_LMM_ATT_REQ_TYPE_CS_PS == NAS_EMM_GLO_GetAttReqType())
         || (EMM_MS_TAU_INIT == enMainState && NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING == NAS_EMM_TAU_GetTAUtype())
         || (EMM_MS_TAU_INIT == enMainState && NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
    {
        pstSimAuthFailInd->enSrvDomain             = LMM_MMC_SRV_DOMAIN_CS_PS;

        NAS_EMM_SECU_LOG_INFO( "attach or tau state send mmc msg");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndMmcSimAuthFailInd_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstSimAuthFailInd);
        /*NAS_LMM_SEND_MSG(pstSimAuthFailInd);*/

        return;
    }

    /*如果是鉴权压栈的情况，栈底状态为attach或tau时*/
    ulCompStaOfStackBase = NAS_LMM_FSM_GetStaAtStackBase(NAS_LMM_PARALLEL_FSM_EMM);
    if ((EMM_MS_REG_INIT == ulCompStaOfStackBase && MMC_LMM_ATT_REQ_TYPE_CS_PS == NAS_EMM_GLO_GetAttReqType())
         || (EMM_MS_TAU_INIT == ulCompStaOfStackBase && NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING == NAS_EMM_TAU_GetTAUtype())
         || (EMM_MS_TAU_INIT == ulCompStaOfStackBase && NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
    {
        pstSimAuthFailInd->enSrvDomain             = LMM_MMC_SRV_DOMAIN_CS_PS;

        NAS_EMM_SECU_LOG_INFO( "stack bottom attach or tau state send mmc msg");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndMmcSimAuthFailInd_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstSimAuthFailInd);
        /*NAS_LMM_SEND_MSG(pstSimAuthFailInd);*/

        return;
    }

}


/*****************************************************************************
 Function Name   : NAS_EMM_PUBM_ClearResource
 Description     : DETACH后，
                    当前运行的安全上下文参数，状态转换时，
                    进入DEREG后，清除新安全上下文参数，
                    修改当前安全上下文状态，
                    不在这里处理，在函数NAS_EMM_AuthClearNewSecuContext处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1. h41410 DRAFT 2010 10 15

*****************************************************************************/
VOS_VOID    NAS_EMM_SECU_ClearResource(VOS_VOID)
{
    NAS_EMM_SECU_LOG_NORM("NAS_EMM_SECU_ClearResource: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SECU_ClearResource_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuUsimAuthParamAddr(),
                        sizeof(NAS_LMM_USIM_AUTH_PARAM_STRU),
                        0,
                        sizeof(NAS_LMM_USIM_AUTH_PARAM_STRU));

    NAS_EMM_GetSmcType() = NAS_EMM_SMC_UPDATE_BUTT;

    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuSrcSpace(),
                        LRRC_LNAS_MAX_DATA_LENGTH,
                        0,
                        LRRC_LNAS_MAX_DATA_LENGTH);

    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuDstSpace(),
                        LRRC_LNAS_MAX_DATA_LENGTH,
                        0,
                        LRRC_LNAS_MAX_DATA_LENGTH);

    NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuBufSpace(),
                        LRRC_LNAS_MAX_DATA_LENGTH,
                        0,
                        LRRC_LNAS_MAX_DATA_LENGTH);
    NAS_LMM_MEM_SET_S(  NAS_EMM_GetAuthReqParamAddr(),
                        sizeof(NAS_LMM_AUTH_REQ_PARAM_STRU),
                        0,
                        sizeof(NAS_LMM_AUTH_REQ_PARAM_STRU));

    NAS_EMM_AuthReqKsi() = NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE;

    NAS_EMM_GetAuthFailTimes() = 0;

    return;
}
/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

