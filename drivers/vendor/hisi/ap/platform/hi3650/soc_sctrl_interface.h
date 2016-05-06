/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_sctrl_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:47:49
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_SCTRL.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_SCTRL_INTERFACE_H__
#define __SOC_SCTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* 寄存器说明：系统控制器寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCTRL_UNION */
#define SOC_SCTRL_SCCTRL_ADDR(base)                   ((base) + (0x000))

/* 寄存器说明：系统状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCSYSSTAT_UNION */
#define SOC_SCTRL_SCSYSSTAT_ADDR(base)                ((base) + (0x004))

/* 寄存器说明：晶振控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCXTALCTRL_UNION */
#define SOC_SCTRL_SCXTALCTRL_ADDR(base)               ((base) + (0x010))

/* 寄存器说明：晶振稳定时间配置寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCXTALTIMEOUT0_UNION */
#define SOC_SCTRL_SCXTALTIMEOUT0_ADDR(base)           ((base) + (0x014))

/* 寄存器说明：晶振稳定时间配置寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCXTALTIMEOUT1_UNION */
#define SOC_SCTRL_SCXTALTIMEOUT1_ADDR(base)           ((base) + (0x018))

/* 寄存器说明：晶振控制状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCXTALSTAT_UNION */
#define SOC_SCTRL_SCXTALSTAT_ADDR(base)               ((base) + (0x01C))

/* 寄存器说明：PPLL0控制寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPPLLCTRL0_UNION */
#define SOC_SCTRL_SCPPLLCTRL0_ADDR(base)              ((base) + (0x020))

/* 寄存器说明：PPLL0控制寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPPLLCTRL1_UNION */
#define SOC_SCTRL_SCPPLLCTRL1_ADDR(base)              ((base) + (0x024))

/* 寄存器说明：PPLL0 SSC控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCPPLLSSCCTRL_UNION */
#define SOC_SCTRL_SCPPLLSSCCTRL_ADDR(base)            ((base) + (0x028))

/* 寄存器说明：PPLL0状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCPPLLSTAT_UNION */
#define SOC_SCTRL_SCPPLLSTAT_ADDR(base)               ((base) + (0x02C))

/* 寄存器说明：外设时钟使能寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPEREN0_UNION */
#define SOC_SCTRL_SCPEREN0_ADDR(base)                 ((base) + (0x030))

/* 寄存器说明：外设时钟禁止寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPERDIS0_UNION */
#define SOC_SCTRL_SCPERDIS0_ADDR(base)                ((base) + (0x034))

/* 寄存器说明：外设时钟使能状态寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPERCLKEN0_UNION */
#define SOC_SCTRL_SCPERCLKEN0_ADDR(base)              ((base) + (0x038))

/* 寄存器说明：外设时钟最终状态寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTAT0_UNION */
#define SOC_SCTRL_SCPERSTAT0_ADDR(base)               ((base) + (0x03C))

/* 寄存器说明：外设时钟使能寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPEREN1_UNION */
#define SOC_SCTRL_SCPEREN1_ADDR(base)                 ((base) + (0x040))

/* 寄存器说明：外设时钟禁止寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPERDIS1_UNION */
#define SOC_SCTRL_SCPERDIS1_ADDR(base)                ((base) + (0x044))

/* 寄存器说明：外设时钟使能状态寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPERCLKEN1_UNION */
#define SOC_SCTRL_SCPERCLKEN1_ADDR(base)              ((base) + (0x048))

/* 寄存器说明：外设时钟最终状态寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTAT1_UNION */
#define SOC_SCTRL_SCPERSTAT1_ADDR(base)               ((base) + (0x04C))

/* 寄存器说明：外设时钟使能寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCPEREN2_UNION */
#define SOC_SCTRL_SCPEREN2_ADDR(base)                 ((base) + (0x050))

/* 寄存器说明：外设时钟禁止寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCPERDIS2_UNION */
#define SOC_SCTRL_SCPERDIS2_ADDR(base)                ((base) + (0x054))

/* 寄存器说明：外设时钟使能状态寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCPERCLKEN2_UNION */
#define SOC_SCTRL_SCPERCLKEN2_ADDR(base)              ((base) + (0x058))

/* 寄存器说明：外设时钟最终状态寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTAT2_UNION */
#define SOC_SCTRL_SCPERSTAT2_ADDR(base)               ((base) + (0x05C))

/* 寄存器说明：系统TIMER时钟选择和控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCTIMERCTRL_UNION */
#define SOC_SCTRL_SCTIMERCTRL_ADDR(base)              ((base) + (0x060))

/* 寄存器说明：FPLL0控制寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCFPLLCTRL0_UNION */
#define SOC_SCTRL_SCFPLLCTRL0_ADDR(base)              ((base) + (0x064))

/* 寄存器说明：FPLL0控制寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCFPLLCTRL1_UNION */
#define SOC_SCTRL_SCFPLLCTRL1_ADDR(base)              ((base) + (0x068))

/* 寄存器说明：FPLL0控制寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCFPLLCTRL2_UNION */
#define SOC_SCTRL_SCFPLLCTRL2_ADDR(base)              ((base) + (0x06C))

/* 寄存器说明：FPLL0控制寄存器3。
   位域定义UNION结构:  SOC_SCTRL_SCFPLLCTRL3_UNION */
#define SOC_SCTRL_SCFPLLCTRL3_ADDR(base)              ((base) + (0x070))

/* 寄存器说明：FPLL0状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCFPLLSTAT_UNION */
#define SOC_SCTRL_SCFPLLSTAT_ADDR(base)               ((base) + (0x074))

/* 寄存器说明：外设时钟最终状态寄存器3。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTAT3_UNION */
#define SOC_SCTRL_SCPERSTAT3_ADDR(base)               ((base) + (0x07C))

/* 寄存器说明：外设软复位使能寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTEN0_UNION */
#define SOC_SCTRL_SCPERRSTEN0_ADDR(base)              ((base) + (0x080))

/* 寄存器说明：外设软复位撤离寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTDIS0_UNION */
#define SOC_SCTRL_SCPERRSTDIS0_ADDR(base)             ((base) + (0x084))

/* 寄存器说明：外设软复位状态寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTSTAT0_UNION */
#define SOC_SCTRL_SCPERRSTSTAT0_ADDR(base)            ((base) + (0x088))

/* 寄存器说明：外设软复位使能寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTEN1_UNION */
#define SOC_SCTRL_SCPERRSTEN1_ADDR(base)              ((base) + (0x08C))

/* 寄存器说明：外设软复位撤离寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTDIS1_UNION */
#define SOC_SCTRL_SCPERRSTDIS1_ADDR(base)             ((base) + (0x090))

/* 寄存器说明：外设软复位状态寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTSTAT1_UNION */
#define SOC_SCTRL_SCPERRSTSTAT1_ADDR(base)            ((base) + (0x094))

/* 寄存器说明：外设软复位使能寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTEN2_UNION */
#define SOC_SCTRL_SCPERRSTEN2_ADDR(base)              ((base) + (0x098))

/* 寄存器说明：外设软复位撤离寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTDIS2_UNION */
#define SOC_SCTRL_SCPERRSTDIS2_ADDR(base)             ((base) + (0x09C))

/* 寄存器说明：外设软复位状态寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTSTAT2_UNION */
#define SOC_SCTRL_SCPERRSTSTAT2_ADDR(base)            ((base) + (0x0A0))

/* 寄存器说明：IP防总线挂死控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIPCLKRSTBUS_UNION */
#define SOC_SCTRL_SCIPCLKRSTBUS_ADDR(base)            ((base) + (0x0A4))

/* 寄存器说明：掉电子系统ISO使能寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCISOEN_UNION */
#define SOC_SCTRL_SCISOEN_ADDR(base)                  ((base) + (0x0C0))

/* 寄存器说明：掉电子系统ISO使能撤销寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCISODIS_UNION */
#define SOC_SCTRL_SCISODIS_ADDR(base)                 ((base) + (0x0C4))

/* 寄存器说明：掉电子系统ISO使能状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCISOSTAT_UNION */
#define SOC_SCTRL_SCISOSTAT_ADDR(base)                ((base) + (0x0C8))

/* 寄存器说明：掉电子系统电源使能寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCPWREN_UNION */
#define SOC_SCTRL_SCPWREN_ADDR(base)                  ((base) + (0x0D0))

/* 寄存器说明：掉电子系统电源使能撤销寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCPWRDIS_UNION */
#define SOC_SCTRL_SCPWRDIS_ADDR(base)                 ((base) + (0x0D4))

/* 寄存器说明：掉电子系统电源使能状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCPWRSTAT_UNION */
#define SOC_SCTRL_SCPWRSTAT_ADDR(base)                ((base) + (0x0D8))

/* 寄存器说明：掉电子系统最终电源状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCPWRACK_UNION */
#define SOC_SCTRL_SCPWRACK_ADDR(base)                 ((base) + (0x0DC))

/* 寄存器说明：外设区掉电时间配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCPERPWRDOWNTIME_UNION */
#define SOC_SCTRL_SCPERPWRDOWNTIME_ADDR(base)         ((base) + (0x0E0))

/* 寄存器说明：外设区上电时间配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCPERPWRUPTIME_UNION */
#define SOC_SCTRL_SCPERPWRUPTIME_ADDR(base)           ((base) + (0x0E4))

/* 寄存器说明：时钟分频比控制寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCCLKDIV0_UNION */
#define SOC_SCTRL_SCCLKDIV0_ADDR(base)                ((base) + (0x100))

/* 寄存器说明：时钟分频比控制寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCCLKDIV1_UNION */
#define SOC_SCTRL_SCCLKDIV1_ADDR(base)                ((base) + (0x104))

/* 寄存器说明：时钟分频比控制寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCCLKDIV2_UNION */
#define SOC_SCTRL_SCCLKDIV2_ADDR(base)                ((base) + (0x108))

/* 寄存器说明：时钟分频比控制寄存器3。
   位域定义UNION结构:  SOC_SCTRL_SCCLKDIV3_UNION */
#define SOC_SCTRL_SCCLKDIV3_ADDR(base)                ((base) + (0x10C))

/* 寄存器说明：时钟分频比控制寄存器4。
   位域定义UNION结构:  SOC_SCTRL_SCCLKDIV4_UNION */
#define SOC_SCTRL_SCCLKDIV4_ADDR(base)                ((base) + (0x110))

/* 寄存器说明：时钟分频比控制寄存器5。
   位域定义UNION结构:  SOC_SCTRL_SCCLKDIV5_UNION */
#define SOC_SCTRL_SCCLKDIV5_ADDR(base)                ((base) + (0x114))

/* 寄存器说明：外设控制寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPERCTRL0_UNION */
#define SOC_SCTRL_SCPERCTRL0_ADDR(base)               ((base) + (0x200))

/* 寄存器说明：外设控制寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPERCTRL1_UNION */
#define SOC_SCTRL_SCPERCTRL1_ADDR(base)               ((base) + (0x204))

/* 寄存器说明：外设控制寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCPERCTRL2_UNION */
#define SOC_SCTRL_SCPERCTRL2_ADDR(base)               ((base) + (0x208))

/* 寄存器说明：外设控制寄存器3。
   位域定义UNION结构:  SOC_SCTRL_SCPERCTRL3_UNION */
#define SOC_SCTRL_SCPERCTRL3_ADDR(base)               ((base) + (0x20C))

/* 寄存器说明：外设控制寄存器4。
   位域定义UNION结构:  SOC_SCTRL_SCPERCTRL4_UNION */
#define SOC_SCTRL_SCPERCTRL4_ADDR(base)               ((base) + (0x210))

/* 寄存器说明：外设控制寄存器5。
   位域定义UNION结构:  SOC_SCTRL_SCPERCTRL5_UNION */
#define SOC_SCTRL_SCPERCTRL5_ADDR(base)               ((base) + (0x214))

/* 寄存器说明：外设控制寄存器6。
   位域定义UNION结构:  SOC_SCTRL_SCPERCTRL6_UNION */
#define SOC_SCTRL_SCPERCTRL6_ADDR(base)               ((base) + (0x218))

/* 寄存器说明：外设状态寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS0_UNION */
#define SOC_SCTRL_SCPERSTATUS0_ADDR(base)             ((base) + (0x21C))

/* 寄存器说明：外设状态寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS1_UNION */
#define SOC_SCTRL_SCPERSTATUS1_ADDR(base)             ((base) + (0x220))

/* 寄存器说明：外设状态寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS2_UNION */
#define SOC_SCTRL_SCPERSTATUS2_ADDR(base)             ((base) + (0x224))

/* 寄存器说明：外设状态寄存器3。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS3_UNION */
#define SOC_SCTRL_SCPERSTATUS3_ADDR(base)             ((base) + (0x228))

/* 寄存器说明：外设状态寄存器4。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS4_UNION */
#define SOC_SCTRL_SCPERSTATUS4_ADDR(base)             ((base) + (0x22C))

/* 寄存器说明：外设状态寄存器5。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS5_UNION */
#define SOC_SCTRL_SCPERSTATUS5_ADDR(base)             ((base) + (0x230))

/* 寄存器说明：外设状态寄存器6。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS6_UNION */
#define SOC_SCTRL_SCPERSTATUS6_ADDR(base)             ((base) + (0x234))

/* 寄存器说明：外设状态寄存器7。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS7_UNION */
#define SOC_SCTRL_SCPERSTATUS7_ADDR(base)             ((base) + (0x238))

/* 寄存器说明：外设状态寄存器8。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS8_UNION */
#define SOC_SCTRL_SCPERSTATUS8_ADDR(base)             ((base) + (0x23C))

/* 寄存器说明：外设状态寄存器9。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS9_UNION */
#define SOC_SCTRL_SCPERSTATUS9_ADDR(base)             ((base) + (0x240))

/* 寄存器说明：外设状态寄存器10。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS10_UNION */
#define SOC_SCTRL_SCPERSTATUS10_ADDR(base)            ((base) + (0x244))

/* 寄存器说明：外设状态寄存器11。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS11_UNION */
#define SOC_SCTRL_SCPERSTATUS11_ADDR(base)            ((base) + (0x248))

/* 寄存器说明：外设状态寄存器12。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS12_UNION */
#define SOC_SCTRL_SCPERSTATUS12_ADDR(base)            ((base) + (0x24C))

/* 寄存器说明：外设状态寄存器13。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS13_UNION */
#define SOC_SCTRL_SCPERSTATUS13_ADDR(base)            ((base) + (0x250))

/* 寄存器说明：外设状态寄存器14。
   位域定义UNION结构:  SOC_SCTRL_SCPERSTATUS14_UNION */
#define SOC_SCTRL_SCPERSTATUS14_ADDR(base)            ((base) + (0x254))

/* 寄存器说明：外设控制寄存器7。
   位域定义UNION结构:  SOC_SCTRL_SCPERCTRL7_UNION */
#define SOC_SCTRL_SCPERCTRL7_ADDR(base)               ((base) + (0x270))

/* 寄存器说明：内部状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCINNERSTAT_UNION */
#define SOC_SCTRL_SCINNERSTAT_ADDR(base)              ((base) + (0x280))

/* 寄存器说明：用于指示系统曾经进入过深度睡眠的状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCDEEPSLEEPED_UNION */
#define SOC_SCTRL_SCDEEPSLEEPED_ADDR(base)            ((base) + (0x300))

/* 寄存器说明：MRB EFUSE BUSY状态指示寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCMRBBUSYSTAT_UNION */
#define SOC_SCTRL_SCMRBBUSYSTAT_ADDR(base)            ((base) + (0x304))

/* 寄存器说明：用于保存软件入口地址的寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCSWADDR_UNION */
#define SOC_SCTRL_SCSWADDR_ADDR(base)                 ((base) + (0x308))

/* 寄存器说明：用于保留DDR训练数据的地址的寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCDDRADDR_UNION */
#define SOC_SCTRL_SCDDRADDR_ADDR(base)                ((base) + (0x30C))

/* 寄存器说明：用于保存DDR训练数据的寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCDDRDATA_UNION */
#define SOC_SCTRL_SCDDRDATA_ADDR(base)                ((base) + (0x310))

/* 寄存器说明：用于软件使用的存储数据寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA0_UNION */
#define SOC_SCTRL_SCBAKDATA0_ADDR(base)               ((base) + (0x314))

/* 寄存器说明：用于软件使用的存储数据寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA1_UNION */
#define SOC_SCTRL_SCBAKDATA1_ADDR(base)               ((base) + (0x318))

/* 寄存器说明：用于软件使用的存储数据寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA2_UNION */
#define SOC_SCTRL_SCBAKDATA2_ADDR(base)               ((base) + (0x31C))

/* 寄存器说明：用于软件使用的存储数据寄存器3。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA3_UNION */
#define SOC_SCTRL_SCBAKDATA3_ADDR(base)               ((base) + (0x320))

/* 寄存器说明：用于软件使用的存储数据寄存器4。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA4_UNION */
#define SOC_SCTRL_SCBAKDATA4_ADDR(base)               ((base) + (0x324))

/* 寄存器说明：用于软件使用的存储数据寄存器5。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA5_UNION */
#define SOC_SCTRL_SCBAKDATA5_ADDR(base)               ((base) + (0x328))

/* 寄存器说明：用于软件使用的存储数据寄存器6。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA6_UNION */
#define SOC_SCTRL_SCBAKDATA6_ADDR(base)               ((base) + (0x32C))

/* 寄存器说明：用于软件使用的存储数据寄存器7。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA7_UNION */
#define SOC_SCTRL_SCBAKDATA7_ADDR(base)               ((base) + (0x330))

/* 寄存器说明：用于软件使用的存储数据寄存器8。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA8_UNION */
#define SOC_SCTRL_SCBAKDATA8_ADDR(base)               ((base) + (0x334))

/* 寄存器说明：用于软件使用的存储数据寄存器9。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA9_UNION */
#define SOC_SCTRL_SCBAKDATA9_ADDR(base)               ((base) + (0x338))

/* 寄存器说明：用于软件使用的存储数据寄存器10。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA10_UNION */
#define SOC_SCTRL_SCBAKDATA10_ADDR(base)              ((base) + (0x33C))

/* 寄存器说明：用于软件使用的存储数据寄存器11。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA11_UNION */
#define SOC_SCTRL_SCBAKDATA11_ADDR(base)              ((base) + (0x340))

/* 寄存器说明：用于软件使用的存储数据寄存器12。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA12_UNION */
#define SOC_SCTRL_SCBAKDATA12_ADDR(base)              ((base) + (0x344))

/* 寄存器说明：用于软件使用的存储数据寄存器13。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA13_UNION */
#define SOC_SCTRL_SCBAKDATA13_ADDR(base)              ((base) + (0x348))

/* 寄存器说明：用于软件使用的存储数据寄存器14。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA14_UNION */
#define SOC_SCTRL_SCBAKDATA14_ADDR(base)              ((base) + (0x34C))

/* 寄存器说明：用于软件使用的存储数据寄存器15。
   位域定义UNION结构:  SOC_SCTRL_SCBAKDATA15_UNION */
#define SOC_SCTRL_SCBAKDATA15_ADDR(base)              ((base) + (0x350))

/* 寄存器说明：聚合后的中断状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCINT_GATHER_STAT_UNION */
#define SOC_SCTRL_SCINT_GATHER_STAT_ADDR(base)        ((base) + (0x450))

/* 寄存器说明：中断屏蔽配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCINT_MASK_UNION */
#define SOC_SCTRL_SCINT_MASK_ADDR(base)               ((base) + (0x454))

/* 寄存器说明：原始中断状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCINT_STAT_UNION */
#define SOC_SCTRL_SCINT_STAT_ADDR(base)               ((base) + (0x458))

/* 寄存器说明：DRX中断分配配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCDRX_INT_CFG_UNION */
#define SOC_SCTRL_SCDRX_INT_CFG_ADDR(base)            ((base) + (0x45C))

/* 寄存器说明：LPMCU WFI中断状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCLPMCUWFI_INT_UNION */
#define SOC_SCTRL_SCLPMCUWFI_INT_ADDR(base)           ((base) + (0x460))

/* 寄存器说明：中断屏蔽配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCINT_MASK1_UNION */
#define SOC_SCTRL_SCINT_MASK1_ADDR(base)              ((base) + (0x464))

/* 寄存器说明：原始中断状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCINT_STAT1_UNION */
#define SOC_SCTRL_SCINT_STAT1_ADDR(base)              ((base) + (0x468))

/* 寄存器说明：中断屏蔽配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCINT_MASK2_UNION */
#define SOC_SCTRL_SCINT_MASK2_ADDR(base)              ((base) + (0x46C))

/* 寄存器说明：原始中断状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCINT_STAT2_UNION */
#define SOC_SCTRL_SCINT_STAT2_ADDR(base)              ((base) + (0x470))

/* 寄存器说明：MALI DBGACK BYPASS配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCMALIBYPCFG_UNION */
#define SOC_SCTRL_SCMALIBYPCFG_ADDR(base)             ((base) + (0x48C))

/* 寄存器说明：LPMCU子系统时钟使能寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCLPMCUCLKEN_UNION */
#define SOC_SCTRL_SCLPMCUCLKEN_ADDR(base)             ((base) + (0x500))

/* 寄存器说明：LPMCU子系统软复位使能寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCLPMCURSTEN_UNION */
#define SOC_SCTRL_SCLPMCURSTEN_ADDR(base)             ((base) + (0x504))

/* 寄存器说明：LPMCU子系统软复位撤离寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCLPMCURSTDIS_UNION */
#define SOC_SCTRL_SCLPMCURSTDIS_ADDR(base)            ((base) + (0x508))

/* 寄存器说明：LPMCU子系统软复位使能状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCLPMCURSTSTAT_UNION */
#define SOC_SCTRL_SCLPMCURSTSTAT_ADDR(base)           ((base) + (0x50C))

/* 寄存器说明：LPMCU子系统控制配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCLPMCUCTRL_UNION */
#define SOC_SCTRL_SCLPMCUCTRL_ADDR(base)              ((base) + (0x510))

/* 寄存器说明：LPMCU子系统状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCLPMCUSTAT_UNION */
#define SOC_SCTRL_SCLPMCUSTAT_ADDR(base)              ((base) + (0x514))

/* 寄存器说明：LPMCU RAM 控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCLPMCURAMCTRL_UNION */
#define SOC_SCTRL_SCLPMCURAMCTRL_ADDR(base)           ((base) + (0x518))

/* 寄存器说明：BBPDRX子系统状态寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCBBPDRXSTAT0_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT0_ADDR(base)            ((base) + (0x530))

/* 寄存器说明：BBPDRX子系统状态寄存器1。
   位域定义UNION结构:  SOC_SCTRL_SCBBPDRXSTAT1_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT1_ADDR(base)            ((base) + (0x534))

/* 寄存器说明：BBPDRX子系统状态寄存器2。
   位域定义UNION结构:  SOC_SCTRL_SCBBPDRXSTAT2_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT2_ADDR(base)            ((base) + (0x538))

/* 寄存器说明：BBPDRX子系统状态寄存器3。
   位域定义UNION结构:  SOC_SCTRL_SCBBPDRXSTAT3_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT3_ADDR(base)            ((base) + (0x53C))

/* 寄存器说明：BBPDRX子系统状态寄存器4。
   位域定义UNION结构:  SOC_SCTRL_SCBBPDRXSTAT4_UNION */
#define SOC_SCTRL_SCBBPDRXSTAT4_ADDR(base)            ((base) + (0x540))

/* 寄存器说明：A53 EVENT屏蔽寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCA53_EVENT_MASK_UNION */
#define SOC_SCTRL_SCA53_EVENT_MASK_ADDR(base)         ((base) + (0x550))

/* 寄存器说明：A57 EVENT屏蔽寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCA57_EVENT_MASK_UNION */
#define SOC_SCTRL_SCA57_EVENT_MASK_ADDR(base)         ((base) + (0x554))

/* 寄存器说明：IOMCU EVENT屏蔽寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIOMCU_EVENT_MASK_UNION */
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_ADDR(base)       ((base) + (0x558))

/* 寄存器说明：LPMCU EVENT屏蔽寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCLPMCU_EVENT_MASK_UNION */
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_ADDR(base)       ((base) + (0x55C))

/* 寄存器说明：MCPU EVENT屏蔽寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCMCPU_EVENT_MASK_UNION */
#define SOC_SCTRL_SCMCPU_EVENT_MASK_ADDR(base)        ((base) + (0x560))

/* 寄存器说明：EVENT状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCEVENT_STAT_UNION */
#define SOC_SCTRL_SCEVENT_STAT_ADDR(base)             ((base) + (0x564))

/* 寄存器说明：MCPU EVENT屏蔽寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCISPA7_EVENT_MASK_UNION */
#define SOC_SCTRL_SCISPA7_EVENT_MASK_ADDR(base)       ((base) + (0x568))

/* 寄存器说明：IOMCU时钟控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIOMCUCLKCTRL_UNION */
#define SOC_SCTRL_SCIOMCUCLKCTRL_ADDR(base)           ((base) + (0x580))

/* 寄存器说明：IOMCU时钟控制信号状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIOMCUCLKSTAT_UNION */
#define SOC_SCTRL_SCIOMCUCLKSTAT_ADDR(base)           ((base) + (0x584))

/* 寄存器说明：IOMCU子系统时钟使能寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIOMCUCLKEN_UNION */
#define SOC_SCTRL_SCIOMCUCLKEN_ADDR(base)             ((base) + (0x588))

/* 寄存器说明：IOMCU子系统软复位使能寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIOMCURSTEN_UNION */
#define SOC_SCTRL_SCIOMCURSTEN_ADDR(base)             ((base) + (0x58C))

/* 寄存器说明：IOMCU子系统软复位撤离寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIOMCURSTDIS_UNION */
#define SOC_SCTRL_SCIOMCURSTDIS_ADDR(base)            ((base) + (0x590))

/* 寄存器说明：IOMCU子系统软复位使能状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIOMCURSTSTAT_UNION */
#define SOC_SCTRL_SCIOMCURSTSTAT_ADDR(base)           ((base) + (0x594))

/* 寄存器说明：IOMCU子系统控制配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIOMCUCTRL_UNION */
#define SOC_SCTRL_SCIOMCUCTRL_ADDR(base)              ((base) + (0x598))

/* 寄存器说明：IOMCU子系统状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCIOMCUSTAT_UNION */
#define SOC_SCTRL_SCIOMCUSTAT_ADDR(base)              ((base) + (0x59C))

/* 寄存器说明：JTAG选择控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCJTAG_SEL_UNION */
#define SOC_SCTRL_SCJTAG_SEL_ADDR(base)               ((base) + (0x800))

/* 寄存器说明：MODEM_KEY0。
   位域定义UNION结构:  SOC_SCTRL_SCMODEM_KEY0_UNION */
#define SOC_SCTRL_SCMODEM_KEY0_ADDR(base)             ((base) + (0x804))

/* 寄存器说明：MODEM_KEY1。
   位域定义UNION结构:  SOC_SCTRL_SCMODEM_KEY1_UNION */
#define SOC_SCTRL_SCMODEM_KEY1_ADDR(base)             ((base) + (0x808))

/* 寄存器说明：MODEM_KEY2。
   位域定义UNION结构:  SOC_SCTRL_SCMODEM_KEY2_UNION */
#define SOC_SCTRL_SCMODEM_KEY2_ADDR(base)             ((base) + (0x80C))

/* 寄存器说明：MODEM_KEY3。
   位域定义UNION结构:  SOC_SCTRL_SCMODEM_KEY3_UNION */
#define SOC_SCTRL_SCMODEM_KEY3_ADDR(base)             ((base) + (0x810))

/* 寄存器说明：DJTAG控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCFG_DJTAG_UNION */
#define SOC_SCTRL_SCCFG_DJTAG_ADDR(base)              ((base) + (0x814))

/* 寄存器说明：CP15DISABLE控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCP15_DISABLE_UNION */
#define SOC_SCTRL_SCCP15_DISABLE_ADDR(base)           ((base) + (0x818))

/* 寄存器说明：时钟计数状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCLKCNTSTAT_UNION */
#define SOC_SCTRL_SCCLKCNTSTAT_ADDR(base)             ((base) + (0x81C))

/* 寄存器说明：时钟计数配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCLKCNTCFG_UNION */
#define SOC_SCTRL_SCCLKCNTCFG_ADDR(base)              ((base) + (0x820))

/* 寄存器说明：时钟监控控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCLKMONCTRL_UNION */
#define SOC_SCTRL_SCCLKMONCTRL_ADDR(base)             ((base) + (0x824))

/* 寄存器说明：时钟监控中断状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCLKMONINT_UNION */
#define SOC_SCTRL_SCCLKMONINT_ADDR(base)              ((base) + (0x828))

/* 寄存器说明：ARM debug en配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCFG_ARM_DBGEN_UNION */
#define SOC_SCTRL_SCCFG_ARM_DBGEN_ADDR(base)          ((base) + (0x82C))

/* 寄存器说明：ARM debug key0配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCARM_DBG_KEY0_UNION */
#define SOC_SCTRL_SCARM_DBG_KEY0_ADDR(base)           ((base) + (0x830))

/* 寄存器说明：ARM debug key1配置寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCARM_DBG_KEY1_UNION */
#define SOC_SCTRL_SCARM_DBG_KEY1_ADDR(base)           ((base) + (0x834))

/* 寄存器说明：ARM debug en状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCARM_DBGEN_STAT_UNION */
#define SOC_SCTRL_SCARM_DBGEN_STAT_ADDR(base)         ((base) + (0x838))

/* 寄存器说明：EFUSE PAD烧写控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCEFUSECTRL_UNION */
#define SOC_SCTRL_SCEFUSECTRL_ADDR(base)              ((base) + (0x83C))

/* 寄存器说明：SECS时钟门控寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCEFUSESEL_UNION */
#define SOC_SCTRL_SCEFUSESEL_ADDR(base)               ((base) + (0x840))

/* 寄存器说明：EFUSE SECURITY状态寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCSECURITYSTAT_UNION */
#define SOC_SCTRL_SCSECURITYSTAT_ADDR(base)           ((base) + (0x844))

/* 寄存器说明：EFUSE CHIP_ID0寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCHIP_ID0_UNION */
#define SOC_SCTRL_SCCHIP_ID0_ADDR(base)               ((base) + (0x848))

/* 寄存器说明：EFUSE CHIP_ID1寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCHIP_ID1_UNION */
#define SOC_SCTRL_SCCHIP_ID1_ADDR(base)               ((base) + (0x84C))

/* 寄存器说明：CPU安全控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCCPUSECCTRL_UNION */
#define SOC_SCTRL_SCCPUSECCTRL_ADDR(base)             ((base) + (0x850))

/* 寄存器说明：外设时钟使能寄存器0（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPEREN0_SEC_UNION */
#define SOC_SCTRL_SCPEREN0_SEC_ADDR(base)             ((base) + (0x900))

/* 寄存器说明：外设时钟禁止寄存器0（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERDIS0_SEC_UNION */
#define SOC_SCTRL_SCPERDIS0_SEC_ADDR(base)            ((base) + (0x904))

/* 寄存器说明：外设时钟使能状态寄存器0（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERCLKEN0_SEC_UNION */
#define SOC_SCTRL_SCPERCLKEN0_SEC_ADDR(base)          ((base) + (0x908))

/* 寄存器说明：外设软复位使能寄存器0（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTEN0_SEC_UNION */
#define SOC_SCTRL_SCPERRSTEN0_SEC_ADDR(base)          ((base) + (0x950))

/* 寄存器说明：外设软复位撤离寄存器0（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTDIS0_SEC_UNION */
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ADDR(base)         ((base) + (0x954))

/* 寄存器说明：外设软复位状态寄存器0（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTSTAT0_SEC_UNION */
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ADDR(base)        ((base) + (0x958))

/* 寄存器说明：安全TIMER控制寄存器。
   位域定义UNION结构:  SOC_SCTRL_SCTIMERCTRL_SEC_UNION */
#define SOC_SCTRL_SCTIMERCTRL_SEC_ADDR(base)          ((base) + (0x9A0))

/* 寄存器说明：外设软复位使能寄存器1（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTEN1_SEC_UNION */
#define SOC_SCTRL_SCPERRSTEN1_SEC_ADDR(base)          ((base) + (0xA50))

/* 寄存器说明：外设软复位撤离寄存器1（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTDIS1_SEC_UNION */
#define SOC_SCTRL_SCPERRSTDIS1_SEC_ADDR(base)         ((base) + (0xA54))

/* 寄存器说明：外设软复位状态寄存器1（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTSTAT1_SEC_UNION */
#define SOC_SCTRL_SCPERRSTSTAT1_SEC_ADDR(base)        ((base) + (0xA58))

/* 寄存器说明：外设软复位使能寄存器2（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTEN2_SEC_UNION */
#define SOC_SCTRL_SCPERRSTEN2_SEC_ADDR(base)          ((base) + (0xB50))

/* 寄存器说明：外设软复位撤离寄存器2（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTDIS2_SEC_UNION */
#define SOC_SCTRL_SCPERRSTDIS2_SEC_ADDR(base)         ((base) + (0xB54))

/* 寄存器说明：外设软复位状态寄存器2（安全）。
   位域定义UNION结构:  SOC_SCTRL_SCPERRSTSTAT2_SEC_UNION */
#define SOC_SCTRL_SCPERRSTSTAT2_SEC_ADDR(base)        ((base) + (0xB58))

/* 寄存器说明：SOCID寄存器0。
   位域定义UNION结构:  SOC_SCTRL_SCSOCID0_UNION */
#define SOC_SCTRL_SCSOCID0_ADDR(base)                 ((base) + (0xE00))





/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/



/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/



/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_SCTRL_SCCTRL_UNION
 结构说明  : SCCTRL 寄存器结构定义。地址偏移量:0x000，初值:0x00000012，宽度:32
 寄存器说明: 系统控制器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modectrl                                 : 3;  /* bit[0-2]  : 系统模式控制。这里定义了系统期望的工作模式。
                                                                                    000：SLEEP；
                                                                                    001：DOZE；
                                                                                    01X： SLOW；
                                                                                    1XX:：NORMAL。 */
        unsigned int  modestatus                               : 4;  /* bit[3-6]  : 指示系统控制器系统状态机当前工作模式。
                                                                                    0000：SLEEP；
                                                                                    0001：DOZE；
                                                                                    0011：XTAL CTL；
                                                                                    1000：XTAL_OFF；
                                                                                    1011：SW to XTAL；
                                                                                    1001：SW from XTAL；
                                                                                    0010：SLOW；
                                                                                    0110：PLL CTL；
                                                                                    1110：SW to PLL；
                                                                                    1010：SW from PLL；
                                                                                    0100：NORMAL；
                                                                                    Others：保留。 */
        unsigned int  reserved_0                               : 1;  /* bit[7]    : 保留。 */
        unsigned int  timeforcehigh                            : 1;  /* bit[8]    : Timer使能端强制拉高的硬件使能配置。
                                                                                    0：硬件不进行自动操作；
                                                                                    1：当系统时钟是32K时，硬件自动强制拉高Timer的使能。 */
        unsigned int  timeren0sel                              : 1;  /* bit[9]    : Time0时钟使能参考时钟选择。
                                                                                    0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                                                    1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren0ov                               : 1;  /* bit[10]   : Timer0时钟使能控制。
                                                                                    0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren0sel]指定；
                                                                                    1：使能信号被强制拉高。 */
        unsigned int  timeren1sel                              : 1;  /* bit[11]   : Time1时钟使能参考时钟选择。
                                                                                    0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                                                    1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren1ov                               : 1;  /* bit[12]   : Timer1时钟使能控制。
                                                                                    0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren1sel]指定；
                                                                                    1：使能信号被强制拉高。 */
        unsigned int  mdmtimer_stop_dbg_bp                     : 1;  /* bit[13]   : modem timer auto stop in modem cpu debug bypass
                                                                                    0:modem timer auto stop in modem cpu debug
                                                                                    1:modem timer not auto stop in modem cpu debug。 */
        unsigned int  reserved_1                               : 1;  /* bit[14]   : 保留。 */
        unsigned int  reserved_2                               : 1;  /* bit[15]   : 保留。 */
        unsigned int  sc_aonoc_asp_mst_i_mainnopendingtrans_bp : 1;  /* bit[16]   : sc_aonoc_asp_mst_i_mainnopendingtrans bypass
                                                                                    0:bypass;
                                                                                    1:sc_aonoc_asp_mst_i_mainnopendingtrans is one input of sc_noc_aobus_idle_flag is AndGate。 */
        unsigned int  timeren4sel                              : 1;  /* bit[17]   : Time4时钟使能参考时钟选择。
                                                                                    0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                                                    1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren4ov                               : 1;  /* bit[18]   : Timer4时钟使能控制。
                                                                                    0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren4sel]指定；
                                                                                    1：使能信号被强制拉高。 */
        unsigned int  timeren5sel                              : 1;  /* bit[19]   : Time5时钟使能参考时钟选择。
                                                                                    0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                                                    1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren5ov                               : 1;  /* bit[20]   : Timer5时钟使能控制。
                                                                                    0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren5sel]指定；
                                                                                    1：使能信号被强制拉高。 */
        unsigned int  timeren6sel                              : 1;  /* bit[21]   : Time6时钟使能参考时钟选择。
                                                                                    0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                                                    1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren6ov                               : 1;  /* bit[22]   : Timer6时钟使能控制。
                                                                                    0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren6sel]指定；
                                                                                    1：使能信号被强制拉高。 */
        unsigned int  timeren7sel                              : 1;  /* bit[23]   : Time7时钟使能参考时钟选择。
                                                                                    0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                                                    1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren7ov                               : 1;  /* bit[24]   : Timer7时钟使能控制。
                                                                                    0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren7sel]指定；
                                                                                    1：使能信号被强制拉高。 */
        unsigned int  deepsleepen                              : 1;  /* bit[25]   : 进入DEEP SLEEP模式使能寄存器（配置该bit控制状态机进入掉电流程，在NORMAL模式下配置，配合modectrl起作用）
                                                                                    0：表示不使能；
                                                                                    1：表示使能。 */
        unsigned int  reserved_3                               : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCCTRL_UNION;
#endif
#define SOC_SCTRL_SCCTRL_modectrl_START                                  (0)
#define SOC_SCTRL_SCCTRL_modectrl_END                                    (2)
#define SOC_SCTRL_SCCTRL_modestatus_START                                (3)
#define SOC_SCTRL_SCCTRL_modestatus_END                                  (6)
#define SOC_SCTRL_SCCTRL_timeforcehigh_START                             (8)
#define SOC_SCTRL_SCCTRL_timeforcehigh_END                               (8)
#define SOC_SCTRL_SCCTRL_timeren0sel_START                               (9)
#define SOC_SCTRL_SCCTRL_timeren0sel_END                                 (9)
#define SOC_SCTRL_SCCTRL_timeren0ov_START                                (10)
#define SOC_SCTRL_SCCTRL_timeren0ov_END                                  (10)
#define SOC_SCTRL_SCCTRL_timeren1sel_START                               (11)
#define SOC_SCTRL_SCCTRL_timeren1sel_END                                 (11)
#define SOC_SCTRL_SCCTRL_timeren1ov_START                                (12)
#define SOC_SCTRL_SCCTRL_timeren1ov_END                                  (12)
#define SOC_SCTRL_SCCTRL_mdmtimer_stop_dbg_bp_START                      (13)
#define SOC_SCTRL_SCCTRL_mdmtimer_stop_dbg_bp_END                        (13)
#define SOC_SCTRL_SCCTRL_sc_aonoc_asp_mst_i_mainnopendingtrans_bp_START  (16)
#define SOC_SCTRL_SCCTRL_sc_aonoc_asp_mst_i_mainnopendingtrans_bp_END    (16)
#define SOC_SCTRL_SCCTRL_timeren4sel_START                               (17)
#define SOC_SCTRL_SCCTRL_timeren4sel_END                                 (17)
#define SOC_SCTRL_SCCTRL_timeren4ov_START                                (18)
#define SOC_SCTRL_SCCTRL_timeren4ov_END                                  (18)
#define SOC_SCTRL_SCCTRL_timeren5sel_START                               (19)
#define SOC_SCTRL_SCCTRL_timeren5sel_END                                 (19)
#define SOC_SCTRL_SCCTRL_timeren5ov_START                                (20)
#define SOC_SCTRL_SCCTRL_timeren5ov_END                                  (20)
#define SOC_SCTRL_SCCTRL_timeren6sel_START                               (21)
#define SOC_SCTRL_SCCTRL_timeren6sel_END                                 (21)
#define SOC_SCTRL_SCCTRL_timeren6ov_START                                (22)
#define SOC_SCTRL_SCCTRL_timeren6ov_END                                  (22)
#define SOC_SCTRL_SCCTRL_timeren7sel_START                               (23)
#define SOC_SCTRL_SCCTRL_timeren7sel_END                                 (23)
#define SOC_SCTRL_SCCTRL_timeren7ov_START                                (24)
#define SOC_SCTRL_SCCTRL_timeren7ov_END                                  (24)
#define SOC_SCTRL_SCCTRL_deepsleepen_START                               (25)
#define SOC_SCTRL_SCCTRL_deepsleepen_END                                 (25)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCSYSSTAT_UNION
 结构说明  : SCSYSSTAT 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 系统状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reset_source : 32; /* bit[0-31]: 写：往该寄存器写入任意值会触发系统软复位。
                                                       读：读该寄存器读出复位源。
                                                       复位源指示：
                                                       [17:14]:ddr_fatal_inter
                                                       0:no int 1:int
                                                       [13]:wait_ddr_selfreflash_timeout
                                                       0:no timeout 1:timeout
                                                       [12]:isp_a7_wd_rst_req
                                                       0:no rst req 1:rst req
                                                       [11]:ivp32_wd_rst_req
                                                       0:no rst req 1:rst req
                                                       [10]:modem_wd_rst_req
                                                       0:no rst req 1:rst req
                                                       [9]:asp_subsys_wd_req
                                                       0:no rst req 1:rst req
                                                       [8]:IOMCU_rst_req
                                                       0:no rst req 1:rst req
                                                       [7]:modem_tsensor_rst_req
                                                       0:no rst req 1:rst req
                                                       [6]:LPMCU_rst_req
                                                       0:no rst req 1:rst req
                                                       [5]:wd1_rst_req
                                                       0:no rst req 1:rst req
                                                       [4]:wd0_rst_req
                                                       0:no rst req 1:rst req
                                                       [3]:soft_rst_req
                                                       0:no rst req 1:rst req
                                                       [2]:g3d_tsensor_rst_req
                                                       0:no rst req 1:rst req
                                                       [1]:a53_tsensor1_rst_req
                                                       0:no rst req 1:rst req
                                                       [0]:a53_tsensor0_rst_req
                                                       0:no rst req 1:rst req。 */
    } reg;
} SOC_SCTRL_SCSYSSTAT_UNION;
#endif
#define SOC_SCTRL_SCSYSSTAT_reset_source_START  (0)
#define SOC_SCTRL_SCSYSSTAT_reset_source_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCXTALCTRL_UNION
 结构说明  : SCXTALCTRL 寄存器结构定义。地址偏移量:0x010，初值:0x00210280，宽度:32
 寄存器说明: 晶振控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcxopresel_apb     : 1;  /* bit[0]    : 晶振选择预配置：
                                                              下次唤醒时切换到选定晶振（只在tcxosoft_apb为0并且tcxohardcon_bypass为1时该功能才有效）。 */
        unsigned int  tcxohardcon_bypass : 1;  /* bit[1]    : 晶振选择硬件切换屏蔽：
                                                              1：选择预配置功能
                                                              0：选择硬件自动切换。 */
        unsigned int  tcxosel_apb        : 1;  /* bit[2]    : 晶振软切换选择：
                                                              1：选择TCXO1
                                                              0：选择TCXO0。 */
        unsigned int  tcxosoft_apb       : 1;  /* bit[3]    : 晶振软切换选择：
                                                              1：选择tcxosel_apb
                                                              0：选择预切换或者硬件自动切换。 */
        unsigned int  defau_tcxo         : 1;  /* bit[4]    : 非DRX中断到来默认选择TCXO
                                                              1：选择晶振1
                                                              0：选择晶振0。 */
        unsigned int  tcxofast_ctrl0     : 1;  /* bit[5]    : 晶振0快速启动控制
                                                              1：快速启动（中断直接打开tcxo，常用）
                                                              0：正常启动（系统状态机切换打开tcxo）。 */
        unsigned int  tcxofast_ctrl1     : 1;  /* bit[6]    : 晶振1快速启动控制
                                                              1：快速启动（中断直接打开tcxo，常用）
                                                              0：正常启动（系统状态机切换打开tcxo）。 */
        unsigned int  ctrlen1_apb        : 1;  /* bit[7]    : 晶振1软件使能控制：
                                                              1：晶振使能
                                                              0：晶振去使能。 */
        unsigned int  ctrlsel1_apb       : 1;  /* bit[8]    : 晶振1软件控制选择：
                                                              1：选择ctrlen1_apb
                                                              0：选择硬件自动控制。 */
        unsigned int  ctrlen0_apb        : 1;  /* bit[9]    : 晶振0软件使能控制：
                                                              1：晶振使能
                                                              0：晶振去使能。 */
        unsigned int  ctrlsel0_apb       : 1;  /* bit[10]   : 晶振0软件控制选择：
                                                              1：选择ctrlen0_apb
                                                              0：选择硬件自动控制。 */
        unsigned int  timeout_bypass0    : 1;  /* bit[11]   : 状态机检测晶振0超时BYPASS控制
                                                              1：BYPASS使能
                                                              0：BYPASS去使能。 */
        unsigned int  timeout_bypass1    : 1;  /* bit[12]   : 状态机检测晶振1超时BYPASS控制
                                                              1：BYPASS使能
                                                              0：BYPASS去使能。 */
        unsigned int  tcxoseq_bypass     : 1;  /* bit[13]   : 状态机检测晶振关闭完成BYPASS控制，低功耗mp3场景配置后，系统模式进入sleep不关闭TCXO：
                                                              1：BYPASS使能
                                                              0：BYPASS去使能。 */
        unsigned int  tcxoseq0_time      : 5;  /* bit[14-18]: 关晶振0与关ABB BUF的时间间隔，以32KHZ为时钟周期。 */
        unsigned int  tcxoseq1_time      : 5;  /* bit[19-23]: 关晶振1与关ABB BUF的时间间隔，以32KHZ为时钟周期。 */
        unsigned int  tcxodown_bypass0   : 1;  /* bit[24]   : 系统进入suspend时状态机是否关闭晶振0：
                                                              0：关闭
                                                              1：不关闭
                                                              由IOMCU配置。 */
        unsigned int  tcxodown_bypass1   : 1;  /* bit[25]   : 系统进入suspend时状态机是否关闭晶振1：
                                                              0：关闭
                                                              1：不关闭
                                                              由IOMCU配置。 */
        unsigned int  reserved           : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCXTALCTRL_UNION;
#endif
#define SOC_SCTRL_SCXTALCTRL_tcxopresel_apb_START      (0)
#define SOC_SCTRL_SCXTALCTRL_tcxopresel_apb_END        (0)
#define SOC_SCTRL_SCXTALCTRL_tcxohardcon_bypass_START  (1)
#define SOC_SCTRL_SCXTALCTRL_tcxohardcon_bypass_END    (1)
#define SOC_SCTRL_SCXTALCTRL_tcxosel_apb_START         (2)
#define SOC_SCTRL_SCXTALCTRL_tcxosel_apb_END           (2)
#define SOC_SCTRL_SCXTALCTRL_tcxosoft_apb_START        (3)
#define SOC_SCTRL_SCXTALCTRL_tcxosoft_apb_END          (3)
#define SOC_SCTRL_SCXTALCTRL_defau_tcxo_START          (4)
#define SOC_SCTRL_SCXTALCTRL_defau_tcxo_END            (4)
#define SOC_SCTRL_SCXTALCTRL_tcxofast_ctrl0_START      (5)
#define SOC_SCTRL_SCXTALCTRL_tcxofast_ctrl0_END        (5)
#define SOC_SCTRL_SCXTALCTRL_tcxofast_ctrl1_START      (6)
#define SOC_SCTRL_SCXTALCTRL_tcxofast_ctrl1_END        (6)
#define SOC_SCTRL_SCXTALCTRL_ctrlen1_apb_START         (7)
#define SOC_SCTRL_SCXTALCTRL_ctrlen1_apb_END           (7)
#define SOC_SCTRL_SCXTALCTRL_ctrlsel1_apb_START        (8)
#define SOC_SCTRL_SCXTALCTRL_ctrlsel1_apb_END          (8)
#define SOC_SCTRL_SCXTALCTRL_ctrlen0_apb_START         (9)
#define SOC_SCTRL_SCXTALCTRL_ctrlen0_apb_END           (9)
#define SOC_SCTRL_SCXTALCTRL_ctrlsel0_apb_START        (10)
#define SOC_SCTRL_SCXTALCTRL_ctrlsel0_apb_END          (10)
#define SOC_SCTRL_SCXTALCTRL_timeout_bypass0_START     (11)
#define SOC_SCTRL_SCXTALCTRL_timeout_bypass0_END       (11)
#define SOC_SCTRL_SCXTALCTRL_timeout_bypass1_START     (12)
#define SOC_SCTRL_SCXTALCTRL_timeout_bypass1_END       (12)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq_bypass_START      (13)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq_bypass_END        (13)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq0_time_START       (14)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq0_time_END         (18)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq1_time_START       (19)
#define SOC_SCTRL_SCXTALCTRL_tcxoseq1_time_END         (23)
#define SOC_SCTRL_SCXTALCTRL_tcxodown_bypass0_START    (24)
#define SOC_SCTRL_SCXTALCTRL_tcxodown_bypass0_END      (24)
#define SOC_SCTRL_SCXTALCTRL_tcxodown_bypass1_START    (25)
#define SOC_SCTRL_SCXTALCTRL_tcxodown_bypass1_END      (25)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCXTALTIMEOUT0_UNION
 结构说明  : SCXTALTIMEOUT0 寄存器结构定义。地址偏移量:0x014，初值:0x00000032，宽度:32
 寄存器说明: 晶振稳定时间配置寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeoutcnt0_apb : 32; /* bit[0-31]: 32KHZ时钟周期。 */
    } reg;
} SOC_SCTRL_SCXTALTIMEOUT0_UNION;
#endif
#define SOC_SCTRL_SCXTALTIMEOUT0_timeoutcnt0_apb_START  (0)
#define SOC_SCTRL_SCXTALTIMEOUT0_timeoutcnt0_apb_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCXTALTIMEOUT1_UNION
 结构说明  : SCXTALTIMEOUT1 寄存器结构定义。地址偏移量:0x018，初值:0x00000032，宽度:32
 寄存器说明: 晶振稳定时间配置寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeoutcnt1_apb : 32; /* bit[0-31]: 32KHZ时钟周期。 */
    } reg;
} SOC_SCTRL_SCXTALTIMEOUT1_UNION;
#endif
#define SOC_SCTRL_SCXTALTIMEOUT1_timeoutcnt1_apb_START  (0)
#define SOC_SCTRL_SCXTALTIMEOUT1_timeoutcnt1_apb_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCXTALSTAT_UNION
 结构说明  : SCXTALSTAT 寄存器结构定义。地址偏移量:0x01C，初值:0x00000E3F，宽度:32
 寄存器说明: 晶振控制状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tcxo_en0        : 1;  /* bit[0]    : 晶振0打开请求状态
                                                           0:无请求 1：请求打开。 */
        unsigned int  tcxo_en1        : 1;  /* bit[1]    : 晶振1打开请求状态
                                                           0:无请求 1：请求打开。 */
        unsigned int  tcxo_timeout1   : 1;  /* bit[2]    : 晶振1超时状态
                                                           0：未超时；1：超时。 */
        unsigned int  tcxo_timeout0   : 1;  /* bit[3]    : 晶振0超时状态
                                                           0：未超时；1：超时。 */
        unsigned int  sysclk_en1      : 1;  /* bit[4]    : 晶振1电源使能状态
                                                           0：关闭 1：打开。 */
        unsigned int  sysclk_en0      : 1;  /* bit[5]    : 晶振0电源使能状态
                                                           0：关闭 1：打开。 */
        unsigned int  sysclk_sel      : 1;  /* bit[6]    : 晶振选择状态
                                                           0：tcxo0 1：tcxo1。 */
        unsigned int  clkgt_ctrl0     : 1;  /* bit[7]    : 晶振0控制输出的clk gate信号
                                                           0：关闭 1：打开。 */
        unsigned int  clkgt_ctrl1     : 1;  /* bit[8]    : 晶振1控制输出的clk gate信号
                                                           0：关闭 1：打开。 */
        unsigned int  clkgt_ctrl      : 1;  /* bit[9]    : 最终输出给CRG的clk gate信号
                                                           0：关闭 1：打开。 */
        unsigned int  abbbuf_en0      : 1;  /* bit[10]   : ABB BUF0的使能状态
                                                           0：关闭 1：打开。 */
        unsigned int  abbbuf_en1      : 1;  /* bit[11]   : ABB BUF1的使能状态
                                                           0：关闭 1：打开。 */
        unsigned int  tcxoseq_finish0 : 1;  /* bit[12]   : 晶振0关闭完成指示状态
                                                           0：未关闭 1：关闭完成。 */
        unsigned int  tcxoseq_finish1 : 1;  /* bit[13]   : 晶振1关闭完成指示状态
                                                           0：未关闭 1：关闭完成。 */
        unsigned int  reserved        : 18; /* bit[14-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCXTALSTAT_UNION;
#endif
#define SOC_SCTRL_SCXTALSTAT_tcxo_en0_START         (0)
#define SOC_SCTRL_SCXTALSTAT_tcxo_en0_END           (0)
#define SOC_SCTRL_SCXTALSTAT_tcxo_en1_START         (1)
#define SOC_SCTRL_SCXTALSTAT_tcxo_en1_END           (1)
#define SOC_SCTRL_SCXTALSTAT_tcxo_timeout1_START    (2)
#define SOC_SCTRL_SCXTALSTAT_tcxo_timeout1_END      (2)
#define SOC_SCTRL_SCXTALSTAT_tcxo_timeout0_START    (3)
#define SOC_SCTRL_SCXTALSTAT_tcxo_timeout0_END      (3)
#define SOC_SCTRL_SCXTALSTAT_sysclk_en1_START       (4)
#define SOC_SCTRL_SCXTALSTAT_sysclk_en1_END         (4)
#define SOC_SCTRL_SCXTALSTAT_sysclk_en0_START       (5)
#define SOC_SCTRL_SCXTALSTAT_sysclk_en0_END         (5)
#define SOC_SCTRL_SCXTALSTAT_sysclk_sel_START       (6)
#define SOC_SCTRL_SCXTALSTAT_sysclk_sel_END         (6)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl0_START      (7)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl0_END        (7)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl1_START      (8)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl1_END        (8)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl_START       (9)
#define SOC_SCTRL_SCXTALSTAT_clkgt_ctrl_END         (9)
#define SOC_SCTRL_SCXTALSTAT_abbbuf_en0_START       (10)
#define SOC_SCTRL_SCXTALSTAT_abbbuf_en0_END         (10)
#define SOC_SCTRL_SCXTALSTAT_abbbuf_en1_START       (11)
#define SOC_SCTRL_SCXTALSTAT_abbbuf_en1_END         (11)
#define SOC_SCTRL_SCXTALSTAT_tcxoseq_finish0_START  (12)
#define SOC_SCTRL_SCXTALSTAT_tcxoseq_finish0_END    (12)
#define SOC_SCTRL_SCXTALSTAT_tcxoseq_finish1_START  (13)
#define SOC_SCTRL_SCXTALSTAT_tcxoseq_finish1_END    (13)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPPLLCTRL0_UNION
 结构说明  : SCPPLLCTRL0 寄存器结构定义。地址偏移量:0x020，初值:0x00904B06，宽度:32
 寄存器说明: PPLL0控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll0_en       : 1;  /* bit[0-0]  : PPLL0软件使能控制（最终的使能由该配置信号、IOMCU侧控制信号IOMCU_pll_ctrl、asp_ppll0_en_req 做或）
                                                          0：去使能；
                                                          1：使能。 */
        unsigned int  ppll0_bp       : 1;  /* bit[1-1]  : PPLL0 Bypass控制。
                                                          0：正常工作；
                                                          1：Bypass。 */
        unsigned int  ppll0_refdiv   : 6;  /* bit[2-7]  : PPLL0输入时钟分频器。分频比=配置值+1。 */
        unsigned int  ppll0_fbdiv    : 12; /* bit[8-19] : PPLL0反馈时钟整数分频器。分频比=配置值+1
                                                          。 */
        unsigned int  ppll0_postdiv1 : 3;  /* bit[20-22]: PPLL0输出时钟分频器1。分频比=配置值+1。 */
        unsigned int  ppll0_postdiv2 : 3;  /* bit[23-25]: PPLL0输出时钟分频器2。分频比=配置值+1。 */
        unsigned int  reserved       : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPPLLCTRL0_UNION;
#endif
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_en_START        (0)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_en_END          (0)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_bp_START        (1)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_bp_END          (1)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_refdiv_START    (2)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_refdiv_END      (7)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_fbdiv_START     (8)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_fbdiv_END       (19)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_postdiv1_START  (20)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_postdiv1_END    (22)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_postdiv2_START  (23)
#define SOC_SCTRL_SCPPLLCTRL0_ppll0_postdiv2_END    (25)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPPLLCTRL1_UNION
 结构说明  : SCPPLLCTRL1 寄存器结构定义。地址偏移量:0x024，初值:0x06000000，宽度:32
 寄存器说明: PPLL0控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll0_fracdiv : 24; /* bit[0-23] : PPLL0反馈时钟分数分频器。分频比=配置值+1。 */
        unsigned int  ppll0_int_mod : 1;  /* bit[24-24]: PPLL0整数分频模式。
                                                         0：分数分频模式；
                                                         1：整数分频模式。
                                                         注意：本PLL支持分数分频和整数分频模式，但在SSC打开时，要求软件只使用分数分频模式。 */
        unsigned int  ppll0_cfg_vld : 1;  /* bit[25-25]: PPLL0配置有效标志。
                                                         0：配置无效；
                                                         1：配置有效。 */
        unsigned int  gt_clk_ppll0  : 1;  /* bit[26-26]: PPLL0门控信号。
                                                         0：PPLL0输出时钟门控；
                                                         1：PPLL0输出时钟不门控。（等待PLL稳定后才能配置该bit）。 */
        unsigned int  reserved_0    : 1;  /* bit[27-27]: 保留。 */
        unsigned int  reserved_1    : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPPLLCTRL1_UNION;
#endif
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_fracdiv_START  (0)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_fracdiv_END    (23)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_int_mod_START  (24)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_int_mod_END    (24)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_cfg_vld_START  (25)
#define SOC_SCTRL_SCPPLLCTRL1_ppll0_cfg_vld_END    (25)
#define SOC_SCTRL_SCPPLLCTRL1_gt_clk_ppll0_START   (26)
#define SOC_SCTRL_SCPPLLCTRL1_gt_clk_ppll0_END     (26)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPPLLSSCCTRL_UNION
 结构说明  : SCPPLLSSCCTRL 寄存器结构定义。地址偏移量:0x028，初值:0x0000019F，宽度:32
 寄存器说明: PPLL0 SSC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll0_ssc_reset      : 1;  /* bit[0]    : 复位信号，高有效。
                                                                0：复位取消
                                                                1：复位有效
                                                                注：不能在PLL工作过程中复位，否则会导致PLL失锁。 */
        unsigned int  ppll0_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator，高有效。
                                                                0：正常工作
                                                                1：bypass。 */
        unsigned int  ppll0_ssc_downspread : 1;  /* bit[2]    : 选择center spread或down spread
                                                                0：Center Spread
                                                                1：Down Spread。 */
        unsigned int  ppll0_ssc_spread     : 3;  /* bit[3-5]  : 设置调制深度(spread%)
                                                                3'b000 = 0
                                                                3'b001 = 0.049%
                                                                3'b010 = 0.098%
                                                                3'b011 = 0.195%
                                                                3'b100 = 0.391%
                                                                3'b101 = 0.781%
                                                                3'b110 = 1.563%
                                                                3'b111 = 3.125%。 */
        unsigned int  ppll0_ssc_divval     : 4;  /* bit[6-9]  : 设置频谱调制的频率，一般约为32KHz；
                                                                freq=(CLKSSCG / (DIVVAL * #points))，其中points为128；当REFDIV=1时，CLKSSCG=FREF。 */
        unsigned int  reserved             : 22; /* bit[10-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPPLLSSCCTRL_UNION;
#endif
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_reset_START       (0)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_reset_END         (0)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_disable_START     (1)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_disable_END       (1)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_downspread_START  (2)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_downspread_END    (2)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_spread_START      (3)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_spread_END        (5)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_divval_START      (6)
#define SOC_SCTRL_SCPPLLSSCCTRL_ppll0_ssc_divval_END        (9)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPPLLSTAT_UNION
 结构说明  : SCPPLLSTAT 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: PPLL0状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pllstat       : 1;  /* bit[0]   : PPLL0状态指示。
                                                        0：未稳定；
                                                        1：已稳定。 */
        unsigned int  ppll0_en_stat : 1;  /* bit[1]   : PPLL0最终使能状态指示（由ppll0_en与IOMCU_pll_ctrl或）。
                                                        0：去使能；
                                                        1：使能。 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPPLLSTAT_UNION;
#endif
#define SOC_SCTRL_SCPPLLSTAT_pllstat_START        (0)
#define SOC_SCTRL_SCPPLLSTAT_pllstat_END          (0)
#define SOC_SCTRL_SCPPLLSTAT_ppll0_en_stat_START  (1)
#define SOC_SCTRL_SCPPLLSTAT_ppll0_en_stat_END    (1)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPEREN0_UNION
 结构说明  : SCPEREN0 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ref_crc    : 1;  /* bit[0]  : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_rtc       : 1;  /* bit[1]  : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_rtc1      : 1;  /* bit[2]  : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_timer0    : 1;  /* bit[3]  : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_timer0     : 1;  /* bit[4]  : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  reserved          : 2;  /* bit[5-6]: 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_timer2    : 1;  /* bit[7]  : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_timer2     : 1;  /* bit[8]  : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_timer3    : 1;  /* bit[9]  : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_timer3     : 1;  /* bit[10] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_ao_gpio0  : 1;  /* bit[11] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_ao_gpio1  : 1;  /* bit[12] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_ao_gpio2  : 1;  /* bit[13] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_ao_gpio3  : 1;  /* bit[14] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_ao_ioc    : 1;  /* bit[15] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_out0       : 1;  /* bit[16] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_out1       : 1;  /* bit[17] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_jtag_auth  : 1;  /* bit[18] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_syscnt    : 1;  /* bit[19] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_syscnt     : 1;  /* bit[20] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_ao_gpio4  : 1;  /* bit[21] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_ao_gpio5  : 1;  /* bit[22] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_sci0       : 1;  /* bit[23] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_sci1       : 1;  /* bit[24] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_memrep     : 1;  /* bit[25] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_asp_subsys : 1;  /* bit[26] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_asp_tcxo   : 1;  /* bit[27] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_bbpdrx     : 1;  /* bit[28] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_aobus      : 1;  /* bit[29] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_pclk_efusec    : 1;  /* bit[30] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  gt_clk_ppll0_sscg : 1;  /* bit[31] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
    } reg;
} SOC_SCTRL_SCPEREN0_UNION;
#endif
#define SOC_SCTRL_SCPEREN0_gt_clk_ref_crc_START     (0)
#define SOC_SCTRL_SCPEREN0_gt_clk_ref_crc_END       (0)
#define SOC_SCTRL_SCPEREN0_gt_pclk_rtc_START        (1)
#define SOC_SCTRL_SCPEREN0_gt_pclk_rtc_END          (1)
#define SOC_SCTRL_SCPEREN0_gt_pclk_rtc1_START       (2)
#define SOC_SCTRL_SCPEREN0_gt_pclk_rtc1_END         (2)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer0_START     (3)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer0_END       (3)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer0_START      (4)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer0_END        (4)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer2_START     (7)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer2_END       (7)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer2_START      (8)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer2_END        (8)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer3_START     (9)
#define SOC_SCTRL_SCPEREN0_gt_pclk_timer3_END       (9)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer3_START      (10)
#define SOC_SCTRL_SCPEREN0_gt_clk_timer3_END        (10)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio0_START   (11)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio0_END     (11)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio1_START   (12)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio1_END     (12)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio2_START   (13)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio2_END     (13)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio3_START   (14)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio3_END     (14)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_ioc_START     (15)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_ioc_END       (15)
#define SOC_SCTRL_SCPEREN0_gt_clk_out0_START        (16)
#define SOC_SCTRL_SCPEREN0_gt_clk_out0_END          (16)
#define SOC_SCTRL_SCPEREN0_gt_clk_out1_START        (17)
#define SOC_SCTRL_SCPEREN0_gt_clk_out1_END          (17)
#define SOC_SCTRL_SCPEREN0_gt_clk_jtag_auth_START   (18)
#define SOC_SCTRL_SCPEREN0_gt_clk_jtag_auth_END     (18)
#define SOC_SCTRL_SCPEREN0_gt_pclk_syscnt_START     (19)
#define SOC_SCTRL_SCPEREN0_gt_pclk_syscnt_END       (19)
#define SOC_SCTRL_SCPEREN0_gt_clk_syscnt_START      (20)
#define SOC_SCTRL_SCPEREN0_gt_clk_syscnt_END        (20)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio4_START   (21)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio4_END     (21)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio5_START   (22)
#define SOC_SCTRL_SCPEREN0_gt_pclk_ao_gpio5_END     (22)
#define SOC_SCTRL_SCPEREN0_gt_clk_sci0_START        (23)
#define SOC_SCTRL_SCPEREN0_gt_clk_sci0_END          (23)
#define SOC_SCTRL_SCPEREN0_gt_clk_sci1_START        (24)
#define SOC_SCTRL_SCPEREN0_gt_clk_sci1_END          (24)
#define SOC_SCTRL_SCPEREN0_gt_clk_memrep_START      (25)
#define SOC_SCTRL_SCPEREN0_gt_clk_memrep_END        (25)
#define SOC_SCTRL_SCPEREN0_gt_clk_asp_subsys_START  (26)
#define SOC_SCTRL_SCPEREN0_gt_clk_asp_subsys_END    (26)
#define SOC_SCTRL_SCPEREN0_gt_clk_asp_tcxo_START    (27)
#define SOC_SCTRL_SCPEREN0_gt_clk_asp_tcxo_END      (27)
#define SOC_SCTRL_SCPEREN0_gt_clk_bbpdrx_START      (28)
#define SOC_SCTRL_SCPEREN0_gt_clk_bbpdrx_END        (28)
#define SOC_SCTRL_SCPEREN0_gt_clk_aobus_START       (29)
#define SOC_SCTRL_SCPEREN0_gt_clk_aobus_END         (29)
#define SOC_SCTRL_SCPEREN0_gt_pclk_efusec_START     (30)
#define SOC_SCTRL_SCPEREN0_gt_pclk_efusec_END       (30)
#define SOC_SCTRL_SCPEREN0_gt_clk_ppll0_sscg_START  (31)
#define SOC_SCTRL_SCPEREN0_gt_clk_ppll0_sscg_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERDIS0_UNION
 结构说明  : SCPERDIS0 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ref_crc    : 1;  /* bit[0]  : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_rtc       : 1;  /* bit[1]  : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_rtc1      : 1;  /* bit[2]  : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_timer0    : 1;  /* bit[3]  : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_timer0     : 1;  /* bit[4]  : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  reserved          : 2;  /* bit[5-6]: 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_timer2    : 1;  /* bit[7]  : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_timer2     : 1;  /* bit[8]  : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_timer3    : 1;  /* bit[9]  : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_timer3     : 1;  /* bit[10] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_ao_gpio0  : 1;  /* bit[11] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_ao_gpio1  : 1;  /* bit[12] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_ao_gpio2  : 1;  /* bit[13] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_ao_gpio3  : 1;  /* bit[14] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_ao_ioc    : 1;  /* bit[15] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_out0       : 1;  /* bit[16] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_out1       : 1;  /* bit[17] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_jtag_auth  : 1;  /* bit[18] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_syscnt    : 1;  /* bit[19] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_syscnt     : 1;  /* bit[20] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_ao_gpio4  : 1;  /* bit[21] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_ao_gpio5  : 1;  /* bit[22] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_sci0       : 1;  /* bit[23] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_sci1       : 1;  /* bit[24] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_memrep     : 1;  /* bit[25] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_asp_subsys : 1;  /* bit[26] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_asp_tcxo   : 1;  /* bit[27] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_bbpdrx     : 1;  /* bit[28] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_aobus      : 1;  /* bit[29] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_pclk_efusec    : 1;  /* bit[30] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  gt_clk_ppll0_sscg : 1;  /* bit[31] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
    } reg;
} SOC_SCTRL_SCPERDIS0_UNION;
#endif
#define SOC_SCTRL_SCPERDIS0_gt_clk_ref_crc_START     (0)
#define SOC_SCTRL_SCPERDIS0_gt_clk_ref_crc_END       (0)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_rtc_START        (1)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_rtc_END          (1)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_rtc1_START       (2)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_rtc1_END         (2)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer0_START     (3)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer0_END       (3)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer0_START      (4)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer0_END        (4)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer2_START     (7)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer2_END       (7)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer2_START      (8)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer2_END        (8)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer3_START     (9)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_timer3_END       (9)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer3_START      (10)
#define SOC_SCTRL_SCPERDIS0_gt_clk_timer3_END        (10)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio0_START   (11)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio0_END     (11)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio1_START   (12)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio1_END     (12)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio2_START   (13)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio2_END     (13)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio3_START   (14)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio3_END     (14)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_ioc_START     (15)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_ioc_END       (15)
#define SOC_SCTRL_SCPERDIS0_gt_clk_out0_START        (16)
#define SOC_SCTRL_SCPERDIS0_gt_clk_out0_END          (16)
#define SOC_SCTRL_SCPERDIS0_gt_clk_out1_START        (17)
#define SOC_SCTRL_SCPERDIS0_gt_clk_out1_END          (17)
#define SOC_SCTRL_SCPERDIS0_gt_clk_jtag_auth_START   (18)
#define SOC_SCTRL_SCPERDIS0_gt_clk_jtag_auth_END     (18)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_syscnt_START     (19)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_syscnt_END       (19)
#define SOC_SCTRL_SCPERDIS0_gt_clk_syscnt_START      (20)
#define SOC_SCTRL_SCPERDIS0_gt_clk_syscnt_END        (20)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio4_START   (21)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio4_END     (21)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio5_START   (22)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_ao_gpio5_END     (22)
#define SOC_SCTRL_SCPERDIS0_gt_clk_sci0_START        (23)
#define SOC_SCTRL_SCPERDIS0_gt_clk_sci0_END          (23)
#define SOC_SCTRL_SCPERDIS0_gt_clk_sci1_START        (24)
#define SOC_SCTRL_SCPERDIS0_gt_clk_sci1_END          (24)
#define SOC_SCTRL_SCPERDIS0_gt_clk_memrep_START      (25)
#define SOC_SCTRL_SCPERDIS0_gt_clk_memrep_END        (25)
#define SOC_SCTRL_SCPERDIS0_gt_clk_asp_subsys_START  (26)
#define SOC_SCTRL_SCPERDIS0_gt_clk_asp_subsys_END    (26)
#define SOC_SCTRL_SCPERDIS0_gt_clk_asp_tcxo_START    (27)
#define SOC_SCTRL_SCPERDIS0_gt_clk_asp_tcxo_END      (27)
#define SOC_SCTRL_SCPERDIS0_gt_clk_bbpdrx_START      (28)
#define SOC_SCTRL_SCPERDIS0_gt_clk_bbpdrx_END        (28)
#define SOC_SCTRL_SCPERDIS0_gt_clk_aobus_START       (29)
#define SOC_SCTRL_SCPERDIS0_gt_clk_aobus_END         (29)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_efusec_START     (30)
#define SOC_SCTRL_SCPERDIS0_gt_pclk_efusec_END       (30)
#define SOC_SCTRL_SCPERDIS0_gt_clk_ppll0_sscg_START  (31)
#define SOC_SCTRL_SCPERDIS0_gt_clk_ppll0_sscg_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCLKEN0_UNION
 结构说明  : SCPERCLKEN0 寄存器结构定义。地址偏移量:0x038，初值:0xF3FFFFFF，宽度:32
 寄存器说明: 外设时钟使能状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ref_crc    : 1;  /* bit[0]  : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_rtc       : 1;  /* bit[1]  : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_rtc1      : 1;  /* bit[2]  : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer0    : 1;  /* bit[3]  : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer0     : 1;  /* bit[4]  : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  reserved          : 2;  /* bit[5-6]: 见SCPERCLKEN0_SEC[1:0]timer1。 */
        unsigned int  gt_pclk_timer2    : 1;  /* bit[7]  : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer2     : 1;  /* bit[8]  : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer3    : 1;  /* bit[9]  : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer3     : 1;  /* bit[10] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio0  : 1;  /* bit[11] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio1  : 1;  /* bit[12] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio2  : 1;  /* bit[13] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio3  : 1;  /* bit[14] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_ioc    : 1;  /* bit[15] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_out0       : 1;  /* bit[16] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_out1       : 1;  /* bit[17] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_jtag_auth  : 1;  /* bit[18] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_syscnt    : 1;  /* bit[19] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_syscnt     : 1;  /* bit[20] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio4  : 1;  /* bit[21] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio5  : 1;  /* bit[22] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_sci0       : 1;  /* bit[23] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_sci1       : 1;  /* bit[24] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_memrep     : 1;  /* bit[25] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_asp_subsys : 1;  /* bit[26] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_asp_tcxo   : 1;  /* bit[27] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_bbpdrx     : 1;  /* bit[28] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_aobus      : 1;  /* bit[29] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_pclk_efusec    : 1;  /* bit[30] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  gt_clk_ppll0_sscg : 1;  /* bit[31] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
    } reg;
} SOC_SCTRL_SCPERCLKEN0_UNION;
#endif
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_ref_crc_START     (0)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_ref_crc_END       (0)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_rtc_START        (1)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_rtc_END          (1)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_rtc1_START       (2)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_rtc1_END         (2)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer0_START     (3)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer0_END       (3)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer0_START      (4)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer0_END        (4)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer2_START     (7)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer2_END       (7)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer2_START      (8)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer2_END        (8)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer3_START     (9)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_timer3_END       (9)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer3_START      (10)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_timer3_END        (10)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio0_START   (11)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio0_END     (11)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio1_START   (12)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio1_END     (12)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio2_START   (13)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio2_END     (13)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio3_START   (14)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio3_END     (14)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_ioc_START     (15)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_ioc_END       (15)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_out0_START        (16)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_out0_END          (16)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_out1_START        (17)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_out1_END          (17)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_jtag_auth_START   (18)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_jtag_auth_END     (18)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_syscnt_START     (19)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_syscnt_END       (19)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_syscnt_START      (20)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_syscnt_END        (20)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio4_START   (21)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio4_END     (21)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio5_START   (22)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_ao_gpio5_END     (22)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_sci0_START        (23)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_sci0_END          (23)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_sci1_START        (24)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_sci1_END          (24)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_memrep_START      (25)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_memrep_END        (25)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_asp_subsys_START  (26)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_asp_subsys_END    (26)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_asp_tcxo_START    (27)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_asp_tcxo_END      (27)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_bbpdrx_START      (28)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_bbpdrx_END        (28)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_aobus_START       (29)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_aobus_END         (29)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_efusec_START     (30)
#define SOC_SCTRL_SCPERCLKEN0_gt_pclk_efusec_END       (30)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_ppll0_sscg_START  (31)
#define SOC_SCTRL_SCPERCLKEN0_gt_clk_ppll0_sscg_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTAT0_UNION
 结构说明  : SCPERSTAT0 寄存器结构定义。地址偏移量:0x03C，初值:0xF3FFFFFF，宽度:32
 寄存器说明: 外设时钟最终状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ref_crc    : 1;  /* bit[0] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_rtc       : 1;  /* bit[1] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_rtc1      : 1;  /* bit[2] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer0    : 1;  /* bit[3] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer0     : 1;  /* bit[4] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer1    : 1;  /* bit[5] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer1     : 1;  /* bit[6] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer2    : 1;  /* bit[7] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer2     : 1;  /* bit[8] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer3    : 1;  /* bit[9] : 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer3     : 1;  /* bit[10]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio0  : 1;  /* bit[11]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio1  : 1;  /* bit[12]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio2  : 1;  /* bit[13]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio3  : 1;  /* bit[14]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_ioc    : 1;  /* bit[15]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_out0       : 1;  /* bit[16]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_out1       : 1;  /* bit[17]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_jtag_auth  : 1;  /* bit[18]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_syscnt    : 1;  /* bit[19]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_syscnt     : 1;  /* bit[20]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio4  : 1;  /* bit[21]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_ao_gpio5  : 1;  /* bit[22]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_sci0       : 1;  /* bit[23]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_sci1       : 1;  /* bit[24]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_memrep     : 1;  /* bit[25]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_asp_subsys : 1;  /* bit[26]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_asp_tcxo   : 1;  /* bit[27]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_bbpdrx     : 1;  /* bit[28]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_aobus      : 1;  /* bit[29]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_pclk_efusec    : 1;  /* bit[30]: 外设时钟最终状态：
                                                          0：IP时钟禁止状态；
                                                          1：IP时钟使能状态。 */
        unsigned int  gt_clk_ppll0_sscg : 1;  /* bit[31]: 整个寄存器的复位值由SCTRL的输入信号peri_clk_stat0[31:0]的复位值来定。 */
    } reg;
} SOC_SCTRL_SCPERSTAT0_UNION;
#endif
#define SOC_SCTRL_SCPERSTAT0_gt_clk_ref_crc_START     (0)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_ref_crc_END       (0)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_rtc_START        (1)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_rtc_END          (1)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_rtc1_START       (2)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_rtc1_END         (2)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer0_START     (3)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer0_END       (3)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer0_START      (4)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer0_END        (4)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer1_START     (5)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer1_END       (5)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer1_START      (6)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer1_END        (6)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer2_START     (7)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer2_END       (7)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer2_START      (8)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer2_END        (8)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer3_START     (9)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_timer3_END       (9)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer3_START      (10)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_timer3_END        (10)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio0_START   (11)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio0_END     (11)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio1_START   (12)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio1_END     (12)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio2_START   (13)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio2_END     (13)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio3_START   (14)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio3_END     (14)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_ioc_START     (15)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_ioc_END       (15)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_out0_START        (16)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_out0_END          (16)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_out1_START        (17)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_out1_END          (17)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_jtag_auth_START   (18)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_jtag_auth_END     (18)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_syscnt_START     (19)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_syscnt_END       (19)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_syscnt_START      (20)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_syscnt_END        (20)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio4_START   (21)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio4_END     (21)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio5_START   (22)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_ao_gpio5_END     (22)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_sci0_START        (23)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_sci0_END          (23)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_sci1_START        (24)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_sci1_END          (24)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_memrep_START      (25)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_memrep_END        (25)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_asp_subsys_START  (26)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_asp_subsys_END    (26)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_asp_tcxo_START    (27)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_asp_tcxo_END      (27)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_bbpdrx_START      (28)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_bbpdrx_END        (28)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_aobus_START       (29)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_aobus_END         (29)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_efusec_START     (30)
#define SOC_SCTRL_SCPERSTAT0_gt_pclk_efusec_END       (30)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_ppll0_sscg_START  (31)
#define SOC_SCTRL_SCPERSTAT0_gt_clk_ppll0_sscg_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPEREN1_UNION
 结构说明  : SCPEREN1 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_dw_axi                : 1;  /* bit[0]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_asp_x2h                   : 1;  /* bit[1]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_asp_h2p                   : 1;  /* bit[2]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_asp_cfg                       : 1;  /* bit[3]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_bbpdrx_oth                : 1;  /* bit[4]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_aobus_noc                 : 1;  /* bit[5]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_noc_aobus2mmbuf           : 1;  /* bit[6]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  ddr_loopback_en                  : 1;  /* bit[7]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_aclk_asc                      : 1;  /* bit[8]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  reserved_0                       : 1;  /* bit[9]    : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_pclk_timer4                   : 1;  /* bit[10]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_timer4                    : 1;  /* bit[11]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_pclk_timer5                   : 1;  /* bit[12]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_timer5                    : 1;  /* bit[13]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_pclk_timer6                   : 1;  /* bit[14]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_timer6                    : 1;  /* bit[15]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_pclk_timer7                   : 1;  /* bit[16]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_timer7                    : 1;  /* bit[17]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_pclk_timer8                   : 1;  /* bit[18]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_timer8                    : 1;  /* bit[19]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_timerclk_refh                 : 1;  /* bit[20]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  reserved_1                       : 1;  /* bit[21]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_aclk_mmbuf                    : 1;  /* bit[22]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_pclk_mmbuf                    : 1;  /* bit[23]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_mmbuf_dss                 : 1;  /* bit[24]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_pclk_mmbufcfg                 : 1;  /* bit[25]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  gt_clk_autodiv_aobus_noc         : 1;  /* bit[26]   : 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  reserved_2                       : 3;  /* bit[27-29]: 外设时钟使能控制：
                                                                            0：写0无效；
                                                                            1：写1使能IP时钟。 */
        unsigned int  aobus2mmbuf_auto_gate_bypass     : 1;  /* bit[30]   : aobus2mmbuf_auto_gate_bypass
                                                                            0：写0无效；
                                                                            1：写1 auto gate bypass。 */
        unsigned int  wait_ddr_selfreflash_done_bypass : 1;  /* bit[31]   : [31]:wait_ddr_selfreflash_done_bypass
                                                                            0：写0无效；
                                                                            1：写1 done bypass。 */
    } reg;
} SOC_SCTRL_SCPEREN1_UNION;
#endif
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_dw_axi_START                 (0)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_dw_axi_END                   (0)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_x2h_START                    (1)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_x2h_END                      (1)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_h2p_START                    (2)
#define SOC_SCTRL_SCPEREN1_gt_clk_asp_h2p_END                      (2)
#define SOC_SCTRL_SCPEREN1_gt_asp_cfg_START                        (3)
#define SOC_SCTRL_SCPEREN1_gt_asp_cfg_END                          (3)
#define SOC_SCTRL_SCPEREN1_gt_clk_bbpdrx_oth_START                 (4)
#define SOC_SCTRL_SCPEREN1_gt_clk_bbpdrx_oth_END                   (4)
#define SOC_SCTRL_SCPEREN1_gt_clk_aobus_noc_START                  (5)
#define SOC_SCTRL_SCPEREN1_gt_clk_aobus_noc_END                    (5)
#define SOC_SCTRL_SCPEREN1_gt_clk_noc_aobus2mmbuf_START            (6)
#define SOC_SCTRL_SCPEREN1_gt_clk_noc_aobus2mmbuf_END              (6)
#define SOC_SCTRL_SCPEREN1_ddr_loopback_en_START                   (7)
#define SOC_SCTRL_SCPEREN1_ddr_loopback_en_END                     (7)
#define SOC_SCTRL_SCPEREN1_gt_aclk_asc_START                       (8)
#define SOC_SCTRL_SCPEREN1_gt_aclk_asc_END                         (8)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer4_START                    (10)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer4_END                      (10)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer4_START                     (11)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer4_END                       (11)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer5_START                    (12)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer5_END                      (12)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer5_START                     (13)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer5_END                       (13)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer6_START                    (14)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer6_END                      (14)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer6_START                     (15)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer6_END                       (15)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer7_START                    (16)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer7_END                      (16)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer7_START                     (17)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer7_END                       (17)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer8_START                    (18)
#define SOC_SCTRL_SCPEREN1_gt_pclk_timer8_END                      (18)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer8_START                     (19)
#define SOC_SCTRL_SCPEREN1_gt_clk_timer8_END                       (19)
#define SOC_SCTRL_SCPEREN1_gt_timerclk_refh_START                  (20)
#define SOC_SCTRL_SCPEREN1_gt_timerclk_refh_END                    (20)
#define SOC_SCTRL_SCPEREN1_gt_aclk_mmbuf_START                     (22)
#define SOC_SCTRL_SCPEREN1_gt_aclk_mmbuf_END                       (22)
#define SOC_SCTRL_SCPEREN1_gt_pclk_mmbuf_START                     (23)
#define SOC_SCTRL_SCPEREN1_gt_pclk_mmbuf_END                       (23)
#define SOC_SCTRL_SCPEREN1_gt_clk_mmbuf_dss_START                  (24)
#define SOC_SCTRL_SCPEREN1_gt_clk_mmbuf_dss_END                    (24)
#define SOC_SCTRL_SCPEREN1_gt_pclk_mmbufcfg_START                  (25)
#define SOC_SCTRL_SCPEREN1_gt_pclk_mmbufcfg_END                    (25)
#define SOC_SCTRL_SCPEREN1_gt_clk_autodiv_aobus_noc_START          (26)
#define SOC_SCTRL_SCPEREN1_gt_clk_autodiv_aobus_noc_END            (26)
#define SOC_SCTRL_SCPEREN1_aobus2mmbuf_auto_gate_bypass_START      (30)
#define SOC_SCTRL_SCPEREN1_aobus2mmbuf_auto_gate_bypass_END        (30)
#define SOC_SCTRL_SCPEREN1_wait_ddr_selfreflash_done_bypass_START  (31)
#define SOC_SCTRL_SCPEREN1_wait_ddr_selfreflash_done_bypass_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERDIS1_UNION
 结构说明  : SCPERDIS1 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_dw_axi                : 1;  /* bit[0]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_asp_x2h                   : 1;  /* bit[1]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_asp_h2p                   : 1;  /* bit[2]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_asp_cfg                       : 1;  /* bit[3]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_bbpdrx_oth                : 1;  /* bit[4]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_aobus_noc                 : 1;  /* bit[5]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_noc_aobus2mmbuf           : 1;  /* bit[6]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  ddr_loopback_en                  : 1;  /* bit[7]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_aclk_asc                      : 1;  /* bit[8]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  reserved_0                       : 1;  /* bit[9]    : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_pclk_timer4                   : 1;  /* bit[10]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_timer4                    : 1;  /* bit[11]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_pclk_timer5                   : 1;  /* bit[12]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_timer5                    : 1;  /* bit[13]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_pclk_timer6                   : 1;  /* bit[14]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_timer6                    : 1;  /* bit[15]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_pclk_timer7                   : 1;  /* bit[16]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_timer7                    : 1;  /* bit[17]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_pclk_timer8                   : 1;  /* bit[18]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_timer8                    : 1;  /* bit[19]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_timerclk_refh                 : 1;  /* bit[20]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  reserved_1                       : 1;  /* bit[21]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_aclk_mmbuf                    : 1;  /* bit[22]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_pclk_mmbuf                    : 1;  /* bit[23]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_mmbuf_dss                 : 1;  /* bit[24]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_pclk_mmbufcfg                 : 1;  /* bit[25]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  gt_clk_autodiv_aobus_noc         : 1;  /* bit[26]   : 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  reserved_2                       : 3;  /* bit[27-29]: 外设时钟禁止控制：
                                                                            0：写0无效；
                                                                            1：写1禁止IP时钟。 */
        unsigned int  aobus2mmbuf_auto_gate_bypass     : 1;  /* bit[30]   : aobus2mmbuf_auto_gate_bypass
                                                                            0：写0无效；
                                                                            1：写1 auto gate not bypass。 */
        unsigned int  wait_ddr_selfreflash_done_bypass : 1;  /* bit[31]   : [31]:wait_ddr_selfreflash_done_bypass
                                                                            0：写0无效；
                                                                            1：写1 done not bypass。 */
    } reg;
} SOC_SCTRL_SCPERDIS1_UNION;
#endif
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_dw_axi_START                 (0)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_dw_axi_END                   (0)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_x2h_START                    (1)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_x2h_END                      (1)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_h2p_START                    (2)
#define SOC_SCTRL_SCPERDIS1_gt_clk_asp_h2p_END                      (2)
#define SOC_SCTRL_SCPERDIS1_gt_asp_cfg_START                        (3)
#define SOC_SCTRL_SCPERDIS1_gt_asp_cfg_END                          (3)
#define SOC_SCTRL_SCPERDIS1_gt_clk_bbpdrx_oth_START                 (4)
#define SOC_SCTRL_SCPERDIS1_gt_clk_bbpdrx_oth_END                   (4)
#define SOC_SCTRL_SCPERDIS1_gt_clk_aobus_noc_START                  (5)
#define SOC_SCTRL_SCPERDIS1_gt_clk_aobus_noc_END                    (5)
#define SOC_SCTRL_SCPERDIS1_gt_clk_noc_aobus2mmbuf_START            (6)
#define SOC_SCTRL_SCPERDIS1_gt_clk_noc_aobus2mmbuf_END              (6)
#define SOC_SCTRL_SCPERDIS1_ddr_loopback_en_START                   (7)
#define SOC_SCTRL_SCPERDIS1_ddr_loopback_en_END                     (7)
#define SOC_SCTRL_SCPERDIS1_gt_aclk_asc_START                       (8)
#define SOC_SCTRL_SCPERDIS1_gt_aclk_asc_END                         (8)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer4_START                    (10)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer4_END                      (10)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer4_START                     (11)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer4_END                       (11)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer5_START                    (12)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer5_END                      (12)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer5_START                     (13)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer5_END                       (13)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer6_START                    (14)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer6_END                      (14)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer6_START                     (15)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer6_END                       (15)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer7_START                    (16)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer7_END                      (16)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer7_START                     (17)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer7_END                       (17)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer8_START                    (18)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_timer8_END                      (18)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer8_START                     (19)
#define SOC_SCTRL_SCPERDIS1_gt_clk_timer8_END                       (19)
#define SOC_SCTRL_SCPERDIS1_gt_timerclk_refh_START                  (20)
#define SOC_SCTRL_SCPERDIS1_gt_timerclk_refh_END                    (20)
#define SOC_SCTRL_SCPERDIS1_gt_aclk_mmbuf_START                     (22)
#define SOC_SCTRL_SCPERDIS1_gt_aclk_mmbuf_END                       (22)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_mmbuf_START                     (23)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_mmbuf_END                       (23)
#define SOC_SCTRL_SCPERDIS1_gt_clk_mmbuf_dss_START                  (24)
#define SOC_SCTRL_SCPERDIS1_gt_clk_mmbuf_dss_END                    (24)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_mmbufcfg_START                  (25)
#define SOC_SCTRL_SCPERDIS1_gt_pclk_mmbufcfg_END                    (25)
#define SOC_SCTRL_SCPERDIS1_gt_clk_autodiv_aobus_noc_START          (26)
#define SOC_SCTRL_SCPERDIS1_gt_clk_autodiv_aobus_noc_END            (26)
#define SOC_SCTRL_SCPERDIS1_aobus2mmbuf_auto_gate_bypass_START      (30)
#define SOC_SCTRL_SCPERDIS1_aobus2mmbuf_auto_gate_bypass_END        (30)
#define SOC_SCTRL_SCPERDIS1_wait_ddr_selfreflash_done_bypass_START  (31)
#define SOC_SCTRL_SCPERDIS1_wait_ddr_selfreflash_done_bypass_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCLKEN1_UNION
 结构说明  : SCPERCLKEN1 寄存器结构定义。地址偏移量:0x048，初值:0xBC1FFC70，宽度:32
 寄存器说明: 外设时钟使能状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_dw_axi                : 1;  /* bit[0]    : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_asp_x2h                   : 1;  /* bit[1]    : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_asp_h2p                   : 1;  /* bit[2]    : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_asp_cfg                       : 1;  /* bit[3]    : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_bbpdrx_oth                : 1;  /* bit[4]    : modem子系统送给bbpdrx的时钟
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_aobus_noc                 : 1;  /* bit[5]    : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_noc_aobus2mmbuf           : 1;  /* bit[6]    : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  ddr_loopback_en                  : 1;  /* bit[7]    : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_aclk_asc                      : 1;  /* bit[8]    : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  reserved_0                       : 1;  /* bit[9]    : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer4                   : 1;  /* bit[10]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer4                    : 1;  /* bit[11]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer5                   : 1;  /* bit[12]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer5                    : 1;  /* bit[13]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer6                   : 1;  /* bit[14]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer6                    : 1;  /* bit[15]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer7                   : 1;  /* bit[16]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer7                    : 1;  /* bit[17]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer8                   : 1;  /* bit[18]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer8                    : 1;  /* bit[19]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_timerclk_refh                 : 1;  /* bit[20]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  reserved_1                       : 1;  /* bit[21]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_aclk_mmbuf                    : 1;  /* bit[22]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_pclk_mmbuf                    : 1;  /* bit[23]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_mmbuf_dss                 : 1;  /* bit[24]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  gt_pclk_mmbufcfg                 : 1;  /* bit[25]   : 0：时钟关闭；
                                                                            1：时钟开启。
                                                                            最终配置值由iomcu，audio和此配置位投票确定，有需求打开就时钟，所有请求都关闭才关闭时钟。 */
        unsigned int  gt_clk_autodiv_aobus_noc         : 1;  /* bit[26]   : 外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  reserved_2                       : 3;  /* bit[27-29]: [29:28]:reserved
                                                                            [27]:输出端口peri_clk_en1[27]由gt_clk_ao_cc驱动
                                                                            外设时钟使能状态：
                                                                            0：IP时钟禁止状态；
                                                                            1：IP时钟使能状态。 */
        unsigned int  aobus2mmbuf_auto_gate_bypass     : 1;  /* bit[30]   : aobus2mmbuf_auto_gate_bypass
                                                                            0:no bypass
                                                                            1:bypass。 */
        unsigned int  wait_ddr_selfreflash_done_bypass : 1;  /* bit[31]   : [31]:wait_ddr_selfreflash_done_bypass
                                                                            0:no bypass
                                                                            1:bypass。 */
    } reg;
} SOC_SCTRL_SCPERCLKEN1_UNION;
#endif
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_dw_axi_START                 (0)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_dw_axi_END                   (0)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_x2h_START                    (1)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_x2h_END                      (1)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_h2p_START                    (2)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_asp_h2p_END                      (2)
#define SOC_SCTRL_SCPERCLKEN1_gt_asp_cfg_START                        (3)
#define SOC_SCTRL_SCPERCLKEN1_gt_asp_cfg_END                          (3)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_bbpdrx_oth_START                 (4)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_bbpdrx_oth_END                   (4)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_aobus_noc_START                  (5)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_aobus_noc_END                    (5)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_noc_aobus2mmbuf_START            (6)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_noc_aobus2mmbuf_END              (6)
#define SOC_SCTRL_SCPERCLKEN1_ddr_loopback_en_START                   (7)
#define SOC_SCTRL_SCPERCLKEN1_ddr_loopback_en_END                     (7)
#define SOC_SCTRL_SCPERCLKEN1_gt_aclk_asc_START                       (8)
#define SOC_SCTRL_SCPERCLKEN1_gt_aclk_asc_END                         (8)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer4_START                    (10)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer4_END                      (10)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer4_START                     (11)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer4_END                       (11)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer5_START                    (12)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer5_END                      (12)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer5_START                     (13)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer5_END                       (13)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer6_START                    (14)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer6_END                      (14)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer6_START                     (15)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer6_END                       (15)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer7_START                    (16)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer7_END                      (16)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer7_START                     (17)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer7_END                       (17)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer8_START                    (18)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_timer8_END                      (18)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer8_START                     (19)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_timer8_END                       (19)
#define SOC_SCTRL_SCPERCLKEN1_gt_timerclk_refh_START                  (20)
#define SOC_SCTRL_SCPERCLKEN1_gt_timerclk_refh_END                    (20)
#define SOC_SCTRL_SCPERCLKEN1_gt_aclk_mmbuf_START                     (22)
#define SOC_SCTRL_SCPERCLKEN1_gt_aclk_mmbuf_END                       (22)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_mmbuf_START                     (23)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_mmbuf_END                       (23)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_mmbuf_dss_START                  (24)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_mmbuf_dss_END                    (24)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_mmbufcfg_START                  (25)
#define SOC_SCTRL_SCPERCLKEN1_gt_pclk_mmbufcfg_END                    (25)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_autodiv_aobus_noc_START          (26)
#define SOC_SCTRL_SCPERCLKEN1_gt_clk_autodiv_aobus_noc_END            (26)
#define SOC_SCTRL_SCPERCLKEN1_aobus2mmbuf_auto_gate_bypass_START      (30)
#define SOC_SCTRL_SCPERCLKEN1_aobus2mmbuf_auto_gate_bypass_END        (30)
#define SOC_SCTRL_SCPERCLKEN1_wait_ddr_selfreflash_done_bypass_START  (31)
#define SOC_SCTRL_SCPERCLKEN1_wait_ddr_selfreflash_done_bypass_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTAT1_UNION
 结构说明  : SCPERSTAT1 寄存器结构定义。地址偏移量:0x04C，初值:0x44FFFC70，宽度:32
 寄存器说明: 外设时钟最终状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_dw_axi           : 1;  /* bit[0] : 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_asp_x2h              : 1;  /* bit[1] : 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_asp_h2p              : 1;  /* bit[2] : 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_asp_cfg                  : 1;  /* bit[3] : 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_104m_bbpdrx          : 1;  /* bit[4] : modem子系统送给bbpdrx的时钟
                                                                    外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  st_clk_noc_aobus2sysbusddrc : 1;  /* bit[5] : 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  st_clk_noc_aobus2mmbuf      : 1;  /* bit[6] : 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  reserved_0                  : 1;  /* bit[7] : 保留。 */
        unsigned int  st_aclk_asc                 : 1;  /* bit[8] : 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  reserved_1                  : 1;  /* bit[9] : 保留。 */
        unsigned int  gt_pclk_timer4              : 1;  /* bit[10]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer4               : 1;  /* bit[11]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer5              : 1;  /* bit[12]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer5               : 1;  /* bit[13]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer6              : 1;  /* bit[14]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer6               : 1;  /* bit[15]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer7              : 1;  /* bit[16]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer7               : 1;  /* bit[17]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_pclk_timer8              : 1;  /* bit[18]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer8               : 1;  /* bit[19]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_timerclk_refh            : 1;  /* bit[20]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_monitor              : 1;  /* bit[21]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  st_aclk_mmbuf               : 1;  /* bit[22]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  st_pclk_mmbuf               : 1;  /* bit[23]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  st_aclk_mmbuf_dss           : 1;  /* bit[24]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_pclk_mmbufcfg            : 1;  /* bit[25]: 0：时钟关闭；
                                                                    1：时钟开启。
                                                                    最终配置值由iomcu，audio和SCPERCLKEN1[25]配置位投票确定，有需求打开就时钟，所有请求都关闭才关闭时钟。 */
        unsigned int  reserved_2                  : 1;  /* bit[26]: 保留。 */
        unsigned int  swdone_clk_asp_subsys_div   : 1;  /* bit[27]: clk_asp_subsysDIV分频比切换是否完成指示信号：
                                                                    0：未完成；
                                                                    1：完成。 */
        unsigned int  swdone_clk_sci_div          : 1;  /* bit[28]: clk_sci DIV分频比切换是否完成指示信号：
                                                                    0：未完成；
                                                                    1：完成。 */
        unsigned int  swdone_clk_aobus_div        : 1;  /* bit[29]: clk_aobus DIV分频比切换是否完成指示信号：
                                                                    0：未完成；
                                                                    1：完成。 */
        unsigned int  aobusclksw2sys              : 1;  /* bit[30]: aobus clk切换至晶振时钟指示，高有效。 */
        unsigned int  aobusclksw2pll              : 1;  /* bit[31]: aobus clk切换至PLL时钟指示，高有效。 */
    } reg;
} SOC_SCTRL_SCPERSTAT1_UNION;
#endif
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_dw_axi_START            (0)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_dw_axi_END              (0)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_x2h_START               (1)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_x2h_END                 (1)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_h2p_START               (2)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_asp_h2p_END                 (2)
#define SOC_SCTRL_SCPERSTAT1_gt_asp_cfg_START                   (3)
#define SOC_SCTRL_SCPERSTAT1_gt_asp_cfg_END                     (3)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_104m_bbpdrx_START           (4)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_104m_bbpdrx_END             (4)
#define SOC_SCTRL_SCPERSTAT1_st_clk_noc_aobus2sysbusddrc_START  (5)
#define SOC_SCTRL_SCPERSTAT1_st_clk_noc_aobus2sysbusddrc_END    (5)
#define SOC_SCTRL_SCPERSTAT1_st_clk_noc_aobus2mmbuf_START       (6)
#define SOC_SCTRL_SCPERSTAT1_st_clk_noc_aobus2mmbuf_END         (6)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_asc_START                  (8)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_asc_END                    (8)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer4_START               (10)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer4_END                 (10)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer4_START                (11)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer4_END                  (11)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer5_START               (12)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer5_END                 (12)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer5_START                (13)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer5_END                  (13)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer6_START               (14)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer6_END                 (14)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer6_START                (15)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer6_END                  (15)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer7_START               (16)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer7_END                 (16)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer7_START                (17)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer7_END                  (17)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer8_START               (18)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_timer8_END                 (18)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer8_START                (19)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_timer8_END                  (19)
#define SOC_SCTRL_SCPERSTAT1_gt_timerclk_refh_START             (20)
#define SOC_SCTRL_SCPERSTAT1_gt_timerclk_refh_END               (20)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_monitor_START               (21)
#define SOC_SCTRL_SCPERSTAT1_gt_clk_monitor_END                 (21)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_mmbuf_START                (22)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_mmbuf_END                  (22)
#define SOC_SCTRL_SCPERSTAT1_st_pclk_mmbuf_START                (23)
#define SOC_SCTRL_SCPERSTAT1_st_pclk_mmbuf_END                  (23)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_mmbuf_dss_START            (24)
#define SOC_SCTRL_SCPERSTAT1_st_aclk_mmbuf_dss_END              (24)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_mmbufcfg_START             (25)
#define SOC_SCTRL_SCPERSTAT1_gt_pclk_mmbufcfg_END               (25)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_asp_subsys_div_START    (27)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_asp_subsys_div_END      (27)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_sci_div_START           (28)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_sci_div_END             (28)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_aobus_div_START         (29)
#define SOC_SCTRL_SCPERSTAT1_swdone_clk_aobus_div_END           (29)
#define SOC_SCTRL_SCPERSTAT1_aobusclksw2sys_START               (30)
#define SOC_SCTRL_SCPERSTAT1_aobusclksw2sys_END                 (30)
#define SOC_SCTRL_SCPERSTAT1_aobusclksw2pll_START               (31)
#define SOC_SCTRL_SCPERSTAT1_aobusclksw2pll_END                 (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPEREN2_UNION
 结构说明  : SCPEREN2 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPEREN2_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERDIS2_UNION
 结构说明  : SCPERDIS2 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERDIS2_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCLKEN2_UNION
 结构说明  : SCPERCLKEN2 寄存器结构定义。地址偏移量:0x058，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 外设时钟使能状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERCLKEN2_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTAT2_UNION
 结构说明  : SCPERSTAT2 寄存器结构定义。地址偏移量:0x05C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 外设时钟最终状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scperstat2 : 32; /* bit[0-31]: [14]:reset_dram_n
                                                     送给片外DRAM的复位，0表示rst。
                                                     [13]:memrep_sw2tcxo
                                                     memrep的时钟切换状态指示： 1：memrep的时钟切换到tcxo； 0：memrep的 时钟未40M时钟；
                                                     [12]:swdone_clk_memrep_div
                                                     memrep 时钟分频完成指示信号， 1 完成，0 未完成；
                                                     [11]:asp_subsys_sw2pll
                                                     asp 源时钟切换源切换指示 1：切换到PLL， 0： 切换到FLL；
                                                     [10]:mmbuf_sw2pll
                                                     [9]:mmbuf_sw2fll
                                                     [8]:mmbuf_sw2tcxo
                                                     mmbuf 时钟源切换指示， 分别为1的时候表示切换到对应时钟源；
                                                     [7]:aobusnoc_sw2pll
                                                     [6]:aobusnoc_sw2ddr
                                                     [5]:aobusnoc_sw2fll
                                                     [4]:aobusnoc_sw2tcxo
                                                     时钟源切换指示， 分别为1的时候表示切换到对应时钟源；
                                                     [3]:swdone_clk_iomcu_pll_div
                                                     [2]:swdone_clk_aobus_noc_div
                                                     [1]:swdone_pclk_mmbuf_div
                                                     [0]:swdone_aclk_mmbuf_div
                                                     各个分频div 分频完成切换指示，1 表示分频完成，0 表示分频过程中
                                                     其他：保留。 */
    } reg;
} SOC_SCTRL_SCPERSTAT2_UNION;
#endif
#define SOC_SCTRL_SCPERSTAT2_scperstat2_START  (0)
#define SOC_SCTRL_SCPERSTAT2_scperstat2_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCTIMERCTRL_UNION
 结构说明  : SCTIMERCTRL 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: 系统TIMER时钟选择和控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeren8ov   : 1;  /* bit[0]    : Timer8时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren0sel]指定；
                                                        1：使能信号被强制拉高。 */
        unsigned int  timeren8sel  : 1;  /* bit[1]    : Time8时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren9ov   : 1;  /* bit[2]    : Timer9时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren1sel]指定；
                                                        1：使能信号被强制拉高。 */
        unsigned int  timeren9sel  : 1;  /* bit[3]    : Time9时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren10ov  : 1;  /* bit[4]    : Timer10时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren2sel]指定；
                                                        1：使能信号被强制拉高。
                                                        注：此TIMER有安全控制需求，可通过配置安全区的timer_secu_en位来强制选择32KHZ时钟。 */
        unsigned int  timeren10sel : 1;  /* bit[5]    : Time10时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren11ov  : 1;  /* bit[6]    : Timer11时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren3sel]指定；
                                                        1：使能信号被强制拉高。 */
        unsigned int  timeren11sel : 1;  /* bit[7]    : Time11时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren12ov  : 1;  /* bit[8]    : Timer12时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren4sel]指定；
                                                        1：使能信号被强制拉高。 */
        unsigned int  timeren12sel : 1;  /* bit[9]    : Time12时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren13ov  : 1;  /* bit[10]   : Timer13时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren5sel]指定；
                                                        1：使能信号被强制拉高。 */
        unsigned int  timeren13sel : 1;  /* bit[11]   : Time13时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren14ov  : 1;  /* bit[12]   : Timer14时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren6sel]指定；
                                                        1：使能信号被强制拉高。 */
        unsigned int  timeren14sel : 1;  /* bit[13]   : Time14时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren15ov  : 1;  /* bit[14]   : Timer15时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren7sel]指定；
                                                        1：使能信号被强制拉高。 */
        unsigned int  timeren15sel : 1;  /* bit[15]   : Time15时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren16ov  : 1;  /* bit[16]   : Timer16时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren6sel]指定；
                                                        1：使能信号被强制拉高。 */
        unsigned int  timeren16sel : 1;  /* bit[17]   : Time16时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren17ov  : 1;  /* bit[18]   : Timer17时钟使能控制。
                                                        0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren7sel]指定；
                                                        1：使能信号被强制拉高。 */
        unsigned int  timeren17sel : 1;  /* bit[19]   : Time17时钟使能参考时钟选择。
                                                        0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                        1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  reserved     : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCTIMERCTRL_UNION;
#endif
#define SOC_SCTRL_SCTIMERCTRL_timeren8ov_START    (0)
#define SOC_SCTRL_SCTIMERCTRL_timeren8ov_END      (0)
#define SOC_SCTRL_SCTIMERCTRL_timeren8sel_START   (1)
#define SOC_SCTRL_SCTIMERCTRL_timeren8sel_END     (1)
#define SOC_SCTRL_SCTIMERCTRL_timeren9ov_START    (2)
#define SOC_SCTRL_SCTIMERCTRL_timeren9ov_END      (2)
#define SOC_SCTRL_SCTIMERCTRL_timeren9sel_START   (3)
#define SOC_SCTRL_SCTIMERCTRL_timeren9sel_END     (3)
#define SOC_SCTRL_SCTIMERCTRL_timeren10ov_START   (4)
#define SOC_SCTRL_SCTIMERCTRL_timeren10ov_END     (4)
#define SOC_SCTRL_SCTIMERCTRL_timeren10sel_START  (5)
#define SOC_SCTRL_SCTIMERCTRL_timeren10sel_END    (5)
#define SOC_SCTRL_SCTIMERCTRL_timeren11ov_START   (6)
#define SOC_SCTRL_SCTIMERCTRL_timeren11ov_END     (6)
#define SOC_SCTRL_SCTIMERCTRL_timeren11sel_START  (7)
#define SOC_SCTRL_SCTIMERCTRL_timeren11sel_END    (7)
#define SOC_SCTRL_SCTIMERCTRL_timeren12ov_START   (8)
#define SOC_SCTRL_SCTIMERCTRL_timeren12ov_END     (8)
#define SOC_SCTRL_SCTIMERCTRL_timeren12sel_START  (9)
#define SOC_SCTRL_SCTIMERCTRL_timeren12sel_END    (9)
#define SOC_SCTRL_SCTIMERCTRL_timeren13ov_START   (10)
#define SOC_SCTRL_SCTIMERCTRL_timeren13ov_END     (10)
#define SOC_SCTRL_SCTIMERCTRL_timeren13sel_START  (11)
#define SOC_SCTRL_SCTIMERCTRL_timeren13sel_END    (11)
#define SOC_SCTRL_SCTIMERCTRL_timeren14ov_START   (12)
#define SOC_SCTRL_SCTIMERCTRL_timeren14ov_END     (12)
#define SOC_SCTRL_SCTIMERCTRL_timeren14sel_START  (13)
#define SOC_SCTRL_SCTIMERCTRL_timeren14sel_END    (13)
#define SOC_SCTRL_SCTIMERCTRL_timeren15ov_START   (14)
#define SOC_SCTRL_SCTIMERCTRL_timeren15ov_END     (14)
#define SOC_SCTRL_SCTIMERCTRL_timeren15sel_START  (15)
#define SOC_SCTRL_SCTIMERCTRL_timeren15sel_END    (15)
#define SOC_SCTRL_SCTIMERCTRL_timeren16ov_START   (16)
#define SOC_SCTRL_SCTIMERCTRL_timeren16ov_END     (16)
#define SOC_SCTRL_SCTIMERCTRL_timeren16sel_START  (17)
#define SOC_SCTRL_SCTIMERCTRL_timeren16sel_END    (17)
#define SOC_SCTRL_SCTIMERCTRL_timeren17ov_START   (18)
#define SOC_SCTRL_SCTIMERCTRL_timeren17ov_END     (18)
#define SOC_SCTRL_SCTIMERCTRL_timeren17sel_START  (19)
#define SOC_SCTRL_SCTIMERCTRL_timeren17sel_END    (19)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCFPLLCTRL0_UNION
 结构说明  : SCFPLLCTRL0 寄存器结构定义。地址偏移量:0x064，初值:0x00904B06，宽度:32
 寄存器说明: FPLL0控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpll0_en    : 1;  /* bit[0]   : [0]:fpll0_en 此bit和asp_fpll_en_req和iomcu_fpll_en_req投票确定，有一个bit为1打开fpll，三个bit都为0关闭fpll。
                                                      1:PLL正常工作，0:powerdown
                                                      1.初始配置检测到EN信号上升沿后30个cycle，Lock信号拉高。 */
        unsigned int  fpll_bypass : 1;  /* bit[1]   : [1]:pll_bypass 
                                                      1:bypass FOUT =FREF ,具有最高优先级，即EN=x，POSTDIV=XX 都能完成bypass
                                                      0:正常工作，FOUT=FREF*FCW/POSTDIV。 */
        unsigned int  scfpllctrl0 : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCFPLLCTRL0_UNION;
#endif
#define SOC_SCTRL_SCFPLLCTRL0_fpll0_en_START     (0)
#define SOC_SCTRL_SCFPLLCTRL0_fpll0_en_END       (0)
#define SOC_SCTRL_SCFPLLCTRL0_fpll_bypass_START  (1)
#define SOC_SCTRL_SCFPLLCTRL0_fpll_bypass_END    (1)
#define SOC_SCTRL_SCFPLLCTRL0_scfpllctrl0_START  (2)
#define SOC_SCTRL_SCFPLLCTRL0_scfpllctrl0_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCFPLLCTRL1_UNION
 结构说明  : SCFPLLCTRL1 寄存器结构定义。地址偏移量:0x068，初值:0x00904B06，宽度:32
 寄存器说明: FPLL0控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fpll_fcw     : 13; /* bit[0-12] : BIT[12:0] =FCW 实现1~8191 分频，要求对应的十进制数即为倍频数。 */
        unsigned int  fpll_postdiv : 2;  /* bit[13-14]: BIT[14:13]=POSTDIV （option功能，先做进去，后续真实电路是否需要，根据产品需求来定）
                                                        00:FOUT低电平 01:1分频 01:2分频 11：4分频。 */
        unsigned int  scfpllctrl1  : 17; /* bit[15-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCFPLLCTRL1_UNION;
#endif
#define SOC_SCTRL_SCFPLLCTRL1_fpll_fcw_START      (0)
#define SOC_SCTRL_SCFPLLCTRL1_fpll_fcw_END        (12)
#define SOC_SCTRL_SCFPLLCTRL1_fpll_postdiv_START  (13)
#define SOC_SCTRL_SCFPLLCTRL1_fpll_postdiv_END    (14)
#define SOC_SCTRL_SCFPLLCTRL1_scfpllctrl1_START   (15)
#define SOC_SCTRL_SCFPLLCTRL1_scfpllctrl1_END     (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCFPLLCTRL2_UNION
 结构说明  : SCFPLLCTRL2 寄存器结构定义。地址偏移量:0x06C，初值:0x00904B06，宽度:32
 寄存器说明: FPLL0控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scfpllctrl2 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCFPLLCTRL2_UNION;
#endif
#define SOC_SCTRL_SCFPLLCTRL2_scfpllctrl2_START  (0)
#define SOC_SCTRL_SCFPLLCTRL2_scfpllctrl2_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCFPLLCTRL3_UNION
 结构说明  : SCFPLLCTRL3 寄存器结构定义。地址偏移量:0x070，初值:0x00904B06，宽度:32
 寄存器说明: FPLL0控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scfpllctrl3 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCFPLLCTRL3_UNION;
#endif
#define SOC_SCTRL_SCFPLLCTRL3_scfpllctrl3_START  (0)
#define SOC_SCTRL_SCFPLLCTRL3_scfpllctrl3_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCFPLLSTAT_UNION
 结构说明  : SCFPLLSTAT 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: FPLL0状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scfpllstat : 32; /* bit[0-31]: [0]:LOCK 1:频率锁定 0:频率未锁定
                                                     其余保留。 */
    } reg;
} SOC_SCTRL_SCFPLLSTAT_UNION;
#endif
#define SOC_SCTRL_SCFPLLSTAT_scfpllstat_START  (0)
#define SOC_SCTRL_SCFPLLSTAT_scfpllstat_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTAT3_UNION
 结构说明  : SCPERSTAT3 寄存器结构定义。地址偏移量:0x07C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 外设时钟最终状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERSTAT3_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTEN0_UNION
 结构说明  : SCPERRSTEN0 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]    : IP软复位使能：
                                                           0：IP软复位使能状态不变；
                                                           1：IP软复位使能。 */
        unsigned int  ip_rst_rtc      : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  ip_rst_rtc1     : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  ip_rst_timer0   : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  reserved_1      : 1;  /* bit[4]    : 含义同bit0。 */
        unsigned int  ip_rst_timer2   : 1;  /* bit[5]    : 含义同bit0。 */
        unsigned int  ip_rst_timer3   : 1;  /* bit[6]    : 含义同bit0。 */
        unsigned int  rst_asp_cfg     : 1;  /* bit[7]    : 含义同bit0。 */
        unsigned int  rst_asp_dw_axi  : 1;  /* bit[8]    : 含义同bit0。 */
        unsigned int  rst_asp_x2h     : 1;  /* bit[9]    : 含义同bit0。 */
        unsigned int  rst_asp_h2p     : 1;  /* bit[10]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio0 : 1;  /* bit[11]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio1 : 1;  /* bit[12]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio2 : 1;  /* bit[13]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio3 : 1;  /* bit[14]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio4 : 1;  /* bit[15]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio5 : 1;  /* bit[16]   : 含义同bit0。 */
        unsigned int  reserved_2      : 1;  /* bit[17]   : 保留。 */
        unsigned int  ip_rst_ao_ioc   : 1;  /* bit[18]   : 含义同bit0 */
        unsigned int  ip_prst_syscnt  : 1;  /* bit[19]   : 含义同bit0 */
        unsigned int  ip_rst_syscnt   : 1;  /* bit[20]   : 含义同bit0 */
        unsigned int  reserved_3      : 2;  /* bit[21-22]: 保留。 */
        unsigned int  ip_rst_sci0     : 1;  /* bit[23]   : 含义同bit0。 */
        unsigned int  ip_rst_sci1     : 1;  /* bit[24]   : 含义同bit0。 */
        unsigned int  reserved_4      : 1;  /* bit[25]   : 保留。 */
        unsigned int  reserved_5      : 1;  /* bit[26]   : 含义同bit0。 */
        unsigned int  ip_rst_bbpdrx   : 1;  /* bit[27]   : 含义同bit0。 */
        unsigned int  reserved_6      : 1;  /* bit[28]   : 保留。 */
        unsigned int  ip_rst_aobus    : 1;  /* bit[29]   : 含义同bit0。 */
        unsigned int  sc_rst_src_clr  : 1;  /* bit[30]   : 复位源信息清除控制：
                                                           0：写0无效果；
                                                           1：复位源信息清除，并关闭复位源记录功能。 */
        unsigned int  sc_pmurst_ctrl  : 1;  /* bit[31]   : PMU复位清除控制：
                                                           0：写0无效果；
                                                           1：关闭PMU复位功能并且开启AP复位功能。 */
    } reg;
} SOC_SCTRL_SCPERRSTEN0_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_rtc_START       (1)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_rtc_END         (1)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_rtc1_START      (2)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_rtc1_END        (2)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer0_START    (3)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer0_END      (3)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer2_START    (5)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer2_END      (5)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer3_START    (6)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_timer3_END      (6)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_cfg_START      (7)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_cfg_END        (7)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_dw_axi_START   (8)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_dw_axi_END     (8)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_x2h_START      (9)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_x2h_END        (9)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_h2p_START      (10)
#define SOC_SCTRL_SCPERRSTEN0_rst_asp_h2p_END        (10)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio0_START  (11)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio0_END    (11)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio1_START  (12)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio1_END    (12)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio2_START  (13)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio2_END    (13)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio3_START  (14)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio3_END    (14)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio4_START  (15)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio4_END    (15)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio5_START  (16)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_gpio5_END    (16)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_ioc_START    (18)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_ao_ioc_END      (18)
#define SOC_SCTRL_SCPERRSTEN0_ip_prst_syscnt_START   (19)
#define SOC_SCTRL_SCPERRSTEN0_ip_prst_syscnt_END     (19)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_syscnt_START    (20)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_syscnt_END      (20)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_sci0_START      (23)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_sci0_END        (23)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_sci1_START      (24)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_sci1_END        (24)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_bbpdrx_START    (27)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_bbpdrx_END      (27)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_aobus_START     (29)
#define SOC_SCTRL_SCPERRSTEN0_ip_rst_aobus_END       (29)
#define SOC_SCTRL_SCPERRSTEN0_sc_rst_src_clr_START   (30)
#define SOC_SCTRL_SCPERRSTEN0_sc_rst_src_clr_END     (30)
#define SOC_SCTRL_SCPERRSTEN0_sc_pmurst_ctrl_START   (31)
#define SOC_SCTRL_SCPERRSTEN0_sc_pmurst_ctrl_END     (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTDIS0_UNION
 结构说明  : SCPERRSTDIS0 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]    : IP软复位撤离：
                                                           0：IP软复位使能状态不变；
                                                           1：IP软复位撤离。 */
        unsigned int  ip_rst_rtc      : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  ip_rst_rtc1     : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  ip_rst_timer0   : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  reserved_1      : 1;  /* bit[4]    : 含义同bit0。 */
        unsigned int  ip_rst_timer2   : 1;  /* bit[5]    : 含义同bit0。 */
        unsigned int  ip_rst_timer3   : 1;  /* bit[6]    : 含义同bit0。 */
        unsigned int  rst_asp_cfg     : 1;  /* bit[7]    : 含义同bit0。 */
        unsigned int  rst_asp_dw_axi  : 1;  /* bit[8]    : 含义同bit0。 */
        unsigned int  rst_asp_x2h     : 1;  /* bit[9]    : 含义同bit0。 */
        unsigned int  rst_asp_h2p     : 1;  /* bit[10]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio0 : 1;  /* bit[11]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio1 : 1;  /* bit[12]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio2 : 1;  /* bit[13]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio3 : 1;  /* bit[14]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio4 : 1;  /* bit[15]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio5 : 1;  /* bit[16]   : 含义同bit0。 */
        unsigned int  reserved_2      : 1;  /* bit[17]   : 保留。 */
        unsigned int  ip_rst_ao_ioc   : 1;  /* bit[18]   : 含义同bit0。 */
        unsigned int  ip_prst_syscnt  : 1;  /* bit[19]   : 含义同bit0。 */
        unsigned int  ip_rst_syscnt   : 1;  /* bit[20]   : 含义同bit0。 */
        unsigned int  reserved_3      : 2;  /* bit[21-22]: 保留。 */
        unsigned int  ip_rst_sci0     : 1;  /* bit[23]   : 含义同bit0。 */
        unsigned int  ip_rst_sci1     : 1;  /* bit[24]   : 含义同bit0。 */
        unsigned int  reserved_4      : 1;  /* bit[25]   : 保留。 */
        unsigned int  reserved_5      : 1;  /* bit[26]   : 含义同bit0。 */
        unsigned int  ip_rst_bbpdrx   : 1;  /* bit[27]   : 含义同bit0。 */
        unsigned int  reserved_6      : 1;  /* bit[28]   : 保留。 */
        unsigned int  ip_rst_aobus    : 1;  /* bit[29]   : 含义同bit0。 */
        unsigned int  sc_rst_src_clr  : 1;  /* bit[30]   : 复位源清除信号控制：
                                                           0：写0无效果；
                                                           1：复位源清除撤销，即复位源记录功能启用。 */
        unsigned int  sc_pmurst_ctrl  : 1;  /* bit[31]   : PMU复位功能控制：
                                                           0：写0无效果；
                                                           1：开启PMU复位功能并且关闭AP复位功能。 */
    } reg;
} SOC_SCTRL_SCPERRSTDIS0_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_rtc_START       (1)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_rtc_END         (1)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_rtc1_START      (2)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_rtc1_END        (2)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer0_START    (3)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer0_END      (3)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer2_START    (5)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer2_END      (5)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer3_START    (6)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_timer3_END      (6)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_cfg_START      (7)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_cfg_END        (7)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_dw_axi_START   (8)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_dw_axi_END     (8)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_x2h_START      (9)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_x2h_END        (9)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_h2p_START      (10)
#define SOC_SCTRL_SCPERRSTDIS0_rst_asp_h2p_END        (10)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio0_START  (11)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio0_END    (11)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio1_START  (12)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio1_END    (12)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio2_START  (13)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio2_END    (13)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio3_START  (14)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio3_END    (14)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio4_START  (15)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio4_END    (15)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio5_START  (16)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_gpio5_END    (16)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_ioc_START    (18)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_ao_ioc_END      (18)
#define SOC_SCTRL_SCPERRSTDIS0_ip_prst_syscnt_START   (19)
#define SOC_SCTRL_SCPERRSTDIS0_ip_prst_syscnt_END     (19)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_syscnt_START    (20)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_syscnt_END      (20)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_sci0_START      (23)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_sci0_END        (23)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_sci1_START      (24)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_sci1_END        (24)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_bbpdrx_START    (27)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_bbpdrx_END      (27)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_aobus_START     (29)
#define SOC_SCTRL_SCPERRSTDIS0_ip_rst_aobus_END       (29)
#define SOC_SCTRL_SCPERRSTDIS0_sc_rst_src_clr_START   (30)
#define SOC_SCTRL_SCPERRSTDIS0_sc_rst_src_clr_END     (30)
#define SOC_SCTRL_SCPERRSTDIS0_sc_pmurst_ctrl_START   (31)
#define SOC_SCTRL_SCPERRSTDIS0_sc_pmurst_ctrl_END     (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTSTAT0_UNION
 结构说明  : SCPERRSTSTAT0 寄存器结构定义。地址偏移量:0x088，初值:0x04000780，宽度:32
 寄存器说明: 外设软复位状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]    : 外设软复位使能状态：
                                                           0：IP软复位使能撤销；
                                                           1：IP软复位使能；
                                                           此peri_rst_ctrl[0]由安全区SCPERRSTSTAT0_SEC.ip_rst_ao_cc控制输出。 */
        unsigned int  ip_rst_rtc      : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  ip_rst_rtc1     : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  ip_rst_timer0   : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  reserved_1      : 1;  /* bit[4]    : 含义同bit0。 */
        unsigned int  ip_rst_timer2   : 1;  /* bit[5]    : 含义同bit0。 */
        unsigned int  ip_rst_timer3   : 1;  /* bit[6]    : 含义同bit0。 */
        unsigned int  rst_asp_cfg     : 1;  /* bit[7]    : 含义同bit0。 */
        unsigned int  rst_asp_dw_axi  : 1;  /* bit[8]    : 含义同bit0。 */
        unsigned int  rst_asp_x2h     : 1;  /* bit[9]    : 含义同bit0。 */
        unsigned int  rst_asp_h2p     : 1;  /* bit[10]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio0 : 1;  /* bit[11]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio1 : 1;  /* bit[12]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio2 : 1;  /* bit[13]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio3 : 1;  /* bit[14]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio4 : 1;  /* bit[15]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_gpio5 : 1;  /* bit[16]   : 含义同bit0。 */
        unsigned int  reserved_2      : 1;  /* bit[17]   : 保留。 */
        unsigned int  ip_rst_ao_ioc   : 1;  /* bit[18]   : 含义同bit0。 */
        unsigned int  ip_prst_syscnt  : 1;  /* bit[19]   : 含义同bit0。 */
        unsigned int  ip_rst_syscnt   : 1;  /* bit[20]   : 含义同bit0。 */
        unsigned int  reserved_3      : 2;  /* bit[21-22]: 保留。 */
        unsigned int  ip_rst_sci0     : 1;  /* bit[23]   : 含义同bit0。 */
        unsigned int  ip_rst_sci1     : 1;  /* bit[24]   : 含义同bit0。 */
        unsigned int  reserved_4      : 1;  /* bit[25]   : 保留。 */
        unsigned int  reserved_5      : 1;  /* bit[26]   : 含义同bit0。 */
        unsigned int  ip_rst_bbpdrx   : 1;  /* bit[27]   : 含义同bit0。 */
        unsigned int  reserved_6      : 1;  /* bit[28]   : 保留。 */
        unsigned int  ip_rst_aobus    : 1;  /* bit[29]   : 含义同bit0。 */
        unsigned int  sc_rst_src_clr  : 1;  /* bit[30]   : 复位源清除控制状态：
                                                           0：保留复位源记录功能；
                                                           1：清除复位源记录功能；
                                                           此bit配置为1后需要再配置为0。 */
        unsigned int  sc_pmurst_ctrl  : 1;  /* bit[31]   : PMU复位功能控制状态：
                                                           0：开启PMU复位功能并且禁用AP复位功能；
                                                           1：禁用PMU复位功能并且开启AP复位功能。 */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT0_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_rtc_START       (1)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_rtc_END         (1)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_rtc1_START      (2)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_rtc1_END        (2)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer0_START    (3)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer0_END      (3)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer2_START    (5)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer2_END      (5)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer3_START    (6)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_timer3_END      (6)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_cfg_START      (7)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_cfg_END        (7)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_dw_axi_START   (8)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_dw_axi_END     (8)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_x2h_START      (9)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_x2h_END        (9)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_h2p_START      (10)
#define SOC_SCTRL_SCPERRSTSTAT0_rst_asp_h2p_END        (10)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio0_START  (11)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio0_END    (11)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio1_START  (12)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio1_END    (12)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio2_START  (13)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio2_END    (13)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio3_START  (14)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio3_END    (14)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio4_START  (15)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio4_END    (15)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio5_START  (16)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_gpio5_END    (16)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_ioc_START    (18)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_ao_ioc_END      (18)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_prst_syscnt_START   (19)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_prst_syscnt_END     (19)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_syscnt_START    (20)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_syscnt_END      (20)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_sci0_START      (23)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_sci0_END        (23)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_sci1_START      (24)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_sci1_END        (24)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_bbpdrx_START    (27)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_bbpdrx_END      (27)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_aobus_START     (29)
#define SOC_SCTRL_SCPERRSTSTAT0_ip_rst_aobus_END       (29)
#define SOC_SCTRL_SCPERRSTSTAT0_sc_rst_src_clr_START   (30)
#define SOC_SCTRL_SCPERRSTSTAT0_sc_rst_src_clr_END     (30)
#define SOC_SCTRL_SCPERRSTSTAT0_sc_pmurst_ctrl_START   (31)
#define SOC_SCTRL_SCPERRSTSTAT0_sc_pmurst_ctrl_END     (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTEN1_UNION
 结构说明  : SCPERRSTEN1 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0]    : IP软复位使能：
                                                                   0：IP软复位使能状态不变；
                                                                   1：IP软复位使能。 */
        unsigned int  reserved_1              : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  reserved_2              : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  ip_rst_timer4           : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  ip_rst_timer5           : 1;  /* bit[4]    : 含义同bit0。 */
        unsigned int  ip_rst_timer6           : 1;  /* bit[5]    : 含义同bit0。 */
        unsigned int  ip_rst_timer7           : 1;  /* bit[6]    : 含义同bit0。 */
        unsigned int  ip_rst_timer8           : 1;  /* bit[7]    : 含义同bit0。 */
        unsigned int  ip_rst_aobus_noc        : 1;  /* bit[8]    : 含义同bit0。 */
        unsigned int  reserved_3              : 1;  /* bit[9]    : 含义同bit0。 */
        unsigned int  reserved_4              : 1;  /* bit[10]   : 含义同bit0。 */
        unsigned int  ip_rst_mmbuf            : 1;  /* bit[11]   : 含义同bit0。 */
        unsigned int  ip_rst_mmbufcfg         : 1;  /* bit[12]   : 含义同bit0。 */
        unsigned int  ip_rst_autodiv_aobusnoc : 1;  /* bit[13]   : 含义同bit0。 */
        unsigned int  reserved_5              : 2;  /* bit[14-15]: 含义同bit0。 */
        unsigned int  ip_rst_dram_tmp_0       : 2;  /* bit[16-17]: dram复位配置
                                                                   0：无操作
                                                                   1：对SCPERRSTSTAT1.ip_rst_dram_tmp_0对应bit置1。 */
        unsigned int  reserved_6              : 14; /* bit[18-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTEN1_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer4_START            (3)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer4_END              (3)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer5_START            (4)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer5_END              (4)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer6_START            (5)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer6_END              (5)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer7_START            (6)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer7_END              (6)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer8_START            (7)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_timer8_END              (7)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_aobus_noc_START         (8)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_aobus_noc_END           (8)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_mmbuf_START             (11)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_mmbuf_END               (11)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_mmbufcfg_START          (12)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_mmbufcfg_END            (12)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_autodiv_aobusnoc_START  (13)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_autodiv_aobusnoc_END    (13)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_dram_tmp_0_START        (16)
#define SOC_SCTRL_SCPERRSTEN1_ip_rst_dram_tmp_0_END          (17)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTDIS1_UNION
 结构说明  : SCPERRSTDIS1 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0]    : IP软复位撤离：
                                                                   0：IP软复位使能状态不变；
                                                                   1：IP软复位撤离。 */
        unsigned int  reserved_1              : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  reserved_2              : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  ip_rst_timer4           : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  ip_rst_timer5           : 1;  /* bit[4]    : 含义同bit0。 */
        unsigned int  ip_rst_timer6           : 1;  /* bit[5]    : 含义同bit0。 */
        unsigned int  ip_rst_timer7           : 1;  /* bit[6]    : 含义同bit0。 */
        unsigned int  ip_rst_timer8           : 1;  /* bit[7]    : 含义同bit0。 */
        unsigned int  ip_rst_aobus_noc        : 1;  /* bit[8]    : 含义同bit0。 */
        unsigned int  reserved_3              : 1;  /* bit[9]    : 含义同bit0。 */
        unsigned int  reserved_4              : 1;  /* bit[10]   : 含义同bit0。 */
        unsigned int  ip_rst_mmbuf            : 1;  /* bit[11]   : 含义同bit0。 */
        unsigned int  ip_rst_mmbufcfg         : 1;  /* bit[12]   : 含义同bit0。 */
        unsigned int  ip_rst_autodiv_aobusnoc : 1;  /* bit[13]   : 含义同bit0。 */
        unsigned int  reserved_5              : 2;  /* bit[14-15]: 含义同bit0。 */
        unsigned int  ip_rst_dram_tmp_0       : 2;  /* bit[16-17]: dram复位配置
                                                                   0：无操作
                                                                   1：对SCPERRSTSTAT1.ip_rst_dram_tmp_0对应bit清0。 */
        unsigned int  reserved_6              : 14; /* bit[18-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTDIS1_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer4_START            (3)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer4_END              (3)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer5_START            (4)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer5_END              (4)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer6_START            (5)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer6_END              (5)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer7_START            (6)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer7_END              (6)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer8_START            (7)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_timer8_END              (7)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_aobus_noc_START         (8)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_aobus_noc_END           (8)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_mmbuf_START             (11)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_mmbuf_END               (11)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_mmbufcfg_START          (12)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_mmbufcfg_END            (12)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_autodiv_aobusnoc_START  (13)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_autodiv_aobusnoc_END    (13)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_dram_tmp_0_START        (16)
#define SOC_SCTRL_SCPERRSTDIS1_ip_rst_dram_tmp_0_END          (17)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTSTAT1_UNION
 结构说明  : SCPERRSTSTAT1 寄存器结构定义。地址偏移量:0x094，初值:0x00001805，宽度:32
 寄存器说明: 外设软复位状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0]    : IP软复位撤离：
                                                                   0：IP软复位使能撤销；
                                                                   1：IP软复位使能。 */
        unsigned int  reserved_1              : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  reserved_2              : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  ip_rst_timer4           : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  ip_rst_timer5           : 1;  /* bit[4]    : 含义同bit0。 */
        unsigned int  ip_rst_timer6           : 1;  /* bit[5]    : 含义同bit0。 */
        unsigned int  ip_rst_timer7           : 1;  /* bit[6]    : 含义同bit0。 */
        unsigned int  ip_rst_timer8           : 1;  /* bit[7]    : 含义同bit0。 */
        unsigned int  ip_rst_aobus_noc        : 1;  /* bit[8]    : 含义同bit0。 */
        unsigned int  reserved_3              : 1;  /* bit[9]    : 含义同bit0。 */
        unsigned int  reserved_4              : 1;  /* bit[10]   : 含义同bit0。 */
        unsigned int  ip_rst_mmbuf            : 1;  /* bit[11]   : 含义同bit0。 */
        unsigned int  ip_rst_mmbufcfg         : 1;  /* bit[12]   : 含义同bit0。 */
        unsigned int  ip_rst_autodiv_aobusnoc : 1;  /* bit[13]   : 含义同bit0。 */
        unsigned int  reserved_5              : 2;  /* bit[14-15]: 含义同bit0。 */
        unsigned int  ip_rst_dram_tmp_0       : 2;  /* bit[16-17]: dram复位状态0
                                                                   01：dram复位条件0满足
                                                                   其他：dram不复位
                                                                   仅当softrst_dram_dis=1'b1时，SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01且SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01同时满足时，对dram进行软复位，
                                                                   当softrst_dram_dis=1'b1时，SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01且SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01不满足时，对dram进行软件解复位。 */
        unsigned int  reserved_6              : 14; /* bit[18-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT1_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer4_START            (3)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer4_END              (3)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer5_START            (4)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer5_END              (4)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer6_START            (5)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer6_END              (5)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer7_START            (6)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer7_END              (6)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer8_START            (7)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_timer8_END              (7)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_aobus_noc_START         (8)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_aobus_noc_END           (8)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_mmbuf_START             (11)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_mmbuf_END               (11)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_mmbufcfg_START          (12)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_mmbufcfg_END            (12)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_autodiv_aobusnoc_START  (13)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_autodiv_aobusnoc_END    (13)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_dram_tmp_0_START        (16)
#define SOC_SCTRL_SCPERRSTSTAT1_ip_rst_dram_tmp_0_END          (17)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTEN2_UNION
 结构说明  : SCPERRSTEN2 寄存器结构定义。地址偏移量:0x098，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]   : 
                                                            IP软复位使能：
                                                            0：IP软复位使能状态不变；
                                                            1：IP软复位使能。 */
        unsigned int  reserved_1        : 1;  /* bit[1]   : 含义同bit0。 */
        unsigned int  reserved_2        : 1;  /* bit[2]   : 含义同bit0。 */
        unsigned int  reserved_3        : 1;  /* bit[3]   : 含义同bit0。 */
        unsigned int  softrst_dram_dis  : 1;  /* bit[4]   : dram复位配置使能
                                                            0：无操作
                                                            1：对SCPERRSTSTAT2.softrst_dram_dis对应bit置1。 */
        unsigned int  ip_rst_dram_tmp_1 : 2;  /* bit[5-6] : dram复位配置
                                                            0：无操作
                                                            1：对SCPERRSTSTAT2.ip_rst_dram_tmp_0对应bit置1。 */
        unsigned int  reserved_4        : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTEN2_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN2_softrst_dram_dis_START   (4)
#define SOC_SCTRL_SCPERRSTEN2_softrst_dram_dis_END     (4)
#define SOC_SCTRL_SCPERRSTEN2_ip_rst_dram_tmp_1_START  (5)
#define SOC_SCTRL_SCPERRSTEN2_ip_rst_dram_tmp_1_END    (6)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTDIS2_UNION
 结构说明  : SCPERRSTDIS2 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]   : IP软复位使能：
                                                            0：IP软复位使能状态不变；
                                                            1：IP软复位使能。 */
        unsigned int  reserved_1        : 1;  /* bit[1]   : 含义同bit0。 */
        unsigned int  reserved_2        : 1;  /* bit[2]   : 含义同bit0。 */
        unsigned int  reserved_3        : 1;  /* bit[3]   : 含义同bit0。 */
        unsigned int  softrst_dram_dis  : 1;  /* bit[4]   : dram复位配置使能
                                                            0：无操作
                                                            1：对SCPERRSTSTAT2.softrst_dram_dis对应bit清0。 */
        unsigned int  ip_rst_dram_tmp_1 : 2;  /* bit[5-6] : dram复位配置
                                                            0：无操作
                                                            1：对SCPERRSTSTAT2.ip_rst_dram_tmp_0对应bit清0。 */
        unsigned int  reserved_4        : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTDIS2_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS2_softrst_dram_dis_START   (4)
#define SOC_SCTRL_SCPERRSTDIS2_softrst_dram_dis_END     (4)
#define SOC_SCTRL_SCPERRSTDIS2_ip_rst_dram_tmp_1_START  (5)
#define SOC_SCTRL_SCPERRSTDIS2_ip_rst_dram_tmp_1_END    (6)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTSTAT2_UNION
 结构说明  : SCPERRSTSTAT2 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]   : 信号端口由安全区SCPERRSTSTAT1_SEC.ip_rst_asp_subsys控制
                                                            0：IP软复位使能撤销；
                                                            1：IP软复位使能。 */
        unsigned int  reserved_1        : 1;  /* bit[1]   : 信号端口由安全区SCPERRSTSTAT2_SEC.ip_rst_iomcu控制
                                                            外设软复位使能状态。 */
        unsigned int  reserved_2        : 1;  /* bit[2]   : 信号端口由安全区SCPERRSTSTAT0_SEC.ip_rst_asc控制
                                                            外设软复位使能状态。 */
        unsigned int  reserved_3        : 1;  /* bit[3]   : 含义同bit0。 */
        unsigned int  softrst_dram_dis  : 1;  /* bit[4]   : dram复位配置使能
                                                            0：dram软复位功能状态保持操作
                                                            1：dram软复位功能可修改，仅当softrst_dram_dis=1'b1时，SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01且SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01同时满足时，对dram进行软复位，
                                                            当softrst_dram_dis=1'b1时，SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01且SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01不满足时，对dram进行软件解复位。 */
        unsigned int  ip_rst_dram_tmp_1 : 2;  /* bit[5-6] : dram复位状态1
                                                            01：dram复位条件1满足
                                                            其他：dram不复位
                                                            仅当softrst_dram_dis=1'b1时，SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01且SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01同时满足时，对dram进行软复位，
                                                            当softrst_dram_dis=1'b1时，SCPERRSTSTAT2.ip_rst_dram_tmp_0=2'b01且SCPERRSTSTAT2.ip_rst_dram_tmp_1=2'b01不满足时，对dram进行软件解复位。 */
        unsigned int  reserved_4        : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT2_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT2_softrst_dram_dis_START   (4)
#define SOC_SCTRL_SCPERRSTSTAT2_softrst_dram_dis_END     (4)
#define SOC_SCTRL_SCPERRSTSTAT2_ip_rst_dram_tmp_1_START  (5)
#define SOC_SCTRL_SCPERRSTSTAT2_ip_rst_dram_tmp_1_END    (6)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIPCLKRSTBUS_UNION
 结构说明  : SCIPCLKRSTBUS 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: IP防总线挂死控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_gt_rtc_bypass    : 1;  /* bit[0]    : 总线防挂死功能bypass
                                                                0:使能复位&时钟门控防总线挂死功能
                                                                1:BYPASS复位&时钟门控防总线挂死功能。 */
        unsigned int  rst_gt_rtc1_bypass   : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  rst_gt_timer0_bypass : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  rst_gt_timer1_bypass : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  rst_gt_timer2_bypass : 1;  /* bit[4]    : 含义同bit0。 */
        unsigned int  rst_gt_timer3_bypass : 1;  /* bit[5]    : 含义同bit0。 */
        unsigned int  rst_gt_gpio0_bypass  : 1;  /* bit[6]    : 含义同bit0。 */
        unsigned int  rst_gt_gpio1_bypass  : 1;  /* bit[7]    : 含义同bit0。 */
        unsigned int  rst_gt_gpio2_bypass  : 1;  /* bit[8]    : 含义同bit0。 */
        unsigned int  rst_gt_gpio3_bypass  : 1;  /* bit[9]    : 含义同bit0。 */
        unsigned int  rst_gt_gpio4_bypass  : 1;  /* bit[10]   : 含义同bit0。 */
        unsigned int  rst_gt_gpio5_bypass  : 1;  /* bit[11]   : 含义同bit0。 */
        unsigned int  rst_gt_ioc_bypass    : 1;  /* bit[12]   : 含义同bit0。 */
        unsigned int  rst_gt_syscnt_bypass : 1;  /* bit[13]   : 含义同bit0。 */
        unsigned int  rst_gt_sci0_bypass   : 1;  /* bit[14]   : 含义同bit0。 */
        unsigned int  rst_gt_sci1_bypass   : 1;  /* bit[15]   : 含义同bit0。 */
        unsigned int  rst_gt_bbpdrx_bypass : 1;  /* bit[16]   : 含义同bit0。 */
        unsigned int  rst_gt_efusec_bypass : 1;  /* bit[17]   : 含义同bit0。 */
        unsigned int  rst_gt_timer4_bypass : 1;  /* bit[18]   : 含义同bit0。 */
        unsigned int  rst_gt_timer5_bypass : 1;  /* bit[19]   : 含义同bit0。 */
        unsigned int  rst_gt_timer6_bypass : 1;  /* bit[20]   : 含义同bit0。 */
        unsigned int  rst_gt_timer7_bypass : 1;  /* bit[21]   : 含义同bit0。 */
        unsigned int  rst_gt_timer8_bypass : 1;  /* bit[22]   : 含义同bit0。 */
        unsigned int  rst_gt_mmbuf_bypass  : 1;  /* bit[23]   : 含义同bit0。 */
        unsigned int  rst_gt_asc_bypass    : 1;  /* bit[24]   : 含义同bit0。 */
        unsigned int  reserved             : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCIPCLKRSTBUS_UNION;
#endif
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_rtc_bypass_START     (0)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_rtc_bypass_END       (0)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_rtc1_bypass_START    (1)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_rtc1_bypass_END      (1)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer0_bypass_START  (2)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer0_bypass_END    (2)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer1_bypass_START  (3)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer1_bypass_END    (3)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer2_bypass_START  (4)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer2_bypass_END    (4)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer3_bypass_START  (5)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer3_bypass_END    (5)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio0_bypass_START   (6)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio0_bypass_END     (6)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio1_bypass_START   (7)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio1_bypass_END     (7)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio2_bypass_START   (8)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio2_bypass_END     (8)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio3_bypass_START   (9)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio3_bypass_END     (9)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio4_bypass_START   (10)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio4_bypass_END     (10)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio5_bypass_START   (11)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_gpio5_bypass_END     (11)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_ioc_bypass_START     (12)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_ioc_bypass_END       (12)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_syscnt_bypass_START  (13)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_syscnt_bypass_END    (13)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_sci0_bypass_START    (14)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_sci0_bypass_END      (14)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_sci1_bypass_START    (15)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_sci1_bypass_END      (15)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_bbpdrx_bypass_START  (16)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_bbpdrx_bypass_END    (16)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_efusec_bypass_START  (17)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_efusec_bypass_END    (17)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer4_bypass_START  (18)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer4_bypass_END    (18)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer5_bypass_START  (19)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer5_bypass_END    (19)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer6_bypass_START  (20)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer6_bypass_END    (20)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer7_bypass_START  (21)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer7_bypass_END    (21)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer8_bypass_START  (22)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_timer8_bypass_END    (22)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_mmbuf_bypass_START   (23)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_mmbuf_bypass_END     (23)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_asc_bypass_START     (24)
#define SOC_SCTRL_SCIPCLKRSTBUS_rst_gt_asc_bypass_END       (24)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCISOEN_UNION
 结构说明  : SCISOEN 寄存器结构定义。地址偏移量:0x0C0，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统ISO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audioisoen    : 1;  /* bit[0]   : Audio子系统ISO单元使能控制：写1执行ISO使能操作，写0无效。 */
        unsigned int  iomcuisoen    : 1;  /* bit[1]   : IOMCU子系统ISO单元使能控制：写1执行ISO使能操作，写0无效。 */
        unsigned int  debugsubisoen : 1;  /* bit[2]   : Debug子系统ISO单元使能控制：写1执行ISO使能操作，写0无效。 */
        unsigned int  mmbufisoen    : 1;  /* bit[3]   : MMBUF子系统ISO单元使能控制：写1执行ISO使能操作，写0无效。 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCISOEN_UNION;
#endif
#define SOC_SCTRL_SCISOEN_audioisoen_START     (0)
#define SOC_SCTRL_SCISOEN_audioisoen_END       (0)
#define SOC_SCTRL_SCISOEN_iomcuisoen_START     (1)
#define SOC_SCTRL_SCISOEN_iomcuisoen_END       (1)
#define SOC_SCTRL_SCISOEN_debugsubisoen_START  (2)
#define SOC_SCTRL_SCISOEN_debugsubisoen_END    (2)
#define SOC_SCTRL_SCISOEN_mmbufisoen_START     (3)
#define SOC_SCTRL_SCISOEN_mmbufisoen_END       (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCISODIS_UNION
 结构说明  : SCISODIS 寄存器结构定义。地址偏移量:0x0C4，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统ISO使能撤销寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audioisoen    : 1;  /* bit[0]   : Audio子系统ISO单元使能控制：写1执行ISO撤销操作，写0无效。 */
        unsigned int  iomcuisoen    : 1;  /* bit[1]   : IOMCU子系统ISO单元使能控制：写1执行ISO撤消操作，写0无效。 */
        unsigned int  debugsubisoen : 1;  /* bit[2]   : Debug子系统ISO单元使能控制：写1执行ISO撤消操作，写0无效。 */
        unsigned int  mmbufisoen    : 1;  /* bit[3]   : MMBUF子系统ISO单元使能控制：写1执行ISO撤消操作，写0无效。 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCISODIS_UNION;
#endif
#define SOC_SCTRL_SCISODIS_audioisoen_START     (0)
#define SOC_SCTRL_SCISODIS_audioisoen_END       (0)
#define SOC_SCTRL_SCISODIS_iomcuisoen_START     (1)
#define SOC_SCTRL_SCISODIS_iomcuisoen_END       (1)
#define SOC_SCTRL_SCISODIS_debugsubisoen_START  (2)
#define SOC_SCTRL_SCISODIS_debugsubisoen_END    (2)
#define SOC_SCTRL_SCISODIS_mmbufisoen_START     (3)
#define SOC_SCTRL_SCISODIS_mmbufisoen_END       (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCISOSTAT_UNION
 结构说明  : SCISOSTAT 寄存器结构定义。地址偏移量:0x0C8，初值:0x0000000B，宽度:32
 寄存器说明: 掉电子系统ISO使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audioisoen    : 1;  /* bit[0]   : Audio子系统ISO单元使能控制：1--ISO使能。 */
        unsigned int  iomcuisoen    : 1;  /* bit[1]   : IOMCU子系统ISO单元使能控制：1--ISO使能。 */
        unsigned int  debugsubisoen : 1;  /* bit[2]   : Debug子系统ISO单元使能控制：1--ISO使能。 */
        unsigned int  mmbufisoen    : 1;  /* bit[3]   : MMBUF子系统ISO单元使能控制：1--ISO使能。 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCISOSTAT_UNION;
#endif
#define SOC_SCTRL_SCISOSTAT_audioisoen_START     (0)
#define SOC_SCTRL_SCISOSTAT_audioisoen_END       (0)
#define SOC_SCTRL_SCISOSTAT_iomcuisoen_START     (1)
#define SOC_SCTRL_SCISOSTAT_iomcuisoen_END       (1)
#define SOC_SCTRL_SCISOSTAT_debugsubisoen_START  (2)
#define SOC_SCTRL_SCISOSTAT_debugsubisoen_END    (2)
#define SOC_SCTRL_SCISOSTAT_mmbufisoen_START     (3)
#define SOC_SCTRL_SCISOSTAT_mmbufisoen_END       (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPWREN_UNION
 结构说明  : SCPWREN 寄存器结构定义。地址偏移量:0x0D0，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统电源使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audiopwren    : 1;  /* bit[0]   : AUDIO子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  iomcupwren    : 1;  /* bit[1]   : IOMCU子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  debugsubpwren : 1;  /* bit[2]   : Debug子系统电源单元使能控制：写1执行电源使能操作，写0无效。 */
        unsigned int  mmbufpwren    : 1;  /* bit[3]   : MMBUF子系统电源单元使能控制：写1执行电源使能操作，写0无效。 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPWREN_UNION;
#endif
#define SOC_SCTRL_SCPWREN_audiopwren_START     (0)
#define SOC_SCTRL_SCPWREN_audiopwren_END       (0)
#define SOC_SCTRL_SCPWREN_iomcupwren_START     (1)
#define SOC_SCTRL_SCPWREN_iomcupwren_END       (1)
#define SOC_SCTRL_SCPWREN_debugsubpwren_START  (2)
#define SOC_SCTRL_SCPWREN_debugsubpwren_END    (2)
#define SOC_SCTRL_SCPWREN_mmbufpwren_START     (3)
#define SOC_SCTRL_SCPWREN_mmbufpwren_END       (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPWRDIS_UNION
 结构说明  : SCPWRDIS 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统电源使能撤销寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audiopwren    : 1;  /* bit[0]   : AUDIO子系统电源使能撤销控制：写1执行电源使能撤销操作。 */
        unsigned int  iomcupwren    : 1;  /* bit[1]   : IOMCU子系统电源使能控制：写1执行电源撤销操作。 */
        unsigned int  debugsubpwren : 1;  /* bit[2]   : Debug子系统电源单元使能控制：写1执行电源撤消操作，写0无效。 */
        unsigned int  mmbufpwren    : 1;  /* bit[3]   : MMBUF子系统电源单元使能控制：写1执行电源撤消操作，写0无效。 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPWRDIS_UNION;
#endif
#define SOC_SCTRL_SCPWRDIS_audiopwren_START     (0)
#define SOC_SCTRL_SCPWRDIS_audiopwren_END       (0)
#define SOC_SCTRL_SCPWRDIS_iomcupwren_START     (1)
#define SOC_SCTRL_SCPWRDIS_iomcupwren_END       (1)
#define SOC_SCTRL_SCPWRDIS_debugsubpwren_START  (2)
#define SOC_SCTRL_SCPWRDIS_debugsubpwren_END    (2)
#define SOC_SCTRL_SCPWRDIS_mmbufpwren_START     (3)
#define SOC_SCTRL_SCPWRDIS_mmbufpwren_END       (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPWRSTAT_UNION
 结构说明  : SCPWRSTAT 寄存器结构定义。地址偏移量:0x0D8，初值:0x00000004，宽度:32
 寄存器说明: 掉电子系统电源使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audiopwrstat    : 1;  /* bit[0]   : AUDIO子系统电源使能状态：
                                                          0：AUDIO子系统电源使能撤销；
                                                          1：AUDIO子系统电源使能。 */
        unsigned int  iomcupwrstat    : 1;  /* bit[1]   : IOMCU子系统电源使能状态：
                                                          0：IOMCU子系统电源使能撤销；
                                                          1：IOMCU子系统电源使能。 */
        unsigned int  debugsubpwrstat : 1;  /* bit[2]   : Debug子系统电源单元使能控制状态：
                                                          0--电源关闭
                                                          1--电源使能。 */
        unsigned int  mmbufpwrstat    : 1;  /* bit[3]   : MMBUF子系统电源单元使能控制状态：
                                                          0--电源关闭
                                                          1--电源使能。 */
        unsigned int  reserved        : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPWRSTAT_UNION;
#endif
#define SOC_SCTRL_SCPWRSTAT_audiopwrstat_START     (0)
#define SOC_SCTRL_SCPWRSTAT_audiopwrstat_END       (0)
#define SOC_SCTRL_SCPWRSTAT_iomcupwrstat_START     (1)
#define SOC_SCTRL_SCPWRSTAT_iomcupwrstat_END       (1)
#define SOC_SCTRL_SCPWRSTAT_debugsubpwrstat_START  (2)
#define SOC_SCTRL_SCPWRSTAT_debugsubpwrstat_END    (2)
#define SOC_SCTRL_SCPWRSTAT_mmbufpwrstat_START     (3)
#define SOC_SCTRL_SCPWRSTAT_mmbufpwrstat_END       (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPWRACK_UNION
 结构说明  : SCPWRACK 寄存器结构定义。地址偏移量:0x0DC，初值:0x00000004，宽度:32
 寄存器说明: 掉电子系统最终电源状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  audiopwrack    : 1;  /* bit[0]   : AUDIO子系统电源反馈状态：
                                                         0：AUDIO子系统电源切断状态；
                                                         1：AUDIO子系统电源供给状态。 */
        unsigned int  reserved_0     : 1;  /* bit[1]   : 因NL此bit被优化问题，修改到在m7_sc_stat[1]体现
                                                         IOMCU子系统电源电源反馈状态：
                                                         0：IOMCU子系统电源使能撤销；
                                                         1：IOMCU子系统电源使能。 */
        unsigned int  debugsubpwrack : 1;  /* bit[2]   : Debug子系统电源单元电源反馈状态：
                                                         0--电源关闭
                                                         1--电源使能。 */
        unsigned int  mmbufpwrack    : 1;  /* bit[3]   : MMBUF子系统电源单元电源反馈状态：
                                                         0--电源关闭
                                                         1--电源使能。 */
        unsigned int  reserved_1     : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPWRACK_UNION;
#endif
#define SOC_SCTRL_SCPWRACK_audiopwrack_START     (0)
#define SOC_SCTRL_SCPWRACK_audiopwrack_END       (0)
#define SOC_SCTRL_SCPWRACK_debugsubpwrack_START  (2)
#define SOC_SCTRL_SCPWRACK_debugsubpwrack_END    (2)
#define SOC_SCTRL_SCPWRACK_mmbufpwrack_START     (3)
#define SOC_SCTRL_SCPWRACK_mmbufpwrack_END       (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERPWRDOWNTIME_UNION
 结构说明  : SCPERPWRDOWNTIME 寄存器结构定义。地址偏移量:0x0E0，初值:0x01FFFFEE，宽度:32
 寄存器说明: 外设区掉电时间配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_pwr_down_time  : 25; /* bit[0-24]: 指示PMU对外设区掉电所需的时间。稳定时间计算公式：（33554432-peri_pwr_down_time+3）计数时钟为32K。(下电完成时间大约为600us,默认为计数20个32K时钟周期)。 */
        unsigned int  timeout_op_rston    : 1;  /* bit[25]  : timeout operation on power FSM stats rston
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable。 */
        unsigned int  timeout_op_clkoff   : 1;  /* bit[26]  : timeout operation on power FSM stats clkoff
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable */
        unsigned int  timeout_op_eniso    : 1;  /* bit[27]  : timeout operation on power FSM stats eniso
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable。 */
        unsigned int  timeout_op_downperi : 1;  /* bit[28]  : timeout operation on power FSM stats downperi
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable。 */
        unsigned int  timeout_op_rston2   : 1;  /* bit[29]  : timeout operation on power FSM stats rston2
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable。 */
        unsigned int  timeout_op_disiso   : 1;  /* bit[30]  : timeout operation on power FSM stats disiso
                                                              1'b0:timeout operation bypass
                                                              1'b1:timeout enable。 */
        unsigned int  reserved            : 1;  /* bit[31]  : 保留。 */
    } reg;
} SOC_SCTRL_SCPERPWRDOWNTIME_UNION;
#endif
#define SOC_SCTRL_SCPERPWRDOWNTIME_peri_pwr_down_time_START   (0)
#define SOC_SCTRL_SCPERPWRDOWNTIME_peri_pwr_down_time_END     (24)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_rston_START     (25)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_rston_END       (25)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_clkoff_START    (26)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_clkoff_END      (26)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_eniso_START     (27)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_eniso_END       (27)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_downperi_START  (28)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_downperi_END    (28)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_rston2_START    (29)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_rston2_END      (29)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_disiso_START    (30)
#define SOC_SCTRL_SCPERPWRDOWNTIME_timeout_op_disiso_END      (30)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERPWRUPTIME_UNION
 结构说明  : SCPERPWRUPTIME 寄存器结构定义。地址偏移量:0x0E4，初值:0x01FFFFD8，宽度:32
 寄存器说明: 外设区上电时间配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_pwr_up_time : 25; /* bit[0-24] : 指示PMU对外设区上电所需的时间。稳定时间计算公式：（33554432-peri_pwr_up_time+3）计数时钟为32K。(上电到外设区完成大约为1.26ms默认为计数42个32K时钟周期)。 */
        unsigned int  reserved         : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERPWRUPTIME_UNION;
#endif
#define SOC_SCTRL_SCPERPWRUPTIME_peri_pwr_up_time_START  (0)
#define SOC_SCTRL_SCPERPWRUPTIME_peri_pwr_up_time_END    (24)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKDIV0_UNION
 结构说明  : SCCLKDIV0 寄存器结构定义。地址偏移量:0x100，初值:0x00000202，宽度:32
 寄存器说明: 时钟分频比控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_asp_subsys   : 3;  /* bit[0-2]  : ASP SUBSYS时钟分频比。（源时钟为PPLL0）
                                                               3'h0:1；
                                                               3'h1:2；
                                                               3'h2:3；
                                                               3'h3:4；
                                                               ……
                                                               3'h7:8。 */
        unsigned int  sc_div_hifidsp      : 6;  /* bit[3-8]  : HIFIDSP时钟分频比。
                                                               6'h0:1；
                                                               6'h1:2；
                                                               6'h2:3；
                                                               6'h3:4；
                                                               …
                                                               6'h1F:64。 */
        unsigned int  sc_div_sci          : 2;  /* bit[9-10] : SCI时钟分频比。(源时钟为clk_aobus 60MHz时钟，分频单独可配)
                                                               2'h0:1；
                                                               2'h1:2；
                                                               2'h2:3；
                                                               2'h3:4。 */
        unsigned int  sc_clk_asp_pll_sel  : 1;  /* bit[11]   : 保留。 ASP 主时钟选择FLL还是PPLL0，先用这bit吧
                                                               0:PPLL0
                                                               1:FPLL。 */
        unsigned int  sc_sel_mmbuf_backup : 1;  /* bit[12]   : MMBUF备份400MHz选择
                                                               0:PPLL0
                                                               1:备份400MHz。 */
        unsigned int  sc_sel_memrep       : 1;  /* bit[13]   : memrep时钟选择
                                                               0:19.2Mhz
                                                               1:40MHz。 */
        unsigned int  reserved            : 1;  /* bit[14]   : 保留。  */
        unsigned int  extclk_en           : 1;  /* bit[15]   : 备用时钟使能，高有效。 */
        unsigned int  scclkdiv0_msk       : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                               只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCCLKDIV0_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV0_sc_div_asp_subsys_START    (0)
#define SOC_SCTRL_SCCLKDIV0_sc_div_asp_subsys_END      (2)
#define SOC_SCTRL_SCCLKDIV0_sc_div_hifidsp_START       (3)
#define SOC_SCTRL_SCCLKDIV0_sc_div_hifidsp_END         (8)
#define SOC_SCTRL_SCCLKDIV0_sc_div_sci_START           (9)
#define SOC_SCTRL_SCCLKDIV0_sc_div_sci_END             (10)
#define SOC_SCTRL_SCCLKDIV0_sc_clk_asp_pll_sel_START   (11)
#define SOC_SCTRL_SCCLKDIV0_sc_clk_asp_pll_sel_END     (11)
#define SOC_SCTRL_SCCLKDIV0_sc_sel_mmbuf_backup_START  (12)
#define SOC_SCTRL_SCCLKDIV0_sc_sel_mmbuf_backup_END    (12)
#define SOC_SCTRL_SCCLKDIV0_sc_sel_memrep_START        (13)
#define SOC_SCTRL_SCCLKDIV0_sc_sel_memrep_END          (13)
#define SOC_SCTRL_SCCLKDIV0_extclk_en_START            (15)
#define SOC_SCTRL_SCCLKDIV0_extclk_en_END              (15)
#define SOC_SCTRL_SCCLKDIV0_scclkdiv0_msk_START        (16)
#define SOC_SCTRL_SCCLKDIV0_scclkdiv0_msk_END          (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKDIV1_UNION
 结构说明  : SCCLKDIV1 寄存器结构定义。地址偏移量:0x104，初值:0x00000017，宽度:32
 寄存器说明: 时钟分频比控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_aobus     : 6;  /* bit[0-5]  : AOBUS时钟分频比选择：(源时钟为PPLL0时钟，分频比单独可配)
                                                            6'h0:1；
                                                            6'h1:2；
                                                            6'h2:3；
                                                            …
                                                            6'h3E:63；
                                                            6'h3F:64。 */
        unsigned int  div_clkout0_tcxo : 3;  /* bit[6-8]  : clkout0 tcxo时钟分频比选择：（源时钟为19.2MHz的晶振时钟）
                                                            3'h0:1；
                                                            3'h1:2；
                                                            3'h2:3；
                                                            …
                                                            3'h6:7；
                                                            3'h7:8。 */
        unsigned int  div_clkout1_tcxo : 3;  /* bit[9-11] : clkout1 tcxo时钟分频比选择：（源时钟为19.2MHz的晶振时钟）
                                                            3'h0:1；
                                                            3'h1:2；
                                                            3'h2:3；
                                                            …
                                                            3'h6:7；
                                                            3'h7:8。 */
        unsigned int  sel_clkout0      : 2;  /* bit[12-13]: clkout0 时钟源选择：
                                                            0：32KHz；
                                                            1：19.2MHz时钟分频；
                                                            2/3：PPLL3时钟分频。 */
        unsigned int  sel_clkout1      : 2;  /* bit[14-15]: clkout1 时钟源选择：
                                                            0：32KHz；
                                                            1：19.2MHz时钟分频；
                                                            2/3：PPLL3时钟分频。 */
        unsigned int  scclkdiv1_msk    : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                            只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCCLKDIV1_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV1_sc_div_aobus_START      (0)
#define SOC_SCTRL_SCCLKDIV1_sc_div_aobus_END        (5)
#define SOC_SCTRL_SCCLKDIV1_div_clkout0_tcxo_START  (6)
#define SOC_SCTRL_SCCLKDIV1_div_clkout0_tcxo_END    (8)
#define SOC_SCTRL_SCCLKDIV1_div_clkout1_tcxo_START  (9)
#define SOC_SCTRL_SCCLKDIV1_div_clkout1_tcxo_END    (11)
#define SOC_SCTRL_SCCLKDIV1_sel_clkout0_START       (12)
#define SOC_SCTRL_SCCLKDIV1_sel_clkout0_END         (13)
#define SOC_SCTRL_SCCLKDIV1_sel_clkout1_START       (14)
#define SOC_SCTRL_SCCLKDIV1_sel_clkout1_END         (15)
#define SOC_SCTRL_SCCLKDIV1_scclkdiv1_msk_START     (16)
#define SOC_SCTRL_SCCLKDIV1_scclkdiv1_msk_END       (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKDIV2_UNION
 结构说明  : SCCLKDIV2 寄存器结构定义。地址偏移量:0x108，初值:0x00003FFF，宽度:32
 寄存器说明: 时钟分频比控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_asp_subsys  : 1;  /* bit[0]    : 时钟门控配置：
                                                              0：时钟关闭；
                                                              1：时钟开启。 */
        unsigned int  gt_hifidsp_clk_div : 1;  /* bit[1]    : 时钟门控配置：
                                                              0：时钟关闭；
                                                              1：时钟开启。 */
        unsigned int  gt_clk_sci         : 1;  /* bit[2]    : 时钟门控配置：
                                                              0：时钟关闭；
                                                              1：时钟开启。 */
        unsigned int  gt_clk_aobus       : 1;  /* bit[3]    : 时钟门控配置：
                                                              0：时钟关闭；
                                                              1：时钟开启。 */
        unsigned int  gt_asp_hclk_div    : 1;  /* bit[4]    : 时钟门控配置：
                                                              0：时钟关闭；
                                                              1：时钟开启。 */
        unsigned int  gt_sclk_tp         : 1;  /* bit[5]    : 时钟门控配置：
                                                              0：时钟关闭；
                                                              1：时钟开启。 */
        unsigned int  gt_pll_clk_mmbuf   : 1;  /* bit[6]    : mmbuf pll分频前时钟门控配置：
                                                              0：时钟关闭；
                                                              1：时钟开启。
                                                              最终配置值由iomcu，audio和此配置位投票确定，有需求打开就时钟，所有请求都关闭才关闭时钟。 */
        unsigned int  gt_pclk_mmbuf      : 1;  /* bit[7]    : mmbuf pll分频后时钟门控配置：
                                                              0：时钟关闭；
                                                              1：时钟开启。 */
        unsigned int  sel_clk_mmbuf      : 2;  /* bit[8-9]  : mmbuf时钟来源选择：
                                                              00：TCXO
                                                              01：FPLL
                                                              1x: PPLL0
                                                              最终配置值由iomcu，audio和此配置位投票确定，按照性能等级进行仲裁，PPLL0>FPLL>TCXO。 */
        unsigned int  sc_div2_mmbuf      : 2;  /* bit[10-11]: mmbuf分频比控制，分频比=配置值+1。 */
        unsigned int  sc_div4_mmbuf      : 4;  /* bit[12-15]: mmbuf分频比控制，分频比=配置值+1。 */
        unsigned int  scclkdiv2_msk      : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                              只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCCLKDIV2_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV2_gt_clk_asp_subsys_START   (0)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_asp_subsys_END     (0)
#define SOC_SCTRL_SCCLKDIV2_gt_hifidsp_clk_div_START  (1)
#define SOC_SCTRL_SCCLKDIV2_gt_hifidsp_clk_div_END    (1)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_sci_START          (2)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_sci_END            (2)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_aobus_START        (3)
#define SOC_SCTRL_SCCLKDIV2_gt_clk_aobus_END          (3)
#define SOC_SCTRL_SCCLKDIV2_gt_asp_hclk_div_START     (4)
#define SOC_SCTRL_SCCLKDIV2_gt_asp_hclk_div_END       (4)
#define SOC_SCTRL_SCCLKDIV2_gt_sclk_tp_START          (5)
#define SOC_SCTRL_SCCLKDIV2_gt_sclk_tp_END            (5)
#define SOC_SCTRL_SCCLKDIV2_gt_pll_clk_mmbuf_START    (6)
#define SOC_SCTRL_SCCLKDIV2_gt_pll_clk_mmbuf_END      (6)
#define SOC_SCTRL_SCCLKDIV2_gt_pclk_mmbuf_START       (7)
#define SOC_SCTRL_SCCLKDIV2_gt_pclk_mmbuf_END         (7)
#define SOC_SCTRL_SCCLKDIV2_sel_clk_mmbuf_START       (8)
#define SOC_SCTRL_SCCLKDIV2_sel_clk_mmbuf_END         (9)
#define SOC_SCTRL_SCCLKDIV2_sc_div2_mmbuf_START       (10)
#define SOC_SCTRL_SCCLKDIV2_sc_div2_mmbuf_END         (11)
#define SOC_SCTRL_SCCLKDIV2_sc_div4_mmbuf_START       (12)
#define SOC_SCTRL_SCCLKDIV2_sc_div4_mmbuf_END         (15)
#define SOC_SCTRL_SCCLKDIV2_scclkdiv2_msk_START       (16)
#define SOC_SCTRL_SCCLKDIV2_scclkdiv2_msk_END         (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKDIV3_UNION
 结构说明  : SCCLKDIV3 寄存器结构定义。地址偏移量:0x10C，初值:0x00007C0F，宽度:32
 寄存器说明: 时钟分频比控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aobus_auto_waitcfg_out : 10; /* bit[0-9]  : 硬件退出自动降频IDLE等待时钟周期配置。 */
        unsigned int  aobus_div_auto_cfg     : 6;  /* bit[10-15]: 硬件自动降频倍数配置
                                                                  6'h00:1；
                                                                  6'h01:2；
                                                                  …
                                                                  6'h3F:64。 */
        unsigned int  scclkdiv3_msk          : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                  只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCCLKDIV3_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV3_aobus_auto_waitcfg_out_START  (0)
#define SOC_SCTRL_SCCLKDIV3_aobus_auto_waitcfg_out_END    (9)
#define SOC_SCTRL_SCCLKDIV3_aobus_div_auto_cfg_START      (10)
#define SOC_SCTRL_SCCLKDIV3_aobus_div_auto_cfg_END        (15)
#define SOC_SCTRL_SCCLKDIV3_scclkdiv3_msk_START           (16)
#define SOC_SCTRL_SCCLKDIV3_scclkdiv3_msk_END             (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKDIV4_UNION
 结构说明  : SCCLKDIV4 寄存器结构定义。地址偏移量:0x110，初值:0x00008DE5，宽度:32
 寄存器说明: 时钟分频比控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_aobus_noc     : 4;  /* bit[0-3]  : aobus ppll0输出分频。 */
        unsigned int  sel_clk_aobus_noc : 2;  /* bit[4-5]  : aobus clk选择pll
                                                             00：TCXO
                                                             01：FPLL
                                                             10：DDRPLL
                                                             11: PPLL0
                                                             最终配置值由iomcu，audio和此配置位投票确定，按照性能等级进行仲裁，DDRPLL>PPLL0>FPLL>TCXO。 */
        unsigned int  gt_aobus_noc_ini  : 1;  /* bit[6]    : aobus ppll0输出门控
                                                             0：时钟关闭；
                                                             1：时钟开启。
                                                             最终配置值由iomcu，audio和此配置位投票确定，有需求打开就时钟，所有请求都关闭才关闭时钟。 */
        unsigned int  reserved          : 1;  /* bit[7]    : 保留。 */
        unsigned int  sc_div_asp_hclk   : 2;  /* bit[8-9]  : asp hclk分频比。(源时钟为clk_asp_subsys)
                                                             2'h0:1；
                                                             2'h1:2；
                                                             2'h2:3；
                                                             2'h3:4。 */
        unsigned int  gt_clk_memrep     : 1;  /* bit[10]   : clk memrep pll输出门控。 */
        unsigned int  sc_div_memrep     : 5;  /* bit[11-15]: clk memrep pll输出分频
                                                             分频比为：配置值的10进制数*2+2,默认值36分频。 */
        unsigned int  scclkdiv4_msk     : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                             只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCCLKDIV4_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV4_div_aobus_noc_START      (0)
#define SOC_SCTRL_SCCLKDIV4_div_aobus_noc_END        (3)
#define SOC_SCTRL_SCCLKDIV4_sel_clk_aobus_noc_START  (4)
#define SOC_SCTRL_SCCLKDIV4_sel_clk_aobus_noc_END    (5)
#define SOC_SCTRL_SCCLKDIV4_gt_aobus_noc_ini_START   (6)
#define SOC_SCTRL_SCCLKDIV4_gt_aobus_noc_ini_END     (6)
#define SOC_SCTRL_SCCLKDIV4_sc_div_asp_hclk_START    (8)
#define SOC_SCTRL_SCCLKDIV4_sc_div_asp_hclk_END      (9)
#define SOC_SCTRL_SCCLKDIV4_gt_clk_memrep_START      (10)
#define SOC_SCTRL_SCCLKDIV4_gt_clk_memrep_END        (10)
#define SOC_SCTRL_SCCLKDIV4_sc_div_memrep_START      (11)
#define SOC_SCTRL_SCCLKDIV4_sc_div_memrep_END        (15)
#define SOC_SCTRL_SCCLKDIV4_scclkdiv4_msk_START      (16)
#define SOC_SCTRL_SCCLKDIV4_scclkdiv4_msk_END        (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKDIV5_UNION
 结构说明  : SCCLKDIV5 寄存器结构定义。地址偏移量:0x114，初值:0x000003FF，宽度:32
 寄存器说明: 时钟分频比控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  aobus_div_auto_reduce_bypass : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                        0：不bypass；
                                                                        1：bypass。 */
        unsigned int  aobus_auto_waitcfg_in        : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置。 */
        unsigned int  aobus_clk_sw_req_cfg         : 2;  /* bit[11-12]: aobus总线切换请求，此接口仅在normal配置，实际配置低bit有效:
                                                                        x1：aobus切换为tcxo时钟
                                                                        其他：aobus切换为系统时钟。 */
        unsigned int  reserved                     : 3;  /* bit[13-15]: 保留。 */
        unsigned int  scclkdiv5_msk                : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCCLKDIV5_UNION;
#endif
#define SOC_SCTRL_SCCLKDIV5_aobus_div_auto_reduce_bypass_START  (0)
#define SOC_SCTRL_SCCLKDIV5_aobus_div_auto_reduce_bypass_END    (0)
#define SOC_SCTRL_SCCLKDIV5_aobus_auto_waitcfg_in_START         (1)
#define SOC_SCTRL_SCCLKDIV5_aobus_auto_waitcfg_in_END           (10)
#define SOC_SCTRL_SCCLKDIV5_aobus_clk_sw_req_cfg_START          (11)
#define SOC_SCTRL_SCCLKDIV5_aobus_clk_sw_req_cfg_END            (12)
#define SOC_SCTRL_SCCLKDIV5_scclkdiv5_msk_START                 (16)
#define SOC_SCTRL_SCCLKDIV5_scclkdiv5_msk_END                   (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCTRL0_UNION
 结构说明  : SCPERCTRL0 寄存器结构定义。地址偏移量:0x200，初值:0x00000C9B，宽度:32
 寄存器说明: 外设控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 16; /* bit[0-15] : 保留。 */
        unsigned int  efuse_remap : 1;  /* bit[16]   : 送给EFUSEC的REMAP控制
                                                       0:not remap 1:image remap。 */
        unsigned int  reserved_1  : 3;  /* bit[17-19]: 保留。 */
        unsigned int  reserved_2  : 12; /* bit[20-31]: mmbuf_sec_ctrl由SCPERCLKEN0_SEC[31:20]控制。 */
    } reg;
} SOC_SCTRL_SCPERCTRL0_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL0_efuse_remap_START  (16)
#define SOC_SCTRL_SCPERCTRL0_efuse_remap_END    (16)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCTRL1_UNION
 结构说明  : SCPERCTRL1 寄存器结构定义。地址偏移量:0x204，初值:0xFFFFFFF8，宽度:32
 寄存器说明: 外设控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_disable : 32; /* bit[0-31]: 用于指示各个IP是否需要做mem repair:
                                                         0代表修复，1代表不修复
                                                         AO_SUBSYS MRB0
                                                         PERI_SUBSYS(现在只看到LP_M3) MRB1
                                                         DEBUG_SEC_HSIC_PERI_SUBSYS MRB2
                                                         MODEM_SUBSYS MRB3
                                                         BBP_COM_TOP_PD MRB4
                                                         BBP_IRM_TOP_PD MRB5
                                                         A9_WRAP_PD MRB6
                                                         DSP_WRAP_PD MRB7
                                                         BBP_LTE_TOP_PD MRB8
                                                         A57_SUBSYS MRB9
                                                         A53_SUBSYS MRB10
                                                         AUDIO_SUBSYS MRB11
                                                         IOMUC_SUBSYS MRB12
                                                         MMBUF_SUBSYS MRB13
                                                         DSS MRB14
                                                         ISP_SUBSYS MRB15
                                                         IVP32_DSP_SUBSYS MRB16
                                                         VDEC MRB17
                                                         VENC MRB18
                                                         GPU_SUBSYS MRB19
                                                         BBP_CS_CORE MRB20。 */
    } reg;
} SOC_SCTRL_SCPERCTRL1_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL1_repair_disable_START  (0)
#define SOC_SCTRL_SCPERCTRL1_repair_disable_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCTRL2_UNION
 结构说明  : SCPERCTRL2 寄存器结构定义。地址偏移量:0x208，初值:0x00000715，宽度:32
 寄存器说明: 外设控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_spram_rtsel    : 2;  /* bit[0-1]  : ao_spram_rtsel具体参考memory手册。 */
        unsigned int  ao_spram_wtsel    : 2;  /* bit[2-3]  : ao_spram_wtsel具体参考memory手册。 */
        unsigned int  ao_spmbsram_rtsel : 2;  /* bit[4-5]  : ao_spmbsram_rtsel目前未使用。 */
        unsigned int  ao_spmbsram_wtsel : 2;  /* bit[6-7]  : ao_spmbsram_wtsel目前未使用。 */
        unsigned int  ao_rom_rtsel      : 2;  /* bit[8-9]  : ao_rom_rtsel目前未使用。 */
        unsigned int  ao_rom_ptsel      : 2;  /* bit[10-11]: ao_rom_ptsel目前未使用。 */
        unsigned int  ao_rom_trb        : 2;  /* bit[12-13]: ao_rom_trb目前未使用。 */
        unsigned int  ao_rom_tm         : 1;  /* bit[14]   : ao_rom_tm目前未使用。 */
        unsigned int  mmbuf_sram_sd     : 1;  /* bit[15]   : mmbuf_sram_sd memory控制信号，具体参考memory手册。 */
        unsigned int  reserved_0        : 8;  /* bit[16-23]: 保留。 */
        unsigned int  jtaq_to_sdcard    : 1;  /* bit[24]   : 送给JTAG MUX的控制信号
                                                             0:dsp jtag使用通过jtag端口进行调试
                                                             1：dsp jtag使用通过SD管脚端口进行调试。 */
        unsigned int  sc_djtaq_sel      : 1;  /* bit[25]   : 控制bit用于选择DJTAG或者JTAG输出
                                                             0:jtag
                                                             1:djtag。 */
        unsigned int  reserved_1        : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERCTRL2_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL2_ao_spram_rtsel_START     (0)
#define SOC_SCTRL_SCPERCTRL2_ao_spram_rtsel_END       (1)
#define SOC_SCTRL_SCPERCTRL2_ao_spram_wtsel_START     (2)
#define SOC_SCTRL_SCPERCTRL2_ao_spram_wtsel_END       (3)
#define SOC_SCTRL_SCPERCTRL2_ao_spmbsram_rtsel_START  (4)
#define SOC_SCTRL_SCPERCTRL2_ao_spmbsram_rtsel_END    (5)
#define SOC_SCTRL_SCPERCTRL2_ao_spmbsram_wtsel_START  (6)
#define SOC_SCTRL_SCPERCTRL2_ao_spmbsram_wtsel_END    (7)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_rtsel_START       (8)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_rtsel_END         (9)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_ptsel_START       (10)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_ptsel_END         (11)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_trb_START         (12)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_trb_END           (13)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_tm_START          (14)
#define SOC_SCTRL_SCPERCTRL2_ao_rom_tm_END            (14)
#define SOC_SCTRL_SCPERCTRL2_mmbuf_sram_sd_START      (15)
#define SOC_SCTRL_SCPERCTRL2_mmbuf_sram_sd_END        (15)
#define SOC_SCTRL_SCPERCTRL2_jtaq_to_sdcard_START     (24)
#define SOC_SCTRL_SCPERCTRL2_jtaq_to_sdcard_END       (24)
#define SOC_SCTRL_SCPERCTRL2_sc_djtaq_sel_START       (25)
#define SOC_SCTRL_SCPERCTRL2_sc_djtaq_sel_END         (25)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCTRL3_UNION
 结构说明  : SCPERCTRL3 寄存器结构定义。地址偏移量:0x20C，初值:0x00004000，宽度:32
 寄存器说明: 外设控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_debug_sel         : 1;  /* bit[0]    : 通过AHB进行DEBUG功能选择：
                                                                    0：AHB端口不能访问SRAM；
                                                                    1：AHB端口可以访问SRAM。 */
        unsigned int  reset_memrep_msk         : 1;  /* bit[1]    : reset_memrep_msk
                                                                    0:bisr复位后更新repair_frm_efu
                                                                    1:bisr复位后不更新repair_frm_efu。 */
        unsigned int  repair_iddq              : 1;  /* bit[2]    : 1'b0:非IDDQ模式
                                                                    1'b1:BISR控制EFUSE进入IDDQ模式。 */
        unsigned int  repair_frm_sram          : 1;  /* bit[3]    : 指示修复数据来源SRAM：
                                                                    1'b0:修复数据来源EFUSE；
                                                                    1'b1:修复数据来源SRAM。 */
        unsigned int  repair_frm_efu           : 1;  /* bit[4]    : 指示修复数据来源EFUSE：
                                                                    1'b0:
                                                                    1'b1:修复数据来源EFUSE
                                                                    该信号在reset_memrep_n信号的上升沿自动变为1。 */
        unsigned int  dram_pwr_ctl             : 3;  /* bit[5-7]  : 控制内部双端口RAM POWER,具体参考memory手册。 */
        unsigned int  efusec_timeout_bypass    : 1;  /* bit[8]    : efusec timeout bypass（暂未使用）。 */
        unsigned int  bbdrx_timeout_bypass     : 1;  /* bit[9]    : bbdrx timeout bypass
                                                                    0:no bypass 1:bypass。 */
        unsigned int  sleep_mode_cfgbus_bypass : 1;  /* bit[10]   : 1'b0:sleepmode有效时关时钟
                                                                    1'b1:sleepmode有效时不关时钟。 */
        unsigned int  sleep_mode_lpmcu_bypass  : 1;  /* bit[11]   : 1'b0:sleepmode有效时关时钟
                                                                    1'b1:sleepmode有效时不关时钟。 */
        unsigned int  ao_mrb_rst_msk           : 1;  /* bit[12]   : ao区memroy修复数据屏蔽保护,此bit需要在suspend流程配置为1'b1
                                                                    1'b0:resume流程中LPM3配置SCtrl这bit寄存器为0，撤销屏蔽，此时BISR可以根据应用需要修复AO区的MRB
                                                                    1'b1:在suspend流程中，即LPM3配置芯片进入睡眠态之前，配置SCtrl这bit寄存器为1，即可屏蔽掉电区BISR输出的复位0电平，然后走正常的睡眠流程。 */
        unsigned int  sleep_mode_aobus_bypass  : 1;  /* bit[13]   : 1'b0:sleepmode有效时关时钟
                                                                    1'b1:sleepmode有效时不关时钟。 */
        unsigned int  bbp_clk_en               : 1;  /* bit[14]   : 送给BBPDRX的时钟使能信号：
                                                                    1'b0:关时钟
                                                                    1'b1:开时钟。 */
        unsigned int  reserved                 : 1;  /* bit[15]   : 保留。 */
        unsigned int  bbp_on_ctrl              : 16; /* bit[16-31]: bbp_on_ctrl，预留调试使用
                                                                    [3]bbp_timer_srst_en bbp on 区 bbp 64bit timer 时钟对应的软复位使能信号：
                                                                    1：复位
                                                                    0：不复位
                                                                    [2]bbp_32k_srst_en bbp on 区 bbp 32k 时钟对应的软复位使能信号：
                                                                    1：复位
                                                                    0：不复位 
                                                                    [1]g2_104m_srst_en bbp on 区 g2 104M时钟对应的软复位使能信号：
                                                                    1：复位
                                                                    0：不复位 
                                                                    [0]g1_104m_srst_en bbp on 区 g1 104M时钟对应的软复位使能信号：
                                                                    1：复位
                                                                    0：不复位 。 */
    } reg;
} SOC_SCTRL_SCPERCTRL3_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL3_repair_debug_sel_START          (0)
#define SOC_SCTRL_SCPERCTRL3_repair_debug_sel_END            (0)
#define SOC_SCTRL_SCPERCTRL3_reset_memrep_msk_START          (1)
#define SOC_SCTRL_SCPERCTRL3_reset_memrep_msk_END            (1)
#define SOC_SCTRL_SCPERCTRL3_repair_iddq_START               (2)
#define SOC_SCTRL_SCPERCTRL3_repair_iddq_END                 (2)
#define SOC_SCTRL_SCPERCTRL3_repair_frm_sram_START           (3)
#define SOC_SCTRL_SCPERCTRL3_repair_frm_sram_END             (3)
#define SOC_SCTRL_SCPERCTRL3_repair_frm_efu_START            (4)
#define SOC_SCTRL_SCPERCTRL3_repair_frm_efu_END              (4)
#define SOC_SCTRL_SCPERCTRL3_dram_pwr_ctl_START              (5)
#define SOC_SCTRL_SCPERCTRL3_dram_pwr_ctl_END                (7)
#define SOC_SCTRL_SCPERCTRL3_efusec_timeout_bypass_START     (8)
#define SOC_SCTRL_SCPERCTRL3_efusec_timeout_bypass_END       (8)
#define SOC_SCTRL_SCPERCTRL3_bbdrx_timeout_bypass_START      (9)
#define SOC_SCTRL_SCPERCTRL3_bbdrx_timeout_bypass_END        (9)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_cfgbus_bypass_START  (10)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_cfgbus_bypass_END    (10)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_lpmcu_bypass_START   (11)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_lpmcu_bypass_END     (11)
#define SOC_SCTRL_SCPERCTRL3_ao_mrb_rst_msk_START            (12)
#define SOC_SCTRL_SCPERCTRL3_ao_mrb_rst_msk_END              (12)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_aobus_bypass_START   (13)
#define SOC_SCTRL_SCPERCTRL3_sleep_mode_aobus_bypass_END     (13)
#define SOC_SCTRL_SCPERCTRL3_bbp_clk_en_START                (14)
#define SOC_SCTRL_SCPERCTRL3_bbp_clk_en_END                  (14)
#define SOC_SCTRL_SCPERCTRL3_bbp_on_ctrl_START               (16)
#define SOC_SCTRL_SCPERCTRL3_bbp_on_ctrl_END                 (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCTRL4_UNION
 结构说明  : SCPERCTRL4 寄存器结构定义。地址偏移量:0x210，初值:0x09280000，宽度:32
 寄存器说明: 外设控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddr_ret_en : 4;  /* bit[0-3]  : 配置DDRPHY进入Retention模式的控制信号，4个通道单独控制；
                                                      1'b0：ret无效。
                                                      1'b1：ret有效。 */
        unsigned int  reserved_0 : 1;  /* bit[4]    : xo_mode_a2d 信号指示当前32K来源是19.2MHz/586 还是32768Hz，
                                                      0表示19.2MHz/586，
                                                      1表示32768Hz;
                                                      注意：软件不允许配置此bit。 */
        unsigned int  reserved_1 : 3;  /* bit[5-7]  : 保留。 */
        unsigned int  crc_value  : 21; /* bit[8-28] : RTC原理：将32K RC时钟同步到19.2MHz时钟域，在连续1024个RC时钟计数窗口内，统计19.2MHz的时钟个数，得到数值A。
                                                      可知A=N*1024+B，其中N和B为整数，用A可以推算出商N和余数B。
                                                      b) 32K来源为19.2MHz/586 时，N为586， B为0；
                                                      c) 32K来源为32768Hz 时， N为585， B为960；
                                                      高11bit 用来配置N；低10bit 用来配置B。 */
        unsigned int  reserved_2 : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERCTRL4_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL4_ddr_ret_en_START  (0)
#define SOC_SCTRL_SCPERCTRL4_ddr_ret_en_END    (3)
#define SOC_SCTRL_SCPERCTRL4_crc_value_START   (8)
#define SOC_SCTRL_SCPERCTRL4_crc_value_END     (28)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCTRL5_UNION
 结构说明  : SCPERCTRL5 寄存器结构定义。地址偏移量:0x214，初值:0x00101003，宽度:32
 寄存器说明: 外设控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usim0_io_sel18    : 1;  /* bit[0]    : USIM卡0的ODIO电压切换控制信号
                                                             0：3.3V 1：1.8V。 */
        unsigned int  usim1_io_sel18    : 1;  /* bit[1]    : USIM卡1的ODIO电压切换控制信号
                                                             0：3.3V 1：1.8V。 */
        unsigned int  sdcard_io_sel18   : 1;  /* bit[2]    : SDCARD的ODIO电压切换信号
                                                             0：3.3V 1：1.8V。 */
        unsigned int  reserved_0        : 3;  /* bit[3-5]  : 保留。 */
        unsigned int  reserved_1        : 1;  /* bit[6]    : 保留。 */
        unsigned int  usim_od_en        : 1;  /* bit[7]    : USIM卡数据类型选择信号
                                                             0：开漏输出（OD）
                                                             1：三态模式（push-pull）。 */
        unsigned int  tp_sel            : 4;  /* bit[8-11] : 测试信号分组选择；详细分配情况请参考集成设计文档。 */
        unsigned int  ao_hpm_clk_div    : 6;  /* bit[12-17]: ao HPM时钟分频器。配置值要求大于1；分频比=配置值+1。 */
        unsigned int  ao_hpm_en         : 1;  /* bit[18]   : ao HPM使能。
                                                             0:disable 1:enable。 */
        unsigned int  ao_hpmx_en        : 1;  /* bit[19]   : ao HPMX使能。
                                                             0:disable 1:enable。 */
        unsigned int  sc_noc_timeout_en : 1;  /* bit[20]   : sc_noc_timeout_en
                                                             0：not timeout 1:timeout。 */
        unsigned int  peri_ctrl5_other  : 11; /* bit[21-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERCTRL5_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL5_usim0_io_sel18_START     (0)
#define SOC_SCTRL_SCPERCTRL5_usim0_io_sel18_END       (0)
#define SOC_SCTRL_SCPERCTRL5_usim1_io_sel18_START     (1)
#define SOC_SCTRL_SCPERCTRL5_usim1_io_sel18_END       (1)
#define SOC_SCTRL_SCPERCTRL5_sdcard_io_sel18_START    (2)
#define SOC_SCTRL_SCPERCTRL5_sdcard_io_sel18_END      (2)
#define SOC_SCTRL_SCPERCTRL5_usim_od_en_START         (7)
#define SOC_SCTRL_SCPERCTRL5_usim_od_en_END           (7)
#define SOC_SCTRL_SCPERCTRL5_tp_sel_START             (8)
#define SOC_SCTRL_SCPERCTRL5_tp_sel_END               (11)
#define SOC_SCTRL_SCPERCTRL5_ao_hpm_clk_div_START     (12)
#define SOC_SCTRL_SCPERCTRL5_ao_hpm_clk_div_END       (17)
#define SOC_SCTRL_SCPERCTRL5_ao_hpm_en_START          (18)
#define SOC_SCTRL_SCPERCTRL5_ao_hpm_en_END            (18)
#define SOC_SCTRL_SCPERCTRL5_ao_hpmx_en_START         (19)
#define SOC_SCTRL_SCPERCTRL5_ao_hpmx_en_END           (19)
#define SOC_SCTRL_SCPERCTRL5_sc_noc_timeout_en_START  (20)
#define SOC_SCTRL_SCPERCTRL5_sc_noc_timeout_en_END    (20)
#define SOC_SCTRL_SCPERCTRL5_peri_ctrl5_other_START   (21)
#define SOC_SCTRL_SCPERCTRL5_peri_ctrl5_other_END     (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCTRL6_UNION
 结构说明  : SCPERCTRL6 寄存器结构定义。地址偏移量:0x218，初值:0x00000000，宽度:32
 寄存器说明: 外设控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_io_ret            : 1;  /* bit[0-0]  : 外设区非启动相关IO Retetion：
                                                                  0：Retetion撤销；
                                                                  1：Retetion使能。 */
        unsigned int  sc_noc_aobus_idle_flag : 1;  /* bit[1]    : sc_noc_aobus_idle_flag
                                                                  0：aobus not idle
                                                                  1:aobus idle
                                                                  此信号是4个信号：
                                                                  sc_aonoc_asp_mst_i_mainnopendingtrans
                                                                  iomcu_axi_ahb_nopendingtrans
                                                                  iomcu_axi_mst_nopendingtrans
                                                                  iomcu_dma_mst_nopendingtrans
                                                                  位与，每个信号支持bypass，此信号有效时，sys bus可自动降频。 */
        unsigned int  efuse_arm_dbg_ctrl     : 2;  /* bit[2-3]  : 安全debug等级
                                                                  00：debug enable default
                                                                  01：由系统鉴权后sc内部输出的cfg_arm_dbgen[3:0]控制
                                                                  10：由dx鉴权后dx内部输出的cfg_arm_dbgen_dx[3:0]控制
                                                                  11：由efuse烧写值efuse_arm_dbgen[3:0]控制。 */
        unsigned int  peri_bootio_ret        : 1;  /* bit[4-4]  : 外设区启动相关IO Retetion：
                                                                  0：Retetion撤销；
                                                                  1：Retetion使能。 */
        unsigned int  peri_bootio_ret_mode   : 1;  /* bit[5-5]  : 外设区启动相关IO Retetion控制模式：
                                                                  0：由比特4的配置值控制；
                                                                  1：由硬件自动控制。 */
        unsigned int  reserved_0             : 2;  /* bit[6-7]  : 端口由sel_clk_aobus_noc_comb驱动,默认值为0x2,aobus clk时钟来源选择：
                                                                  00：TCXO
                                                                  01：FPLL
                                                                  10：DDRPLL
                                                                  11: PPLL0
                                                                  最终配置值由iomcu，audio和sel_clk_aobus_noc配置位投票确定，按照性能等级进行仲裁，DDRPLL>PPLL0>FPLL>TCXO。 */
        unsigned int  reserved_1             : 2;  /* bit[8-9]  : 端口由sel_clk_mmbuf_comb驱动,默认值为0x3,mmbuf时钟来源选择：
                                                                  00：TCXO
                                                                  01：FPLL
                                                                  1x: PPLL0
                                                                  最终配置值由iomcu，audio和sel_clk_mmbuf配置位投票确定，按照性能等级进行仲裁，PPLL0>FPLL>TCXO。 */
        unsigned int  reserved_2             : 9;  /* bit[10-18]: 保留。 */
        unsigned int  gt_rst_asc             : 1;  /* bit[19]   : 保留。 */
        unsigned int  reserved_3             : 1;  /* bit[20]   : 由原始中断aomcu_ao_noc_mainstatalarm_int和mask位aomcu_ao_noc_mainstatalarm_intmsk相与后确定，含义如下：
                                                                  0:no int;
                                                                  1:int produced。 */
        unsigned int  reserved_4             : 1;  /* bit[21]   : 由原始中断aomcu_ao_noc_mainfault_int和mask位aomcu_ao_noc_mainfault_intmsk相与后确定，含义如下：
                                                                  0:no int;
                                                                  1:int produced。 */
        unsigned int  reserved_5             : 1;  /* bit[22]   : 由原始中断asp_transaction_probe_mainstatalarm_int和mask位asp_transaction_probe_mainstatalarm_intmsk相与后确定，含义如下：
                                                                  0:no int;
                                                                  1:int produced。 */
        unsigned int  reserved_6             : 1;  /* bit[23]   : 由原始中断asp_error_probe_observer_mainfault_int和mask位asp_error_probe_observer_mainfault_intmsk相与后确定，含义如下：
                                                                  0:no int;
                                                                  1:int produced。 */
        unsigned int  reserved_7             : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERCTRL6_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL6_peri_io_ret_START             (0)
#define SOC_SCTRL_SCPERCTRL6_peri_io_ret_END               (0)
#define SOC_SCTRL_SCPERCTRL6_sc_noc_aobus_idle_flag_START  (1)
#define SOC_SCTRL_SCPERCTRL6_sc_noc_aobus_idle_flag_END    (1)
#define SOC_SCTRL_SCPERCTRL6_efuse_arm_dbg_ctrl_START      (2)
#define SOC_SCTRL_SCPERCTRL6_efuse_arm_dbg_ctrl_END        (3)
#define SOC_SCTRL_SCPERCTRL6_peri_bootio_ret_START         (4)
#define SOC_SCTRL_SCPERCTRL6_peri_bootio_ret_END           (4)
#define SOC_SCTRL_SCPERCTRL6_peri_bootio_ret_mode_START    (5)
#define SOC_SCTRL_SCPERCTRL6_peri_bootio_ret_mode_END      (5)
#define SOC_SCTRL_SCPERCTRL6_gt_rst_asc_START              (19)
#define SOC_SCTRL_SCPERCTRL6_gt_rst_asc_END                (19)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS0_UNION
 结构说明  : SCPERSTATUS0 寄存器结构定义。地址偏移量:0x21C，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_dwaxi_dlock_wr  : 1;  /* bit[0]    : asp子系统内部bus的死锁指示信号。 */
        unsigned int  asp_dwaxi_dlock_id  : 4;  /* bit[1-4]  : asp子系统内部bus的死锁指示信号。 */
        unsigned int  asp_dwaxi_dlock_slv : 3;  /* bit[5-7]  : asp子系统内部bus的死锁指示信号。 */
        unsigned int  asp_dwaxi_dlock_mst : 2;  /* bit[8-9]  : asp子系统内部bus的死锁指示信号。 */
        unsigned int  tp_a0_grp           : 10; /* bit[10-19]: 测试管脚
                                                               sys_mode[0] AO管脚-A0 A0_0
                                                               sys_mode[1] AO管脚-A0 A0_1
                                                               sys_mode[2] AO管脚-A0 A0_2
                                                               sys_mode[3] AO管脚-A0 A0_3
                                                               clkgt_ctrl AO管脚-A0 A0_4
                                                               por_int_n AO管脚-A0 A0_5
                                                               sclk_tp AO管脚-A0 A0_6
                                                               xtal_sw_ack AO管脚-A0 A0_7
                                                               preset_efusec_n AO管脚-A0 A0_8
                                                               reset_memrep_n AO管脚-A0 A0_9。 */
        unsigned int  tp_a1_grp           : 10; /* bit[20-29]: 测试管脚
                                                               sys_pw_stat[0] AO管脚-A1 A1_0
                                                               sys_pw_stat[1] AO管脚-A1 A1_1
                                                               sys_pw_stat[2] AO管脚-A1 A1_2
                                                               sys_pw_stat[3] AO管脚-A1 A1_3
                                                               tcxo0_en AO管脚-A1 A1_4
                                                               tcxo1_en AO管脚-A1 A1_5
                                                               clkgt_ctrl0 AO管脚-A1 A1_6
                                                               clkgt_ctrl1 AO管脚-A1 A1_7
                                                               abbbuf_en0 AO管脚-A1 A1_8
                                                               abbbuf_en1 AO管脚-A1 A1_9。 */
        unsigned int  reserved_0          : 1;  /* bit[30]   : 保留。 */
        unsigned int  reserved_1          : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS0_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_wr_START   (0)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_wr_END     (0)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_id_START   (1)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_id_END     (4)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_slv_START  (5)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_slv_END    (7)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_mst_START  (8)
#define SOC_SCTRL_SCPERSTATUS0_asp_dwaxi_dlock_mst_END    (9)
#define SOC_SCTRL_SCPERSTATUS0_tp_a0_grp_START            (10)
#define SOC_SCTRL_SCPERSTATUS0_tp_a0_grp_END              (19)
#define SOC_SCTRL_SCPERSTATUS0_tp_a1_grp_START            (20)
#define SOC_SCTRL_SCPERSTATUS0_tp_a1_grp_END              (29)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS1_UNION
 结构说明  : SCPERSTATUS1 寄存器结构定义。地址偏移量:0x220，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  err_flag : 32; /* bit[0-31]: memory repair模块err指示。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS1_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS1_err_flag_START  (0)
#define SOC_SCTRL_SCPERSTATUS1_err_flag_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS2_UNION
 结构说明  : SCPERSTATUS2 寄存器结构定义。地址偏移量:0x224，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_a2_grp : 10; /* bit[0-9]  : 测试管脚
                                                     tcxoseq_finish0 AO管脚-A2 A2_0
                                                     tcxoseq_finish1 AO管脚-A2 A2_1
                                                     tcxo_timeout0 AO管脚-A2 A2_2
                                                     tcxo_timeout1 AO管脚-A2 A2_3
                                                     tcxoseq_stat0[0] AO管脚-A4 A2 A4_0 A2_4
                                                     tcxoseq_stat0[1] AO管脚-A4 A2 A4_0 A2_5
                                                     tcxoseq_stat0[2] AO管脚-A4 A2 A4_0 A2_6
                                                     tcxoseq_stat1[0] AO管脚-A4 A2 A4_0 A2_7
                                                     tcxoseq_stat1[1] AO管脚-A4 A2 A4_0 A2_8
                                                     tcxoseq_stat1[2] AO管脚-A4 A2 A4_0 A2_9。 */
        unsigned int  tp_a3_grp : 10; /* bit[10-19]: 测试管脚
                                                     sys_been_deepsleepde AO管脚-A4 A3 A4_6 A3_0
                                                     sys_been_ltsleeped AO管脚-A4 A3 A4_6 A3_1
                                                     intr_ao_wakeup0 AO管脚-A4 A3 A4_6 A3_2
                                                     intr_ao_wakeup1 AO管脚-A8 A3 A8_1 A3_3
                                                     intr_peri_wakeup AO管脚-A8 A3 A8_8 A3_4。 */
        unsigned int  tp_a4_grp : 10; /* bit[20-29]: 测试管脚
                                                     ao_fll_tp[9:0] AO管脚-A4 A4_0~9。 */
        unsigned int  reserved  : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS2_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS2_tp_a2_grp_START  (0)
#define SOC_SCTRL_SCPERSTATUS2_tp_a2_grp_END    (9)
#define SOC_SCTRL_SCPERSTATUS2_tp_a3_grp_START  (10)
#define SOC_SCTRL_SCPERSTATUS2_tp_a3_grp_END    (19)
#define SOC_SCTRL_SCPERSTATUS2_tp_a4_grp_START  (20)
#define SOC_SCTRL_SCPERSTATUS2_tp_a4_grp_END    (29)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS3_UNION
 结构说明  : SCPERSTATUS3 寄存器结构定义。地址偏移量:0x228，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_done : 32; /* bit[0-31]: 各bit对应1路MRB：
                                                      0：该路MRB，在该次memory修复过程中，没有启动repair； 
                                                      1：该路MRB，在该次memory修复过程中，启动了repair。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS3_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS3_repair_done_START  (0)
#define SOC_SCTRL_SCPERSTATUS3_repair_done_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS4_UNION
 结构说明  : SCPERSTATUS4 寄存器结构定义。地址偏移量:0x22C，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bbdrx_timeout_dbg_info : 32; /* bit[0-31]: bbdrx_timeout_dbg_info
                                                                 [22]:pready_s
                                                                 0:not ready 1:ready
                                                                 [21]:dbg_timeout
                                                                 0:not timeout 1:timeout
                                                                 [20]:dbg_pwrite
                                                                 0:read 1:write
                                                                 [19:0]:dbg_addr。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS4_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS4_bbdrx_timeout_dbg_info_START  (0)
#define SOC_SCTRL_SCPERSTATUS4_bbdrx_timeout_dbg_info_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS5_UNION
 结构说明  : SCPERSTATUS5 寄存器结构定义。地址偏移量:0x230，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_a9_grp                               : 10; /* bit[0-9]  : 测试管脚，具体含义参考tp测试文档
                                                                                   ppll0_lock AO管脚-A9 A9_4
                                                                                   ppll0_en AO管脚-A9 A9_5
                                                                                   xtal_sw_req AO管脚-A9 A9_6
                                                                                   pll_sw_req AO管脚-A9 A9_7
                                                                                   pll_sw_ack AO管脚-A9 A9_8
                                                                                   reset_peri_n AO管脚-A9 A9_9。 */
        unsigned int  tp_a10_grp                              : 10; /* bit[10-19]: 测试管脚，具体含义参考tp测试文档
                                                                                   tp_iomcu[0] AO管脚-A10 A10_0
                                                                                   tp_iomcu[1] AO管脚-A10 A10_1
                                                                                   tp_iomcu[2] AO管脚-A10 A10_2
                                                                                   tp_iomcu[3] AO管脚-A10 A10_3
                                                                                   tp_iomcu[4] AO管脚-A10 A10_4
                                                                                   tp_iomcu[5] AO管脚-A10 A10_5
                                                                                   tp_iomcu[6] AO管脚-A10 A10_6
                                                                                   tp_iomcu[7] AO管脚-A10 A10_7
                                                                                   tp_iomcu[8] AO管脚-A10 A10_8
                                                                                   tp_iomcu[9] AO管脚-A10 A10_9。 */
        unsigned int  aomcu_ao_noc_mainstatalarm_int          : 1;  /* bit[20]   : aomcu_ao_noc_mainstatalarm_int目前未使用。 */
        unsigned int  aomcu_ao_noc_mainfault_int              : 1;  /* bit[21]   : aomcu_ao_noc_mainfault_int目前未使用。 */
        unsigned int  asp_transaction_probe_mainstatalarm_int : 1;  /* bit[22]   : asp_transaction_probe_mainstatalarm_int0:no int 1:int occur 。 */
        unsigned int  asp_error_probe_observer_mainfault_int  : 1;  /* bit[23]   : asp_error_probe_observer_mainfault_int目前未使用。 */
        unsigned int  repair_start_point_err                  : 1;  /* bit[24]   : [0]:repair_start_point_err
                                                                                   指示启动修复是否从状态机的idle态开始：
                                                                                   0：是；
                                                                                   1：否（发起修复启动错误）。 */
        unsigned int  pack_is0_err                            : 1;  /* bit[25]   : 指示修复时从EFUSE/SRAM的数据包是否全0：
                                                                                   0：非全0；
                                                                                   1：全0（数据包错误）。 */
        unsigned int  repair_finish                           : 1;  /* bit[26]   : 指示该次修复过程是否完成：
                                                                                   0：该次修复过程没有结束；
                                                                                   1：该次修复过程结束。 */
        unsigned int  mdmcpu_dbgack                           : 1;  /* bit[27]   : modem dbgack
                                                                                   0：debug not acknowledged
                                                                                   1:debug acknowledged。 */
        unsigned int  cfg_ispa7_dbgen_dx                      : 4;  /* bit[28-31]: [31:28]:cfg_ispa7_dbgen_dx。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS5_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS5_tp_a9_grp_START                                (0)
#define SOC_SCTRL_SCPERSTATUS5_tp_a9_grp_END                                  (9)
#define SOC_SCTRL_SCPERSTATUS5_tp_a10_grp_START                               (10)
#define SOC_SCTRL_SCPERSTATUS5_tp_a10_grp_END                                 (19)
#define SOC_SCTRL_SCPERSTATUS5_aomcu_ao_noc_mainstatalarm_int_START           (20)
#define SOC_SCTRL_SCPERSTATUS5_aomcu_ao_noc_mainstatalarm_int_END             (20)
#define SOC_SCTRL_SCPERSTATUS5_aomcu_ao_noc_mainfault_int_START               (21)
#define SOC_SCTRL_SCPERSTATUS5_aomcu_ao_noc_mainfault_int_END                 (21)
#define SOC_SCTRL_SCPERSTATUS5_asp_transaction_probe_mainstatalarm_int_START  (22)
#define SOC_SCTRL_SCPERSTATUS5_asp_transaction_probe_mainstatalarm_int_END    (22)
#define SOC_SCTRL_SCPERSTATUS5_asp_error_probe_observer_mainfault_int_START   (23)
#define SOC_SCTRL_SCPERSTATUS5_asp_error_probe_observer_mainfault_int_END     (23)
#define SOC_SCTRL_SCPERSTATUS5_repair_start_point_err_START                   (24)
#define SOC_SCTRL_SCPERSTATUS5_repair_start_point_err_END                     (24)
#define SOC_SCTRL_SCPERSTATUS5_pack_is0_err_START                             (25)
#define SOC_SCTRL_SCPERSTATUS5_pack_is0_err_END                               (25)
#define SOC_SCTRL_SCPERSTATUS5_repair_finish_START                            (26)
#define SOC_SCTRL_SCPERSTATUS5_repair_finish_END                              (26)
#define SOC_SCTRL_SCPERSTATUS5_mdmcpu_dbgack_START                            (27)
#define SOC_SCTRL_SCPERSTATUS5_mdmcpu_dbgack_END                              (27)
#define SOC_SCTRL_SCPERSTATUS5_cfg_ispa7_dbgen_dx_START                       (28)
#define SOC_SCTRL_SCPERSTATUS5_cfg_ispa7_dbgen_dx_END                         (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS6_UNION
 结构说明  : SCPERSTATUS6 寄存器结构定义。地址偏移量:0x234，初值:0x00020000，宽度:32
 寄存器说明: 外设状态寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_stat6 : 32; /* bit[0-31]: other:reserved
                                                     [31:30]AO_BUS的时钟切换 asp_aobus_clk_sw_req，not use
                                                     [29:28]MMBUF的时钟切换 asp_mmbuf_clk_sw_req，not use
                                                     [27]AO_BUS的时钟门控 asp_aobus_clk_en_req，1bit,1：打开 0：关闭，not use
                                                     [26]MMBUF的时钟门控 asp_mmbuf_clk_en_req，1bit,1：打开 0：关闭，not use
                                                     [25]FLL的开关控制 asp_fpll_en_req，1bit,1：打开 0：关闭，not use
                                                     [24]PPLL0的开关控制 asp_ppll0_en_req ，1bit,1：打开 0：关闭，not use
                                                     [23:20]:cfg_mcu_dbgen_dx
                                                     ={spniden,spiden,niden,dbgen}
                                                     0:disable 1:enable
                                                     [19:16]:cfg_arm_dbgen_dx
                                                     ={spniden,spiden,niden,dbgen}
                                                     0:disable 1:enable
                                                     [14]sc_aonoc_asp_mst_i_mainnopendingtrans
                                                     0:trans 1:no pending trans
                                                     [13]sc_aobus_service_target_mainnopendingtrans
                                                     0:trans 1:no pending trans
                                                     [12]iomcu_power_idleack
                                                     0：not idle 1:idle
                                                     [11]iomcu_power_idle
                                                     0：not idle 1:idle
                                                     [10]iomcu_apb_slv_maintimeout
                                                     0：not timeout 1:timeout
                                                     [9]iomcu_ahb_slv_maintimeout
                                                     0：not timeout 1:timeout
                                                     [8]noc_asp_power_idleack
                                                     0：not idle 1:idle
                                                     [7]reserved
                                                     [6]保留。
                                                     [5]noc_asp_power_idle
                                                     0：not idle 1:idle
                                                     [4]reserved
                                                     [3]保留。
                                                     [2]noc_asp_cfg_t_maintimeout
                                                     0：not timeout 1:timeout
                                                     [1]reserved
                                                     [0]noc_aobus_mmbuf_t_maintimeout
                                                     0：not timeout 1:timeout。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS6_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS6_peri_stat6_START  (0)
#define SOC_SCTRL_SCPERSTATUS6_peri_stat6_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS7_UNION
 结构说明  : SCPERSTATUS7 寄存器结构定义。地址偏移量:0x238，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_finish_flag : 32; /* bit[0-31]: 每1bit对应1路MRB，指示MRB是否修复修复完成(没有启动修复也认为是一种修复完成)：
                                                             0：该MRB修复没有完成；
                                                             1：该MRB修复完成。
                                                             [31:19]为预留位。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS7_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS7_repair_finish_flag_START  (0)
#define SOC_SCTRL_SCPERSTATUS7_repair_finish_flag_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS8_UNION
 结构说明  : SCPERSTATUS8 寄存器结构定义。地址偏移量:0x23C，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_data_err0 : 32; /* bit[0-31]: [2:0]->MRB0,[5:3]->MRB1,…,{repair_data_err1[0],[31:30]}->MRB10。每组含义：
                                                           000：数据正常；
                                                           001：期望收到压缩数据包，但收到了非压缩数据包；
                                                           010：期望收到非压缩数据包，但收到了压缩数据包；
                                                           011：收到的数据解压后，bit流长度小于对应MRB期望的bit流长度；
                                                           100：收到的数据解压后，bit流长度大于对应MRB期望的bit流长度；
                                                           101：数据包的[15:13]，既不是3'b000，也不是3'b001。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS8_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS8_repair_data_err0_START  (0)
#define SOC_SCTRL_SCPERSTATUS8_repair_data_err0_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS9_UNION
 结构说明  : SCPERSTATUS9 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_data_err1 : 32; /* bit[0-31]: [3:1]->MRB11,[6:4]->MRB12,…,[30:28]->MRB20。每组含义：
                                                           000：数据正常；
                                                           001：期望收到压缩数据包，但收到了非压缩数据包；
                                                           010：期望收到非压缩数据包，但收到了压缩数据包；
                                                           011：收到的数据解压后，bit流长度小于对应MRB期望的bit流长度；
                                                           100：收到的数据解压后，bit流长度大于对应MRB期望的bit流长度；
                                                           101：数据包的[15:13]，既不是3'b000，也不是3'b001。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS9_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS9_repair_data_err1_START  (0)
#define SOC_SCTRL_SCPERSTATUS9_repair_data_err1_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS10_UNION
 结构说明  : SCPERSTATUS10 寄存器结构定义。地址偏移量:0x244，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_data_err2 : 32; /* bit[0-31]: {[1:0],repair_data_err1[31]}->MRB21,[4:2]->MRB22,…,[31:29]->MRB31。每组含义：
                                                           000：数据正常；
                                                           001：期望收到压缩数据包，但收到了非压缩数据包；
                                                           010：期望收到非压缩数据包，但收到了压缩数据包；
                                                           011：收到的数据解压后，bit流长度小于对应MRB期望的bit流长度；
                                                           100：收到的数据解压后，bit流长度大于对应MRB期望的bit流长度；
                                                           101：数据包的[15:13]，既不是3'b000，也不是3'b001。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS10_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS10_repair_data_err2_START  (0)
#define SOC_SCTRL_SCPERSTATUS10_repair_data_err2_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS11_UNION
 结构说明  : SCPERSTATUS11 寄存器结构定义。地址偏移量:0x248，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mrb_need_repair : 32; /* bit[0-31]: 每bit对应1路MRB，指示该MRB是否有输出bit1(该MRB有坏点)。
                                                          0：没有坏点；
                                                          1：有坏点。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS11_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS11_mrb_need_repair_START  (0)
#define SOC_SCTRL_SCPERSTATUS11_mrb_need_repair_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS12_UNION
 结构说明  : SCPERSTATUS12 寄存器结构定义。地址偏移量:0x24C，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器12。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  repair_disable_flag : 32; /* bit[0-31]: 没bit对应1路MRB，指示该MRB是否真实的启动了修复(MRB0/1/2还有硬件控制)。
                                                              0：可以修复；
                                                              1：禁止修复。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS12_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS12_repair_disable_flag_START  (0)
#define SOC_SCTRL_SCPERSTATUS12_repair_disable_flag_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS13_UNION
 结构说明  : SCPERSTATUS13 寄存器结构定义。地址偏移量:0x250，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器13。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ao_hpm_opc      : 10; /* bit[0-9]  : ao HPM原始性能码。 */
        unsigned int  ao_hpm_opc_vld  : 1;  /* bit[10]   : ao HPM原始性能码有效的状态指示。
                                                           0:not valid 1:valid。 */
        unsigned int  reserved        : 1;  /* bit[11]   : 保留。 */
        unsigned int  ao_hpmx_opc     : 10; /* bit[12-21]: ao HPMX原始性能码。 */
        unsigned int  ao_hpmx_opc_vld : 1;  /* bit[22]   : ao HPMX原始性能码有效的状态指示。
                                                           0:not valid 1:valid。 */
        unsigned int  scperstatus13   : 9;  /* bit[23-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS13_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS13_ao_hpm_opc_START       (0)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpm_opc_END         (9)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpm_opc_vld_START   (10)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpm_opc_vld_END     (10)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpmx_opc_START      (12)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpmx_opc_END        (21)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpmx_opc_vld_START  (22)
#define SOC_SCTRL_SCPERSTATUS13_ao_hpmx_opc_vld_END    (22)
#define SOC_SCTRL_SCPERSTATUS13_scperstatus13_START    (23)
#define SOC_SCTRL_SCPERSTATUS13_scperstatus13_END      (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERSTATUS14_UNION
 结构说明  : SCPERSTATUS14 寄存器结构定义。地址偏移量:0x254，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器14。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scperstatus14 : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERSTATUS14_UNION;
#endif
#define SOC_SCTRL_SCPERSTATUS14_scperstatus14_START  (0)
#define SOC_SCTRL_SCPERSTATUS14_scperstatus14_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCTRL7_UNION
 结构说明  : SCPERCTRL7 寄存器结构定义。地址偏移量:0x270，初值:0x0000000C，宽度:32
 寄存器说明: 外设控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_mmbuf_pending_en                    : 1;  /* bit[0]    : clk_mmbuf根据总线pending信号sc_noc_aobus_idle_flag自动关闭
                                                                                      0：disable
                                                                                      1：enable。 */
        unsigned int  reserved                                   : 1;  /* bit[1]    : 保留。 */
        unsigned int  noc_asp_power_idlereq                      : 1;  /* bit[2]    : noc_asp_power_idlereq 0:not req 1:idle req。 */
        unsigned int  iomcu_power_idlereq                        : 1;  /* bit[3]    : iomcu_power_idlereq 0:not req 1:idle req。 */
        unsigned int  aomcu_ao_noc_mainstatalarm_intmsk          : 1;  /* bit[4]    : aomcu_ao_noc_mainstatalarm_intmsk
                                                                                      0:int msk
                                                                                      1:int enable。 */
        unsigned int  aomcu_ao_noc_mainfault_intmsk              : 1;  /* bit[5]    : aomcu_ao_noc_mainfault_intmsk
                                                                                      0:int msk
                                                                                      1:int enable。 */
        unsigned int  asp_transaction_probe_mainstatalarm_intmsk : 1;  /* bit[6]    : asp_transaction_probe_mainstatalarm_intmsk
                                                                                      0:int msk
                                                                                      1:int enable。 */
        unsigned int  asp_error_probe_observer_mainfault_intmsk  : 1;  /* bit[7]    : asp_error_probe_observer_mainfault_intmsk
                                                                                      0:int msk
                                                                                      1:int enable。 */
        unsigned int  msk_noc_aobus_mmbuf_t_maintimeout          : 1;  /* bit[8]    : msk_noc_aobus_mmbuf_t_maintimeout
                                                                                      0:int msk
                                                                                      1:int enable。 */
        unsigned int  msk_noc_asp_cfg_t_maintimeout              : 1;  /* bit[9]    : msk_noc_asp_cfg_t_maintimeout
                                                                                      0:int msk
                                                                                      1:int enable。 */
        unsigned int  msk_iomcu_ahb_slv_maintimeout              : 1;  /* bit[10]   : msk_iomcu_ahb_slv_maintimeout
                                                                                      0:int msk
                                                                                      1:int enable。 */
        unsigned int  msk_iomcu_apb_slv_maintimeout              : 1;  /* bit[11]   : msk_iomcu_apb_slv_maintimeout
                                                                                      0:int msk
                                                                                      1:int enable。 */
        unsigned int  scperctrl7                                 : 4;  /* bit[12-15]: 保留。 */
        unsigned int  scperctrl7_msk                             : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                                      只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCPERCTRL7_UNION;
#endif
#define SOC_SCTRL_SCPERCTRL7_gt_clk_mmbuf_pending_en_START                     (0)
#define SOC_SCTRL_SCPERCTRL7_gt_clk_mmbuf_pending_en_END                       (0)
#define SOC_SCTRL_SCPERCTRL7_noc_asp_power_idlereq_START                       (2)
#define SOC_SCTRL_SCPERCTRL7_noc_asp_power_idlereq_END                         (2)
#define SOC_SCTRL_SCPERCTRL7_iomcu_power_idlereq_START                         (3)
#define SOC_SCTRL_SCPERCTRL7_iomcu_power_idlereq_END                           (3)
#define SOC_SCTRL_SCPERCTRL7_aomcu_ao_noc_mainstatalarm_intmsk_START           (4)
#define SOC_SCTRL_SCPERCTRL7_aomcu_ao_noc_mainstatalarm_intmsk_END             (4)
#define SOC_SCTRL_SCPERCTRL7_aomcu_ao_noc_mainfault_intmsk_START               (5)
#define SOC_SCTRL_SCPERCTRL7_aomcu_ao_noc_mainfault_intmsk_END                 (5)
#define SOC_SCTRL_SCPERCTRL7_asp_transaction_probe_mainstatalarm_intmsk_START  (6)
#define SOC_SCTRL_SCPERCTRL7_asp_transaction_probe_mainstatalarm_intmsk_END    (6)
#define SOC_SCTRL_SCPERCTRL7_asp_error_probe_observer_mainfault_intmsk_START   (7)
#define SOC_SCTRL_SCPERCTRL7_asp_error_probe_observer_mainfault_intmsk_END     (7)
#define SOC_SCTRL_SCPERCTRL7_msk_noc_aobus_mmbuf_t_maintimeout_START           (8)
#define SOC_SCTRL_SCPERCTRL7_msk_noc_aobus_mmbuf_t_maintimeout_END             (8)
#define SOC_SCTRL_SCPERCTRL7_msk_noc_asp_cfg_t_maintimeout_START               (9)
#define SOC_SCTRL_SCPERCTRL7_msk_noc_asp_cfg_t_maintimeout_END                 (9)
#define SOC_SCTRL_SCPERCTRL7_msk_iomcu_ahb_slv_maintimeout_START               (10)
#define SOC_SCTRL_SCPERCTRL7_msk_iomcu_ahb_slv_maintimeout_END                 (10)
#define SOC_SCTRL_SCPERCTRL7_msk_iomcu_apb_slv_maintimeout_START               (11)
#define SOC_SCTRL_SCPERCTRL7_msk_iomcu_apb_slv_maintimeout_END                 (11)
#define SOC_SCTRL_SCPERCTRL7_scperctrl7_START                                  (12)
#define SOC_SCTRL_SCPERCTRL7_scperctrl7_END                                    (15)
#define SOC_SCTRL_SCPERCTRL7_scperctrl7_msk_START                              (16)
#define SOC_SCTRL_SCPERCTRL7_scperctrl7_msk_END                                (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCINNERSTAT_UNION
 结构说明  : SCINNERSTAT 寄存器结构定义。地址偏移量:0x280，初值:0x02E00000，宽度:32
 寄存器说明: 内部状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  memory_repair_bypass    : 1;  /* bit[0]    : Memory repair bypass信号状态，来自efuse。 */
        unsigned int  hardw_ctrl_sel0         : 1;  /* bit[1]    : test_mode0信号经锁存后的状态。 */
        unsigned int  factest_mode            : 2;  /* bit[2-3]  : FACTEST_MODE[1:0]=
                                                                   2'b00: SYS EFUSE QA TEST
                                                                   2'b01: FAC_TEST。 */
        unsigned int  memory_repair_bypass_hw : 10; /* bit[4-13] : Memory repair bypass hardware信号状态，启动和gpu相关，来自efuse。 */
        unsigned int  isp_face_detect_fuse    : 1;  /* bit[14]   : ISP内部需求to control whether FD(face detect) works */
        unsigned int  reserved_0              : 1;  /* bit[15]   : 保留。 */
        unsigned int  ate_mode                : 3;  /* bit[16-18]: ATE_MODE[2:0]=
                                                                   3'b000 ABB TEST
                                                                   3'b001: Tsensor TEST
                                                                   3'b010: SYS EFUSE TEST
                                                                   3'b011: BISR EFUSE TEST
                                                                   3'b100: BOOT_MODE_NAND
                                                                   Other: ABB TEST。 */
        unsigned int  vote_clk_gt_sel_flag    : 7;  /* bit[19-25]: [25:24]:sel_clk_aobus_noc
                                                                   00：TCXO
                                                                   01：FPLL
                                                                   10：DDRPLL
                                                                   11: PPLL0
                                                                   最终配置值由iomcu，audio和此配置位投票确定，按照性能等级进行仲裁，DDRPLL>PPLL0>FPLL>TCXO
                                                                   [23:22]:sel_clk_mmbuf
                                                                   mmbuf时钟来源选择：
                                                                   00：TCXO
                                                                   01：FPLL
                                                                   1x: PPLL0
                                                                   最终配置值由iomcu，audio和此配置位投票确定，按照性能等级进行仲裁，PPLL0>FPLL>TCXO
                                                                   [21]:gt_aobus_noc_ini
                                                                   aobus ppll0输出门控
                                                                   0：时钟关闭；
                                                                   1：时钟开启。
                                                                   最终配置值由iomcu，audio和此配置位投票确定，有需求打开就时钟，所有请求都关闭才关闭时钟；
                                                                   [20]:gt_pclk_mmbufcfg
                                                                   0：时钟关闭；
                                                                   1：时钟开启。
                                                                   最终配置值由iomcu，audio和此配置位投票确定，有需求打开就时钟，所有请求都关闭才关闭时钟；
                                                                   [19]:gt_clk_mmbuf
                                                                   mmbuf pll分频前时钟门控配置：
                                                                   0：时钟关闭；
                                                                   1：时钟开启。
                                                                   最终配置值由iomcu，audio和此配置位投票确定，有需求打开就时钟，所有请求都关闭才关闭时钟。 */
        unsigned int  reserved_1              : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCINNERSTAT_UNION;
#endif
#define SOC_SCTRL_SCINNERSTAT_memory_repair_bypass_START     (0)
#define SOC_SCTRL_SCINNERSTAT_memory_repair_bypass_END       (0)
#define SOC_SCTRL_SCINNERSTAT_hardw_ctrl_sel0_START          (1)
#define SOC_SCTRL_SCINNERSTAT_hardw_ctrl_sel0_END            (1)
#define SOC_SCTRL_SCINNERSTAT_factest_mode_START             (2)
#define SOC_SCTRL_SCINNERSTAT_factest_mode_END               (3)
#define SOC_SCTRL_SCINNERSTAT_memory_repair_bypass_hw_START  (4)
#define SOC_SCTRL_SCINNERSTAT_memory_repair_bypass_hw_END    (13)
#define SOC_SCTRL_SCINNERSTAT_isp_face_detect_fuse_START     (14)
#define SOC_SCTRL_SCINNERSTAT_isp_face_detect_fuse_END       (14)
#define SOC_SCTRL_SCINNERSTAT_ate_mode_START                 (16)
#define SOC_SCTRL_SCINNERSTAT_ate_mode_END                   (18)
#define SOC_SCTRL_SCINNERSTAT_vote_clk_gt_sel_flag_START     (19)
#define SOC_SCTRL_SCINNERSTAT_vote_clk_gt_sel_flag_END       (25)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCDEEPSLEEPED_UNION
 结构说明  : SCDEEPSLEEPED 寄存器结构定义。地址偏移量:0x300，初值:0x00000000，宽度:32
 寄存器说明: 用于指示系统曾经进入过深度睡眠的状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  deepsleeped     : 1;  /* bit[0]    : 系统是否曾经进入过掉电状态机的DEEP SLEEP模式指示位。
                                                           0：系统没有进入过DEEP SLEEP状态；
                                                           1：系统曾经进入过DEEP SLEEP状态且没有被读清。
                                                           （对该比特位写1清除该位的状态到复位值）。 */
        unsigned int  reserved_0      : 3;  /* bit[1-3]  : 保留。 */
        unsigned int  sleeped         : 1;  /* bit[4]    : 系统是否曾经进入过系统状态机的 SLEEP模式指示位。
                                                           0：系统没有进入过SLEEP状态；
                                                           1：系统曾经进入过SLEEP状态且没有被读清。
                                                           （对该比特位写1清除该位的状态到复位值）。 */
        unsigned int  reserved_1      : 15; /* bit[5-19] : 保留。 */
        unsigned int  reserved_2      : 11; /* bit[20-30]: reserved_efuse0 
                                                           bit20:reserved的bit1987现用作coresight的deviceen信号复位ccs的bypass控制信号；
                                                           0：deviceen信号无法复位ccs
                                                           1：deviceen信号可以复位ccs
                                                           bit30:usbphy参考时钟19.2MHz选择
                                                           0：选择abb buffer输出时钟
                                                           1：选择ppll0输出时钟
                                                           other:reserved。 */
        unsigned int  reserved_3      : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_SCTRL_SCDEEPSLEEPED_UNION;
#endif
#define SOC_SCTRL_SCDEEPSLEEPED_deepsleeped_START      (0)
#define SOC_SCTRL_SCDEEPSLEEPED_deepsleeped_END        (0)
#define SOC_SCTRL_SCDEEPSLEEPED_sleeped_START          (4)
#define SOC_SCTRL_SCDEEPSLEEPED_sleeped_END            (4)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCMRBBUSYSTAT_UNION
 结构说明  : SCMRBBUSYSTAT 寄存器结构定义。地址偏移量:0x304，初值:0x00000000，宽度:32
 寄存器说明: MRB EFUSE BUSY状态指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mrb_efuse_busy : 32; /* bit[0-31]: 用于指示各个IP是否完成mem repair:
                                                         0代表完成，1代表未完成
                                                         用于指示各个IP是否需要做mem repair:
                                                         0代表修复，1代表不修复
                                                         AO_SUBSYS MRB0
                                                         PERI_SUBSYS(现在只看到LP_M3) MRB1
                                                         DEBUG_SEC_HSIC_PERI_SUBSYS MRB2
                                                         MODEM_SUBSYS MRB3
                                                         BBP_COM_TOP_PD MRB4
                                                         BBP_IRM_TOP_PD MRB5
                                                         A9_WRAP_PD MRB6
                                                         DSP_WRAP_PD MRB7
                                                         BBP_LTE_TOP_PD MRB8
                                                         A57_SUBSYS MRB9
                                                         A53_SUBSYS MRB10
                                                         AUDIO_SUBSYS MRB11
                                                         IOMUC_SUBSYS MRB12
                                                         MMBUF_SUBSYS MRB13
                                                         DSS MRB14
                                                         ISP_SUBSYS MRB15
                                                         IVP32_DSP_SUBSYS MRB16
                                                         VDEC MRB17
                                                         VENC MRB18
                                                         GPU_SUBSYS MRB19
                                                         BBP_CS_CORE MRB20。 */
    } reg;
} SOC_SCTRL_SCMRBBUSYSTAT_UNION;
#endif
#define SOC_SCTRL_SCMRBBUSYSTAT_mrb_efuse_busy_START  (0)
#define SOC_SCTRL_SCMRBBUSYSTAT_mrb_efuse_busy_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCSWADDR_UNION
 结构说明  : SCSWADDR 寄存器结构定义。地址偏移量:0x308，初值:0x00000000，宽度:32
 寄存器说明: 用于保存软件入口地址的寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  swaddr : 32; /* bit[0-31]: 保存软件的入口地址。 */
    } reg;
} SOC_SCTRL_SCSWADDR_UNION;
#endif
#define SOC_SCTRL_SCSWADDR_swaddr_START  (0)
#define SOC_SCTRL_SCSWADDR_swaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCDDRADDR_UNION
 结构说明  : SCDDRADDR 寄存器结构定义。地址偏移量:0x30C，初值:0x00000000，宽度:32
 寄存器说明: 用于保留DDR训练数据的地址的寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrtrainaddr : 32; /* bit[0-31]: 保存DDR训练数据的地址。 */
    } reg;
} SOC_SCTRL_SCDDRADDR_UNION;
#endif
#define SOC_SCTRL_SCDDRADDR_ddrtrainaddr_START  (0)
#define SOC_SCTRL_SCDDRADDR_ddrtrainaddr_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCDDRDATA_UNION
 结构说明  : SCDDRDATA 寄存器结构定义。地址偏移量:0x310，初值:0x00000000，宽度:32
 寄存器说明: 用于保存DDR训练数据的寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrtraindata : 32; /* bit[0-31]: 保存DDR的训练数据。 */
    } reg;
} SOC_SCTRL_SCDDRDATA_UNION;
#endif
#define SOC_SCTRL_SCDDRDATA_ddrtraindata_START  (0)
#define SOC_SCTRL_SCDDRDATA_ddrtraindata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA0_UNION
 结构说明  : SCBAKDATA0 寄存器结构定义。地址偏移量:0x314，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器0，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA0_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA0_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA0_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA1_UNION
 结构说明  : SCBAKDATA1 寄存器结构定义。地址偏移量:0x318，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器1，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA1_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA1_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA1_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA2_UNION
 结构说明  : SCBAKDATA2 寄存器结构定义。地址偏移量:0x31C，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器2，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA2_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA2_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA2_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA3_UNION
 结构说明  : SCBAKDATA3 寄存器结构定义。地址偏移量:0x320，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器3，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA3_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA3_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA3_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA4_UNION
 结构说明  : SCBAKDATA4 寄存器结构定义。地址偏移量:0x324，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器4，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA4_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA4_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA4_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA5_UNION
 结构说明  : SCBAKDATA5 寄存器结构定义。地址偏移量:0x328，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器5，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA5_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA5_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA5_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA6_UNION
 结构说明  : SCBAKDATA6 寄存器结构定义。地址偏移量:0x32C，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器6，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA6_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA6_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA6_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA7_UNION
 结构说明  : SCBAKDATA7 寄存器结构定义。地址偏移量:0x330，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器7，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA7_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA7_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA7_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA8_UNION
 结构说明  : SCBAKDATA8 寄存器结构定义。地址偏移量:0x334，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器8，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA8_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA8_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA8_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA9_UNION
 结构说明  : SCBAKDATA9 寄存器结构定义。地址偏移量:0x338，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器9，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA9_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA9_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA9_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA10_UNION
 结构说明  : SCBAKDATA10 寄存器结构定义。地址偏移量:0x33C，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器10，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA10_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA10_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA10_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA11_UNION
 结构说明  : SCBAKDATA11 寄存器结构定义。地址偏移量:0x340，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器11，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA11_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA11_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA11_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA12_UNION
 结构说明  : SCBAKDATA12 寄存器结构定义。地址偏移量:0x344，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器12。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器12，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA12_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA12_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA12_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA13_UNION
 结构说明  : SCBAKDATA13 寄存器结构定义。地址偏移量:0x348，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器13。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器13，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA13_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA13_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA13_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA14_UNION
 结构说明  : SCBAKDATA14 寄存器结构定义。地址偏移量:0x34C，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器14。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器14，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA14_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA14_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA14_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBAKDATA15_UNION
 结构说明  : SCBAKDATA15 寄存器结构定义。地址偏移量:0x350，初值:0x00000000，宽度:32
 寄存器说明: 用于软件使用的存储数据寄存器15。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bakdata : 32; /* bit[0-31]: 给软件预留的数据寄存器15，用于临时数据的缓存。 */
    } reg;
} SOC_SCTRL_SCBAKDATA15_UNION;
#endif
#define SOC_SCTRL_SCBAKDATA15_bakdata_START  (0)
#define SOC_SCTRL_SCBAKDATA15_bakdata_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCINT_GATHER_STAT_UNION
 结构说明  : SCINT_GATHER_STAT 寄存器结构定义。地址偏移量:0x450，初值:0x00000000，宽度:32
 寄存器说明: 聚合后的中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_wakeup_sys : 1;  /* bit[0]   : 1：中断有效；
                                                         0：中断无效；
                                                         注：该中断状态是已经考虑中断屏蔽配置之后的状态。 */
        unsigned int  drx0_int       : 1;  /* bit[1]   : 1：中断有效；
                                                         0：中断无效；
                                                         注：该中断状态是已经考虑中断屏蔽配置之后的状态。 */
        unsigned int  drx1_int       : 1;  /* bit[2]   : 1：中断有效；
                                                         0：中断无效；
                                                         注：该中断状态是已经考虑中断屏蔽配置之后的状态。 */
        unsigned int  notdrx_int     : 1;  /* bit[3]   : 1：中断有效；
                                                         0：中断无效；
                                                         注：该中断状态是已经考虑中断屏蔽配置之后的状态。 */
        unsigned int  reserved       : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCINT_GATHER_STAT_UNION;
#endif
#define SOC_SCTRL_SCINT_GATHER_STAT_int_wakeup_sys_START  (0)
#define SOC_SCTRL_SCINT_GATHER_STAT_int_wakeup_sys_END    (0)
#define SOC_SCTRL_SCINT_GATHER_STAT_drx0_int_START        (1)
#define SOC_SCTRL_SCINT_GATHER_STAT_drx0_int_END          (1)
#define SOC_SCTRL_SCINT_GATHER_STAT_drx1_int_START        (2)
#define SOC_SCTRL_SCINT_GATHER_STAT_drx1_int_END          (2)
#define SOC_SCTRL_SCINT_GATHER_STAT_notdrx_int_START      (3)
#define SOC_SCTRL_SCINT_GATHER_STAT_notdrx_int_END        (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCINT_MASK_UNION
 结构说明  : SCINT_MASK 寄存器结构定义。地址偏移量:0x454，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio_22_int             : 1;  /* bit[0] : 中断屏蔽寄存器。
                                                                0：屏蔽有效；
                                                                1：屏蔽无效。 */
        unsigned int  gpio_23_int             : 1;  /* bit[1] : 含义同bit0。 */
        unsigned int  gpio_24_int             : 1;  /* bit[2] : 含义同bit0。 */
        unsigned int  gpio_25_int             : 1;  /* bit[3] : 含义同bit0。 */
        unsigned int  gpio_26_int             : 1;  /* bit[4] : 含义同bit0。 */
        unsigned int  gpio_27_int             : 1;  /* bit[5] : 含义同bit0。 */
        unsigned int  rtc_int                 : 1;  /* bit[6] : 含义同bit0。 */
        unsigned int  rtc1_int                : 1;  /* bit[7] : 含义同bit0。 */
        unsigned int  timer00_int             : 1;  /* bit[8] : 含义同bit0。 */
        unsigned int  timer01_int             : 1;  /* bit[9] : 含义同bit0。 */
        unsigned int  timer10_int             : 1;  /* bit[10]: 含义同bit0。 */
        unsigned int  timer11_int             : 1;  /* bit[11]: 含义同bit0。 */
        unsigned int  timer20_int             : 1;  /* bit[12]: 含义同bit0。 */
        unsigned int  timer21_int             : 1;  /* bit[13]: 含义同bit0。 */
        unsigned int  timer30_int             : 1;  /* bit[14]: 含义同bit0。 */
        unsigned int  timer31_int             : 1;  /* bit[15]: 含义同bit0。 */
        unsigned int  timer40_int             : 1;  /* bit[16]: 含义同bit0。 */
        unsigned int  timer41_int             : 1;  /* bit[17]: 含义同bit0。 */
        unsigned int  timer50_int             : 1;  /* bit[18]: 含义同bit0。 */
        unsigned int  timer51_int             : 1;  /* bit[19]: 含义同bit0。 */
        unsigned int  timer60_int             : 1;  /* bit[20]: 含义同bit0。 */
        unsigned int  timer61_int             : 1;  /* bit[21]: 含义同bit0。 */
        unsigned int  timer70_int             : 1;  /* bit[22]: 含义同bit0。 */
        unsigned int  timer71_int             : 1;  /* bit[23]: 含义同bit0。 */
        unsigned int  timer80_int             : 1;  /* bit[24]: 含义同bit0。 */
        unsigned int  timer81_int             : 1;  /* bit[25]: 含义同bit0。 */
        unsigned int  intr_asp_ipc_arm        : 1;  /* bit[26]: 含义同bit0。 */
        unsigned int  intr_asp_watchdog       : 1;  /* bit[27]: 含义同bit0。 */
        unsigned int  intr_iomcu_wdog         : 1;  /* bit[28]: 含义同bit0。 */
        unsigned int  intr_iomcu_gpio_comb    : 1;  /* bit[29]: 屏蔽IOMCU GPIO中断唤醒晶振和系统。 */
        unsigned int  intr_iomcu_gpio_comb_sc : 1;  /* bit[30]: 屏蔽IOMCU GPIO中断唤醒系统，当bit 30为0且bit 29为1时，只唤醒晶振；bit 30和29都为1时，为一般唤醒中断。 */
        unsigned int  intr_wakeup_iomcu       : 1;  /* bit[31]: 含义同bit0。 */
    } reg;
} SOC_SCTRL_SCINT_MASK_UNION;
#endif
#define SOC_SCTRL_SCINT_MASK_gpio_22_int_START              (0)
#define SOC_SCTRL_SCINT_MASK_gpio_22_int_END                (0)
#define SOC_SCTRL_SCINT_MASK_gpio_23_int_START              (1)
#define SOC_SCTRL_SCINT_MASK_gpio_23_int_END                (1)
#define SOC_SCTRL_SCINT_MASK_gpio_24_int_START              (2)
#define SOC_SCTRL_SCINT_MASK_gpio_24_int_END                (2)
#define SOC_SCTRL_SCINT_MASK_gpio_25_int_START              (3)
#define SOC_SCTRL_SCINT_MASK_gpio_25_int_END                (3)
#define SOC_SCTRL_SCINT_MASK_gpio_26_int_START              (4)
#define SOC_SCTRL_SCINT_MASK_gpio_26_int_END                (4)
#define SOC_SCTRL_SCINT_MASK_gpio_27_int_START              (5)
#define SOC_SCTRL_SCINT_MASK_gpio_27_int_END                (5)
#define SOC_SCTRL_SCINT_MASK_rtc_int_START                  (6)
#define SOC_SCTRL_SCINT_MASK_rtc_int_END                    (6)
#define SOC_SCTRL_SCINT_MASK_rtc1_int_START                 (7)
#define SOC_SCTRL_SCINT_MASK_rtc1_int_END                   (7)
#define SOC_SCTRL_SCINT_MASK_timer00_int_START              (8)
#define SOC_SCTRL_SCINT_MASK_timer00_int_END                (8)
#define SOC_SCTRL_SCINT_MASK_timer01_int_START              (9)
#define SOC_SCTRL_SCINT_MASK_timer01_int_END                (9)
#define SOC_SCTRL_SCINT_MASK_timer10_int_START              (10)
#define SOC_SCTRL_SCINT_MASK_timer10_int_END                (10)
#define SOC_SCTRL_SCINT_MASK_timer11_int_START              (11)
#define SOC_SCTRL_SCINT_MASK_timer11_int_END                (11)
#define SOC_SCTRL_SCINT_MASK_timer20_int_START              (12)
#define SOC_SCTRL_SCINT_MASK_timer20_int_END                (12)
#define SOC_SCTRL_SCINT_MASK_timer21_int_START              (13)
#define SOC_SCTRL_SCINT_MASK_timer21_int_END                (13)
#define SOC_SCTRL_SCINT_MASK_timer30_int_START              (14)
#define SOC_SCTRL_SCINT_MASK_timer30_int_END                (14)
#define SOC_SCTRL_SCINT_MASK_timer31_int_START              (15)
#define SOC_SCTRL_SCINT_MASK_timer31_int_END                (15)
#define SOC_SCTRL_SCINT_MASK_timer40_int_START              (16)
#define SOC_SCTRL_SCINT_MASK_timer40_int_END                (16)
#define SOC_SCTRL_SCINT_MASK_timer41_int_START              (17)
#define SOC_SCTRL_SCINT_MASK_timer41_int_END                (17)
#define SOC_SCTRL_SCINT_MASK_timer50_int_START              (18)
#define SOC_SCTRL_SCINT_MASK_timer50_int_END                (18)
#define SOC_SCTRL_SCINT_MASK_timer51_int_START              (19)
#define SOC_SCTRL_SCINT_MASK_timer51_int_END                (19)
#define SOC_SCTRL_SCINT_MASK_timer60_int_START              (20)
#define SOC_SCTRL_SCINT_MASK_timer60_int_END                (20)
#define SOC_SCTRL_SCINT_MASK_timer61_int_START              (21)
#define SOC_SCTRL_SCINT_MASK_timer61_int_END                (21)
#define SOC_SCTRL_SCINT_MASK_timer70_int_START              (22)
#define SOC_SCTRL_SCINT_MASK_timer70_int_END                (22)
#define SOC_SCTRL_SCINT_MASK_timer71_int_START              (23)
#define SOC_SCTRL_SCINT_MASK_timer71_int_END                (23)
#define SOC_SCTRL_SCINT_MASK_timer80_int_START              (24)
#define SOC_SCTRL_SCINT_MASK_timer80_int_END                (24)
#define SOC_SCTRL_SCINT_MASK_timer81_int_START              (25)
#define SOC_SCTRL_SCINT_MASK_timer81_int_END                (25)
#define SOC_SCTRL_SCINT_MASK_intr_asp_ipc_arm_START         (26)
#define SOC_SCTRL_SCINT_MASK_intr_asp_ipc_arm_END           (26)
#define SOC_SCTRL_SCINT_MASK_intr_asp_watchdog_START        (27)
#define SOC_SCTRL_SCINT_MASK_intr_asp_watchdog_END          (27)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_wdog_START          (28)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_wdog_END            (28)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_gpio_comb_START     (29)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_gpio_comb_END       (29)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_gpio_comb_sc_START  (30)
#define SOC_SCTRL_SCINT_MASK_intr_iomcu_gpio_comb_sc_END    (30)
#define SOC_SCTRL_SCINT_MASK_intr_wakeup_iomcu_START        (31)
#define SOC_SCTRL_SCINT_MASK_intr_wakeup_iomcu_END          (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCINT_STAT_UNION
 结构说明  : SCINT_STAT 寄存器结构定义。地址偏移量:0x458，初值:0x00000000，宽度:32
 寄存器说明: 原始中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpio_22_int          : 1;  /* bit[0] : 中断状态寄存器。
                                                             0：中断无效；
                                                             1：中断有效。 */
        unsigned int  gpio_23_int          : 1;  /* bit[1] : 含义同bit0。 */
        unsigned int  gpio_24_int          : 1;  /* bit[2] : 含义同bit0。 */
        unsigned int  gpio_25_int          : 1;  /* bit[3] : 含义同bit0。 */
        unsigned int  gpio_26_int          : 1;  /* bit[4] : 含义同bit0。 */
        unsigned int  gpio_27_int          : 1;  /* bit[5] : 含义同bit0。 */
        unsigned int  rtc_int              : 1;  /* bit[6] : 含义同bit0。 */
        unsigned int  rtc1_int             : 1;  /* bit[7] : 含义同bit0。 */
        unsigned int  timer00_int          : 1;  /* bit[8] : 含义同bit0。 */
        unsigned int  timer01_int          : 1;  /* bit[9] : 含义同bit0。 */
        unsigned int  timer10_int          : 1;  /* bit[10]: 含义同bit0。 */
        unsigned int  timer11_int          : 1;  /* bit[11]: 含义同bit0。 */
        unsigned int  timer20_int          : 1;  /* bit[12]: 含义同bit0。 */
        unsigned int  timer21_int          : 1;  /* bit[13]: 含义同bit0。 */
        unsigned int  timer30_int          : 1;  /* bit[14]: 含义同bit0。 */
        unsigned int  timer31_int          : 1;  /* bit[15]: 含义同bit0。 */
        unsigned int  timer40_int          : 1;  /* bit[16]: 含义同bit0。 */
        unsigned int  timer41_int          : 1;  /* bit[17]: 含义同bit0。 */
        unsigned int  timer50_int          : 1;  /* bit[18]: 含义同bit0。 */
        unsigned int  timer51_int          : 1;  /* bit[19]: 含义同bit0。 */
        unsigned int  timer60_int          : 1;  /* bit[20]: 含义同bit0。 */
        unsigned int  timer61_int          : 1;  /* bit[21]: 含义同bit0。 */
        unsigned int  timer70_int          : 1;  /* bit[22]: 含义同bit0。 */
        unsigned int  timer71_int          : 1;  /* bit[23]: 含义同bit0。 */
        unsigned int  timer80_int          : 1;  /* bit[24]: 含义同bit0。 */
        unsigned int  timer81_int          : 1;  /* bit[25]: 含义同bit0。 */
        unsigned int  intr_asp_ipc_arm     : 1;  /* bit[26]: 含义同bit0。 */
        unsigned int  intr_asp_watchdog    : 1;  /* bit[27]: 含义同bit0。 */
        unsigned int  intr_iomcu_wdog      : 1;  /* bit[28]: 含义同bit0。 */
        unsigned int  intr_iomcu_gpio_comb : 1;  /* bit[29]: 含义同bit0。 */
        unsigned int  intr_wakeup_iomcu    : 1;  /* bit[30]: 含义同bit0。 */
        unsigned int  reserved             : 1;  /* bit[31]: 保留。 */
    } reg;
} SOC_SCTRL_SCINT_STAT_UNION;
#endif
#define SOC_SCTRL_SCINT_STAT_gpio_22_int_START           (0)
#define SOC_SCTRL_SCINT_STAT_gpio_22_int_END             (0)
#define SOC_SCTRL_SCINT_STAT_gpio_23_int_START           (1)
#define SOC_SCTRL_SCINT_STAT_gpio_23_int_END             (1)
#define SOC_SCTRL_SCINT_STAT_gpio_24_int_START           (2)
#define SOC_SCTRL_SCINT_STAT_gpio_24_int_END             (2)
#define SOC_SCTRL_SCINT_STAT_gpio_25_int_START           (3)
#define SOC_SCTRL_SCINT_STAT_gpio_25_int_END             (3)
#define SOC_SCTRL_SCINT_STAT_gpio_26_int_START           (4)
#define SOC_SCTRL_SCINT_STAT_gpio_26_int_END             (4)
#define SOC_SCTRL_SCINT_STAT_gpio_27_int_START           (5)
#define SOC_SCTRL_SCINT_STAT_gpio_27_int_END             (5)
#define SOC_SCTRL_SCINT_STAT_rtc_int_START               (6)
#define SOC_SCTRL_SCINT_STAT_rtc_int_END                 (6)
#define SOC_SCTRL_SCINT_STAT_rtc1_int_START              (7)
#define SOC_SCTRL_SCINT_STAT_rtc1_int_END                (7)
#define SOC_SCTRL_SCINT_STAT_timer00_int_START           (8)
#define SOC_SCTRL_SCINT_STAT_timer00_int_END             (8)
#define SOC_SCTRL_SCINT_STAT_timer01_int_START           (9)
#define SOC_SCTRL_SCINT_STAT_timer01_int_END             (9)
#define SOC_SCTRL_SCINT_STAT_timer10_int_START           (10)
#define SOC_SCTRL_SCINT_STAT_timer10_int_END             (10)
#define SOC_SCTRL_SCINT_STAT_timer11_int_START           (11)
#define SOC_SCTRL_SCINT_STAT_timer11_int_END             (11)
#define SOC_SCTRL_SCINT_STAT_timer20_int_START           (12)
#define SOC_SCTRL_SCINT_STAT_timer20_int_END             (12)
#define SOC_SCTRL_SCINT_STAT_timer21_int_START           (13)
#define SOC_SCTRL_SCINT_STAT_timer21_int_END             (13)
#define SOC_SCTRL_SCINT_STAT_timer30_int_START           (14)
#define SOC_SCTRL_SCINT_STAT_timer30_int_END             (14)
#define SOC_SCTRL_SCINT_STAT_timer31_int_START           (15)
#define SOC_SCTRL_SCINT_STAT_timer31_int_END             (15)
#define SOC_SCTRL_SCINT_STAT_timer40_int_START           (16)
#define SOC_SCTRL_SCINT_STAT_timer40_int_END             (16)
#define SOC_SCTRL_SCINT_STAT_timer41_int_START           (17)
#define SOC_SCTRL_SCINT_STAT_timer41_int_END             (17)
#define SOC_SCTRL_SCINT_STAT_timer50_int_START           (18)
#define SOC_SCTRL_SCINT_STAT_timer50_int_END             (18)
#define SOC_SCTRL_SCINT_STAT_timer51_int_START           (19)
#define SOC_SCTRL_SCINT_STAT_timer51_int_END             (19)
#define SOC_SCTRL_SCINT_STAT_timer60_int_START           (20)
#define SOC_SCTRL_SCINT_STAT_timer60_int_END             (20)
#define SOC_SCTRL_SCINT_STAT_timer61_int_START           (21)
#define SOC_SCTRL_SCINT_STAT_timer61_int_END             (21)
#define SOC_SCTRL_SCINT_STAT_timer70_int_START           (22)
#define SOC_SCTRL_SCINT_STAT_timer70_int_END             (22)
#define SOC_SCTRL_SCINT_STAT_timer71_int_START           (23)
#define SOC_SCTRL_SCINT_STAT_timer71_int_END             (23)
#define SOC_SCTRL_SCINT_STAT_timer80_int_START           (24)
#define SOC_SCTRL_SCINT_STAT_timer80_int_END             (24)
#define SOC_SCTRL_SCINT_STAT_timer81_int_START           (25)
#define SOC_SCTRL_SCINT_STAT_timer81_int_END             (25)
#define SOC_SCTRL_SCINT_STAT_intr_asp_ipc_arm_START      (26)
#define SOC_SCTRL_SCINT_STAT_intr_asp_ipc_arm_END        (26)
#define SOC_SCTRL_SCINT_STAT_intr_asp_watchdog_START     (27)
#define SOC_SCTRL_SCINT_STAT_intr_asp_watchdog_END       (27)
#define SOC_SCTRL_SCINT_STAT_intr_iomcu_wdog_START       (28)
#define SOC_SCTRL_SCINT_STAT_intr_iomcu_wdog_END         (28)
#define SOC_SCTRL_SCINT_STAT_intr_iomcu_gpio_comb_START  (29)
#define SOC_SCTRL_SCINT_STAT_intr_iomcu_gpio_comb_END    (29)
#define SOC_SCTRL_SCINT_STAT_intr_wakeup_iomcu_START     (30)
#define SOC_SCTRL_SCINT_STAT_intr_wakeup_iomcu_END       (30)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCDRX_INT_CFG_UNION
 结构说明  : SCDRX_INT_CFG 寄存器结构定义。地址偏移量:0x45C，初值:0x00000000，宽度:32
 寄存器说明: DRX中断分配配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drx0_int             : 1;  /* bit[0]   : ldrx2arm_wakeup_int
                                                               中断配置寄存器。
                                                               0：属于DRX0的中断；
                                                               1：属于DRX1的中断。 */
        unsigned int  drx1_int             : 1;  /* bit[1]   : tdrx2arm_wakeup_int，含义同bit0。 */
        unsigned int  drx2_int             : 1;  /* bit[2]   : g1_int_bbp_to_cpu_32k，含义同bit0。 */
        unsigned int  drx3_int             : 1;  /* bit[3]   : g2_int_bbp_to_cpu_32k，含义同bit0。 */
        unsigned int  drx4_int             : 1;  /* bit[4]   : intr_wbbp_arm_int02，含义同bit0。 */
        unsigned int  intr_iomcu_gpio_comb : 1;  /* bit[5]   : intr_iomcu_gpio_comb，含义同bit0。 */
        unsigned int  drx5_int             : 1;  /* bit[6]   : intr_cbbp_int01，含义同bit0。 */
        unsigned int  reserved_0           : 1;  /* bit[7]   : 保留。 */
        unsigned int  reserved_1           : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCDRX_INT_CFG_UNION;
#endif
#define SOC_SCTRL_SCDRX_INT_CFG_drx0_int_START              (0)
#define SOC_SCTRL_SCDRX_INT_CFG_drx0_int_END                (0)
#define SOC_SCTRL_SCDRX_INT_CFG_drx1_int_START              (1)
#define SOC_SCTRL_SCDRX_INT_CFG_drx1_int_END                (1)
#define SOC_SCTRL_SCDRX_INT_CFG_drx2_int_START              (2)
#define SOC_SCTRL_SCDRX_INT_CFG_drx2_int_END                (2)
#define SOC_SCTRL_SCDRX_INT_CFG_drx3_int_START              (3)
#define SOC_SCTRL_SCDRX_INT_CFG_drx3_int_END                (3)
#define SOC_SCTRL_SCDRX_INT_CFG_drx4_int_START              (4)
#define SOC_SCTRL_SCDRX_INT_CFG_drx4_int_END                (4)
#define SOC_SCTRL_SCDRX_INT_CFG_intr_iomcu_gpio_comb_START  (5)
#define SOC_SCTRL_SCDRX_INT_CFG_intr_iomcu_gpio_comb_END    (5)
#define SOC_SCTRL_SCDRX_INT_CFG_drx5_int_START              (6)
#define SOC_SCTRL_SCDRX_INT_CFG_drx5_int_END                (6)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCLPMCUWFI_INT_UNION
 结构说明  : SCLPMCUWFI_INT 寄存器结构定义。地址偏移量:0x460，初值:0x00000000，宽度:32
 寄存器说明: LPMCU WFI中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpmcu_wfi_int : 1;  /* bit[0]   : 写操作清除LPMCU_wfi_int中断；
                                                        读操作返回LPMCU_wfi_int中断状态。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCLPMCUWFI_INT_UNION;
#endif
#define SOC_SCTRL_SCLPMCUWFI_INT_lpmcu_wfi_int_START  (0)
#define SOC_SCTRL_SCLPMCUWFI_INT_lpmcu_wfi_int_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCINT_MASK1_UNION
 结构说明  : SCINT_MASK1 寄存器结构定义。地址偏移量:0x464，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drx0_int : 1;  /* bit[0]   : 中断屏蔽寄存器。
                                                   0：屏蔽有效；
                                                   1：屏蔽无效。 */
        unsigned int  drx1_int : 1;  /* bit[1]   : 含义同bit0。 */
        unsigned int  drx2_int : 1;  /* bit[2]   : 含义同bit0。 */
        unsigned int  drx3_int : 1;  /* bit[3]   : 含义同bit0。 */
        unsigned int  drx4_int : 1;  /* bit[4]   : 含义同bit0。 */
        unsigned int  drx5_int : 1;  /* bit[5]   : 含义同bit0。 */
        unsigned int  reserved_0: 1;  /* bit[6]   : 保留。 */
        unsigned int  reserved_1: 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCINT_MASK1_UNION;
#endif
#define SOC_SCTRL_SCINT_MASK1_drx0_int_START  (0)
#define SOC_SCTRL_SCINT_MASK1_drx0_int_END    (0)
#define SOC_SCTRL_SCINT_MASK1_drx1_int_START  (1)
#define SOC_SCTRL_SCINT_MASK1_drx1_int_END    (1)
#define SOC_SCTRL_SCINT_MASK1_drx2_int_START  (2)
#define SOC_SCTRL_SCINT_MASK1_drx2_int_END    (2)
#define SOC_SCTRL_SCINT_MASK1_drx3_int_START  (3)
#define SOC_SCTRL_SCINT_MASK1_drx3_int_END    (3)
#define SOC_SCTRL_SCINT_MASK1_drx4_int_START  (4)
#define SOC_SCTRL_SCINT_MASK1_drx4_int_END    (4)
#define SOC_SCTRL_SCINT_MASK1_drx5_int_START  (5)
#define SOC_SCTRL_SCINT_MASK1_drx5_int_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCINT_STAT1_UNION
 结构说明  : SCINT_STAT1 寄存器结构定义。地址偏移量:0x468，初值:0x00000000，宽度:32
 寄存器说明: 原始中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drx0_int : 1;  /* bit[0]   : ldrx2arm_wakeup_int
                                                   中断状态寄存器。
                                                   0：中断无效；
                                                   1：中断有效。 */
        unsigned int  drx1_int : 1;  /* bit[1]   : tdrx2arm_wakeup_int，含义同bit0。 */
        unsigned int  drx2_int : 1;  /* bit[2]   : g1_int_bbp_to_cpu_32k，含义同bit0。 */
        unsigned int  drx3_int : 1;  /* bit[3]   : g2_int_bbp_to_cpu_32k，含义同bit0 */
        unsigned int  drx4_int : 1;  /* bit[4]   : intr_wbbp_arm_int02，含义同bit0。 */
        unsigned int  drx5_int : 1;  /* bit[5]   : intr_cbbp_int01，含义同bit0。 */
        unsigned int  reserved_0: 1;  /* bit[6]   : 保留。 */
        unsigned int  reserved_1: 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCINT_STAT1_UNION;
#endif
#define SOC_SCTRL_SCINT_STAT1_drx0_int_START  (0)
#define SOC_SCTRL_SCINT_STAT1_drx0_int_END    (0)
#define SOC_SCTRL_SCINT_STAT1_drx1_int_START  (1)
#define SOC_SCTRL_SCINT_STAT1_drx1_int_END    (1)
#define SOC_SCTRL_SCINT_STAT1_drx2_int_START  (2)
#define SOC_SCTRL_SCINT_STAT1_drx2_int_END    (2)
#define SOC_SCTRL_SCINT_STAT1_drx3_int_START  (3)
#define SOC_SCTRL_SCINT_STAT1_drx3_int_END    (3)
#define SOC_SCTRL_SCINT_STAT1_drx4_int_START  (4)
#define SOC_SCTRL_SCINT_STAT1_drx4_int_END    (4)
#define SOC_SCTRL_SCINT_STAT1_drx5_int_START  (5)
#define SOC_SCTRL_SCINT_STAT1_drx5_int_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCINT_MASK2_UNION
 结构说明  : SCINT_MASK2 寄存器结构定义。地址偏移量:0x46C，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gic_irq_int0       : 1;  /* bit[0]   : 中断屏蔽寄存器。
                                                             0：屏蔽有效；
                                                             1：屏蔽无效。 */
        unsigned int  gic_irq_int1       : 1;  /* bit[1]   : 含义同bit0。 */
        unsigned int  gic_fiq_int2       : 1;  /* bit[2]   : 含义同bit0。 */
        unsigned int  gic_fiq_int3       : 1;  /* bit[3]   : 含义同bit0。 */
        unsigned int  intr_lpmcu_wdog    : 1;  /* bit[4]   : 含义同bit0。 */
        unsigned int  lpmcu_wfi_int      : 1;  /* bit[5]   : 含义同bit0。 */
        unsigned int  clk_monitor_intmsk : 1;  /* bit[6]   : 含义同bit0。 */
        unsigned int  reserved           : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCINT_MASK2_UNION;
#endif
#define SOC_SCTRL_SCINT_MASK2_gic_irq_int0_START        (0)
#define SOC_SCTRL_SCINT_MASK2_gic_irq_int0_END          (0)
#define SOC_SCTRL_SCINT_MASK2_gic_irq_int1_START        (1)
#define SOC_SCTRL_SCINT_MASK2_gic_irq_int1_END          (1)
#define SOC_SCTRL_SCINT_MASK2_gic_fiq_int2_START        (2)
#define SOC_SCTRL_SCINT_MASK2_gic_fiq_int2_END          (2)
#define SOC_SCTRL_SCINT_MASK2_gic_fiq_int3_START        (3)
#define SOC_SCTRL_SCINT_MASK2_gic_fiq_int3_END          (3)
#define SOC_SCTRL_SCINT_MASK2_intr_lpmcu_wdog_START     (4)
#define SOC_SCTRL_SCINT_MASK2_intr_lpmcu_wdog_END       (4)
#define SOC_SCTRL_SCINT_MASK2_lpmcu_wfi_int_START       (5)
#define SOC_SCTRL_SCINT_MASK2_lpmcu_wfi_int_END         (5)
#define SOC_SCTRL_SCINT_MASK2_clk_monitor_intmsk_START  (6)
#define SOC_SCTRL_SCINT_MASK2_clk_monitor_intmsk_END    (6)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCINT_STAT2_UNION
 结构说明  : SCINT_STAT2 寄存器结构定义。地址偏移量:0x470，初值:0x00000000，宽度:32
 寄存器说明: 原始中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gic_irq_int0     : 1;  /* bit[0]   : 中断状态寄存器。
                                                           0：中断无效；
                                                           1：中断有效。 */
        unsigned int  gic_irq_int1     : 1;  /* bit[1]   : 含义同bit0。 */
        unsigned int  gic_fiq_int0     : 1;  /* bit[2]   : 含义同bit0。 */
        unsigned int  gic_fiq_int1     : 1;  /* bit[3]   : 含义同bit0。 */
        unsigned int  intr_lpmcu_wdog  : 1;  /* bit[4]   : 含义同bit0。 */
        unsigned int  clk_monitor_intr : 1;  /* bit[5]   : 含义同bit0。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCINT_STAT2_UNION;
#endif
#define SOC_SCTRL_SCINT_STAT2_gic_irq_int0_START      (0)
#define SOC_SCTRL_SCINT_STAT2_gic_irq_int0_END        (0)
#define SOC_SCTRL_SCINT_STAT2_gic_irq_int1_START      (1)
#define SOC_SCTRL_SCINT_STAT2_gic_irq_int1_END        (1)
#define SOC_SCTRL_SCINT_STAT2_gic_fiq_int0_START      (2)
#define SOC_SCTRL_SCINT_STAT2_gic_fiq_int0_END        (2)
#define SOC_SCTRL_SCINT_STAT2_gic_fiq_int1_START      (3)
#define SOC_SCTRL_SCINT_STAT2_gic_fiq_int1_END        (3)
#define SOC_SCTRL_SCINT_STAT2_intr_lpmcu_wdog_START   (4)
#define SOC_SCTRL_SCINT_STAT2_intr_lpmcu_wdog_END     (4)
#define SOC_SCTRL_SCINT_STAT2_clk_monitor_intr_START  (5)
#define SOC_SCTRL_SCINT_STAT2_clk_monitor_intr_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCMALIBYPCFG_UNION
 结构说明  : SCMALIBYPCFG 寄存器结构定义。地址偏移量:0x48C，初值:0x00000001，宽度:32
 寄存器说明: MALI DBGACK BYPASS配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mali_dbgack_byp : 1;  /* bit[0]   : 0：bypass无效；
                                                          1：bypass有效。 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCMALIBYPCFG_UNION;
#endif
#define SOC_SCTRL_SCMALIBYPCFG_mali_dbgack_byp_START  (0)
#define SOC_SCTRL_SCMALIBYPCFG_mali_dbgack_byp_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCLPMCUCLKEN_UNION
 结构说明  : SCLPMCUCLKEN 寄存器结构定义。地址偏移量:0x500，初值:0x0000FFFF，宽度:32
 寄存器说明: LPMCU子系统时钟使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dapclkoff_sys_n        : 1;  /* bit[0]    : M3 DAPCLK时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  ssi1_clk_clkoff_sys_n  : 1;  /* bit[1]    : PMU_SSI1的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  rom_clk_clkoff_sys_n   : 1;  /* bit[2]    : BOOTROM的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  ram_clk_clkoff_sys_n   : 1;  /* bit[3]    : LP_RAM的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  aon_clk_clkoff_sys_n   : 1;  /* bit[4]    : AON_SUBSYS访问接口的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  ddrc_clk_clkoff_sys_n  : 1;  /* bit[5]    : DDRC配置接口的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  tsen_clk_clkoff_sys_n  : 1;  /* bit[6]    : TSENSORC的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  pmc_clk_clkoff_sys_n   : 1;  /* bit[7]    : PMC的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  uart_clk_clkoff_sys_n  : 1;  /* bit[8]    : UART的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  i2c_clk_clkoff_sys_n   : 1;  /* bit[9]    : PMU_I2C的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  ssi_clk_clkoff_sys_n   : 1;  /* bit[10]   : PMU_SSI的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  pcrg_clk_clkoff_sys_n  : 1;  /* bit[11]   : 外设CRG配置接口的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  nandc_clk_clkoff_sys_n : 1;  /* bit[12]   : NANDC的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  wdog_clk_clkoff_sys_n  : 1;  /* bit[13]   : LP_WDG的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  tim_clk_clkoff_sys_n   : 1;  /* bit[14]   : LP_TIMER的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  cssys_clk_clkoff_sys_n : 1;  /* bit[15]   : CSSYS访问接口的时钟门控系统控制。0：关闭时钟；1：开启时钟。 */
        unsigned int  sclpmcuclken_msk       : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                  只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCLPMCUCLKEN_UNION;
#endif
#define SOC_SCTRL_SCLPMCUCLKEN_dapclkoff_sys_n_START         (0)
#define SOC_SCTRL_SCLPMCUCLKEN_dapclkoff_sys_n_END           (0)
#define SOC_SCTRL_SCLPMCUCLKEN_ssi1_clk_clkoff_sys_n_START   (1)
#define SOC_SCTRL_SCLPMCUCLKEN_ssi1_clk_clkoff_sys_n_END     (1)
#define SOC_SCTRL_SCLPMCUCLKEN_rom_clk_clkoff_sys_n_START    (2)
#define SOC_SCTRL_SCLPMCUCLKEN_rom_clk_clkoff_sys_n_END      (2)
#define SOC_SCTRL_SCLPMCUCLKEN_ram_clk_clkoff_sys_n_START    (3)
#define SOC_SCTRL_SCLPMCUCLKEN_ram_clk_clkoff_sys_n_END      (3)
#define SOC_SCTRL_SCLPMCUCLKEN_aon_clk_clkoff_sys_n_START    (4)
#define SOC_SCTRL_SCLPMCUCLKEN_aon_clk_clkoff_sys_n_END      (4)
#define SOC_SCTRL_SCLPMCUCLKEN_ddrc_clk_clkoff_sys_n_START   (5)
#define SOC_SCTRL_SCLPMCUCLKEN_ddrc_clk_clkoff_sys_n_END     (5)
#define SOC_SCTRL_SCLPMCUCLKEN_tsen_clk_clkoff_sys_n_START   (6)
#define SOC_SCTRL_SCLPMCUCLKEN_tsen_clk_clkoff_sys_n_END     (6)
#define SOC_SCTRL_SCLPMCUCLKEN_pmc_clk_clkoff_sys_n_START    (7)
#define SOC_SCTRL_SCLPMCUCLKEN_pmc_clk_clkoff_sys_n_END      (7)
#define SOC_SCTRL_SCLPMCUCLKEN_uart_clk_clkoff_sys_n_START   (8)
#define SOC_SCTRL_SCLPMCUCLKEN_uart_clk_clkoff_sys_n_END     (8)
#define SOC_SCTRL_SCLPMCUCLKEN_i2c_clk_clkoff_sys_n_START    (9)
#define SOC_SCTRL_SCLPMCUCLKEN_i2c_clk_clkoff_sys_n_END      (9)
#define SOC_SCTRL_SCLPMCUCLKEN_ssi_clk_clkoff_sys_n_START    (10)
#define SOC_SCTRL_SCLPMCUCLKEN_ssi_clk_clkoff_sys_n_END      (10)
#define SOC_SCTRL_SCLPMCUCLKEN_pcrg_clk_clkoff_sys_n_START   (11)
#define SOC_SCTRL_SCLPMCUCLKEN_pcrg_clk_clkoff_sys_n_END     (11)
#define SOC_SCTRL_SCLPMCUCLKEN_nandc_clk_clkoff_sys_n_START  (12)
#define SOC_SCTRL_SCLPMCUCLKEN_nandc_clk_clkoff_sys_n_END    (12)
#define SOC_SCTRL_SCLPMCUCLKEN_wdog_clk_clkoff_sys_n_START   (13)
#define SOC_SCTRL_SCLPMCUCLKEN_wdog_clk_clkoff_sys_n_END     (13)
#define SOC_SCTRL_SCLPMCUCLKEN_tim_clk_clkoff_sys_n_START    (14)
#define SOC_SCTRL_SCLPMCUCLKEN_tim_clk_clkoff_sys_n_END      (14)
#define SOC_SCTRL_SCLPMCUCLKEN_cssys_clk_clkoff_sys_n_START  (15)
#define SOC_SCTRL_SCLPMCUCLKEN_cssys_clk_clkoff_sys_n_END    (15)
#define SOC_SCTRL_SCLPMCUCLKEN_sclpmcuclken_msk_START        (16)
#define SOC_SCTRL_SCLPMCUCLKEN_sclpmcuclken_msk_END          (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCLPMCURSTEN_UNION
 结构说明  : SCLPMCURSTEN 寄存器结构定义。地址偏移量:0x504，初值:0x00000000，宽度:32
 寄存器说明: LPMCU子系统软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_software_req       : 1;  /* bit[0]    : 0:无变化 1:SCLPMCURSTSTAT对应bit置1。 */
        unsigned int  coresight_soft_rst_req : 1;  /* bit[1]    : bit含义参考bit0。 */
        unsigned int  ssi1_soft_rst_req      : 1;  /* bit[2]    : bit含义参考bit0。 */
        unsigned int  rom_soft_rst_req       : 1;  /* bit[3]    : bit含义参考bit0。 */
        unsigned int  ram_soft_rst_req       : 1;  /* bit[4]    : bit含义参考bit0。 */
        unsigned int  aon_soft_rst_req       : 1;  /* bit[5]    : bit含义参考bit0。 */
        unsigned int  ddrc_soft_rst_req      : 1;  /* bit[6]    : bit含义参考bit0。 */
        unsigned int  tsen_soft_rst_req      : 1;  /* bit[7]    : bit含义参考bit0。 */
        unsigned int  pmc_soft_rst_req       : 1;  /* bit[8]    : bit含义参考bit0。 */
        unsigned int  uart_soft_rst_req      : 1;  /* bit[9]    : bit含义参考bit0。 */
        unsigned int  i2c_soft_rst_req       : 1;  /* bit[10]   : bit含义参考bit0。 */
        unsigned int  ssi_soft_rst_req       : 1;  /* bit[11]   : bit含义参考bit0。 */
        unsigned int  pcrg_soft_rst_req      : 1;  /* bit[12]   : bit含义参考bit0。 */
        unsigned int  nandc_soft_rst_req     : 1;  /* bit[13]   : bit含义参考bit0。 */
        unsigned int  wdog_soft_rst_req      : 1;  /* bit[14]   : bit含义参考bit0。 */
        unsigned int  tim_soft_rst_req       : 1;  /* bit[15]   : bit含义参考bit0。 */
        unsigned int  cssys_soft_rst_req     : 1;  /* bit[16]   : bit含义参考bit0。 */
        unsigned int  m3_lp_rst_req          : 1;  /* bit[17]   : bit含义参考bit0。 */
        unsigned int  reserved               : 14; /* bit[18-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCLPMCURSTEN_UNION;
#endif
#define SOC_SCTRL_SCLPMCURSTEN_rst_software_req_START        (0)
#define SOC_SCTRL_SCLPMCURSTEN_rst_software_req_END          (0)
#define SOC_SCTRL_SCLPMCURSTEN_coresight_soft_rst_req_START  (1)
#define SOC_SCTRL_SCLPMCURSTEN_coresight_soft_rst_req_END    (1)
#define SOC_SCTRL_SCLPMCURSTEN_ssi1_soft_rst_req_START       (2)
#define SOC_SCTRL_SCLPMCURSTEN_ssi1_soft_rst_req_END         (2)
#define SOC_SCTRL_SCLPMCURSTEN_rom_soft_rst_req_START        (3)
#define SOC_SCTRL_SCLPMCURSTEN_rom_soft_rst_req_END          (3)
#define SOC_SCTRL_SCLPMCURSTEN_ram_soft_rst_req_START        (4)
#define SOC_SCTRL_SCLPMCURSTEN_ram_soft_rst_req_END          (4)
#define SOC_SCTRL_SCLPMCURSTEN_aon_soft_rst_req_START        (5)
#define SOC_SCTRL_SCLPMCURSTEN_aon_soft_rst_req_END          (5)
#define SOC_SCTRL_SCLPMCURSTEN_ddrc_soft_rst_req_START       (6)
#define SOC_SCTRL_SCLPMCURSTEN_ddrc_soft_rst_req_END         (6)
#define SOC_SCTRL_SCLPMCURSTEN_tsen_soft_rst_req_START       (7)
#define SOC_SCTRL_SCLPMCURSTEN_tsen_soft_rst_req_END         (7)
#define SOC_SCTRL_SCLPMCURSTEN_pmc_soft_rst_req_START        (8)
#define SOC_SCTRL_SCLPMCURSTEN_pmc_soft_rst_req_END          (8)
#define SOC_SCTRL_SCLPMCURSTEN_uart_soft_rst_req_START       (9)
#define SOC_SCTRL_SCLPMCURSTEN_uart_soft_rst_req_END         (9)
#define SOC_SCTRL_SCLPMCURSTEN_i2c_soft_rst_req_START        (10)
#define SOC_SCTRL_SCLPMCURSTEN_i2c_soft_rst_req_END          (10)
#define SOC_SCTRL_SCLPMCURSTEN_ssi_soft_rst_req_START        (11)
#define SOC_SCTRL_SCLPMCURSTEN_ssi_soft_rst_req_END          (11)
#define SOC_SCTRL_SCLPMCURSTEN_pcrg_soft_rst_req_START       (12)
#define SOC_SCTRL_SCLPMCURSTEN_pcrg_soft_rst_req_END         (12)
#define SOC_SCTRL_SCLPMCURSTEN_nandc_soft_rst_req_START      (13)
#define SOC_SCTRL_SCLPMCURSTEN_nandc_soft_rst_req_END        (13)
#define SOC_SCTRL_SCLPMCURSTEN_wdog_soft_rst_req_START       (14)
#define SOC_SCTRL_SCLPMCURSTEN_wdog_soft_rst_req_END         (14)
#define SOC_SCTRL_SCLPMCURSTEN_tim_soft_rst_req_START        (15)
#define SOC_SCTRL_SCLPMCURSTEN_tim_soft_rst_req_END          (15)
#define SOC_SCTRL_SCLPMCURSTEN_cssys_soft_rst_req_START      (16)
#define SOC_SCTRL_SCLPMCURSTEN_cssys_soft_rst_req_END        (16)
#define SOC_SCTRL_SCLPMCURSTEN_m3_lp_rst_req_START           (17)
#define SOC_SCTRL_SCLPMCURSTEN_m3_lp_rst_req_END             (17)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCLPMCURSTDIS_UNION
 结构说明  : SCLPMCURSTDIS 寄存器结构定义。地址偏移量:0x508，初值:0x00000000，宽度:32
 寄存器说明: LPMCU子系统软复位撤离寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_software_req       : 1;  /* bit[0]    : 0:无变化 1:SCLPMCURSTSTAT对应bit清0。 */
        unsigned int  coresight_soft_rst_req : 1;  /* bit[1]    : bit含义参考bit0。 */
        unsigned int  ssi1_soft_rst_req      : 1;  /* bit[2]    : bit含义参考bit0。 */
        unsigned int  rom_soft_rst_req       : 1;  /* bit[3]    : bit含义参考bit0。 */
        unsigned int  ram_soft_rst_req       : 1;  /* bit[4]    : bit含义参考bit0。 */
        unsigned int  aon_soft_rst_req       : 1;  /* bit[5]    : bit含义参考bit0。 */
        unsigned int  ddrc_soft_rst_req      : 1;  /* bit[6]    : bit含义参考bit0。 */
        unsigned int  tsen_soft_rst_req      : 1;  /* bit[7]    : bit含义参考bit0。 */
        unsigned int  pmc_soft_rst_req       : 1;  /* bit[8]    : bit含义参考bit0。 */
        unsigned int  uart_soft_rst_req      : 1;  /* bit[9]    : bit含义参考bit0。 */
        unsigned int  i2c_soft_rst_req       : 1;  /* bit[10]   : bit含义参考bit0。 */
        unsigned int  ssi_soft_rst_req       : 1;  /* bit[11]   : bit含义参考bit0。 */
        unsigned int  pcrg_soft_rst_req      : 1;  /* bit[12]   : bit含义参考bit0。 */
        unsigned int  nandc_soft_rst_req     : 1;  /* bit[13]   : bit含义参考bit0。 */
        unsigned int  wdog_soft_rst_req      : 1;  /* bit[14]   : bit含义参考bit0。 */
        unsigned int  tim_soft_rst_req       : 1;  /* bit[15]   : bit含义参考bit0。 */
        unsigned int  cssys_soft_rst_req     : 1;  /* bit[16]   : bit含义参考bit0。 */
        unsigned int  m3_lp_rst_req          : 1;  /* bit[17]   : bit含义参考bit0。 */
        unsigned int  reserved               : 14; /* bit[18-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCLPMCURSTDIS_UNION;
#endif
#define SOC_SCTRL_SCLPMCURSTDIS_rst_software_req_START        (0)
#define SOC_SCTRL_SCLPMCURSTDIS_rst_software_req_END          (0)
#define SOC_SCTRL_SCLPMCURSTDIS_coresight_soft_rst_req_START  (1)
#define SOC_SCTRL_SCLPMCURSTDIS_coresight_soft_rst_req_END    (1)
#define SOC_SCTRL_SCLPMCURSTDIS_ssi1_soft_rst_req_START       (2)
#define SOC_SCTRL_SCLPMCURSTDIS_ssi1_soft_rst_req_END         (2)
#define SOC_SCTRL_SCLPMCURSTDIS_rom_soft_rst_req_START        (3)
#define SOC_SCTRL_SCLPMCURSTDIS_rom_soft_rst_req_END          (3)
#define SOC_SCTRL_SCLPMCURSTDIS_ram_soft_rst_req_START        (4)
#define SOC_SCTRL_SCLPMCURSTDIS_ram_soft_rst_req_END          (4)
#define SOC_SCTRL_SCLPMCURSTDIS_aon_soft_rst_req_START        (5)
#define SOC_SCTRL_SCLPMCURSTDIS_aon_soft_rst_req_END          (5)
#define SOC_SCTRL_SCLPMCURSTDIS_ddrc_soft_rst_req_START       (6)
#define SOC_SCTRL_SCLPMCURSTDIS_ddrc_soft_rst_req_END         (6)
#define SOC_SCTRL_SCLPMCURSTDIS_tsen_soft_rst_req_START       (7)
#define SOC_SCTRL_SCLPMCURSTDIS_tsen_soft_rst_req_END         (7)
#define SOC_SCTRL_SCLPMCURSTDIS_pmc_soft_rst_req_START        (8)
#define SOC_SCTRL_SCLPMCURSTDIS_pmc_soft_rst_req_END          (8)
#define SOC_SCTRL_SCLPMCURSTDIS_uart_soft_rst_req_START       (9)
#define SOC_SCTRL_SCLPMCURSTDIS_uart_soft_rst_req_END         (9)
#define SOC_SCTRL_SCLPMCURSTDIS_i2c_soft_rst_req_START        (10)
#define SOC_SCTRL_SCLPMCURSTDIS_i2c_soft_rst_req_END          (10)
#define SOC_SCTRL_SCLPMCURSTDIS_ssi_soft_rst_req_START        (11)
#define SOC_SCTRL_SCLPMCURSTDIS_ssi_soft_rst_req_END          (11)
#define SOC_SCTRL_SCLPMCURSTDIS_pcrg_soft_rst_req_START       (12)
#define SOC_SCTRL_SCLPMCURSTDIS_pcrg_soft_rst_req_END         (12)
#define SOC_SCTRL_SCLPMCURSTDIS_nandc_soft_rst_req_START      (13)
#define SOC_SCTRL_SCLPMCURSTDIS_nandc_soft_rst_req_END        (13)
#define SOC_SCTRL_SCLPMCURSTDIS_wdog_soft_rst_req_START       (14)
#define SOC_SCTRL_SCLPMCURSTDIS_wdog_soft_rst_req_END         (14)
#define SOC_SCTRL_SCLPMCURSTDIS_tim_soft_rst_req_START        (15)
#define SOC_SCTRL_SCLPMCURSTDIS_tim_soft_rst_req_END          (15)
#define SOC_SCTRL_SCLPMCURSTDIS_cssys_soft_rst_req_START      (16)
#define SOC_SCTRL_SCLPMCURSTDIS_cssys_soft_rst_req_END        (16)
#define SOC_SCTRL_SCLPMCURSTDIS_m3_lp_rst_req_START           (17)
#define SOC_SCTRL_SCLPMCURSTDIS_m3_lp_rst_req_END             (17)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCLPMCURSTSTAT_UNION
 结构说明  : SCLPMCURSTSTAT 寄存器结构定义。地址偏移量:0x50C，初值:0x00000000，宽度:32
 寄存器说明: LPMCU子系统软复位使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_software_req       : 1;  /* bit[0]    : M3 Core复位请求，有效时将会复位M3 Core内所有逻辑
                                                                  0：unrst req 1:rst req。 */
        unsigned int  coresight_soft_rst_req : 1;  /* bit[1]    : M3 CoreSight 系统软件复位请求，复位所有的coresight组件，bit含义参考bit0。 */
        unsigned int  ssi1_soft_rst_req      : 1;  /* bit[2]    : PMU_SSI1的复位请求。有效时将会复位PMU_SSI1所有逻辑，bit含义参考bit0。 */
        unsigned int  rom_soft_rst_req       : 1;  /* bit[3]    : BOOTROM的复位请求。有效时将会复位BOOTROM接口逻辑，bit含义参考bit0。 */
        unsigned int  ram_soft_rst_req       : 1;  /* bit[4]    : LP_RAM的复位请求。有效时将会复位LP_RAM接口逻辑，bit含义参考bit0。 */
        unsigned int  aon_soft_rst_req       : 1;  /* bit[5]    : AON_SUBSYS访问接口的复位请求。有效时将会复位访问AON_SUBSYS的接口逻辑，bit含义参考bit0。 */
        unsigned int  ddrc_soft_rst_req      : 1;  /* bit[6]    : DDRC配置接口的复位请求。有效时将会复位DDRC的配置接口逻辑，bit含义参考bit0。 */
        unsigned int  tsen_soft_rst_req      : 1;  /* bit[7]    : TSENSORC的复位请求。有效时将会复位TSENSORC所有逻辑，bit含义参考bit0。 */
        unsigned int  pmc_soft_rst_req       : 1;  /* bit[8]    : PMC的复位请求。有效时将会复位PMC的所有逻辑，bit含义参考bit0。 */
        unsigned int  uart_soft_rst_req      : 1;  /* bit[9]    : UART的复位请求。有效时将会复位UART所有逻辑，bit含义参考bit0。 */
        unsigned int  i2c_soft_rst_req       : 1;  /* bit[10]   : PMU_I2C的复位请求。有效时将会复位PMU_I2C所有逻辑，bit含义参考bit0。 */
        unsigned int  ssi_soft_rst_req       : 1;  /* bit[11]   : PMU_SSI的复位请求。有效时将会复位PMU_SSI所有逻辑，bit含义参考bit0。 */
        unsigned int  pcrg_soft_rst_req      : 1;  /* bit[12]   : 外设CRG配置接口的复位请求。有效时将会复位外设CRG的配置接口逻辑，bit含义参考bit0。 */
        unsigned int  nandc_soft_rst_req     : 1;  /* bit[13]   : NANDC的复位请求。有效时将会复位NANDC所有逻辑，bit含义参考bit0。 */
        unsigned int  wdog_soft_rst_req      : 1;  /* bit[14]   : LP_WDG的复位请求。有效时将会复位watchdog所有逻辑，bit含义参考bit0。 */
        unsigned int  tim_soft_rst_req       : 1;  /* bit[15]   : LP_TIMER的复位请求。有效时将会复位timer所有逻辑，bit含义参考bit0。 */
        unsigned int  cssys_soft_rst_req     : 1;  /* bit[16]   : CSSYS访问接口的复位请求。有效时将会复位访问CSSYS的接口逻辑，bit含义参考bit0。 */
        unsigned int  m3_lp_rst_req          : 1;  /* bit[17]   : lpm3 rst请求，bit含义参考bit0。 */
        unsigned int  reserved               : 14; /* bit[18-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCLPMCURSTSTAT_UNION;
#endif
#define SOC_SCTRL_SCLPMCURSTSTAT_rst_software_req_START        (0)
#define SOC_SCTRL_SCLPMCURSTSTAT_rst_software_req_END          (0)
#define SOC_SCTRL_SCLPMCURSTSTAT_coresight_soft_rst_req_START  (1)
#define SOC_SCTRL_SCLPMCURSTSTAT_coresight_soft_rst_req_END    (1)
#define SOC_SCTRL_SCLPMCURSTSTAT_ssi1_soft_rst_req_START       (2)
#define SOC_SCTRL_SCLPMCURSTSTAT_ssi1_soft_rst_req_END         (2)
#define SOC_SCTRL_SCLPMCURSTSTAT_rom_soft_rst_req_START        (3)
#define SOC_SCTRL_SCLPMCURSTSTAT_rom_soft_rst_req_END          (3)
#define SOC_SCTRL_SCLPMCURSTSTAT_ram_soft_rst_req_START        (4)
#define SOC_SCTRL_SCLPMCURSTSTAT_ram_soft_rst_req_END          (4)
#define SOC_SCTRL_SCLPMCURSTSTAT_aon_soft_rst_req_START        (5)
#define SOC_SCTRL_SCLPMCURSTSTAT_aon_soft_rst_req_END          (5)
#define SOC_SCTRL_SCLPMCURSTSTAT_ddrc_soft_rst_req_START       (6)
#define SOC_SCTRL_SCLPMCURSTSTAT_ddrc_soft_rst_req_END         (6)
#define SOC_SCTRL_SCLPMCURSTSTAT_tsen_soft_rst_req_START       (7)
#define SOC_SCTRL_SCLPMCURSTSTAT_tsen_soft_rst_req_END         (7)
#define SOC_SCTRL_SCLPMCURSTSTAT_pmc_soft_rst_req_START        (8)
#define SOC_SCTRL_SCLPMCURSTSTAT_pmc_soft_rst_req_END          (8)
#define SOC_SCTRL_SCLPMCURSTSTAT_uart_soft_rst_req_START       (9)
#define SOC_SCTRL_SCLPMCURSTSTAT_uart_soft_rst_req_END         (9)
#define SOC_SCTRL_SCLPMCURSTSTAT_i2c_soft_rst_req_START        (10)
#define SOC_SCTRL_SCLPMCURSTSTAT_i2c_soft_rst_req_END          (10)
#define SOC_SCTRL_SCLPMCURSTSTAT_ssi_soft_rst_req_START        (11)
#define SOC_SCTRL_SCLPMCURSTSTAT_ssi_soft_rst_req_END          (11)
#define SOC_SCTRL_SCLPMCURSTSTAT_pcrg_soft_rst_req_START       (12)
#define SOC_SCTRL_SCLPMCURSTSTAT_pcrg_soft_rst_req_END         (12)
#define SOC_SCTRL_SCLPMCURSTSTAT_nandc_soft_rst_req_START      (13)
#define SOC_SCTRL_SCLPMCURSTSTAT_nandc_soft_rst_req_END        (13)
#define SOC_SCTRL_SCLPMCURSTSTAT_wdog_soft_rst_req_START       (14)
#define SOC_SCTRL_SCLPMCURSTSTAT_wdog_soft_rst_req_END         (14)
#define SOC_SCTRL_SCLPMCURSTSTAT_tim_soft_rst_req_START        (15)
#define SOC_SCTRL_SCLPMCURSTSTAT_tim_soft_rst_req_END          (15)
#define SOC_SCTRL_SCLPMCURSTSTAT_cssys_soft_rst_req_START      (16)
#define SOC_SCTRL_SCLPMCURSTSTAT_cssys_soft_rst_req_END        (16)
#define SOC_SCTRL_SCLPMCURSTSTAT_m3_lp_rst_req_START           (17)
#define SOC_SCTRL_SCLPMCURSTSTAT_m3_lp_rst_req_END             (17)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCLPMCUCTRL_UNION
 结构说明  : SCLPMCUCTRL 寄存器结构定义。地址偏移量:0x510，初值:0x000002E8，宽度:32
 寄存器说明: LPMCU子系统控制配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  m3_lp_gnspwm_clkoff_n : 1;  /* bit[0]    : m3_lp_clkoff_n[16]是gnspwm的时钟软门控
                                                                 0：关闭时钟；1：开启时钟。 */
        unsigned int  mpudisable            : 1;  /* bit[1]    : M3内存保护单元除能信号
                                                                 0:enable 1:disable。 */
        unsigned int  nmi_in                : 1;  /* bit[2]    : 外部不可屏蔽中断输入
                                                                 0：no int 1:int occur。 */
        unsigned int  bus_div_clk_sel       : 2;  /* bit[3-4]  : bus_div_clk分频比选择信号
                                                                 00：bus_clk的1分频
                                                                 01：bus_clk的2分频
                                                                 10：bus_clk的3分频
                                                                 11：bus_clk的4分频。 */
        unsigned int  sysresetreq_en        : 1;  /* bit[5]    : M3 SYSRESETREQ使能控制。
                                                                 0：M3自身的系统复位请求不会被M3 CRG响应。1：M3自身的系统复位请求可被M3 CRG响应。 */
        unsigned int  reserved_0            : 5;  /* bit[6-10] : 保留。 */
        unsigned int  lpmcuidle_bypass      : 1;  /* bit[11]   : 系统状态机LPMCU IDLE判断BYPASS控制：
                                                                 1'b1：bypass有效
                                                                 1'b0：bypass无效。 */
        unsigned int  reserved_1            : 12; /* bit[12-23]: 保留。 */
        unsigned int  reserved_2            : 8;  /* bit[24-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCLPMCUCTRL_UNION;
#endif
#define SOC_SCTRL_SCLPMCUCTRL_m3_lp_gnspwm_clkoff_n_START  (0)
#define SOC_SCTRL_SCLPMCUCTRL_m3_lp_gnspwm_clkoff_n_END    (0)
#define SOC_SCTRL_SCLPMCUCTRL_mpudisable_START             (1)
#define SOC_SCTRL_SCLPMCUCTRL_mpudisable_END               (1)
#define SOC_SCTRL_SCLPMCUCTRL_nmi_in_START                 (2)
#define SOC_SCTRL_SCLPMCUCTRL_nmi_in_END                   (2)
#define SOC_SCTRL_SCLPMCUCTRL_bus_div_clk_sel_START        (3)
#define SOC_SCTRL_SCLPMCUCTRL_bus_div_clk_sel_END          (4)
#define SOC_SCTRL_SCLPMCUCTRL_sysresetreq_en_START         (5)
#define SOC_SCTRL_SCLPMCUCTRL_sysresetreq_en_END           (5)
#define SOC_SCTRL_SCLPMCUCTRL_lpmcuidle_bypass_START       (11)
#define SOC_SCTRL_SCLPMCUCTRL_lpmcuidle_bypass_END         (11)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCLPMCUSTAT_UNION
 结构说明  : SCLPMCUSTAT 寄存器结构定义。地址偏移量:0x514，初值:0x00000000，宽度:32
 寄存器说明: LPMCU子系统状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sysresetreq_sign_out_stat : 1;  /* bit[0]   : M3 SYSRESETREQ复位事件标志输出
                                                                    读清
                                                                    0:no rst 1:rst。 */
        unsigned int  sleeping                  : 1;  /* bit[1]   : M3 休眠状态指示信号
                                                                    0:no sleeping 1:sleeping。 */
        unsigned int  lockup                    : 1;  /* bit[2]   : M3 core锁死指示信号
                                                                    0: no lockup 1:lockup。 */
        unsigned int  halted                    : 1;  /* bit[3]   : M3 core停机指示信号（debug状态）
                                                                    0：no halt 1:halted。 */
        unsigned int  reserved                  : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCLPMCUSTAT_UNION;
#endif
#define SOC_SCTRL_SCLPMCUSTAT_sysresetreq_sign_out_stat_START  (0)
#define SOC_SCTRL_SCLPMCUSTAT_sysresetreq_sign_out_stat_END    (0)
#define SOC_SCTRL_SCLPMCUSTAT_sleeping_START                   (1)
#define SOC_SCTRL_SCLPMCUSTAT_sleeping_END                     (1)
#define SOC_SCTRL_SCLPMCUSTAT_lockup_START                     (2)
#define SOC_SCTRL_SCLPMCUSTAT_lockup_END                       (2)
#define SOC_SCTRL_SCLPMCUSTAT_halted_START                     (3)
#define SOC_SCTRL_SCLPMCUSTAT_halted_END                       (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCLPMCURAMCTRL_UNION
 结构说明  : SCLPMCURAMCTRL 寄存器结构定义。地址偏移量:0x518，初值:0x00000000，宽度:32
 寄存器说明: LPMCU RAM 控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpramctrl_sel       : 1;  /* bit[0]    : LPMCU ram低功耗模式控制选择：
                                                               1：软件控制
                                                               0：状态机控制。 */
        unsigned int  lpram0_mod          : 2;  /* bit[1-2]  : LPMCU ram0低功耗模式配置
                                                               00;normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down。 */
        unsigned int  lpram1_mod          : 2;  /* bit[3-4]  : LPMCU ram1低功耗模式配置
                                                               00;normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down。 */
        unsigned int  lpram2_mod          : 2;  /* bit[5-6]  : LPMCU ram2低功耗模式配置
                                                               00;normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down。 */
        unsigned int  lpram3_mod          : 2;  /* bit[7-8]  : LPMCU ram3低功耗模式配置
                                                               00;normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down。 */
        unsigned int  lpram0ctrl_soft     : 3;  /* bit[9-11] : LPMCU ram0低功耗控制信号软件配置：
                                                               bit9:slp
                                                               bit10:dslp
                                                               bit11:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown。 */
        unsigned int  lpram1ctrl_soft     : 3;  /* bit[12-14]: LPMCU ram1低功耗控制信号软件配置：
                                                               bit12:slp
                                                               bit13:dslp
                                                               bit14:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown。 */
        unsigned int  lpram2ctrl_soft     : 3;  /* bit[15-17]: LPMCU ram2低功耗控制信号软件配置：
                                                               bit15:slp
                                                               bit16:dslp
                                                               bit17:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown。 */
        unsigned int  lpram3ctrl_soft     : 3;  /* bit[18-20]: LPMCU ram3低功耗控制信号软件配置：
                                                               bit18:slp
                                                               bit19:dslp
                                                               bit20:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown。 */
        unsigned int  memrep_ram_mod      : 2;  /* bit[21-22]: memrep ram低功耗模式配置（状态机控制）
                                                               00:normal
                                                               01:sleep
                                                               10:deepsleep
                                                               11:power-down。 */
        unsigned int  memrep_ramctrl_soft : 3;  /* bit[23-25]: memrep ram低功耗控制信号软件配置：
                                                               bit23:slp
                                                               bit24:dslp
                                                               bit25:sd
                                                               000:normal
                                                               001:sleep
                                                               010:deepsleep
                                                               100:powerdown。 */
        unsigned int  reserved            : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCLPMCURAMCTRL_UNION;
#endif
#define SOC_SCTRL_SCLPMCURAMCTRL_lpramctrl_sel_START        (0)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpramctrl_sel_END          (0)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram0_mod_START           (1)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram0_mod_END             (2)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram1_mod_START           (3)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram1_mod_END             (4)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram2_mod_START           (5)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram2_mod_END             (6)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram3_mod_START           (7)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram3_mod_END             (8)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram0ctrl_soft_START      (9)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram0ctrl_soft_END        (11)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram1ctrl_soft_START      (12)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram1ctrl_soft_END        (14)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram2ctrl_soft_START      (15)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram2ctrl_soft_END        (17)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram3ctrl_soft_START      (18)
#define SOC_SCTRL_SCLPMCURAMCTRL_lpram3ctrl_soft_END        (20)
#define SOC_SCTRL_SCLPMCURAMCTRL_memrep_ram_mod_START       (21)
#define SOC_SCTRL_SCLPMCURAMCTRL_memrep_ram_mod_END         (22)
#define SOC_SCTRL_SCLPMCURAMCTRL_memrep_ramctrl_soft_START  (23)
#define SOC_SCTRL_SCLPMCURAMCTRL_memrep_ramctrl_soft_END    (25)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBBPDRXSTAT0_UNION
 结构说明  : SCBBPDRXSTAT0 寄存器结构定义。地址偏移量:0x530，初值:0x00000000，宽度:32
 寄存器说明: BBPDRX子系统状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g2_gdrx_depsleep_flag    : 1;  /* bit[0]   : 状态指示信号，高有效。 */
        unsigned int  g1_gdrx_depsleep_flag    : 1;  /* bit[1]   : 状态指示信号，高有效。 */
        unsigned int  wdrx_deepsleep_flag      : 1;  /* bit[2]   : 状态指示信号，高有效。 */
        unsigned int  cdrx_deepsleep_flag_1x   : 1;  /* bit[3]   : 状态指示信号，高有效。 */
        unsigned int  cdrx_deepsleep_flag_evdo : 1;  /* bit[4]   : 状态指示信号，高有效。 */
        unsigned int  reserved                 : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT0_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT0_g2_gdrx_depsleep_flag_START     (0)
#define SOC_SCTRL_SCBBPDRXSTAT0_g2_gdrx_depsleep_flag_END       (0)
#define SOC_SCTRL_SCBBPDRXSTAT0_g1_gdrx_depsleep_flag_START     (1)
#define SOC_SCTRL_SCBBPDRXSTAT0_g1_gdrx_depsleep_flag_END       (1)
#define SOC_SCTRL_SCBBPDRXSTAT0_wdrx_deepsleep_flag_START       (2)
#define SOC_SCTRL_SCBBPDRXSTAT0_wdrx_deepsleep_flag_END         (2)
#define SOC_SCTRL_SCBBPDRXSTAT0_cdrx_deepsleep_flag_1x_START    (3)
#define SOC_SCTRL_SCBBPDRXSTAT0_cdrx_deepsleep_flag_1x_END      (3)
#define SOC_SCTRL_SCBBPDRXSTAT0_cdrx_deepsleep_flag_evdo_START  (4)
#define SOC_SCTRL_SCBBPDRXSTAT0_cdrx_deepsleep_flag_evdo_END    (4)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBBPDRXSTAT1_UNION
 结构说明  : SCBBPDRXSTAT1 寄存器结构定义。地址偏移量:0x534，初值:0x00000000，宽度:32
 寄存器说明: BBPDRX子系统状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx2dbg_abs_timer : 32; /* bit[0-31]: ldrx2dbg_abs_timer的低32bit。(32KHz时钟域的计数)。 */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT1_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT1_ldrx2dbg_abs_timer_START  (0)
#define SOC_SCTRL_SCBBPDRXSTAT1_ldrx2dbg_abs_timer_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBBPDRXSTAT2_UNION
 结构说明  : SCBBPDRXSTAT2 寄存器结构定义。地址偏移量:0x538，初值:0x00000000，宽度:32
 寄存器说明: BBPDRX子系统状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx2dbg_abs_timer : 32; /* bit[0-31]: ldrx2dbg_abs_timer的高32bit。(32KHz时钟域的计数)。 */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT2_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT2_ldrx2dbg_abs_timer_START  (0)
#define SOC_SCTRL_SCBBPDRXSTAT2_ldrx2dbg_abs_timer_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBBPDRXSTAT3_UNION
 结构说明  : SCBBPDRXSTAT3 寄存器结构定义。地址偏移量:0x53C，初值:0x00000000，宽度:32
 寄存器说明: BBPDRX子系统状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx2dbg_abs_timer_sleep : 32; /* bit[0-31]: 最近一次进入sleep时ldrx2dbg_abs_timer的低32bit。(32KHz时钟域的计数)。 */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT3_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT3_ldrx2dbg_abs_timer_sleep_START  (0)
#define SOC_SCTRL_SCBBPDRXSTAT3_ldrx2dbg_abs_timer_sleep_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCBBPDRXSTAT4_UNION
 结构说明  : SCBBPDRXSTAT4 寄存器结构定义。地址偏移量:0x540，初值:0x00000000，宽度:32
 寄存器说明: BBPDRX子系统状态寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldrx2dbg_abs_timer_sleep : 32; /* bit[0-31]: 最近一次进入sleep时ldrx2dbg_abs_timer的高32bit。(32KHz时钟域的计数)。 */
    } reg;
} SOC_SCTRL_SCBBPDRXSTAT4_UNION;
#endif
#define SOC_SCTRL_SCBBPDRXSTAT4_ldrx2dbg_abs_timer_sleep_START  (0)
#define SOC_SCTRL_SCBBPDRXSTAT4_ldrx2dbg_abs_timer_sleep_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCA53_EVENT_MASK_UNION
 结构说明  : SCA53_EVENT_MASK 寄存器结构定义。地址偏移量:0x550，初值:0x0000000F，宽度:32
 寄存器说明: A53 EVENT屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCA53_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCA53_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCA53_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCA53_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCA53_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCA53_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCA53_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCA53_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCA53_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCA53_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCA53_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCA53_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCA53_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCA57_EVENT_MASK_UNION
 结构说明  : SCA57_EVENT_MASK 寄存器结构定义。地址偏移量:0x554，初值:0x0000000F，宽度:32
 寄存器说明: A57 EVENT屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCA57_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCA57_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCA57_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCA57_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCA57_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCA57_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCA57_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCA57_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCA57_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCA57_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCA57_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCA57_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCA57_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIOMCU_EVENT_MASK_UNION
 结构说明  : SCIOMCU_EVENT_MASK 寄存器结构定义。地址偏移量:0x558，初值:0x0000000F，宽度:32
 寄存器说明: IOMCU EVENT屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCIOMCU_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCIOMCU_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCLPMCU_EVENT_MASK_UNION
 结构说明  : SCLPMCU_EVENT_MASK 寄存器结构定义。地址偏移量:0x55C，初值:0x0000000F，宽度:32
 寄存器说明: LPMCU EVENT屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCLPMCU_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCLPMCU_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCMCPU_EVENT_MASK_UNION
 结构说明  : SCMCPU_EVENT_MASK 寄存器结构定义。地址偏移量:0x560，初值:0x00000000，宽度:32
 寄存器说明: MCPU EVENT屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCMCPU_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCMCPU_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCMCPU_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCEVENT_STAT_UNION
 结构说明  : SCEVENT_STAT 寄存器结构定义。地址偏移量:0x564，初值:0x00000000，宽度:32
 寄存器说明: EVENT状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event   : 1;  /* bit[0]   : 1：event有效；
                                                      0：event无效。 */
        unsigned int  a57_event   : 1;  /* bit[1]   : 1：event有效；
                                                      0：event无效。 */
        unsigned int  iomcu_event : 1;  /* bit[2]   : 1：event有效；
                                                      0：event无效。 */
        unsigned int  lpmcu_event : 1;  /* bit[3]   : 1：event有效；
                                                      0：event无效。 */
        unsigned int  mcpu_event  : 1;  /* bit[4]   : 1：event有效；
                                                      0：event无效。 */
        unsigned int  ispa7_event : 1;  /* bit[5]   : 1：event有效；
                                                      0：event无效。 */
        unsigned int  reserved    : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCEVENT_STAT_UNION;
#endif
#define SOC_SCTRL_SCEVENT_STAT_a53_event_START    (0)
#define SOC_SCTRL_SCEVENT_STAT_a53_event_END      (0)
#define SOC_SCTRL_SCEVENT_STAT_a57_event_START    (1)
#define SOC_SCTRL_SCEVENT_STAT_a57_event_END      (1)
#define SOC_SCTRL_SCEVENT_STAT_iomcu_event_START  (2)
#define SOC_SCTRL_SCEVENT_STAT_iomcu_event_END    (2)
#define SOC_SCTRL_SCEVENT_STAT_lpmcu_event_START  (3)
#define SOC_SCTRL_SCEVENT_STAT_lpmcu_event_END    (3)
#define SOC_SCTRL_SCEVENT_STAT_mcpu_event_START   (4)
#define SOC_SCTRL_SCEVENT_STAT_mcpu_event_END     (4)
#define SOC_SCTRL_SCEVENT_STAT_ispa7_event_START  (5)
#define SOC_SCTRL_SCEVENT_STAT_ispa7_event_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCISPA7_EVENT_MASK_UNION
 结构说明  : SCISPA7_EVENT_MASK 寄存器结构定义。地址偏移量:0x568，初值:0x0000000F，宽度:32
 寄存器说明: MCPU EVENT屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_event_mask   : 1;  /* bit[0]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  a57_event_mask   : 1;  /* bit[1]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  iomcu_event_mask : 1;  /* bit[2]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  lpmcu_event_mask : 1;  /* bit[3]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  mcpu_event_mask  : 1;  /* bit[4]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  ispa7_event_mask : 1;  /* bit[5]   : 1：屏蔽无效；
                                                           0：屏蔽有效。 */
        unsigned int  reserved         : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCISPA7_EVENT_MASK_UNION;
#endif
#define SOC_SCTRL_SCISPA7_EVENT_MASK_a53_event_mask_START    (0)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_a53_event_mask_END      (0)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_a57_event_mask_START    (1)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_a57_event_mask_END      (1)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_iomcu_event_mask_START  (2)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_iomcu_event_mask_END    (2)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_lpmcu_event_mask_START  (3)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_lpmcu_event_mask_END    (3)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_mcpu_event_mask_START   (4)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_mcpu_event_mask_END     (4)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_ispa7_event_mask_START  (5)
#define SOC_SCTRL_SCISPA7_EVENT_MASK_ispa7_event_mask_END    (5)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIOMCUCLKCTRL_UNION
 结构说明  : SCIOMCUCLKCTRL 寄存器结构定义。地址偏移量:0x580，初值:0x00000003，宽度:32
 寄存器说明: IOMCU时钟控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_iomcu_pll_div   : 1;  /* bit[0]    : IOMCU PLL分频器使能：
                                                              0：使能关闭
                                                              1：使能打开
                                                              最终的使能信号由该配置信号与IOMCU_pll_div_ctrl做或。 */
        unsigned int  gt_iomcu_sys_div   : 1;  /* bit[1]    : IOMCU SYS分频器使能：
                                                              0：使能关闭
                                                              1：使能打开
                                                              最终的使能信号由该配置信号与IOMCU_sys_div_ctrl做或。 */
        unsigned int  reserved           : 14; /* bit[2-15] : 保留。 */
        unsigned int  sciomcuclkctrl_msk : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                              只有当clkdivmasken对应的比特位写1'b1，写clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCIOMCUCLKCTRL_UNION;
#endif
#define SOC_SCTRL_SCIOMCUCLKCTRL_gt_iomcu_pll_div_START    (0)
#define SOC_SCTRL_SCIOMCUCLKCTRL_gt_iomcu_pll_div_END      (0)
#define SOC_SCTRL_SCIOMCUCLKCTRL_gt_iomcu_sys_div_START    (1)
#define SOC_SCTRL_SCIOMCUCLKCTRL_gt_iomcu_sys_div_END      (1)
#define SOC_SCTRL_SCIOMCUCLKCTRL_sciomcuclkctrl_msk_START  (16)
#define SOC_SCTRL_SCIOMCUCLKCTRL_sciomcuclkctrl_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIOMCUCLKSTAT_UNION
 结构说明  : SCIOMCUCLKSTAT 寄存器结构定义。地址偏移量:0x584，初值:0x00000000，宽度:32
 寄存器说明: IOMCU时钟控制信号状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_pll_ctrl        : 1;  /* bit[0]   : IOMCU侧控制PLL使能状态：
                                                                0：使能关闭
                                                                1：使能打开。 */
        unsigned int  iomcu_pll_div_ctrl    : 1;  /* bit[1]   : IOMCU侧控制PLL DIV使能状态：
                                                                0：使能关闭
                                                                1：使能打开。 */
        unsigned int  iomcu_sys_div_ctrl    : 1;  /* bit[2]   : IOMCU侧控制SYS DIV使能状态：
                                                                0：使能关闭
                                                                1：使能打开。 */
        unsigned int  gt_iomcu_pll_div_stat : 1;  /* bit[3]   : IOMCU的PLL DIV使能最终状态（gt_IOMCU_pll_div与IOMCU_pll_div_ctrl或）：
                                                                0：使能关闭
                                                                1：使能打开。 */
        unsigned int  gt_iomcu_sys_div_stat : 1;  /* bit[4]   : IOMCU的SYS DIV使能最终状态（gt_IOMCU_sys_div与IOMCU_sys_div_ctrl或）：
                                                                0：使能关闭
                                                                1：使能打开。 */
        unsigned int  reserved              : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCIOMCUCLKSTAT_UNION;
#endif
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_pll_ctrl_START         (0)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_pll_ctrl_END           (0)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_pll_div_ctrl_START     (1)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_pll_div_ctrl_END       (1)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_sys_div_ctrl_START     (2)
#define SOC_SCTRL_SCIOMCUCLKSTAT_iomcu_sys_div_ctrl_END       (2)
#define SOC_SCTRL_SCIOMCUCLKSTAT_gt_iomcu_pll_div_stat_START  (3)
#define SOC_SCTRL_SCIOMCUCLKSTAT_gt_iomcu_pll_div_stat_END    (3)
#define SOC_SCTRL_SCIOMCUCLKSTAT_gt_iomcu_sys_div_stat_START  (4)
#define SOC_SCTRL_SCIOMCUCLKSTAT_gt_iomcu_sys_div_stat_END    (4)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIOMCUCLKEN_UNION
 结构说明  : SCIOMCUCLKEN 寄存器结构定义。地址偏移量:0x588，初值:0x00003FFF，宽度:32
 寄存器说明: IOMCU子系统时钟使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved         : 16; /* bit[0-15] : 保留。 */
        unsigned int  sciomcuclken_msk : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                            只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_SCTRL_SCIOMCUCLKEN_UNION;
#endif
#define SOC_SCTRL_SCIOMCUCLKEN_sciomcuclken_msk_START  (16)
#define SOC_SCTRL_SCIOMCUCLKEN_sciomcuclken_msk_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIOMCURSTEN_UNION
 结构说明  : SCIOMCURSTEN 寄存器结构定义。地址偏移量:0x58C，初值:0x00000000，宽度:32
 寄存器说明: IOMCU子系统软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCIOMCURSTEN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIOMCURSTDIS_UNION
 结构说明  : SCIOMCURSTDIS 寄存器结构定义。地址偏移量:0x590，初值:0x00000000，宽度:32
 寄存器说明: IOMCU子系统软复位撤离寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCIOMCURSTDIS_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIOMCURSTSTAT_UNION
 结构说明  : SCIOMCURSTSTAT 寄存器结构定义。地址偏移量:0x594，初值:0x00000000，宽度:32
 寄存器说明: IOMCU子系统软复位使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCIOMCURSTSTAT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIOMCUCTRL_UNION
 结构说明  : SCIOMCUCTRL 寄存器结构定义。地址偏移量:0x598，初值:0x00000005，宽度:32
 寄存器说明: IOMCU子系统控制配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]   : 保留。 */
        unsigned int  nmi_int  : 1;  /* bit[1]   : 外部不可屏蔽中断输入
                                                   0:no nmi 1:nmi int。 */
        unsigned int  reserved_1: 1;  /* bit[2]   : 保留。 */
        unsigned int  reserved_2: 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCIOMCUCTRL_UNION;
#endif
#define SOC_SCTRL_SCIOMCUCTRL_nmi_int_START   (1)
#define SOC_SCTRL_SCIOMCUCTRL_nmi_int_END     (1)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCIOMCUSTAT_UNION
 结构说明  : SCIOMCUSTAT 寄存器结构定义。地址偏移量:0x59C，初值:0x00000000，宽度:32
 寄存器说明: IOMCU子系统状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomcu_sysresetreq               : 1;  /* bit[0]    : iomcu_sysresetreq，读清
                                                                           0:normal 1:rst have occurred。 */
        unsigned int  iomcu_m7_state                  : 3;  /* bit[1-3]  : [3]sleeping
                                                                           0:no sleeping 1:sleeping
                                                                           [2]lockup
                                                                           0:no lockup 1:lockup
                                                                           [1]halted
                                                                           0:no halted 1:halted。 */
        unsigned int  iomcu_dma_mst_nopendingtrans_bp : 1;  /* bit[4]    : iomcu_dma_mst_nopendingtrans bypass
                                                                           0:bypass;
                                                                           1:iomcu_dma_mst_nopendingtrans is one input of sc_noc_aobus_idle_flag is AndGate。 */
        unsigned int  iomcu_axi_mst_nopendingtrans_bp : 1;  /* bit[5]    : iomcu_axi_mst_nopendingtrans bypass
                                                                           0:bypass;
                                                                           1:iomcu_axi_mst_nopendingtrans is one input of sc_noc_aobus_idle_flag is AndGate。 */
        unsigned int  iomcu_axi_ahb_nopendingtrans_bp : 1;  /* bit[6]    : iomcu_axi_ahb_nopendingtrans bypass
                                                                           0:bypass;
                                                                           1:iomcu_axi_ahb_nopendingtrans is one input of sc_noc_aobus_idle_flag is AndGate。 */
        unsigned int  m7_sc_stat                      : 9;  /* bit[7-15] : m7_sc_stat[7:0]
                                                                           [0]:m7 deepsleep
                                                                           [1]:iomcu_mtcmos_ack 因网表优化，EC修改到此bit，IOMCU子系统电源电源反馈状态：
                                                                           0：IOMCU子系统电源使能撤销；
                                                                           1：IOMCU子系统电源使能。
                                                                           others:reserved。 */
        unsigned int  iomcu_dma_mst_nopendingtrans    : 1;  /* bit[16]   : iomcu_dma_mst_nopendingtrans
                                                                           0:bus have trans 1:bus no pending trans。 */
        unsigned int  iomcu_axi_mst_nopendingtrans    : 1;  /* bit[17]   : iomcu_axi_mst_nopendingtrans
                                                                           0:bus have trans 1:bus no pending trans。 */
        unsigned int  reserved                        : 1;  /* bit[18]   : 保留。 */
        unsigned int  iomcu_axi_ahb_nopendingtrans    : 1;  /* bit[19]   : iomcu_axi_ahb_nopendingtrans
                                                                           0:bus have trans 1:bus no pending trans。 */
        unsigned int  iomcu_stat                      : 12; /* bit[20-31]: others:reserved
                                                                           [31:30]AO_BUS的时钟切换 iomcu_aobus_clk_sw_req，
                                                                           [29:28]MMBUF的时钟切换 iomcu_mmbuf_clk_sw_req，
                                                                           [27]AO_BUS的时钟门控 iomcu_aobus_clk_en_req，1bit,1：打开 0：关闭
                                                                           [26]MMBUF的时钟门控 iomcu_mmbuf_clk_en_req，1bit,1：打开 0：关闭
                                                                           [25]FLL的开关控制 iomcu_fpll_en_req，1bit,1：打开 0：关闭
                                                                           [24]PPLL0的开关控制 已单独给出。 */
    } reg;
} SOC_SCTRL_SCIOMCUSTAT_UNION;
#endif
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_sysresetreq_START                (0)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_sysresetreq_END                  (0)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_m7_state_START                   (1)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_m7_state_END                     (3)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_dma_mst_nopendingtrans_bp_START  (4)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_dma_mst_nopendingtrans_bp_END    (4)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_mst_nopendingtrans_bp_START  (5)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_mst_nopendingtrans_bp_END    (5)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_ahb_nopendingtrans_bp_START  (6)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_ahb_nopendingtrans_bp_END    (6)
#define SOC_SCTRL_SCIOMCUSTAT_m7_sc_stat_START                       (7)
#define SOC_SCTRL_SCIOMCUSTAT_m7_sc_stat_END                         (15)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_dma_mst_nopendingtrans_START     (16)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_dma_mst_nopendingtrans_END       (16)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_mst_nopendingtrans_START     (17)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_mst_nopendingtrans_END       (17)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_ahb_nopendingtrans_START     (19)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_axi_ahb_nopendingtrans_END       (19)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_stat_START                       (20)
#define SOC_SCTRL_SCIOMCUSTAT_iomcu_stat_END                         (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCJTAG_SEL_UNION
 结构说明  : SCJTAG_SEL 寄存器结构定义。地址偏移量:0x800，初值:0x00000000，宽度:32
 寄存器说明: JTAG选择控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  processor_jtag_sel : 1;  /* bit[0]   : 0：DSP通过专用DSP jtag端口即SD卡复用管脚调试时，此时coresight jtag可以通过通用DSP和Coresight jtag共用端口端口调试；
                                                             1：DSP可通过通用DSP和Coresight jtag共用端口调试时，此时coresight jtag不能调试。 */
        unsigned int  dsp_jtag_sel       : 2;  /* bit[1-2] : 10：hifi dsp的JTAG
                                                             01：bbp dsp的JTAG
                                                             others：ivp32 dsp的JTAG。 */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCJTAG_SEL_UNION;
#endif
#define SOC_SCTRL_SCJTAG_SEL_processor_jtag_sel_START  (0)
#define SOC_SCTRL_SCJTAG_SEL_processor_jtag_sel_END    (0)
#define SOC_SCTRL_SCJTAG_SEL_dsp_jtag_sel_START        (1)
#define SOC_SCTRL_SCJTAG_SEL_dsp_jtag_sel_END          (2)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCMODEM_KEY0_UNION
 结构说明  : SCMODEM_KEY0 寄存器结构定义。地址偏移量:0x804，初值:0x00000000，宽度:32
 寄存器说明: MODEM_KEY0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_key0 : 32; /* bit[0-31]: modem_key0。 */
    } reg;
} SOC_SCTRL_SCMODEM_KEY0_UNION;
#endif
#define SOC_SCTRL_SCMODEM_KEY0_modem_key0_START  (0)
#define SOC_SCTRL_SCMODEM_KEY0_modem_key0_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCMODEM_KEY1_UNION
 结构说明  : SCMODEM_KEY1 寄存器结构定义。地址偏移量:0x808，初值:0x00000000，宽度:32
 寄存器说明: MODEM_KEY1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_key1 : 32; /* bit[0-31]: modem_key1。 */
    } reg;
} SOC_SCTRL_SCMODEM_KEY1_UNION;
#endif
#define SOC_SCTRL_SCMODEM_KEY1_modem_key1_START  (0)
#define SOC_SCTRL_SCMODEM_KEY1_modem_key1_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCMODEM_KEY2_UNION
 结构说明  : SCMODEM_KEY2 寄存器结构定义。地址偏移量:0x80C，初值:0x00000000，宽度:32
 寄存器说明: MODEM_KEY2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_key2 : 32; /* bit[0-31]: modem_key2。 */
    } reg;
} SOC_SCTRL_SCMODEM_KEY2_UNION;
#endif
#define SOC_SCTRL_SCMODEM_KEY2_modem_key2_START  (0)
#define SOC_SCTRL_SCMODEM_KEY2_modem_key2_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCMODEM_KEY3_UNION
 结构说明  : SCMODEM_KEY3 寄存器结构定义。地址偏移量:0x810，初值:0x00000000，宽度:32
 寄存器说明: MODEM_KEY3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  modem_key3 : 32; /* bit[0-31]: modem_key3。 */
    } reg;
} SOC_SCTRL_SCMODEM_KEY3_UNION;
#endif
#define SOC_SCTRL_SCMODEM_KEY3_modem_key3_START  (0)
#define SOC_SCTRL_SCMODEM_KEY3_modem_key3_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCFG_DJTAG_UNION
 结构说明  : SCCFG_DJTAG 寄存器结构定义。地址偏移量:0x814，初值:0x00000000，宽度:32
 寄存器说明: DJTAG控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_djtag : 1;  /* bit[0]   : 1：djtag disable
                                                    0：normal
                                                    写一次锁定，密码认证通过后数据才能写入并且只有当efuse_djtag_ctrl为2'b01时，cfg_djtag才输出到djtag_disable。 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCCFG_DJTAG_UNION;
#endif
#define SOC_SCTRL_SCCFG_DJTAG_cfg_djtag_START  (0)
#define SOC_SCTRL_SCCFG_DJTAG_cfg_djtag_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCP15_DISABLE_UNION
 结构说明  : SCCP15_DISABLE 寄存器结构定义。地址偏移量:0x818，初值:0x00000000，宽度:32
 寄存器说明: CP15DISABLE控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cp15disable0 : 1;  /* bit[0]    : A53 CPU0的控制bit，写1锁定，CPU0复位上升沿解锁。 */
        unsigned int  a53_cp15disable1 : 1;  /* bit[1]    : A53 CPU1的控制bit，写1锁定，CPU1复位上升沿解锁。 */
        unsigned int  a53_cp15disable2 : 1;  /* bit[2]    : A53 CPU2的控制bit，写1锁定，CPU2复位上升沿解锁。 */
        unsigned int  a53_cp15disable3 : 1;  /* bit[3]    : A53 CPU3的控制bit，写1锁定，CPU3复位上升沿解锁。 */
        unsigned int  a57_cp15disable0 : 1;  /* bit[4]    : A57 CPU0的控制bit，写1锁定，CPU0复位上升沿解锁。 */
        unsigned int  a57_cp15disable1 : 1;  /* bit[5]    : A57 CPU1的控制bit，写1锁定，CPU1复位上升沿解锁。 */
        unsigned int  a57_cp15disable2 : 1;  /* bit[6]    : A57 CPU2的控制bit，写1锁定，CPU2复位上升沿解锁。 */
        unsigned int  a57_cp15disable3 : 1;  /* bit[7]    : A57 CPU3的控制bit，写1锁定，CPU3复位上升沿解锁。 */
        unsigned int  ispa7cp15disable : 1;  /* bit[8]    : ISPA7 CPU的控制bit，写1锁定，CPU复位上升沿解锁。 */
        unsigned int  gicdisable       : 1;  /* bit[9]    : GIC的控制bit，写1锁定，GIC复位上升沿解锁。 */
        unsigned int  reserved         : 22; /* bit[10-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCCP15_DISABLE_UNION;
#endif
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable0_START  (0)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable0_END    (0)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable1_START  (1)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable1_END    (1)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable2_START  (2)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable2_END    (2)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable3_START  (3)
#define SOC_SCTRL_SCCP15_DISABLE_a53_cp15disable3_END    (3)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable0_START  (4)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable0_END    (4)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable1_START  (5)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable1_END    (5)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable2_START  (6)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable2_END    (6)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable3_START  (7)
#define SOC_SCTRL_SCCP15_DISABLE_a57_cp15disable3_END    (7)
#define SOC_SCTRL_SCCP15_DISABLE_ispa7cp15disable_START  (8)
#define SOC_SCTRL_SCCP15_DISABLE_ispa7cp15disable_END    (8)
#define SOC_SCTRL_SCCP15_DISABLE_gicdisable_START        (9)
#define SOC_SCTRL_SCCP15_DISABLE_gicdisable_END          (9)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKCNTSTAT_UNION
 结构说明  : SCCLKCNTSTAT 寄存器结构定义。地址偏移量:0x81C，初值:0x00000000，宽度:32
 寄存器说明: 时钟计数状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_stat : 16; /* bit[0-15] : clk_monitor模块时钟计数状态寄存器。当clk_cnt_en = 1'b1且在32KHz睡眠时钟上升或下降沿时更新，其余情况维持不变。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCCLKCNTSTAT_UNION;
#endif
#define SOC_SCTRL_SCCLKCNTSTAT_cnt_stat_START  (0)
#define SOC_SCTRL_SCCLKCNTSTAT_cnt_stat_END    (15)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKCNTCFG_UNION
 结构说明  : SCCLKCNTCFG 寄存器结构定义。地址偏移量:0x820，初值:0x40000340，宽度:32
 寄存器说明: 时钟计数配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_cfg        : 16; /* bit[0-15] : clk_monitor模块时钟计数配置寄存器。 */
        unsigned int  timer_secu_en  : 1;  /* bit[16]   : AO区TIMER1安全控制，使能时TIMER1的时钟有效，复位撤离，timer_clk_en2和timer_clk_en3为32KHZ时钟
                                                          0：安全控制不使能，timer2,3可选择32K和TCXO的4分频时钟；
                                                          1：安全控制使能，timer2,3都只使用32K时钟；并且此时timer2,3无法修改门控使能。 */
        unsigned int  reserved       : 13; /* bit[17-29]: 保留。 */
        unsigned int  clk_cnt_en     : 1;  /* bit[30]   : clk_cnt使能配置。
                                                          0：不使能
                                                          1：使能。 */
        unsigned int  clk_monitor_en : 1;  /* bit[31]   : clk_monitor模块使能配置。
                                                          0：不使能
                                                          1：使能
                                                          注：要先配置cnt_cfg[15:0]，再配置clk_monitor_en。 */
    } reg;
} SOC_SCTRL_SCCLKCNTCFG_UNION;
#endif
#define SOC_SCTRL_SCCLKCNTCFG_cnt_cfg_START         (0)
#define SOC_SCTRL_SCCLKCNTCFG_cnt_cfg_END           (15)
#define SOC_SCTRL_SCCLKCNTCFG_timer_secu_en_START   (16)
#define SOC_SCTRL_SCCLKCNTCFG_timer_secu_en_END     (16)
#define SOC_SCTRL_SCCLKCNTCFG_clk_cnt_en_START      (30)
#define SOC_SCTRL_SCCLKCNTCFG_clk_cnt_en_END        (30)
#define SOC_SCTRL_SCCLKCNTCFG_clk_monitor_en_START  (31)
#define SOC_SCTRL_SCCLKCNTCFG_clk_monitor_en_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKMONCTRL_UNION
 结构说明  : SCCLKMONCTRL 寄存器结构定义。地址偏移量:0x824，初值:0x00000002，宽度:32
 寄存器说明: 时钟监控控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_clr  : 1;  /* bit[0]   : 中断清除
                                                    0：不清中断
                                                    1：清中断
                                                    注：写1之后要再写0，否则会一直处于清中断的状态。 */
        unsigned int  intr_mask : 1;  /* bit[1]   : 中断屏蔽
                                                    0：不屏蔽中断
                                                    1：屏蔽中断。 */
        unsigned int  reserved  : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCCLKMONCTRL_UNION;
#endif
#define SOC_SCTRL_SCCLKMONCTRL_intr_clr_START   (0)
#define SOC_SCTRL_SCCLKMONCTRL_intr_clr_END     (0)
#define SOC_SCTRL_SCCLKMONCTRL_intr_mask_START  (1)
#define SOC_SCTRL_SCCLKMONCTRL_intr_mask_END    (1)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCLKMONINT_UNION
 结构说明  : SCCLKMONINT 寄存器结构定义。地址偏移量:0x828，初值:0x00000000，宽度:32
 寄存器说明: 时钟监控中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  raw_intr : 1;  /* bit[0]   : 中断指示
                                                   0：无中断
                                                   1：有中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCCLKMONINT_UNION;
#endif
#define SOC_SCTRL_SCCLKMONINT_raw_intr_START  (0)
#define SOC_SCTRL_SCCLKMONINT_raw_intr_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCFG_ARM_DBGEN_UNION
 结构说明  : SCCFG_ARM_DBGEN 寄存器结构定义。地址偏移量:0x82C，初值:0x00000002，宽度:32
 寄存器说明: ARM debug en配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_arm_dbgen : 4;  /* bit[0-3] : ARM debugen配置。（由系统寄存器逻辑保护每次上电复位之后此值只可写一次。）
                                                        [3:0]={spniden,spiden,niden,dbgen}
                                                        0:disable 1:enable。 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCCFG_ARM_DBGEN_UNION;
#endif
#define SOC_SCTRL_SCCFG_ARM_DBGEN_cfg_arm_dbgen_START  (0)
#define SOC_SCTRL_SCCFG_ARM_DBGEN_cfg_arm_dbgen_END    (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCARM_DBG_KEY0_UNION
 结构说明  : SCARM_DBG_KEY0 寄存器结构定义。地址偏移量:0x830，初值:0x00000000，宽度:32
 寄存器说明: ARM debug key0配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arm_dbg_key0 : 32; /* bit[0-31]: arm_dbg_key的低32位。（由系统寄存器逻辑保护每次上电复位之后此值只可写3次）。 */
    } reg;
} SOC_SCTRL_SCARM_DBG_KEY0_UNION;
#endif
#define SOC_SCTRL_SCARM_DBG_KEY0_arm_dbg_key0_START  (0)
#define SOC_SCTRL_SCARM_DBG_KEY0_arm_dbg_key0_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCARM_DBG_KEY1_UNION
 结构说明  : SCARM_DBG_KEY1 寄存器结构定义。地址偏移量:0x834，初值:0x00000000，宽度:32
 寄存器说明: ARM debug key1配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arm_dbg_key1 : 32; /* bit[0-31]: arm_dbg_key的高32位。（由系统寄存器逻辑保护每次上电复位之后此值只可写3次）。 */
    } reg;
} SOC_SCTRL_SCARM_DBG_KEY1_UNION;
#endif
#define SOC_SCTRL_SCARM_DBG_KEY1_arm_dbg_key1_START  (0)
#define SOC_SCTRL_SCARM_DBG_KEY1_arm_dbg_key1_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCARM_DBGEN_STAT_UNION
 结构说明  : SCARM_DBGEN_STAT 寄存器结构定义。地址偏移量:0x838，初值:0x00000000，宽度:32
 寄存器说明: ARM debug en状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arm_dbgen_wr : 1;  /* bit[0]   : ARM debugen wr状态寄存器。
                                                       0：当前不可写cfg_arm_dbgen寄存器。1：当前可写cfg_arm_dbgen寄存器。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCARM_DBGEN_STAT_UNION;
#endif
#define SOC_SCTRL_SCARM_DBGEN_STAT_arm_dbgen_wr_START  (0)
#define SOC_SCTRL_SCARM_DBGEN_STAT_arm_dbgen_wr_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCEFUSECTRL_UNION
 结构说明  : SCEFUSECTRL 寄存器结构定义。地址偏移量:0x83C，初值:0x00000000，宽度:32
 寄存器说明: EFUSE PAD烧写控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sys_efuse_pad_sel : 1;  /* bit[0]   : 0：PAD烧写；
                                                            1：软件烧写。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCEFUSECTRL_UNION;
#endif
#define SOC_SCTRL_SCEFUSECTRL_sys_efuse_pad_sel_START  (0)
#define SOC_SCTRL_SCEFUSECTRL_sys_efuse_pad_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCEFUSESEL_UNION
 结构说明  : SCEFUSESEL 寄存器结构定义。地址偏移量:0x840，初值:0x00000000，宽度:32
 寄存器说明: SECS时钟门控寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_secs : 1;  /* bit[0]   : secs时钟门控控制：
                                                      0：IP时钟禁止；
                                                      1：IP时钟使能。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCEFUSESEL_UNION;
#endif
#define SOC_SCTRL_SCEFUSESEL_gt_clk_secs_START  (0)
#define SOC_SCTRL_SCEFUSESEL_gt_clk_secs_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCSECURITYSTAT_UNION
 结构说明  : SCSECURITYSTAT 寄存器结构定义。地址偏移量:0x844，初值:0x00000000，宽度:32
 寄存器说明: EFUSE SECURITY状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc_sel : 1;  /* bit[0]   : 来自efuse的emmc_sel指示
                                                   0：emmc5.0
                                                   1：emmc4.5。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCSECURITYSTAT_UNION;
#endif
#define SOC_SCTRL_SCSECURITYSTAT_emmc_sel_START  (0)
#define SOC_SCTRL_SCSECURITYSTAT_emmc_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCHIP_ID0_UNION
 结构说明  : SCCHIP_ID0 寄存器结构定义。地址偏移量:0x848，初值:0x00000000，宽度:32
 寄存器说明: EFUSE CHIP_ID0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CHIP_ID0 : 32; /* bit[0-31]: CHIP_ID低32bit。 */
    } reg;
} SOC_SCTRL_SCCHIP_ID0_UNION;
#endif
#define SOC_SCTRL_SCCHIP_ID0_CHIP_ID0_START  (0)
#define SOC_SCTRL_SCCHIP_ID0_CHIP_ID0_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCHIP_ID1_UNION
 结构说明  : SCCHIP_ID1 寄存器结构定义。地址偏移量:0x84C，初值:0x00000000，宽度:32
 寄存器说明: EFUSE CHIP_ID1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CHIP_ID1 : 32; /* bit[0-31]: CHIP_ID高32bit。 */
    } reg;
} SOC_SCTRL_SCCHIP_ID1_UNION;
#endif
#define SOC_SCTRL_SCCHIP_ID1_CHIP_ID1_START  (0)
#define SOC_SCTRL_SCCHIP_ID1_CHIP_ID1_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCCPUSECCTRL_UNION
 结构说明  : SCCPUSECCTRL 寄存器结构定义。地址偏移量:0x850，初值:0x00000000，宽度:32
 寄存器说明: CPU安全控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_cryptodisable : 4;  /* bit[0-3] : 单核加密引擎disable
                                                            0：Enable the Cryptography engine；
                                                            1：Disable the Cryptography engine。 */
        unsigned int  a57_cryptodisable : 4;  /* bit[4-7] : 单核加密引擎disable
                                                            0：Enable the Cryptography engine；
                                                            1：Disable the Cryptography engine。 */
        unsigned int  reserved          : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCCPUSECCTRL_UNION;
#endif
#define SOC_SCTRL_SCCPUSECCTRL_a53_cryptodisable_START  (0)
#define SOC_SCTRL_SCCPUSECCTRL_a53_cryptodisable_END    (3)
#define SOC_SCTRL_SCCPUSECCTRL_a57_cryptodisable_START  (4)
#define SOC_SCTRL_SCCPUSECCTRL_a57_cryptodisable_END    (7)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPEREN0_SEC_UNION
 结构说明  : SCPEREN0_SEC 寄存器结构定义。地址偏移量:0x900，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器0（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_timer1    : 1;  /* bit[0]    : 外设时钟使能控制：
                                                             0：写0无效果；
                                                             1：使能IP时钟。 */
        unsigned int  gt_clk_timer1     : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  gt_clk_clkmonitor : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  gt_clk_ao_cc      : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  reserved          : 16; /* bit[4-19] : 含义同bit0。 */
        unsigned int  mmbuf_sec_ctrl    : 12; /* bit[20-31]: 安全控制：
                                                             0：写0无效果；
                                                             1：SCPERCLKEN0_SEC.mmbuf_sec_ctrl相应bit置1。 */
    } reg;
} SOC_SCTRL_SCPEREN0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPEREN0_SEC_gt_pclk_timer1_START     (0)
#define SOC_SCTRL_SCPEREN0_SEC_gt_pclk_timer1_END       (0)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_timer1_START      (1)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_timer1_END        (1)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_clkmonitor_START  (2)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_clkmonitor_END    (2)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_ao_cc_START       (3)
#define SOC_SCTRL_SCPEREN0_SEC_gt_clk_ao_cc_END         (3)
#define SOC_SCTRL_SCPEREN0_SEC_mmbuf_sec_ctrl_START     (20)
#define SOC_SCTRL_SCPEREN0_SEC_mmbuf_sec_ctrl_END       (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERDIS0_SEC_UNION
 结构说明  : SCPERDIS0_SEC 寄存器结构定义。地址偏移量:0x904，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器0（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_timer1    : 1;  /* bit[0]    : 外设时钟禁止控制：
                                                             0：写0无效果；
                                                             1：禁止IP时钟。 */
        unsigned int  gt_clk_timer1     : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  gt_clk_clkmonitor : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  gt_clk_ao_cc      : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  reserved          : 16; /* bit[4-19] : 含义同bit0。 */
        unsigned int  mmbuf_sec_ctrl    : 12; /* bit[20-31]: 安全控制：
                                                             0：写0无效果；
                                                             1：SCPERCLKEN0_SEC.mmbuf_sec_ctrl相应bit清0。 */
    } reg;
} SOC_SCTRL_SCPERDIS0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERDIS0_SEC_gt_pclk_timer1_START     (0)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_pclk_timer1_END       (0)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_timer1_START      (1)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_timer1_END        (1)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_clkmonitor_START  (2)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_clkmonitor_END    (2)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_ao_cc_START       (3)
#define SOC_SCTRL_SCPERDIS0_SEC_gt_clk_ao_cc_END         (3)
#define SOC_SCTRL_SCPERDIS0_SEC_mmbuf_sec_ctrl_START     (20)
#define SOC_SCTRL_SCPERDIS0_SEC_mmbuf_sec_ctrl_END       (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERCLKEN0_SEC_UNION
 结构说明  : SCPERCLKEN0_SEC 寄存器结构定义。地址偏移量:0x908，初值:0x003FFFFF，宽度:32
 寄存器说明: 外设时钟使能状态寄存器0（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_timer1    : 1;  /* bit[0]    : 外设时钟使能状态：
                                                             0：IP时钟使能撤销状态；
                                                             1：IP时钟使能状态。 */
        unsigned int  gt_clk_timer1     : 1;  /* bit[1]    : 含义同bit0。 */
        unsigned int  gt_clk_clkmonitor : 1;  /* bit[2]    : 含义同bit0。 */
        unsigned int  gt_clk_ao_cc      : 1;  /* bit[3]    : 含义同bit0。 */
        unsigned int  reserved          : 16; /* bit[4-19] : 含义同bit0。 */
        unsigned int  mmbuf_sec_ctrl    : 12; /* bit[20-31]: 安全状态
                                                             tzpcdecprot5[20] ENABLE_FIREWALL 
                                                             0：disable firewall
                                                             1： enable firewall
                                                             tzpcdecprot5[21] ERR_RESP 
                                                             0： disable err resp
                                                             1： enable err resp
                                                             tzpcdecprot5[22] REGION0_IS_SEC(0xea800000~0xea80c7ff) 0：安全；1：非安全
                                                             tzpcdecprot5[23] REGION1_IS_SEC(0xea80c800~0xea818fff) 0：安全；1：非安全
                                                             tzpcdecprot5[24] REGION2_IS_SEC(0xea819000~0xea8257ff) 0：安全；1：非安全
                                                             tzpcdecprot5[25] REGION3_IS_SEC(0xea825800~0xea831fff) 0：安全；1：非安全
                                                             tzpcdecprot5[26] REGION4_IS_SEC(0xea832000~0xea83e7ff) 0：安全；1：非安全
                                                             tzpcdecprot5[27] REGION5_IS_SEC(0xea83e800~0xea84afff) 0：安全；1：非安全
                                                             tzpcdecprot5[28] REGION6_IS_SEC(0xea84b000~0xea8577ff) 0：安全；1：非安全
                                                             tzpcdecprot5[29] REGION7_IS_SEC(0xea857800~0xea863fff) 0：安全；1：非安全
                                                             tzpcdecprot5[30] Reserved 默认安全
                                                             tzpcdecprot5[31] Reserved 默认安全。 */
    } reg;
} SOC_SCTRL_SCPERCLKEN0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_pclk_timer1_START     (0)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_pclk_timer1_END       (0)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_timer1_START      (1)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_timer1_END        (1)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_clkmonitor_START  (2)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_clkmonitor_END    (2)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_ao_cc_START       (3)
#define SOC_SCTRL_SCPERCLKEN0_SEC_gt_clk_ao_cc_END         (3)
#define SOC_SCTRL_SCPERCLKEN0_SEC_mmbuf_sec_ctrl_START     (20)
#define SOC_SCTRL_SCPERCLKEN0_SEC_mmbuf_sec_ctrl_END       (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTEN0_SEC_UNION
 结构说明  : SCPERRSTEN0_SEC 寄存器结构定义。地址偏移量:0x950，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器0（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_timer1 : 1;  /* bit[0]   : IP软复位使能：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位使能。 */
        unsigned int  ip_rst_asc    : 1;  /* bit[1]   : 含义同bit0。 */
        unsigned int  reserved_0    : 1;  /* bit[2]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_cc  : 1;  /* bit[3]   : 含义同bit0。 */
        unsigned int  reserved_1    : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTEN0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_timer1_START  (0)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_timer1_END    (0)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_asc_START     (1)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_asc_END       (1)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_ao_cc_START   (3)
#define SOC_SCTRL_SCPERRSTEN0_SEC_ip_rst_ao_cc_END     (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTDIS0_SEC_UNION
 结构说明  : SCPERRSTDIS0_SEC 寄存器结构定义。地址偏移量:0x954，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器0（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_timer1 : 1;  /* bit[0]   : IP软复位撤离：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位撤离。 */
        unsigned int  ip_rst_asc    : 1;  /* bit[1]   : 含义同bit0。 */
        unsigned int  reserved_0    : 1;  /* bit[2]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_cc  : 1;  /* bit[3]   : 含义同bit0。 */
        unsigned int  reserved_1    : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTDIS0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_timer1_START  (0)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_timer1_END    (0)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_asc_START     (1)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_asc_END       (1)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_ao_cc_START   (3)
#define SOC_SCTRL_SCPERRSTDIS0_SEC_ip_rst_ao_cc_END     (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTSTAT0_SEC_UNION
 结构说明  : SCPERRSTSTAT0_SEC 寄存器结构定义。地址偏移量:0x958，初值:0x00000002，宽度:32
 寄存器说明: 外设软复位状态寄存器0（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_timer1 : 1;  /* bit[0]   : 外设软复位使能状态：
                                                        0：IP软复位使能撤销；
                                                        1：IP软复位使能。 */
        unsigned int  ip_rst_asc    : 1;  /* bit[1]   : 含义同bit0。 */
        unsigned int  reserved_0    : 1;  /* bit[2]   : 含义同bit0。 */
        unsigned int  ip_rst_ao_cc  : 1;  /* bit[3]   : 含义同bit0。 */
        unsigned int  reserved_1    : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT0_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_timer1_START  (0)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_timer1_END    (0)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_asc_START     (1)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_asc_END       (1)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_ao_cc_START   (3)
#define SOC_SCTRL_SCPERRSTSTAT0_SEC_ip_rst_ao_cc_END     (3)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCTIMERCTRL_SEC_UNION
 结构说明  : SCTIMERCTRL_SEC 寄存器结构定义。地址偏移量:0x9A0，初值:0x00000000，宽度:32
 寄存器说明: 安全TIMER控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeren2sel    : 1;  /* bit[0]   : Time2时钟使能参考时钟选择。
                                                         0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                         1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren2ov     : 1;  /* bit[1]   : Timer2时钟使能控制。
                                                         0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren2sel]指定；
                                                         1：使能信号被强制拉高。 */
        unsigned int  timeren3sel    : 1;  /* bit[2]   : Time3时钟使能参考时钟选择。
                                                         0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                         1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren3ov     : 1;  /* bit[3]   : Timer3时钟使能控制。
                                                         0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren3sel]指定；
                                                         1：使能信号被强制拉高。 */
        unsigned int  reserved       : 27; /* bit[4-30]: 保留。 */
        unsigned int  timerforcehigh : 1;  /* bit[31]  : Timer23使能端强制拉高的硬件使能配置。
                                                         0：硬件不进行自动操作；
                                                         1：当系统时钟是32K时，硬件自动强制拉高Timer23的使能。 */
    } reg;
} SOC_SCTRL_SCTIMERCTRL_SEC_UNION;
#endif
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren2sel_START     (0)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren2sel_END       (0)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren2ov_START      (1)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren2ov_END        (1)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren3sel_START     (2)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren3sel_END       (2)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren3ov_START      (3)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timeren3ov_END        (3)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timerforcehigh_START  (31)
#define SOC_SCTRL_SCTIMERCTRL_SEC_timerforcehigh_END    (31)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTEN1_SEC_UNION
 结构说明  : SCPERRSTEN1_SEC 寄存器结构定义。地址偏移量:0xA50，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器1（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_asp_subsys : 1;  /* bit[0]   : IP软复位使能：
                                                            0：IP软复位使能状态不变；
                                                            1：IP软复位使能。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTEN1_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN1_SEC_ip_rst_asp_subsys_START  (0)
#define SOC_SCTRL_SCPERRSTEN1_SEC_ip_rst_asp_subsys_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTDIS1_SEC_UNION
 结构说明  : SCPERRSTDIS1_SEC 寄存器结构定义。地址偏移量:0xA54，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器1（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_asp_subsys : 1;  /* bit[0]   : IP软复位撤离：
                                                            0：IP软复位使能状态不变；
                                                            1：IP软复位撤离。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTDIS1_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS1_SEC_ip_rst_asp_subsys_START  (0)
#define SOC_SCTRL_SCPERRSTDIS1_SEC_ip_rst_asp_subsys_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTSTAT1_SEC_UNION
 结构说明  : SCPERRSTSTAT1_SEC 寄存器结构定义。地址偏移量:0xA58，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 外设软复位状态寄存器1（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_asp_subsys : 1;  /* bit[0]   : 输出控制crg的rsten2[0]
                                                            外设软复位使能状态：
                                                            0：IP软复位使能撤销；
                                                            1：IP软复位使能。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT1_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT1_SEC_ip_rst_asp_subsys_START  (0)
#define SOC_SCTRL_SCPERRSTSTAT1_SEC_ip_rst_asp_subsys_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTEN2_SEC_UNION
 结构说明  : SCPERRSTEN2_SEC 寄存器结构定义。地址偏移量:0xB50，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器2（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_iomcu : 1;  /* bit[0]   : IP软复位使能：
                                                       0：IP软复位使能状态不变；
                                                       1：IP软复位使能。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTEN2_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTEN2_SEC_ip_rst_iomcu_START  (0)
#define SOC_SCTRL_SCPERRSTEN2_SEC_ip_rst_iomcu_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTDIS2_SEC_UNION
 结构说明  : SCPERRSTDIS2_SEC 寄存器结构定义。地址偏移量:0xB54，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器2（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_iomcu : 1;  /* bit[0]   : IP软复位撤离：
                                                       0：IP软复位使能状态不变；
                                                       1：IP软复位撤离。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTDIS2_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTDIS2_SEC_ip_rst_iomcu_START  (0)
#define SOC_SCTRL_SCPERRSTDIS2_SEC_ip_rst_iomcu_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCPERRSTSTAT2_SEC_UNION
 结构说明  : SCPERRSTSTAT2_SEC 寄存器结构定义。地址偏移量:0xB58，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 外设软复位状态寄存器2（安全）。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_iomcu : 1;  /* bit[0]   : 输出控制crg的rsten2[1]
                                                       外设软复位使能状态：
                                                       0：IP软复位使能撤销；
                                                       1：IP软复位使能。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_SCTRL_SCPERRSTSTAT2_SEC_UNION;
#endif
#define SOC_SCTRL_SCPERRSTSTAT2_SEC_ip_rst_iomcu_START  (0)
#define SOC_SCTRL_SCPERRSTSTAT2_SEC_ip_rst_iomcu_END    (0)


/*****************************************************************************
 结构名    : SOC_SCTRL_SCSOCID0_UNION
 结构说明  : SCSOCID0 寄存器结构定义。地址偏移量:0xE00，初值:0x36500100，宽度:32
 寄存器说明: SOCID寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version_code : 16; /* bit[0-15] : 0x0100是芯片的版本号。
                                                        ASIC使用：TSMC16FF_TSMC_MEM ，默认值为0x36500100
                                                        FPGA使用： FPGA_XILINX ，默认值为 0x36501000
                                                        emulator使用：EMULATOR_VERSION ， 默认值为 0x36502000。 */
        unsigned int  chip_code    : 16; /* bit[16-31]: 0x3650是芯片的编号 */
    } reg;
} SOC_SCTRL_SCSOCID0_UNION;
#endif
#define SOC_SCTRL_SCSOCID0_version_code_START  (0)
#define SOC_SCTRL_SCSOCID0_version_code_END    (15)
#define SOC_SCTRL_SCSOCID0_chip_code_START     (16)
#define SOC_SCTRL_SCSOCID0_chip_code_END       (31)






/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_sctrl_interface.h */
