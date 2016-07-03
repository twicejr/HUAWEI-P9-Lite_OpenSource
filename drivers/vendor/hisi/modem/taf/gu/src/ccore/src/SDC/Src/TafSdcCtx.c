

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "TafSdcCtx.h"
#include "TafLog.h"

#include "TafSdcLib.h"

#include "TafNvInterface.h"
#include  "NasNvInterface.h"
#if (FEATURE_IMS == FEATURE_ON)
#include  "ImsaNvInterface.h"
#endif

#include  "LNvCommon.h"


#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif
#include  "LNasNvInterface.h"
#if (FEATURE_ON == FEATURE_BASTET)
#include  "TtfNvInterface.h"
#endif

#include  "NasUtranCtrlInterface.h"

#include  "MmaAppLocal.h"
#include "TafStdlib.h"

#include "NasUsimmApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 常量定义
*****************************************************************************/

/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define THIS_FILE_ID PS_FILE_ID_TAFSDC_CTX_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/
/* 保存TAF层共用的CTX */
TAF_SDC_CTX_STRU                        g_stTafSdcCtx;

/*默认情况下使用的GSM 7bit to ASCII码转换表*/
LOCAL VOS_UINT8 g_aucTafSdcDef7BitToAsciiTbl[] =
{
 '@', 0xA3, '$', 0xA5, 0xE8, 0xE9, 0xF9, 0xEC, 0xF2, 0xC7,0x0A, 0xD8, 0xF8,0x0D, 0xC5, 0xE5,
 '?', '_', '?', '?', '?', '?', '?', '?', '?', '?', '?',' ', 0xC6, 0xE6, 0xDF, 0xC9,
 ' ', '!',0x22, '#', 0x2A, '%', '&',0x27, '(', ')', '*', '+', ',', '-', '.', '/',
 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
 0xA1, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0xC4, 0xD6, 0xD1, 0xDC, 0xA7,
 0xBF, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0xE4, 0xF6, 0xF1, 0xFC, 0xE0
};


/*TME定制使用的GSM 7bit to ASCII码转换表*/
LOCAL VOS_UINT8 g_aucTafSdcTme7BitToAsciiTbl[] =
{
 '@', 0x9C, '$', 0x9D, 0x8A, 0x82, 0x97, 0x8D, 0x95, 0x80,0x0A, '?', '?',0x0D, 0x8F, 0x86,
 '?', '_', 0xE8, 0xE2, '?', 0xEA, 0xE3, '?',0xE4, 0xE9, '?','?', 0x92, 0x91, 0xE1, 0x90,
 ' ', '!',0x22, '#', '?', '%', '&',0x27, '(', ')', '*', '+', ',', '-', '.', '/',
 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
 0xAD, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 0x8E, 0x99, 0xA5, 0x9A, '?',
 0xA8, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 0x84, 0x94, 0xA4, 0x81, 0x85
};


LOCAL VOS_CHAR *g_aucTafSdcCallEmerNumsNoUsim[TAF_SDC_NUMOF_EMER_NUMS_NO_USIM] =
{
"112", "911", "000", "08", "110", "118", "119", "999"
};

LOCAL VOS_CHAR *g_aucTafSdcCallEmerNumsWithUsim[TAF_SDC_NUMOF_EMER_NUMS_WITH_USIM] =
{"112", "911"};

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
LOCAL VOS_CHAR *g_acTafSdcCdmaCallEmcNums[TAF_SDC_NUMOF_CDMA_PRESET_EMC_NUM] =
{
    "110", "112", "911", "999", "119", "120"
};
#endif

/*lint -save -e958 */

/*****************************************************************************
  6 函数定义
*****************************************************************************/

TAF_SDC_CTX_STRU*  TAF_SDC_GetSdcCtx( VOS_VOID )
{
    return &(g_stTafSdcCtx);
}


TAF_SDC_MS_CAP_INFO_STRU*  TAF_SDC_GetMsCapInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo);
}


VOS_UINT8 TAF_SDC_GetRoamFlag( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRoamFlag);
}


VOS_VOID TAF_SDC_SetRoamFlag(VOS_UINT8 ucRoamFlag)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRoamFlag = ucRoamFlag;
    return;
}


VOS_UINT8 TAF_SDC_GetCampOnFlag( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg);
}


VOS_VOID TAF_SDC_SetCampOnFlag(VOS_UINT8 ucCampOnFlg)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg = ucCampOnFlg;
    return;
}



VOS_VOID TAF_SDC_Set3GppRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.uc3GppRfAvailFlg = ucRfAvailFlg;
    return;
}


VOS_UINT8 TAF_SDC_Get3GppRfAvailFlag(VOS_VOID)
{
    return (g_stTafSdcCtx.stNetworkInfo.stSysInfo.st3gppSysInfo.uc3GppRfAvailFlg);
}


VOS_VOID TAF_SDC_Set1xRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.uc1xRfAvailFlg = ucRfAvailFlg;
    return;
}


VOS_UINT8 TAF_SDC_Get1xRfAvailFlag(VOS_VOID)
{
    return (g_stTafSdcCtx.stNetworkInfo.stSysInfo.st1xSysInfo.uc1xRfAvailFlg);
}


VOS_VOID TAF_SDC_SetHrpdRfAvailFlag(
    VOS_UINT8                           ucRfAvailFlg
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.stHrpdSysInfo.ucHrpdRfAvailFlg = ucRfAvailFlg;
    return;
}


VOS_UINT8 TAF_SDC_GetHrpdRfAvailFlag(VOS_VOID)
{
    return (g_stTafSdcCtx.stNetworkInfo.stSysInfo.stHrpdSysInfo.ucHrpdRfAvailFlg);
}





TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetSysMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysMode);
}


VOS_VOID TAF_SDC_SetSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysMode = enSysMode;
    return;
}


TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetSysSubMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysSubMode);
}

VOS_VOID TAF_SDC_SetSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.enSysSubMode = enSysSubMode;
    return;
}


TAF_SDC_3GPP_SYS_INFO_STRU* TAF_SDC_Get3gppSysInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo);
}


TAF_SDC_SYS_INFO_STRU* TAF_SDC_GetSysInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo);
}




VOS_VOID TAF_SDC_SetCurrCampPlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.stPlmnId = *pstPlmnId;
    return;
}


TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetCurrCampPlmnId(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.stPlmnId);
}


VOS_UINT16 TAF_SDC_GetCurrCampLac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.usLac);
}


VOS_VOID TAF_SDC_SetCurrCampLac(VOS_UINT16 usLac)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.usLac = usLac;
    return;
}


VOS_UINT8 TAF_SDC_GetCurrCampRac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRac);
}


VOS_VOID TAF_SDC_SetCurrCampRac(VOS_UINT8 ucRac)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ucRac = ucRac;
    return;
}


VOS_UINT32 TAF_SDC_GetCurrCampCellId(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulCellId);
}


VOS_VOID TAF_SDC_SetCurrCampCellId(VOS_UINT32 ulCellId)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulCellId = ulCellId;
    return;
}


TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 TAF_SDC_GetCurrLmmAccessType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.enLmmAccessType);
}


VOS_VOID TAF_SDC_SetCurrLmmAccessType(TAF_SDC_LMM_ACCESS_TYPE_ENUM_UINT8 enLmmAccessType)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.enLmmAccessType  = enLmmAccessType;
    return;
}



TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetCsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsServiceStatus);
}


VOS_VOID TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsServiceStatus = enCsServiceStatus;
    return;
}


TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetPsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsServiceStatus);
}


VOS_VOID TAF_SDC_SetPsServiceStatus(TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsServiceStatus = enPsServiceStatus;
    return;
}



VOS_VOID TAF_SDC_SetPsAttachAllowFlg(VOS_UINT8 ucPsAttachAllowFlg)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllowFlg = ucPsAttachAllowFlg;
    return;
}


VOS_UINT8 TAF_SDC_GetPsAttachAllowFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucPsAttachAllowFlg;
}




VOS_VOID TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.enReportSrvsta = enReportSrvsta;
    return;
}


TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetServiceStatus(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.enReportSrvsta;
}


VOS_VOID TAF_SDC_SetAppServiceStatus(
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 enReportSrvsta
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enReportSrvsta = enReportSrvsta;
    return;
}


TAF_SDC_REPORT_SRVSTA_ENUM_UINT8 TAF_SDC_GetAppServiceStatus(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enReportSrvsta;
}

TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetServiceDomain( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.enServiceDomain);
}


VOS_VOID TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.enServiceDomain = enServiceDomain;
    return;
}



TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 TAF_SDC_GetAppServiceDomain( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enServiceDomain);
}


VOS_VOID TAF_SDC_SetAppServiceDomain(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8 enServiceDomain
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.enServiceDomain = enServiceDomain;
    return;
}


TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetCsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus);
}


VOS_VOID TAF_SDC_SetCsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.enCsRegStatus = enCsRegStatus;
    return;
}


TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsRegStatus);
}


VOS_VOID TAF_SDC_SetAppCsRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8 enCsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsRegStatus = enCsRegStatus;
    return;
}



TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetPsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus);
}



VOS_VOID TAF_SDC_SetPsRegStatus(TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.enPsRegStatus = enPsRegStatus;
    return;
}


TAF_SDC_REG_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsRegStatus);
}



VOS_VOID TAF_SDC_SetAppPsRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8 enPsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsRegStatus = enPsRegStatus;
    return;
}


VOS_UINT8 TAF_SDC_GetSimCsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucSimCsRegStatus);
}


VOS_VOID TAF_SDC_SetSimCsRegStatus(
    VOS_UINT8       ucSimCsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucSimCsRegStatus = ucSimCsRegStatus;
    return;
}



VOS_UINT8 TAF_SDC_GetSimPsRegStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucSimPsRegStatus);
}



VOS_VOID TAF_SDC_SetSimPsRegStatus(
    VOS_UINT8       ucSimPsRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.ucSimPsRegStatus= ucSimPsRegStatus;
    return;
}



VOS_VOID TAF_SDC_SetCsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstCsAcRetriction)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction = *pstCsAcRetriction;
    return;
}


TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetCsAcRestriction(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.stCsAcRestriction));
}


TAF_SDC_ACCESS_RESTRICTION_STRU *TAF_SDC_GetPsAcRestriction(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction));
}



VOS_VOID TAF_SDC_SetPsAcRestriction(TAF_SDC_ACCESS_RESTRICTION_STRU *pstPsAcRetriction)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stPsDomainInfo.stPsAcRestriction = *pstPsAcRetriction;
    return;
}


VOS_UINT8* TAF_SDC_GetSimImsi( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucImsi);
}


VOS_UINT8* TAF_SDC_GetCsimImsi( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stMsIdentity.aucImsi);
}


VOS_VOID TAF_SDC_SetSimImsi(
    VOS_UINT8                          *pstImsi
)
{
    PS_MEM_CPY(TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucImsi, pstImsi, sizeof(g_stTafSdcCtx.stSimInfo.stUsimInfo.stMsIdentity.aucImsi));
    return;
}


VOS_UINT8* TAF_SDC_GetLastSimImsi(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucLastImsi);
}


VOS_VOID TAF_SDC_SetLastSimImsi(
    VOS_UINT8                          *pstImsi
)
{
    PS_MEM_CPY(TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stMsIdentity.aucLastImsi, pstImsi,
                sizeof(g_stTafSdcCtx.stSimInfo.stUsimInfo.stMsIdentity.aucLastImsi));
    return;
}


TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetSimStatus(
    VOS_VOID
)
{
    /* 综合Usim和Csim的CardService获取卡状态 */
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enUsimStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enCsimStatus;

    enUsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus;
    enCsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus;

    if (TAF_SDC_USIM_STATUS_VALID == enUsimStatus)
    {
        return enUsimStatus;
    }
    else if (TAF_SDC_USIM_STATUS_NO_PRESENT != enUsimStatus)
    {
        if (TAF_SDC_USIM_STATUS_VALID == enCsimStatus)
        {
            return enCsimStatus;
        }
        else
        {
            return enUsimStatus;
        }
    }
    else
    {
        if (TAF_SDC_USIM_STATUS_NO_PRESENT != enCsimStatus)
        {
            return enCsimStatus;
        }
        else
        {
            return TAF_SDC_USIM_STATUS_NO_PRESENT;
        }
    }
}


VOS_VOID TAF_SDC_SetUsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus = enSimStatus;
    return;
}


TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetUsimStatus(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus);
}


TAF_SDC_USIM_STATUS_ENUM_UINT8 TAF_SDC_GetCsimStatus(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus);
}


VOS_VOID TAF_SDC_SetCsimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus = enSimStatus;

    return;
}


VOS_VOID TAF_SDC_SetIccIdInfo(
    VOS_UINT8                   ucLen,
    VOS_UINT8                  *pucIccId
)
{
    TAF_SDC_ICCID_INFO_STRU    *pstIccIdInfo    = VOS_NULL_PTR;

    pstIccIdInfo                = TAF_SDC_GetIccIdInfo();

    PS_MEM_SET(pstIccIdInfo, 0xFF, sizeof(TAF_SDC_ICCID_INFO_STRU));

    PS_MEM_CPY(pstIccIdInfo->aucIccId, pucIccId, ucLen);

    pstIccIdInfo->ucLen         = ucLen;

    return;
}


TAF_SDC_ICCID_INFO_STRU *TAF_SDC_GetIccIdInfo( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stSimInfo.stIccIdInfo);
}


VOS_VOID TAF_SDC_SetCsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enCsimType
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType = enCsimType;

    return;
}


VOS_VOID TAF_SDC_SetUsimType(
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enUsimType
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType = enUsimType;

    return;
}


TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetUsimType(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType);
}


TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetCsimType(
    VOS_VOID
)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType);
}


TAF_SDC_SIM_TYPE_ENUM_UINT8 TAF_SDC_GetSimType(VOS_VOID)
{
    /* 获取综合的卡类型，下个迭代将改成GetCardType */
    TAF_SDC_USIM_STATUS_ENUM_UINT8      pstUsimStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      pstCsimStatus;

    pstUsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.stUsimStatus.enSimStatus;
    pstCsimStatus = TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.stCsimStatus.enSimStatus;

    if (TAF_SDC_USIM_STATUS_VALID == pstUsimStatus)
    {
        return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType);
    }
    else if (TAF_SDC_USIM_STATUS_NO_PRESENT != pstUsimStatus)
    {
        if (TAF_SDC_USIM_STATUS_VALID == pstCsimStatus)
        {
            return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType);
        }
        else
        {
            return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enUsimType);
        }
    }
    else
    {
        if (TAF_SDC_USIM_STATUS_NO_PRESENT != pstCsimStatus)
        {
            return (TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.enCsimType);
        }
        else
        {
            return TAF_SDC_SIM_TYPE_BUTT;
        }
    }
}


TAF_SDC_PLATFORM_RAT_CAP_STRU*  TAF_SDC_GetPlatformRatCap( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stPlatformRatCap);
}

TAF_SDC_CURC_RPT_CTRL_STRU*  TAF_SDC_GetCurcRptCtrl( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stRptCtrl.stCurcRptCtrl);
}


TAF_SDC_UNSOLICITED_RPT_CTRL_STRU*  TAF_SDC_GetUnsolicitedRptCtrl( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stRptCtrl.stUnsolicitedRptCtrl);
}


TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetGuNwCapInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo);
}



TAF_SDC_NETWORK_CAP_INFO_STRU *TAF_SDC_GetLteNwCapInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo);
}


VOS_VOID TAF_SDC_SetGuNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo.enLteCsCap   = pstNwCapInfo->enLteCsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo.enNwEmcBsCap = pstNwCapInfo->enNwEmcBsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stGuNwCapInfo.enNwImsVoCap = pstNwCapInfo->enNwImsVoCap;
}


VOS_VOID TAF_SDC_SetLteNwCapInfo(TAF_SDC_NETWORK_CAP_INFO_STRU *pstNwCapInfo)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo.enLteCsCap   = pstNwCapInfo->enLteCsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo.enNwEmcBsCap = pstNwCapInfo->enNwEmcBsCap;
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stLteNwCapInfo.enNwImsVoCap = pstNwCapInfo->enNwImsVoCap;
}


VOS_VOID TAF_SDC_SetCsAttachAllowFlg(VOS_UINT8 ucCsAttachAllowFlg)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllowFlg = ucCsAttachAllowFlg;
    return;
}


VOS_UINT8 TAF_SDC_GetCsAttachAllowFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stCsDomainInfo.ucCsAttachAllowFlg;
}





TAF_SDC_NETWORK_INFO_STRU* TAF_SDC_GetCurrNetworkInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo);
}



VOS_VOID TAF_SDC_SetAppRssiValue(VOS_UINT8 ucRssiValue)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.ucRssiValue = ucRssiValue;
    return;
}


VOS_UINT8 TAF_SDC_GetAppRssiValue(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.ucRssiValue;
}


VOS_UINT16 TAF_SDC_GetAppCellUlFreq(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.usCellUlFreq;
}


VOS_UINT16 TAF_SDC_GetAppCellDlFreq(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.usCellDlFreq;
}



VOS_UINT32 TAF_SDC_GetAppLteArfcn(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulLteArfcn;
}


VOS_VOID TAF_SDC_SetAppLteArfcn(VOS_UINT32 ulLteArfcn)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st3gppSysInfo.ulLteArfcn = ulLteArfcn;
}


VOS_VOID TAF_SDC_SetAppServicePlmnId(TAF_SDC_PLMN_ID_STRU *pstPlmnId)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.stServicePlmnId = *pstPlmnId;
    return;
}


TAF_SDC_PLMN_ID_STRU *TAF_SDC_GetAppServicePlmnId(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.stServicePlmnId);
}




VOS_VOID TAF_SDC_SetAppSysMode(TAF_SDC_SYS_MODE_ENUM_UINT8 enSysMode)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysMode = enSysMode;
    return;
}


TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetAppSysMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysMode);
}



VOS_VOID TAF_SDC_SetAppSysSubMode(TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysSubMode = enSysSubMode;

    return;
}


TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_SDC_GetAppSysSubMode( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysSubMode);
}



VOS_VOID TAF_SDC_SetAppCampLac(VOS_UINT16 usLac)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.usServiceLac = usLac;
    return;
}


VOS_UINT16 TAF_SDC_GetAppCampLac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.usServiceLac);
}



VOS_VOID TAF_SDC_SetAppCampRac(VOS_UINT8 ucRac)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRac = ucRac;
    return;
}


VOS_UINT8 TAF_SDC_GetAppCampRac(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRac);
}


VOS_VOID TAF_SDC_SetAppCampCellId(VOS_UINT32 ulServiceCellId)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ulServiceCellId = ulServiceCellId;
    return;
}


VOS_UINT32 TAF_SDC_GetAppCampCellId(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ulServiceCellId);
}


VOS_VOID TAF_SDC_SetAppRoamFlg(VOS_UINT8 ucServiceRoamFlg)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg = ucServiceRoamFlg;
    return;
}


VOS_UINT8 TAF_SDC_GetAppRoamFlg(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg);
}


TAF_SDC_APPNETWORK_INFO* TAF_SDC_GetAppNetworkInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo);
}


VOS_VOID TAF_SDC_SetAppUtranMode(VOS_UINT8 ucServiceUtranMode)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceUtranMode = ucServiceUtranMode;
    return;
}


VOS_UINT8 TAF_SDC_GetAppUtranMode(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.ucServiceUtranMode);
}



TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppCsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsServiceStatus);
}


VOS_VOID TAF_SDC_SetAppCsServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enCsServiceStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stCsDomainInfo.enCsServiceStatus = enCsServiceStatus;
    return;
}


TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_SDC_GetAppPsServiceStatus( VOS_VOID )
{
    return (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsServiceStatus);
}


VOS_VOID TAF_SDC_SetAppPsServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8 enPsServiceStatus
)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stPsDomainInfo.enPsServiceStatus = enPsServiceStatus;
    return;
}



VOS_VOID TAF_SDC_InitSvlteSupportFlag(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                                  ulLength;
    SVLTE_SUPPORT_FLAG_STRU                     stSvlteFlag;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 初始化为不支持SVLTE */
    pstMsCapInfo->ucSvlteSupportFlag = VOS_FALSE;

    /* SVLTE只有在FEATURE_MULTI_MODEM打开时，才有可能设置为开启 */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_SVLTE_FLAG, &ulLength);

    if (ulLength > sizeof(SVLTE_SUPPORT_FLAG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSvlteSupportFlag():WARNING: en_NV_Item_SVLTE length Error");

        return;
    }

    /* 读NV项en_NV_Item_SVLTE_FLAG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_SVLTE_FLAG,
                         &stSvlteFlag, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSvlteSupportFlag():WARNING: read en_NV_Item_SVLTE Error");

        return;
    }

    /* 赋值到全局变量中 */
    pstMsCapInfo->ucSvlteSupportFlag = stSvlteFlag.ucSvlteSupportFlag;
#endif

    return;
}



VOS_VOID TAF_SDC_InitImsRatSupport(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    IMSA_NV_IMS_RAT_SUPPORT_STRU                stImsSupport;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* IMS宏关闭时，默认初始化为不支持IMS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stImsRatSupport), 0, sizeof(TAF_SDC_IMS_RAT_SUPPORT_STRU));
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmEmsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranEmsSupportFlag = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag   = VOS_FALSE;

    /* IMS能力只有在FEATURE_IMS打开时，才有可能设置为开启 */
#if (FEATURE_ON == FEATURE_IMS)

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_RAT_SUPPORT, &ulLength);

    if (ulLength > sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsRatSupport():WARNING: EN_NV_ID_IMS_RAT_SUPPORT length Error");

        return;
    }

    /* 读NV项EN_NV_ID_IMS_RAT_SUPPORT，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_RAT_SUPPORT,
                         &stImsSupport, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsRatSupport():WARNING: read EN_NV_ID_IMS_RAT_SUPPORT Error");

        return;
    }

    /* 赋值到全局变量中 */
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag = stImsSupport.ucUtranImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag   = stImsSupport.ucLteImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucGsmEmsSupportFlag   = stImsSupport.ucGsmEmsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucUtranEmsSupportFlag = stImsSupport.ucUtranEmsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag   = stImsSupport.ucLteEmsSupportFlag;
#endif

    return;
}



VOS_VOID TAF_SDC_InitImsCapability(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    IMS_NV_IMS_CAP_STRU                         stImsCapa;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* IMS宏关闭时，默认初始化为不支持IMS VOICE和IMS SMS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stImsCapability), 0, sizeof(TAF_SDC_IMS_CAPABILITY_STRU));
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag   = VOS_FALSE;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag         = VOS_FALSE;

    /* IMS能力只有在FEATURE_IMS打开时，才有可能设置为开启 */
#if (FEATURE_ON == FEATURE_IMS)

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_IMS_CAPABILITY, &ulLength);

    if (ulLength > sizeof(IMS_NV_IMS_CAP_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsCapability():WARNING: EN_NV_ID_IMS_CAPABILITY length Error");

        return;
    }

    /* 读NV项EN_NV_ID_IMS_CAPABILITY，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_IMS_CAPABILITY,
                         &stImsCapa, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitImsCapability():WARNING: read EN_NV_ID_IMS_CAPABILITY Error");

        return;
    }

    /* 赋值到全局变量中 */
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag   = stImsCapa.ucVoiceCallOnImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag   = stImsCapa.ucVideoCallOnImsSupportFlag;
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag         = stImsCapa.ucSmsOnImsSupportFlag;
#endif

    return;
}


VOS_VOID TAF_SDC_InitVoiceDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    LNAS_LMM_NV_VOICE_DOMAIN_STRU               stVoiceDomain;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* NV关闭时，默认初始化为CS ONLY */
    pstMsCapInfo->stImsConfigPara.enVoiceDomain = TAF_SDC_VOICE_DOMAIN_CS_ONLY;

#if (FEATURE_ON == FEATURE_IMS)

    /* NV打开时，默认初始化为ps preferred */
    pstMsCapInfo->stImsConfigPara.enVoiceDomain = TAF_SDC_VOICE_DOMAIN_IMS_PS_PREFERRED;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(EN_NV_ID_UE_VOICE_DOMAIN, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitVoiceDomain():WARNING: EN_NV_ID_UE_VOICE_DOMAIN length Error");

        return;
    }

    /* 读NV项EN_NV_ID_UE_VOICE_DOMAIN，失败，直接返回 */
    if (NV_OK != NV_Read(EN_NV_ID_UE_VOICE_DOMAIN,
                         &stVoiceDomain, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitVoiceDomain():WARNING: read EN_NV_ID_UE_VOICE_DOMAIN Error");

        return;
    }

    /* NV项激活，并且取值合法时，赋值到全局变量中 */
    if ( (NV_ITEM_ACTIVE == stVoiceDomain.bitOpVoicDomain)
      && (NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED >= stVoiceDomain.enVoicDomain) )
    {
        pstMsCapInfo->stImsConfigPara.enVoiceDomain = stVoiceDomain.enVoicDomain;
    }
#endif

    return;
}


VOS_VOID TAF_SDC_InitSmsDomain(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NVIM_SMS_DOMAIN_STRU                    stSmsDomain;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 默认初始化为not use sms over ip */
    pstMsCapInfo->stImsConfigPara.enSmsDomain   = TAF_SDC_SMS_DOMAIN_NOT_USE_SMS_OVER_IP;

#if (FEATURE_ON == FEATURE_IMS)
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_SMS_DOMAIN, &ulLength);

    if (ulLength > sizeof(TAF_NVIM_SMS_DOMAIN_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSmsDomain():WARNING: en_NV_Item_SMS_DOMAIN length Error");

        return;
    }

    /* 读NV项en_NV_Item_SMS_DOMAIN，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_SMS_DOMAIN,
                         &stSmsDomain, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitSmsDomain():WARNING: read en_NV_Item_SMS_DOMAIN Error");

        return;
    }

    /* NV项激活，并且取值合法时，赋值到全局变量中 */
    if (TAF_SDC_SMS_DOMAIN_PREFER_TO_USE_SMS_OVER_IP >= stSmsDomain.ucSmsDomain)
    {
        pstMsCapInfo->stImsConfigPara.enSmsDomain = stSmsDomain.ucSmsDomain;
    }
#endif

    return;
}



VOS_VOID TAF_SDC_InitLteCsServiceCfg(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
    NAS_NVIM_LTE_CS_SERVICE_CFG_STRU                        stLteCsServiceCfg;
    VOS_UINT32                                              ulLength;

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    ulLength        = 0;
    PS_MEM_SET(&stLteCsServiceCfg, 0x00, sizeof(NAS_NVIM_LTE_CS_SERVICE_CFG_STRU));

    /* 默认初始化为TAF_SDC_LTE_SUPPORT_BUTT，和MMC初始值保持一致 */
    pstMsCapInfo->stImsConfigPara.enLteCsServiceCfg = TAF_SDC_LTE_SUPPORT_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_Lte_Cs_Service_Config, &ulLength);

    if (ulLength > sizeof(stLteCsServiceCfg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitLteCsServiceCfg():WARNING: en_NV_Item_Lte_Cs_Service_Config length Error");
        return;
    }
    if ( NV_OK != NV_Read(en_NV_Item_Lte_Cs_Service_Config,
                          &stLteCsServiceCfg,
                          ulLength ))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitLteCsServiceCfg(): en_NV_Item_Lte_Cs_Service_Config Error");
        return;
    }

    /* 如果NV项激活并且值有效，则更新全局变量 */
    if ((NV_ITEM_ACTIVE == stLteCsServiceCfg.ucNvimActiveFlg)
     && (stLteCsServiceCfg.ucLteCsServiceCfg < TAF_SDC_LTE_SUPPORT_BUTT))
    {
        pstMsCapInfo->stImsConfigPara.enLteCsServiceCfg = stLteCsServiceCfg.ucLteCsServiceCfg;

    }

    return;
}


VOS_VOID TAF_SDC_InitRedialCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU  stRedialImsToCs;

    PS_MEM_SET(&stRedialImsToCs, 0, sizeof(TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU));
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 默认初始化为FALSE */
    /* IMS to CS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs),
               0,
               sizeof(TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU));

    /* CS to IMS */
    PS_MEM_SET(&(pstMsCapInfo->stImsConfigPara.stRedial.stRedialCsToIms),
               0,
               sizeof(TAF_SDC_SWITCH_CS_TO_IMS_REDIAL_CONFIG_STRU));

#if (FEATURE_ON == FEATURE_IMS)
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG, &ulLength);

    if (ulLength > sizeof(TAF_NV_SWITCH_IMS_TO_CS_REDIAL_CONFIG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRedialConfig():WARNING: en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG length Error");

        return;
    }

    /* 读NV项en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG,
                         &stRedialImsToCs, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRedialConfig():WARNING: read en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN_CFG Error");

        return;
    }

    /* NV项激活，更新重拨配置 */
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.ucCallRedial = stRedialImsToCs.ucCallRedial;
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.ucSmsRedial  = stRedialImsToCs.ucSmsRedial;
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.ucSsRedial   = stRedialImsToCs.ucSsRedial;

    /* IMS REDIAL NUM */
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum  = TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM;

    if (stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum <= TAF_NVIM_IMS2CS_CALL_REDIAL_CAUSE_MAX_NUM)
    {
        pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum = stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum;
    }



    /* IMSA REDIAL NUM */
    pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum = TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM;

    if (stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum <= TAF_NVIM_IMSA2CS_CALL_REDIAL_CAUSE_MAX_NUM)
    {
        pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum = stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum;
    }



    /* IMS REDIAL CAUSE */
    PS_MEM_CPY(pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ausImsRedialCause,
                stRedialImsToCs.stCallRedialCauseCfg.ausImsRedialCause,
                (stRedialImsToCs.stCallRedialCauseCfg.ucImsRedialCauseNum)*sizeof(VOS_UINT16));



    /* IMSA REDIAL CAUSE */
    PS_MEM_CPY(pstMsCapInfo->stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg.ausImsaRedialCause,
                stRedialImsToCs.stCallRedialCauseCfg.ausImsaRedialCause,
                (stRedialImsToCs.stCallRedialCauseCfg.ucImsaRedialCauseNum)*sizeof(VOS_UINT16));

    /* CS to IMS方向的换域重拨未来在这儿添加 */
#endif

    return;
}


VOS_VOID TAF_SDC_InitImsRoamingCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NV_IMS_ROAMING_SUPPORT_STRU             stRoamingFlg;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 默认初始化为FALSE */
    pstMsCapInfo->stImsConfigPara.ucRoamingSupport = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_IMS_ROAMING_SUPPORT_FLG, &ulLength);

    if (ulLength > sizeof(TAF_NV_IMS_ROAMING_SUPPORT_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsRoamingCfgInfo():WARNING: en_NV_Item_IMS_ROAMING_SUPPORT_FLG length Error");

        return;
    }

    /* 读NV项en_NV_Item_IMS_ROAMING_SUPPORT_FLG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_IMS_ROAMING_SUPPORT_FLG,
                         &stRoamingFlg, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsRoamingCfgInfo():WARNING: read en_NV_Item_IMS_ROAMING_SUPPORT_FLG Error");

        return;
    }

    /* NV项激活，更新ims漫游支持配置信息 */
    pstMsCapInfo->stImsConfigPara.ucRoamingSupport = stRoamingFlg.ucImsRoamingFlg;
#endif

    return;
}


VOS_VOID TAF_SDC_InitImsUssdCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                                  ulLength;
    TAF_NV_IMS_USSD_SUPPORT_STRU                stUssdFlg;
#endif

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 默认初始化为FALSE */
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_IMS_USSD_SUPPORT_FLG, &ulLength);

    if (ulLength > sizeof(TAF_NV_IMS_USSD_SUPPORT_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsUssdCfgInfo():WARNING: en_NV_Item_IMS_USSD_SUPPORT_FLG length Error");

        return;
    }

    /* 读NV项en_NV_Item_IMS_USSD_SUPPORT_FLG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_IMS_USSD_SUPPORT_FLG,
                         &stUssdFlg, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_SDC_InitImsUssdCfgInfo():WARNING: read en_NV_Item_IMS_USSD_SUPPORT_FLG Error");

        return;
    }

    /* NV项激活，更新USSD支持配置信息 */
    pstMsCapInfo->stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag = stUssdFlg.ucUssdOnImsSupportFlag;
#endif

    return;
}


VOS_VOID TAF_SDC_InitImsConfigPara(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
    /* EN_NV_ID_IMS_RAT_SUPPORT */
    TAF_SDC_InitImsRatSupport(enInitType, pstMsCapInfo);

    /* EN_NV_ID_IMS_CAPABILITY */
    TAF_SDC_InitImsCapability(enInitType, pstMsCapInfo);

    /* EN_NV_ID_UE_VOICE_DOMAIN */
    TAF_SDC_InitVoiceDomain(enInitType, pstMsCapInfo);

    /* en_NV_Item_SMS_DOMAIN */
    TAF_SDC_InitSmsDomain(enInitType, pstMsCapInfo);

    /* en_NV_Item_Lte_Cs_Service_Config */
    TAF_SDC_InitLteCsServiceCfg(enInitType, pstMsCapInfo);

    TAF_SDC_InitRedialCfgInfo(enInitType, pstMsCapInfo);

    TAF_SDC_InitImsRoamingCfgInfo(enInitType, pstMsCapInfo);


    TAF_SDC_InitImsUssdCfgInfo(enInitType, pstMsCapInfo);
}


VOS_VOID TAF_SDC_InitLcConfigPara(
    TAF_SDC_LC_CONFIG_PARA_STRU        *pstLcConfigPara
)
{
    pstLcConfigPara->ucLCEnableFlg  = VOS_FALSE;
    pstLcConfigPara->enRatCombined  = TAF_NVIM_LC_RAT_COMBINED_BUTT;
    pstLcConfigPara->enLCWorkCfg    = TAF_NVIM_LC_WORK_CFG_BUTT;
    pstLcConfigPara->aucReserved[0] = 0;

    return;
}
#if (FEATURE_ON == FEATURE_BASTET)

VOS_VOID TAF_SDC_InitBastetSupportFlag(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    TAF_SDC_MS_CAP_INFO_STRU           *pstMsCapInfo
)
{
    VOS_UINT32                                  ulLength;
    BASTET_SUPPORT_FLG_STRU                     stBastetFlag;

    /* 仅在上电初始化时进行初始化操作，后续不修改 */
    if (TAF_SDC_INIT_CTX_STARTUP != enInitType)
    {
        return;
    }

    /* 初始化为不支持bastet*/
    pstMsCapInfo->ucBastetSupportFlag = VOS_FALSE;

    /* 先获取NV的长度 */
    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_Bastet_CONFIG, &ulLength);

    if (ulLength > sizeof(BASTET_SUPPORT_FLG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitBastetSupportFlag():WARNING: en_NV_Item_Bastet_CONFIG length Error");

        return;
    }

    /* en_NV_Item_Bastet_CONFIG，失败，直接返回 */
    if (NV_OK != NV_Read(en_NV_Item_Bastet_CONFIG,
                         &stBastetFlag, ulLength))
    {

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitBastetSupportFlag():WARNING: read en_NV_Item_Bastet_CONFIG Error");

        return;
    }

    /* 赋值到全局变量中 */
    pstMsCapInfo->ucBastetSupportFlag = stBastetFlag.ucActiveFlg;

    return;
}

/*lint -restore */

#endif

VOS_VOID TAF_SDC_InitMsCapInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_MS_CAP_INFO_STRU            *pstMsCapInfo
)
{
    TAF_SDC_InitSvlteSupportFlag(enInitType, pstMsCapInfo);

    TAF_SDC_InitImsConfigPara(enInitType, pstMsCapInfo);

    TAF_SDC_InitLcConfigPara(&(pstMsCapInfo->stLcConfigPara));
#if (FEATURE_ON == FEATURE_BASTET)
    TAF_SDC_InitBastetSupportFlag(enInitType, pstMsCapInfo);
#endif
}


VOS_VOID TAF_SDC_InitRptCtrlInfo(VOS_VOID)
{
    /* 初始化全局变量 */
    TAF_SDC_InitCurcRptCtrlInfo();

    /* 初始化单个命令主动上报标识 */
    TAF_SDC_InitUnsolicitedRptCtrlInfo();
    return;
}


VOS_VOID TAF_SDC_InitUssdCfgInfo(VOS_VOID)
{
    TAF_SDC_ReadUssdTransModeNvim();

    TAF_SDC_ReadUssdTransTableNvim();

    return;
}



VOS_VOID TAF_SDC_ReadUssdTransModeNvim(VOS_VOID)
{
    TAF_USSD_NVIM_TRANS_MODE_STRU       stUssdTranMode;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stUssdTranMode, 0x00, sizeof(TAF_USSD_NVIM_TRANS_MODE_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_CUST_USSD_MODE, &ulLength);

    /* 读取USSD是否透传设置 */
    if (NV_OK == NV_Read(en_NV_Item_CUST_USSD_MODE,
                          &stUssdTranMode,
                          ulLength))
    {
        if (VOS_TRUE != stUssdTranMode.ucStatus)
        {
            stUssdTranMode.ucUssdTransMode = TAF_SDC_USSD_TRAN_MODE;
        }
    }
    else
    {
        stUssdTranMode.ucUssdTransMode = TAF_SDC_USSD_TRAN_MODE;
    }

    TAF_SDC_SetUssdTransMode(stUssdTranMode.ucUssdTransMode);

    return;
}


VOS_VOID TAF_SDC_ReadUssdTransTableNvim(VOS_VOID)
{
    SSA_NV_ITEM_ALPHA_to_ASCII_STRU               stUSSDApha;
    VOS_UINT32                                    ulResult;
    VOS_UINT32                                    ulLength;

    ulLength = 0;
    stUSSDApha.ucStatus         = VOS_FALSE;
    stUSSDApha.ucAlphaTransMode = TAF_SDC_USSD_TRAN_MODE_BUTT;

    (VOS_VOID)NV_GetLength(en_NV_Item_USSD_Apha_To_Ascii, &ulLength);

    ulResult = NV_Read(en_NV_Item_USSD_Apha_To_Ascii,
                       &stUSSDApha,
                       ulLength);

    if ((ulResult == NV_OK)
     && (VOS_TRUE == stUSSDApha.ucStatus)
     && (VOS_TRUE == (stUSSDApha.ucAlphaTransMode & 0x01)))
    {
        TAF_SDC_Set7BitToAssicTableType(TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_TME);
    }
    else
    {
        TAF_SDC_Set7BitToAssicTableType(TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_DEF);
    }

    return;
}



VOS_VOID TAF_SDC_InitAppCfgSupportType(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stSysAppConfig;
    VOS_UINT16                          usAppCfgType;

    stSysAppConfig.usSysAppConfigType = SYSTEM_APP_BUTT;
    ulLength                          = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_System_APP_Config, &ulLength);

    if (ulLength > sizeof(stSysAppConfig))
    {
        TAF_SDC_SetAppCfgSupportType(SYSTEM_APP_MP);
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config,
                         &stSysAppConfig, ulLength))
    {
        TAF_SDC_SetAppCfgSupportType(SYSTEM_APP_MP);

        return;
    }

    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType )
    {
        usAppCfgType    = SYSTEM_APP_MP;
    }
    else
    {
        usAppCfgType    = stSysAppConfig.usSysAppConfigType ;
    }

    TAF_SDC_SetAppCfgSupportType(usAppCfgType);

    return;
}



VOS_VOID TAF_SDC_InitPlmnExactlyCompareFlg(VOS_VOID)
{
    NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU             stPlmnExactlyCompara;
    VOS_UINT32                                              ulLength;

    PS_MEM_SET(&stPlmnExactlyCompara, 0x00, sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU));

    ulLength = 0;
    TAF_SDC_SetPlmnExactlyCompareFlg(VOS_FALSE);

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &ulLength);

    if (ulLength > sizeof(NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitPlmnExactlyCompareFlg():WARNING: en_NV_Item_PLMN_EXACTLY_COMPARE_FLG length Error");
        return;
    }

    /* 读取NV */
    if (NV_OK != NV_Read (en_NV_Item_PLMN_EXACTLY_COMPARE_FLG, &stPlmnExactlyCompara, ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitPlmnExactlyCompareFlg(): en_NV_Item_PLMN_EXACTLY_COMPARE_FLG Error");
        return;
    }

    /* NV有效性检查 */
    if (VOS_TRUE == stPlmnExactlyCompara.ucPlmnExactlyCompareFlag)
    {
        /* 赋值到全局变量 */
        TAF_SDC_SetPlmnExactlyCompareFlg(stPlmnExactlyCompara.ucPlmnExactlyCompareFlag);
    }

    return;
}



VOS_VOID TAF_SDC_InitRefreshAllFileRestartFlag(VOS_VOID)
{
    TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU              stRefreshAllFileRestartFlag;
    VOS_UINT32                                              ulLength;

    PS_MEM_SET(&stRefreshAllFileRestartFlag, 0x00, sizeof(TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU));

    ulLength = 0;
    TAF_SDC_SetRefreshAllFileRestartFlag(VOS_FALSE);

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG, &ulLength);

    if (ulLength > sizeof(TAF_NVIM_REFRESH_ALL_FILE_RESTART_CFG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRefreshAllFileRestartFlag():WARNING: en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG length Error");
        return;
    }

    /* 读取NV */
    if (NV_OK != NV_Read (en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG, &stRefreshAllFileRestartFlag, ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitRefreshAllFileRestartFlag(): en_NV_Item_REFRESH_ALL_FILE_RESTART_CFG Error");
        return;
    }

    /* NV有效性检查 */
    if (VOS_TRUE == stRefreshAllFileRestartFlag.ucRefreshAllFileRestartFlag)
    {
        /* 赋值到全局变量 */
        TAF_SDC_SetRefreshAllFileRestartFlag(stRefreshAllFileRestartFlag.ucRefreshAllFileRestartFlag);
    }

    return;
}



VOS_VOID TAF_SDC_InitUeUsageSetting(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    LNAS_LMM_NV_UE_CENTER_STRU          stUeCentric;

    ulLength = 0;

    (VOS_VOID)NV_GetLength(EN_NV_ID_UE_CENTER, &ulLength);

    if (ulLength > sizeof(LNAS_LMM_NV_UE_CENTER_STRU))
    {
        /* set data centric same as LNAS operation */
        TAF_SDC_SetUeUsageSetting(EMM_SETTING_DATA_CENTRIC);

        return;
    }

    stUeCentric.enUeCenter = EMM_USAGE_SETTING_BUTT;

    if (NV_OK != NV_Read(EN_NV_ID_UE_CENTER,
                         &stUeCentric, ulLength))
    {
        /* set data centric same as LNAS operation */
        TAF_SDC_SetUeUsageSetting(TAF_SDC_UE_USAGE_DATA_CENTRIC);

        return;
    }

    TAF_SDC_SetUeUsageSetting((TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8)(stUeCentric.enUeCenter));

    return;
}


VOS_VOID TAF_SDC_InitMsSysCfgInfo(TAF_SDC_MS_SYS_CFG_INFO_STRU *pstMsSysCfgInfo)
{
    TAF_SDC_InitRptCtrlInfo();

    TAF_SDC_InitUssdCfgInfo();

    TAF_SDC_InitAppCfgSupportType();

    TAF_SDC_InitPlmnExactlyCompareFlg();
    TAF_SDC_InitRefreshAllFileRestartFlag();

    TAF_SDC_InitDsdaPlmnSearchEnhancedCfg();

    TAF_SDC_InitUeUsageSetting();

#if (FEATURE_ON == FEATURE_LTE)
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = TAF_SDC_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[0]= TAF_SDC_SYS_MODE_LTE;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[1]= TAF_SDC_SYS_MODE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[2]= TAF_SDC_SYS_MODE_GSM;
#else
    pstMsSysCfgInfo->stPrioRatList.ucRatNum     = TAF_SDC_MAX_RAT_NUM;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[0]= TAF_SDC_SYS_MODE_WCDMA;
    pstMsSysCfgInfo->stPrioRatList.aenRatPrio[1]= TAF_SDC_SYS_MODE_GSM;
#endif

    pstMsSysCfgInfo->stNonnormalRegStatusMergeCfg.ucMergeFlg = VOS_TRUE;

    return;
}



VOS_VOID TAF_SDC_InitMsCfgInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_MS_CFG_INFO_STRU            *pstMsCfgInfo
)
{
    TAF_SDC_InitMsCapInfo(enInitType, &(pstMsCfgInfo->stMsCapInfo));

    TAF_SDC_InitMsSysCfgInfo(&pstMsCfgInfo->stMsSysCfgInfo);
    return;
}


VOS_VOID TAF_SDC_Init3gppSysInfo(TAF_SDC_3GPP_SYS_INFO_STRU *pst3gppSysInfo)
{
    pst3gppSysInfo->stPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
    pst3gppSysInfo->stPlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    pst3gppSysInfo->ucRac          = TAF_SDC_RAC_INVALID;
    pst3gppSysInfo->usLac          = TAF_SDC_LAC_INVALID;
    pst3gppSysInfo->ulCellId       = TAF_SDC_CELLID_INVALID;
    pst3gppSysInfo->ucRoamFlag     = VOS_FALSE;
    pst3gppSysInfo->ucCampOnFlg    = VOS_FALSE;

    TAF_SDC_Set3GppRfAvailFlag(VOS_TRUE);

    pst3gppSysInfo->enLmmAccessType   = TAF_SDC_LMM_ACCESS_TYPE_BUTT;

}


VOS_VOID TAF_SDC_Init1xSysInfo(
    TAF_SDC_1X_SYS_INFO_STRU           *pst1xSysInfo
)
{
    PS_MEM_SET(pst1xSysInfo, 0x0, sizeof(TAF_SDC_1X_SYS_INFO_STRU));

    pst1xSysInfo->lSid                = MMA_INVALID_SID;
    pst1xSysInfo->lNid                = MMA_INVALID_NID;

    pst1xSysInfo->uc1xRfAvailFlg      = VOS_TRUE;

    /* 需要将一些特性的参数，设置成无效值 */
    pst1xSysInfo->stServiceInfo.ulMcc = (VOS_UINT32)MMA_INVALID_MCC;
    pst1xSysInfo->stServiceInfo.usMnc = (VOS_UINT16)MMA_INVALID_MNC;
    pst1xSysInfo->ucRoamingInd        = TAF_SDC_SYS_ROAMING_STATUS_OFF;

    pst1xSysInfo->ulIsInEmcCallBack   = VOS_FALSE;
    pst1xSysInfo->ucIsEmcCallExistFlg = VOS_FALSE;

    pst1xSysInfo->enRegInfoIncl         = PS_FALSE;
    pst1xSysInfo->enBaseStationInfoIncl = PS_FALSE;
    pst1xSysInfo->enServiceInfoIncl     = PS_FALSE;
}


VOS_VOID TAF_SDC_InitHrpdSysInfo(
    TAF_SDC_HRPD_SYS_INFO_STRU         *pstHrpdSysInfo
)
{
    PS_MEM_SET(pstHrpdSysInfo, 0x0, sizeof(TAF_SDC_HRPD_SYS_INFO_STRU));

    pstHrpdSysInfo->ucHrpdRfAvailFlg = VOS_TRUE;


    pstHrpdSysInfo->ucSessionStatus  = HRPD_SESSION_STATUS_CLOSE;

    pstHrpdSysInfo->ulMcc            = (VOS_UINT32)MMA_INVALID_MCC;

}




VOS_VOID TAF_SDC_InitCsDomainInfo(TAF_SDC_CS_DOMAIN_INFO_STRU *pstCsDomainInfo)
{
    pstCsDomainInfo->enCsRegStatus                         = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstCsDomainInfo->enCsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* 小区受限类型默认需要设置为不受限,否则设置为BUTT时RIL层认为受限 */
    pstCsDomainInfo->stCsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;

    pstCsDomainInfo->stCsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictRegister  = VOS_FALSE;

    pstCsDomainInfo->ucSimCsRegStatus                      = VOS_FALSE;

    TAF_SDC_SetCsAttachAllowFlg(VOS_FALSE);
    return;
}


VOS_VOID TAF_SDC_InitPsDomainInfo(TAF_SDC_PS_DOMAIN_INFO_STRU *pstPsDomainInfo)
{
    pstPsDomainInfo->enPsRegStatus                         = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstPsDomainInfo->enPsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* 小区受限类型默认需要设置为不受限,否则设置为BUTT时RIL层认为受限 */
    pstPsDomainInfo->stPsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;

    pstPsDomainInfo->stPsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictRegister  = VOS_FALSE;
    pstPsDomainInfo->ucSimPsRegStatus                      = VOS_FALSE;

    TAF_SDC_SetPsAttachAllowFlg(VOS_FALSE);

    return;
}


VOS_VOID TAF_SDC_InitGuNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstGuNwCapInfo
)
{
    /* 初始化网络的能力信息 */
    PS_MEM_SET(pstGuNwCapInfo, 0, sizeof(TAF_SDC_NETWORK_CAP_INFO_STRU));
    pstGuNwCapInfo->enNwImsVoCap = TAF_SDC_NW_IMS_VOICE_NOT_SUPPORTED;
    pstGuNwCapInfo->enNwEmcBsCap = TAF_SDC_NW_EMC_BS_NOT_SUPPORTED;
    pstGuNwCapInfo->enLteCsCap   = TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED;

    return;
}


VOS_VOID TAF_SDC_InitLteNwCapInfo(
    TAF_SDC_NETWORK_CAP_INFO_STRU *pstLteNwCapInfo
)
{
    /* 初始化网络的能力信息 */
    PS_MEM_SET(pstLteNwCapInfo, 0, sizeof(TAF_SDC_NETWORK_CAP_INFO_STRU));
    pstLteNwCapInfo->enNwImsVoCap = TAF_SDC_NW_IMS_VOICE_NOT_SUPPORTED;
    pstLteNwCapInfo->enNwEmcBsCap = TAF_SDC_NW_EMC_BS_NOT_SUPPORTED;
    pstLteNwCapInfo->enLteCsCap   = TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED;

    return;
}



VOS_VOID TAF_SDC_InitNetWorkInfo(TAF_SDC_NETWORK_INFO_STRU *pstNetworkInfo)
{
    pstNetworkInfo->stSysInfo.enSysMode      = TAF_SDC_SYS_MODE_BUTT;
    pstNetworkInfo->stSysInfo.enSysSubMode   = TAF_SDC_SYS_SUBMODE_BUTT;
    pstNetworkInfo->stSysInfo.en1xCallState  = CDMA_1X_CALL_STATE_BUTT;

    TAF_SDC_Init3gppSysInfo(&pstNetworkInfo->stSysInfo.st3gppSysInfo);

    TAF_SDC_Init1xSysInfo(&pstNetworkInfo->stSysInfo.st1xSysInfo);

    TAF_SDC_InitHrpdSysInfo(&pstNetworkInfo->stSysInfo.stHrpdSysInfo);

    TAF_SDC_InitCsDomainInfo(&pstNetworkInfo->stCsDomainInfo);

    TAF_SDC_InitPsDomainInfo(&pstNetworkInfo->stPsDomainInfo);

    pstNetworkInfo->enServiceDomain = TAF_SDC_SERVICE_DOMAIN_BUTT;

    pstNetworkInfo->enReportSrvsta  = TAF_SDC_REPORT_SRVSTA_BUTT;

    TAF_SDC_InitGuNwCapInfo(&pstNetworkInfo->stGuNwCapInfo);
    TAF_SDC_InitLteNwCapInfo(&pstNetworkInfo->stLteNwCapInfo);


    PS_MEM_SET(pstNetworkInfo->aucReserved, 0, sizeof(pstNetworkInfo->aucReserved));


    TAF_SDC_SetImsNormalRegStatus(TAF_SDC_IMS_NORMAL_REG_STATUS_DEREG);

    TAF_SDC_InitNetworkRssiValue(&pstNetworkInfo->stSigQuaInfo);

    pstNetworkInfo->lSid = MMA_INVALID_SID;
    return;
}

VOS_VOID TAF_SDC_InitCsInfo(TAF_SDC_CS_INFO_STRU *pstCsInfo)
{

    PS_MEM_SET(pstCsInfo->aucReserved, 0, sizeof(pstCsInfo->aucReserved));
    pstCsInfo->ucCsServiceConnStatusFlag    = VOS_FALSE;

    return;
}



VOS_VOID TAF_SDC_InitPsInfo(TAF_SDC_PS_INFO_STRU *pstPsInfo)
{

    PS_MEM_SET(pstPsInfo->aucReserved, 0, sizeof(pstPsInfo->aucReserved));
    pstPsInfo->ucPsServiceConnStatusFlag    = VOS_FALSE;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID TAF_SDC_InitEpsInfo(TAF_SDC_EPS_INFO_STRU *pstEpsInfo)
{

    PS_MEM_SET(pstEpsInfo->aucReserved, 0, sizeof(pstEpsInfo->aucReserved));
    pstEpsInfo->ucEpsServiceConnStatusFlag    = VOS_FALSE;

    return;
}
#endif


VOS_VOID TAF_SDC_InitServiceInfo(
    TAF_SDC_SERVICE_INFO_STRU          *pstServiceInfo
)
{
    pstServiceInfo->stSmsInfo.ucCsSmsSrvExistFlg    = VOS_FALSE;
    pstServiceInfo->stSmsInfo.ucPsSmsSrvExistFlg    = VOS_FALSE;
    pstServiceInfo->stSmsInfo.ucImsSmsSrvExistFlg   = VOS_FALSE;
    pstServiceInfo->stSsInfo.ucCsSsSrvExistFlg      = VOS_FALSE;
    pstServiceInfo->stSsInfo.ucImsSsSrvExistFlg     = VOS_FALSE;
    PS_MEM_SET(pstServiceInfo->stSmsInfo.aucReserved, 0, sizeof(pstServiceInfo->stSmsInfo.aucReserved));
    PS_MEM_SET(pstServiceInfo->stSsInfo.aucReserved, 0, sizeof(pstServiceInfo->stSsInfo.aucReserved));

    TAF_SDC_InitCallInfo(&(pstServiceInfo->stCallInfo));

    PS_MEM_SET(&pstServiceInfo->stTrigPlmnSrcSrvType, 0, sizeof(pstServiceInfo->stTrigPlmnSrcSrvType));

    TAF_SDC_InitCsInfo(&(pstServiceInfo->stCsInfo));
    TAF_SDC_InitPsInfo(&(pstServiceInfo->stPsInfo));
#if (FEATURE_ON == FEATURE_LTE)
    TAF_SDC_InitEpsInfo(&(pstServiceInfo->stEpsInfo));
#endif

    return;
}


#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_SDC_InitECallNumber(
    TAF_SDC_ECALL_NUM_STRU             *pstECallNumber
)
{
    PS_MEM_SET(pstECallNumber, 0, sizeof(TAF_SDC_ECALL_NUM_STRU));

    pstECallNumber->ucNumType = 0x81;

    return;
}

#endif


VOS_VOID TAF_SDC_InitCallInfo(
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo
)
{

    /* 初始化CALL相关标志 */
    pstCallInfo->ucCsCallExistFlg                       = VOS_FALSE;
    pstCallInfo->ucImsCallExistFlg                      = VOS_FALSE;

    /* SRVCC标志管理移到到CALL模块*/

    /* 初始化MM相关紧急呼号码列表 */
    PS_MEM_SET(&(pstCallInfo->stMmCallEmerNumList), 0, sizeof(TAF_SDC_MM_EMERGENCY_LIST_STRU));
    pstCallInfo->stMmCallEmerNumList.ulMcc              = TAF_SDC_INVALID_MCC;
    pstCallInfo->stMmCallEmerNumList.ucEmergencyNumber  = 0;

    /* 根据NV项en_NV_Item_CUSTOM_ECC_NUM_LIST，初始化APP定制紧急呼号码列表 */
    PS_MEM_SET(&(pstCallInfo->stCustomCallEccNumCtx), 0, sizeof(TAF_SDC_CUSTOM_ECC_CTX_STRU));
    TAF_SDC_ReadCustomEccNumListNvim();


    return;
}


VOS_VOID TAF_SDC_InitPhoneInfo(
    TAF_SDC_PHONE_INFO_STRU            *pstPhInfo
)
{
    PS_MEM_SET(pstPhInfo, 0, sizeof(TAF_SDC_PHONE_INFO_STRU));

    pstPhInfo->enPhMode = TAF_SDC_PHONE_MODE_MINI;

    pstPhInfo->enImsSwitchState = TAF_SDC_IMS_SWITCH_STATE_OFF;

    PS_MEM_SET(pstPhInfo->stHardWareInfo.aucMeId, 0xFF, sizeof(VOS_UINT8) * NAS_OM_MMA_MEID_OCTET_NUM);
    pstPhInfo->stHardWareInfo.ulEsn          = 0xFFFFFFFF;
}



VOS_VOID TAF_SDC_InitRegReportStatus(
    TAF_SDC_REG_REPORT_STATUS_STRU     *pstRegReportStatus
)
{
    PS_MEM_SET(pstRegReportStatus, 0, sizeof(TAF_SDC_REG_REPORT_STATUS_STRU));

    pstRegReportStatus->enCregType  = TAF_SDC_CREG_TYPE_BUTT;
    pstRegReportStatus->enCgregType = TAF_SDC_CGREG_TYPE_BUTT;
    pstRegReportStatus->enCeregType = TAF_SDC_CEREG_TYPE_BUTT;
}


VOS_VOID TAF_SDC_ReadCustomEccNumListNvim(VOS_VOID)
{
    MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU   stCustomEccNumList;
    VOS_UINT8                               i;
    TAF_SDC_CALL_INFO_STRU                 *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();


    PS_MEM_SET(&stCustomEccNumList, 0x00, sizeof(stCustomEccNumList));

    /* 读取APP定制紧急呼列表NV */
    if (NV_OK != NV_Read(en_NV_Item_CUSTOM_ECC_NUM_LIST,
                         &stCustomEccNumList,
                         sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU)))
    {
        return;
    }

    /* 如果列表中保存的个数为无效值 */
    if ( stCustomEccNumList.ucEccNumCount > TAF_SDC_MAX_CUSTOM_ECC_NUM)
    {
        return;
    }


    /* 根据NV项的值赋值到全局变量中 */
    pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.ucEccNumCount
        = stCustomEccNumList.ucEccNumCount;

    /* 将NV读取的内容保存在全局变量中 */
    for (i = 0; i < stCustomEccNumList.ucEccNumCount; i++)
    {
        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ucCategory
            = stCustomEccNumList.astCustomEccNumList[i].ucCategory;

        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent
            = stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent;

        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ulMcc
            = stCustomEccNumList.astCustomEccNumList[i].ulMcc;

        pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen
            = stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen;

        (VOS_VOID)VOS_MemCpy(pstCallInfo->stCustomCallEccNumCtx.stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen);
    }

    return;
}




VOS_VOID TAF_SDC_InitMsIdentity(TAF_SDC_SIM_MS_IDENTITY_STRU *pstMsIdentity)
{
    VOS_UINT32                          i;

    PS_MEM_SET(pstMsIdentity, 0, sizeof(TAF_SDC_SIM_MS_IDENTITY_STRU));

    for ( i = 0 ; i < TAF_SDC_MAX_IMSI_LEN; i++ )
    {
        pstMsIdentity->aucImsi[i]      = TAF_SDC_IMSI_INVALID;

		pstMsIdentity->aucLastImsi[i]  = TAF_SDC_IMSI_INVALID;
	}

    return;
}


VOS_VOID TAF_SDC_InitSimStatus(TAF_SDC_SIM_STATUS_STRU *pstSimStatus)
{
    PS_MEM_SET(pstSimStatus, 0, sizeof(TAF_SDC_SIM_STATUS_STRU));

    pstSimStatus->enSimStatus = TAF_SDC_USIM_STATUS_BUTT;
    return;
}



VOS_VOID TAF_SDC_InitSimInfo(TAF_SDC_USIM_INFO_STRU *pstSimInfo)
{
    TAF_SDC_InitSimStatus(&pstSimInfo->stUsimStatus);

    TAF_SDC_InitMsIdentity(&pstSimInfo->stMsIdentity);

    pstSimInfo->enUsimType = TAF_SDC_SIM_TYPE_BUTT;

#if (FEATURE_ON == FEATURE_ECALL)
    TAF_SDC_SetCurCallMode(TAF_SDC_CALL_MODE_BUTT);
#endif

    return;
}


VOS_VOID TAF_SDC_InitCsimInfo(
    TAF_SDC_CSIM_INFO_STRU             *pstCsimInfo
)
{
    TAF_SDC_InitSimStatus(&pstCsimInfo->stCsimStatus);

    TAF_SDC_InitMsIdentity(&pstCsimInfo->stMsIdentity);

    pstCsimInfo->enCsimType = TAF_SDC_SIM_TYPE_BUTT;

    PS_MEM_SET(pstCsimInfo->aucRuimid, 0xff, TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT);

    return;
}


VOS_VOID TAF_SDC_InitCtx(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    TAF_SDC_CTX_STRU                    *pstSdcCtx
)
{
    TAF_SDC_InitMsCfgInfo(enInitType, &pstSdcCtx->stMsCfgInfo);

    TAF_SDC_InitNetWorkInfo(&pstSdcCtx->stNetworkInfo);

    TAF_SDC_InitSimInfo(&pstSdcCtx->stSimInfo.stUsimInfo);

    TAF_SDC_InitCsimInfo(&(pstSdcCtx->stSimInfo.stCsimInfo));

    TAF_SDC_InitServiceInfo(&pstSdcCtx->stServiceInfo);

#if (FEATURE_ON == FEATURE_PTM)
    TAF_SDC_InitErrLogInfo(&pstSdcCtx->stErrlogInfo);
#endif

    TAF_SDC_InitPhoneInfo(&pstSdcCtx->stPhoneInfo);

    TAF_SDC_InitRegReportStatus(&pstSdcCtx->stRegReportStatus);

    TAF_SDC_InitAppNetwork_Info(&pstSdcCtx->stAppNetworkInfo);

    TAF_SDC_InitEnhancedOperatorNameInfo(enInitType, &pstSdcCtx->stEnhancedOperatorNameInfo);

    return;
}


VOS_VOID TAF_SDC_InitCurcRptCtrlInfo(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl = VOS_NULL_PTR;
    NVIM_PRIVATE_CMD_STATUS_RPT_STRU        stNvimCmdRptCtrl;
    VOS_UINT32                              ulLength;

    ulLength = 0;

    /* 读取^CURC命令对应的NV项到全局变量 */
    stNvimCmdRptCtrl.ucStatus                     = VOS_FALSE;
    stNvimCmdRptCtrl.ucStatusRptGeneralControl    = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT;

    pstCurcRptCtrl = TAF_SDC_GetCurcRptCtrl();
    (VOS_VOID)NV_GetLength(en_NV_Item_PRIVATE_CMD_STATUS_RPT, &ulLength);

    if(NV_OK != NV_Read(en_NV_Item_PRIVATE_CMD_STATUS_RPT,
                          &stNvimCmdRptCtrl,
                          ulLength))
    {
        pstCurcRptCtrl->enStatusRptGeneralControl = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT;
        PS_MEM_SET(pstCurcRptCtrl->aucRptCfg, 0xFF, TAF_SDC_RPT_CFG_MAX_SIZE);
    }
    else
    {
        if( (VOS_TRUE == stNvimCmdRptCtrl.ucStatus)
         && (VOS_FALSE == stNvimCmdRptCtrl.ucStatusRptGeneralControl) )
        {
            pstCurcRptCtrl->enStatusRptGeneralControl = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_NO_REPORT;
            PS_MEM_SET(pstCurcRptCtrl->aucRptCfg, 0x00, TAF_SDC_RPT_CFG_MAX_SIZE);
        }
        else
        {
            pstCurcRptCtrl->enStatusRptGeneralControl = TAF_SDC_STATUS_RPT_GENERAL_CONTROL_TYPE_REPORT;
            PS_MEM_SET(pstCurcRptCtrl->aucRptCfg, 0xFF, TAF_SDC_RPT_CFG_MAX_SIZE);
        }
    }
}


VOS_VOID TAF_SDC_InitUnsolicitedRptCtrlInfo(VOS_VOID)
{
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    /* 默认为主动上报全打开 */
    PS_MEM_SET(pstUnsolicitedRptCtrl->aucRptCfg, 0xFF, TAF_SDC_RPT_CFG_MAX_SIZE);

    /* CREG/CGREG/CEREG关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CREG, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CGREG, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CEREG, VOS_FALSE);

    /* CTZR关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZV, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZE, VOS_FALSE);

    /* CUSD关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUSD, VOS_FALSE);

    /* CUUS1关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1I, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1U, VOS_FALSE);

    /* CSSN关闭 */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSI, VOS_FALSE);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSU, VOS_FALSE);

    /* 流量上报初始值通过读NV en_NV_Item_DSFLOW_REPORT获取 */

    /* CERSSI上报初始值通过读en_NV_Item_CELL_SIGN_REPORT_CFG获取 */
    TAF_SDC_ReadCellSignReportCfgNV();
    return;
}


VOS_VOID TAF_SDC_ReadEnhancedOperNameServiceCfgNvim( VOS_VOID )
{
    TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU            stOperNameCfg;
    VOS_UINT32                                              ulLength;
    TAF_SDC_OPER_NAME_TYPE_PRIO_STRU                       *pstOperNamePrio = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    VOS_UINT8                                               ucOperNamePrioNum;
    VOS_CHAR                                                cWildCard;

    pstOperNamePrio   = TAF_SDC_GetOperNamePrio();
    PS_MEM_SET(&stOperNameCfg, 0x00, sizeof(stOperNameCfg));
    ulLength          = 0;
    ucOperNamePrioNum = 0;

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG, &ulLength);

    if (ulLength > sizeof(TAF_NVIM_ENHANCED_OPER_NAME_SERVICE_CFG_STRU))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadEnhancedOperNameServiceCfgNvim:read en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG len failed");
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG,
                         &stOperNameCfg, ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadEnhancedOperNameServiceCfgNvim:read en_NV_Item_ENHANCED_OPERATOR_NAME_SRV_CFG failed");
        return;
    }

    pstOperNamePrio->ucOperNamePrioNum = stOperNameCfg.ucOperNameServicePrioNum;

    if (pstOperNamePrio->ucOperNamePrioNum > TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM)
    {
        pstOperNamePrio->ucOperNamePrioNum = TAF_NVIM_MAX_OPER_NAME_SERVICE_PRIO_NUM;
    }

    for (ucIndex = 0; ucIndex < pstOperNamePrio->ucOperNamePrioNum; ucIndex++)
    {
        if (stOperNameCfg.aucOperNameSerivcePrio[ucIndex] >= TAF_SDC_OPER_NAME_TYPE_BUTT)
        {
            continue;
        }

        pstOperNamePrio->aucOperNameTypePrio[ucOperNamePrioNum] = stOperNameCfg.aucOperNameSerivcePrio[ucIndex];
        ucOperNamePrioNum++;
    }

    pstOperNamePrio->ucOperNamePrioNum = ucOperNamePrioNum;

    /* plmn比较支持通配符且通配符为a-f,则更新全局变量 */
    if (VOS_FALSE == stOperNameCfg.ucPlmnCompareSupportWildCardFlag)
    {
        return;
    }

    /* 数字不能做为通配符 */
    if (stOperNameCfg.ucWildCard <= 0x09)
    {
        return;
    }

    /* nv项配置0xA代表字符'A',0xA代表字符'B',0xC代表字符'C',0xD代表字符'D',
       0xE代表字符'E',0xF代表字符'F',其他值认为非法 */
    if ((0x0A == stOperNameCfg.ucWildCard)
     || (0x0B == stOperNameCfg.ucWildCard)
     || (0x0C == stOperNameCfg.ucWildCard)
     || (0x0D == stOperNameCfg.ucWildCard)
     || (0x0E == stOperNameCfg.ucWildCard)
     || (0x0F == stOperNameCfg.ucWildCard))
    {
        cWildCard = (VOS_CHAR)(stOperNameCfg.ucWildCard + 0x37);
        TAF_SDC_SetPlmnCompareWildCard(cWildCard);
        return;
    }

    return;
}


VOS_VOID TAF_SDC_ReadCustomOperNameInfoNvim(VOS_VOID)
{
    VOS_UINT16                          usIndex;
    NAS_MMA_NVIM_OPERATOR_NAME_STRU     stNvCustomOperName;
    VOS_UINT32                          ulNvLen;
    TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU *pstCustomOperNameInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucNvDataIndex = VOS_NULL_PTR;

    pstCustomOperNameInfo = TAF_SDC_GetCustomOperNameInfo();
    ulNvLen               = 0;
    PS_MEM_SET(&stNvCustomOperName, 0x00, sizeof(stNvCustomOperName));

    (VOS_VOID)NV_GetLength(en_NV_Item_HUAWEI_NW_OPL_NAME_CUSTOMIZED, &ulNvLen);

    if ( ulNvLen > sizeof(NAS_MMA_NVIM_OPERATOR_NAME_STRU))
    {
        return;
    }

    if (NV_OK !=  NV_Read(en_NV_Item_HUAWEI_NW_OPL_NAME_CUSTOMIZED,(VOS_VOID *)(&stNvCustomOperName),  ulNvLen))
    {
        return;
    }

    if( NV_ITEM_DEACTIVE == stNvCustomOperName.aucRcvData[0])
    {
        return;
    }

    pucNvDataIndex = stNvCustomOperName.aucRcvData + 4;

    for ( usIndex = 0; usIndex < TAF_NVIM_STORED_OPER_NAME_NUM; usIndex++ )
    {
        PS_MEM_CPY(&pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorPlmnId,
                   pucNvDataIndex, NV_ITEM_PLMN_ID_LEN);

        TAF_SDC_ConvertPlmnId2NasStyle(&pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorPlmnId);
        pucNvDataIndex += NV_ITEM_PLMN_ID_LEN;

        PS_MEM_CPY(pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorNameShort.aucOperatorName,
                   pucNvDataIndex, NV_ITEM_OPER_NAME_SHORT);

        pucNvDataIndex += NV_ITEM_OPER_NAME_SHORT;

        PS_MEM_CPY(pstCustomOperNameInfo->astCustomOperName[usIndex].stOperatorNameLong.aucOperatorName,
                   pucNvDataIndex, NV_ITEM_OPER_NAME_LONG);

        pucNvDataIndex += NV_ITEM_OPER_NAME_LONG;
    }

    return;
}




VOS_VOID TAF_SDC_ReadCellSignReportCfgNV( VOS_VOID )
{
    TAF_SDC_CELL_SIGN_REPORT_CFG_STRU   stCellSignReportCfg;
    VOS_UINT32                          ulCerssiRptFlg;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stCellSignReportCfg, 0x0, sizeof(stCellSignReportCfg));
    (VOS_VOID)NV_GetLength(en_NV_Item_CELL_SIGN_REPORT_CFG, &ulLength);
    if (ulLength > sizeof(stCellSignReportCfg))
    {
        return;
    }
    if(NV_OK != NV_Read(en_NV_Item_CELL_SIGN_REPORT_CFG,
                          &stCellSignReportCfg,
                          ulLength))
    {
         TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadCellSignReportCfgNV:read en_NV_Item_CELL_SIGN_REPORT_CFG failed");
         return;
    }

    ulCerssiRptFlg  = VOS_TRUE;

    /* 门限值为无效值，不上报 */
    if (TAF_SDC_MAX_SIGN_THRESHOLD < stCellSignReportCfg.ucSignThreshold)
    {
        ulCerssiRptFlg  = VOS_FALSE;
    }

    /* 门限值为0，不上报 */
    if (0 == stCellSignReportCfg.ucSignThreshold)
    {
        ulCerssiRptFlg  = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CERSSI, ulCerssiRptFlg);

    return;
}



VOS_VOID    TAF_SDC_SetXsmsCallExistFlg(
    VOS_UINT8                           ucIsXsmsCallExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucIsXsmsCallExistFlg = ucIsXsmsCallExistFlg;

    return;
}


VOS_UINT8 TAF_SDC_GetXsmsCallExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucIsXsmsCallExistFlg;
}


VOS_VOID    TAF_SDC_SetCsCallExistFlg(
    VOS_UINT8                           ucCsCallExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsCallExistFlg = ucCsCallExistFlg;

    return;
}


VOS_VOID    TAF_SDC_SetCsEccExistFlg(
    VOS_UINT8                           ucCsEccExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsEccExistFlg = ucCsEccExistFlg;
    return;
}


VOS_UINT8 TAF_SDC_GetCsEccExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsEccExistFlg;
}


VOS_VOID TAF_SDC_SetCsServiceConnStatusFlag(
    VOS_UINT8                           ucCsServiceConnStatusFlag
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCsInfo.ucCsServiceConnStatusFlag = ucCsServiceConnStatusFlag;

    return;
}

/*****************************************************************************
 函 数 名  : TAF_SDC_GetTrigPlmnSearchSrvType
 功能描述  : 获取业务触发搜网业务类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 业务类型
 调用函数  :
 被调函数  :

 修改历史     :

*****************************************************************************/
TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION *TAF_SDC_GetTrigPlmnSearchSrvType(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stTrigPlmnSrcSrvType);
}




VOS_UINT8 TAF_SDC_GetCsServiceConnStatusFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCsInfo.ucCsServiceConnStatusFlag;
}




VOS_UINT8   TAF_SDC_GetCsCallExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucCsCallExistFlg;
}


VOS_VOID    TAF_SDC_SetImsCallExistFlg(
    VOS_UINT8                           ucImsCallExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucImsCallExistFlg = ucImsCallExistFlg;

    return;
}


VOS_UINT8   TAF_SDC_GetImsCallExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.ucImsCallExistFlg;
}

/* SRVCC移到CALL模块自己维护管理*/


TAF_SDC_CALL_INFO_STRU* TAF_SDC_GetCallInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo);
}



VOS_VOID TAF_SDC_SetMmCallEmerNumList(
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList
)
{
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();

    PS_MEM_CPY(&(pstCallInfo->stMmCallEmerNumList), pstMmCallEmerNumList, sizeof(TAF_SDC_MM_EMERGENCY_LIST_STRU));

    return;
}


TAF_SDC_MM_EMERGENCY_LIST_STRU* TAF_SDC_GetMmCallEmerNumList(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stMmCallEmerNumList);
}


VOS_VOID TAF_SDC_SetCustomCallEccNumCtx(
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEccNumCtx
)
{
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();

    PS_MEM_CPY(&(pstCallInfo->stCustomCallEccNumCtx), pstCustomCallEccNumCtx, sizeof(TAF_SDC_CUSTOM_ECC_CTX_STRU));

    return;
}


TAF_SDC_CUSTOM_ECC_CTX_STRU* TAF_SDC_GetCustomCallEccNumCtx(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stCustomCallEccNumCtx);
}



VOS_CHAR** TAF_SDC_GetCallEmerNumsNoUsimTblAddr(VOS_VOID)
{
    return g_aucTafSdcCallEmerNumsNoUsim;
}


VOS_CHAR** TAF_SDC_GetCallEmerNumsWithUsimTblAddr(VOS_VOID)
{
    return g_aucTafSdcCallEmerNumsWithUsim;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_CHAR** TAF_SDC_GetCdmaCallEmcNumsAddr(VOS_VOID)
{
    return g_acTafSdcCdmaCallEmcNums;
}
#endif

VOS_VOID  TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8  ucUtranSkipWPlmnSearchFlag)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag = ucUtranSkipWPlmnSearchFlag;
    return;
}



VOS_UINT8  TAF_SDC_GetUtranSkipWPlmnSearchFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stDsdaPlmnSearchEnhancedCfg.ucUtranSkipWPlmnSearchFlag;
}



VOS_VOID TAF_SDC_InitDsdaPlmnSearchEnhancedCfg(VOS_VOID)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU                   stDsdaPlmnSearchEnhancedCfg;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stDsdaPlmnSearchEnhancedCfg, 0x00, sizeof(stDsdaPlmnSearchEnhancedCfg));

    TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_FALSE);

    /* 先获取NV的长度 */
    (VOS_VOID)NV_GetLength(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG, &ulLength);

    if (ulLength > sizeof(NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU))
    {
        return;
    }

    /* 读NV失败 */
    if (NV_OK != NV_Read(en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG,
                         &stDsdaPlmnSearchEnhancedCfg, ulLength))
    {
        return;
    }

    if (VOS_TRUE == (stDsdaPlmnSearchEnhancedCfg.usSolutionMask & 0x0001))
    {
         TAF_SDC_SetUtranSkipWPlmnSearchFlag(VOS_TRUE);
    }
#endif

    return;
}




VOS_VOID    TAF_SDC_SetUssdTransMode(
    VOS_UINT8                           ucTransMode
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucUssdTransMode = ucTransMode;

    return;
}


VOS_UINT8   TAF_SDC_GetUssdTransMode(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucUssdTransMode;
}


VOS_VOID    TAF_SDC_Set7BitToAssicTableType(
    VOS_UINT8                           ucType
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucAlphaTransMode = ucType;

    return;
}


VOS_UINT8   TAF_SDC_Get7BitToAssicTableType(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stUssdCfg.ucAlphaTransMode;
}


VOS_UINT8*   TAF_SDC_GetCurr7BitToAsciiTableAddr(VOS_VOID)
{
    if (TAF_SDC_ALPHA_TO_ASCII_TRAN_TABLE_TME == TAF_SDC_Get7BitToAssicTableType())
    {
        return g_aucTafSdcTme7BitToAsciiTbl;
    }
    else
    {
        return g_aucTafSdcDef7BitToAsciiTbl;
    }
}



VOS_VOID TAF_SDC_Get3GppCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
)
{
    VOS_UINT32                          ulPos;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_3GPP_SYS_INFO_STRU         *pst3gppSysInfo = VOS_NULL_PTR;
    TAF_SDC_SYS_INFO_STRU              *pstSysInfo = VOS_NULL_PTR;

    pst3gppSysInfo = TAF_SDC_Get3gppSysInfo();
    pstSysInfo     = TAF_SDC_GetSysInfo();

    ulPos = 0;

    aucLai[ulPos]  = (VOS_UINT8)(0x0000000F & pst3gppSysInfo->stPlmnId.ulMcc);
    aucLai[ulPos] |= (VOS_UINT8)((0x00000F00 & pst3gppSysInfo->stPlmnId.ulMcc) >> 4);
    ulPos++;

    aucLai[ulPos]  = (VOS_UINT8)((0x000F0000 & pst3gppSysInfo->stPlmnId.ulMcc) >> 16);
    aucLai[ulPos] |= (VOS_UINT8)((0x000F0000 & pst3gppSysInfo->stPlmnId.ulMnc) >> 12);
    ulPos++;

    aucLai[ulPos]  = (VOS_UINT8)(0x0000000F & pst3gppSysInfo->stPlmnId.ulMnc);
    aucLai[ulPos] |= (VOS_UINT8)((0x00000F00 & pst3gppSysInfo->stPlmnId.ulMnc) >> 4);
    ulPos++;

    aucLai[ulPos]  = (VOS_UINT8)((pst3gppSysInfo->usLac & 0xff00) >> 8);
    ulPos++;
    aucLai[ulPos]  = (VOS_UINT8)(pst3gppSysInfo->usLac & 0x00ff);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((pst3gppSysInfo->ulCellId >> 8) & 0xff);
    ulPos++;
    aucLai[ulPos] = (VOS_UINT8)(pst3gppSysInfo->ulCellId & 0xff);
    ulPos++;

    if (TAF_SDC_SYS_MODE_GSM != pstSysInfo->enSysMode)
    {
        aucLai[ulPos] = (VOS_UINT8)((pst3gppSysInfo->ulCellId >> 24) & 0xff);
        ulPos++;
        aucLai[ulPos] = (VOS_UINT8)((pst3gppSysInfo->ulCellId >> 16) & 0xff);
        ulPos++;
    }

    *pulLaiLen = ulPos;

    /*获取MM层注册状态*/
    enCsRegStatus = TAF_SDC_GetCsRegStatus();
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK != enCsRegStatus)
     && (TAF_SDC_REG_REGISTERED_ROAM != enCsRegStatus))
    {
        PS_MEM_SET(aucLai, (VOS_CHAR)0xff, ulPos);
    }

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_SDC_Get3Gpp2CurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
)
{
    /***********************************************************************
     Description                      Length(Byte)
     MCC                              2
     IMSI_11_12                       1
     SID                              2
     NID                              2
     BASE_ID                          2
     BASE_LAT                         3
     BASE_LONG                        3
     ************************************************************************/
    VOS_UINT32                          ulPos;
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulMcc;
    VOS_UINT8                           ucImsi_11_12;

    ulPos = 0;
    pstSdc1xSysInfo   = TAF_SDC_Get1xSysInfo();

    /* MCC */
    ulMcc = TAF_STD_TransformBcdMccToDeciDigit(pstSdc1xSysInfo->stServiceInfo.ulMcc);
    aucLai[ulPos]  = TAF_SDC_GET_STK_MCC(ulMcc) & 0x00FF;
    ulPos++;

    aucLai[ulPos]  = (TAF_SDC_GET_STK_MCC(ulMcc) & 0xFF00) >> 8;
    ulPos++;

    /* IMSI_11_12*/
    ucImsi_11_12 = TAF_STD_TransformBcdImsi1112ToDeciDigit(pstSdc1xSysInfo->stServiceInfo.usImsi11_12);
    aucLai[ulPos]  = (VOS_UINT8)TAF_SDC_GET_STK_MNC(ucImsi_11_12);
    ulPos++;

    /* SID */
    aucLai[ulPos] = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->lSid);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->lSid) >> 8);
    ulPos++;

    /* NID */
    aucLai[ulPos] = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->lNid);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->lNid) >> 8);
    ulPos++;

    /* BASE_ID */
    aucLai[ulPos] = (VOS_UINT8)(0x00FF & pstSdc1xSysInfo->stBaseStationInfo.usBaseId);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0xFF00 & pstSdc1xSysInfo->stBaseStationInfo.usBaseId) >> 8);
    ulPos++;

    /* BASE_LAI */
    aucLai[ulPos] = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude) >> 8);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x00FF0000 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude) >> 16);
    ulPos++;

    /* BASE_LONG */
    aucLai[ulPos]  = (VOS_UINT8)(0x000000FF & pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x0000FF00 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude) >> 8);
    ulPos++;

    aucLai[ulPos] = (VOS_UINT8)((0x00FF0000 & pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude) >> 16);
    ulPos++;

    *pulLaiLen = ulPos;

}
#endif


VOS_VOID TAF_SDC_GetCurrentLai(
    VOS_UINT8                          *aucLai,
    VOS_UINT32                         *pulLaiLen
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* CDMA inside，并且当前是CL模式 */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        TAF_SDC_Get3Gpp2CurrentLai(aucLai, pulLaiLen);
    }
    else
    {
        TAF_SDC_Get3GppCurrentLai(aucLai, pulLaiLen);
    }
#else
    TAF_SDC_Get3GppCurrentLai(aucLai, pulLaiLen);
#endif
}





VOS_VOID    TAF_SDC_SetSvlteSupportFlag(
    VOS_UINT8                          ucSvlteSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.ucSvlteSupportFlag = ucSvlteSupportFlag;

    return;
}


VOS_UINT8   TAF_SDC_GetSvlteSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.ucSvlteSupportFlag;
}


VOS_VOID    TAF_SDC_SetCsSmsSrvExistFlg(
    VOS_UINT8                           ucCsSmsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucCsSmsSrvExistFlg = ucCsSmsSrvExistFlg;

    return;
}


VOS_UINT8   TAF_SDC_GetCsSmsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucCsSmsSrvExistFlg;
}


VOS_VOID TAF_SDC_SetPsSmsSrvExistFlg(
    VOS_UINT8                           ucPsSmsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucPsSmsSrvExistFlg = ucPsSmsSrvExistFlg;

    return;
}


VOS_UINT8 TAF_SDC_GetPsSmsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucPsSmsSrvExistFlg;
}


VOS_VOID TAF_SDC_SetImsSmsSrvExistFlg(
    VOS_UINT8                           ucImsSmsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucImsSmsSrvExistFlg = ucImsSmsSrvExistFlg;

    return;
}


VOS_UINT8 TAF_SDC_GetImsSmsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSmsInfo.ucImsSmsSrvExistFlg;
}



VOS_VOID    TAF_SDC_SetCsSsSrvExistFlg(
    VOS_UINT8                           ucCsSsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucCsSsSrvExistFlg = ucCsSsSrvExistFlg;

    return;
}


VOS_UINT8   TAF_SDC_GetCsSsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucCsSsSrvExistFlg;
}


VOS_VOID    TAF_SDC_SetImsSsSrvExistFlg(
    VOS_UINT8                           ucImsSsSrvExistFlg
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucImsSsSrvExistFlg = ucImsSsSrvExistFlg;

    return;
}


VOS_UINT8   TAF_SDC_GetImsSsSrvExistFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stSsInfo.ucImsSsSrvExistFlg;
}



VOS_VOID TAF_SDC_SetGsmImsSupportFlag(
    VOS_UINT8                          ucGsmImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag = ucGsmImsSupportFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetGsmImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucGsmImsSupportFlag;
}


VOS_VOID TAF_SDC_SetUtranImsSupportFlag(
    VOS_UINT8                          ucUtranImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag = ucUtranImsSupportFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetUtranImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucUtranImsSupportFlag;
}



VOS_VOID TAF_SDC_SetLteImsSupportFlag(
    VOS_UINT8                          ucLteImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag = ucLteImsSupportFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetLteImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteImsSupportFlag;
}


VOS_VOID TAF_SDC_SetAppCfgSupportType(
    VOS_UINT16                          usAppCfgSupportType
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.usAppCfgSupportType = usAppCfgSupportType;

    return;
}


VOS_UINT16 TAF_SDC_GetAppCfgSupportType(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.usAppCfgSupportType;
}


VOS_VOID TAF_SDC_SaveCsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
)
{
        VOS_UINT8                           ucSimType;

        switch (enCardType)
        {
            case USIMM_CARD_UIM:
                ucSimType = TAF_SDC_SIM_TYPE_UIM;
                break;

            case USIMM_CARD_CSIM:
                ucSimType = TAF_SDC_SIM_TYPE_CSIM;
                break;

            case USIMM_CARD_NOCARD:
            case USIMM_CARD_ISIM:
            default:

                ucSimType = TAF_SDC_SIM_TYPE_BUTT;
                break;
        }

        TAF_SDC_SetCsimType(ucSimType);

        return;
}


VOS_VOID TAF_SDC_SaveUsimCardType(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType
)
{
    VOS_UINT8                           ucSimType;

    switch (enCardType)
    {
        case USIMM_CARD_SIM:

            ucSimType = TAF_SDC_SIM_TYPE_SIM;
            break;

        case USIMM_CARD_USIM:

            ucSimType = TAF_SDC_SIM_TYPE_USIM;
            break;

        case USIMM_CARD_ROM_SIM:
            ucSimType = TAF_SDC_SIM_TYPE_ROM_SIM;
            break;

        case USIMM_CARD_NOCARD:
        case USIMM_CARD_ISIM:
        default:

            ucSimType = TAF_SDC_SIM_TYPE_BUTT;
            break;
    }

    TAF_SDC_SetUsimType(ucSimType);

    return;
}


VOS_VOID TAF_SDC_SaveUsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enUsimStatus
)
{
    switch ( enUsimStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_NO_PRESENT);
             return;

        case USIMM_CARD_SERVIC_UNAVAILABLE :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_UNVALID);
             return;

        case USIMM_CARD_SERVIC_SIM_PIN :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_SIM_PIN);
             return;

        case USIMM_CARD_SERVIC_SIM_PUK :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_SIM_PUK);
             return;

        case USIMM_CARD_SERVIC_NET_LCOK :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_NET_LCOK);
             return;

        case USIMM_CARD_SERVICE_IMSI_LOCK :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_IMSI_LCOK);
             return;

        case USIMM_CARD_SERVIC_AVAILABLE :
             TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_VALID);
             return;

        /* 异常处理 */
        default :
            TAF_WARNING_LOG(WUEPS_PID_MMA, "MMA_ChangeUsimStatus: USIM STATUS INVALID");

            /* 其他情况下认为卡状态有效 */
            TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_VALID);
            return ;
    }
}


VOS_VOID TAF_SDC_SaveCsimCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCsimStatus
)
{
    switch ( enCsimStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_NO_PRESENT);
             return;

        case USIMM_CARD_SERVIC_UNAVAILABLE :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_UNVALID);
             return;

        case USIMM_CARD_SERVIC_SIM_PIN :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_SIM_PIN);
             return;

        case USIMM_CARD_SERVIC_SIM_PUK :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_SIM_PUK);
             return;

        case USIMM_CARD_SERVIC_NET_LCOK :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_NET_LCOK);
             return;

        case USIMM_CARD_SERVICE_IMSI_LOCK :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_IMSI_LCOK);
             return;

        case USIMM_CARD_SERVIC_AVAILABLE :
             TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_VALID);
             return;

        /* 异常处理 */
        default :
            TAF_WARNING_LOG(WUEPS_PID_MMA, "MMA_ChangeUsimStatus: USIM STATUS INVALID");

            /* 其他情况下认为卡状态有效 */
            TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_VALID);
            return ;
    }
}



OM_RING_ID TAF_SDC_GetErrLogRingBufAddr(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.pstRingBuffer;
}


VOS_VOID TAF_SDC_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.pstRingBuffer = pRingBuffer;

    return;
}


VOS_UINT8 TAF_SDC_GetErrlogCtrlFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.ucErrLogCtrlFlag;
}


VOS_VOID TAF_SDC_SetErrlogCtrlFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.ucErrLogCtrlFlag = ucFlag;

    return;
}


VOS_UINT16 TAF_SDC_GetErrlogAlmLevel(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.usAlmLevel;
}


VOS_VOID TAF_SDC_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.usAlmLevel = usAlmLevel;

    return;
}


VOS_UINT32 TAF_SDC_GetErrlogOverflowCnt(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.ulOverflowCnt;
}


VOS_VOID TAF_SDC_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stBuffInfo.ulOverflowCnt = ulOverflowCnt;

    return;
}


VOS_UINT8 TAF_SDC_GetErrLogCsOosReportToAppFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucCsOosReportToAppFlag;
}


VOS_VOID TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucCsOosReportToAppFlag = ucFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetErrLogPsOosReportToAppFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucPsOosReportToAppFlag;
}


VOS_VOID TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucPsOosReportToAppFlag = ucFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetErrLogReportPowerOnBeginFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOnBeginFlag;
}


VOS_VOID TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOnBeginFlag = ucFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetErrLogReportPowerOffBeginFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOffBeginFlag;
}


VOS_VOID TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_UINT8 ucFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stOosInfo.ucReportPowerOffBeginFlag = ucFlag;

    return;
}

VOS_UINT8 TAF_SDC_GetErrLogImsCallFailFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo.ucImsCallFailFlag;
}

VOS_VOID TAF_SDC_SetErrLogImsCallFailFlag(
    VOS_UINT8                           ucImsCallFailFlag
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo.ucImsCallFailFlag = ucImsCallFailFlag;

    return;
}

VOS_UINT32 TAF_SDC_GetErrLogImsCallFailCause(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo.ulImsCallFailCause;
}

VOS_VOID TAF_SDC_SetErrLogImsCallFailCause(
    VOS_UINT32                          ulImsCallFailCause
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo.ulImsCallFailCause = ulImsCallFailCause;

    return;
}


VOS_VOID TAF_SDC_InitErrLogImsCallFailInfo(VOS_VOID)
{
    PS_MEM_SET(&(TAF_SDC_GetSdcCtx()->stErrlogInfo.stImsCallFailInfo),
               0,
               sizeof(NAS_ERR_LOG_IMS_CALL_FAIL_INFO_STRU));

    return;
}

VOS_UINT8 TAF_SDC_GetErrlogActiveRptFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpActiveRptFlag;
}


VOS_VOID TAF_SDC_SetErrlogActiveRptFlag(VOS_UINT8 ucActiveRptFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpActiveRptFlag = (ucActiveRptFlag & 0x01);
}


VOS_UINT8 TAF_SDC_GetErrlogRatSwitchRptFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpRatSwitchRptFlag;
}


VOS_VOID TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_UINT8 ucRatSwitchRptFlag)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stCtrlInfo.stErrLogRptCtrl.bitOpRatSwitchRptFlag = (ucRatSwitchRptFlag & 0x01);
}


VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticTime(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvStatisticTime;
}


VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticTime(
    VOS_UINT32                           ulStatisticTime
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvStatisticTime = ulStatisticTime;

    return;
}


VOS_UINT32 TAF_SDC_GetErrlogRatSwitchStatisticNum(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvSwitchNum;
}


VOS_VOID TAF_SDC_SetErrlogRatSwitchStatisticNum(
    VOS_UINT32                           ulSwitchNum
)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ulNvSwitchNum = ulSwitchNum;

    return;
}


VOS_UINT8 TAF_SDC_GetErrLogOldRatType(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ucOldRatType;
}


VOS_VOID TAF_SDC_SetErrLogOldRatType(VOS_UINT8 ucRatType)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.ucOldRatType = ucRatType;

    return;
}


OM_RING_ID TAF_SDC_GetRatSwitchRingBufAddr(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.pstRingBuffer;
}


VOS_VOID TAF_SDC_SetRatSwitchRingBufAddr(OM_RING_ID pRingBuffer)
{
    TAF_SDC_GetSdcCtx()->stErrlogInfo.stRatFrequentlySwitchInfo.pstRingBuffer = pRingBuffer;

    return;
}


VOS_VOID TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim(VOS_VOID)
{
    VOS_UINT32                                           ulResult;
    VOS_UINT32                                           ulLength;
    TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU        stRatFrequentlySwitchChrRptCfg;

    ulLength = 0;
    PS_MEM_SET(&stRatFrequentlySwitchChrRptCfg,
               0x00, sizeof(TAF_NV_RAT_FREQUENTLY_SWITCH_CHR_RPT_CFG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg, &ulLength);

    ulResult = NV_Read(en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg,
                       &stRatFrequentlySwitchChrRptCfg,
                       ulLength);

    if (NV_OK != ulResult)
    {
        TAF_SDC_SetErrlogRatSwitchStatisticTime(0);
        TAF_SDC_SetErrlogRatSwitchStatisticNum(0);
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim: read en_NV_Item_Rat_Frequently_Switch_Chr_Rpt_Cfg failed");

        return;
    }


    /* 从NV读取的频繁切换限定时间大于规定的最大值 */
    if (stRatFrequentlySwitchChrRptCfg.ulStatisticTime > NAS_ERR_LOG_MAX_RAT_SWITCH_STATISTIC_TIME)
    {
        stRatFrequentlySwitchChrRptCfg.ulStatisticTime = NAS_ERR_LOG_MAX_RAT_SWITCH_STATISTIC_TIME;
    }

    TAF_SDC_SetErrlogRatSwitchStatisticTime(stRatFrequentlySwitchChrRptCfg.ulStatisticTime);

    /* 从NV读取的频繁切换限定次数大于规定的最大值 */
    if (stRatFrequentlySwitchChrRptCfg.ulSwitchNum > NAS_ERR_LOG_MAX_RAT_SWITCH_RECORD_MUN)
    {
        stRatFrequentlySwitchChrRptCfg.ulSwitchNum = NAS_ERR_LOG_MAX_RAT_SWITCH_RECORD_MUN;
    }

    TAF_SDC_SetErrlogRatSwitchStatisticNum(stRatFrequentlySwitchChrRptCfg.ulSwitchNum);

    return;
}


VOS_VOID TAF_SDC_ReadErrlogCtrlInfoNvim(VOS_VOID)
{
    VOS_UINT8                           ucActiveRptFlag;
    VOS_UINT8                           ucRatSwitchRptFlag;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;
    NV_ID_ERR_LOG_CTRL_INFO_STRU        stErrorLogCtrlInfo;

    ulLength = 0;
    PS_MEM_SET(&stErrorLogCtrlInfo, 0x00, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_ErrLogCtrlInfo, &ulLength);

    ulResult = NV_Read(en_NV_Item_ErrLogCtrlInfo,
                       &stErrorLogCtrlInfo,
                       ulLength);

    if (ulResult == NV_OK)
    {
        TAF_SDC_SetErrlogCtrlFlag(stErrorLogCtrlInfo.ucAlmStatus);
        TAF_SDC_SetErrlogAlmLevel(stErrorLogCtrlInfo.ucAlmLevel);

        ucActiveRptFlag    = (stErrorLogCtrlInfo.aucReportBitMap[0] >> NAS_ERR_LOG_ACTIVE_RPT_FLAG_OFFSET) & 0x01;
        ucRatSwitchRptFlag = (stErrorLogCtrlInfo.aucReportBitMap[1] >> NAS_ERR_LOG_RAT_SWITCH_RPT_FLAG_OFFSET) & 0x01;

        TAF_SDC_SetErrlogActiveRptFlag(ucActiveRptFlag);
        TAF_SDC_SetErrlogRatSwitchRptFlag(ucRatSwitchRptFlag);
    }
    else
    {
        TAF_SDC_SetErrlogCtrlFlag(VOS_FALSE);
        TAF_SDC_SetErrlogAlmLevel(NAS_ERR_LOG_CTRL_LEVEL_CRITICAL);

        TAF_SDC_SetErrlogActiveRptFlag(VOS_FALSE);
        TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_FALSE);

        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_ReadErrlogCtrlInfoNvim:read en_NV_Item_ErrLogCtrlInfo failed");
    }

    /* 测试卡，则不开启该功能 */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        TAF_SDC_SetErrlogCtrlFlag(VOS_FALSE);
        TAF_SDC_SetErrlogActiveRptFlag(VOS_FALSE);
        TAF_SDC_SetErrlogRatSwitchRptFlag(VOS_FALSE);
    }

    return;
}

/*lint -e593 -e830*/


VOS_VOID TAF_SDC_InitErrLogInfo(
    TAF_SDC_ERRLOG_INFO_STRU           *pstErrLogInfo
)
{
#if (FEATURE_ON == FEATURE_PTM)
    VOS_CHAR                           *pbuffer;
    OM_RING_ID                          pRingbuffer;
#endif

    TAF_SDC_ReadErrlogCtrlInfoNvim();

    TAF_SDC_ReadRatFrequentlySwitchChrRptCfgNvim();

#if (FEATURE_ON == FEATURE_PTM)
    TAF_SDC_CreatRatSwitchRingBuf();
#endif

    TAF_SDC_SetErrLogOldRatType(TAF_PH_INFO_NONE_RAT);

    PS_MEM_SET(&pstErrLogInfo->stOosInfo,
               0x0,
               sizeof(TAF_SDC_ERRLOG_OOS_INFO_STRU));

    TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_FALSE);
    TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_FALSE);

    TAF_SDC_InitErrLogImsCallFailInfo();

#if (FEATURE_ON == FEATURE_PTM)
    /* 申请cache的动态内存 , 长度加1是因为读和写指针之间在写满时会相差一个字节 */
    pbuffer = (char *)PS_MEM_ALLOC(WUEPS_PID_TAF, TAF_SDC_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
        pstErrLogInfo->stBuffInfo.pstRingBuffer = VOS_NULL_PTR;
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SDC_InitErrLogInfo: alloc fail");
        return;
    }

    /* 调用OM的接口，将申请的动态内存创建为RING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, TAF_SDC_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pbuffer);
    }

    /* 保存ringbuffer指针 */
    pstErrLogInfo->stBuffInfo.pstRingBuffer = pRingbuffer;

    pstErrLogInfo->stBuffInfo.ulOverflowCnt = 0;
#endif

    return;

}
/*lint +e593 +e830*/

#if (FEATURE_ON == FEATURE_PTM)

VOS_UINT32 TAF_SDC_PutRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    OM_RING_ID                          pTafRingBuffer;
    VOS_UINT32                          ulRatRingbufferLength;
    VOS_UINT32                          ulNvSwitchNum;
    VOS_UINT32                          ulLength;

    pTafRingBuffer = TAF_SDC_GetRatSwitchRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    ulNvSwitchNum         = TAF_SDC_GetErrlogRatSwitchStatisticNum();
    ulRatRingbufferLength = ulNvSwitchNum * sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU);

    /* 如果写入比RING BUFFER还大则不写入 */
    if ((ulbytes > ulRatRingbufferLength)
     || (ulbytes != sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU)))
    {
        return 0;
    }

    /* 获取RING BUFFER剩余空间大小 */
    ulFreeSize = TAF_SDC_GetRatSwitchRingBufferFreeBytes();

    /* 如果队列已经满了，则队列头部记录出列 */
    if (0 == ulFreeSize)
    {
        ulLength = TAF_SDC_RatSwitchRingBufRemoveRecord(sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU));

        if (ulLength != sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU))
        {
            return 0;
        }
    }

    /* 写入RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}


VOS_UINT32 TAF_SDC_RatSwitchRingBufRemoveRecord(
    VOS_UINT32                          ulbytes
)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferRemove(TAF_SDC_GetRatSwitchRingBufAddr(), (VOS_INT)ulbytes);
}


VOS_UINT32 TAF_SDC_GetRecordFromRatSwitchRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferGetReserve(TAF_SDC_GetRatSwitchRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}



VOS_UINT32 TAF_SDC_GetRatSwitchRingBufferFreeBytes(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferFreeBytes(TAF_SDC_GetRatSwitchRingBufAddr());
}


VOS_VOID TAF_SDC_CleanRatSwitchRingBuf(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetRatSwitchRingBufAddr())
    {
        return;
    }

    OM_RingBufferFlush(TAF_SDC_GetRatSwitchRingBufAddr());

    return;
}

/*lint -e830 -e593*/

VOS_VOID TAF_SDC_CreatRatSwitchRingBuf(VOS_VOID)
{
    VOS_CHAR                           *pbuffer;
    OM_RING_ID                          pRatRingbuffer;
    VOS_UINT32                          ulNvSwitchNum;                          /* NV配置的gutl切换的统计次数 */
    VOS_INT32                           lRatRingbufferLength;

    ulNvSwitchNum = TAF_SDC_GetErrlogRatSwitchStatisticNum();

    if (0 == ulNvSwitchNum)
    {
        TAF_SDC_SetRatSwitchRingBufAddr(VOS_NULL_PTR);

        return;
    }

    lRatRingbufferLength = (VOS_INT32)ulNvSwitchNum * (VOS_INT32)sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU) + 1;

    pbuffer = (char *)PS_MEM_ALLOC(WUEPS_PID_TAF, (VOS_UINT32)lRatRingbufferLength);
    if (VOS_NULL_PTR == pbuffer)
    {
        TAF_SDC_SetRatSwitchRingBufAddr(VOS_NULL_PTR);
        return;
    }

    PS_MEM_SET(pbuffer, 0, (VOS_UINT32)lRatRingbufferLength);

    /* 调用OM的接口，将申请的动态内存创建为RING BUFFER */
    pRatRingbuffer = OM_RingBufferCreateEx(pbuffer, lRatRingbufferLength);
    if (VOS_NULL_PTR == pRatRingbuffer)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pbuffer);
    }

    TAF_SDC_SetRatSwitchRingBufAddr(pRatRingbuffer);

    return;
}
/*lint +e830 +e593*/


VOS_UINT32 TAF_SDC_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pTafRingBuffer;

    pTafRingBuffer = TAF_SDC_GetErrLogRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    /* 如果写入比RING BUFFER还大则不写入 */
    if (ulbytes > TAF_SDC_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* 获取RING BUFFER剩余空间大小 */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pTafRingBuffer);

    ulCount = TAF_SDC_GetErrlogOverflowCnt();
    /* 如果剩余空间不足写入的大小，则清空RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        TAF_SDC_SetErrlogOverflowCnt(ulCount);

        OM_RingBufferFlush(pTafRingBuffer);
    }

    /* 写入RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}


VOS_UINT32 TAF_SDC_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferGet(TAF_SDC_GetErrLogRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}


VOS_UINT32 TAF_SDC_GetErrLogRingBufferUseBytes(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetErrLogRingBufAddr())
    {
        return 0;
    }

    return (VOS_UINT32)OM_RingBufferNBytes(TAF_SDC_GetErrLogRingBufAddr());
}


VOS_VOID TAF_SDC_CleanErrLogRingBuf(VOS_VOID)
{
    /* 增加异常保护 */
    if (VOS_NULL_PTR == TAF_SDC_GetErrLogRingBufAddr())
    {
        return;
    }

    OM_RingBufferFlush(TAF_SDC_GetErrLogRingBufAddr());

    return;
}

#endif


VOS_VOID TAF_SDC_SetVoiceCallOnImsSupportFlag(
    VOS_UINT8                          ucVoiceCallOnImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag = ucVoiceCallOnImsSupportFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetVoiceCallOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVoiceCallOnImsSupportFlag;
}


VOS_VOID TAF_SDC_SetSmsOnImsSupportFlag(
    VOS_UINT8                          ucSmsOnImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag = ucSmsOnImsSupportFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetSmsOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucSmsOnImsSupportFlag;
}


VOS_VOID TAF_SDC_SetVideoCallOnImsSupportFlag(
    VOS_UINT8                          ucVideoCallOnImsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag = ucVideoCallOnImsSupportFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetVideoCallOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucVideoCallOnImsSupportFlag;
}



VOS_VOID TAF_SDC_SetVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enVoiceDomain = enVoiceDomain;

    return;
}


TAF_SDC_VOICE_DOMAIN_ENUM_UINT32 TAF_SDC_GetVoiceDomain(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enVoiceDomain;
}




VOS_VOID TAF_SDC_SetSmsDomain(
    TAF_SDC_SMS_DOMAIN_ENUM_UINT8      enSmsDomain
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enSmsDomain = enSmsDomain;

    return;
}


TAF_SDC_SMS_DOMAIN_ENUM_UINT8 TAF_SDC_GetSmsDomain(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enSmsDomain;
}


VOS_VOID TAF_SDC_SetLteEmsSupportFlag(
    VOS_UINT8                           ucLteEmsSupportFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag = ucLteEmsSupportFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetLteEmsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsRatSupport.ucLteEmsSupportFlag;
}


VOS_VOID TAF_SDC_SetLteCsSeviceCap(
    TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8   enLteCsServiceCap
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enLteCsServiceCfg = enLteCsServiceCap;

    return;
}


TAF_SDC_LTE_CS_SERVICE_ENUM_UINT8 TAF_SDC_GetLteCsSeviceCap(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.enLteCsServiceCfg);
}


TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8 TAF_SDC_GetUeUsageSetting(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.enUeUsageSetting);
}


VOS_VOID TAF_SDC_SetUeUsageSetting(
    TAF_SDC_UE_USAGE_SETTING_ENUM_UINT8   enUeUsageSetting
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.enUeUsageSetting = enUeUsageSetting;
}


TAF_SDC_SYS_MODE_ENUM_UINT8 TAF_SDC_GetCampSysMode( VOS_VOID )
{
    if (VOS_TRUE == TAF_SDC_GetCampOnFlag())
    {
        return TAF_SDC_GetSysMode();
    }

    return TAF_SDC_SYS_MODE_BUTT;
}


TAF_SDC_RAT_PRIO_STRU* TAF_SDC_GetMsPrioRatList( VOS_VOID )
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList);
}




VOS_VOID TAF_SDC_SetMsPrioRatList(
    TAF_SDC_RAT_PRIO_STRU              *pstPrioRatList
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPrioRatList = *pstPrioRatList;
}



VOS_UINT8 TAF_SDC_GetCallRedailFromImsToCsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial                    \
        .stRedialImsToCs.ucCallRedial;
}


VOS_VOID TAF_SDC_SetCallRedailFromImsToCsSupportFlag(VOS_UINT8 ucCallRedialFromImsToCs)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs           \
        .ucCallRedial = ucCallRedialFromImsToCs;
}


VOS_UINT8 TAF_SDC_GetSmsRedailFromImsToCsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs    \
        .ucSmsRedial;
}


VOS_VOID TAF_SDC_SetSmsRedailFromImsToCsSupportFlag(VOS_UINT8 ucSmsRedialFromImsToCs)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs           \
        .ucSmsRedial = ucSmsRedialFromImsToCs;
}


VOS_UINT8 TAF_SDC_GetRoamingSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.ucRoamingSupport;
}


VOS_VOID TAF_SDC_SetRoamingSupportFlag(VOS_UINT8 ucRoamingSupport)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.ucRoamingSupport = ucRoamingSupport;
}


VOS_VOID    TAF_SDC_SetImsNormalRegStatus(
    TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8    enRegStatus
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta = enRegStatus;

    return;
}


TAF_SDC_IMS_NORMAL_REG_STATUS_ENUM_UINT8   TAF_SDC_GetImsNormalRegStatus(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stImsDomainInfo.enImsNormalRegSta;
}




VOS_VOID  TAF_SDC_SetCurPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
)
{
    (TAF_SDC_GetSdcCtx()->stPhoneInfo.enPhMode) = enPhoneMode;
}



TAF_SDC_PHONE_MODE_ENUM_UINT8  TAF_SDC_GetCurPhoneMode(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stPhoneInfo.enPhMode);
}



VOS_VOID  TAF_SDC_SetCurImsSwitchState(
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8       enState
)
{
    (TAF_SDC_GetSdcCtx()->stPhoneInfo.enImsSwitchState) = enState;
}


TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8  TAF_SDC_GetCurImsSwitchState(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stPhoneInfo.enImsSwitchState);
}


TAF_SDC_CREG_TYPE_ENUM_UINT8  TAF_SDC_GetCregType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stRegReportStatus.enCregType);
}


VOS_VOID  TAF_SDC_SetCregType(TAF_SDC_CREG_TYPE_ENUM_UINT8 enCregType)
{
    TAF_SDC_GetSdcCtx()->stRegReportStatus.enCregType = enCregType;
}


TAF_SDC_CGREG_TYPE_ENUM_UINT8  TAF_SDC_GetCgregType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stRegReportStatus.enCgregType);
}


VOS_VOID  TAF_SDC_SetCgregType(TAF_SDC_CGREG_TYPE_ENUM_UINT8 enCgregType)
{
    TAF_SDC_GetSdcCtx()->stRegReportStatus.enCgregType = enCgregType;
}


TAF_SDC_CEREG_TYPE_ENUM_UINT8  TAF_SDC_GetCeregType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stRegReportStatus.enCeregType);
}


VOS_VOID  TAF_SDC_SetCeregType(TAF_SDC_CEREG_TYPE_ENUM_UINT8 enCeregType)
{
    TAF_SDC_GetSdcCtx()->stRegReportStatus.enCeregType = enCeregType;
}


VOS_UINT8 TAF_SDC_GetUssdOnImsSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag;
}


VOS_VOID TAF_SDC_SetUssdOnImsSupportFlag(VOS_UINT8 ucUssdOnImsSupportFlag)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stImsCapability.ucUssdOnImsSupportFlag = ucUssdOnImsSupportFlag;
}

#if (FEATURE_ON == FEATURE_ECALL)

TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallTestNumber(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stEcallTestNumber));
}


TAF_SDC_ECALL_NUM_STRU*                 TAF_SDC_GetEcallRecfgNumber(VOS_VOID)
{
    return (&(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.stEcallRecfgNumber));
}


TAF_SDC_CALL_MODE_ENUM_UINT8            TAF_SDC_GetCurCallMode(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enCallMode);
}


VOS_VOID  TAF_SDC_SetCurCallMode(
    TAF_SDC_CALL_MODE_ENUM_UINT8        enCallMode
)
{
    TAF_SDC_GetSdcCtx()->stSimInfo.stUsimInfo.enCallMode = enCallMode;
    return;
}

#endif


VOS_VOID TAF_SDC_SetLCEnableFlg(
    VOS_UINT8                           ucLCEnableFlg
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.ucLCEnableFlg = ucLCEnableFlg;
}



VOS_UINT8 TAF_SDC_GetLCEnableFlg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.ucLCEnableFlg;
}



VOS_VOID TAF_SDC_SetLCWorkCfg(
    TAF_NVIM_LC_WORK_CFG_ENUM_UINT8     enLCWorkCfg
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.enLCWorkCfg = enLCWorkCfg;
}



VOS_UINT8 TAF_SDC_GetLCWorkCfg(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.enLCWorkCfg;
}


VOS_UINT8 TAF_SDC_GetLCRatCombined(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara.enRatCombined;
}


TAF_SDC_LC_CONFIG_PARA_STRU* TAF_SDC_GetLcConfigPara(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stLcConfigPara);
}


VOS_VOID TAF_SDC_SetPsServiceConnStatusFlag(
    VOS_UINT8                           ucPsServiceConnStatusFlag
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stPsInfo.ucPsServiceConnStatusFlag = ucPsServiceConnStatusFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetPsServiceConnStatusFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stPsInfo.ucPsServiceConnStatusFlag;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID TAF_SDC_SetEpsServiceConnStatusFlag(
    VOS_UINT8                           ucEpsServiceConnStatusFlag
)
{
    TAF_SDC_GetSdcCtx()->stServiceInfo.stEpsInfo.ucEpsServiceConnStatusFlag = ucEpsServiceConnStatusFlag;

    return;
}


VOS_UINT8 TAF_SDC_GetEpsServiceConnStatusFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stServiceInfo.stEpsInfo.ucEpsServiceConnStatusFlag;
}
#endif


VOS_VOID TAF_SDC_InitAppSysMode(VOS_VOID)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysMode      = TAF_SDC_SYS_MODE_BUTT;
}


VOS_VOID TAF_SDC_InitAppSysSubMode(VOS_VOID)
{
    TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.enSysSubMode   = TAF_SDC_SYS_SUBMODE_BUTT;
}



VOS_VOID TAF_SDC_InitAppNetworkPlmnInfo(TAF_SDC_SERVICED_PLMN_INFO_STRU  *pstServPlmnInfo)
{
    pstServPlmnInfo->stServicePlmnId.ulMcc = TAF_SDC_INVALID_MCC;
    pstServPlmnInfo->stServicePlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    pstServPlmnInfo->ucServiceUtranMode    = NAS_UTRANCTRL_UTRAN_MODE_BUTT;
    pstServPlmnInfo->ucServiceRac          = TAF_SDC_RAC_INVALID;
    pstServPlmnInfo->usServiceLac          = TAF_SDC_LAC_INVALID;
    pstServPlmnInfo->ulServiceCellId       = TAF_SDC_CELLID_INVALID;
    pstServPlmnInfo->ucServiceRoamFlg      = TAF_PH_INFO_ROAM_UNKNOW;
}



TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU *TAF_SDC_GetEnhancedOperatorNameInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo);
}



TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetUsimOplFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimOplFileInfo);
}


TAF_SDC_OPER_NAME_TYPE_PRIO_STRU* TAF_SDC_GetOperNamePrio(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stOperNameTypePrio);
}


TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 TAF_SDC_GetCopsFormatType(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.enCopsFormatType);
}


VOS_VOID TAF_SDC_InitEonsRelatedSimFileInfo(VOS_VOID)
{
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperatorNameInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;

    pstEnhancedOperatorNameInfo = &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo);

    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimOplFileInfo), 0, sizeof(TAF_SDC_OPL_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimOplFileInfo), 0, sizeof(TAF_SDC_OPL_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimPnnFileInfo), 0, sizeof(TAF_SDC_PNN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimPnnFileInfo), 0, sizeof(TAF_SDC_PNN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stCphsFileInfo), 0, sizeof(TAF_SDC_CPHS_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimSpnFileInfo), 0, sizeof(TAF_SDC_SPN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimSpnFileInfo), 0, sizeof(TAF_SDC_SPN_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stUsimSpdiFileInfo), 0, sizeof(TAF_SDC_SPDI_FILE_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stSimSpdiFileInfo), 0, sizeof(TAF_SDC_SPDI_FILE_INFO_STRU));

    for (ulIndex = 0; ulIndex < TAF_SDC_MAX_SERVICE_PROVIDER_PLMN_NUM; ulIndex++)
    {
        pstEnhancedOperatorNameInfo->stUsimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMcc = TAF_SDC_INVALID_MCC;
        pstEnhancedOperatorNameInfo->stUsimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMnc = TAF_SDC_INVALID_MNC;
        pstEnhancedOperatorNameInfo->stSimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMcc = TAF_SDC_INVALID_MCC;
        pstEnhancedOperatorNameInfo->stSimSpdiFileInfo.astSeriveProviderPlmn[ulIndex].ulMnc = TAF_SDC_INVALID_MNC;
    }

}


VOS_VOID TAF_SDC_InitEnhancedOperatorNameInfo(
    TAF_SDC_INIT_CTX_TYPE_ENUM_UINT8                        enInitType,
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperatorNameInfo
)
{
    VOS_UINT32                                              ulIndex;

    if (TAF_MMA_INIT_CTX_STARTUP == enInitType)
    {
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SDC_InitEnhancedOperatorNameInfo: Start up scena, init EONS related SIM file info");
        TAF_SDC_InitEonsRelatedSimFileInfo();
    }

    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stOperNameTypePrio), 0, sizeof(TAF_SDC_OPER_NAME_TYPE_PRIO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stMmInfo), 0, sizeof(TAF_SDC_MM_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stCustomOperNameInfo), 0, sizeof(TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU));
    PS_MEM_SET(&(pstEnhancedOperatorNameInfo->stCustomOperNameInfo), 0, sizeof(TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU));
    pstEnhancedOperatorNameInfo->cWildCard = 0;

    pstEnhancedOperatorNameInfo->enCopsFormatType = TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH;

    for (ulIndex = 0; ulIndex < TAF_SDC_MAX_OPER_NAME_PRIO_NUM; ulIndex++)
    {
        pstEnhancedOperatorNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ulIndex] = TAF_SDC_OPER_NAME_TYPE_BUTT;
    }

    pstEnhancedOperatorNameInfo->stMmInfo.stOperatorPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
    pstEnhancedOperatorNameInfo->stMmInfo.stOperatorPlmnId.ulMnc = TAF_SDC_INVALID_MNC;

    for (ulIndex = 0; ulIndex < TAF_NVIM_STORED_OPER_NAME_NUM; ulIndex++)
    {
        pstEnhancedOperatorNameInfo->stCustomOperNameInfo.astCustomOperName[ulIndex].stOperatorPlmnId.ulMcc = TAF_SDC_INVALID_MCC;
        pstEnhancedOperatorNameInfo->stCustomOperNameInfo.astCustomOperName[ulIndex].stOperatorPlmnId.ulMnc = TAF_SDC_INVALID_MNC;
    }

    TAF_SDC_ReadEnhancedOperNameServiceCfgNvim();
    TAF_SDC_ReadCustomOperNameInfoNvim();
    return;
}



VOS_VOID TAF_SDC_SetCopsFormatType(
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8                     enCopsFormatType
)
{
    TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.enCopsFormatType = enCopsFormatType;
}



TAF_SDC_OPL_FILE_INFO_STRU* TAF_SDC_GetSimOplFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimOplFileInfo);
}


TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetUsimPnnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimPnnFileInfo);
}


TAF_SDC_PNN_FILE_INFO_STRU* TAF_SDC_GetSimPnnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimPnnFileInfo);
}


TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetUsimSpnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimSpnFileInfo);
}


TAF_SDC_SPN_FILE_INFO_STRU* TAF_SDC_GetSimSpnFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimSpnFileInfo);
}


TAF_SDC_CPHS_FILE_INFO_STRU* TAF_SDC_GetChpsFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stCphsFileInfo);
}


TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetUsimSpdiFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stUsimSpdiFileInfo);
}


TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetSimSpdiFileInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stSimSpdiFileInfo);
}



TAF_SDC_MM_INFO_STRU* TAF_SDC_GetMmInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stMmInfo);
}


TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU* TAF_SDC_GetCustomOperNameInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.stCustomOperNameInfo);
}



VOS_UINT8 TAF_SDC_GetPlmnExactlyCompareFlg(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPlmnExactlyCompareInfo.ucPlmnExactlyCompareFlag);
}


VOS_VOID  TAF_SDC_SetPlmnExactlyCompareFlg(VOS_UINT8  ucPlmnExactlyComparaFlag)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stPlmnExactlyCompareInfo.ucPlmnExactlyCompareFlag = ucPlmnExactlyComparaFlag;
}


VOS_UINT8 TAF_SDC_GetRefreshAllFileRestartFlag(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.ucRefreshAllFileRestartFlag);
}


VOS_VOID TAF_SDC_SetRefreshAllFileRestartFlag(
    VOS_UINT8                           ucRefreshAllFileRestartFlag
)
{
    TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.ucRefreshAllFileRestartFlag = ucRefreshAllFileRestartFlag;
    return;
}




VOS_VOID  TAF_SDC_SetPlmnCompareWildCard(
    VOS_CHAR                            cWildCard
)
{
    TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.cWildCard = cWildCard;
    return;
}


VOS_CHAR  TAF_SDC_GetPlmnCompareWildCard(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stEnhancedOperatorNameInfo.cWildCard;
}




VOS_VOID  TAF_SDC_InitNetworkRssiValue(TAF_SDC_SIG_QUALITY_INFO_STRU *pstSigQuaInfo)
{
    /* 3PGG相关制式的信号强度  */
    pstSigQuaInfo->st3GppRssiInfo.sUeRfPower                            = TAF_SDC_UE_RFPOWER_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.ucChannalQual                         = TAF_SDC_BLER_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.ucRssiValue                           = TAF_SDC_RSSI_VALUE_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.usCellDlFreq                          = TAF_SDC_UE_FREQ_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.usCellUlFreq                          = TAF_SDC_UE_FREQ_INVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRssi              = TAF_SDC_RSSI_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRsd               = 0;   /*填充值*/
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRsrp              = TAF_SDC_RSRP_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.sRsrq              = TAF_SDC_RSRQ_UNVALID;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.lSINR              = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.usRI         = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.aucRes[0]    = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.aucRes[1]    = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[0]    = 0;
    pstSigQuaInfo->st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[1]    = 0;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* 3GPP2相关制式的信号强度，目前只有1x的 */
    TAF_SDC_Init1xSigQualityRptValue();

    TAF_SDC_InitHrpdSigQualityRptValue();
#endif
}


VOS_VOID TAF_SDC_InitAppCsDomainInfo(
    TAF_SDC_CS_DOMAIN_INFO_STRU *pstCsDomainInfo
)
{
    pstCsDomainInfo->enCsRegStatus                         = TAF_SDC_REG_STATUS_BUTT;
    pstCsDomainInfo->enCsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* 小区受限类型默认需要设置为不受限,否则设置为BUTT时RIL层认为受限 */
    pstCsDomainInfo->stCsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstCsDomainInfo->stCsAcRestriction.ucRestrictRegister  = VOS_FALSE;
    pstCsDomainInfo->ucSimCsRegStatus                      = VOS_FALSE;
    pstCsDomainInfo->ucCsAttachAllowFlg                    = VOS_FALSE;

    return;
}


VOS_VOID TAF_SDC_InitAppPsDomainInfo(
    TAF_SDC_PS_DOMAIN_INFO_STRU *pstPsDomainInfo
)
{
    pstPsDomainInfo->enPsRegStatus                         = TAF_SDC_REG_STATUS_BUTT;
    pstPsDomainInfo->enPsServiceStatus                     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;

    /* 小区受限类型默认需要设置为不受限,否则设置为BUTT时RIL层认为受限 */
    pstPsDomainInfo->stPsAcRestriction.enCellAcType        = TAF_SDC_CELL_RESTRICTION_TYPE_NONE;

    pstPsDomainInfo->stPsAcRestriction.ucRestrictPagingRsp = VOS_FALSE;
    pstPsDomainInfo->stPsAcRestriction.ucRestrictRegister  = VOS_FALSE;
    pstPsDomainInfo->ucSimPsRegStatus                      = VOS_FALSE;
    pstPsDomainInfo->ucPsAttachAllowFlg                    = VOS_FALSE;

    return;
}


VOS_VOID TAF_SDC_InitAppNetwork_Info(
    TAF_SDC_APPNETWORK_INFO *pstAppNetworkInfo
)
{
    TAF_SDC_InitAppSysMode();
    TAF_SDC_InitAppSysSubMode();

    TAF_SDC_InitAppNetworkPlmnInfo(&pstAppNetworkInfo->stAppSysInfo.stServPlmnInfo);

    TAF_SDC_Init1xSysInfo(&pstAppNetworkInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo);

    TAF_SDC_InitNetworkRssiValue(&pstAppNetworkInfo->stAppSigQuaInfo);

    TAF_SDC_InitAppCsDomainInfo(&pstAppNetworkInfo->stCsDomainInfo);
    TAF_SDC_InitAppPsDomainInfo(&pstAppNetworkInfo->stPsDomainInfo);

    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_BUTT);
    TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_BUTT);

}

/*lint -restore */
#if (FEATURE_ON == FEATURE_BASTET)

VOS_UINT8   TAF_SDC_GetBastetSupportFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.ucBastetSupportFlag;
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_SDC_Set1xCallUcimEmccNumList(
    TAF_SDC_UCIM_ECC_NUM_LIST_STRU     *pstUcimEccNumList
)
{
    TAF_SDC_CALL_INFO_STRU             *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = TAF_SDC_GetCallInfo();

    PS_MEM_CPY(&(pstCallInfo->st1xCallUcimEccNumList), pstUcimEccNumList, sizeof(TAF_SDC_UCIM_ECC_NUM_LIST_STRU));

    return;
}


TAF_SDC_UCIM_ECC_NUM_LIST_STRU* TAF_SDC_Get1xCallUcimEmccNumList(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stServiceInfo.stCallInfo.st1xCallUcimEccNumList);
}


VOS_UINT16 TAF_SDC_Get1xBaseId(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.stBaseStationInfo.usBaseId;
}


VOS_INT32 TAF_SDC_Get1xSid(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.lSid;
}


VOS_INT32 TAF_SDC_Get1xNid(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.lNid;
}


VOS_UINT8 TAF_SDC_Get1xRoamingFlag(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.ucRoamingInd;
}


VOS_VOID TAF_SDC_Set1xSysInfo(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU         *pSysInfo
)
{
    TAF_SDC_1X_SYS_INFO_STRU           *pSdc1xSysInfo;

    pSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    pSdc1xSysInfo->usBandClass      = pSysInfo->usBandClass;
    pSdc1xSysInfo->ucRoamingInd     = pSysInfo->ucRoamingInd;
    pSdc1xSysInfo->ucPacketZoneId   = pSysInfo->ucPzid;
    pSdc1xSysInfo->lSid             = (0x00000000 | pSysInfo->usSid);
    pSdc1xSysInfo->lNid             = (0x00000000 | pSysInfo->usNid);
    pSdc1xSysInfo->ucPrevInUse      = pSysInfo->ucPrevInUse;
    pSdc1xSysInfo->usFreq           = pSysInfo->usFreq;

    pSdc1xSysInfo->enRegInfoIncl         = pSysInfo->enRegInfoIncl;
    pSdc1xSysInfo->enBaseStationInfoIncl = pSysInfo->enBaseStationInfoIncl;
    pSdc1xSysInfo->enServiceInfoIncl     = pSysInfo->enServiceInfoIncl;

    if (PS_TRUE == pSysInfo->enRegInfoIncl)
    {
        PS_MEM_CPY(&(pSdc1xSysInfo->stRegInfo), &(pSysInfo->stRegInfo), sizeof(NAS_MSCC_PIF_OHM_REG_INFO_STRU));
    }

    if (PS_TRUE == pSysInfo->enBaseStationInfoIncl)
    {
        PS_MEM_CPY(&(pSdc1xSysInfo->stBaseStationInfo), &(pSysInfo->stBaseStationInfo), sizeof(NAS_MSCC_PIF_OHM_BASE_STATION_INFO_STRU));
    }

    if (PS_TRUE == pSysInfo->enServiceInfoIncl)
    {
        PS_MEM_CPY(&(pSdc1xSysInfo->stServiceInfo), &(pSysInfo->stServiceInfo), sizeof(NAS_MSCC_PIF_OHM_SERVICE_INFO_STRU));
    }
}



TAF_SDC_HRPD_SYS_INFO_STRU* TAF_SDC_GethrpdSysInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.stHrpdSysInfo);
}



TAF_SDC_1X_SYS_INFO_STRU* TAF_SDC_Get1xSysInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo);
}



TAF_SDC_1X_SIG_QUALITY_INFO_STRU* TAF_SDC_Get1xSigQualityInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo);
}

TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU* TAF_SDC_GetHrpdSigQualityInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo.stSigQuaInfo.st3Gpp2SigQuaInfo.stHrpdSigQualityRptInfo);
}


VOS_VOID TAF_SDC_InitHrpdSigQualityRptValue(VOS_VOID)
{
    TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU         *pstSdcHrpdSigQualityInfo;

    pstSdcHrpdSigQualityInfo                     = TAF_SDC_GetHrpdSigQualityInfo();

    pstSdcHrpdSigQualityInfo->enMode             = TAF_SDC_HDR_CSQ_MODE_ENABLE;
    pstSdcHrpdSigQualityInfo->ucTimeInterval     = 0;
    pstSdcHrpdSigQualityInfo->ucRssiThreshold    = 3;
    pstSdcHrpdSigQualityInfo->ucSnrThreshold     = 3;
    pstSdcHrpdSigQualityInfo->ucEcioThreshold    = 10;
    pstSdcHrpdSigQualityInfo->sHdrRssi           = TAF_SDC_HRPD_INVALID_RSSI_VALUE;
    pstSdcHrpdSigQualityInfo->sHdrSnr            = TAF_SDC_HRPD_INVALID_SNR_VALUE;
    pstSdcHrpdSigQualityInfo->sHdrEcio           = TAF_SDC_HRPD_INVALID_ECIO_VALUE;
}


VOS_VOID TAF_SDC_Init1xSigQualityRptValue(VOS_VOID)
{
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU            *pstSdc1xSigQualityInfo;

    pstSdc1xSigQualityInfo                          = TAF_SDC_Get1xSigQualityInfo();

    pstSdc1xSigQualityInfo->enMode                  = TAF_SDC_CDMACSQ_MODE_ENABLE;
    pstSdc1xSigQualityInfo->ucTimeInterval          = 3;
    pstSdc1xSigQualityInfo->ucRssiRptThreshold      = 3;
    pstSdc1xSigQualityInfo->ucEcIoRptThreshold      = 3;
    pstSdc1xSigQualityInfo->sCdmaRssi               = TAF_SDC_CDMA_INVALID_RSSI_VALUE;
    pstSdc1xSigQualityInfo->sCdmaEcIo               = TAF_SDC_CDMA_INVALID_ECIO_VALUE;
}


VOS_UINT8 TAF_SDC_Get1xPrevInUse(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.ucPrevInUse;
}


VOS_UINT16 TAF_SDC_Get1xChan(VOS_VOID)
{
    return TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.st1xSysInfo.usFreq;
}


VOS_VOID TAF_SDC_SetXCaLLState(
    NAS_OM_1X_CALL_STATE_ENUM_UINT8        enXCallState
)
{
    TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.en1xCallState = enXCallState;
    return;
}


NAS_OM_1X_CALL_STATE_ENUM_UINT8 TAF_SDC_GetXCallState(
    VOS_VOID
)
{
    return   TAF_SDC_GetSdcCtx()->stNetworkInfo.stSysInfo.en1xCallState;

}

VOS_UINT32  TAF_SDC_GetCdmaStatusReportPeriod(
    VOS_VOID
)
{
    return TAF_SDC_GetSdcCtx()->stCdmaMntn.ulRptPeriod;
}


VOS_VOID TAF_SDC_SetCdmaStatusReportPeriod(
    VOS_UINT32                          ulRptPeriod
)
{
    TAF_SDC_GetSdcCtx()->stCdmaMntn.ulRptPeriod = ulRptPeriod;
}



VOS_VOID TAF_SDC_SetCdmaCurUeState(
    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8    enCasState
)
{
    TAF_SDC_GetSdcCtx()->enCasState = enCasState;
}


VOS_UINT8 TAF_SDC_GetCdmaCurUeState(
    VOS_VOID
)
{
    return  TAF_SDC_GetSdcCtx()->enCasState;
}



TAF_SDC_1X_SIG_QUALITY_INFO_STRU* TAF_SDC_GetApp1xSigQualityInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo);
}


TAF_SDC_1X_SYS_INFO_STRU* TAF_SDC_GetApp1xSysInfo(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo);
}


VOS_UINT8 TAF_SDC_GetApp1xRoamingFlag(VOS_VOID)
{
   return TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo.ucRoamingInd;
}


#endif





TAF_SDC_SWITCH_IMS_TO_CS_REDIAL_CAUSE_CONFIG_STRU * TAF_SDC_GetImsToCsRedialCauseConfig(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsCapInfo.stImsConfigPara.stRedial.stRedialImsToCs.stCallRedialCauseCfg);

}


TAF_SDC_NONNORMAL_REG_STATUS_MERGE_CFG_STRU* TAF_SDC_GetNonnormalRegStatusMergeCfg(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stNonnormalRegStatusMergeCfg);
}


VOS_UINT8 TAF_SDC_GetNonnormalRegStatusMergeFlg(VOS_VOID)
{
    return (TAF_SDC_GetSdcCtx()->stMsCfgInfo.stMsSysCfgInfo.stNonnormalRegStatusMergeCfg.ucMergeFlg);
}



TAF_SDC_NETWORK_INFO_STRU* TAF_SDC_GetNetWorkInfoAddr(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stNetworkInfo);
}


TAF_SDC_APPNETWORK_INFO* TAF_SDC_GetAppNetWorkInfoAddr(VOS_VOID)
{
    return &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo);
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

