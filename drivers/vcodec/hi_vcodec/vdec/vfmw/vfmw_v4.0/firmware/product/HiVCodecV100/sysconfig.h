/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfvzHyMxSEsfcbL/G0fFswaAZ8tsS4we+PBWC6a/UNlzCWIaw+Ujkv9NAY+as0
fg7WZIRvw27AjvRqJbkRJvqFUORSa6KPQaSBMxCxJTGTTf//sQbjPOyYldN0OVR9ut4HFO4U
ZguGQVqcOAJQbE96v6175DqhuprKgQB8R+2fu7VD3qtX+ZJh/t0512oqv+e8YA==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
#ifndef __VFMW_SYSCONFIG_HEADER__
#define __VFMW_SYSCONFIG_HEADER__

#include "vfmw.h"

/* valid vdh num */
#define MAX_VDH_NUM              (1)
#define MAX_SCD_NUM              (MAX_VDH_NUM)

/* test memory config, not used in release version */
#define BOARD_MEM_BASE_ADDR      (0x0E000000)
#define BOARD_MEM_TOTAL_SIZE     (500*1024*1024) 

/* register offset */
#define SCD_REG_OFFSET           (0xc000)
#define BPD_REG_OFFSET           (0xd000)

#define SOFTRST_REQ_OFFSET       (0xf80c)
#define SOFTRST_OK_OFFSET        (0xf810)

#define ALL_RESET_CTRL_BIT       (0)
#define MFDE_RESET_CTRL_BIT      (1)
#define SCD_RESET_CTRL_BIT       (2)
#define BPD_RESET_CTRL_BIT       (3)

#define ALL_RESET_OK_BIT         (0)
#define MFDE_RESET_OK_BIT        (1)
#define SCD_RESET_OK_BIT         (2)
#define BPD_RESET_OK_BIT         (3)

/* FPGA flag */
extern UINT32  gIsFPGA;

/* register base addr & range */
extern UINT32  gVdhRegBaseAddr;
extern UINT32  gScdRegBaseAddr;
extern UINT32  gBpdRegBaseAddr;
extern UINT32  gVdhRegRange;
extern UINT32  gSOFTRST_REQ_Addr;
extern UINT32  gSOFTRST_OK_ADDR;

/* smmu page table base addr */
extern UINT64  gSmmuPageBase;

/* irq num */
extern UINT32  gMfdeIrqNum;
extern UINT32  gScdIrqNum;
extern UINT32  gBpdIrqNum;
extern UINT32  gSmmuIrqNum;

#endif
