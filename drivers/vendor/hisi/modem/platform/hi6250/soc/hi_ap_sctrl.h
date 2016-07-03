/******************************************************************************/
/*  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_AP_SCTRL.h */
/* Version       : 2.0 */
/* Created       : 2014-03-11*/
/* Last Modified : */
/* Description   :  The C union definition file for the module AP_SCTRL*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_AP_SCTRL_H__
#define __HI_AP_SCTRL_H__

/*
 * Project: hi
 * Module : AP_SCTRL
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    AP_SCTRL 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_AP_SCTRL_SCCTRL_OFFSET                         (0x0) /* 系统控制器寄存器 */
#define    HI_AP_SCTRL_SCSYSSTAT_OFFSET                      (0x4) /* 系统状态寄存器 */
#define    HI_AP_SCTRL_SCITMCTRL_OFFSET                      (0x8) /* 中断模式控制寄存器 */
#define    HI_AP_SCTRL_SCIMSTAT_OFFSET                       (0xC) /* 中断模式状态寄存器 */
#define    HI_AP_SCTRL_SCXTALCTRL_OFFSET                     (0x10) /* 晶振控制寄存器 */
#define    HI_AP_SCTRL_SCXTALTIMEOUT0_OFFSET                 (0x14) /* 晶振稳定时间配置寄存器0 */
#define    HI_AP_SCTRL_SCXTALTIMEOUT1_OFFSET                 (0x18) /* 晶振稳定时间配置寄存器1 */
#define    HI_AP_SCTRL_SCXTALSTAT_OFFSET                     (0x1C) /* 晶振控制状态寄存器 */
#define    HI_AP_SCTRL_SCPPLLCTRL0_OFFSET                    (0x20) /* PPLL0控制寄存器0 */
#define    HI_AP_SCTRL_SCPPLLCTRL1_OFFSET                    (0x24) /* PPLL0控制寄存器1 */
#define    HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET                  (0x28) /* PPLL0 SSC控制寄存器 */
#define    HI_AP_SCTRL_SCPPLLSTAT_OFFSET                     (0x2C) /* PPLL0状态寄存器 */
#define    HI_AP_SCTRL_SCPEREN0_OFFSET                       (0x30) /* 外设时钟使能寄存器0 */
#define    HI_AP_SCTRL_SCPERDIS0_OFFSET                      (0x34) /* 外设时钟禁止寄存器0 */
#define    HI_AP_SCTRL_SCPERCLKEN0_OFFSET                    (0x38) /* 外设时钟使能状态寄存器0 */
#define    HI_AP_SCTRL_SCPERSTAT0_OFFSET                     (0x3C) /* 外设时钟最终状态寄存器0 */
#define    HI_AP_SCTRL_SCPEREN1_OFFSET                       (0x40) /* 外设时钟使能寄存器1 */
#define    HI_AP_SCTRL_SCPERDIS1_OFFSET                      (0x44) /* 外设时钟禁止寄存器1 */
#define    HI_AP_SCTRL_SCPERCLKEN1_OFFSET                    (0x48) /* 外设时钟使能状态寄存器1 */
#define    HI_AP_SCTRL_SCPERSTAT1_OFFSET                     (0x4C) /* 外设时钟最终状态寄存器1 */
#define    HI_AP_SCTRL_SCPEREN2_OFFSET                       (0x50) /* 外设时钟使能寄存器2 */
#define    HI_AP_SCTRL_SCPERDIS2_OFFSET                      (0x54) /* 外设时钟禁止寄存器2 */
#define    HI_AP_SCTRL_SCPERCLKEN2_OFFSET                    (0x58) /* 外设时钟使能状态寄存器2 */
#define    HI_AP_SCTRL_SCPERSTAT2_OFFSET                     (0x5C) /* 外设时钟最终状态寄存器2 */
#define    HI_AP_SCTRL_SCPERRSTEN0_OFFSET                    (0x80) /* 外设软复位使能寄存器0 */
#define    HI_AP_SCTRL_SCPERRSTDIS0_OFFSET                   (0x84) /* 外设软复位撤离寄存器0 */
#define    HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET                  (0x88) /* 外设软复位状态寄存器0 */
#define    HI_AP_SCTRL_SCPERRSTEN1_OFFSET                    (0x8C) /* 外设软复位使能寄存器1 */
#define    HI_AP_SCTRL_SCPERRSTDIS1_OFFSET                   (0x90) /* 外设软复位撤离寄存器1 */
#define    HI_AP_SCTRL_SCPERRSTSTAT1_OFFSET                  (0x94) /* 外设软复位状态寄存器1 */
#define    HI_AP_SCTRL_SCPERRSTEN2_OFFSET                    (0x98) /* 外设软复位使能寄存器2 */
#define    HI_AP_SCTRL_SCPERRSTDIS2_OFFSET                   (0x9C) /* 外设软复位撤离寄存器2 */
#define    HI_AP_SCTRL_SCPERRSTSTAT2_OFFSET                  (0xA0) /* 外设软复位状态寄存器2 */
#define    HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET                  (0xA4) /* IP防总线挂死控制寄存器 */
#define    HI_AP_SCTRL_SCISOEN_OFFSET                        (0xC0) /* 掉电子系统ISO使能寄存器 */
#define    HI_AP_SCTRL_SCISODIS_OFFSET                       (0xC4) /* 掉电子系统ISO使能撤销寄存器 */
#define    HI_AP_SCTRL_SCISOSTAT_OFFSET                      (0xC8) /* 掉电子系统ISO使能状态寄存器 */
#define    HI_AP_SCTRL_SCPWREN_OFFSET                        (0xD0) /* 掉电子系统电源使能寄存器 */
#define    HI_AP_SCTRL_SCPWRDIS_OFFSET                       (0xD4) /* 掉电子系统电源使能撤销寄存器 */
#define    HI_AP_SCTRL_SCPWRSTAT_OFFSET                      (0xD8) /* 掉电子系统电源使能状态寄存器 */
#define    HI_AP_SCTRL_SCPWRACK_OFFSET                       (0xDC) /* 掉电子系统最终电源状态寄存器 */
#define    HI_AP_SCTRL_SCPERPWRDOWNTIME_OFFSET               (0xE0) /* 外设区掉电时间配置寄存器 */
#define    HI_AP_SCTRL_SCPERPWRUPTIME_OFFSET                 (0xE4) /* 外设区上电时间配置寄存器 */
#define    HI_AP_SCTRL_SCCLKDIV0_OFFSET                      (0x100) /* 时钟分频比控制寄存器0 */
#define    HI_AP_SCTRL_SCCLKDIV1_OFFSET                      (0x104) /* 时钟分频比控制寄存器1 */
#define    HI_AP_SCTRL_SCCLKDIV2_OFFSET                      (0x108) /* 时钟分频比控制寄存器2 */
#define    HI_AP_SCTRL_SCCLKDIV3_OFFSET                      (0x10C) /* 时钟分频比控制寄存器3 */
#define    HI_AP_SCTRL_SCCLKDIV4_OFFSET                      (0x110) /* 时钟分频比控制寄存器4 */
#define    HI_AP_SCTRL_SCCLKDIV5_OFFSET                      (0x114) /* 时钟分频比控制寄存器5 */
#define    HI_AP_SCTRL_SCPERCTRL0_OFFSET                     (0x200) /* 外设控制寄存器0 */
#define    HI_AP_SCTRL_SCPERCTRL1_OFFSET                     (0x204) /* 外设控制寄存器1 */
#define    HI_AP_SCTRL_SCPERCTRL2_OFFSET                     (0x208) /* 外设控制寄存器2 */
#define    HI_AP_SCTRL_SCPERCTRL3_OFFSET                     (0x20C) /* 外设控制寄存器3 */
#define    HI_AP_SCTRL_SCPERCTRL4_OFFSET                     (0x210) /* 外设控制寄存器4 */
#define    HI_AP_SCTRL_SCPERCTRL5_OFFSET                     (0x214) /* 外设控制寄存器5 */
#define    HI_AP_SCTRL_SCPERCTRL6_OFFSET                     (0x218) /* 外设控制寄存器6 */
#define    HI_AP_SCTRL_SCPERSTATUS0_OFFSET                   (0x21C) /* 外设状态寄存器0 */
#define    HI_AP_SCTRL_SCPERSTATUS1_OFFSET                   (0x220) /* 外设状态寄存器1 */
#define    HI_AP_SCTRL_SCPERSTATUS2_OFFSET                   (0x224) /* 外设状态寄存器2 */
#define    HI_AP_SCTRL_SCPERSTATUS3_OFFSET                   (0x228) /* 外设状态寄存器3 */
#define    HI_AP_SCTRL_SCPERSTATUS4_OFFSET                   (0x22C) /* 外设状态寄存器4 */
#define    HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET                  (0x300) /* 用于指示系统曾经进入过深度睡眠的状态寄存器 */
#define    HI_AP_SCTRL_SCMRBBUSYSTAT_OFFSET                  (0x304) /* MRB EFUSE BUSY状态指示寄存器 */
#define    HI_AP_SCTRL_SCSWADDR_OFFSET                       (0x308) /* 用于保存软件入口地址的寄存器 */
#define    HI_AP_SCTRL_SCDDRADDR_OFFSET                      (0x30C) /* 用于保留DDR训练数据的地址的寄存器 */
#define    HI_AP_SCTRL_SCDDRDATA_OFFSET                      (0x310) /* 用于保存DDR训练数据的寄存器 */
#define    HI_AP_SCTRL_SCBAKDATA0_OFFSET                     (0x314) /* 用于软件使用的存储数据寄存器0 */
#define    HI_AP_SCTRL_SCBAKDATA1_OFFSET                     (0x318) /* 用于软件使用的存储数据寄存器1 */
#define    HI_AP_SCTRL_SCBAKDATA2_OFFSET                     (0x31C) /* 用于软件使用的存储数据寄存器2 */
#define    HI_AP_SCTRL_SCBAKDATA3_OFFSET                     (0x320) /* 用于软件使用的存储数据寄存器3 */
#define    HI_AP_SCTRL_SCBAKDATA4_OFFSET                     (0x324) /* 用于软件使用的存储数据寄存器4 */
#define    HI_AP_SCTRL_SCBAKDATA5_OFFSET                     (0x328) /* 用于软件使用的存储数据寄存器5 */
#define    HI_AP_SCTRL_SCBAKDATA6_OFFSET                     (0x32C) /* 用于软件使用的存储数据寄存器6 */
#define    HI_AP_SCTRL_SCBAKDATA7_OFFSET                     (0x330) /* 用于软件使用的存储数据寄存器7 */
#define    HI_AP_SCTRL_SCBAKDATA8_OFFSET                     (0x334) /* 用于软件使用的存储数据寄存器8 */
#define    HI_AP_SCTRL_SCBAKDATA9_OFFSET                     (0x338) /* 用于软件使用的存储数据寄存器9 */
#define    HI_AP_SCTRL_SCBAKDATA10_OFFSET                    (0x33C) /* 用于软件使用的存储数据寄存器10 */
#define    HI_AP_SCTRL_SCBAKDATA11_OFFSET                    (0x340) /* 用于软件使用的存储数据寄存器11 */
#define    HI_AP_SCTRL_SCBAKDATA12_OFFSET                    (0x344) /* 用于软件使用的存储数据寄存器12 */
#define    HI_AP_SCTRL_SCBAKDATA13_OFFSET                    (0x348) /* 用于软件使用的存储数据寄存器13 */
#define    HI_AP_SCTRL_SCBAKDATA14_OFFSET                    (0x34C) /* 用于软件使用的存储数据寄存器14 */
#define    HI_AP_SCTRL_SCBAKDATA15_OFFSET                    (0x350) /* 用于软件使用的存储数据寄存器15 */
#define    HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET              (0x450) /* 聚合后的中断状态寄存器 */
#define    HI_AP_SCTRL_SCINT_MASK_OFFSET                     (0x454) /* 中断屏蔽配置寄存器 */
#define    HI_AP_SCTRL_SCINT_STAT_OFFSET                     (0x458) /* 原始中断状态寄存器 */
#define    HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET                  (0x45C) /* DRX中断分配配置寄存器 */
#define    HI_AP_SCTRL_SCLPM3WFI_INT_CLR_OFFSET              (0x460) /* LPM3 WFI中断清除寄存器 */
#define    HI_AP_SCTRL_SCMALIBYPCFG_OFFSET                   (0x48C) /* MALI DBGACK BYPASS配置寄存器 */
#define    HI_AP_SCTRL_SCLPM3CLKEN_OFFSET                    (0x500) /* LPM3子系统时钟使能寄存器 */
#define    HI_AP_SCTRL_SCLPM3RSTEN_OFFSET                    (0x504) /* LPM3子系统软复位使能寄存器 */
#define    HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET                   (0x508) /* LPM3子系统软复位撤离寄存器 */
#define    HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET                  (0x50C) /* LPM3子系统软复位使能状态寄存器 */
#define    HI_AP_SCTRL_SCLPM3CTRL_OFFSET                     (0x510) /* LPM3子系统控制配置寄存器 */
#define    HI_AP_SCTRL_SCLPM3STAT_OFFSET                     (0x514) /* LPM3子系统状态寄存器 */
#define    HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET                  (0x518) /* LPM3 RAM 控制寄存器 */
#define    HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET                  (0x530) /* BBPDRX子系统状态寄存器0 */
#define    HI_AP_SCTRL_SCBBPDRXSTAT1_OFFSET                  (0x534) /* BBPDRX子系统状态寄存器1 */
#define    HI_AP_SCTRL_SCBBPDRXSTAT2_OFFSET                  (0x538) /* BBPDRX子系统状态寄存器2 */
#define    HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET                (0x550) /* A7 EVENT屏蔽寄存器 */
#define    HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET               (0x554) /* A15 EVENT屏蔽寄存器 */
#define    HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET              (0x558) /* IOM3 EVENT屏蔽寄存器 */
#define    HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET              (0x55C) /* LPM3 EVENT屏蔽寄存器 */
#define    HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET              (0x560) /* MCPU EVENT屏蔽寄存器 */
#define    HI_AP_SCTRL_SCEVENT_STAT_OFFSET                   (0x564) /* EVENT状态寄存器 */
#define    HI_AP_SCTRL_SCJTAG_SEL_OFFSET                     (0x800) /* JTAG选择控制寄存器 */
#define    HI_AP_SCTRL_SCMODEM_KEY0_OFFSET                   (0x804) /* MODEM_KEY0 */
#define    HI_AP_SCTRL_SCMODEM_KEY1_OFFSET                   (0x808) /* MODEM_KEY1 */
#define    HI_AP_SCTRL_SCMODEM_KEY2_OFFSET                   (0x80C) /* MODEM_KEY2 */
#define    HI_AP_SCTRL_SCMODEM_KEY3_OFFSET                   (0x810) /* MODEM_KEY3 */
#define    HI_AP_SCTRL_SCCFG_DJTAG_OFFSET                    (0x814) /* DJTAG控制寄存器 */
#define    HI_AP_SCTRL_SCCP15_DISABLE_OFFSET                 (0x818) /* CP15DISABLE控制寄存器 */
#define    HI_AP_SCTRL_SCCLKCNTSTAT_OFFSET                   (0x81C) /* 时钟计数状态寄存器 */
#define    HI_AP_SCTRL_SCCLKCNTCFG_OFFSET                    (0x820) /* 时钟计数配置寄存器 */
#define    HI_AP_SCTRL_SCCLKMONCTRL_OFFSET                   (0x824) /* 时钟监控控制寄存器 */
#define    HI_AP_SCTRL_SCCLKMONINT_OFFSET                    (0x828) /* 时钟监控中断状态寄存器 */
#define    HI_AP_SCTRL_SCCFG_ARM_DBGEN_OFFSET                (0x82C) /* ARM debug en配置寄存器 */
#define    HI_AP_SCTRL_SCARM_DBG_KEY0_OFFSET                 (0x830) /* ARM debug key0配置寄存器 */
#define    HI_AP_SCTRL_SCARM_DBG_KEY1_OFFSET                 (0x834) /* ARM debug key1配置寄存器 */
#define    HI_AP_SCTRL_SCARM_DBGEN_STAT_OFFSET               (0x838) /* ARM debug en状态寄存器 */
#define    HI_AP_SCTRL_SCEFUSECTRL_OFFSET                    (0x83C) /* EFUSE PAD烧写控制寄存器 */
#define    HI_AP_SCTRL_SCEFUSESEL_OFFSET                     (0x840) /* AOCC/SECS时钟门控寄存器 */
#define    HI_AP_SCTRL_SCSECURITYSTAT_OFFSET                 (0x844) /* EFUSE SECURITY状态寄存器 */
#define    HI_AP_SCTRL_SCCHIP_ID0_OFFSET                     (0x848) /* EFUSE CHIP_ID0寄存器 */
#define    HI_AP_SCTRL_SCCHIP_ID1_OFFSET                     (0x84C) /* EFUSE CHIP_ID1寄存器 */
#define    HI_AP_SCTRL_SCSOCID0_OFFSET                       (0xE00) /* SOCID寄存器0 */

/********************************************************************************/
/*    AP_SCTRL 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    modectrl                   : 3; /* [2..0] 系统模式控制。这里定义了系统期望的工作模式。000：SLEEP；001：DOZE；01X： SLOW；1XX:：NORMAL； */
        unsigned int    modestatus                 : 4; /* [6..3] 指示系统控制器系统状态机当前工作模式。0000：SLEEP；0001：DOZE；0011：XTAL CTL；1000：XTAL_OFF；1011：SW to XTAL；1001：SW from XTAL；0010：SLOW；0110：PLL CTL；1110：SW to PLL；1010：SW from PLL；0100：NORMAL；Others：保留。 */
        unsigned int    reserved_1                 : 1; /* [7..7] 保留。 */
        unsigned int    timeforcehigh              : 1; /* [8..8] Timer01、Timer23、Timer45、Timer67使能端强制拉高的硬件使能配置。0：硬件不进行自动操作；1：当系统时钟是32K时，硬件自动强制拉高Timer01、Timer23、Timer45、Timer67的使能。 */
        unsigned int    timeren0sel                : 1; /* [9..9] Time0时钟使能参考时钟选择。0：选择32.768kHz睡眠时钟作为参考时钟计数；1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int    timeren0ov                 : 1; /* [10..10] Timer0时钟使能控制。0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren0sel]指定；1：使能信号被强制拉高。 */
        unsigned int    timeren1sel                : 1; /* [11..11] Time1时钟使能参考时钟选择。0：选择32.768kHz睡眠时钟作为参考时钟计数；1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int    timeren1ov                 : 1; /* [12..12] Timer1时钟使能控制。0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren1sel]指定；1：使能信号被强制拉高。 */
        unsigned int    timeren2sel                : 1; /* [13..13] Time2时钟使能参考时钟选择。0：选择32.768kHz睡眠时钟作为参考时钟计数；1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int    timeren2ov                 : 1; /* [14..14] Timer2时钟使能控制。0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren2sel]指定；1：使能信号被强制拉高。注：此TIMER有安全控制需求，可通过配置安全区的timer_secu_en位来强制选择32KHZ时钟 */
        unsigned int    timeren3sel                : 1; /* [15..15] Time3时钟使能参考时钟选择。0：选择32.768kHz睡眠时钟作为参考时钟计数；1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int    timeren3ov                 : 1; /* [16..16] Timer3时钟使能控制。0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren3sel]指定；1：使能信号被强制拉高。 */
        unsigned int    timeren4sel                : 1; /* [17..17] Time4时钟使能参考时钟选择。0：选择32.768kHz睡眠时钟作为参考时钟计数；1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int    timeren4ov                 : 1; /* [18..18] Timer4时钟使能控制。0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren4sel]指定；1：使能信号被强制拉高。 */
        unsigned int    timeren5sel                : 1; /* [19..19] Time5时钟使能参考时钟选择。0：选择32.768kHz睡眠时钟作为参考时钟计数；1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int    timeren5ov                 : 1; /* [20..20] Timer5时钟使能控制。0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren5sel]指定；1：使能信号被强制拉高。 */
        unsigned int    timeren6sel                : 1; /* [21..21] Time6时钟使能参考时钟选择。0：选择32.768kHz睡眠时钟作为参考时钟计数；1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int    timeren6ov                 : 1; /* [22..22] Timer6时钟使能控制。0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren6sel]指定；1：使能信号被强制拉高。 */
        unsigned int    timeren7sel                : 1; /* [23..23] Time7时钟使能参考时钟选择。0：选择32.768kHz睡眠时钟作为参考时钟计数；1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int    timeren7ov                 : 1; /* [24..24] Timer7时钟使能控制。0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren7sel]指定；1：使能信号被强制拉高。 */
        unsigned int    deepsleepen                : 1; /* [25..25] 进入DEEP SLEEP模式使能寄存器（配置该bit控制状态机进入掉电流程，在NORMAL模式下配置，配合modectrl起作用）0：表示不使能；1：表示使能。 */
        unsigned int    reserved_0                 : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCTRL_T;    /* 系统控制器寄存器 */

typedef union
{
    struct
    {
        unsigned int    reset_source               : 11; /* [10..0] 复位源指示：[10]:modem_wd_rst_req[9]:asp_subsys_wd_req[8]:iom3_rst_req[7]:modem_tsensor_rst_req[6]:lpm3_rst_req[5]:wd1_rst_req[4]:wd0_rst_req[3]:soft_rst_req[2]:g3d_tsensor_rst_req[1]:a7_tsensor_rst_req[0]:a15_tsensor_rst_req */
        unsigned int    reserved                   : 21; /* [31..11] 写：往该寄存器写入任意值会触发系统软复位。读：读该寄存器读出复位源。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCSYSSTAT_T;    /* 系统状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    itmden                     : 1; /* [0..0] 中断模式使能。0：中断模式被禁止；1：当有中断发生时，进入中断模式。 */
        unsigned int    itmdctrl                   : 3; /* [3..1] 设置中断模式下系统最低的工作模式，该寄存器的值和SCCTRL寄存器ModeCtrl的值相或后作为中断发生后系统所处的工作模式。 */
        unsigned int    reserved_1                 : 3; /* [6..4] 保留。 */
        unsigned int    inmdtype                   : 1; /* [7..7] 设置触发系统进入中断模式的中断类型。0：FIQ；1：FIQ或者IRQ。 */
        unsigned int    reserved_0                 : 24; /* [31..8] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCITMCTRL_T;    /* 中断模式控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    itmdstat                   : 1; /* [0..0] 中断模式状态。该位可用于由软件控制直接进入中断模式。读该寄存器时：0：当前未处于中断模式；1：当前处于中断模式。写该寄存器时：A、当前处于非中断响应模式下：0：软件不控制进入中断模式；1：不经过中断触发直接进入中断模式。B、当前已经进入中断响应模式：0：清除中断响应模式1：不清除中断响应模式。（在B场景下下，系统处于中断响应模式，且处于SLOW模式下，此时要求软件的操作步骤为：1、配置目标模式为NORMAL模式；2、在NORMAL模式下清除FIQ或IRQ中断；3、清除itmdstat比特，即对该比特写0） */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCIMSTAT_T;    /* 中断模式状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    tcxopresel_apb             : 1; /* [0..0] 晶振选择预配置：下次唤醒时切换到选定晶振（只在tcxosoft_apb为0并且tcxohardcon_bypass为1时该功能才有效） */
        unsigned int    tcxohardcon_bypass         : 1; /* [1..1] 晶振选择硬件切换屏蔽：1：选择预配置功能0：选择硬件自动切换 */
        unsigned int    tcxosel_apb                : 1; /* [2..2] 晶振软切换选择：1：选择TCXO10：选择TCXO0 */
        unsigned int    tcxosoft_apb               : 1; /* [3..3] 晶振软切换选择：1：选择tcxosel_apb0：选择预切换或者硬件自动切换 */
        unsigned int    defau_tcxo                 : 1; /* [4..4] 非DRX中断到来默认选择TCXO1：选择晶振10：选择晶振0 */
        unsigned int    tcxofast_ctrl0             : 1; /* [5..5] 晶振0快速启动控制1：快速启动0：正常启动 */
        unsigned int    tcxofast_ctrl1             : 1; /* [6..6] 晶振1快速启动控制1：快速启动0：正常启动 */
        unsigned int    ctrlen1_apb                : 1; /* [7..7] 晶振1软件使能控制：1：晶振使能0：晶振去使能 */
        unsigned int    ctrlsel1_apb               : 1; /* [8..8] 晶振1软件控制选择：1：选择ctrlen1_apb0：选择硬件自动控制 */
        unsigned int    ctrlen0_apb                : 1; /* [9..9] 晶振0软件使能控制：1：晶振使能0：晶振去使能 */
        unsigned int    ctrlsel0_apb               : 1; /* [10..10] 晶振0软件控制选择：1：选择ctrlen0_apb0：选择硬件自动控制 */
        unsigned int    timeout_bypass0            : 1; /* [11..11] 状态机检测晶振0超时BYPASS控制1：BYPASS使能0：BYPASS去使能 */
        unsigned int    timeout_bypass1            : 1; /* [12..12] 状态机检测晶振1超时BYPASS控制1：BYPASS使能0：BYPASS去使能 */
        unsigned int    tcxoseq_bypass             : 1; /* [13..13] 状态机检测晶振关闭完成BYPASS控制1：BYPASS使能0：BYPASS去使能 */
        unsigned int    tcxoseq0_time              : 5; /* [18..14] 关晶振0与关ABB BUF的时间间隔，以32KHZ为时钟周期 */
        unsigned int    tcxoseq1_time              : 5; /* [23..19] 关晶振1与关ABB BUF的时间间隔，以32KHZ为时钟周期 */
        unsigned int    reserved                   : 8; /* [31..24] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCXTALCTRL_T;    /* 晶振控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    timeoutcnt0_apb            : 32; /* [31..0] 32KHZ时钟周期 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCXTALTIMEOUT0_T;    /* 晶振稳定时间配置寄存器0 */

typedef union
{
    struct
    {
        unsigned int    timeoutcnt1_apb            : 32; /* [31..0] 32KHZ时钟周期 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCXTALTIMEOUT1_T;    /* 晶振稳定时间配置寄存器1 */

typedef union
{
    struct
    {
        unsigned int    tcxo_en0                   : 1; /* [0..0] 晶振0唤醒中断状态 */
        unsigned int    tcxo_en1                   : 1; /* [1..1] 晶振1唤醒中断状态 */
        unsigned int    tcxo_timeout1              : 1; /* [2..2] 晶振1超时状态 */
        unsigned int    tcxo_timeout0              : 1; /* [3..3] 晶振0超时状态 */
        unsigned int    sysclk_en1                 : 1; /* [4..4] 晶振1使能状态 */
        unsigned int    sysclk_en0                 : 1; /* [5..5] 晶振0使能状态 */
        unsigned int    sysclk_sel                 : 1; /* [6..6] 晶振选择状态 */
        unsigned int    clkgt_ctrl0                : 1; /* [7..7] 晶振0控制输出的clk gate信号 */
        unsigned int    clkgt_ctrl1                : 1; /* [8..8] 晶振1控制输出的clk gate信号 */
        unsigned int    clkgt_ctrl                 : 1; /* [9..9] 最终输出给CRG的clk gate信号 */
        unsigned int    abbbuf_en0                 : 1; /* [10..10] ABB BUF0的使能状态 */
        unsigned int    abbbuf_en1                 : 1; /* [11..11] ABB BUF1的使能状态 */
        unsigned int    tcxoseq_finish0            : 1; /* [12..12] 晶振0关闭完成指示状态 */
        unsigned int    tcxoseq_finish1            : 1; /* [13..13] 晶振1关闭完成指示状态 */
        unsigned int    reserved                   : 18; /* [31..14] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCXTALSTAT_T;    /* 晶振控制状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    ppll0_en                   : 1; /* [0..0] PPLL0使能控制（与AUDIO子系统送来的PPLL使能控制做或逻辑）0：去使能；1：使能。 */
        unsigned int    ppll0_bp                   : 1; /* [1..1] PPLL0 Bypass控制。0：正常工作；1：Bypass。 */
        unsigned int    ppll0_refdiv               : 6; /* [7..2] PPLL0输入时钟分频器。 */
        unsigned int    ppll0_fbdiv                : 12; /* [19..8] PPLL0反馈时钟整数分频器。 */
        unsigned int    ppll0_postdiv1             : 3; /* [22..20] PPLL0输出时钟分频器1。 */
        unsigned int    ppll0_postdiv2             : 3; /* [25..23] PPLL0输出时钟分频器2。 */
        unsigned int    reserved                   : 6; /* [31..26] 保留 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPPLLCTRL0_T;    /* PPLL0控制寄存器0 */

typedef union
{
    struct
    {
        unsigned int    ppll0_fracdiv              : 24; /* [23..0] PPLL0反馈时钟分数分频器。 */
        unsigned int    ppll0_int_mod              : 1; /* [24..24] PPLL0整数分频模式。0：分数分频模式；1：整数分频模式。注意：本PLL支持分数分频和整数分频模式，但在SSC打开时，要求软件只使用分数分频模式。 */
        unsigned int    ppll0_cfg_vld              : 1; /* [25..25] PPLL0配置有效标志。0：配置无效；1：配置有效。 */
        unsigned int    gt_clk_ppll0               : 1; /* [26..26] PPLL0门控信号。0：PPLL0输出时钟门控；1：PPLL0输出时钟不门控。（等待PLL稳定后才能配置该bit） */
        unsigned int    reserved                   : 5; /* [31..27] 保留 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPPLLCTRL1_T;    /* PPLL0控制寄存器1 */

typedef union
{
    struct
    {
        unsigned int    ppll0_ssc_reset            : 1; /* [0..0] 复位信号，高有效。0：复位取消1：复位有效注：不能在PLL工作过程中复位，否则会导致PLL失锁。 */
        unsigned int    ppll0_ssc_disable          : 1; /* [1..1] Bypass the modulator，高有效。0：正常工作1：bypass */
        unsigned int    ppll0_ssc_downspread       : 1; /* [2..2] 选择center spread或down spread0：Center Spread1：Down Spread */
        unsigned int    ppll0_ssc_spread           : 3; /* [5..3] 设置调制深度(spread%)3'b000 = 03'b001 = 0.049%3'b010 = 0.098%3'b011 = 0.195%3'b100 = 0.391%3'b101 = 0.781%3'b110 = 1.563%3'b111 = 3.125% */
        unsigned int    ppll0_ssc_divval           : 4; /* [9..6] 设置频谱调制的频率，一般约为32KHz；freq=(CLKSSCG / (DIVVAL * #points))，其中points为128；当REFDIV=1时，CLKSSCG=FREF。 */
        unsigned int    reserved                   : 22; /* [31..10] 保留 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPPLLSSCCTRL_T;    /* PPLL0 SSC控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    pllstat                    : 1; /* [0..0] PPLL0状态指示。0：未稳定；1：已稳定。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPPLLSTAT_T;    /* PPLL0状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 1; /* [0..0] 外设时钟使能控制：0：写0无效果；1：使能IP时钟。 */
        unsigned int    gt_pclk_rtc                : 1; /* [1..1]  */
        unsigned int    gt_pclk_rtc1               : 1; /* [2..2]  */
        unsigned int    gt_pclk_timer0             : 1; /* [3..3]  */
        unsigned int    gt_clk_timer0              : 1; /* [4..4]  */
        unsigned int    gt_pclk_timer1             : 1; /* [5..5]  */
        unsigned int    gt_clk_timer1              : 1; /* [6..6]  */
        unsigned int    gt_pclk_timer2             : 1; /* [7..7]  */
        unsigned int    gt_clk_timer2              : 1; /* [8..8]  */
        unsigned int    gt_pclk_timer3             : 1; /* [9..9]  */
        unsigned int    gt_clk_timer3              : 1; /* [10..10]  */
        unsigned int    gt_pclk_ao_gpio0           : 1; /* [11..11]  */
        unsigned int    gt_pclk_ao_gpio1           : 1; /* [12..12]  */
        unsigned int    gt_pclk_ao_gpio2           : 1; /* [13..13]  */
        unsigned int    gt_pclk_ao_gpio3           : 1; /* [14..14]  */
        unsigned int    gt_pclk_ao_ioc             : 1; /* [15..15]  */
        unsigned int    gt_clk_out0                : 1; /* [16..16]  */
        unsigned int    gt_clk_out1                : 1; /* [17..17]  */
        unsigned int    gt_clk_jtag_auth           : 1; /* [18..18]  */
        unsigned int    gt_pclk_syscnt             : 1; /* [19..19]  */
        unsigned int    gt_clk_syscnt              : 1; /* [20..20]  */
        unsigned int    gt_pclk_ao_gpio4           : 1; /* [21..21]  */
        unsigned int    gt_pclk_ao_gpio5           : 1; /* [22..22]  */
        unsigned int    gt_clk_sci0                : 1; /* [23..23]  */
        unsigned int    gt_clk_sci1                : 1; /* [24..24]  */
        unsigned int    gt_clk_memrep              : 1; /* [25..25]  */
        unsigned int    gt_clk_asp_subsys          : 1; /* [26..26]  */
        unsigned int    gt_clk_asp_tcxo            : 1; /* [27..27]  */
        unsigned int    gt_clk_bbpdrx              : 1; /* [28..28]  */
        unsigned int    gt_clk_aobus               : 1; /* [29..29]  */
        unsigned int    gt_pclk_efusec             : 1; /* [30..30]  */
        unsigned int    gt_clk_ppll0_sscg          : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPEREN0_T;    /* 外设时钟使能寄存器0 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 1; /* [0..0] 外设时钟禁止控制：0：写0无效果；1：禁止IP时钟。 */
        unsigned int    gt_pclk_rtc                : 1; /* [1..1]  */
        unsigned int    gt_pclk_rtc1               : 1; /* [2..2]  */
        unsigned int    gt_pclk_timer0             : 1; /* [3..3]  */
        unsigned int    gt_clk_timer0              : 1; /* [4..4]  */
        unsigned int    gt_pclk_timer1             : 1; /* [5..5]  */
        unsigned int    gt_clk_timer1              : 1; /* [6..6]  */
        unsigned int    gt_pclk_timer2             : 1; /* [7..7]  */
        unsigned int    gt_clk_timer2              : 1; /* [8..8]  */
        unsigned int    gt_pclk_timer3             : 1; /* [9..9]  */
        unsigned int    gt_clk_timer3              : 1; /* [10..10]  */
        unsigned int    gt_pclk_ao_gpio0           : 1; /* [11..11]  */
        unsigned int    gt_pclk_ao_gpio1           : 1; /* [12..12]  */
        unsigned int    gt_pclk_ao_gpio2           : 1; /* [13..13]  */
        unsigned int    gt_pclk_ao_gpio3           : 1; /* [14..14]  */
        unsigned int    gt_pclk_ao_ioc             : 1; /* [15..15]  */
        unsigned int    gt_clk_out0                : 1; /* [16..16]  */
        unsigned int    gt_clk_out1                : 1; /* [17..17]  */
        unsigned int    gt_clk_jtag_auth           : 1; /* [18..18]  */
        unsigned int    gt_pclk_syscnt             : 1; /* [19..19]  */
        unsigned int    gt_clk_syscnt              : 1; /* [20..20]  */
        unsigned int    gt_pclk_ao_gpio4           : 1; /* [21..21]  */
        unsigned int    gt_pclk_ao_gpio5           : 1; /* [22..22]  */
        unsigned int    gt_clk_sci0                : 1; /* [23..23]  */
        unsigned int    gt_clk_sci1                : 1; /* [24..24]  */
        unsigned int    gt_clk_memrep              : 1; /* [25..25]  */
        unsigned int    gt_clk_asp_subsys          : 1; /* [26..26]  */
        unsigned int    gt_clk_asp_tcxo            : 1; /* [27..27]  */
        unsigned int    gt_clk_bbpdrx              : 1; /* [28..28]  */
        unsigned int    gt_clk_aobus               : 1; /* [29..29]  */
        unsigned int    gt_pclk_efusec             : 1; /* [30..30]  */
        unsigned int    gt_clk_ppll0_sscg          : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERDIS0_T;    /* 外设时钟禁止寄存器0 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 1; /* [0..0] 外设时钟使能状态：0：IP时钟使能撤销状态；1：IP时钟使能状态。 */
        unsigned int    gt_pclk_rtc                : 1; /* [1..1]  */
        unsigned int    gt_pclk_rtc1               : 1; /* [2..2]  */
        unsigned int    gt_pclk_timer0             : 1; /* [3..3]  */
        unsigned int    gt_clk_timer0              : 1; /* [4..4]  */
        unsigned int    gt_pclk_timer1             : 1; /* [5..5]  */
        unsigned int    gt_clk_timer1              : 1; /* [6..6]  */
        unsigned int    gt_pclk_timer2             : 1; /* [7..7]  */
        unsigned int    gt_clk_timer2              : 1; /* [8..8]  */
        unsigned int    gt_pclk_timer3             : 1; /* [9..9]  */
        unsigned int    gt_clk_timer3              : 1; /* [10..10]  */
        unsigned int    gt_pclk_ao_gpio0           : 1; /* [11..11]  */
        unsigned int    gt_pclk_ao_gpio1           : 1; /* [12..12]  */
        unsigned int    gt_pclk_ao_gpio2           : 1; /* [13..13]  */
        unsigned int    gt_pclk_ao_gpio3           : 1; /* [14..14]  */
        unsigned int    gt_pclk_ao_ioc             : 1; /* [15..15]  */
        unsigned int    gt_clk_out0                : 1; /* [16..16]  */
        unsigned int    gt_clk_out1                : 1; /* [17..17]  */
        unsigned int    gt_clk_jtag_auth           : 1; /* [18..18]  */
        unsigned int    gt_pclk_syscnt             : 1; /* [19..19]  */
        unsigned int    gt_clk_syscnt              : 1; /* [20..20]  */
        unsigned int    gt_pclk_ao_gpio4           : 1; /* [21..21]  */
        unsigned int    gt_pclk_ao_gpio5           : 1; /* [22..22]  */
        unsigned int    gt_clk_sci0                : 1; /* [23..23]  */
        unsigned int    gt_clk_sci1                : 1; /* [24..24]  */
        unsigned int    gt_clk_memrep              : 1; /* [25..25]  */
        unsigned int    gt_clk_asp_subsys          : 1; /* [26..26]  */
        unsigned int    gt_clk_asp_tcxo            : 1; /* [27..27]  */
        unsigned int    gt_clk_bbpdrx              : 1; /* [28..28]  */
        unsigned int    gt_clk_aobus               : 1; /* [29..29]  */
        unsigned int    gt_pclk_efusec             : 1; /* [30..30]  */
        unsigned int    gt_clk_ppll0_sscg          : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCLKEN0_T;    /* 外设时钟使能状态寄存器0 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_ao_cc               : 1; /* [0..0] 外设时钟最终状态：0：IP时钟禁止状态；1：IP时钟使能状态。 */
        unsigned int    gt_pclk_rtc                : 1; /* [1..1]  */
        unsigned int    gt_pclk_rtc1               : 1; /* [2..2]  */
        unsigned int    gt_pclk_timer0             : 1; /* [3..3]  */
        unsigned int    gt_clk_timer0              : 1; /* [4..4]  */
        unsigned int    gt_pclk_timer1             : 1; /* [5..5]  */
        unsigned int    gt_clk_timer1              : 1; /* [6..6]  */
        unsigned int    gt_pclk_timer2             : 1; /* [7..7]  */
        unsigned int    gt_clk_timer2              : 1; /* [8..8]  */
        unsigned int    gt_pclk_timer3             : 1; /* [9..9]  */
        unsigned int    gt_clk_timer3              : 1; /* [10..10]  */
        unsigned int    gt_pclk_ao_gpio0           : 1; /* [11..11]  */
        unsigned int    gt_pclk_ao_gpio1           : 1; /* [12..12]  */
        unsigned int    gt_pclk_ao_gpio2           : 1; /* [13..13]  */
        unsigned int    gt_pclk_ao_gpio3           : 1; /* [14..14]  */
        unsigned int    gt_pclk_ao_ioc             : 1; /* [15..15]  */
        unsigned int    gt_clk_out0                : 1; /* [16..16]  */
        unsigned int    gt_clk_out1                : 1; /* [17..17]  */
        unsigned int    gt_clk_jtag_auth           : 1; /* [18..18]  */
        unsigned int    gt_pclk_syscnt             : 1; /* [19..19]  */
        unsigned int    gt_clk_syscnt              : 1; /* [20..20]  */
        unsigned int    gt_pclk_ao_gpio4           : 1; /* [21..21]  */
        unsigned int    gt_pclk_ao_gpio5           : 1; /* [22..22]  */
        unsigned int    gt_clk_sci0                : 1; /* [23..23]  */
        unsigned int    gt_clk_sci1                : 1; /* [24..24]  */
        unsigned int    gt_clk_memrep              : 1; /* [25..25]  */
        unsigned int    gt_clk_asp_subsys          : 1; /* [26..26]  */
        unsigned int    gt_clk_asp_tcxo            : 1; /* [27..27]  */
        unsigned int    gt_clk_bbpdrx              : 1; /* [28..28]  */
        unsigned int    gt_clk_aobus               : 1; /* [29..29]  */
        unsigned int    gt_pclk_efusec             : 1; /* [30..30]  */
        unsigned int    gt_clk_ppll0_sscg          : 1; /* [31..31] 整个寄存器的复位值由SCTRL的输入信号peri_clk_stat0[31:0]的复位值来定。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTAT0_T;    /* 外设时钟最终状态寄存器0 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_dw_axi          : 1; /* [0..0] 外设时钟使能控制：0：写0无效；1：写1使能IP时钟。 */
        unsigned int    gt_clk_asp_x2h             : 1; /* [1..1]  */
        unsigned int    gt_clk_asp_h2p             : 1; /* [2..2]  */
        unsigned int    gt_asp_cfg                 : 1; /* [3..3]  */
        unsigned int    gt_clk_bbpdrx_oth          : 1; /* [4..4]  */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPEREN1_T;    /* 外设时钟使能寄存器1 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_dw_axi          : 1; /* [0..0] 外设时钟禁止控制：0：写0无效；1：写1禁止IP时钟。 */
        unsigned int    gt_clk_asp_x2h             : 1; /* [1..1]  */
        unsigned int    gt_clk_asp_h2p             : 1; /* [2..2]  */
        unsigned int    gt_asp_cfg                 : 1; /* [3..3]  */
        unsigned int    gt_clk_bbpdrx_oth          : 1; /* [4..4]  */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERDIS1_T;    /* 外设时钟禁止寄存器1 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_dw_axi          : 1; /* [0..0] 外设时钟使能状态：0：IP时钟禁止状态；1：IP时钟使能状态。 */
        unsigned int    gt_clk_asp_x2h             : 1; /* [1..1]  */
        unsigned int    gt_clk_asp_h2p             : 1; /* [2..2]  */
        unsigned int    gt_asp_cfg                 : 1; /* [3..3]  */
        unsigned int    gt_clk_bbpdrx_oth          : 1; /* [4..4] modem子系统送给bbpdrx的时钟 */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCLKEN1_T;    /* 外设时钟使能状态寄存器1 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_dw_axi          : 1; /* [0..0] 外设时钟最终状态：0：IP时钟禁止状态；1：IP时钟使能状态。 */
        unsigned int    gt_clk_asp_x2h             : 1; /* [1..1]  */
        unsigned int    gt_clk_asp_h2p             : 1; /* [2..2]  */
        unsigned int    gt_asp_cfg                 : 1; /* [3..3]  */
        unsigned int    gt_clk_bbpdrx_oth          : 1; /* [4..4] modem子系统送给bbpdrx的时钟 */
        unsigned int    reserved                   : 22; /* [26..5] 保留。 */
        unsigned int    swdone_clk_asp_subsys_div  : 1; /* [27..27] clk_asp_subsysDIV分频比切换是否完成指示信号：0：未完成；1：完成； */
        unsigned int    swdone_clk_sci_div         : 1; /* [28..28] clk_sci DIV分频比切换是否完成指示信号：0：未完成；1：完成； */
        unsigned int    swdone_clk_aobus_div       : 1; /* [29..29] clk_aobus DIV分频比切换是否完成指示信号：0：未完成；1：完成； */
        unsigned int    aobusclksw2sys             : 1; /* [30..30] aobus clk切换至晶振时钟指示，高有效。 */
        unsigned int    aobusclksw2pll             : 1; /* [31..31] aobus clk切换至PLL时钟指示，高有效。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTAT1_T;    /* 外设时钟最终状态寄存器1 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPEREN2_T;    /* 外设时钟使能寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERDIS2_T;    /* 外设时钟禁止寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCLKEN2_T;    /* 外设时钟使能状态寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 整个寄存器的复位值由SCTRL的输入信号peri_clk_stat2[31:0]的复位值来定。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTAT2_T;    /* 外设时钟最终状态寄存器2 */

typedef union
{
    struct
    {
        unsigned int    ip_rst_ao_cc               : 1; /* [0..0] IP软复位使能：0：IP软复位使能状态不变；1：IP软复位使能。 */
        unsigned int    ip_rst_rtc                 : 1; /* [1..1]  */
        unsigned int    ip_rst_rtc1                : 1; /* [2..2]  */
        unsigned int    ip_rst_timer0              : 1; /* [3..3]  */
        unsigned int    ip_rst_timer1              : 1; /* [4..4]  */
        unsigned int    ip_rst_timer2              : 1; /* [5..5]  */
        unsigned int    ip_rst_timer3              : 1; /* [6..6]  */
        unsigned int    rst_asp_cfg                : 1; /* [7..7]  */
        unsigned int    rst_asp_dw_axi             : 1; /* [8..8]  */
        unsigned int    rst_asp_x2h                : 1; /* [9..9]  */
        unsigned int    rst_asp_h2p                : 1; /* [10..10]  */
        unsigned int    ip_rst_ao_gpio0            : 1; /* [11..11]  */
        unsigned int    ip_rst_ao_gpio1            : 1; /* [12..12]  */
        unsigned int    ip_rst_ao_gpio2            : 1; /* [13..13]  */
        unsigned int    ip_rst_ao_gpio3            : 1; /* [14..14]  */
        unsigned int    ip_rst_ao_gpio4            : 1; /* [15..15]  */
        unsigned int    ip_rst_ao_gpio5            : 1; /* [16..16]  */
        unsigned int    reserved_3                 : 1; /* [17..17] 保留。 */
        unsigned int    ip_rst_ao_ioc              : 1; /* [18..18]  */
        unsigned int    ip_prst_syscnt             : 1; /* [19..19]  */
        unsigned int    ip_rst_syscnt              : 1; /* [20..20]  */
        unsigned int    reserved_2                 : 2; /* [22..21] 保留。 */
        unsigned int    ip_rst_sci0                : 1; /* [23..23]  */
        unsigned int    ip_rst_sci1                : 1; /* [24..24]  */
        unsigned int    reserved_1                 : 1; /* [25..25] 保留。 */
        unsigned int    ip_rst_asp_subsys          : 1; /* [26..26]  */
        unsigned int    ip_rst_bbpdrx              : 1; /* [27..27]  */
        unsigned int    reserved_0                 : 1; /* [28..28] 保留。 */
        unsigned int    ip_rst_aobus               : 1; /* [29..29]  */
        unsigned int    sc_rst_src_clr             : 1; /* [30..30] 复位源信息清除控制：0：写0无效果；1：复位源信息清除，并关闭复位源记录功能； */
        unsigned int    sc_pmurst_ctrl             : 1; /* [31..31] PMU复位清除控制：0：写0无效果；1：PMU复位撤销，并关闭PMU复位功能； */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTEN0_T;    /* 外设软复位使能寄存器0 */

typedef union
{
    struct
    {
        unsigned int    ip_rst_ao_cc               : 1; /* [0..0] IP软复位撤离：0：IP软复位使能状态不变；1：IP软复位撤离。 */
        unsigned int    ip_rst_rtc                 : 1; /* [1..1]  */
        unsigned int    ip_rst_rtc1                : 1; /* [2..2]  */
        unsigned int    ip_rst_timer0              : 1; /* [3..3]  */
        unsigned int    ip_rst_timer1              : 1; /* [4..4]  */
        unsigned int    ip_rst_timer2              : 1; /* [5..5]  */
        unsigned int    ip_rst_timer3              : 1; /* [6..6]  */
        unsigned int    rst_asp_cfg                : 1; /* [7..7]  */
        unsigned int    rst_asp_dw_axi             : 1; /* [8..8]  */
        unsigned int    rst_asp_x2h                : 1; /* [9..9]  */
        unsigned int    rst_asp_h2p                : 1; /* [10..10]  */
        unsigned int    ip_rst_ao_gpio0            : 1; /* [11..11]  */
        unsigned int    ip_rst_ao_gpio1            : 1; /* [12..12]  */
        unsigned int    ip_rst_ao_gpio2            : 1; /* [13..13]  */
        unsigned int    ip_rst_ao_gpio3            : 1; /* [14..14]  */
        unsigned int    ip_rst_ao_gpio4            : 1; /* [15..15]  */
        unsigned int    ip_rst_ao_gpio5            : 1; /* [16..16]  */
        unsigned int    reserved_3                 : 1; /* [17..17] 保留。 */
        unsigned int    ip_rst_ao_ioc              : 1; /* [18..18]  */
        unsigned int    ip_prst_syscnt             : 1; /* [19..19]  */
        unsigned int    ip_rst_syscnt              : 1; /* [20..20]  */
        unsigned int    reserved_2                 : 2; /* [22..21] 保留。 */
        unsigned int    ip_rst_sci0                : 1; /* [23..23]  */
        unsigned int    ip_rst_sci1                : 1; /* [24..24]  */
        unsigned int    reserved_1                 : 1; /* [25..25] 保留。 */
        unsigned int    ip_rst_asp_subsys          : 1; /* [26..26]  */
        unsigned int    ip_rst_bbpdrx              : 1; /* [27..27]  */
        unsigned int    reserved_0                 : 1; /* [28..28] 保留。 */
        unsigned int    ip_rst_aobus               : 1; /* [29..29]  */
        unsigned int    sc_rst_src_clr             : 1; /* [30..30] 复位源清除信号控制：0：写0无效果；1：复位源清除撤销，即复位源记录功能启用； */
        unsigned int    sc_pmurst_ctrl             : 1; /* [31..31] PMU复位功能控制：0：写0无效果；1：PMU复位功能启用； */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTDIS0_T;    /* 外设软复位撤离寄存器0 */

typedef union
{
    struct
    {
        unsigned int    ip_rst_ao_cc               : 1; /* [0..0] 外设软复位使能状态：0：IP软复位使能撤销；1：IP软复位使能； */
        unsigned int    ip_rst_rtc                 : 1; /* [1..1]  */
        unsigned int    ip_rst_rtc1                : 1; /* [2..2]  */
        unsigned int    ip_rst_timer0              : 1; /* [3..3]  */
        unsigned int    ip_rst_timer1              : 1; /* [4..4]  */
        unsigned int    ip_rst_timer2              : 1; /* [5..5]  */
        unsigned int    ip_rst_timer3              : 1; /* [6..6]  */
        unsigned int    rst_asp_cfg                : 1; /* [7..7]  */
        unsigned int    rst_asp_dw_axi             : 1; /* [8..8]  */
        unsigned int    rst_asp_x2h                : 1; /* [9..9]  */
        unsigned int    rst_asp_h2p                : 1; /* [10..10]  */
        unsigned int    ip_rst_ao_gpio0            : 1; /* [11..11]  */
        unsigned int    ip_rst_ao_gpio1            : 1; /* [12..12]  */
        unsigned int    ip_rst_ao_gpio2            : 1; /* [13..13]  */
        unsigned int    ip_rst_ao_gpio3            : 1; /* [14..14]  */
        unsigned int    ip_rst_ao_gpio4            : 1; /* [15..15]  */
        unsigned int    ip_rst_ao_gpio5            : 1; /* [16..16]  */
        unsigned int    reserved_3                 : 1; /* [17..17] 保留。 */
        unsigned int    ip_rst_ao_ioc              : 1; /* [18..18]  */
        unsigned int    ip_prst_syscnt             : 1; /* [19..19]  */
        unsigned int    ip_rst_syscnt              : 1; /* [20..20]  */
        unsigned int    reserved_2                 : 2; /* [22..21] 保留。 */
        unsigned int    ip_rst_sci0                : 1; /* [23..23]  */
        unsigned int    ip_rst_sci1                : 1; /* [24..24]  */
        unsigned int    reserved_1                 : 1; /* [25..25] 保留。 */
        unsigned int    ip_rst_asp_subsys          : 1; /* [26..26]  */
        unsigned int    ip_rst_bbpdrx              : 1; /* [27..27]  */
        unsigned int    reserved_0                 : 1; /* [28..28] 保留。 */
        unsigned int    ip_rst_aobus               : 1; /* [29..29]  */
        unsigned int    sc_rst_src_clr             : 1; /* [30..30] 复位源清除控制状态：0：禁用复位源记录功能；1：开启复位源记录功能； */
        unsigned int    sc_pmurst_ctrl             : 1; /* [31..31] PMU复位功能控制状态：0：开启PMU复位功能；1：禁用PMU复位功能； */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTSTAT0_T;    /* 外设软复位状态寄存器0 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTEN1_T;    /* 外设软复位使能寄存器1 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTDIS1_T;    /* 外设软复位撤离寄存器1 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTSTAT1_T;    /* 外设软复位状态寄存器1 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTEN2_T;    /* 外设软复位使能寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTDIS2_T;    /* 外设软复位撤离寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERRSTSTAT2_T;    /* 外设软复位状态寄存器2 */

typedef union
{
    struct
    {
        unsigned int    rst_gt_rtc_bypass          : 1; /* [0..0] 1:BYPASS复位&时钟门控防总线挂死功能0:使能复位&时钟门控防总线挂死功能 */
        unsigned int    rst_gt_rtc1_bypass         : 1; /* [1..1]  */
        unsigned int    rst_gt_timer0_bypass       : 1; /* [2..2]  */
        unsigned int    rst_gt_timer1_bypass       : 1; /* [3..3]  */
        unsigned int    rst_gt_timer2_bypass       : 1; /* [4..4]  */
        unsigned int    rst_gt_timer3_bypass       : 1; /* [5..5]  */
        unsigned int    rst_gt_gpio0_bypass        : 1; /* [6..6]  */
        unsigned int    rst_gt_gpio1_bypass        : 1; /* [7..7]  */
        unsigned int    rst_gt_gpio2_bypass        : 1; /* [8..8]  */
        unsigned int    rst_gt_gpio3_bypass        : 1; /* [9..9]  */
        unsigned int    rst_gt_gpio4_bypass        : 1; /* [10..10]  */
        unsigned int    rst_gt_gpio5_bypass        : 1; /* [11..11]  */
        unsigned int    rst_gt_ioc_bypass          : 1; /* [12..12]  */
        unsigned int    rst_gt_syscnt_bypass       : 1; /* [13..13]  */
        unsigned int    rst_gt_sci0_bypass         : 1; /* [14..14]  */
        unsigned int    rst_gt_sci1_bypass         : 1; /* [15..15]  */
        unsigned int    rst_gt_bbpdrx_bypass       : 1; /* [16..16]  */
        unsigned int    rst_gt_efusec_bypass       : 1; /* [17..17]  */
        unsigned int    reserved                   : 14; /* [31..18] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCIPCLKRSTBUS_T;    /* IP防总线挂死控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    audioisoen                 : 1; /* [0..0] Audio子系统ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCISOEN_T;    /* 掉电子系统ISO使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    audioisoen                 : 1; /* [0..0] Audio子系统ISO单元使能控制：写1执行ISO撤消操作。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCISODIS_T;    /* 掉电子系统ISO使能撤销寄存器 */

typedef union
{
    struct
    {
        unsigned int    audioisoen                 : 1; /* [0..0] Audio子系统ISO单元使能控制：1--ISO使能 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCISOSTAT_T;    /* 掉电子系统ISO使能状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    audiopwren                 : 1; /* [0..0] AUDIO子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPWREN_T;    /* 掉电子系统电源使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    audiopwren                 : 1; /* [0..0] AUDIO子系统电源使能撤销控制：写1执行电源使能撤销操作。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPWRDIS_T;    /* 掉电子系统电源使能撤销寄存器 */

typedef union
{
    struct
    {
        unsigned int    audiopwrstat               : 1; /* [0..0] AUDIO子系统电源使能状态：0：AUDIO子系统电源使能撤销；1：AUDIO子系统电源使能。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPWRSTAT_T;    /* 掉电子系统电源使能状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    audiopwrack                : 1; /* [0..0] AUDIO子系统电源状态：0：AUDIO子系统电源切断状态；1：AUDIO子系统电源供给状态。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPWRACK_T;    /* 掉电子系统最终电源状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    peri_pwr_down_time         : 25; /* [24..0] 指示PMU对外设区掉电所需的时间。稳定时间计算公式：（33554432-peri_pwr_down_time+3）。计数时钟为32K。(下电完成时间大约为600us,默认为计数20个32K时钟周期) */
        unsigned int    reserved                   : 7; /* [31..25] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERPWRDOWNTIME_T;    /* 外设区掉电时间配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    peri_pwr_up_time           : 25; /* [24..0] 指示PMU对外设区上电所需的时间。稳定时间计算公式：（33554432-peri_pwr_up_time+3）。计数时钟为32K。(上电到外设区完成大约为1.26ms默认为计数42个32K时钟周期) */
        unsigned int    reserved                   : 7; /* [31..25] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERPWRUPTIME_T;    /* 外设区上电时间配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    sc_div_asp_subsys          : 3; /* [2..0] ASP SUBSYS时钟分频比。（源时钟为PPLL0）3'h0:1；3'h1:2；3'h2:3；3'h3:4；……3'h7:8； */
        unsigned int    sc_div_hifidsp             : 6; /* [8..3] HIFIDSP时钟分频比。6'h0:1；6'h1:2；6'h2:3；6'h3:4；…6'h1F:64； */
        unsigned int    sc_div_sci                 : 2; /* [10..9] SCI时钟分频比。(源时钟为clk_aobus 60MHz时钟，分频单独可配)2'h0:1；2'h1:2；2'h2:3；2'h3:4； */
        unsigned int    reserved                   : 4; /* [14..11] 保留。 */
        unsigned int    extclk_en                  : 1; /* [15..15] 备用时钟使能，高有效。 */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdiv每个比特位的使能位：只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV0_T;    /* 时钟分频比控制寄存器0 */

typedef union
{
    struct
    {
        unsigned int    sc_div_aobus               : 6; /* [5..0] AOBUS时钟分频比选择：(源时钟为PPLL0时钟，分频比单独可配)6'h0:1；6'h1:2；6'h2:3；…6'h3E:63；6'h3F:64； */
        unsigned int    div_clkout0_tcxo           : 3; /* [8..6] clkout0 tcxo时钟分频比选择：（源时钟为19.2MHz的晶振时钟）3'h0:1；3'h1:2；3'h2:3；…3'h6:7；3'h7:8； */
        unsigned int    div_clkout1_tcxo           : 3; /* [11..9] clkout1 tcxo时钟分频比选择：（源时钟为19.2MHz的晶振时钟）3'h0:1；3'h1:2；3'h2:3；…3'h6:7；3'h7:8； */
        unsigned int    sel_clkout0                : 2; /* [13..12] clkout0 时钟源选择：0：32KHz；1：19.2MHz时钟分频；2/3：PPLL3时钟分频； */
        unsigned int    sel_clkout1                : 2; /* [15..14] clkout1 时钟源选择：0：32KHz；1：19.2MHz时钟分频；2/3：PPLL3时钟分频； */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdiv每个比特位的使能位：只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV1_T;    /* 时钟分频比控制寄存器1 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_asp_subsys          : 1; /* [0..0] 时钟门控配置：0：时钟关闭；1：时钟开启。 */
        unsigned int    gt_hifidsp_clk_div         : 1; /* [1..1]  */
        unsigned int    gt_clk_sci                 : 1; /* [2..2]  */
        unsigned int    gt_clk_aobus               : 1; /* [3..3]  */
        unsigned int    gt_asp_hclk_div            : 1; /* [4..4]  */
        unsigned int    reserved_1                 : 3; /* [7..5] 保留。 */
        unsigned int    sc_div_asp_hclk            : 2; /* [9..8] asp hclk分频比：2'b0:1；2'b1:2；…… */
        unsigned int    reserved_0                 : 6; /* [15..10] 保留。 */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdiv每个比特位的使能位：只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV2_T;    /* 时钟分频比控制寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 16; /* [15..0] 保留。 */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdiv每个比特位的使能位：只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV3_T;    /* 时钟分频比控制寄存器3 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 16; /* [15..0] 保留。 */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdiv每个比特位的使能位：只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV4_T;    /* 时钟分频比控制寄存器4 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 16; /* [15..0] 保留。 */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdiv每个比特位的使能位：只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKDIV5_T;    /* 时钟分频比控制寄存器5 */

typedef union
{
    struct
    {
        unsigned int    efusec_mem_ctrl            : 16; /* [15..0] efusec的MEMORY控制 */
        unsigned int    efuse_remap                : 1; /* [16..16] 送给EFUSEC的REMAP控制 */
        unsigned int    reserved                   : 15; /* [31..17] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL0_T;    /* 外设控制寄存器0 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL1_T;    /* 外设控制寄存器1 */

typedef union
{
    struct
    {
        unsigned int    repair_disable             : 20; /* [19..0] 用于指示各个IP是否需要做mem repair:bit[19]:MRB19-VENCbit[18]:MRB18-VDECbit[17]:MRB17-MDDRC/MCUbit[16]:MRB16-LTE_BBP_WRAPbit[15]:MRB15-LTE_BBPbit[14]:MRB14-BBP_COMMbit[13]:MRB13-BBE16_WRAPbit[12]:MRB12-MODEM_PERI_WRAPbit[11]:MRB11-ISPbit[10]:MRB10-MALI_SHADERCORE3bit[9]:MRB9-MALI_SHADERCORE2bit[8]:MRB8-MALI_SHADERCORE1bit[7]:MRB7-MALI_SHADERCORE0bit[6]:MRB6-MALI_TOPbit[5]:MRB5-DSS_SDPbit[4]:MRB4-DSS_SUBSYSbit[3]:MRB3-ASP_SUBSYSbit[2]:MRB2-AO_M3_MEMbit[1]:MRB1-A7_CLUSTERbit[0]:MRB0-A15_CLUSTER0代表修复，1代表不修复 */
        unsigned int    reserved_1                 : 4; /* [23..20] reserved */
        unsigned int    jtaq_to_sdcard             : 1; /* [24..24] 送给JTAG MUX的控制信号 */
        unsigned int    reserved_0                 : 7; /* [31..25] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL2_T;    /* 外设控制寄存器2 */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 1; /* [0..0] reserved */
        unsigned int    reset_memrep_msk           : 1; /* [1..1] reset_memrep_msk */
        unsigned int    repair_iddq                : 1; /* [2..2] 1'b0:非IDDQ模式1'b1:BISR控制EFUSE进入IDDQ模式 */
        unsigned int    repair_frm_sram            : 1; /* [3..3] 指示修复数据来源SRAM：1'b0:1'b1:修复数据来源SRAM */
        unsigned int    repair_frm_efu             : 1; /* [4..4] 指示修复数据来源EFUSE：1'b0:1'b1:修复数据来源EFUSE此信号与从CRG输出的reset_memrep控制做逻辑后输出给BISR */
        unsigned int    dram_pwr_ctl               : 3; /* [7..5] 控制内部双端口RAM POWER */
        unsigned int    efusec_timeout_bypass      : 1; /* [8..8] efusec timeout bypass */
        unsigned int    bbdrx_timeout_bypass       : 1; /* [9..9] bbdrx timeout bypass */
        unsigned int    sleep_mode_cfgbus_bypass   : 1; /* [10..10] 1'b0:sleepmode有效时关时钟1'b1:sleepmode有效时不关时钟 */
        unsigned int    sleep_mode_lpmcu_bypass    : 1; /* [11..11] 1'b0:sleepmode有效时关时钟1'b1:sleepmode有效时不关时钟 */
        unsigned int    sleep_mode_iomcu_bypass    : 1; /* [12..12] 1'b0:sleepmode有效时关时钟1'b1:sleepmode有效时不关时钟 */
        unsigned int    sleep_mode_aobus_bypass    : 1; /* [13..13] 1'b0:sleepmode有效时关时钟1'b1:sleepmode有效时不关时钟 */
        unsigned int    bbp_clk_en                 : 1; /* [14..14] 送给BBPDRX的时钟使能信号：1'b0:关时钟1'b1:开时钟 */
        unsigned int    reserved_0                 : 17; /* [31..15] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL3_T;    /* 外设控制寄存器3 */

typedef union
{
    struct
    {
        unsigned int    ddr_ret_en                 : 2; /* [1..0] 配置DDRPHY进入Retention模式的控制信号，写2'b11有效。 */
        unsigned int    reserved                   : 30; /* [31..2] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL4_T;    /* 外设控制寄存器4 */

typedef union
{
    struct
    {
        unsigned int    usim0_io_sel18             : 1; /* [0..0] USIM卡0的ODIO电压切换控制信号 */
        unsigned int    usim1_io_sel18             : 1; /* [1..1] USIM卡1的ODIO电压切换控制信号 */
        unsigned int    sdcard_io_sel18            : 1; /* [2..2] SDCARD的ODIO电压切换信号 */
        unsigned int    tp_sel                     : 3; /* [5..3] 测试信号分组选择；详细分配情况请参考集成设计文档 */
        unsigned int    tcxo_mode                  : 1; /* [6..6] 送给MODEM的晶振控制 */
        unsigned int    reserved                   : 25; /* [31..7] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL5_T;    /* 外设控制寄存器5 */

typedef union
{
    struct
    {
        unsigned int    peri_io_ret                : 1; /* [0..0] 外设区非启动相关IO Retetion：0：Retetion撤销；1：Retetion使能； */
        unsigned int    reserved_1                 : 3; /* [3..1] 保留。 */
        unsigned int    peri_bootio_ret            : 1; /* [4..4] 外设区启动相关IO Retetion：0：Retetion撤销；1：Retetion使能； */
        unsigned int    peri_bootio_ret_mode       : 1; /* [5..5] 外设区启动相关IO Retetion控制模式：0：由比特4的配置值控制；1：由硬件自动控制； */
        unsigned int    reserved_0                 : 26; /* [31..6] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERCTRL6_T;    /* 外设控制寄存器6 */

typedef union
{
    struct
    {
        unsigned int    asp_dwaxi_dlock_wr         : 1; /* [0..0] asp桥dlock wr状态 */
        unsigned int    asp_dwaxi_dlock_id         : 4; /* [4..1] asp桥dlock id状态 */
        unsigned int    asp_dwaxi_dlock_slv        : 3; /* [7..5] asp桥slave dlock状态 */
        unsigned int    asp_dwaxi_dlock_mst        : 2; /* [9..8] asp桥master dlock状态 */
        unsigned int    sys_pw_stat                : 4; /* [13..10] 系统掉电状态机状态 */
        unsigned int    tcxoseq_stat0              : 3; /* [16..14] 晶振0控制逻辑状态机状态 */
        unsigned int    tcxoseq_stat1              : 3; /* [19..17] 晶振1控制逻辑状态机状态 */
        unsigned int    tp_a3_grp                  : 9; /* [28..20] bit[28]:lpram2 ret2n outbit[27]:lpram2 ret1n outbit[26]:lpram2 pgen outbit[25]:lpram1 ret2n outbit[24]:lpram1 ret1n outbit[23]:lpram1 pgen outbit[22]:lpram0 ret2n outbit[21]:lpram0 ret1n outbit[20]:lpram0 pgen out */
        unsigned int    tp_a4_grp0                 : 2; /* [30..29] bit[30]:lpram3 ret2n outbit[29]:lpram3 ret1n out */
        unsigned int    tp_a4_grp1                 : 1; /* [31..31] bit[31]:memrep pgen out */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS0_T;    /* 外设状态寄存器0 */

typedef union
{
    struct
    {
        unsigned int    err_flag                   : 32; /* [31..0] memory repair模块err指示 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS1_T;    /* 外设状态寄存器1 */

typedef union
{
    struct
    {
        unsigned int    peri_stat2                 : 10; /* [9..0] bit[9]:sclkbit[8]:por_int_nbit[7]:xtal_sw_ackbit[6]:xtal_sw_reqbit[5]:ppll0_enbit[4]:ppll0_lockbit[3]:reset_memrep_nbit[2]:preset_efusec_nbit[1]:pll_sw_reqbit[0]:pll_sw_ack */
        unsigned int    reserved                   : 22; /* [31..10] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS2_T;    /* 外设状态寄存器2 */

typedef union
{
    struct
    {
        unsigned int    efusec_timeout_dbg_info    : 32; /* [31..0] efusec timeout dbg info */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS3_T;    /* 外设状态寄存器3 */

typedef union
{
    struct
    {
        unsigned int    bbdrx_timeout_dbg_info     : 32; /* [31..0] bbdrx_timeout_dbg_info */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCPERSTATUS4_T;    /* 外设状态寄存器4 */

typedef union
{
    struct
    {
        unsigned int    deepsleeped                : 1; /* [0..0] 系统是否曾经进入过掉电状态机的DEEP SLEEP模式指示位。0：系统没有进入过DEEP SLEEP状态；1：系统曾经进入过DEEP SLEEP状态且没有被读清。（对该比特位写1清除该位的状态到复位值） */
        unsigned int    reserved_1                 : 3; /* [3..1] 保留。 */
        unsigned int    sleeped                    : 1; /* [4..4] 系统是否曾经进入过系统状态机的 SLEEP模式指示位。0：系统没有进入过SLEEP状态；1：系统曾经进入过SLEEP状态且没有被读清。（对该比特位写1清除该位的状态到复位值） */
        unsigned int    reserved_0                 : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCDEEPSLEEPED_T;    /* 用于指示系统曾经进入过深度睡眠的状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    mrb_efuse_busy             : 20; /* [19..0] 用于指示各个IP是否完成mem repair:bit[19]:MRB19-VENCbit[18]:MRB18-VDECbit[17]:MRB17-MDDRC/MCUbit[16]:MRB16-LTE_BBP_WRAPbit[15]:MRB15-LTE_BBPbit[14]:MRB14-BBP_COMMbit[13]:MRB13-BBE16_WRAPbit[12]:MRB12-MODEM_PERI_WRAPbit[11]:MRB11-ISPbit[10]:MRB10-MALI_SHADERCORE3bit[9]:MRB9-MALI_SHADERCORE2bit[8]:MRB8-MALI_SHADERCORE1bit[7]:MRB7-MALI_SHADERCORE0bit[6]:MRB6-MALI_TOPbit[5]:MRB5-DSS_SDPbit[4]:MRB4-DSS_SUBSYSbit[3]:MRB3-ASP_SUBSYSbit[2]:MRB2-AO_M3_MEMbit[1]:MRB1-A7_CLUSTERbit[0]:MRB0-A15_CLUSTER0代表完成，1代表未完成 */
        unsigned int    reserved                   : 12; /* [31..20] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMRBBUSYSTAT_T;    /* MRB EFUSE BUSY状态指示寄存器 */

typedef union
{
    struct
    {
        unsigned int    swaddr                     : 32; /* [31..0] 保存软件的入口地址。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCSWADDR_T;    /* 用于保存软件入口地址的寄存器 */

typedef union
{
    struct
    {
        unsigned int    ddrtrainaddr               : 32; /* [31..0] 保存DDR训练数据的地址。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCDDRADDR_T;    /* 用于保留DDR训练数据的地址的寄存器 */

typedef union
{
    struct
    {
        unsigned int    ddrtraindata               : 32; /* [31..0] 保存DDR的训练数据。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCDDRDATA_T;    /* 用于保存DDR训练数据的寄存器 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器0，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA0_T;    /* 用于软件使用的存储数据寄存器0 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器1，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA1_T;    /* 用于软件使用的存储数据寄存器1 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器2，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA2_T;    /* 用于软件使用的存储数据寄存器2 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器3，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA3_T;    /* 用于软件使用的存储数据寄存器3 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器4，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA4_T;    /* 用于软件使用的存储数据寄存器4 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器5，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA5_T;    /* 用于软件使用的存储数据寄存器5 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器6，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA6_T;    /* 用于软件使用的存储数据寄存器6 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器7，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA7_T;    /* 用于软件使用的存储数据寄存器7 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器8，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA8_T;    /* 用于软件使用的存储数据寄存器8 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器9，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA9_T;    /* 用于软件使用的存储数据寄存器9 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器10，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA10_T;    /* 用于软件使用的存储数据寄存器10 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器11，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA11_T;    /* 用于软件使用的存储数据寄存器11 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器12，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA12_T;    /* 用于软件使用的存储数据寄存器12 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器13，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA13_T;    /* 用于软件使用的存储数据寄存器13 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器14，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA14_T;    /* 用于软件使用的存储数据寄存器14 */

typedef union
{
    struct
    {
        unsigned int    bakdata                    : 32; /* [31..0] 给软件预留的数据寄存器15，用于临时数据的缓存。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBAKDATA15_T;    /* 用于软件使用的存储数据寄存器15 */

typedef union
{
    struct
    {
        unsigned int    int_wakeup_sys             : 1; /* [0..0] 1：中断有效；0：中断无效；注：该中断状态是已经考虑中断屏蔽配置之后的状态。 */
        unsigned int    drx0_int                   : 1; /* [1..1] 1：中断有效；0：中断无效；注：该中断状态是已经考虑中断屏蔽配置之后的状态。 */
        unsigned int    drx1_int                   : 1; /* [2..2] 1：中断有效；0：中断无效；注：该中断状态是已经考虑中断屏蔽配置之后的状态。 */
        unsigned int    notdrx_int                 : 1; /* [3..3] 1：中断有效；0：中断无效；注：该中断状态是已经考虑中断屏蔽配置之后的状态。 */
        unsigned int    reserved                   : 28; /* [31..4] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCINT_GATHER_STAT_T;    /* 聚合后的中断状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    gpio_22_int                : 1; /* [0..0] 中断屏蔽寄存器。0：屏蔽有效；1：屏蔽无效； */
        unsigned int    gpio_23_int                : 1; /* [1..1]  */
        unsigned int    gpio_24_int                : 1; /* [2..2]  */
        unsigned int    gpio_25_int                : 1; /* [3..3]  */
        unsigned int    gpio_26_int                : 1; /* [4..4]  */
        unsigned int    rtc_int                    : 1; /* [5..5]  */
        unsigned int    rtc1_int                   : 1; /* [6..6]  */
        unsigned int    timer0_int                 : 1; /* [7..7]  */
        unsigned int    timer1_int                 : 1; /* [8..8]  */
        unsigned int    timer2_int                 : 1; /* [9..9]  */
        unsigned int    timer3_int                 : 1; /* [10..10]  */
        unsigned int    timer4_int                 : 1; /* [11..11]  */
        unsigned int    timer5_int                 : 1; /* [12..12]  */
        unsigned int    timer6_int                 : 1; /* [13..13]  */
        unsigned int    timer7_int                 : 1; /* [14..14]  */
        unsigned int    gic_irq_int0               : 1; /* [15..15]  */
        unsigned int    gic_irq_int1               : 1; /* [16..16]  */
        unsigned int    gic_fiq_int2               : 1; /* [17..17]  */
        unsigned int    gic_fiq_int3               : 1; /* [18..18]  */
        unsigned int    lpm3_int                   : 1; /* [19..19]  */
        unsigned int    iom3_int                   : 1; /* [20..20]  */
        unsigned int    asp_ipc_arm_int            : 1; /* [21..21]  */
        unsigned int    drx0_int                   : 1; /* [22..22]  */
        unsigned int    drx1_int                   : 1; /* [23..23]  */
        unsigned int    drx2_int                   : 1; /* [24..24]  */
        unsigned int    drx3_int                   : 1; /* [25..25]  */
        unsigned int    drx4_int                   : 1; /* [26..26]  */
        unsigned int    gpio_27_int                : 1; /* [27..27]  */
        unsigned int    gpio_asp_int               : 1; /* [28..28]  */
        unsigned int    gpio_asp_int_sc            : 1; /* [29..29]  */
        unsigned int    intr_asp_watchdog          : 1; /* [30..30]  */
        unsigned int    lpm3_wfi_int               : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCINT_MASK_T;    /* 中断屏蔽配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    gpio_22_int                : 1; /* [0..0] 中断状态寄存器。0：中断无效；1：中断有效； */
        unsigned int    gpio_23_int                : 1; /* [1..1]  */
        unsigned int    gpio_24_int                : 1; /* [2..2]  */
        unsigned int    gpio_25_int                : 1; /* [3..3]  */
        unsigned int    gpio_26_int                : 1; /* [4..4]  */
        unsigned int    rtc_int                    : 1; /* [5..5]  */
        unsigned int    rtc1_int                   : 1; /* [6..6]  */
        unsigned int    timer0_int                 : 1; /* [7..7]  */
        unsigned int    timer1_int                 : 1; /* [8..8]  */
        unsigned int    timer2_int                 : 1; /* [9..9]  */
        unsigned int    timer3_int                 : 1; /* [10..10]  */
        unsigned int    timer4_int                 : 1; /* [11..11]  */
        unsigned int    timer5_int                 : 1; /* [12..12]  */
        unsigned int    timer6_int                 : 1; /* [13..13]  */
        unsigned int    timer7_int                 : 1; /* [14..14]  */
        unsigned int    gic_int0                   : 1; /* [15..15]  */
        unsigned int    gic_int1                   : 1; /* [16..16]  */
        unsigned int    gic_int2                   : 1; /* [17..17]  */
        unsigned int    gic_int3                   : 1; /* [18..18]  */
        unsigned int    lpm3_int                   : 1; /* [19..19]  */
        unsigned int    iom3_int                   : 1; /* [20..20]  */
        unsigned int    asp_ipc_arm_int            : 1; /* [21..21]  */
        unsigned int    drx0_int                   : 1; /* [22..22]  */
        unsigned int    drx1_int                   : 1; /* [23..23]  */
        unsigned int    drx2_int                   : 1; /* [24..24]  */
        unsigned int    drx3_int                   : 1; /* [25..25]  */
        unsigned int    drx4_int                   : 1; /* [26..26]  */
        unsigned int    gpio_27_int                : 1; /* [27..27]  */
        unsigned int    intr_asp_watchdog          : 1; /* [28..28]  */
        unsigned int    gpio_asp_int               : 1; /* [29..29]  */
        unsigned int    reserved                   : 2; /* [31..30]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCINT_STAT_T;    /* 原始中断状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    drx0_int                   : 1; /* [0..0] 中断配置寄存器。0：属于DRX0的中断；1：属于DRX1的中断； */
        unsigned int    drx1_int                   : 1; /* [1..1]  */
        unsigned int    drx2_int                   : 1; /* [2..2]  */
        unsigned int    drx3_int                   : 1; /* [3..3]  */
        unsigned int    drx4_int                   : 1; /* [4..4]  */
        unsigned int    gpio_asp_int               : 1; /* [5..5]  */
        unsigned int    reserved                   : 26; /* [31..6]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCDRX_INT_CFG_T;    /* DRX中断分配配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    lpm3_wfi_int_clr           : 1; /* [0..0] 写操作清除lpm3_wfi_int中断；读操作返回lpm3_wfi_int中断状态 */
        unsigned int    reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3WFI_INT_CLR_T;    /* LPM3 WFI中断清除寄存器 */

typedef union
{
    struct
    {
        unsigned int    mali_dbgack_byp            : 1; /* [0..0] 0：bypass无效；1：bypass有效； */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMALIBYPCFG_T;    /* MALI DBGACK BYPASS配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    dapclkoff_sys_n            : 1; /* [0..0] M3 DAPCLK时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    reserved_1                 : 1; /* [1..1] reserved */
        unsigned int    rom_clk_clkoff_sys_n       : 1; /* [2..2] BOOTROM的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    ram_clk_clkoff_sys_n       : 1; /* [3..3] LP_RAM的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    reserved_0                 : 1; /* [4..4] reserved */
        unsigned int    ddrc_clk_clkoff_sys_n      : 1; /* [5..5] DDRC配置接口的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    tsen_clk_clkoff_sys_n      : 1; /* [6..6] TSENSORC的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    pmc_clk_clkoff_sys_n       : 1; /* [7..7] PMC的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    uart_clk_clkoff_sys_n      : 1; /* [8..8] UART的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    i2c_clk_clkoff_sys_n       : 1; /* [9..9] PMU_I2C的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    ssi_clk_clkoff_sys_n       : 1; /* [10..10] PMU_SSI的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    pcrg_clk_clkoff_sys_n      : 1; /* [11..11] 外设CRG配置接口的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    nandc_clk_clkoff_sys_n     : 1; /* [12..12] NANDC的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    wdog_clk_clkoff_sys_n      : 1; /* [13..13] LP_WDG的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    tim_clk_clkoff_sys_n       : 1; /* [14..14] LP_TIMER的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    cssys_clk_clkoff_sys_n     : 1; /* [15..15] CSSYS访问接口的时钟门控系统控制。0：关闭时钟；1：开启时钟 */
        unsigned int    clkdivmasken               : 16; /* [31..16] clkdiv每个比特位的使能位：只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3CLKEN_T;    /* LPM3子系统时钟使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    rst_software_req           : 1; /* [0..0] M3 Core复位请求，有效时将会复位M3 Core内所有逻辑 */
        unsigned int    coresight_soft_rst_req     : 1; /* [1..1] M3 CoreSight 系统软件复位请求，复位所有的coresight组件 */
        unsigned int    reserved_2                 : 1; /* [2..2] reserved */
        unsigned int    rom_soft_rst_req           : 1; /* [3..3] BOOTROM的复位请求。有效时将会复位BOOTROM接口逻辑。 */
        unsigned int    ram_soft_rst_req           : 1; /* [4..4] LP_RAM的复位请求。有效时将会复位LP_RAM接口逻辑。 */
        unsigned int    reserved_1                 : 1; /* [5..5] reserved */
        unsigned int    ddrc_soft_rst_req          : 1; /* [6..6] DDRC配置接口的复位请求。有效时将会复位DDRC的配置接口逻辑。 */
        unsigned int    tsen_soft_rst_req          : 1; /* [7..7] TSENSORC的复位请求。有效时将会复位TSENSORC所有逻辑。 */
        unsigned int    pmc_soft_rst_req           : 1; /* [8..8] PMC的复位请求。有效时将会复位PMC的所有逻辑。 */
        unsigned int    uart_soft_rst_req          : 1; /* [9..9] UART的复位请求。有效时将会复位UART所有逻辑。 */
        unsigned int    i2c_soft_rst_req           : 1; /* [10..10] PMU_I2C的复位请求。有效时将会复位PMU_I2C所有逻辑。 */
        unsigned int    ssi_soft_rst_req           : 1; /* [11..11] PMU_SSI的复位请求。有效时将会复位PMU_SSI所有逻辑。 */
        unsigned int    pcrg_soft_rst_req          : 1; /* [12..12] 外设CRG配置接口的复位请求。有效时将会复位外设CRG的配置接口逻辑。 */
        unsigned int    nandc_soft_rst_req         : 1; /* [13..13] NANDC的复位请求。有效时将会复位NANDC所有逻辑。 */
        unsigned int    wdog_soft_rst_req          : 1; /* [14..14] LP_WDG的复位请求。有效时将会复位watchdog所有逻辑。 */
        unsigned int    tim_soft_rst_req           : 1; /* [15..15] LP_TIMER的复位请求。有效时将会复位timer所有逻辑。 */
        unsigned int    cssys_soft_rst_req         : 1; /* [16..16] CSSYS访问接口的复位请求。有效时将会复位访问CSSYS的接口逻辑。 */
        unsigned int    reserved_0                 : 15; /* [31..17] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3RSTEN_T;    /* LPM3子系统软复位使能寄存器 */

typedef union
{
    struct
    {
        unsigned int    rst_software_req           : 1; /* [0..0] M3 Core复位请求，有效时将会复位M3 Core内所有逻辑 */
        unsigned int    coresight_soft_rst_req     : 1; /* [1..1] M3 CoreSight 系统软件复位请求，复位所有的coresight组件 */
        unsigned int    bus_soft_rst_req           : 1; /* [2..2] M3内部总线复位请求，有效时将会复位M3子系统内部AHB总线及APB总线，及对应设备。 */
        unsigned int    rom_soft_rst_req           : 1; /* [3..3] BOOTROM的复位请求。有效时将会复位BOOTROM接口逻辑。 */
        unsigned int    ram_soft_rst_req           : 1; /* [4..4] LP_RAM的复位请求。有效时将会复位LP_RAM接口逻辑。 */
        unsigned int    aon_soft_rst_req           : 1; /* [5..5] AON_SUBSYS访问接口的复位请求。有效时将会复位访问AON_SUBSYS的接口逻辑。 */
        unsigned int    ddrc_soft_rst_req          : 1; /* [6..6] DDRC配置接口的复位请求。有效时将会复位DDRC的配置接口逻辑。 */
        unsigned int    tsen_soft_rst_req          : 1; /* [7..7] TSENSORC的复位请求。有效时将会复位TSENSORC所有逻辑。 */
        unsigned int    pmc_soft_rst_req           : 1; /* [8..8] PMC的复位请求。有效时将会复位PMC的所有逻辑。 */
        unsigned int    uart_soft_rst_req          : 1; /* [9..9] UART的复位请求。有效时将会复位UART所有逻辑。 */
        unsigned int    i2c_soft_rst_req           : 1; /* [10..10] PMU_I2C的复位请求。有效时将会复位PMU_I2C所有逻辑。 */
        unsigned int    ssi_soft_rst_req           : 1; /* [11..11] PMU_SSI的复位请求。有效时将会复位PMU_SSI所有逻辑。 */
        unsigned int    pcrg_soft_rst_req          : 1; /* [12..12] 外设CRG配置接口的复位请求。有效时将会复位外设CRG的配置接口逻辑。 */
        unsigned int    nandc_soft_rst_req         : 1; /* [13..13] NANDC的复位请求。有效时将会复位NANDC所有逻辑。 */
        unsigned int    wdog_soft_rst_req          : 1; /* [14..14] LP_WDG的复位请求。有效时将会复位watchdog所有逻辑。 */
        unsigned int    tim_soft_rst_req           : 1; /* [15..15] LP_TIMER的复位请求。有效时将会复位timer所有逻辑。 */
        unsigned int    cssys_soft_rst_req         : 1; /* [16..16] CSSYS访问接口的复位请求。有效时将会复位访问CSSYS的接口逻辑。 */
        unsigned int    reserved                   : 15; /* [31..17] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3RSTDIS_T;    /* LPM3子系统软复位撤离寄存器 */

typedef union
{
    struct
    {
        unsigned int    rst_software_req           : 1; /* [0..0] M3 Core复位请求，有效时将会复位M3 Core内所有逻辑 */
        unsigned int    coresight_soft_rst_req     : 1; /* [1..1] M3 CoreSight 系统软件复位请求，复位所有的coresight组件 */
        unsigned int    bus_soft_rst_req           : 1; /* [2..2] M3内部总线复位请求，有效时将会复位M3子系统内部AHB总线及APB总线，及对应设备。 */
        unsigned int    rom_soft_rst_req           : 1; /* [3..3] BOOTROM的复位请求。有效时将会复位BOOTROM接口逻辑。 */
        unsigned int    ram_soft_rst_req           : 1; /* [4..4] LP_RAM的复位请求。有效时将会复位LP_RAM接口逻辑。 */
        unsigned int    aon_soft_rst_req           : 1; /* [5..5] AON_SUBSYS访问接口的复位请求。有效时将会复位访问AON_SUBSYS的接口逻辑。 */
        unsigned int    ddrc_soft_rst_req          : 1; /* [6..6] DDRC配置接口的复位请求。有效时将会复位DDRC的配置接口逻辑。 */
        unsigned int    tsen_soft_rst_req          : 1; /* [7..7] TSENSORC的复位请求。有效时将会复位TSENSORC所有逻辑。 */
        unsigned int    pmc_soft_rst_req           : 1; /* [8..8] PMC的复位请求。有效时将会复位PMC的所有逻辑。 */
        unsigned int    uart_soft_rst_req          : 1; /* [9..9] UART的复位请求。有效时将会复位UART所有逻辑。 */
        unsigned int    i2c_soft_rst_req           : 1; /* [10..10] PMU_I2C的复位请求。有效时将会复位PMU_I2C所有逻辑。 */
        unsigned int    ssi_soft_rst_req           : 1; /* [11..11] PMU_SSI的复位请求。有效时将会复位PMU_SSI所有逻辑。 */
        unsigned int    pcrg_soft_rst_req          : 1; /* [12..12] 外设CRG配置接口的复位请求。有效时将会复位外设CRG的配置接口逻辑。 */
        unsigned int    nandc_soft_rst_req         : 1; /* [13..13] NANDC的复位请求。有效时将会复位NANDC所有逻辑。 */
        unsigned int    wdog_soft_rst_req          : 1; /* [14..14] LP_WDG的复位请求。有效时将会复位watchdog所有逻辑。 */
        unsigned int    tim_soft_rst_req           : 1; /* [15..15] LP_TIMER的复位请求。有效时将会复位timer所有逻辑。 */
        unsigned int    cssys_soft_rst_req         : 1; /* [16..16] CSSYS访问接口的复位请求。有效时将会复位访问CSSYS的接口逻辑。 */
        unsigned int    reserved                   : 15; /* [31..17] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3RSTSTAT_T;    /* LPM3子系统软复位使能状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    boot_remap_en              : 1; /* [0..0] M3启动模式选择。0：从本地BOOTROM启动；1：从系统NAND启动 */
        unsigned int    mpudisable                 : 1; /* [1..1] M3内存保护单元除能信号 */
        unsigned int    nmi_in                     : 1; /* [2..2] 外部不可屏蔽中断输入 */
        unsigned int    bus_div_clk_sel            : 2; /* [4..3] bus_div_clk分频比选择信号00：bus_clk的1分频01：bus_clk的2分频10：bus_clk的3分频11：bus_clk的4分频 */
        unsigned int    sysresetreq_en             : 1; /* [5..5] M3 SYSRESETREQ使能控制。0：M3自身的系统复位请求不会被M3 CRG响应。1：M3自身的系统复位请求可被M3 CRG响应； */
        unsigned int    mem_ctrl_ema_lpram         : 5; /* [10..6] tcm与cache ram的memory速度调节信号。Bit[4:3]：EMAW，memory写速率控制。默认值2'b01Bit[2:0]：EMA，memory读速率控制。默认值3'b011 */
        unsigned int    lpm3idle_bypass            : 1; /* [11..11] 系统状态机LPM3 IDLE判断BYPASS控制：1'b1：bypass有效1'b0：bypass无效 */
        unsigned int    reserved_1                 : 12; /* [23..12] 保留。 */
        unsigned int    reserved_0                 : 8; /* [31..24] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3CTRL_T;    /* LPM3子系统控制配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    sysresetreq_sign_out_stat  : 1; /* [0..0] M3 SYSRESETREQ复位事件标志输出读清 */
        unsigned int    sleeping                   : 1; /* [1..1] M3 休眠状态指示信号 */
        unsigned int    lockup                     : 1; /* [2..2] M3 core锁死指示信号 */
        unsigned int    halted                     : 1; /* [3..3] M3 core停机指示信号（debug状态） */
        unsigned int    reserved                   : 28; /* [31..4] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3STAT_T;    /* LPM3子系统状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    lpramctrl_sel              : 1; /* [0..0] lpm3 ram低功耗模式控制选择：1：软件控制0：状态机控制 */
        unsigned int    lpram0_mod                 : 2; /* [2..1] lpm3 ram0低功耗模式配置（状态机控制）00/10:retention201:retention111:power-down */
        unsigned int    lpram1_mod                 : 2; /* [4..3] lpm3 ram1低功耗模式配置（状态机控制）00/10:retention201:retention111:power-down */
        unsigned int    lpram2_mod                 : 2; /* [6..5] lpm3 ram2低功耗模式配置（状态机控制）00/10:retention201:retention111:power-down */
        unsigned int    lpram3_mod                 : 2; /* [8..7] lpm3 ram3低功耗模式配置（状态机控制）00/10:retention201:retention111:power-down */
        unsigned int    lpram0ctrl_soft            : 3; /* [11..9] lpm0 ram低功耗控制信号软件配置：bit9:pgenbit10:ret1nbit11:ret2n */
        unsigned int    lpram1ctrl_soft            : 3; /* [14..12] lpm1 ram低功耗控制信号软件配置：bit12:pgenbit13:ret1nbit14:ret2n */
        unsigned int    lpram2ctrl_soft            : 3; /* [17..15] lpm2 ram低功耗控制信号软件配置：bit15:pgenbit16:ret1nbit17:ret2n */
        unsigned int    lpram3ctrl_soft            : 3; /* [20..18] lpm3 ram低功耗控制信号软件配置：bit18:pgenbit19:ret1nbit20:ret2n */
        unsigned int    memrep_ram_mod             : 2; /* [22..21] memrep ram低功耗模式配置（状态机控制）00/10:retention201:retention111:power-down */
        unsigned int    memrep_ramctrl_soft        : 3; /* [25..23] memrep ram低功耗控制信号软件配置：bit23:pgenbit24:ret1nbit25:ret2n */
        unsigned int    reserved                   : 6; /* [31..26] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3RAMCTRL_T;    /* LPM3 RAM 控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    g2_gdrx_depsleep_flag      : 1; /* [0..0] 状态指示信号，高有效 */
        unsigned int    g1_gdrx_depsleep_flag      : 1; /* [1..1] 状态指示信号，高有效 */
        unsigned int    wdrx_deepsleep_flag        : 1; /* [2..2] 状态指示信号，高有效 */
        unsigned int    reserved                   : 29; /* [31..3] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBBPDRXSTAT0_T;    /* BBPDRX子系统状态寄存器0 */

typedef union
{
    struct
    {
        unsigned int    ldrx2dbg_abs_timer         : 32; /* [31..0] ldrx2dbg_abs_timer的低32bit。(32KHz时钟域的计数) */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBBPDRXSTAT1_T;    /* BBPDRX子系统状态寄存器1 */

typedef union
{
    struct
    {
        unsigned int    ldrx2dbg_abs_timer         : 32; /* [31..0] ldrx2dbg_abs_timer的高32bit。(32KHz时钟域的计数) */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCBBPDRXSTAT2_T;    /* BBPDRX子系统状态寄存器2 */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCA7_EVENT_MASK_T;    /* A7 EVENT屏蔽寄存器 */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCA15_EVENT_MASK_T;    /* A15 EVENT屏蔽寄存器 */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCIOM3_EVENT_MASK_T;    /* IOM3 EVENT屏蔽寄存器 */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCLPM3_EVENT_MASK_T;    /* LPM3 EVENT屏蔽寄存器 */

typedef union
{
    struct
    {
        unsigned int    a7_event_mask              : 1; /* [0..0] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    a15_event_mask             : 1; /* [1..1] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    iom3_event_mask            : 1; /* [2..2] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    lpm3_event_mask            : 1; /* [3..3] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    mcpu_event_mask            : 1; /* [4..4] 1：屏蔽无效；0：屏蔽有效； */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMCPU_EVENT_MASK_T;    /* MCPU EVENT屏蔽寄存器 */

typedef union
{
    struct
    {
        unsigned int    a7_event                   : 1; /* [0..0] 1：event有效；0：event无效； */
        unsigned int    a15_event                  : 1; /* [1..1] 1：event有效；0：event无效； */
        unsigned int    iom3_event                 : 1; /* [2..2] 1：event有效；0：event无效； */
        unsigned int    lpm3_event                 : 1; /* [3..3] 1：event有效；0：event无效； */
        unsigned int    mcpu_event                 : 1; /* [4..4] 1：event有效；0：event无效； */
        unsigned int    reserved                   : 27; /* [31..5] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCEVENT_STAT_T;    /* EVENT状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    processor_jtag_sel         : 1; /* [0..0] 1：DSP jtag,function pins useless0：coresight jtag ,DSP on function pins */
        unsigned int    dsp_jtag_sel               : 2; /* [2..1] 10：hifi dsp的JTAG01：bbp dsp的JTAG00：jtag链串起来的hifi dsp->bbp dsp */
        unsigned int    reserved                   : 29; /* [31..3] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCJTAG_SEL_T;    /* JTAG选择控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    modem_key0                 : 32; /* [31..0] modem_key0 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMODEM_KEY0_T;    /* MODEM_KEY0 */

typedef union
{
    struct
    {
        unsigned int    modem_key1                 : 32; /* [31..0] modem_key1 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMODEM_KEY1_T;    /* MODEM_KEY1 */

typedef union
{
    struct
    {
        unsigned int    modem_key2                 : 32; /* [31..0] modem_key2 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMODEM_KEY2_T;    /* MODEM_KEY2 */

typedef union
{
    struct
    {
        unsigned int    modem_key3                 : 32; /* [31..0] modem_key3 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCMODEM_KEY3_T;    /* MODEM_KEY3 */

typedef union
{
    struct
    {
        unsigned int    cfg_djtag                  : 1; /* [0..0] 1：djtag disable0：normal写一次锁定，密码认证通过后数据才能写入并且只有当efuse_djtag_ctrl为2'b01时，cfg_djtag才输出到djtag_disable */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCFG_DJTAG_T;    /* DJTAG控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    a7cp15disable0             : 1; /* [0..0] A7 CPU0的控制bit，写1锁定，CPU0复位上升沿解锁 */
        unsigned int    a7cp15disable1             : 1; /* [1..1] A7 CPU1的控制bit，写1锁定，CPU1复位上升沿解锁 */
        unsigned int    a7cp15disable2             : 1; /* [2..2] A7 CPU2的控制bit，写1锁定，CPU2复位上升沿解锁 */
        unsigned int    a7cp15disable3             : 1; /* [3..3] A7 CPU3的控制bit，写1锁定，CPU3复位上升沿解锁 */
        unsigned int    a15cp15disable0            : 1; /* [4..4] A15 CPU0的控制bit，写1锁定，CPU0复位上升沿解锁 */
        unsigned int    a15cp15disable1            : 1; /* [5..5] A15 CPU1的控制bit，写1锁定，CPU1复位上升沿解锁 */
        unsigned int    a15cp15disable2            : 1; /* [6..6] A15 CPU2的控制bit，写1锁定，CPU2复位上升沿解锁 */
        unsigned int    a15cp15disable3            : 1; /* [7..7] A15 CPU3的控制bit，写1锁定，CPU3复位上升沿解锁 */
        unsigned int    a9cp15disable              : 1; /* [8..8] A9 CPU的控制bit，写1锁定，CPU复位上升沿解锁 */
        unsigned int    gicdisable                 : 1; /* [9..9] GIC的控制bit，写1锁定，GIC复位上升沿解锁 */
        unsigned int    reserved                   : 22; /* [31..10] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCP15_DISABLE_T;    /* CP15DISABLE控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    cnt_stat                   : 16; /* [15..0] clk_monitor模块时钟计数状态寄存器。当clk_cnt_en = 1'b1且在32KHz睡眠时钟上升或下降沿时更新，其余情况维持不变。 */
        unsigned int    reserved                   : 16; /* [31..16] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKCNTSTAT_T;    /* 时钟计数状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    cnt_cfg                    : 16; /* [15..0] clk_monitor模块时钟计数配置寄存器。 */
        unsigned int    timer_secu_en              : 1; /* [16..16] AO区TIMER2安全控制，使能时timer2的时钟有效，复位撤离，timer_clk_en2为32KHZ时钟0：安全控制不使能1：安全控制使能 */
        unsigned int    reserved                   : 13; /* [29..17] 保留。 */
        unsigned int    clk_cnt_en                 : 1; /* [30..30] clk_cnt使能配置。0：不使能1：使能 */
        unsigned int    clk_monitor_en             : 1; /* [31..31] clk_monitor模块使能配置。0：不使能1：使能注：要先配置cnt_cfg[15:0]，再配置clk_monitor_en。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKCNTCFG_T;    /* 时钟计数配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    intr_clr                   : 1; /* [0..0] 中断清除0：不清中断1：清中断注：写1之后要再写0，否则会一直处于清中断的状态。 */
        unsigned int    intr_mask                  : 1; /* [1..1] 中断屏蔽0：不屏蔽中断1：屏蔽中断 */
        unsigned int    reserved                   : 30; /* [31..2] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKMONCTRL_T;    /* 时钟监控控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    raw_intr                   : 1; /* [0..0] 中断指示0：无中断1：有中断 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCLKMONINT_T;    /* 时钟监控中断状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    cfg_arm_dbgen              : 4; /* [3..0] ARM debugen配置。（由系统寄存器逻辑保护每次上电复位之后此值只可写一次。） */
        unsigned int    reserved                   : 28; /* [31..4] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCFG_ARM_DBGEN_T;    /* ARM debug en配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    arm_dbg_key0               : 32; /* [31..0] arm_dbg_key的低32位。（由系统寄存器逻辑保护每次上电复位之后此值只可写3次。） */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCARM_DBG_KEY0_T;    /* ARM debug key0配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    arm_dbg_key1               : 32; /* [31..0] arm_dbg_key的高32位。（由系统寄存器逻辑保护每次上电复位之后此值只可写3次。） */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCARM_DBG_KEY1_T;    /* ARM debug key1配置寄存器 */

typedef union
{
    struct
    {
        unsigned int    arm_dbgen_wr               : 1; /* [0..0] ARM debugen wr状态寄存器。0：当前不可写cfg_arm_dbgen寄存器。1：当前可写cfg_arm_dbgen寄存器。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCARM_DBGEN_STAT_T;    /* ARM debug en状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    sys_efuse_pad_sel          : 1; /* [0..0] 0：PAD烧写；1：软件烧写； */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCEFUSECTRL_T;    /* EFUSE PAD烧写控制寄存器 */

typedef union
{
    struct
    {
        unsigned int    gt_clk_ao_cc_secs          : 1; /* [0..0] aocc/secs时钟门控控制：0：IP时钟禁止；1：IP时钟使能。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCEFUSESEL_T;    /* AOCC/SECS时钟门控寄存器 */

typedef union
{
    struct
    {
        unsigned int    security_n                 : 1; /* [0..0] 表征芯片安全等级 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCSECURITYSTAT_T;    /* EFUSE SECURITY状态寄存器 */

typedef union
{
    struct
    {
        unsigned int    chip_id0                   : 32; /* [31..0] CHIP_ID低32bit */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCHIP_ID0_T;    /* EFUSE CHIP_ID0寄存器 */

typedef union
{
    struct
    {
        unsigned int    chip_id1                   : 32; /* [31..0] CHIP_ID高32bit */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCCHIP_ID1_T;    /* EFUSE CHIP_ID1寄存器 */

typedef union
{
    struct
    {
        unsigned int    version_code               : 16; /* [15..0] 0x0100是芯片的版本号。 */
        unsigned int    chip_code                  : 16; /* [31..16] 0x3630是芯片的编号 */
    } bits;
    unsigned int    u32;
}HI_AP_SCTRL_SCSOCID0_T;    /* SOCID寄存器0 */


/********************************************************************************/
/*    AP_SCTRL 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
HI_SET_GET(hi_ap_sctrl_scctrl_modectrl,modectrl,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_modestatus,modestatus,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_reserved_1,reserved_1,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeforcehigh,timeforcehigh,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren0sel,timeren0sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren0ov,timeren0ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren1sel,timeren1sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren1ov,timeren1ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren2sel,timeren2sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren2ov,timeren2ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren3sel,timeren3sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren3ov,timeren3ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren4sel,timeren4sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren4ov,timeren4ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren5sel,timeren5sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren5ov,timeren5ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren6sel,timeren6sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren6ov,timeren6ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren7sel,timeren7sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren7ov,timeren7ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_deepsleepen,deepsleepen,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_reserved_0,reserved_0,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsysstat_reset_source,reset_source,HI_AP_SCTRL_SCSYSSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSYSSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsysstat_reserved,reserved,HI_AP_SCTRL_SCSYSSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSYSSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_itmden,itmden,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_itmdctrl,itmdctrl,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_reserved_1,reserved_1,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_inmdtype,inmdtype,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_reserved_0,reserved_0,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scimstat_itmdstat,itmdstat,HI_AP_SCTRL_SCIMSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIMSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scimstat_reserved,reserved,HI_AP_SCTRL_SCIMSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIMSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxopresel_apb,tcxopresel_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxohardcon_bypass,tcxohardcon_bypass,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxosel_apb,tcxosel_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxosoft_apb,tcxosoft_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_defau_tcxo,defau_tcxo,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxofast_ctrl0,tcxofast_ctrl0,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxofast_ctrl1,tcxofast_ctrl1,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlen1_apb,ctrlen1_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlsel1_apb,ctrlsel1_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlen0_apb,ctrlen0_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlsel0_apb,ctrlsel0_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_timeout_bypass0,timeout_bypass0,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_timeout_bypass1,timeout_bypass1,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxoseq_bypass,tcxoseq_bypass,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxoseq0_time,tcxoseq0_time,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxoseq1_time,tcxoseq1_time,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_reserved,reserved,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtaltimeout0_timeoutcnt0_apb,timeoutcnt0_apb,HI_AP_SCTRL_SCXTALTIMEOUT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALTIMEOUT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtaltimeout1_timeoutcnt1_apb,timeoutcnt1_apb,HI_AP_SCTRL_SCXTALTIMEOUT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALTIMEOUT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_en0,tcxo_en0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_en1,tcxo_en1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_timeout1,tcxo_timeout1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_timeout0,tcxo_timeout0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_sysclk_en1,sysclk_en1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_sysclk_en0,sysclk_en0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_sysclk_sel,sysclk_sel,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_clkgt_ctrl0,clkgt_ctrl0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_clkgt_ctrl1,clkgt_ctrl1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_clkgt_ctrl,clkgt_ctrl,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_abbbuf_en0,abbbuf_en0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_abbbuf_en1,abbbuf_en1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxoseq_finish0,tcxoseq_finish0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxoseq_finish1,tcxoseq_finish1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_reserved,reserved,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_en,ppll0_en,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_bp,ppll0_bp,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_refdiv,ppll0_refdiv,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_fbdiv,ppll0_fbdiv,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_postdiv1,ppll0_postdiv1,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_postdiv2,ppll0_postdiv2,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_reserved,reserved,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_ppll0_fracdiv,ppll0_fracdiv,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_ppll0_int_mod,ppll0_int_mod,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_ppll0_cfg_vld,ppll0_cfg_vld,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_gt_clk_ppll0,gt_clk_ppll0,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_reserved,reserved,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_reset,ppll0_ssc_reset,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_disable,ppll0_ssc_disable,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_downspread,ppll0_ssc_downspread,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_spread,ppll0_ssc_spread,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_divval,ppll0_ssc_divval,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_reserved,reserved,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllstat_pllstat,pllstat,HI_AP_SCTRL_SCPPLLSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllstat_reserved,reserved,HI_AP_SCTRL_SCPPLLSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_reserved,reserved,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_reserved,reserved,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_reserved,reserved,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_ao_cc,gt_clk_ao_cc,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_reserved,reserved,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_reserved,reserved,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_reserved,reserved,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_reserved,reserved,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_swdone_clk_asp_subsys_div,swdone_clk_asp_subsys_div,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_swdone_clk_sci_div,swdone_clk_sci_div,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_swdone_clk_aobus_div,swdone_clk_aobus_div,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_aobusclksw2sys,aobusclksw2sys,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_aobusclksw2pll,aobusclksw2pll,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen2_reserved,reserved,HI_AP_SCTRL_SCPEREN2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis2_reserved,reserved,HI_AP_SCTRL_SCPERDIS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken2_reserved,reserved,HI_AP_SCTRL_SCPERCLKEN2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat2_reserved,reserved,HI_AP_SCTRL_SCPERSTAT2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_cc,ip_rst_ao_cc,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_rtc,ip_rst_rtc,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_rtc1,ip_rst_rtc1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer0,ip_rst_timer0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer1,ip_rst_timer1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer2,ip_rst_timer2,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer3,ip_rst_timer3,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_cfg,rst_asp_cfg,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_dw_axi,rst_asp_dw_axi,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_x2h,rst_asp_x2h,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_h2p,rst_asp_h2p,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio0,ip_rst_ao_gpio0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio1,ip_rst_ao_gpio1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio2,ip_rst_ao_gpio2,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio3,ip_rst_ao_gpio3,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio4,ip_rst_ao_gpio4,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio5,ip_rst_ao_gpio5,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_3,reserved_3,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_ioc,ip_rst_ao_ioc,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_prst_syscnt,ip_prst_syscnt,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_syscnt,ip_rst_syscnt,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_2,reserved_2,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_sci0,ip_rst_sci0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_sci1,ip_rst_sci1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_1,reserved_1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_asp_subsys,ip_rst_asp_subsys,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_bbpdrx,ip_rst_bbpdrx,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_0,reserved_0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_aobus,ip_rst_aobus,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_sc_rst_src_clr,sc_rst_src_clr,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_sc_pmurst_ctrl,sc_pmurst_ctrl,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_cc,ip_rst_ao_cc,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_rtc,ip_rst_rtc,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_rtc1,ip_rst_rtc1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer0,ip_rst_timer0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer1,ip_rst_timer1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer2,ip_rst_timer2,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer3,ip_rst_timer3,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_cfg,rst_asp_cfg,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_dw_axi,rst_asp_dw_axi,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_x2h,rst_asp_x2h,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_h2p,rst_asp_h2p,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio0,ip_rst_ao_gpio0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio1,ip_rst_ao_gpio1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio2,ip_rst_ao_gpio2,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio3,ip_rst_ao_gpio3,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio4,ip_rst_ao_gpio4,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio5,ip_rst_ao_gpio5,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_3,reserved_3,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_ioc,ip_rst_ao_ioc,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_prst_syscnt,ip_prst_syscnt,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_syscnt,ip_rst_syscnt,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_2,reserved_2,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_sci0,ip_rst_sci0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_sci1,ip_rst_sci1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_1,reserved_1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_asp_subsys,ip_rst_asp_subsys,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_bbpdrx,ip_rst_bbpdrx,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_0,reserved_0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_aobus,ip_rst_aobus,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_sc_rst_src_clr,sc_rst_src_clr,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_sc_pmurst_ctrl,sc_pmurst_ctrl,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_cc,ip_rst_ao_cc,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_rtc,ip_rst_rtc,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_rtc1,ip_rst_rtc1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer0,ip_rst_timer0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer1,ip_rst_timer1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer2,ip_rst_timer2,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer3,ip_rst_timer3,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_cfg,rst_asp_cfg,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_dw_axi,rst_asp_dw_axi,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_x2h,rst_asp_x2h,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_h2p,rst_asp_h2p,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio0,ip_rst_ao_gpio0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio1,ip_rst_ao_gpio1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio2,ip_rst_ao_gpio2,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio3,ip_rst_ao_gpio3,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio4,ip_rst_ao_gpio4,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio5,ip_rst_ao_gpio5,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_3,reserved_3,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_ioc,ip_rst_ao_ioc,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_prst_syscnt,ip_prst_syscnt,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_syscnt,ip_rst_syscnt,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_2,reserved_2,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_sci0,ip_rst_sci0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_sci1,ip_rst_sci1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_1,reserved_1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_asp_subsys,ip_rst_asp_subsys,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_bbpdrx,ip_rst_bbpdrx,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_0,reserved_0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_aobus,ip_rst_aobus,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_sc_rst_src_clr,sc_rst_src_clr,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_sc_pmurst_ctrl,sc_pmurst_ctrl,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten1_reserved,reserved,HI_AP_SCTRL_SCPERRSTEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis1_reserved,reserved,HI_AP_SCTRL_SCPERRSTDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat1_reserved,reserved,HI_AP_SCTRL_SCPERRSTSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten2_reserved,reserved,HI_AP_SCTRL_SCPERRSTEN2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis2_reserved,reserved,HI_AP_SCTRL_SCPERRSTDIS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat2_reserved,reserved,HI_AP_SCTRL_SCPERRSTSTAT2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_rtc_bypass,rst_gt_rtc_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_rtc1_bypass,rst_gt_rtc1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer0_bypass,rst_gt_timer0_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer1_bypass,rst_gt_timer1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer2_bypass,rst_gt_timer2_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer3_bypass,rst_gt_timer3_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio0_bypass,rst_gt_gpio0_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio1_bypass,rst_gt_gpio1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio2_bypass,rst_gt_gpio2_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio3_bypass,rst_gt_gpio3_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio4_bypass,rst_gt_gpio4_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio5_bypass,rst_gt_gpio5_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_ioc_bypass,rst_gt_ioc_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_syscnt_bypass,rst_gt_syscnt_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_sci0_bypass,rst_gt_sci0_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_sci1_bypass,rst_gt_sci1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_bbpdrx_bypass,rst_gt_bbpdrx_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_efusec_bypass,rst_gt_efusec_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_reserved,reserved,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisoen_audioisoen,audioisoen,HI_AP_SCTRL_SCISOEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisoen_reserved,reserved,HI_AP_SCTRL_SCISOEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisodis_audioisoen,audioisoen,HI_AP_SCTRL_SCISODIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISODIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisodis_reserved,reserved,HI_AP_SCTRL_SCISODIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISODIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisostat_audioisoen,audioisoen,HI_AP_SCTRL_SCISOSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisostat_reserved,reserved,HI_AP_SCTRL_SCISOSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwren_audiopwren,audiopwren,HI_AP_SCTRL_SCPWREN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWREN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwren_reserved,reserved,HI_AP_SCTRL_SCPWREN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWREN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrdis_audiopwren,audiopwren,HI_AP_SCTRL_SCPWRDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrdis_reserved,reserved,HI_AP_SCTRL_SCPWRDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrstat_audiopwrstat,audiopwrstat,HI_AP_SCTRL_SCPWRSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrstat_reserved,reserved,HI_AP_SCTRL_SCPWRSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrack_audiopwrack,audiopwrack,HI_AP_SCTRL_SCPWRACK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRACK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrack_reserved,reserved,HI_AP_SCTRL_SCPWRACK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRACK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwrdowntime_peri_pwr_down_time,peri_pwr_down_time,HI_AP_SCTRL_SCPERPWRDOWNTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRDOWNTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwrdowntime_reserved,reserved,HI_AP_SCTRL_SCPERPWRDOWNTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRDOWNTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwruptime_peri_pwr_up_time,peri_pwr_up_time,HI_AP_SCTRL_SCPERPWRUPTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRUPTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwruptime_reserved,reserved,HI_AP_SCTRL_SCPERPWRUPTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRUPTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_sc_div_asp_subsys,sc_div_asp_subsys,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_sc_div_hifidsp,sc_div_hifidsp,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_sc_div_sci,sc_div_sci,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_reserved,reserved,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_extclk_en,extclk_en,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_sc_div_aobus,sc_div_aobus,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_div_clkout0_tcxo,div_clkout0_tcxo,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_div_clkout1_tcxo,div_clkout1_tcxo,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_sel_clkout0,sel_clkout0,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_sel_clkout1,sel_clkout1,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_hifidsp_clk_div,gt_hifidsp_clk_div,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_clk_sci,gt_clk_sci,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_asp_hclk_div,gt_asp_hclk_div,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_reserved_1,reserved_1,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_sc_div_asp_hclk,sc_div_asp_hclk,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_reserved_0,reserved_0,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv3_reserved,reserved,HI_AP_SCTRL_SCCLKDIV3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv3_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv4_reserved,reserved,HI_AP_SCTRL_SCCLKDIV4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv4_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv5_reserved,reserved,HI_AP_SCTRL_SCCLKDIV5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv5_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl0_efusec_mem_ctrl,efusec_mem_ctrl,HI_AP_SCTRL_SCPERCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl0_efuse_remap,efuse_remap,HI_AP_SCTRL_SCPERCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl0_reserved,reserved,HI_AP_SCTRL_SCPERCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl1_reserved,reserved,HI_AP_SCTRL_SCPERCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_repair_disable,repair_disable,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_reserved_1,reserved_1,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_jtaq_to_sdcard,jtaq_to_sdcard,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_reserved_0,reserved_0,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_reserved_1,reserved_1,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_reset_memrep_msk,reset_memrep_msk,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_repair_iddq,repair_iddq,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_repair_frm_sram,repair_frm_sram,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_repair_frm_efu,repair_frm_efu,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_dram_pwr_ctl,dram_pwr_ctl,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_efusec_timeout_bypass,efusec_timeout_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_bbdrx_timeout_bypass,bbdrx_timeout_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_cfgbus_bypass,sleep_mode_cfgbus_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_lpmcu_bypass,sleep_mode_lpmcu_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_iomcu_bypass,sleep_mode_iomcu_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_aobus_bypass,sleep_mode_aobus_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_bbp_clk_en,bbp_clk_en,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_reserved_0,reserved_0,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl4_ddr_ret_en,ddr_ret_en,HI_AP_SCTRL_SCPERCTRL4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl4_reserved,reserved,HI_AP_SCTRL_SCPERCTRL4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_usim0_io_sel18,usim0_io_sel18,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_usim1_io_sel18,usim1_io_sel18,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_sdcard_io_sel18,sdcard_io_sel18,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_tp_sel,tp_sel,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_tcxo_mode,tcxo_mode,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_reserved,reserved,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_peri_io_ret,peri_io_ret,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_reserved_1,reserved_1,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_peri_bootio_ret,peri_bootio_ret,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_peri_bootio_ret_mode,peri_bootio_ret_mode,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_reserved_0,reserved_0,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_wr,asp_dwaxi_dlock_wr,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_id,asp_dwaxi_dlock_id,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_slv,asp_dwaxi_dlock_slv,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_mst,asp_dwaxi_dlock_mst,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_sys_pw_stat,sys_pw_stat,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tcxoseq_stat0,tcxoseq_stat0,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tcxoseq_stat1,tcxoseq_stat1,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tp_a3_grp,tp_a3_grp,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tp_a4_grp0,tp_a4_grp0,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tp_a4_grp1,tp_a4_grp1,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus1_err_flag,err_flag,HI_AP_SCTRL_SCPERSTATUS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus2_peri_stat2,peri_stat2,HI_AP_SCTRL_SCPERSTATUS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus2_reserved,reserved,HI_AP_SCTRL_SCPERSTATUS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus3_efusec_timeout_dbg_info,efusec_timeout_dbg_info,HI_AP_SCTRL_SCPERSTATUS3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus4_bbdrx_timeout_dbg_info,bbdrx_timeout_dbg_info,HI_AP_SCTRL_SCPERSTATUS4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_deepsleeped,deepsleeped,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_reserved_1,reserved_1,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_sleeped,sleeped,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_reserved_0,reserved_0,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmrbbusystat_mrb_efuse_busy,mrb_efuse_busy,HI_AP_SCTRL_SCMRBBUSYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMRBBUSYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmrbbusystat_reserved,reserved,HI_AP_SCTRL_SCMRBBUSYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMRBBUSYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scswaddr_swaddr,swaddr,HI_AP_SCTRL_SCSWADDR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSWADDR_OFFSET)
HI_SET_GET(hi_ap_sctrl_scddraddr_ddrtrainaddr,ddrtrainaddr,HI_AP_SCTRL_SCDDRADDR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDDRADDR_OFFSET)
HI_SET_GET(hi_ap_sctrl_scddrdata_ddrtraindata,ddrtraindata,HI_AP_SCTRL_SCDDRDATA_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDDRDATA_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata0_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata1_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata2_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata3_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata4_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata5_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata6_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata7_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA7_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA7_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata8_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA8_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA8_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata9_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA9_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA9_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata10_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA10_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA10_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata11_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA11_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA11_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata12_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA12_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA12_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata13_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA13_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA13_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata14_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA14_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA14_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata15_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA15_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA15_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_int_wakeup_sys,int_wakeup_sys,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_drx0_int,drx0_int,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_drx1_int,drx1_int,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_notdrx_int,notdrx_int,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_reserved,reserved,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_22_int,gpio_22_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_23_int,gpio_23_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_24_int,gpio_24_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_25_int,gpio_25_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_26_int,gpio_26_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_rtc_int,rtc_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_rtc1_int,rtc1_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer0_int,timer0_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer1_int,timer1_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer2_int,timer2_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer3_int,timer3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer4_int,timer4_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer5_int,timer5_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer6_int,timer6_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer7_int,timer7_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_irq_int0,gic_irq_int0,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_irq_int1,gic_irq_int1,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_fiq_int2,gic_fiq_int2,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_fiq_int3,gic_fiq_int3,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_lpm3_int,lpm3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_iom3_int,iom3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_asp_ipc_arm_int,asp_ipc_arm_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx0_int,drx0_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx1_int,drx1_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx2_int,drx2_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx3_int,drx3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx4_int,drx4_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_27_int,gpio_27_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_asp_int,gpio_asp_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_asp_int_sc,gpio_asp_int_sc,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_intr_asp_watchdog,intr_asp_watchdog,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_lpm3_wfi_int,lpm3_wfi_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_22_int,gpio_22_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_23_int,gpio_23_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_24_int,gpio_24_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_25_int,gpio_25_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_26_int,gpio_26_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_rtc_int,rtc_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_rtc1_int,rtc1_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer0_int,timer0_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer1_int,timer1_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer2_int,timer2_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer3_int,timer3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer4_int,timer4_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer5_int,timer5_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer6_int,timer6_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer7_int,timer7_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int0,gic_int0,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int1,gic_int1,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int2,gic_int2,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int3,gic_int3,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_lpm3_int,lpm3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_iom3_int,iom3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_asp_ipc_arm_int,asp_ipc_arm_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx0_int,drx0_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx1_int,drx1_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx2_int,drx2_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx3_int,drx3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx4_int,drx4_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_27_int,gpio_27_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_intr_asp_watchdog,intr_asp_watchdog,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_asp_int,gpio_asp_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_reserved,reserved,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx0_int,drx0_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx1_int,drx1_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx2_int,drx2_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx3_int,drx3_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx4_int,drx4_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_gpio_asp_int,gpio_asp_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_reserved,reserved,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3wfi_int_clr_lpm3_wfi_int_clr,lpm3_wfi_int_clr,HI_AP_SCTRL_SCLPM3WFI_INT_CLR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3WFI_INT_CLR_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3wfi_int_clr_reserved,reserved,HI_AP_SCTRL_SCLPM3WFI_INT_CLR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3WFI_INT_CLR_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmalibypcfg_mali_dbgack_byp,mali_dbgack_byp,HI_AP_SCTRL_SCMALIBYPCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMALIBYPCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmalibypcfg_reserved,reserved,HI_AP_SCTRL_SCMALIBYPCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMALIBYPCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_dapclkoff_sys_n,dapclkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_reserved_1,reserved_1,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_rom_clk_clkoff_sys_n,rom_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_ram_clk_clkoff_sys_n,ram_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_reserved_0,reserved_0,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_ddrc_clk_clkoff_sys_n,ddrc_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_tsen_clk_clkoff_sys_n,tsen_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_pmc_clk_clkoff_sys_n,pmc_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_uart_clk_clkoff_sys_n,uart_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_i2c_clk_clkoff_sys_n,i2c_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_ssi_clk_clkoff_sys_n,ssi_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_pcrg_clk_clkoff_sys_n,pcrg_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_nandc_clk_clkoff_sys_n,nandc_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_wdog_clk_clkoff_sys_n,wdog_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_tim_clk_clkoff_sys_n,tim_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_cssys_clk_clkoff_sys_n,cssys_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_rst_software_req,rst_software_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_coresight_soft_rst_req,coresight_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_reserved_2,reserved_2,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_rom_soft_rst_req,rom_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_ram_soft_rst_req,ram_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_reserved_1,reserved_1,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_ddrc_soft_rst_req,ddrc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_tsen_soft_rst_req,tsen_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_pmc_soft_rst_req,pmc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_uart_soft_rst_req,uart_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_i2c_soft_rst_req,i2c_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_ssi_soft_rst_req,ssi_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_pcrg_soft_rst_req,pcrg_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_nandc_soft_rst_req,nandc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_wdog_soft_rst_req,wdog_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_tim_soft_rst_req,tim_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_cssys_soft_rst_req,cssys_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_reserved_0,reserved_0,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_rst_software_req,rst_software_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_coresight_soft_rst_req,coresight_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_bus_soft_rst_req,bus_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_rom_soft_rst_req,rom_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_ram_soft_rst_req,ram_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_aon_soft_rst_req,aon_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_ddrc_soft_rst_req,ddrc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_tsen_soft_rst_req,tsen_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_pmc_soft_rst_req,pmc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_uart_soft_rst_req,uart_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_i2c_soft_rst_req,i2c_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_ssi_soft_rst_req,ssi_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_pcrg_soft_rst_req,pcrg_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_nandc_soft_rst_req,nandc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_wdog_soft_rst_req,wdog_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_tim_soft_rst_req,tim_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_cssys_soft_rst_req,cssys_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_reserved,reserved,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_rst_software_req,rst_software_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_coresight_soft_rst_req,coresight_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_bus_soft_rst_req,bus_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_rom_soft_rst_req,rom_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_ram_soft_rst_req,ram_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_aon_soft_rst_req,aon_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_ddrc_soft_rst_req,ddrc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_tsen_soft_rst_req,tsen_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_pmc_soft_rst_req,pmc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_uart_soft_rst_req,uart_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_i2c_soft_rst_req,i2c_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_ssi_soft_rst_req,ssi_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_pcrg_soft_rst_req,pcrg_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_nandc_soft_rst_req,nandc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_wdog_soft_rst_req,wdog_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_tim_soft_rst_req,tim_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_cssys_soft_rst_req,cssys_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_reserved,reserved,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_boot_remap_en,boot_remap_en,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_mpudisable,mpudisable,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_nmi_in,nmi_in,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_bus_div_clk_sel,bus_div_clk_sel,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_sysresetreq_en,sysresetreq_en,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_mem_ctrl_ema_lpram,mem_ctrl_ema_lpram,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_lpm3idle_bypass,lpm3idle_bypass,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_reserved_1,reserved_1,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_reserved_0,reserved_0,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_sysresetreq_sign_out_stat,sysresetreq_sign_out_stat,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_sleeping,sleeping,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_lockup,lockup,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_halted,halted,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_reserved,reserved,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpramctrl_sel,lpramctrl_sel,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram0_mod,lpram0_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram1_mod,lpram1_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram2_mod,lpram2_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram3_mod,lpram3_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram0ctrl_soft,lpram0ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram1ctrl_soft,lpram1ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram2ctrl_soft,lpram2ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram3ctrl_soft,lpram3ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_memrep_ram_mod,memrep_ram_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_memrep_ramctrl_soft,memrep_ramctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_reserved,reserved,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_g2_gdrx_depsleep_flag,g2_gdrx_depsleep_flag,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_g1_gdrx_depsleep_flag,g1_gdrx_depsleep_flag,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_wdrx_deepsleep_flag,wdrx_deepsleep_flag,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_reserved,reserved,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat1_ldrx2dbg_abs_timer,ldrx2dbg_abs_timer,HI_AP_SCTRL_SCBBPDRXSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat2_ldrx2dbg_abs_timer,ldrx2dbg_abs_timer,HI_AP_SCTRL_SCBBPDRXSTAT2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT2_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_reserved,reserved,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_reserved,reserved,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_reserved,reserved,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_reserved,reserved,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_reserved,reserved,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_a7_event,a7_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_a15_event,a15_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_iom3_event,iom3_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_lpm3_event,lpm3_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_mcpu_event,mcpu_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_reserved,reserved,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scjtag_sel_processor_jtag_sel,processor_jtag_sel,HI_AP_SCTRL_SCJTAG_SEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCJTAG_SEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scjtag_sel_dsp_jtag_sel,dsp_jtag_sel,HI_AP_SCTRL_SCJTAG_SEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCJTAG_SEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scjtag_sel_reserved,reserved,HI_AP_SCTRL_SCJTAG_SEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCJTAG_SEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key0_modem_key0,modem_key0,HI_AP_SCTRL_SCMODEM_KEY0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key1_modem_key1,modem_key1,HI_AP_SCTRL_SCMODEM_KEY1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key2_modem_key2,modem_key2,HI_AP_SCTRL_SCMODEM_KEY2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key3_modem_key3,modem_key3,HI_AP_SCTRL_SCMODEM_KEY3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY3_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_djtag_cfg_djtag,cfg_djtag,HI_AP_SCTRL_SCCFG_DJTAG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_DJTAG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_djtag_reserved,reserved,HI_AP_SCTRL_SCCFG_DJTAG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_DJTAG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable0,a7cp15disable0,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable1,a7cp15disable1,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable2,a7cp15disable2,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable3,a7cp15disable3,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable0,a15cp15disable0,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable1,a15cp15disable1,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable2,a15cp15disable2,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable3,a15cp15disable3,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a9cp15disable,a9cp15disable,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_gicdisable,gicdisable,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_reserved,reserved,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntstat_cnt_stat,cnt_stat,HI_AP_SCTRL_SCCLKCNTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntstat_reserved,reserved,HI_AP_SCTRL_SCCLKCNTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_cnt_cfg,cnt_cfg,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_timer_secu_en,timer_secu_en,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_reserved,reserved,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_clk_cnt_en,clk_cnt_en,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_clk_monitor_en,clk_monitor_en,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonctrl_intr_clr,intr_clr,HI_AP_SCTRL_SCCLKMONCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonctrl_intr_mask,intr_mask,HI_AP_SCTRL_SCCLKMONCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonctrl_reserved,reserved,HI_AP_SCTRL_SCCLKMONCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonint_raw_intr,raw_intr,HI_AP_SCTRL_SCCLKMONINT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONINT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonint_reserved,reserved,HI_AP_SCTRL_SCCLKMONINT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONINT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_arm_dbgen_cfg_arm_dbgen,cfg_arm_dbgen,HI_AP_SCTRL_SCCFG_ARM_DBGEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_ARM_DBGEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_arm_dbgen_reserved,reserved,HI_AP_SCTRL_SCCFG_ARM_DBGEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_ARM_DBGEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbg_key0_arm_dbg_key0,arm_dbg_key0,HI_AP_SCTRL_SCARM_DBG_KEY0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBG_KEY0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbg_key1_arm_dbg_key1,arm_dbg_key1,HI_AP_SCTRL_SCARM_DBG_KEY1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBG_KEY1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbgen_stat_arm_dbgen_wr,arm_dbgen_wr,HI_AP_SCTRL_SCARM_DBGEN_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBGEN_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbgen_stat_reserved,reserved,HI_AP_SCTRL_SCARM_DBGEN_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBGEN_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusectrl_sys_efuse_pad_sel,sys_efuse_pad_sel,HI_AP_SCTRL_SCEFUSECTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSECTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusectrl_reserved,reserved,HI_AP_SCTRL_SCEFUSECTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSECTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusesel_gt_clk_ao_cc_secs,gt_clk_ao_cc_secs,HI_AP_SCTRL_SCEFUSESEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSESEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusesel_reserved,reserved,HI_AP_SCTRL_SCEFUSESEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSESEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsecuritystat_security_n,security_n,HI_AP_SCTRL_SCSECURITYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSECURITYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsecuritystat_reserved,reserved,HI_AP_SCTRL_SCSECURITYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSECURITYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scchip_id0_chip_id0,chip_id0,HI_AP_SCTRL_SCCHIP_ID0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCHIP_ID0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scchip_id1_chip_id1,chip_id1,HI_AP_SCTRL_SCCHIP_ID1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCHIP_ID1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsocid0_version_code,version_code,HI_AP_SCTRL_SCSOCID0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSOCID0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsocid0_chip_code,chip_code,HI_AP_SCTRL_SCSOCID0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSOCID0_OFFSET)

#endif // __HI_AP_SCTRL_H__

