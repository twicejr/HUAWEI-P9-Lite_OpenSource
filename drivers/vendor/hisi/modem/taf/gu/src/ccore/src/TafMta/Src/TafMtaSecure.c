/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaSecure.c
  版 本 号   : 初稿
  作    者   : 李紫剑/00198894
  生成日期   : 2012年8月30日
  最近修改   :
  功能描述   : 包含MTA模块安全相关函数
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月30日
    作    者   : 李紫剑/00198894
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafMtaSecure.h"
#include "TafMtaMain.h"
#include "ScInterface.h"
#include "SysNvId.h"
#include "TafNvInterface.h"
#include "NVIM_Interface.h"
#include "TafMtaComm.h"
#include "mdrv.h"
#include "TafSdcCtx.h"
#include "NasUsimmApi.h"
#include "NasMsccPifInterface.h"
#include "TafMmaFsmPhoneMode.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "omnvinterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 修改人: 李紫剑 00198894; 原因: Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_SECURE_C
/*lint +e767 修改人: 李紫剑 00198894; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_MTA_ConvertScErr
 功能描述  : 转换SC模块返回的错误码
 输入参数  : enErrCode  -- SC模块返回的错误码
 输出参数  : 无
 返 回 值  : MTA_AT_RESULT_ENUM_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月04日
    作    者   : l00198894
    修改内容   : 新增函数
*****************************************************************************/
MTA_AT_RESULT_ENUM_UINT32 TAF_MTA_ConvertScErr(
    SC_ERROR_CODE_ENUM_UINT32           enErrCode
)
{
    switch(enErrCode)
    {
        case SC_ERROR_CODE_NO_ERROR:
            return MTA_AT_RESULT_NO_ERROR;

        case SC_ERROR_CODE_OPEN_FILE_FAIL:
        case SC_ERROR_CODE_READ_FILE_FAIL:
        case SC_ERROR_CODE_WRITE_FILE_FAIL:
        case SC_ERROR_CODE_WRITE_FILE_IMEI_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_FLASH_ERROR;

        case SC_ERROR_CODE_VERIFY_SIGNATURE_FAIL:
        case SC_ERROR_CODE_VERIFY_PUB_KEY_SIGNATURE_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

        case SC_ERROR_CODE_DK_INCORRECT:
            return MTA_AT_RESULT_DEVICE_SEC_DK_INCORRECT;

        case SC_ERROR_CODE_UNLOCK_KEY_INCORRECT:
            return MTA_AT_RESULT_DEVICE_SEC_UNLOCK_KEY_INCORRECT;

        case SC_ERROR_CODE_RSA_ENCRYPT_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_RSA_ENCRYPT_FAIL;

        case SC_ERROR_CODE_RSA_DECRYPT_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_RSA_DECRYPT_FAIL;

        case SC_ERROR_CODE_GET_RAND_NUMBER_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_GET_RAND_NUMBER_FAIL;

        case SC_ERROR_CODE_IDENTIFY_FAIL:
        case SC_ERROR_CODE_IDENTIFY_NOT_FINISH:
            return MTA_AT_RESULT_DEVICE_SEC_IDENTIFY_FAIL;

        case SC_ERROR_CODE_WRITE_HUK_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_WRITE_HUK_FAIL;

        case SC_ERROR_CODE_NV_READ_FAIL:
        case SC_ERROR_CODE_NV_WRITE_FAIL:
            return MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;

        case SC_ERROR_CODE_LOCK_CODE_INVALID:
        case SC_ERROR_CODE_CREATE_KEY_FAIL:
        case SC_ERROR_CODE_GENERATE_HASH_FAIL:
        case SC_ERROR_CODE_AES_ECB_ENCRYPT_FAIL:
        case SC_ERROR_CODE_ALLOC_MEM_FAIL:
        case SC_ERROR_CODE_UNLOCK_STATUS_ABNORMAL:
        case SC_ERROR_CODE_BUTT:
        default:
            /* 上述错误以及其他错误，返回OTHER_ERROR */
            return MTA_AT_RESULT_DEVICE_SEC_OTHER_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtApSecSetReq
 功能描述  : 处理AT模块发送的ID_AT_MTA_APSEC_SET_REQ消息
 输入参数  : VOS_VOID *pMsg     -- AT模块发送的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月30日
    作    者   : 李紫剑/00198894
    修改内容   : V7R1C50 ISDB 安全存储项目新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtApSecSetReq( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;
    AT_MTA_APSEC_REQ_STRU              *pstApSecReq;
    MTA_AT_APSEC_CNF_STRU               stApSecCnf;
    VOS_UINT32                          ulResult;

    /* 局部变量初始化 */
    pstAtMtaReqMsg  = (AT_MTA_MSG_STRU*)pMsg;
    pstApSecReq     = (AT_MTA_APSEC_REQ_STRU*)pstAtMtaReqMsg->aucContent;

    /* 调用SC模块提供的安全封包解析函数 */
    ulResult        = SC_APSEC_ParseSecPacket(&pstApSecReq->ulSPLen,
                                              pstApSecReq->aucSecPacket);
    if (VOS_OK == ulResult)
    {
        /* 解析成功，将返回的安全封包发送给AT模块 */
        stApSecCnf.enResult = MTA_AT_RESULT_NO_ERROR;
        stApSecCnf.ulSPLen  = pstApSecReq->ulSPLen;
        PS_MEM_CPY(stApSecCnf.aucSecPacket, pstApSecReq->aucSecPacket, MTA_SEC_PACKET_MAX_LEN);
    }
    else
    {
        /* 解析失败，返回对应的错误码 */
        PS_MEM_SET(&stApSecCnf, 0x00, sizeof(MTA_AT_APSEC_CNF_STRU));
        stApSecCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_APSEC_SET_CNF,
                      sizeof(MTA_AT_APSEC_CNF_STRU),
                      (VOS_UINT8*)&stApSecCnf );

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtSimlockUnlockSetReq
 功能描述  : 处理AT模块发送的ID_AT_MTA_SIMLOCKUNLOCK_SET_REQ消息
 输入参数  : VOS_VOID *pMsg     -- AT模块发送的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年09月18日
    作    者   : 李紫剑/00198894
    修改内容   : STK补充特性及DCM需求开发项目新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSimlockUnlockSetReq( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;
    AT_MTA_SIMLOCKUNLOCK_REQ_STRU      *pstSimlockUnlockReq;
    MTA_AT_SIMLOCKUNLOCK_CNF_STRU       stSimlockUnlockCnf;
    VOS_UINT32                          ulResult;

    /* 局部变量初始化 */
    pstAtMtaReqMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstSimlockUnlockReq     = (AT_MTA_SIMLOCKUNLOCK_REQ_STRU *)pstAtMtaReqMsg->aucContent;

    /* 调用SC模块提供的锁网锁卡解锁函数 */
    ulResult        = SC_PERS_SimlockUnlock(pstSimlockUnlockReq->enCategory,
                                            pstSimlockUnlockReq->aucPassword);
    if (VOS_OK == ulResult)
    {
        /* 解锁成功，返回结果给AT模块 */
        stSimlockUnlockCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        /* 解锁失败，返回结果给AT模块 */
        stSimlockUnlockCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF,
                      sizeof(MTA_AT_SIMLOCKUNLOCK_CNF_STRU),
                      (VOS_UINT8*)&stSimlockUnlockCnf );

    return;
}

/**********************************************************
 函 数 名  : TAF_MTA_RcvQryImeiVerifyReq
 功能描述  : IMEI 校验
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月23日
    作    者   : Y00213812
    修改内容   : 新增函数
*************************************************************/
VOS_VOID TAF_MTA_RcvQryImeiVerifyReq(VOS_VOID *pMsg)
{
    SC_ERROR_CODE_ENUM_UINT32           enScResult;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulImeiVerify;
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg = VOS_NULL_PTR;

    pstAtMtaReqMsg = (AT_MTA_MSG_STRU *)pMsg;
    ulImeiVerify = VOS_TRUE;

    /* 由PID获取MODEMID */
    enModemId = VOS_GetModemIDFromPid(UEPS_PID_MTA);

    /* 调用SC接口进行IMEI校验，若函数执行失败，则按照IMEI校验失败处理 */
    enScResult = SC_PERS_VerifyIMEI(enModemId);
    if (SC_ERROR_CODE_NO_ERROR != enScResult)
    {
        ulImeiVerify = VOS_FALSE;
    }

    /* 返回跨核消息ID_MTA_AT_IMEI_VERIFY_QRY_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_IMEI_VERIFY_QRY_CNF,
                      sizeof(VOS_UINT32),
                      (VOS_UINT8*)&ulImeiVerify );

    return;
}

/**********************************************************
 函 数 名  : TAF_MTA_RcvQryCgsnReq
 功能描述  : IMEI 校验
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月23日
    作    者   : Y00213812
    修改内容   : 新增函数
*************************************************************/
VOS_VOID TAF_MTA_RcvQryCgsnReq(VOS_VOID *pMsg)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg = VOS_NULL_PTR;
    MTA_AT_CGSN_QRY_CNF_STRU            stCgsnCnf;

    /* 初始化 */
    pstAtMtaReqMsg = (AT_MTA_MSG_STRU *)pMsg;
    PS_MEM_SET(&stCgsnCnf, 0x00, sizeof(MTA_AT_CGSN_QRY_CNF_STRU));

    /* 由PID获取MODEMID */
    enModemId = VOS_GetModemIDFromPid(UEPS_PID_MTA);

    /* 调用SC接口读取IMEI号码 */
    (VOS_VOID)SC_PERS_VerifyNvReadImei(enModemId, en_NV_Item_IMEI, stCgsnCnf.aucImei, NV_ITEM_IMEI_SIZE);

    /* 返回跨核消息ID_MTA_AT_IMEI_VERIFY_QRY_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_CGSN_QRY_CNF,
                      sizeof(MTA_AT_CGSN_QRY_CNF_STRU),
                      (VOS_UINT8*)&stCgsnCnf );

    return;
}


/*lint +e958*/

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvAtNvwrSecCtrlSetReq
 功能描述  : 处理AT模块发送的ID_AT_MTA_NVWRSECCTRL_SET_REQ消息
 输入参数  : VOS_VOID *pMsg     -- AT模块发送的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月04日
    作    者   : l00198894
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtNvwrSecCtrlSetReq( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg;
    AT_MTA_NVWRSECCTRL_SET_REQ_STRU    *pstNvwrSecCtrlReq;
    MTA_AT_RESULT_CNF_STRU              stNvwrSecCtrlCnf;
    TAF_NV_NVWR_SEC_CTRL_STRU           stNvwrSecCtrlNV;
    IMEI_STRU                           stImeiSrc;
    IMEI_STRU                           stImeiPara;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulImeiLen;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucImeiStr[TAF_NVIM_ITEM_IMEI_SIZE + 1];

    /* 局部变量初始化 */
    pstAtMtaReqMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstNvwrSecCtrlReq       = (AT_MTA_NVWRSECCTRL_SET_REQ_STRU *)pstAtMtaReqMsg->aucContent;

    /* SC提供的RSA封装需要调用者将解密后结果的预期长度传入 */
    ulImeiLen               = MTA_IMEI_LEN;

    PS_MEM_SET(&stNvwrSecCtrlNV, 0x00, sizeof(stNvwrSecCtrlNV));
    PS_MEM_SET(&stNvwrSecCtrlCnf, 0x00, sizeof(stNvwrSecCtrlCnf));
    PS_MEM_SET(&stImeiSrc, 0x00, sizeof(stImeiSrc));
    PS_MEM_SET(&stImeiPara, 0x00, sizeof(stImeiPara));
    PS_MEM_SET(aucImeiStr, 0x00, sizeof(aucImeiStr));

    /* 如果单板没有HUK则不作安全校验 */
    if (VOS_TRUE == mdrv_efuse_check_huk_valid())
    {
        /* 单板已经写入HUK但未下发安全密文则返回失败 */
        if (VOS_TRUE != pstNvwrSecCtrlReq->ucSecStrFlg)
        {
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* 由PID获取MODEMID */
        enModemId = VOS_GetModemIDFromPid(UEPS_PID_MTA);

        /* 调用SC接口读取IMEI号码 */
        ulResult = SC_PERS_VerifyNvReadImei(enModemId, en_NV_Item_IMEI, stImeiSrc.aucImei, TAF_NVIM_ITEM_IMEI_SIZE);

        if (SC_ERROR_CODE_NO_ERROR != ulResult)
        {
            /* 异常，返回结果给AT模块 */
            stNvwrSecCtrlCnf.enResult = TAF_MTA_ConvertScErr(ulResult);

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* 调用SC模块接口, 对密文进行RSA解密 */
        ulResult = SC_FAC_RsaDecrypt(pstNvwrSecCtrlReq->aucSecString,
                                     AT_RSA_CIPHERTEXT_LEN,
                                     aucImeiStr,
                                     &ulImeiLen);

        if (MTA_IMEI_LEN != ulImeiLen)
        {
            ulResult = SC_ERROR_CODE_RSA_DECRYPT_FAIL;
        }

        if (SC_ERROR_CODE_NO_ERROR != ulResult)
        {
            /* 异常，返回结果给AT模块 */
            stNvwrSecCtrlCnf.enResult = TAF_MTA_ConvertScErr(ulResult);

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* 数字字符串转换为数字串 */
        if (VOS_OK != TAF_MTA_AcNums2DecNums(aucImeiStr, stImeiPara.aucImei, ulImeiLen))
        {
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }

        /* 校验IMEI码 */
        if (0 != PS_MEM_CMP(stImeiPara.aucImei, stImeiSrc.aucImei, ulImeiLen))
        {
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_SIGNATURE_FAIL;

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }
    }

    /* 修改安全控制NV */
    if (NV_OK == NV_Read(en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
    {
        stNvwrSecCtrlNV.ucSecType = pstNvwrSecCtrlReq->ucSecType;

        if (NV_OK == NV_Write(en_NV_Item_NVWR_SEC_CTRL, &stNvwrSecCtrlNV, sizeof(stNvwrSecCtrlNV)))
        {
            /* 设置成功 */
            stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_NO_ERROR;

            /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
            TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                              ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                              sizeof(stNvwrSecCtrlCnf),
                              (VOS_UINT8*)&stNvwrSecCtrlCnf );

            return;
        }
    }

    /* NV修改失败 */
    stNvwrSecCtrlCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 返回跨核消息ID_MTA_AT_APSEC_SET_CNF到AT模块 */
    TAF_MTA_SndAtMsg( &pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_NVWRSECCTRL_SET_CNF,
                      sizeof(stNvwrSecCtrlCnf),
                      (VOS_UINT8*)&stNvwrSecCtrlCnf );

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#ifdef DMT
VOS_UINT32 CAS_GetpEsnByMeid(VOS_UINT8 *pucMeid, VOS_UINT32 *pulEsn)
{
    *pulEsn = 0x80c16f14;

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvMeidSetReq
 功能描述  : MTA预处理中处理^MEID设置命令
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月23日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvMeidSetReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq       = VOS_NULL_PTR;
    AT_MTA_MEID_SET_REQ_STRU           *pstMeidSetReq   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stMeifSetCnf;
    NV_MEID_STRU                        stMeId;
    NV_PESN_STRU                        stPEsn;
    NV_ESN_MEID_STRU                    stEsnMeId;
    VOS_UINT32                          ulEsn;

    PS_MEM_SET(&stMeId, 0x00, sizeof(NV_MEID_STRU));
    PS_MEM_SET(&stPEsn, 0x00, sizeof(NV_PESN_STRU));
    PS_MEM_SET(&stEsnMeId, 0x00, sizeof(NV_ESN_MEID_STRU));
    PS_MEM_SET(&stMeifSetCnf, 0x00, sizeof(stMeifSetCnf));

    pstSetReq           = (AT_MTA_MSG_STRU *)pMsg;
    pstMeidSetReq       = (AT_MTA_MEID_SET_REQ_STRU *)pstSetReq->aucContent;

    PS_MEM_CPY(stMeId.aucMeID, pstMeidSetReq->aucMeid, AT_MTA_MEID_DATA_LEN * sizeof(VOS_UINT8));

    /* 根据meid计算pesn */
    if (VOS_OK != CAS_GetpEsnByMeid(pstMeidSetReq->aucMeid, &ulEsn))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():Cal PESN Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_INCORRECT_PARAMETERS;
        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    stPEsn.aucPEsn[0] = ((VOS_UINT8)ulEsn & 0xFF);
    stPEsn.aucPEsn[1] = ((VOS_UINT8)(ulEsn>>8) & 0xFF);
    stPEsn.aucPEsn[2] = ((VOS_UINT8)(ulEsn>>16) & 0xFF);
    stPEsn.aucPEsn[3] = ((VOS_UINT8)(ulEsn>>24) & 0xFF);

    if (NV_OK != NV_Write(en_NV_Item_MEID, &stMeId, sizeof(stMeId)))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():en_NV_Item_MEID NV Write Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;
        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    if (NV_OK != NV_Write(en_NV_Item_PESN, &stPEsn, sizeof(stPEsn)))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():en_NV_Item_PESN NV Write Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;
        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    /* 更新老的NV项 */
    stEsnMeId.enEsnMeIDFlag = MEID_ME_ENABLE_FLAG;
    stEsnMeId.aucEsn[0]     = PESN_NV_DATA_LEN;
    PS_MEM_CPY(&(stEsnMeId.aucEsn[1]), stPEsn.aucPEsn, PESN_NV_DATA_LEN);

    stEsnMeId.aucMeID[0]    = MEID_NV_DATA_LEN_NEW;
    PS_MEM_CPY(&(stEsnMeId.aucMeID[1]), stMeId.aucMeID, MEID_NV_DATA_LEN_NEW);

    if (NV_OK != NV_Write(en_NV_Item_ESN_MEID, &stEsnMeId, sizeof(stEsnMeId)))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidSetReq():en_NV_Item_ESN_MEID NV Write Fail!");

        stMeifSetCnf.enResult = MTA_AT_RESULT_DEVICE_SEC_NV_ERROR;
        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MEID_SET_CNF,
                         sizeof(stMeifSetCnf),
                         (VOS_UINT8*)&stMeifSetCnf );

        return;
    }

    stMeifSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;

    /* 给at回消息 */
    TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                     ID_MTA_AT_MEID_SET_CNF,
                     sizeof(stMeifSetCnf),
                     (VOS_UINT8*)&stMeifSetCnf );

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvMeidQryReq
 功能描述  : MTA预处理中处理^MEID查询命令
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月18日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvMeidQryReq(
    VOS_VOID                           *pMsg
)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimCardStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8                          enCsimStatus;
    MTA_AT_MEID_QRY_CNF_STRU                                stMeifQryCnf;
    AT_MTA_MSG_STRU                                        *pstQryReq       = VOS_NULL_PTR;
    TAF_SDC_SIM_TYPE_ENUM_UINT8                             enCsimType;

    PS_MEM_SET(&stMeifQryCnf, 0x00, sizeof(stMeifQryCnf));

    pstQryReq = (AT_MTA_MSG_STRU *)pMsg;

#ifdef DMT
    enCsimStatus = TAF_SDC_USIM_STATUS_UNVALID;
#else
    enCsimStatus = TAF_SDC_GetCsimStatus();
#endif

    enCsimType   = TAF_SDC_GetCsimType();

    /* 消除coverity告警 */
    if (TAF_SDC_USIM_STATUS_BUTT == enCsimStatus)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidQryReq: Csim Status is BUTT!");
    }

    if (TAF_SDC_SIM_TYPE_BUTT == enCsimType)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidQryReq: Csim Type is BUTT!");
    }
    /* 消除coverity告警 */

    enCsimCardStatus = TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode(enCsimStatus, enCsimType);

    if (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT == enCsimCardStatus)
    {
        /* 读取卡文件6f31 */
        TAF_MTA_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CSIM_EFRUIMID_ID);
    }
    else if (NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT == enCsimCardStatus)
    {
        /* 读取卡文件6f31 */
        TAF_MTA_SndReadUsimmFileReq(USIMM_CDMA_APP, USIMM_CDMA_EFRUIMID_ID);
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvMeidQryReq():Card State Error!");

        stMeifQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;

        /* 给at回消息 */
        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_MEID_QRY_CNF,
                         sizeof(stMeifQryCnf),
                         (VOS_UINT8*)&stMeifQryCnf);

        return;
    }

    /* 卡存在时，启动定时器 */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_UIMID_READ_CNF, TI_TAF_MTA_WAIT_UIMID_READ_CNF_LEN);

    /* 添加消息进等待队列 */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_UIMID_READ_CNF,
                                    (VOS_UINT8*)&(pstQryReq->stAppCtrl),
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_SndReadUsimmFileReq
 功能描述  : MTA发送读卡请求
 输入参数  : USIMM_CARDAPP_ENUM_UINT32           ulEventType
             USIMM_DEF_FILEID_ENUM_UINT32        enFileId
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月18日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MTA_SndReadUsimmFileReq(
    USIMM_CARDAPP_ENUM_UINT32           enCardApp,
    VOS_UINT16                          enFileId
)
{
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      enCardApp,
                                      enFileId,
                                      0);

    (VOS_VOID)NAS_USIMMAPI_GetFileReq(UEPS_PID_MTA, 0, &stGetFileInfo);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvRcvUsimGetFileRsp
 功能描述  : 收到读取UIM_ID的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年10月19日
    作    者   : z00316370
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRcvUsimGetFileRsp(
    VOS_VOID                           *pMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstUsimmReadCnfMsg;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    MTA_AT_MEID_QRY_CNF_STRU            stMeifQryCnf;

    PS_MEM_SET(&stMeifQryCnf, 0x0, sizeof(stMeifQryCnf));

    /* 判断定时器是否运行 */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UIMID_READ_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRcvUsimGetFileRsp: WARNING: Timer was already stop!");
        return;
    }

    /* 停止保护定时器 */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_UIMID_READ_CNF);

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UIMID_READ_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRcvUsimGetFileRsp: get command buffer failed!");
        return;
    }

    pstUsimmReadCnfMsg = (USIMM_READFILE_CNF_STRU*)pMsg;

    TAF_MTA_RcvUsimmReadUimidFileCnf(pstUsimmReadCnfMsg, stMeifQryCnf.aucEFRUIMID);

    /* 长度为0，表示UIMID无效 */
    if (0 == stMeifQryCnf.aucEFRUIMID[0])
    {
        stMeifQryCnf.enResult = MTA_AT_RESULT_ERROR;
    }
    else
    {
        stMeifQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MEID_QRY_CNF,
                     sizeof(stMeifQryCnf),
                     (VOS_UINT8*)&stMeifQryCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_UIMID_READ_CNF);

    return;

}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvUsimmReadUimidFileCnf
 功能描述  : 解析UIM_ID的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年10月19日
    作    者   : z00316370
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID  TAF_MTA_RcvUsimmReadUimidFileCnf(
    USIMM_READFILE_CNF_STRU            *pstUsimmReadCnfMsg,
    VOS_UINT8                          *paucEFRUIMID
)
{
    VOS_UINT32                          enEfId;

    PS_MEM_SET(paucEFRUIMID, 0xff, sizeof(VOS_UINT8) * MTA_AT_EFRUIMID_OCTET_LEN_EIGHT);

    if (VOS_OK != USIMM_ChangePathToDefFileID(pstUsimmReadCnfMsg->stCmdResult.enApptype,
                                              pstUsimmReadCnfMsg->stFilePath.ulPathLen,
                                              pstUsimmReadCnfMsg->stFilePath.acPath,
                                              &enEfId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvUsimmReadUimidFileCnf: Read UIMID FAIL");

        /* the first byte EFRUIMID indicates the byte num of UIMID value,if read fail,
            set the UIMID length to 0, namely invalid UIMID */
        paucEFRUIMID[0] = 0;

        return;
    }

    /* Read file fail */
    if (VOS_OK != pstUsimmReadCnfMsg->stCmdResult.ulResult)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvUsimmReadUimidFileCnf: Read UIMID FAIL");

        /* the first byte EFRUIMID indicates the byte num of UIMID value,if read fail,
            set the UIMID length to 0, namely invalid UIMID */
        paucEFRUIMID[0] = 0;

        return;
    }

    /* the EFRUIMID may have 5 or 8 bytes */
    if ((MTA_AT_EFRUIMID_OCTET_LEN_EIGHT != pstUsimmReadCnfMsg->usEfLen)
     && (MTA_AT_EFRUIMID_OCTET_LEN_FIVE  != pstUsimmReadCnfMsg->usEfLen))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvUsimmReadUimidFileCnf: Read UIMID length FAIL");

        /* the first byte EFRUIMID indicates the byte num of UIMID value,if read length fail,
            set the UIMID length to 0, namely invalid UIMID */
        paucEFRUIMID[0] = 0;

        return;
    }

    PS_MEM_CPY(paucEFRUIMID,
               pstUsimmReadCnfMsg->aucEf,
               pstUsimmReadCnfMsg->usEfLen);

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MTA_RcvTiWaitUIMIDReadExpired
 功能描述  : 读取UIM_ID超时的处理函数
 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
  1.日    期   : 2015年10月19日
    作    者   : z00316370
    修改内容   : 新增函数

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitUIMIDReadExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_MEID_QRY_CNF_STRU            stMeifQryCnf;

    /* 获取当前定时器对应的消息队列 */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UIMID_READ_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*定时器超时log*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitUIMIDReadExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMeifQryCnf, 0x0, sizeof(stMeifQryCnf));

    stMeifQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* 上报给AT模块错误信息 */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MEID_QRY_CNF,
                     sizeof(stMeifQryCnf),
                     (VOS_UINT8*)&stMeifQryCnf );


    /* 从等待队列中删除消息 */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

