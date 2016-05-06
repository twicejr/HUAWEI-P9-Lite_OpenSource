//******************************************************************************
//   Project name : SOC
//   File    name : reg_addr_def.hpp
//   Description  : Module Information
//   Author       :f57854
//
//   All Right Reserved
//******************************************************************************

#ifndef _REG_ADDR_H_
#define _REG_ADDR_H_
/*******************************************************/
#define     BIT_SMMU_BRST_DIS           (1 << 0)    //TBU dis-reset bit
#define     BIT_SMMU_CRST_DIS           (1 << 1)    //TCU dis-reset bit

#define     BIT_SMMU_BRST_EN            (1 << 0)    //TBU reset bit
#define     BIT_SMMU_CRST_EN            (1 << 1)    //TCU reset bit
#define     IVP_SMMU_CB_VMID_NS    (0)		    //vmid  for ivp.NON_SEC

#define BIT_BUS_GATE_CLOCK_X2X_ACLK                (0x01 << 11)
#define BIT_BUS_GATE_CLOCK_IVP32_CFG_PCLK          (0x01 << 10)
#define BIT_BUS_GATE_CLOCK_X2P_ACLN                (0x01 << 9)
#define BIT_BUS_GATE_CLOCK_X2P_PCLN                (0x01 << 8)
#define BIT_BUS_GATE_CLOCK_DEFAULT_SLN             (0x01 << 7)
#define BIT_BUS_GATE_CLOCK_DW_AXI_S5               (0x01 << 6)
#define BIT_BUS_GATE_CLOCK_DW_AXI_S4               (0x01 << 5)
#define BIT_BUS_GATE_CLOCK_DW_AXI_S3               (0x01 << 4)
#define BIT_BUS_GATE_CLOCK_DW_AXI_S2               (0x01 << 3)
#define BIT_BUS_GATE_CLOCK_DW_AXI_S1               (0x01 << 2)
#define BIT_BUS_GATE_CLOCK_DW_AXI_M2               (0x01 << 1)
#define BIT_BUS_GATE_CLOCK_DW_AXI_M1               (0x01 << 0)

#define BIT_SMMU_TCU_HWGT_BYPASS                   (0x01 << 3)
#define BIT_SMMU_TBU_HWGT_BYPASS                   (0x01 << 2)
#define BIT_SMMU_TCU_AWOKE_BYPASS                  (0x01 << 1)
#define BIT_SMMU_TBU_AWOKE_BYPASS                  (0x01 << 0)

#define BIT_SMMU_TCU_PWR_HANDSHAKE_ST              (0x01 << 1)
#define BIT_SMMU_TBU_PWR_HANDSHAKE_ST              (0x01 << 1)

/******************************************************/

/******addr defines for block IVP_CFG_NON_SEC_REG******/
#define IVP_REG_OFF_PRID                           (0x0000)
#define IVP_REG_OFF_OCDHALTONRESET                 (0x0004)
#define IVP_REG_OFF_STATVECTORSEL                  (0x0008)
#define IVP_REG_OFF_RUNSTALL                       (0x000c)
#define IVP_REG_OFF_PWAITMODE                      (0x0010)
#define IVP_REG_OFF_BINTERRUPT                     (0x0100)
#define IVP_REG_OFF_NMI                            (0x0104)
#define IVP_REG_OFF_DSP_CORE_RESET_EN              (0x0200)
#define IVP_REG_OFF_DSP_CORE_RESET_DIS             (0x0204)
#define IVP_REG_OFF_DSP_CORE_RESET_STATUS          (0x0208) 
#define IVP_REG_OFF_REF_CLOCK_SEL                  (0x020c)
#define IVP_REG_OFF_APB_GATE_CLOCK                 (0x0210)
#define IVP_REG_OFF_BUS_GATE_CLOCK                 (0x0214)
#define IVP_REG_OFF_TIMER_WDG_RST_EN               (0x0218)
#define IVP_REG_OFF_TIMER_WDG_RST_DIS              (0x021c)
#define IVP_REG_OFF_TIMER_WDG_RST_STATUS           (0x0220)
#define IVP_REG_OFF_DSPCORE_GATE                   (0x0224)
#define IVP_REG_OFF_DSPCRE_GATE_ST                 (0x0228)
#define IVP_REG_OFF_INTERCONNECT_PRIORITY_CFG      (0x030c)
#define IVP_REG_OFF_IVP_SYSTEM_QOS_CFG           (0x0310)
#define IVP_REG_OFF_MEM_CTRL0                      (0x0320)
#define IVP_REG_OFF_MEM_CTRL1                      (0x0324)
#define IVP_REG_OFF_MEM_CTRL2                      (0x0328)
#define IVP_REG_OFF_CRG_PERI_GT_ST                 (0x032c)
#define IVP_REG_OFF_SMMU_AWAKEBYPASS               (0x0330)
#define IVP_REG_OFF_SMMU_PWR_HANDSHAKE_ST          (0x033c)
#define IVP_REG_OFF_APB_IF_DLOCK_BYPASS            (0x0340)
#define IVP_REG_OFF_ADDR_MON_EN                    (0x0400)
#define IVP_REG_OFF_ADDR_MON_CLR                   (0x0404)
#define IVP_REG_OFF_ADDR_MON_INTR_EN               (0x0408)
#define IVP_REG_OFF_ADDR_MON_INTR_STAT             (0x040c)
#define IVP_REG_OFF_ADDR_MON0_ADDR_BASE            (0x0410)
#define IVP_REG_OFF_ADDR_MON0_ADDR_LEN             (0x0414)
#define IVP_REG_OFF_ADDR_MON0_HIT_AWADDR           (0x0418)
#define IVP_REG_OFF_ADDR_MON0_HIT_ARADDR           (0x041c)
#define IVP_REG_OFF_ADDR_MON1_ADDR_BASE            (0x0420)
#define IVP_REG_OFF_ADDR_MON1_ADDR_LEN             (0x0424)
#define IVP_REG_OFF_ADDR_MON1_HIT_AWADDR           (0x0428)
#define IVP_REG_OFF_ADDR_MON1_HIT_ARADDR           (0x042c)
#define IVP_REG_OFF_ADDR_MON2_ADDR_BASE            (0x0430)
#define IVP_REG_OFF_ADDR_MON2_ADDR_LEN             (0x0434)
#define IVP_REG_OFF_ADDR_MON2_HIT_AWADDR           (0x0438)
#define IVP_REG_OFF_ADDR_MON2_HIT_ARADDR           (0x043c)
#define IVP_REG_OFF_ADDR_MON3_ADDR_BASE            (0x0440)
#define IVP_REG_OFF_ADDR_MON3_ADDR_LEN             (0x0444)
#define IVP_REG_OFF_ADDR_MON3_HIT_AWADDR           (0x0448)
#define IVP_REG_OFF_ADDR_MON3_HIT_ARADDR           (0x044c)
#define IVP_REG_OFF_ADDR_MON4_ADDR_BASE            (0x0450)
#define IVP_REG_OFF_ADDR_MON4_ADDR_LEN             (0x0454)
#define IVP_REG_OFF_ADDR_MON4_HIT_AWADDR           (0x0458)
#define IVP_REG_OFF_ADDR_MON4_HIT_ARADDR           (0x045c)
#define IVP_REG_OFF_ADDR_MON5_ADDR_BASE            (0x0460)
#define IVP_REG_OFF_ADDR_MON5_ADDR_LEN             (0x0464)
#define IVP_REG_OFF_ADDR_MON5_HIT_AWADDR           (0x0468)
#define IVP_REG_OFF_ADDR_MON5_HIT_ARADDR           (0x046c)
#define IVP_REG_OFF_ADDR_MON6_ADDR_BASE            (0x0470)
#define IVP_REG_OFF_ADDR_MON6_ADDR_LEN             (0x0474)
#define IVP_REG_OFF_ADDR_MON6_HIT_AWADDR           (0x0478)
#define IVP_REG_OFF_ADDR_MON6_HIT_ARADDR           (0x047c)
#define IVP_REG_OFF_ADDR_MON7_ADDR_BASE            (0x0480)
#define IVP_REG_OFF_ADDR_MON7_ADDR_LEN             (0x0484)
#define IVP_REG_OFF_ADDR_MON7_HIT_AWADDR           (0x0488)
#define IVP_REG_OFF_ADDR_MON7_HIT_ARADDR           (0x048c)
#define IVP_REG_OFF_SMMU_SW_GT                     (0x0500)
#define IVP_REG_OFF_SMMU_GT_ST                     (0x0504)
#define IVP_REG_OFF_SMMU_HW_GT_CNT                 (0x050c)
#define IVP_REG_OFF_SMMU_RST_EN                    (0x0510)
#define IVP_REG_OFF_SMMU_RST_DIS                   (0x0514)
#define IVP_REG_OFF_SMMU_RST_ST                    (0x0518)
#define IVP_REG_OFF_SUBSYS_VERSION_NUM             (0x0800)

/******addr defines for block IVP_CFG_SEC_REG******/
#define ADDR_IVP_CFG_SEC_REG_IVP_SLV_SEC_SEL 768
#define ADDR_IVP_CFG_SEC_REG_IVP_MST_SEC_SEL 772
#define ADDR_IVP_CFG_SEC_REG_APB_IF_SEC_SEL 776
#define ADDR_IVP_CFG_SEC_REG_START_REMAP_ADDR 788
#define ADDR_IVP_CFG_SEC_REG_REMAP_LENGTH 792
#define ADDR_IVP_CFG_SEC_REG_DDR_REMAP_ADDR 796
#define ADDR_IVP_CFG_SEC_REG_REMAP_SECURITY_CFG 820
#define ADDR_IVP_CFG_SEC_REG_IVP_MST_MID_CFG 824
#define ADDR_IVP_CFG_SEC_REG_SMMU_INTEG_SEC_OVERRIDE 1308
#define ADDR_IVP_CFG_SEC_REG_SMMU_SPNIDEN 1312
//watchdog reg
#define WDG_REG_LOCK_KEY      (0x00)
#define WDG_REG_UNLOCK_KEY    (0x1ACCE551)

#define WDG_REG_OFF_WDLOAD    (0x0000)
#define WDG_REG_OFF_WDVALUE   (0x0004)
#define WDG_REG_OFF_WDCONTROL (0x0008)
#define WDG_REG_OFF_WDINTCLR  (0x000c)
#define WDG_REG_OFF_WDRIS     (0x0010)
#define WDG_REG_OFF_WDMIS     (0x0014)
#define WDG_REG_OFF_WDLOCK    (0x0c00)
//smmu reg
#define     SMMU_NS_CR0             0x0000
#define     SMMU_NS_ACR             0x0010
#define     SMMU_NS_IDR0            0x0020
#define     SMMU_NS_IDR1            0x0024
#define     SMMU_NS_IDR2            0x0028
#define     SMMU_NS_IDR7            0x003C
#define     SMMU_NS_GFAR_LOW        0x0040
#define     SMMU_NS_GFAR_HIGH       0x0044
#define     SMMU_NS_GFSR            0x0048
#define		SMMU_NS_GFSRRESTORE     0x004C
#define		SMMU_NS_GFSYNR0         0x0050
#define		SMMU_NS_GFSYNR1         0x0054
#define		SMMU_NS_GFSYNR2         0x0058
#define		SMMU_NS_TLBIVMID        0x0064 //invalid tlb by VMID
#define		SMMU_NS_TLBIALLNSNH     0x0068
#define		SMMU_NS_TLBGSYNC        0x0070
#define		SMMU_NS_TLBGSTATUS      0x0074
#define		SMMU_NS_SMR0            0x0800
#define		SMMU_NS_SMR1            0x0804
#define		SMMU_NS_SMR2            0x0808
#define		SMMU_NS_SMR3            0x080C
#define		SMMU_NS_S2CR0           0x0C00
#define		SMMU_NS_S2CR1           0x0C04
#define		SMMU_NS_S2CR2           0x0C08
#define		SMMU_NS_S2CR3           0x0C0C
#define		SMMU_NS_CBFRSYNRA0      0x1400
#define		SMMU_NS_CBFRSYNRA1      0x1404
#define		SMMU_NS_CBFRSYNRA2      0x1408
#define		SMMU_NS_CBFRSYNRA3      0x140C
#define		SMMU_NS_CBAR0           0x1000
#define		SMMU_NS_CBA2R0          0x1800
#define		SMMU_NS_CBAR1           0x1004
#define		SMMU_NS_CBAR2           0x1008
#define		SMMU_NS_CBAR3           0x100C
#define		SMMU_NS_CB0_SCTLR       0x8000
#define		SMMU_NS_CB0_RESUME      0x8008
#define		SMMU_NS_CB0_TTBCR2      0x8010 //SMMU_CB0_TCR2
#define		SMMU_NS_CB0_TTBR0_LOW   0x8020
#define		SMMU_NS_CB0_TTBR0_HIGH  0x8024
#define		SMMU_NS_CB0_TTBCR       0x8030 //SMMU_CB0_TCR
#define		SMMU_NS_CB0_FSR         0x8058
#define		SMMU_NS_CB0_FSRRESTORE  0x805C
#define		SMMU_NS_CB0_FAR_LOW     0x8060
#define		SMMU_NS_CB0_FAR_HIGH    0x8064
#define		SMMU_NS_CB0_FSYNR0      0x8068
#define		SMMU_NS_CB0_TLBIVA      0x8600 //invalid tlb by VA
#define		SMMU_NS_CB0_TLBIASID    0x8610 //invalid tlb by ASID
#define		SMMU_NS_CB0_TLBIALL     0x8618 //invalid tlb ALL
#define		SMMU_NS_CB0_TLBSYNC     0x87F0 //invalid tlb sync
#define		SMMU_NS_CB0_TLBSTATUS   0x87F4 //invalid tlb status
//pctrl reg
#define PCTRL_REG_OFF_PERI_STAT4                (0x00A4)
//pericrg reg
#define  PERICRG_REG_OFF_PERI_AUTODIV0    (0x360)
#define  PERICRG_REG_OFF_PEREN6           (0x410)
#define  PERICRG_REG_OFF_PERDIS6          (0x414)
#define  PERICRG_REG_OFF_PERCLKEN6        (0x418)

#define IVP_DW_AXI_M2_ST_BYPASS           (0x01 << 29)
#define IVP_DW_AXI_M1_ST_BYPASS           (0x01 << 28)
#define IVP_PWAITMODE_BYPASS              (0x01 << 27)
#define IVP_DIV_AUTO_REDUCE_BYPASS        (0x01 << 0)

#define GATE_CLK_AUTODIV_IVP              (0x01 << 0)

//gic reg
#define GIC_REG_OFF_GICD_ICENABLERn       (0x11A4)
#endif

