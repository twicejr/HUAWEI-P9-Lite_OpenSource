/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmSecuProtect.c
  Description     :
  History         :
        1. zhengjunyan 00148421 2010-03-02 Draft Enact
        2. zhengjunyan 00148421 2011-03-16 MOD:底层接口由 L2修改为CIPHER提供
        3. zhengjunyan 00148421 2011-04-22 MOD:支持G/U模式
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmSecuInclude.h"
#include    "NasLmmPubMPrint.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSECUPROTECT_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSECUPROTECT_C
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

/*状态事件动作表
typedef VOS_UINT32 ( * NAS_LMM_ACTION_FUN )
(
    VOS_UINT32, 安全头类型
    VOS_VOID *  RRC_NAS_MSG_STRU类型的码流，包括: CN消息长度和CN的消息码流
);
*/

/* EMM_CUR_SECU_NOT_EXIST BEGIN ===================================*/
/*================= EMM_NEW_SECU_NOT_EXIST ========================*/
NAS_EMM_ACT_STRU    g_astEmmCurNoExistNewNotExistTable[] =
{
    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_PLAIN,
                        NAS_EMM_CurNotActiveNewAnyMsgPlain),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_INTEGRITY,
                        NAS_EMM_CurNotActiveNewAnyMsgInt),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY,
                        NAS_EMM_CurNotExistNewNotExistMsgSmc)
};
/*================= EMM_NEW_SECU_EXIST ========================*/
NAS_EMM_ACT_STRU    g_astEmmCurNoExistNewExistTable[] =
{
    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_PLAIN,
                        NAS_EMM_CurNotActiveNewAnyMsgPlain),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_INTEGRITY,
                        NAS_EMM_CurNotActiveNewAnyMsgInt),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY,
                        NAS_EMM_CurAnyNewExistMsgSmc)
};

/* EMM_CUR_SECU_EXIST_NOT_ACTIVE BEGIN ===================================*/
/*================= EMM_NEW_SECU_NOT_EXIST ========================*/
NAS_EMM_ACT_STRU    g_astEmmCurExistNotActiveNewNotExistTable[] =
{
    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_PLAIN,
                        NAS_EMM_CurNotActiveNewAnyMsgPlain),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_INTEGRITY,
                        NAS_EMM_CurNotActiveNewAnyMsgInt),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_INTEGRITY_CIPHERED,
                        NAS_EMM_CurExistNotAcitveNewAnyMsgIntEnc),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY,
                        NAS_EMM_OnlyCurExistMsgSmc)
};
/*================= EMM_NEW_SECU_EXIST ============================*/
NAS_EMM_ACT_STRU    g_astEmmCurExistNotActiveNewExistTable[] =
{
    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_PLAIN,
                        NAS_EMM_CurNotActiveNewAnyMsgPlain),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_INTEGRITY,
                        NAS_EMM_CurNotActiveNewAnyMsgInt),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_INTEGRITY_CIPHERED,
                        NAS_EMM_CurExistNotAcitveNewAnyMsgIntEnc),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY,
                        NAS_EMM_CurAnyNewExistMsgSmc)
};

/* EMM_CUR_SECU_EXIST_ACTIVE BEGIN ===================================*/
/*================= EMM_NEW_SECU_NOT_EXIST ========================*/
NAS_EMM_ACT_STRU    g_astEmmCurExistActiveNewNotExistTable[] =
{
    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_PLAIN,
                        NAS_EMM_CurExistActiveNewAnyMsgPlain),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_INTEGRITY_CIPHERED,
                        NAS_EMM_CurExistActiveNewAnyMsgIntEnc),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY,
                        NAS_EMM_OnlyCurExistMsgSmc)
};
/*================= EMM_NEW_SECU_EXIST ============================*/
NAS_EMM_ACT_STRU    g_astEmmCurExistActiveNewExistTable[] =
{
    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_PLAIN,
                        NAS_EMM_CurExistActiveNewAnyMsgPlain),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_INTEGRITY_CIPHERED,
                        NAS_EMM_CurExistActiveNewAnyMsgIntEnc),

    NAS_EMM_SECU_ACT_TBL_ITEM(
                        NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY,
                        NAS_EMM_CurAnyNewExistMsgSmc)
};

/* 状态转移表 */
NAS_EMM_STA_STRU     g_astEmmSecuStaTbl[] =
{
/*================= EMM_CUR_SECU_NOT_EXIST 状态机的描述表 ========*/
    NAS_LMM_STA_TBL_ITEM(EMM_CUR_SECU_NOT_EXIST,
                        EMM_NEW_SECU_NOT_EXIST,
                        g_astEmmCurNoExistNewNotExistTable),

    NAS_LMM_STA_TBL_ITEM(EMM_CUR_SECU_NOT_EXIST,
                        EMM_NEW_SECU_EXIST,
                        g_astEmmCurNoExistNewExistTable),

/*================= EMM_CUR_SECU_EXIST_NOT_ACTIVE 状态机的描述表 ========*/
    NAS_LMM_STA_TBL_ITEM(EMM_CUR_SECU_EXIST_NOT_ACTIVE,
                        EMM_NEW_SECU_NOT_EXIST,
                        g_astEmmCurExistNotActiveNewNotExistTable),

    NAS_LMM_STA_TBL_ITEM(EMM_CUR_SECU_EXIST_NOT_ACTIVE,
                        EMM_NEW_SECU_EXIST,
                        g_astEmmCurExistNotActiveNewExistTable),

/*================= EMM_CUR_SECU_EXIST_ACTIVE 状态机的描述表 ========*/
    NAS_LMM_STA_TBL_ITEM(EMM_CUR_SECU_EXIST_ACTIVE,
                        EMM_NEW_SECU_NOT_EXIST,
                        g_astEmmCurExistActiveNewNotExistTable),

    NAS_LMM_STA_TBL_ITEM(EMM_CUR_SECU_EXIST_ACTIVE,
                        EMM_NEW_SECU_EXIST,
                        g_astEmmCurExistActiveNewExistTable),


};

#if (VOS_OS_VER == VOS_WIN32)
NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_PRINT_STR_STRU  g_LmmSecuFailTypePrintTable[] =
{
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_SPECIAL_NAS_MSG            , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_SPECIAL_NAS_MSG"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_EIA0                       , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_EIA0"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_INT_CHECK_FAIL                 , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_INT_CHECK_FAIL"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECRYPT_FAIL                   , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECRYPT_FAIL"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_REJ_PLAIN_MSG                  , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_REJ_PLAIN_MSG"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_PD_EMM                     , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_PD_EMM"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_SMC                        , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_SMC"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_EIA0_NO_EMC_PDN                , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_EIA0_NO_EMC_PDN"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL                    , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_KSI_MISMATCH                   , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_KSI_MISMATCH"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ALG_NOT_SUPPORT                , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ALG_NOT_SUPPORT"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_UE_CAP_MISMATCH                , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_UE_CAP_MISMATCH"},
    {NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NONCE_MISMATCH                 , "NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NONCE_MISMATCH"}
};

const VOS_UINT32 g_LmmSecuFailTypePrintTableSize =
              (sizeof(g_LmmSecuFailTypePrintTable)/sizeof(NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_PRINT_STR_STRU));
#endif



/* 删除TAU消息加密的相关无效配置代码 y00307272 20151017 DTS2015101700432 */


/* 安全激活场景下能否处理明文REJ空口消息: 0为不能处理，1为能处理。默认为不处理 */
VOS_UINT32  g_ulNasPlainRejMsgFlag  = 0;

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_LMM_SECU_FsmErr
 Description     : 安全上下文状态机出错处理回调函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-4  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_SECU_FsmErr(         VOS_UINT32           ulMsgId,
                                        VOS_VOID      *PMsg)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)PMsg;

    return NAS_EMM_SECU_UNPROT_FAIL;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SECU_FsmReg
 Description     : 安全上下文状态机注册函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-4  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_SECU_FsmReg(VOS_VOID)
{
    VOS_UINT32                          ulRslt;

    ulRslt                              = NAS_LMM_FAIL;

    /* 注册状态机 */
    ulRslt = NAS_LMM_FsmRegisterFsm(NAS_LMM_PARALLEL_FSM_SECU,
                                   (sizeof(g_astEmmSecuStaTbl)/sizeof(NAS_LMM_STA_STRU)),
                                   g_astEmmSecuStaTbl,
                                   NAS_LMM_SECU_FsmErr);
    if (ulRslt != NAS_LMM_SUCC)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_LMM_SECU_FsmReg:ERROR:register fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SECU_FsmReg_ENUM,LNAS_FAIL);
    }
    else
    {
        NAS_EMM_SECU_LOG_INFO("NAS_LMM_SECU_FsmReg!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_SECU_FsmReg_ENUM,LNAS_SUCC);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuStateConvert
 Description     : 安全上下文状态转换函数
 Input           : usCurSta:当前安全上下文目标状态
                   usNewSta:新安全上下文目标状态
 Output          : None
 Return          : None

 History         :
    1.zhengjunyan 00148421      2010-3-4  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuStateConvert(NAS_EMM_MAIN_STATE_ENUM_UINT16 usCurSta,
                                   NAS_EMM_SUB_STATE_ENUM_UINT16 usNewSta )
{
    NAS_EMM_FSM_STATE_STRU              stDestState;

    stDestState.enFsmId                 = NAS_LMM_PARALLEL_FSM_SECU;
    stDestState.enMainState             = usCurSta;
    stDestState.enSubState              = usNewSta;
    stDestState.enStaTId                = NAS_LMM_STATE_TI_BUTT;

    /*状态机迁移*/
    NAS_LMM_FsmTranState(stDestState);
    /*NAS_LMM_StaTransProc(stDestState);*/
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsSpecNasMsg
 Description     : 判断收到的消息是不是NAS特权消息
 Input           : pucRcvNasMsg:明文消息
                   pulNasMsgSize:明文消息的长度
 Output          : None
 Return          : VOS_TRUE: 是特权消息
                   VOS_FALSE:不是特权消息

 History         :
    1.zhengjunyan 00148421      2010-3-4  Draft Enact
    2.zhengjunyan 00148421      2011-12-23 DTS2011122103346:REJ #25不作为特权消息
*****************************************************************************/
VOS_BOOL NAS_EMM_IsSpecNasMsg(          const VOS_UINT8     *pucRcvNasMsg,
                                        VOS_UINT32          *pulNasMsgSize)
{
    VOS_UINT8                           ucEmmMsgType = 0;
    VOS_UINT8                           ucIdenTypeId = 0;
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucRejCauseVal = NAS_LMM_CAUSE_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_IsSpecNasMsg entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSpecNasMsg_ENUM,LNAS_ENTRY);
    (VOS_VOID)pulNasMsgSize;

    /*如果不是EMM的消息，则不是特权消息*/
    if(EMM_CN_MSG_PD_EMM != pucRcvNasMsg[NAS_EMM_SECU_CN_MSG_HEAD_POS])
    {
        NAS_EMM_SECU_LOG_INFO("Nas_Emm_IsSpcNasMsg: NOT EMM MSG.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSpecNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return VOS_FALSE;
    }

    /*获取空口消息类型*/
    ucEmmMsgType = pucRcvNasMsg[NAS_EMM_SECU_CN_MSG_TYPE_POS];

    /*24301-821-4.4.4.2:判断NAS特权消息*/
    switch(ucEmmMsgType)
    {
        case NAS_EMM_CN_MT_AUTH_REQ:
        case NAS_EMM_CN_MT_AUTH_REJ:
        case NAS_EMM_CN_MT_DETACH_ACP_MO:
            return VOS_TRUE;

        /*ATTACH/TAU/SERVICE REJ #25不是特权消息，其他原因值都作为特权消息处理*/
        case NAS_EMM_CN_MT_ATTACH_REJ:
        case NAS_EMM_CN_MT_TAU_REJ:
        case NAS_EMM_CN_MT_SER_REJ:
            ucRejCauseVal = pucRcvNasMsg[NAS_EMM_SECU_REJ_CAUSE_POS];
            if(NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG == ucRejCauseVal)
            {
                NAS_EMM_SECU_LOG_INFO("Nas_Emm_IsSpcNasMsg: REJ #25不是特权消息.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSpecNasMsg_ENUM,LNAS_FUNCTION_LABEL2);
                return VOS_FALSE;
            }
            else
            {
                return VOS_TRUE;
            }

        case NAS_EMM_CN_MT_IDEN_REQ:
            ucIdenTypeId = pucRcvNasMsg[NAS_EMM_SECU_IDEN_REQ_TYPE_POS]
                         & NAS_EMM_LOW_3_BITS_F;
            if(NAS_EMM_MOBILE_ID_IMSI == ucIdenTypeId)
            {
                return VOS_TRUE;
            }
            else
            {
                NAS_EMM_SECU_LOG_INFO("Nas_Emm_IsSpcNasMsg: IDEN REQ不是查询IMSI，不是特权消息.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSpecNasMsg_ENUM,LNAS_FUNCTION_LABEL3);
                return VOS_FALSE;
            }

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_CompDlNasCount
 Description     : 获得新的DL_NASCOUNT
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-9  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_CompDlNasCount(
                                        VOS_UINT32  ulLocDlNasCount,
                                        VOS_UINT8   ucRcvSn )
{
    VOS_UINT8                       ucLocDlCountLowByte;
    VOS_UINT32                      ulDlForUnprot = 0;
    VOS_UINT32                      ucLocDlCountHighByte;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_CompDlNasCount enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CompDlNasCount_ENUM,LNAS_ENTRY);

    /* 获取本地 NAS DL COUNT的低字节 */
    ulDlForUnprot = ulLocDlNasCount;

    /* 获取 Local_DlNascount的最低字节:SN*/
    ucLocDlCountLowByte     = ulDlForUnprot & NAS_EMM_SECU_MASK_NAS_COUNT_SQN;

    /* LOCAL SQN大于等于窗体时，如果LOCAL SQN大于RCV SQN并且LOCAL SQN减
    去RCV SQN大于窗体则COUNT高位加1，其他情况正常处理。LOCAL SQN小于窗体时，
    如果COUNT值高位大于0,LOCAL SQN小于RCV SQN并且RCV SQN减去LOCAL SQN大于0xFF减
    去窗体则高位减去1，其他情况正常处理 */
    ucLocDlCountHighByte    = ulDlForUnprot & NAS_EMM_SECU_MASK_OVERFLOW_COUNT;
    if(ucLocDlCountLowByte >= NAS_EMM_SECU_DL_COUNT_WINDOW)
    {
        if((ucLocDlCountLowByte > ucRcvSn)
            &&(ucLocDlCountLowByte - ucRcvSn > NAS_EMM_SECU_DL_COUNT_WINDOW))

        {
            ulDlForUnprot += NAS_EMM_SECU_COUNT_FLOW_OFFSET;
        }
    }
    else
    {
        if((ucLocDlCountHighByte > 0)
            &&(ucRcvSn>ucLocDlCountLowByte)
            &&(ucRcvSn - ucLocDlCountLowByte >= (0xFF-NAS_EMM_SECU_DL_COUNT_WINDOW)))
        {
             ulDlForUnprot -= NAS_EMM_SECU_COUNT_FLOW_OFFSET;
        }
    }

    /* 清空最低字节 */
    ulDlForUnprot &= NAS_EMM_SECU_MASK_OVERFLOW_COUNT;

    /* 最低字节赋值为收到的SN */
    ulDlForUnprot += ucRcvSn;

    return ulDlForUnprot;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuIntCheck
 Description     : 对收到的空口消息进行完整性检查
 Input           : pucRcvCnNasMsg: 带安全头的NAS消息
                   pstUnProtParam->pucMsg       : 头类型+MAC+SN+MSG
                   pstUnProtParam->pulMsgSize   : 头类型+MAC+SN+MSG 的长度
 Output          : pstUnProtParam->pucMsg       : MSG
                   pstUnProtParam->pulMsgSize   : MSG 的长度
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-9  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_SecuIntCheck( const NAS_EMM_PROT_PARAM_STRU   *pstUnProtParam)
{
/*PC环境:如果消息携带的MAC不是aucPcMac,认为完整性检查失败*/
#if(VOS_WIN32 == VOS_OS_VER)
    #ifdef PS_ITT_PC_TEST_NAS_ST
    VOS_UINT8                           aucPcMac[] = {0x5D, 0x22, 0x11, 0x02};
    #else
    VOS_UINT8                           aucPcMac[] = {0x02, 0x11, 0x22, 0x5D};
    #endif
    VOS_UINT8                          *pucMacOfMsg = VOS_NULL_PTR;

    pucMacOfMsg = &(pstUnProtParam->pucMsg[NAS_EMM_SECU_MAC_POS]);
    if(NAS_EMM_SECU_MEM_CMP_EQUAL !=  NAS_LMM_MEM_CMP(pucMacOfMsg,
                                                     aucPcMac,
                                                     NAS_EMM_SECU_MAC_LEN))
    {
        return NAS_EMM_SECU_FAIL;
    }

/* 单板环境*/
#else
     CIPHER_SINGLE_CFG_S                 stSingleSecuPara;
     VOS_INT32                           lRslt;
     VOS_UINT8                          *pucSrcAddr = VOS_NULL_PTR;
     VOS_UINT8                          *pucDstAddr = VOS_NULL_PTR;

     /* 若是完整性空算法，则去掉安全头，然后返回 */
     if(PS_SECU_ALG_NULL == pstUnProtParam->ucSecuALg)
     {
         NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuIntCheck: ALG is NULL_ALG.");
         TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuIntCheck_ENUM,LNAS_FUNCTION_LABEL1);

         NAS_EMM_SecuDelSecuHead(pstUnProtParam->pucMsg,pstUnProtParam->pulMsgSize);

         return  NAS_EMM_SECU_SUCC;
     }

     /* 完整性检查，参数赋值*/
     NAS_LMM_MEM_SET_S( &stSingleSecuPara,
                        sizeof(CIPHER_SINGLE_CFG_S),
                        0,
                        sizeof(CIPHER_SINGLE_CFG_S));

     stSingleSecuPara.enOpt = CIPHER_OPT_CHECK_PRE_LMAC;
     stSingleSecuPara.u8Direction = NAS_EMM_SECU_DNLINK;
     stSingleSecuPara.u32Count = pstUnProtParam->ulNasCount;
     stSingleSecuPara.u32BlockLen = (*pstUnProtParam->pulMsgSize)
                                             - NAS_EMM_SECU_HEADER_LEN;
     stSingleSecuPara.stAlgKeyInfo.u32KeyIndexInt = LTE_SECU_NAS_INTEGRITY_KEY_INDEX;


     stSingleSecuPara.stAlgKeyInfo.enAlgIntegrity
                                = NAS_EMM_GetIntegrityAlg(pstUnProtParam->ucSecuALg);

     stSingleSecuPara.u8BearId = NAS_EMM_SECU_SECURITY_BEARERID;
     stSingleSecuPara.bMemBlock = PS_TRUE;
     stSingleSecuPara.enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     stSingleSecuPara.enHeaderLen = CIPHER_HDR_BIT_TYPE_0;

     pucSrcAddr = NAS_EMM_GetSecuSrcSpace();
     NAS_LMM_MEM_CPY_S( pucSrcAddr,
                        LRRC_LNAS_MAX_DATA_LENGTH,
                        &(pstUnProtParam->pucMsg[NAS_EMM_SECU_MAC_POS]),
                        stSingleSecuPara.u32BlockLen);
     pucDstAddr = NAS_EMM_NULL_PTR;

     /*打印Cipher参数*/
     NAS_EMM_SecuPrintCipherPara(&stSingleSecuPara, pucSrcAddr);

     stSingleSecuPara.pInMemMgr = (VOS_VOID *)pucSrcAddr;
     stSingleSecuPara.pOutMemMgr = (VOS_VOID *)pucDstAddr;

     /* 调用BSP接口解保护*/
     lRslt = NAS_CIPHER_SingleSubmitTask(&stSingleSecuPara);
     if (CIPHER_SUCCESS != lRslt)
     {
         NAS_EMM_SECU_LOG1_ERR("NAS_EMM_SecuIntCheck:mdrv_cipher_single_submit_task fail.lRslt = ",
                                  lRslt);
         TLPS_PRINT2LAYER_ERROR1(NAS_EMM_SecuIntCheck_ENUM,LNAS_FUNCTION_LABEL2,lRslt);
         return NAS_EMM_SECU_FAIL;
     }

    /*单板环境完整性检查正确，需要继续将MAC头去掉*/

#endif

    NAS_EMM_SecuDelSecuHead(pstUnProtParam->pucMsg,pstUnProtParam->pulMsgSize);

    return NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuDecrypt
 Description     : 解密
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuDecrypt(const NAS_EMM_PROT_PARAM_STRU   *pstUnProtParam)
{

/* 单板环境比PC环境多出来的操作 */
#if(VOS_WIN32 != VOS_OS_VER)
    CIPHER_SINGLE_CFG_S                 stSingleSecuPara;
    VOS_INT32                           lRslt;
    VOS_UINT8                          *pucSrcAddr = VOS_NULL_PTR;
    VOS_UINT8                          *pucDstAddr = VOS_NULL_PTR;

    /* 若是空算法，则直接返回 */
    if(PS_SECU_ALG_NULL == pstUnProtParam->ucSecuALg)
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuDecrypt: ALG is NULL_ALG.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuDecrypt_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_EMM_SECU_SUCC;
    }

    /* 消息解密，参数赋值*/
    NAS_LMM_MEM_SET_S(&stSingleSecuPara, sizeof(CIPHER_SINGLE_CFG_S), 0, sizeof(CIPHER_SINGLE_CFG_S));

    stSingleSecuPara.enOpt = CIPHER_OPT_DECRYPT;
    stSingleSecuPara.u8Direction = NAS_EMM_SECU_DNLINK;
    stSingleSecuPara.u32Count = pstUnProtParam->ulNasCount;
    stSingleSecuPara.u32BlockLen = *(pstUnProtParam->pulMsgSize);
    stSingleSecuPara.stAlgKeyInfo.u32KeyIndexSec = LTE_SECU_NAS_CIPHER_KEY_INDEX;

    stSingleSecuPara.stAlgKeyInfo.enAlgSecurity
                                = NAS_EMM_GetSecurityAlg(pstUnProtParam->ucSecuALg);
    stSingleSecuPara.u8BearId = NAS_EMM_SECU_SECURITY_BEARERID;
    stSingleSecuPara.bMemBlock = PS_TRUE;
    stSingleSecuPara.enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    stSingleSecuPara.enHeaderLen = CIPHER_HDR_BIT_TYPE_0;

    pucSrcAddr = NAS_EMM_GetSecuSrcSpace();
    NAS_LMM_MEM_CPY_S(  pucSrcAddr,
                        LRRC_LNAS_MAX_DATA_LENGTH,
                        pstUnProtParam->pucMsg,
                        *(pstUnProtParam->pulMsgSize));
    pucDstAddr = NAS_EMM_GetSecuDstSpace();

    stSingleSecuPara.pInMemMgr = (VOS_VOID *)pucSrcAddr;
    stSingleSecuPara.pOutMemMgr = (VOS_VOID *)pucDstAddr;

    /*打印Cipher参数*/
    NAS_EMM_SecuPrintCipherPara(&stSingleSecuPara, pucSrcAddr);

    /* 调用BSP接口解保护*/
    lRslt = NAS_CIPHER_SingleSubmitTask(&stSingleSecuPara);
    if (CIPHER_SUCCESS != lRslt)
    {
        NAS_EMM_SECU_LOG1_ERR("NAS_EMM_SecuDecrypt:mdrv_cipher_single_submit_task fail.lRslt = ",
                                 lRslt);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_SecuDecrypt_ENUM,LNAS_FUNCTION_LABEL2,
                                 lRslt);
        return NAS_EMM_SECU_FAIL;
    }

    /*将明文拷贝到Dopra消息 */
    *(pstUnProtParam->pulMsgSize)       = stSingleSecuPara.u32BlockLen;
    NAS_LMM_MEM_CPY_S(                  pstUnProtParam->pucMsg,
                                        stSingleSecuPara.u32BlockLen,
                                        NAS_EMM_GetSecuDstSpace(),
                                        stSingleSecuPara.u32BlockLen);


#endif

    return NAS_EMM_SECU_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SecuDelSecuHead
 Description     : 去掉空口消息中的安全头
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuDelSecuHead(VOS_UINT8          *pucRcvCnNasMsg,
                                 VOS_UINT32         *pulNasMsgSize)
{
    /*获取明文消息*/
    *pulNasMsgSize = *pulNasMsgSize - NAS_EMM_SECU_MSG_HEAD_LEN;
    /*安全函数TLPS_MEM_CPY_S 要求源地址和目的地址不重叠，改用NAS_LMM_MEM_MOVE_S */
    NAS_LMM_MEM_MOVE_S(  pucRcvCnNasMsg,
                        *pulNasMsgSize,
                        &pucRcvCnNasMsg[NAS_EMM_SECU_PLAIN_MSG_POS],
                        *pulNasMsgSize);
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_IntEncMsgCommProc
 Description     : 完整性保护并且加密的消息统一处理函数
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IntEncMsgCommProc( LRRC_LNAS_MSG_STRU *pstNasMsg )
{

    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;
    VOS_UINT32                          ulDlForUnprot = 0;
    NAS_EMM_PROT_PARAM_STRU             stUnProtParam;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_IntEncMsgCommProc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IntEncMsgCommProc_ENUM,LNAS_ENTRY);

    /*计算DL_NASCOUNT*/
    /*lint -e416 -e415*/
    ulDlForUnprot = NAS_EMM_CompDlNasCount(NAS_EMM_GetSecuDlNasCount(),
                                 pstNasMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS]);
    /*lint +e416 +e415*/

    /*填写完整性检查需要的参数*/
    stUnProtParam.ulNasCount            = ulDlForUnprot;
    stUnProtParam.ucSecuALg             = NAS_EMM_GetSecuEia();
    /*stUnProtParam.pucNasKey             = NAS_EMM_GetSecuCurNasIkAddr();*/
    stUnProtParam.pucMsg                = pstNasMsg->aucNasMsg;
    stUnProtParam.pulMsgSize            = &(pstNasMsg->ulNasMsgSize);

    /*完整性检查*/
    ulRslt = NAS_EMM_SecuIntCheck(&stUnProtParam);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SndOmLogEpsSecContextInfo();
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_INT_CHECK_FAIL,
                                       0);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IntEncMsgCommProc_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_FAIL;
    }

    /*完整性检查通过，则接受本次DL_NASCOUNT*/
    /* 计算的count值大于本地count值才更新 */
    if(ulDlForUnprot > NAS_EMM_GetSecuDlNasCount())
    {
        NAS_EMM_GetSecuDlNasCount() = ulDlForUnprot;
    }
    /*填写解密需要的参数,*/
    stUnProtParam.ulNasCount            = ulDlForUnprot;
    stUnProtParam.ucSecuALg             = NAS_EMM_GetSecuEca();
    /*stUnProtParam.pucNasKey             = NAS_EMM_GetSecuCurNasCkAddr();*/
    stUnProtParam.pucMsg                = pstNasMsg->aucNasMsg;
    stUnProtParam.pulMsgSize            = &(pstNasMsg->ulNasMsgSize);

    /*解密*/
    ulRslt = NAS_EMM_SecuDecrypt(&stUnProtParam);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        NAS_EMM_SndOmLogEpsSecContextInfo();

        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECRYPT_FAIL,
                                       0);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IntEncMsgCommProc_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    return NAS_EMM_SECU_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CurNotActiveNewAnyMsgPlain
 Description     : 状态:
                     1)EMM_CUR_SECU_NOT_EXIST.EMM_NEW_SECU_ANY
                     2)EMM_CUR_SECU_EXIST_NOT_ACTIVE.EMM_NWW_SECU_ANY
                   消息:
                     明文消息(0x07)
 Input           : pulRrcNasMsg:指向RRC_NAS_MSG_STRU
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-4  Draft Enact

*****************************************************************************/
NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32  NAS_EMM_CurNotActiveNewAnyMsgPlain(
                                        VOS_UINT32  ulSecuHeadType,
                                        VOS_VOID   *pulRrcNasMsg)
{
    VOS_BOOL                            bRlst =  VOS_FALSE;
    LRRC_LNAS_MSG_STRU                   *pstNasMsg = VOS_NULL_PTR;

    (VOS_VOID)ulSecuHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_CurNotActiveNewAnyMsgPlain enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CurNotActiveNewAnyMsgPlain_ENUM,LNAS_ENTRY);

    pstNasMsg = (LRRC_LNAS_MSG_STRU *)pulRrcNasMsg;

    /*判断是不是特权消息*/
    bRlst = NAS_EMM_IsSpecNasMsg(       pstNasMsg->aucNasMsg,
                                        &(pstNasMsg->ulNasMsgSize));
    if(VOS_FALSE == bRlst)
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_SPECIAL_NAS_MSG,
                                       pstNasMsg->aucNasMsg[NAS_EMM_SECU_CN_MSG_TYPE_POS]);
        return NAS_EMM_SECU_UNPROT_FAIL;
    }

    return NAS_EMM_SECU_UNPROT_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CurNotActiveNewAnyMsgInt
 Description     : 没有安全连接的情况下收到完整性保护的消息，判断是特权消息则
                   获取明文，否则丢弃。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-9  Draft Enact

*****************************************************************************/
NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32  NAS_EMM_CurNotActiveNewAnyMsgInt(
                                        VOS_UINT32  ulSecuHeadType,
                                        VOS_VOID   *pulRrcNasMsg)
{
    VOS_BOOL                            bRlst =  VOS_FALSE;
    LRRC_LNAS_MSG_STRU                   *pstNasMsg = VOS_NULL_PTR;

    (VOS_VOID)ulSecuHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_CurNotActiveNewAnyMsgInt enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CurNotActiveNewAnyMsgInt_ENUM,LNAS_ENTRY);

    pstNasMsg = (LRRC_LNAS_MSG_STRU *)pulRrcNasMsg;

    /*完整性保护的消息，去掉安全头*/
    NAS_EMM_SecuDelSecuHead(pstNasMsg->aucNasMsg, &(pstNasMsg->ulNasMsgSize));

    /*判断是不是特权消息*/
    bRlst = NAS_EMM_IsSpecNasMsg(       pstNasMsg->aucNasMsg,
                                        &(pstNasMsg->ulNasMsgSize));
    if(VOS_FALSE == bRlst)
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_SPECIAL_NAS_MSG,
                                       pstNasMsg->aucNasMsg[NAS_EMM_SECU_CN_MSG_TYPE_POS]);
        return NAS_EMM_SECU_UNPROT_FAIL;
    }

    return NAS_EMM_SECU_UNPROT_SUCC;

}

/*****************************************************************************
 Function Name   : NAS_EMM_CurExistNotAcitveNewAnyMsgIntEnc
 Description     : 当前安全上下文存在但是没有激活的情况下，收到完整性保护并
                   且加密的消息，如果完整性检查和解密都通过，则恢复安全连接
                   ；否则丢弃。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-9  Draft Enact

*****************************************************************************/
NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32  NAS_EMM_CurExistNotAcitveNewAnyMsgIntEnc(
                                        VOS_UINT32  ulSecuHeadType,
                                        VOS_VOID   *pulRrcNasMsg)
{
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;
    LRRC_LNAS_MSG_STRU                   *pstNasMsg = VOS_NULL_PTR;

    (VOS_VOID)ulSecuHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_CurExistNotAcitveNewAnyMsgIntEnc enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CurExistNotAcitveNewAnyMsgIntEnc_ENUM,LNAS_ENTRY);

    pstNasMsg = (LRRC_LNAS_MSG_STRU *)pulRrcNasMsg;

    /*完整性检查,解密*/
    ulRslt = NAS_EMM_IntEncMsgCommProc(pstNasMsg);
    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        return NAS_EMM_SECU_UNPROT_FAIL;
    }

    /*安全上下文状态迁移*/
    NAS_EMM_SecuStateConvert(EMM_CUR_SECU_EXIST_ACTIVE,NAS_LMM_GetSecuCurFsmNS());

    return NAS_EMM_SECU_UNPROT_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CurExistActiveNewAnyMsgIntEnc
 Description     : 安全连接存在的情况下，收到完整性保护且加密的消息，解保护
                   ，解密。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-9  Draft Enact

*****************************************************************************/
NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32  NAS_EMM_CurExistActiveNewAnyMsgIntEnc(
                                        VOS_UINT32  ulSecuHeadType,
                                        VOS_VOID   *pulRrcNasMsg)
{
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;
    LRRC_LNAS_MSG_STRU                   *pstNasMsg = VOS_NULL_PTR;

    (VOS_VOID)ulSecuHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_CurExistActiveNewAnyMsgIntEnc enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CurExistActiveNewAnyMsgIntEnc_ENUM,LNAS_ENTRY);

    pstNasMsg = (LRRC_LNAS_MSG_STRU *)pulRrcNasMsg;

    /*完整性检查,解密*/
    ulRslt = NAS_EMM_IntEncMsgCommProc(pstNasMsg);

    if(NAS_EMM_SECU_FAIL == ulRslt)
    {
        return NAS_EMM_SECU_UNPROT_FAIL;
    }

    return NAS_EMM_SECU_UNPROT_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_CurExistActiveNewAnyMsgPlain
 Description     : 安全连接存在的情况下，收到明文的消息，根据当前NV设置以及是否是
                   特权消息决定是否处理，特权消息仅为:
                   ATTACH REJ, TAU REJ ,SER REJ.
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2014-05-30  Draft Enact

*****************************************************************************/
NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32  NAS_EMM_CurExistActiveNewAnyMsgPlain(
                                        VOS_UINT32  ulSecuHeadType,
                                        VOS_VOID   *pulRrcNasMsg)
{
    VOS_UINT8                           ucEmmMsgType = 0;
    VOS_UINT32                          ucRslt = 0;
    LRRC_LNAS_MSG_STRU                 *pstNasMsg = VOS_NULL_PTR;
    VOS_UINT8                          *pucRcvNasMsg = VOS_NULL_PTR;

    (VOS_VOID)ulSecuHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_CurExistActiveNewAnyMsgPlain enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CurExistActiveNewAnyMsgPlain_ENUM,LNAS_ENTRY);

    pstNasMsg = (LRRC_LNAS_MSG_STRU *)pulRrcNasMsg;
    pucRcvNasMsg = pstNasMsg->aucNasMsg;

    if(0 == g_ulNasPlainRejMsgFlag)
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_REJ_PLAIN_MSG,
                                       0);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_CurExistActiveNewAnyMsgPlain_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_UNPROT_FAIL;
    }

    /*如果不是EMM的消息，直接丢弃*/
    if(EMM_CN_MSG_PD_EMM != pucRcvNasMsg[NAS_EMM_SECU_CN_MSG_HEAD_POS])
    {
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_PD_EMM,
                                       pucRcvNasMsg[NAS_EMM_SECU_CN_MSG_HEAD_POS]);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_CurExistActiveNewAnyMsgPlain_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_UNPROT_FAIL;
    }

    /*获取空口消息类型*/
    ucEmmMsgType = pucRcvNasMsg[NAS_EMM_SECU_CN_MSG_TYPE_POS];

    switch(ucEmmMsgType)
    {
        /* ATTACH/TAU/SERVICE REJ 作为特权消息可以进状态机处理，其它消息丢弃 */
        case NAS_EMM_CN_MT_ATTACH_REJ:
        case NAS_EMM_CN_MT_TAU_REJ:
        case NAS_EMM_CN_MT_SER_REJ:

            ucRslt = NAS_EMM_SECU_UNPROT_SUCC;
            break;

       default:
            ucRslt = NAS_EMM_SECU_UNPROT_FAIL;
            break;
    }

    return ucRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_OnlyCurExistMsgSmc
 Description     : 只存在current安全上下文，new mapped和new native都不存在，
                   收到SMC消息，则SMC只能激活current安全上下文

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
     1.zhengjunyan 00148421      2011-4-26  Draft Enact

*****************************************************************************/
NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32    NAS_EMM_OnlyCurExistMsgSmc(
                                        VOS_UINT32  ulSecuHeadType,
                                        VOS_VOID   *pulRrcNasMsg)
{
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;
    LRRC_LNAS_MSG_STRU                   *pstSmcMsg = VOS_NULL_PTR;

    (VOS_VOID)ulSecuHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_OnlyCurExistMsgSmc enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_OnlyCurExistMsgSmc_ENUM,LNAS_ENTRY);

    pstSmcMsg = (LRRC_LNAS_MSG_STRU *)pulRrcNasMsg;

    ulRslt = NAS_EMM_SmcCommProcess(pstSmcMsg);
    if(NAS_EMM_SECU_SUCC == ulRslt)
    {
        /*安全上下文状态迁移*/
        NAS_EMM_SecuStateConvert(       EMM_CUR_SECU_EXIST_ACTIVE,
                                        EMM_NEW_SECU_NOT_EXIST);
        /*SMC消息验证成功的处理*/
        NAS_EMM_SmcSucc(pstSmcMsg);
    }

    return NAS_EMM_SECU_UNPROT_SMC;
}


NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32    NAS_EMM_CurAnyNewExistMsgSmc(
                                        VOS_UINT32  ulSecuHeadType,
                                        VOS_VOID   *pulRrcNasMsg)
{
    VOS_UINT32                          ulRslt = NAS_EMM_SECU_FAIL;
    LRRC_LNAS_MSG_STRU                   *pstSmcMsg = VOS_NULL_PTR;

    (VOS_VOID)ulSecuHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_CurAnyNewExistMsgSmc enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CurAnyNewExistMsgSmc_ENUM,LNAS_ENTRY);

    pstSmcMsg = (LRRC_LNAS_MSG_STRU *)pulRrcNasMsg;

    ulRslt = NAS_EMM_SmcCommProcess(pstSmcMsg);
    if(NAS_EMM_SECU_SUCC == ulRslt)
    {
        NAS_LMM_SetSecuCurFsmCS(EMM_CUR_SECU_EXIST_ACTIVE);
        if((NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNewMappedKSIsgsn())
         ||(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNewNativeKSIasme())
         ||(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE != NAS_EMM_GetSecuNonCurNativeKSIasme()))
        {
            NAS_LMM_SetSecuCurFsmNS(EMM_NEW_SECU_EXIST);
        }
        else
        {
            NAS_LMM_SetSecuCurFsmNS(EMM_NEW_SECU_NOT_EXIST);
        }

        /*SMC消息验证成功的处理*/
        NAS_EMM_SmcSucc(pstSmcMsg);
    }


    return NAS_EMM_SECU_UNPROT_SMC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_CurNotExistNewNotExistMsgSmc
 Description     : 当前安全上下文不存在，new mapped、new native和non-current
                   native都不存在，收到SMC消息，只能处理启动算法为EIA0

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
     1.zhengjunyan 00148421      2011-4-26  Draft Enact

*****************************************************************************/
NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32 NAS_EMM_CurNotExistNewNotExistMsgSmc
(
    VOS_UINT32                          ulSecuHeadType,
    VOS_VOID                           *pulRrcNasMsg
)
{
    VOS_UINT32                          ulRslt      = NAS_EMM_SECU_FAIL;
    VOS_UINT8                           ucSmcEia    = NAS_EMM_NULL;
    LRRC_LNAS_MSG_STRU                 *pstSmcMsg   = VOS_NULL_PTR;

    (VOS_VOID)ulSecuHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_CurNotExistNewNotExistMsgSmc enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CurNotExistNewNotExistMsgSmc_ENUM,LNAS_ENTRY);

    pstSmcMsg = (LRRC_LNAS_MSG_STRU *)pulRrcNasMsg;

    /* 如果不是启用EIA0，则直接回复smc rej原因值24 */
    /*lint -e416 -e415*/
    ucSmcEia =  pstSmcMsg->aucNasMsg[NAS_EMM_SECU_SMC_ALG_POSE] & NAS_EMM_LOW_3_BITS_F;
    /*lint +e416 +e415*/
    if (NAS_EMM_SECU_ALG_EIA0 != ucSmcEia)
    {
        NAS_EMM_SecuSendSmcRej(NAS_EMM_SMC_REJ_UNSPECIFIED);
        NAS_EMM_SndOmLogSecuVerifyFail(NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_EIA0,
                                       ucSmcEia);
        return NAS_EMM_SECU_UNPROT_FAIL;
    }

    ulRslt = NAS_EMM_SmcCommProcess(pstSmcMsg);
    if(NAS_EMM_SECU_SUCC == ulRslt)
    {
        /*安全上下文状态迁移*/
        NAS_EMM_SecuStateConvert(       EMM_CUR_SECU_EXIST_ACTIVE,
                                        EMM_NEW_SECU_NOT_EXIST);
        /*SMC消息验证成功的处理*/
        NAS_EMM_SmcSucc(pstSmcMsg);
    }

    return NAS_EMM_SECU_UNPROT_SMC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_VerifyDlMsgLen
 Description     : 检查下行空口消息的长度是否合法:
                   明文消息:   最短长度 2
                   保护的消息: 最短长度 8
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-4-12  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_VerifyDlMsgLen(      VOS_UINT32   ulSecuHeaderType,
                                        MsgBlock    *pMsg )
{
    LRRC_LMM_DATA_IND_STRU               *pstRrcNasMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulVerifyRslt = NAS_EMM_SECU_SUCC;

    pstRrcNasMsg = (LRRC_LMM_DATA_IND_STRU *)pMsg;

    switch(ulSecuHeaderType)
    {
        case NAS_EMM_SECU_HEAD_TYPE_PLAIN:
            if(pstRrcNasMsg->stNasMsg.ulNasMsgSize < NAS_EMM_MIN_PLAIN_MSG_LEN)
            {
                ulVerifyRslt = NAS_EMM_SECU_FAIL;
            }
            break;

        case NAS_EMM_SECU_HEAD_TYPE_INTEGRITY:
        case NAS_EMM_SECU_HEAD_TYPE_INTEGRITY_CIPHERED:
        case NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY:
            if(pstRrcNasMsg->stNasMsg.ulNasMsgSize < NAS_EMM_MIN_PROT_MSG_LEN)
            {
                ulVerifyRslt = NAS_EMM_SECU_FAIL;
            }
            break;

        default:
            ulVerifyRslt = NAS_EMM_SECU_FAIL;
             break;
    }

    return ulVerifyRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuUnProtect
 Description     : 根据安全上下文的状态将CN消息解保护，
                   若是SMC消息则在此函数中成处理，
                   其他CN消息解密后此函数生成明文，消息继续进入EMM状态机, 解码
                   并根据状态处理。
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-11  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuUnProtect( MsgBlock  *pMsg )
{
    NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32    enRslt = NAS_EMM_SECU_UNPROT_FAIL;
    NAS_LMM_PID_MSG_STRU                    *pMmPidMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_IND_STRU                   *pRrcMmDataIndMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulSecuHeaderType = 0;
    VOS_UINT8                              *pucNasCnMsg = VOS_NULL_PTR;
    VOS_UINT8                               ucPd = 0;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuUnProtect enterd.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_ENTRY);

    pMmPidMsg                           = (NAS_LMM_PID_MSG_STRU *)pMsg;
    pRrcMmDataIndMsg                    = (LRRC_LMM_DATA_IND_STRU *)pMsg;
    pucNasCnMsg                         = pRrcMmDataIndMsg->stNasMsg.aucNasMsg;

    NAS_LMM_SetMsgIsIntegrityFlag(VOS_FALSE);

    /*安全开关没打开或者不是空口消息，则不解保护，直接进状态机*/
    if( (NAS_EMM_SMC_OPEN != g_ulSmcControl) ||
        (ID_LRRC_LMM_DATA_IND != pMmPidMsg->ulMsgId))
    {
        NAS_EMM_SECU_LOG1_INFO("NAS_EMM_SecuUnProtect: SMC NOT OPEN or NOT AIR MSG.g_ulSmcControl = ",
                                g_ulSmcControl);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL1,
                                g_ulSmcControl);
        return NAS_EMM_GO_INTO_EMM_FSM;
    }

    /*打印当前安全上下文状态和空口消息原始码流*/
    NAS_LMM_PUBM_LOG_NORM("\n");
    NAS_LMM_PUBM_LOG_NORM("======NAS_CUR_SECU_CONTEXT_STATE:======");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL2);
    NAS_LMM_PrintFsmState(NAS_LMM_PARALLEL_FSM_SECU);
    NAS_LMM_PUBM_LOG_NORM("~~~~~~NAS Receive Message:~~~~~~");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_RCV_MSG);
    NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                     pRrcMmDataIndMsg->stNasMsg.aucNasMsg,
                                     pRrcMmDataIndMsg->stNasMsg.ulNasMsgSize);
    /*判断ID_RRC_MM_DATA_IND中的CN消息的安全头的Protocol discriminator，若不是
    EMM的消息，退出*/
    ucPd = pucNasCnMsg[NAS_EMM_SECU_CN_MSG_HEAD_POS]& NAS_EMM_LOW_HALF_BYTE_F;
    if(EMM_CN_MSG_PD_EMM != ucPd)
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuUnProtect: NOT EMM MSG.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_NOT_GO_INTO_EMM_FSM;
    }

    /*获取安全头类型*/
    ulSecuHeaderType =  (VOS_UINT32)pucNasCnMsg[NAS_EMM_SECU_CN_MSG_HEAD_POS]
                        & NAS_EMM_HIGH_HALF_BYTE_F;
    NAS_EMM_SECU_LOG1_INFO("NAS_EMM_SecuUnProtect: ulSecuHeaderType = ",
                        ulSecuHeaderType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL4,
                        ulSecuHeaderType);

    /* 记录消息是否是完整性保护的标识 */
    if (NAS_EMM_SECU_HEAD_TYPE_PLAIN != ulSecuHeaderType)
    {
        NAS_LMM_SetMsgIsIntegrityFlag(VOS_TRUE);
    }

    /*检查下行空口消息码流的长度*/
    if( NAS_EMM_SECU_FAIL == NAS_EMM_VerifyDlMsgLen(ulSecuHeaderType, pMsg))
    {
        NAS_EMM_SECU_LOG_WARN("NAS_EMM_SecuUnProtect: MsgLen Err or SecuHeadType Err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL5);
        return NAS_EMM_NOT_GO_INTO_EMM_FSM;
    }

    /*查找动作函数并执行:输入消息为NAS消息内容，不包含DOPRA消息头*/
    enRslt = NAS_LMM_MsgProcessInFsm(    NAS_LMM_PARALLEL_FSM_SECU,
                                        (MsgBlock  *)&(pRrcMmDataIndMsg->stNasMsg),
                                        ulSecuHeaderType,
                                        ulSecuHeaderType);

    /*动作函数处理中的加、解保护可能会修改NAS消息的长度，重新计算DOPRA消息的长度*/
    pRrcMmDataIndMsg->ulLength = pRrcMmDataIndMsg->stNasMsg.ulNasMsgSize
                               + sizeof(pRrcMmDataIndMsg->enMsgId)
                               + sizeof(pRrcMmDataIndMsg->stNasMsg.ulNasMsgSize);

    /*经过解保护之后的消息码流*/
    NAS_LMM_PUBM_LOG_NORM("\n");
    NAS_LMM_PUBM_LOG_NORM("~~~~~~Message After UnProt~~~~~~");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL6);
    NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                     pRrcMmDataIndMsg->stNasMsg.aucNasMsg,
                                     pRrcMmDataIndMsg->stNasMsg.ulNasMsgSize);
    /*处理消息解保护结果*/
    switch(enRslt)
    {
        case    NAS_EMM_SECU_UNPROT_SUCC:
                NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuUnProtect: NAS_EMM_SECU_UNPROT_SUCC");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL7);
                return NAS_EMM_GO_INTO_EMM_FSM;

        case    NAS_EMM_SECU_UNPROT_FAIL:
                NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuUnProtect: NAS_EMM_SECU_UNPROT_FAIL");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL8);
                return NAS_EMM_NOT_GO_INTO_EMM_FSM;

        case    NAS_EMM_SECU_UNPROT_SMC:

                /* 然后MM内部消息处理 */
                (VOS_VOID)NAS_LMM_IntraMsgProcess();

                /*开始buff的处理*/
                (VOS_VOID)NAS_LMM_BufMsgProcess();


                /*如果是SMC消息,不进入状态机处理*/
                NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuUnProtect: NAS_EMM_SECU_UNPROT_SMC");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL9);
                return NAS_EMM_NOT_GO_INTO_EMM_FSM;
        default:
                NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuUnProtect: default");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUnProtect_ENUM,LNAS_FUNCTION_LABEL10);
                return NAS_EMM_NOT_GO_INTO_EMM_FSM;
    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuSerIntProt
 Description     : SER REQ消息的格式与其他CN消息不同，需单独处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-16  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_SecuSerIntProt( LRRC_LNAS_MSG_STRU *pstSerReqMsg )
{
/* PC环境:短MAC在SERVICE REQ消息组装时已经被赋值为0，不再需要处理 */
#if(VOS_WIN32 == VOS_OS_VER)
    VOS_UINT8                           aucPcShortMac[] = {0x11, 0x02};

    NAS_LMM_MEM_CPY_S(                  &(pstSerReqMsg->aucNasMsg[NAS_EMM_SECU_SHORT_MAC_POS]),
                                        NAS_EMM_SECU_SHORT_MAC_LEN,
                                        aucPcShortMac,
                                        NAS_EMM_SECU_SHORT_MAC_LEN);

    return NAS_EMM_SUCC;

/* 单板环境 */
#else
     CIPHER_SINGLE_CFG_S                 stSingleSecuPara;
     VOS_INT32                           lRslt;
     VOS_UINT8                          *pucSrcAddr = VOS_NULL_PTR;
     VOS_UINT8                          *pucDstAddr = VOS_NULL_PTR;


     /* 若是完整性空算法，则在设置短MAC为0，然后返回 */
     if(PS_SECU_ALG_NULL == NAS_EMM_GetSecuEia())
     {
         NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuSerIntProt: ALG is NULL_ALG.");
         TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuSerIntProt_ENUM,LNAS_FUNCTION_LABEL1);
         NAS_LMM_MEM_SET_S( &(pstSerReqMsg->aucNasMsg[NAS_EMM_SECU_SHORT_MAC_POS]),
                            NAS_EMM_SECU_SHORT_MAC_LEN,
                            0,
                            NAS_EMM_SECU_SHORT_MAC_LEN);
         return  NAS_EMM_SECU_SUCC;
     }

     /*清空MEM,完整性保护，参数赋值*/
     NAS_LMM_MEM_SET_S( &stSingleSecuPara,
                        sizeof(CIPHER_SINGLE_CFG_S),
                        0,
                        sizeof(CIPHER_SINGLE_CFG_S));

     stSingleSecuPara.enOpt = CIPHER_OPT_PROTECT_LMAC;
     stSingleSecuPara.u8Direction = NAS_EMM_SECU_UPLINK;
     stSingleSecuPara.u32Count = NAS_EMM_GetSecuUlNasCount();
     stSingleSecuPara.u32BlockLen = pstSerReqMsg->ulNasMsgSize - NAS_EMM_SECU_SHORT_MAC_LEN;;
     stSingleSecuPara.stAlgKeyInfo.u32KeyIndexInt = LTE_SECU_NAS_INTEGRITY_KEY_INDEX;
     stSingleSecuPara.stAlgKeyInfo.enAlgIntegrity
                                     = NAS_EMM_GetIntegrityAlg(NAS_EMM_GetSecuEia());

     stSingleSecuPara.u8BearId = NAS_EMM_SECU_SECURITY_BEARERID;
     stSingleSecuPara.bMemBlock = PS_TRUE;
     stSingleSecuPara.enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
     stSingleSecuPara.enHeaderLen = CIPHER_HDR_BIT_TYPE_0;

     pucSrcAddr = NAS_EMM_GetSecuSrcSpace();
     NAS_LMM_MEM_CPY_S( pucSrcAddr,
                        LRRC_LNAS_MAX_DATA_LENGTH,
                        pstSerReqMsg->aucNasMsg,
                        stSingleSecuPara.u32BlockLen);

     pucDstAddr = NAS_EMM_GetSecuDstSpace();

     /*打印Cipher参数*/
     NAS_EMM_SecuPrintCipherPara(&stSingleSecuPara, pucSrcAddr);

    stSingleSecuPara.pInMemMgr = (VOS_VOID *)pucSrcAddr;
    stSingleSecuPara.pOutMemMgr = (VOS_VOID *)pucDstAddr;

     /* 调用BSP接口解保护*/
     lRslt = NAS_CIPHER_SingleSubmitTask(&stSingleSecuPara);
     if (CIPHER_SUCCESS != lRslt)
     {
         NAS_EMM_SECU_LOG1_ERR("NAS_EMM_SecuSerIntProt:mdrv_cipher_single_submit_task fail.lRslt = ",
                                  lRslt);
         TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuSerIntProt_ENUM,LNAS_FUNCTION_LABEL2);
         return NAS_EMM_SECU_FAIL;
     }

     /*完整性保护成功完成，组装SER REQ消息*/
     NAS_LMM_MEM_CPY_S(   &(pstSerReqMsg->aucNasMsg[NAS_EMM_SECU_SHORT_MAC_POS]),
                           NAS_EMM_SECU_SHORT_MAC_LEN,
                           pucDstAddr + NAS_EMM_SECU_SHORT_MAC_POS,
                           NAS_EMM_SECU_SHORT_MAC_LEN);
     return NAS_EMM_SUCC;

#endif
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuNotSerIntProt
 Description     : 非SER REQ消息完整性保护
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-17  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuNotSerIntProt( const LRRC_LNAS_MSG_STRU *pstRrcNasMsg )
{
/* PC环境: MAC赋值 */
#if(VOS_WIN32 == VOS_OS_VER)
    #ifdef PS_ITT_PC_TEST_NAS_ST
    VOS_UINT8                           aucPcMac[] = {0x5D, 0x22, 0x11, 0x02};
    #else
    VOS_UINT8                           aucPcMac[] = {0x02, 0x11, 0x22, 0x5D};
    #endif

    NAS_LMM_MEM_CPY_S(  NAS_EMM_GetSecuDstSpace(),
                        NAS_EMM_SECU_MAC_LEN,
                        aucPcMac,
                        NAS_EMM_SECU_MAC_LEN);
    return NAS_EMM_SUCC;
#else
/* 单板环境 */
    CIPHER_SINGLE_CFG_S                 stSingleSecuPara;
    VOS_INT32                           lRslt;
    VOS_UINT8                          *pucSrcAddr = VOS_NULL_PTR;
    VOS_UINT8                          *pucDstAddr = VOS_NULL_PTR;

    /* 若是完整性空算法，则在目的区域设置MAC为0，然后返回 */
    if(PS_SECU_ALG_NULL == NAS_EMM_GetSecuEia())
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuNotSerIntProt: ALG is NULL_ALG.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuNotSerIntProt_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_MEM_SET_S(  NAS_EMM_GetSecuDstSpace(),
                            NAS_EMM_SECU_MAC_LEN,
                            0,
                            NAS_EMM_SECU_MAC_LEN);
        return  NAS_EMM_SECU_SUCC;
    }

    /*清空MEM,完整性保护，参数赋值*/
    NAS_LMM_MEM_SET_S(  &stSingleSecuPara,
                        sizeof(CIPHER_SINGLE_CFG_S),
                        0,
                        sizeof(CIPHER_SINGLE_CFG_S));

    stSingleSecuPara.enOpt = CIPHER_OPT_PROTECT_LMAC;
    stSingleSecuPara.u8Direction = NAS_EMM_SECU_UPLINK;
    stSingleSecuPara.u32Count = NAS_EMM_GetSecuUlNasCount();
    stSingleSecuPara.u32BlockLen = pstRrcNasMsg->ulNasMsgSize + NAS_EMM_SECU_SN_LEN;
    stSingleSecuPara.stAlgKeyInfo.u32KeyIndexInt = LTE_SECU_NAS_INTEGRITY_KEY_INDEX;
    stSingleSecuPara.stAlgKeyInfo.enAlgIntegrity
                                = NAS_EMM_GetIntegrityAlg(NAS_EMM_GetSecuEia());

    stSingleSecuPara.u8BearId = NAS_EMM_SECU_SECURITY_BEARERID;
    stSingleSecuPara.bMemBlock = PS_TRUE;
    stSingleSecuPara.enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    stSingleSecuPara.enHeaderLen = CIPHER_HDR_BIT_TYPE_0;

    pucSrcAddr = NAS_EMM_GetSecuSrcSpace();
    pucSrcAddr[0] = NAS_EMM_GetSecuUlSn();
    NAS_LMM_MEM_CPY_S(                  pucSrcAddr + NAS_EMM_SECU_SN_LEN,
                                        LRRC_LNAS_MAX_DATA_LENGTH - NAS_EMM_SECU_SN_LEN,
                                        pstRrcNasMsg->aucNasMsg,
                                        pstRrcNasMsg->ulNasMsgSize);
    pucDstAddr = NAS_EMM_GetSecuDstSpace();

    /*打印Cipher参数*/
    NAS_EMM_SecuPrintCipherPara(&stSingleSecuPara, pucSrcAddr);

    stSingleSecuPara.pInMemMgr = (VOS_VOID *)pucSrcAddr;
    stSingleSecuPara.pOutMemMgr = (VOS_VOID *)pucDstAddr;

    /* 调用BSP接口解保护*/
    lRslt = NAS_CIPHER_SingleSubmitTask(&stSingleSecuPara);
    if (CIPHER_SUCCESS != lRslt)
    {
        NAS_EMM_SECU_LOG1_ERR("NAS_EMM_SecuNotSerIntProt:mdrv_cipher_single_submit_task fail.lRslt = ",
                                 lRslt);
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_SecuNotSerIntProt_ENUM,LNAS_FUNCTION_LABEL2,
                                lRslt);
        return NAS_EMM_SECU_FAIL;
    }
    return NAS_EMM_SUCC;

#endif
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuAddSecuHeader
 Description     : 完整性保护计算MAC完成后，将 SecuHeadType,MAC,SN,PlainMsg
                   组装起来,其中MAC存储在全局变量NAS_EMM_GetSecuDstSpace()中
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-17  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SecuAddSecuHeader(NAS_EMM_SECU_HEAD_TYPE_ENUM_UINT8 enSecurHeadType,
                                  LRRC_LNAS_MSG_STRU                 *pstRrcNasMsg)
{
    VOS_UINT8                          *pucSecuBuf = VOS_NULL_PTR;


    /* pstRrcNasMsg 中的CN消息后移6个字节，即安全头的长度*/
    pucSecuBuf = NAS_EMM_GetSecuBufSpace();

    NAS_LMM_MEM_SET_S(pucSecuBuf, LRRC_LNAS_MAX_DATA_LENGTH, 0, LRRC_LNAS_MAX_DATA_LENGTH);
    NAS_LMM_MEM_CPY_S(  pucSecuBuf,
                        LRRC_LNAS_MAX_DATA_LENGTH,
                        pstRrcNasMsg->aucNasMsg,
                        pstRrcNasMsg->ulNasMsgSize);

    /*lint -e416 -e415*/
    NAS_LMM_MEM_CPY_S(  &(pstRrcNasMsg->aucNasMsg[NAS_EMM_SECU_MSG_HEAD_LEN]),
                        pstRrcNasMsg->ulNasMsgSize,
                        pucSecuBuf,
                        pstRrcNasMsg->ulNasMsgSize);
    /*lint +e416 +e415*/

    /* 修改 pstNasMsg 中的CN长度 */
    pstRrcNasMsg->ulNasMsgSize += NAS_EMM_SECU_MSG_HEAD_LEN;

    /* 0字节填安全头类型 */
    pstRrcNasMsg->aucNasMsg[0] = EMM_CN_MSG_PD_EMM | enSecurHeadType ;

    /* 1~4字节: MAC*/
    /*lint -e419*/
    NAS_LMM_MEM_CPY_S(  &(pstRrcNasMsg->aucNasMsg[NAS_EMM_SECU_MAC_POS]),
                        NAS_EMM_SECU_MAC_LEN,
                        NAS_EMM_GetSecuDstSpace(),
                        NAS_EMM_SECU_MAC_LEN);
    /*lint +e419*/

    /*5字节:SN */
    /*lint -e416 -e415*/
    pstRrcNasMsg->aucNasMsg[NAS_EMM_SECU_MSG_SN_POS] = NAS_EMM_GetSecuUlSn();/* [false alarm]:代码保证了不会越界 */
    /*lint +e416 +e415*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuEncrypt
 Description     : 非SER REQ消息进行加密处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-17  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuEncrypt( LRRC_LNAS_MSG_STRU *pstRrcNasMsg )
{
/*PC环境下明文不变，直接返回*/
#if(VOS_WIN32 == VOS_OS_VER)
    return NAS_EMM_SUCC;

/*单板环境下*/
#else
    CIPHER_SINGLE_CFG_S                 stSingleSecuPara;
    VOS_INT32                           lRslt;
    VOS_UINT8                          *pucSrcAddr = VOS_NULL_PTR;
    VOS_UINT8                          *pucDstAddr = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuEncrypt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuEncrypt_ENUM,LNAS_ENTRY);
    /*若是空算法，则直接返回 */
    if(PS_SECU_ALG_NULL == NAS_EMM_GetSecuEca())
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuEncrypt: Eca IS NULL.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuEncrypt_ENUM,LNAS_FUNCTION_LABEL1);
        return  NAS_EMM_SUCC;
    }

    /* 消息加密，参数赋值*/
    NAS_LMM_MEM_SET_S(  &stSingleSecuPara,
                        sizeof(CIPHER_SINGLE_CFG_S),
                        0,
                        sizeof(CIPHER_SINGLE_CFG_S));

    stSingleSecuPara.enOpt = CIPHER_OPT_ENCRYPT;
    stSingleSecuPara.u8Direction = NAS_EMM_SECU_UPLINK;
    stSingleSecuPara.u32Count = NAS_EMM_GetSecuUlNasCount();
    stSingleSecuPara.u32BlockLen = pstRrcNasMsg->ulNasMsgSize;
    stSingleSecuPara.stAlgKeyInfo.u32KeyIndexSec = LTE_SECU_NAS_CIPHER_KEY_INDEX;
    stSingleSecuPara.stAlgKeyInfo.enAlgSecurity
                                = NAS_EMM_GetSecurityAlg(NAS_EMM_GetSecuEca());


    stSingleSecuPara.u8BearId = NAS_EMM_SECU_SECURITY_BEARERID;
    stSingleSecuPara.bMemBlock = PS_TRUE;
    stSingleSecuPara.enAppdHeaderLen = CIPHER_HDR_BIT_TYPE_0;
    stSingleSecuPara.enHeaderLen = CIPHER_HDR_BIT_TYPE_0;

    pucSrcAddr = NAS_EMM_GetSecuSrcSpace();
    NAS_LMM_MEM_CPY_S(                  pucSrcAddr,
                                        LRRC_LNAS_MAX_DATA_LENGTH,
                                        pstRrcNasMsg->aucNasMsg,
                                        pstRrcNasMsg->ulNasMsgSize);
    pucDstAddr = NAS_EMM_GetSecuDstSpace();

    /*打印Cipher参数*/
    NAS_EMM_SecuPrintCipherPara(&stSingleSecuPara, pucSrcAddr);

    stSingleSecuPara.pInMemMgr = (VOS_VOID *)pucSrcAddr;
    stSingleSecuPara.pOutMemMgr = (VOS_VOID *)pucDstAddr;

    /* 调用BSP接口解保护*/
    lRslt = NAS_CIPHER_SingleSubmitTask(&stSingleSecuPara);
    if (CIPHER_SUCCESS != lRslt)
    {
        NAS_EMM_SECU_LOG1_ERR("NAS_EMM_SecuEncrypt:mdrv_cipher_single_submit_task fail.lRslt = ",
                                 lRslt);
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuEncrypt_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SECU_FAIL;
    }

    /*将空口消息替换为密文*/
    NAS_LMM_MEM_CPY_S(                  pstRrcNasMsg->aucNasMsg,
                                        pstRrcNasMsg->ulNasMsgSize,
                                        NAS_EMM_GetSecuDstSpace(),
                                        pstRrcNasMsg->ulNasMsgSize);

    return NAS_EMM_SUCC;

#endif

}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuMsgNeedNotEncrypt
 Description     : 判断消息是否可以加密
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-9-20  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuMsgNeedNotEncrypt( NAS_EMM_CN_MSG_TYPE_ENUM_UINT8 enMsgType)
{
    /* 删除TAU消息加密的相关无效配置代码 y00307272 20151017 DTS2015101700432 */
    /* TAU和attach req消息永远不能加密*/
    if(( NAS_EMM_CN_MT_TAU_REQ == enMsgType)||( NAS_EMM_CN_MT_ATTACH_REQ == enMsgType))
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuMsgNeedNotEncrypt: attach req or tau req cannot encrypt.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuMsgNeedNotEncrypt_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_NotSerReqMsgProt
 Description     : 不是SER REQ消息加保护处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-16  Draft Enact
    2.sunbing 49683             2010-9-20  TAU和attach req消息永远不加密
*****************************************************************************/
VOS_UINT32  NAS_EMM_NotSerReqMsgProt( LRRC_LNAS_MSG_STRU *pstRrcNasMsg )
{
    VOS_UINT32                          ulRslt    = NAS_EMM_FAIL;
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enMsgType = NAS_EMM_CN_MT_BUTT;
    NAS_EMM_SECU_HEAD_TYPE_ENUM_UINT8   enSecurHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_NotSerReqMsgProt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_NotSerReqMsgProt_ENUM,LNAS_ENTRY);

    /* 获取消息类别 */
    enMsgType = pstRrcNasMsg->aucNasMsg[NAS_EMM_SECU_CN_MSG_TYPE_POS];

    /*初始化安全头0x10*/
    enSecurHeadType = NAS_EMM_SECU_HEAD_TYPE_INTEGRITY;

    /*如果当前状态为CurExistActive,并且消息需要加密，则对消息先加密，安全头修改为 0x20*/
    if((EMM_CUR_SECU_EXIST_ACTIVE == NAS_LMM_GetSecuCurFsmCS())
     &&(NAS_EMM_FAIL == NAS_EMM_SecuMsgNeedNotEncrypt(enMsgType)))
    {
        enSecurHeadType = NAS_EMM_SECU_HEAD_TYPE_INTEGRITY_CIPHERED;

        /*EMM消息，并且是 SMC COMPLETE消息，则安全头为 4*/
        if( NAS_EMM_CN_MT_SMC_CMP == enMsgType)
        {
            enSecurHeadType = NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY_CIPHERED;
        }

        ulRslt = NAS_EMM_SecuEncrypt(pstRrcNasMsg);
        if(NAS_EMM_FAIL == ulRslt)
        {
            return NAS_EMM_FAIL;
        }
    }

    /*非SER REQ消息完整性保护:计算MAC*/
    ulRslt = NAS_EMM_SecuNotSerIntProt(pstRrcNasMsg);
    if(NAS_EMM_FAIL == ulRslt)
    {
        return NAS_EMM_FAIL;
    }

    /*组装消息*/
    NAS_EMM_SecuAddSecuHeader(enSecurHeadType,pstRrcNasMsg);

    return NAS_EMM_SUCC;
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_EMM_SecuWhetherNeedProt
 Description     : 判断是否需要做保护
 Input           : pstNasMsg:  指向 RRC_NAS_MSG_STRU结构
 Output          : None
 Return          :

 History         :
    1.zhengjunyan 00148421      2010-3-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SecuWhetherNeedProt(const LRRC_LNAS_MSG_STRU *pstNasMsg)

{
    (VOS_VOID)pstNasMsg;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuWhetherNeedProt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuWhetherNeedProt_ENUM,LNAS_ENTRY);

    /*1.如果安全开关打开，当前安全上下文状态为:CurNotExit，则直接返回*/
    if(EMM_CUR_SECU_NOT_EXIST == NAS_LMM_GetSecuCurFsmCS())
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuWhetherNeedProt: Cur Secu Context Not Exit.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuWhetherNeedProt_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SECU_NOT_NEED_PROT;
    }

    /*zhengjunyan mod 2010-4-21:SMC REJ加保护*/

    return NAS_EMM_SECU_NEED_PROT;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuUpLayerMsgProt
 Description     : EMM上层透传消息加密，加完整性保护:包括ESM上行透传消息，环回消息等
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuUpLayerMsgProt( LRRC_LNAS_MSG_STRU *pstNasMsg )
{
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;
    NAS_EMM_SECU_HEAD_TYPE_ENUM_UINT8   enSecurHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuUpLayerMsgProt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuUpLayerMsgProt_ENUM,LNAS_ENTRY);

    /*ESM上行透传消息一定是在安全连接存在情况下,否则流程处理有错误*/
    if(EMM_CUR_SECU_EXIST_ACTIVE != NAS_LMM_GetSecuCurFsmCS())
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuUpLayerMsgProt: ESM MSG PROT ERR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuUpLayerMsgProt_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*安全头赋值*/
    enSecurHeadType = NAS_EMM_SECU_HEAD_TYPE_INTEGRITY_CIPHERED;

    /*加密*/
    ulRslt = NAS_EMM_SecuEncrypt(pstNasMsg);
    if(NAS_EMM_FAIL == ulRslt)
    {
        return NAS_EMM_FAIL;
    }

    /*加完整性保护:计算MAC*/
    ulRslt = NAS_EMM_SecuNotSerIntProt(pstNasMsg);
    if(NAS_EMM_FAIL == ulRslt)
    {
        return NAS_EMM_FAIL;
    }

    /*组装消息*/
    NAS_EMM_SecuAddSecuHeader(enSecurHeadType,pstNasMsg);

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuEmmMsgProt
 Description     : EMM上行消息加保护处理:需要区分是否是SER REQ消息进行不同处理
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-3-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_SecuEmmMsgProt( LRRC_LNAS_MSG_STRU *pstNasMsg )
{
    NAS_EMM_SECU_HEAD_TYPE_ENUM_UINT8   enSecurHeadType;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuEmmMsgProt entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuEmmMsgProt_ENUM,LNAS_ENTRY);

    /* 获取安全头*/
    enSecurHeadType = pstNasMsg->aucNasMsg[NAS_EMM_SECU_CN_MSG_HEAD_POS]
                    & NAS_EMM_SECU_MSG_HIGH_BIT;
    /*是SER REQ消息*/
    if( NAS_EMM_SECU_HEAD_TYPE_SERVICE_REQUEST == enSecurHeadType)
    {
        if(NAS_EMM_FAIL == NAS_EMM_SecuSerIntProt(pstNasMsg))
        {
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuEmmMsgProt:SER REQ PROT ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuEmmMsgProt_ENUM,LNAS_FUNCTION_LABEL1);
            return NAS_EMM_FAIL;
        }
    }
    /*不是SER REQ消息*/
    else
    {
        if(NAS_EMM_FAIL == NAS_EMM_NotSerReqMsgProt(pstNasMsg))
        {
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuEmmMsgProt:NOT SER REQ PROT ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuEmmMsgProt_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_FAIL;
        }
    }

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SecuProtect
 Description     : 对上行空口消息加保护处理
 Input           : pstMrrcDataReq:  指向 NAS_EMM_MRRC_DATA_REQ_STRU结构
 Output          : None
 Return          :

 History         :
    1.zhengjunyan 00148421      2010-3-15  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_EMM_SecuProtect(VOS_VOID  * pstMrrcDataReq)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pstIntraDataReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPd;


    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuProtect entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuProtect_ENUM,LNAS_ENTRY);

    /*安全上下文当前状态*/
    NAS_LMM_PUBM_LOG_NORM("\n");
    NAS_LMM_PUBM_LOG_NORM("======NAS_CUR_SECU_CONTEXT_STATE:======");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuProtect_ENUM,LNAS_FUNCTION_LABEL1);
    NAS_LMM_PrintFsmState(NAS_LMM_PARALLEL_FSM_SECU);

    pstIntraDataReq = (NAS_EMM_MRRC_DATA_REQ_STRU *)pstMrrcDataReq;

    /*如果连接不存在，需要给RRC下发RRC_MM_INFO_CHANGE_REQ消息*/
    if(NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState() )
    {
        NAS_EMM_SendSecuParamToRrc();
    }

    /*获取消息协议头*/
    ucPd = pstIntraDataReq->stNasMsg.aucNasMsg[NAS_EMM_SECU_CN_MSG_HEAD_POS]
         & NAS_EMM_LOW_HALF_BYTE_F;

    /*如果是EMM消息*/
    if(EMM_CN_MSG_PD_EMM == ucPd)
    {
        /*判断是否需要做保护*/
        if( NAS_EMM_SECU_NOT_NEED_PROT == NAS_EMM_SecuWhetherNeedProt(&(pstIntraDataReq->stNasMsg)))
        {
            NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuProtect: No need to protect.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuProtect_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_SUCC;
        }

        /*EMM消息上行加保护*/
        if(NAS_EMM_FAIL == NAS_EMM_SecuEmmMsgProt(&(pstIntraDataReq->stNasMsg)))
        {
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuProtect: EMM MSG PROT ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuProtect_ENUM,LNAS_FUNCTION_LABEL3);
            return NAS_EMM_FAIL;
        }
    }
    /*上层透传消息*/
    else
    {
        if(NAS_EMM_FAIL == NAS_EMM_SecuUpLayerMsgProt(&(pstIntraDataReq->stNasMsg)))
        {
            NAS_EMM_SECU_LOG_ERR("NAS_EMM_SecuProtect: ESM MSG PROT ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SecuProtect_ENUM,LNAS_FUNCTION_LABEL4);
            return NAS_EMM_FAIL;
        }

    }

    /*消息加保护完成后，NAS消息的长度可能会发生变化，需要更新DOPRA消息的长度*/
    pstIntraDataReq->ulLength = NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(
                                    pstIntraDataReq->stNasMsg.ulNasMsgSize);

    /*经过加保护之后的消息码流*/
    NAS_LMM_PUBM_LOG_NORM("\n");
    NAS_LMM_PUBM_LOG_NORM("~~~~~~Message After Prot~~~~~~");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuProtect_ENUM,LNAS_FUNCTION_LABEL5);

    NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                     pstIntraDataReq->stNasMsg.aucNasMsg,
                                     pstIntraDataReq->stNasMsg.ulNasMsgSize);

    /*上行NASCOUNT增 1*/
    NAS_EMM_GetSecuUlNasCount()++;

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SndOmLogSecuVerifyFail
 Description     : 安全检查失败，可维可测上报
 Input           : enIeType 信元类型
                   enCause  失败原因
                   ulValue  失败值
 Output          : None
 Return          : None

 History         :
    1.chengmin 00285307      2015-6-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SndOmLogSecuVerifyFail
(
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ENUM_UINT32           enSecuFailType,
    VOS_UINT32                                          ulValue
)
{
    NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_STRU      *pstMsg = VOS_NULL_PTR;
    NAS_LMM_FSM_STATE_STRU                    *pstEmmCurState;
    NAS_LMM_FSM_STATE_STRU                    *pstSecuCurState;
#if (VOS_OS_VER == VOS_WIN32)
    VOS_CHAR                                   acPrintStr[MAX_PRINT_CHAR_NUM] = {0};
    VOS_CHAR                                   acValue[MAX_PRINT_CHAR_NUM]    = {0};
#endif

    pstMsg = (NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SndOmLogSecuVerifyFail: mem alloc fail!.");
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_LMM_OM_LOG_SECU_VERIFY_FAIL;
    pstMsg->enSecuFailType              = enSecuFailType;
    pstMsg->ulValue                     = ulValue;

    pstEmmCurState      = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pstSecuCurState     = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_SECU);

    NAS_LMM_MEM_CPY_S(  &(pstMsg->stEmmCurState),
                        sizeof(NAS_LMM_FSM_STATE_STRU),
                        pstEmmCurState,
                        sizeof(NAS_LMM_FSM_STATE_STRU));
    NAS_LMM_MEM_CPY_S(  &(pstMsg->stSecuCurState),
                        sizeof(NAS_LMM_FSM_STATE_STRU),
                        pstSecuCurState,
                        sizeof(NAS_LMM_FSM_STATE_STRU));

#if (VOS_OS_VER == VOS_WIN32)
    VOS_StrCpy(acPrintStr, "SECU Verify Fail, Fail Cause:");
    VOS_StrCat(acPrintStr, g_LmmSecuFailTypePrintTable[enSecuFailType-1].aucPrintStr);
    VOS_sprintf(acValue, ", Value:%d", ulValue);
    VOS_StrCat(acPrintStr, acValue);
    NAS_EMM_SECU_LOG_ERR(acPrintStr);
#endif

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

