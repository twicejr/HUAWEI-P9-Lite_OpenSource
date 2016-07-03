

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MM_Share_inc.h"
#include "NVIM_Interface.h"

#include "MnComm.h"
#include "NasMmcCtx.h"
#include "TafStdlib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_SHARE_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

extern VOS_VOID Mm_ComInit (VOS_VOID);
extern VOS_VOID Gmm_TaskInit(VOS_VOID);
extern VOS_VOID MMC_GolbalVarInit(VOS_VOID);


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
MM_SUB_LAYER_SHARE_STRU                 g_MmSubLyrShare = {{0}};
VOS_UINT32                              g_ulGmmDelaySuspendRsp = 0;
/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*lint -save -e958 */


VOS_UINT32 Mm_AtTest_GetGprsState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 2;
    /* 0--A/Gb mode ,1--IU mode */
    pstAtCmdRslt->aulRslt[0] = NAS_MML_GetCurrNetRatType();
    /*
    A/Gb mode: 0--IDLE     1--STANDBY  2--READY
    IU mode  : 0--DETACHED 1--IDLE     2--CONNECTED
    */
    pstAtCmdRslt->aulRslt[1] = Gmm_GetGprsState();
    return VOS_OK;
}

VOS_UINT32 Mm_AtTest_GetGmmState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 1;
    pstAtCmdRslt->aulRslt[0] = Gmm_GetState();
    return VOS_OK;
}

VOS_UINT32 Mm_AtTest_GetMmState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 1;
    pstAtCmdRslt->aulRslt[0] = Mm_GetState();
    return VOS_OK;
}

VOS_UINT32 Mm_AtTest_GetMmRegState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 1;
    pstAtCmdRslt->aulRslt[0] = NAS_MML_GetCsRegStatus();
    return VOS_OK;
}

VOS_UINT32 Mm_AtTest_GetGmmRegState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 1;
    pstAtCmdRslt->aulRslt[0] = NAS_MML_GetPsRegStatus();
    return VOS_OK;
}



VOS_UINT32 Mm_AtTest_SetPlmnSearchMode(VOS_UINT32 ulPlmnSearchMode)
{
    NAS_NVIM_SELPLMN_MODE_STRU      stPlmnSelMode;

    if ( (ulPlmnSearchMode != 0) && (ulPlmnSearchMode != 1) )
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetPlmnSearchMode():WARNING: AT^CMM PARA Error!");
        return VOS_ERR;
    }

    if ( ulPlmnSearchMode == 0 )  /* 自动搜网模式 */
    {
        stPlmnSelMode.usSelPlmnMode = NAS_MMC_PLMN_SELECTION_MODE_AUTO;
        if (NV_OK != NV_Write (en_NV_Item_SelPlmn_Mode,
                               &stPlmnSelMode,
                               sizeof(NAS_NVIM_SELPLMN_MODE_STRU)))
        {
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetPlmnSearchMode():WARNING: Write en_NV_Item_SelPlmn_Mode Error");
            return VOS_ERR;
        }
    }
    else  /* 手动搜网模式 */
    {
        stPlmnSelMode.usSelPlmnMode = NAS_MMC_PLMN_SELECTION_MODE_MANUAL;
        if (NV_OK != NV_Write (en_NV_Item_SelPlmn_Mode,
                               &stPlmnSelMode,
                               sizeof(NAS_NVIM_SELPLMN_MODE_STRU)))
        {
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetPlmnSearchMode():WARNING: Write en_NV_Item_SelPlmn_Mode Error");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 Mm_AtTest_SetRatMode(VOS_UINT32 ulRatMode)
{
    NVIM_EQUIVALENT_PLMN_LIST_STRU  stEquivPlmn;
    VOS_UINT32  ulLen;

    if ( (ulRatMode != 0) && (ulRatMode != 1) )
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetRatMode():WARNING: AT^CMM PARA Error!");
        return VOS_ERR;
    }

    ulLen = sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU);

    PS_MEM_SET(&stEquivPlmn, 0x00, ulLen );

    /* 读取 equivalent PLMN list                 */
    if(NV_OK != NV_Read (en_NV_Item_EquivalentPlmn, &stEquivPlmn, ulLen))
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetRatMode():WARNING: Read en_NV_Item_EquivalentPlmn Error");
        return VOS_ERR;
    }
    else
    {   /* 设置接入模式                 */
        if ( ulRatMode == 0 )  /* GSM */
        {
            stEquivPlmn.struPlmnList[NVIM_MAX_EPLMN_NUM - 1].ucMnc[NVIM_MAX_MNC_SIZE - 1] = NAS_MML_NET_RAT_TYPE_GSM;
        }
        else /* WCDMA */
        {
            stEquivPlmn.struPlmnList[NVIM_MAX_EPLMN_NUM - 1].ucMnc[NVIM_MAX_MNC_SIZE - 1] = NAS_MML_NET_RAT_TYPE_WCDMA;
        }

        /* 存储 equivalent PLMN list                 */
        if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn, &stEquivPlmn, ulLen))
        {
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetRatMode():WARNING: Write en_NV_Item_EquivalentPlmn Error");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

#if ( VOS_WIN32 == VOS_OS_VER )

VOS_UINT32 Mm_AtTest_SetAdditionalUpdateRsltIe(
    VOS_UINT32 AdditionalUpdateRsltIe
)
{
    if (0x0 == AdditionalUpdateRsltIe)
    {
        NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_NO_ADDITION_INFO);
    }
    else if (0x1 == AdditionalUpdateRsltIe)
    {
        NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_CSFB_NOT_PREFERRED);
    }
    else
    {
        NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY);
    }

    return VOS_OK;
}


VOS_UINT32 Mm_AtTest_SetLteUeUsageSetting(
    VOS_UINT32 ulLteUeUsageSetting
)
{
    if (0x0 == ulLteUeUsageSetting)
    {
        NAS_MML_SetLteUeUsageSetting(NAS_MML_LTE_UE_USAGE_SETTING_VOICE_CENTRIC);
    }
    else
    {
        NAS_MML_SetLteUeUsageSetting(NAS_MML_LTE_UE_USAGE_SETTING_DATA_CENTRIC);
    }

    return VOS_OK;
}


VOS_UINT32 Mm_AtTest_SetGmmDelaySuspendRsp(
    VOS_UINT32 ulGmmDelaySuspendRspFlg
)
{
    if (0x0 == ulGmmDelaySuspendRspFlg)
    {
        g_ulGmmDelaySuspendRsp = 0;
    }
    else
    {
        g_ulGmmDelaySuspendRsp = 1;
    }

    return VOS_OK;
}


VOS_UINT32 Mm_AtTest_SetCsfbHighPrioFlg(
    VOS_UINT8                       ucFlg
)
{
    if ( VOS_TRUE == ucFlg )
    {
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
    }
    return VOS_OK;
}


#endif


VOS_UINT32 Mm_AtTest_SetOriginalRejectCause(
    VOS_UINT32                          ulOriginalUeCause
)
{
    VOS_UINT8                           ucOriginalUeCause;
    ucOriginalUeCause = (VOS_UINT8)ulOriginalUeCause;
    NAS_MML_SetOriginalRejectCause(ucOriginalUeCause);
    return VOS_OK;
}


VOS_UINT32 Mm_AtTest_ClearUserPlmnId( VOS_VOID )
{
    NAS_MML_PLMN_WITH_RAT_STRU         stUserPlmn;

    stUserPlmn.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stUserPlmn.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    NAS_MMC_SetUserSpecPlmnId(&stUserPlmn);

    return VOS_OK;
}



VOS_UINT32 Mm_AtTest(VOS_VOID* pstAtCmd,VOS_VOID* pstAtCmdRslt)
{
    VOS_UINT32 ulRst;
    ulRst = VOS_OK;
    switch(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->ucCmd)
    {
        case MM_TEST_AT_CMD_MM_STATE:
            ulRst = Mm_AtTest_GetMmState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_GMM_STATE:
            ulRst = Mm_AtTest_GetGmmState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_GPRS_STATE:
            ulRst = Mm_AtTest_GetGprsState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_MM_REG_STATE:
            ulRst = Mm_AtTest_GetMmRegState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_GMM_REG_STATE:
            ulRst = Mm_AtTest_GetGmmRegState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_PLMN_SEARCH_MODE:
            ulRst = Mm_AtTest_SetPlmnSearchMode(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;
        case MM_TEST_AT_CMD_SET_RAT_MODE:
            ulRst = Mm_AtTest_SetRatMode(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;

#if ( VOS_WIN32 == VOS_OS_VER )
        case MM_TEST_AT_CMD_SET_ADDITIONAL_UPDATE_RESULT_IE:
            ulRst = Mm_AtTest_SetAdditionalUpdateRsltIe(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;

        case MM_TEST_AT_CMD_SET_LTE_UE_USAGE_SETTING:
            ulRst = Mm_AtTest_SetLteUeUsageSetting(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;

        case MM_TEST_AT_CMD_SET_GMM_DEALY_SUSPENDRSP:
            ulRst = Mm_AtTest_SetGmmDelaySuspendRsp(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;

        case MM_TEST_AT_CMD_SET_CSFB_HIGH_PRIO_FLG:
            ulRst = Mm_AtTest_SetCsfbHighPrioFlg(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;
        case MM_TEST_AT_CMD_CLEAR_USER_PLMN_:
            ulRst = Mm_AtTest_ClearUserPlmnId();
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;

#endif
        case MM_TEST_AT_CMD_SET_ORIGINAL_REJECT_CAUSE:
             ulRst = Mm_AtTest_SetOriginalRejectCause(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;
        default:
            ulRst = VOS_ERR;
            break;
    }
    return ulRst;
}

 
 VOS_UINT32 MM_HexAlpha2AsciiString(VOS_UINT32 ulDestLength,VOS_UINT8 *pucDst,VOS_UINT8 *pucSrc,VOS_UINT16 usSrcLen)
 {
     VOS_UINT16 usLen = 0;
     VOS_UINT16 usChkLen = 0;
     VOS_UINT8 *pWrite = pucDst;
     VOS_UINT8 *pRead = pucSrc;
     VOS_UINT8  ucHigh = 0;
     VOS_UINT8  ucLow = 0;

     if((2 * usSrcLen)>= ulDestLength)
     {
         PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "MM_HexAlpha2AsciiString too long");
         return 0;
     }
     /*lint -e961*/
     if(0 != usSrcLen)
     {
         /* 扫完整个字串 */
         while( usChkLen++ < usSrcLen )
         {
             ucHigh = 0x0F & (*pRead >> 4);
             ucLow = 0x0F & *pRead;

             usLen += 2;    /* 记录长度 */

             if(0x09 >= ucHigh)   /* 0-9 */
             {
                 *pWrite++ = ucHigh + 0x30;
             }
             else if(0x0A <= ucHigh)    /* A-F */
             {
                 *pWrite++ = ucHigh + 0x37;
             }
             else
             {

             }

             if(0x09 >= ucLow)   /* 0-9 */
             {
                 *pWrite++ = ucLow + 0x30;
             }
             else if(0x0A <= ucLow)    /* A-F */
             {
                 *pWrite++ = ucLow + 0x37;
             }
             else
             {

             }

             /* 下一个字符 */
             pRead++;
         }

     }
     /*lint +e961*/
     return usLen;
 }

/* Deleted Mm_TranslateNtwkName2Str */



VOS_VOID MMC_ComGetRatType(VOS_UINT8 *pucRatType)
{
    *pucRatType = NAS_MML_GetCurrNetRatType();
    return;
}


VOS_UINT8  NAS_MM_GetMncLenFromBCCHMnc(
    VOS_UINT32                          ulBcchMnc
)
{
    VOS_UINT8                           ucBcchMnc3;
    VOS_UINT8                           ucMncLen;

    ucBcchMnc3 = (VOS_UINT8)((ulBcchMnc & 0x00ff0000) >> 16);

    if (0x0F == ucBcchMnc3)
    {
        ucMncLen = 2;
    }
    else
    {
       ucMncLen = 3;
    }

    return ucMncLen;
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


