#ifndef __HIVDEC_SMMU_H__
#define __HIVDEC_SMMU_H__

#include "sysconfig.h"//for VDM_REG_PHY_ADDR, SCD_REG_PHY_ADDR, BPD_REG_PHY_ADDR
#include "vfmw.h"

#define SMMU_OK     0
#define SMMU_ERR   -1

#define SECURE_ON   1
#define SECURE_OFF  0
#define SMMU_ON     1
#define SMMU_OFF    0

typedef enum{
    MFDE = 0,
    BPD,
    SCD,
}SMMU_MASTER_TYPE;

SINT32 SMMU_Init(VOID);
VOID SMMU_DeInit(VOID);
VOID SMMU_SetMasterReg(SMMU_MASTER_TYPE master_type, UINT8 secure_en, UINT8 mmu_en);
VOID SMMU_InitGlobalReg(VOID);
VOID SMMU_IntServProc(VOID);

#endif
