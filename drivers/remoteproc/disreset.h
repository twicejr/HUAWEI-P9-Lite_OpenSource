#ifndef _DRIVERS_REMOTEPROC_DISRESET_H_
#define _DRIVERS_REMOTEPROC_DISRESET_H_

/* Regs Base */
#define REG_BASE_CRGPERI_PHY         (0xFFF35000)
#define REG_BASE_SYSCTRL_PHY         (0xFFF0A000)
#define REG_BASE_PMCCTRL_PHY         (0xFFF31000)
#define REG_BASE_VIVOBUS_PHY         (0xE86D0000)
#define REG_BASE_ISP_PHY             (0xE8400000)

/* VivoBus Regs Offset */
#define ISP_RD_QOS_PRIORITY          (0x8)
#define ISP_RD_QOS_MODE              (0xC)
#define ISP_WR_QOS_PRIORITY          (0x88)
#define ISP_WR_QOS_MODE              (0x8C)
#define A7T0VIVOBUS_RD_QOS_PRIORITY  (0x108)
#define A7T0VIVOBUS_RD_QOS_MODE      (0x10C)
#define A7T0VIVOBUS_WR_QOS_PRIORITY  (0x188)
#define A7T0VIVOBUS_WR_QOS_MODE      (0x18C)

#define QOS_FIX_MODE 0x0
#define QOS_BYPASS_MODE 0x2
#define QOS_PRIO_1 0x0
#define QOS_PRIO_2 0x101
#define QOS_PRIO_3 0x202
#define QOS_PRIO_3_PLUS_RD 0x302
#define QOS_PRIO_4 0x303

/* CRG Regs Offset */
#define CRG_0D0_PERIPHCLKDIV10              (0x0D0)
#define CRG_0F0_PERIPHCLKDIV18              (0x0F0)
#define CRG_0F8_PERIPHCLKDIV20              (0x0F8)

#define CRG_008_PERIPHPERCLKEN0             (0x008)
#define CRG_00C_PERIPHPERSTAT0              (0x00C)
#define CRG_038_PERIPHPERCLKEN3             (0x038)
#define CRG_03C_PERIPHPERSTAT3              (0x03C)
#define CRG_058_PERIPHPERCLKEN5             (0x058)
#define CRG_05C_PERIPHPERSTAT5              (0x05C)

#define CRG_068_PERIPHPERRSTSTAT0           (0x068)
#define CRG_08C_PERIPHPERRSTSTAT3           (0x08C)

#define CRG_14C_PERIPHISOSTAT               (0x14C)
#define CRG_158_PERIPHPERPWRSTAT            (0x158)
#define CRG_15C_PERIPHPERPWRACK             (0x15C)

#define CRG_C84_PERIPHISP_SEC_RSTDIS        (0xC84)
#define CRG_C88_PERIPHISP_SEC_RSTSTAT       (0xC88)
#define IP_RST_ISPA7                        (1 << 4)
#define IP_RST_ISP                          (1 << 0)

#define CRG_C90_PERIPHISP_ISPA7_CTRL_BASE   (0xC90)
#define ISPA7_DBGPWRDUP                     (1 << 2)
#define ISPA7_VINITHI_HIGH                  (1 << 1)
#define ISPA7_REMAP_ENABLE                  (1 << 11)

/* PMCtrl Regs Offset */
#define PMCTRL_384_NOC_POWER_IDLEACK        (0x384)
#define PMCTRL_388_NOC_POWER_IDLE           (0x388)

/* ISP Regs Offset */
#define REVISION_ID_OFFSET                  (0x20008)

#endif /* _DRIVERS_REMOTEPROC_DISRESET_H_ */
