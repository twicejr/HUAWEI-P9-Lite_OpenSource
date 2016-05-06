#ifndef __HIVDEC_SMMU_REGS_H__
#define __HIVDEC_SMMU_REGS_H__

/*******************************************************************************
**SMMU COMMON registers
*/
#define SMMU_SCR        (0x0000)

//non-secure
#define SMMU_INTSTAT_NS (0x0018)
#define SMMU_SMRx_NS    (0x0020)//(0x0020+n*0x4) SMMU control register per stream for non-secure
#define SMMU_RLD_EN0_NS (0x01F0)//SMR reload enable register
#define SMMU_RLD_EN1_NS (0x01F4)
#define SMMU_CB_TTBR0   (0x0204)//SMMU translation table base register for non-secure context bank0
#define SMMU_CB_TTBCR   (0x020C)//SMMU Translation Table Base Control Register for Non-Secure Context Bank
#define SMMU_ERR_RDADDR (0x0304)//SMMU Error Address of TLB miss for Read transaction
#define SMMU_ERR_WRADDR (0x0308)//SMMU Error Address of TLB miss for Write transaction

//secure
#define SMMU_SMRx_S     (0x0500)//(0x0500+n*0x4) SMMU control register per stream for secure
#define SMMU_RLD_EN0_S  (0x06F0)//SMR reload enable register
#define SMMU_RLD_EN1_S  (0x06F4)
#define SMMU_SCB_TTBR   (0x0718)//SMMU Translation Table Base Register for Secure Context Bank
#define SMMU_SCB_TTBCR  (0x071C)//Descriptor select for Secure Context Bank
/**********************************************/

/**********************************************
**MASTER(MFDE/SCD/BPD) registers
*/
#define REG_MFDE_MMU_CFG_SECURE (0x0008)
#define REG_MFDE_MMU_CFG_EN     (0x000c)
#define REG_SCD_MMU_CFG         (0x0820)
#define REG_BPD_MMU_CFG         (0x0004)
/***********************************************/

/*************************************************
**SMMU MASTER registers
*/
#define SMMU_MSTR_GLB_BYPASS    (0x0000)

#define SMMU_MSTR_DBG_0         (0x0010)
#define SMMU_MSTR_DBG_1         (0x0014)
#define SMMU_MSTR_DBG_2         (0x0018)
#define SMMU_MSTR_DBG_3         (0x001c)
#define SMMU_MSTR_DBG_4         (0x0020)
#define SMMU_MSTR_DBG_5         (0x0024)
#define SMMU_MSTR_DBG_6         (0x0028)

#define RD_CMD_TOTAL_CNT        (0x100)//q*0x4+0x100, q:0~19
#define RD_CMD_MISS_CNT         (0x150)//q*0x4+0x150
#define WR_CMD_TOTAL_CNT        (0x300)//r*0x4+0x300, r:0~11
#define WR_CMD_MISS_CNT         (0x330)//r*0x4+0x330
/***********************************************/
#endif
