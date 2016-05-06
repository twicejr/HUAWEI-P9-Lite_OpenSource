


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccFsmSysCfg.h"
#include "NasComm.h"
#include "NasUtranCtrlInterface.h"
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoadApi.h"
#include "NasDynLoad.h"
#endif


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_FSM_SYS_CFG_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* operation tables for Power save in system config  */
NAS_MSCC_POWER_SAVE_OPERATION_STRU      g_astSysCfgPowerSaveOperTable[NAS_MSCC_SYSCFG_SUPPORT_BUTT + 1][NAS_MSCC_SYSCFG_SUPPORT_BUTT + 1] =
             /* GSM */ /*UMTS*/ /*LTE*/  /*GU*/   /*GL*/   /*UL*/   /*GUL*/  /*1X*/   /*HRPD*/ /*C*/    /*1X&L*/ /*HRPD&L*/ /*CL*/ /*BUTT*/
{
/*GSM*/      {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}},
/*UMTS*/     {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}},
/*LTE*/      {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}},
/*GU*/       {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}},
/*GL*/       {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}},
/*UL*/       {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}},
/*GUL*/      {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,1}, {0,0,1}, {0,0,1}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}},
/*1X*/       {{1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {0,0,0}, {1,0,0}, {0,0,0}, {0,0,0}, {1,0,0}, {0,0,0}, {0,0,0}},
/*HRPD*/     {{0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,0,0}, {0,1,0}, {0,1,0}, {0,0,0}, {0,1,0}, {0,0,0}},
/*1X_HRPD*/  {{1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {0,1,0}, {1,0,0}, {0,0,0}, {0,1,0}, {1,0,0}, {0,0,0}, {0,0,0}},
/*1X_LTE*/   {{1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {1,0,0}, {0,0,1}, {1,0,1}, {0,0,1}, {0,0,0}, {1,0,0}, {0,0,0}, {0,0,0}},
/*HRPD_LTE*/ {{0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, {0,1,1}, {0,0,1}, {0,1,1}, {0,1,0}, {0,0,0}, {0,1,0}, {0,0,0}},
/*1X_HRPD_L*/ {{1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {1,1,0}, {0,1,1}, {1,0,1}, {0,0,1}, {0,1,0}, {1,0,0}, {0,0,0}, {0,0,0}},
/*BUTT*/     {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}}
};

/* This table is used to Map the System config Rat type Flag to System config RAt type Enum */
NAS_MSCC_SYS_CFG_RAT_TYPE_MAP_STRU      g_astNasMsccSysCfgRatTypeMapTbl[] =
{
    {NAS_MSCC_GSM_SUPPORT,          NAS_MSCC_SYSCFG_SUPPORT_GSM},
    {NAS_MSCC_UMTS_SUPPORT,         NAS_MSCC_SYSCFG_SUPPORT_UMTS},
    {NAS_MSCC_LTE_SUPPORT,          NAS_MSCC_SYSCFG_SUPPORT_LTE},
    {NAS_MSCC_1X_SUPPORT,           NAS_MSCC_SYSCFG_SUPPORT_1X},
    {NAS_MSCC_HRPD_SUPPORT,         NAS_MSCC_SYSCFG_SUPPORT_HRPD},
    {NAS_MSCC_GU_SUPPORT,           NAS_MSCC_SYSCFG_SUPPORT_GU},
    {NAS_MSCC_GL_SUPPORT,           NAS_MSCC_SYSCFG_SUPPORT_GL},
    {NAS_MSCC_UL_SUPPORT,           NAS_MSCC_SYSCFG_SUPPORT_UL},
    {NAS_MSCC_GUL_SUPPORT,          NAS_MSCC_SYSCFG_SUPPORT_GUL},
    {NAS_MSCC_1X_LTE_SUPPORT,       NAS_MSCC_SYSCFG_SUPPORT_1X_LTE},
    {NAS_MSCC_HRPD_LTE_SUPPORT,     NAS_MSCC_SYSCFG_SUPPORT_HRPD_LTE},
    {NAS_MSCC_1X_HRPD_SUPPORT,      NAS_MSCC_SYSCFG_SUPPORT_1X_HRPD},
    {NAS_MSCC_1X_HRPD_LTE_SUPPORT,  NAS_MSCC_SYSCFG_SUPPORT_1X_HRPD_LTE}
};
#ifdef DMT
    TEST_NAS_MSCC_POWER_SAVE_SYS_CFG_CNF_FAILURE_STRU g_stTestMsccPowerSaveSysCfgCnfFailure;
#endif
/*****************************************************************************
  3 函数定义
*****************************************************************************/




NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16 NAS_MSCC_MapSysCfgRatType(
    VOS_UINT16                          usRatTypeFlg
)
{
    NAS_MSCC_SYS_CFG_RAT_TYPE_MAP_STRU                     *pstSysCfgRatTypeMapTblPtr = VOS_NULL_PTR;
    VOS_UINT16                                              ulSysCfgRatTypeMapTblSize;
    VOS_UINT16                                              i;

    pstSysCfgRatTypeMapTblPtr = NAS_MSCC_GET_SYS_CFG_RAT_TYPE_MAP_TBL_PTR();
    ulSysCfgRatTypeMapTblSize = NAS_MSCC_GET_SYS_CFG_RAT_TYPE_MAP_TBL_SIZE();

    for (i = 0; i < ulSysCfgRatTypeMapTblSize; i++)
    {
        if (pstSysCfgRatTypeMapTblPtr[i].ulRatTypeFlg == usRatTypeFlg)
        {
            return pstSysCfgRatTypeMapTblPtr[i].enRatType;
        }
    }

    return NAS_MSCC_SYSCFG_SUPPORT_BUTT;
}


NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16 NAS_MSCC_GetSysCfgSupportedRatType(
    NAS_MSCC_PIF_RAT_PRIO_STRU          *pstRatPrio
)
{
    VOS_UINT16                          usRatTypeFlg = 0;
    VOS_UINT8                           i;

    for (i = 0; i < pstRatPrio->ucRatNum; i++)
    {
        switch (pstRatPrio->aucRatPrio[i])
        {
            case NAS_MSCC_PIF_NET_RAT_TYPE_GSM:
                usRatTypeFlg |= NAS_MSCC_GSM_SUPPORT;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA:
                usRatTypeFlg |= NAS_MSCC_UMTS_SUPPORT;
                break;

#if (FEATURE_ON == FEATURE_LTE)
            case NAS_MSCC_PIF_NET_RAT_TYPE_LTE:
                usRatTypeFlg |= NAS_MSCC_LTE_SUPPORT;
                break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            case NAS_MSCC_PIF_NET_RAT_TYPE_1X:
                usRatTypeFlg |= NAS_MSCC_1X_SUPPORT;
                break;

            case NAS_MSCC_PIF_NET_RAT_TYPE_HRPD:
                usRatTypeFlg |= NAS_MSCC_HRPD_SUPPORT;
                break;
#endif
            default:
                break;
        }

    }

    return (NAS_MSCC_MapSysCfgRatType(usRatTypeFlg));

}


NAS_MSCC_POWER_SAVE_OPERATION_STRU *NAS_MSCC_GetPowerSaveOperTypeFromTbl(
    NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16    ulLastRatType,
    NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16    ulCurrRatType
)
{
    return &(g_astSysCfgPowerSaveOperTable[ulLastRatType][ulCurrRatType]);
}




VOS_VOID NAS_MSCC_MapPowerSaveOperTypeToPowerSaveModuleOrder(
    NAS_MSCC_POWER_SAVE_OPERATION_STRU       *pstPowerSaveOperType
)
{
    NAS_MSCC_PREF_ORDER_MODULE_LIST                        *pstPowerSaveModuleOrder = VOS_NULL_PTR;
    VOS_UINT32                                              ulModuleID;
    NAS_MSCC_CTX_STRU                                      *pstMsccCtx              = VOS_NULL_PTR;

    pstMsccCtx              = NAS_MSCC_GetMsccCtxAddr();

    /* Get the power save module structure */
    pstPowerSaveModuleOrder = NAS_MSCC_GetPowerSaveModuleOrderAddr_SysCfg();

    PS_MEM_SET(pstPowerSaveModuleOrder,
               0x00,
               sizeof(NAS_MSCC_PREF_ORDER_MODULE_LIST));

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((VOS_TRUE == pstPowerSaveOperType->uc1XPowerSaveFlg)
     && (VOS_TRUE == pstMsccCtx->stPowerSaveCtrl.uc1xActiveFlg))
    {
        /* Adding XSD Module ID */
        pstPowerSaveModuleOrder->aulModuleID[pstPowerSaveModuleOrder->usNum] = UEPS_PID_XSD;
        pstPowerSaveModuleOrder->usNum ++;
    }

    if ((VOS_TRUE == pstPowerSaveOperType->ucHrpdPowerSaveFlg)
     && (VOS_TRUE == pstMsccCtx->stPowerSaveCtrl.ucHrpdActiveFlg))
    {
        /* Adding HSD Module ID */
        pstPowerSaveModuleOrder->aulModuleID[pstPowerSaveModuleOrder->usNum] = UEPS_PID_HSD;
        pstPowerSaveModuleOrder->usNum ++;
    }
#endif

    if ((VOS_TRUE == pstPowerSaveOperType->uc3GppPowerSaveFlg)
     && (VOS_TRUE == pstMsccCtx->stPowerSaveCtrl.uc3gppActiveFlg))
    {
        /* Adding MMC Module ID */
        pstPowerSaveModuleOrder->aulModuleID[pstPowerSaveModuleOrder->usNum] = WUEPS_PID_MMC;
        pstPowerSaveModuleOrder->usNum ++;
    }

    if (VOS_TRUE == pstMsccCtx->stPowerSaveCtrl.uc3gppActiveFlg)
    {
        if(VOS_TRUE == pstPowerSaveOperType->uc3GppPowerSaveFlg)
        {
            ulModuleID                              = pstPowerSaveModuleOrder->aulModuleID[0];
            pstPowerSaveModuleOrder->aulModuleID[0] = WUEPS_PID_MMC;
            pstPowerSaveModuleOrder->aulModuleID[pstPowerSaveModuleOrder->usNum - 1] = ulModuleID;
        }
    }

    /* Resetting the module order index */
    pstPowerSaveModuleOrder->usIndex = 0;
}



VOS_VOID NAS_MSCC_SetPowerSaveModuleOrder_SysCfg(VOS_VOID)
{

    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstLastUserRatPrio = VOS_NULL_PTR;
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstCurrUserRatPrio = VOS_NULL_PTR;
    NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16            enLastRatType;
    NAS_MSCC_SYSCFG_SUPPORT_RAT_TYPE_ENUM_UINT16            enCurrRatType;
    NAS_MSCC_POWER_SAVE_OPERATION_STRU                     *pstPowerSaveOperType = VOS_NULL_PTR;

    /* Get the LAst User RAT support */
    pstLastUserRatPrio = NAS_MSCC_GetRatPrioList();

    /* Get the current User RAT support */
    pstCurrUserRatPrio = NAS_MSCC_GetRatPrioListFromEntryMsg_SysCfg();

    /* Get the LAst User RAT support type */
    enLastRatType  = NAS_MSCC_GetSysCfgSupportedRatType(pstLastUserRatPrio);

    /* Get the current User RAT support type */
    enCurrRatType  = NAS_MSCC_GetSysCfgSupportedRatType(pstCurrUserRatPrio);

    if ((NAS_MSCC_SYSCFG_SUPPORT_BUTT == enLastRatType) || (NAS_MSCC_SYSCFG_SUPPORT_BUTT == enCurrRatType))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetPowerSaveModuleOrder_SysCfg(): Invaild Rat type ");
    }

    /* Get the Power save Operation type from the operation table */
    pstPowerSaveOperType      = NAS_MSCC_GetPowerSaveOperTypeFromTbl(enLastRatType,enCurrRatType);

    /* Save the power save module array */
    NAS_MSCC_MapPowerSaveOperTypeToPowerSaveModuleOrder(pstPowerSaveOperType);

    return ;

}

/*****************************************************************************
Function Name   :   NAS_MSCC_SetSysCfgModuleOrder_SysCfg
Description     :   This function is used to set the Power save module order global structure address. The Power Save order is
                    written in the list by reading the Platform Rat Cap global strucuture in the MSCC global context and the existing
                    system config details.

Input parameters:   None.
Output parameters:  None.
Return Value    :   None.
Modify History:
    1)  Date    :   2015-04-08
        Author  :   m00270891
        Modify content :    Create

    2.日    期   : 2015年5月12日
      作    者   : y00245242
      修改内容   : iteration 13开发
*****************************************************************************/
VOS_VOID NAS_MSCC_SetSysCfgModuleOrder_SysCfg(VOS_VOID)
{
    NAS_MSCC_PREF_ORDER_MODULE_LIST    *pstSysCfgModuleOrder = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT16                          usPowerOffHrpdIndex;
    VOS_UINT16                          usPowerOff3GppIndex;

    usPowerOffHrpdIndex                = 0xFFFF;
    usPowerOff3GppIndex                = 0xFFFF;
#endif

    pstSysCfgModuleOrder = NAS_MSCC_GetSysCfgModuleOrderAddr_SysCfg();

    PS_MEM_SET(pstSysCfgModuleOrder,
               0x00,
               sizeof(NAS_MSCC_PREF_ORDER_MODULE_LIST));


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if(VOS_TRUE == NAS_MSCC_IsPlatformSupportCdma1X())
    {
        /* Adding XSD Module ID */
        pstSysCfgModuleOrder->aulModuleID[pstSysCfgModuleOrder->usNum] = UEPS_PID_XSD;
        pstSysCfgModuleOrder->usNum ++;
    }

    if(VOS_TRUE == NAS_MSCC_IsPlatformSupportCdmaEVDO())
    {
        /* Adding HSD Module ID */
        pstSysCfgModuleOrder->aulModuleID[pstSysCfgModuleOrder->usNum] = UEPS_PID_HSD;
        pstSysCfgModuleOrder->usNum ++;

        usPowerOffHrpdIndex = pstSysCfgModuleOrder->usNum - 1;
    }
#endif

    if (VOS_TRUE == NAS_MSCC_IsPlatformSupport3Gpp())
    {
        /* Adding MMC Module ID */
        pstSysCfgModuleOrder->aulModuleID[pstSysCfgModuleOrder->usNum] = WUEPS_PID_MMC;
        pstSysCfgModuleOrder->usNum ++;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        usPowerOff3GppIndex = pstSysCfgModuleOrder->usNum - 1;
#endif
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((VOS_TRUE == NAS_MSCC_GetHrpdActiveFlg())
     && (0xFFFF    != usPowerOffHrpdIndex)
     && (0xFFFF    != usPowerOff3GppIndex))
    {
        pstSysCfgModuleOrder->aulModuleID[usPowerOffHrpdIndex] = WUEPS_PID_MMC;

        pstSysCfgModuleOrder->aulModuleID[usPowerOff3GppIndex] = UEPS_PID_HSD;
    }
#endif

    return ;
}

VOS_VOID NAS_MSCC_InitFsmCtx_SysCfg(VOS_VOID)
{
    if (NAS_MSCC_FSM_SYSTEM_CONFIG != NAS_MSCC_GetCurrFsmId())
    {
        /* Make Error log is FSM Id is not Power Off */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmCtx_SysCfg:ENTERED");

        return;
    }

    /* creat the Power save module order list */
    NAS_MSCC_SetPowerSaveModuleOrder_SysCfg();

    /* creat the system config module order list */
    NAS_MSCC_SetSysCfgModuleOrder_SysCfg();
}


NAS_MSCC_PIF_RAT_PRIO_STRU * NAS_MSCC_GetRatPrioListFromEntryMsg_SysCfg(VOS_VOID)
{

    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq = VOS_NULL_PTR;

    pstSysCfgReq   = (MMA_MSCC_SYS_CFG_SET_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();

    return &(pstSysCfgReq->stRatPrioList);
}



VOS_UINT32 NAS_MSCC_GetNextPowerSaveModuleId_SysCfg(
    VOS_UINT32                          *pulNextModuleId
)
{
    NAS_MSCC_PREF_ORDER_MODULE_LIST                        *pstPowerSaveModuleOrder = VOS_NULL_PTR;

    pstPowerSaveModuleOrder = NAS_MSCC_GetPowerSaveModuleOrderAddr_SysCfg();

    /* If the index of the Module order array is greater than the Total number of supported Modules, Return FALSE*/
    if (pstPowerSaveModuleOrder->usIndex >= pstPowerSaveModuleOrder->usNum)
    {
        return VOS_FALSE;
    }

    /* Write the next module ID from the module order array at the address pointed by pulNextModuleId */
    *pulNextModuleId = pstPowerSaveModuleOrder->aulModuleID[pstPowerSaveModuleOrder->usIndex];

    /* Increment the index of the module order array */
    pstPowerSaveModuleOrder->usIndex ++;

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_GetNextSysCfgModuleId_SysCfg(
    VOS_UINT32                          *pulNextModuleId
)
{
    NAS_MSCC_PREF_ORDER_MODULE_LIST                        *pstSysCfgModuleOrder = VOS_NULL_PTR;

    pstSysCfgModuleOrder = NAS_MSCC_GetSysCfgModuleOrderAddr_SysCfg();

    /* If the index of the Module order array is greater than the Total number of supported Modules, Return FALSE*/
    if (pstSysCfgModuleOrder->usIndex >= pstSysCfgModuleOrder->usNum)
    {
        return VOS_FALSE;
    }

    /* Write the next module ID from the module order array at the address pointed by pulNextModuleId */
    *pulNextModuleId = pstSysCfgModuleOrder->aulModuleID[pstSysCfgModuleOrder->usIndex];

    /* Increment the index of the module order array */
    pstSysCfgModuleOrder->usIndex ++;

    return VOS_TRUE;
}


VOS_VOID NAS_MSCC_SndSysCfgReq_SysCfg(
    VOS_UINT32                          ulReceivePid
)
{
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq   = VOS_NULL_PTR;

    /* Get the System config request from Entry message */
    pstSysCfgReq   = (MMA_MSCC_SYS_CFG_SET_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();

    switch (ulReceivePid)
    {
        case WUEPS_PID_MMC:
        {
            /* Send the System Config request to MMC */
            NAS_MSCC_SndMmcSysCfgReq(pstSysCfgReq);

            /* Start the protection timer */
            (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_SYS_CFG_CNF, TI_NAS_MSCC_WAIT_MMC_SYS_CFG_CNF_LEN);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSCFG_STA_WAIT_MMC_SYS_CFG_CNF);
        }
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case UEPS_PID_XSD:
        {
            /* Send the System Config request to XSD */
            NAS_MSCC_SndXsdSysCfgReq(pstSysCfgReq);

            /* Start the protection timer */
            NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_XSD_SYS_CFG_CNF, TI_NAS_MSCC_WAIT_XSD_SYS_CFG_CNF_LEN);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSCFG_STA_WAIT_XSD_SYS_CFG_CNF);
        }
            break;
        case UEPS_PID_HSD:
        {
            /* Send the System Config request to HSD */
            NAS_MSCC_SndHsdSysCfgReq(pstSysCfgReq);

            /* Start the protection timer */
            NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_SYS_CFG_CNF, TI_NAS_MSCC_WAIT_HSD_SYS_CFG_CNF_LEN);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSCFG_STA_WAIT_HSD_SYS_CFG_CNF);
        }
            break;
#endif

        default:
            NAS_ERROR_LOG(UEPS_PID_MSCC,"\n*NAS_MSCC_SndSysCfgReq_SysCfg():invalid ulReceivePid \n");
            break;
    }

}


VOS_VOID NAS_MSCC_SndPowerSaveReq_SysCfg(
    VOS_UINT32                          ulReceivePid
)
{

    switch (ulReceivePid)
    {
        case WUEPS_PID_MMC:
        {
            /* Send the Power Save request to MMC */
            NAS_MSCC_SndMmcPowerSaveReq();

            /* Start the protection timer */
            (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF, TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF_LEN);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSCFG_STA_WAIT_MMC_POWER_SAVE_CNF);
        }
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case UEPS_PID_XSD:
        {
            /* Send the Power save request to XSD */
            NAS_MSCC_SndXsdPowerSaveReq(NAS_MSCC_PIF_POWER_SAVE_TYPE_SYSCFG);

            /* Start the protection timer */
            NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_XSD_POWER_SAVE_CNF, TI_NAS_MSCC_WAIT_XSD_POWER_SAVE_CNF_LEN);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSCFG_STA_WAIT_XSD_POWER_SAVE_CNF);
        }
            break;
        case UEPS_PID_HSD:
        {
            /* Send the Power save request to HSD */
            NAS_MSCC_SndHsdPowerSaveReq();

            /* Start the protection timer */
            NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF, TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF_LEN);

            /* Update the currewnt FSM State */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_SYSCFG_STA_WAIT_HSD_POWER_SAVE_CNF);
        }
            break;
#endif

        default:
            NAS_ERROR_LOG(UEPS_PID_MSCC, "\n*NAS_MSCC_SndPowerSaveReq_SysCfg():invalid ulReceivePid \n");
            break;
    }

}

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
/*****************************************************************************
Function Name   :   NAS_MSCC_GetRatModeChangeType_SysCfg
Description     :   用于获取当前接入模式变化，如CL->GUL,GUL->CL等
Input parameters:   pstLastUserRatPrio
                    pstCurrUserRatPrio
Output parameters:  None
Return Value    :   NAS_MSCC_RAT_MODE_TYPE_ENUM_UINT8

Modify History:
    1)  Date    :   2015-08-21
        Author  :   w00242748
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_RAT_MODE_CHG_TYPE_ENUM_UINT8 NAS_MSCC_GetRatModeChangeType_SysCfg(
    NAS_MSCC_PIF_RAT_PRIO_STRU        *pstLastUserRatPrio,
    NAS_MSCC_PIF_RAT_PRIO_STRU        *pstCurrUserRatPrio
)
{
    NAS_MSCC_RAT_MODE_CHG_TYPE_ENUM_UINT8                   enRatModeType;
    VOS_UINT32                                              ulIsLastRatPrioCLMode;
    VOS_UINT32                                              ulIsCurrRatPrioCLMode;

    ulIsLastRatPrioCLMode = NAS_MSCC_IsCLModeSupportedInRatList(pstLastUserRatPrio);
    ulIsCurrRatPrioCLMode = NAS_MSCC_IsCLModeSupportedInRatList(pstCurrUserRatPrio);

    if (VOS_FALSE == ulIsLastRatPrioCLMode)
    {
        if (VOS_FALSE == ulIsCurrRatPrioCLMode)
        {
            enRatModeType = NAS_MSCC_RAT_MODE_CHG_GUL_TO_GUL;
        }
        else
        {
            enRatModeType = NAS_MSCC_RAT_MODE_CHG_GUL_TO_CL;
        }
    }
    else
    {
        if (VOS_FALSE == ulIsCurrRatPrioCLMode)
        {
            enRatModeType = NAS_MSCC_RAT_MODE_CHG_CL_TO_GUL;
        }
        else
        {
            enRatModeType = NAS_MSCC_RAT_MODE_CHG_CL_TO_CL;
        }
    }

    return enRatModeType;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ProcDynamicLoad_SysCfg
Description     :   SYSCFG状态机中，处理动态加载信息
Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-08-21
        Author  :   w00242748
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcDynamicLoad_SysCfg(VOS_VOID)
{
    VOS_RATMODE_ENUM_UINT32                                 enRatMode;
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstLastUserRatPrio = VOS_NULL_PTR;
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstCurrUserRatPrio = VOS_NULL_PTR;
    NAS_MSCC_RAT_MODE_CHG_TYPE_ENUM_UINT8                   enRatModeType;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enUtranMode;

    /* SYSCFG配置时，根据当前的utran mode来进行加载TDS或者W */
    enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
    enRatMode   = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enUtranMode);

    /* 获取当前SYSCFG支持的接入技术 */
    pstLastUserRatPrio = NAS_MSCC_GetRatPrioList();

    /* 获取用户设置的SYSCFG的接入技术 */
    pstCurrUserRatPrio = NAS_MSCC_GetRatPrioListFromEntryMsg_SysCfg();

    enRatModeType = NAS_MSCC_GetRatModeChangeType_SysCfg(pstLastUserRatPrio, pstCurrUserRatPrio);

    if (NAS_MSCC_RAT_MODE_CHG_CL_TO_GUL == enRatModeType)
    {
        (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
    }

    if (NAS_MSCC_RAT_MODE_CHG_GUL_TO_CL == enRatModeType)
    {
        (VOS_VOID)NAS_DYNLOAD_UnloadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
    }
}
#endif


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmaSysCfgReq_SysCfg_Init
Description     :   This function deals with the init of the System config FSM

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2015-04-09
        Author  :   m00270891
        Modify content :    Create
    2)  Date    :   2015-08-29
        Author  :   w00242748
        Modify content :动态加载项目
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaSysCfgReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    /* Get the next Power Save Module ID */
    ulRslt = NAS_MSCC_GetNextPowerSaveModuleId_SysCfg(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Send the Power Save request to Next module */
        NAS_MSCC_SndPowerSaveReq_SysCfg(ulModuleId);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
    {
        NAS_MSCC_ProcDynamicLoad_SysCfg();
    }
#endif

    /* if the Power save module List is empty
       get next module ID from system config Module list */
    ulRslt = NAS_MSCC_GetNextSysCfgModuleId_SysCfg(&ulModuleId);
    if (VOS_TRUE == ulRslt)
    {
        /* Send the System Config request to Next module */
        NAS_MSCC_SndSysCfgReq_SysCfg(ulModuleId);
        return VOS_TRUE;
    }

    /* if the system config module array is empty
        send system config failure result */
    NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvMmaSysCfgReq_SysCfg_Init():Invalid Module order");

    /* send the result to Main FSM */
    NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_FAILURE);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_MSCC_RcvXsdPowerSaveCnf_SysCfg_WaitXsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_POWER_SAVE_CNF_STRU       *pstPowerSaveCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;
    pstPowerSaveCnf                     = (XSD_MSCC_POWER_SAVE_CNF_STRU*)pstMsg;

#ifdef DMT
    if (VOS_TRUE == g_stTestMsccPowerSaveSysCfgCnfFailure.ulXsdPowerSaveCnfFailureFlag)
    {
        pstPowerSaveCnf->enResult = NAS_MSCC_PIF_POWER_SAVE_FAILURE;
    }
#endif

    /* Stop the timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_XSD_POWER_SAVE_CNF);

    /* Check whether the Power save result is success or not
        1)If result is success get the next module and send power save request to next module
        2)If result is Success and Power save Module array is empty then get the next module from the system config array.
        3)If the system config array is empty send system config failure result.
        4)If result is failure send failure result */
    if ( NAS_MSCC_PIF_POWER_SAVE_SUCCESS == pstPowerSaveCnf->enResult )
    {
        /* Get the next module ID from power save modulr array */
        ulRslt      = NAS_MSCC_GetNextPowerSaveModuleId_SysCfg(&ulModuleId);

        if (VOS_TRUE == ulRslt)
        {
            /* send Power save request to next module */
            NAS_MSCC_SndPowerSaveReq_SysCfg(ulModuleId);
            return VOS_TRUE;
        }

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            NAS_MSCC_ProcDynamicLoad_SysCfg();
        }
#endif
        /* if the Power save module List is over
            get next module ID from system config MOdule list */
        ulRslt = NAS_MSCC_GetNextSysCfgModuleId_SysCfg(&ulModuleId);
        if (VOS_TRUE == ulRslt)
        {
            /* Send the System Config request to Next module */
            NAS_MSCC_SndSysCfgReq_SysCfg(ulModuleId);
            return VOS_TRUE;
        }

    }

    /* if the result is failure send system config failure result */
    NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvXsdPowerSaveCnf_SysCfg_WaitXsdPowerSaveCnf:Result Failure!");

    /* send the failure result */
    NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_FAILURE);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiWaitXsdPowerSaveCnfExpired_SysCfg_WaitXsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Print Warning Log */
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitXsdPowerSaveCnfExpired_SysCfg_WaitXsdPowerSaveCnf:time expired!");

    /* Reboot */
    NAS_MSCC_SoftReBoot(NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_XSD_POWER_SAVE_CNF_EXPIRED, UEPS_PID_XSD);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_SysCfg_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_POWER_SAVE_CNF_STRU       *pstPowerSaveCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;
    pstPowerSaveCnf                     = (HSD_MSCC_POWER_SAVE_CNF_STRU*)pstMsg;

#ifdef DMT
    if (VOS_TRUE == g_stTestMsccPowerSaveSysCfgCnfFailure.ulHsdPowerSaveCnfFailureFlag)
    {
        pstPowerSaveCnf->enResult = NAS_MSCC_PIF_POWER_SAVE_FAILURE;
    }
#endif

    /* Stop the timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF);

    /* Check whether the Power save result is success or not
        1)If result is success get the next module and send power save request to next module
        2)If result is Success and Power save Module array is empty then get the next module from the system config array.
        3)If the system config array is empty send system config failure result.
        4)If result is failure send failure result */
    if ( NAS_MSCC_PIF_POWER_SAVE_SUCCESS == pstPowerSaveCnf->enResult )
    {
        /* Get the next module ID from power save modulr array */
        ulRslt      = NAS_MSCC_GetNextPowerSaveModuleId_SysCfg(&ulModuleId);

        if (VOS_TRUE == ulRslt)
        {
            /* send Power save request to next module */
            NAS_MSCC_SndPowerSaveReq_SysCfg(ulModuleId);
            return VOS_TRUE;
        }

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            NAS_MSCC_ProcDynamicLoad_SysCfg();
        }
#endif

        /* if the Power save module List is over
            get next module ID from system config MOdule list */
        ulRslt = NAS_MSCC_GetNextSysCfgModuleId_SysCfg(&ulModuleId);
        if (VOS_TRUE == ulRslt)
        {
            /* Send the System Config request to Next module */
            NAS_MSCC_SndSysCfgReq_SysCfg(ulModuleId);
            return VOS_TRUE;
        }

    }

    NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvHsdPowerSaveCnf_SysCfg_WaitHsdPowerSaveCnf:Result Failure!");

    /* send the failure result */
    NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_FAILURE);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_SysCfg_WaitHsdPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Print Warning Log */
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdPowerSaveCnfExpired_SysCfg_WaitHsdPowerSaveCnf:time expired!");

    /* Reboot */
    NAS_MSCC_SoftReBoot(NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_HSD_POWER_SAVE_CNF_EXPIRED, UEPS_PID_HSD);

    return VOS_TRUE;
}
#endif


VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_SysCfg_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_POWER_SAVE_CNF_STRU       *pstPowerSaveCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;
    pstPowerSaveCnf                     = (MMC_MSCC_POWER_SAVE_CNF_STRU*)pstMsg;

#ifdef DMT
    if (VOS_TRUE == g_stTestMsccPowerSaveSysCfgCnfFailure.ulMmcPowerSaveCnfFailureFlag)
    {
        pstPowerSaveCnf->enResult = NAS_MSCC_PIF_POWER_SAVE_FAILURE;
    }
#endif

    /* Stop the timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF);

    /* Check whether the Power save result is success or not
        1)If result is success get the next module and send power save request to next module
        2)If result is Success and Power save Module array is empty then get the next module from the system config array.
        3)If the system config array is empty send system config failure result.
        4)If result is failure send failure result */
    if ( NAS_MSCC_PIF_POWER_SAVE_SUCCESS == pstPowerSaveCnf->enResult )
    {
        /* Get the next module ID from power save modulr array */
        ulRslt      = NAS_MSCC_GetNextPowerSaveModuleId_SysCfg(&ulModuleId);

        if (VOS_TRUE == ulRslt)
        {
            /* send Power save request to next module */
            NAS_MSCC_SndPowerSaveReq_SysCfg(ulModuleId);
            return VOS_TRUE;
        }

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            NAS_MSCC_ProcDynamicLoad_SysCfg();
        }
#endif

        /* if the Power save module List is over
            get next module ID from system config MOdule list */
        ulRslt = NAS_MSCC_GetNextSysCfgModuleId_SysCfg(&ulModuleId);
        if (VOS_TRUE == ulRslt)
        {
            /* Send the System Config request to Next module */
            NAS_MSCC_SndSysCfgReq_SysCfg(ulModuleId);
            return VOS_TRUE;
        }

    }

    NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvMmcPowerSaveCnf_SysCfg_WaitMmcPowerSaveCnf:Result Failure!");

    /* send the failure result */
    NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_FAILURE);

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_SysCfg_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Print Warning Log */
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_SysCfg_WaitMmcPowerSaveCnf:time expired!");

    /* Reboot */
    NAS_MSCC_SoftReBoot(NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_MMC_POWER_SAVE_CNF_EXPIRED, WUEPS_PID_MMC);
    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_MSCC_RcvXsdSysCfgCnf_SysCfg_WaitXsdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_SYS_CFG_CNF_STRU          *pstSysCfgCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;
    pstSysCfgCnf                        = (XSD_MSCC_SYS_CFG_CNF_STRU*)pstMsg;

#ifdef DMT
    if (VOS_TRUE == g_stTestMsccPowerSaveSysCfgCnfFailure.ulXsdSysCfgCnfFailureFlag)
    {
        pstSysCfgCnf->enRst = NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER;
    }
#endif

    /* Stop the timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_XSD_SYS_CFG_CNF);

    /* Check whether the System config result is success or not
        1)If result is success get the next module and send System config request to next module.
        3)If the system config array is over send system config success result.
        4)If result is failure send failure result */
    if (NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS == pstSysCfgCnf->enRst)
    {
        /* Get next module ID from system config Module list */
        ulRslt = NAS_MSCC_GetNextSysCfgModuleId_SysCfg(&ulModuleId);
        if (VOS_TRUE == ulRslt)
        {
            /* Send the System Config request to Next module */
            NAS_MSCC_SndSysCfgReq_SysCfg(ulModuleId);
            return VOS_TRUE;
        }

        /* if the module array is empty send the Success result */
        NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_SUCCESS);

    }
    else
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvXsdSysCfgCnf_SysCfg_WaitXsdSysCfgCnf:Result Failure!");

        /* send the failure result */
        NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_FAILURE);

    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvTiWaitXsdSysCfgCnfExpired_SysCfg_WaitXsdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Print Warning Log */
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitXsdSysCfgCnfExpired_SysCfg_WaitXsdSysCfgCnf:time expired!");

    /* Process the timer expired message */

    /* Send the internal message */
    NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_FAILURE);

    /* Quit the sub FSM*/
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdSysCfgCnf_SysCfg_WaitHsdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_SYS_CFG_CNF_STRU          *pstSysCfgCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;
    pstSysCfgCnf                        = (HSD_MSCC_SYS_CFG_CNF_STRU*)pstMsg;

#ifdef DMT
    if (VOS_TRUE == g_stTestMsccPowerSaveSysCfgCnfFailure.ulHsdSysCfgCnfFailureFlag)
    {
        pstSysCfgCnf->enRst = NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER;
    }
#endif

    /* Stop the timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_HSD_SYS_CFG_CNF);

    /* Check whether the System config result is success or not
        1)If result is success get the next module and send System config request to next module.
        3)If the system config array is over send system config success result.
        4)If result is failure send failure result */
    if (NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS == pstSysCfgCnf->enRst)
    {
        /* Get next module ID from system config Module list */
        ulRslt = NAS_MSCC_GetNextSysCfgModuleId_SysCfg(&ulModuleId);
        if (VOS_TRUE == ulRslt)
        {
            /* Send the System Config request to Next module */
            NAS_MSCC_SndSysCfgReq_SysCfg(ulModuleId);
            return VOS_TRUE;
        }

        /* if the module array is empty send the Success result */
        NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_SUCCESS);

    }
    else
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,"NAS_MSCC_RcvHsdSysCfgCnf_SysCfg_WaitHsdSysCfgCnf:Result Failure!");

        /* send the failure result */
        NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_FAILURE);

    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvTiWaitHsdSysCfgCnfExpired_SysCfg_WaitHsdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Print ERROR LOG*/
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitHsdSysCfgCnfExpired_SysCfg_WaitHsdSysCfgCnf:time expired!");

    /* Process the timer expired message */

    /* Send the internal message */
    NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_FAILURE);

    /* Quit the sub FSM*/
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}
#endif


VOS_UINT32 NAS_MSCC_RcvMmcSysCfgCnf_SysCfg_WaitMmcSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SYS_CFG_SET_CNF_STRU      *pstSysCfgCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRslt;

    ulModuleId                          = 0;
    pstSysCfgCnf                        = (MMC_MSCC_SYS_CFG_SET_CNF_STRU*)pstMsg;

#ifdef DMT
    if (VOS_TRUE == g_stTestMsccPowerSaveSysCfgCnfFailure.ulMmcSysCfgCnfFailureFlag)
    {
        pstSysCfgCnf->enRst = NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER;
    }
#endif

    /* Stop the timer */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_SYS_CFG_CNF);

    /* Check whether the System config result is success or not
        1)If result is success get the next module and send System config request to next module.
        3)If the system config array is over send system config success result.
        4)If result is failure send failure result */
    if (NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS == pstSysCfgCnf->enRst)
    {
        /* Get next module ID from system config Module list */
        ulRslt = NAS_MSCC_GetNextSysCfgModuleId_SysCfg(&ulModuleId);
        if (VOS_TRUE == ulRslt)
        {
            /* Send the System Config request to Next module */
            NAS_MSCC_SndSysCfgReq_SysCfg(ulModuleId);
            return VOS_TRUE;
        }

        /* if the module array is empty send the Success result */
        NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_SUCCESS);
    }
    else
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvMmcSysCfgCnf_SysCfg_WaitMmcSysCfgCnf:Result Failure!");

        /* send the failure result */
        NAS_MSCC_SndSysCfgRslt(pstSysCfgCnf->enRst);

    }

    /* Quit the SubFSM */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvTiWaitMmcSysCfgCnfExpired_SysCfg_WaitMmcSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Print ERROR LOG*/
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcSysCfgCnfExpired_SysCfg_WaitMmcSysCfgCnf:time expired!");

    /* Process the timer expired message */

    /* Send the internal message */
    NAS_MSCC_SndSysCfgRslt(NAS_MSCC_SYS_CFG_RESULT_FAILURE);

    /* Quit the sub FSM*/
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


