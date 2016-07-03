
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"
#include "NVIM_Interface.h"
#include "MnComm.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
extern VOS_CHAR *g_pucSmsFileOnFlash;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MN_MSG_PROC_NIVM_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
   4 函数实现
*****************************************************************************/


VOS_VOID  MN_MSG_ReadCsmpParaFromUsimSupportFlgNvim( VOS_VOID )
{
    MN_MSG_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG_STRU        stGetCsmpParaFromUsimSupportFlg;
    MN_MSG_CUSTOM_CFG_INFO_STRU                           *pstMsCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                             ulLength;

    ulLength                                                        = 0;


    stGetCsmpParaFromUsimSupportFlg.ucGetCsmpParaFromUsimSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
    stGetCsmpParaFromUsimSupportFlg.ucGetScAddrIgnoreScIndication   = MN_MSG_NV_ITEM_DEACTIVE;


    pstMsCfgInfo = MN_MSG_GetCustomCfgInfo();

    /* 全局变量默认关闭 */
    pstMsCfgInfo->ucGetScAddrIgnoreScIndication = MN_MSG_NV_ITEM_DEACTIVE;

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(MN_MSG_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NVIM_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG,
                         &stGetCsmpParaFromUsimSupportFlg, ulLength))
    {
        MN_WARN_LOG("MN_MSG_ReadCsmpParaFromUsimSupportFlgNvim():WARNING: en_NV_Item_NVIM_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG Error");

        return;
    }

    if (MN_MSG_NV_ITEM_ACTIVE == stGetCsmpParaFromUsimSupportFlg.ucGetScAddrIgnoreScIndication)
    {
        pstMsCfgInfo->ucGetScAddrIgnoreScIndication = stGetCsmpParaFromUsimSupportFlg.ucGetScAddrIgnoreScIndication;
    }

    if ((MN_MSG_NV_ITEM_ACTIVE != stGetCsmpParaFromUsimSupportFlg.ucGetCsmpParaFromUsimSupportFlg)
     && (MN_MSG_NV_ITEM_DEACTIVE != stGetCsmpParaFromUsimSupportFlg.ucGetCsmpParaFromUsimSupportFlg))
    {
        pstMsCfgInfo->ucGetCsmpParaFromUsimSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_MSG_ReadCsmpParaFromUsimSupportFlgNvim():WARNING: NV parameter Error");
        return;
    }

    pstMsCfgInfo->ucGetCsmpParaFromUsimSupportFlg = stGetCsmpParaFromUsimSupportFlg.ucGetCsmpParaFromUsimSupportFlg;


    return;
}


VOS_VOID  MN_MSG_ReadSmsPpDownloadSupportFlgNvim( VOS_VOID )
{
    MN_MSG_SMS_PP_DOWNLOAD_SUPPORT_FLG_STRU        stSmsPpDownlodSupportFlg;
    MN_MSG_CUSTOM_CFG_INFO_STRU                   *pstMsCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                     ulLength;

    ulLength                                          = 0;

    stSmsPpDownlodSupportFlg.ucSmsPpDownlodSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
    stSmsPpDownlodSupportFlg.ucReserved1              = 0;
    stSmsPpDownlodSupportFlg.ucReserved2              = 0;
    stSmsPpDownlodSupportFlg.ucReserved3              = 0;


    pstMsCfgInfo = MN_MSG_GetCustomCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_SMS_PP_DOWNLOAD_SUPPORT_FLG, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_NVIM_SMS_PP_DOWNLOAD_SUPPORT_FLG,
                         &stSmsPpDownlodSupportFlg, ulLength))
    {
        MN_WARN_LOG("MN_MSG_ReadSmsPpDownloadSupportFlgNvim():WARNING: en_NV_Item_NVIM_SMS_PP_DOWNLOAD_SUPPORT_FLG Error");

        return;
    }


    if ((MN_MSG_NV_ITEM_ACTIVE != stSmsPpDownlodSupportFlg.ucSmsPpDownlodSupportFlg)
     && (MN_MSG_NV_ITEM_DEACTIVE != stSmsPpDownlodSupportFlg.ucSmsPpDownlodSupportFlg))
    {
        pstMsCfgInfo->ucSmsPpDownlodSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_MSG_ReadSmsPpDownloadSupportFlgNvim():WARNING: NV parameter Error");
        return;
    }

    pstMsCfgInfo->ucSmsPpDownlodSupportFlg = stSmsPpDownlodSupportFlg.ucSmsPpDownlodSupportFlg;

    return;
}


VOS_VOID  MN_MSG_GetFlashSmsStoragePath( VOS_VOID )
{
    #if((defined __PS_WIN32_RECUR__) || (defined DMT))
    g_pucSmsFileOnFlash = "EfSmsOnFlash.bin";
    return;

    #else

    TAF_NV_FLASH_DIRECTORY_TYPE_STRU    stFlashDirectory;

#if defined(INSTANCE_1)
    g_pucSmsFileOnFlash = "/modem_log/EfSmsOnFlashModem1.bin";
#elif defined(INSTANCE_2)
    g_pucSmsFileOnFlash = "/modem_log/EfSmsOnFlashModem2.bin";
#else
    g_pucSmsFileOnFlash = "/modem_log/EfSmsOnFlash.bin";
#endif

    if (NV_OK != NV_Read(en_NV_Item_ProductTypeForLogDirectory,
                         &stFlashDirectory,
                         sizeof(stFlashDirectory)))
    {
        MN_WARN_LOG("MN_MSG_GetFlashSmsStoragePath():WARNING: en_NV_Item_ProductTypeForLogDirectory Error");

        return;
    }

    if (TAF_FLASH_DIRECTORY_TYPE_V9R1PHONE == stFlashDirectory.enFlashDirectoryType)
    {
#if defined(INSTANCE_1)
        g_pucSmsFileOnFlash = "/mnvm3:0/EfSmsOnFlashModem1.bin";
#elif defined(INSTANCE_2)
        g_pucSmsFileOnFlash = "/mnvm3:0/EfSmsOnFlashModem2.bin";
#else
        g_pucSmsFileOnFlash = "/mnvm3:0/EfSmsOnFlash.bin";
#endif
        return;
    }

    if (TAF_FLASH_DIRECTORY_TYPE_V3R3E5_V3R3STICK == stFlashDirectory.enFlashDirectoryType)
    {
#if defined(INSTANCE_1)
        g_pucSmsFileOnFlash = "/yaffs0/EfSmsOnFlashModem1.bin";
#elif defined(INSTANCE_2)
        g_pucSmsFileOnFlash = "/yaffs0/EfSmsOnFlashModem2.bin";
#else
        g_pucSmsFileOnFlash = "/yaffs0/EfSmsOnFlash.bin";
#endif
        return;
    }

    return;
    #endif


}


VOS_VOID  MN_MSG_ReadSmsNvimSmsRexistSupportFlgNvim( VOS_VOID )
{
    MN_MSG_SMS_NVIM_SMSREXIST_SUPPORT_FLG_STRU     stSmsNvSmsrexitSupportFlg;
    MN_MSG_CUSTOM_CFG_INFO_STRU                   *pstMsCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                     ulLength;

    ulLength                                            = 0;

    stSmsNvSmsrexitSupportFlg.ucSmsNvSmsRexitSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
    stSmsNvSmsrexitSupportFlg.ucReserved1               = 0;
    stSmsNvSmsrexitSupportFlg.ucReserved2               = 0;
    stSmsNvSmsrexitSupportFlg.ucReserved3               = 0;


    pstMsCfgInfo = MN_MSG_GetCustomCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_SMS_NVIM_SMSREXIST_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(MN_MSG_SMS_NVIM_SMSREXIST_SUPPORT_FLG_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NVIM_SMS_NVIM_SMSREXIST_SUPPORT_FLG,
                         &stSmsNvSmsrexitSupportFlg, ulLength))
    {
        MN_WARN_LOG("MN_MSG_ReadSmsNvimSmsRexistSupportFlgNvim():WARNING: en_NV_Item_NVIM_SMS_PP_DOWNLOAD_SUPPORT_FLG Error");

        return;
    }


    if ((MN_MSG_NV_ITEM_ACTIVE != stSmsNvSmsrexitSupportFlg.ucSmsNvSmsRexitSupportFlg)
     && (MN_MSG_NV_ITEM_DEACTIVE != stSmsNvSmsrexitSupportFlg.ucSmsNvSmsRexitSupportFlg))
    {
        pstMsCfgInfo->ucSmsNvSmsRexitSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_MSG_ReadSmsNvimSmsRexistSupportFlgNvim():WARNING: NV parameter Error");
        return;
    }

    pstMsCfgInfo->ucSmsNvSmsRexitSupportFlg = stSmsNvSmsrexitSupportFlg.ucSmsNvSmsRexitSupportFlg;

    MN_MSG_GetFlashSmsStoragePath();

    return;
}


VOS_VOID  MN_MSG_ReadSmsStatusReportInEfsmsSupportFlgNvim( VOS_VOID )
{
    MN_MSG_SMS_STATUS_IN_EFSMS_SUPPORT_FLG_STRU    stSmsStatusInEfsmsSupportFlg;
    MN_MSG_CUSTOM_CFG_INFO_STRU                   *pstMsCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                     ulLength;

    ulLength                                                  = 0;


    stSmsStatusInEfsmsSupportFlg.ucSmsStatusInEfsmsSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
    stSmsStatusInEfsmsSupportFlg.ucReserved1                  = 0;
    stSmsStatusInEfsmsSupportFlg.ucReserved2                  = 0;
    stSmsStatusInEfsmsSupportFlg.ucReserved3                  = 0;


    pstMsCfgInfo = MN_MSG_GetCustomCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_SMS_STATUS_REPORT_IN_EFSMS_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(MN_MSG_SMS_STATUS_IN_EFSMS_SUPPORT_FLG_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NVIM_SMS_STATUS_REPORT_IN_EFSMS_SUPPORT_FLG,
                         &stSmsStatusInEfsmsSupportFlg, ulLength))
    {
        MN_WARN_LOG("MN_MSG_ReadSmsStatusReportInEfsmsSupportFlgNvim():WARNING: en_NV_Item_NVIM_SMS_STATUS_REPORT_IN_EFSMS_SUPPORT_FLG Error");

        return;
    }


    if ((MN_MSG_NV_ITEM_ACTIVE != stSmsStatusInEfsmsSupportFlg.ucSmsStatusInEfsmsSupportFlg)
     && (MN_MSG_NV_ITEM_DEACTIVE != stSmsStatusInEfsmsSupportFlg.ucSmsStatusInEfsmsSupportFlg))
    {
        pstMsCfgInfo->ucSmsStatusInEfsmsSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_MSG_ReadSmsStatusReportInEfsmsSupportFlgNvim():WARNING: NV parameter Error");
        return;
    }

    pstMsCfgInfo->ucSmsStatusInEfsmsSupportFlg = stSmsStatusInEfsmsSupportFlg.ucSmsStatusInEfsmsSupportFlg;

    return;
}


VOS_VOID  MN_MSG_ReadPsOnlyCsServiceSupportFlgNvim( VOS_VOID )
{
    NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU   stPsOnlyCsServiceSupportFlg;
    MN_MSG_CUSTOM_CFG_INFO_STRU                   *pstMsCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                                     ulLength;

    ulLength                                                = 0;


    stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
    stPsOnlyCsServiceSupportFlg.ucReserved1                 = 0;
    stPsOnlyCsServiceSupportFlg.ucReserved2                 = 0;
    stPsOnlyCsServiceSupportFlg.ucReserved3                 = 0;


    pstMsCfgInfo = MN_MSG_GetCustomCfgInfo();

    (VOS_VOID)NV_GetLength(en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG, &ulLength);
    if (ulLength > sizeof(NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG,
                         &stPsOnlyCsServiceSupportFlg, ulLength))
    {
        MN_WARN_LOG("MN_MSG_ReadPsOnlyCsServiceSupportFlgNvim():WARNING: en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG Error");

        return;
    }


    if ((MN_MSG_NV_ITEM_ACTIVE != stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg)
     && (MN_MSG_NV_ITEM_DEACTIVE != stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg))
    {
        pstMsCfgInfo->ucPsOnlyCsServiceSupportFlg = MN_MSG_NV_ITEM_DEACTIVE;
        MN_WARN_LOG("MN_MSG_ReadPsOnlyCsServiceSupportFlgNvim():WARNING: NV parameter Error");
        return;
    }

    pstMsCfgInfo->ucPsOnlyCsServiceSupportFlg = stPsOnlyCsServiceSupportFlg.ucPsOnlyCsServiceSupportFlg;

    return;
}


VOS_VOID  MN_MSG_ReadClosePathFlgNvim( VOS_VOID )
{
    VOS_UINT8                                      aucCustomizeChgRcvPath[2];
    MN_MSG_CUSTOM_CFG_INFO_STRU                   *pstMsCfgInfo = VOS_NULL_PTR;

    pstMsCfgInfo = MN_MSG_GetCustomCfgInfo();

    pstMsCfgInfo->ucLocalStoreFlg = VOS_TRUE;

    if (NV_OK == NV_Read(en_NV_Item_SMS_Close_Path, aucCustomizeChgRcvPath, sizeof(aucCustomizeChgRcvPath)))
    {
        if (VOS_TRUE == aucCustomizeChgRcvPath[0])
        {
            pstMsCfgInfo->ucLocalStoreFlg = aucCustomizeChgRcvPath[1];
        }
    }

    return;
}


VOS_VOID MN_MSG_ReadNvimInfo(VOS_VOID)
{
    /* en_NV_Item_NVIM_GET_CSMP_PARA_FROM_USIM_SUPPORT_FLG */
    MN_MSG_ReadCsmpParaFromUsimSupportFlgNvim();

    /* en_NV_Item_NVIM_SMS_PP_DOWNLOAD_SUPPORT_FLG */
    MN_MSG_ReadSmsPpDownloadSupportFlgNvim();

    /* en_NV_Item_NVIM_SMS_NVIM_SMSREXIST_SUPPORT_FLG */
    MN_MSG_ReadSmsNvimSmsRexistSupportFlgNvim();

    /* en_NV_Item_NVIM_SMS_STATUS_REPORT_IN_EFSMS_SUPPORT_FLG */
    MN_MSG_ReadSmsStatusReportInEfsmsSupportFlgNvim();

    /* en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG */
    MN_MSG_ReadPsOnlyCsServiceSupportFlgNvim();

    MN_MSG_ReadClosePathFlgNvim();

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



