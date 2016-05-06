/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
File name   : NasCommDebug.c
Description : NAS提供的软调信息
History     :
 1.郑军燕 00148421        2010-08-26  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "LPsSoftDebug.h"
#include    "NasLmmPubMFsm.h"
#include    "NasEsmPublic.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASCOMMDEBUG_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASCOMMDEBUG_C
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
/*****************************************************************************
 Function Name   : LNAS_DEBUG_GetEmmSta
 Description     : NAS软调信息：返回NAS所处的状态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-27  Draft Enact

*****************************************************************************/
LPS_LNAS_STA_ENUM_UINT32 LNAS_DEBUG_GetEmmSta(VOS_VOID)
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    NAS_LMM_FSM_STATE_STACK_STRU         *pstFsmStack = VOS_NULL_PTR;    /* 状态机栈地址 */
    NAS_LMM_FSM_STATE_STRU               *pstFsmStackBase = VOS_NULL_PTR; /* 指向栈底状态 */

    /* 从当前状态机中获取状态 */
    enMainState                         = NAS_LMM_GetEmmCurFsmMS();
    enSubState                          = NAS_LMM_GetEmmCurFsmSS();

    /* 连接建立过程,释放过程,鉴权过程 需要从状态栈获取状态 */
    if (EMM_MS_AUTH_INIT == enMainState)
    {
        /* 获取状态栈栈底地址 */
        pstFsmStack
            =  NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);
        pstFsmStackBase
            = &((pstFsmStack->astFsmStack)[NAS_LMM_STACK_BASE]);

        /* 从状态栈获取状态 */
        enMainState                     = pstFsmStackBase->enMainState;
        enSubState                      = pstFsmStackBase->enSubState;
    }

    if ((EMM_SS_REG_NO_CELL_AVAILABLE   == enSubState)
      ||(EMM_SS_DEREG_NO_CELL_AVAILABLE == enSubState)
      ||(EMM_SS_DEREG_NO_IMSI           == enSubState))
    {
        return LPS_LNAS_STA_NO_SERVICE;
    }

    if ((EMM_MS_REG == enMainState)
      ||(EMM_MS_TAU_INIT == enMainState)
      ||(EMM_MS_SER_INIT == enMainState))
    {
        return LPS_LNAS_STA_ATTACHED;
    }

    if (EMM_MS_DEREG == enMainState)
    {
        return LPS_LNAS_STA_DETACHED;
    }

    return LPS_LNAS_STA_OTHER;

}

/*****************************************************************************
 Function Name   : LNAS_DEBUG_GetUeIpInfo
 Description     : NAS软调信息：返回NAS当前所有激活的缺省承载对应的IP地址
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-09-22  Draft Enact

*****************************************************************************/
/*lint -e960*/
VOS_VOID LNAS_DEBUG_GetUeIpInfo
(
    LPS_LNAS_UE_IP_INFO_STRU           *pstUeIpInfo
)
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    VOS_UINT32                          ulActDftBearNum     = NAS_ESM_NULL;

    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_EPSB_NUM; ulCnt++)
    {
        /*获取对应EpsbCntxtTbl表地址*/
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulCnt);

        if (NAS_ESM_BEARER_STATE_ACTIVE != pstEpsbCntxtInfo->enBearerCntxtState)
        {
            continue;
        }

        if (PS_FALSE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
        {
            continue;
        }

        pstUeIpInfo->astUeIpInfo[ulActDftBearNum].ucPndId   = (VOS_UINT8)ulCnt;
        pstUeIpInfo->astUeIpInfo[ulActDftBearNum].enIpType  = pstEpsbCntxtInfo->stPdnAddrInfo.ucIpType;
        NAS_ESM_MEM_CPY_S(  pstUeIpInfo->astUeIpInfo[ulActDftBearNum].aucIpv4Addr,
                            LPS_OM_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr,
                            LPS_OM_IPV4_ADDR_LEN);

        NAS_ESM_MEM_CPY_S(    pstUeIpInfo->astUeIpInfo[ulActDftBearNum].aucIpv6Addr,
                            LPS_OM_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV6Addr,
                            LPS_OM_IPV6_ADDR_LEN);

        ulActDftBearNum++;
    }

    pstUeIpInfo->ulPdnNum = ulActDftBearNum;

    return;
}
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasCommDebug.c */
