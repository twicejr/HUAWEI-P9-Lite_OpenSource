
#include "product_config.h"

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

#include "vos_Id.h"
#include "usimmbase.h"
#include "usimmapdu.h"
#include "usimmglobal.h"
#include "usimminit.h"
#include "usimmvsimauth.h"
#include "softcrypto.h"
#include "NasNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_USIMM_VSIM_C
/*lint +e767*/

#if (FEATURE_VSIM == FEATURE_ON)

USIMM_VSIM_FILE_INFO_STRU g_astUSIMMVSimFileInfo[] =
{
    {"EFIMSI",      0x6F07, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFAD",        0x6FAD, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFACC",       0x6F78, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFBCCH",      0x6F74, USIMM_SIM_MANDATORY_FILE,   USIMM_VSIM_WRITE_AVALIBALE},
    {"EFFPLMN",     0x6F7B, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_AVALIBALE},
    {"EFPSLOCI",    0x6F73, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_AVALIBALE},
    {"EFLOCI",      0x6F7E, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_AVALIBALE},
    {"EFEST",       0x6F56, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFUST",       0x6F38, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFHPPLMN",    0x6F31, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFNETPAR",    0x6FC4, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_AVALIBALE},
    {"EFTHRESHOLD", 0x6F5C, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFSTARTHFN",  0x6F5B, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_AVALIBALE},
    {"EFEHPLMN",    0x6FD9, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFPLMNWACT",  0x6F60, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_AVALIBALE},
    {"EFSMSP",      0x6F42, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_AVALIBALE},
    {"EFSMSS",      0x6F43, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_AVALIBALE},
    {"EFLOCIGPRS",  0x6F53, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_AVALIBALE},
    {"EFICCID",     0x2FE2, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_UNAVALIBALE}
};

USIMM_VSIM_AUTH_INFO_STRU g_stUSIMMVSimAuthInfo;

VOS_CHAR *g_pcUSIMMVSimXmlFilePath = VSIM_XML_FILE_PATH;



FILE *USIMM_File_Open(VOS_CHAR *pcFileName, VOS_CHAR *pcAccessMode)
{
    FILE *fp;

    fp = mdrv_file_open(pcFileName,pcAccessMode);

    if ( VOS_NULL_PTR == fp )
    {
        USIMM_WARNING_LOG("Open File fail!");
    }

    return fp;
}


VOS_INT32 USIMM_File_Close(FILE *Fp)
{
    VOS_INT32 lRslt = VOS_ERR;

    lRslt = mdrv_file_close(Fp);

    if ( VOS_OK != lRslt )
    {
        USIMM_WARNING_LOG("Close File fail!");
    }

    return lRslt;
}


VOS_INT32 USIMM_File_Write(VOS_VOID *pBuf,VOS_UINT32 ulSize,VOS_UINT32 ulCount,FILE *Fp)
{
    VOS_INT32                             lRslt;

    lRslt = mdrv_file_write_sync(pBuf,ulSize,ulCount,Fp);

    if ( lRslt != (VOS_INT32)ulCount )
    {
        USIMM_WARNING_LOG("Write File fail!");
    }

    return lRslt;

}


VOS_INT32 USIMM_File_Seek( FILE *Fp,VOS_INT32 lOffset,VOS_INT32 lWhence)
{
    VOS_INT32 ulRslt = VOS_ERR;

    ulRslt = mdrv_file_seek(Fp,lOffset,lWhence);

    if ( VOS_OK != ulRslt )
    {
        USIMM_WARNING_LOG("Seek File fail!");
    }

    return ulRslt;
}


VOS_INT32 USIMM_File_Tell(FILE *Fp)
{
    VOS_INT32 lFileSize = VOS_ERROR;

    lFileSize = mdrv_file_tell(Fp);

    if ( VOS_ERROR == lFileSize)
    {
        USIMM_WARNING_LOG("Tell File Size fail!");
    }

    return lFileSize;
}


VOS_INT32 USIMM_File_Read(VOS_VOID *pBuf,VOS_UINT32 ulSize,VOS_UINT32 ulCount,FILE *Fp)
{
    VOS_INT                             lRslt;

    lRslt = mdrv_file_read(pBuf,ulSize,ulCount,Fp);

    if ( (VOS_UINT32)lRslt != ulCount )
    {
        USIMM_WARNING_LOG("Read File fail!");
    }

    return lRslt;
}


VOS_INT32 USIMM_File_Rename(VOS_CHAR *pcOldFileName,VOS_CHAR *pcNewFileName)
{
    VOS_INT32 ulRslt;

    ulRslt = mdrv_file_rename(pcOldFileName,pcNewFileName);

    if(VOS_OK != ulRslt)
    {
        USIMM_WARNING_LOG("Rename file fail!");
    }

    return ulRslt;
}


VOS_INT32 USIMM_OpenDir(VOS_CHAR *pcDirName)
{
    DRV_DIR_S           *pstTmpDir;

    pstTmpDir = mdrv_file_opendir(pcDirName);

    if(VOS_NULL_PTR == pstTmpDir)
    {
        USIMM_WARNING_LOG("Make Dir fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_INT32 USIMM_Mkdir(VOS_CHAR *pcDirName)
{
    VOS_INT32 ulRslt;

    ulRslt = mdrv_file_mkdir(pcDirName);

    if(VOS_OK != ulRslt)
    {
        USIMM_WARNING_LOG("Make Dir fail!");
    }

    return ulRslt;
}


VOS_VOID USIMM_InitVsimGlobal(VOS_VOID)
{
    USIMM_COMM_PIN_INFO_STRU           *pstCommPinInfo;
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info;

    USIMM_CCB_GetFilePoolTotalGlobal()->enPoolStatus = USIMM_POOL_AVAILABLE;   /*设置当前的POOL的状态*/

    USIMM_CCB_SetAppChNO(0, USIMM_GUTL_APP);

    USIMM_CCB_SetAppService(USIMM_GUTL_APP, USIMM_CARD_SERVIC_AVAILABLE);

    USIMM_CCB_SetMainAppType(USIMM_GUTL_APP);

    USIMM_CCB_SetAIDByApp(USIMM_GUTL_APP, VOS_StrLen(USIMM_GSM_STR), (VOS_UINT8 *)USIMM_GSM_STR);

    /* 初始化当前的PIN基本内容 */
    pstCommPinInfo = USIMM_CCB_GetPINInfo(USIMM_GUTL_APP);

    pstCommPinInfo->enCurPINType  = USIMM_PIN2;

    /* 初始化PIN信息 */
    pstCommPinInfo->enPinKeyRef   = USIMM_KEY_REF_PIN_01;

    pstPin1Info = USIMM_CCB_GetPIN1InfoByRef(USIMM_KEY_REF_PIN_01);

    pstPin1Info->ucPINRefNum     = USIMM_KEY_REF_PIN_01;

    /* 初始化默认次数 */
    pstPin1Info->ucPinRemainTime = 3;

    pstCommPinInfo->stPin2Info.ucPinRemainTime = 3;

    pstPin1Info->ucPukRemainTime = 10;

    pstCommPinInfo->stPin2Info.ucPukRemainTime = 10;

    return;
}


VOS_UINT32 USIMM_VsimGetRealKiOpc(VOS_UINT8 *pucKi, VOS_UINT8 *pucOpc)
{
    VOS_UINT8                           aucKey[VSIM_DH_AGREE_KEY] = {0};
    VOS_UINT8                           aucKi[USIMM_VSIM_SECUR_MAX_LEN] = {0};
    VOS_UINT8                           aucOpc[USIMM_VSIM_SECUR_MAX_LEN] = {0};
    NVIM_VSIM_HVSDH_NV_STRU             stNVDHKey;
    DH_KEY                              stDHPara;
    VSIM_KEYDATA_STRU                   stCPrivateKey;   /* 单板私钥 */

    /*lint -e534*/
    VOS_MemSet(&stDHPara, 0, sizeof(stDHPara));
    (VOS_VOID)VOS_MemSet(&stCPrivateKey, 0, sizeof(VSIM_KEYDATA_STRU));
    /*lint +e534*/

    if(VOS_NULL == g_stUSIMMVSimAuthInfo.ucKILen)
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: Ki Len is 0");
        return VOS_ERR;
    }

    if(NV_OK != NV_Read(en_NV_Item_VSIM_HVSDH_INFO, &stNVDHKey, sizeof(NVIM_VSIM_HVSDH_NV_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: NV Read Key is Failed");

        return VOS_ERR;
    }

    if(VSIM_ALGORITHM_NULL == stNVDHKey.enAlgorithm)
    {
        USIMM_WARNING_LOG("USIMM_VsimGetRealKiOpc: Algorithm is OFF");

        /*lint -e534*/
        VOS_MemCpy(pucKi, g_stUSIMMVSimAuthInfo.aucKi, USIMM_AUTH_KI_LEN);

        VOS_MemCpy(pucOpc, g_stUSIMMVSimAuthInfo.aucOpc, USIMM_AUTH_OPC_LEN);
        /*lint +e534*/

        return VOS_OK;
    }

    if(VOS_OK != USIMM_VsimHUKDecode(stNVDHKey.stCPrivateKey.aucKey,
                                        VSIM_DH_PRIVATE_KEY,
                                        stCPrivateKey.aucKey,
                                        &stCPrivateKey.ulKeyLen))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: USIMM_VsimHUKDecode is Failed");/* [false alarm]:fortify */

        return VOS_ERR;
    }

    (VOS_VOID)VOS_MemCpy(stDHPara.privateValue, stCPrivateKey.aucKey, VSIM_DH_PRIVATE_KEY);

    stDHPara.priVallen = VSIM_DH_PRIVATE_KEY;

    DH_FillFixParams(&stDHPara);

    if(VOS_OK != DH_ComputeAgreedKey(aucKey, stNVDHKey.stSPublicKey.aucKey, &stDHPara))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: DH_ComputeAgreedKey is Failed");
        return VOS_ERR;
    }

    if(VOS_FALSE == AESDecrypt(g_stUSIMMVSimAuthInfo.aucKi, g_stUSIMMVSimAuthInfo.ucKILen, aucKey, sizeof(aucKey), aucKi, sizeof(aucKi)))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: AESDecrypt Ki is Failed");
        return VOS_ERR;
    }

    /*lint -e534*/
    (VOS_VOID)VOS_MemCpy(pucKi, aucKi, USIMM_AUTH_KI_LEN);
    /*lint +e534*/

    if(VOS_NULL == g_stUSIMMVSimAuthInfo.ucOpcLen)
    {
        USIMM_NORMAL_LOG("USIMM_VsimGetRealKiOpc: Only get Ki Data");
        return VOS_OK;
    }

    if(VOS_FALSE == AESDecrypt(g_stUSIMMVSimAuthInfo.aucOpc, g_stUSIMMVSimAuthInfo.ucOpcLen, aucKey, sizeof(aucKey), aucOpc, sizeof(aucOpc)))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: AESDecrypt Opc is Failed");
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(pucOpc, aucOpc, USIMM_AUTH_OPC_LEN);
    /*lint +e534*/

    USIMM_NORMAL_LOG("USIMM_VsimGetRealKiOpc: Get Ki and Opc Data");

    return VOS_OK;
}


VOS_UINT32 USIMM_SetVsimFile(USIMM_UPDATEFILE_REQ_STRU *pstUpdateMsg, VOS_UINT16 usEFID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;
    USIMM_SETCNF_INFO_STRU              stCnfInfo;
    USIMM_POOL_ONERECORD_ST             stRecord;

    stCnfInfo.ucRecordNum  = pstUpdateMsg->ucRecordNum;
    stCnfInfo.usEFLen      = 1;
    stCnfInfo.usEfid       = usEFID;

    /*lint -e534*/
    VOS_MemSet(&stRecord, 0 , sizeof(USIMM_POOL_ONERECORD_ST));
    /*lint +e534*/

    if (USIMM_GUTL_APP != pstUpdateMsg->stMsgHeader.enAppType)
    {
        USIMM_SetFileCnf(pstUpdateMsg,
                         USIMM_SW_MSGCHECK_ERROR,
                         &stCnfInfo);

        return VOS_OK;
    }

    for (i=0; i<ARRAYSIZE(g_astUSIMMVSimFileInfo); i++)
    {
        if (usEFID == g_astUSIMMVSimFileInfo[i].usFileID)
        {
            break;
        }
    }

    if (i >= ARRAYSIZE(g_astUSIMMVSimFileInfo))  /*没有找到*/
    {
        USIMM_SetFileCnf(pstUpdateMsg,
                         VOS_OK,
                         &stCnfInfo);/*回复更新结果,默认按照成功回复*/

        return VOS_OK;
    }

    if(USIMM_VSIM_WRITE_AVALIBALE != g_astUSIMMVSimFileInfo[i].enFileAC)
    {
        USIMM_SetFileCnf(pstUpdateMsg,
                         USIMM_SW_SECURITY_ERROR,
                         &stCnfInfo);/*回复更新结果,默认按照失败回复*/

        return VOS_OK;
    }

    /* 如果文件存在在缓冲中则需要更新 */
    ulResult = USIMM_PoolUpdateOneFile(pstUpdateMsg->stMsgHeader.enAppType,
                                       usEFID,
                                       pstUpdateMsg->usDataLen,
                                       pstUpdateMsg->aucContent);

    if(VOS_OK != ulResult)/*如果文件存在在缓冲中则需要更新*/
    {
        USIMM_ERROR_LOG("USIMM_SetVsimFile:USIMM_PoolInsertOneFile error");
    }

    USIMM_SetFileCnf(pstUpdateMsg, VOS_OK, &stCnfInfo);/*回复更新结果,默认按照成功回复*/

    return VOS_OK;
}


VOS_UINT32 USIMM_GetVsimFile(USIMM_READFILE_REQ_STRU *pstReadMsg, VOS_UINT16 usEFID)
{
    VOS_UINT32                          ulFileNum = 0;
    USIMM_GETCNF_INFO_STRU              stCnfInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    stCnfInfo.ucRecordNum      = pstReadMsg->ucRecordNum;
    stCnfInfo.usEfId           = usEFID;

    if (USIMM_GUTL_APP != pstReadMsg->stMsgHeader.enAppType)
    {
        USIMM_WARNING_LOG("USIMM_GetVsimFile: The AppType is not USIMM_GUTL_APP");

        USIMM_GetFileCnf(pstReadMsg, USIMM_SW_MSGCHECK_ERROR, &stCnfInfo);

        return VOS_ERR;
    }

    if(VOS_OK == USIMM_PoolFindFile(usEFID, &ulFileNum, USIMM_GUTL_APP))
    {
        stCnfInfo.usDataLen    = USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen;
        stCnfInfo.usEfLen      = USIMM_CCB_GetPoolFileByIndex(ulFileNum)->usLen;
        stCnfInfo.pucEf        = USIMM_CCB_GetPoolFileByIndex(ulFileNum)->pucContent;
        stCnfInfo.ucTotalNum   = 1;

        USIMM_INFO_LOG("USIMM_GetVSimFile: Get File Success from Usimm Pool");

        USIMM_GetFileCnf(pstReadMsg, USIMM_SW_OK, &stCnfInfo);
    }
    else
    {
        stCnfInfo.usDataLen    = VOS_NULL;
        stCnfInfo.usEfLen      = VOS_NULL;
        stCnfInfo.pucEf        = VOS_NULL_PTR;

        USIMM_INFO_LOG("USIMM_GetVSimFile: Get File Failed from Usimm Pool");

        USIMM_GetFileCnf(pstReadMsg, USIMM_SW_NOFILE_FOUND, &stCnfInfo);
    }

    return VOS_OK;
}


VOS_VOID USIMM_VsimConfidentialDataVerifyErrHandle(VOS_VOID)
{
    NVIM_VSIM_HVSDH_NV_STRU             stDhNv;
    VSIM_ALGORITHM_TYPE_ENUM_UINT32     enAlgorithm;

    USIMM_ResetGlobalVarWithCard();

    stDhNv.enAlgorithm = VSIM_ALGORITHM_NULL;

    /* 清除公私钥 */
    if (NV_OK != NV_Read(en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv)))
    {
        USIMM_WARNING_LOG("USIMM_VsimConfidentialDataVerify: Get HVSDT Info failed.");
    }

    enAlgorithm = stDhNv.enAlgorithm;

    /*lint -e534*/
    VOS_MemSet(&stDhNv, 0, sizeof(NVIM_VSIM_HVSDH_NV_STRU));
    /*lint +e534*/

    stDhNv.enAlgorithm = enAlgorithm;

    if (NV_OK != NV_Write(en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv)))
    {
        USIMM_WARNING_LOG("USIMM_VsimConfidentialDataVerify: Clean HVSDT Info failed.");
    }

    USIMM_VsimReDhNegotiateInd();

    return;
}


VOS_UINT32 USIMM_VsimBase16Decode(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_UINT8 *pucDst, VOS_UINT32 *pulDstLen)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j = 0;
    VOS_UINT32                          ulLen = 0;
    VOS_CHAR                            acTemp[2];

    for (i = 0; i < ulSrcLen; i++)
    {
        if ((pcSrc[i] >= '0') && (pcSrc[i] <= '9'))            /*转换数字字符*/
        {
            acTemp[j] = pcSrc[i] - '0';

            j++;
        }
        else if((pcSrc[i] >= 'a')&&(pcSrc[i+j] <= 'f'))     /*转换小写字符*/
        {
            acTemp[j] = (pcSrc[i] - 'a') + 10;              /*字符相减后加上差值恢复*/

            j++;
        }
        else if((pcSrc[i] >= 'A')&&(pcSrc[i] <= 'F'))       /*转换大写字符*/
        {
            acTemp[j] = (pcSrc[i] - 'A') + 10;

            j++;
        }
        else                                                /*不能转换和跳过的字符*/
        {
            continue;
        }

        if (2 == j)                                         /*已经凑够两个字符*/
        {
            pucDst[ulLen] = (VOS_UINT8)(((VOS_UINT8)acTemp[0]<<4)+acTemp[1]);

            ulLen++;

            j = 0;
        }
    }

    if (1 == j)                                              /*转换的字符串为奇数*/
    {
        return VOS_ERR;
    }

    *pulDstLen = ulLen;

    return VOS_OK;

}


VOS_VOID USIMM_VsimBase16Encode(VOS_UINT8 *pucSrc, VOS_UINT8 *pucDst, VOS_UINT32 ulLen)
{
    VOS_UINT8   aucNibble[2];
    VOS_UINT32  i;
    VOS_UINT32  j;

    for (i = 0; i < ulLen; i++)
    {
        aucNibble[0] = (pucSrc[i] & 0xF0) >> 4;
        aucNibble[1] = pucSrc[i] & 0x0F;
        for (j = 0; j < 2; j++)
        {
            if (aucNibble[j] < 10)
            {
                aucNibble[j] += 0x30;
            }
            else
            {
                if (aucNibble[j] < 16)
                {
                    aucNibble[j] = aucNibble[j] - 10 + 'A';
                }
            }

            *pucDst++ = aucNibble[j];
        }
    }

    return;
}


VOS_UINT32 USIMM_VsimHUKDecode(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          *pulDstLen)
{
    VOS_UINT8           auckey[USIMM_HUK_LEN];
    VOS_INT32           lDstLen;

    if (MDRV_OK != mdrv_efuse_read_huk(auckey, sizeof(auckey)))
    {
        USIMM_ERROR_LOG("USIMM_VsimHUKDecode: efuseReadHUK Failed");

        return VOS_ERR;
    }

    lDstLen = AESDecryptS(pucSrc, (VOS_INT)ulSrcLen, auckey, USIMM_HUK_BITS, pucDst, VSIM_DH_AGREE_KEY);

    if (VOS_NULL == lDstLen)
    {
        USIMM_ERROR_LOG("USIMM_VsimHUKDecode: AESEncrypt Fail");

        return VOS_ERR;
    }

    *pulDstLen = (VOS_UINT32)lDstLen;

    return VOS_OK;
}


VOS_UINT32 USIMM_VsimConfidentialDataVerify(VOS_VOID)
{
    VOS_UINT32                          ulImsiLen;
    VOS_UINT32                          ulSimkeyLen;
    VOS_INT32                           lResult;
    VOS_UINT32                          ulRecordNum;
    VOS_INT                             lDataLen;
    VOS_INT                             lHashLen;
    VOS_UINT8                          *pucImsi;
    VOS_UINT8                           aucData[USIMM_EF_IMSI_LEN * 2 + USIMM_VSIM_SECUR_MAX_LEN * 4];
    VOS_UINT8                           aucHashData[USIMM_VSIM_HASH_LEN];
    VOS_UINT8                           aucKey[VSIM_DH_AGREE_KEY] = {0};
    VOS_UINT8                           aucCipher[USIMM_VSIM_SIM_KEY_HASH_LEN/2];
    VOS_UINT8                           aucSimkey[USIMM_VSIM_SIM_KEY_HASH_LEN/2];
    NVIM_VSIM_HVSDH_NV_STRU             stNVDHKey;
    DH_KEY                              stDHPara;
    VSIM_KEYDATA_STRU                   stCPrivateKey;   /* 单板私钥 */

    /*lint -e534*/
    VOS_MemSet(&stDHPara, 0, sizeof(stDHPara));
    (VOS_VOID)VOS_MemSet(&stCPrivateKey, 0, sizeof(VSIM_KEYDATA_STRU));
    /*lint +e534*/

    /* 查询文件位置，这里不能直接调用USIMM_GetCachedFile，服务状态的全局变量未设置 */
    if (VOS_ERR == USIMM_PoolFindFile(EFIMSI, &ulRecordNum, USIMM_GUTL_APP))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: File Could not Found");

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent)
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: File Content is Empty");

        return VOS_ERR;
    }

    ulImsiLen = USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->usLen;

    pucImsi   = USIMM_CCB_GetPoolFileByIndex(ulRecordNum)->pucContent;

    USIMM_VsimBase16Encode(pucImsi, aucData, ulImsiLen);

    /*lint -e534*/
    VOS_MemCpy(aucData + ulImsiLen * 2,
               g_stUSIMMVSimAuthInfo.stBase16Ki.aucData,
               g_stUSIMMVSimAuthInfo.stBase16Ki.ulLen);

    VOS_MemCpy(aucData + ulImsiLen * 2 + g_stUSIMMVSimAuthInfo.stBase16Ki.ulLen,
               g_stUSIMMVSimAuthInfo.stBase16Opc.aucData,
               g_stUSIMMVSimAuthInfo.stBase16Opc.ulLen);
    /*lint +e534*/

    lDataLen = (VOS_INT)(ulImsiLen * 2 + g_stUSIMMVSimAuthInfo.stBase16Ki.ulLen + g_stUSIMMVSimAuthInfo.stBase16Opc.ulLen);

    /* 用IMSI+KI+OPC的长度和内容数据计算HASH */
    lHashLen = USIMM_VSIM_HASH_LEN;

    lResult  = mdrv_crypto_hash((VOS_CHAR *)aucData,
                           lDataLen,
                           CRYPTO_ALGORITHM_SHA256,
                           (VOS_CHAR *)aucHashData,
                           &lHashLen);

    if ((VOS_OK != lResult)
      ||(USIMM_VSIM_HASH_LEN != lHashLen))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: mdrv_crypto_hash Failed");

        return VOS_ERR;
    }

    if (NV_OK != NV_Read(en_NV_Item_VSIM_HVSDH_INFO, &stNVDHKey, sizeof(NVIM_VSIM_HVSDH_NV_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: NV Read Key is Failed");

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_VsimHUKDecode(stNVDHKey.stCPrivateKey.aucKey,
                                        VSIM_DH_PRIVATE_KEY,
                                        stCPrivateKey.aucKey,
                                        &stCPrivateKey.ulKeyLen))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: USIMM_VsimHUKDecode is Failed");/* [false alarm]:fortify */

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(stDHPara.privateValue, stCPrivateKey.aucKey, VSIM_DH_PRIVATE_KEY);
    /*lint +e534*/

    stDHPara.priVallen = VSIM_DH_PRIVATE_KEY;

    DH_FillFixParams(&stDHPara);

    if (VOS_OK != DH_ComputeAgreedKey(aucKey, stNVDHKey.stSPublicKey.aucKey, &stDHPara))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: DH_ComputeAgreedKey is Failed");

        return VOS_ERR;
    }

    (VOS_VOID)AESEncrypt(aucHashData, lHashLen, aucKey, sizeof(aucKey), aucCipher, USIMM_VSIM_SIM_KEY_HASH_LEN/2);

    if (VOS_OK != USIMM_VsimBase16Decode((VOS_CHAR *)g_stUSIMMVSimAuthInfo.aucSimKeyHash, USIMM_VSIM_SIM_KEY_HASH_LEN, aucSimkey, &ulSimkeyLen))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: USIMM_VsimBase16Decode Failed");

        return VOS_ERR;
    }

#ifndef OAM_DMT
    if (VOS_OK == VOS_MemCmp(aucSimkey, aucCipher, USIMM_VSIM_SIM_KEY_HASH_LEN/2))
    {
        return VOS_OK;
    }

    return VOS_ERR;
#else
    return VOS_OK;
#endif  /*OAM_DMT*/
}

VOS_UINT32 USIMM_VirtualUsimAuthenticationProc(USIMM_AUTHENTICATION_REQ_STRU *pstMsg)
{
    VOS_UINT8                           ucResult;
    VOS_UINT8                           aucxRes[USIMM_AUTH_XRES_LEN+1]  = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucIK[USIMM_AUTH_IK_LEN+1]      = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucCK[USIMM_AUTH_CK_LEN+1]      = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucGsmKC[USIMM_AUTH_KC_LEN+1]   = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucKi[USIMM_AUTH_KI_LEN]        = {0};
    VOS_UINT8                           aucOpc[USIMM_AUTH_OPC_LEN]      = {0};
    USIMM_TELECOM_AUTH_INFO_STRU        stCnfInfo;
    USIMM_U8_DATA_STRU                  stData;
    VOS_UINT8                           ucOffset;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    VOS_MemSet(&stData, 0, sizeof(USIMM_U8_DATA_STRU));
    /*lint +e534*/

    if (VOS_OK != USIMM_AuthenticationDataFillDataProc(pstMsg, &stData))
    {
        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* 解密全局变量中的Ki Opc */
    if(VOS_OK != USIMM_VsimGetRealKiOpc(aucKi, aucOpc))
    {
        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(Rand, &stData.aucData[1], stData.aucData[0]);
    /*lint +e534*/

    ucOffset = stData.aucData[0] + 1;

    /*lint -e534*/
    VOS_MemCpy(Autn, &stData.aucData[ucOffset + 1], stData.aucData[ucOffset]);
    /*lint +e534*/

    if (USIMM_3G_AUTH == pstMsg->enAuthType)
    {
        ucResult = Milenage(aucKi, aucOpc, &aucxRes[1], &aucCK[1], &aucIK[1], &aucGsmKC[1]);

        if(AUTH_OK != ucResult) /*Mac错误的时候才返回失败*/
        {
            stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

            USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

            return VOS_ERR;
        }
        else
        {
            /*返回的数据长度是固定的 */
            aucxRes[0]  = USIMM_AUTH_XRES_LEN;
            aucIK[0]    = USIMM_AUTH_IK_LEN;
            aucCK[0]    = USIMM_AUTH_CK_LEN;
            aucGsmKC[0] = USIMM_AUTH_KC_LEN;

            stCnfInfo.pucAuthRes    = aucxRes;
            stCnfInfo.pucIK         = aucIK;
            stCnfInfo.pucCK         = aucCK;
            stCnfInfo.pucGsmKC      = aucGsmKC;
            stCnfInfo.pucAuts       = VOS_NULL_PTR;

            stCnfInfo.enResult      = USIMM_AUTH_UMTS_SUCCESS;

            USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

            return VOS_OK;
        }
    }
    else
    {
        Milenage2G(aucKi, aucOpc, &aucxRes[1], &aucGsmKC[1]);

        aucxRes[0]  = USIMM_AUTH_RES_LEN;
        aucGsmKC[0] = USIMM_AUTH_KC_LEN;

        stCnfInfo.pucAuthRes        = aucxRes;
        stCnfInfo.pucIK             = VOS_NULL_PTR;
        stCnfInfo.pucCK             = VOS_NULL_PTR;
        stCnfInfo.pucGsmKC          = aucGsmKC;
        stCnfInfo.pucAuts           = VOS_NULL_PTR;

        stCnfInfo.enResult          = USIMM_AUTH_GSM_SUCCESS;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_OK;
    }
}


VOS_UINT32 USIMM_VirtualSimAuthenticationProc(USIMM_AUTHENTICATION_REQ_STRU *pstMsg)
{
    VOS_UINT8                           aucOutPut[USIMM_AUTH_RES_LEN+USIMM_AUTH_KC_LEN] = {0};    /*RES+KC*/
    VOS_UINT8                           aucxRes[USIMM_AUTH_RES_LEN+1]                   = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucGsmKC[USIMM_AUTH_KC_LEN+1]                   = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucKi[USIMM_AUTH_KI_LEN];
    VOS_UINT8                           aucOpc[USIMM_AUTH_OPC_LEN];                               /*不使用，但是需要避免XML里面有*/
    USIMM_TELECOM_AUTH_INFO_STRU        stCnfInfo;
    USIMM_U8_DATA_STRU                  stData;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    VOS_MemSet(&stData, 0, sizeof(USIMM_U8_DATA_STRU));
    /*lint +e534*/

    if (VOS_OK != USIMM_AuthenticationDataFillDataProc(pstMsg, &stData))
    {
        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /* 解密全局变量中的Ki Opc */
    if (VOS_OK != USIMM_VsimGetRealKiOpc(aucKi, aucOpc))
    {
        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if (USIMM_VSIM_COMPV1 == g_stUSIMMVSimAuthInfo.enAuthType)        /*comp 128 v1*/
    {
        RUNA3A8_V1(aucKi, &stData.aucData[1], aucOutPut);
    }
    else if (USIMM_VSIM_COMPV2 == g_stUSIMMVSimAuthInfo.enAuthType)   /*comp 128 v2*/
    {
        RUNA3A8_V2(aucKi, &stData.aucData[1], aucOutPut);
    }
    else        /*comp 128 v3*/
    {
        RUNA3A8_V3(aucKi, &stData.aucData[1], aucOutPut);
    }

    aucxRes[0]  = USIMM_AUTH_RES_LEN;

    /*lint -e534*/
    VOS_MemCpy(&aucxRes[1], aucOutPut, USIMM_AUTH_RES_LEN);
    /*lint +e534*/

    aucGsmKC[0] = USIMM_AUTH_KC_LEN;

    /*lint -e534*/
    VOS_MemCpy(&aucGsmKC[1], &aucOutPut[USIMM_AUTH_RES_LEN], USIMM_AUTH_KC_LEN);
    /*lint +e534*/

    stCnfInfo.pucAuthRes        = aucxRes;
    stCnfInfo.pucIK             = VOS_NULL_PTR;
    stCnfInfo.pucCK             = VOS_NULL_PTR;
    stCnfInfo.pucGsmKC          = aucGsmKC;
    stCnfInfo.pucAuts           = VOS_NULL_PTR;

    stCnfInfo.enResult          = USIMM_AUTH_GSM_SUCCESS;

    USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

    return VOS_OK;
}


VOS_UINT32 USIMM_VirtualAuthenticationProc(USIMM_AUTHENTICATION_REQ_STRU *pstMsg)
{
    VOS_UINT32                          ulRslt;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;

    /* 虚拟卡必须是GUTL类型的APP */
    if (USIMM_GUTL_APP != pstMsg->stMsgHeader.enAppType)
    {
        return VOS_ERR;
    }

    enCardType = USIMM_CCB_GetCardType();

    if (USIMM_PHYCARD_TYPE_UICC == enCardType)
    {
        ulRslt = USIMM_VirtualUsimAuthenticationProc(pstMsg);
    }
    else if (USIMM_PHYCARD_TYPE_ICC == enCardType)
    {
        ulRslt = USIMM_VirtualSimAuthenticationProc(pstMsg);
    }
    else
    {
        ulRslt = VOS_ERR;
    }

    return ulRslt;
}


VOS_UINT32 USIMM_DeactiveVsim(USIMM_MsgBlock *pMsg)
{
    USIMM_NORMAL_LOG("USIMM_DeactiveVSim: Deactive Card");

    USIMM_ResetGlobalVarWithCard();

    return VOS_OK;
}


VOS_UINT32 USIMM_VsimPoolSearchFile(VOS_UINT16 usFileId, VOS_UINT32 *pulData)
{
    VOS_UINT32                          i;
    USIMM_POOL_ST                      *pstPoolGlobal;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    pstPoolGlobal       =  USIMM_CCB_GetFilePoolTotalGlobal();
    if (USIMM_POOL_NOINTIAL == pstPoolGlobal->enPoolStatus)
    {
        return VOS_ERR;
    }

    if (VOS_NULL == pstPoolGlobal->ucPoolFileCount)  /*当前内容为空*/
    {
        if (VOS_NULL == usFileId)       /*查询空位置*/
        {
            *pulData = 0;

            return VOS_OK;
        }

        return VOS_ERR;
    }

    for (i = 0; i < USIMM_POOL_MAX_NUM; i++)
    {
        enAppType = USIMM_CCB_GetPoolFileByIndex(i)->enAppType;

        if ((USIMM_CCB_GetPoolFileByIndex(i)->usEFId == usFileId) /*找到该文件*/
            && (USIMM_GUTL_APP == enAppType))                     /*返回文件所在单元号*/
        {
            *pulData = i;

            return VOS_OK;
        }
    }

    return VOS_ERR;
}



VOS_UINT32 USIMM_CheckVsimFileInPool(VOS_VOID)
{
    VOS_UINT32      i;
    VOS_UINT32      ulIndex;
    VOS_UINT32      ulResult;

    ulResult = VOS_OK;

    for(i=0; i<ARRAYSIZE(g_astUSIMMVSimFileInfo); i++)
    {
        /*lint -e960*/
        if (USIMM_VSIM_IS_FILE_ATTR_VALID(i))
        /*lint +e960*/
        {
            ulResult = USIMM_VsimPoolSearchFile(g_astUSIMMVSimFileInfo[i].usFileID, &ulIndex);
        }

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_CheckVSIMFileInPoll: the File is not in POOL!");

            return ulResult;
        }
    }

    if((USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType()) /*USIM卡必须具备KI,OPC, 鉴权类型目前仅支持标准方式*/
        &&((VOS_NULL == g_stUSIMMVSimAuthInfo.ucKILen)||(VOS_NULL == g_stUSIMMVSimAuthInfo.ucOpcLen))
        &&(USIMM_VSIM_MILENAGE != g_stUSIMMVSimAuthInfo.enAuthType))
    {
        USIMM_ERROR_LOG("USIMM_CheckVSIMFileInPoll: USIM Auth Para is Error!");

        return VOS_ERR;
    }

    if((USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())/*SIM卡必须具备KI，鉴权类型为标准*/
        &&(VOS_NULL == g_stUSIMMVSimAuthInfo.ucKILen)
        &&((USIMM_VSIM_AUTH_NULL == g_stUSIMMVSimAuthInfo.enAuthType)||(USIMM_VSIM_MILENAGE == g_stUSIMMVSimAuthInfo.enAuthType)))
    {
        USIMM_ERROR_LOG("USIMM_CheckVSIMFileInPoll: SIM Auth Para is Error!");

        return VOS_ERR;
    }

    return VOS_OK;
}




VOS_UINT32 USIMM_AddVsimFileToPool(VOS_CHAR *pucFileStr, VOS_UINT32 ulStrLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFileIndex;
    VOS_UINT8                          *pucContent;
    VOS_UINT32                          ulContentLen;
    USIMM_POOL_ONERECORD_ST             stRecord;

    /*lint -e534*/
    VOS_MemSet(&stRecord, 0 , sizeof(USIMM_POOL_ONERECORD_ST));
    /*lint +e534*/

    if((VOS_NULL_PTR == pcValue)||(VOS_NULL == ulValueLen))
    {
        USIMM_WARNING_LOG("USIMM_AddVSIMFileToPool: Para is NULL!");

        return VOS_OK;      /*跳过节点插入后续文件*/
    }

    for(i=0; i<ARRAYSIZE(g_astUSIMMVSimFileInfo); i++)
    {
        /*lint -e534*/
        if(VOS_OK == VOS_MemCmp(g_astUSIMMVSimFileInfo[i].pcVSIMName, pucFileStr, ulStrLen))
        {
            break;
        /*lint +e534*/
        }
    }

    if(i >= ARRAYSIZE(g_astUSIMMVSimFileInfo))
    {
        USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: the File Name is not support!");

        return VOS_OK;
    }

    pucContent = (VOS_UINT8*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulValueLen);

    if(VOS_NULL_PTR == pucContent)
    {
        USIMM_ERROR_LOG("USIMM_AddVSIMFileToPoll: VOS_MemAlloc is NULL!");

        return VOS_ERR;
    }

    /*过滤特殊字符*/
    if(VOS_OK != OAM_XML_GetIntArray(pcValue, ulValueLen, pucContent, &ulContentLen))
    {
        USIMM_ERROR_LOG("USIMM_AddVSIMFileToPoll: OAM_XML_GetIntArray is Failed!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucContent);
        /*lint +e534*/

        return VOS_OK;  /*如果错误，继续解析后面的内容，最后由必选文件检查决定卡状态*/
    }

    if(VOS_OK == USIMM_VsimPoolSearchFile(g_astUSIMMVSimFileInfo[i].usFileID, &ulFileIndex))
    {
        USIMM_ERROR_LOG("USIMM_AddVSIMFileToPoll: File is Already Exist!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucContent);
        /*lint +e534*/

        return VOS_OK;  /*重复插入就保持之前的值不变*/
    }

    stRecord.usEFId     = g_astUSIMMVSimFileInfo[i].usFileID;
    stRecord.usLen      = (VOS_UINT16)ulContentLen;
    stRecord.enAppType  = USIMM_GUTL_APP;
    stRecord.enFileType = USIMM_EFSTRUCTURE_TRANSPARENT;
    stRecord.pucContent = pucContent;

    /*插入失败认为是POOL已经满了*/
    if(VOS_OK != USIMM_PoolInsertOneFile(&stRecord))
    {
        USIMM_ERROR_LOG("USIMM_AddVSIMFileToPoll: USIMM_PoolInsertOneFile Error"); /*如果错误，继续解析后面的内容，最后由必选文件检查决定卡状态*/
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucContent);
    /*lint +e534*/

    return VOS_OK;
}


VOS_UINT32 USIMM_AddVsimAuthPara(VOS_CHAR *pucFileStr, VOS_UINT32 ulFileLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen)
{
    VOS_UINT32      ulContentLen;
    VOS_CHAR        *pcContent;
    VOS_UINT8       aucAuthPara[USIMM_VSIM_SIM_KEY_HASH_LEN];
    VOS_UINT32      ulAuthParaLen = 0;
    VOS_UINT32      ulResult;

    if((VOS_NULL_PTR == pcValue)||(VOS_NULL == ulValueLen))
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: Para is NULL!");
        return VOS_ERR;
    }

    pcContent = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulValueLen);

    if(VOS_NULL_PTR == pcContent)
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: VOS_MemAlloc is NULL!");
        return VOS_ERR;
    }

    /*过滤特殊字符*/
    OAM_XML_FilterStrInvalidChar(pcValue, ulValueLen, pcContent, &ulContentLen);

    if(VOS_NULL == ulContentLen)
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: OAM_XML_GetStrContent return 0!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    if((USIMM_VSIM_SECUR_MAX_LEN*2) < ulContentLen) /*检查Base16编码长度，不能超过当前全局变量的最大值*/
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: Base16Decode Result is too long!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    ulResult = OAM_XML_GetIntArray(pcContent, ulContentLen, aucAuthPara, &ulAuthParaLen);

    if((VOS_ERR == ulResult) || (0 == ulAuthParaLen) || (USIMM_VSIM_SECUR_MAX_LEN < ulAuthParaLen))  /*检查转换后的结果*/
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: Base16Decode is Failed!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    /* 保存转换后的内容，转换前的内容也要保存下来 */
    /*lint -e534*/
    if (VOS_OK == VOS_MemCmp(USIMM_VSIM_KI_STR, pucFileStr, ulFileLen))
    {
        g_stUSIMMVSimAuthInfo.ucKILen = (VOS_UINT8)ulAuthParaLen;
    /*lint +e534*/

        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.aucKi, aucAuthPara, ulAuthParaLen);
        /*lint +e534*/

        g_stUSIMMVSimAuthInfo.stBase16Ki.ulLen = ulContentLen;

        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.stBase16Ki.aucData, pcContent, ulContentLen);
    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_OPC_STR, pucFileStr, ulFileLen))
    {
        g_stUSIMMVSimAuthInfo.ucOpcLen = (VOS_UINT8)ulAuthParaLen;
    /*lint +e534*/

        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.aucOpc, aucAuthPara, ulAuthParaLen);
        /*lint +e534*/

        g_stUSIMMVSimAuthInfo.stBase16Opc.ulLen = ulContentLen;

        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.stBase16Opc.aucData, pcContent, ulContentLen);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.aucSimKeyHash, aucAuthPara, USIMM_VSIM_SIM_KEY_HASH_LEN);
        /*lint +e534*/
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pcContent);
    /*lint +e534*/

    return VOS_OK;
}


VOS_UINT32 USIMM_AddVsimVerifyHashPara(VOS_CHAR *pucFileStr, VOS_UINT32 ulFileLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen)
{
    VOS_UINT32      ulContentLen;
    VOS_CHAR        *pcContent;

    if((VOS_NULL_PTR == pcValue)||(VOS_NULL == ulValueLen))
    {
        USIMM_ERROR_LOG("USIMM_AddVsimVerifyHashPara: Para is NULL!");
        return VOS_ERR;
    }

    pcContent = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulValueLen);

    if(VOS_NULL_PTR == pcContent)
    {
        USIMM_ERROR_LOG("USIMM_AddVsimVerifyHashPara: VOS_MemAlloc is NULL!");
        return VOS_ERR;
    }

    /*过滤特殊字符*/
    OAM_XML_FilterStrInvalidChar(pcValue, ulValueLen, pcContent, &ulContentLen);

    if(VOS_NULL == ulContentLen)
    {
        USIMM_ERROR_LOG("USIMM_AddVsimVerifyHashPara: OAM_XML_GetStrContent return 0!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    if(USIMM_VSIM_SIM_KEY_HASH_LEN < ulContentLen) /*检查Base16编码长度，不能超过当前全局变量的最大值*/
    {
        USIMM_ERROR_LOG("USIMM_AddVsimVerifyHashPara: Base16Decode Result is too long!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(g_stUSIMMVSimAuthInfo.aucSimKeyHash, pcContent, ulContentLen);
    /*lint +e534 -e534*/

    VOS_MemFree(WUEPS_PID_USIM, pcContent);
    /*lint +e534*/

    return VOS_OK;
}




VOS_UINT32 USIMM_DecodeVsimEf(OAM_XML_NODE_STRU *pstXmlNode)
{
    VOS_CHAR                    *pcTemp;
    VOS_UINT32                  ulStrLen;
    VOS_UINT32                  ulResult;
    OAM_XML_NODE_STRU           *pstTmpNode;
    OAM_XML_NODE_ATTRIBUTE_STRU *pstAttr;

    if(USIMM_POOL_MAX_NUM < OAM_XML_GetChildCount(pstXmlNode))  /*文件个数超过缓冲池，目前仅告警*/
    {
        USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: The EF Num is more than Pool Space!");
    }

    pstTmpNode = pstXmlNode->pstFirstChild;

    if(VOS_NULL_PTR == pstTmpNode)  /*当前无子节点，文件解析失败*/
    {
        USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: The EF Num is NULL!");

        return VOS_ERR;
    }

    while (VOS_NULL_PTR != pstTmpNode)
    {
        if(VOS_NULL_PTR == pstTmpNode->pstFirstAttrib)                 /*需要依赖节点属性和节点值解析文件*/
        {
            USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: The EF Name is NULL!");

            pstTmpNode = pstTmpNode->pstNexBrother; /*指向下一个节点*/

            continue;     /*空节点继续解析*/
        }

        pstAttr = OAM_XML_SearchAttNodeByName(pstTmpNode->pstFirstAttrib, USIMM_VSIM_NAME_STR);

        if(VOS_NULL_PTR == pstAttr)
        {
            USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: The XML item NAME Attr is NULL!");

            pstTmpNode = pstTmpNode->pstNexBrother; /*指向下一个节点*/

            continue;     /*空节点继续解析*/
        }

        /*申请文件名称的内存*/
        pcTemp = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstAttr->ulValueLength);

        if(VOS_NULL_PTR == pcTemp)
        {
            USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: VOS_MemAlloc is NULL!");

            return VOS_ERR;
        }

        /*过滤文件名称中特殊字符*/
        OAM_XML_GetStrContent(pstAttr->pcAttribValue, pstAttr->ulValueLength, pcTemp, &ulStrLen);

        /*判断当前文件名称*/
/*lint -e960 -e418*/
        if((VOS_OK == VOS_MemCmp(USIMM_VSIM_KI_STR, pcTemp, ulStrLen))
            ||(VOS_OK == VOS_MemCmp(USIMM_VSIM_OPC_STR, pcTemp, ulStrLen)))
/*lint +e960 +e418*/
        {
            ulResult = USIMM_AddVsimAuthPara(pcTemp, ulStrLen, pstTmpNode->pcNodeValue, pstTmpNode->ulValueLength);
        }
        /*lint -e534*/
        else if (VOS_OK == VOS_MemCmp(USIMM_VSIM_VERIFY_HASH_STR, pcTemp, ulStrLen))
        {
            ulResult = USIMM_AddVsimVerifyHashPara(pcTemp, ulStrLen, pstTmpNode->pcNodeValue, pstTmpNode->ulValueLength);
        /*lint +e534*/
        }
        else
        {
            ulResult = USIMM_AddVsimFileToPool(pcTemp, ulStrLen, pstTmpNode->pcNodeValue, pstTmpNode->ulValueLength);
        }

        /*lint -e534*/
        (VOS_VOID)VOS_MemFree(WUEPS_PID_USIM, pcTemp);    /*释放文件名称的内存*/
        /*lint +e534*/

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: Decode XML File Node is Failed!");
        }

        pstTmpNode = pstTmpNode->pstNexBrother; /*指向下一个节点*/
    }

    return VOS_OK;
}


VOS_VOID USIMM_VsimDecodeCardType(
    VOS_CHAR                       *pucStr,
    VOS_UINT32                      ulStrLen,
    USIMM_PHYCARD_TYPE_ENUM_UINT32 *pulCardType
)
{
    VOS_CHAR                    *pcTemp;
    VOS_UINT32                  ulDataLen;

    *pulCardType = USIMM_PHYCARD_TYPE_NOCARD;   /*默认返回无卡*/

    if(VOS_NULL == ulStrLen)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: Card Type is NULL!");

        return;
    }

    /*申请用于存放卡类型的内存*/
    pcTemp = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulStrLen);

    if(VOS_NULL_PTR == pcTemp)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: VOS_MemAlloc is NULL!");

        return;
    }

    /*过滤特殊字符*/
    OAM_XML_GetStrContent(pucStr, ulStrLen, pcTemp, &ulDataLen);

    if(VOS_NULL == ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: Card Type Content is NULL!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcTemp);
        /*lint +e534*/

        return;
    }

	/*lint -e418 -e534*/
    if(VOS_OK == VOS_MemCmp(USIMM_VSIM_USIM_STR, pcTemp, ulDataLen))
    {
        *pulCardType = USIMM_PHYCARD_TYPE_UICC;

    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_SIM_STR, pcTemp, ulDataLen))
    /*lint +e418 +e534*/
    {
        *pulCardType = USIMM_PHYCARD_TYPE_ICC;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: Card Type is not support!");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pcTemp);    /*释放用于存放卡类型的内存*/
    /*lint +e534*/

    return;
}


VOS_VOID USIMM_VsimDecodeAuthType(VOS_CHAR                  *pucStr,
                                            VOS_UINT32                  ulStrLen,
                                            USIMM_VSIM_AUTH_ENUM_UINT32*pulAuthType)
{
    VOS_CHAR                    *pcTemp;
    VOS_UINT32                  ulDataLen;

    *pulAuthType = USIMM_VSIM_AUTH_NULL;

    if(VOS_NULL == ulStrLen)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeAuthType: Auth Type is NULL!");

        return;
    }

    pcTemp = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulStrLen);

    if(VOS_NULL_PTR == pcTemp)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeAuthType: VOS_MemAlloc is NULL!");

        return;
    }

    OAM_XML_GetStrContent(pucStr, ulStrLen, pcTemp, &ulDataLen);

    if(VOS_NULL == ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeAuthType: Auth Type Content is NULL!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcTemp);
        /*lint +e534*/

        return;
    }

/*lint -e418 -e534*/
    if(VOS_OK == VOS_MemCmp(USIMM_VSIM_AUTH_3G_STR, pcTemp, ulDataLen))
    {
        *pulAuthType = USIMM_VSIM_MILENAGE;
    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_AUTH_2GV1_STR, pcTemp, ulDataLen))
    {
        *pulAuthType = USIMM_VSIM_COMPV1;
    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_AUTH_2GV2_STR, pcTemp, ulDataLen))
    {
        *pulAuthType = USIMM_VSIM_COMPV2;
    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_AUTH_2GV3_STR, pcTemp, ulDataLen))
/*lint +e418 +e534*/
    {
        *pulAuthType = USIMM_VSIM_COMPV3;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeAuthType: Auth Type is not support!");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pcTemp);
    /*lint +e534*/

    return;
}



VOS_UINT32 USIMM_DecodeVsimRoot(OAM_XML_NODE_STRU             *pstXmlNode,
                                        USIMM_PHYCARD_TYPE_ENUM_UINT32   *pulCardType,
                                        USIMM_VSIM_AUTH_ENUM_UINT8       *pucAuthType)
{
    OAM_XML_NODE_ATTRIBUTE_STRU        *pstAttr;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      ulCardType = USIMM_PHYCARD_TYPE_NOCARD;
    USIMM_VSIM_AUTH_ENUM_UINT32         ulAuthType = USIMM_VSIM_AUTH_NULL;

    if(VOS_NULL_PTR == pstXmlNode->pstFirstAttrib)  /*必须依赖属性节点解析卡类型等内容*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeVsimRoot: Xml Root FirstAttrib is NULL!");

        return VOS_ERR;
    }

    pstAttr = OAM_XML_SearchAttNodeByName(pstXmlNode->pstFirstAttrib, USIMM_VSIM_TYPE_STR);

    if(VOS_NULL_PTR == pstAttr)
    {
        USIMM_ERROR_LOG("USIMM_DecodeVsimRoot: Search TYPE is NULL!");

        return VOS_ERR;
    }

    USIMM_VsimDecodeCardType(pstAttr->pcAttribValue, pstAttr->ulValueLength, &ulCardType);

    pstAttr = OAM_XML_SearchAttNodeByName(pstXmlNode->pstFirstAttrib, USIMM_VSIM_AUTH_STR);

    if(VOS_NULL_PTR == pstAttr)
    {
        USIMM_ERROR_LOG("USIMM_DecodeVsimRoot: Search ALGORITHM is NULL!");

        return VOS_ERR;
    }

    USIMM_VsimDecodeAuthType(pstAttr->pcAttribValue, pstAttr->ulValueLength, &ulAuthType);

    /*节点信息不具备或者错误*/
    if((USIMM_PHYCARD_TYPE_NOCARD == ulCardType)||(USIMM_VSIM_AUTH_NULL == ulAuthType))
    {
        USIMM_ERROR_LOG("USIMM_DecodeVsimRoot: Card Type or Auth Type is NULL!");

        return VOS_ERR;
    }

    if(VOS_NULL_PTR != pulCardType)
    {
        *pulCardType = ulCardType;
    }

    if(VOS_NULL_PTR != pucAuthType)
    {
        *pucAuthType = (VOS_UINT8)ulAuthType;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_DecodeVsimFile(VOS_UINT8 *pucData)
{
    OAM_XML_CTX_STRU                    stXmlCtx;
    OAM_XML_NODE_STRU                  *pstXmlNode;
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType;

    /*解析xml文件*/
    /*lint -e534*/
    VOS_MemSet(&stXmlCtx, 0x00, sizeof(stXmlCtx));
    /*lint +e534*/

    /* 调用XML码流解析函数,构造XML结构树 */
    if (OAM_XML_RESULT_SUCCEED != OAM_XML_InitXMLCtx(&stXmlCtx))
    {
        USIMM_ERROR_LOG("USIMM_DecodeVSIMFile: Xml initialization failed!");

        return VOS_ERR;
    }

    pstXmlNode = OAM_XML_BuildXMLTree( (VOS_CHAR*)pucData, &stXmlCtx);

    if (VOS_NULL_PTR == pstXmlNode)
    {
        USIMM_ERROR_LOG("USIMM_DecodeVSIMFile: Build xml tree failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_ERR;
    }

    /*解析文件根节点*/
    if(VOS_OK != USIMM_DecodeVsimRoot(pstXmlNode, &enCardType, &g_stUSIMMVSimAuthInfo.enAuthType))
    {
        USIMM_ERROR_LOG("USIMM_DecodeVSIMFile: USIMM_DecodeVsimRoot failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_ERR;
    }

    USIMM_CCB_SetCardType(enCardType);

    USIMM_CCB_SetCardVersion(enCardType);

    /*内容插入POOL*/
    if(VOS_OK != USIMM_DecodeVsimEf(pstXmlNode))
    {
        USIMM_ERROR_LOG("USIMM_DecodeVSIMFile: USIMM_AddVSIMFileToPoll failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_ERR;
    }

    (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

    return VOS_OK;
}


VOS_UINT8* USIMM_ReadVsimFile(VOS_UINT32 ulReadPID)
{
    FILE                                *pXmlFile;
    VOS_UINT8                           *pucXMLData;
    VOS_INT32                           lLength;
    VOS_UINT32                          ulResult;

    pXmlFile = USIMM_File_Open(g_pcUSIMMVSimXmlFilePath, USIMM_FILE_OPEN_MODE_R);

    if(VOS_NULL_PTR == pXmlFile)
    {
        USIMM_ERROR_LOG("USIMM_ReadVsimFile: Open vsim.xml Failed");

        return VOS_NULL_PTR;
    }

    /*获取vSIM卡文件大小*/
    (VOS_VOID)USIMM_File_Seek(pXmlFile, 0, USIMM_FILE_SEEK_END);

    lLength = USIMM_File_Tell(pXmlFile);

    if(lLength <= 0)
    {
        USIMM_ERROR_LOG("USIMM_ReadVsimFile: vsim.xml is empty");

        (VOS_VOID)USIMM_File_Close(pXmlFile);

        return VOS_NULL_PTR;
    }

    (VOS_VOID)USIMM_File_Seek(pXmlFile, 0, USIMM_FILE_SEEK_SET);

    /*申请内存,多申请一个字符作为结束标记*/
    pucXMLData = (VOS_UINT8 *)VOS_MemAlloc(ulReadPID, DYNAMIC_MEM_PT, (VOS_UINT32)(lLength+1));

    if(VOS_NULL_PTR == pucXMLData)
    {
        USIMM_ERROR_LOG("USIMM_ReadVsimFile: VOS_MemAlloc Failed");

        (VOS_VOID)USIMM_File_Close(pXmlFile);

        return VOS_NULL_PTR;
    }

    ulResult = (VOS_UINT32)USIMM_File_Read(pucXMLData, (VOS_UINT32)lLength, VSIM_FILE_READ_COUNT, pXmlFile);

    (VOS_VOID)USIMM_File_Close(pXmlFile);

    if(VSIM_FILE_READ_COUNT != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ReadVsimFile: NV_File_Read Failed");

        /*lint -e534*/
        (VOS_VOID)VOS_MemFree(ulReadPID, pucXMLData);
        /*lint +e534*/

        return VOS_NULL_PTR;
    }

    pucXMLData[lLength] = '\0';    /*设置结束符*/

    return pucXMLData;
}


VOS_UINT32 USIMM_InitVsimCard(USIMM_MsgBlock *pMsg)
{
    VOS_UINT8                           *pucXMLData;
    VOS_UINT32                          ulResult;

    USIMM_ResetGlobalVar();

    /*lint -e534*/
    VOS_MemSet(&g_stUSIMMVSimAuthInfo, 0, sizeof(g_stUSIMMVSimAuthInfo));
    /*lint +e534*/

    USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

    USIMM_CCB_SetCardVersion(USIMM_PHYCARD_TYPE_NOCARD);

    if (VOS_TRUE == USIMM_CheckSupportAP())
    {
        pucXMLData = g_pucUSIMMVsimData;
    }
    else
    {
        pucXMLData = USIMM_ReadVsimFile(WUEPS_PID_USIM);
    }

    if(VOS_NULL_PTR == pucXMLData)
    {
        USIMM_ERROR_LOG("USIMM_InitVSIMCard: USIMM_ReadVsimFile Failed");

        return VOS_ERR;
    }

    ulResult = USIMM_DecodeVsimFile(pucXMLData);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucXMLData);
    /*lint +e534*/

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_InitVSIMCard: USIMM_DecodeVSIMFile Failed");

        USIMM_ResetGlobalVar();

        return VOS_ERR;
    }

    /* 对IMSI+KI+OPC进行校验，如校验不过上报无卡并要求DH重协商 */
    if (VOS_OK != USIMM_VsimConfidentialDataVerify())
    {
        USIMM_ERROR_LOG("USIMM_InitVSIMCard: USIMM_VsimConfidentialDataVerify Failed");

        USIMM_VsimConfidentialDataVerifyErrHandle();

        return VOS_ERR;
    }

    /*检查必选文件是否都在*/
    if (VOS_OK != USIMM_CheckVsimFileInPool())
    {
        USIMM_ERROR_LOG("USIMM_InitVSIMCard: USIMM_CheckVSIMFileInPoll Failed");

        USIMM_ResetGlobalVar();

        return VOS_ERR;
    }

    USIMM_InitVsimGlobal();

    return VOS_OK;
}

#endif  /* (FEATURE_VSIM == FEATURE_ON)*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#else

#include "vos_Id.h"
#include "usimmbase.h"
#include "usimmapdu.h"
#include "usimmdl.h"
#include "usimmvsimauth.h"
#include "softcrypto.h"
#include "NasNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_USIMM_VSIM_C
/*lint +e767*/

#if (FEATURE_VSIM == FEATURE_ON)

USIMM_VSIM_FILE_INFO_STRU g_astUSIMMVSimFileInfo[] =
{
    {"EFIMSI",      0x6F07, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFAD",        0x6FAD, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFACC",       0x6F78, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFBCCH",      0x6F74, USIMM_SIM_MANDATORY_FILE,   USIMM_VSIM_WRITE_AVALIBALE},
    {"EFFPLMN",     0x6F7B, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_AVALIBALE},
    {"EFPSLOCI",    0x6F73, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_AVALIBALE},
    {"EFLOCI",      0x6F7E, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_AVALIBALE},
    {"EFEST",       0x6F56, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFUST",       0x6F38, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFHPPLMN",    0x6F31, USIMM_MANDATORY_FILE,       USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFNETPAR",    0x6FC4, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_AVALIBALE},
    {"EFTHRESHOLD", 0x6F5C, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFSTARTHFN",  0x6F5B, USIMM_USIM_MANDATORY_FILE,  USIMM_VSIM_WRITE_AVALIBALE},
    {"EFEHPLMN",    0x6FD9, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_UNAVALIBALE},
    {"EFPLMNWACT",  0x6F60, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_AVALIBALE},
    {"EFSMSP",      0x6F42, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_AVALIBALE},
    {"EFSMSS",      0x6F43, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_AVALIBALE},
    {"EFLOCIGPRS",  0x6F53, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_AVALIBALE},
    {"EFICCID",     0x2FE2, USIMM_OPTIONAL_FILE,        USIMM_VSIM_WRITE_UNAVALIBALE}
};

USIMM_VSIM_AUTH_INFO_STRU g_stUSIMMVSimAuthInfo;

VOS_CHAR *g_pcUSIMMVSimXmlFilePath = VSIM_XML_FILE_PATH;


FILE *USIMM_File_Open(VOS_CHAR *pcFileName, VOS_CHAR *pcAccessMode)
{
    FILE *fp;

    fp = mdrv_file_open(pcFileName,pcAccessMode);

    if ( VOS_NULL_PTR == fp )
    {
        USIMM_WARNING_LOG("Open File fail!");
    }

    return fp;
}


VOS_INT32 USIMM_File_Close(FILE *Fp)
{
    VOS_INT32 lRslt = VOS_ERR;

    lRslt = mdrv_file_close(Fp);

    if ( VOS_OK != lRslt )
    {
        USIMM_WARNING_LOG("Close File fail!");
    }

    return lRslt;
}


VOS_INT32 USIMM_File_Write(
    VOS_VOID                            *pBuf,
    VOS_UINT32                          ulSize,
    VOS_UINT32                          ulCount,
    FILE                                *Fp)
{
    VOS_INT32                             lRslt;

    lRslt = mdrv_file_write_sync(pBuf,ulSize,ulCount,Fp);

    if ( lRslt != (VOS_INT32)ulCount )
    {
        USIMM_WARNING_LOG("Write File fail!");
    }

    return lRslt;

}


VOS_INT32 USIMM_File_Seek( FILE *Fp,VOS_INT32 lOffset,VOS_INT32 lWhence)
{
    VOS_INT32 ulRslt = VOS_ERR;

    ulRslt = mdrv_file_seek(Fp,lOffset,lWhence);

    if ( VOS_OK != ulRslt )
    {
        USIMM_WARNING_LOG("Seek File fail!");
    }

    return ulRslt;
}


VOS_INT32 USIMM_File_Tell(FILE *Fp)
{
    VOS_INT32 lFileSize = VOS_ERROR;

    lFileSize = mdrv_file_tell(Fp);

    if ( VOS_ERROR == lFileSize)
    {
        USIMM_WARNING_LOG("Tell File Size fail!");
    }

    return lFileSize;
}


VOS_INT32 USIMM_File_Read(VOS_VOID *pBuf,VOS_UINT32 ulSize,VOS_UINT32 ulCount,FILE *Fp)
{
    VOS_INT                             lRslt;

    lRslt = mdrv_file_read(pBuf,ulSize,ulCount,Fp);

    if ( (VOS_UINT32)lRslt != ulCount )
    {
        USIMM_WARNING_LOG("Read File fail!");
    }

    return lRslt;
}


VOS_INT32 USIMM_File_Rename(VOS_CHAR *pcOldFileName,VOS_CHAR *pcNewFileName)
{
    VOS_INT32 ulRslt;

    ulRslt = mdrv_file_rename(pcOldFileName,pcNewFileName);

    if(VOS_OK != ulRslt)
    {
        USIMM_WARNING_LOG("Rename file fail!");
    }

    return ulRslt;
}


VOS_INT32 USIMM_OpenDir(VOS_CHAR *pcDirName)
{
    DRV_DIR_S           *pstTmpDir;

    pstTmpDir = mdrv_file_opendir(pcDirName);

    if(VOS_NULL_PTR == pstTmpDir)
    {
        USIMM_WARNING_LOG("Make Dir fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_INT32 USIMM_Mkdir(VOS_CHAR *pcDirName)
{
    VOS_INT32 ulRslt;

    ulRslt = mdrv_file_mkdir(pcDirName);

    if(VOS_OK != ulRslt)
    {
        USIMM_WARNING_LOG("Make Dir fail!");
    }

    return ulRslt;
}



VOS_VOID USIMM_ClearVsimGlobal(VOS_VOID)
{
    USIMM_PoolDelAll();

    USIMM_InitGlobalVarOnReset();

    /*lint -e534*/
    VOS_MemSet(&g_stUSIMMVSimAuthInfo, 0, sizeof(g_stUSIMMVSimAuthInfo));
    /*lint +e534*/

    return;
}


VOS_VOID USIMM_InitVsimGlobal(VOS_VOID)
{
    gstUSIMMPOOL.enPoolStatus = USIMM_POOL_AVAILABLE;   /*设置当前的POOL的状态*/

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardService = USIMM_CARD_SERVIC_AVAILABLE;

    /*初始化当前的PIN基本内容*/
    gstUSIMMBaseInfo.enCurPINType  = USIMM_PIN2;

    /*初始化默认次数*/
    gstUSIMMADFInfo.stPINInfo.ucPin1RemainTime = 3;

    gstUSIMMADFInfo.stPINInfo.ucPin2RemainTime = 3;

    gstUSIMMADFInfo.stPINInfo.ucPuk1RemainTime = 10;

    gstUSIMMADFInfo.stPINInfo.ucPuk2RemainTime = 10;

    return;
}


VOS_UINT32 USIMM_VsimGetRealKiOpc(VOS_UINT8 *pucKi, VOS_UINT8 *pucOpc)
{
    VOS_UINT8                           aucKey[VSIM_DH_AGREE_KEY] = {0};
    VOS_UINT8                           aucKi[USIMM_VSIM_SECUR_MAX_LEN] = {0};
    VOS_UINT8                           aucOpc[USIMM_VSIM_SECUR_MAX_LEN] = {0};
    NVIM_VSIM_HVSDH_NV_STRU             stNVDHKey;
    DH_KEY                              stDHPara;
    VSIM_KEYDATA_STRU                   stCPrivateKey;   /* 单板私钥 */

    /*lint -e534*/
    VOS_MemSet(&stDHPara, 0, sizeof(stDHPara));
    (VOS_VOID)VOS_MemSet(&stCPrivateKey, 0, sizeof(VSIM_KEYDATA_STRU));
    /*lint +e534*/

    if(VOS_NULL == g_stUSIMMVSimAuthInfo.ucKILen)
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: Ki Len is 0");
        return VOS_ERR;
    }

    if(NV_OK != NV_Read(en_NV_Item_VSIM_HVSDH_INFO, &stNVDHKey, sizeof(NVIM_VSIM_HVSDH_NV_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: NV Read Key is Failed");

        return VOS_ERR;
    }

    if(VSIM_ALGORITHM_NULL == stNVDHKey.enAlgorithm)
    {
        USIMM_WARNING_LOG("USIMM_VsimGetRealKiOpc: Algorithm is OFF");

        /*lint -e534*/
        VOS_MemCpy(pucKi, g_stUSIMMVSimAuthInfo.aucKi, USIMM_AUTH_KI_LEN);

        VOS_MemCpy(pucOpc, g_stUSIMMVSimAuthInfo.aucOpc, USIMM_AUTH_OPC_LEN);
        /*lint +e534*/

        return VOS_OK;
    }

    if(VOS_OK != USIMM_VsimHUKDecode(stNVDHKey.stCPrivateKey.aucKey,
                                        VSIM_DH_PRIVATE_KEY,
                                        stCPrivateKey.aucKey,
                                        &stCPrivateKey.ulKeyLen))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: USIMM_VsimHUKDecode is Failed");/* [false alarm]:fortify */

        return VOS_ERR;
    }

    (VOS_VOID)VOS_MemCpy(stDHPara.privateValue, stCPrivateKey.aucKey, VSIM_DH_PRIVATE_KEY);

    stDHPara.priVallen = VSIM_DH_PRIVATE_KEY;

    DH_FillFixParams(&stDHPara);

    if(VOS_OK != DH_ComputeAgreedKey(aucKey, stNVDHKey.stSPublicKey.aucKey, &stDHPara))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: DH_ComputeAgreedKey is Failed");
        return VOS_ERR;
    }

    if(VOS_FALSE == AESDecrypt(g_stUSIMMVSimAuthInfo.aucKi, g_stUSIMMVSimAuthInfo.ucKILen, aucKey, sizeof(aucKey), aucKi, sizeof(aucKi)))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: AESDecrypt Ki is Failed");
        return VOS_ERR;
    }

    /*lint -e534*/
    (VOS_VOID)VOS_MemCpy(pucKi, aucKi, USIMM_AUTH_KI_LEN);
    /*lint +e534*/

    if(VOS_NULL == g_stUSIMMVSimAuthInfo.ucOpcLen)
    {
        USIMM_NORMAL_LOG("USIMM_VsimGetRealKiOpc: Only get Ki Data");
        return VOS_OK;
    }

    if(VOS_FALSE == AESDecrypt(g_stUSIMMVSimAuthInfo.aucOpc, g_stUSIMMVSimAuthInfo.ucOpcLen, aucKey, sizeof(aucKey), aucOpc, sizeof(aucOpc)))
    {
        USIMM_ERROR_LOG("USIMM_VsimGetRealKiOpc: AESDecrypt Opc is Failed");
        return VOS_ERR;
    }

    /*lint -e534*/
    (VOS_VOID)VOS_MemCpy(pucOpc, aucOpc, USIMM_AUTH_OPC_LEN);
    /*lint +e534*/

    USIMM_NORMAL_LOG("USIMM_VsimGetRealKiOpc: Get Ki and Opc Data");

    return VOS_OK;
}


VOS_UINT32 USIMM_SetVsimFile(USIMM_SETFILE_REQ_STRU *pstMsg, USIMM_UPDATEFILE_REQ_STRU *pstNewMsg)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;
    USIMM_SETCNF_INFO_STRU              stCnfInfo;

    stCnfInfo.ucRecordNum  = pstMsg->ucRecordNum;
    stCnfInfo.usEFLen      = pstMsg->usDataLen;
    stCnfInfo.usEfid       = pstMsg->usFileID;

    for(i=0; i<ARRAYSIZE(g_astUSIMMVSimFileInfo); i++)
    {
        if(pstMsg->usFileID == g_astUSIMMVSimFileInfo[i].usFileID)
        {
            break;
        }
    }

    if(i >= ARRAYSIZE(g_astUSIMMVSimFileInfo))  /*没有找到*/
    {
        USIMM_SetFileCnf(pstNewMsg,
                         VOS_OK,
                         &stCnfInfo);/*回复更新结果,默认按照成功回复*/

        return VOS_OK;
    }

    if(USIMM_VSIM_WRITE_AVALIBALE != g_astUSIMMVSimFileInfo[i].enFileAC)
    {
        USIMM_SetFileCnf(pstNewMsg,
                         USIMM_SW_SECURITY_ERROR,
                         &stCnfInfo);/*回复更新结果,默认按照失败回复*/

        return VOS_OK;
    }

    ulResult = USIMM_PoolDelOneFile(pstMsg->usFileID, USIMM_UNLIMIT_APP);

    if(VOS_OK == ulResult)/*如果文件存在在缓冲中则需要更新*/
    {
        (VOS_VOID)USIMM_PoolInsertOneFile(pstMsg->usFileID,
                                pstMsg->usDataLen,
                                pstMsg->aucContent,
                                USIMM_UNLIMIT_APP,
                                USIMM_EFSTRUCTURE_TRANSPARENT);
    }

    USIMM_SetFileCnf(pstNewMsg,
                     VOS_OK,
                     &stCnfInfo);/*回复更新结果,默认按照成功回复*/

    return VOS_OK;
}


VOS_UINT32 USIMM_GetVsimFile(USIMM_GETFILE_REQ_STRU  *pstOldMsg, USIMM_READFILE_REQ_STRU *pstNewMsg)
{
    VOS_UINT32                  ulFileNum = 0;
    USIMM_GETCNF_INFO_STRU      stCnfInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    stCnfInfo.ucRecordNum      = pstOldMsg->ucRecordNum;
    stCnfInfo.usEfId           = pstOldMsg->usFileID;

    if(VOS_OK == USIMM_PoolFindFile(pstOldMsg->usFileID, &ulFileNum, USIMM_UNLIMIT_APP))
    {
        stCnfInfo.usDataLen    = gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen;
        stCnfInfo.usEfLen      = gstUSIMMPOOL.astpoolRecord[ulFileNum].usLen;
        stCnfInfo.pucEf        = gstUSIMMPOOL.astpoolRecord[ulFileNum].pucContent;
        stCnfInfo.ucTotalNum   = 1;

        USIMM_INFO_LOG("USIMM_GetVSimFile: Get File Success from Usimm Pool");

        USIMM_GetFileCnf(pstNewMsg, USIMM_SW_OK, &stCnfInfo);
    }
    else
    {
        stCnfInfo.usDataLen    = VOS_NULL;
        stCnfInfo.usEfLen      = VOS_NULL;
        stCnfInfo.pucEf        = VOS_NULL_PTR;

        USIMM_INFO_LOG("USIMM_GetVSimFile: Get File Failed from Usimm Pool");

        USIMM_GetFileCnf(pstNewMsg, USIMM_SW_NOFILE_FOUND, &stCnfInfo);
    }
    return VOS_OK;
}


VOS_VOID USIMM_VsimConfidentialDataVerifyErrHandle(VOS_VOID)
{
    NVIM_VSIM_HVSDH_NV_STRU             stDhNv;
    VSIM_ALGORITHM_TYPE_ENUM_UINT32     enAlgorithm;

    USIMM_ClearVsimGlobal();

    stDhNv.enAlgorithm = VSIM_ALGORITHM_NULL;

    /* 清除公私钥 */
    if (NV_OK != NV_Read(en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv)))
    {
        USIMM_WARNING_LOG("USIMM_VsimConfidentialDataVerify: Get HVSDT Info failed.");
    }

    enAlgorithm = stDhNv.enAlgorithm;

    /*lint -e534*/
    VOS_MemSet(&stDhNv, 0, sizeof(NVIM_VSIM_HVSDH_NV_STRU));
    /*lint +e534*/

    stDhNv.enAlgorithm = enAlgorithm;

    if (NV_OK != NV_Write(en_NV_Item_VSIM_HVSDH_INFO, &stDhNv, sizeof(stDhNv)))
    {
        USIMM_WARNING_LOG("USIMM_VsimConfidentialDataVerify: Clean HVSDT Info failed.");
    }

    USIMM_VsimReDhNegotiateInd();

    return;
}


VOS_UINT32 USIMM_VsimBase16Decode(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_UINT8 *pucDst, VOS_UINT32 *pulDstLen)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j = 0;
    VOS_UINT32                          ulLen = 0;
    VOS_CHAR                            acTemp[2];

    for (i = 0; i < ulSrcLen; i++)
    {
        if ((pcSrc[i] >= '0') && (pcSrc[i] <= '9'))            /*转换数字字符*/
        {
            acTemp[j] = pcSrc[i] - '0';

            j++;
        }
        else if((pcSrc[i] >= 'a')&&(pcSrc[i+j] <= 'f'))     /*转换小写字符*/
        {
            acTemp[j] = (pcSrc[i] - 'a') + 10;              /*字符相减后加上差值恢复*/

            j++;
        }
        else if((pcSrc[i] >= 'A')&&(pcSrc[i] <= 'F'))       /*转换大写字符*/
        {
            acTemp[j] = (pcSrc[i] - 'A') + 10;

            j++;
        }
        else                                                /*不能转换和跳过的字符*/
        {
            continue;
        }

        if (2 == j)                                         /*已经凑够两个字符*/
        {
            pucDst[ulLen] = (VOS_UINT8)(((VOS_UINT8)acTemp[0]<<4)+acTemp[1]);

            ulLen++;

            j = 0;
        }
    }

    if (1 == j)                                              /*转换的字符串为奇数*/
    {
        return VOS_ERR;
    }

    *pulDstLen = ulLen;

    return VOS_OK;

}


VOS_VOID USIMM_VsimBase16Encode(VOS_UINT8 *pucSrc, VOS_UINT8 *pucDst, VOS_UINT32 ulLen)
{
    VOS_UINT8   aucNibble[2];
    VOS_UINT32  i;
    VOS_UINT32  j;

    for (i = 0; i < ulLen; i++)
    {
        aucNibble[0] = (pucSrc[i] & 0xF0) >> 4;
        aucNibble[1] = pucSrc[i] & 0x0F;
        for (j = 0; j < 2; j++)
        {
            if (aucNibble[j] < 10)
            {
                aucNibble[j] += 0x30;
            }
            else
            {
                if (aucNibble[j] < 16)
                {
                    aucNibble[j] = aucNibble[j] - 10 + 'A';
                }
            }

            *pucDst++ = aucNibble[j];
        }
    }

    return;
}


VOS_UINT32 USIMM_VsimHUKDecode(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          ulSrcLen,
    VOS_UINT8                           *pucDst,
    VOS_UINT32                          *pulDstLen)
{
    VOS_UINT8           auckey[USIMM_HUK_LEN];
    VOS_INT32           lDstLen;

    if (MDRV_OK != mdrv_efuse_read_huk(auckey, sizeof(auckey)))
    {
        USIMM_ERROR_LOG("USIMM_VsimHUKDecode: efuseReadHUK Failed");

        return VOS_ERR;
    }

    lDstLen = AESDecryptS(pucSrc, (VOS_INT)ulSrcLen, auckey, USIMM_HUK_BITS, pucDst, VSIM_DH_AGREE_KEY);

    if (VOS_NULL == lDstLen)
    {
        USIMM_ERROR_LOG("USIMM_VsimHUKDecode: AESEncrypt Fail");

        return VOS_ERR;
    }

    *pulDstLen = (VOS_UINT32)lDstLen;

    return VOS_OK;
}


VOS_UINT32 USIMM_VsimConfidentialDataVerify(VOS_VOID)
{
    VOS_UINT32                          ulImsiLen;
    VOS_UINT32                          ulSimkeyLen;
    VOS_INT32                           lResult;
    VOS_UINT32                          ulRecordNum;
    VOS_INT                             lDataLen;
    VOS_INT                             lHashLen;
    VOS_UINT8                          *pucImsi;
    VOS_UINT8                           aucData[USIMM_EF_IMSI_LEN * 2 + USIMM_VSIM_SECUR_MAX_LEN * 4];
    VOS_UINT8                           aucHashData[USIMM_VSIM_HASH_LEN];
    VOS_UINT8                           aucKey[VSIM_DH_AGREE_KEY] = {0};
    VOS_UINT8                           aucCipher[USIMM_VSIM_SIM_KEY_HASH_LEN/2];
    VOS_UINT8                           aucSimkey[USIMM_VSIM_SIM_KEY_HASH_LEN/2];
    NVIM_VSIM_HVSDH_NV_STRU             stNVDHKey;
    DH_KEY                              stDHPara;
    VSIM_KEYDATA_STRU                   stCPrivateKey;   /* 单板私钥 */

    /*lint -e534*/
    VOS_MemSet(&stDHPara, 0, sizeof(stDHPara));
    (VOS_VOID)VOS_MemSet(&stCPrivateKey, 0, sizeof(VSIM_KEYDATA_STRU));
    /*lint +e534*/

    /* 查询文件位置，这里不能直接调用USIMM_GetCachedFile，服务状态的全局变量未设置 */
    if (VOS_ERR == USIMM_PoolFindFile(EFIMSI, &ulRecordNum, USIMM_UNLIMIT_APP))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: File Could not Found");

        return VOS_ERR;
    }

    if (VOS_NULL_PTR == gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent)
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: File Content is Empty");

        return VOS_ERR;
    }

    ulImsiLen = gstUSIMMPOOL.astpoolRecord[ulRecordNum].usLen;

    pucImsi   = gstUSIMMPOOL.astpoolRecord[ulRecordNum].pucContent;

    USIMM_VsimBase16Encode(pucImsi, aucData, ulImsiLen);

    /*lint -e534*/
    VOS_MemCpy(aucData + ulImsiLen * 2,
               g_stUSIMMVSimAuthInfo.stBase16Ki.aucData,
               g_stUSIMMVSimAuthInfo.stBase16Ki.ulLen);

    VOS_MemCpy(aucData + ulImsiLen * 2 + g_stUSIMMVSimAuthInfo.stBase16Ki.ulLen,
               g_stUSIMMVSimAuthInfo.stBase16Opc.aucData,
               g_stUSIMMVSimAuthInfo.stBase16Opc.ulLen);
    /*lint +e534*/

    lDataLen = (VOS_INT)(ulImsiLen * 2 + g_stUSIMMVSimAuthInfo.stBase16Ki.ulLen + g_stUSIMMVSimAuthInfo.stBase16Opc.ulLen);

    /* 用IMSI+KI+OPC的长度和内容数据计算HASH */
    lHashLen = USIMM_VSIM_HASH_LEN;

    lResult  = mdrv_crypto_hash((VOS_CHAR *)aucData,
                           lDataLen,
                           CRYPTO_ALGORITHM_SHA256,
                           (VOS_CHAR *)aucHashData,
                           &lHashLen);

    if ((VOS_OK != lResult)
      ||(USIMM_VSIM_HASH_LEN != lHashLen))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: mdrv_crypto_hash Failed");

        return VOS_ERR;
    }

    if (NV_OK != NV_Read(en_NV_Item_VSIM_HVSDH_INFO, &stNVDHKey, sizeof(NVIM_VSIM_HVSDH_NV_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: NV Read Key is Failed");

        return VOS_ERR;
    }

    if (VOS_OK != USIMM_VsimHUKDecode(stNVDHKey.stCPrivateKey.aucKey,
                                        VSIM_DH_PRIVATE_KEY,
                                        stCPrivateKey.aucKey,
                                        &stCPrivateKey.ulKeyLen))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: USIMM_VsimHUKDecode is Failed");/* [false alarm]:fortify */

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(stDHPara.privateValue, stCPrivateKey.aucKey, VSIM_DH_PRIVATE_KEY);
    /*lint +e534*/

    stDHPara.priVallen = VSIM_DH_PRIVATE_KEY;

    DH_FillFixParams(&stDHPara);

    if (VOS_OK != DH_ComputeAgreedKey(aucKey, stNVDHKey.stSPublicKey.aucKey, &stDHPara))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: DH_ComputeAgreedKey is Failed");

        return VOS_ERR;
    }

    (VOS_VOID)AESEncrypt(aucHashData, lHashLen, aucKey, sizeof(aucKey), aucCipher, USIMM_VSIM_SIM_KEY_HASH_LEN/2);

    if (VOS_OK != USIMM_VsimBase16Decode((VOS_CHAR *)g_stUSIMMVSimAuthInfo.aucSimKeyHash, USIMM_VSIM_SIM_KEY_HASH_LEN, aucSimkey, &ulSimkeyLen))
    {
        USIMM_ERROR_LOG("USIMM_VsimConfidentialDataVerify: USIMM_VsimBase16Decode Failed");

        return VOS_ERR;
    }

#ifndef OAM_DMT
    if (VOS_OK == VOS_MemCmp(aucSimkey, aucCipher, USIMM_VSIM_SIM_KEY_HASH_LEN/2))
    {
        return VOS_OK;
    }

    return VOS_ERR;
#else
    return VOS_OK;
#endif  /*OAM_DMT*/
}


VOS_UINT32 USIMM_AuthenVirtulUsim(USIMM_AUTH_REQ_STRU *pstMsg)
{
    VOS_UINT8                           ucResult;
    VOS_UINT8                           aucxRes[USIMM_AUTH_XRES_LEN+1]  = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucIK[USIMM_AUTH_IK_LEN+1]      = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucCK[USIMM_AUTH_CK_LEN+1]      = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucGsmKC[USIMM_AUTH_KC_LEN+1]   = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucKi[USIMM_AUTH_KI_LEN]        = {0};
    VOS_UINT8                           aucOpc[USIMM_AUTH_OPC_LEN]      = {0};
    USIMM_TELECOM_AUTH_INFO_STRU        stCnfInfo;
    VOS_UINT8                           ucOffset;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    /* 解密全局变量中的Ki Opc */
    if(VOS_OK != USIMM_VsimGetRealKiOpc(aucKi, aucOpc))
    {
        stCnfInfo.enResult = USIMM_AUTH_UMTS_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(Rand, &pstMsg->aucData[1], pstMsg->aucData[0]);
    /*lint +e534*/

    ucOffset = pstMsg->aucData[0] + 1;

    /*lint -e534*/
    VOS_MemCpy(Autn, &pstMsg->aucData[ucOffset + 1], pstMsg->aucData[ucOffset]);
    /*lint +e534*/

    if (USIMM_3G_AUTH == pstMsg->enAuthType)
    {
        ucResult = Milenage(aucKi, aucOpc, &aucxRes[1], &aucCK[1], &aucIK[1], &aucGsmKC[1]);

        if(AUTH_OK != ucResult) /*Mac错误的时候才返回失败*/
        {
            stCnfInfo.enResult = USIMM_AUTH_MAC_FAILURE;

            USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

            return VOS_ERR;
        }
        else
        {
            /*返回的数据长度是固定的 */
            aucxRes[0]  = USIMM_AUTH_XRES_LEN;
            aucIK[0]    = USIMM_AUTH_IK_LEN;
            aucCK[0]    = USIMM_AUTH_CK_LEN;
            aucGsmKC[0] = USIMM_AUTH_KC_LEN;

            stCnfInfo.pucAuthRes    = aucxRes;
            stCnfInfo.pucIK         = aucIK;
            stCnfInfo.pucCK         = aucCK;
            stCnfInfo.pucGsmKC      = aucGsmKC;
            stCnfInfo.pucAuts       = VOS_NULL_PTR;

            stCnfInfo.enResult      = USIMM_AUTH_UMTS_SUCCESS;

            USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

            return VOS_OK;
        }
    }
    else
    {
        Milenage2G(aucKi, aucOpc, &aucxRes[1], &aucGsmKC[1]);

        aucxRes[0]  = USIMM_AUTH_RES_LEN;
        aucGsmKC[0] = USIMM_AUTH_KC_LEN;

        stCnfInfo.pucAuthRes        = aucxRes;
        stCnfInfo.pucIK             = VOS_NULL_PTR;
        stCnfInfo.pucCK             = VOS_NULL_PTR;
        stCnfInfo.pucGsmKC          = aucGsmKC;
        stCnfInfo.pucAuts           = VOS_NULL_PTR;

        stCnfInfo.enResult          = USIMM_AUTH_GSM_SUCCESS;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_OK;
    }
}


VOS_UINT32 USIMM_AuthenVirtulSim(USIMM_AUTH_REQ_STRU *pstMsg)
{
    VOS_UINT8                           aucOutPut[USIMM_AUTH_RES_LEN+USIMM_AUTH_KC_LEN] = {0};    /*RES+KC*/
    VOS_UINT8                           aucxRes[USIMM_AUTH_RES_LEN+1]                   = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucGsmKC[USIMM_AUTH_KC_LEN+1]                   = {0};    /*长度1Byte+内容*/
    VOS_UINT8                           aucKi[USIMM_AUTH_KI_LEN]                        = {0};
    VOS_UINT8                           aucOpc[USIMM_AUTH_OPC_LEN]                      = {0};     /*不使用，但是需要避免XML里面有*/
    USIMM_TELECOM_AUTH_INFO_STRU        stCnfInfo;

    /*lint -e534*/
    VOS_MemSet(&stCnfInfo, 0, sizeof(stCnfInfo));
    /*lint +e534*/

    /* 解密全局变量中的Ki Opc */
    if(VOS_OK != USIMM_VsimGetRealKiOpc(aucKi, aucOpc))
    {
        stCnfInfo.enResult = USIMM_AUTH_GSM_OTHER_FAILURE;

        USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

        return VOS_ERR;
    }

    if(USIMM_VSIM_COMPV1 == g_stUSIMMVSimAuthInfo.enAuthType)        /*comp 128 v1*/
    {
        RUNA3A8_V1(aucKi, &pstMsg->aucData[1], aucOutPut);
    }
    else if(USIMM_VSIM_COMPV2 == g_stUSIMMVSimAuthInfo.enAuthType)   /*comp 128 v2*/
    {
        RUNA3A8_V2(aucKi, &pstMsg->aucData[1], aucOutPut);
    }
    else        /*comp 128 v3*/
    {
        RUNA3A8_V3(aucKi, &pstMsg->aucData[1], aucOutPut);
    }

    aucxRes[0]  = USIMM_AUTH_RES_LEN;

    /*lint -e534*/
    VOS_MemCpy(&aucxRes[1], aucOutPut, USIMM_AUTH_RES_LEN);
    /*lint +e534*/

    aucGsmKC[0] = USIMM_AUTH_KC_LEN;

    /*lint -e534*/
    VOS_MemCpy(&aucGsmKC[1], &aucOutPut[USIMM_AUTH_RES_LEN], USIMM_AUTH_KC_LEN);
    /*lint +e534*/

    stCnfInfo.pucAuthRes        = aucxRes;
    stCnfInfo.pucIK             = VOS_NULL_PTR;
    stCnfInfo.pucCK             = VOS_NULL_PTR;
    stCnfInfo.pucGsmKC          = aucGsmKC;
    stCnfInfo.pucAuts           = VOS_NULL_PTR;

    stCnfInfo.enResult          = USIMM_AUTH_GSM_SUCCESS;

    USIMM_TelecomAuthCnf(pstMsg, &stCnfInfo);

    return VOS_OK;
}


VOS_UINT32 USIMM_DeactiveVsim(USIMM_MsgBlock *pMsg)
{
    USIMM_NORMAL_LOG("USIMM_DeactiveVSim: Deactive Card");

    USIMM_ClearVsimGlobal();

    return VOS_OK;
}


VOS_UINT32 USIMM_VsimPoolSearchFile(VOS_UINT16 usFileId, VOS_UINT32 *pulData)
{
    VOS_UINT32 i;

    if(USIMM_POOL_NOINTIAL == gstUSIMMPOOL.enPoolStatus)
    {
        return VOS_ERR;
    }

    if(VOS_NULL == gstUSIMMPOOL.ucNowLen)  /*当前内容为空*/
    {
        if(VOS_NULL == usFileId)       /*查询空位置*/
        {
            *pulData = 0;

            return VOS_OK;
        }

        return VOS_ERR;
    }

    for(i=0; i<POOLMAXNUM; i++)
    {
        if(gstUSIMMPOOL.astpoolRecord[i].usFId == usFileId)                     /*找到该文件*/
        {
            *pulData = i;                                                       /*返回文件所在单元号*/

            return VOS_OK;
        }
    }

    return VOS_ERR;
}



VOS_UINT32 USIMM_CheckVsimFileInPool(VOS_VOID)
{
    VOS_UINT32      i;
    VOS_UINT32      ulIndex;
    VOS_UINT32      ulResult;

    ulResult = VOS_OK;

    for(i=0; i<ARRAYSIZE(g_astUSIMMVSimFileInfo); i++)
    {
        /*lint -e960*/
        if (USIMM_VSIM_IS_FILE_ATTR_VALID(i))
        /*lint +e960*/
        {
            ulResult = USIMM_VsimPoolSearchFile(g_astUSIMMVSimFileInfo[i].usFileID, &ulIndex);
        }

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_CheckVSIMFileInPoll: the File is not in POOL!");

            return ulResult;
        }
    }

    if((USIMM_CARD_USIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType) /*USIM卡必须具备KI,OPC, 鉴权类型目前仅支持标准方式*/
        &&((VOS_NULL == g_stUSIMMVSimAuthInfo.ucKILen)||(VOS_NULL == g_stUSIMMVSimAuthInfo.ucOpcLen))
        &&(USIMM_VSIM_MILENAGE != g_stUSIMMVSimAuthInfo.enAuthType))
    {
        USIMM_ERROR_LOG("USIMM_CheckVSIMFileInPoll: USIM Auth Para is Error!");

        return VOS_ERR;
    }

    if((USIMM_CARD_SIM == gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType)/*SIM卡必须具备KI，鉴权类型为标准*/
        &&(VOS_NULL == g_stUSIMMVSimAuthInfo.ucKILen)
        &&((USIMM_VSIM_AUTH_NULL == g_stUSIMMVSimAuthInfo.enAuthType)||(USIMM_VSIM_MILENAGE == g_stUSIMMVSimAuthInfo.enAuthType)))
    {
        USIMM_ERROR_LOG("USIMM_CheckVSIMFileInPoll: SIM Auth Para is Error!");

        return VOS_ERR;
    }

    return VOS_OK;
}




VOS_UINT32 USIMM_AddVsimFileToPool(VOS_CHAR *pucFileStr, VOS_UINT32 ulStrLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen)
{
    VOS_UINT32          i;
    VOS_UINT32          ulFileIndex;
    VOS_UINT8           *pucContent;
    VOS_UINT32          ulContentLen;

    if((VOS_NULL_PTR == pcValue)||(VOS_NULL == ulValueLen))
    {
        USIMM_WARNING_LOG("USIMM_AddVSIMFileToPool: Para is NULL!");

        return VOS_OK;      /*跳过节点插入后续文件*/
    }

    for(i=0; i<ARRAYSIZE(g_astUSIMMVSimFileInfo); i++)
    {
        /*lint -e534*/
        if(VOS_OK == VOS_MemCmp(g_astUSIMMVSimFileInfo[i].pcVSIMName, pucFileStr, ulStrLen))
        {
            break;
        /*lint +e534*/
        }
    }

    if(i >= ARRAYSIZE(g_astUSIMMVSimFileInfo))
    {
        USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: the File Name is not support!");

        return VOS_OK;
    }

    pucContent = (VOS_UINT8*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulValueLen);

    if(VOS_NULL_PTR == pucContent)
    {
        USIMM_ERROR_LOG("USIMM_AddVSIMFileToPoll: VOS_MemAlloc is NULL!");

        return VOS_ERR;
    }

    /*过滤特殊字符*/
    if(VOS_OK != OAM_XML_GetIntArray(pcValue, ulValueLen, pucContent, &ulContentLen))
    {
        USIMM_ERROR_LOG("USIMM_AddVSIMFileToPoll: OAM_XML_GetIntArray is Failed!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucContent);
        /*lint +e534*/

        return VOS_OK;  /*如果错误，继续解析后面的内容，最后由必选文件检查决定卡状态*/
    }

    if(VOS_OK == USIMM_VsimPoolSearchFile(g_astUSIMMVSimFileInfo[i].usFileID, &ulFileIndex))
    {
        USIMM_ERROR_LOG("USIMM_AddVSIMFileToPoll: File is Already Exist!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucContent);
        /*lint +e534*/

        return VOS_OK;  /*重复插入就保持之前的值不变*/
    }

    /*插入失败认为是POOL已经满了*/
    if(VOS_OK != USIMM_PoolInsertOneFile(g_astUSIMMVSimFileInfo[i].usFileID, (VOS_UINT16)ulContentLen, pucContent, USIMM_UNLIMIT_APP, USIMM_EFSTRUCTURE_TRANSPARENT))
    {
        USIMM_ERROR_LOG("USIMM_AddVSIMFileToPoll: USIMM_PoolInsertOneFile Error"); /*如果错误，继续解析后面的内容，最后由必选文件检查决定卡状态*/
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucContent);
    /*lint +e534*/

    return VOS_OK;
}


VOS_UINT32 USIMM_AddVsimAuthPara(VOS_CHAR *pucFileStr, VOS_UINT32 ulFileLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen)
{
    VOS_UINT32      ulContentLen;
    VOS_CHAR        *pcContent;
    VOS_UINT8       aucAuthPara[USIMM_VSIM_SIM_KEY_HASH_LEN];
    VOS_UINT32      ulAuthParaLen = 0;
    VOS_UINT32      ulResult;

    if((VOS_NULL_PTR == pcValue)||(VOS_NULL == ulValueLen))
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: Para is NULL!");
        return VOS_ERR;
    }

    pcContent = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulValueLen);

    if(VOS_NULL_PTR == pcContent)
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: VOS_MemAlloc is NULL!");
        return VOS_ERR;
    }

    /*过滤特殊字符*/
    OAM_XML_FilterStrInvalidChar(pcValue, ulValueLen, pcContent, &ulContentLen);

    if(VOS_NULL == ulContentLen)
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: OAM_XML_GetStrContent return 0!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    if((USIMM_VSIM_SECUR_MAX_LEN*2) < ulContentLen) /*检查Base16编码长度，不能超过当前全局变量的最大值*/
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: Base16Decode Result is too long!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    ulResult = OAM_XML_GetIntArray(pcContent, ulContentLen, aucAuthPara, &ulAuthParaLen);

    if((VOS_ERR == ulResult) || (0 == ulAuthParaLen) || (USIMM_VSIM_SECUR_MAX_LEN < ulAuthParaLen))  /*检查转换后的结果*/
    {
        USIMM_ERROR_LOG("USIMM_AddVsimAuthPara: Base16Decode is Failed!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    /* 保存转换后的内容，转换前的内容也要保存下来 */
    /*lint -e534*/
    if (VOS_OK == VOS_MemCmp(USIMM_VSIM_KI_STR, pucFileStr, ulFileLen))
    {
        g_stUSIMMVSimAuthInfo.ucKILen = (VOS_UINT8)ulAuthParaLen;
    /*lint +e534*/

        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.aucKi, aucAuthPara, ulAuthParaLen);
        /*lint +e534*/

        g_stUSIMMVSimAuthInfo.stBase16Ki.ulLen = ulContentLen;

        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.stBase16Ki.aucData, pcContent, ulContentLen);
    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_OPC_STR, pucFileStr, ulFileLen))
    {
        g_stUSIMMVSimAuthInfo.ucOpcLen = (VOS_UINT8)ulAuthParaLen;
    /*lint +e534*/

        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.aucOpc, aucAuthPara, ulAuthParaLen);
        /*lint +e534*/

        g_stUSIMMVSimAuthInfo.stBase16Opc.ulLen = ulContentLen;

        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.stBase16Opc.aucData, pcContent, ulContentLen);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        VOS_MemCpy(g_stUSIMMVSimAuthInfo.aucSimKeyHash, aucAuthPara, USIMM_VSIM_SIM_KEY_HASH_LEN);
        /*lint +e534*/
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pcContent);
    /*lint +e534*/

    return VOS_OK;
}


VOS_UINT32 USIMM_AddVsimVerifyHashPara(VOS_CHAR *pucFileStr, VOS_UINT32 ulFileLen, VOS_CHAR *pcValue, VOS_UINT32 ulValueLen)
{
    VOS_UINT32      ulContentLen;
    VOS_CHAR        *pcContent;

    if((VOS_NULL_PTR == pcValue)||(VOS_NULL == ulValueLen))
    {
        USIMM_ERROR_LOG("USIMM_AddVsimVerifyHashPara: Para is NULL!");
        return VOS_ERR;
    }

    pcContent = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulValueLen);

    if(VOS_NULL_PTR == pcContent)
    {
        USIMM_ERROR_LOG("USIMM_AddVsimVerifyHashPara: VOS_MemAlloc is NULL!");
        return VOS_ERR;
    }

    /*过滤特殊字符*/
    OAM_XML_FilterStrInvalidChar(pcValue, ulValueLen, pcContent, &ulContentLen);

    if(VOS_NULL == ulContentLen)
    {
        USIMM_ERROR_LOG("USIMM_AddVsimVerifyHashPara: OAM_XML_GetStrContent return 0!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    if(USIMM_VSIM_SIM_KEY_HASH_LEN < ulContentLen) /*检查Base16编码长度，不能超过当前全局变量的最大值*/
    {
        USIMM_ERROR_LOG("USIMM_AddVsimVerifyHashPara: Base16Decode Result is too long!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/

        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(g_stUSIMMVSimAuthInfo.aucSimKeyHash, pcContent, ulContentLen);
    /*lint +e534 -e534*/

    VOS_MemFree(WUEPS_PID_USIM, pcContent);
    /*lint +e534*/

    return VOS_OK;
}




VOS_UINT32 USIMM_DecodeVsimEf(OAM_XML_NODE_STRU *pstXmlNode)
{
    VOS_CHAR                    *pcTemp;
    VOS_UINT32                  ulStrLen;
    VOS_UINT32                  ulResult;
    OAM_XML_NODE_STRU           *pstTmpNode;
    OAM_XML_NODE_ATTRIBUTE_STRU *pstAttr;

    if(POOLMAXNUM < OAM_XML_GetChildCount(pstXmlNode))  /*文件个数超过缓冲池，目前仅告警*/
    {
        USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: The EF Num is more than Pool Space!");
    }

    pstTmpNode = pstXmlNode->pstFirstChild;

    if(VOS_NULL_PTR == pstTmpNode)  /*当前无子节点，文件解析失败*/
    {
        USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: The EF Num is NULL!");

        return VOS_ERR;
    }

    while (VOS_NULL_PTR != pstTmpNode)
    {
        if(VOS_NULL_PTR == pstTmpNode->pstFirstAttrib)                 /*需要依赖节点属性和节点值解析文件*/
        {
            USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: The EF Name is NULL!");

            pstTmpNode = pstTmpNode->pstNexBrother; /*指向下一个节点*/

            continue;     /*空节点继续解析*/
        }

        pstAttr = OAM_XML_SearchAttNodeByName(pstTmpNode->pstFirstAttrib, USIMM_VSIM_NAME_STR);

        if(VOS_NULL_PTR == pstAttr)
        {
            USIMM_WARNING_LOG("USIMM_AddVSIMFileToPoll: The XML item NAME Attr is NULL!");

            pstTmpNode = pstTmpNode->pstNexBrother; /*指向下一个节点*/

            continue;     /*空节点继续解析*/
        }

        /*申请文件名称的内存*/
        pcTemp = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstAttr->ulValueLength);

        if(VOS_NULL_PTR == pcTemp)
        {
            USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: VOS_MemAlloc is NULL!");

            return VOS_ERR;
        }

        /*过滤文件名称中特殊字符*/
        OAM_XML_GetStrContent(pstAttr->pcAttribValue, pstAttr->ulValueLength, pcTemp, &ulStrLen);

        /*判断当前文件名称*/
/*lint -e960 -e418*/
        if((VOS_OK == VOS_MemCmp(USIMM_VSIM_KI_STR, pcTemp, ulStrLen))
            ||(VOS_OK == VOS_MemCmp(USIMM_VSIM_OPC_STR, pcTemp, ulStrLen)))
/*lint +e960 +e418*/
        {
            ulResult = USIMM_AddVsimAuthPara(pcTemp, ulStrLen, pstTmpNode->pcNodeValue, pstTmpNode->ulValueLength);
        }
        /*lint -e534*/
        else if (VOS_OK == VOS_MemCmp(USIMM_VSIM_VERIFY_HASH_STR, pcTemp, ulStrLen))
        {
            ulResult = USIMM_AddVsimVerifyHashPara(pcTemp, ulStrLen, pstTmpNode->pcNodeValue, pstTmpNode->ulValueLength);
        /*lint +e534*/
        }
        else
        {
            ulResult = USIMM_AddVsimFileToPool(pcTemp, ulStrLen, pstTmpNode->pcNodeValue, pstTmpNode->ulValueLength);
        }

        /*lint -e534*/
        (VOS_VOID)VOS_MemFree(WUEPS_PID_USIM, pcTemp);    /*释放文件名称的内存*/
        /*lint +e534*/

        if(VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: Decode XML File Node is Failed!");
        }

        pstTmpNode = pstTmpNode->pstNexBrother; /*指向下一个节点*/
    }

    return VOS_OK;
}


VOS_VOID USIMM_VsimDecodeCardType(VOS_CHAR                  *pucStr,
                                            VOS_UINT32                  ulStrLen,
                                            USIMM_CARD_TYPE_ENUM_UINT32 *pulCardType)
{
    VOS_CHAR                    *pcTemp;
    VOS_UINT32                  ulDataLen;

    *pulCardType = USIMM_CARD_NOCARD;   /*默认返回无卡*/

    if(VOS_NULL == ulStrLen)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: Card Type is NULL!");

        return;
    }

    /*申请用于存放卡类型的内存*/
    pcTemp = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulStrLen);

    if(VOS_NULL_PTR == pcTemp)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: VOS_MemAlloc is NULL!");

        return;
    }

    /*过滤特殊字符*/
    OAM_XML_GetStrContent(pucStr, ulStrLen, pcTemp, &ulDataLen);

    if(VOS_NULL == ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: Card Type Content is NULL!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcTemp);
        /*lint +e534*/

        return;
    }

	/*lint -e418 -e534*/
    if(VOS_OK == VOS_MemCmp(USIMM_VSIM_USIM_STR, pcTemp, ulDataLen))
    {
        *pulCardType = USIMM_CARD_USIM;
    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_SIM_STR, pcTemp, ulDataLen))
    /*lint +e418 +e534*/
    {
        *pulCardType = USIMM_CARD_SIM;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeCardType: Card Type is not support!");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pcTemp);    /*释放用于存放卡类型的内存*/
    /*lint +e534*/

    return;
}


VOS_VOID USIMM_VsimDecodeAuthType(VOS_CHAR                  *pucStr,
                                            VOS_UINT32                  ulStrLen,
                                            USIMM_VSIM_AUTH_ENUM_UINT32*pulAuthType)
{
    VOS_CHAR                    *pcTemp;
    VOS_UINT32                  ulDataLen;

    *pulAuthType = USIMM_VSIM_AUTH_NULL;

    if(VOS_NULL == ulStrLen)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeAuthType: Auth Type is NULL!");

        return;
    }

    pcTemp = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, ulStrLen);

    if(VOS_NULL_PTR == pcTemp)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeAuthType: VOS_MemAlloc is NULL!");

        return;
    }

    OAM_XML_GetStrContent(pucStr, ulStrLen, pcTemp, &ulDataLen);

    if(VOS_NULL == ulDataLen)
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeAuthType: Auth Type Content is NULL!");

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcTemp);
        /*lint +e534*/

        return;
    }

/*lint -e418 -e534*/
    if(VOS_OK == VOS_MemCmp(USIMM_VSIM_AUTH_3G_STR, pcTemp, ulDataLen))
    {
        *pulAuthType = USIMM_VSIM_MILENAGE;
    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_AUTH_2GV1_STR, pcTemp, ulDataLen))
    {
        *pulAuthType = USIMM_VSIM_COMPV1;
    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_AUTH_2GV2_STR, pcTemp, ulDataLen))
    {
        *pulAuthType = USIMM_VSIM_COMPV2;
    }
    else if(VOS_OK == VOS_MemCmp(USIMM_VSIM_AUTH_2GV3_STR, pcTemp, ulDataLen))
/*lint +e418 +e534*/
    {
        *pulAuthType = USIMM_VSIM_COMPV3;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_VSIMDecodeAuthType: Auth Type is not support!");
    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pcTemp);
    /*lint +e534*/

    return;
}



VOS_UINT32 USIMM_DecodeVsimRoot(OAM_XML_NODE_STRU             *pstXmlNode,
                                        USIMM_CARD_TYPE_ENUM_UINT32     *pulCardType,
                                        USIMM_VSIM_AUTH_ENUM_UINT8      *pucAuthType)
{
    OAM_XML_NODE_ATTRIBUTE_STRU *pstAttr;
    USIMM_CARD_TYPE_ENUM_UINT32 ulCardType = USIMM_CARD_NOCARD;
    USIMM_VSIM_AUTH_ENUM_UINT32 ulAuthType = USIMM_VSIM_AUTH_NULL;

    if(VOS_NULL_PTR == pstXmlNode->pstFirstAttrib)  /*必须依赖属性节点解析卡类型等内容*/
    {
        USIMM_ERROR_LOG("USIMM_DecodeVsimRoot: Xml Root FirstAttrib is NULL!");

        return VOS_ERR;
    }

    pstAttr = OAM_XML_SearchAttNodeByName(pstXmlNode->pstFirstAttrib, USIMM_VSIM_TYPE_STR);

    if(VOS_NULL_PTR == pstAttr)
    {
        USIMM_ERROR_LOG("USIMM_DecodeVsimRoot: Search TYPE is NULL!");

        return VOS_ERR;
    }

    USIMM_VsimDecodeCardType(pstAttr->pcAttribValue, pstAttr->ulValueLength, &ulCardType);

    pstAttr = OAM_XML_SearchAttNodeByName(pstXmlNode->pstFirstAttrib, USIMM_VSIM_AUTH_STR);

    if(VOS_NULL_PTR == pstAttr)
    {
        USIMM_ERROR_LOG("USIMM_DecodeVsimRoot: Search ALGORITHM is NULL!");

        return VOS_ERR;
    }

    USIMM_VsimDecodeAuthType(pstAttr->pcAttribValue, pstAttr->ulValueLength, &ulAuthType);

    /*节点信息不具备或者错误*/
    if((USIMM_CARD_NOCARD == ulCardType)||(USIMM_VSIM_AUTH_NULL == ulAuthType))
    {
        USIMM_ERROR_LOG("USIMM_DecodeVsimRoot: Card Type or Auth Type is NULL!");

        return VOS_ERR;
    }

    if(VOS_NULL_PTR != pulCardType)
    {
        *pulCardType = ulCardType;
    }

    if(VOS_NULL_PTR != pucAuthType)
    {
        *pucAuthType = (VOS_UINT8)ulAuthType;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_DecodeVsimFile(VOS_UINT8 *pucData)
{
    OAM_XML_CTX_STRU                    stXmlCtx;
    OAM_XML_NODE_STRU                   *pstXmlNode;

    /*解析xml文件*/
    /*lint -e534*/
    VOS_MemSet(&stXmlCtx, 0x00, sizeof(stXmlCtx));
    /*lint +e534*/

    /* 调用XML码流解析函数,构造XML结构树 */
    if (OAM_XML_RESULT_SUCCEED != OAM_XML_InitXMLCtx(&stXmlCtx))
    {
        USIMM_ERROR_LOG("USIMM_DecodeVSIMFile: Xml initialization failed!");

        return VOS_ERR;
    }

    pstXmlNode = OAM_XML_BuildXMLTree( (VOS_CHAR*)pucData, &stXmlCtx);

    if (VOS_NULL_PTR == pstXmlNode)
    {
        USIMM_ERROR_LOG("USIMM_DecodeVSIMFile: Build xml tree failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_ERR;
    }

    /*解析文件根节点*/
    if(VOS_OK != USIMM_DecodeVsimRoot(pstXmlNode, &gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType, &g_stUSIMMVSimAuthInfo.enAuthType))
    {
        USIMM_ERROR_LOG("USIMM_DecodeVSIMFile: USIMM_DecodeVsimRoot failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_ERR;
    }

    /*内容插入POOL*/
    if(VOS_OK != USIMM_DecodeVsimEf(pstXmlNode))
    {
        USIMM_ERROR_LOG("USIMM_DecodeVSIMFile: USIMM_AddVSIMFileToPoll failed!");

        (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

        return VOS_ERR;
    }

    (VOS_VOID)OAM_XML_ClearXMLCtx(&stXmlCtx);

    return VOS_OK;
}


VOS_UINT8* USIMM_ReadVsimFile(VOS_UINT32 ulReadPID)
{
    FILE                                *pXmlFile;
    VOS_UINT8                           *pucXMLData;
    VOS_INT32                           lLength;
    VOS_UINT32                          ulResult;

    pXmlFile = USIMM_File_Open(g_pcUSIMMVSimXmlFilePath, USIMM_FILE_OPEN_MODE_R);

    if(VOS_NULL_PTR == pXmlFile)
    {
        USIMM_ERROR_LOG("USIMM_ReadVsimFile: Open vsim.xml Failed");

        return VOS_NULL_PTR;
    }

    /*获取vSIM卡文件大小*/
    (VOS_VOID)USIMM_File_Seek(pXmlFile, 0, USIMM_FILE_SEEK_END);

    lLength = USIMM_File_Tell(pXmlFile);

    if(lLength <= 0)
    {
        USIMM_ERROR_LOG("USIMM_ReadVsimFile: vsim.xml is empty");

        (VOS_VOID)USIMM_File_Close(pXmlFile);

        return VOS_NULL_PTR;
    }

    (VOS_VOID)USIMM_File_Seek(pXmlFile, 0, USIMM_FILE_SEEK_SET);

    /*申请内存,多申请一个字符作为结束标记*/
    pucXMLData = (VOS_UINT8 *)VOS_MemAlloc(ulReadPID, DYNAMIC_MEM_PT, (VOS_UINT32)(lLength+1));

    if(VOS_NULL_PTR == pucXMLData)
    {
        USIMM_ERROR_LOG("USIMM_ReadVsimFile: VOS_MemAlloc Failed");

        (VOS_VOID)USIMM_File_Close(pXmlFile);

        return VOS_NULL_PTR;
    }

    ulResult = (VOS_UINT32)USIMM_File_Read(pucXMLData, (VOS_UINT32)lLength, VSIM_FILE_READ_COUNT, pXmlFile);

    (VOS_VOID)USIMM_File_Close(pXmlFile);

    if(VSIM_FILE_READ_COUNT != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ReadVsimFile: NV_File_Read Failed");

        /*lint -e534*/
        (VOS_VOID)VOS_MemFree(ulReadPID, pucXMLData);
        /*lint +e534*/

        return VOS_NULL_PTR;
    }

    pucXMLData[lLength] = '\0';    /*设置结束符*/

    return pucXMLData;
}


VOS_UINT32 USIMM_InitVsimCard(USIMM_MsgBlock *pMsg)
{
    VOS_UINT8                           *pucXMLData;
    VOS_UINT32                          ulResult;

    USIMM_InitGlobalVarOnReset(); /*初始化其他全局变量内容*/

    /*lint -e534*/
    VOS_MemSet(&g_stUSIMMVSimAuthInfo, 0, sizeof(g_stUSIMMVSimAuthInfo));
    /*lint +e534*/

    gastUSIMMCardAppInfo[USIMM_UICC_USIM].enCardType     = USIMM_CARD_NOCARD;

    if (VOS_TRUE == USIMM_CheckSupportAP())
    {
        pucXMLData = g_pucUSIMMVsimData;
    }
    else
    {
        pucXMLData = USIMM_ReadVsimFile(WUEPS_PID_USIM);
    }

    if(VOS_NULL_PTR == pucXMLData)
    {
        USIMM_ERROR_LOG("USIMM_InitVSIMCard: USIMM_ReadVsimFile Failed");

        return VOS_ERR;
    }

    ulResult = USIMM_DecodeVsimFile(pucXMLData);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucXMLData);
    /*lint +e534*/

	g_pucUSIMMVsimData = VOS_NULL_PTR;

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_InitVSIMCard: USIMM_DecodeVSIMFile Failed");

        USIMM_ClearVsimGlobal();

        return VOS_ERR;
    }

    /* 对IMSI+KI+OPC进行校验，如校验不过上报无卡并要求DH重协商 */
    if (VOS_OK != USIMM_VsimConfidentialDataVerify())
    {
        USIMM_ERROR_LOG("USIMM_InitVSIMCard: USIMM_VsimConfidentialDataVerify Failed");

        USIMM_VsimConfidentialDataVerifyErrHandle();

        return VOS_ERR;
    }

    /*检查必选文件是否都在*/
    if (VOS_OK != USIMM_CheckVsimFileInPool())
    {
        USIMM_ERROR_LOG("USIMM_InitVSIMCard: USIMM_CheckVSIMFileInPoll Failed");

        USIMM_ClearVsimGlobal();

        return VOS_ERR;
    }

    USIMM_InitVsimGlobal();

    return VOS_OK;
}


#endif  /* (FEATURE_VSIM == FEATURE_ON)*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* end of #if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT) */
