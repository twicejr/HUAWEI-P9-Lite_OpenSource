#ifndef __HI6XXX-IOMMU_H
#define __HI6XXX-IOMMU_H

#define SMMU_CTRL_OFFSET             (0x0000)
#define SMMU_ENABLE_OFFSET           (0x0004)
#define SMMU_PTBR_OFFSET             (0x0008)
#define SMMU_START_OFFSET            (0x000C)
#define SMMU_END_OFFSET              (0x0010)
#define SMMU_INTMASK_OFFSET          (0x0014)
#define SMMU_RINTSTS_OFFSET          (0x0018)
#define SMMU_MINTSTS_OFFSET          (0x001C)
#define SMMU_INTCLR_OFFSET           (0x0020)
#define SMMU_STATUS_OFFSET           (0x0024)
#define SMMU_AXIID_OFFSET            (0x0028)
#define SMMU_CNTCTRL_OFFSET          (0x002C)
#define SMMU_TRANSCNT_OFFSET         (0x0030)
#define SMMU_L0TLBHITCNT_OFFSET      (0x0034)
#define SMMU_L1TLBHITCNT_OFFSET      (0x0038)
#define SMMU_WRAPCNT_OFFSET          (0x003C)
#define SMMU_SEC_START_OFFSET        (0x0040)
#define SMMU_SEC_END_OFFSET          (0x0044)
#define SMMU_VERSION_OFFSET          (0x0048)
#define SMMU_IPTSRC_OFFSET           (0x004C)
#define SMMU_IPTPA_OFFSET            (0x0050)
#define SMMU_TRBA_OFFSET             (0x0054)
#define SMMU_BYS_START_OFFSET        (0x0058)
#define SMMU_BYS_END_OFFSET          (0x005C)
#define SMMU_RAM_OFFSET              (0x1000)
#define SMMU_REGS_MAX                (15)
#define SMMU_REGS_SGMT_END           (0x60)

#define SMMU_CHIP_ID_V100            (1)
#define SMMU_CHIP_ID_V200            (2)

#define SMMU_REGS_OPS_SEGMT_START    (0xf00)
#define SMMU_REGS_OPS_SEGMT_NUMB     (8)
#define SMMU_REGS_AXI_SEGMT_START    (0xf80)
#define SMMU_REGS_AXI_SEGMT_NUMB     (8)

#define SMMU_INIT                    (0x1)
#define SMMU_RUNNING                 (0x2)
#define SMMU_SUSPEND                 (0x3)
#define SMMU_STOP                    (0x4)

#define PAGE_ENTRY_VALID             (0x1)

#endif
