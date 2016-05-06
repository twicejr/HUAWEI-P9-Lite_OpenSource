#ifdef ENV_ARMLINUX_KERNEL
#include <asm/memory.h>
#include <linux/types.h>
#include <linux/gfp.h>
#endif

#include "smmu.h"
#include "smmu_regs.h"
#include "public.h"

#define SMRx_ID_SIZE            32
#define SMMU_RWERRADDR_SIZE     128

#define HIVDEC_SMMU_COMMON_OFFSET	(0xE000)
#define HIVDEC_SMMU_MASTER_OFFSET	(0xF000)

#define HIVDEC_SMMU_COMMON_BASE_ADDR (gVdhRegBaseAddr + HIVDEC_SMMU_COMMON_OFFSET)
#define HIVDEC_SMMU_MASTER_BASE_ADDR (gVdhRegBaseAddr + HIVDEC_SMMU_MASTER_OFFSET)

//SMMU common and Master(MFDE/SCD/BPD) virtual base address
typedef struct{
    SINT32 *pSMMUCommonBaseVirAddr;
    SINT32 *pSMMUMasterBaseVirAddr;
    SINT32 *pSMMUMFDERegVirAddr;
    SINT32 *pSMMUBPDRegVirAddr;
    SINT32 *pSMMUSCDRegVirAddr;	
}SMMU_REG_VIR_S;

SMMU_REG_VIR_S gSmmuRegVir;
MEM_DESC_S gAllocMem_RD;
MEM_DESC_S gAllocMem_WR;

SINT32 gSmmuInitFlag    = 0;
SINT32 gMfdeSecureFlag  = 0;
SINT32 gMfdeSmmuFlag    = 1;
SINT32 gScdSecureFlag   = 0;
SINT32 gScdSmmuFlag     = 1;
SINT32 gBpdSecureFlag   = 0;
SINT32 gBpdSmmuFlag     = 0;

//smmu common regs r/w
#define RD_SMMU_COMMON_VREG( reg, dat )               \
do {                    \
    dat = *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUCommonBaseVirAddr + reg)); \
} while(0)

#define WR_SMMU_COMMON_VREG( reg, dat )               \
do {                    \
    *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUCommonBaseVirAddr + reg)) = dat; \
} while(0)
//smmu master regs r/w
#define RD_SMMU_MASTER_VREG( reg, dat )               \
do {                    \
    dat = *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUMasterBaseVirAddr + reg)); \
} while(0)

#define WR_SMMU_MASTER_VREG( reg, dat )               \
do {                    \
    *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUMasterBaseVirAddr + reg)) = dat; \
} while(0)

//mfde regs r/w
#define RD_SMMU_MFDE_VREG( reg, dat )               \
do {                    \
    dat = *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUMFDERegVirAddr + reg)); \
} while(0)

#define WR_SMMU_MFDE_VREG( reg, dat )               \
do {                    \
    *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUMFDERegVirAddr + reg)) = dat; \
} while(0)
//bpd regs r/w
#define RD_SMMU_BPD_VREG( reg, dat )               \
do {                    \
    dat = *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUBPDRegVirAddr + reg)); \
} while(0)

#define WR_SMMU_BPD_VREG( reg, dat )               \
do {                    \
    *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUBPDRegVirAddr + reg)) = dat; \
} while(0)
//scd regs r/w
#define RD_SMMU_SCD_VREG( reg, dat )               \
do {                    \
    dat = *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUSCDRegVirAddr + reg)); \
} while(0)

#define WR_SMMU_SCD_VREG( reg, dat )               \
do {                    \
    *((volatile SINT32*)((SINT8*)gSmmuRegVir.pSMMUSCDRegVirAddr + reg)) = dat; \
} while(0)

#if 0
static VOID dump_regs()
{
    SINT32 tmp = -1;

    RD_SMMU_COMMON_VREG(SMMU_SCR, tmp);
    dprint(PRN_ALWS,"%s,  SMMU_SCR = %x\n", __func__, tmp);
    RD_SMMU_COMMON_VREG(SMMU_SMRx_NS, tmp);
    dprint(PRN_ALWS,"%s,  SMMU_SMRx_NS = %x\n", __func__, tmp);
    RD_SMMU_COMMON_VREG(SMMU_RLD_EN0_NS, tmp);
    dprint(PRN_ALWS,"%s,  SMMU_RLD_EN0_NS = %x\n", __func__, tmp);
    RD_SMMU_COMMON_VREG(SMMU_RLD_EN1_NS, tmp);
    dprint(PRN_ALWS,"%s,  SMMU_RLD_EN1_NS = %x\n", __func__, tmp);
    RD_SMMU_COMMON_VREG(SMMU_CB_TTBR0, tmp);
    dprint(PRN_ALWS,"%s,  SMMU_CB_TTBR0 = %x\n", __func__, tmp);

    RD_SMMU_MASTER_VREG(0, tmp);
    dprint(PRN_ALWS,"%s,  master glb_bypass = %x\n", __func__, tmp);

}

static VOID dump_master_regs(SMMU_MASTER_TYPE master_type)
{
    SINT32 tmp = -1;

    switch(master_type)
    {
        case MFDE:
            RD_SMMU_MFDE_VREG(REG_MFDE_MMU_CFG_EN, tmp);
            dprint(PRN_ALWS,"%s,  REG_MFDE_MMU_CFG_EN[12] = %x\n", __func__, tmp);
            RD_SMMU_MFDE_VREG(REG_MFDE_MMU_CFG_SECURE, tmp);
            dprint(PRN_ALWS,"%s,  REG_MFDE_MMU_CFG_SECURE[31] = %x\n", __func__, tmp);
            break;
        case SCD:
            RD_SMMU_SCD_VREG(REG_SCD_MMU_CFG, tmp);
            dprint(PRN_ALWS,"%s,  REG_SCD_MMU_CFG = %x\n", __func__, tmp);
            break;
        case BPD:
            RD_SMMU_BPD_VREG(REG_BPD_MMU_CFG, tmp);
            dprint(PRN_ALWS,"%s,  REG_BPD_MMU_CFG = %x\n", __func__, tmp);
            break;
    }

}
#endif 

/**
 *function: set SMMU common register
 *addr: register's vir addr
 *val: value to be set
 *bw: bit width
 *bs: bit start
 */
static VOID set_common_reg(UADDR addr, SINT32 val, SINT32 bw, SINT32 bs)
{
    SINT32 mask = (1UL << bw) - 1UL;
    SINT32 tmp = 0;

    RD_SMMU_COMMON_VREG(addr, tmp);
    tmp &= ~(mask << bs);
    WR_SMMU_COMMON_VREG(addr, tmp | ((val & mask) << bs));
}

/**
 *function: set SMMU master register
 *addr: register's vir addr
 *val: value to be set
 *bw: bit width
 *bs: bit start
 */
static VOID set_master_reg(UADDR addr, SINT32 val, SINT32 bw, SINT32 bs)
{
    SINT32 mask = (1UL << bw) - 1UL;
    SINT32 tmp = 0;

    RD_SMMU_MASTER_VREG(addr, tmp);
    tmp &= ~(mask << bs);
    WR_SMMU_MASTER_VREG(addr, tmp | ((val & mask) << bs));
   
}

/**
 *function: set mfde/scd/bpd register
 *master_type: MFDE/SCD/BPD
 *addr: register's vir addr
 *val: value to be set
 *bw: bit width
 *bs: bit start
 */
static VOID set_vdh_master_reg(SMMU_MASTER_TYPE master_type, UADDR addr, SINT32 val, SINT32 bw, SINT32 bs)
{
    SINT32 mask = (1UL << bw) - 1UL;
    SINT32 tmp = 0;

    switch(master_type)
    {
    case MFDE:
        RD_SMMU_MFDE_VREG(addr, tmp);
        tmp &= ~(mask << bs);
        WR_SMMU_MFDE_VREG(addr, tmp | ((val & mask) << bs));
        break;
    case BPD:
        RD_SMMU_BPD_VREG(addr, tmp);
        tmp &= ~(mask << bs);
        WR_SMMU_BPD_VREG(addr, tmp | ((val & mask) << bs));
        break;
    case SCD:
        RD_SMMU_SCD_VREG(addr, tmp);
        tmp &= ~(mask << bs);
        WR_SMMU_SCD_VREG(addr, tmp | ((val & mask) << bs));
        break;
    default:
        break;
    }
}

/**
 *function: set mfde mmu cfg register
 */
static VOID set_mmu_cfg_reg_mfde(SMMU_MASTER_TYPE master_type, UINT32 secure_en, UINT32 mmu_en)
{
    if (mmu_en)//MMU enable
    {
        set_vdh_master_reg(master_type, REG_MFDE_MMU_CFG_EN, 0x1, 1, 12);//[12]mmu_en=1
        if (secure_en)//secure
        {
            dprint(PRN_ALWS, "IN %s not support this mode: mmu_en:secure!\n", __func__);
            dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_MFDE_MMU_CFG_SECURE, 0x1, 1, 31);//[31]secure_en=1
        }
        else//non-secure
        {
            //dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_MFDE_MMU_CFG_SECURE, 0x0, 1, 31);//[31]secure_en=0
        }
    }
    else//MMU disable
    {
        set_vdh_master_reg(master_type, REG_MFDE_MMU_CFG_EN, 0x0, 1, 12);//[12]mmu_en=0
        if (secure_en)//secure
        {
            //dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_MFDE_MMU_CFG_SECURE, 0x1, 1, 31);//[31]secure_en=1
        }
        else//non-secure
        {
            dprint(PRN_ALWS, "IN %s not support this mode: non_mmu:non_secure!\n", __func__);
            dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_MFDE_MMU_CFG_SECURE, 0x0, 1, 31);//[31]secure_en=0
        }
    }
}

/**
 *function: set bpd mmu cfg register
 */
static VOID set_mmu_cfg_reg_bpd(SMMU_MASTER_TYPE master_type, UINT32 secure_en, UINT32 mmu_en)
{
    if (mmu_en)//MMU enable
    {
        set_vdh_master_reg(master_type, REG_BPD_MMU_CFG, 0x1, 1, 21);//[21]mmu_en=1
        if (secure_en)//secure
        {
            dprint(PRN_ALWS, "IN %s not support this mode: mmu_en:secure!\n", __func__);
            dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_BPD_MMU_CFG, 0x1, 1, 20);//[20]secure_en=1
        }
        else//non-secure
        {
            //dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_BPD_MMU_CFG, 0x0, 1, 20);//[20]secure_en=0
        }
    }
    else//MMU disable
    {
        set_vdh_master_reg(master_type, REG_BPD_MMU_CFG, 0x0, 1, 21);//[21]mmu_en=0
        if (secure_en)//secure
        {
            //dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_BPD_MMU_CFG, 0x1, 1, 20);//[20]secure_en=1
        }
        else//non-secure
        {
            dprint(PRN_ALWS, "IN %s not support this mode: non_mmu:non_secure!\n", __func__);
            dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_BPD_MMU_CFG, 0x0, 1, 20);//[20]secure_en=0
        }
    }
}

/**
 *function: set scd mmu cfg register
 */
static VOID set_mmu_cfg_reg_scd(SMMU_MASTER_TYPE master_type, UINT32 secure_en, UINT32 mmu_en)
{
    if (mmu_en)//MMU enable
    {
        set_vdh_master_reg(master_type, REG_SCD_MMU_CFG, 0x1, 1, 9);//[9]mmu_en=1
        if (secure_en)//secure
        {
            dprint(PRN_ALWS, "IN %s not support this mode: mmu_en:secure!\n", __func__);
            dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_SCD_MMU_CFG, 0x1, 1, 7);//[7]secure_en=1
        }
        else//non-secure
        {
            //dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_SCD_MMU_CFG, 0x0, 1, 7);//[7]secure_en=0
        }
    }
    else//MMU disable
    {
        set_vdh_master_reg(master_type, REG_SCD_MMU_CFG, 0x0, 1, 9);//[9]mmu_en=0
        if (secure_en)//secure
        {
            //dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_SCD_MMU_CFG, 0x1, 1, 7);//[7]secure_en=1
        }
        else//non-secure
        {
            dprint(PRN_ALWS, "IN %s not support this mode: non_mmu:non_secure!\n", __func__);
            dprint(PRN_ALWS, "%s, secure_en:%d, mmu_en:%d\n", __func__, secure_en, mmu_en);
            set_vdh_master_reg(master_type, REG_SCD_MMU_CFG, 0x0, 1, 7);//[7]secure_en=0
        }
    }
}

/**
 *function: Alloc MEM for TLB miss .
 */
static SINT32 alloc_smmu_tlb_miss_addr(VOID)
{
    SINT32 ret = OSAL_ERR;

    memset(&gAllocMem_RD, 0, sizeof(MEM_DESC_S));
    memset(&gAllocMem_WR, 0, sizeof(MEM_DESC_S));
    
    gAllocMem_RD.MemType = MEM_CMA_ZERO;
    ret = VFMW_OSAL_MemAlloc("SMMU_RDERR", SMMU_RWERRADDR_SIZE, 4, 0, &gAllocMem_RD);
    if (ret != OSAL_OK)
    {
        dprint(PRN_FATAL, "%s kzalloc mem for smmu rderr failed!\n", __func__);
        return SMMU_ERR;
    }

    gAllocMem_WR.MemType = MEM_CMA_ZERO;
    ret = VFMW_OSAL_MemAlloc("SMMU_WRERR", SMMU_RWERRADDR_SIZE, 4, 0, &gAllocMem_WR);
    if (ret != OSAL_OK)
    {
        dprint(PRN_FATAL, "%s kzalloc mem for smmu wrerr failed!\n", __func__);
        VFMW_OSAL_MemFree(&gAllocMem_RD);
        return SMMU_ERR;
    }

    return SMMU_OK;
}

/**
 *function: init SMMU global registers.
 */
VOID SMMU_InitGlobalReg(VOID)
{
    UINT32 i = 0;
    if (1 == gSmmuInitFlag)
    {
        //0000 0000 0000 1111 0000 0000 0011 1000 --> 0x000f0038
        set_common_reg(SMMU_SCR, 0x0, 1, 0);//SMMU_SCR[0].glb_bypass
        set_common_reg(SMMU_SCR, 0x7, 3, 3);//SMMU_SCR[3].int_en, SMMU_SCR[4].cache_l1_en, SMMU_SCR[5].cache_l2_en
        set_common_reg(SMMU_SCR, 0xF, 4, 16);//SMMU_SCR[19:16].ptw_pf, Maximum read outstanding of PTW request.
        set_common_reg(SMMU_SCR, 0x0, 8, 20);//SMMU_SCR[27:20].ptw_mid, MID of PTW request.

        //SMRX_S had set default value. Only need to set SMMU_SMRx_NS secure SID  bypass
        //SMMU_SMRx[0]smr_bypass=0(non-bypass); SMMU_SMRx[4]smr_invld_en=0x1; SMMU_SMRx[5:11]smr_ptw_qos=0x3;
        for (i = 0; i < SMRx_ID_SIZE; i += 2)
        {
            set_common_reg(SMMU_SMRx_NS + i*0x4, 0x70, 32, 0);//0x00000003 none secure
        }
        for (i = 1; i < SMRx_ID_SIZE; i += 2)
        {
            set_common_reg(SMMU_SMRx_NS + i*0x4, 0x71, 32, 0);//0x00000002 secure
        }

        set_common_reg(SMMU_RLD_EN0_NS, 0x0, 32, 0);
        set_common_reg(SMMU_RLD_EN1_NS, 0x0, 32, 0);

        set_common_reg(SMMU_CB_TTBR0, gSmmuPageBase, 32, 0);
        set_common_reg(SMMU_CB_TTBCR, 0x1, 1, 0);

        if (gAllocMem_RD.PhyAddr != 0 && gAllocMem_WR.PhyAddr != 0)
        {
            set_common_reg(SMMU_ERR_RDADDR, gAllocMem_RD.PhyAddr, 32, 0);
            set_common_reg(SMMU_ERR_WRADDR, gAllocMem_WR.PhyAddr, 32, 0);
        }

        //glb_bypass, 0x0: normal mode, 0x1: bypass mode
        set_master_reg(SMMU_MSTR_GLB_BYPASS, 0x0, 32, 0);//master mmu enable
        
        //dprint(PRN_ALWS, "Init smmu global reg success.\n");
    }
    else
    {
        return;
    }
}

/**
 *function: set MFDE/SCD/BPD mmu cfg register, MMU or secure.
 */
VOID SMMU_SetMasterReg(SMMU_MASTER_TYPE master_type, UINT8 secure_en, UINT8 mmu_en)
{
    switch(master_type)
    {
    case MFDE:
        set_mmu_cfg_reg_mfde(master_type, secure_en, mmu_en);
        gMfdeSecureFlag = secure_en;
        gMfdeSmmuFlag  = mmu_en;
        break;
    case SCD:
        set_mmu_cfg_reg_scd(master_type, secure_en, mmu_en);
        gScdSecureFlag = secure_en;
        gScdSmmuFlag  = mmu_en;
        break;
    case BPD:
        set_mmu_cfg_reg_bpd(master_type, secure_en, mmu_en);
        gBpdSecureFlag = secure_en;
        gBpdSmmuFlag  = mmu_en;
        break;
    default:
        dprint(PRN_FATAL, "%s unkown master type %d\n", __func__, master_type);
        break;        
    }
}

VOID SMMU_IntServProc(VOID)
{
    SINT32 tmp = -1;
    dprint(PRN_ALWS, "%s enter", __func__);
    RD_SMMU_COMMON_VREG(SMMU_INTSTAT_NS, tmp);
    dprint(PRN_ALWS, "SMMU_INTSTAT_NS = 0x%x\n", tmp);
    RD_SMMU_MASTER_VREG(SMMU_MSTR_DBG_0, tmp);
    dprint(PRN_ALWS, "SMMU_MSTR_DBG_0 = 0x%x\n", tmp);
    RD_SMMU_MASTER_VREG(SMMU_MSTR_DBG_1, tmp);
    dprint(PRN_ALWS, "SMMU_MSTR_DBG_1 = 0x%x\n", tmp);
    RD_SMMU_MASTER_VREG(SMMU_MSTR_DBG_2, tmp);
    dprint(PRN_ALWS, "SMMU_MSTR_DBG_2 = 0x%x\n", tmp);
    RD_SMMU_MASTER_VREG(SMMU_MSTR_DBG_3, tmp);
    dprint(PRN_ALWS, "SMMU_MSTR_DBG_3 = 0x%x\n", tmp);
    RD_SMMU_MASTER_VREG(SMMU_MSTR_DBG_4, tmp);
    dprint(PRN_ALWS, "SMMU_MSTR_DBG_4 = 0x%x\n", tmp);
    RD_SMMU_MASTER_VREG(SMMU_MSTR_DBG_5, tmp);
    dprint(PRN_ALWS, "SMMU_MSTR_DBG_5 = 0x%x\n", tmp);
    RD_SMMU_MASTER_VREG(SMMU_MSTR_DBG_6, tmp);
    dprint(PRN_ALWS, "SMMU_MSTR_DBG_6 = 0x%x\n", tmp);
    dprint(PRN_ALWS, "%s end", __func__);
}

/**
 *function: get registers virtual address, and alloc mem for TLB miss.
 */
SINT32 SMMU_Init(VOID)
{
    SINT32 ret = SMMU_ERR;
    memset(&gSmmuRegVir, 0, sizeof(SMMU_REG_VIR_S));

    gSmmuRegVir.pSMMUMFDERegVirAddr   = (SINT32 *)MEM_Phy2Vir(gVdhRegBaseAddr);
    if (NULL == gSmmuRegVir.pSMMUMFDERegVirAddr)
    {
        dprint(PRN_FATAL, "%s pSMMUMFDERegVirAddr = NULL, SMMU Init failed!\n", __func__);
        return SMMU_ERR;
    }
    gSmmuRegVir.pSMMUSCDRegVirAddr   = (SINT32 *)MEM_Phy2Vir(gScdRegBaseAddr);
    if (NULL == gSmmuRegVir.pSMMUSCDRegVirAddr)
    {
        dprint(PRN_FATAL, "%s pSMMUSCDRegVirAddr = NULL, SMMU Init failed!\n", __func__);
        return SMMU_ERR;
    }
    gSmmuRegVir.pSMMUBPDRegVirAddr   = (SINT32 *)MEM_Phy2Vir(gBpdRegBaseAddr);
    if (NULL == gSmmuRegVir.pSMMUBPDRegVirAddr)
    {
        dprint(PRN_FATAL, "%s pSMMUBPDRegVirAddr = NULL, SMMU Init failed!\n", __func__);
        return SMMU_ERR;
    }
    gSmmuRegVir.pSMMUCommonBaseVirAddr   = (SINT32 *)MEM_Phy2Vir(HIVDEC_SMMU_COMMON_BASE_ADDR);
    if (NULL == gSmmuRegVir.pSMMUCommonBaseVirAddr)
    {
        dprint(PRN_FATAL, "%s pSMMUCommonBaseVirAddr = NULL, SMMU Init failed!\n", __func__);
        return SMMU_ERR;
    }
    gSmmuRegVir.pSMMUMasterBaseVirAddr   = (SINT32 *)MEM_Phy2Vir(HIVDEC_SMMU_MASTER_BASE_ADDR);
    if (NULL == gSmmuRegVir.pSMMUMasterBaseVirAddr)
    {
        dprint(PRN_FATAL, "%s pSMMUMasterBaseVirAddr = NULL, SMMU Init failed!\n", __func__);
        return SMMU_ERR;
    }

    ret = alloc_smmu_tlb_miss_addr();
    if (ret != SMMU_OK)
    {
        dprint(PRN_FATAL, "%s alloc_smmu_tlb_miss_addr failed!\n",  __func__);
        return SMMU_ERR;
    }

    gSmmuInitFlag = 1;
    
    return SMMU_OK;
}

/**
 *function: free mem of SMMU_ERR_RDADDR and SMMU_ERR_WRADDR.
 */
VOID SMMU_DeInit(VOID)
{
    if (gAllocMem_RD.PhyAddr != 0)
    {
        VFMW_OSAL_MemFree(&gAllocMem_RD);
    }
    if (gAllocMem_WR.PhyAddr != 0)
    {
        VFMW_OSAL_MemFree(&gAllocMem_WR);
    }
}

