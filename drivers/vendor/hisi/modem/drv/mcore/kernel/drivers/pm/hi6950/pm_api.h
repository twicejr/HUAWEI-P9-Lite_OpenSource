#ifndef __PM_API_H__
#define __PM_API_H__

#include "osl_types.h"
#include "soc_memmap.h"
#include "soc_clk.h"
#include "soc_interrupts.h"
#include <irq.h>
#include <bsp_sram.h>


#define PM_MCU_TIMER_CLK       HI_TCXO_CLK

#define  M3_CM3_DBG_WAKE_INT            173

/* WSRC_REG number*/
#define WSRC_REG_NUM            2
/* PWR_CTRL16/PWR_CTRL17 */
/* m3 wake_src  bit*/
#define M3_WSRC_0_TIMER7        (0x1UL<<12)
#define M3_WSRC_1_DEBUG         (0x1UL<<6)
#define M3_WSRC_1_CCPU          (0x1UL<<5)
#define M3_WSRC_1_ACPU          (0x1UL<<4)

/* PWR_CTRL24/PWR_CTRL25 */
/* appa9 wake_src  bit*/
#define APPA9_WSRC_0_IPC0       (0x1UL<<0)
#define APPA9_WSRC_0_IPC1       (0x1UL<<1)
#define APPA9_WSRC_0_RTC        (0x1UL<<2)
#define APPA9_WSRC_0_IPF1       (0x1UL<<5)
#define APPA9_WSRC_0_TIMER0     (0x1UL<<7)
#define APPA9_WSRC_0_TIMER2     (0x1UL<<9)
#define APPA9_WSRC_0_PMU        (0x1UL<<28)
#define APPA9_WSRC_1_GPIO_0     (0x1UL<<6)
#define APPA9_WSRC_1_PSAM_0     (0x1UL<<17)
#define APPA9_WSRC_1_DEBUG      (0x1UL<<20)

/* PWR_CTRL30/PWR_CTRL31 */
/* mdma9 wake_src  bit*/
#define MDMA9_WSRC_0_IPF0       (0x1UL<<0)
#define MDMA9_WSRC_0_TIMER1     (0x1UL<<3)
#define MDMA9_WSRC_0_TIMER3     (0x1UL<<5)
#define MDMA9_WSRC_0_TIMER4     (0x1UL<<6)
#define MDMA9_WSRC_0_LDRX_CPU   (0x1UL<<24)
#define MDMA9_WSRC_0_TDRX_CPU   (0x1UL<<25)
#define MDMA9_WSRC_0_G1_CPU     (0x1UL<<26)
#define MDMA9_WSRC_0_G2_CPU     (0x1UL<<28)
#define MDMA9_WSRC_0_W_CPU      (0x1UL<<31)
#define MDMA9_WSRC_1_IPC0       (0x1UL<<2)
#define MDMA9_WSRC_1_IPC1       (0x1UL<<3)
#define MDMA9_WSRC_1_DEBUG      (0x1UL<<8)
/* dynamic set wsrc for ccore */
#define MDMA9_WSRC_0_TIMER5     (0x1UL<<7)


#define M3PM_SC_BASE_MDM    HI_SYSSC_MDM_BASE_ADDR          /*0x80200000*/
#define M3PM_SC_BASE_PD     HI_SYSSC_PD_BASE_ADDR           /*0x90000000*/
#define M3PM_SC_BASE_AO     HI_SYSSC_AO_BASE_ADDR           /*0x20000000*/
//#define M3PM_SC_PCIE_BASE   HI_SYSCTRL_PCIE_REG_BASE_ADDR   /*0x90000000*/


/* PD_CRG */
#define PD_CRG_CLKEN2 0x010
#define PD_CRG_CLKEN3 0x020
#define PD_CRG_CLKDIS3 0x024
#define PD_CRG_SRSTEN1 0x060
#define PD_CRG_SRSTDIS1 0x064
#define PD_CRG_SRSTEN2 0x06C
#define PD_CRG_SRSTDIS2 0x070
#define PD_CRG_CLKDIV2 0x104
#define CRG_DFS1_CTRL1 0x200
#define CRG_DFS1_CTRL2 0x204
#define CRG_DFS1_CTRL3 0x208

#define CRG_DFS2_CTRL3	0x214      /*  DSP DFS  */
#define CRG_DFS3_CTRL3	0x220      /*  HIFI DFS */
#define CRG_DFS5_CTRL3	0x238      /*  PERI DFS  */
#define CRG_DFS6_CTRL3	0x244  	   /*  PERI USB DFS */


/* CRG_MDM */


#define MDM_CRG_CLKEN0 0x000
#define MDM_CRG_CLKDIS0 0x004
#define MDM_CRG_SRSTEN0 0x020
#define MDM_CRG_SRSTDIS0 0x024

/* sysctrl */
/* SYS_AO */
#define SC_AO_CTRL22 0x458

#define PWR_CTRL0 0xC00
#define PWR_CTRL2 0xC08
#define PWR_CTRL4 0xC10
#define PWR_CTRL5 0xC14
#define PWR_CTRL6 0xC18
#define PWR_CTRL7 0xC1C
#define PWR_CTRL8 0xC20
#define PWR_CTRL9 0xC24
#define PWR_CTRL10 0xC28
#define PWR_CTRL11 0xC2C
#define PWR_CTRL12 0xC30
#define PWR_CTRL13 0xC34
#define PWR_CTRL16 0xC40
#define PWR_CTRL17 0xC44
#define PWR_CTRL24 0xC60
#define PWR_CTRL25 0xC64
#define PWR_CTRL30 0xC78
#define PWR_CTRL31 0xC7C
#define PWR_CTRL38 0xC98
#define PWR_STAT0 0xE00
#define PWR_STAT1 0xE04

#define PWR_STAT6  0xE18    /* cm3 »½ÐÑÖÐ¶ÏÎ»ÖÃ¼Ä´æÆ÷ */
#define PWR_STAT7  0xE1C    /* cm3 »½ÐÑÖÐ¶Ï×´Ì¬0 */
#define PWR_STAT8  0xE20    /* cm3 »½ÐÑÖÐ¶Ï×´Ì¬1 */
#define PWR_STAT15 0xE3C    /* app a9 »½ÐÑÖÐ¶ÏÎ»ÖÃ¼Ä´æÆ÷ */
#define PWR_STAT16 0xE40    /* app a9 »½ÐÑÖÐ¶Ï×´Ì¬0 */
#define PWR_STAT17 0xE44    /* app a9 »½ÐÑÖÐ¶Ï×´Ì¬1 */
#define PWR_STAT22 0xE58    /* mdm a9 »½ÐÑÖÐ¶ÏÎ»ÖÃ¼Ä´æÆ÷ */
#define PWR_STAT23 0xE5C    /* mdm a9 »½ÐÑÖÐ¶Ï×´Ì¬0 */
#define PWR_STAT24 0xE60    /* mdm a9 »½ÐÑÖÐ¶Ï×´Ì¬1 */

/* SC_PD */
#define SC_TOP_CTRL21       0x454  /* DDRPHYÄ£Ê½Ñ¡Ôñ¼Ä´æÆ÷ */


/* SC_MDM */
#define ISO_EN 0xC0C
#define ISO_DIS 0xC10
#define MTCMOS_EN 0xC18
#define MTCMOS_DIS 0xC1C
#define MTCMOS_RDY_STAT 0xE04



#ifdef HiMDDRCV500
#endif 
#define DDRC_CTRL_SREF 0x000
#define DDRC_CFG_LP 0x01C
#define DDRC_CFG_SREF 0x020
#define DDRC_CFG_PD 0x028
#define DDRC_CFG_AREF 0x02C
#define DDRC_CFG_DDRMODE 0x050
#define DDRC_CFG_RNKVOL 0x060
#define DDRC_CFG_TIMING0 0x100
#define DDRC_CFG_TIMING1 0x104
#define DDRC_CFG_TIMING2 0x108
#define DDRC_CFG_TIMING3 0x10C
#define DDRC_CFG_TIMING4 0x110
#define DDRC_CFG_TIMING5 0x114
#define DDRC_CFG_TIMING6 0x118
#define DDRC_CFG_DDRPHY 0x200
#define DDRC_CURR_FUNC 0x294



#ifdef DDRC_PACK
#endif

#define PHYINITCTRL 0x004
#define PHYCLKGATED 0x000C
#define PHYTIMER0 0x010
#define PHYTIMER1 0x014
#define PLLCTRL 0x018
#define PLLTIMER 0x01C
#define DLYMEASCTRL 0x020
#define IMPSTATUS 0x028
#define DRAMCFG 0x02C
#define DRAMTIMER0 0x030
#define DRAMTIMER1 0x034
#define DRAMTIMER2 0x038
#define DRAMTIMER3 0x03C
#define DRAMTIMER4 0x040
#define TRAINCTRL0 0x048
#define MODEREG01 0x0064
#define MODEREG23 0x0068
#define MISC 0x0070
#define PHYCTRL0 0x0078
#define RETCTRL0 0x0080
#define DMSEL 0x0084
#define DRAMTIMER5 0x0BC
#define TRAINCTRL6 0x0E8
#define ACADDRBDL0 0x140
#define ACADDRBDL1 0x144
#define ACADDRBDL2 0x148
#define ACADDRBDL3 0x14C
#define ACADDRBDL4 0x150
#define ACPHYCTL0 0x170
#define ADDRPHBOUND 0x01D4
#define LPCTRL 0x01E4
#define DXNWDQNBDL0 0x210
#define DXNWDQNBDL1 0x214
#define DXNWDQNBDL2 0x218
#define DXNRDQNBDL0 0x21C
#define DXNRDQNBDL1 0x220
#define DXNOEBDL 0x228
#define DXNRDQSDLY 0x22C
#define DXNWDQSDLY 0x230
#define DXNWDQDLY 0x234
#define DXNWLSL 0x238
#define DXNGDS 0x23C
#define DXNRDQSGDLY 0x240
#define DXNMISCCTRL0 0x260
#define IOCTL3 0xFF0

enum cpu_debug_suspend_bit
{
    acpu_debug_suspend_bit = 31,
    ccpu_debug_suspend_bit = 30,
    cm3_debug_suspend_bit  = 29
};
static inline void set_cpu_dbg_suspend(u32 cpu_bit,u32 suspend_flag)
{
#if 0
    u32 tmp = 0;
    tmp = readl( M3PM_SC_BASE_AO + SC_AO_CTRL22);
    tmp &= ~(0x1<<cpu_bit);
    tmp |= (suspend_flag<<cpu_bit);
    writel(tmp,  M3PM_SC_BASE_AO + SC_AO_CTRL22);
#endif
}

#define CM3_DDRC_BASE_ADDR    0xE0046000
#define CM3_CRG_BASE_ADDR     0xE0045000


#define CM3_LP_ISO_EN        (0xE0044000)
#define CM3_LP_ISO_DIS       (0xE0044004)
#define CM3_LP_MTCMOS_EN     (0xE0044010)
#define CM3_LP_MTCMOS_DIS    (0xE0044014)
#define CM3_LP_PWRCTRL0      (0xE0044020)

#define MDDRC_SREFCTRL       (0x90048000)
#define MDDRC_STATUS         (0x90048294)


typedef struct {
	u32	timing0;
	u32 timing1;
	u32 timing2;
	u32 timing3;
    u32 zq0dr;
    u32 zq1dr;
}T_PM_DDRC;


#endif
