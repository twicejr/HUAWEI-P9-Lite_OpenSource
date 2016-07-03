


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPublic.h"
#include    "NasLmmPubMOsa.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmAttDetInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBLIC_C
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


/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_VOID    NAS_LMM_GetMccFromPlmn
(
    const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
    VOS_UINT8                           *pucMcc1,
    VOS_UINT8                           *pucMcc2,
    VOS_UINT8                           *pucMcc3
)
{
    if ( (VOS_NULL_PTR == pucMcc1)
        ||(VOS_NULL_PTR == pucMcc2)
        ||(VOS_NULL_PTR == pucMcc3)
        ||(VOS_NULL_PTR == pstPlmnId))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetMccFromPlmn: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetMccFromPlmn_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* PLMN未定义，则返回F */
    if (VOS_TRUE == NAS_LMM_PlmnIsUndef(pstPlmnId))
    {
        *pucMcc1                         = NAS_LMM_HEX_DIGIT_F;
        *pucMcc2                         = NAS_LMM_HEX_DIGIT_F;
        *pucMcc3                         = NAS_LMM_HEX_DIGIT_F;
    }
    else
    {
        /* 取出每一位MCC */
        *pucMcc1 =  pstPlmnId->aucPlmnId[0] & NAS_LMM_HIGH_HALF_BYTE_MASK;
        *pucMcc2 = (pstPlmnId->aucPlmnId[0] & NAS_LMM_LOW_HALF_BYTE_MASK)
                   >> NAS_LMM_RIGHT_SHIFT_HALF_BYTE;
        *pucMcc3 =  pstPlmnId->aucPlmnId[1] & NAS_LMM_HIGH_HALF_BYTE_MASK;
    }

    return;
}


VOS_VOID    NAS_LMM_GetMncFromPlmn
(
    const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
    VOS_UINT8                           *pucMnc1,
    VOS_UINT8                           *pucMnc2,
    VOS_UINT8                           *pucMnc3
)
{
    if ( (VOS_NULL_PTR == pucMnc1)
        ||(VOS_NULL_PTR == pucMnc2)
        ||(VOS_NULL_PTR == pucMnc3)
        ||(VOS_NULL_PTR == pstPlmnId))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetMncFromPlmn: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetMncFromPlmn_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* PLMN未定义，则返回F */
    if (VOS_TRUE == NAS_LMM_PlmnIsUndef(pstPlmnId))
    {
        *pucMnc1                         = NAS_LMM_HEX_DIGIT_F;
        *pucMnc2                         = NAS_LMM_HEX_DIGIT_F;
        *pucMnc3                         = NAS_LMM_HEX_DIGIT_F;
    }
    else
    {
        /* 取出每一位MNC */
        *pucMnc1 =  pstPlmnId->aucPlmnId[2] & NAS_LMM_HIGH_HALF_BYTE_MASK;
        *pucMnc2 = (pstPlmnId->aucPlmnId[2] & NAS_LMM_LOW_HALF_BYTE_MASK)
                   >> NAS_LMM_RIGHT_SHIFT_HALF_BYTE;
        *pucMnc3 = (pstPlmnId->aucPlmnId[1] & NAS_LMM_LOW_HALF_BYTE_MASK)
                   >> NAS_LMM_RIGHT_SHIFT_HALF_BYTE;
    }
    return;
}


VOS_VOID    NAS_LMM_GetMccMncFromPlmn
(
    const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
    VOS_UINT32                          *pulMCC,
    VOS_UINT32                          *pulMNC
)
{
    VOS_UINT8                           ucMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit3 = NAS_LMM_NULL;

    if ( (VOS_NULL_PTR == pulMCC)
       ||(VOS_NULL_PTR == pulMNC)
       ||(VOS_NULL_PTR == pstPlmnId))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetMccMncFromPlmn: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetMccMncFromPlmn_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* PLMN未定义，则返回0 */
    if (VOS_TRUE == NAS_LMM_PlmnIsUndef(pstPlmnId))
    {
        *pulMCC                         = 0;
        *pulMNC                         = 0;
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetMccMncFromPlmn: PLMN is not defined.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetMccMncFromPlmn_ENUM,LNAS_FUNCTION_LABEL1);

        return;
    }

    /* 获取MCC每一位 */
    NAS_LMM_GetMccFromPlmn(pstPlmnId,&ucMccDigit1,&ucMccDigit2,&ucMccDigit3);

    /* 获取MNC每一位 */
    NAS_LMM_GetMncFromPlmn(pstPlmnId,&ucMncDigit1,&ucMncDigit2,&ucMncDigit3);

    *pulMCC = (100*ucMccDigit1) + (10*ucMccDigit2) + ucMccDigit3;

    /* MNC3:F,只取MNC1,MNC2*/
    if ( NAS_LMM_HEX_DIGIT_F == ucMncDigit3 )
    {
        *pulMNC = (10*ucMncDigit1) + ucMncDigit2;
    }
    else
    {
        *pulMNC = (100*ucMncDigit1) + (10*ucMncDigit2) + ucMncDigit3;
    }

    return;
}

NAS_LMM_MATCH_RESULT_ENUM_UINT32  NAS_LMM_ExactlyPlmnMatch
(
    const NAS_MM_PLMN_ID_STRU          *pstLocalPlmn,
    const NAS_MM_PLMN_ID_STRU          *pstBcchPlmn
)
{
    VOS_UINT32                          ulMatchResult = NAS_LMM_MATCH_FAIL;
    VOS_UINT32                          ulSimMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulSimMnc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMnc = NAS_LMM_NULL;

    /* SIM MCC MNC Digits */
    VOS_UINT8                           ucSimMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit3 = NAS_LMM_NULL;

    /* BCCH MCC MNC Digits */
    VOS_UINT8                           ucBcchMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit3 = NAS_LMM_NULL;

    if ( (VOS_NULL_PTR == pstLocalPlmn)
        ||(VOS_NULL_PTR ==pstBcchPlmn))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    /* 把每一位MCC,MNC获取出来 */
    NAS_LMM_GetMccFromPlmn(pstLocalPlmn,&ucSimMccDigit1,&ucSimMccDigit2,&ucSimMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstLocalPlmn,&ucSimMncDigit1,&ucSimMncDigit2,&ucSimMncDigit3);

    NAS_LMM_GetMccFromPlmn(pstBcchPlmn,&ucBcchMccDigit1,&ucBcchMccDigit2,&ucBcchMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstBcchPlmn,&ucBcchMncDigit1,&ucBcchMncDigit2,&ucBcchMncDigit3);

    NAS_LMM_GetMccMncFromPlmn(pstLocalPlmn, &ulSimMcc, &ulSimMnc);

    NAS_LMM_GetMccMncFromPlmn(pstBcchPlmn, &ulBcchMcc, &ulBcchMnc);

    /* 判断SIM-MCC与BCCH-MCC是否相等 */
    if ( ulSimMcc != ulBcchMcc  )
    {
        return NAS_LMM_MATCH_FAIL;
    }
    if (ulSimMnc == ulBcchMnc)
    {
        return NAS_LMM_MATCH_SUCCESS;
    }

    if ((310 <= ulBcchMcc) && (316 >= ulBcchMcc))
    {
        if (((0x0f == ucBcchMncDigit3)&&(0x0 == ucSimMncDigit3))
           ||((0x0f == ucSimMncDigit3)&&(0x0 == ucBcchMncDigit3)))
        {
           ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                        && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
    }

    return ulMatchResult;
}

/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_LMM_GetPlmnExactlyComparaFlg( VOS_VOID )
{
    NAS_LMM_PUBM_LOG1_NORM("NAS_LMM_GetPlmnExactlyComparaFlg:NAS_MML_GetPlmnExactlyComparaFlg() =",
                        NAS_MML_GetPlmnExactlyComparaFlg());
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_GetPlmnExactlyComparaFlg_ENUM,LNAS_FUNCTION_LABEL1,
                        NAS_MML_GetPlmnExactlyComparaFlg());
    #ifndef __PS_WIN32_RECUR__

    if (VOS_TRUE == NAS_MML_GetPlmnExactlyComparaFlg())
    {
        NAS_LMM_LogPlmnexactlyCmpFlag(VOS_TRUE);
        return NAS_LMM_SUCC;
    }
    NAS_LMM_LogPlmnexactlyCmpFlag(VOS_FALSE);
    return NAS_LMM_FAIL;
    #else
    if (VOS_TRUE == Stub_NAS_MML_GetPlmnExactlyComparaFlg())
    {
        return NAS_LMM_SUCC;
    }
    return NAS_LMM_FAIL;

    #endif
}

NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnMatch
(
    const NAS_MM_PLMN_ID_STRU          *pstLocalPlmn,
    const NAS_MM_PLMN_ID_STRU          *pstBcchPlmn
)
{
    VOS_UINT32                          ulMatchResult = NAS_LMM_MATCH_FAIL;
    VOS_UINT32                          ulSimMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulSimMnc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMnc = NAS_LMM_NULL;

    /* SIM MCC MNC Digits */
    VOS_UINT8                           ucSimMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit3 = NAS_LMM_NULL;

    /* BCCH MCC MNC Digits */
    VOS_UINT8                           ucBcchMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit3 = NAS_LMM_NULL;

    if ( (VOS_NULL_PTR == pstLocalPlmn)
        ||(VOS_NULL_PTR ==pstBcchPlmn))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    if (NAS_LMM_SUCC == NAS_LMM_GetPlmnExactlyComparaFlg())
    {
        ulMatchResult = NAS_LMM_ExactlyPlmnMatch(pstLocalPlmn,pstBcchPlmn);

        return ulMatchResult;
    }

    /* 把每一位MCC,MNC获取出来 */
    NAS_LMM_GetMccFromPlmn(pstLocalPlmn,&ucSimMccDigit1,&ucSimMccDigit2,&ucSimMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstLocalPlmn,&ucSimMncDigit1,&ucSimMncDigit2,&ucSimMncDigit3);

    NAS_LMM_GetMccFromPlmn(pstBcchPlmn,&ucBcchMccDigit1,&ucBcchMccDigit2,&ucBcchMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstBcchPlmn,&ucBcchMncDigit1,&ucBcchMncDigit2,&ucBcchMncDigit3);

    NAS_LMM_GetMccMncFromPlmn(pstLocalPlmn, &ulSimMcc, &ulSimMnc);

    NAS_LMM_GetMccMncFromPlmn(pstBcchPlmn, &ulBcchMcc, &ulBcchMnc);

    /* 判断SIM-MCC与BCCH-MCC是否相等 */
    if ( ulSimMcc != ulBcchMcc  )
    {
        return NAS_LMM_MATCH_FAIL;
    }

    /* 除北美以外的环境中 */
    if ((310 > ulBcchMcc) || (316 < ulBcchMcc))
    {
        /* MNC长度为2的情况 */
        if (0x0f == ucBcchMncDigit3)
        {
            /* 6.判断SIM-MNC与BCCH-MNC前两个数字是否匹配 */
            ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                            && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
        else /* MNC长度为3的情况 */
        {
            /* 判断SIM-MNC与BCCH-MNC三个数字是否匹配 */
            ulMatchResult = (ulSimMnc == ulBcchMnc);
        }
    }
    else /* 北美场景下MCC范围为310~316 */
    {
        /* 如果BCCH-MNC&SIM-MNC的第三个数分别是0和F,则满足PCS1900要求 */
        if (((0x0f == ucBcchMncDigit3)&&(0x0 == ucSimMncDigit3))
           ||((0x0f == ucSimMncDigit3)&&(0x0 == ucBcchMncDigit3)))
        {
            /* 判断SIM-MNC与BCCH-MNC前两个数字是否匹配 */
            ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                            && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
        else
        {
            /* 判断SIM-MNC与BCCH-MNC三个数字是否匹配 */
            ulMatchResult = (ulSimMnc == ulBcchMnc);
        }
    }

    return ulMatchResult;
}

NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_HplmnMatch
(
    const   NAS_MM_PLMN_ID_STRU        *pstHplmn,
    const   NAS_MM_PLMN_ID_STRU        *pstBcchPlmn
)
{
    VOS_UINT32                          ulMatchResult = NAS_LMM_MATCH_FAIL;
    VOS_UINT32                          ulSimMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulSimMnc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMnc = NAS_LMM_NULL;
    /* SIM MCC MNC Digits */
    VOS_UINT8                           ucSimMccDigit1;
    VOS_UINT8                           ucSimMccDigit2;
    VOS_UINT8                           ucSimMccDigit3;
    VOS_UINT8                           ucSimMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit3 = NAS_LMM_NULL;

    /* BCCH MCC MNC Digits */
    VOS_UINT8                           ucBcchMccDigit1;
    VOS_UINT8                           ucBcchMccDigit2 ;
    VOS_UINT8                           ucBcchMccDigit3;
    VOS_UINT8                           ucBcchMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit3 = NAS_LMM_NULL;

    if ( (VOS_NULL_PTR == pstHplmn)
        ||(VOS_NULL_PTR ==pstBcchPlmn))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    if (NAS_LMM_SUCC == NAS_LMM_GetPlmnExactlyComparaFlg())
    {
        ulMatchResult = NAS_LMM_ExactlyPlmnMatch(pstHplmn,pstBcchPlmn);

        return ulMatchResult;
    }

    /* 把每一位MCC,MNC获取出来 */
    NAS_LMM_GetMccFromPlmn(pstHplmn,&ucSimMccDigit1,&ucSimMccDigit2,&ucSimMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstHplmn,&ucSimMncDigit1,&ucSimMncDigit2,&ucSimMncDigit3);

    NAS_LMM_GetMccFromPlmn(pstBcchPlmn,&ucBcchMccDigit1,&ucBcchMccDigit2,&ucBcchMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstBcchPlmn,&ucBcchMncDigit1,&ucBcchMncDigit2,&ucBcchMncDigit3);


    NAS_LMM_GetMccMncFromPlmn(pstHplmn, &ulSimMcc, &ulSimMnc);

    NAS_LMM_GetMccMncFromPlmn(pstBcchPlmn,&ulBcchMcc, &ulBcchMnc);

   /* 判断SIM-MCC与BCCH-MCC是否相等 */
    if ( ulSimMcc != ulBcchMcc  )
    {
        return NAS_LMM_MATCH_FAIL;
    }

    /* 除北美以外的环境中 */
    if ((310 > ulBcchMcc) || (316 < ulBcchMcc))
    {
        /* MNC长度为2的情况 */
        if (0x0f == ucBcchMncDigit3)
        {
            /* 6.判断SIM-MNC与BCCH-MNC前两个数字是否匹配 */
            ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                            && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
        else /* MNC长度为3的情况 */
        {
            /* 判断SIM-MNC与BCCH-MNC三个数字是否匹配 */
            ulMatchResult = (ulSimMnc == ulBcchMnc);
        }
    }
    else /* 北美场景下MCC范围为310~316 */
    {
        /* 如果BCCH-MNC&SIM-MNC的第三个数分别是0和F,则满足PCS1900要求 */
        if (((0x0f == ucBcchMncDigit3)&&(0x0 == ucSimMncDigit3))
           ||((0x0f == ucSimMncDigit3)&&(0x0 == ucBcchMncDigit3)))
        {
            /* 判断SIM-MNC与BCCH-MNC前两个数字是否匹配 */
            ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                            && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
        else
        {
            /* 判断SIM-MNC与BCCH-MNC三个数字是否匹配 */
            ulMatchResult = (ulSimMnc == ulBcchMnc);
        }
    }

    return ulMatchResult;
}


NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnIDMatchPlmnList
(
    const NAS_MM_PLMN_ID_STRU          *pstPlmnId,
    const NAS_MM_PLMN_LIST_STRU        *pstPlmnList
)
{
    VOS_UINT8                           i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult;

    if ( (VOS_NULL_PTR == pstPlmnId)
       ||(VOS_NULL_PTR == pstPlmnList))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    for (i=0; i<pstPlmnList->ulPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_LMM_PlmnMatch(pstPlmnId, &pstPlmnList->astPlmnId[i]))
        {
            ulMatchResult = NAS_LMM_MATCH_SUCCESS;
            /* 如果有一项匹配成功，立即结束循环 */
            break;
        }
    }
    return ulMatchResult;
}



NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnIDMatchHplmnList
(
    const NAS_MM_PLMN_ID_STRU          *pstPlmnId,
    const NAS_MM_PLMN_LIST_STRU        *pstPlmnList
)
{
    VOS_UINT8                           i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult;

    if ( (VOS_NULL_PTR == pstPlmnId)
       ||(VOS_NULL_PTR == pstPlmnList))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    for (i=0; i<pstPlmnList->ulPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_LMM_HplmnMatch(&pstPlmnList->astPlmnId[i],pstPlmnId))
        {
            ulMatchResult = NAS_LMM_MATCH_SUCCESS;
            /* 如果有一项匹配成功，立即结束循环 */
            break;
        }
    }
    return ulMatchResult;
}



VOS_VOID NAS_LMM_TaCpy
(
    NAS_MM_TA_STRU                      *pstDestTa,
    const   NAS_MM_TA_STRU              *pstOrgTa
)
{
    if ( (VOS_NULL_PTR == pstDestTa)
       ||(VOS_NULL_PTR == pstOrgTa))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_TaCpy: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_TaCpy_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstDestTa->stTac.ucTac              = pstOrgTa->stTac.ucTac;
    pstDestTa->stTac.ucTacCnt           = pstOrgTa->stTac.ucTacCnt;

    NAS_LMM_PlmnCpy(&(pstDestTa->stPlmnId), &(pstOrgTa->stPlmnId));

    return;
}




VOS_VOID    NAS_LMM_PlmnCpy
(
    NAS_MM_PLMN_ID_STRU                *pstDestPlmn,
    const   NAS_MM_PLMN_ID_STRU        *pstOrgPlmn
)
{
    if ( (VOS_NULL_PTR == pstDestPlmn)
       ||(VOS_NULL_PTR == pstOrgPlmn))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PlmnCpy: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PlmnCpy_ENUM,LNAS_NULL_PTR);
        return;
    }
    pstDestPlmn->aucPlmnId[0] = pstOrgPlmn->aucPlmnId[0];
    pstDestPlmn->aucPlmnId[1] = pstOrgPlmn->aucPlmnId[1];
    pstDestPlmn->aucPlmnId[2] = pstOrgPlmn->aucPlmnId[2];
    return;
}


VOS_VOID    NAS_LMM_PlmnListCpy
(
    NAS_MM_PLMN_LIST_STRU               *pstDestPlmnList,
    const   NAS_MM_PLMN_LIST_STRU       *pstOrgPlmnList
)
{
    VOS_UINT8                           i;

    if ( (VOS_NULL_PTR == pstDestPlmnList)
       ||(VOS_NULL_PTR == pstOrgPlmnList))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PlmnListCpy: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PlmnListCpy_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstDestPlmnList->ulPlmnNum    = pstOrgPlmnList->ulPlmnNum;

    for (i=0; i<pstOrgPlmnList->ulPlmnNum; i++)
    {
        NAS_LMM_PlmnCpy(&pstDestPlmnList->astPlmnId[i],
                    &pstOrgPlmnList->astPlmnId[i]);
    }
    return;
}


NAS_LMM_ERROR_CODE_ENUM_UINT32 NAS_LMM_TaIncrease
(
    NAS_MM_TAC_STRU                     *pstTac
)
{
    VOS_UINT16                          usTac;

    if (VOS_NULL_PTR == pstTac)
    {
        return NAS_LMM_ERR_CODE_PTR_NULL;
    }

    usTac = (pstTac->ucTac<<8) | (pstTac->ucTacCnt);

    usTac++;

    pstTac->ucTac = (usTac>>8) & 0xFF;

    pstTac->ucTacCnt = usTac & 0xFF;

    return NAS_LMM_SUCC;

}


NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TacMatch
(
    const   NAS_MM_TAC_STRU            *pstTac1,
    const   NAS_MM_TAC_STRU            *pstTac2
)
{
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult;

    if ( (VOS_NULL_PTR == pstTac1)
       ||(VOS_NULL_PTR == pstTac2))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    if ( (pstTac1->ucTac == pstTac2->ucTac)
       &&(pstTac1->ucTacCnt == pstTac2->ucTacCnt))
    {
        ulMatchResult                   = NAS_LMM_MATCH_SUCCESS;
    }
    return ulMatchResult;
}



NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatch
(
    const   NAS_MM_TA_STRU             *pstTa1,
    const   NAS_MM_TA_STRU             *pstTa2
)
{
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult;

    if ( (VOS_NULL_PTR == pstTa1)
       ||(VOS_NULL_PTR == pstTa2))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    if ( NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch(&pstTa1->stPlmnId, &pstTa2->stPlmnId))
    {
        if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TacMatch(&pstTa1->stTac,&pstTa2->stTac) )
        {
            ulMatchResult               = NAS_LMM_MATCH_SUCCESS;
        }
    }

    return ulMatchResult;
}




NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchTaList
(
    const   NAS_MM_TA_STRU             *pstTa,
    const   NAS_MM_TA_LIST_STRU        *pstTaList
)
{
    VOS_UINT8                           i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32     ulMatchResult;
    NAS_MM_TA_STRU                      stTaInTalist;

    if ( (VOS_NULL_PTR == pstTa)
       ||(VOS_NULL_PTR == pstTaList))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    NAS_LMM_PUBM_LOG3_INFO("DST_PLMNID: ",  pstTa->stPlmnId.aucPlmnId[0],
                                            pstTa->stPlmnId.aucPlmnId[1],
                                            pstTa->stPlmnId.aucPlmnId[2]);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL1,
                                            pstTa->stPlmnId.aucPlmnId[0]);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL2,
                                            pstTa->stPlmnId.aucPlmnId[1],
                                            pstTa->stPlmnId.aucPlmnId[2]);

    NAS_LMM_PUBM_LOG2_INFO("DST_TAC: ",     pstTa->stTac.ucTac,
                                            pstTa->stTac.ucTacCnt);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL3,
                                            pstTa->stTac.ucTac,
                                            pstTa->stTac.ucTacCnt);

    /* 匹配TA列表 */
    for (i=0; i<pstTaList->ulTaNum; i++)
    {
        NAS_LMM_TaCpy(&stTaInTalist, &(pstTaList->astTa[i]));

        NAS_LMM_PUBM_LOG3_INFO("LIST_PLMNID: ", stTaInTalist.stPlmnId.aucPlmnId[0],
                                                stTaInTalist.stPlmnId.aucPlmnId[1],
                                                stTaInTalist.stPlmnId.aucPlmnId[2]);
        TLPS_PRINT2LAYER_INFO1(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL4,
                                                stTaInTalist.stPlmnId.aucPlmnId[0]);
        TLPS_PRINT2LAYER_INFO2(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL5,
                                                stTaInTalist.stPlmnId.aucPlmnId[1],
                                                stTaInTalist.stPlmnId.aucPlmnId[2]);

        NAS_LMM_PUBM_LOG2_INFO("LIST_TAC: ",    stTaInTalist.stTac.ucTac,
                                                stTaInTalist.stTac.ucTacCnt);
        TLPS_PRINT2LAYER_INFO2(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL6,
                                                stTaInTalist.stTac.ucTac,
                                                stTaInTalist.stTac.ucTacCnt);

        if ( VOS_TRUE == NAS_LMM_TaMatch(pstTa, &stTaInTalist))
        {
            ulMatchResult           = NAS_LMM_MATCH_SUCCESS;

            /* 如果有一项匹配成功，立即结束循环 */
            break;
        }
    }
    return ulMatchResult;

}



VOS_VOID    NAS_LMM_AddTaInTaList
(
    const   NAS_MM_TA_STRU              *pstTa,
    NAS_MM_TA_LIST_STRU                 *pstTaList,
    VOS_UINT32                          ulListNumMax
)
{
    VOS_UINT32                          i;

    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(pstTa, pstTaList))
    {
         NAS_LMM_PUBM_LOG_NORM("NAS_LMM_AddTaInTaList: TA is already in TaiList. ");
         TLPS_PRINT2LAYER_INFO(NAS_LMM_AddTaInTaList_ENUM,LNAS_ENTRY);
         return;
    }

    /* 列表中不存在当前要加入被禁列表的TA*/
    /* TA个数没有到最大，直接将TA加到末尾 */
    if (ulListNumMax > pstTaList->ulTaNum)
    {
        NAS_LMM_TaCpy(&pstTaList->astTa[pstTaList->ulTaNum],pstTa);
        pstTaList->ulTaNum++;
    }
    /* TA个数到最大，将TA加到末尾，其余TA往前移动，第一个TA移出 */
    else
    {
        pstTaList->ulTaNum             = ulListNumMax;

        for (i=0; i<(ulListNumMax -1) ; i++)
        {
            NAS_LMM_TaCpy(&(pstTaList->astTa[i]),
                         &(pstTaList->astTa[i+1]));
        }

        NAS_LMM_TaCpy(&(pstTaList->astTa[i]),
                     pstTa);
    }
    return;

}



VOS_VOID    NAS_LMM_DeleteTaFromTaList
(
    const   NAS_MM_TA_STRU              *pstTa,
    NAS_MM_TA_LIST_STRU                 *pstTaList,
    VOS_UINT32                          ulListNumMax
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFound;

    ulFound                             = VOS_FALSE;

    for (i=0; i<pstTaList->ulTaNum; i++)
    {
        if (VOS_FALSE == ulFound)
        {
            if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch( pstTa, &pstTaList->astTa[i]))
            {
                ulFound = VOS_TRUE;
            }
        }
        if ( (VOS_TRUE == ulFound) && (i < (ulListNumMax-1)) )
        {
            NAS_LMM_TaCpy(&(pstTaList->astTa[i]),
                         &(pstTaList->astTa[i+1]));
        }
    }

    /* 被删除的TA在列表中,列表个数减少一个 */
    if (VOS_TRUE == ulFound)
    {
        pstTaList->ulTaNum--;
    }

    return;
}


VOS_VOID    NAS_LMM_AddPlmnInPlmnList
(
    const   NAS_MM_PLMN_ID_STRU         *pstPlmnId,
    NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
    VOS_UINT32                          ulListNumMax
)
{
    VOS_UINT32                          i;

    /* 传入指针非空检查 */
    if ( (VOS_NULL_PTR == pstPlmnId)
        ||(VOS_NULL_PTR == pstPlmnList))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_AddPlmnInPlmnList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_AddPlmnInPlmnList_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* 被添加的PLMN不在列表中才添加 */
    if (NAS_LMM_MATCH_FAIL == NAS_LMM_PlmnIDMatchPlmnList(pstPlmnId, pstPlmnList))
    {
        /* 列表未满，直接添加到最后 */
        if (ulListNumMax > pstPlmnList->ulPlmnNum)
        {
            NAS_LMM_PlmnCpy(&pstPlmnList->astPlmnId[pstPlmnList->ulPlmnNum],
                        pstPlmnId);
            pstPlmnList->ulPlmnNum++;
        }
        /* 列表满，将第一个FPLMN移出,被添加的PLMN加到最后 */
        else
        {
            pstPlmnList->ulPlmnNum  = ulListNumMax;

            for (i=0; i<(ulListNumMax -1) ; i++)
            {
                NAS_LMM_PlmnCpy(&(pstPlmnList->astPlmnId[i]),
                               &(pstPlmnList->astPlmnId[i+1]));
            }
            NAS_LMM_PlmnCpy(&pstPlmnList->astPlmnId[i],pstPlmnId);
        }
    }
    return;
}


VOS_VOID    NAS_LMM_DeletePlmnFromPlmnList
(
    const   NAS_MM_PLMN_ID_STRU         *pstPlmnId,
    NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
    VOS_UINT32                          ulListNumMax
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFound;

    /* 传入指针非空检查 */
    if ( (VOS_NULL_PTR == pstPlmnId)
       ||(VOS_NULL_PTR == pstPlmnList))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_DeletePlmnFromPlmnList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DeletePlmnFromPlmnList_ENUM,LNAS_NULL_PTR);
        return;
    }

    if (pstPlmnList->ulPlmnNum > ulListNumMax)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_DeletePlmnFromPlmnList:List num or ulListNumMax is err!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DeletePlmnFromPlmnList_ENUM,LNAS_ERROR);
        return;
    }

    /* 被删除的PLMN在列表中才删除 */
    ulFound                             = VOS_FALSE;
    for (i=0; i<pstPlmnList->ulPlmnNum; i++)
    {
        if (VOS_FALSE == ulFound)
        {
            if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch( pstPlmnId, &pstPlmnList->astPlmnId[i]))
            {
                ulFound = VOS_TRUE;
            }
        }
        if ( (VOS_TRUE == ulFound) && (i < (ulListNumMax-1)) )
        {
            NAS_LMM_PlmnCpy(&(pstPlmnList->astPlmnId[i]),
                           &(pstPlmnList->astPlmnId[i+1]));
        }
    }

    /* 被删除的PLMN在当前列表中,列表个数减少一个 */
    if (VOS_TRUE == ulFound)
    {
        pstPlmnList->ulPlmnNum--;
    }
    return;
}


VOS_UINT32 NAS_LMM_PlmnIsUndef(const NAS_MM_PLMN_ID_STRU *pstPlmnId)
{
    if (VOS_NULL_PTR == pstPlmnId)
    {
        return VOS_TRUE;
    }

    /* 传入指针非空检查 */
    if ( (0xff == pstPlmnId->aucPlmnId[0])
       &&(0xff == pstPlmnId->aucPlmnId[1])
       &&(0xff == pstPlmnId->aucPlmnId[2])
       )
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32 NAS_LMM_TacIsInvalid(const NAS_MM_TAC_STRU *pstTac)
{
    /* 传入指针非空检查 */
    if (VOS_NULL_PTR == pstTac)
    {
        return VOS_TRUE;
    }

    if ((0xff == pstTac->ucTac)
       &&(0xfe == pstTac->ucTacCnt))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}



VOS_UINT32 NAS_LMM_PlmnIsUnexist(const NAS_MM_PLMN_ID_STRU *pstPlmnId)
{
    if (VOS_NULL_PTR == pstPlmnId)
    {
        return VOS_TRUE;
    }

    /* 传入指针非空检查 */
    if ( (0x00== pstPlmnId->aucPlmnId[0])
       &&(0x00 == pstPlmnId->aucPlmnId[1])
       &&(0x00 == pstPlmnId->aucPlmnId[2])
       )
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}



VOS_VOID    NAS_LMM_UndefPlmn
(
    NAS_MM_PLMN_ID_STRU                 *pstPlmnId
)
{
    /* 传入指针非空检查 */
    if (VOS_NULL_PTR == pstPlmnId)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_UndefPlmn: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UndefPlmn_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstPlmnId->aucPlmnId[0]             = 0xff;
    pstPlmnId->aucPlmnId[1]             = 0xff;
    pstPlmnId->aucPlmnId[2]             = 0xff;

    return;
}


VOS_VOID    NAS_LMM_UndefTac
(
    NAS_MM_TAC_STRU                 *pstTac
)
{
    /* 传入指针非空检查 */
    if (VOS_NULL_PTR == pstTac)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_UndefTac: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UndefTac_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstTac->ucTac                       = 0xff;
    pstTac->ucTacCnt                    = 0xfe;

    return;
}

VOS_UINT32    NAS_LMM_TacIsUnexist
(
    const NAS_MM_TAC_STRU                 *pstTac
)
{
    if (VOS_NULL_PTR == pstTac)
    {
        return VOS_TRUE;
    }

    /* 传入指针非空检查 */
    if((0x00 == pstTac->ucTac) &&
        (0x00 == pstTac->ucTacCnt))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32    NAS_LMM_CheckPlmnIsInvalid
(
    const NAS_MM_PLMN_ID_STRU                 *pstPlmnId
)
{
    VOS_UINT8                           ucMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit3 = NAS_LMM_NULL;
    VOS_UINT32                          ulMccMatchRslt;
    VOS_UINT32                          ulMncMatchRslt;

    if (VOS_NULL_PTR == pstPlmnId)
    {
        return VOS_TRUE;
    }

    /* 取出MCC */
    NAS_LMM_GetMccFromPlmn(pstPlmnId,&ucMccDigit1,&ucMccDigit2,&ucMccDigit3);

    /* 取出MNC */
    NAS_LMM_GetMncFromPlmn(pstPlmnId,&ucMncDigit1,&ucMncDigit2,&ucMncDigit3);

    ulMccMatchRslt = NAS_LMM_CheckMccIsValid(ucMccDigit1,ucMccDigit2,ucMccDigit3);

    ulMncMatchRslt = NAS_LMM_CheckMncIsValid(ucMncDigit1,ucMncDigit2,ucMncDigit3);

    if ((VOS_FALSE == ulMccMatchRslt) ||
        (VOS_FALSE == ulMncMatchRslt))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32    NAS_LMM_CheckMccIsValid
(
    VOS_UINT8   ucMcc1,
    VOS_UINT8   ucMcc2,
    VOS_UINT8   ucMcc3
)
{
    VOS_UINT32                          ulRslt = VOS_FALSE;

    if ((ucMcc1 <= NAS_LMM_DEC_DIGIT_9) &&
        (ucMcc2 <= NAS_LMM_DEC_DIGIT_9) &&
        (ucMcc3 <= NAS_LMM_DEC_DIGIT_9))
    {
        ulRslt = VOS_TRUE;
    }

    return ulRslt;
}


VOS_UINT32    NAS_LMM_CheckMncIsValid
(
    VOS_UINT8   ucMnc1,
    VOS_UINT8   ucMnc2,
    VOS_UINT8   ucMnc3
)
{
    VOS_UINT32                          ulRslt = VOS_FALSE;

    if ((ucMnc1 <= NAS_LMM_DEC_DIGIT_9) &&
        (ucMnc2 <= NAS_LMM_DEC_DIGIT_9) &&
        ((ucMnc3 <= NAS_LMM_DEC_DIGIT_9) || (ucMnc3 == NAS_LMM_HEX_DIGIT_F)))
    {
        ulRslt = VOS_TRUE;
    }

    return ulRslt;
}





VOS_VOID    NAS_LMM_ClearPlmnList(NAS_MM_PLMN_LIST_STRU  *pstPlmnList)
{

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ClearPlmnList: is entered !!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ClearPlmnList_ENUM,LNAS_ENTRY);

     /* 传入指针非空检查 */
    if (VOS_NULL_PTR == pstPlmnList)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_ClearPlmnList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_ClearPlmnList_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstPlmnList->ulPlmnNum            = 0;

    NAS_LMM_MEM_SET_S(  pstPlmnList->astPlmnId,
                        NAS_MM_MAX_PLMN_NUM * sizeof(NAS_MM_PLMN_ID_STRU),
                        0,
                        NAS_MM_MAX_PLMN_NUM * sizeof(NAS_MM_PLMN_ID_STRU));

    return;
}



VOS_VOID  NAS_LMM_ClearTaList(NAS_MM_FORB_TA_LIST_STRU  *pstTaList)
{

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ClearTaList: is entered !!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ClearTaList_ENUM,LNAS_ENTRY);

     /* 传入指针非空检查 */
    if (VOS_NULL_PTR == pstTaList)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_ClearTaList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_ClearTaList_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(pstTaList,sizeof(NAS_MM_FORB_TA_LIST_STRU),0,sizeof(NAS_MM_FORB_TA_LIST_STRU));

    return;
}


VOS_UINT32  NAS_LMM_CheckWhetherAllBytesAreFF(  const VOS_UINT8 *pucSimRecord,
                                                            const VOS_UINT32 ulIndex,
                                                            const VOS_UINT32 ulLen )
{
    VOS_UINT32                          i;

    if ((VOS_NULL_PTR == pucSimRecord) || (VOS_NULL == ulLen))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckWhetherAllBytesAreFF: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckWhetherAllBytesAreFF_ENUM,LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    for (i = 0; i< ulLen; i++)
    {
        if ( NAS_LMM_HEX_DIGIT_FF != pucSimRecord[ulIndex + i])
        {
            /* 如果存在不为0xFF,返回失败 */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}



VOS_UINT32  NAS_LMM_CheckWhetherAnyByteIsFF(   const VOS_UINT8 *pucSimRecord,
                                                            const VOS_UINT32 ulIndex,
                                                            const VOS_UINT32 ulLen)
{
    VOS_UINT32                          i;

    if ((VOS_NULL_PTR == pucSimRecord) || (VOS_NULL == ulLen))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckWhetherAnyByteIsFF: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckWhetherAnyByteIsFF_ENUM,LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    for (i = 0; i < ulLen; i++)
    {
        if ( NAS_LMM_HEX_DIGIT_FF == pucSimRecord[ulIndex + i])
        {
            return VOS_TRUE;
        }
    }

    /*如果不存在0xff,返回VOS_FALSE*/
    return VOS_FALSE;

}


VOS_VOID NAS_LMM_SetArrayAllBytesFF( VOS_UINT8 *pucArray,
                                              const VOS_UINT32 ulLen )
{
    VOS_UINT32                          i;

    if ((VOS_NULL_PTR == pucArray) || (VOS_NULL == ulLen))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckWhetherAnyByteIsFF: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SetArrayAllBytesFF_ENUM,LNAS_NULL_PTR);
        return ;
    }

    for (i = 0; i < ulLen; i++)
    {
        pucArray[i] = NAS_LMM_HEX_DIGIT_FF;
    }

    return;
}



VOS_UINT32  NAS_LMM_CheckSimRecordHeadValid( const VOS_UINT8 *pucSimRecord,
                                                          const VOS_UINT32 ulIndex,
                                                          const VOS_UINT32 ulLen )
{
    VOS_UINT32                        ulRslt;

    ulRslt =  NAS_LMM_CheckWhetherAnyByteIsFF( pucSimRecord, ulIndex, ulLen);

    if (VOS_FALSE == ulRslt)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}



VOS_UINT32  NAS_LMM_CheckSecuAlgValid( VOS_UINT8 ucSecuAlg)
{
    VOS_UINT8                    ucEncAlg;
    VOS_UINT8                    ucIntAlg;

    ucEncAlg = (ucSecuAlg & NAS_EMM_HIGH_HALF_BYTE_F) >> NAS_EMM_MOVEMENT_4_BITS;
    ucIntAlg = ucSecuAlg & NAS_EMM_LOW_HALF_BYTE_F;

    if ( (NAS_LMM_NVIM_ALG_VALID_IE < ucEncAlg)||(NAS_LMM_NVIM_ALG_VALID_IE < ucIntAlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}


VOS_UINT32  NAS_LMM_CheckModifyT3402DefaultValue( VOS_VOID)
{
    NAS_MM_PLMN_ID_STRU                *pstPresentPlmnId = NAS_EMM_NULL_PTR;

    pstPresentPlmnId = NAS_LMM_GetEmmInfoPresentPlmnAddr();

    if ((NAS_EMM_AD_BIT_SLCT == NAS_LMM_GetEmmInfoOpLastRegPlmn())
        && (NAS_LMM_MATCH_FAIL == NAS_LMM_PlmnMatch(pstPresentPlmnId, NAS_LMM_GetEmmInfoLastRegPlmnAddr())))
    {
        if ((NAS_EMM_AD_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
            && (NAS_LMM_MATCH_FAIL == NAS_LMM_PlmnIDMatchPlmnList(pstPresentPlmnId, NAS_LMM_GetEmmInfoNetInfoEplmnListAddr())))
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;

}


VOS_VOID    NAS_LMM_UndefCsgId
(
    VOS_UINT32             *pulCsgId
)
{
    /* 传入指针非空检查 */
    if (VOS_NULL_PTR == pulCsgId)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_UndefCsgId: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UndefCsgId_ENUM,LNAS_NULL_PTR);
        return;
    }

    *pulCsgId = 0xffffffff;

    return;
}
#if(FEATURE_ON == FEATURE_CSG)


VOS_UINT32 NAS_LMM_IsCsgCampOn( VOS_VOID )
{
    NAS_MM_CELL_TYPE_ENUM_UINT8         ucCellType;

    ucCellType = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->ucCellType;


    if((NAS_MM_CELL_TYPE_CSG == ucCellType)
        ||(NAS_MM_CELL_TYPE_HYBRID == ucCellType))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCsgCampOn:CSG Camp On.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_IsCsgCampOn_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_YES;
    }
    else
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCsgCampOn:CSG Not Camp On.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_IsCsgCampOn_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_NO;
    }
}


NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList
(
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU  *pstAllowedCsgList,
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU  *pstOperatorCsgList
)
{
    VOS_UINT8                           i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32    ulMatchResult;
    NAS_MM_PLMN_ID_STRU                *pstPlmnId;
    NAS_MM_PLMN_ID_STRU                 stPlmnIdInList;
    VOS_UINT32                          ulCsgId;

    /* 判断是否指针空 */
    if ((VOS_NULL_PTR == pstAllowedCsgList)
       ||(VOS_NULL_PTR == pstOperatorCsgList))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulCsgId                             = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->ulCsgId;
    pstPlmnId                           = NAS_EMM_GLO_AD_GetPresPlmnIdAddr();
    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    NAS_LMM_PUBM_LOG1_INFO("DTS_CSGID: ",  ulCsgId);
    TLPS_PRINT2LAYER_INFO1( NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList_ENUM,
                            LNAS_FUNCTION_LABEL1,
                            ulCsgId);

    /* 匹配CSG列表 */
    for (i=0; i<pstAllowedCsgList->ulPlmnWithCsgIdListNum; i++)
    {

        NAS_LMM_PUBM_LOG1_INFO("LIST_CSGID: ", pstAllowedCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId);

        TLPS_PRINT2LAYER_INFO1( NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList_ENUM,
                                LNAS_FUNCTION_LABEL2,
                                pstAllowedCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId);

        /* 转换PLMN格式 */
        NAS_LMM_ConvertGuPlmnToLteFormat(   &pstAllowedCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId,
                                            &stPlmnIdInList);

        if (( ulCsgId == pstAllowedCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId)
            &&(pstPlmnId->aucPlmnId[0] == stPlmnIdInList.aucPlmnId[0])
            &&(pstPlmnId->aucPlmnId[1] == stPlmnIdInList.aucPlmnId[1])
            &&(pstPlmnId->aucPlmnId[2] == stPlmnIdInList.aucPlmnId[2]))
        {
            ulMatchResult               = NAS_LMM_MATCH_SUCCESS;

            /* 如果有一项匹配成功，立即结束循环 */
            return ulMatchResult;
        }
    }
    for (i=0; i<pstOperatorCsgList->ulPlmnWithCsgIdListNum; i++)
    {

        NAS_LMM_PUBM_LOG1_INFO("LIST_CSGID: ", pstOperatorCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId);

        TLPS_PRINT2LAYER_INFO1( NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList_ENUM,
                                LNAS_FUNCTION_LABEL3,
                                pstOperatorCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId);
        /* 转换PLMN格式 */
        NAS_LMM_ConvertGuPlmnToLteFormat(   &pstOperatorCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId,
                                            &stPlmnIdInList);

        if (( ulCsgId == pstOperatorCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId)
            &&(pstPlmnId->aucPlmnId[0] == stPlmnIdInList.aucPlmnId[0])
            &&(pstPlmnId->aucPlmnId[1] == stPlmnIdInList.aucPlmnId[1])
            &&(pstPlmnId->aucPlmnId[2] == stPlmnIdInList.aucPlmnId[2]))
        {
            ulMatchResult           = NAS_LMM_MATCH_SUCCESS;

            /* 如果有一项匹配成功，立即结束循环 */
            break;
        }
    }
    return ulMatchResult;

}


VOS_UINT32 NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId( VOS_VOID )
{
    VOS_UINT32                          ulCurCsgId;
    NAS_MM_CSG_INFO_STRU               *pstLastAttmpRegCsgInfo;
    NAS_MM_PLMN_ID_STRU                *pstPlmnId;
    NAS_MM_PLMN_ID_STRU                *pstLastAttmpPlmnId;


    ulCurCsgId                          = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->ulCsgId;
    pstLastAttmpRegCsgInfo              = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegCsgInfoAddr();
    pstPlmnId                           = NAS_LMM_GetEmmInfoPresentPlmnAddr();
    pstLastAttmpPlmnId                  = NAS_LMM_GetEmmInfoLastAttmpRegPlmnAddr();

    /* 由宏小区到CSG小区，CSG ID不在LIST中直接发起TAU */
    if(NAS_MM_CELL_TYPE_MACRO == pstLastAttmpRegCsgInfo->ucCellType)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId: Last camp on macro.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_NO;
    }

    if((ulCurCsgId == pstLastAttmpRegCsgInfo->ulCsgId)
        &&(pstPlmnId->aucPlmnId[0] == pstLastAttmpPlmnId->aucPlmnId[0])
        &&(pstPlmnId->aucPlmnId[1] == pstLastAttmpPlmnId->aucPlmnId[1])
        &&(pstPlmnId->aucPlmnId[2] == pstLastAttmpPlmnId->aucPlmnId[2]))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId: equal last attempt register CSG ID.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_YES;
    }
    else
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId: not equal last attempt register CSG ID.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_NO;
    }
}
#endif

VOS_VOID  NAS_LMM_ConvertGuPlmnToLteFormat
(
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn,
    NAS_MM_PLMN_ID_STRU                *pstLNasPlmn
)
{
    pstLNasPlmn->aucPlmnId[0]
      = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMcc);
    pstLNasPlmn->aucPlmnId[0]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMcc) >> 4);

    pstLNasPlmn->aucPlmnId[1]
     = (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMcc) >> 16);

    pstLNasPlmn->aucPlmnId[1]
     |= (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMnc) >> 12);

    pstLNasPlmn->aucPlmnId[2]
     = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMnc);
    pstLNasPlmn->aucPlmnId[2]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMnc) >> 4);

    return;

}



VOS_UINT32  LMM_Get3402TimerLen(VOS_VOID)
{
    return NAS_EMM_GetEmmInfoDamParaT3402Len();
}


VOS_INT32 NAS_LMM_PUBM_SecuMemCpy
(
    VOS_VOID            * pDst,
    VOS_UINT32          ulMaxBuffer,
    const VOS_VOID      * pSrc,
    VOS_UINT32          ulLength,
    VOS_UINT32          ulLineNO,
    VOS_UINT32          ulFileID
)
{
    /*如果源地址和目的地址重叠，需改用TLPS_MEM_MOVE_S，否则安全拷贝失败 */
    if(((pSrc > pDst) && ((VOS_UINT8 *)pSrc <= ((VOS_UINT8 *)pDst + ulMaxBuffer)))
        ||((pDst> pSrc) && ((VOS_UINT8 *)pDst <= ((VOS_UINT8 *)pSrc + ulLength)))
        || (pSrc == pDst))
    {
        return TLPS_MEM_MOVE_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
    else
    {
        return TLPS_MEM_CPY_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
}


/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

