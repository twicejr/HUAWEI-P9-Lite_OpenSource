
#include "vfmw_dts.h"
#include "sysconfig.h"
#include "public.h"


/* FPGA flag*/
UINT32  gIsFPGA           = 0;

/* register base addr & range */
UINT32  gVdhRegBaseAddr   = 0;
UINT32  gScdRegBaseAddr   = 0;
UINT32  gBpdRegBaseAddr   = 0;
UINT32  gVdhRegRange      = 0;
UINT32  gSOFTRST_REQ_Addr = 0;
UINT32  gSOFTRST_OK_ADDR  = 0;

/* smmu page table base addr */
UINT64  gSmmuPageBase     = 0;

/* irq num */
UINT32  gMfdeIrqNum       = 0;
UINT32  gScdIrqNum        = 0;
UINT32  gBpdIrqNum        = 0;
UINT32  gSmmuIrqNum       = 0;


SINT32 VFMW_SetDtsConfig(VFMW_DTS_CONFIG_S *pDtsConfig)
{
    if (NULL == pDtsConfig)
    {
        dprint(PRN_ERROR, "%s FATAL: pDtsConfig = NULL.\n", __func__);
        return VDEC_ERR;
    }
    
    if (0 == pDtsConfig->MfdeIrqNum     || 0 == pDtsConfig->ScdIrqNum
     || 0 == pDtsConfig->BpdIrqNum      || 0 == pDtsConfig->SmmuIrqNum
     || 0 == pDtsConfig->VdhRegBaseAddr || 0 == pDtsConfig->VdhRegRange
     || 0 == pDtsConfig->SmmuPageBaseAddr)
    {
        dprint(PRN_ERROR, "%s invalid param: IsFPGA=%d, MfdeIrqNum=%d, ScdIrqNum=%d, BpdIrqNum=%d, SmmuIrqNum=%d, VdhRegBaseAddr=%x, VdhRegSize=%d, SmmuPageBaseAddr=%llx\n", __func__, 
               pDtsConfig->IsFPGA, pDtsConfig->MfdeIrqNum, pDtsConfig->ScdIrqNum, pDtsConfig->BpdIrqNum, pDtsConfig->SmmuIrqNum, pDtsConfig->VdhRegBaseAddr, pDtsConfig->VdhRegRange, pDtsConfig->SmmuPageBaseAddr);
        return VDEC_ERR;
    }

    gIsFPGA           = pDtsConfig->IsFPGA;
    gMfdeIrqNum       = pDtsConfig->MfdeIrqNum;
    gScdIrqNum        = pDtsConfig->ScdIrqNum;
    gBpdIrqNum        = pDtsConfig->BpdIrqNum;
    gSmmuIrqNum       = pDtsConfig->SmmuIrqNum;
    
    gVdhRegBaseAddr   = pDtsConfig->VdhRegBaseAddr;
    gVdhRegRange      = pDtsConfig->VdhRegRange;
    gSmmuPageBase     = pDtsConfig->SmmuPageBaseAddr;
    
    gScdRegBaseAddr   = gVdhRegBaseAddr + SCD_REG_OFFSET;
    gBpdRegBaseAddr   = gVdhRegBaseAddr + BPD_REG_OFFSET;
    gSOFTRST_REQ_Addr = gVdhRegBaseAddr + SOFTRST_REQ_OFFSET;
    gSOFTRST_OK_ADDR  = gVdhRegBaseAddr + SOFTRST_OK_OFFSET;
    
#ifdef ENV_SOS_KERNEL    
    dprint(PRN_ALWS, "%s done: IsFPGA=%d, MfdeIrqNum=%d, ScdIrqNum=%d, BpdIrqNum=%d, SmmuIrqNum=%d, VdhRegBaseAddr=0x%x, VdhRegSize=%d, SmmuPageBaseAddr=0x%x\n", __func__, 
           pDtsConfig->IsFPGA, pDtsConfig->MfdeIrqNum, pDtsConfig->ScdIrqNum, pDtsConfig->BpdIrqNum, pDtsConfig->SmmuIrqNum, pDtsConfig->VdhRegBaseAddr, pDtsConfig->VdhRegRange, pDtsConfig->SmmuPageBaseAddr);
#endif

    return VDEC_OK;
}

SINT32 VFMW_GetDtsConfig(VFMW_DTS_CONFIG_S *pDtsConfig)
{
    if (NULL == pDtsConfig)
    {
        dprint(PRN_ERROR, "%s FATAL: pDtsConfig = NULL.\n", __func__);
        return VDEC_ERR;
    }
    
    pDtsConfig->IsFPGA           = gIsFPGA;
    pDtsConfig->MfdeIrqNum       = gMfdeIrqNum;
    pDtsConfig->ScdIrqNum        = gScdIrqNum;
    pDtsConfig->BpdIrqNum        = gBpdIrqNum;
    pDtsConfig->SmmuIrqNum       = gSmmuIrqNum;
    pDtsConfig->VdhRegBaseAddr   = gVdhRegBaseAddr;
    pDtsConfig->VdhRegRange      = gVdhRegRange;
    pDtsConfig->SmmuPageBaseAddr = gSmmuPageBase;
        
#if 0    
    dprint(PRN_ALWS, "%s done: MfdeIrqNum=%d, ScdIrqNum=%d, BpdIrqNum=%d, SmmuIrqNum=%d, VdhRegBaseAddr=0x%x, VdhRegSize=%d, SmmuPageBaseAddr=0x%x\n", __func__, 
           pDtsConfig->MfdeIrqNum, pDtsConfig->ScdIrqNum, pDtsConfig->BpdIrqNum, pDtsConfig->SmmuIrqNum, pDtsConfig->VdhRegBaseAddr, pDtsConfig->VdhRegSize, pDtsConfig->SmmuPageBaseAddr);
#endif

    return VDEC_OK;
}

SINT32 VFMW_IsDtsDataValid(VOID)
{
    if (0 == gMfdeIrqNum       || 0 == gScdIrqNum
     || 0 == gBpdIrqNum        || 0 == gSmmuIrqNum
     || 0 == gVdhRegBaseAddr   || 0 == gVdhRegRange
     || 0 == gScdRegBaseAddr   || 0 == gBpdRegBaseAddr
     || 0 == gSOFTRST_REQ_Addr || 0 == gSOFTRST_OK_ADDR
     || 0 == gSmmuPageBase)
    {
        dprint(PRN_ERROR, "CheckDtsConfig FAILED: gMfdeIrqNum=%d, gScdIrqNum=%d, gBpdIrqNum=%d, gSmmuIrqNum=%d, gVdhRegBaseAddr=%x, gVdhRegRange=%d, gScdRegBaseAddr%x, gBpdRegBaseAddr=%x, gSOFTRST_REQ_Addr=%x, gSOFTRST_OK_ADDR=%x, gSmmuPageBase=%llx\n",
               gMfdeIrqNum, gScdIrqNum, gBpdIrqNum, gSmmuIrqNum, gVdhRegBaseAddr, gVdhRegRange, gScdRegBaseAddr, gBpdRegBaseAddr, gSOFTRST_REQ_Addr, gSOFTRST_OK_ADDR, gSmmuPageBase);
        return VDEC_ERR;
    }

    return VDEC_OK;
}

#ifdef ENV_ARMLINUX_KERNEL
EXPORT_SYMBOL(VFMW_SetDtsConfig);
#endif

