

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafXsmsCtx.h"
#include "TafFsm.h"
#include "TafXsmsTimer.h"
#include "NVIM_Interface.h"
#include "TafXsmsMsgProc.h"
#include "TafCdmaPlusTranslate.h"
#include "UsimPsInterface.h"
#include "TafStdlib.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* MT 的全局变量定义 */
TAF_XSMS_MSG_MT_REC_STRU                g_stTafXsmsMtRec;
TAF_XSMS_MT_CTX_STRU                    g_stTafXsmsMtCtx;

/* MO 的全局变量定义 */
TAF_XSMS_MSG_MO_REC_STRU                g_stTafXsmsMoRec;
TAF_XSMS_MO_CTX_STRU                    g_stTafXsmsMoCtx;

/* AP 侧短信存储满的FLAG */
TAF_XSMS_CCF_AP_MEM_FULL_ENUM8          g_enCcfMemFullFlag = TAF_XSMS_CCF_AP_MEM_NOT_FULL;

TAF_XSMS_MO_SEND_MSG_POOL_STRU          g_stXsmsMoSendPool;


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

TAF_XSMS_MSG_MO_REC_STRU* TAF_XSMS_MoGetRecAddr(VOS_VOID)
{
    return &g_stTafXsmsMoRec;
}


TAF_XSMS_MSG_MT_REC_STRU* TAF_XSMS_MtGetRecAddr(VOS_VOID)
{
    return &g_stTafXsmsMtRec;
}




TAF_XSMS_MO_CTX_STRU* TAF_XSMS_MoGetCtxAddr(VOS_VOID)
{
    return &(g_stTafXsmsMoCtx);
}



TAF_XSMS_MT_CTX_STRU* TAF_XSMS_MtGetCtxAddr(VOS_VOID)
{
    return &(g_stTafXsmsMtCtx);
}


TAF_XSMS_MT_FSM_CTX_STRU* TAF_XSMS_MtGetCurFsmAddr(VOS_VOID)
{
    return &(TAF_XSMS_MtGetCtxAddr()->stCurFsm);
}


TAF_XSMS_MO_FSM_CTX_STRU* TAF_XSMS_MoGetCurFsmAddr(VOS_VOID)
{
    return &(TAF_XSMS_MoGetCtxAddr()->stCurFsm);
}


VOS_VOID TAF_XSMS_MtSetCurrFsmState(VOS_UINT32 ulCurrState)
{
    TAF_XSMS_MT_FSM_CTX_STRU           *pstCurFsm;

    /* 获取当前的状态信息 */
    pstCurFsm               = TAF_XSMS_MtGetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->enFsmId      = ulCurrState;

    TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_MT_FSM, (VOS_UINT8*)&ulCurrState, sizeof(TAF_XSMS_MT_FSM_ID_ENUM_UINT32));

    return;
}


VOS_VOID TAF_XSMS_MoSetCurrFsmState(VOS_UINT32 ulCurrState)
{
    TAF_XSMS_MO_FSM_CTX_STRU                *pstCurFsm;

    /* 获取当前的状态信息 */
    pstCurFsm           = TAF_XSMS_MoGetCurFsmAddr();

    /* 设置当前状态 */
    pstCurFsm->enFsmId  = ulCurrState;

    TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_MO_FSM, (VOS_UINT8*)&ulCurrState, sizeof(TAF_XSMS_MO_FSM_ID_ENUM_UINT32));

    return;
}


TAF_XSMS_MO_FSM_ID_ENUM_UINT32 TAF_XSMS_MoGetCurrFsmId(VOS_VOID)
{
    return (TAF_XSMS_MoGetCtxAddr()->stCurFsm.enFsmId);
}


TAF_XSMS_MT_FSM_ID_ENUM_UINT32 TAF_XSMS_MtGetCurrFsmId(VOS_VOID)
{
    return (TAF_XSMS_MtGetCtxAddr()->stCurFsm.enFsmId);
}


TAF_STA_STRU* TAF_XSMS_MoGetStaTblAddr(VOS_VOID)
{
    return g_astTafXsmsMoStaTbl;
}


VOS_VOID TAF_XSMS_MoIdleInit(VOS_VOID)
{
    TAF_XSMS_MO_CTX_STRU               *pstXsmsMoCtx = VOS_NULL_PTR;

    pstXsmsMoCtx = TAF_XSMS_MoGetCtxAddr();

    /* 将XSMS链路标志位置为FALSE */
    TAF_SDC_SetXsmsCallExistFlg(VOS_FALSE);

    /* 初始化MO全局变量 */
    TAF_XSMS_MoInitGobal();

    /* 初始化MO状态机ACT表 */
    pstXsmsMoCtx->stCurFsm.pstFsmDesc   = TAF_XSMS_MoGetStaTblAddr();

    /* 初始化MO状态 */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_IDLE_STATE);

    /* 停止MO所有定时器 */
    TAF_XSMS_MoStopAllTimer();

    /* 如果当前发送池不为空 发送文件池内容*/
    if (VOS_TRUE != TAF_XSMS_IsMoSendPoolEmpty())
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MoIdleInit: TAF_XSMS_IsMoSendPoolEmpty not empty");
        TAF_XSMS_RcvSendPoolMsgReq_MoIdle();
    }

    return;
}


TAF_STA_STRU* TAF_XSMS_MtGetStaTblAddr(VOS_VOID)
{
    return g_astTafXsmsMtStaTbl;
}


VOS_VOID TAF_XSMS_MtIdleInit(VOS_VOID)
{
    TAF_XSMS_MT_CTX_STRU               *pstXsmsMtCtx = VOS_NULL_PTR;

    pstXsmsMtCtx = TAF_XSMS_MtGetCtxAddr();

    /* 如果当前的链路时XSMS所有设置标志位 */
    TAF_SDC_SetXsmsCallExistFlg(VOS_FALSE);

    /* 初始MT化全局变量 */
    TAF_XSMS_MtInitGobal();

    /* 初始化MT状态机ACT表 */
    pstXsmsMtCtx->stCurFsm.pstFsmDesc = TAF_XSMS_MtGetStaTblAddr();

    /* 初始化 MT状态 */
    TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_IDLE_STATE);

    /* 停止MT所有定时器 */
    TAF_XSMS_MtStopAllTimer();

    return;
}


VOS_VOID TAF_XSMS_MoStopAllTimer(VOS_VOID)
{
    VOS_UINT32                          ulMoTimerId;

    for (ulMoTimerId = TI_TAF_XSMS_TIMER_MO_IDLE;
         ulMoTimerId < TI_TAF_XSMS_TIMER_MO_POOL_REFRESH;
         ulMoTimerId++)
    {
        if (VOS_NULL_PTR != g_astXsmsTimer[ulMoTimerId])
        {
            TAF_XSMS_StopTimer(ulMoTimerId);
        }
    }

    return;
}



VOS_VOID TAF_XSMS_MtStopAllTimer(VOS_VOID)
{
    VOS_UINT32                              ulMtTimerId;

    for (ulMtTimerId = TI_TAF_XSMS_TIMER_MT_IDLE;
         ulMtTimerId < TI_TAF_XSMS_TIMER_MT_END_LINK_PROTECT;
         ulMtTimerId++)
    {
        if (VOS_NULL_PTR != g_astXsmsTimer[ulMtTimerId])
        {
            TAF_XSMS_StopTimer(ulMtTimerId);
        }
    }

    return;
}


VOS_VOID TAF_XSMS_MoInitGobal(VOS_VOID)
{
    VOS_UINT32                          ulTmp;

    ulTmp = (VOS_UINT32)&g_stTafXsmsMoRec.st1xSms;

    /* 清空NV项之外的其他全局变量 */
    PS_MEM_SET((VOS_VOID *)ulTmp, 0, sizeof(TAF_XSMS_MSG_MO_REC_STRU) - sizeof(TAF_NVIM_1X_XSMS_CFG_STRU) - 4*sizeof(VOS_UINT8));

    PS_MEM_SET(&g_stTafXsmsMoCtx, 0, sizeof(g_stTafXsmsMoCtx));

    return;
}


VOS_VOID TAF_XSMS_MtInitGobal(VOS_VOID)
{
    VOS_UINT32                          ulTmp;

    ulTmp = (VOS_UINT32)&g_stTafXsmsMtRec.stTlAck;

    /* 清空NV项之外的其他全局变量 */
    PS_MEM_SET((VOS_VOID *)ulTmp, 0, sizeof(TAF_XSMS_MSG_MT_REC_STRU) - sizeof(TAF_NVIM_1X_XSMS_CFG_STRU));

    PS_MEM_SET(&g_stTafXsmsMtCtx, 0, sizeof(g_stTafXsmsMtCtx));

    return;
}


TAF_XSMS_CTRL_INFO_STRU * TAF_XSMS_GetReqCtrlInfoAddr(VOS_VOID)
{
    return &g_stTafXsmsReqCtrlInfo;
}


TAF_XSMS_INIT_CTRL_INFO_STRU * TAF_XSMS_GetInitCtrlInfoAddr(VOS_VOID)
{
    return &g_stTafXsmsInitCtrlInfo;
}


VOS_VOID TAF_XSMS_ReqCtrlInfoClear(VOS_VOID)
{
    PS_MEM_SET(TAF_XSMS_GetReqCtrlInfoAddr(), 0, sizeof(TAF_XSMS_CTRL_INFO_STRU));

    return;
}


VOS_VOID TAF_XSMS_InitCtrlInfoClear(VOS_VOID)
{
    PS_MEM_SET(TAF_XSMS_GetInitCtrlInfoAddr(), 0, sizeof(TAF_XSMS_INIT_CTRL_INFO_STRU));

    return;
}



VOS_UINT8 TAF_XSMS_MoGetBearSeqNum(TAF_XSMS_MSG_MO_REC_STRU *pstMoRec)
{
    VOS_UINT8 ucBearReqNum;

    ucBearReqNum            = pstMoRec->ucReplySeq % TAF_XSMS_BEAER_SEQ_NUM_MAX;

    pstMoRec->ucReplySeq    = ucBearReqNum + 1;

    TAF_XSMS_INFO_LOG1(" THE CURRENT SEQ NUM IS", ucBearReqNum);

    return ucBearReqNum;
}


VOS_VOID TAF_XSMS_InitFsmCtx_Main(VOS_VOID)
{
    return;
}

VOS_VOID TAF_XSMS_RegMoFsm(VOS_VOID)
{
    g_stTafXsmsMoFsmDesc.pStaTable          = g_astTafXsmsMoStaTbl;
    g_stTafXsmsMoFsmDesc.ulSize             = TAF_XSMS_GetMoFsmTblNum();

    /* 主处理状态机注册 */
    TAF_FSM_RegisterFsm(&g_stTafXsmsMoFsmDesc,
                         "TAF_XSMS:FSM:MainProcess",
                         g_stTafXsmsMoFsmDesc.ulSize,
                         g_astTafXsmsMoStaTbl,
                         VOS_NULL_PTR,
                         TAF_XSMS_InitFsmCtx_Main);

    return;
}


VOS_VOID TAF_XSMS_RegMtFsm(VOS_VOID)
{
    g_stTafXsmsMtFsmDesc.pStaTable          = g_astTafXsmsMtStaTbl;
    g_stTafXsmsMtFsmDesc.ulSize             = TAF_XSMS_GetMtFsmTblNum();

    /* 主处理状态机注册 */
    TAF_FSM_RegisterFsm(&g_stTafXsmsMtFsmDesc,
                         "TAF_XSMS:FSM:MainProcess",
                         g_stTafXsmsMtFsmDesc.ulSize,
                         g_astTafXsmsMtStaTbl,
                         VOS_NULL_PTR,
                         TAF_XSMS_InitFsmCtx_Main);

    return;
}


VOS_VOID TAF_XSMS_SetApMemFullFlag(
    TAF_XSMS_AP_MEM_FULL_ENUM_UINT8     enAPMemFullFlag
)
{
    if (TAF_XSMS_AP_MEM_BUTT <= enAPMemFullFlag)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_SetApMemFullFlag: WRONG enAPMemFullFlag");
        return;
    }

    if (TAF_XSMS_AP_MEM_FULL == enAPMemFullFlag)
    {
        g_enCcfMemFullFlag = TAF_XSMS_CCF_AP_MEM_FULL;
    }
    else
    {



        g_enCcfMemFullFlag = TAF_XSMS_CCF_AP_MEM_NOT_FULL;
    }

    return;
}


TAF_XSMS_CCF_AP_MEM_FULL_ENUM8 TAF_XSMS_GetApMemFullFlag(VOS_VOID)
{
    return g_enCcfMemFullFlag;
}


VOS_VOID TAF_XSMS_TranslatePlusToNum(
    TAF_XSMS_ADDR_STRU                 *pstXsmsAddr
)
{
    VOS_INT32                                               lSid;
    VOS_UINT16                                              usHomeMcc;
    VOS_UINT16                                              usCurMcc;
    TAF_SDC_1X_SYS_INFO_STRU                               *pstSdc1xSysInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucCurDigitsLen  = 0;
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                     enNumType;

    ucCurDigitsLen    = (VOS_UINT8)pstXsmsAddr->ulNumberOfDigits;

    /*获取mcc */
    pstSdc1xSysInfo   = TAF_SDC_Get1xSysInfo();

    usCurMcc          = TAF_STD_TransformBcdMccToDeciDigit(pstSdc1xSysInfo->stServiceInfo.ulMcc);

    lSid              = 0;

    /* 如果当前号码是国际号码而且是8BITS ASCII,转换成DTMF  */
    /* Used only when digitMode is 8-bit.
     * To specify an international address, use the following:
     * digitMode = TAF_XSMS_DIGIT_MODE_8_BIT
     * numberMode = TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK
     * numberType = TAF_XSMS_NUMBER_TYPE_INTERNATIONAL_OR_DATA_IP
     * numberPlan = TAF_XSMS_NUMBER_PLAN_TELEPHONY
     * numberOfDigits = number of digits
     * digits = ASCII digits, e.g. '1', '2', '3'3, '4', and '5'
     */
    if ((TAF_XSMS_DIGIT_MODE_8_BIT                     == pstXsmsAddr->enDigitMode)
     && (TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK         == pstXsmsAddr->enNumberMode)
     && (TAF_XSMS_NUMBER_PLAN_TELEPHONY                == pstXsmsAddr->enNumberPlan)
     && (TAF_XSMS_NUMBER_TYPE_INTERNATIONAL_OR_DATA_IP == pstXsmsAddr->enNumberType))
    {
        if (TAF_XSMS_ADDRESS_MAX < pstXsmsAddr->ulNumberOfDigits)
        {
            TAF_XSMS_ERROR_LOG1("TAF_XSMS_TranslatePlusToNum: num is too many", pstXsmsAddr->ulNumberOfDigits);
            return;
        }
        /* 当前的短信默认只支持在大陆和澳门发送，X模手机在国外其他地方切成GU模式 */
        /* 大陆 或者 澳门*/
        /* 获取HOME MCC */
        usHomeMcc = (VOS_UINT16)TAF_XSMS_GetHomeMcc();

        if ((460 != usCurMcc)
         && (455 != usCurMcc))
        {
            /* 在非中国和澳门，打印但是正常转换 */
            TAF_XSMS_ERROR_LOG("TAF_XSMS_TranslatePlusToNum : home mcc is not China/Macao");
        }

        enNumType = TAF_PLUS_TRANSLATE_NUM_INTERNATIONAL;

        lSid      = TAF_ConvertHomeMccToSidRange(usHomeMcc);

        TAF_TranslatePlusToNum(lSid,
                               TAF_PLUS_TRANSLATE_DIAL_TYPE_SMS,
                               &enNumType,
                               pstXsmsAddr->aucDigits,
                               &ucCurDigitsLen);

        pstXsmsAddr->ulNumberOfDigits   = ucCurDigitsLen;

        /* 将ASCII 转换成DTMF */
        TAF_XSMS_TransAsciiToDtmf(pstXsmsAddr->aucDigits,
                                  pstXsmsAddr->aucDigits,
                                  ucCurDigitsLen);

        pstXsmsAddr->enDigitMode    = TAF_XSMS_DIGIT_MODE_4_BIT;
        pstXsmsAddr->enNumberMode   = TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK;
        pstXsmsAddr->enNumberPlan   = TAF_XSMS_NUMBER_PLAN_UNKNOWN;
        pstXsmsAddr->enNumberType   = TAF_XSMS_NUMBER_TYPE_UNKNOWN;

    }
    return ;
}


VOS_UINT32 TAF_XSMS_GetHomeMcc(
    VOS_VOID
)
{
    VOS_UINT8                           aucImsiData[10] = {0};
    VOS_UINT16                          usMcc           = 460;
    VOS_UINT32                          ulDataLen       = 0;
    VOS_UINT8                          *pucImsiData    = VOS_NULL_PTR;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType;

    /* 得到卡文件中的IMSI */
    enCsimType =  TAF_SDC_GetCsimType();

    if (TAF_SDC_SIM_TYPE_CSIM == enCsimType)
    {
        if (VOS_OK != USIMM_GetCachedFile(USIMM_CSIM_EFIMSIM_STR, &ulDataLen, &pucImsiData, USIMM_CDMA_APP))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_GetHomeMcc: USIMM_GetCachedFile ERR");
            return usMcc;
        }
    }
    else if (TAF_SDC_SIM_TYPE_UIM == enCsimType)
    {
        if (VOS_OK != USIMM_GetCachedFile(USIMM_CDMA_EFIMSIM_STR, &ulDataLen, &pucImsiData, USIMM_CDMA_APP))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_GetHomeMcc: USIMM_GetCachedFile ERR");
            return usMcc;
        }
    }
    else
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetHomeMcc: WRONG CARD TYPE");
        return usMcc;
    }

    if (VOS_NULL_PTR == pucImsiData)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetHomeMcc: pucImsiData null");
        return usMcc;
    }

    PS_MEM_CPY(aucImsiData, pucImsiData, 10);

    usMcc       = ((aucImsiData[9] & 0x03) << 8) + aucImsiData[8];

    usMcc       = TAF_XSMS_GET_MCC(usMcc);

    return usMcc;
}


VOS_VOID TAF_XSMS_TransAsciiToDtmf(
    VOS_UINT8                          *pucSrcData,
    VOS_UINT8                          *pucDestData,
    VOS_UINT8                           ucLen
)
{
    VOS_UINT16                          usIndex = 0;

    for (; usIndex < ucLen; usIndex++)
    {

        if ((0x30 > pucSrcData[usIndex])
        ||  (0x39 < pucSrcData[usIndex]))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_TransAsciiToDtmf : address is not num");

            return;
        }

        if (0 == (pucSrcData[usIndex] % 16))
        {
            pucDestData[usIndex] = 0x0a;
        }
        else
        {
            pucDestData[usIndex] = pucSrcData[usIndex] % 16;
        }
    }

    return;
}


VOS_VOID TAF_XSMS_MoInitSendPool(VOS_VOID)
{
    PS_MEM_SET(&g_stXsmsMoSendPool, 0, sizeof(TAF_XSMS_MO_SEND_POOL_ITEM_STRU));
    return;
}

/* 判断是不是记录满 */

VOS_UINT32 TAF_XSMS_IsMoSendPoolFull(VOS_VOID)
{
    return (VOS_UINT32)((g_stXsmsMoSendPool.ulCurItemNumInPool < TAF_XSMS_MAX_REC_IN_POOL)? VOS_FALSE:VOS_TRUE);
}

/* 插入缓冲池记录 */

VOS_UINT32 TAF_XSMS_InsertRecToMoSendPool
(
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid,
    VOS_UINT16                          usIsTlAckNeeded,
    VOS_UINT16                          usOpId,
    TAF_XSMS_MESSAGE_STRU              *pst1xSms
)
{
    TAF_XSMS_MO_SEND_POOL_ITEM_STRU    *pstFirstEmptyRec = VOS_NULL_PTR;

    if (VOS_TRUE == TAF_XSMS_IsMoSendPoolFull())
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_InsertRecToMoSendPool: MO SEND POOL IS FULL");
        return VOS_ERR;
    }

    /* 如果当前为空，设置需要启动轮询定时器 */

    if (VOS_TRUE == TAF_XSMS_IsMoSendPoolEmpty())
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_InsertRecToMoSendPool: need start timer");
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_POOL_REFRESH, TI_TAF_XSMS_TIMER_MO_POOL_REFRESH_MAX);
    }

    pstFirstEmptyRec = &g_stXsmsMoSendPool.stPoolItem[g_stXsmsMoSendPool.ulCurItemNumInPool];

    pstFirstEmptyRec->pst1xSms = (TAF_XSMS_MESSAGE_STRU*)PS_MEM_ALLOC(UEPS_PID_XSMS, sizeof(TAF_XSMS_MESSAGE_STRU));

    if (VOS_NULL_PTR == pstFirstEmptyRec->pst1xSms)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_InsertRecToMoSendPool: pstCurSMS is null ptr");
        return VOS_ERR;
    }

    PS_MEM_CPY(pstFirstEmptyRec->pst1xSms, pst1xSms, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstFirstEmptyRec->enOrigPid             = enOrigPid;
    pstFirstEmptyRec->ucIsRecExist          = VOS_TRUE;
    pstFirstEmptyRec->ucRecTimeLeft         = TAF_XSMS_POOL_REC_MAX_TIME;
    pstFirstEmptyRec->usIsTlAckNeeded       = usIsTlAckNeeded;
    pstFirstEmptyRec->usOpId                = usOpId;

    g_stXsmsMoSendPool.ulCurItemNumInPool++;

    return VOS_OK;
}


/* 删除一个记录 */

VOS_UINT32 TAF_XSMS_DeleteRecInMoSendPool(
    VOS_UINT32                          ulRecIndex
)
{
    TAF_XSMS_MO_SEND_POOL_ITEM_STRU    *pstFirstEmptyRec = VOS_NULL_PTR;

    /* 被删除的元素不在里面 */
    if (ulRecIndex >= g_stXsmsMoSendPool.ulCurItemNumInPool)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_DeleteRecInMoSendPool: ulRecIndex not valid");
        return VOS_ERR;
    }

    pstFirstEmptyRec = &g_stXsmsMoSendPool.stPoolItem[ulRecIndex];

    if (VOS_NULL_PTR != pstFirstEmptyRec->pst1xSms)
    {
        PS_MEM_FREE(UEPS_PID_XSMS,pstFirstEmptyRec->pst1xSms);
    }

    /* 如果是最后一个元素不需要memmove */
    if (ulRecIndex != (g_stXsmsMoSendPool.ulCurItemNumInPool - 1))
    {
        PS_MEM_MOVE(pstFirstEmptyRec,
                    &g_stXsmsMoSendPool.stPoolItem[ulRecIndex + 1],
                    sizeof(TAF_XSMS_MO_SEND_POOL_ITEM_STRU) * (g_stXsmsMoSendPool.ulCurItemNumInPool - ulRecIndex - 1)); /* 移动长度 原来总元素个数 -1 -被删掉的index */

    }

    g_stXsmsMoSendPool.ulCurItemNumInPool--;

    /* 将memmove之后的最后一个元素 清空 */
    PS_MEM_SET(&g_stXsmsMoSendPool.stPoolItem[g_stXsmsMoSendPool.ulCurItemNumInPool],
                0,
                sizeof(TAF_XSMS_MO_SEND_POOL_ITEM_STRU));

    return VOS_OK;
}

/* POP出来一个记录 */

VOS_UINT32 TAF_XSMS_GetRecFromMoSendPool
(
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16   *pusOrigPid,
    VOS_UINT16                         *pusIsTlAckNeeded,
    VOS_UINT16                         *pusOpId,
    TAF_XSMS_MESSAGE_STRU              *pst1xSms
)
{

    TAF_XSMS_MO_SEND_POOL_ITEM_STRU    *pstFirstRec;

    if (g_stXsmsMoSendPool.ulCurItemNumInPool < 1)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetRecFromMoSendPool : cur pool is empty");
        return VOS_ERR;
    }

    pstFirstRec             = &g_stXsmsMoSendPool.stPoolItem[0];

    *pusOrigPid             = pstFirstRec->enOrigPid;
    *pusIsTlAckNeeded       = pstFirstRec->usIsTlAckNeeded;
    *pusOpId                = pstFirstRec->usOpId;

    PS_MEM_CPY(pst1xSms, pstFirstRec->pst1xSms, sizeof(TAF_XSMS_MESSAGE_STRU));

    TAF_XSMS_DeleteRecInMoSendPool(0);

    return VOS_OK;
}

/* 定时器超时之后刷新所有记录 */

VOS_VOID TAF_XSMS_RefreshRecsInMoSendPool(VOS_VOID)
{
    VOS_UINT16                          usIndex = 0;

    /* 如果已经超时删除当前元素 */
    while (usIndex < g_stXsmsMoSendPool.ulCurItemNumInPool)
    {
        /* 如果遗留时间大于1 时间-- */
        if (1 <= g_stXsmsMoSendPool.stPoolItem[usIndex].ucRecTimeLeft)
        {
           g_stXsmsMoSendPool.stPoolItem[usIndex].ucRecTimeLeft--;
        }

        /* 时间耗尽删除记录 */
        if (0 == g_stXsmsMoSendPool.stPoolItem[usIndex].ucRecTimeLeft)
        {
            TAF_XSMS_DeleteRecInMoSendPool(usIndex);
        }
        else
        {
            usIndex++;
        }
    }

    /* 如果还有记录，启动轮询定时器 */

    if (VOS_TRUE != TAF_XSMS_IsMoSendPoolEmpty())
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_POOL_REFRESH, TI_TAF_XSMS_TIMER_MO_POOL_REFRESH_MAX);
    }

    return;
}



VOS_UINT32 TAF_XSMS_IsRecCanInsertToPool
(
    TAF_XSMS_SMS_ORIGPID_ENUM_UINT16    enOrigPid
)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    VOS_UINT32                          ulIndex = 0;
    VOS_UINT8                           ucMsfSendingNum = 0;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    if (VOS_TRUE ==  TAF_XSMS_IsMoSendPoolFull())
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_IsRecCanInsertToPool : TAF_XSMS_IsMoSendPoolFull");
        return VOS_FALSE;
    }

    /* 如果文件池中的特定短信个数加已经在发的短信个数大于限度，不能在插入 */
    if (enOrigPid == pstMoRec->enOrigPid)
    {
        ucMsfSendingNum++;
    }

    for (ulIndex = 0;
         ulIndex < g_stXsmsMoSendPool.ulCurItemNumInPool;
         ulIndex++)
    {
        if (enOrigPid == g_stXsmsMoSendPool.stPoolItem[ulIndex].enOrigPid)
        {
            ucMsfSendingNum++;
        }
    }

    /* XCALL的限度 是3条，其他类型是2条 */
    if ((TAF_XSMS_SMS_ORIGPID_XCALL == enOrigPid)
     && (2 >= ucMsfSendingNum))
    {
        return VOS_TRUE;
    }

    if (1 >= ucMsfSendingNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID TAF_XSMS_GetKmcDefaultAddress
(
    TAF_XSMS_ADDR_STRU                 *pstXsmsKmcAddr
)
{
    TAF_XSMS_KMC_DEF_ADDRESS_STRU       stDefAddr;

    PS_MEM_SET(&stDefAddr, 0, sizeof(TAF_XSMS_KMC_DEF_ADDRESS_STRU));

    /* 先读NV 2045,NV读取失败使用默认值 */
    if (NV_OK != NV_Read(en_NV_Item_1X_XSMS_KMC_ADDRESS,
                         &stDefAddr,
                         sizeof(TAF_XSMS_KMC_DEF_ADDRESS_STRU)))
    {
        /* read nv fail, use def value  */
        stDefAddr.usNumOfDigits     = 11;

        stDefAddr.aucDigits[0]      = 1;
        stDefAddr.aucDigits[1]      = 8;
        stDefAddr.aucDigits[2]      = 9;
        stDefAddr.aucDigits[3]      = 1;
        stDefAddr.aucDigits[4]      = 8;
        stDefAddr.aucDigits[5]      = 9;
        stDefAddr.aucDigits[6]      = 1;
        stDefAddr.aucDigits[7]      = 0x0a;
        stDefAddr.aucDigits[8]      = 0x0a;;
        stDefAddr.aucDigits[9]      = 0x0a;;
        stDefAddr.aucDigits[10]     = 1;

        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetKmcDefaultAddress:NV_Read fail");
    }

    PS_MEM_SET(pstXsmsKmcAddr, 0, sizeof(TAF_XSMS_ADDR_STRU));

    pstXsmsKmcAddr->enDigitMode    = TAF_XSMS_DIGIT_MODE_4_BIT;
    pstXsmsKmcAddr->enNumberMode   = TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK;
    pstXsmsKmcAddr->enNumberPlan   = TAF_XSMS_NUMBER_PLAN_UNKNOWN;
    pstXsmsKmcAddr->enNumberType   = TAF_XSMS_NUMBER_TYPE_UNKNOWN;

    pstXsmsKmcAddr->ulNumberOfDigits = stDefAddr.usNumOfDigits;

    PS_MEM_CPY(pstXsmsKmcAddr->aucDigits,
               stDefAddr.aucDigits,
               stDefAddr.usNumOfDigits);
    return;
}



VOS_UINT32 TAF_XSMS_IsMoSendPoolEmpty(VOS_VOID)
{
    return (VOS_UINT32)((g_stXsmsMoSendPool.ulCurItemNumInPool == 0)? VOS_TRUE:VOS_FALSE);
}


VOS_UINT32 TAF_XSMS_IsMtKmcSms(
    TAF_XSMS_ADDR_STRU                 *pstXsmsKmcAddr
)
{
    TAF_XSMS_ADDR_STRU                  stXsmsAddr;

    PS_MEM_SET(&stXsmsAddr, 0, sizeof(TAF_XSMS_ADDR_STRU));

    TAF_XSMS_GetKmcDefaultAddress(&stXsmsAddr);

    /* 比较号码内容 */
    /*
    1.0 号码是18918910001 或者 是8618918910001
    */

    if (pstXsmsKmcAddr->ulNumberOfDigits == stXsmsAddr.ulNumberOfDigits)
    {
        if (0 == PS_MEM_CMP(stXsmsAddr.aucDigits, pstXsmsKmcAddr->aucDigits, stXsmsAddr.ulNumberOfDigits))
        {
            return VOS_TRUE;
        }
    }
    else
    {
        if (0 == PS_MEM_CMP(stXsmsAddr.aucDigits, pstXsmsKmcAddr->aucDigits + 2, stXsmsAddr.ulNumberOfDigits))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



