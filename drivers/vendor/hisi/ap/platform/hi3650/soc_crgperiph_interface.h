/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_crgperiph_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:44:11
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_CRGPERIPH.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CRGPERIPH_INTERFACE_H__
#define __SOC_CRGPERIPH_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_CRGPERIPH
 ****************************************************************************/
/* 寄存器说明：外设时钟使能寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PEREN0_UNION */
#define SOC_CRGPERIPH_PEREN0_ADDR(base)               ((base) + (0x000))

/* 寄存器说明：外设时钟禁止寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PERDIS0_UNION */
#define SOC_CRGPERIPH_PERDIS0_ADDR(base)              ((base) + (0x004))

/* 寄存器说明：外设时钟使能状态寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCLKEN0_UNION */
#define SOC_CRGPERIPH_PERCLKEN0_ADDR(base)            ((base) + (0x008))

/* 寄存器说明：外设时钟最终状态寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PERSTAT0_UNION */
#define SOC_CRGPERIPH_PERSTAT0_ADDR(base)             ((base) + (0x00C))

/* 寄存器说明：外设时钟使能寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PEREN1_UNION */
#define SOC_CRGPERIPH_PEREN1_ADDR(base)               ((base) + (0x010))

/* 寄存器说明：外设时钟禁止寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PERDIS1_UNION */
#define SOC_CRGPERIPH_PERDIS1_ADDR(base)              ((base) + (0x014))

/* 寄存器说明：外设时钟使能状态寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCLKEN1_UNION */
#define SOC_CRGPERIPH_PERCLKEN1_ADDR(base)            ((base) + (0x018))

/* 寄存器说明：外设时钟最终状态寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PERSTAT1_UNION */
#define SOC_CRGPERIPH_PERSTAT1_ADDR(base)             ((base) + (0x01C))

/* 寄存器说明：外设时钟使能寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PEREN2_UNION */
#define SOC_CRGPERIPH_PEREN2_ADDR(base)               ((base) + (0x020))

/* 寄存器说明：外设时钟禁止寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PERDIS2_UNION */
#define SOC_CRGPERIPH_PERDIS2_ADDR(base)              ((base) + (0x024))

/* 寄存器说明：外设时钟使能状态寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCLKEN2_UNION */
#define SOC_CRGPERIPH_PERCLKEN2_ADDR(base)            ((base) + (0x028))

/* 寄存器说明：外设时钟最终状态寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PERSTAT2_UNION */
#define SOC_CRGPERIPH_PERSTAT2_ADDR(base)             ((base) + (0x02C))

/* 寄存器说明：外设时钟使能寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PEREN3_UNION */
#define SOC_CRGPERIPH_PEREN3_ADDR(base)               ((base) + (0x030))

/* 寄存器说明：外设时钟禁止寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PERDIS3_UNION */
#define SOC_CRGPERIPH_PERDIS3_ADDR(base)              ((base) + (0x034))

/* 寄存器说明：外设时钟使能状态寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCLKEN3_UNION */
#define SOC_CRGPERIPH_PERCLKEN3_ADDR(base)            ((base) + (0x038))

/* 寄存器说明：外设时钟最终状态寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PERSTAT3_UNION */
#define SOC_CRGPERIPH_PERSTAT3_ADDR(base)             ((base) + (0x03C))

/* 寄存器说明：外设时钟使能寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_PEREN4_UNION */
#define SOC_CRGPERIPH_PEREN4_ADDR(base)               ((base) + (0x040))

/* 寄存器说明：外设时钟禁止寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_PERDIS4_UNION */
#define SOC_CRGPERIPH_PERDIS4_ADDR(base)              ((base) + (0x044))

/* 寄存器说明：外设时钟使能状态寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCLKEN4_UNION */
#define SOC_CRGPERIPH_PERCLKEN4_ADDR(base)            ((base) + (0x048))

/* 寄存器说明：外设时钟最终状态寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_PERSTAT4_UNION */
#define SOC_CRGPERIPH_PERSTAT4_ADDR(base)             ((base) + (0x04C))

/* 寄存器说明：外设时钟使能寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_PEREN5_UNION */
#define SOC_CRGPERIPH_PEREN5_ADDR(base)               ((base) + (0x050))

/* 寄存器说明：外设时钟禁止寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_PERDIS5_UNION */
#define SOC_CRGPERIPH_PERDIS5_ADDR(base)              ((base) + (0x054))

/* 寄存器说明：外设时钟使能状态寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCLKEN5_UNION */
#define SOC_CRGPERIPH_PERCLKEN5_ADDR(base)            ((base) + (0x058))

/* 寄存器说明：外设时钟最终状态寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_PERSTAT5_UNION */
#define SOC_CRGPERIPH_PERSTAT5_ADDR(base)             ((base) + (0x05C))

/* 寄存器说明：外设软复位使能寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTEN0_UNION */
#define SOC_CRGPERIPH_PERRSTEN0_ADDR(base)            ((base) + (0x060))

/* 寄存器说明：外设软复位撤离寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTDIS0_UNION */
#define SOC_CRGPERIPH_PERRSTDIS0_ADDR(base)           ((base) + (0x064))

/* 寄存器说明：外设软复位状态寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTSTAT0_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT0_ADDR(base)          ((base) + (0x068))

/* 寄存器说明：外设软复位使能寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTEN1_UNION */
#define SOC_CRGPERIPH_PERRSTEN1_ADDR(base)            ((base) + (0x06C))

/* 寄存器说明：外设软复位撤离寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTDIS1_UNION */
#define SOC_CRGPERIPH_PERRSTDIS1_ADDR(base)           ((base) + (0x070))

/* 寄存器说明：外设软复位状态寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTSTAT1_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT1_ADDR(base)          ((base) + (0x074))

/* 寄存器说明：外设软复位使能寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTEN2_UNION */
#define SOC_CRGPERIPH_PERRSTEN2_ADDR(base)            ((base) + (0x078))

/* 寄存器说明：外设软复位撤离寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTDIS2_UNION */
#define SOC_CRGPERIPH_PERRSTDIS2_ADDR(base)           ((base) + (0x07C))

/* 寄存器说明：外设软复位状态寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTSTAT2_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT2_ADDR(base)          ((base) + (0x080))

/* 寄存器说明：外设软复位使能寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTEN3_UNION */
#define SOC_CRGPERIPH_PERRSTEN3_ADDR(base)            ((base) + (0x084))

/* 寄存器说明：外设软复位撤离寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTDIS3_UNION */
#define SOC_CRGPERIPH_PERRSTDIS3_ADDR(base)           ((base) + (0x088))

/* 寄存器说明：外设软复位状态寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTSTAT3_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT3_ADDR(base)          ((base) + (0x008C))

/* 寄存器说明：外设软复位使能寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTEN4_UNION */
#define SOC_CRGPERIPH_PERRSTEN4_ADDR(base)            ((base) + (0x090))

/* 寄存器说明：外设软复位撤离寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTDIS4_UNION */
#define SOC_CRGPERIPH_PERRSTDIS4_ADDR(base)           ((base) + (0x094))

/* 寄存器说明：外设软复位状态寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTSTAT4_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT4_ADDR(base)          ((base) + (0x098))

/* 寄存器说明：外设软复位使能寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTEN5_UNION */
#define SOC_CRGPERIPH_PERRSTEN5_ADDR(base)            ((base) + (0x09C))

/* 寄存器说明：外设软复位撤离寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTDIS5_UNION */
#define SOC_CRGPERIPH_PERRSTDIS5_ADDR(base)           ((base) + (0x0A0))

/* 寄存器说明：外设软复位状态寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_PERRSTSTAT5_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT5_ADDR(base)          ((base) + (0x0A4))

/* 寄存器说明：时钟分频比控制寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV0_UNION */
#define SOC_CRGPERIPH_CLKDIV0_ADDR(base)              ((base) + (0x0A8))

/* 寄存器说明：时钟分频比控制寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV1_UNION */
#define SOC_CRGPERIPH_CLKDIV1_ADDR(base)              ((base) + (0x0AC))

/* 寄存器说明：时钟分频比控制寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV2_UNION */
#define SOC_CRGPERIPH_CLKDIV2_ADDR(base)              ((base) + (0x0B0))

/* 寄存器说明：时钟分频比控制寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV3_UNION */
#define SOC_CRGPERIPH_CLKDIV3_ADDR(base)              ((base) + (0x0B4))

/* 寄存器说明：时钟分频比控制寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV4_UNION */
#define SOC_CRGPERIPH_CLKDIV4_ADDR(base)              ((base) + (0x0B8))

/* 寄存器说明：时钟分频比控制寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV5_UNION */
#define SOC_CRGPERIPH_CLKDIV5_ADDR(base)              ((base) + (0x0BC))

/* 寄存器说明：时钟分频比控制寄存器6。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV6_UNION */
#define SOC_CRGPERIPH_CLKDIV6_ADDR(base)              ((base) + (0x0C0))

/* 寄存器说明：时钟分频比控制寄存器7。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV7_UNION */
#define SOC_CRGPERIPH_CLKDIV7_ADDR(base)              ((base) + (0x0C4))

/* 寄存器说明：时钟分频比控制寄存器8。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV8_UNION */
#define SOC_CRGPERIPH_CLKDIV8_ADDR(base)              ((base) + (0x0C8))

/* 寄存器说明：时钟分频比控制寄存器9。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV9_UNION */
#define SOC_CRGPERIPH_CLKDIV9_ADDR(base)              ((base) + (0x0CC))

/* 寄存器说明：时钟分频比控制寄存器10。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV10_UNION */
#define SOC_CRGPERIPH_CLKDIV10_ADDR(base)             ((base) + (0x0D0))

/* 寄存器说明：时钟分频比控制寄存器11。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV11_UNION */
#define SOC_CRGPERIPH_CLKDIV11_ADDR(base)             ((base) + (0x0D4))

/* 寄存器说明：时钟分频比控制寄存器12。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV12_UNION */
#define SOC_CRGPERIPH_CLKDIV12_ADDR(base)             ((base) + (0x0D8))

/* 寄存器说明：时钟分频比控制寄存器13。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV13_UNION */
#define SOC_CRGPERIPH_CLKDIV13_ADDR(base)             ((base) + (0x0DC))

/* 寄存器说明：时钟分频比控制寄存器14。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV14_UNION */
#define SOC_CRGPERIPH_CLKDIV14_ADDR(base)             ((base) + (0x0E0))

/* 寄存器说明：时钟分频比控制寄存器15。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV15_UNION */
#define SOC_CRGPERIPH_CLKDIV15_ADDR(base)             ((base) + (0x0E4))

/* 寄存器说明：时钟分频比控制寄存器16。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV16_UNION */
#define SOC_CRGPERIPH_CLKDIV16_ADDR(base)             ((base) + (0x0E8))

/* 寄存器说明：时钟分频比控制寄存器17。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV17_UNION */
#define SOC_CRGPERIPH_CLKDIV17_ADDR(base)             ((base) + (0x0EC))

/* 寄存器说明：时钟分频比控制寄存器18。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV18_UNION */
#define SOC_CRGPERIPH_CLKDIV18_ADDR(base)             ((base) + (0x0F0))

/* 寄存器说明：时钟分频比控制寄存器19。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV19_UNION */
#define SOC_CRGPERIPH_CLKDIV19_ADDR(base)             ((base) + (0x0F4))

/* 寄存器说明：时钟分频比控制寄存器20。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV20_UNION */
#define SOC_CRGPERIPH_CLKDIV20_ADDR(base)             ((base) + (0x0F8))

/* 寄存器说明：时钟分频比控制寄存器21。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV21_UNION */
#define SOC_CRGPERIPH_CLKDIV21_ADDR(base)             ((base) + (0x0FC))

/* 寄存器说明：时钟分频比控制寄存器22。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV22_UNION */
#define SOC_CRGPERIPH_CLKDIV22_ADDR(base)             ((base) + (0x100))

/* 寄存器说明：时钟分频比控制寄存器23。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV23_UNION */
#define SOC_CRGPERIPH_CLKDIV23_ADDR(base)             ((base) + (0x104))

/* 寄存器说明：时钟分频比控制寄存器24。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV24_UNION */
#define SOC_CRGPERIPH_CLKDIV24_ADDR(base)             ((base) + (0x108))

/* 寄存器说明：时钟分频比控制寄存器25。
   位域定义UNION结构:  SOC_CRGPERIPH_CLKDIV25_UNION */
#define SOC_CRGPERIPH_CLKDIV25_ADDR(base)             ((base) + (0x10C))

/* 寄存器说明：外设状态寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PER_STAT0_UNION */
#define SOC_CRGPERIPH_PER_STAT0_ADDR(base)            ((base) + (0x110))

/* 寄存器说明：外设状态寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PER_STAT1_UNION */
#define SOC_CRGPERIPH_PER_STAT1_ADDR(base)            ((base) + (0x114))

/* 寄存器说明：外设状态寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PER_STAT2_UNION */
#define SOC_CRGPERIPH_PER_STAT2_ADDR(base)            ((base) + (0x118))

/* 寄存器说明：外设状态寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PER_STAT3_UNION */
#define SOC_CRGPERIPH_PER_STAT3_ADDR(base)            ((base) + (0x11C))

/* 寄存器说明：外设控制寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCTRL0_UNION */
#define SOC_CRGPERIPH_PERCTRL0_ADDR(base)             ((base) + (0x120))

/* 寄存器说明：外设控制寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCTRL1_UNION */
#define SOC_CRGPERIPH_PERCTRL1_ADDR(base)             ((base) + (0x124))

/* 寄存器说明：外设控制寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCTRL2_UNION */
#define SOC_CRGPERIPH_PERCTRL2_ADDR(base)             ((base) + (0x128))

/* 寄存器说明：外设控制寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCTRL3_UNION */
#define SOC_CRGPERIPH_PERCTRL3_ADDR(base)             ((base) + (0x12C))

/* 寄存器说明：外设控制寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCTRL4_UNION */
#define SOC_CRGPERIPH_PERCTRL4_ADDR(base)             ((base) + (0x130))

/* 寄存器说明：外设控制寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCTRL5_UNION */
#define SOC_CRGPERIPH_PERCTRL5_ADDR(base)             ((base) + (0x134))

/* 寄存器说明：外设控制寄存器6。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCTRL6_UNION */
#define SOC_CRGPERIPH_PERCTRL6_ADDR(base)             ((base) + (0x138))

/* 寄存器说明：外设TIME控制寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_PERTIMECTRL_UNION */
#define SOC_CRGPERIPH_PERTIMECTRL_ADDR(base)          ((base) + (0x140))

/* 寄存器说明：掉电子系统ISO使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISOEN_UNION */
#define SOC_CRGPERIPH_ISOEN_ADDR(base)                ((base) + (0x144))

/* 寄存器说明：掉电子系统ISO使能撤销寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISODIS_UNION */
#define SOC_CRGPERIPH_ISODIS_ADDR(base)               ((base) + (0x148))

/* 寄存器说明：掉电子系统ISO使能状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISOSTAT_UNION */
#define SOC_CRGPERIPH_ISOSTAT_ADDR(base)              ((base) + (0x14C))

/* 寄存器说明：掉电子系统电源使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_PERPWREN_UNION */
#define SOC_CRGPERIPH_PERPWREN_ADDR(base)             ((base) + (0x150))

/* 寄存器说明：掉电子系统电源使能撤销寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_PERPWRDIS_UNION */
#define SOC_CRGPERIPH_PERPWRDIS_ADDR(base)            ((base) + (0x154))

/* 寄存器说明：掉电子系统电源使能状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_PERPWRSTAT_UNION */
#define SOC_CRGPERIPH_PERPWRSTAT_ADDR(base)           ((base) + (0x158))

/* 寄存器说明：掉电子系统最终电源状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_PERPWRACK_UNION */
#define SOC_CRGPERIPH_PERPWRACK_ADDR(base)            ((base) + (0x15C))

/* 寄存器说明：A53 CLUSTER子系统时钟使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_CLKEN_UNION */
#define SOC_CRGPERIPH_A53_CLKEN_ADDR(base)            ((base) + (0x160))

/* 寄存器说明：A53 CLUSTER子系统软复位使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_RSTEN_UNION */
#define SOC_CRGPERIPH_A53_RSTEN_ADDR(base)            ((base) + (0x164))

/* 寄存器说明：A53 CLUSTER子系统软复位撤离寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_RSTDIS_UNION */
#define SOC_CRGPERIPH_A53_RSTDIS_ADDR(base)           ((base) + (0x168))

/* 寄存器说明：A53 CLUSTER子系统软复位使能状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_RSTSTAT_UNION */
#define SOC_CRGPERIPH_A53_RSTSTAT_ADDR(base)          ((base) + (0x16C))

/* 寄存器说明：A53 CLUSTER ADB低功耗寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_ADBLPSTAT_UNION */
#define SOC_CRGPERIPH_A53_ADBLPSTAT_ADDR(base)        ((base) + (0x174))

/* 寄存器说明：A53 CLUSTER控制配置寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_CTRL0_UNION */
#define SOC_CRGPERIPH_A53_CTRL0_ADDR(base)            ((base) + (0x178))

/* 寄存器说明：A53 CLUSTER控制配置寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_CTRL1_UNION */
#define SOC_CRGPERIPH_A53_CTRL1_ADDR(base)            ((base) + (0x17C))

/* 寄存器说明：A53 CLUSTER控制配置寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_CTRL2_UNION */
#define SOC_CRGPERIPH_A53_CTRL2_ADDR(base)            ((base) + (0x180))

/* 寄存器说明：A53 CLUSTER状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_STAT_UNION */
#define SOC_CRGPERIPH_A53_STAT_ADDR(base)             ((base) + (0x194))

/* 寄存器说明：A57 CLUSTER子系统时钟使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_CLKEN_UNION */
#define SOC_CRGPERIPH_MAIA_CLKEN_ADDR(base)           ((base) + (0x1C0))

/* 寄存器说明：A57 CLUSTER子系统软复位使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_RSTEN_UNION */
#define SOC_CRGPERIPH_MAIA_RSTEN_ADDR(base)           ((base) + (0x1C4))

/* 寄存器说明：A57 CLUSTER子系统软复位撤离寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_RSTDIS_UNION */
#define SOC_CRGPERIPH_MAIA_RSTDIS_ADDR(base)          ((base) + (0x1C8))

/* 寄存器说明：A57 CLUSTER子系统软复位使能状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_RSTSTAT_UNION */
#define SOC_CRGPERIPH_MAIA_RSTSTAT_ADDR(base)         ((base) + (0x1CC))

/* 寄存器说明：A57 CLUSTER ADB低功耗寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_ADBLPSTAT_UNION */
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_ADDR(base)       ((base) + (0x1D4))

/* 寄存器说明：A57 CLUSTER控制配置寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_CTRL0_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL0_ADDR(base)           ((base) + (0x1D8))

/* 寄存器说明：A57 CLUSTER控制配置寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_CTRL1_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL1_ADDR(base)           ((base) + (0x1DC))

/* 寄存器说明：A57 CLUSTER控制配置寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_CTRL2_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL2_ADDR(base)           ((base) + (0x1E0))

/* 寄存器说明：A57 CLUSTER状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_STAT_UNION */
#define SOC_CRGPERIPH_MAIA_STAT_ADDR(base)            ((base) + (0x1F4))

/* 寄存器说明：A57 CLUSTER状态寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_STAT_1_UNION */
#define SOC_CRGPERIPH_MAIA_STAT_1_ADDR(base)          ((base) + (0x1F8))

/* 寄存器说明：core sight状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_CORESIGHTSTAT_UNION */
#define SOC_CRGPERIPH_CORESIGHTSTAT_ADDR(base)        ((base) + (0x200))

/* 寄存器说明：core sight低功耗寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_CORESIGHTLPSTAT_UNION */
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_ADDR(base)      ((base) + (0x204))

/* 寄存器说明：core sight控制配置寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_CORESIGHTCTRL0_UNION */
#define SOC_CRGPERIPH_CORESIGHTCTRL0_ADDR(base)       ((base) + (0x208))

/* 寄存器说明：core sight ETF中断状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_CORESIGHTETFINT_UNION */
#define SOC_CRGPERIPH_CORESIGHTETFINT_ADDR(base)      ((base) + (0x20C))

/* 寄存器说明：core sight ETR中断状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_CORESIGHTETRINT_UNION */
#define SOC_CRGPERIPH_CORESIGHTETRINT_ADDR(base)      ((base) + (0x210))

/* 寄存器说明：CCI400状态寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_CCI400STAT1_UNION */
#define SOC_CRGPERIPH_CCI400STAT1_ADDR(base)          ((base) + (0x21C))

/* 寄存器说明：ADB400状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ADB400STAT_UNION */
#define SOC_CRGPERIPH_ADB400STAT_ADDR(base)           ((base) + (0x220))

/* 寄存器说明：CCI400控制配置寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_CCI400CTRL0_UNION */
#define SOC_CRGPERIPH_CCI400CTRL0_ADDR(base)          ((base) + (0x228))

/* 寄存器说明：CCI400控制配置寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_CCI400CTRL1_UNION */
#define SOC_CRGPERIPH_CCI400CTRL1_ADDR(base)          ((base) + (0x22C))

/* 寄存器说明：CCI400状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_CCI400STAT_UNION */
#define SOC_CRGPERIPH_CCI400STAT_ADDR(base)           ((base) + (0x230))

/* 寄存器说明：G3D ADB0低功耗寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_G3D_0_ADBLPSTAT_UNION */
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_ADDR(base)      ((base) + (0x234))

/* 寄存器说明：G3D ADB1低功耗寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_G3D_1_ADBLPSTAT_UNION */
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_ADDR(base)      ((base) + (0x238))

/* 寄存器说明：外设IP防挂死功能byapss控制寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_IPCLKRST_BYPASS0_UNION */
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_ADDR(base)     ((base) + (0x240))

/* 寄存器说明：外设IP防挂死功能byapss控制寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_IPCLKRST_BYPASS1_UNION */
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ADDR(base)     ((base) + (0x244))

/* 寄存器说明：外设IP防挂死功能byapss控制寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_IPCLKRST_BYPASS2_UNION */
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_ADDR(base)     ((base) + (0x248))

/* 寄存器说明：A53上下电状态机使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_PDCEN_UNION */
#define SOC_CRGPERIPH_A53_PDCEN_ADDR(base)            ((base) + (0x260))

/* 寄存器说明：A53从核上下电完成中断使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREPWRINTEN_UNION */
#define SOC_CRGPERIPH_A53_COREPWRINTEN_ADDR(base)     ((base) + (0x264))

/* 寄存器说明：A53从核上下电完成中断状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREPWRINTSTAT_UNION */
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_ADDR(base)   ((base) + (0x268))

/* 寄存器说明：A53从核GIC中断屏蔽寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREGICMASK_UNION */
#define SOC_CRGPERIPH_A53_COREGICMASK_ADDR(base)      ((base) + (0x26C))

/* 寄存器说明：A53从核上电请求寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREPOWERUP_UNION */
#define SOC_CRGPERIPH_A53_COREPOWERUP_ADDR(base)      ((base) + (0x270))

/* 寄存器说明：A53从核下电请求寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREPOWERDN_UNION */
#define SOC_CRGPERIPH_A53_COREPOWERDN_ADDR(base)      ((base) + (0x274))

/* 寄存器说明：A53从核状态机状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREPOWERSTAT_UNION */
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_ADDR(base)    ((base) + (0x278))

/* 寄存器说明：A53从核上电时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREPWRUPTIME_UNION */
#define SOC_CRGPERIPH_A53_COREPWRUPTIME_ADDR(base)    ((base) + (0x27C))

/* 寄存器说明：A53从核下电时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREPWRDNTIME_UNION */
#define SOC_CRGPERIPH_A53_COREPWRDNTIME_ADDR(base)    ((base) + (0x280))

/* 寄存器说明：A53从核钳位配置时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREISOTIME_UNION */
#define SOC_CRGPERIPH_A53_COREISOTIME_ADDR(base)      ((base) + (0x284))

/* 寄存器说明：A53从核DBG配置时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREDBGTIME_UNION */
#define SOC_CRGPERIPH_A53_COREDBGTIME_ADDR(base)      ((base) + (0x288))

/* 寄存器说明：A53从核复位时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_CORERSTTIME_UNION */
#define SOC_CRGPERIPH_A53_CORERSTTIME_ADDR(base)      ((base) + (0x28C))

/* 寄存器说明：A53从核解复位时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_COREURSTTIME_UNION */
#define SOC_CRGPERIPH_A53_COREURSTTIME_ADDR(base)     ((base) + (0x290))

/* 寄存器说明：MAIA上下电状态机使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_PDCEN_UNION */
#define SOC_CRGPERIPH_MAIA_PDCEN_ADDR(base)           ((base) + (0x300))

/* 寄存器说明：MAIA_从核上下电完成中断使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREPWRINTEN_UNION */
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_ADDR(base)    ((base) + (0x304))

/* 寄存器说明：MAIA从核上下电完成中断状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_UNION */
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_ADDR(base)  ((base) + (0x308))

/* 寄存器说明：MAIA从核GIC中断屏蔽寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREGICMASK_UNION */
#define SOC_CRGPERIPH_MAIA_COREGICMASK_ADDR(base)     ((base) + (0x30C))

/* 寄存器说明：MAIA从核上电请求寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREPOWERUP_UNION */
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_ADDR(base)     ((base) + (0x310))

/* 寄存器说明：MAIA从核下电请求寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREPOWERDN_UNION */
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_ADDR(base)     ((base) + (0x314))

/* 寄存器说明：MAIA从核状态机状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREPOWERSTAT_UNION */
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_ADDR(base)   ((base) + (0x318))

/* 寄存器说明：MAIA从核上电时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREPWRUPTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREPWRUPTIME_ADDR(base)   ((base) + (0x31C))

/* 寄存器说明：MAIA从核下电时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREPWRDNTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREPWRDNTIME_ADDR(base)   ((base) + (0x320))

/* 寄存器说明：MAIA从核钳位配置时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREISOTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREISOTIME_ADDR(base)     ((base) + (0x324))

/* 寄存器说明：MAIA从核DBG配置时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREDBGTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREDBGTIME_ADDR(base)     ((base) + (0x328))

/* 寄存器说明：MAIA从核复位时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_CORERSTTIME_UNION */
#define SOC_CRGPERIPH_MAIA_CORERSTTIME_ADDR(base)     ((base) + (0x32C))

/* 寄存器说明：MAIA从核解复位时间寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_COREURSTTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREURSTTIME_ADDR(base)    ((base) + (0x330))

/* 寄存器说明：ISPA7子系统时钟使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISPA7_CLKEN_UNION */
#define SOC_CRGPERIPH_ISPA7_CLKEN_ADDR(base)          ((base) + (0x340))

/* 寄存器说明：ISPA7子系统软复位使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISPA7_RSTEN_UNION */
#define SOC_CRGPERIPH_ISPA7_RSTEN_ADDR(base)          ((base) + (0x344))

/* 寄存器说明：ISPA7子系统软复位撤离寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISPA7_RSTDIS_UNION */
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ADDR(base)         ((base) + (0x348))

/* 寄存器说明：ISPA7子系统软复位使能状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISPA7_RSTSTAT_UNION */
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ADDR(base)        ((base) + (0x34C))

/* 寄存器说明：ISPA7状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISPA7_STAT_UNION */
#define SOC_CRGPERIPH_ISPA7_STAT_ADDR(base)           ((base) + (0x354))

/* 寄存器说明：外设自动降频控制寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV0_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV0_ADDR(base)        ((base) + (0x360))

/* 寄存器说明：外设自动降频控制寄存器1。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV1_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV1_ADDR(base)        ((base) + (0x364))

/* 寄存器说明：外设自动降频控制寄存器2。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV2_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV2_ADDR(base)        ((base) + (0x368))

/* 寄存器说明：外设自动降频控制寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV3_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV3_ADDR(base)        ((base) + (0x36C))

/* 寄存器说明：外设自动降频控制寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV4_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV4_ADDR(base)        ((base) + (0x370))

/* 寄存器说明：外设自动降频控制寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV5_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV5_ADDR(base)        ((base) + (0x374))

/* 寄存器说明：外设自动降频控制寄存器6。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV6_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV6_ADDR(base)        ((base) + (0x378))

/* 寄存器说明：外设自动降频控制寄存器7。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV7_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV7_ADDR(base)        ((base) + (0x37C))

/* 寄存器说明：外设自动降频控制寄存器8。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV8_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV8_ADDR(base)        ((base) + (0x380))

/* 寄存器说明：外设自动降频控制寄存器9。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV9_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV9_ADDR(base)        ((base) + (0x384))

/* 寄存器说明：外设自动降频控制寄存器10。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV10_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV10_ADDR(base)       ((base) + (0x388))

/* 寄存器说明：外设自动降频控制寄存器11。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV11_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV11_ADDR(base)       ((base) + (0x38C))

/* 寄存器说明：外设自动降频控制寄存器12。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV12_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV12_ADDR(base)       ((base) + (0x390))

/* 寄存器说明：外设自动降频控制寄存器13。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV13_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV13_ADDR(base)       ((base) + (0x394))

/* 寄存器说明：外设自动降频控制寄存器14。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV14_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV14_ADDR(base)       ((base) + (0x398))

/* 寄存器说明：外设自动降频控制寄存器15。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV15_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV15_ADDR(base)       ((base) + (0x39C))

/* 寄存器说明：外设自动降频控制寄存器ACPU。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV_ACPU_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_ADDR(base)    ((base) + (0x404))

/* 寄存器说明：外设自动降频控制寄存器MCPU。
   位域定义UNION结构:  SOC_CRGPERIPH_PERI_AUTODIV_MCPU_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_ADDR(base)    ((base) + (0x408))

/* 寄存器说明：外设时钟使能寄存器6。
   位域定义UNION结构:  SOC_CRGPERIPH_PEREN6_UNION */
#define SOC_CRGPERIPH_PEREN6_ADDR(base)               ((base) + (0x410))

/* 寄存器说明：外设时钟禁止寄存器6。
   位域定义UNION结构:  SOC_CRGPERIPH_PERDIS6_UNION */
#define SOC_CRGPERIPH_PERDIS6_ADDR(base)              ((base) + (0x414))

/* 寄存器说明：外设时钟使能状态寄存器6。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCLKEN6_UNION */
#define SOC_CRGPERIPH_PERCLKEN6_ADDR(base)            ((base) + (0x418))

/* 寄存器说明：外设时钟最终状态寄存器6。
   位域定义UNION结构:  SOC_CRGPERIPH_PERSTAT6_UNION */
#define SOC_CRGPERIPH_PERSTAT6_ADDR(base)             ((base) + (0x41C))

/* 寄存器说明：外设时钟使能寄存器7。
   位域定义UNION结构:  SOC_CRGPERIPH_PEREN7_UNION */
#define SOC_CRGPERIPH_PEREN7_ADDR(base)               ((base) + (0x420))

/* 寄存器说明：外设时钟禁止寄存器7。
   位域定义UNION结构:  SOC_CRGPERIPH_PERDIS7_UNION */
#define SOC_CRGPERIPH_PERDIS7_ADDR(base)              ((base) + (0x424))

/* 寄存器说明：外设时钟使能状态寄存器7。
   位域定义UNION结构:  SOC_CRGPERIPH_PERCLKEN7_UNION */
#define SOC_CRGPERIPH_PERCLKEN7_ADDR(base)            ((base) + (0x428))

/* 寄存器说明：外设时钟最终状态寄存器7。
   位域定义UNION结构:  SOC_CRGPERIPH_PERSTAT7_UNION */
#define SOC_CRGPERIPH_PERSTAT7_ADDR(base)             ((base) + (0x42C))

/* 寄存器说明：IVP安全软复位使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_IVP_SEC_RSTEN_UNION */
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ADDR(base)        ((base) + (0xC00))

/* 寄存器说明：IVP安全软复位撤离寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_IVP_SEC_RSTDIS_UNION */
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ADDR(base)       ((base) + (0xC04))

/* 寄存器说明：IVP安全软复位使能状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_IVP_SEC_RSTSTAT_UNION */
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ADDR(base)      ((base) + (0xC08))

/* 寄存器说明：ISP安全软复位使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISP_SEC_RSTEN_UNION */
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ADDR(base)        ((base) + (0xC80))

/* 寄存器说明：ISP安全软复位撤离寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISP_SEC_RSTDIS_UNION */
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ADDR(base)       ((base) + (0xC84))

/* 寄存器说明：ISP安全软复位状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_ISP_SEC_RSTSTAT_UNION */
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ADDR(base)      ((base) + (0xC88))

/* 寄存器说明：ISPA7控制配置寄存器0。
   位域定义UNION结构:  SOC_CRGPERIPH_ISPA7_CTRL0_UNION */
#define SOC_CRGPERIPH_ISPA7_CTRL0_ADDR(base)          ((base) + (0xC90))

/* 寄存器说明：MODEM安全软复位使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MDM_SEC_RSTEN_UNION */
#define SOC_CRGPERIPH_MDM_SEC_RSTEN_ADDR(base)        ((base) + (0xD00))

/* 寄存器说明：MODEM安全软复位撤离寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MDM_SEC_RSTDIS_UNION */
#define SOC_CRGPERIPH_MDM_SEC_RSTDIS_ADDR(base)       ((base) + (0xD04))

/* 寄存器说明：MODEM安全软复位使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_MDM_SEC_RSTSTAT_UNION */
#define SOC_CRGPERIPH_MDM_SEC_RSTSTAT_ADDR(base)      ((base) + (0xD08))

/* 寄存器说明：A53 CLUSTER控制配置寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_CTRL3_UNION */
#define SOC_CRGPERIPH_A53_CTRL3_ADDR(base)            ((base) + (0xE00))

/* 寄存器说明：A53 CLUSTER控制配置寄存器4。。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_CTRL4_UNION */
#define SOC_CRGPERIPH_A53_CTRL4_ADDR(base)            ((base) + (0xE04))

/* 寄存器说明：A53 CLUSTER控制配置寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_CTRL5_UNION */
#define SOC_CRGPERIPH_A53_CTRL5_ADDR(base)            ((base) + (0xE08))

/* 寄存器说明：A53 CLUSTER控制配置寄存器6。
   位域定义UNION结构:  SOC_CRGPERIPH_A53_CTRL6_UNION */
#define SOC_CRGPERIPH_A53_CTRL6_ADDR(base)            ((base) + (0xE0C))

/* 寄存器说明：A57 CLUSTER控制配置寄存器3。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_CTRL3_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL3_ADDR(base)           ((base) + (0xE10))

/* 寄存器说明：A57 CLUSTER控制配置寄存器4。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_CTRL4_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL4_ADDR(base)           ((base) + (0xE14))

/* 寄存器说明：A57 CLUSTER控制配置寄存器5。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_CTRL5_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL5_ADDR(base)           ((base) + (0xE18))

/* 寄存器说明：A57 CLUSTER控制配置寄存器6。
   位域定义UNION结构:  SOC_CRGPERIPH_MAIA_CTRL6_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL6_ADDR(base)           ((base) + (0xE1C))

/* 寄存器说明：通用安全软复位使能寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_GENERAL_SEC_RSTEN_UNION */
#define SOC_CRGPERIPH_GENERAL_SEC_RSTEN_ADDR(base)    ((base) + (0xE20))

/* 寄存器说明：通用安全软复位撤离寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_UNION */
#define SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_ADDR(base)   ((base) + (0xE24))

/* 寄存器说明：通用安全软复位使能状态寄存器。
   位域定义UNION结构:  SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_UNION */
#define SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_ADDR(base)  ((base) + (0xE28))





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
                     (1/1) register_CRGPERIPH
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PEREN0_UNION
 结构说明  : PEREN0 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_b          : 1;  /* bit[0] : 外设时钟使能控制：
                                                                 0：写0无效果；
                                                                 1：使能IP时钟。 */
        unsigned int  gt_clk_ddrbyp_ckp0       : 1;  /* bit[1] :  */
        unsigned int  gt_clk_ddrc              : 1;  /* bit[2] :  */
        unsigned int  reserved_0               : 1;  /* bit[3] :  */
        unsigned int  gt_clk_ddrphy_ref        : 1;  /* bit[4] :  */
        unsigned int  gt_clk_vcodeccfg         : 1;  /* bit[5] :  */
        unsigned int  gt_clk_vcodecbus         : 1;  /* bit[6] :  */
        unsigned int  reserved_1               : 1;  /* bit[7] : 保留。 */
        unsigned int  reserved_2               : 1;  /* bit[8] : 保留。 */
        unsigned int  gt_clk_sysbus            : 1;  /* bit[9] :  */
        unsigned int  gt_clk_cfgbus            : 1;  /* bit[10]:  */
        unsigned int  gt_clk_sys2cfgbus        : 1;  /* bit[11]:  */
        unsigned int  gt_clk_vivobus2ddrc      : 1;  /* bit[12]:  */
        unsigned int  gt_hclk_emmc0            : 1;  /* bit[13]:  */
        unsigned int  gt_clk_mmc1peri2sysbus   : 1;  /* bit[14]:  */
        unsigned int  gt_clk_mmc1_peribus      : 1;  /* bit[15]:  */
        unsigned int  gt_hclk_emmc1            : 1;  /* bit[16]:  */
        unsigned int  gt_clk_mmc0peri2sysbus   : 1;  /* bit[17]:  */
        unsigned int  gt_clk_mmc0_peribus      : 1;  /* bit[18]:  */
        unsigned int  gt_hclk_sdio0            : 1;  /* bit[19]:  */
        unsigned int  gt_clk_lpm32cfgbus       : 1;  /* bit[20]:  */
        unsigned int  gt_hclk_sdio1            : 1;  /* bit[21]:  */
        unsigned int  gt_clk_dmabus            : 1;  /* bit[22]:  */
        unsigned int  gt_clk_dma2cfgbus        : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hclk_memrep       : 1;  /* bit[24]:  */
        unsigned int  gt_clk_dbgsechsicbus     : 1;  /* bit[25]:  */
        unsigned int  gt_clk_dbgsechsic2sysbus : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ddrphy_a          : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ddrphy_c          : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ddrphy_d          : 1;  /* bit[29]:  */
        unsigned int  gt_hclk_sd               : 1;  /* bit[30]:  */
        unsigned int  gt_clk_aomm              : 1;  /* bit[31]: 外设时钟使能控制：
                                                                 0：写0无效果；
                                                                 1：使能IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PEREN0_UNION;
#endif
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_b_START           (0)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_b_END             (0)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrbyp_ckp0_START        (1)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrbyp_ckp0_END          (1)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrc_START               (2)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrc_END                 (2)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_ref_START         (4)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_ref_END           (4)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodeccfg_START          (5)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodeccfg_END            (5)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodecbus_START          (6)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodecbus_END            (6)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sysbus_START             (9)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sysbus_END               (9)
#define SOC_CRGPERIPH_PEREN0_gt_clk_cfgbus_START             (10)
#define SOC_CRGPERIPH_PEREN0_gt_clk_cfgbus_END               (10)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sys2cfgbus_START         (11)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sys2cfgbus_END           (11)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vivobus2ddrc_START       (12)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vivobus2ddrc_END         (12)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc0_START             (13)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc0_END               (13)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1peri2sysbus_START    (14)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1peri2sysbus_END      (14)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1_peribus_START       (15)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1_peribus_END         (15)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc1_START             (16)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc1_END               (16)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0peri2sysbus_START    (17)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0peri2sysbus_END      (17)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0_peribus_START       (18)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0_peribus_END         (18)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio0_START             (19)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio0_END               (19)
#define SOC_CRGPERIPH_PEREN0_gt_clk_lpm32cfgbus_START        (20)
#define SOC_CRGPERIPH_PEREN0_gt_clk_lpm32cfgbus_END          (20)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio1_START             (21)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio1_END               (21)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dmabus_START             (22)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dmabus_END               (22)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dma2cfgbus_START         (23)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dma2cfgbus_END           (23)
#define SOC_CRGPERIPH_PEREN0_gt_clk_hclk_memrep_START        (24)
#define SOC_CRGPERIPH_PEREN0_gt_clk_hclk_memrep_END          (24)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsicbus_START      (25)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsicbus_END        (25)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsic2sysbus_START  (26)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsic2sysbus_END    (26)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_a_START           (27)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_a_END             (27)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_c_START           (28)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_c_END             (28)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_d_START           (29)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_d_END             (29)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sd_START                (30)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sd_END                  (30)
#define SOC_CRGPERIPH_PEREN0_gt_clk_aomm_START               (31)
#define SOC_CRGPERIPH_PEREN0_gt_clk_aomm_END                 (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERDIS0_UNION
 结构说明  : PERDIS0 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_b          : 1;  /* bit[0] : 外设时钟禁止控制：
                                                                 0：写0无效果；
                                                                 1：禁止IP时钟。 */
        unsigned int  gt_clk_ddrbyp_ckp0       : 1;  /* bit[1] :  */
        unsigned int  gt_clk_ddrc              : 1;  /* bit[2] :  */
        unsigned int  reserved_0               : 1;  /* bit[3] :  */
        unsigned int  gt_clk_ddrphy_ref        : 1;  /* bit[4] :  */
        unsigned int  gt_clk_vcodeccfg         : 1;  /* bit[5] :  */
        unsigned int  gt_clk_vcodecbus         : 1;  /* bit[6] :  */
        unsigned int  reserved_1               : 1;  /* bit[7] : 保留。 */
        unsigned int  reserved_2               : 1;  /* bit[8] : 保留。 */
        unsigned int  gt_clk_sysbus            : 1;  /* bit[9] :  */
        unsigned int  gt_clk_cfgbus            : 1;  /* bit[10]:  */
        unsigned int  gt_clk_sys2cfgbus        : 1;  /* bit[11]:  */
        unsigned int  gt_clk_vivobus2ddrc      : 1;  /* bit[12]:  */
        unsigned int  gt_hclk_emmc0            : 1;  /* bit[13]:  */
        unsigned int  gt_clk_mmc1peri2sysbus   : 1;  /* bit[14]:  */
        unsigned int  gt_clk_mmc1_peribus      : 1;  /* bit[15]:  */
        unsigned int  gt_hclk_emmc1            : 1;  /* bit[16]:  */
        unsigned int  gt_clk_mmc0peri2sysbus   : 1;  /* bit[17]:  */
        unsigned int  gt_clk_mmc0_peribus      : 1;  /* bit[18]:  */
        unsigned int  gt_hclk_sdio0            : 1;  /* bit[19]:  */
        unsigned int  gt_clk_lpm32cfgbus       : 1;  /* bit[20]:  */
        unsigned int  gt_hclk_sdio1            : 1;  /* bit[21]:  */
        unsigned int  gt_clk_dmabus            : 1;  /* bit[22]:  */
        unsigned int  gt_clk_dma2cfgbus        : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hclk_memrep       : 1;  /* bit[24]:  */
        unsigned int  gt_clk_dbgsechsicbus     : 1;  /* bit[25]:  */
        unsigned int  gt_clk_dbgsechsic2sysbus : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ddrphy_a          : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ddrphy_c          : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ddrphy_d          : 1;  /* bit[29]:  */
        unsigned int  gt_hclk_sd               : 1;  /* bit[30]:  */
        unsigned int  gt_clk_aomm              : 1;  /* bit[31]: 外设时钟禁止控制：
                                                                 0：写0无效果；
                                                                 1：禁止IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PERDIS0_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_b_START           (0)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_b_END             (0)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrbyp_ckp0_START        (1)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrbyp_ckp0_END          (1)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrc_START               (2)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrc_END                 (2)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_ref_START         (4)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_ref_END           (4)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodeccfg_START          (5)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodeccfg_END            (5)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodecbus_START          (6)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodecbus_END            (6)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sysbus_START             (9)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sysbus_END               (9)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_cfgbus_START             (10)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_cfgbus_END               (10)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sys2cfgbus_START         (11)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sys2cfgbus_END           (11)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vivobus2ddrc_START       (12)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vivobus2ddrc_END         (12)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc0_START             (13)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc0_END               (13)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1peri2sysbus_START    (14)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1peri2sysbus_END      (14)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1_peribus_START       (15)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1_peribus_END         (15)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc1_START             (16)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc1_END               (16)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0peri2sysbus_START    (17)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0peri2sysbus_END      (17)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0_peribus_START       (18)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0_peribus_END         (18)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio0_START             (19)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio0_END               (19)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_lpm32cfgbus_START        (20)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_lpm32cfgbus_END          (20)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio1_START             (21)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio1_END               (21)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dmabus_START             (22)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dmabus_END               (22)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dma2cfgbus_START         (23)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dma2cfgbus_END           (23)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_hclk_memrep_START        (24)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_hclk_memrep_END          (24)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsicbus_START      (25)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsicbus_END        (25)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsic2sysbus_START  (26)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsic2sysbus_END    (26)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_a_START           (27)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_a_END             (27)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_c_START           (28)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_c_END             (28)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_d_START           (29)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_d_END             (29)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sd_START                (30)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sd_END                  (30)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_aomm_START               (31)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_aomm_END                 (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCLKEN0_UNION
 结构说明  : PERCLKEN0 寄存器结构定义。地址偏移量:0x008，初值:0x7EFFEF9F，宽度:32
 寄存器说明: 外设时钟使能状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_b          : 1;  /* bit[0] : 外设时钟使能状态：
                                                                 0：IP时钟使能撤销状态；
                                                                 1：IP时钟使能状态。 */
        unsigned int  gt_clk_ddrbyp_ckp0       : 1;  /* bit[1] :  */
        unsigned int  gt_clk_ddrc              : 1;  /* bit[2] :  */
        unsigned int  reserved_0               : 1;  /* bit[3] :  */
        unsigned int  gt_clk_ddrphy_ref        : 1;  /* bit[4] :  */
        unsigned int  gt_clk_vcodeccfg         : 1;  /* bit[5] :  */
        unsigned int  gt_clk_vcodecbus         : 1;  /* bit[6] :  */
        unsigned int  reserved_1               : 1;  /* bit[7] : 保留。 */
        unsigned int  reserved_2               : 1;  /* bit[8] : 保留。 */
        unsigned int  gt_clk_sysbus            : 1;  /* bit[9] :  */
        unsigned int  gt_clk_cfgbus            : 1;  /* bit[10]:  */
        unsigned int  gt_clk_sys2cfgbus        : 1;  /* bit[11]:  */
        unsigned int  gt_clk_vivobus2ddrc      : 1;  /* bit[12]:  */
        unsigned int  gt_hclk_emmc0            : 1;  /* bit[13]:  */
        unsigned int  gt_clk_mmc1peri2sysbus   : 1;  /* bit[14]:  */
        unsigned int  gt_clk_mmc1_peribus      : 1;  /* bit[15]:  */
        unsigned int  gt_hclk_emmc1            : 1;  /* bit[16]:  */
        unsigned int  gt_clk_mmc0peri2sysbus   : 1;  /* bit[17]:  */
        unsigned int  gt_clk_mmc0_peribus      : 1;  /* bit[18]:  */
        unsigned int  gt_hclk_sdio0            : 1;  /* bit[19]:  */
        unsigned int  gt_clk_lpm32cfgbus       : 1;  /* bit[20]:  */
        unsigned int  gt_hclk_sdio1            : 1;  /* bit[21]:  */
        unsigned int  gt_clk_dmabus            : 1;  /* bit[22]:  */
        unsigned int  gt_clk_dma2cfgbus        : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hclk_memrep       : 1;  /* bit[24]:  */
        unsigned int  gt_clk_dbgsechsicbus     : 1;  /* bit[25]:  */
        unsigned int  gt_clk_dbgsechsic2sysbus : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ddrphy_a          : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ddrphy_c          : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ddrphy_d          : 1;  /* bit[29]:  */
        unsigned int  gt_hclk_sd               : 1;  /* bit[30]:  */
        unsigned int  gt_clk_aomm              : 1;  /* bit[31]: 外设时钟使能状态：
                                                                 0：IP时钟使能撤销状态；
                                                                 1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERCLKEN0_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_b_START           (0)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_b_END             (0)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrbyp_ckp0_START        (1)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrbyp_ckp0_END          (1)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrc_START               (2)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrc_END                 (2)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_ref_START         (4)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_ref_END           (4)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodeccfg_START          (5)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodeccfg_END            (5)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodecbus_START          (6)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodecbus_END            (6)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sysbus_START             (9)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sysbus_END               (9)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_cfgbus_START             (10)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_cfgbus_END               (10)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sys2cfgbus_START         (11)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sys2cfgbus_END           (11)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vivobus2ddrc_START       (12)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vivobus2ddrc_END         (12)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc0_START             (13)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc0_END               (13)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1peri2sysbus_START    (14)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1peri2sysbus_END      (14)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1_peribus_START       (15)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1_peribus_END         (15)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc1_START             (16)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc1_END               (16)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0peri2sysbus_START    (17)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0peri2sysbus_END      (17)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0_peribus_START       (18)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0_peribus_END         (18)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio0_START             (19)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio0_END               (19)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_lpm32cfgbus_START        (20)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_lpm32cfgbus_END          (20)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio1_START             (21)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio1_END               (21)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dmabus_START             (22)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dmabus_END               (22)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dma2cfgbus_START         (23)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dma2cfgbus_END           (23)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_hclk_memrep_START        (24)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_hclk_memrep_END          (24)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsicbus_START      (25)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsicbus_END        (25)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsic2sysbus_START  (26)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsic2sysbus_END    (26)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_a_START           (27)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_a_END             (27)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_c_START           (28)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_c_END             (28)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_d_START           (29)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_d_END             (29)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sd_START                (30)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sd_END                  (30)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_aomm_START               (31)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_aomm_END                 (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERSTAT0_UNION
 结构说明  : PERSTAT0 寄存器结构定义。地址偏移量:0x00C，初值:0x7EFFEF9F，宽度:32
 寄存器说明: 外设时钟最终状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_b          : 1;  /* bit[0] : 外设时钟最终状态：
                                                                 0：IP时钟禁止状态；
                                                                 1：IP时钟使能状态。 */
        unsigned int  gt_clk_ddrbyp_ckp0       : 1;  /* bit[1] :  */
        unsigned int  gt_clk_ddrc              : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ddrcfg            : 1;  /* bit[3] :  */
        unsigned int  gt_clk_ddrphy_ref        : 1;  /* bit[4] :  */
        unsigned int  gt_clk_vcodeccfg         : 1;  /* bit[5] :  */
        unsigned int  gt_clk_vcodecbus         : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ddrsys_noc        : 1;  /* bit[7] :  */
        unsigned int  gt_clk_ddrsys_ao         : 1;  /* bit[8] :  */
        unsigned int  gt_clk_sysbus            : 1;  /* bit[9] :  */
        unsigned int  gt_clk_cfgbus            : 1;  /* bit[10]:  */
        unsigned int  gt_clk_sys2cfgbus        : 1;  /* bit[11]:  */
        unsigned int  gt_clk_vivobus2ddrc      : 1;  /* bit[12]:  */
        unsigned int  gt_hclk_emmc0            : 1;  /* bit[13]:  */
        unsigned int  gt_clk_mmc1peri2sysbus   : 1;  /* bit[14]:  */
        unsigned int  gt_clk_mmc1_peribus      : 1;  /* bit[15]:  */
        unsigned int  gt_hclk_emmc1            : 1;  /* bit[16]:  */
        unsigned int  gt_clk_mmc0peri2sysbus   : 1;  /* bit[17]:  */
        unsigned int  gt_clk_mmc0_peribus      : 1;  /* bit[18]:  */
        unsigned int  gt_hclk_sdio0            : 1;  /* bit[19]:  */
        unsigned int  gt_clk_lpm32cfgbus       : 1;  /* bit[20]:  */
        unsigned int  gt_hclk_sdio1            : 1;  /* bit[21]:  */
        unsigned int  gt_clk_dmabus            : 1;  /* bit[22]:  */
        unsigned int  gt_clk_dma2cfgbus        : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hclk_memrep       : 1;  /* bit[24]:  */
        unsigned int  gt_clk_dbgsechsicbus     : 1;  /* bit[25]:  */
        unsigned int  gt_clk_dbgsechsic2sysbus : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ddrphy_a          : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ddrphy_c          : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ddrphy_d          : 1;  /* bit[29]:  */
        unsigned int  gt_hclk_sd               : 1;  /* bit[30]:  */
        unsigned int  gt_clk_aomm              : 1;  /* bit[31]: 外设时钟最终状态：
                                                                 0：IP时钟禁止状态；
                                                                 1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERSTAT0_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_b_START           (0)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_b_END             (0)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrbyp_ckp0_START        (1)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrbyp_ckp0_END          (1)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrc_START               (2)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrc_END                 (2)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrcfg_START             (3)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrcfg_END               (3)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_ref_START         (4)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_ref_END           (4)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodeccfg_START          (5)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodeccfg_END            (5)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodecbus_START          (6)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodecbus_END            (6)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_noc_START         (7)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_noc_END           (7)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_ao_START          (8)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_ao_END            (8)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sysbus_START             (9)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sysbus_END               (9)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_cfgbus_START             (10)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_cfgbus_END               (10)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sys2cfgbus_START         (11)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sys2cfgbus_END           (11)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vivobus2ddrc_START       (12)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vivobus2ddrc_END         (12)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc0_START             (13)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc0_END               (13)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1peri2sysbus_START    (14)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1peri2sysbus_END      (14)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1_peribus_START       (15)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1_peribus_END         (15)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc1_START             (16)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc1_END               (16)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0peri2sysbus_START    (17)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0peri2sysbus_END      (17)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0_peribus_START       (18)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0_peribus_END         (18)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio0_START             (19)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio0_END               (19)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_lpm32cfgbus_START        (20)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_lpm32cfgbus_END          (20)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio1_START             (21)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio1_END               (21)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dmabus_START             (22)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dmabus_END               (22)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dma2cfgbus_START         (23)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dma2cfgbus_END           (23)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_hclk_memrep_START        (24)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_hclk_memrep_END          (24)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsicbus_START      (25)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsicbus_END        (25)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsic2sysbus_START  (26)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsic2sysbus_END    (26)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_a_START           (27)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_a_END             (27)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_c_START           (28)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_c_END             (28)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_d_START           (29)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_d_END             (29)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sd_START                (30)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sd_END                  (30)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_aomm_START               (31)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_aomm_END                 (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PEREN1_UNION
 结构说明  : PEREN1 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_gpio0    : 1;  /* bit[0] : 外设时钟使能控制：
                                                         0：写0无效果；
                                                         1：使能IP时钟。 */
        unsigned int  gt_pclk_gpio1    : 1;  /* bit[1] :  */
        unsigned int  gt_pclk_gpio2    : 1;  /* bit[2] :  */
        unsigned int  gt_pclk_gpio3    : 1;  /* bit[3] :  */
        unsigned int  gt_pclk_gpio4    : 1;  /* bit[4] :  */
        unsigned int  gt_pclk_gpio5    : 1;  /* bit[5] :  */
        unsigned int  gt_pclk_gpio6    : 1;  /* bit[6] :  */
        unsigned int  gt_pclk_gpio7    : 1;  /* bit[7] :  */
        unsigned int  gt_pclk_gpio8    : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_gpio9    : 1;  /* bit[9] :  */
        unsigned int  gt_pclk_gpio10   : 1;  /* bit[10]:  */
        unsigned int  gt_pclk_gpio11   : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_gpio12   : 1;  /* bit[12]:  */
        unsigned int  gt_pclk_gpio13   : 1;  /* bit[13]:  */
        unsigned int  gt_pclk_gpio14   : 1;  /* bit[14]:  */
        unsigned int  gt_pclk_gpio15   : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_gpio16   : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_gpio17   : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_gpio18   : 1;  /* bit[18]:  */
        unsigned int  gt_pclk_gpio19   : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_gpio20   : 1;  /* bit[20]:  */
        unsigned int  gt_pclk_gpio21   : 1;  /* bit[21]:  */
        unsigned int  gt_pclk_timer9   : 1;  /* bit[22]:  */
        unsigned int  gt_pclk_timer10  : 1;  /* bit[23]:  */
        unsigned int  gt_pclk_timer11  : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_timer12  : 1;  /* bit[25]:  */
        unsigned int  gt_clk_socp_lpm3 : 1;  /* bit[26]:  */
        unsigned int  gt_clk_djtag     : 1;  /* bit[27]:  */
        unsigned int  gt_clk_socp_acpu : 1;  /* bit[28]:  */
        unsigned int  gt_clk_socp_mcpu : 1;  /* bit[29]:  */
        unsigned int  reserved_0       : 1;  /* bit[30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]: 外设时钟使能控制：
                                                         0：写0无效果；
                                                         1：使能IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PEREN1_UNION;
#endif
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio0_START     (0)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio0_END       (0)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio1_START     (1)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio1_END       (1)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio2_START     (2)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio2_END       (2)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio3_START     (3)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio3_END       (3)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio4_START     (4)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio4_END       (4)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio5_START     (5)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio5_END       (5)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio6_START     (6)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio6_END       (6)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio7_START     (7)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio7_END       (7)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio8_START     (8)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio8_END       (8)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio9_START     (9)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio9_END       (9)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio10_START    (10)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio10_END      (10)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio11_START    (11)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio11_END      (11)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio12_START    (12)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio12_END      (12)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio13_START    (13)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio13_END      (13)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio14_START    (14)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio14_END      (14)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio15_START    (15)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio15_END      (15)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio16_START    (16)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio16_END      (16)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio17_START    (17)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio17_END      (17)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio18_START    (18)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio18_END      (18)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio19_START    (19)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio19_END      (19)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio20_START    (20)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio20_END      (20)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio21_START    (21)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio21_END      (21)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer9_START    (22)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer9_END      (22)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer10_START   (23)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer10_END     (23)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer11_START   (24)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer11_END     (24)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer12_START   (25)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer12_END     (25)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_lpm3_START  (26)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_lpm3_END    (26)
#define SOC_CRGPERIPH_PEREN1_gt_clk_djtag_START      (27)
#define SOC_CRGPERIPH_PEREN1_gt_clk_djtag_END        (27)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_acpu_START  (28)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_acpu_END    (28)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_mcpu_START  (29)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_mcpu_END    (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERDIS1_UNION
 结构说明  : PERDIS1 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_gpio0    : 1;  /* bit[0] : 外设时钟禁止控制：
                                                         0：写0无效果；
                                                         1：禁止IP时钟。 */
        unsigned int  gt_pclk_gpio1    : 1;  /* bit[1] :  */
        unsigned int  gt_pclk_gpio2    : 1;  /* bit[2] :  */
        unsigned int  gt_pclk_gpio3    : 1;  /* bit[3] :  */
        unsigned int  gt_pclk_gpio4    : 1;  /* bit[4] :  */
        unsigned int  gt_pclk_gpio5    : 1;  /* bit[5] :  */
        unsigned int  gt_pclk_gpio6    : 1;  /* bit[6] :  */
        unsigned int  gt_pclk_gpio7    : 1;  /* bit[7] :  */
        unsigned int  gt_pclk_gpio8    : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_gpio9    : 1;  /* bit[9] :  */
        unsigned int  gt_pclk_gpio10   : 1;  /* bit[10]:  */
        unsigned int  gt_pclk_gpio11   : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_gpio12   : 1;  /* bit[12]:  */
        unsigned int  gt_pclk_gpio13   : 1;  /* bit[13]:  */
        unsigned int  gt_pclk_gpio14   : 1;  /* bit[14]:  */
        unsigned int  gt_pclk_gpio15   : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_gpio16   : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_gpio17   : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_gpio18   : 1;  /* bit[18]:  */
        unsigned int  gt_pclk_gpio19   : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_gpio20   : 1;  /* bit[20]:  */
        unsigned int  gt_pclk_gpio21   : 1;  /* bit[21]:  */
        unsigned int  gt_pclk_timer9   : 1;  /* bit[22]:  */
        unsigned int  gt_pclk_timer10  : 1;  /* bit[23]:  */
        unsigned int  gt_pclk_timer11  : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_timer12  : 1;  /* bit[25]:  */
        unsigned int  gt_clk_socp_lpm3 : 1;  /* bit[26]:  */
        unsigned int  gt_clk_djtag     : 1;  /* bit[27]:  */
        unsigned int  gt_clk_socp_acpu : 1;  /* bit[28]:  */
        unsigned int  gt_clk_socp_mcpu : 1;  /* bit[29]:  */
        unsigned int  reserved_0       : 1;  /* bit[30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]: 外设时钟禁止控制：
                                                         0：写0无效果；
                                                         1：禁止IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PERDIS1_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio0_START     (0)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio0_END       (0)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio1_START     (1)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio1_END       (1)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio2_START     (2)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio2_END       (2)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio3_START     (3)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio3_END       (3)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio4_START     (4)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio4_END       (4)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio5_START     (5)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio5_END       (5)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio6_START     (6)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio6_END       (6)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio7_START     (7)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio7_END       (7)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio8_START     (8)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio8_END       (8)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio9_START     (9)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio9_END       (9)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio10_START    (10)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio10_END      (10)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio11_START    (11)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio11_END      (11)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio12_START    (12)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio12_END      (12)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio13_START    (13)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio13_END      (13)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio14_START    (14)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio14_END      (14)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio15_START    (15)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio15_END      (15)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio16_START    (16)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio16_END      (16)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio17_START    (17)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio17_END      (17)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio18_START    (18)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio18_END      (18)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio19_START    (19)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio19_END      (19)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio20_START    (20)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio20_END      (20)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio21_START    (21)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio21_END      (21)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer9_START    (22)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer9_END      (22)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer10_START   (23)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer10_END     (23)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer11_START   (24)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer11_END     (24)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer12_START   (25)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer12_END     (25)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_lpm3_START  (26)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_lpm3_END    (26)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_djtag_START      (27)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_djtag_END        (27)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_acpu_START  (28)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_acpu_END    (28)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_mcpu_START  (29)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_mcpu_END    (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCLKEN1_UNION
 结构说明  : PERCLKEN1 寄存器结构定义。地址偏移量:0x018，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 外设时钟使能状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_gpio0    : 1;  /* bit[0] : 外设时钟使能状态：
                                                         0：IP时钟使能撤销状态；
                                                         1：IP时钟使能状态。 */
        unsigned int  gt_pclk_gpio1    : 1;  /* bit[1] :  */
        unsigned int  gt_pclk_gpio2    : 1;  /* bit[2] :  */
        unsigned int  gt_pclk_gpio3    : 1;  /* bit[3] :  */
        unsigned int  gt_pclk_gpio4    : 1;  /* bit[4] :  */
        unsigned int  gt_pclk_gpio5    : 1;  /* bit[5] :  */
        unsigned int  gt_pclk_gpio6    : 1;  /* bit[6] :  */
        unsigned int  gt_pclk_gpio7    : 1;  /* bit[7] :  */
        unsigned int  gt_pclk_gpio8    : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_gpio9    : 1;  /* bit[9] :  */
        unsigned int  gt_pclk_gpio10   : 1;  /* bit[10]:  */
        unsigned int  gt_pclk_gpio11   : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_gpio12   : 1;  /* bit[12]:  */
        unsigned int  gt_pclk_gpio13   : 1;  /* bit[13]:  */
        unsigned int  gt_pclk_gpio14   : 1;  /* bit[14]:  */
        unsigned int  gt_pclk_gpio15   : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_gpio16   : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_gpio17   : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_gpio18   : 1;  /* bit[18]:  */
        unsigned int  gt_pclk_gpio19   : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_gpio20   : 1;  /* bit[20]:  */
        unsigned int  gt_pclk_gpio21   : 1;  /* bit[21]:  */
        unsigned int  gt_pclk_timer9   : 1;  /* bit[22]:  */
        unsigned int  gt_pclk_timer10  : 1;  /* bit[23]:  */
        unsigned int  gt_pclk_timer11  : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_timer12  : 1;  /* bit[25]:  */
        unsigned int  gt_clk_socp_lpm3 : 1;  /* bit[26]:  */
        unsigned int  gt_clk_djtag     : 1;  /* bit[27]:  */
        unsigned int  gt_clk_socp_acpu : 1;  /* bit[28]:  */
        unsigned int  gt_clk_socp_mcpu : 1;  /* bit[29]:  */
        unsigned int  reserved_0       : 1;  /* bit[30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]: 外设时钟使能状态：
                                                         0：IP时钟使能撤销状态；
                                                         1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERCLKEN1_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio0_START     (0)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio0_END       (0)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio1_START     (1)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio1_END       (1)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio2_START     (2)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio2_END       (2)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio3_START     (3)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio3_END       (3)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio4_START     (4)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio4_END       (4)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio5_START     (5)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio5_END       (5)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio6_START     (6)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio6_END       (6)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio7_START     (7)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio7_END       (7)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio8_START     (8)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio8_END       (8)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio9_START     (9)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio9_END       (9)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio10_START    (10)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio10_END      (10)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio11_START    (11)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio11_END      (11)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio12_START    (12)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio12_END      (12)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio13_START    (13)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio13_END      (13)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio14_START    (14)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio14_END      (14)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio15_START    (15)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio15_END      (15)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio16_START    (16)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio16_END      (16)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio17_START    (17)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio17_END      (17)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio18_START    (18)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio18_END      (18)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio19_START    (19)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio19_END      (19)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio20_START    (20)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio20_END      (20)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio21_START    (21)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio21_END      (21)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer9_START    (22)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer9_END      (22)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer10_START   (23)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer10_END     (23)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer11_START   (24)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer11_END     (24)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer12_START   (25)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer12_END     (25)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_lpm3_START  (26)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_lpm3_END    (26)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_djtag_START      (27)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_djtag_END        (27)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_acpu_START  (28)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_acpu_END    (28)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_mcpu_START  (29)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_mcpu_END    (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERSTAT1_UNION
 结构说明  : PERSTAT1 寄存器结构定义。地址偏移量:0x01C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 外设时钟最终状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_gpio0   : 1;  /* bit[0] : 外设时钟最终状态：
                                                        0：IP时钟禁止状态；
                                                        1：IP时钟使能状态。 */
        unsigned int  gt_pclk_gpio1   : 1;  /* bit[1] :  */
        unsigned int  gt_pclk_gpio2   : 1;  /* bit[2] :  */
        unsigned int  gt_pclk_gpio3   : 1;  /* bit[3] :  */
        unsigned int  gt_pclk_gpio4   : 1;  /* bit[4] :  */
        unsigned int  gt_pclk_gpio5   : 1;  /* bit[5] :  */
        unsigned int  gt_pclk_gpio6   : 1;  /* bit[6] :  */
        unsigned int  gt_pclk_gpio7   : 1;  /* bit[7] :  */
        unsigned int  gt_pclk_gpio8   : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_gpio9   : 1;  /* bit[9] :  */
        unsigned int  gt_pclk_gpio10  : 1;  /* bit[10]:  */
        unsigned int  gt_pclk_gpio11  : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_gpio12  : 1;  /* bit[12]:  */
        unsigned int  gt_pclk_gpio13  : 1;  /* bit[13]:  */
        unsigned int  gt_pclk_gpio14  : 1;  /* bit[14]:  */
        unsigned int  gt_pclk_gpio15  : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_gpio16  : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_gpio17  : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_gpio18  : 1;  /* bit[18]:  */
        unsigned int  gt_pclk_gpio19  : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_gpio20  : 1;  /* bit[20]:  */
        unsigned int  gt_pclk_gpio21  : 1;  /* bit[21]:  */
        unsigned int  gt_pclk_timer9  : 1;  /* bit[22]:  */
        unsigned int  gt_pclk_timer10 : 1;  /* bit[23]:  */
        unsigned int  gt_pclk_timer11 : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_timer12 : 1;  /* bit[25]:  */
        unsigned int  gt_clk_socp     : 1;  /* bit[26]: socp时钟最终状态：gt_clk_socp_lpm3\gt_clk_socp_acpu\gt_clk_socp_mcpu任何一个为1'b1则时钟开启；全部为0时时钟关闭。 */
        unsigned int  gt_clk_djtag    : 1;  /* bit[27]:  */
        unsigned int  reserved_0      : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_1      : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_2      : 1;  /* bit[30]:  */
        unsigned int  reserved_3      : 1;  /* bit[31]: 外设时钟最终状态：
                                                        0：IP时钟禁止状态；
                                                        1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERSTAT1_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio0_START    (0)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio0_END      (0)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio1_START    (1)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio1_END      (1)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio2_START    (2)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio2_END      (2)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio3_START    (3)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio3_END      (3)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio4_START    (4)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio4_END      (4)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio5_START    (5)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio5_END      (5)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio6_START    (6)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio6_END      (6)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio7_START    (7)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio7_END      (7)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio8_START    (8)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio8_END      (8)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio9_START    (9)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio9_END      (9)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio10_START   (10)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio10_END     (10)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio11_START   (11)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio11_END     (11)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio12_START   (12)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio12_END     (12)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio13_START   (13)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio13_END     (13)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio14_START   (14)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio14_END     (14)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio15_START   (15)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio15_END     (15)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio16_START   (16)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio16_END     (16)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio17_START   (17)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio17_END     (17)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio18_START   (18)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio18_END     (18)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio19_START   (19)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio19_END     (19)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio20_START   (20)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio20_END     (20)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio21_START   (21)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio21_END     (21)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer9_START   (22)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer9_END     (22)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer10_START  (23)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer10_END    (23)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer11_START  (24)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer11_END    (24)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer12_START  (25)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer12_END    (25)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_socp_START      (26)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_socp_END        (26)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_djtag_START     (27)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_djtag_END       (27)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PEREN2_UNION
 结构说明  : PEREN2 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_pwm         : 1;  /* bit[0] : 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
        unsigned int  reserved_0         : 1;  /* bit[1] : 保留。 */
        unsigned int  gt_clk_ipc0        : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ipc1        : 1;  /* bit[3] :  */
        unsigned int  reserved_1         : 1;  /* bit[4] : 保留。 */
        unsigned int  reserved_2         : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_3         : 1;  /* bit[6] : 保留。 */
        unsigned int  gt_clk_i2c3        : 1;  /* bit[7] :  */
        unsigned int  reserved_4         : 1;  /* bit[8] : 保留。 */
        unsigned int  gt_clk_spi1        : 1;  /* bit[9] :  */
        unsigned int  gt_clk_uart0       : 1;  /* bit[10]:  */
        unsigned int  gt_clk_uart1       : 1;  /* bit[11]:  */
        unsigned int  gt_clk_uart2       : 1;  /* bit[12]:  */
        unsigned int  reserved_5         : 1;  /* bit[13]: 保留。 */
        unsigned int  gt_clk_uart4       : 1;  /* bit[14]:  */
        unsigned int  gt_clk_uart5       : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_wd0        : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_wd1        : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_tzpc       : 1;  /* bit[18]:  */
        unsigned int  reserved_6         : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_ipc_mdm    : 1;  /* bit[20]:  */
        unsigned int  gt_clk_adb_mst_a53 : 1;  /* bit[21]:  */
        unsigned int  gt_clk_adb_mst_a57 : 1;  /* bit[22]:  */
        unsigned int  gt_clk_gic         : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hkadcssi    : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_ioc        : 1;  /* bit[25]:  */
        unsigned int  gt_clk_codecssi    : 1;  /* bit[26]:  */
        unsigned int  gt_clk_i2c4        : 1;  /* bit[27]:  */
        unsigned int  reserved_7         : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_8         : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_9         : 1;  /* bit[30]: 保留。 */
        unsigned int  gt_pclk_pctrl      : 1;  /* bit[31]: 外设时钟使能控制：
                                                           0：写0无效果；
                                                           1：使能IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PEREN2_UNION;
#endif
#define SOC_CRGPERIPH_PEREN2_gt_clk_pwm_START          (0)
#define SOC_CRGPERIPH_PEREN2_gt_clk_pwm_END            (0)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc0_START         (2)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc0_END           (2)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc1_START         (3)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc1_END           (3)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c3_START         (7)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c3_END           (7)
#define SOC_CRGPERIPH_PEREN2_gt_clk_spi1_START         (9)
#define SOC_CRGPERIPH_PEREN2_gt_clk_spi1_END           (9)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart0_START        (10)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart0_END          (10)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart1_START        (11)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart1_END          (11)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart2_START        (12)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart2_END          (12)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart4_START        (14)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart4_END          (14)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart5_START        (15)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart5_END          (15)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd0_START         (16)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd0_END           (16)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd1_START         (17)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd1_END           (17)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_tzpc_START        (18)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_tzpc_END          (18)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ipc_mdm_START     (20)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ipc_mdm_END       (20)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a53_START  (21)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a53_END    (21)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a57_START  (22)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a57_END    (22)
#define SOC_CRGPERIPH_PEREN2_gt_clk_gic_START          (23)
#define SOC_CRGPERIPH_PEREN2_gt_clk_gic_END            (23)
#define SOC_CRGPERIPH_PEREN2_gt_clk_hkadcssi_START     (24)
#define SOC_CRGPERIPH_PEREN2_gt_clk_hkadcssi_END       (24)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ioc_START         (25)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ioc_END           (25)
#define SOC_CRGPERIPH_PEREN2_gt_clk_codecssi_START     (26)
#define SOC_CRGPERIPH_PEREN2_gt_clk_codecssi_END       (26)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c4_START         (27)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c4_END           (27)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_pctrl_START       (31)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_pctrl_END         (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERDIS2_UNION
 结构说明  : PERDIS2 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_pwm         : 1;  /* bit[0] : 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
        unsigned int  reserved_0         : 1;  /* bit[1] : 保留。 */
        unsigned int  gt_clk_ipc0        : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ipc1        : 1;  /* bit[3] :  */
        unsigned int  reserved_1         : 1;  /* bit[4] : 保留。 */
        unsigned int  reserved_2         : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_3         : 1;  /* bit[6] : 保留。 */
        unsigned int  gt_clk_i2c3        : 1;  /* bit[7] :  */
        unsigned int  reserved_4         : 1;  /* bit[8] : 保留。 */
        unsigned int  gt_clk_spi1        : 1;  /* bit[9] :  */
        unsigned int  gt_clk_uart0       : 1;  /* bit[10]:  */
        unsigned int  gt_clk_uart1       : 1;  /* bit[11]:  */
        unsigned int  gt_clk_uart2       : 1;  /* bit[12]:  */
        unsigned int  reserved_5         : 1;  /* bit[13]: 保留。 */
        unsigned int  gt_clk_uart4       : 1;  /* bit[14]:  */
        unsigned int  gt_clk_uart5       : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_wd0        : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_wd1        : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_tzpc       : 1;  /* bit[18]:  */
        unsigned int  reserved_6         : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_ipc_mdm    : 1;  /* bit[20]:  */
        unsigned int  gt_clk_adb_mst_a53 : 1;  /* bit[21]:  */
        unsigned int  gt_clk_adb_mst_a57 : 1;  /* bit[22]:  */
        unsigned int  gt_clk_gic         : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hkadcssi    : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_ioc        : 1;  /* bit[25]:  */
        unsigned int  gt_clk_codecssi    : 1;  /* bit[26]:  */
        unsigned int  gt_clk_i2c4        : 1;  /* bit[27]:  */
        unsigned int  reserved_7         : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_8         : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_9         : 1;  /* bit[30]: 保留。 */
        unsigned int  gt_pclk_pctrl      : 1;  /* bit[31]: 外设时钟禁止控制：
                                                           0：写0无效果；
                                                           1：禁止IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PERDIS2_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS2_gt_clk_pwm_START          (0)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_pwm_END            (0)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc0_START         (2)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc0_END           (2)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc1_START         (3)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc1_END           (3)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c3_START         (7)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c3_END           (7)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_spi1_START         (9)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_spi1_END           (9)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart0_START        (10)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart0_END          (10)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart1_START        (11)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart1_END          (11)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart2_START        (12)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart2_END          (12)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart4_START        (14)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart4_END          (14)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart5_START        (15)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart5_END          (15)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd0_START         (16)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd0_END           (16)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd1_START         (17)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd1_END           (17)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_tzpc_START        (18)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_tzpc_END          (18)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ipc_mdm_START     (20)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ipc_mdm_END       (20)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a53_START  (21)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a53_END    (21)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a57_START  (22)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a57_END    (22)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_gic_START          (23)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_gic_END            (23)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_hkadcssi_START     (24)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_hkadcssi_END       (24)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ioc_START         (25)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ioc_END           (25)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_codecssi_START     (26)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_codecssi_END       (26)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c4_START         (27)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c4_END           (27)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_pctrl_START       (31)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_pctrl_END         (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCLKEN2_UNION
 结构说明  : PERCLKEN2 寄存器结构定义。地址偏移量:0x028，初值:0xFF9FFFFF，宽度:32
 寄存器说明: 外设时钟使能状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_pwm         : 1;  /* bit[0] : 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  reserved_0         : 1;  /* bit[1] : 保留。 */
        unsigned int  gt_clk_ipc0        : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ipc1        : 1;  /* bit[3] :  */
        unsigned int  reserved_1         : 1;  /* bit[4] : 保留。 */
        unsigned int  reserved_2         : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_3         : 1;  /* bit[6] : 保留。 */
        unsigned int  gt_clk_i2c3        : 1;  /* bit[7] :  */
        unsigned int  reserved_4         : 1;  /* bit[8] : 保留。 */
        unsigned int  gt_clk_spi1        : 1;  /* bit[9] :  */
        unsigned int  gt_clk_uart0       : 1;  /* bit[10]:  */
        unsigned int  gt_clk_uart1       : 1;  /* bit[11]:  */
        unsigned int  gt_clk_uart2       : 1;  /* bit[12]:  */
        unsigned int  reserved_5         : 1;  /* bit[13]: 保留。 */
        unsigned int  gt_clk_uart4       : 1;  /* bit[14]:  */
        unsigned int  gt_clk_uart5       : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_wd0        : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_wd1        : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_tzpc       : 1;  /* bit[18]:  */
        unsigned int  reserved_6         : 1;  /* bit[19]: 保留。 */
        unsigned int  gt_pclk_ipc_mdm    : 1;  /* bit[20]:  */
        unsigned int  gt_clk_adb_mst_a53 : 1;  /* bit[21]:  */
        unsigned int  gt_clk_adb_mst_a57 : 1;  /* bit[22]:  */
        unsigned int  gt_clk_gic         : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hkadcssi    : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_ioc        : 1;  /* bit[25]:  */
        unsigned int  gt_clk_codecssi    : 1;  /* bit[26]:  */
        unsigned int  gt_clk_i2c4        : 1;  /* bit[27]:  */
        unsigned int  reserved_7         : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_8         : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_9         : 1;  /* bit[30]: 保留。 */
        unsigned int  gt_pclk_pctrl      : 1;  /* bit[31]: 外设时钟使能状态：
                                                           0：IP时钟使能撤销状态；
                                                           1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERCLKEN2_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_pwm_START          (0)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_pwm_END            (0)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc0_START         (2)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc0_END           (2)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc1_START         (3)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc1_END           (3)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c3_START         (7)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c3_END           (7)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_spi1_START         (9)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_spi1_END           (9)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart0_START        (10)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart0_END          (10)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart1_START        (11)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart1_END          (11)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart2_START        (12)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart2_END          (12)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart4_START        (14)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart4_END          (14)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart5_START        (15)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart5_END          (15)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd0_START         (16)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd0_END           (16)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd1_START         (17)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd1_END           (17)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_tzpc_START        (18)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_tzpc_END          (18)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ipc_mdm_START     (20)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ipc_mdm_END       (20)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a53_START  (21)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a53_END    (21)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a57_START  (22)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a57_END    (22)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_gic_START          (23)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_gic_END            (23)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_hkadcssi_START     (24)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_hkadcssi_END       (24)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ioc_START         (25)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ioc_END           (25)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_codecssi_START     (26)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_codecssi_END       (26)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c4_START         (27)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c4_END           (27)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_pctrl_START       (31)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_pctrl_END         (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERSTAT2_UNION
 结构说明  : PERSTAT2 寄存器结构定义。地址偏移量:0x02C，初值:0xFF9FFFFF，宽度:32
 寄存器说明: 外设时钟最终状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_pwm         : 1;  /* bit[0] : 外设时钟最终状态：
                                                           0：IP时钟禁止状态；
                                                           1：IP时钟使能状态。 */
        unsigned int  reserved_0         : 1;  /* bit[1] : 保留。 */
        unsigned int  gt_clk_ipc0        : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ipc1        : 1;  /* bit[3] :  */
        unsigned int  reserved_1         : 1;  /* bit[4] : 保留。 */
        unsigned int  reserved_2         : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_3         : 1;  /* bit[6] : 保留。 */
        unsigned int  gt_clk_i2c3        : 1;  /* bit[7] :  */
        unsigned int  reserved_4         : 1;  /* bit[8] : 保留。 */
        unsigned int  gt_clk_spi1        : 1;  /* bit[9] :  */
        unsigned int  gt_clk_uart0       : 1;  /* bit[10]:  */
        unsigned int  gt_clk_uart1       : 1;  /* bit[11]:  */
        unsigned int  gt_clk_uart2       : 1;  /* bit[12]:  */
        unsigned int  reserved_5         : 1;  /* bit[13]: 保留。 */
        unsigned int  gt_clk_uart4       : 1;  /* bit[14]:  */
        unsigned int  gt_clk_uart5       : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_wd0        : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_wd1        : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_tzpc       : 1;  /* bit[18]:  */
        unsigned int  reserved_6         : 1;  /* bit[19]: 保留。 */
        unsigned int  gt_pclk_ipc_mdm    : 1;  /* bit[20]:  */
        unsigned int  gt_clk_adb_mst_a53 : 1;  /* bit[21]:  */
        unsigned int  gt_clk_adb_mst_a57 : 1;  /* bit[22]:  */
        unsigned int  gt_clk_gic         : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hkadcssi    : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_ioc        : 1;  /* bit[25]:  */
        unsigned int  gt_clk_codecssi    : 1;  /* bit[26]:  */
        unsigned int  gt_clk_i2c4        : 1;  /* bit[27]:  */
        unsigned int  reserved_7         : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_8         : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_9         : 1;  /* bit[30]: 保留。 */
        unsigned int  gt_pclk_pctrl      : 1;  /* bit[31]: 外设时钟最终状态：
                                                           0：IP时钟禁止状态；
                                                           1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERSTAT2_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_pwm_START          (0)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_pwm_END            (0)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc0_START         (2)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc0_END           (2)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc1_START         (3)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc1_END           (3)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c3_START         (7)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c3_END           (7)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_spi1_START         (9)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_spi1_END           (9)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart0_START        (10)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart0_END          (10)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart1_START        (11)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart1_END          (11)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart2_START        (12)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart2_END          (12)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart4_START        (14)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart4_END          (14)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart5_START        (15)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart5_END          (15)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd0_START         (16)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd0_END           (16)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd1_START         (17)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd1_END           (17)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_tzpc_START        (18)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_tzpc_END          (18)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ipc_mdm_START     (20)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ipc_mdm_END       (20)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a53_START  (21)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a53_END    (21)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a57_START  (22)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a57_END    (22)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_gic_START          (23)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_gic_END            (23)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_hkadcssi_START     (24)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_hkadcssi_END       (24)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ioc_START         (25)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ioc_END           (25)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_codecssi_START     (26)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_codecssi_END       (26)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c4_START         (27)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c4_END           (27)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_pctrl_START       (31)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_pctrl_END         (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PEREN3_UNION
 结构说明  : PEREN3 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_dmac_lpm3       : 1;  /* bit[0]  : 外设时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
        unsigned int  gt_clk_dmac_acpu       : 1;  /* bit[1]  :  */
        unsigned int  gt_clk_dmac_mcpu       : 1;  /* bit[2]  :  */
        unsigned int  gt_pclk_g3d            : 1;  /* bit[3]  :  */
        unsigned int  gt_clk_g3dmt           : 1;  /* bit[4]  :  */
        unsigned int  gt_clk_g3d             : 1;  /* bit[5]  :  */
        unsigned int  sc_abb_pll_gps_en      : 2;  /* bit[6-7]:  */
        unsigned int  sc_abb_pll_audio_en    : 2;  /* bit[8-9]:  */
        unsigned int  gt_clk_venc            : 1;  /* bit[10] :  */
        unsigned int  gt_clk_vdec            : 1;  /* bit[11] :  */
        unsigned int  gt_pclk_dss            : 1;  /* bit[12] :  */
        unsigned int  gt_aclk_dss            : 1;  /* bit[13] :  */
        unsigned int  gt_clk_ldi1            : 1;  /* bit[14] :  */
        unsigned int  gt_clk_ldi0            : 1;  /* bit[15] :  */
        unsigned int  reserved_0             : 1;  /* bit[16] : 保留。 */
        unsigned int  gt_clk_edc0            : 1;  /* bit[17] :  */
        unsigned int  sc_abb_pll_gps_gt_en   : 1;  /* bit[18] :  */
        unsigned int  sc_abb_pll_audio_gt_en : 1;  /* bit[19] :  */
        unsigned int  gt_clk_rxdphy0_cfg     : 1;  /* bit[20] :  */
        unsigned int  gt_clk_rxdphy1_cfg     : 1;  /* bit[21] :  */
        unsigned int  gt_clk_rxdphy2_cfg     : 1;  /* bit[22] :  */
        unsigned int  gt_aclk_isp            : 1;  /* bit[23] :  */
        unsigned int  gt_hclk_isp            : 1;  /* bit[24] :  */
        unsigned int  gt_clk_ispfunc         : 1;  /* bit[25] :  */
        unsigned int  reserved_1             : 1;  /* bit[26] :  */
        unsigned int  gt_clk_ispa7cfg        : 1;  /* bit[27] :  */
        unsigned int  gt_clk_txdphy0_cfg     : 1;  /* bit[28] :  */
        unsigned int  gt_clk_txdphy0_ref     : 1;  /* bit[29] :  */
        unsigned int  gt_clk_txdphy1_cfg     : 1;  /* bit[30] :  */
        unsigned int  gt_clk_txdphy1_ref     : 1;  /* bit[31] : 外设时钟使能控制：
                                                                0：写0无效果；
                                                                1：使能IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PEREN3_UNION;
#endif
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_lpm3_START        (0)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_lpm3_END          (0)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_acpu_START        (1)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_acpu_END          (1)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_mcpu_START        (2)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_mcpu_END          (2)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_g3d_START             (3)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_g3d_END               (3)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3dmt_START            (4)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3dmt_END              (4)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3d_START              (5)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3d_END                (5)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_en_START       (6)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_en_END         (7)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_en_START     (8)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_en_END       (9)
#define SOC_CRGPERIPH_PEREN3_gt_clk_venc_START             (10)
#define SOC_CRGPERIPH_PEREN3_gt_clk_venc_END               (10)
#define SOC_CRGPERIPH_PEREN3_gt_clk_vdec_START             (11)
#define SOC_CRGPERIPH_PEREN3_gt_clk_vdec_END               (11)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_dss_START             (12)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_dss_END               (12)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_dss_START             (13)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_dss_END               (13)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi1_START             (14)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi1_END               (14)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi0_START             (15)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi0_END               (15)
#define SOC_CRGPERIPH_PEREN3_gt_clk_edc0_START             (17)
#define SOC_CRGPERIPH_PEREN3_gt_clk_edc0_END               (17)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_gt_en_START    (18)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_gt_en_END      (18)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_gt_en_START  (19)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_gt_en_END    (19)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy0_cfg_START      (20)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy0_cfg_END        (20)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy1_cfg_START      (21)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy1_cfg_END        (21)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy2_cfg_START      (22)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy2_cfg_END        (22)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_isp_START             (23)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_isp_END               (23)
#define SOC_CRGPERIPH_PEREN3_gt_hclk_isp_START             (24)
#define SOC_CRGPERIPH_PEREN3_gt_hclk_isp_END               (24)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispfunc_START          (25)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispfunc_END            (25)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispa7cfg_START         (27)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispa7cfg_END           (27)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_cfg_START      (28)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_cfg_END        (28)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_ref_START      (29)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_ref_END        (29)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_cfg_START      (30)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_cfg_END        (30)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_ref_START      (31)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_ref_END        (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERDIS3_UNION
 结构说明  : PERDIS3 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_dmac_lpm3       : 1;  /* bit[0]  : 外设时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
        unsigned int  gt_clk_dmac_acpu       : 1;  /* bit[1]  :  */
        unsigned int  gt_clk_dmac_mcpu       : 1;  /* bit[2]  :  */
        unsigned int  gt_pclk_g3d            : 1;  /* bit[3]  :  */
        unsigned int  gt_clk_g3dmt           : 1;  /* bit[4]  :  */
        unsigned int  gt_clk_g3d             : 1;  /* bit[5]  :  */
        unsigned int  sc_abb_pll_gps_en      : 2;  /* bit[6-7]:  */
        unsigned int  sc_abb_pll_audio_en    : 2;  /* bit[8-9]: 保留。 */
        unsigned int  gt_clk_venc            : 1;  /* bit[10] :  */
        unsigned int  gt_clk_vdec            : 1;  /* bit[11] :  */
        unsigned int  gt_pclk_dss            : 1;  /* bit[12] :  */
        unsigned int  gt_aclk_dss            : 1;  /* bit[13] :  */
        unsigned int  gt_clk_ldi1            : 1;  /* bit[14] :  */
        unsigned int  gt_clk_ldi0            : 1;  /* bit[15] :  */
        unsigned int  reserved_0             : 1;  /* bit[16] : 保留。 */
        unsigned int  gt_clk_edc0            : 1;  /* bit[17] :  */
        unsigned int  sc_abb_pll_gps_gt_en   : 1;  /* bit[18] :  */
        unsigned int  sc_abb_pll_audio_gt_en : 1;  /* bit[19] :  */
        unsigned int  gt_clk_rxdphy0_cfg     : 1;  /* bit[20] :  */
        unsigned int  gt_clk_rxdphy1_cfg     : 1;  /* bit[21] :  */
        unsigned int  gt_clk_rxdphy2_cfg     : 1;  /* bit[22] :  */
        unsigned int  gt_aclk_isp            : 1;  /* bit[23] :  */
        unsigned int  gt_hclk_isp            : 1;  /* bit[24] :  */
        unsigned int  gt_clk_ispfunc         : 1;  /* bit[25] :  */
        unsigned int  reserved_1             : 1;  /* bit[26] :  */
        unsigned int  gt_clk_ispa7cfg        : 1;  /* bit[27] :  */
        unsigned int  gt_clk_txdphy0_cfg     : 1;  /* bit[28] :  */
        unsigned int  gt_clk_txdphy0_ref     : 1;  /* bit[29] :  */
        unsigned int  gt_clk_txdphy1_cfg     : 1;  /* bit[30] :  */
        unsigned int  gt_clk_txdphy1_ref     : 1;  /* bit[31] : 外设时钟禁止控制：
                                                                0：写0无效果；
                                                                1：禁止IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PERDIS3_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_lpm3_START        (0)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_lpm3_END          (0)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_acpu_START        (1)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_acpu_END          (1)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_mcpu_START        (2)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_mcpu_END          (2)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_g3d_START             (3)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_g3d_END               (3)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3dmt_START            (4)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3dmt_END              (4)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3d_START              (5)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3d_END                (5)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_en_START       (6)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_en_END         (7)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_en_START     (8)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_en_END       (9)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_venc_START             (10)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_venc_END               (10)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_vdec_START             (11)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_vdec_END               (11)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_dss_START             (12)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_dss_END               (12)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_dss_START             (13)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_dss_END               (13)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi1_START             (14)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi1_END               (14)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi0_START             (15)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi0_END               (15)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_edc0_START             (17)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_edc0_END               (17)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_gt_en_START    (18)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_gt_en_END      (18)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_gt_en_START  (19)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_gt_en_END    (19)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy0_cfg_START      (20)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy0_cfg_END        (20)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy1_cfg_START      (21)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy1_cfg_END        (21)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy2_cfg_START      (22)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy2_cfg_END        (22)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_isp_START             (23)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_isp_END               (23)
#define SOC_CRGPERIPH_PERDIS3_gt_hclk_isp_START             (24)
#define SOC_CRGPERIPH_PERDIS3_gt_hclk_isp_END               (24)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispfunc_START          (25)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispfunc_END            (25)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispa7cfg_START         (27)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispa7cfg_END           (27)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_cfg_START      (28)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_cfg_END        (28)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_ref_START      (29)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_ref_END        (29)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_cfg_START      (30)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_cfg_END        (30)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_ref_START      (31)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_ref_END        (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCLKEN3_UNION
 结构说明  : PERCLKEN3 寄存器结构定义。地址偏移量:0x038，初值:0x04010007，宽度:32
 寄存器说明: 外设时钟使能状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_dmac_lpm3       : 1;  /* bit[0]  : 外设时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
        unsigned int  gt_clk_dmac_acpu       : 1;  /* bit[1]  :  */
        unsigned int  gt_clk_dmac_mcpu       : 1;  /* bit[2]  :  */
        unsigned int  gt_pclk_g3d            : 1;  /* bit[3]  :  */
        unsigned int  gt_clk_g3dmt           : 1;  /* bit[4]  :  */
        unsigned int  gt_clk_g3d             : 1;  /* bit[5]  :  */
        unsigned int  sc_abb_pll_gps_en      : 2;  /* bit[6-7]:  */
        unsigned int  sc_abb_pll_audio_en    : 2;  /* bit[8-9]: 保留。 */
        unsigned int  gt_clk_venc            : 1;  /* bit[10] :  */
        unsigned int  gt_clk_vdec            : 1;  /* bit[11] :  */
        unsigned int  gt_pclk_dss            : 1;  /* bit[12] :  */
        unsigned int  gt_aclk_dss            : 1;  /* bit[13] :  */
        unsigned int  gt_clk_ldi1            : 1;  /* bit[14] :  */
        unsigned int  gt_clk_ldi0            : 1;  /* bit[15] :  */
        unsigned int  reserved_0             : 1;  /* bit[16] : 保留。 */
        unsigned int  gt_clk_edc0            : 1;  /* bit[17] :  */
        unsigned int  sc_abb_pll_gps_gt_en   : 1;  /* bit[18] :  */
        unsigned int  sc_abb_pll_audio_gt_en : 1;  /* bit[19] :  */
        unsigned int  gt_clk_rxdphy0_cfg     : 1;  /* bit[20] :  */
        unsigned int  gt_clk_rxdphy1_cfg     : 1;  /* bit[21] :  */
        unsigned int  gt_clk_rxdphy2_cfg     : 1;  /* bit[22] :  */
        unsigned int  gt_aclk_isp            : 1;  /* bit[23] :  */
        unsigned int  gt_hclk_isp            : 1;  /* bit[24] :  */
        unsigned int  gt_clk_ispfunc         : 1;  /* bit[25] :  */
        unsigned int  reserved_1             : 1;  /* bit[26] :  */
        unsigned int  gt_clk_ispa7cfg        : 1;  /* bit[27] :  */
        unsigned int  gt_clk_txdphy0_cfg     : 1;  /* bit[28] :  */
        unsigned int  gt_clk_txdphy0_ref     : 1;  /* bit[29] :  */
        unsigned int  gt_clk_txdphy1_cfg     : 1;  /* bit[30] :  */
        unsigned int  gt_clk_txdphy1_ref     : 1;  /* bit[31] : 外设时钟使能状态：
                                                                0：IP时钟使能撤销状态；
                                                                1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERCLKEN3_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_lpm3_START        (0)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_lpm3_END          (0)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_acpu_START        (1)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_acpu_END          (1)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_mcpu_START        (2)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_mcpu_END          (2)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_g3d_START             (3)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_g3d_END               (3)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3dmt_START            (4)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3dmt_END              (4)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3d_START              (5)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3d_END                (5)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_en_START       (6)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_en_END         (7)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_en_START     (8)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_en_END       (9)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_venc_START             (10)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_venc_END               (10)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_vdec_START             (11)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_vdec_END               (11)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_dss_START             (12)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_dss_END               (12)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_dss_START             (13)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_dss_END               (13)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi1_START             (14)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi1_END               (14)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi0_START             (15)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi0_END               (15)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_edc0_START             (17)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_edc0_END               (17)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_gt_en_START    (18)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_gt_en_END      (18)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_gt_en_START  (19)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_gt_en_END    (19)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy0_cfg_START      (20)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy0_cfg_END        (20)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy1_cfg_START      (21)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy1_cfg_END        (21)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy2_cfg_START      (22)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy2_cfg_END        (22)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_isp_START             (23)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_isp_END               (23)
#define SOC_CRGPERIPH_PERCLKEN3_gt_hclk_isp_START             (24)
#define SOC_CRGPERIPH_PERCLKEN3_gt_hclk_isp_END               (24)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispfunc_START          (25)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispfunc_END            (25)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispa7cfg_START         (27)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispa7cfg_END           (27)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_cfg_START      (28)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_cfg_END        (28)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_ref_START      (29)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_ref_END        (29)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_cfg_START      (30)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_cfg_END        (30)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_ref_START      (31)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_ref_END        (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERSTAT3_UNION
 结构说明  : PERSTAT3 寄存器结构定义。地址偏移量:0x03C，初值:0x040D03C7，宽度:32
 寄存器说明: 外设时钟最终状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_dmac0       : 1;  /* bit[0] : DMAC时钟状态动态变化 */
        unsigned int  gt_clk_dmac1       : 1;  /* bit[1] : DMAC时钟状态动态变化 */
        unsigned int  reserved_0         : 1;  /* bit[2] : 保留。 */
        unsigned int  gt_pclk_g3d        : 1;  /* bit[3] :  */
        unsigned int  gt_clk_g3dmt       : 1;  /* bit[4] :  */
        unsigned int  gt_clk_g3d         : 1;  /* bit[5] :  */
        unsigned int  reserved_1         : 1;  /* bit[6] : 保留。 */
        unsigned int  reserved_2         : 1;  /* bit[7] : 保留。 */
        unsigned int  reserved_3         : 1;  /* bit[8] : 保留。 */
        unsigned int  reserved_4         : 1;  /* bit[9] :  */
        unsigned int  gt_clk_venc        : 1;  /* bit[10]:  */
        unsigned int  gt_clk_vdec        : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_dss        : 1;  /* bit[12]:  */
        unsigned int  gt_aclk_dss        : 1;  /* bit[13]:  */
        unsigned int  gt_clk_ldi1        : 1;  /* bit[14]:  */
        unsigned int  gt_clk_ldi0        : 1;  /* bit[15]:  */
        unsigned int  reserved_5         : 1;  /* bit[16]: 保留。 */
        unsigned int  gt_clk_edc0        : 1;  /* bit[17]:  */
        unsigned int  reserved_6         : 1;  /* bit[18]: 保留。 */
        unsigned int  reserved_7         : 1;  /* bit[19]: 保留。 */
        unsigned int  gt_clk_rxdphy0_cfg : 1;  /* bit[20]:  */
        unsigned int  gt_clk_rxdphy1_cfg : 1;  /* bit[21]:  */
        unsigned int  gt_clk_rxdphy2_cfg : 1;  /* bit[22]:  */
        unsigned int  gt_aclk_isp        : 1;  /* bit[23]:  */
        unsigned int  gt_hclk_isp        : 1;  /* bit[24]:  */
        unsigned int  gt_clk_ispfunc     : 1;  /* bit[25]:  */
        unsigned int  reserved_8         : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ispa7cfg    : 1;  /* bit[27]:  */
        unsigned int  gt_clk_txdphy0_cfg : 1;  /* bit[28]:  */
        unsigned int  gt_clk_txdphy0_ref : 1;  /* bit[29]:  */
        unsigned int  gt_clk_txdphy1_cfg : 1;  /* bit[30]:  */
        unsigned int  gt_clk_txdphy1_ref : 1;  /* bit[31]: 外设时钟最终状态：
                                                           0：IP时钟禁止状态；
                                                           1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERSTAT3_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac0_START        (0)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac0_END          (0)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac1_START        (1)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac1_END          (1)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_g3d_START         (3)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_g3d_END           (3)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3dmt_START        (4)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3dmt_END          (4)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3d_START          (5)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3d_END            (5)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_venc_START         (10)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_venc_END           (10)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_vdec_START         (11)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_vdec_END           (11)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_dss_START         (12)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_dss_END           (12)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_dss_START         (13)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_dss_END           (13)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi1_START         (14)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi1_END           (14)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi0_START         (15)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi0_END           (15)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_edc0_START         (17)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_edc0_END           (17)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy0_cfg_START  (20)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy0_cfg_END    (20)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy1_cfg_START  (21)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy1_cfg_END    (21)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy2_cfg_START  (22)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy2_cfg_END    (22)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_isp_START         (23)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_isp_END           (23)
#define SOC_CRGPERIPH_PERSTAT3_gt_hclk_isp_START         (24)
#define SOC_CRGPERIPH_PERSTAT3_gt_hclk_isp_END           (24)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispfunc_START      (25)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispfunc_END        (25)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispa7cfg_START     (27)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispa7cfg_END       (27)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_cfg_START  (28)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_cfg_END    (28)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_ref_START  (29)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_ref_END    (29)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_cfg_START  (30)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_cfg_END    (30)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_ref_START  (31)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_ref_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PEREN4_UNION
 结构说明  : PEREN4 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_usb3otg_ref     : 1;  /* bit[0] : 外设时钟使能控制：
                                                               0：写0无效果；
                                                               1：使能IP时钟。 */
        unsigned int  gt_aclk_usb3otg        : 1;  /* bit[1] :  */
        unsigned int  gt_clk_usb3phy_ref     : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[3] :  */
        unsigned int  reserved_0             : 1;  /* bit[4] :  */
        unsigned int  gt_clk_ivp32dsp_sysbus : 1;  /* bit[5] :  */
        unsigned int  gt_clk_usb3phy_ref_pll : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ivp32dsp_tcxo   : 1;  /* bit[7] :  */
        unsigned int  gt_clk_perf_stat       : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_perf_stat      : 1;  /* bit[9] :  */
        unsigned int  gt_aclk_perf_stat      : 1;  /* bit[10]:  */
        unsigned int  reserved_1             : 1;  /* bit[11]: 保留。 */
        unsigned int  gt_clk_secp            : 1;  /* bit[12]:  */
        unsigned int  reserved_2             : 1;  /* bit[13]: 保留。 */
        unsigned int  gt_clk_emmc1_3p2m      : 1;  /* bit[14]:  */
        unsigned int  gt_clk_emmc0           : 1;  /* bit[15]:  */
        unsigned int  gt_clk_emmc1           : 1;  /* bit[16]:  */
        unsigned int  gt_clk_sd              : 1;  /* bit[17]:  */
        unsigned int  gt_clk_sdio0           : 1;  /* bit[18]:  */
        unsigned int  gt_clk_sdio1           : 1;  /* bit[19]:  */
        unsigned int  reserved_3             : 1;  /* bit[20]: 保留。 */
        unsigned int  gt_clk_a57_tsensor     : 1;  /* bit[21]:  */
        unsigned int  gt_clk_a53_tsensor     : 1;  /* bit[22]:  */
        unsigned int  gt_clk_apll0_sscg      : 1;  /* bit[23]:  */
        unsigned int  gt_clk_apll1_sscg      : 1;  /* bit[24]:  */
        unsigned int  gt_clk_apll2_sscg      : 1;  /* bit[25]:  */
        unsigned int  gt_clk_ppll1_sscg      : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ppll2_sscg      : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ppll3_sscg      : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ppll4_sscg      : 1;  /* bit[29]:  */
        unsigned int  gt_clk_ppll5_sscg      : 1;  /* bit[30]:  */
        unsigned int  gt_clk_a53_tp          : 1;  /* bit[31]: 外设时钟使能控制（maya_svdf 64分频测试时钟）：
                                                               0：写0无效果；
                                                               1：使能IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PEREN4_UNION;
#endif
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3otg_ref_START      (0)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3otg_ref_END        (0)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_usb3otg_START         (1)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_usb3otg_END           (1)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_START      (2)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_END        (2)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_core_START    (3)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_core_END      (3)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_sysbus_START  (5)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_sysbus_END    (5)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_pll_START  (6)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_pll_END    (6)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_tcxo_START    (7)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_tcxo_END      (7)
#define SOC_CRGPERIPH_PEREN4_gt_clk_perf_stat_START        (8)
#define SOC_CRGPERIPH_PEREN4_gt_clk_perf_stat_END          (8)
#define SOC_CRGPERIPH_PEREN4_gt_pclk_perf_stat_START       (9)
#define SOC_CRGPERIPH_PEREN4_gt_pclk_perf_stat_END         (9)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_perf_stat_START       (10)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_perf_stat_END         (10)
#define SOC_CRGPERIPH_PEREN4_gt_clk_secp_START             (12)
#define SOC_CRGPERIPH_PEREN4_gt_clk_secp_END               (12)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_3p2m_START       (14)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_3p2m_END         (14)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc0_START            (15)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc0_END              (15)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_START            (16)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_END              (16)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sd_START               (17)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sd_END                 (17)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio0_START            (18)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio0_END              (18)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio1_START            (19)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio1_END              (19)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a57_tsensor_START      (21)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a57_tsensor_END        (21)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tsensor_START      (22)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tsensor_END        (22)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll0_sscg_START       (23)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll0_sscg_END         (23)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll1_sscg_START       (24)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll1_sscg_END         (24)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll2_sscg_START       (25)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll2_sscg_END         (25)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll1_sscg_START       (26)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll1_sscg_END         (26)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll2_sscg_START       (27)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll2_sscg_END         (27)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll3_sscg_START       (28)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll3_sscg_END         (28)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll4_sscg_START       (29)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll4_sscg_END         (29)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll5_sscg_START       (30)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll5_sscg_END         (30)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tp_START           (31)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tp_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERDIS4_UNION
 结构说明  : PERDIS4 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_usb3otg_ref     : 1;  /* bit[0] : 外设时钟禁止控制：
                                                               0：写0无效果；
                                                               1：禁止IP时钟。 */
        unsigned int  gt_aclk_usb3otg        : 1;  /* bit[1] :  */
        unsigned int  gt_clk_usb3phy_ref     : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[3] :  */
        unsigned int  reserved_0             : 1;  /* bit[4] :  */
        unsigned int  gt_clk_ivp32dsp_sysbus : 1;  /* bit[5] :  */
        unsigned int  gt_clk_usb3phy_ref_pll : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ivp32dsp_tcxo   : 1;  /* bit[7] :  */
        unsigned int  gt_clk_perf_stat       : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_perf_stat      : 1;  /* bit[9] :  */
        unsigned int  gt_aclk_perf_stat      : 1;  /* bit[10]:  */
        unsigned int  reserved_1             : 1;  /* bit[11]: 保留。 */
        unsigned int  gt_clk_secp            : 1;  /* bit[12]:  */
        unsigned int  reserved_2             : 1;  /* bit[13]: 保留。 */
        unsigned int  gt_clk_emmc1_3p2m      : 1;  /* bit[14]:  */
        unsigned int  gt_clk_emmc0           : 1;  /* bit[15]:  */
        unsigned int  gt_clk_emmc1           : 1;  /* bit[16]:  */
        unsigned int  gt_clk_sd              : 1;  /* bit[17]:  */
        unsigned int  gt_clk_sdio0           : 1;  /* bit[18]:  */
        unsigned int  gt_clk_sdio1           : 1;  /* bit[19]: 保留。 */
        unsigned int  reserved_3             : 1;  /* bit[20]: 保留。 */
        unsigned int  gt_clk_a57_tsensor     : 1;  /* bit[21]:  */
        unsigned int  gt_clk_a53_tsensor     : 1;  /* bit[22]:  */
        unsigned int  gt_clk_apll0_sscg      : 1;  /* bit[23]:  */
        unsigned int  gt_clk_apll1_sscg      : 1;  /* bit[24]:  */
        unsigned int  gt_clk_apll2_sscg      : 1;  /* bit[25]:  */
        unsigned int  gt_clk_ppll1_sscg      : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ppll2_sscg      : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ppll3_sscg      : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ppll4_sscg      : 1;  /* bit[29]:  */
        unsigned int  gt_clk_ppll5_sscg      : 1;  /* bit[30]:  */
        unsigned int  gt_clk_a53_tp          : 1;  /* bit[31]: 外设时钟禁止控制（maya_svdf 64分频测试时钟）：
                                                               0：写0无效果；
                                                               1：禁止IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PERDIS4_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3otg_ref_START      (0)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3otg_ref_END        (0)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_usb3otg_START         (1)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_usb3otg_END           (1)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_START      (2)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_END        (2)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_core_START    (3)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_core_END      (3)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_sysbus_START  (5)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_sysbus_END    (5)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_pll_START  (6)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_pll_END    (6)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_tcxo_START    (7)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_tcxo_END      (7)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_perf_stat_START        (8)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_perf_stat_END          (8)
#define SOC_CRGPERIPH_PERDIS4_gt_pclk_perf_stat_START       (9)
#define SOC_CRGPERIPH_PERDIS4_gt_pclk_perf_stat_END         (9)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_perf_stat_START       (10)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_perf_stat_END         (10)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_secp_START             (12)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_secp_END               (12)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_3p2m_START       (14)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_3p2m_END         (14)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc0_START            (15)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc0_END              (15)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_START            (16)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_END              (16)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sd_START               (17)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sd_END                 (17)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio0_START            (18)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio0_END              (18)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio1_START            (19)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio1_END              (19)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a57_tsensor_START      (21)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a57_tsensor_END        (21)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tsensor_START      (22)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tsensor_END        (22)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll0_sscg_START       (23)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll0_sscg_END         (23)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll1_sscg_START       (24)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll1_sscg_END         (24)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll2_sscg_START       (25)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll2_sscg_END         (25)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll1_sscg_START       (26)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll1_sscg_END         (26)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll2_sscg_START       (27)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll2_sscg_END         (27)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll3_sscg_START       (28)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll3_sscg_END         (28)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll4_sscg_START       (29)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll4_sscg_END         (29)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll5_sscg_START       (30)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll5_sscg_END         (30)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tp_START           (31)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tp_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCLKEN4_UNION
 结构说明  : PERCLKEN4 寄存器结构定义。地址偏移量:0x048，初值:0x7FF078D7，宽度:32
 寄存器说明: 外设时钟使能状态寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_usb3otg_ref     : 1;  /* bit[0] : 外设时钟使能状态：
                                                               0：IP时钟使能撤销状态；
                                                               1：IP时钟使能状态。 */
        unsigned int  gt_aclk_usb3otg        : 1;  /* bit[1] :  */
        unsigned int  gt_clk_usb3phy_ref     : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[3] :  */
        unsigned int  reserved_0             : 1;  /* bit[4] : 保留。 */
        unsigned int  gt_clk_ivp32dsp_sysbus : 1;  /* bit[5] :  */
        unsigned int  gt_clk_usb3phy_ref_pll : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ivp32dsp_tcxo   : 1;  /* bit[7] :  */
        unsigned int  gt_clk_perf_stat       : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_perf_stat      : 1;  /* bit[9] :  */
        unsigned int  gt_aclk_perf_stat      : 1;  /* bit[10]:  */
        unsigned int  reserved_1             : 1;  /* bit[11]: 保留。 */
        unsigned int  gt_clk_secp            : 1;  /* bit[12]:  */
        unsigned int  reserved_2             : 1;  /* bit[13]: 保留。 */
        unsigned int  gt_clk_emmc1_3p2m      : 1;  /* bit[14]:  */
        unsigned int  gt_clk_emmc0           : 1;  /* bit[15]:  */
        unsigned int  gt_clk_emmc1           : 1;  /* bit[16]:  */
        unsigned int  gt_clk_sd              : 1;  /* bit[17]:  */
        unsigned int  gt_clk_sdio0           : 1;  /* bit[18]:  */
        unsigned int  gt_clk_sdio1           : 1;  /* bit[19]:  */
        unsigned int  reserved_3             : 1;  /* bit[20]: 保留。 */
        unsigned int  gt_clk_a57_tsensor     : 1;  /* bit[21]:  */
        unsigned int  gt_clk_a53_tsensor     : 1;  /* bit[22]:  */
        unsigned int  gt_clk_apll0_sscg      : 1;  /* bit[23]:  */
        unsigned int  gt_clk_apll1_sscg      : 1;  /* bit[24]:  */
        unsigned int  gt_clk_apll2_sscg      : 1;  /* bit[25]:  */
        unsigned int  gt_clk_ppll1_sscg      : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ppll2_sscg      : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ppll3_sscg      : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ppll4_sscg      : 1;  /* bit[29]:  */
        unsigned int  gt_clk_ppll5_sscg      : 1;  /* bit[30]:  */
        unsigned int  gt_clk_a53_tp          : 1;  /* bit[31]: 外设时钟使能状态（maya_svdf 64分频测试时钟）：
                                                               0：IP时钟使能撤销状态；
                                                               1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERCLKEN4_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3otg_ref_START      (0)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3otg_ref_END        (0)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_usb3otg_START         (1)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_usb3otg_END           (1)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_START      (2)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_END        (2)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_core_START    (3)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_core_END      (3)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_sysbus_START  (5)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_sysbus_END    (5)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_pll_START  (6)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_pll_END    (6)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_tcxo_START    (7)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_tcxo_END      (7)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_perf_stat_START        (8)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_perf_stat_END          (8)
#define SOC_CRGPERIPH_PERCLKEN4_gt_pclk_perf_stat_START       (9)
#define SOC_CRGPERIPH_PERCLKEN4_gt_pclk_perf_stat_END         (9)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_perf_stat_START       (10)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_perf_stat_END         (10)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_secp_START             (12)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_secp_END               (12)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_3p2m_START       (14)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_3p2m_END         (14)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc0_START            (15)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc0_END              (15)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_START            (16)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_END              (16)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sd_START               (17)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sd_END                 (17)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio0_START            (18)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio0_END              (18)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio1_START            (19)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio1_END              (19)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a57_tsensor_START      (21)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a57_tsensor_END        (21)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tsensor_START      (22)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tsensor_END        (22)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll0_sscg_START       (23)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll0_sscg_END         (23)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll1_sscg_START       (24)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll1_sscg_END         (24)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll2_sscg_START       (25)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll2_sscg_END         (25)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll1_sscg_START       (26)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll1_sscg_END         (26)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll2_sscg_START       (27)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll2_sscg_END         (27)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll3_sscg_START       (28)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll3_sscg_END         (28)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll4_sscg_START       (29)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll4_sscg_END         (29)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll5_sscg_START       (30)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll5_sscg_END         (30)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tp_START           (31)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tp_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERSTAT4_UNION
 结构说明  : PERSTAT4 寄存器结构定义。地址偏移量:0x04C，初值:0x7FF078D7，宽度:32
 寄存器说明: 外设时钟最终状态寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_usb3otg_ref     : 1;  /* bit[0] : 外设时钟最终状态：
                                                               0：IP时钟禁止状态；
                                                               1：IP时钟使能状态。 */
        unsigned int  gt_aclk_usb3otg        : 1;  /* bit[1] :  */
        unsigned int  gt_clk_usb3phy_ref     : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[3] :  */
        unsigned int  reserved_0             : 1;  /* bit[4] : 保留。 */
        unsigned int  gt_clk_ivp32dsp_sysbus : 1;  /* bit[5] :  */
        unsigned int  gt_clk_usb3phy_ref_pll : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ivp32dsp_tcxo   : 1;  /* bit[7] :  */
        unsigned int  gt_clk_perf_stat       : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_perf_stat      : 1;  /* bit[9] :  */
        unsigned int  gt_aclk_perf_stat      : 1;  /* bit[10]:  */
        unsigned int  gt_clk_secs            : 1;  /* bit[11]:  */
        unsigned int  gt_clk_secp            : 1;  /* bit[12]:  */
        unsigned int  reserved_1             : 1;  /* bit[13]: 保留。 */
        unsigned int  gt_clk_emmc1_3p2m      : 1;  /* bit[14]:  */
        unsigned int  gt_clk_emmc0           : 1;  /* bit[15]:  */
        unsigned int  gt_clk_emmc1           : 1;  /* bit[16]:  */
        unsigned int  gt_clk_sd              : 1;  /* bit[17]:  */
        unsigned int  gt_clk_sdio0           : 1;  /* bit[18]:  */
        unsigned int  gt_clk_sdio1           : 1;  /* bit[19]:  */
        unsigned int  reserved_2             : 1;  /* bit[20]: 保留。 */
        unsigned int  gt_clk_a57_tsensor     : 1;  /* bit[21]:  */
        unsigned int  gt_clk_a53_tsensor     : 1;  /* bit[22]:  */
        unsigned int  gt_clk_apll0_sscg      : 1;  /* bit[23]:  */
        unsigned int  gt_clk_apll1_sscg      : 1;  /* bit[24]:  */
        unsigned int  gt_clk_apll2_sscg      : 1;  /* bit[25]:  */
        unsigned int  gt_clk_ppll1_sscg      : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ppll2_sscg      : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ppll3_sscg      : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ppll4_sscg      : 1;  /* bit[29]:  */
        unsigned int  gt_clk_ppll5_sscg      : 1;  /* bit[30]:  */
        unsigned int  gt_clk_a53_tp          : 1;  /* bit[31]: 外设时钟最终状态（maya_svdf 64分频测试时钟）：
                                                               0：IP时钟禁止状态；
                                                               1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERSTAT4_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3otg_ref_START      (0)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3otg_ref_END        (0)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_usb3otg_START         (1)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_usb3otg_END           (1)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_START      (2)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_END        (2)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_core_START    (3)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_core_END      (3)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_sysbus_START  (5)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_sysbus_END    (5)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_pll_START  (6)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_pll_END    (6)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_tcxo_START    (7)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_tcxo_END      (7)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_perf_stat_START        (8)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_perf_stat_END          (8)
#define SOC_CRGPERIPH_PERSTAT4_gt_pclk_perf_stat_START       (9)
#define SOC_CRGPERIPH_PERSTAT4_gt_pclk_perf_stat_END         (9)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_perf_stat_START       (10)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_perf_stat_END         (10)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secs_START             (11)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secs_END               (11)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secp_START             (12)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secp_END               (12)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_3p2m_START       (14)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_3p2m_END         (14)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc0_START            (15)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc0_END              (15)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_START            (16)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_END              (16)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sd_START               (17)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sd_END                 (17)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio0_START            (18)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio0_END              (18)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio1_START            (19)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio1_END              (19)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a57_tsensor_START      (21)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a57_tsensor_END        (21)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tsensor_START      (22)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tsensor_END        (22)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll0_sscg_START       (23)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll0_sscg_END         (23)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll1_sscg_START       (24)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll1_sscg_END         (24)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll2_sscg_START       (25)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll2_sscg_END         (25)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll1_sscg_START       (26)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll1_sscg_END         (26)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll2_sscg_START       (27)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll2_sscg_END         (27)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll3_sscg_START       (28)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll3_sscg_END         (28)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll4_sscg_START       (29)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll4_sscg_END         (29)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll5_sscg_START       (30)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll5_sscg_END         (30)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tp_START           (31)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tp_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PEREN5_UNION
 结构说明  : PEREN5 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_sysbus2hkmem       : 1;  /* bit[0]    : 外设时钟使能控制：
                                                                     0：写0无效果；
                                                                     1：使能IP时钟。 */
        unsigned int  gt_clk_modem_sys          : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_modem_subsys       : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_noc_timeout_extref : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7              : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_g3d_tsensor        : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_tsensor      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_slimbus            : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_lpmcu              : 1;  /* bit[8]    : LPM3子系统时钟使能控制：
                                                                     0：写0无效果；
                                                                     1：使能IP时钟。 */
        unsigned int  gt_clk_a57_hpm            : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_cci2sysbus_asyn    : 1;  /* bit[10]   : CCI2SYSBUS异步桥的门控控制。 */
        unsigned int  gt_clk_ao_hpm             : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_peri_hpm           : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_a53_hpm            : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_cci400             : 1;  /* bit[14]   :  */
        unsigned int  gt_clk_gpu_hpm            : 1;  /* bit[15]   :  */
        unsigned int  gt_clk_isp_snclk          : 3;  /* bit[16-18]:  */
        unsigned int  reserved_0                : 1;  /* bit[19]   : 保留。 */
        unsigned int  reserved_1                : 1;  /* bit[20]   : 保留。 */
        unsigned int  reserved_2                : 1;  /* bit[21]   : 保留。 */
        unsigned int  reserved_3                : 1;  /* bit[22]   : 保留。 */
        unsigned int  gt_clk_modem_mcpu_tp      : 1;  /* bit[23]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_c   : 1;  /* bit[24]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_d   : 1;  /* bit[25]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_b   : 1;  /* bit[26]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_a   : 1;  /* bit[27]   :  */
        unsigned int  gt_pclk_dsi0              : 1;  /* bit[28]   :  */
        unsigned int  gt_pclk_dsi1              : 1;  /* bit[29]   : 1：使能IP时钟。 */
        unsigned int  gt_clk_lpmcu_tp           : 1;  /* bit[30]   : 0：写0无效果； */
        unsigned int  gt_clk_sysbus_tp          : 1;  /* bit[31]   : 外设时钟使能控制：
                                                                     0：写0无效果；
                                                                     1：使能IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PEREN5_UNION;
#endif
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus2hkmem_START        (0)
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus2hkmem_END          (0)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_sys_START           (1)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_sys_END             (1)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_subsys_START        (2)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_subsys_END          (2)
#define SOC_CRGPERIPH_PEREN5_gt_clk_noc_timeout_extref_START  (3)
#define SOC_CRGPERIPH_PEREN5_gt_clk_noc_timeout_extref_END    (3)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ispa7_START               (4)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ispa7_END                 (4)
#define SOC_CRGPERIPH_PEREN5_gt_clk_g3d_tsensor_START         (5)
#define SOC_CRGPERIPH_PEREN5_gt_clk_g3d_tsensor_END           (5)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_tsensor_START       (6)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_tsensor_END         (6)
#define SOC_CRGPERIPH_PEREN5_gt_clk_slimbus_START             (7)
#define SOC_CRGPERIPH_PEREN5_gt_clk_slimbus_END               (7)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_START               (8)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_END                 (8)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a57_hpm_START             (9)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a57_hpm_END               (9)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci2sysbus_asyn_START     (10)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci2sysbus_asyn_END       (10)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ao_hpm_START              (11)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ao_hpm_END                (11)
#define SOC_CRGPERIPH_PEREN5_gt_clk_peri_hpm_START            (12)
#define SOC_CRGPERIPH_PEREN5_gt_clk_peri_hpm_END              (12)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a53_hpm_START             (13)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a53_hpm_END               (13)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci400_START              (14)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci400_END                (14)
#define SOC_CRGPERIPH_PEREN5_gt_clk_gpu_hpm_START             (15)
#define SOC_CRGPERIPH_PEREN5_gt_clk_gpu_hpm_END               (15)
#define SOC_CRGPERIPH_PEREN5_gt_clk_isp_snclk_START           (16)
#define SOC_CRGPERIPH_PEREN5_gt_clk_isp_snclk_END             (18)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_mcpu_tp_START       (23)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_mcpu_tp_END         (23)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_c_START    (24)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_c_END      (24)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_d_START    (25)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_d_END      (25)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_b_START    (26)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_b_END      (26)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_a_START    (27)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_a_END      (27)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi0_START               (28)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi0_END                 (28)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi1_START               (29)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi1_END                 (29)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_tp_START            (30)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_tp_END              (30)
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus_tp_START           (31)
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus_tp_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERDIS5_UNION
 结构说明  : PERDIS5 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_sysbus2hkmem       : 1;  /* bit[0]    : 外设时钟禁止控制：
                                                                     0：写0无效果；
                                                                     1：禁止IP时钟。 */
        unsigned int  gt_clk_modem_sys          : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_modem_subsys       : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_noc_timeout_extref : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7              : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_g3d_tsensor        : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_tsensor      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_slimbus            : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_lpmcu              : 1;  /* bit[8]    : LPM3子系统时钟使能控制：
                                                                     0：写0无效果；
                                                                     1：使能IP时钟。 */
        unsigned int  gt_clk_a57_hpm            : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_cci2sysbus_asyn    : 1;  /* bit[10]   : CCI2SYSBUS异步桥的门控控制。 */
        unsigned int  gt_clk_ao_hpm             : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_peri_hpm           : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_a53_hpm            : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_cci400             : 1;  /* bit[14]   :  */
        unsigned int  gt_clk_gpu_hpm            : 1;  /* bit[15]   :  */
        unsigned int  gt_clk_isp_snclk          : 3;  /* bit[16-18]:  */
        unsigned int  reserved_0                : 1;  /* bit[19]   : 保留。 */
        unsigned int  reserved_1                : 1;  /* bit[20]   : 保留。 */
        unsigned int  reserved_2                : 1;  /* bit[21]   : 保留。 */
        unsigned int  reserved_3                : 1;  /* bit[22]   : 保留。 */
        unsigned int  gt_clk_modem_mcpu_tp      : 1;  /* bit[23]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_c   : 1;  /* bit[24]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_d   : 1;  /* bit[25]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_b   : 1;  /* bit[26]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_a   : 1;  /* bit[27]   :  */
        unsigned int  gt_pclk_dsi0              : 1;  /* bit[28]   :  */
        unsigned int  gt_pclk_dsi1              : 1;  /* bit[29]   :  */
        unsigned int  gt_clk_lpmcu_tp           : 1;  /* bit[30]   :  */
        unsigned int  gt_clk_sysbus_tp          : 1;  /* bit[31]   : 外设时钟禁止控制：
                                                                     0：写0无效果；
                                                                     1：禁止IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PERDIS5_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus2hkmem_START        (0)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus2hkmem_END          (0)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_sys_START           (1)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_sys_END             (1)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_subsys_START        (2)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_subsys_END          (2)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_noc_timeout_extref_START  (3)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_noc_timeout_extref_END    (3)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ispa7_START               (4)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ispa7_END                 (4)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_g3d_tsensor_START         (5)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_g3d_tsensor_END           (5)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_tsensor_START       (6)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_tsensor_END         (6)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_slimbus_START             (7)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_slimbus_END               (7)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_START               (8)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_END                 (8)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a57_hpm_START             (9)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a57_hpm_END               (9)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci2sysbus_asyn_START     (10)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci2sysbus_asyn_END       (10)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ao_hpm_START              (11)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ao_hpm_END                (11)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_peri_hpm_START            (12)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_peri_hpm_END              (12)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a53_hpm_START             (13)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a53_hpm_END               (13)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci400_START              (14)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci400_END                (14)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_gpu_hpm_START             (15)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_gpu_hpm_END               (15)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_isp_snclk_START           (16)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_isp_snclk_END             (18)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_mcpu_tp_START       (23)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_mcpu_tp_END         (23)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_c_START    (24)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_c_END      (24)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_d_START    (25)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_d_END      (25)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_b_START    (26)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_b_END      (26)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_a_START    (27)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_a_END      (27)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi0_START               (28)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi0_END                 (28)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi1_START               (29)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi1_END                 (29)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_tp_START            (30)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_tp_END              (30)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus_tp_START           (31)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus_tp_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCLKEN5_UNION
 结构说明  : PERCLKEN5 寄存器结构定义。地址偏移量:0x058，初值:0xFF78BB6B，宽度:32
 寄存器说明: 外设时钟使能状态寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_sysbus2hkmem       : 1;  /* bit[0]    : 外设时钟使能状态：
                                                                     0：IP时钟使能撤销状态；
                                                                     1：IP时钟使能状态。 */
        unsigned int  gt_clk_modem_sys          : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_modem_subsys       : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_noc_timeout_extref : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7              : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_g3d_tsensor        : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_tsensor      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_slimbus            : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_lpmcu              : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_a57_hpm            : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_cci2sysbus_asyn    : 1;  /* bit[10]   : CCI2SYSBUS异步桥的门控控制。 */
        unsigned int  gt_clk_ao_hpm             : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_peri_hpm           : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_a53_hpm            : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_cci400             : 1;  /* bit[14]   :  */
        unsigned int  gt_clk_gpu_hpm            : 1;  /* bit[15]   :  */
        unsigned int  gt_clk_isp_snclk          : 3;  /* bit[16-18]:  */
        unsigned int  reserved_0                : 1;  /* bit[19]   : 保留。 */
        unsigned int  reserved_1                : 1;  /* bit[20]   : 保留。 */
        unsigned int  reserved_2                : 1;  /* bit[21]   : 保留。 */
        unsigned int  reserved_3                : 1;  /* bit[22]   : 保留。 */
        unsigned int  gt_clk_modem_mcpu_tp      : 1;  /* bit[23]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_c   : 1;  /* bit[24]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_d   : 1;  /* bit[25]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_b   : 1;  /* bit[26]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_a   : 1;  /* bit[27]   :  */
        unsigned int  gt_pclk_dsi0              : 1;  /* bit[28]   :  */
        unsigned int  gt_pclk_dsi1              : 1;  /* bit[29]   :  */
        unsigned int  gt_clk_lpmcu_tp           : 1;  /* bit[30]   :  */
        unsigned int  gt_clk_sysbus_tp          : 1;  /* bit[31]   : 外设时钟使能状态（SYSBUS测试时钟）：
                                                                     0：IP时钟使能撤销状态；
                                                                     1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERCLKEN5_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus2hkmem_START        (0)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus2hkmem_END          (0)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_sys_START           (1)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_sys_END             (1)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_subsys_START        (2)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_subsys_END          (2)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_noc_timeout_extref_START  (3)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_noc_timeout_extref_END    (3)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ispa7_START               (4)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ispa7_END                 (4)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_g3d_tsensor_START         (5)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_g3d_tsensor_END           (5)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_tsensor_START       (6)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_tsensor_END         (6)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_slimbus_START             (7)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_slimbus_END               (7)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_START               (8)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_END                 (8)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a57_hpm_START             (9)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a57_hpm_END               (9)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci2sysbus_asyn_START     (10)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci2sysbus_asyn_END       (10)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ao_hpm_START              (11)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ao_hpm_END                (11)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_peri_hpm_START            (12)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_peri_hpm_END              (12)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a53_hpm_START             (13)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a53_hpm_END               (13)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci400_START              (14)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci400_END                (14)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_gpu_hpm_START             (15)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_gpu_hpm_END               (15)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_isp_snclk_START           (16)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_isp_snclk_END             (18)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_mcpu_tp_START       (23)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_mcpu_tp_END         (23)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_c_START    (24)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_c_END      (24)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_d_START    (25)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_d_END      (25)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_b_START    (26)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_b_END      (26)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_a_START    (27)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_a_END      (27)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi0_START               (28)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi0_END                 (28)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi1_START               (29)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi1_END                 (29)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_tp_START            (30)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_tp_END              (30)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus_tp_START           (31)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus_tp_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERSTAT5_UNION
 结构说明  : PERSTAT5 寄存器结构定义。地址偏移量:0x05C，初值:0x3FF8BB6B，宽度:32
 寄存器说明: 外设时钟最终状态寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_sysbus2hkmem       : 1;  /* bit[0]    : 外设时钟最终状态（modem hkmem时钟）：
                                                                     0：IP时钟禁止状态；
                                                                     1：IP时钟使能状态。 */
        unsigned int  gt_clk_modem_sys          : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_modem_subsys       : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_noc_timeout_extref : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7              : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_g3d_tsensor        : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_tsensor      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_slimbus            : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_lpmcu              : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_a57_hpm            : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_cci2sysbus_asyn    : 1;  /* bit[10]   : CCI2SYSBUS异步桥的时钟最终状态。 */
        unsigned int  gt_clk_ao_hpm             : 1;  /* bit[11]   : 同上 */
        unsigned int  gt_clk_peri_hpm           : 1;  /* bit[12]   : 同上 */
        unsigned int  gt_clk_a53_hpm            : 1;  /* bit[13]   : 同上 */
        unsigned int  gt_clk_cci400             : 1;  /* bit[14]   : 同上 */
        unsigned int  gt_clk_gpu_hpm            : 1;  /* bit[15]   : 同上 */
        unsigned int  gt_clk_isp_snclk          : 3;  /* bit[16-18]: clk_isp_snclk_0/1/2 时钟最终状态。 */
        unsigned int  reserved_0                : 1;  /* bit[19]   : 保留。 */
        unsigned int  reserved_1                : 1;  /* bit[20]   : 保留。 */
        unsigned int  reserved_2                : 1;  /* bit[21]   : 保留。 */
        unsigned int  reserved_3                : 1;  /* bit[22]   : 保留。 */
        unsigned int  reserved_4                : 1;  /* bit[23]   : 保留。 */
        unsigned int  gt_clk_ddrphy_apb_dfi_c   : 1;  /* bit[24]   : 同上 */
        unsigned int  gt_clk_ddrphy_apb_dfi_d   : 1;  /* bit[25]   : 同上 */
        unsigned int  gt_clk_ddrphy_apb_dfi_b   : 1;  /* bit[26]   : 同上 */
        unsigned int  gt_clk_ddrphy_apb_dfi_a   : 1;  /* bit[27]   : 同上 */
        unsigned int  gt_pclk_dsi0              : 1;  /* bit[28]   : 同上 */
        unsigned int  gt_pclk_dsi1              : 1;  /* bit[29]   : 同上 */
        unsigned int  gt_clk_ace0_mst_g3d       : 1;  /* bit[30]   : 同上 */
        unsigned int  gt_clk_ace1_mst_g3d       : 1;  /* bit[31]   : 外设时钟最终状态（G3D ACE1时钟）：
                                                                     0：IP时钟禁止状态；
                                                                     1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERSTAT5_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_sysbus2hkmem_START        (0)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_sysbus2hkmem_END          (0)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_sys_START           (1)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_sys_END             (1)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_subsys_START        (2)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_subsys_END          (2)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_noc_timeout_extref_START  (3)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_noc_timeout_extref_END    (3)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ispa7_START               (4)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ispa7_END                 (4)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_g3d_tsensor_START         (5)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_g3d_tsensor_END           (5)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_tsensor_START       (6)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_tsensor_END         (6)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_slimbus_START             (7)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_slimbus_END               (7)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_lpmcu_START               (8)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_lpmcu_END                 (8)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a57_hpm_START             (9)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a57_hpm_END               (9)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci2sysbus_asyn_START     (10)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci2sysbus_asyn_END       (10)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ao_hpm_START              (11)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ao_hpm_END                (11)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_peri_hpm_START            (12)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_peri_hpm_END              (12)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a53_hpm_START             (13)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a53_hpm_END               (13)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci400_START              (14)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci400_END                (14)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_gpu_hpm_START             (15)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_gpu_hpm_END               (15)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_isp_snclk_START           (16)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_isp_snclk_END             (18)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_c_START    (24)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_c_END      (24)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_d_START    (25)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_d_END      (25)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_b_START    (26)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_b_END      (26)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_a_START    (27)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_a_END      (27)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi0_START               (28)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi0_END                 (28)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi1_START               (29)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi1_END                 (29)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace0_mst_g3d_START        (30)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace0_mst_g3d_END          (30)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace1_mst_g3d_START        (31)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace1_mst_g3d_END          (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTEN0_UNION
 结构说明  : PERRSTEN0 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ddrc          : 1;  /* bit[0]    : IP软复位使能：
                                                                0：IP软复位使能状态不变；
                                                                1：IP软复位使能。 */
        unsigned int  ip_rst_sysbus2ddrc   : 1;  /* bit[1]    :  */
        unsigned int  ip_rst_ddr_exmbist   : 1;  /* bit[2]    :  */
        unsigned int  ip_rst_vcodeccfg     : 1;  /* bit[3]    :  */
        unsigned int  ip_rst_vcodecbus     : 1;  /* bit[4]    :  */
        unsigned int  reserved_0           : 1;  /* bit[5]    : 保留。 */
        unsigned int  ip_rst_vivobus       : 1;  /* bit[6]    :  */
        unsigned int  ip_rst_sysbus        : 1;  /* bit[7]    :  */
        unsigned int  ip_rst_cfgbus        : 1;  /* bit[8]    :  */
        unsigned int  ip_rst_timerperi     : 1;  /* bit[9]    :  */
        unsigned int  reserved_1           : 1;  /* bit[10]   : 保留。 */
        unsigned int  ip_rst_mmc1pericfg   : 1;  /* bit[11]   :  */
        unsigned int  ip_rst_mmc0pericfg   : 1;  /* bit[12]   :  */
        unsigned int  reserved_2           : 1;  /* bit[13]   :  */
        unsigned int  reserved_3           : 1;  /* bit[14]   :  */
        unsigned int  reserved_4           : 1;  /* bit[15]   :  */
        unsigned int  reserved_5           : 1;  /* bit[16]   : 保留。 */
        unsigned int  reserved_6           : 1;  /* bit[17]   : 保留。 */
        unsigned int  ip_rst_perf_stat     : 1;  /* bit[18]   :  */
        unsigned int  ip_rst_dbgsechsicbus : 1;  /* bit[19]   :  */
        unsigned int  ip_rst_lpm32cfgbus   : 1;  /* bit[20]   :  */
        unsigned int  ip_rst_noc_dmabus    : 1;  /* bit[21]   :  */
        unsigned int  ip_rst_memrep        : 1;  /* bit[22]   :  */
        unsigned int  ip_rst_vdm_gpu       : 1;  /* bit[23]   :  */
        unsigned int  ip_rst_vdm_acg2      : 1;  /* bit[24]   :  */
        unsigned int  reserved_7           : 1;  /* bit[25]   : 保留。 */
        unsigned int  reserved_8           : 1;  /* bit[26]   :  */
        unsigned int  reserved_9           : 1;  /* bit[27]   : 保留。 */
        unsigned int  ip_rst_mbus2bus      : 1;  /* bit[28]   :  */
        unsigned int  reserved_10          : 1;  /* bit[29]   :  */
        unsigned int  reserved_11          : 2;  /* bit[30-31]: IP软复位使能：
                                                                0：IP软复位使能状态不变；
                                                                1：IP软复位使能。 */
    } reg;
} SOC_CRGPERIPH_PERRSTEN0_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddrc_START           (0)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddrc_END             (0)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus2ddrc_START    (1)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus2ddrc_END      (1)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddr_exmbist_START    (2)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddr_exmbist_END      (2)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodeccfg_START      (3)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodeccfg_END        (3)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodecbus_START      (4)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodecbus_END        (4)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vivobus_START        (6)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vivobus_END          (6)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus_START         (7)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus_END           (7)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_cfgbus_START         (8)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_cfgbus_END           (8)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_timerperi_START      (9)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_timerperi_END        (9)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc1pericfg_START    (11)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc1pericfg_END      (11)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc0pericfg_START    (12)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc0pericfg_END      (12)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_perf_stat_START      (18)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_perf_stat_END        (18)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_dbgsechsicbus_START  (19)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_dbgsechsicbus_END    (19)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_lpm32cfgbus_START    (20)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_lpm32cfgbus_END      (20)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_noc_dmabus_START     (21)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_noc_dmabus_END       (21)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_memrep_START         (22)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_memrep_END           (22)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_gpu_START        (23)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_gpu_END          (23)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_acg2_START       (24)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_acg2_END         (24)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mbus2bus_START       (28)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mbus2bus_END         (28)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTDIS0_UNION
 结构说明  : PERRSTDIS0 寄存器结构定义。地址偏移量:0x064，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ddrc          : 1;  /* bit[0]    : IP软复位撤离：
                                                                0：IP软复位使能状态不变；
                                                                1：IP软复位撤离。 */
        unsigned int  ip_rst_sysbus2ddrc   : 1;  /* bit[1]    :  */
        unsigned int  ip_rst_ddr_exmbist   : 1;  /* bit[2]    :  */
        unsigned int  ip_rst_vcodeccfg     : 1;  /* bit[3]    :  */
        unsigned int  ip_rst_vcodecbus     : 1;  /* bit[4]    :  */
        unsigned int  reserved_0           : 1;  /* bit[5]    : 保留。 */
        unsigned int  ip_rst_vivobus       : 1;  /* bit[6]    :  */
        unsigned int  ip_rst_sysbus        : 1;  /* bit[7]    :  */
        unsigned int  ip_rst_cfgbus        : 1;  /* bit[8]    :  */
        unsigned int  ip_rst_timerperi     : 1;  /* bit[9]    :  */
        unsigned int  reserved_1           : 1;  /* bit[10]   : 保留。 */
        unsigned int  ip_rst_mmc1pericfg   : 1;  /* bit[11]   :  */
        unsigned int  ip_rst_mmc0pericfg   : 1;  /* bit[12]   :  */
        unsigned int  reserved_2           : 1;  /* bit[13]   :  */
        unsigned int  reserved_3           : 1;  /* bit[14]   :  */
        unsigned int  reserved_4           : 1;  /* bit[15]   :  */
        unsigned int  reserved_5           : 1;  /* bit[16]   : 保留。 */
        unsigned int  reserved_6           : 1;  /* bit[17]   : 保留。 */
        unsigned int  ip_rst_perf_stat     : 1;  /* bit[18]   :  */
        unsigned int  ip_rst_dbgsechsicbus : 1;  /* bit[19]   :  */
        unsigned int  ip_rst_lpm32cfgbus   : 1;  /* bit[20]   :  */
        unsigned int  ip_rst_noc_dmabus    : 1;  /* bit[21]   :  */
        unsigned int  ip_rst_memrep        : 1;  /* bit[22]   :  */
        unsigned int  ip_rst_vdm_gpu       : 1;  /* bit[23]   :  */
        unsigned int  ip_rst_vdm_acg2      : 1;  /* bit[24]   :  */
        unsigned int  reserved_7           : 1;  /* bit[25]   : 保留。 */
        unsigned int  reserved_8           : 1;  /* bit[26]   :  */
        unsigned int  reserved_9           : 1;  /* bit[27]   : 保留。 */
        unsigned int  ip_rst_mbus2bus      : 1;  /* bit[28]   :  */
        unsigned int  reserved_10          : 1;  /* bit[29]   :  */
        unsigned int  reserved_11          : 2;  /* bit[30-31]: IP软复位撤离：
                                                                0：IP软复位使能状态不变；
                                                                1：IP软复位撤离。 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS0_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddrc_START           (0)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddrc_END             (0)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus2ddrc_START    (1)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus2ddrc_END      (1)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddr_exmbist_START    (2)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddr_exmbist_END      (2)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodeccfg_START      (3)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodeccfg_END        (3)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodecbus_START      (4)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodecbus_END        (4)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vivobus_START        (6)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vivobus_END          (6)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus_START         (7)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus_END           (7)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_cfgbus_START         (8)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_cfgbus_END           (8)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_timerperi_START      (9)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_timerperi_END        (9)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc1pericfg_START    (11)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc1pericfg_END      (11)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc0pericfg_START    (12)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc0pericfg_END      (12)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_perf_stat_START      (18)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_perf_stat_END        (18)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_dbgsechsicbus_START  (19)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_dbgsechsicbus_END    (19)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_lpm32cfgbus_START    (20)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_lpm32cfgbus_END      (20)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_noc_dmabus_START     (21)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_noc_dmabus_END       (21)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_memrep_START         (22)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_memrep_END           (22)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_gpu_START        (23)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_gpu_END          (23)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_acg2_START       (24)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_acg2_END         (24)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mbus2bus_START       (28)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mbus2bus_END         (28)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTSTAT0_UNION
 结构说明  : PERRSTSTAT0 寄存器结构定义。地址偏移量:0x068，初值:0x11C40058，宽度:32
 寄存器说明: 外设软复位状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ddrc          : 1;  /* bit[0]    : 外设软复位使能状态：
                                                                0：IP软复位使能撤销；
                                                                1：IP软复位使能； */
        unsigned int  ip_rst_sysbus2ddrc   : 1;  /* bit[1]    :  */
        unsigned int  ip_rst_ddr_exmbist   : 1;  /* bit[2]    :  */
        unsigned int  ip_rst_vcodeccfg     : 1;  /* bit[3]    : 上电默认处于复位状态。 */
        unsigned int  ip_rst_vcodecbus     : 1;  /* bit[4]    : 上电默认处于复位状态。 */
        unsigned int  reserved_0           : 1;  /* bit[5]    : 保留。 */
        unsigned int  ip_rst_vivobus       : 1;  /* bit[6]    :  */
        unsigned int  ip_rst_sysbus        : 1;  /* bit[7]    :  */
        unsigned int  ip_rst_cfgbus        : 1;  /* bit[8]    :  */
        unsigned int  ip_rst_timerperi     : 1;  /* bit[9]    :  */
        unsigned int  reserved_1           : 1;  /* bit[10]   : 保留。 */
        unsigned int  ip_rst_mmc1pericfg   : 1;  /* bit[11]   :  */
        unsigned int  ip_rst_mmc0pericfg   : 1;  /* bit[12]   :  */
        unsigned int  reserved_2           : 1;  /* bit[13]   : 保留。 */
        unsigned int  reserved_3           : 1;  /* bit[14]   : 保留。 */
        unsigned int  reserved_4           : 1;  /* bit[15]   : 保留。 */
        unsigned int  reserved_5           : 1;  /* bit[16]   : 保留。 */
        unsigned int  reserved_6           : 1;  /* bit[17]   : 保留。 */
        unsigned int  ip_rst_perf_stat     : 1;  /* bit[18]   : 上电默认处于复位状态。 */
        unsigned int  ip_rst_dbgsechsicbus : 1;  /* bit[19]   :  */
        unsigned int  ip_rst_lpm32cfgbus   : 1;  /* bit[20]   :  */
        unsigned int  ip_rst_noc_dmabus    : 1;  /* bit[21]   :  */
        unsigned int  ip_rst_memrep        : 1;  /* bit[22]   : 上电默认处于复位状态。 */
        unsigned int  ip_rst_vdm_gpu       : 1;  /* bit[23]   : 上电默认处于复位状态。 */
        unsigned int  ip_rst_vdm_acg2      : 1;  /* bit[24]   : 上电默认处于复位状态。 */
        unsigned int  reserved_7           : 1;  /* bit[25]   : 保留。 */
        unsigned int  reserved_8           : 1;  /* bit[26]   : 保留。 */
        unsigned int  reserved_9           : 1;  /* bit[27]   : 保留。 */
        unsigned int  ip_rst_mbus2bus      : 1;  /* bit[28]   : 上电默认处于复位状态。 */
        unsigned int  reserved_10          : 1;  /* bit[29]   : 保留。 */
        unsigned int  reserved_11          : 2;  /* bit[30-31]: IP软复位使能状态：
                                                                0：IP处于复位撤离状态；
                                                                1：IP处于软复位使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT0_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddrc_START           (0)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddrc_END             (0)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus2ddrc_START    (1)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus2ddrc_END      (1)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddr_exmbist_START    (2)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddr_exmbist_END      (2)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodeccfg_START      (3)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodeccfg_END        (3)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodecbus_START      (4)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodecbus_END        (4)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vivobus_START        (6)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vivobus_END          (6)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus_START         (7)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus_END           (7)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_cfgbus_START         (8)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_cfgbus_END           (8)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_timerperi_START      (9)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_timerperi_END        (9)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc1pericfg_START    (11)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc1pericfg_END      (11)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc0pericfg_START    (12)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc0pericfg_END      (12)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_perf_stat_START      (18)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_perf_stat_END        (18)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_dbgsechsicbus_START  (19)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_dbgsechsicbus_END    (19)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_lpm32cfgbus_START    (20)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_lpm32cfgbus_END      (20)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_noc_dmabus_START     (21)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_noc_dmabus_END       (21)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_memrep_START         (22)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_memrep_END           (22)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_gpu_START        (23)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_gpu_END          (23)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_acg2_START       (24)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_acg2_END         (24)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mbus2bus_START       (28)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mbus2bus_END         (28)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTEN1_UNION
 结构说明  : PERRSTEN1 寄存器结构定义。地址偏移量:0x06C，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_gpio0    : 1;  /* bit[0] : IP软复位使能：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位使能。 */
        unsigned int  ip_rst_gpio1    : 1;  /* bit[1] :  */
        unsigned int  ip_rst_gpio2    : 1;  /* bit[2] :  */
        unsigned int  ip_rst_gpio3    : 1;  /* bit[3] :  */
        unsigned int  ip_rst_gpio4    : 1;  /* bit[4] :  */
        unsigned int  ip_rst_gpio5    : 1;  /* bit[5] :  */
        unsigned int  ip_rst_gpio6    : 1;  /* bit[6] :  */
        unsigned int  ip_rst_gpio7    : 1;  /* bit[7] :  */
        unsigned int  ip_rst_gpio8    : 1;  /* bit[8] :  */
        unsigned int  ip_rst_gpio9    : 1;  /* bit[9] :  */
        unsigned int  ip_rst_gpio10   : 1;  /* bit[10]:  */
        unsigned int  ip_rst_gpio11   : 1;  /* bit[11]:  */
        unsigned int  ip_rst_gpio12   : 1;  /* bit[12]:  */
        unsigned int  ip_rst_gpio13   : 1;  /* bit[13]:  */
        unsigned int  ip_rst_gpio14   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_gpio15   : 1;  /* bit[15]:  */
        unsigned int  ip_rst_gpio16   : 1;  /* bit[16]:  */
        unsigned int  ip_rst_gpio17   : 1;  /* bit[17]:  */
        unsigned int  ip_rst_gpio18   : 1;  /* bit[18]:  */
        unsigned int  ip_rst_gpio19   : 1;  /* bit[19]:  */
        unsigned int  ip_rst_gpio20   : 1;  /* bit[20]:  */
        unsigned int  ip_rst_gpio21   : 1;  /* bit[21]:  */
        unsigned int  ip_rst_timer9   : 1;  /* bit[22]:  */
        unsigned int  ip_rst_timer10  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_timer11  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_timer12  : 1;  /* bit[25]:  */
        unsigned int  ip_rst_socp     : 1;  /* bit[26]:  */
        unsigned int  ip_rst_djtag    : 1;  /* bit[27]:  */
        unsigned int  ip_rst_vdm_maya : 1;  /* bit[28]:  */
        unsigned int  ip_rst_vdm_a53  : 1;  /* bit[29]:  */
        unsigned int  ip_rst_vdm_acg0 : 1;  /* bit[30]:  */
        unsigned int  ip_rst_vdm_acg1 : 1;  /* bit[31]: IP软复位使能（vdm_acg1）：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位使能。 */
    } reg;
} SOC_CRGPERIPH_PERRSTEN1_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio0_START     (0)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio0_END       (0)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio1_START     (1)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio1_END       (1)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio2_START     (2)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio2_END       (2)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio3_START     (3)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio3_END       (3)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio4_START     (4)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio4_END       (4)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio5_START     (5)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio5_END       (5)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio6_START     (6)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio6_END       (6)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio7_START     (7)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio7_END       (7)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio8_START     (8)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio8_END       (8)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio9_START     (9)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio9_END       (9)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio10_START    (10)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio10_END      (10)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio11_START    (11)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio11_END      (11)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio12_START    (12)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio12_END      (12)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio13_START    (13)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio13_END      (13)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio14_START    (14)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio14_END      (14)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio15_START    (15)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio15_END      (15)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio16_START    (16)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio16_END      (16)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio17_START    (17)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio17_END      (17)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio18_START    (18)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio18_END      (18)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio19_START    (19)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio19_END      (19)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio20_START    (20)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio20_END      (20)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio21_START    (21)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio21_END      (21)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer9_START    (22)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer9_END      (22)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer10_START   (23)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer10_END     (23)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer11_START   (24)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer11_END     (24)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer12_START   (25)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer12_END     (25)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_socp_START      (26)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_socp_END        (26)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_djtag_START     (27)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_djtag_END       (27)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_maya_START  (28)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_maya_END    (28)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_a53_START   (29)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_a53_END     (29)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg0_START  (30)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg0_END    (30)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg1_START  (31)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg1_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTDIS1_UNION
 结构说明  : PERRSTDIS1 寄存器结构定义。地址偏移量:0x070，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_gpio0    : 1;  /* bit[0] : IP软复位撤离：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位撤离。 */
        unsigned int  ip_rst_gpio1    : 1;  /* bit[1] :  */
        unsigned int  ip_rst_gpio2    : 1;  /* bit[2] :  */
        unsigned int  ip_rst_gpio3    : 1;  /* bit[3] :  */
        unsigned int  ip_rst_gpio4    : 1;  /* bit[4] :  */
        unsigned int  ip_rst_gpio5    : 1;  /* bit[5] :  */
        unsigned int  ip_rst_gpio6    : 1;  /* bit[6] :  */
        unsigned int  ip_rst_gpio7    : 1;  /* bit[7] :  */
        unsigned int  ip_rst_gpio8    : 1;  /* bit[8] :  */
        unsigned int  ip_rst_gpio9    : 1;  /* bit[9] :  */
        unsigned int  ip_rst_gpio10   : 1;  /* bit[10]:  */
        unsigned int  ip_rst_gpio11   : 1;  /* bit[11]:  */
        unsigned int  ip_rst_gpio12   : 1;  /* bit[12]:  */
        unsigned int  ip_rst_gpio13   : 1;  /* bit[13]:  */
        unsigned int  ip_rst_gpio14   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_gpio15   : 1;  /* bit[15]:  */
        unsigned int  ip_rst_gpio16   : 1;  /* bit[16]:  */
        unsigned int  ip_rst_gpio17   : 1;  /* bit[17]:  */
        unsigned int  ip_rst_gpio18   : 1;  /* bit[18]:  */
        unsigned int  ip_rst_gpio19   : 1;  /* bit[19]:  */
        unsigned int  ip_rst_gpio20   : 1;  /* bit[20]:  */
        unsigned int  ip_rst_gpio21   : 1;  /* bit[21]:  */
        unsigned int  ip_rst_timer9   : 1;  /* bit[22]:  */
        unsigned int  ip_rst_timer10  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_timer11  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_timer12  : 1;  /* bit[25]:  */
        unsigned int  ip_rst_socp     : 1;  /* bit[26]:  */
        unsigned int  ip_rst_djtag    : 1;  /* bit[27]:  */
        unsigned int  ip_rst_vdm_maya : 1;  /* bit[28]:  */
        unsigned int  ip_rst_vdm_a53  : 1;  /* bit[29]:  */
        unsigned int  ip_rst_vdm_acg0 : 1;  /* bit[30]:  */
        unsigned int  ip_rst_vdm_acg1 : 1;  /* bit[31]: IP软复位撤离（vdm_acg1）：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位撤离。 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS1_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio0_START     (0)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio0_END       (0)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio1_START     (1)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio1_END       (1)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio2_START     (2)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio2_END       (2)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio3_START     (3)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio3_END       (3)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio4_START     (4)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio4_END       (4)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio5_START     (5)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio5_END       (5)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio6_START     (6)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio6_END       (6)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio7_START     (7)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio7_END       (7)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio8_START     (8)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio8_END       (8)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio9_START     (9)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio9_END       (9)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio10_START    (10)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio10_END      (10)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio11_START    (11)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio11_END      (11)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio12_START    (12)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio12_END      (12)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio13_START    (13)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio13_END      (13)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio14_START    (14)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio14_END      (14)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio15_START    (15)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio15_END      (15)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio16_START    (16)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio16_END      (16)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio17_START    (17)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio17_END      (17)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio18_START    (18)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio18_END      (18)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio19_START    (19)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio19_END      (19)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio20_START    (20)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio20_END      (20)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio21_START    (21)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio21_END      (21)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer9_START    (22)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer9_END      (22)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer10_START   (23)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer10_END     (23)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer11_START   (24)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer11_END     (24)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer12_START   (25)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer12_END     (25)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_socp_START      (26)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_socp_END        (26)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_djtag_START     (27)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_djtag_END       (27)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_maya_START  (28)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_maya_END    (28)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_a53_START   (29)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_a53_END     (29)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg0_START  (30)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg0_END    (30)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg1_START  (31)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg1_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTSTAT1_UNION
 结构说明  : PERRSTSTAT1 寄存器结构定义。地址偏移量:0x074，初值:0xF0000000，宽度:32
 寄存器说明: 外设软复位状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_gpio0    : 1;  /* bit[0] : 外设软复位使能状态：
                                                        0：IP软复位使能撤销；
                                                        1：IP软复位使能； */
        unsigned int  ip_rst_gpio1    : 1;  /* bit[1] :  */
        unsigned int  ip_rst_gpio2    : 1;  /* bit[2] :  */
        unsigned int  ip_rst_gpio3    : 1;  /* bit[3] :  */
        unsigned int  ip_rst_gpio4    : 1;  /* bit[4] :  */
        unsigned int  ip_rst_gpio5    : 1;  /* bit[5] :  */
        unsigned int  ip_rst_gpio6    : 1;  /* bit[6] :  */
        unsigned int  ip_rst_gpio7    : 1;  /* bit[7] :  */
        unsigned int  ip_rst_gpio8    : 1;  /* bit[8] :  */
        unsigned int  ip_rst_gpio9    : 1;  /* bit[9] :  */
        unsigned int  ip_rst_gpio10   : 1;  /* bit[10]:  */
        unsigned int  ip_rst_gpio11   : 1;  /* bit[11]:  */
        unsigned int  ip_rst_gpio12   : 1;  /* bit[12]:  */
        unsigned int  ip_rst_gpio13   : 1;  /* bit[13]:  */
        unsigned int  ip_rst_gpio14   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_gpio15   : 1;  /* bit[15]:  */
        unsigned int  ip_rst_gpio16   : 1;  /* bit[16]:  */
        unsigned int  ip_rst_gpio17   : 1;  /* bit[17]:  */
        unsigned int  ip_rst_gpio18   : 1;  /* bit[18]:  */
        unsigned int  ip_rst_gpio19   : 1;  /* bit[19]:  */
        unsigned int  ip_rst_gpio20   : 1;  /* bit[20]:  */
        unsigned int  ip_rst_gpio21   : 1;  /* bit[21]:  */
        unsigned int  ip_rst_timer9   : 1;  /* bit[22]:  */
        unsigned int  ip_rst_timer10  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_timer11  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_timer12  : 1;  /* bit[25]:  */
        unsigned int  ip_rst_socp     : 1;  /* bit[26]:  */
        unsigned int  ip_rst_djtag    : 1;  /* bit[27]:  */
        unsigned int  ip_rst_vdm_maya : 1;  /* bit[28]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_vdm_a53  : 1;  /* bit[29]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_vdm_acg0 : 1;  /* bit[30]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_vdm_acg1 : 1;  /* bit[31]: IP软复位使能状态（vdm_acg1）：
                                                        0：IP处于复位撤离状态；
                                                        1：IP处于软复位使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT1_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio0_START     (0)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio0_END       (0)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio1_START     (1)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio1_END       (1)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio2_START     (2)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio2_END       (2)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio3_START     (3)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio3_END       (3)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio4_START     (4)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio4_END       (4)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio5_START     (5)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio5_END       (5)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio6_START     (6)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio6_END       (6)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio7_START     (7)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio7_END       (7)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio8_START     (8)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio8_END       (8)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio9_START     (9)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio9_END       (9)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio10_START    (10)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio10_END      (10)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio11_START    (11)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio11_END      (11)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio12_START    (12)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio12_END      (12)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio13_START    (13)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio13_END      (13)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio14_START    (14)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio14_END      (14)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio15_START    (15)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio15_END      (15)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio16_START    (16)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio16_END      (16)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio17_START    (17)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio17_END      (17)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio18_START    (18)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio18_END      (18)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio19_START    (19)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio19_END      (19)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio20_START    (20)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio20_END      (20)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio21_START    (21)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio21_END      (21)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer9_START    (22)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer9_END      (22)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer10_START   (23)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer10_END     (23)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer11_START   (24)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer11_END     (24)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer12_START   (25)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer12_END     (25)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_socp_START      (26)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_socp_END        (26)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_djtag_START     (27)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_djtag_END       (27)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_maya_START  (28)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_maya_END    (28)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_a53_START   (29)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_a53_END     (29)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg0_START  (30)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg0_END    (30)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg1_START  (31)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg1_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTEN2_UNION
 结构说明  : PERRSTEN2 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_pwm      : 1;  /* bit[0] : IP软复位使能：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位使能。 */
        unsigned int  reserved_0      : 1;  /* bit[1] : 保留。 */
        unsigned int  ip_rst_ipc0     : 1;  /* bit[2] :  */
        unsigned int  ip_rst_ipc1     : 1;  /* bit[3] :  */
        unsigned int  reserved_1      : 1;  /* bit[4] : 保留。 */
        unsigned int  reserved_2      : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_3      : 1;  /* bit[6] : 保留。 */
        unsigned int  ip_rst_i2c3     : 1;  /* bit[7] :  */
        unsigned int  reserved_4      : 1;  /* bit[8] : 保留。 */
        unsigned int  ip_rst_spi1     : 1;  /* bit[9] :  */
        unsigned int  ip_rst_uart0    : 1;  /* bit[10]:  */
        unsigned int  ip_rst_uart1    : 1;  /* bit[11]:  */
        unsigned int  ip_rst_uart2    : 1;  /* bit[12]:  */
        unsigned int  reserved_5      : 1;  /* bit[13]: 保留。 */
        unsigned int  ip_rst_uart4    : 1;  /* bit[14]:  */
        unsigned int  ip_rst_uart5    : 1;  /* bit[15]:  */
        unsigned int  ip_rst_tzpc     : 1;  /* bit[16]:  */
        unsigned int  reserved_6      : 1;  /* bit[17]:  */
        unsigned int  reserved_7      : 1;  /* bit[18]:  */
        unsigned int  reserved_8      : 1;  /* bit[19]: 保留。 */
        unsigned int  ip_prst_ipc_mdm : 1;  /* bit[20]:  */
        unsigned int  ip_rst_adb_a53  : 1;  /* bit[21]:  */
        unsigned int  ip_rst_adb_a57  : 1;  /* bit[22]:  */
        unsigned int  ip_rst_gic      : 1;  /* bit[23]:  */
        unsigned int  ip_rst_hkadcssi : 1;  /* bit[24]:  */
        unsigned int  ip_rst_ioc      : 1;  /* bit[25]:  */
        unsigned int  ip_rst_codecssi : 1;  /* bit[26]:  */
        unsigned int  ip_rst_i2c4     : 1;  /* bit[27]:  */
        unsigned int  reserved_9      : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_10     : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_11     : 1;  /* bit[30]: 保留。 */
        unsigned int  ip_rst_pctrl    : 1;  /* bit[31]: IP软复位使能（pctrl）：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位使能。 */
    } reg;
} SOC_CRGPERIPH_PERRSTEN2_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pwm_START       (0)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pwm_END         (0)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc0_START      (2)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc0_END        (2)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc1_START      (3)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc1_END        (3)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c3_START      (7)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c3_END        (7)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_spi1_START      (9)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_spi1_END        (9)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart0_START     (10)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart0_END       (10)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart1_START     (11)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart1_END       (11)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart2_START     (12)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart2_END       (12)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart4_START     (14)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart4_END       (14)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart5_START     (15)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart5_END       (15)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_tzpc_START      (16)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_tzpc_END        (16)
#define SOC_CRGPERIPH_PERRSTEN2_ip_prst_ipc_mdm_START  (20)
#define SOC_CRGPERIPH_PERRSTEN2_ip_prst_ipc_mdm_END    (20)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a53_START   (21)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a53_END     (21)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a57_START   (22)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a57_END     (22)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_gic_START       (23)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_gic_END         (23)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_hkadcssi_START  (24)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_hkadcssi_END    (24)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ioc_START       (25)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ioc_END         (25)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_codecssi_START  (26)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_codecssi_END    (26)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c4_START      (27)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c4_END        (27)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pctrl_START     (31)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pctrl_END       (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTDIS2_UNION
 结构说明  : PERRSTDIS2 寄存器结构定义。地址偏移量:0x07C，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_pwm      : 1;  /* bit[0] : IP软复位撤离：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位撤离。 */
        unsigned int  reserved_0      : 1;  /* bit[1] : 保留。 */
        unsigned int  ip_rst_ipc0     : 1;  /* bit[2] :  */
        unsigned int  ip_rst_ipc1     : 1;  /* bit[3] :  */
        unsigned int  reserved_1      : 1;  /* bit[4] : 保留。 */
        unsigned int  reserved_2      : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_3      : 1;  /* bit[6] : 保留。 */
        unsigned int  ip_rst_i2c3     : 1;  /* bit[7] :  */
        unsigned int  reserved_4      : 1;  /* bit[8] : 保留。 */
        unsigned int  ip_rst_spi1     : 1;  /* bit[9] :  */
        unsigned int  ip_rst_uart0    : 1;  /* bit[10]:  */
        unsigned int  ip_rst_uart1    : 1;  /* bit[11]:  */
        unsigned int  ip_rst_uart2    : 1;  /* bit[12]:  */
        unsigned int  reserved_5      : 1;  /* bit[13]: 保留。 */
        unsigned int  ip_rst_uart4    : 1;  /* bit[14]:  */
        unsigned int  ip_rst_uart5    : 1;  /* bit[15]:  */
        unsigned int  ip_rst_tzpc     : 1;  /* bit[16]:  */
        unsigned int  reserved_6      : 1;  /* bit[17]:  */
        unsigned int  reserved_7      : 1;  /* bit[18]:  */
        unsigned int  reserved_8      : 1;  /* bit[19]: 保留。 */
        unsigned int  ip_prst_ipc_mdm : 1;  /* bit[20]:  */
        unsigned int  ip_rst_adb_a53  : 1;  /* bit[21]:  */
        unsigned int  ip_rst_adb_a57  : 1;  /* bit[22]:  */
        unsigned int  ip_rst_gic      : 1;  /* bit[23]:  */
        unsigned int  ip_rst_hkadcssi : 1;  /* bit[24]:  */
        unsigned int  ip_rst_ioc      : 1;  /* bit[25]:  */
        unsigned int  ip_rst_codecssi : 1;  /* bit[26]:  */
        unsigned int  ip_rst_i2c4     : 1;  /* bit[27]:  */
        unsigned int  reserved_9      : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_10     : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_11     : 1;  /* bit[30]: 保留。 */
        unsigned int  ip_rst_pctrl    : 1;  /* bit[31]: IP软复位撤离（pctrl）：
                                                        0：IP软复位使能状态不变；
                                                        1：IP软复位撤离。 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS2_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pwm_START       (0)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pwm_END         (0)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc0_START      (2)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc0_END        (2)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc1_START      (3)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc1_END        (3)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c3_START      (7)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c3_END        (7)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_spi1_START      (9)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_spi1_END        (9)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart0_START     (10)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart0_END       (10)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart1_START     (11)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart1_END       (11)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart2_START     (12)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart2_END       (12)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart4_START     (14)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart4_END       (14)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart5_START     (15)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart5_END       (15)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_tzpc_START      (16)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_tzpc_END        (16)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_prst_ipc_mdm_START  (20)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_prst_ipc_mdm_END    (20)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a53_START   (21)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a53_END     (21)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a57_START   (22)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a57_END     (22)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_gic_START       (23)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_gic_END         (23)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_hkadcssi_START  (24)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_hkadcssi_END    (24)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ioc_START       (25)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ioc_END         (25)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_codecssi_START  (26)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_codecssi_END    (26)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c4_START      (27)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c4_END        (27)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pctrl_START     (31)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pctrl_END       (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTSTAT2_UNION
 结构说明  : PERRSTSTAT2 寄存器结构定义。地址偏移量:0x080，初值:0x00600000，宽度:32
 寄存器说明: 外设软复位状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_pwm      : 1;  /* bit[0] : IP软复位使能状态：
                                                        0：IP处于复位撤离状态；
                                                        1：IP处于软复位使能状态。 */
        unsigned int  reserved_0      : 1;  /* bit[1] : 保留。 */
        unsigned int  ip_rst_ipc0     : 1;  /* bit[2] :  */
        unsigned int  ip_rst_ipc1     : 1;  /* bit[3] :  */
        unsigned int  reserved_1      : 1;  /* bit[4] : 保留。 */
        unsigned int  reserved_2      : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_3      : 1;  /* bit[6] : 保留。 */
        unsigned int  ip_rst_i2c3     : 1;  /* bit[7] :  */
        unsigned int  reserved_4      : 1;  /* bit[8] : 保留。 */
        unsigned int  ip_rst_spi1     : 1;  /* bit[9] :  */
        unsigned int  ip_rst_uart0    : 1;  /* bit[10]:  */
        unsigned int  ip_rst_uart1    : 1;  /* bit[11]:  */
        unsigned int  ip_rst_uart2    : 1;  /* bit[12]:  */
        unsigned int  reserved_5      : 1;  /* bit[13]: 保留。 */
        unsigned int  ip_rst_uart4    : 1;  /* bit[14]:  */
        unsigned int  ip_rst_uart5    : 1;  /* bit[15]:  */
        unsigned int  ip_rst_tzpc     : 1;  /* bit[16]:  */
        unsigned int  reserved_6      : 1;  /* bit[17]:  */
        unsigned int  reserved_7      : 1;  /* bit[18]:  */
        unsigned int  reserved_8      : 1;  /* bit[19]: 保留。 */
        unsigned int  ip_prst_ipc_mdm : 1;  /* bit[20]:  */
        unsigned int  ip_rst_adb_a53  : 1;  /* bit[21]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_adb_a57  : 1;  /* bit[22]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_gic      : 1;  /* bit[23]:  */
        unsigned int  ip_rst_hkadcssi : 1;  /* bit[24]:  */
        unsigned int  ip_rst_ioc      : 1;  /* bit[25]:  */
        unsigned int  ip_rst_codecssi : 1;  /* bit[26]:  */
        unsigned int  ip_rst_i2c4     : 1;  /* bit[27]:  */
        unsigned int  reserved_9      : 1;  /* bit[28]: 保留。 */
        unsigned int  reserved_10     : 1;  /* bit[29]: 保留。 */
        unsigned int  reserved_11     : 1;  /* bit[30]: 保留。 */
        unsigned int  ip_rst_pctrl    : 1;  /* bit[31]: IP软复位使能状态（pctrl）：
                                                        0：IP处于复位撤离状态；
                                                        1：IP处于软复位使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT2_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pwm_START       (0)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pwm_END         (0)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc0_START      (2)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc0_END        (2)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc1_START      (3)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc1_END        (3)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c3_START      (7)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c3_END        (7)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_spi1_START      (9)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_spi1_END        (9)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart0_START     (10)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart0_END       (10)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart1_START     (11)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart1_END       (11)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart2_START     (12)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart2_END       (12)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart4_START     (14)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart4_END       (14)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart5_START     (15)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart5_END       (15)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_tzpc_START      (16)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_tzpc_END        (16)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_prst_ipc_mdm_START  (20)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_prst_ipc_mdm_END    (20)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a53_START   (21)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a53_END     (21)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a57_START   (22)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a57_END     (22)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_gic_START       (23)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_gic_END         (23)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_hkadcssi_START  (24)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_hkadcssi_END    (24)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ioc_START       (25)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ioc_END         (25)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_codecssi_START  (26)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_codecssi_END    (26)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c4_START      (27)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c4_END        (27)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pctrl_START     (31)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pctrl_END       (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTEN3_UNION
 结构说明  : PERRSTEN3 寄存器结构定义。地址偏移量:0x084，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dmac      : 1;  /* bit[0] : IP软复位使能：
                                                         0：IP软复位使能状态不变；
                                                         1：IP软复位使能。 */
        unsigned int  reserved_0       : 1;  /* bit[1] : 保留。 */
        unsigned int  ip_prst_g3d      : 1;  /* bit[2] :  */
        unsigned int  ip_rst_g3d       : 1;  /* bit[3] :  */
        unsigned int  ip_rst_g3dmt     : 1;  /* bit[4] :  */
        unsigned int  reserved_1       : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_2       : 1;  /* bit[6] : 保留。 */
        unsigned int  reserved_3       : 1;  /* bit[7] : 保留。 */
        unsigned int  ip_rst_venc      : 1;  /* bit[8] :  */
        unsigned int  ip_rst_vdec      : 1;  /* bit[9] :  */
        unsigned int  ip_rst_dss       : 1;  /* bit[10]:  */
        unsigned int  ip_prst_dss      : 1;  /* bit[11]:  */
        unsigned int  reserved_4       : 1;  /* bit[12]: 保留。 */
        unsigned int  reserved_5       : 1;  /* bit[13]: 保留。 */
        unsigned int  reserved_6       : 1;  /* bit[14]: 保留。 */
        unsigned int  reserved_7       : 1;  /* bit[15]: 保留。 */
        unsigned int  ip_rst_g3ds_hpm5 : 1;  /* bit[16]:  */
        unsigned int  ip_rst_g3ds_hpm4 : 1;  /* bit[17]:  */
        unsigned int  ip_rst_g3ds_hpm3 : 1;  /* bit[18]:  */
        unsigned int  ip_rst_g3ds_hpm2 : 1;  /* bit[19]:  */
        unsigned int  ip_rst_g3ds_hpm1 : 1;  /* bit[20]:  */
        unsigned int  ip_rst_g3ds_hpm0 : 1;  /* bit[21]:  */
        unsigned int  ip_rst_g3dg_hpm  : 1;  /* bit[22]:  */
        unsigned int  ip_rst_peri_hpm  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_ao_hpm    : 1;  /* bit[24]:  */
        unsigned int  reserved_8       : 1;  /* bit[25]: 保留。 */
        unsigned int  reserved_9       : 1;  /* bit[26]: 保留。 */
        unsigned int  reserved_10      : 1;  /* bit[27]: 保留。 */
        unsigned int  ip_rst_dsi0      : 1;  /* bit[28]:  */
        unsigned int  ip_rst_dsi1      : 1;  /* bit[29]:  */
        unsigned int  reserved_11      : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_12      : 1;  /* bit[31]: IP软复位使能：
                                                         0：IP软复位使能状态不变；
                                                         1：IP软复位使能。 */
    } reg;
} SOC_CRGPERIPH_PERRSTEN3_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dmac_START       (0)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dmac_END         (0)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_g3d_START       (2)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_g3d_END         (2)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3d_START        (3)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3d_END          (3)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dmt_START      (4)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dmt_END        (4)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_venc_START       (8)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_venc_END         (8)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_vdec_START       (9)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_vdec_END         (9)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dss_START        (10)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dss_END          (10)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_dss_START       (11)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_dss_END         (11)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm5_START  (16)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm5_END    (16)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm4_START  (17)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm4_END    (17)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm3_START  (18)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm3_END    (18)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm2_START  (19)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm2_END    (19)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm1_START  (20)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm1_END    (20)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm0_START  (21)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm0_END    (21)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dg_hpm_START   (22)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dg_hpm_END     (22)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_peri_hpm_START   (23)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_peri_hpm_END     (23)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_ao_hpm_START     (24)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_ao_hpm_END       (24)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi0_START       (28)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi0_END         (28)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi1_START       (29)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi1_END         (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTDIS3_UNION
 结构说明  : PERRSTDIS3 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dmac      : 1;  /* bit[0] : IP软复位撤离：
                                                         0：IP软复位使能状态不变；
                                                         1：IP软复位撤离。 */
        unsigned int  reserved_0       : 1;  /* bit[1] : 保留。 */
        unsigned int  ip_prst_g3d      : 1;  /* bit[2] :  */
        unsigned int  ip_rst_g3d       : 1;  /* bit[3] :  */
        unsigned int  ip_rst_g3dmt     : 1;  /* bit[4] :  */
        unsigned int  reserved_1       : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_2       : 1;  /* bit[6] : 保留。 */
        unsigned int  reserved_3       : 1;  /* bit[7] : 保留。 */
        unsigned int  ip_rst_venc      : 1;  /* bit[8] :  */
        unsigned int  ip_rst_vdec      : 1;  /* bit[9] :  */
        unsigned int  ip_rst_dss       : 1;  /* bit[10]:  */
        unsigned int  ip_prst_dss      : 1;  /* bit[11]:  */
        unsigned int  reserved_4       : 1;  /* bit[12]: 保留。 */
        unsigned int  reserved_5       : 1;  /* bit[13]: 保留。 */
        unsigned int  reserved_6       : 1;  /* bit[14]: 保留。 */
        unsigned int  reserved_7       : 1;  /* bit[15]: 保留。 */
        unsigned int  ip_rst_g3ds_hpm5 : 1;  /* bit[16]:  */
        unsigned int  ip_rst_g3ds_hpm4 : 1;  /* bit[17]:  */
        unsigned int  ip_rst_g3ds_hpm3 : 1;  /* bit[18]:  */
        unsigned int  ip_rst_g3ds_hpm2 : 1;  /* bit[19]:  */
        unsigned int  ip_rst_g3ds_hpm1 : 1;  /* bit[20]:  */
        unsigned int  ip_rst_g3ds_hpm0 : 1;  /* bit[21]:  */
        unsigned int  ip_rst_g3dg_hpm  : 1;  /* bit[22]:  */
        unsigned int  ip_rst_peri_hpm  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_ao_hpm    : 1;  /* bit[24]:  */
        unsigned int  reserved_8       : 1;  /* bit[25]: 保留。 */
        unsigned int  reserved_9       : 1;  /* bit[26]: 保留。 */
        unsigned int  reserved_10      : 1;  /* bit[27]: 保留。 */
        unsigned int  ip_rst_dsi0      : 1;  /* bit[28]:  */
        unsigned int  ip_rst_dsi1      : 1;  /* bit[29]:  */
        unsigned int  reserved_11      : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_12      : 1;  /* bit[31]: IP软复位撤离：
                                                         0：IP软复位使能状态不变；
                                                         1：IP软复位撤离。 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS3_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dmac_START       (0)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dmac_END         (0)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_g3d_START       (2)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_g3d_END         (2)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3d_START        (3)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3d_END          (3)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dmt_START      (4)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dmt_END        (4)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_venc_START       (8)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_venc_END         (8)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_vdec_START       (9)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_vdec_END         (9)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dss_START        (10)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dss_END          (10)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_dss_START       (11)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_dss_END         (11)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm5_START  (16)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm5_END    (16)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm4_START  (17)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm4_END    (17)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm3_START  (18)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm3_END    (18)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm2_START  (19)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm2_END    (19)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm1_START  (20)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm1_END    (20)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm0_START  (21)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm0_END    (21)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dg_hpm_START   (22)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dg_hpm_END     (22)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_peri_hpm_START   (23)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_peri_hpm_END     (23)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_ao_hpm_START     (24)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_ao_hpm_END       (24)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi0_START       (28)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi0_END         (28)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi1_START       (29)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi1_END         (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTSTAT3_UNION
 结构说明  : PERRSTSTAT3 寄存器结构定义。地址偏移量:0x008C，初值:0x71FF5F1C，宽度:32
 寄存器说明: 外设软复位状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dmac      : 1;  /* bit[0] : IP软复位使能状态：
                                                         0：IP处于复位撤离状态；
                                                         1：IP处于软复位使能状态。 */
        unsigned int  reserved_0       : 1;  /* bit[1] : 保留。 */
        unsigned int  ip_prst_g3d      : 1;  /* bit[2] : 上电默认处于复位状态。 */
        unsigned int  ip_rst_g3d       : 1;  /* bit[3] : 上电默认处于复位状态。 */
        unsigned int  ip_rst_g3dmt     : 1;  /* bit[4] : 上电默认处于复位状态。 */
        unsigned int  reserved_1       : 1;  /* bit[5] : 保留。 */
        unsigned int  reserved_2       : 1;  /* bit[6] : 保留。 */
        unsigned int  reserved_3       : 1;  /* bit[7] : 保留。 */
        unsigned int  ip_rst_venc      : 1;  /* bit[8] : 上电默认处于复位状态。 */
        unsigned int  ip_rst_vdec      : 1;  /* bit[9] : 上电默认处于复位状态。 */
        unsigned int  ip_rst_dss       : 1;  /* bit[10]: 上电默认处于复位状态。 */
        unsigned int  ip_prst_dss      : 1;  /* bit[11]: 上电默认处于复位状态。 */
        unsigned int  reserved_4       : 1;  /* bit[12]: 保留。 */
        unsigned int  reserved_5       : 1;  /* bit[13]: 保留。 */
        unsigned int  reserved_6       : 1;  /* bit[14]: 保留。 */
        unsigned int  reserved_7       : 1;  /* bit[15]: 保留。 */
        unsigned int  ip_rst_g3ds_hpm5 : 1;  /* bit[16]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_g3ds_hpm4 : 1;  /* bit[17]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_g3ds_hpm3 : 1;  /* bit[18]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_g3ds_hpm2 : 1;  /* bit[19]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_g3ds_hpm1 : 1;  /* bit[20]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_g3ds_hpm0 : 1;  /* bit[21]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_g3dg_hpm  : 1;  /* bit[22]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_peri_hpm  : 1;  /* bit[23]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_ao_hpm    : 1;  /* bit[24]: 上电默认处于复位状态。 */
        unsigned int  reserved_8       : 1;  /* bit[25]: 保留。 */
        unsigned int  reserved_9       : 1;  /* bit[26]: 保留。 */
        unsigned int  reserved_10      : 1;  /* bit[27]: 保留。 */
        unsigned int  ip_rst_dsi0      : 1;  /* bit[28]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_dsi1      : 1;  /* bit[29]: 上电默认处于复位状态。 */
        unsigned int  reserved_11      : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_12      : 1;  /* bit[31]: IP软复位使能状态：
                                                         0：IP处于复位撤离状态；
                                                         1：IP处于软复位使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT3_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dmac_START       (0)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dmac_END         (0)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_g3d_START       (2)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_g3d_END         (2)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3d_START        (3)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3d_END          (3)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dmt_START      (4)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dmt_END        (4)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_venc_START       (8)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_venc_END         (8)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_vdec_START       (9)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_vdec_END         (9)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dss_START        (10)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dss_END          (10)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_dss_START       (11)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_dss_END         (11)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm5_START  (16)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm5_END    (16)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm4_START  (17)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm4_END    (17)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm3_START  (18)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm3_END    (18)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm2_START  (19)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm2_END    (19)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm1_START  (20)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm1_END    (20)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm0_START  (21)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm0_END    (21)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dg_hpm_START   (22)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dg_hpm_END     (22)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_peri_hpm_START   (23)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_peri_hpm_END     (23)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_ao_hpm_START     (24)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_ao_hpm_END       (24)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi0_START       (28)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi0_END         (28)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi1_START       (29)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi1_END         (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTEN4_UNION
 结构说明  : PERRSTEN4 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dbgsechsic_subsys_crg : 1;  /* bit[0] : IP软复位使能：
                                                                     0：IP软复位使能状态不变；
                                                                     1：IP软复位使能。 */
        unsigned int  reserved_0                   : 1;  /* bit[1] : 保留。 */
        unsigned int  reserved_1                   : 1;  /* bit[2] : 保留。 */
        unsigned int  ip_rst_usb3otgphy_por        : 1;  /* bit[3] :  */
        unsigned int  reserved_2                   : 1;  /* bit[4] : 保留。 */
        unsigned int  ip_rst_usb3otg               : 1;  /* bit[5] :  */
        unsigned int  ip_rst_usb3otg_32k           : 1;  /* bit[6] :  */
        unsigned int  ip_rst_usb3otg_ahbif         : 1;  /* bit[7] :  */
        unsigned int  ip_rst_usb3otg_mux           : 1;  /* bit[8] :  */
        unsigned int  reserved_3                   : 1;  /* bit[9] : 保留。 */
        unsigned int  reserved_4                   : 1;  /* bit[10]: 保留。 */
        unsigned int  reserved_5                   : 1;  /* bit[11]: 保留。 */
        unsigned int  reserved_6                   : 1;  /* bit[12]: 保留。 */
        unsigned int  reserved_7                   : 1;  /* bit[13]: 保留。 */
        unsigned int  reserved_8                   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_secp                  : 1;  /* bit[15]:  */
        unsigned int  ip_rst_emmc0                 : 1;  /* bit[16]:  */
        unsigned int  ip_rst_emmc1                 : 1;  /* bit[17]:  */
        unsigned int  ip_rst_sd                    : 1;  /* bit[18]:  */
        unsigned int  ip_rst_sdio0                 : 1;  /* bit[19]:  */
        unsigned int  ip_rst_sdio1                 : 1;  /* bit[20]:  */
        unsigned int  ip_rst_cci400                : 1;  /* bit[21]:  */
        unsigned int  ip_rst_emmc0_m               : 1;  /* bit[22]:  */
        unsigned int  ip_rst_emmc1_m               : 1;  /* bit[23]:  */
        unsigned int  ip_rst_sd_m                  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_sdio0_m               : 1;  /* bit[25]:  */
        unsigned int  ip_rst_sdio1_m               : 1;  /* bit[26]:  */
        unsigned int  reserved_9                   : 1;  /* bit[27]: 保留。 */
        unsigned int  ip_rst_lpmcu                 : 1;  /* bit[28]: 整个LPM3子系统的复位使能：
                                                                     0：软复位使能状态不变；
                                                                     1：软复位使能。
                                                                     不允许软件使用，一旦配置会导致系统死锁。 */
        unsigned int  ip_rst_sysbus2hkmem          : 1;  /* bit[29]:  */
        unsigned int  reserved_10                  : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_11                  : 1;  /* bit[31]: IP软复位使能：
                                                                     0：IP软复位使能状态不变；
                                                                     1：IP软复位使能。 */
    } reg;
} SOC_CRGPERIPH_PERRSTEN4_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_dbgsechsic_subsys_crg_START  (0)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_dbgsechsic_subsys_crg_END    (0)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otgphy_por_START         (3)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otgphy_por_END           (3)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_START                (5)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_END                  (5)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_32k_START            (6)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_32k_END              (6)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_ahbif_START          (7)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_ahbif_END            (7)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_mux_START            (8)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_mux_END              (8)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_secp_START                   (15)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_secp_END                     (15)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_START                  (16)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_END                    (16)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_START                  (17)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_END                    (17)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_START                     (18)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_END                       (18)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_START                  (19)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_END                    (19)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_START                  (20)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_END                    (20)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_cci400_START                 (21)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_cci400_END                   (21)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_m_START                (22)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_m_END                  (22)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_m_START                (23)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_m_END                  (23)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_m_START                   (24)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_m_END                     (24)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_m_START                (25)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_m_END                  (25)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_m_START                (26)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_m_END                  (26)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_lpmcu_START                  (28)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_lpmcu_END                    (28)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sysbus2hkmem_START           (29)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sysbus2hkmem_END             (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTDIS4_UNION
 结构说明  : PERRSTDIS4 寄存器结构定义。地址偏移量:0x094，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dbgsechsic_subsys_crg : 1;  /* bit[0] : IP软复位撤离：
                                                                     0：IP软复位使能状态不变；
                                                                     1：IP软复位撤离。 */
        unsigned int  reserved_0                   : 1;  /* bit[1] : 保留。 */
        unsigned int  reserved_1                   : 1;  /* bit[2] : 保留。 */
        unsigned int  ip_rst_usb3otgphy_por        : 1;  /* bit[3] :  */
        unsigned int  reserved_2                   : 1;  /* bit[4] : 保留。 */
        unsigned int  ip_rst_usb3otg               : 1;  /* bit[5] :  */
        unsigned int  ip_rst_usb3otg_32k           : 1;  /* bit[6] :  */
        unsigned int  ip_rst_usb3otg_ahbif         : 1;  /* bit[7] :  */
        unsigned int  ip_rst_usb3otg_mux           : 1;  /* bit[8] :  */
        unsigned int  reserved_3                   : 1;  /* bit[9] : 保留。 */
        unsigned int  reserved_4                   : 1;  /* bit[10]: 保留。 */
        unsigned int  reserved_5                   : 1;  /* bit[11]: 保留。 */
        unsigned int  reserved_6                   : 1;  /* bit[12]: 保留。 */
        unsigned int  reserved_7                   : 1;  /* bit[13]: 保留。 */
        unsigned int  reserved_8                   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_secp                  : 1;  /* bit[15]:  */
        unsigned int  ip_rst_emmc0                 : 1;  /* bit[16]: 保留。 */
        unsigned int  ip_rst_emmc1                 : 1;  /* bit[17]:  */
        unsigned int  ip_rst_sd                    : 1;  /* bit[18]:  */
        unsigned int  ip_rst_sdio0                 : 1;  /* bit[19]:  */
        unsigned int  ip_rst_sdio1                 : 1;  /* bit[20]:  */
        unsigned int  ip_rst_cci400                : 1;  /* bit[21]:  */
        unsigned int  ip_rst_emmc0_m               : 1;  /* bit[22]:  */
        unsigned int  ip_rst_emmc1_m               : 1;  /* bit[23]:  */
        unsigned int  ip_rst_sd_m                  : 1;  /* bit[24]: 保留。 */
        unsigned int  ip_rst_sdio0_m               : 1;  /* bit[25]: 保留。 */
        unsigned int  ip_rst_sdio1_m               : 1;  /* bit[26]: 保留。 */
        unsigned int  reserved_9                   : 1;  /* bit[27]: 保留。 */
        unsigned int  ip_rst_lpmcu                 : 1;  /* bit[28]: 整个LPM3子系统的复位使能：
                                                                     0：软复位使能状态不变；
                                                                     1：软复位撤离。 */
        unsigned int  ip_rst_sysbus2hkmem          : 1;  /* bit[29]:  */
        unsigned int  reserved_10                  : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_11                  : 1;  /* bit[31]: IP软复位撤离：
                                                                     0：IP软复位使能状态不变；
                                                                     1：IP软复位撤离。 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS4_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_dbgsechsic_subsys_crg_START  (0)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_dbgsechsic_subsys_crg_END    (0)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otgphy_por_START         (3)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otgphy_por_END           (3)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_START                (5)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_END                  (5)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_32k_START            (6)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_32k_END              (6)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_ahbif_START          (7)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_ahbif_END            (7)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_mux_START            (8)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_mux_END              (8)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_secp_START                   (15)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_secp_END                     (15)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_START                  (16)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_END                    (16)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_START                  (17)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_END                    (17)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_START                     (18)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_END                       (18)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_START                  (19)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_END                    (19)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_START                  (20)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_END                    (20)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_cci400_START                 (21)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_cci400_END                   (21)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_m_START                (22)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_m_END                  (22)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_m_START                (23)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_m_END                  (23)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_m_START                   (24)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_m_END                     (24)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_m_START                (25)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_m_END                  (25)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_m_START                (26)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_m_END                  (26)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_lpmcu_START                  (28)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_lpmcu_END                    (28)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sysbus2hkmem_START           (29)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sysbus2hkmem_END             (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTSTAT4_UNION
 结构说明  : PERRSTSTAT4 寄存器结构定义。地址偏移量:0x098，初值:0x003F41E1，宽度:32
 寄存器说明: 外设软复位状态寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dbgsechsic_subsys_crg : 1;  /* bit[0] : IP软复位使能状态：
                                                                     0：IP处于复位撤离状态；
                                                                     1：IP处于软复位使能状态。 */
        unsigned int  reserved_0                   : 1;  /* bit[1] : 保留。 */
        unsigned int  reserved_1                   : 1;  /* bit[2] : 保留。 */
        unsigned int  ip_rst_usb3otgphy_por        : 1;  /* bit[3] :  */
        unsigned int  reserved_2                   : 1;  /* bit[4] : 保留。 */
        unsigned int  ip_rst_usb3otg               : 1;  /* bit[5] : 上电默认处于复位状态。 */
        unsigned int  ip_rst_usb3otg_32k           : 1;  /* bit[6] : 上电默认处于复位状态。 */
        unsigned int  ip_rst_usb3otg_ahbif         : 1;  /* bit[7] : 上电默认处于复位状态。 */
        unsigned int  ip_rst_usb3otg_mux           : 1;  /* bit[8] : 上电默认处于复位状态。 */
        unsigned int  reserved_3                   : 1;  /* bit[9] : 保留。 */
        unsigned int  reserved_4                   : 1;  /* bit[10]: 保留。 */
        unsigned int  reserved_5                   : 1;  /* bit[11]: 保留。 */
        unsigned int  reserved_6                   : 1;  /* bit[12]: 保留。 */
        unsigned int  reserved_7                   : 1;  /* bit[13]: 保留。 */
        unsigned int  reserved_8                   : 1;  /* bit[14]: 保留。 */
        unsigned int  ip_rst_secp                  : 1;  /* bit[15]:  */
        unsigned int  ip_rst_emmc0                 : 1;  /* bit[16]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_emmc1                 : 1;  /* bit[17]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_sd                    : 1;  /* bit[18]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_sdio0                 : 1;  /* bit[19]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_sdio1                 : 1;  /* bit[20]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_cci400                : 1;  /* bit[21]: 上电默认处于复位状态。 */
        unsigned int  ip_rst_emmc0_m               : 1;  /* bit[22]:  */
        unsigned int  ip_rst_emmc1_m               : 1;  /* bit[23]:  */
        unsigned int  ip_rst_sd_m                  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_sdio0_m               : 1;  /* bit[25]:  */
        unsigned int  ip_rst_sdio1_m               : 1;  /* bit[26]:  */
        unsigned int  reserved_9                   : 1;  /* bit[27]:  */
        unsigned int  ip_rst_lpmcu                 : 1;  /* bit[28]: LPM3子系统上电默认处于复位撤离状态。 */
        unsigned int  ip_rst_sysbus2hkmem          : 1;  /* bit[29]:  */
        unsigned int  reserved_10                  : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_11                  : 1;  /* bit[31]: IP软复位使能状态：
                                                                     0：IP处于复位撤离状态；
                                                                     1：IP处于软复位使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT4_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_dbgsechsic_subsys_crg_START  (0)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_dbgsechsic_subsys_crg_END    (0)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otgphy_por_START         (3)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otgphy_por_END           (3)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_START                (5)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_END                  (5)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_32k_START            (6)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_32k_END              (6)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_ahbif_START          (7)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_ahbif_END            (7)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_mux_START            (8)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_mux_END              (8)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_secp_START                   (15)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_secp_END                     (15)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_START                  (16)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_END                    (16)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_START                  (17)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_END                    (17)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_START                     (18)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_END                       (18)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_START                  (19)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_END                    (19)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_START                  (20)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_END                    (20)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_cci400_START                 (21)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_cci400_END                   (21)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_m_START                (22)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_m_END                  (22)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_m_START                (23)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_m_END                  (23)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_m_START                   (24)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_m_END                     (24)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_m_START                (25)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_m_END                  (25)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_m_START                (26)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_m_END                  (26)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_lpmcu_START                  (28)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_lpmcu_END                    (28)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sysbus2hkmem_START           (29)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sysbus2hkmem_END             (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTEN5_UNION
 结构说明  : PERRSTEN5 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位使能寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: IP软复位使能：
                                                   0：IP软复位使能状态不变；
                                                   1：IP软复位使能。 */
    } reg;
} SOC_CRGPERIPH_PERRSTEN5_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTDIS5_UNION
 结构说明  : PERRSTDIS5 寄存器结构定义。地址偏移量:0x0A0，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位撤离寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: IP软复位撤离：
                                                   0：IP软复位使能状态不变；
                                                   1：IP软复位撤离。 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS5_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERRSTSTAT5_UNION
 结构说明  : PERRSTSTAT5 寄存器结构定义。地址偏移量:0x0A4，初值:0x00000000，宽度:32
 寄存器说明: 外设软复位状态寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: IP软复位使能状态：
                                                   0：IP处于复位撤离状态；
                                                   1：IP处于软复位使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT5_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV0_UNION
 结构说明  : CLKDIV0 寄存器结构定义。地址偏移量:0x0A8，初值:0x00000CE5，宽度:32
 寄存器说明: 时钟分频比控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_sysbus        : 5;  /* bit[0-4]  : SYSBUS总线时钟分频比。（可选PPLL0\PPLL1分频，控制见sel_sysbus）
                                                                5'h0:1；
                                                                5'h1:2；
                                                                5'h2:3；
                                                                …
                                                                5'h1E:31；
                                                                5'h1F:32； */
        unsigned int  sc_div_lpmcu         : 5;  /* bit[5-9]  : LPMCU总线时钟分频比。（可选PPLL0\PPLL1分频，控制见sel_lpmcu）
                                                                5'h0:1；
                                                                5'h1:2；
                                                                5'h2:3；
                                                                …
                                                                5'h1E:31；
                                                                5'h1F:32； */
        unsigned int  sc_div_ivp32dsp_core : 4;  /* bit[10-13]: IVP32DSP CORE时钟分频比。（可选PPLL0\PPLL1\PPLL2\PPLL3分频，控制见sel_ivp32dsp_core）
                                                                4'h0:1；
                                                                4'h1:2；
                                                                4'h2:3；
                                                                …
                                                                4'hE:15；
                                                                4'hF:16； */
        unsigned int  sel_ivp32dsp_core    : 2;  /* bit[14-15]: IVP32DSP CORE时钟源选择。（可选PPLL0\PPLL1\PPLL2\PPLL3）
                                                                00:PPLL0；
                                                                01:PPLL1；
                                                                10:PPLL2；
                                                                11:PPLL3; */
        unsigned int  clkdivmasken         : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV0_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV0_sc_div_sysbus_START         (0)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_sysbus_END           (4)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_lpmcu_START          (5)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_lpmcu_END            (9)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_ivp32dsp_core_START  (10)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_ivp32dsp_core_END    (13)
#define SOC_CRGPERIPH_CLKDIV0_sel_ivp32dsp_core_START     (14)
#define SOC_CRGPERIPH_CLKDIV0_sel_ivp32dsp_core_END       (15)
#define SOC_CRGPERIPH_CLKDIV0_clkdivmasken_START          (16)
#define SOC_CRGPERIPH_CLKDIV0_clkdivmasken_END            (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV1_UNION
 结构说明  : CLKDIV1 寄存器结构定义。地址偏移量:0x0AC，初值:0x00002000，宽度:32
 寄存器说明: 时钟分频比控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_sysbus            : 1;  /* bit[0]    : SYSBUS PLL源选择。
                                                                 0：PPLL1；
                                                                 1：PPLL0。 */
        unsigned int  sel_lpmcu             : 1;  /* bit[1]    : LPMCU PLL源选择。
                                                                 0：PPLL1；
                                                                 1：PPLL0。 */
        unsigned int  sel_uartl             : 1;  /* bit[2]    : UART0/UART2/UART5工作时钟源选择：
                                                                 0：19.2MHz时钟；
                                                                 1：从clk_a53hpm(480MHz时钟分频产生)。 */
        unsigned int  sel_uarth             : 1;  /* bit[3]    : UART1/UART4工作时钟源选择：
                                                                 0：19.2MHz时钟；
                                                                 1：从clk_a53hpm(480MHz时钟分频产生)。 */
        unsigned int  reserved_0            : 1;  /* bit[4]    : 保留。 */
        unsigned int  reserved_1            : 1;  /* bit[5]    : 保留。 */
        unsigned int  reserved_2            : 1;  /* bit[6]    : 保留。 */
        unsigned int  reserved_3            : 1;  /* bit[7]    : 保留。 */
        unsigned int  sel_spi               : 1;  /* bit[8]    : SPI1工作时钟源选择：
                                                                 0：19.2MHz时钟；
                                                                 1：从clk_a53hpm(480MHz时钟分频产生)。 */
        unsigned int  lpmcu_clk_sw_req_cfg  : 2;  /* bit[9-10] : 系统工作在NORMAL模式时，软件控制LPMCU时钟切换配置，实际配置低bit有效：
                                                                 2'bx1:LPMCU时钟切换至19.2MHz晶振时钟；
                                                                 2'bx0:LPMCU时钟源为PLL时钟； */
        unsigned int  reserved_4            : 1;  /* bit[11]   : 保留。 */
        unsigned int  reserved_5            : 1;  /* bit[12]   : 保留。 */
        unsigned int  sel_i2c               : 1;  /* bit[13]   : I2C3/I2C4工作时钟源选择：
                                                                 0：19.2MHz时钟；
                                                                 1：从clk_a53hpm(480MHz时钟分频产生)。 */
        unsigned int  sysbus_clk_sw_req_cfg : 2;  /* bit[14-15]: 系统工作在NORMAL模式时，软件控制sysbus时钟切换配置，实际配置低bit有效：
                                                                 2'bx1:sysbus时钟切换至19.2MHz晶振时钟；
                                                                 2'bx0:sysbus时钟源为PLL时钟； */
        unsigned int  clkdivmasken          : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                 只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV1_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV1_sel_sysbus_START             (0)
#define SOC_CRGPERIPH_CLKDIV1_sel_sysbus_END               (0)
#define SOC_CRGPERIPH_CLKDIV1_sel_lpmcu_START              (1)
#define SOC_CRGPERIPH_CLKDIV1_sel_lpmcu_END                (1)
#define SOC_CRGPERIPH_CLKDIV1_sel_uartl_START              (2)
#define SOC_CRGPERIPH_CLKDIV1_sel_uartl_END                (2)
#define SOC_CRGPERIPH_CLKDIV1_sel_uarth_START              (3)
#define SOC_CRGPERIPH_CLKDIV1_sel_uarth_END                (3)
#define SOC_CRGPERIPH_CLKDIV1_sel_spi_START                (8)
#define SOC_CRGPERIPH_CLKDIV1_sel_spi_END                  (8)
#define SOC_CRGPERIPH_CLKDIV1_lpmcu_clk_sw_req_cfg_START   (9)
#define SOC_CRGPERIPH_CLKDIV1_lpmcu_clk_sw_req_cfg_END     (10)
#define SOC_CRGPERIPH_CLKDIV1_sel_i2c_START                (13)
#define SOC_CRGPERIPH_CLKDIV1_sel_i2c_END                  (13)
#define SOC_CRGPERIPH_CLKDIV1_sysbus_clk_sw_req_cfg_START  (14)
#define SOC_CRGPERIPH_CLKDIV1_sysbus_clk_sw_req_cfg_END    (15)
#define SOC_CRGPERIPH_CLKDIV1_clkdivmasken_START           (16)
#define SOC_CRGPERIPH_CLKDIV1_clkdivmasken_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV2_UNION
 结构说明  : CLKDIV2 寄存器结构定义。地址偏移量:0x0B0，初值:0x00002200，宽度:32
 寄存器说明: 时钟分频比控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 7;  /* bit[0-6]  : 保留。 */
        unsigned int  sc_div_uarth : 4;  /* bit[7-10] : uart1\uart4时钟分频比选择。(从clk_a53hpm 480MHz时钟分频产生)
                                                        4'h0:1；
                                                        4'h1:2；
                                                        4'h2:3；
                                                        …
                                                        4'hE:15；
                                                        4'hF:16； */
        unsigned int  sc_div_uartl : 4;  /* bit[11-14]: uart0\uart2\uaart5时钟分频比选择。(从clk_a53hpm 480MHz时钟分频产生)
                                                        4'h0:1；
                                                        4'h1:2；
                                                        4'h2:3；
                                                        …
                                                        4'hE:15；
                                                        4'hF:16； */
        unsigned int  reserved_1   : 1;  /* bit[15]   : 保留。 */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV2_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uarth_START  (7)
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uarth_END    (10)
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uartl_START  (11)
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uartl_END    (14)
#define SOC_CRGPERIPH_CLKDIV2_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV2_clkdivmasken_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV3_UNION
 结构说明  : CLKDIV3 寄存器结构定义。地址偏移量:0x0B4，初值:0x00000038，宽度:32
 寄存器说明: 时钟分频比控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_sel_emmc  : 3;  /* bit[0-2]  : EMMC0/EMMC1时钟源选择。
                                                        0xx:3.2M；
                                                        1x0:PPLL0；
                                                        1x1:PPLL3； */
        unsigned int  sc_div_emmc  : 4;  /* bit[3-6]  : EMMC0/EMMC1时钟分频比选择。
                                                        4'h0:1；
                                                        4'h1:2；
                                                        4'h2:3；
                                                        …
                                                        4'hE:15；
                                                        4'hF:16； */
        unsigned int  reserved     : 7;  /* bit[7-13] : 保留。 */
        unsigned int  sc_div_ldi0  : 2;  /* bit[14-15]: LDI0时钟的PLL时钟源选择的高2bit */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV3_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV3_sc_sel_emmc_START   (0)
#define SOC_CRGPERIPH_CLKDIV3_sc_sel_emmc_END     (2)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_emmc_START   (3)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_emmc_END     (6)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_ldi0_START   (14)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_ldi0_END     (15)
#define SOC_CRGPERIPH_CLKDIV3_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV3_clkdivmasken_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV4_UNION
 结构说明  : CLKDIV4 寄存器结构定义。地址偏移量:0x0B8，初值:0x00000306，宽度:32
 寄存器说明: 时钟分频比控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_sd    : 4;  /* bit[0-3]  : SD时钟分频比选择。
                                                        4'h0:1；
                                                        4'h1:2；
                                                        4'h2:3；
                                                        …
                                                        4'hE:15；
                                                        4'hF:16； */
        unsigned int  sc_sel_sd    : 3;  /* bit[4-6]  : SD时钟源选择。
                                                        0xx:3.2M；
                                                        100:PPLL0；
                                                        101:PPLL1；
                                                        11x:PPLL3; */
        unsigned int  sc_div_sdio0 : 4;  /* bit[7-10] : SDIO0时钟分频比选择。
                                                        4'h0:1；
                                                        4'h1:2；
                                                        4'h2:3；
                                                        …
                                                        4'hE:15；
                                                        4'hF:16； */
        unsigned int  sc_sel_sdio0 : 3;  /* bit[11-13]: SDIO0时钟源选择。
                                                        0xx:3.2M；
                                                        100:PPLL0；
                                                        101:PPLL1；
                                                        11x:PPLL3; */
        unsigned int  sc_div_ldi1  : 2;  /* bit[14-15]: LDI1时钟的PLL时钟源选择的高2bit */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV4_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sd_START     (0)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sd_END       (3)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sd_START     (4)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sd_END       (6)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sdio0_START  (7)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sdio0_END    (10)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sdio0_START  (11)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sdio0_END    (13)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_ldi1_START   (14)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_ldi1_END     (15)
#define SOC_CRGPERIPH_CLKDIV4_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV4_clkdivmasken_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV5_UNION
 结构说明  : CLKDIV5 寄存器结构定义。地址偏移量:0x0BC，初值:0x00004303，宽度:32
 寄存器说明: 时钟分频比控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_edc0  : 6;  /* bit[0-5]  : EDC0时钟分频比选择。
                                                        6'h0:1；
                                                        6'h1:2；
                                                        6'h2:3；
                                                        …
                                                        6'h3E:63；
                                                        6'h3F:64； */
        unsigned int  sel_edc0_pll : 2;  /* bit[6-7]  : EDC0的PLL时钟源选择：
                                                        2'b00:PPLL0；
                                                        2'b01:PPLL1；
                                                        2'b10:PPLL2；
                                                        2'b11:PPLL3； */
        unsigned int  sc_div_ldi0  : 6;  /* bit[8-13] : LDI0时钟分频比选择。
                                                        6'h0:1；
                                                        6'h1:2；
                                                        6'h2:3；
                                                        …
                                                        6'h3E:63；
                                                        6'h3F:64； */
        unsigned int  sel_ldi0_pll : 2;  /* bit[14-15]: LDI0时钟的PLL时钟源选择的低2bit，高2bit见CLKDIV3[15:14]：
                                                        4'b0001:PPLL0；
                                                        4'b0010:PPLL2；
                                                        4'b0100:PPLL1；
                                                        4'b1000:PPLL3；
                                                        其他值无效。 */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV5_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV5_sc_div_edc0_START   (0)
#define SOC_CRGPERIPH_CLKDIV5_sc_div_edc0_END     (5)
#define SOC_CRGPERIPH_CLKDIV5_sel_edc0_pll_START  (6)
#define SOC_CRGPERIPH_CLKDIV5_sel_edc0_pll_END    (7)
#define SOC_CRGPERIPH_CLKDIV5_sc_div_ldi0_START   (8)
#define SOC_CRGPERIPH_CLKDIV5_sc_div_ldi0_END     (13)
#define SOC_CRGPERIPH_CLKDIV5_sel_ldi0_pll_START  (14)
#define SOC_CRGPERIPH_CLKDIV5_sel_ldi0_pll_END    (15)
#define SOC_CRGPERIPH_CLKDIV5_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV5_clkdivmasken_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV6_UNION
 结构说明  : CLKDIV6 寄存器结构定义。地址偏移量:0x0C0，初值:0x00004406，宽度:32
 寄存器说明: 时钟分频比控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_sdio1 : 4;  /* bit[0-3]  : SDIO1时钟分频比选择。
                                                        4'h0:1；
                                                        4'h1:2；
                                                        4'h2:3；
                                                        …
                                                        4'hE:15；
                                                        4'hF:16； */
        unsigned int  sc_sel_sdio1 : 3;  /* bit[4-6]  : SDIO1时钟源选择。
                                                        0xx:3.2M；
                                                        100:PPLL0；
                                                        101:PPLL1；
                                                        11x:PPLL3; */
        unsigned int  reserved     : 1;  /* bit[7]    : 保留。 */
        unsigned int  sc_div_ldi1  : 6;  /* bit[8-13] : LDI1时钟分频比选择。
                                                        6'h0:1；
                                                        6'h1:2；
                                                        6'h2:3；
                                                        …
                                                        6'h3E:63；
                                                        6'h3F:64； */
        unsigned int  sel_ldi1_pll : 2;  /* bit[14-15]: LDI1时钟的PLL时钟源选择的低2bit，高2bit见CLKDIV4[15:14]：
                                                        4'b0001:PPLL0；
                                                        4'b0010:PPLL2；
                                                        4'b0100:PPLL1；
                                                        4'b1000:PPLL3；
                                                        其他值无效。 */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV6_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV6_sc_div_sdio1_START  (0)
#define SOC_CRGPERIPH_CLKDIV6_sc_div_sdio1_END    (3)
#define SOC_CRGPERIPH_CLKDIV6_sc_sel_sdio1_START  (4)
#define SOC_CRGPERIPH_CLKDIV6_sc_sel_sdio1_END    (6)
#define SOC_CRGPERIPH_CLKDIV6_sc_div_ldi1_START   (8)
#define SOC_CRGPERIPH_CLKDIV6_sc_div_ldi1_END     (13)
#define SOC_CRGPERIPH_CLKDIV6_sel_ldi1_pll_START  (14)
#define SOC_CRGPERIPH_CLKDIV6_sel_ldi1_pll_END    (15)
#define SOC_CRGPERIPH_CLKDIV6_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV6_clkdivmasken_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV7_UNION
 结构说明  : CLKDIV7 寄存器结构定义。地址偏移量:0x0C4，初值:0x00005043，宽度:32
 寄存器说明: 时钟分频比控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_ispfunc1              : 5;  /* bit[0-4]  : ISPFUNC1 时钟分频比：
                                                                        5'h0:1；
                                                                        5'h1:2；
                                                                        5'h2:3；
                                                                        …
                                                                        5'h1E:31；
                                                                        5'h1F:32； */
        unsigned int  sel_ispfunc1                 : 2;  /* bit[5-6]  : ISPFUNC1 PLL时钟源选择：
                                                                        2'h00：PPLL0；
                                                                        2'h01：PPLL1；
                                                                        2'h1x：PPLL3； */
        unsigned int  sc_isp_func_clk_sel_ispfunc1 : 1;  /* bit[7]    : ISPFUNC 时钟源选择：
                                                                        1'h0：clk_ispfunc2；
                                                                        1'h1：clk_ispfunc1； */
        unsigned int  sc_sel_clk_rxdpbhy_cfg       : 1;  /* bit[8]    : RXDPHYCFG 时钟源选择：
                                                                        1'h0：clk_rxdphy_fix_div；
                                                                        1'h1：clk_sys； */
        unsigned int  reserved                     : 3;  /* bit[9-11] :  */
        unsigned int  div_clk_spi                  : 4;  /* bit[12-15]: SPI时钟分频比（源时钟是clk_a53hpm_div(默认480M，可单独配置分频比)）：
                                                                        4'h0:1；
                                                                        4'h1:2；
                                                                        4'h2:3；
                                                                        …
                                                                        4'hE:15；
                                                                        4'hF:16； */
        unsigned int  clkdivmasken                 : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV7_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV7_sc_div_ispfunc1_START               (0)
#define SOC_CRGPERIPH_CLKDIV7_sc_div_ispfunc1_END                 (4)
#define SOC_CRGPERIPH_CLKDIV7_sel_ispfunc1_START                  (5)
#define SOC_CRGPERIPH_CLKDIV7_sel_ispfunc1_END                    (6)
#define SOC_CRGPERIPH_CLKDIV7_sc_isp_func_clk_sel_ispfunc1_START  (7)
#define SOC_CRGPERIPH_CLKDIV7_sc_isp_func_clk_sel_ispfunc1_END    (7)
#define SOC_CRGPERIPH_CLKDIV7_sc_sel_clk_rxdpbhy_cfg_START        (8)
#define SOC_CRGPERIPH_CLKDIV7_sc_sel_clk_rxdpbhy_cfg_END          (8)
#define SOC_CRGPERIPH_CLKDIV7_div_clk_spi_START                   (12)
#define SOC_CRGPERIPH_CLKDIV7_div_clk_spi_END                     (15)
#define SOC_CRGPERIPH_CLKDIV7_clkdivmasken_START                  (16)
#define SOC_CRGPERIPH_CLKDIV7_clkdivmasken_END                    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV8_UNION
 结构说明  : CLKDIV8 寄存器结构定义。地址偏移量:0x0C8，初值:0x000010C3，宽度:32
 寄存器说明: 时钟分频比控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_ispfunc2 : 5;  /* bit[0-4]  : ISPFUNC2 时钟分频比：
                                                           5'h0:1；
                                                           5'h1:2；
                                                           5'h2:3；
                                                           …
                                                           5'h1E:31；
                                                           5'h1F:32； */
        unsigned int  sel_ispfunc2    : 1;  /* bit[5]    : ISPFUNC2 PLL时钟源选择：
                                                           0：PPLL0；
                                                           1：PPLL1。 */
        unsigned int  sc_div_venc     : 5;  /* bit[6-10] : VENC时钟分频比：
                                                           5'h0:1；
                                                           5'h1:2；
                                                           5'h2:3；
                                                           …
                                                           5'h1E:31；
                                                           5'h1F:32； */
        unsigned int  sel_venc        : 2;  /* bit[11-12]: VENC PLL时钟源选择：
                                                           2'b00：PPLL0；
                                                           2'b01：PPLL1；
                                                           2'b1x：PPLL3。 */
        unsigned int  reserved        : 3;  /* bit[13-15]: 保留。 */
        unsigned int  clkdivmasken    : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                           只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV8_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV8_sc_div_ispfunc2_START  (0)
#define SOC_CRGPERIPH_CLKDIV8_sc_div_ispfunc2_END    (4)
#define SOC_CRGPERIPH_CLKDIV8_sel_ispfunc2_START     (5)
#define SOC_CRGPERIPH_CLKDIV8_sel_ispfunc2_END       (5)
#define SOC_CRGPERIPH_CLKDIV8_sc_div_venc_START      (6)
#define SOC_CRGPERIPH_CLKDIV8_sc_div_venc_END        (10)
#define SOC_CRGPERIPH_CLKDIV8_sel_venc_START         (11)
#define SOC_CRGPERIPH_CLKDIV8_sel_venc_END           (12)
#define SOC_CRGPERIPH_CLKDIV8_clkdivmasken_START     (16)
#define SOC_CRGPERIPH_CLKDIV8_clkdivmasken_END       (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV9_UNION
 结构说明  : CLKDIV9 寄存器结构定义。地址偏移量:0x0CC，初值:0x00000043，宽度:32
 寄存器说明: 时钟分频比控制寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_vdec  : 5;  /* bit[0-4]  : VDEC时钟分频比选择。
                                                        5'h0:1；
                                                        5'h1:2；
                                                        5'h2:3；
                                                        …
                                                        5'h1E:31；
                                                        5'h1F:32； */
        unsigned int  sel_vdec     : 2;  /* bit[5-6]  : VDEC PLL时钟源选择：
                                                        2'b00：PPLL0；
                                                        2'b01：PPLL1；
                                                        2'b10：PPLL2；
                                                        2'b11：PPLL3。 */
        unsigned int  reserved     : 9;  /* bit[7-15] : 保留。 */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV9_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV9_sc_div_vdec_START   (0)
#define SOC_CRGPERIPH_CLKDIV9_sc_div_vdec_END     (4)
#define SOC_CRGPERIPH_CLKDIV9_sel_vdec_START      (5)
#define SOC_CRGPERIPH_CLKDIV9_sel_vdec_END        (6)
#define SOC_CRGPERIPH_CLKDIV9_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV9_clkdivmasken_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV10_UNION
 结构说明  : CLKDIV10 寄存器结构定义。地址偏移量:0x0D0，初值:0x0000E142，宽度:32
 寄存器说明: 时钟分频比控制寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_vcodecbus : 5;  /* bit[0-4]  : VCODECBUS 时钟分频比：
                                                            5'h0:1；
                                                            5'h1:2；
                                                            …
                                                            5'h1E:31；
                                                            5'h1F:32； */
        unsigned int  sc_sel_vcodecbus : 2;  /* bit[5-6]  : VCODECBUS PLL时钟源选择：
                                                            2'b00:PPLL0；
                                                            2'b01:PPLL1；
                                                            2'b10:PPLL2；
                                                            2'b11:PPLL3； */
        unsigned int  sc_div_vivobus   : 5;  /* bit[7-11] : VIVOBUS 时钟分频比：
                                                            5'h0:1；
                                                            5'h1:2；
                                                            …
                                                            5'h1E:31；
                                                            5'h1F:32； */
        unsigned int  sc_sel_vivobus   : 2;  /* bit[12-13]: VIVOBUS PLL时钟源选择：
                                                            2'b00:PPLL0；
                                                            2'b01:PPLL1；
                                                            2'b10:PPLL2；
                                                            2'b11:PPLL3； */
        unsigned int  sc_div_perf_stat : 2;  /* bit[14-15]: CLK_PERF_STAT 时钟分频比：
                                                            2'h0:1；
                                                            2'h1:2；
                                                            2'h2:3；
                                                            2'h3:4； */
        unsigned int  clkdivmasken     : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                            只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV10_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vcodecbus_START  (0)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vcodecbus_END    (4)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vcodecbus_START  (5)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vcodecbus_END    (6)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vivobus_START    (7)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vivobus_END      (11)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vivobus_START    (12)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vivobus_END      (13)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_perf_stat_START  (14)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_perf_stat_END    (15)
#define SOC_CRGPERIPH_CLKDIV10_clkdivmasken_START      (16)
#define SOC_CRGPERIPH_CLKDIV10_clkdivmasken_END        (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV11_UNION
 结构说明  : CLKDIV11 寄存器结构定义。地址偏移量:0x0D4，初值:0x00000141，宽度:32
 寄存器说明: 时钟分频比控制寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_ispa7  : 5;  /* bit[0-4]  : ISPA7 时钟分频比：
                                                         5'h0:1；
                                                         5'h1:2；
                                                         5'h2:3；
                                                         …
                                                         5'h1E:31；
                                                         5'h1F:32； */
        unsigned int  sel_ispa7     : 2;  /* bit[5-6]  : ISPA7 PLL时钟源选择：
                                                         2'b00:PPLL0；
                                                         2'b01:PPLL1；
                                                         2'b1x:PPLL3； */
        unsigned int  sc_div_a53hpm : 2;  /* bit[7-8]  : A53HPM时钟分频比：
                                                         2'h0:1；
                                                         2'h1:2；
                                                         2'h2:3；
                                                         2'h3:4； */
        unsigned int  sel_a53hpm    : 1;  /* bit[9]    : A53HPM PLL时钟源选择：
                                                         0：PPLL0；
                                                         1：PPLL1。 */
        unsigned int  reserved      : 6;  /* bit[10-15]: 保留。 */
        unsigned int  clkdivmasken  : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                         只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV11_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV11_sc_div_ispa7_START   (0)
#define SOC_CRGPERIPH_CLKDIV11_sc_div_ispa7_END     (4)
#define SOC_CRGPERIPH_CLKDIV11_sel_ispa7_START      (5)
#define SOC_CRGPERIPH_CLKDIV11_sel_ispa7_END        (6)
#define SOC_CRGPERIPH_CLKDIV11_sc_div_a53hpm_START  (7)
#define SOC_CRGPERIPH_CLKDIV11_sc_div_a53hpm_END    (8)
#define SOC_CRGPERIPH_CLKDIV11_sel_a53hpm_START     (9)
#define SOC_CRGPERIPH_CLKDIV11_sel_a53hpm_END       (9)
#define SOC_CRGPERIPH_CLKDIV11_clkdivmasken_START   (16)
#define SOC_CRGPERIPH_CLKDIV11_clkdivmasken_END     (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV12_UNION
 结构说明  : CLKDIV12 寄存器结构定义。地址偏移量:0x0D8，初值:0x000007E0，宽度:32
 寄存器说明: 时钟分频比控制寄存器12。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_modem_bbe16 : 2;  /* bit[0-1]  : MODEM BBE16 PLL时钟源选择的高2bit */
        unsigned int  sc_div_modem_mcpu  : 2;  /* bit[2-3]  : MODEM MCPU PLL时钟源选择的高2bit */
        unsigned int  reserved_0         : 1;  /* bit[4]    : 保留。 */
        unsigned int  sc_div_slimbus     : 6;  /* bit[5-10] : SLIMBUS时钟分频比(（源时钟是PPLL1/2/3)：
                                                              6'h0:1；
                                                              6'h1:2；
                                                              6'h2:3；
                                                              …
                                                              6'h3E:63；
                                                              6'h3F:64； */
        unsigned int  sc_sel_slimbus     : 2;  /* bit[11-12]: SLIMBUS时钟源选择：
                                                              2'b00:PPLL1；
                                                              2'b01:PPLL2；
                                                              2'b1x:PPLL3； */
        unsigned int  reserved_1         : 3;  /* bit[13-15]: 保留。 */
        unsigned int  clkdivmasken       : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                              只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV12_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_bbe16_START  (0)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_bbe16_END    (1)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_mcpu_START   (2)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_mcpu_END     (3)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_slimbus_START      (5)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_slimbus_END        (10)
#define SOC_CRGPERIPH_CLKDIV12_sc_sel_slimbus_START      (11)
#define SOC_CRGPERIPH_CLKDIV12_sc_sel_slimbus_END        (12)
#define SOC_CRGPERIPH_CLKDIV12_clkdivmasken_START        (16)
#define SOC_CRGPERIPH_CLKDIV12_clkdivmasken_END          (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV13_UNION
 结构说明  : CLKDIV13 寄存器结构定义。地址偏移量:0x0DC，初值:0x00003420，宽度:32
 寄存器说明: 时钟分频比控制寄存器13。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_modem_bbe16 : 4;  /* bit[0-3]  : MODEM BBE16时钟分频比选择：
                                                           4'h0:1；
                                                           4'h1:2；
                                                           4'h2:3；
                                                           …
                                                           4'hE:15；
                                                           4'hF:16； */
        unsigned int  sel_modem_bbe16 : 2;  /* bit[4-5]  : MODEM BBE16 PLL时钟源选择的低2bit，高2bit见CLKDIV12[1:0]：
                                                           4'b0001：PPLL4；
                                                           4'b0010：PPLL5；
                                                           4'b0100：PPLL0；
                                                           4'b1000：PPLL3。
                                                           其他值无效。 */
        unsigned int  div_modem_mcpu  : 4;  /* bit[6-9]  : MODEM MCPU时钟分频比选择：
                                                           4'h0:1；
                                                           4'h1:2；
                                                           4'h2:3；
                                                           …
                                                           4'hE:15；
                                                           4'hF:16； */
        unsigned int  sel_modem_mcpu  : 2;  /* bit[10-11]: MODEM MCPU PLL时钟源选择的低2bit，高2bit见CLKDIV12[3:2]：
                                                           4'b0001：PPLL4；
                                                           4'b0010：PPLL5；
                                                           4'b0100：PPLL0；
                                                           4'b1000：PPLL3。
                                                           其他值无效。 */
        unsigned int  div_ptp         : 4;  /* bit[12-15]: PWM/TIMER/PCTRL PCLK时钟分频比选择：
                                                           4'h0:1；
                                                           4'h1:2；
                                                           4'h2:3；
                                                           …
                                                           4'hE:15；
                                                           4'hF:16； */
        unsigned int  clkdivmasken    : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                           只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV13_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV13_div_modem_bbe16_START  (0)
#define SOC_CRGPERIPH_CLKDIV13_div_modem_bbe16_END    (3)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_bbe16_START  (4)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_bbe16_END    (5)
#define SOC_CRGPERIPH_CLKDIV13_div_modem_mcpu_START   (6)
#define SOC_CRGPERIPH_CLKDIV13_div_modem_mcpu_END     (9)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_mcpu_START   (10)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_mcpu_END     (11)
#define SOC_CRGPERIPH_CLKDIV13_div_ptp_START          (12)
#define SOC_CRGPERIPH_CLKDIV13_div_ptp_END            (15)
#define SOC_CRGPERIPH_CLKDIV13_clkdivmasken_START     (16)
#define SOC_CRGPERIPH_CLKDIV13_clkdivmasken_END       (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV14_UNION
 结构说明  : CLKDIV14 寄存器结构定义。地址偏移量:0x0E0，初值:0x0000EBA0，宽度:32
 寄存器说明: 时钟分频比控制寄存器14。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_sel_clk_usb3phy_ref : 1;  /* bit[0]    : PERI_CRG 送给USB3PHY 参考时钟的时钟源选择：
                                                                  0:19.2M clk_usb3phy_ref;
                                                                  1:PLL0 clk_usb2phy_pll */
        unsigned int  reserved               : 3;  /* bit[1-3]  : 保留。 */
        unsigned int  div_clkout0_pll        : 6;  /* bit[4-9]  : clkout0 PLL时钟分频比选择：(源时钟为PPLL3)
                                                                  6'h0:1；
                                                                  6'h1:2；
                                                                  6'h2:3；
                                                                  …
                                                                  6'h3E:63；
                                                                  6'h3F:64； */
        unsigned int  div_clkout1_pll        : 6;  /* bit[10-15]: clkout1 PLL时钟分频比选择：(源时钟为PPLL3)
                                                                  6'h0:1；
                                                                  6'h1:2；
                                                                  6'h2:3；
                                                                  …
                                                                  6'h3E:63；
                                                                  6'h3F:64； */
        unsigned int  clkdivmasken           : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                  只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV14_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV14_sc_sel_clk_usb3phy_ref_START  (0)
#define SOC_CRGPERIPH_CLKDIV14_sc_sel_clk_usb3phy_ref_END    (0)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout0_pll_START         (4)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout0_pll_END           (9)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout1_pll_START         (10)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout1_pll_END           (15)
#define SOC_CRGPERIPH_CLKDIV14_clkdivmasken_START            (16)
#define SOC_CRGPERIPH_CLKDIV14_clkdivmasken_END              (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV15_UNION
 结构说明  : CLKDIV15 寄存器结构定义。地址偏移量:0x0E4，初值:0x00000000，宽度:32
 寄存器说明: 时钟分频比控制寄存器15。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_avstrig  : 16; /* bit[0-15] : AVS触发信号的分频比配置的低16位（源时钟是睡眠时钟） */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV15_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV15_div_avstrig_START   (0)
#define SOC_CRGPERIPH_CLKDIV15_div_avstrig_END     (15)
#define SOC_CRGPERIPH_CLKDIV15_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV15_clkdivmasken_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV16_UNION
 结构说明  : CLKDIV16 寄存器结构定义。地址偏移量:0x0E8，初值:0x00000130，宽度:32
 寄存器说明: 时钟分频比控制寄存器16。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_avstrig         : 4;  /* bit[0-3]  : AVS触发信号的分频比配置的高4位（源时钟是睡眠时钟） */
        unsigned int  sc_div_i2c          : 4;  /* bit[4-7]  : I2C3\I2C4时钟分频比选择：（源时钟是clk_a53hpm_div(默认480M，可单独配置分频比)）
                                                               4'h0:1；
                                                               4'h1:2；
                                                               4'h2:3；
                                                               …
                                                               4'hE:15；
                                                               4'hF:16； */
        unsigned int  ddrcpll_sw          : 4;  /* bit[8-11] : DDRC时钟选择哪个PLL：
                                                               0001:PPLL0;
                                                               0010:PPLL1;
                                                               0100:PPLl2;
                                                               1000:PPLL3; */
        unsigned int  ddrc_clk_sw_req_cfg : 2;  /* bit[12-13]: 系统工作在NORMAL模式时，软件控制DDRC时钟切换配置，实际配置低bit有效：
                                                               2'bx1:DDRC时钟切换至19.2MHz晶振时钟；
                                                               2'bx0:DDRC时钟源为PLL时钟； */
        unsigned int  reserved            : 2;  /* bit[14-15]: 保留。 */
        unsigned int  clkdivmasken        : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                               只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV16_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV16_div_avstrig_START          (0)
#define SOC_CRGPERIPH_CLKDIV16_div_avstrig_END            (3)
#define SOC_CRGPERIPH_CLKDIV16_sc_div_i2c_START           (4)
#define SOC_CRGPERIPH_CLKDIV16_sc_div_i2c_END             (7)
#define SOC_CRGPERIPH_CLKDIV16_ddrcpll_sw_START           (8)
#define SOC_CRGPERIPH_CLKDIV16_ddrcpll_sw_END             (11)
#define SOC_CRGPERIPH_CLKDIV16_ddrc_clk_sw_req_cfg_START  (12)
#define SOC_CRGPERIPH_CLKDIV16_ddrc_clk_sw_req_cfg_END    (13)
#define SOC_CRGPERIPH_CLKDIV16_clkdivmasken_START         (16)
#define SOC_CRGPERIPH_CLKDIV16_clkdivmasken_END           (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV17_UNION
 结构说明  : CLKDIV17 寄存器结构定义。地址偏移量:0x0EC，初值:0x0000B42D，宽度:32
 寄存器说明: 时钟分频比控制寄存器17。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_cfgbus         : 2;  /* bit[0-1]  : config BUS时钟分频比。(源时钟是clk_sysbus，默认240MHz，分频单独可配)
                                                                 2'h0:1；
                                                                 2'h1:2；
                                                                 2'h2:3；
                                                                 2'h3:4； */
        unsigned int  sc_div_mmc0_peribus   : 1;  /* bit[2]    : MMC0 PERIBUS时钟分频比。(源时钟是clk_sysbus，默认240MHz，分频单独可配)
                                                                 1'b0:1；
                                                                 1'b1:2； */
        unsigned int  sc_div_mmc1_peribus   : 1;  /* bit[3]    : MMC1 PERIBUS时钟分频比。(源时钟是clk_sysbus，默认240MHz，分频单独可配)
                                                                 1'b0:1；
                                                                 1'b1:2； */
        unsigned int  div_modem_bbe16_tdl   : 4;  /* bit[4-7]  : MODEM BBE16时钟分频比选择：
                                                                 4'h0:1；
                                                                 4'h1:2；
                                                                 4'h2:3；
                                                                 …
                                                                 4'hE:15；
                                                                 4'hF:16； */
        unsigned int  sel_modem_bbe16_tdl   : 4;  /* bit[8-11] : MODEM BBE16 PLL时钟源选择：
                                                                 4'b0001：PPLL4；
                                                                 4'b0010：PPLL5；
                                                                 4'b0100：PPLL0；
                                                                 4'b1000：PPLL3。
                                                                 其他值无效。 */
        unsigned int  sc_div_dbgsechsic_bus : 1;  /* bit[12]   : DBGSECHSIC BUS时钟分频比。(源时钟是clk_sysbus，默认240MHz，分频单独可配)
                                                                 1'b0:1；
                                                                 1'b1:2； */
        unsigned int  sc_div_cssysdbg       : 1;  /* bit[13]   : CSSYS DEBUG时钟分频比。(源时钟是clk_sysbus，默认240MHz，分频单独可配)
                                                                 1'b0:1；
                                                                 1'b1:2； */
        unsigned int  reserved              : 1;  /* bit[14]   : 保留。 */
        unsigned int  sc_div_dmabus         : 1;  /* bit[15]   : DMA BUS时钟分频比。(源时钟是clk_sysbus，默认240MHz，分频单独可配)
                                                                 1'b0:1；
                                                                 1'b1:2； */
        unsigned int  clkdivmasken          : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                 只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV17_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cfgbus_START          (0)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cfgbus_END            (1)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc0_peribus_START    (2)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc0_peribus_END      (2)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc1_peribus_START    (3)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc1_peribus_END      (3)
#define SOC_CRGPERIPH_CLKDIV17_div_modem_bbe16_tdl_START    (4)
#define SOC_CRGPERIPH_CLKDIV17_div_modem_bbe16_tdl_END      (7)
#define SOC_CRGPERIPH_CLKDIV17_sel_modem_bbe16_tdl_START    (8)
#define SOC_CRGPERIPH_CLKDIV17_sel_modem_bbe16_tdl_END      (11)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dbgsechsic_bus_START  (12)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dbgsechsic_bus_END    (12)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cssysdbg_START        (13)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cssysdbg_END          (13)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dmabus_START          (15)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dmabus_END            (15)
#define SOC_CRGPERIPH_CLKDIV17_clkdivmasken_START           (16)
#define SOC_CRGPERIPH_CLKDIV17_clkdivmasken_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV18_UNION
 结构说明  : CLKDIV18 寄存器结构定义。地址偏移量:0x0F0，初值:0x0000FFFF，宽度:32
 寄存器说明: 时钟分频比控制寄存器18。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_g3daxi0    : 1;  /* bit[0]    : 1：时钟开启； 0：时钟关闭 */
        unsigned int  gt_clk_g3daxi1    : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_ddrc       : 1;  /* bit[2]    :  */
        unsigned int  reserved_0        : 1;  /* bit[3]    : 保留。 */
        unsigned int  gt_clk_lpmcu      : 1;  /* bit[4]    :  */
        unsigned int  reserved_1        : 1;  /* bit[5]    : 保留。 */
        unsigned int  gt_clk_ldi0       : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_ldi1       : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_edc0       : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 1;  /* bit[9]    : 保留。 */
        unsigned int  gt_clk_out0       : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_out1       : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_rxdphy_cfg : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_ispfunc1   : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_ispfunc2   : 1;  /* bit[14]   :  */
        unsigned int  gt_clk_vdec       : 1;  /* bit[15]   :  */
        unsigned int  clkdivmasken      : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                             只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV18_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi0_START     (0)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi0_END       (0)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi1_START     (1)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi1_END       (1)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ddrc_START        (2)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ddrc_END          (2)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_lpmcu_START       (4)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_lpmcu_END         (4)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi0_START        (6)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi0_END          (6)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi1_START        (7)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi1_END          (7)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_edc0_START        (8)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_edc0_END          (8)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out0_START        (10)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out0_END          (10)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out1_START        (11)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out1_END          (11)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_rxdphy_cfg_START  (12)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_rxdphy_cfg_END    (12)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc1_START    (13)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc1_END      (13)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc2_START    (14)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc2_END      (14)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_vdec_START        (15)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_vdec_END          (15)
#define SOC_CRGPERIPH_CLKDIV18_clkdivmasken_START       (16)
#define SOC_CRGPERIPH_CLKDIV18_clkdivmasken_END         (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV19_UNION
 结构说明  : CLKDIV19 寄存器结构定义。地址偏移量:0x0F4，初值:0x0000FFFF，宽度:32
 寄存器说明: 时钟分频比控制寄存器19。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_venc    : 1;  /* bit[0]    : 1：时钟开启； 0：时钟关闭 */
        unsigned int  reserved_0     : 1;  /* bit[1]    : 保留。 */
        unsigned int  gt_clk_emmc0   : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_sd      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_sdio0   : 1;  /* bit[4]    :  */
        unsigned int  reserved_1     : 1;  /* bit[5]    : 保留。 */
        unsigned int  reserved_2     : 1;  /* bit[6]    : 保留。 */
        unsigned int  gt_clk_a53hpm  : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_sdio1   : 1;  /* bit[8]    :  */
        unsigned int  reserved_3     : 1;  /* bit[9]    : 保留。 */
        unsigned int  reserved_4     : 1;  /* bit[10]   : 保留。 */
        unsigned int  gt_clk_uarth   : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_uartl   : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_spi     : 1;  /* bit[13]   :  */
        unsigned int  reserved_5     : 1;  /* bit[14]   : 保留。 */
        unsigned int  gt_clk_slimbus : 1;  /* bit[15]   :  */
        unsigned int  clkdivmasken   : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                          只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV19_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_venc_START     (0)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_venc_END       (0)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_emmc0_START    (2)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_emmc0_END      (2)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sd_START       (3)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sd_END         (3)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio0_START    (4)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio0_END      (4)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_a53hpm_START   (7)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_a53hpm_END     (7)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio1_START    (8)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio1_END      (8)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uarth_START    (11)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uarth_END      (11)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uartl_START    (12)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uartl_END      (12)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_spi_START      (13)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_spi_END        (13)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_slimbus_START  (15)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_slimbus_END    (15)
#define SOC_CRGPERIPH_CLKDIV19_clkdivmasken_START    (16)
#define SOC_CRGPERIPH_CLKDIV19_clkdivmasken_END      (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV20_UNION
 结构说明  : CLKDIV20 寄存器结构定义。地址偏移量:0x0F8，初值:0x0000FFFF，宽度:32
 寄存器说明: 时钟分频比控制寄存器20。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_i2c             : 1;  /* bit[0]    : 1：时钟开启； 0：时钟关闭 */
        unsigned int  gt_clk_vivobus         : 1;  /* bit[1]    : 保留。 */
        unsigned int  gt_clk_vcodecbus       : 1;  /* bit[2]    : 保留。 */
        unsigned int  gt_clk_aomm            : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7           : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_ptp             : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_mcpu      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_modem_bbe16     : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_modem_bbe16_tdl : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[9]    :  */
        unsigned int  reserved_0             : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_ddrphy_ref_a    : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_ddrphy_ref_b    : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_ddrphy_ref_c    : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_ddrphy_ref_d    : 1;  /* bit[14]   :  */
        unsigned int  reserved_1             : 1;  /* bit[15]   : 保留。 */
        unsigned int  clkdivmasken           : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                  只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV20_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_i2c_START              (0)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_i2c_END                (0)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vivobus_START          (1)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vivobus_END            (1)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vcodecbus_START        (2)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vcodecbus_END          (2)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_aomm_START             (3)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_aomm_END               (3)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ispa7_START            (4)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ispa7_END              (4)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ptp_START              (5)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ptp_END                (5)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_mcpu_START       (6)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_mcpu_END         (6)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_START      (7)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_END        (7)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_tdl_START  (8)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_tdl_END    (8)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ivp32dsp_core_START    (9)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ivp32dsp_core_END      (9)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_a_START     (11)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_a_END       (11)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_b_START     (12)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_b_END       (12)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_c_START     (13)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_c_END       (13)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_d_START     (14)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_d_END       (14)
#define SOC_CRGPERIPH_CLKDIV20_clkdivmasken_START            (16)
#define SOC_CRGPERIPH_CLKDIV20_clkdivmasken_END              (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV21_UNION
 结构说明  : CLKDIV21 寄存器结构定义。地址偏移量:0x0FC，初值:0x00000000，宽度:32
 寄存器说明: 时钟分频比控制寄存器21。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 16; /* bit[0-15] : 保留。 */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV21_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV21_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV21_clkdivmasken_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV22_UNION
 结构说明  : CLKDIV22 寄存器结构定义。地址偏移量:0x100，初值:0x00007980，宽度:32
 寄存器说明: 时钟分频比控制寄存器22。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0         : 7;  /* bit[0-6]  :  */
        unsigned int  sc_div_aomm        : 4;  /* bit[7-10] : AONOMMBUF 400M备份时钟分频系数 */
        unsigned int  div_clk_sys_ddr    : 2;  /* bit[11-12]: DDR SW sysclk 分频系数 */
        unsigned int  div_clk_sys_sysbus : 2;  /* bit[13-14]: SYSBUS SW sysclk 分频系数 */
        unsigned int  reserved_1         : 1;  /* bit[15]   : 保留。 */
        unsigned int  clkdivmasken       : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                              只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV22_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV22_sc_div_aomm_START         (7)
#define SOC_CRGPERIPH_CLKDIV22_sc_div_aomm_END           (10)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_ddr_START     (11)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_ddr_END       (12)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_sysbus_START  (13)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_sysbus_END    (14)
#define SOC_CRGPERIPH_CLKDIV22_clkdivmasken_START        (16)
#define SOC_CRGPERIPH_CLKDIV22_clkdivmasken_END          (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV23_UNION
 结构说明  : CLKDIV23 寄存器结构定义。地址偏移量:0x104，初值:0x000036A5，宽度:32
 寄存器说明: 时钟分频比控制寄存器23。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_clk_ddrc          : 5;  /* bit[0-4]  : DDRC源时钟分频选择：
                                                                 5'h00:1；
                                                                 5'h01:2；
                                                                 5'h02:3；
                                                                 …
                                                                 5'h1E:15；
                                                                 5'h1F:32； */
        unsigned int  div_clk_ddrcfg        : 2;  /* bit[5-6]  : DDRCFG时钟分频选择：
                                                                 2'h0:1；
                                                                 2'h1:2；
                                                                 2'h2:3；
                                                                 2'h3:4； */
        unsigned int  gt_clk_ddrcfg         : 1;  /* bit[7]    : clk_ddrcfg门控使能信号：
                                                                 0：时钟关闭；
                                                                 1：时钟使能； */
        unsigned int  div_clk_ddrphy_ref    : 1;  /* bit[8]    : ddrphy refclk分频选择：
                                                                 1'h0：1；
                                                                 1'h1：2； */
        unsigned int  div_clk_ddrphy_ref_en : 1;  /* bit[9]    : ddrphy refclk分频使能：
                                                                 0：分频使能撤销；
                                                                 1：时钟使能有效； */
        unsigned int  div_clk_ddrsys        : 2;  /* bit[10-11]: DDRSYS时钟分频选择：
                                                                 2'h0:1；
                                                                 2'h1:2；
                                                                 2'h2:3；
                                                                 2'h3:4； */
        unsigned int  gt_div_ddrsys_noc     : 1;  /* bit[12]   : clk_ddrsys_noc时钟门控使能信号：
                                                                 0：时钟关闭；
                                                                 1：时钟使能； */
        unsigned int  gt_clk_ddrc_sw        : 1;  /* bit[13]   : ddrc OCC_ROOT之前门控使能信号 */
        unsigned int  reserved              : 2;  /* bit[14-15]: 保留。 */
        unsigned int  clkdivmasken          : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                                 只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV23_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrc_START           (0)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrc_END             (4)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrcfg_START         (5)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrcfg_END           (6)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrcfg_START          (7)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrcfg_END            (7)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_START     (8)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_END       (8)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_en_START  (9)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_en_END    (9)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrsys_START         (10)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrsys_END           (11)
#define SOC_CRGPERIPH_CLKDIV23_gt_div_ddrsys_noc_START      (12)
#define SOC_CRGPERIPH_CLKDIV23_gt_div_ddrsys_noc_END        (12)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrc_sw_START         (13)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrc_sw_END           (13)
#define SOC_CRGPERIPH_CLKDIV23_clkdivmasken_START           (16)
#define SOC_CRGPERIPH_CLKDIV23_clkdivmasken_END             (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV24_UNION
 结构说明  : CLKDIV24 寄存器结构定义。地址偏移量:0x108，初值:0x00000007，宽度:32
 寄存器说明: 时钟分频比控制寄存器24。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_isp_snclk     : 2;  /* bit[0-1]  : clk_isp_snclk 分频选择：
                                                             2'h0:1分频，48M；
                                                             2'h1:2分频，24M；
                                                             2'h2:3分频，16M；
                                                             2'h3:4分频，12M； */
        unsigned int  gt_clk_isp_snclk  : 1;  /* bit[2]    : clk_isp_snclk 分频门控使能信号：
                                                             0：时钟关闭；
                                                             1：时钟使能； */
        unsigned int  sel_clk_isp_snclk : 1;  /* bit[3]    : clk_isp_snclk_sys 时钟选择信号：
                                                             0：clk_isp_snclk_sys；
                                                             1：clk_isp_snclk_div； */
        unsigned int  reserved          : 12; /* bit[4-15] : 保留。 */
        unsigned int  clkdivmasken      : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                             只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV24_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV24_div_isp_snclk_START      (0)
#define SOC_CRGPERIPH_CLKDIV24_div_isp_snclk_END        (1)
#define SOC_CRGPERIPH_CLKDIV24_gt_clk_isp_snclk_START   (2)
#define SOC_CRGPERIPH_CLKDIV24_gt_clk_isp_snclk_END     (2)
#define SOC_CRGPERIPH_CLKDIV24_sel_clk_isp_snclk_START  (3)
#define SOC_CRGPERIPH_CLKDIV24_sel_clk_isp_snclk_END    (3)
#define SOC_CRGPERIPH_CLKDIV24_clkdivmasken_START       (16)
#define SOC_CRGPERIPH_CLKDIV24_clkdivmasken_END         (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CLKDIV25_UNION
 结构说明  : CLKDIV25 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: 时钟分频比控制寄存器25。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 16; /* bit[0-15] : 保留。 */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdiv每个比特位的使能位：
                                                        只有当clkdivmasken对应的比特位为1'b1，clkdiv相应的比特位才起作用。Clkdivmasken[0]就是clkdiv[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_CLKDIV25_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV25_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV25_clkdivmasken_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PER_STAT0_UNION
 结构说明  : PER_STAT0 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PER_STAT0_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PER_STAT1_UNION
 结构说明  : PER_STAT1 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: 外设状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bootmode               : 2;  /* bit[0-1] : 加载模式控制位（高bit集成固定接0）：
                                                                 2'bx0：bootrom启动-USB加载；
                                                                 2'bx1：正常bootrom启动-eMMC启动； */
        unsigned int  sc_noc_aobus_idle_flag : 1;  /* bit[2]   : aobus idle 指示信号：
                                                                 0：busy；
                                                                 1：idle； */
        unsigned int  isp_to_ddrc_dfs_en     : 1;  /* bit[3]   : ISP是否同意DDRC切换频率,每次DDR需要调频时，LPM3会查询该信号状态来决定是否执行本次DDR调频：
                                                                 1:同意;
                                                                 0:不同意. */
        unsigned int  reserved               : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PER_STAT1_UNION;
#endif
#define SOC_CRGPERIPH_PER_STAT1_bootmode_START                (0)
#define SOC_CRGPERIPH_PER_STAT1_bootmode_END                  (1)
#define SOC_CRGPERIPH_PER_STAT1_sc_noc_aobus_idle_flag_START  (2)
#define SOC_CRGPERIPH_PER_STAT1_sc_noc_aobus_idle_flag_END    (2)
#define SOC_CRGPERIPH_PER_STAT1_isp_to_ddrc_dfs_en_START      (3)
#define SOC_CRGPERIPH_PER_STAT1_isp_to_ddrc_dfs_en_END        (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PER_STAT2_UNION
 结构说明  : PER_STAT2 寄存器结构定义。地址偏移量:0x118，初值:0x00004000，宽度:32
 寄存器说明: 外设状态寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  swdone_clk_aclk_ddrc       : 1;  /* bit[0]    :  */
        unsigned int  swdone_clk_sysbus_div      : 1;  /* bit[1]    : DIV分频比切换是否完成指示信号：
                                                                      0：未完成；
                                                                      1：完成； */
        unsigned int  swdone_clk_lpmcu_div       : 1;  /* bit[2]    :  */
        unsigned int  swdone_clk_vcodecbus_div   : 1;  /* bit[3]    :  */
        unsigned int  swdone_clk_vivobus_div     : 1;  /* bit[4]    :  */
        unsigned int  swdone_clk_ddrcfg          : 1;  /* bit[5]    :  */
        unsigned int  swdone_clk_ldi0_div        : 1;  /* bit[6]    :  */
        unsigned int  swdone_clk_ldi1_div        : 1;  /* bit[7]    :  */
        unsigned int  swdone_clk_edc0_div        : 1;  /* bit[8]    :  */
        unsigned int  swdone_clk_ddrsys          : 1;  /* bit[9]    :  */
        unsigned int  swdone_clk_ispfunc1_div    : 1;  /* bit[10]   :  */
        unsigned int  swdone_clk_ispfunc2_div    : 1;  /* bit[11]   :  */
        unsigned int  swdone_clk_vdec_div        : 1;  /* bit[12]   :  */
        unsigned int  swdone_clk_venc_div        : 1;  /* bit[13]   :  */
        unsigned int  ddr_pll_sw_ack             : 4;  /* bit[14-17]: ddr pll时钟源切换ack信号： 
                                                                      4'b0001:PPLL0；
                                                                      4'b0010:PPLL1；
                                                                      4'b0100:PPLL2；
                                                                      4'b1000:PPLL3； */
        unsigned int  swdone_clk_sd_div          : 1;  /* bit[18]   :  */
        unsigned int  swdone_clk_sdio0_div       : 1;  /* bit[19]   :  */
        unsigned int  swdone_clk_sdio1_div       : 1;  /* bit[20]   :  */
        unsigned int  swdone_clk_a53hpm_div      : 1;  /* bit[21]   :  */
        unsigned int  swdone_clk_emmc0_div       : 1;  /* bit[22]   :  */
        unsigned int  swdone_clk_aomm_div        : 1;  /* bit[23]   :  */
        unsigned int  swdone_clk_isp_snclk_div   : 1;  /* bit[24]   :  */
        unsigned int  swdone_clk_uarth_div       : 1;  /* bit[25]   :  */
        unsigned int  swdone_clk_uartl_div       : 1;  /* bit[26]   :  */
        unsigned int  swdone_clk_spi_div         : 1;  /* bit[27]   :  */
        unsigned int  swdone_clk_i2c_div         : 1;  /* bit[28]   :  */
        unsigned int  swdone_clk_modem_mcpu_div  : 1;  /* bit[29]   :  */
        unsigned int  swdone_clk_modem_bbe16_div : 1;  /* bit[30]   :  */
        unsigned int  swdone_clk_out0_div1       : 1;  /* bit[31]   :  */
    } reg;
} SOC_CRGPERIPH_PER_STAT2_UNION;
#endif
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aclk_ddrc_START        (0)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aclk_ddrc_END          (0)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sysbus_div_START       (1)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sysbus_div_END         (1)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_lpmcu_div_START        (2)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_lpmcu_div_END          (2)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vcodecbus_div_START    (3)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vcodecbus_div_END      (3)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vivobus_div_START      (4)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vivobus_div_END        (4)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrcfg_START           (5)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrcfg_END             (5)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi0_div_START         (6)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi0_div_END           (6)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi1_div_START         (7)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi1_div_END           (7)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_edc0_div_START         (8)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_edc0_div_END           (8)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrsys_START           (9)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrsys_END             (9)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc1_div_START     (10)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc1_div_END       (10)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc2_div_START     (11)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc2_div_END       (11)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vdec_div_START         (12)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vdec_div_END           (12)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_venc_div_START         (13)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_venc_div_END           (13)
#define SOC_CRGPERIPH_PER_STAT2_ddr_pll_sw_ack_START              (14)
#define SOC_CRGPERIPH_PER_STAT2_ddr_pll_sw_ack_END                (17)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sd_div_START           (18)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sd_div_END             (18)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio0_div_START        (19)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio0_div_END          (19)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio1_div_START        (20)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio1_div_END          (20)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_a53hpm_div_START       (21)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_a53hpm_div_END         (21)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_emmc0_div_START        (22)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_emmc0_div_END          (22)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aomm_div_START         (23)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aomm_div_END           (23)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_isp_snclk_div_START    (24)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_isp_snclk_div_END      (24)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uarth_div_START        (25)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uarth_div_END          (25)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uartl_div_START        (26)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uartl_div_END          (26)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_spi_div_START          (27)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_spi_div_END            (27)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_i2c_div_START          (28)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_i2c_div_END            (28)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_mcpu_div_START   (29)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_mcpu_div_END     (29)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_bbe16_div_START  (30)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_bbe16_div_END    (30)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_out0_div1_START        (31)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_out0_div1_END          (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PER_STAT3_UNION
 结构说明  : PER_STAT3 寄存器结构定义。地址偏移量:0x11C，初值:0x15211100，宽度:32
 寄存器说明: 外设状态寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  swdone_clk_out1_div1           : 1;  /* bit[0]    : DIV分频比切换是否完成指示信号：
                                                                          0：未完成；
                                                                          1：完成； */
        unsigned int  swdone_clk_cfgbus_div          : 1;  /* bit[1]    : DIV分频比切换是否完成指示信号：
                                                                          0：未完成；
                                                                          1：完成； */
        unsigned int  swdone_clk_dbgsechsic_bus_div  : 1;  /* bit[2]    : DIV分频比切换是否完成指示信号：
                                                                          0：未完成；
                                                                          1：完成； */
        unsigned int  swdone_clk_modem_bbe16_tdl_div : 1;  /* bit[3]    : DIV分频比切换是否完成指示信号：
                                                                          0：未完成；
                                                                          1：完成； */
        unsigned int  swdone_clk_dmabus_div          : 1;  /* bit[4]    : DIV分频比切换是否完成指示信号：
                                                                          0：未完成；
                                                                          1：完成； */
        unsigned int  swdone_clk_ispfunc             : 1;  /* bit[5]    : clk_ispfunc 切换时钟源指示信号：
                                                                          0：切换成clk_isp_func2(480/360)；
                                                                          1：切换成clk_isp_func1(400/320)； */
        unsigned int  swdone_clk_slimbus_div         : 1;  /* bit[6]    : DIV分频比切换是否完成指示信号：
                                                                          0：未完成；
                                                                          1：完成； */
        unsigned int  swdone_clk_ispa7_div           : 1;  /* bit[7]    : DIV分频比切换是否完成指示信号：
                                                                          0：未完成；
                                                                          1：完成； */
        unsigned int  ldi0_pll_sw_ack                : 4;  /* bit[8-11] : ldi0 pll时钟源切换ack信号： 
                                                                          4'b0001:PPLL0；
                                                                          4'b0010:PPLL2；
                                                                          4'b0100:PPLL1；
                                                                          4'b1000:PPLL3； */
        unsigned int  ldi1_pll_sw_ack                : 4;  /* bit[12-15]: ldi1 pll时钟源切换ack信号： 
                                                                          4'b0001:PPLL0；
                                                                          4'b0010:PPLL2；
                                                                          4'b0100:PPLL1；
                                                                          4'b1000:PPLL3； */
        unsigned int  mcpu_pll_sw_ack                : 4;  /* bit[16-19]: modem cpu pll时钟源切换ack信号： 
                                                                          4'b0001：PPLL4；
                                                                          4'b0010：PPLL5；
                                                                          4'b0100：PPLL0；
                                                                          4'b1000：PPLL3。 */
        unsigned int  bbe16_pll_sw_ack               : 4;  /* bit[20-23]: modem bbe16 pll时钟源切换ack信号： 
                                                                          4'b0001：PPLL4；
                                                                          4'b0010：PPLL5；
                                                                          4'b0100：PPLL0；
                                                                          4'b1000：PPLL3。 */
        unsigned int  ddrclksw2sys                   : 1;  /* bit[24]   : ddrc clk切换至晶振时钟指示，高有效。 */
        unsigned int  ddrclksw2pll                   : 1;  /* bit[25]   : ddrc clk切换至PLL时钟指示，高有效。 */
        unsigned int  sysbusclksw2sys                : 1;  /* bit[26]   : sysbus clk切换至晶振时钟指示，高有效。 */
        unsigned int  sysbusclksw2pll                : 1;  /* bit[27]   : sysbus clk切换至PLL时钟指示，高有效。 */
        unsigned int  lpmcuclksw2sys                 : 1;  /* bit[28]   : lpmcu clk切换至晶振时钟指示，高有效。 */
        unsigned int  lpmcuclksw2pll                 : 1;  /* bit[29]   : lpmcu clk切换至PLL时钟指示，高有效。 */
        unsigned int  swdone_clk_cssysdbg_div        : 1;  /* bit[30]   : DIV分频比切换是否完成指示信号：
                                                                          0：未完成；
                                                                          1：完成； */
        unsigned int  swdone_clk_ivp32dsp_core_div   : 1;  /* bit[31]   : DIV分频比切换是否完成指示信号：
                                                                          0：未完成；
                                                                          1：完成； */
    } reg;
} SOC_CRGPERIPH_PER_STAT3_UNION;
#endif
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_out1_div1_START            (0)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_out1_div1_END              (0)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cfgbus_div_START           (1)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cfgbus_div_END             (1)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dbgsechsic_bus_div_START   (2)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dbgsechsic_bus_div_END     (2)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_modem_bbe16_tdl_div_START  (3)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_modem_bbe16_tdl_div_END    (3)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dmabus_div_START           (4)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dmabus_div_END             (4)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispfunc_START              (5)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispfunc_END                (5)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_slimbus_div_START          (6)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_slimbus_div_END            (6)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispa7_div_START            (7)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispa7_div_END              (7)
#define SOC_CRGPERIPH_PER_STAT3_ldi0_pll_sw_ack_START                 (8)
#define SOC_CRGPERIPH_PER_STAT3_ldi0_pll_sw_ack_END                   (11)
#define SOC_CRGPERIPH_PER_STAT3_ldi1_pll_sw_ack_START                 (12)
#define SOC_CRGPERIPH_PER_STAT3_ldi1_pll_sw_ack_END                   (15)
#define SOC_CRGPERIPH_PER_STAT3_mcpu_pll_sw_ack_START                 (16)
#define SOC_CRGPERIPH_PER_STAT3_mcpu_pll_sw_ack_END                   (19)
#define SOC_CRGPERIPH_PER_STAT3_bbe16_pll_sw_ack_START                (20)
#define SOC_CRGPERIPH_PER_STAT3_bbe16_pll_sw_ack_END                  (23)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2sys_START                    (24)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2sys_END                      (24)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2pll_START                    (25)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2pll_END                      (25)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2sys_START                 (26)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2sys_END                   (26)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2pll_START                 (27)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2pll_END                   (27)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2sys_START                  (28)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2sys_END                    (28)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2pll_START                  (29)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2pll_END                    (29)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cssysdbg_div_START         (30)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cssysdbg_div_END           (30)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ivp32dsp_core_div_START    (31)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ivp32dsp_core_div_END      (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCTRL0_UNION
 结构说明  : PERCTRL0 寄存器结构定义。地址偏移量:0x120，初值:0x000001FF，宽度:32
 寄存器说明: 外设控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cactive_cci400_cfgcnt : 8;  /* bit[0-7] : CCI-400硬件自动门控等待时钟周期配置 */
        unsigned int  gt_clk_cci400_bypass  : 1;  /* bit[8]   : CCI-400时钟门控bypass控制：
                                                                0：bypass无效，时钟可通过硬件自动门控；
                                                                1：bypass有效，时钟不门控； */
        unsigned int  reserved              : 23; /* bit[9-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERCTRL0_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL0_cactive_cci400_cfgcnt_START  (0)
#define SOC_CRGPERIPH_PERCTRL0_cactive_cci400_cfgcnt_END    (7)
#define SOC_CRGPERIPH_PERCTRL0_gt_clk_cci400_bypass_START   (8)
#define SOC_CRGPERIPH_PERCTRL0_gt_clk_cci400_bypass_END     (8)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCTRL1_UNION
 结构说明  : PERCTRL1 寄存器结构定义。地址偏移量:0x124，初值:0x0000000F，宽度:32
 寄存器说明: 外设控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_auto_clk_cci2sysbus_async_bypass : 1;  /* bit[0]   : 是否bypass cci2sysbus异步桥S侧时钟自动门控：
                                                                              0：不bypass；
                                                                              1：bypass */
        unsigned int  gt_auto_clk_i2c34_bypass            : 1;  /* bit[1]   : 是否bypass I2C34异步桥S侧时钟自动门控：
                                                                              0：不bypass；
                                                                              1：bypass */
        unsigned int  gt_auto_clk_uart025_bypass          : 1;  /* bit[2]   : 是否bypass UART025异步桥S侧时钟自动门控：
                                                                              0：不bypass；
                                                                              1：bypass */
        unsigned int  gt_auto_clk_uart14_bypass           : 1;  /* bit[3]   : 是否bypass UART14异步桥S侧时钟自动门控：
                                                                              0：不bypass；
                                                                              1：bypass */
        unsigned int  reserved                            : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERCTRL1_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_cci2sysbus_async_bypass_START  (0)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_cci2sysbus_async_bypass_END    (0)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_i2c34_bypass_START             (1)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_i2c34_bypass_END               (1)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart025_bypass_START           (2)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart025_bypass_END             (2)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart14_bypass_START            (3)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart14_bypass_END              (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCTRL2_UNION
 结构说明  : PERCTRL2 寄存器结构定义。地址偏移量:0x128，初值:0x7FE337FE，宽度:32
 寄存器说明: 外设控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pclkdbg_sel                    : 1;  /* bit[0]    : debug APB工作时钟频率比选择信号（相对于debugAPB_trace_clk），默认1:2。
                                                                          0：1:2
                                                                          1：1:4  */
        unsigned int  pclkdbg_clkoff_sys             : 1;  /* bit[1]    : top_cssys 内部使用的PCLKDBG时钟使能系统控制：上电默认为1 。
                                                                          0：关闭PCLKDBG
                                                                          1：打开PCLKDBG */
        unsigned int  pclkdbg_to_a53cfg_clkoff_sys_0 : 1;  /* bit[2]    : 送给A53 cluster0 CRG的pclkdbg时钟使能系统控制：上电默认为1 。
                                                                          0：关闭PCLKDBG_TO_A53CRG
                                                                          1：打开PCLKDBG_TO_A53CRG */
        unsigned int  pclkdbg_to_a53cfg_clkoff_sys_1 : 1;  /* bit[3]    : 送给A53 cluster1 CRG的pclkdbg时钟使能系统控制：上电默认为1 。
                                                                          0：关闭PCLKDBG_TO_A57CRG
                                                                          1：打开PCLKDBG_TO_A57CRG */
        unsigned int  pclkdbg_to_iomcu_clkoff_sys    : 1;  /* bit[4]    : 送给IOMCU的pclkdbg时钟使能系统控制：上电默认为1 。
                                                                          0：关闭PCLKDBG_TO_IOMCU
                                                                          1：打开PCLKDBG_TO_IOMCU */
        unsigned int  pclkdbg_to_lpmcu_clkoff_sys    : 1;  /* bit[5]    : 送给LPMCU的pclkdbg时钟使能系统控制：上电默认为1 。
                                                                          0：关闭PCLKDBG_TO_LPMCU
                                                                          1：打开PCLKDBG_TO_LPMCU */
        unsigned int  traceclkin_clkoff_sys          : 1;  /* bit[6]    : TRACECLKIN时钟使能系统控制：上电默认为1 。
                                                                          0：关闭TRACECLKIN
                                                                          1：打开TRACELKIN */
        unsigned int  atclkoff_sys                   : 1;  /* bit[7]    : ATCLK时钟使能系统控制：上电默认为1。
                                                                          0：关闭ATCLK
                                                                          1：打开ATCLK */
        unsigned int  atclk_to_iomcu_clkoff_sys      : 1;  /* bit[8]    : ATCLK_TO_IOMCU G时钟使能系统控制：上电默认为1 。
                                                                          0：关闭ATCLK_TO_IOMCU
                                                                          1：打开ATCLK_TO_IOMCU */
        unsigned int  atclk_to_a53crg_clkoff_sys_0   : 1;  /* bit[9]    : ATCLK_TO_A53 cluster0 CRG时钟使能系统控制：上电默认为1 。
                                                                          0：关闭ATCLK_TO_A57CRG
                                                                          1：打开ATCLK_TO_A57CRG */
        unsigned int  atclk_to_a53crg_clkoff_sys_1   : 1;  /* bit[10]   : ATCLK_TO_A53 cluster1 CRG时钟使能系统控制：上电默认为1 。
                                                                          0：关闭ATCLK_TO_A53CRG
                                                                          1：打开ATCLK_TO_A53CRG */
        unsigned int  cs_soft_rst_req                : 1;  /* bit[11]   : top_cssys软件复位请求，复位请求持续时间最少16个PCLKDBG时钟周期。
                                                                          0：请求无效；
                                                                          1：请求有效。 */
        unsigned int  traceclkin_sel                 : 2;  /* bit[12-13]: trace port工作时钟频率比选择信号（相对于debugAPB_trace_clk），默认1:4。（使用场景固定为1:4）
                                                                          00：1:1
                                                                          01：1:2
                                                                          10：1:3
                                                                          11：1:4 */
        unsigned int  reserved                       : 1;  /* bit[14]   : 保留。 */
        unsigned int  cs_cssys_rst_req               : 1;  /* bit[15]   : 送给的top_cssys 复位请求信号，上电默认为0 。
                                                                          0：请求无效；
                                                                          1：请求有效。 */
        unsigned int  atclk_to_modem_clkoff_sys      : 1;  /* bit[16]   : ATCLK_TO_MODEMCRG时钟使能系统控制：上电默认为1 。
                                                                          0：关闭ATCLK_TO_MODEMCRG
                                                                          1：打开ATCLK_TO_MODEMCRG */
        unsigned int  pclkdbg_to_modem_clkoff_sys    : 1;  /* bit[17]   : 送给MODEMCRG的pclkdbg时钟使能系统控制，上电默认为1 。
                                                                          0：关闭PCLKDBG_TO_MODEMCRG
                                                                          1：打开PCLKDBG_TO_MODEMCRG */
        unsigned int  modem_cssys_rst_req            : 1;  /* bit[18]   : 送给MODEM的cssys 复位请求信号，上电默认为0 。
                                                                          0：请求无效；
                                                                          1：请求有效。 */
        unsigned int  asp_cssys_rst_req              : 1;  /* bit[19]   : 送给ASP的cssys 复位请求信号，上电默认为0 。
                                                                          0：请求无效；
                                                                          1：请求有效。 */
        unsigned int  atclk_to_asp_clkoff_sys        : 1;  /* bit[20]   : 送给ASPCRG 的ATCLK_TO_ASPCRG时钟使能系统控制，上电默认为0(Austin ASP 20140825删除trace功能) 。
                                                                          0：关闭ATCLK_TO_ASPCRG
                                                                          1：打开ATCLK_TO_ASPCRG */
        unsigned int  pclkdbg_to_asp_clkoff_sys      : 1;  /* bit[21]   : 送给ASPCRG的pclkdbg时钟使能系统控制，上电默认为1 。
                                                                          0：关闭PCLKDBG_TO_ASPCRG
                                                                          1：打开PCLKDBG_TO_ASPCRG */
        unsigned int  time_stamp_clk_sel             : 3;  /* bit[22-24]: 分频比配置：(最低配置4分频)
                                                                          3'h0:2分频；
                                                                          3'h1:4分频；
                                                                          3'h2:6分频；
                                                                          3'h3:8分频；
                                                                          3'h4:10分频；
                                                                          3'h5:12分频；
                                                                          3'h6:14分频；
                                                                          3'h7:16分频； */
        unsigned int  gt_clk_cssys_atclk             : 1;  /* bit[25]   : cssys ATB internal区atclk时钟门控
                                                                          0：时钟关闭
                                                                          1：时钟开启 */
        unsigned int  ip_rst_cssys_atclk             : 1;  /* bit[26]   : cssys ATB internal区atclk时钟对应的复位控制
                                                                          0：复位有效
                                                                          1：复位撤销 */
        unsigned int  gt_clk_time_stamp              : 1;  /* bit[27]   : time stamp的时钟门控
                                                                          0：时钟关闭
                                                                          1：时钟开启 */
        unsigned int  ip_rst_time_stamp              : 1;  /* bit[28]   : time stamp的复位控制
                                                                          0：复位有效
                                                                          1：复位撤销 */
        unsigned int  atclk_to_iapa7_clkoff_sys      : 1;  /* bit[29]   : ATCLK_TO_ISPA7时钟使能系统控制：上电默认为1 。
                                                                          0：关闭ATCLK_TO_IAPA7
                                                                          1：打开ATCLK_TO_IAPA7 */
        unsigned int  pclkdbg_to_iapa7_clkoff_sys    : 1;  /* bit[30]   : PCLKDBG_TO_ISPA7时钟使能系统控制，上电默认为1 。
                                                                          0：关闭PCLKDBG_TO_ISPA7
                                                                          1：打开PCLKDBG_TO_ISPA7 */
        unsigned int  ispa7_mask                     : 1;  /* bit[31]   : ISPA7 的使能位：
                                                                          当该bit为1'b1，[30:29]的值才能被改写，同时[28:0]的值不能被改写；当该bit为1'b0，[30:29]的值不能被改写，同时[28:0]的值能被改写。 */
    } reg;
} SOC_CRGPERIPH_PERCTRL2_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_sel_START                     (0)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_sel_END                       (0)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_clkoff_sys_START              (1)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_clkoff_sys_END                (1)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_0_START  (2)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_0_END    (2)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_1_START  (3)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_1_END    (3)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iomcu_clkoff_sys_START     (4)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iomcu_clkoff_sys_END       (4)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_lpmcu_clkoff_sys_START     (5)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_lpmcu_clkoff_sys_END       (5)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_clkoff_sys_START           (6)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_clkoff_sys_END             (6)
#define SOC_CRGPERIPH_PERCTRL2_atclkoff_sys_START                    (7)
#define SOC_CRGPERIPH_PERCTRL2_atclkoff_sys_END                      (7)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iomcu_clkoff_sys_START       (8)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iomcu_clkoff_sys_END         (8)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_0_START    (9)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_0_END      (9)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_1_START    (10)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_1_END      (10)
#define SOC_CRGPERIPH_PERCTRL2_cs_soft_rst_req_START                 (11)
#define SOC_CRGPERIPH_PERCTRL2_cs_soft_rst_req_END                   (11)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_sel_START                  (12)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_sel_END                    (13)
#define SOC_CRGPERIPH_PERCTRL2_cs_cssys_rst_req_START                (15)
#define SOC_CRGPERIPH_PERCTRL2_cs_cssys_rst_req_END                  (15)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_modem_clkoff_sys_START       (16)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_modem_clkoff_sys_END         (16)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_modem_clkoff_sys_START     (17)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_modem_clkoff_sys_END       (17)
#define SOC_CRGPERIPH_PERCTRL2_modem_cssys_rst_req_START             (18)
#define SOC_CRGPERIPH_PERCTRL2_modem_cssys_rst_req_END               (18)
#define SOC_CRGPERIPH_PERCTRL2_asp_cssys_rst_req_START               (19)
#define SOC_CRGPERIPH_PERCTRL2_asp_cssys_rst_req_END                 (19)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_asp_clkoff_sys_START         (20)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_asp_clkoff_sys_END           (20)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_asp_clkoff_sys_START       (21)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_asp_clkoff_sys_END         (21)
#define SOC_CRGPERIPH_PERCTRL2_time_stamp_clk_sel_START              (22)
#define SOC_CRGPERIPH_PERCTRL2_time_stamp_clk_sel_END                (24)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_cssys_atclk_START              (25)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_cssys_atclk_END                (25)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_cssys_atclk_START              (26)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_cssys_atclk_END                (26)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_time_stamp_START               (27)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_time_stamp_END                 (27)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_time_stamp_START               (28)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_time_stamp_END                 (28)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iapa7_clkoff_sys_START       (29)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iapa7_clkoff_sys_END         (29)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iapa7_clkoff_sys_START     (30)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iapa7_clkoff_sys_END       (30)
#define SOC_CRGPERIPH_PERCTRL2_ispa7_mask_START                      (31)
#define SOC_CRGPERIPH_PERCTRL2_ispa7_mask_END                        (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCTRL3_UNION
 结构说明  : PERCTRL3 寄存器结构定义。地址偏移量:0x12C，初值:0x00001001，宽度:32
 寄存器说明: 外设控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  noc_timeout_en    : 1;  /* bit[0]    : NOC timeout counter使能控制：
                                                             0：不使能；
                                                             1：使能。 */
        unsigned int  reserved_0        : 5;  /* bit[1-5]  : 保留。 */
        unsigned int  mem_ctrl_pgt_lpm3 : 6;  /* bit[6-11] : LP_RAM的memory低功耗控制信号。每3-bit为一组，各对应16KB RAM。从高位至低位分别对应：SD、DSLP、SLP。
                                                             bit[5:3]:tcm_ram1，默认值3'b000;
                                                             bit[2:0]:tcm_ram0，默认值3'b000; */
        unsigned int  mcpu_fiq_n        : 1;  /* bit[12]   : MCPU FIQ 中断，低有效。 */
        unsigned int  reserved_1        : 19; /* bit[13-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERCTRL3_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL3_noc_timeout_en_START     (0)
#define SOC_CRGPERIPH_PERCTRL3_noc_timeout_en_END       (0)
#define SOC_CRGPERIPH_PERCTRL3_mem_ctrl_pgt_lpm3_START  (6)
#define SOC_CRGPERIPH_PERCTRL3_mem_ctrl_pgt_lpm3_END    (11)
#define SOC_CRGPERIPH_PERCTRL3_mcpu_fiq_n_START         (12)
#define SOC_CRGPERIPH_PERCTRL3_mcpu_fiq_n_END           (12)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCTRL4_UNION
 结构说明  : PERCTRL4 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: 外设控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acpu_ipf_clk_en : 1;  /* bit[0]   : modem的IPF门控控制信号 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERCTRL4_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL4_acpu_ipf_clk_en_START  (0)
#define SOC_CRGPERIPH_PERCTRL4_acpu_ipf_clk_en_END    (0)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCTRL5_UNION
 结构说明  : PERCTRL5 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: 外设控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERCTRL5_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCTRL6_UNION
 结构说明  : PERCTRL6 寄存器结构定义。地址偏移量:0x138，初值:0x00000000，宽度:32
 寄存器说明: 外设控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERCTRL6_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERTIMECTRL_UNION
 结构说明  : PERTIMECTRL 寄存器结构定义。地址偏移量:0x140，初值:0x000C0000，宽度:32
 寄存器说明: 外设TIME控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeren18sel   : 1;  /* bit[0]    : Timer18时钟使能参考时钟选择。
                                                          0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                          1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren18ov    : 1;  /* bit[1]    : Timer18时钟使能控制。
                                                          0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren18sel]指定；
                                                          1：使能信号被强制拉高。 */
        unsigned int  timeren19sel   : 1;  /* bit[2]    : Timer19时钟使能参考时钟选择。
                                                          0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                          1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren19ov    : 1;  /* bit[3]    : Timer19时钟使能控制。
                                                          0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren19sel]指定；
                                                          1：使能信号被强制拉高。 */
        unsigned int  timeren20sel   : 1;  /* bit[4]    : Timer20时钟使能参考时钟选择。
                                                          0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                          1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren20ov    : 1;  /* bit[5]    : Timer20时钟使能控制。
                                                          0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren10sel]指定；
                                                          1：使能信号被强制拉高。 */
        unsigned int  timeren21sel   : 1;  /* bit[6]    : Timer21时钟使能参考时钟选择。
                                                          0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                          1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren21ov    : 1;  /* bit[7]    : Timer21时钟使能控制。
                                                          0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren21sel]指定；
                                                          1：使能信号被强制拉高。 */
        unsigned int  timeren22sel   : 1;  /* bit[8]    : Timer22时钟使能参考时钟选择。
                                                          0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                          1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren22ov    : 1;  /* bit[9]    : Timer22时钟使能控制。
                                                          0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren12sel]指定；
                                                          1：使能信号被强制拉高。 */
        unsigned int  timeren23sel   : 1;  /* bit[10]   : Timer23时钟使能参考时钟选择。
                                                          0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                          1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren23ov    : 1;  /* bit[11]   : Timer23时钟使能控制。
                                                          0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren23sel]指定；
                                                          1：使能信号被强制拉高。 */
        unsigned int  timeren24sel   : 1;  /* bit[12]   : Timer24时钟使能参考时钟选择。
                                                          0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                          1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren24ov    : 1;  /* bit[13]   : Timer24时钟使能控制。
                                                          0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren24sel]指定；
                                                          1：使能信号被强制拉高。 */
        unsigned int  timeren25sel   : 1;  /* bit[14]   : Timer25时钟使能参考时钟选择。
                                                          0：选择32.768kHz睡眠时钟作为参考时钟计数；
                                                          1：选择TCXO时钟的4分频时钟作为参考时钟计数。 */
        unsigned int  timeren25ov    : 1;  /* bit[15]   : Timer25时钟使能控制。
                                                          0：使能信号通过采样参考时钟得到，参考时钟的选择由[timeren25sel]指定；
                                                          1：使能信号被强制拉高。 */
        unsigned int  wdog1enov      : 1;  /* bit[16]   : 看门狗时钟使能控制。
                                                          0：使能由采样32.768kHz时钟产生；
                                                          1：使能被强制拉高。 */
        unsigned int  wdog0enov      : 1;  /* bit[17]   : 看门狗时钟使能控制。
                                                          0：使能由采样32.768kHz时钟产生；
                                                          1：使能被强制拉高。 */
        unsigned int  wd0_dbgack_byp : 1;  /* bit[18]   : 0：bypass无效；
                                                          1：bypass有效； */
        unsigned int  wd1_dbgack_byp : 1;  /* bit[19]   : 0：bypass无效；
                                                          1：bypass有效； */
        unsigned int  reserved       : 12; /* bit[20-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERTIMECTRL_UNION;
#endif
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18sel_START    (0)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18sel_END      (0)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18ov_START     (1)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18ov_END       (1)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19sel_START    (2)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19sel_END      (2)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19ov_START     (3)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19ov_END       (3)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20sel_START    (4)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20sel_END      (4)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20ov_START     (5)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20ov_END       (5)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21sel_START    (6)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21sel_END      (6)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21ov_START     (7)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21ov_END       (7)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22sel_START    (8)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22sel_END      (8)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22ov_START     (9)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22ov_END       (9)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23sel_START    (10)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23sel_END      (10)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23ov_START     (11)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23ov_END       (11)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24sel_START    (12)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24sel_END      (12)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24ov_START     (13)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24ov_END       (13)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25sel_START    (14)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25sel_END      (14)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25ov_START     (15)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25ov_END       (15)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog1enov_START       (16)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog1enov_END         (16)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog0enov_START       (17)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog0enov_END         (17)
#define SOC_CRGPERIPH_PERTIMECTRL_wd0_dbgack_byp_START  (18)
#define SOC_CRGPERIPH_PERTIMECTRL_wd0_dbgack_byp_END    (18)
#define SOC_CRGPERIPH_PERTIMECTRL_wd1_dbgack_byp_START  (19)
#define SOC_CRGPERIPH_PERTIMECTRL_wd1_dbgack_byp_END    (19)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISOEN_UNION
 结构说明  : ISOEN 寄存器结构定义。地址偏移量:0x144，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统ISO使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispisoen         : 1;  /* bit[0]    : ISP子系统ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  vencisoen        : 1;  /* bit[1]    : VENC子系统ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  vdecisoen        : 1;  /* bit[2]    : VDEC子系统ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  reserved_0       : 1;  /* bit[3]    : 保留。 */
        unsigned int  modemsubsysisoen : 1;  /* bit[4]    : MODEM子系统 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  g3disoen         : 1;  /* bit[5]    : G3D子系统ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  dsssubsysisoen   : 1;  /* bit[6]    : DSS SUBSYS ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  reserved_1       : 1;  /* bit[7]    : 保留。 */
        unsigned int  reserved_2       : 1;  /* bit[8]    : 保留。 */
        unsigned int  reserved_3       : 1;  /* bit[9]    : 保留。 */
        unsigned int  reserved_4       : 1;  /* bit[10]   : 保留。 */
        unsigned int  reserved_5       : 1;  /* bit[11]   : 保留。 */
        unsigned int  a53_0_cor0isoen  : 1;  /* bit[12]   : A53 cluster0子系统CORE0 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  a53_0_cor1isoen  : 1;  /* bit[13]   : A53 cluster0子系统CORE1 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  a53_0_cor2isoen  : 1;  /* bit[14]   : A53 cluster0子系统CORE2 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  a53_0_cor3isoen  : 1;  /* bit[15]   : A53 cluster0子系统CORE3 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  a53isoen         : 1;  /* bit[16]   : A53子系统ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  a53_1_cor0isoen  : 1;  /* bit[17]   : A57 cluster子系统CORE0 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  a53_1_cor1isoen  : 1;  /* bit[18]   : A57 cluster子系统CORE1 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  a53_1_cor2isoen  : 1;  /* bit[19]   : A57 cluster子系统CORE2 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  a53_1_cor3isoen  : 1;  /* bit[20]   : A57 cluster子系统CORE3 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  a57isoen         : 1;  /* bit[21]   : A57 cluster子系统 ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  modemperiisoen   : 1;  /* bit[22]   : MODEM子系统PERI ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  modemirmisoen    : 1;  /* bit[23]   : MODEM子系统IRM ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  ivp32dspisoen    : 1;  /* bit[24]   : IVP32DSP子系统ISO单元使能控制：写1执行ISO使能操作。 */
        unsigned int  reserved_6       : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISOEN_UNION;
#endif
#define SOC_CRGPERIPH_ISOEN_ispisoen_START          (0)
#define SOC_CRGPERIPH_ISOEN_ispisoen_END            (0)
#define SOC_CRGPERIPH_ISOEN_vencisoen_START         (1)
#define SOC_CRGPERIPH_ISOEN_vencisoen_END           (1)
#define SOC_CRGPERIPH_ISOEN_vdecisoen_START         (2)
#define SOC_CRGPERIPH_ISOEN_vdecisoen_END           (2)
#define SOC_CRGPERIPH_ISOEN_modemsubsysisoen_START  (4)
#define SOC_CRGPERIPH_ISOEN_modemsubsysisoen_END    (4)
#define SOC_CRGPERIPH_ISOEN_g3disoen_START          (5)
#define SOC_CRGPERIPH_ISOEN_g3disoen_END            (5)
#define SOC_CRGPERIPH_ISOEN_dsssubsysisoen_START    (6)
#define SOC_CRGPERIPH_ISOEN_dsssubsysisoen_END      (6)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor0isoen_START   (12)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor0isoen_END     (12)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor1isoen_START   (13)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor1isoen_END     (13)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor2isoen_START   (14)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor2isoen_END     (14)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor3isoen_START   (15)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor3isoen_END     (15)
#define SOC_CRGPERIPH_ISOEN_a53isoen_START          (16)
#define SOC_CRGPERIPH_ISOEN_a53isoen_END            (16)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor0isoen_START   (17)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor0isoen_END     (17)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor1isoen_START   (18)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor1isoen_END     (18)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor2isoen_START   (19)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor2isoen_END     (19)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor3isoen_START   (20)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor3isoen_END     (20)
#define SOC_CRGPERIPH_ISOEN_a57isoen_START          (21)
#define SOC_CRGPERIPH_ISOEN_a57isoen_END            (21)
#define SOC_CRGPERIPH_ISOEN_modemperiisoen_START    (22)
#define SOC_CRGPERIPH_ISOEN_modemperiisoen_END      (22)
#define SOC_CRGPERIPH_ISOEN_modemirmisoen_START     (23)
#define SOC_CRGPERIPH_ISOEN_modemirmisoen_END       (23)
#define SOC_CRGPERIPH_ISOEN_ivp32dspisoen_START     (24)
#define SOC_CRGPERIPH_ISOEN_ivp32dspisoen_END       (24)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISODIS_UNION
 结构说明  : ISODIS 寄存器结构定义。地址偏移量:0x148，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统ISO使能撤销寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispisoen         : 1;  /* bit[0]    : ISP子系统ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  vencisoen        : 1;  /* bit[1]    : VENC子系统ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  vdecisoen        : 1;  /* bit[2]    : VDEC子系统ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  reserved_0       : 1;  /* bit[3]    : 保留。 */
        unsigned int  modemsubsysisoen : 1;  /* bit[4]    : MODEM子系统 ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  g3disoen         : 1;  /* bit[5]    : G3D子系统ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  dsssubsysisoen   : 1;  /* bit[6]    : DSS SUBSYS ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  reserved_1       : 1;  /* bit[7]    : 保留。 */
        unsigned int  reserved_2       : 1;  /* bit[8]    : 保留。 */
        unsigned int  reserved_3       : 1;  /* bit[9]    : 保留。 */
        unsigned int  reserved_4       : 1;  /* bit[10]   : 保留。 */
        unsigned int  reserved_5       : 1;  /* bit[11]   : 保留。 */
        unsigned int  a53_0_cor0isoen  : 1;  /* bit[12]   : A53 cluster0子系统CORE0 ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  a53_0_cor1isoen  : 1;  /* bit[13]   : A53 cluster0子系统CORE1 ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  a53_0_cor2isoen  : 1;  /* bit[14]   : A53 cluster0子系统CORE2 ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  a53_0_cor3isoen  : 1;  /* bit[15]   : A53 cluster0子系统CORE3 ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  a53isoen         : 1;  /* bit[16]   : A53子系统ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  a53_1_cor0isoen  : 1;  /* bit[17]   : A57 cluster子系统CORE0 ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  a53_1_cor1isoen  : 1;  /* bit[18]   : A57 cluster子系统CORE1 ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  a53_1_cor2isoen  : 1;  /* bit[19]   : A57 cluster子系统CORE2 ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  a53_1_cor3isoen  : 1;  /* bit[20]   : A57 cluster子系统CORE3 ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  a57isoen         : 1;  /* bit[21]   : A57子系统ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  modemperiisoen   : 1;  /* bit[22]   : MODEM子系统PERI ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  modemirmisoen    : 1;  /* bit[23]   : MODEM子系统IRM ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  ivp32dspisoen    : 1;  /* bit[24]   : IVP32DSP子系统ISO单元使能控制：写1执行ISO使能撤消操作。 */
        unsigned int  reserved_6       : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISODIS_UNION;
#endif
#define SOC_CRGPERIPH_ISODIS_ispisoen_START          (0)
#define SOC_CRGPERIPH_ISODIS_ispisoen_END            (0)
#define SOC_CRGPERIPH_ISODIS_vencisoen_START         (1)
#define SOC_CRGPERIPH_ISODIS_vencisoen_END           (1)
#define SOC_CRGPERIPH_ISODIS_vdecisoen_START         (2)
#define SOC_CRGPERIPH_ISODIS_vdecisoen_END           (2)
#define SOC_CRGPERIPH_ISODIS_modemsubsysisoen_START  (4)
#define SOC_CRGPERIPH_ISODIS_modemsubsysisoen_END    (4)
#define SOC_CRGPERIPH_ISODIS_g3disoen_START          (5)
#define SOC_CRGPERIPH_ISODIS_g3disoen_END            (5)
#define SOC_CRGPERIPH_ISODIS_dsssubsysisoen_START    (6)
#define SOC_CRGPERIPH_ISODIS_dsssubsysisoen_END      (6)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor0isoen_START   (12)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor0isoen_END     (12)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor1isoen_START   (13)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor1isoen_END     (13)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor2isoen_START   (14)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor2isoen_END     (14)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor3isoen_START   (15)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor3isoen_END     (15)
#define SOC_CRGPERIPH_ISODIS_a53isoen_START          (16)
#define SOC_CRGPERIPH_ISODIS_a53isoen_END            (16)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor0isoen_START   (17)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor0isoen_END     (17)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor1isoen_START   (18)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor1isoen_END     (18)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor2isoen_START   (19)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor2isoen_END     (19)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor3isoen_START   (20)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor3isoen_END     (20)
#define SOC_CRGPERIPH_ISODIS_a57isoen_START          (21)
#define SOC_CRGPERIPH_ISODIS_a57isoen_END            (21)
#define SOC_CRGPERIPH_ISODIS_modemperiisoen_START    (22)
#define SOC_CRGPERIPH_ISODIS_modemperiisoen_END      (22)
#define SOC_CRGPERIPH_ISODIS_modemirmisoen_START     (23)
#define SOC_CRGPERIPH_ISODIS_modemirmisoen_END       (23)
#define SOC_CRGPERIPH_ISODIS_ivp32dspisoen_START     (24)
#define SOC_CRGPERIPH_ISODIS_ivp32dspisoen_END       (24)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISOSTAT_UNION
 结构说明  : ISOSTAT 寄存器结构定义。地址偏移量:0x14C，初值:0x01FFFFFF，宽度:32
 寄存器说明: 掉电子系统ISO使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispisoen         : 1;  /* bit[0]    : ISP子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  vencisoen        : 1;  /* bit[1]    : VENC子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  vdecisoen        : 1;  /* bit[2]    : VDEC子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  reserved_0       : 1;  /* bit[3]    : 保留。 */
        unsigned int  modemsubsysisoen : 1;  /* bit[4]    : MODEM子系统 ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  g3disoen         : 1;  /* bit[5]    : G3D子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  dsssubsysisoen   : 1;  /* bit[6]    : DSS SUBSYS ISOO单元使能状态：0：不使能；1：使能。 */
        unsigned int  reserved_1       : 1;  /* bit[7]    : 保留。 */
        unsigned int  reserved_2       : 1;  /* bit[8]    : 保留。 */
        unsigned int  reserved_3       : 1;  /* bit[9]    : 保留。 */
        unsigned int  reserved_4       : 1;  /* bit[10]   : 保留。 */
        unsigned int  reserved_5       : 1;  /* bit[11]   : 保留。 */
        unsigned int  a53_0_cor0isoen  : 1;  /* bit[12]   : A53 cluster0 CPU0子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  a53_0_cor1isoen  : 1;  /* bit[13]   : A53 cluster0 CPU1子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  a53_0_cor2isoen  : 1;  /* bit[14]   : A53 cluster0 CPU2子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  a53_0_cor3isoen  : 1;  /* bit[15]   : A53 cluster0 CPU3子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  a53isoen         : 1;  /* bit[16]   : A53 子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  a53_1_cor0isoen  : 1;  /* bit[17]   : A57 cluster CPU0子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  a53_1_cor1isoen  : 1;  /* bit[18]   : A57 cluster CPU1子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  a53_1_cor2isoen  : 1;  /* bit[19]   : A57 cluster CPU2子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  a53_1_cor3isoen  : 1;  /* bit[20]   : A57 cluster CPU3子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  a57isoen         : 1;  /* bit[21]   : A57 子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  modemperiisoen   : 1;  /* bit[22]   : MODEM子系统PERI ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  modemirmisoen    : 1;  /* bit[23]   : MODEM子系统IRM ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  ivp32dspisoen    : 1;  /* bit[24]   : IVP32DSP子系统ISO单元使能状态：0：不使能；1：使能。 */
        unsigned int  reserved_6       : 7;  /* bit[25-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISOSTAT_UNION;
#endif
#define SOC_CRGPERIPH_ISOSTAT_ispisoen_START          (0)
#define SOC_CRGPERIPH_ISOSTAT_ispisoen_END            (0)
#define SOC_CRGPERIPH_ISOSTAT_vencisoen_START         (1)
#define SOC_CRGPERIPH_ISOSTAT_vencisoen_END           (1)
#define SOC_CRGPERIPH_ISOSTAT_vdecisoen_START         (2)
#define SOC_CRGPERIPH_ISOSTAT_vdecisoen_END           (2)
#define SOC_CRGPERIPH_ISOSTAT_modemsubsysisoen_START  (4)
#define SOC_CRGPERIPH_ISOSTAT_modemsubsysisoen_END    (4)
#define SOC_CRGPERIPH_ISOSTAT_g3disoen_START          (5)
#define SOC_CRGPERIPH_ISOSTAT_g3disoen_END            (5)
#define SOC_CRGPERIPH_ISOSTAT_dsssubsysisoen_START    (6)
#define SOC_CRGPERIPH_ISOSTAT_dsssubsysisoen_END      (6)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor0isoen_START   (12)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor0isoen_END     (12)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor1isoen_START   (13)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor1isoen_END     (13)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor2isoen_START   (14)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor2isoen_END     (14)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor3isoen_START   (15)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor3isoen_END     (15)
#define SOC_CRGPERIPH_ISOSTAT_a53isoen_START          (16)
#define SOC_CRGPERIPH_ISOSTAT_a53isoen_END            (16)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor0isoen_START   (17)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor0isoen_END     (17)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor1isoen_START   (18)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor1isoen_END     (18)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor2isoen_START   (19)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor2isoen_END     (19)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor3isoen_START   (20)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor3isoen_END     (20)
#define SOC_CRGPERIPH_ISOSTAT_a57isoen_START          (21)
#define SOC_CRGPERIPH_ISOSTAT_a57isoen_END            (21)
#define SOC_CRGPERIPH_ISOSTAT_modemperiisoen_START    (22)
#define SOC_CRGPERIPH_ISOSTAT_modemperiisoen_END      (22)
#define SOC_CRGPERIPH_ISOSTAT_modemirmisoen_START     (23)
#define SOC_CRGPERIPH_ISOSTAT_modemirmisoen_END       (23)
#define SOC_CRGPERIPH_ISOSTAT_ivp32dspisoen_START     (24)
#define SOC_CRGPERIPH_ISOSTAT_ivp32dspisoen_END       (24)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERPWREN_UNION
 结构说明  : PERPWREN 寄存器结构定义。地址偏移量:0x150，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统电源使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isppwren        : 1;  /* bit[0]    : ISP电源使能控制：写1执行电源使能操作。 */
        unsigned int  vencpwren       : 1;  /* bit[1]    : VENC电源使能控制：写1执行电源使能操作。 */
        unsigned int  vdecpwren       : 1;  /* bit[2]    : VDEC电源使能控制：写1执行电源使能操作。 */
        unsigned int  reserved_0      : 1;  /* bit[3]    : 保留。 */
        unsigned int  reserved_1      : 1;  /* bit[4]    : 保留。 */
        unsigned int  dsssubsyspwren  : 1;  /* bit[5]    : DSS SUBSYS电源使能控制：写1执行电源使能操作。 */
        unsigned int  reserved_2      : 1;  /* bit[6]    : 保留。 */
        unsigned int  reserved_3      : 1;  /* bit[7]    : 保留。 */
        unsigned int  reserved_4      : 1;  /* bit[8]    : 保留。 */
        unsigned int  reserved_5      : 1;  /* bit[9]    : 保留。 */
        unsigned int  reserved_6      : 1;  /* bit[10]   : 保留。 */
        unsigned int  a53_0_cor0pwren : 1;  /* bit[11]   : A53 cluster0 CORE0子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  a53_0_cor1pwren : 1;  /* bit[12]   : A53 cluster0 CORE1子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  a53_0_cor2pwren : 1;  /* bit[13]   : A53 cluster0 CORE2子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  a53_0_cor3pwren : 1;  /* bit[14]   : A53 cluster0 CORE3子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  a53_1_cor0pwren : 1;  /* bit[15]   : A53 cluster1 CORE0子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  a53_1_cor1pwren : 1;  /* bit[16]   : A53 cluster1 CORE1子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  a53_1_cor2pwren : 1;  /* bit[17]   : A53 cluster1 CORE2子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  a53_1_cor3pwren : 1;  /* bit[18]   : A53 cluster1 CORE3子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  modemperipwren  : 1;  /* bit[19]   : MODEM子系统PERI电源使能控制：写1执行电源使能操作。 */
        unsigned int  modemirmpwren   : 1;  /* bit[20]   : MODEM子系统IRM电源使能控制：写1执行电源使能操作。 */
        unsigned int  ivp32dsppwren   : 1;  /* bit[21]   : IVP32DSP子系统电源使能控制：写1执行电源使能操作。 */
        unsigned int  reserved_7      : 10; /* bit[22-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERPWREN_UNION;
#endif
#define SOC_CRGPERIPH_PERPWREN_isppwren_START         (0)
#define SOC_CRGPERIPH_PERPWREN_isppwren_END           (0)
#define SOC_CRGPERIPH_PERPWREN_vencpwren_START        (1)
#define SOC_CRGPERIPH_PERPWREN_vencpwren_END          (1)
#define SOC_CRGPERIPH_PERPWREN_vdecpwren_START        (2)
#define SOC_CRGPERIPH_PERPWREN_vdecpwren_END          (2)
#define SOC_CRGPERIPH_PERPWREN_dsssubsyspwren_START   (5)
#define SOC_CRGPERIPH_PERPWREN_dsssubsyspwren_END     (5)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor0pwren_START  (11)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor0pwren_END    (11)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor1pwren_START  (12)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor1pwren_END    (12)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor2pwren_START  (13)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor2pwren_END    (13)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor3pwren_START  (14)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor3pwren_END    (14)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor0pwren_START  (15)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor0pwren_END    (15)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor1pwren_START  (16)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor1pwren_END    (16)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor2pwren_START  (17)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor2pwren_END    (17)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor3pwren_START  (18)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor3pwren_END    (18)
#define SOC_CRGPERIPH_PERPWREN_modemperipwren_START   (19)
#define SOC_CRGPERIPH_PERPWREN_modemperipwren_END     (19)
#define SOC_CRGPERIPH_PERPWREN_modemirmpwren_START    (20)
#define SOC_CRGPERIPH_PERPWREN_modemirmpwren_END      (20)
#define SOC_CRGPERIPH_PERPWREN_ivp32dsppwren_START    (21)
#define SOC_CRGPERIPH_PERPWREN_ivp32dsppwren_END      (21)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERPWRDIS_UNION
 结构说明  : PERPWRDIS 寄存器结构定义。地址偏移量:0x154，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统电源使能撤销寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isppwrdis        : 1;  /* bit[0]    : ISP电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  vencpwrdis       : 1;  /* bit[1]    : VENC电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  vdecpwrdis       : 1;  /* bit[2]    : VDEC电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  reserved_0       : 1;  /* bit[3]    : 保留。 */
        unsigned int  reserved_1       : 1;  /* bit[4]    : 保留。 */
        unsigned int  dsssubsyspwrdis  : 1;  /* bit[5]    : DSS SUBSYS电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  reserved_2       : 1;  /* bit[6]    : 保留。 */
        unsigned int  reserved_3       : 1;  /* bit[7]    : 保留。 */
        unsigned int  reserved_4       : 1;  /* bit[8]    : 保留。 */
        unsigned int  reserved_5       : 1;  /* bit[9]    : 保留。 */
        unsigned int  reserved_6       : 1;  /* bit[10]   : 保留。 */
        unsigned int  a53_0_cor0pwrdis : 1;  /* bit[11]   : A53 cluster0 CORE0子系统电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  a53_0_cor1pwrdis : 1;  /* bit[12]   : A53 cluster0 CORE1子系统电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  a53_0_cor2pwrdis : 1;  /* bit[13]   : A53 cluster0 CORE2子系统电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  a53_0_cor3pwrdis : 1;  /* bit[14]   : A53 cluster0 CORE3子系统电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  a53_1_cor0pwrdis : 1;  /* bit[15]   : A53 cluster1 CORE0子系统电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  a53_1_cor1pwrdis : 1;  /* bit[16]   : A53 cluster1 CORE1子系统电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  a53_1_cor2pwrdis : 1;  /* bit[17]   : A53 cluster1 CORE2子系统电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  a53_1_cor3pwrdis : 1;  /* bit[18]   : A53 cluster1 CORE3子系统电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  modemperipwrdis  : 1;  /* bit[19]   : MODEM子系统PERI电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  modemirmpwrdis   : 1;  /* bit[20]   : MODEM子系统IRM电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  ivp32dsppwrdis   : 1;  /* bit[21]   : IVP32DSP子系统电源使能控制：写1执行电源使能撤销操作。 */
        unsigned int  reserved_7       : 10; /* bit[22-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERPWRDIS_UNION;
#endif
#define SOC_CRGPERIPH_PERPWRDIS_isppwrdis_START         (0)
#define SOC_CRGPERIPH_PERPWRDIS_isppwrdis_END           (0)
#define SOC_CRGPERIPH_PERPWRDIS_vencpwrdis_START        (1)
#define SOC_CRGPERIPH_PERPWRDIS_vencpwrdis_END          (1)
#define SOC_CRGPERIPH_PERPWRDIS_vdecpwrdis_START        (2)
#define SOC_CRGPERIPH_PERPWRDIS_vdecpwrdis_END          (2)
#define SOC_CRGPERIPH_PERPWRDIS_dsssubsyspwrdis_START   (5)
#define SOC_CRGPERIPH_PERPWRDIS_dsssubsyspwrdis_END     (5)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor0pwrdis_START  (11)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor0pwrdis_END    (11)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor1pwrdis_START  (12)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor1pwrdis_END    (12)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor2pwrdis_START  (13)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor2pwrdis_END    (13)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor3pwrdis_START  (14)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor3pwrdis_END    (14)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor0pwrdis_START  (15)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor0pwrdis_END    (15)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor1pwrdis_START  (16)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor1pwrdis_END    (16)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor2pwrdis_START  (17)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor2pwrdis_END    (17)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor3pwrdis_START  (18)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor3pwrdis_END    (18)
#define SOC_CRGPERIPH_PERPWRDIS_modemperipwrdis_START   (19)
#define SOC_CRGPERIPH_PERPWRDIS_modemperipwrdis_END     (19)
#define SOC_CRGPERIPH_PERPWRDIS_modemirmpwrdis_START    (20)
#define SOC_CRGPERIPH_PERPWRDIS_modemirmpwrdis_END      (20)
#define SOC_CRGPERIPH_PERPWRDIS_ivp32dsppwrdis_START    (21)
#define SOC_CRGPERIPH_PERPWRDIS_ivp32dsppwrdis_END      (21)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERPWRSTAT_UNION
 结构说明  : PERPWRSTAT 寄存器结构定义。地址偏移量:0x158，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统电源使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isppwrstat        : 1;  /* bit[0]    : ISP电源使能状态：
                                                             0：ISP电源使能撤销；
                                                             1：ISP电源使能。 */
        unsigned int  vencpwrstat       : 1;  /* bit[1]    : VENC电源使能状态：
                                                             0：VENC电源使能撤销；
                                                             1：VENC电源使能。 */
        unsigned int  vdecpwrstat       : 1;  /* bit[2]    : VDEC电源使能状态：
                                                             0：VDEC电源使能撤销；
                                                             1：VDEC电源使能。 */
        unsigned int  reserved_0        : 1;  /* bit[3]    : 保留。 */
        unsigned int  reserved_1        : 1;  /* bit[4]    : 保留。 */
        unsigned int  dsssubsyspwrstat  : 1;  /* bit[5]    : DSS SUBSYS电源使能状态：
                                                             0：DSS SUBSYS电源使能撤销；
                                                             1：DSS SUBSYS电源使能。 */
        unsigned int  reserved_2        : 1;  /* bit[6]    : 保留。 */
        unsigned int  reserved_3        : 1;  /* bit[7]    : 保留。 */
        unsigned int  reserved_4        : 1;  /* bit[8]    : 保留。 */
        unsigned int  reserved_5        : 1;  /* bit[9]    : 保留。 */
        unsigned int  reserved_6        : 1;  /* bit[10]   : 保留。 */
        unsigned int  a53_0_cor0pwrstat : 1;  /* bit[11]   : A53 cluster0 CORE0子系统电源使能状态：
                                                             0：A53 cluster0 CORE0子系统电源使能撤销；
                                                             1：A53 cluster0 CORE0子系统电源使能。 */
        unsigned int  a53_0_cor1pwrstat : 1;  /* bit[12]   : A53 cluster0 CORE1子系统电源使能状态：
                                                             0：A53 cluster0 CORE1子系统电源使能撤销；
                                                             1：A53 cluster0 CORE1子系统电源使能。 */
        unsigned int  a53_0_cor2pwrstat : 1;  /* bit[13]   : A53 cluster0 CORE2子系统电源使能状态：
                                                             0：A53 cluster0 CORE2子系统电源使能撤销；
                                                             1：A53 cluster0 CORE2子系统电源使能。 */
        unsigned int  a53_0_cor3pwrstat : 1;  /* bit[14]   : A53 cluster0 CORE3子系统电源使能状态：
                                                             0：A53 cluster0 CORE3子系统电源使能撤销；
                                                             1：A53 cluster0 CORE3子系统电源使能。 */
        unsigned int  a53_1_cor0pwrstat : 1;  /* bit[15]   : A53 cluster1 CORE0子系统电源使能状态：
                                                             0：A53 cluster1 CORE0子系统电源使能撤销；
                                                             1：A53 cluster1 CORE0子系统电源使能。 */
        unsigned int  a53_1_cor1pwrstat : 1;  /* bit[16]   : A53 cluster1 CORE1子系统电源使能状态：
                                                             0：A53 cluster1 CORE1子系统电源使能撤销；
                                                             1：A53 cluster1 CORE1子系统电源使能。 */
        unsigned int  a53_1_cor2pwrstat : 1;  /* bit[17]   : A53 cluster1 CORE2子系统电源使能状态：
                                                             0：A53 cluster1 CORE2子系统电源使能撤销；
                                                             1：A53 cluster1 CORE2子系统电源使能。 */
        unsigned int  a53_1_cor3pwrstat : 1;  /* bit[18]   : A53 cluster1 CORE3子系统电源使能状态：
                                                             0：A53 cluster1 CORE3子系统电源使能撤销；
                                                             1：A53 cluster1 CORE3子系统电源使能。 */
        unsigned int  modemperipwrstat  : 1;  /* bit[19]   : MODEM子系统PERI电源使能状态：
                                                             0：MODEM子系统PERI电源使能撤销；
                                                             1：MODEM子系统PERI电源使能。 */
        unsigned int  modemirmpwrstat   : 1;  /* bit[20]   : MODEM子系统IRM电源使能状态：
                                                             0：MODEM子系统IRM电源使能撤销；
                                                             1：MODEM子系统IRM电源使能。 */
        unsigned int  ivp32dsppwrstat   : 1;  /* bit[21]   : IVP32DSP子系统电源使能状态：
                                                             0：IVP32DSP子系统电源使能撤销；
                                                             1：IVP32DSP子系统电源使能。 */
        unsigned int  reserved_7        : 10; /* bit[22-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERPWRSTAT_UNION;
#endif
#define SOC_CRGPERIPH_PERPWRSTAT_isppwrstat_START         (0)
#define SOC_CRGPERIPH_PERPWRSTAT_isppwrstat_END           (0)
#define SOC_CRGPERIPH_PERPWRSTAT_vencpwrstat_START        (1)
#define SOC_CRGPERIPH_PERPWRSTAT_vencpwrstat_END          (1)
#define SOC_CRGPERIPH_PERPWRSTAT_vdecpwrstat_START        (2)
#define SOC_CRGPERIPH_PERPWRSTAT_vdecpwrstat_END          (2)
#define SOC_CRGPERIPH_PERPWRSTAT_dsssubsyspwrstat_START   (5)
#define SOC_CRGPERIPH_PERPWRSTAT_dsssubsyspwrstat_END     (5)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor0pwrstat_START  (11)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor0pwrstat_END    (11)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor1pwrstat_START  (12)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor1pwrstat_END    (12)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor2pwrstat_START  (13)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor2pwrstat_END    (13)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor3pwrstat_START  (14)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor3pwrstat_END    (14)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor0pwrstat_START  (15)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor0pwrstat_END    (15)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor1pwrstat_START  (16)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor1pwrstat_END    (16)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor2pwrstat_START  (17)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor2pwrstat_END    (17)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor3pwrstat_START  (18)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor3pwrstat_END    (18)
#define SOC_CRGPERIPH_PERPWRSTAT_modemperipwrstat_START   (19)
#define SOC_CRGPERIPH_PERPWRSTAT_modemperipwrstat_END     (19)
#define SOC_CRGPERIPH_PERPWRSTAT_modemirmpwrstat_START    (20)
#define SOC_CRGPERIPH_PERPWRSTAT_modemirmpwrstat_END      (20)
#define SOC_CRGPERIPH_PERPWRSTAT_ivp32dsppwrstat_START    (21)
#define SOC_CRGPERIPH_PERPWRSTAT_ivp32dsppwrstat_END      (21)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERPWRACK_UNION
 结构说明  : PERPWRACK 寄存器结构定义。地址偏移量:0x15C，初值:0x00000000，宽度:32
 寄存器说明: 掉电子系统最终电源状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isppwrack         : 1;  /* bit[0]    : ISP电源状态：
                                                             0：ISP电源切断状态；
                                                             1：ISP电源供给状态。 */
        unsigned int  vencpwrack        : 1;  /* bit[1]    : VENC电源状态：
                                                             0：VENC电源切断状态；
                                                             1：VENC电源供给状态。 */
        unsigned int  vdecpwrack        : 1;  /* bit[2]    : VDEC电源状态：
                                                             0：VDEC电源切断状态；
                                                             1：VDEC电源供给状态。 */
        unsigned int  reserved_0        : 1;  /* bit[3]    : 保留。 */
        unsigned int  reserved_1        : 1;  /* bit[4]    : 保留。 */
        unsigned int  dsssubsyspwrack   : 1;  /* bit[5]    : DSS SUBSYS电源使能状态：
                                                             0：DSS SUBSYS电源切断状态。
                                                             1：DSS SUBSYS电源供给状态； */
        unsigned int  reserved_2        : 1;  /* bit[6]    : 保留。 */
        unsigned int  reserved_3        : 1;  /* bit[7]    : 保留。 */
        unsigned int  reserved_4        : 1;  /* bit[8]    : 保留。 */
        unsigned int  reserved_5        : 1;  /* bit[9]    : 保留。 */
        unsigned int  reserved_6        : 1;  /* bit[10]   : 保留。 */
        unsigned int  a53_0_core0pwrack : 1;  /* bit[11]   : A53 cluster0CORE0子系统电源使能状态：
                                                             0：A53 cluster0CORE0子系统电源切断状态。
                                                             1：A53 cluster0CORE0子系统电源供给状态； */
        unsigned int  a53_0_core1pwrack : 1;  /* bit[12]   : A53 cluster0CORE1子系统电源使能状态：
                                                             0：A53 cluster0CORE1子系统电源切断状态。
                                                             1：A53 cluster0CORE1子系统电源供给状态； */
        unsigned int  a53_0_core2pwrack : 1;  /* bit[13]   : A53 cluster0CORE2子系统电源使能状态：
                                                             0：A53 cluster0CORE2子系统电源切断状态。
                                                             1：A53 cluster0CORE2子系统电源供给状态； */
        unsigned int  a53_0_core3pwrack : 1;  /* bit[14]   : A53 cluster0 CORE3子系统电源使能状态：
                                                             0：A53 cluster0CORE3子系统电源切断状态。
                                                             1：A53 cluster0CORE3子系统电源供给状态； */
        unsigned int  a53_1_core0pwrack : 1;  /* bit[15]   : A53 cluster1 CORE0子系统电源使能状态：
                                                             0：A53 cluster1 CORE0子系统电源切断状态。
                                                             1：A53 cluster1 CORE0子系统电源供给状态； */
        unsigned int  a53_1_core1pwrack : 1;  /* bit[16]   : A53 cluster1 CORE1子系统电源使能状态：
                                                             0：A53 cluster1 CORE1子系统电源切断状态。
                                                             1：A53 cluster1 CORE1子系统电源供给状态； */
        unsigned int  a53_1_core2pwrack : 1;  /* bit[17]   : A53 cluster1 CORE2子系统电源使能状态：
                                                             0：A53 cluster1 CORE2子系统电源切断状态。
                                                             1：A53 cluster1 CORE2子系统电源供给状态； */
        unsigned int  a53_1_core3pwrack : 1;  /* bit[18]   : A53 cluster1 CORE3子系统电源使能状态：
                                                             0：A53 cluster1 CORE3子系统电源切断状态。
                                                             1：A53 cluster1 CORE3子系统电源供给状态； */
        unsigned int  reserved_7        : 1;  /* bit[19]   : 保留。 */
        unsigned int  g3dshpwrack0      : 1;  /* bit[20]   : G3D shader mtcmos0电源使能状态：
                                                             0：G3D shader mtcmos0电源切断状态
                                                             1：G3D shader mtcmos0电源供给状态 */
        unsigned int  g3dshpwrack1      : 1;  /* bit[21]   : G3D shader mtcmos1电源使能状态：
                                                             0：G3D shader mtcmos1电源切断状态
                                                             1：G3D shader mtcmos1电源供给状态 */
        unsigned int  g3dshpwrack2      : 1;  /* bit[22]   : G3D shader mtcmos2电源使能状态：
                                                             0：G3D shader mtcmos2电源切断状态
                                                             1：G3D shader mtcmos2电源供给状态 */
        unsigned int  g3dshpwrack3      : 1;  /* bit[23]   : G3D shader mtcmos3电源使能状态：
                                                             0：G3D shader mtcmos3电源切断状态
                                                             1：G3D shader mtcmos3电源供给状态 */
        unsigned int  g3dshpwrack4      : 1;  /* bit[24]   : G3D shader mtcmos4电源使能状态：
                                                             0：G3D shader mtcmos4电源切断状态
                                                             1：G3D shader mtcmos4电源供给状态 */
        unsigned int  g3dshpwrack5      : 1;  /* bit[25]   : G3D shader mtcmos5电源使能状态：
                                                             0：G3D shader mtcmos5电源切断状态
                                                             1：G3D shader mtcmos5电源供给状态 */
        unsigned int  g3dcg0en          : 1;  /* bit[26]   : 指示G3D内部core group0工作模式
                                                             0：掉电或precharge模式
                                                             1：正常工作模式 */
        unsigned int  modemperipwrack   : 1;  /* bit[27]   : MODEM子系统PERI电源使能状态：
                                                             0：MODEM子系统PERI电源切断状态
                                                             1：MODEM子系统PERI电源供给状态 */
        unsigned int  modemirmpwrack    : 1;  /* bit[28]   : MODEM子系统IRM电源使能状态：
                                                             0：MODEM子系统IRM电源切断状态
                                                             1：MODEM子系统IRM电源供给状态 */
        unsigned int  ivp32dsppwrack    : 1;  /* bit[29]   : IVP32DSP子系统电源使能状态：
                                                             0：IVP32DSP子系统电源切断状态
                                                             1：IVP32DSP子系统电源供给状态 */
        unsigned int  reserved_8        : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERPWRACK_UNION;
#endif
#define SOC_CRGPERIPH_PERPWRACK_isppwrack_START          (0)
#define SOC_CRGPERIPH_PERPWRACK_isppwrack_END            (0)
#define SOC_CRGPERIPH_PERPWRACK_vencpwrack_START         (1)
#define SOC_CRGPERIPH_PERPWRACK_vencpwrack_END           (1)
#define SOC_CRGPERIPH_PERPWRACK_vdecpwrack_START         (2)
#define SOC_CRGPERIPH_PERPWRACK_vdecpwrack_END           (2)
#define SOC_CRGPERIPH_PERPWRACK_dsssubsyspwrack_START    (5)
#define SOC_CRGPERIPH_PERPWRACK_dsssubsyspwrack_END      (5)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core0pwrack_START  (11)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core0pwrack_END    (11)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core1pwrack_START  (12)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core1pwrack_END    (12)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core2pwrack_START  (13)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core2pwrack_END    (13)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core3pwrack_START  (14)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core3pwrack_END    (14)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core0pwrack_START  (15)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core0pwrack_END    (15)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core1pwrack_START  (16)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core1pwrack_END    (16)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core2pwrack_START  (17)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core2pwrack_END    (17)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core3pwrack_START  (18)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core3pwrack_END    (18)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack0_START       (20)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack0_END         (20)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack1_START       (21)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack1_END         (21)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack2_START       (22)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack2_END         (22)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack3_START       (23)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack3_END         (23)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack4_START       (24)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack4_END         (24)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack5_START       (25)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack5_END         (25)
#define SOC_CRGPERIPH_PERPWRACK_g3dcg0en_START           (26)
#define SOC_CRGPERIPH_PERPWRACK_g3dcg0en_END             (26)
#define SOC_CRGPERIPH_PERPWRACK_modemperipwrack_START    (27)
#define SOC_CRGPERIPH_PERPWRACK_modemperipwrack_END      (27)
#define SOC_CRGPERIPH_PERPWRACK_modemirmpwrack_START     (28)
#define SOC_CRGPERIPH_PERPWRACK_modemirmpwrack_END       (28)
#define SOC_CRGPERIPH_PERPWRACK_ivp32dsppwrack_START     (29)
#define SOC_CRGPERIPH_PERPWRACK_ivp32dsppwrack_END       (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_CLKEN_UNION
 结构说明  : A53_CLKEN 寄存器结构定义。地址偏移量:0x160，初值:0x0000FFFF，宽度:32
 寄存器说明: A53 CLUSTER子系统时钟使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_clkinen_sys                          : 1;  /* bit[0]    : CPU时钟使能系统控制：
                                                                                    0：关闭时钟
                                                                                    1：开启时钟 */
        unsigned int  a53_atclkoff_sys_n                       : 1;  /* bit[1]    : ATCLK时钟门控系统控制：
                                                                                    0：关闭时钟
                                                                                    1：开启时钟 */
        unsigned int  a53_pclkdbg_to_a53_asyn_bri_clkoff_sys_n : 1;  /* bit[2]    : PCLKDBG_TO_A53_ASYN_BRI时钟使能系统控制：
                                                                                    0：关闭时钟
                                                                                    1：开启时钟 */
        unsigned int  a53_atclk_to_asyn_bri_clkoff_sys_n       : 1;  /* bit[3]    : ATCLK_TO_ASYN_BRI时钟使能系统控制：
                                                                                    0：关闭时钟
                                                                                    1：开启时钟 */
        unsigned int  a53_pclkdbg_to_a53_cs_clkoff_sys_n       : 1;  /* bit[4]    : PCLKDBG_TO_A53_CS时钟使能系统控制：
                                                                                    0：关闭时钟
                                                                                    1：开启时钟 */
        unsigned int  reserved                                 : 10; /* bit[5-14] : 保留。 */
        unsigned int  a53_clkoff_sys                           : 1;  /* bit[15]   : A53子系统整体时钟关断使能：
                                                                                    0：时钟维持；
                                                                                    1：时钟关断。 */
        unsigned int  clkmasken                                : 16; /* bit[16-31]: clken每个比特位的使能位：
                                                                                    只有当clkmasken对应的比特位为1'b1，clken相应的比特位才起作用。clkmasken[0]就是clken[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_A53_CLKEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkinen_sys_START                           (0)
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkinen_sys_END                             (0)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclkoff_sys_n_START                        (1)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclkoff_sys_n_END                          (1)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_START  (2)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_END    (2)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclk_to_asyn_bri_clkoff_sys_n_START        (3)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclk_to_asyn_bri_clkoff_sys_n_END          (3)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_cs_clkoff_sys_n_START        (4)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_cs_clkoff_sys_n_END          (4)
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkoff_sys_START                            (15)
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkoff_sys_END                              (15)
#define SOC_CRGPERIPH_A53_CLKEN_clkmasken_START                                 (16)
#define SOC_CRGPERIPH_A53_CLKEN_clkmasken_END                                   (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_RSTEN_UNION
 结构说明  : A53_RSTEN 寄存器结构定义。地址偏移量:0x164，初值:0x00000000，宽度:32
 寄存器说明: A53 CLUSTER子系统软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_coresight_soft_rst_req : 1;  /* bit[0]    : A53 cluster内部coresight 系统软复位请求，高有效 */
        unsigned int  a53_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A53 ADB异步桥系统软复位请求，高有效 */
        unsigned int  a53_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB、CTI、CTM复位请求，电平复位，高有效。有效时将会复位PCLKDBG时钟域的debug逻辑。 */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : 保留。 */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : 保留。 */
        unsigned int  a53_core_rst_software_req  : 4;  /* bit[11-14]: 单核软复位请求，电平复位，高有效。有效时将会复位处理器逻辑，包括core、NEON和VFP。 */
        unsigned int  a53_rst_software_req       : 1;  /* bit[15]   : A53MP整体软复位请求，电平复位，高有效 */
        unsigned int  a53_core_por_rst_req       : 4;  /* bit[16-19]: 单核上电复位请求，电平复位，高有效。有效时将会复位所有的处理器逻辑，包括core、NEON和VFP、debug、PTM及breakpoint、watchpoint等CLK时钟域的全部逻辑。 */
        unsigned int  a53_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm上电复位请求，电平复位，高有效 */
        unsigned int  a53_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm上电复位请求，电平复位，高有效 */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: 保留。 */
        unsigned int  a53_srst_req_en            : 1;  /* bit[31]   : CPU子系统整体软复位使能：
                                                                      0：无效果；
                                                                      1：软复位使能； */
    } reg;
} SOC_CRGPERIPH_A53_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_RSTEN_a53_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_A53_RSTEN_a53_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_A53_RSTEN_a53_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_A53_RSTEN_a53_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_A53_RSTEN_a53_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_A53_RSTEN_a53_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_A53_RSTEN_a53_rst_software_req_START        (15)
#define SOC_CRGPERIPH_A53_RSTEN_a53_rst_software_req_END          (15)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_A53_RSTEN_a53_srst_req_en_START             (31)
#define SOC_CRGPERIPH_A53_RSTEN_a53_srst_req_en_END               (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_RSTDIS_UNION
 结构说明  : A53_RSTDIS 寄存器结构定义。地址偏移量:0x168，初值:0x00000000，宽度:32
 寄存器说明: A53 CLUSTER子系统软复位撤离寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_coresight_soft_rst_req : 1;  /* bit[0]    : A53 cluster内部coresight 系统软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a53_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A53 ADB异步桥系统软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a53_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB、CTI、CTM复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : 保留。 */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : 保留。 */
        unsigned int  a53_core_rst_software_req  : 4;  /* bit[11-14]: 单核软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a53_rst_software_req       : 1;  /* bit[15]   : A53MP整体软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a53_core_por_rst_req       : 4;  /* bit[16-19]: 单核上电复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a53_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm上电复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a53_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm上电复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: 保留。 */
        unsigned int  a53_srst_req_en            : 1;  /* bit[31]   : CPU子系统整体软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
    } reg;
} SOC_CRGPERIPH_A53_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_A53_RSTDIS_a53_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_rst_software_req_START        (15)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_rst_software_req_END          (15)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_srst_req_en_START             (31)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_srst_req_en_END               (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_RSTSTAT_UNION
 结构说明  : A53_RSTSTAT 寄存器结构定义。地址偏移量:0x16C，初值:0x800F0002，宽度:32
 寄存器说明: A53 CLUSTER子系统软复位使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_coresight_soft_rst_req : 1;  /* bit[0]    : A53 cluster内部coresight 系统软复位状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a53_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A53 ADB异步桥系统软复位状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a53_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB、CTI、CTM复位状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : 保留。 */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : 保留。 */
        unsigned int  a53_core_rst_software_req  : 4;  /* bit[11-14]: 单核软复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a53_rst_software_req       : 1;  /* bit[15]   : A53MP整体软复位状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a53_core_por_rst_req       : 4;  /* bit[16-19]: 单核上电复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a53_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm上电复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a53_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm上电复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: 保留。 */
        unsigned int  a53_srst_req_en            : 1;  /* bit[31]   : CPU子系统整体软复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
    } reg;
} SOC_CRGPERIPH_A53_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_rst_software_req_START        (15)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_rst_software_req_END          (15)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_srst_req_en_START             (31)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_srst_req_en_END               (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_ADBLPSTAT_UNION
 结构说明  : A53_ADBLPSTAT 寄存器结构定义。地址偏移量:0x174，初值:0x00000000，宽度:32
 寄存器说明: A53 CLUSTER ADB低功耗寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_d_pwrdnreqn : 1;  /* bit[0]   : ADB-400异步桥下电请求应答信号，低有效 */
        unsigned int  a53_d_pwrdnackn : 1;  /* bit[1]   : ADB-400异步桥下电请求应答信号，低有效 */
        unsigned int  a53_d_cactives  : 1;  /* bit[2]   : 指示ADB-400异步桥中是否尚有活动的transaction。
                                                          0：异步桥中所有transaction都已完成
                                                          1：异步桥中尚存在活动的transaction */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnreqn_START  (0)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnreqn_END    (0)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnackn_START  (1)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnackn_END    (1)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_cactives_START   (2)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_cactives_END     (2)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_CTRL0_UNION
 结构说明  : A53_CTRL0 寄存器结构定义。地址偏移量:0x178，初值:0xFFF0F000，宽度:32
 寄存器说明: A53 CLUSTER控制配置寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_pd_detect_clr       : 1;  /* bit[0]    : A53掉电探测状态清除指示信号 */
        unsigned int  a53_pd_detect_start     : 1;  /* bit[1]    : A53掉电探测开始指示信号 */
        unsigned int  a53_set_acinactm_low    : 1;  /* bit[2]    : ACINACTM生成逻辑bypass信号 */
        unsigned int  a53_set_acinactm_high   : 1;  /* bit[3]    : ACINACTM生成逻辑bypass信号 */
        unsigned int  a53_dbgpwrdup           : 4;  /* bit[4-7]  : CPU核上电指示信号 */
        unsigned int  a53_l2rstdisable        : 1;  /* bit[8]    : 复位阶段禁止L2 cache自动invalidate信号 */
        unsigned int  a53_l1rstdisable        : 1;  /* bit[9]    : 复位阶段禁止L1 cache自动invalidate信号 */
        unsigned int  reserved                : 2;  /* bit[10-11]: 保留。 */
        unsigned int  a53_broadcastcachemaint : 1;  /* bit[12]   : 使能cache一致性操作是否会广播至下游cache：
                                                                   0：一致性操作不会广播至下游cache
                                                                   1：一致性操作会广播至下游cache */
        unsigned int  a53_broadcastouter      : 1;  /* bit[13]   : 是否使能外部shareable操作的广播
                                                                   0：outer shareable操作不广播
                                                                   1：outer shareable会向外广播 */
        unsigned int  a53_broadcastinner      : 1;  /* bit[14]   : 是否使能内部shareable操作的广播
                                                                   0：inner shareable操作不广播
                                                                   1：inner shareable会向外广播 */
        unsigned int  a53_sysbardisable       : 1;  /* bit[15]   : barriers操作是否广播至系统总线
                                                                   0：barriers操作会广播至系统总线
                                                                   1：barriers操作不会广播至系统总线 */
        unsigned int  a53_vinithi             : 4;  /* bit[16-19]: A53启动方式选择，每bit对应一个core：
                                                                   0：从低位地址（0x00000000）启动
                                                                   1：从高位地址（0xFFFF0000）启动 */
        unsigned int  a53_sei_n               : 4;  /* bit[20-23]: 单核system error中断请求信号，低脉冲有效。 */
        unsigned int  a53_rei_n               : 4;  /* bit[24-27]: 单核RAM error中断请求信号，低脉冲有效。 */
        unsigned int  a53_vsei_n              : 4;  /* bit[28-31]: 单核虚拟system error中断请求信号，低脉冲有效。 */
    } reg;
} SOC_CRGPERIPH_A53_CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_clr_START        (0)
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_clr_END          (0)
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_start_START      (1)
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_start_END        (1)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_low_START     (2)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_low_END       (2)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_high_START    (3)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_high_END      (3)
#define SOC_CRGPERIPH_A53_CTRL0_a53_dbgpwrdup_START            (4)
#define SOC_CRGPERIPH_A53_CTRL0_a53_dbgpwrdup_END              (7)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l2rstdisable_START         (8)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l2rstdisable_END           (8)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l1rstdisable_START         (9)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l1rstdisable_END           (9)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastcachemaint_START  (12)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastcachemaint_END    (12)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastouter_START       (13)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastouter_END         (13)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastinner_START       (14)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastinner_END         (14)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sysbardisable_START        (15)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sysbardisable_END          (15)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vinithi_START              (16)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vinithi_END                (19)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sei_n_START                (20)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sei_n_END                  (23)
#define SOC_CRGPERIPH_A53_CTRL0_a53_rei_n_START                (24)
#define SOC_CRGPERIPH_A53_CTRL0_a53_rei_n_END                  (27)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vsei_n_START               (28)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vsei_n_END                 (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_CTRL1_UNION
 结构说明  : A53_CTRL1 寄存器结构定义。地址偏移量:0x17C，初值:0x00000013，宽度:32
 寄存器说明: A53 CLUSTER控制配置寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_cpu     : 16; /* bit[0-15] : a53 CPU memory控制 */
        unsigned int  mem_ctrl_s_a53cs : 16; /* bit[16-31]: a53 ETF ram控制信号，使用TSMC memory，bit分配如下：
                                                            bit[0]：SLP
                                                            bit[1]：DSLP
                                                            bit[2]：SD
                                                            bit[15:3]：unused */
    } reg;
} SOC_CRGPERIPH_A53_CTRL1_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_cpu_START      (0)
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_cpu_END        (15)
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_s_a53cs_START  (16)
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_s_a53cs_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_CTRL2_UNION
 结构说明  : A53_CTRL2 寄存器结构定义。地址偏移量:0x180，初值:0x09F1C020，宽度:32
 寄存器说明: A53 CLUSTER控制配置寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_aa64naa32           : 4;  /* bit[0-3]  : 单核寄存器位宽，复位时采样。
                                                                   0：AArch32；
                                                                   1：AArch64。 */
        unsigned int  a53_ret_ctrl_ret        : 3;  /* bit[4-6]  : A53MP noncpu部分正常工作模式下memory控制信号。Bit分配如下：
                                                                   bit[0]：SLP
                                                                   bit[1]：DSLP
                                                                   bit[2]：unused */
        unsigned int  a53_ret_ctrl_norm       : 3;  /* bit[7-9]  : A53MP noncpu部分正常工作模式下memory控制信号。Bit分配如下：
                                                                   bit[0]：SLP
                                                                   bit[1]：DSLP
                                                                   bit[2]：unused */
        unsigned int  a53_wfe_ret_en_l2       : 1;  /* bit[10]   : A53MP noncpu部分WFE状态下自动retention使能 */
        unsigned int  a53_wfi_ret_en_l2       : 1;  /* bit[11]   : A53MP noncpu部分WFI状态下自动retention使能 */
        unsigned int  a53_dyn_ret_en_l2       : 1;  /* bit[12]   : A53MP noncpu部分动态retention全局使能 */
        unsigned int  a53_l2flushreq          : 1;  /* bit[13]   : L2硬件flush请求。 */
        unsigned int  a53_sys_cnt_en_dly      : 6;  /* bit[14-19]: A53 sysconter 采样en延迟 */
        unsigned int  a53_ret_wait_cycle      : 6;  /* bit[20-25]: A53 L2 RAM退出ret状态延迟 */
        unsigned int  a53_ret_wait_cycle_chg  : 1;  /* bit[26]   : 动态修改等待周期时，给出的采样使能信号 */
        unsigned int  a53_l2_input_lat_sel    : 1;  /* bit[27]   : L2 RAM输入延迟配置 */
        unsigned int  a53_l2_output_lat_sel   : 1;  /* bit[28]   : L2 RAM输出延迟配置 */
        unsigned int  a53_stretch_l2ramclk_en : 1;  /* bit[29]   : L2 RAM时钟扩展使能 */
        unsigned int  reserved                : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_CTRL2_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL2_a53_aa64naa32_START            (0)
#define SOC_CRGPERIPH_A53_CTRL2_a53_aa64naa32_END              (3)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_ret_START         (4)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_ret_END           (6)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_norm_START        (7)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_norm_END          (9)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfe_ret_en_l2_START        (10)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfe_ret_en_l2_END          (10)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfi_ret_en_l2_START        (11)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfi_ret_en_l2_END          (11)
#define SOC_CRGPERIPH_A53_CTRL2_a53_dyn_ret_en_l2_START        (12)
#define SOC_CRGPERIPH_A53_CTRL2_a53_dyn_ret_en_l2_END          (12)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2flushreq_START           (13)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2flushreq_END             (13)
#define SOC_CRGPERIPH_A53_CTRL2_a53_sys_cnt_en_dly_START       (14)
#define SOC_CRGPERIPH_A53_CTRL2_a53_sys_cnt_en_dly_END         (19)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_START       (20)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_END         (25)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_chg_START   (26)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_chg_END     (26)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_input_lat_sel_START     (27)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_input_lat_sel_END       (27)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_output_lat_sel_START    (28)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_output_lat_sel_END      (28)
#define SOC_CRGPERIPH_A53_CTRL2_a53_stretch_l2ramclk_en_START  (29)
#define SOC_CRGPERIPH_A53_CTRL2_a53_stretch_l2ramclk_en_END    (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_STAT_UNION
 结构说明  : A53_STAT 寄存器结构定义。地址偏移量:0x194，初值:0x0000100F，宽度:32
 寄存器说明: A53 CLUSTER状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_standbywfi   : 4;  /* bit[0-3]  : 指示CPU是否处于WFI状态 */
        unsigned int  a53_standbywfe   : 4;  /* bit[4-7]  : 指示CPU是否处于WFE状态 */
        unsigned int  a53_smpen        : 4;  /* bit[8-11] : 0：Disables receiving of instruction cache and TLB maintenance operations. This is the reset 
                                                            value
                                                            1：Enables receiving of instruction cache and TLB maintenance operations */
        unsigned int  a53_standbywfil2 : 1;  /* bit[12]   : 指示L2是否处于WFI状态 */
        unsigned int  a53_dbgack       : 1;  /* bit[13]   : A53 core进入debug状态后的状态指示，高有效。当任一core进入debug状态时，该信号有效 */
        unsigned int  a53_l2flushdone  : 1;  /* bit[14]   : L2硬件flush已完成。 */
        unsigned int  a53_idle_flag    : 1;  /* bit[15]   : a53idle指示状态，为1表示idle，可以切tcxo */
        unsigned int  a53_sbgpwrupreq  : 4;  /* bit[16-19]: Processor powerup request:
                                                            0: No request for processor power up.
                                                            1: Request for processor power up. */
        unsigned int  a53_dbgnopwrdwn  : 4;  /* bit[20-23]: No powerdown request. On a powerdown request:
                                                            0: The SoC power controller powers down the processor.
                                                            1: The SoC power controller does not power down the processor */
        unsigned int  a53_snoop_cnt    : 6;  /* bit[24-29]: A53 snoop counter计数值 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_STAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfi_START    (0)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfi_END      (3)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfe_START    (4)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfe_END      (7)
#define SOC_CRGPERIPH_A53_STAT_a53_smpen_START         (8)
#define SOC_CRGPERIPH_A53_STAT_a53_smpen_END           (11)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfil2_START  (12)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfil2_END    (12)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgack_START        (13)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgack_END          (13)
#define SOC_CRGPERIPH_A53_STAT_a53_l2flushdone_START   (14)
#define SOC_CRGPERIPH_A53_STAT_a53_l2flushdone_END     (14)
#define SOC_CRGPERIPH_A53_STAT_a53_idle_flag_START     (15)
#define SOC_CRGPERIPH_A53_STAT_a53_idle_flag_END       (15)
#define SOC_CRGPERIPH_A53_STAT_a53_sbgpwrupreq_START   (16)
#define SOC_CRGPERIPH_A53_STAT_a53_sbgpwrupreq_END     (19)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgnopwrdwn_START   (20)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgnopwrdwn_END     (23)
#define SOC_CRGPERIPH_A53_STAT_a53_snoop_cnt_START     (24)
#define SOC_CRGPERIPH_A53_STAT_a53_snoop_cnt_END       (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_CLKEN_UNION
 结构说明  : MAIA_CLKEN 寄存器结构定义。地址偏移量:0x1C0，初值:0x0000FFFF，宽度:32
 寄存器说明: A57 CLUSTER子系统时钟使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_clkinen_sys                          : 1;  /* bit[0]    : CPU时钟使能系统控制：
                                                                                    0：关闭时钟
                                                                                    1：开启时钟 */
        unsigned int  a57_atclkoff_sys_n                       : 1;  /* bit[1]    : ATCLK时钟门控系统控制：
                                                                                    0：关闭时钟
                                                                                    1：开启时钟 */
        unsigned int  a57_pclkdbg_to_a53_asyn_bri_clkoff_sys_n : 1;  /* bit[2]    : PCLKDBG_TO_A53_ASYN_BRI时钟使能系统控制：
                                                                                    0：关闭时钟
                                                                                    1：开启时钟 */
        unsigned int  a57_atclk_to_asyn_bri_clkoff_sys_n       : 1;  /* bit[3]    : ATCLK_TO_ASYN_BRI时钟使能系统控制：
                                                                                    0：关闭时钟
                                                                                    1：开启时钟 */
        unsigned int  reserved                                 : 11; /* bit[4-14] : 保留。 */
        unsigned int  a57_clkoff_sys                           : 1;  /* bit[15]   : A57子系统整体时钟关断使能：
                                                                                    0：时钟维持；
                                                                                    1：时钟关断。 */
        unsigned int  clkmasken                                : 16; /* bit[16-31]: clken每个比特位的使能位：
                                                                                    只有当clkmasken对应的比特位为1'b1，clken相应的比特位才起作用。clkmasken[0]就是clken[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_MAIA_CLKEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkinen_sys_START                           (0)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkinen_sys_END                             (0)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclkoff_sys_n_START                        (1)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclkoff_sys_n_END                          (1)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_START  (2)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_END    (2)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclk_to_asyn_bri_clkoff_sys_n_START        (3)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclk_to_asyn_bri_clkoff_sys_n_END          (3)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkoff_sys_START                            (15)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkoff_sys_END                              (15)
#define SOC_CRGPERIPH_MAIA_CLKEN_clkmasken_START                                 (16)
#define SOC_CRGPERIPH_MAIA_CLKEN_clkmasken_END                                   (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_RSTEN_UNION
 结构说明  : MAIA_RSTEN 寄存器结构定义。地址偏移量:0x1C4，初值:0x00000000，宽度:32
 寄存器说明: A57 CLUSTER子系统软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_coresight_soft_rst_req : 1;  /* bit[0]    : A53 cluster内部coresight 系统软复位请求，高有效 */
        unsigned int  a57_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A53 ADB异步桥系统软复位请求，高有效 */
        unsigned int  a57_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB、CTI、CTM复位请求，电平复位，高有效。有效时将会复位PCLKDBG时钟域的debug逻辑。 */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : 保留。 */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : 保留。 */
        unsigned int  a57_core_rst_software_req  : 4;  /* bit[11-14]: 单核软复位请求，电平复位，高有效。有效时将会复位处理器逻辑，包括core、NEON和VFP。 */
        unsigned int  a57_rst_software_req       : 1;  /* bit[15]   : A53MP整体软复位请求，电平复位，高有效 */
        unsigned int  a57_core_por_rst_req       : 4;  /* bit[16-19]: 单核上电复位请求，电平复位，高有效。有效时将会复位所有的处理器逻辑，包括core、NEON和VFP、debug、PTM及breakpoint、watchpoint等CLK时钟域的全部逻辑。 */
        unsigned int  a57_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm上电复位请求，电平复位，高有效 */
        unsigned int  a57_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm上电复位请求，电平复位，高有效 */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: 保留。 */
        unsigned int  a57_srst_req_en            : 1;  /* bit[31]   : CPU子系统整体软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
    } reg;
} SOC_CRGPERIPH_MAIA_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_rst_software_req_START        (15)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_rst_software_req_END          (15)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_srst_req_en_START             (31)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_srst_req_en_END               (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_RSTDIS_UNION
 结构说明  : MAIA_RSTDIS 寄存器结构定义。地址偏移量:0x1C8，初值:0x00000000，宽度:32
 寄存器说明: A57 CLUSTER子系统软复位撤离寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_coresight_soft_rst_req : 1;  /* bit[0]    : A57 cluster内部coresight 系统软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a57_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A57 ADB异步桥系统软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a57_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB、CTI、CTM复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : 保留。 */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : 保留。 */
        unsigned int  a57_core_rst_software_req  : 4;  /* bit[11-14]: 单核软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a57_rst_software_req       : 1;  /* bit[15]   : A53MP整体软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a57_core_por_rst_req       : 4;  /* bit[16-19]: 单核上电复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a57_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm上电复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  a57_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm上电复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: 保留。 */
        unsigned int  a57_srst_req_en            : 1;  /* bit[31]   : CPU子系统整体软复位撤销：
                                                                      0：无效果；
                                                                      1：软复位撤销； */
    } reg;
} SOC_CRGPERIPH_MAIA_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_rst_software_req_START        (15)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_rst_software_req_END          (15)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_srst_req_en_START             (31)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_srst_req_en_END               (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_RSTSTAT_UNION
 结构说明  : MAIA_RSTSTAT 寄存器结构定义。地址偏移量:0x1CC，初值:0x800F0002，宽度:32
 寄存器说明: A57 CLUSTER子系统软复位使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_coresight_soft_rst_req : 1;  /* bit[0]    : A57 cluster内部coresight 系统软复位状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a57_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A57 ADB异步桥系统软复位状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a57_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB、CTI、CTM复位状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : 保留。 */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : 保留。 */
        unsigned int  a57_core_rst_software_req  : 4;  /* bit[11-14]: 单核软复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a57_rst_software_req       : 1;  /* bit[15]   : A53MP整体软复位状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a57_core_por_rst_req       : 4;  /* bit[16-19]: 单核上电复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a57_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm上电复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  a57_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm上电复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: 保留。 */
        unsigned int  a57_srst_req_en            : 1;  /* bit[31]   : CPU子系统整体软复位使能状态：
                                                                      0：软复位不使能；
                                                                      1：软复位使能； */
    } reg;
} SOC_CRGPERIPH_MAIA_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_rst_software_req_START        (15)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_rst_software_req_END          (15)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_srst_req_en_START             (31)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_srst_req_en_END               (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_ADBLPSTAT_UNION
 结构说明  : MAIA_ADBLPSTAT 寄存器结构定义。地址偏移量:0x1D4，初值:0x00000000，宽度:32
 寄存器说明: A57 CLUSTER ADB低功耗寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_d_pwrdnreqn : 1;  /* bit[0]   : ADB-400异步桥下电请求应答信号，低有效 */
        unsigned int  a57_d_pwrdnackn : 1;  /* bit[1]   : ADB-400异步桥下电请求应答信号，低有效 */
        unsigned int  a57_d_cactives  : 1;  /* bit[2]   : 指示ADB-400异步桥中是否尚有活动的transaction。
                                                          0：异步桥中所有transaction都已完成
                                                          1：异步桥中尚存在活动的transaction */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnreqn_START  (0)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnreqn_END    (0)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnackn_START  (1)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnackn_END    (1)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_cactives_START   (2)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_cactives_END     (2)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_CTRL0_UNION
 结构说明  : MAIA_CTRL0 寄存器结构定义。地址偏移量:0x1D8，初值:0xFFF0F000，宽度:32
 寄存器说明: A57 CLUSTER控制配置寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_pd_detect_clr       : 1;  /* bit[0]    : A57掉电探测状态清除指示信号 */
        unsigned int  a57_pd_detect_start     : 1;  /* bit[1]    : A57掉电探测开始指示信号 */
        unsigned int  a57_set_acinactm_low    : 1;  /* bit[2]    : ACINACTM生成逻辑bypass信号 */
        unsigned int  a57_set_acinactm_high   : 1;  /* bit[3]    : ACINACTM生成逻辑bypass信号 */
        unsigned int  a57_dbgpwrdup           : 4;  /* bit[4-7]  : CPU核上电指示信号 */
        unsigned int  a57_l2rstdisable        : 1;  /* bit[8]    : 复位阶段禁止L2 cache自动invalidate信号 */
        unsigned int  a57_l1rstdisable        : 1;  /* bit[9]    : 复位阶段禁止L1 cache自动invalidate信号 */
        unsigned int  reserved                : 2;  /* bit[10-11]: 保留。 */
        unsigned int  a57_broadcastcachemaint : 1;  /* bit[12]   : 使能cache一致性操作是否会广播至下游cache：
                                                                   0：一致性操作不会广播至下游cache
                                                                   1：一致性操作会广播至下游cache */
        unsigned int  a57_broadcastouter      : 1;  /* bit[13]   : 是否使能外部shareable操作的广播
                                                                   0：outer shareable操作不广播
                                                                   1：outer shareable会向外广播 */
        unsigned int  a57_broadcastinner      : 1;  /* bit[14]   : 是否使能内部shareable操作的广播
                                                                   0：inner shareable操作不广播
                                                                   1：inner shareable会向外广播 */
        unsigned int  a57_sysbardisable       : 1;  /* bit[15]   : barriers操作是否广播至系统总线
                                                                   0：barriers操作会广播至系统总线
                                                                   1：barriers操作不会广播至系统总线 */
        unsigned int  a57_vinithi             : 4;  /* bit[16-19]: A53启动方式选择，每bit对应一个core：
                                                                   0：从低位地址（0x00000000）启动
                                                                   1：从高位地址（0xFFFF0000）启动 */
        unsigned int  a57_sei_n               : 4;  /* bit[20-23]: 单核system error中断请求信号，低脉冲有效。 */
        unsigned int  a57_rei_n               : 4;  /* bit[24-27]: 单核RAM error中断请求信号，低脉冲有效。 */
        unsigned int  a57_vsei_n              : 4;  /* bit[28-31]: 单核虚拟system error中断请求信号，低脉冲有效。 */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_clr_START        (0)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_clr_END          (0)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_start_START      (1)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_start_END        (1)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_low_START     (2)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_low_END       (2)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_high_START    (3)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_high_END      (3)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_dbgpwrdup_START            (4)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_dbgpwrdup_END              (7)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l2rstdisable_START         (8)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l2rstdisable_END           (8)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l1rstdisable_START         (9)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l1rstdisable_END           (9)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastcachemaint_START  (12)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastcachemaint_END    (12)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastouter_START       (13)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastouter_END         (13)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastinner_START       (14)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastinner_END         (14)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sysbardisable_START        (15)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sysbardisable_END          (15)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vinithi_START              (16)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vinithi_END                (19)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sei_n_START                (20)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sei_n_END                  (23)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_rei_n_START                (24)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_rei_n_END                  (27)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vsei_n_START               (28)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vsei_n_END                 (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_CTRL1_UNION
 结构说明  : MAIA_CTRL1 寄存器结构定义。地址偏移量:0x1DC，初值:0x0000000B，宽度:32
 寄存器说明: A57 CLUSTER控制配置寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_apu     : 16; /* bit[0-15] : a57 CPU memory控制 */
        unsigned int  mem_ctrl_s_a53cs : 16; /* bit[16-31]: a57 ETF ram控制信号，使用TSMC memory，bit分配如下：
                                                            bit[0]：SLP
                                                            bit[1]：DSLP
                                                            bit[2]：SD
                                                            bit[15:3]：unused */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL1_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_apu_START      (0)
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_apu_END        (15)
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_s_a53cs_START  (16)
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_s_a53cs_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_CTRL2_UNION
 结构说明  : MAIA_CTRL2 寄存器结构定义。地址偏移量:0x1E0，初值:0x01F1C020，宽度:32
 寄存器说明: A57 CLUSTER控制配置寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_aa64naa32          : 4;  /* bit[0-3]  : 单核寄存器位宽，复位时采样。
                                                                  0：AArch32；
                                                                  1：AArch64。 */
        unsigned int  a57_ret_ctrl_ret       : 3;  /* bit[4-6]  : A57MP noncpu部分正常工作模式下memory控制信号。Bit分配如下：
                                                                  bit[0]：SLP
                                                                  bit[1]：DSLP
                                                                  bit[2]：unused */
        unsigned int  a57_ret_ctrl_norm      : 3;  /* bit[7-9]  : A57MP noncpu部分正常工作模式下memory控制信号。Bit分配如下：
                                                                  bit[0]：SLP
                                                                  bit[1]：DSLP
                                                                  bit[2]：unused */
        unsigned int  a57_wfe_ret_en_l2      : 1;  /* bit[10]   : A57MP noncpu部分WFE状态下自动retention使能 */
        unsigned int  a57_wfi_ret_en_l2      : 1;  /* bit[11]   : A57MP noncpu部分WFI状态下自动retention使能 */
        unsigned int  a57_dyn_ret_en_l2      : 1;  /* bit[12]   : A57MP noncpu部分动态retention全局使能 */
        unsigned int  a57_l2flushreq         : 1;  /* bit[13]   : L2硬件flush请求。 */
        unsigned int  a57_sys_cnt_en_dly     : 6;  /* bit[14-19]: A57 sysconter 采样en延迟 */
        unsigned int  a57_ret_wait_cycle     : 6;  /* bit[20-25]: A57 L2 RAM退出ret状态延迟 */
        unsigned int  a57_ret_wait_cycle_chg : 1;  /* bit[26]   : 动态修改等待周期时，给出的采样使能信号 */
        unsigned int  reserved               : 1;  /* bit[27]   : 保留。 */
        unsigned int  a57_pmusnapshotreq     : 4;  /* bit[28-31]: pmubug请求 */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL2_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_aa64naa32_START           (0)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_aa64naa32_END             (3)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_ret_START        (4)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_ret_END          (6)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_norm_START       (7)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_norm_END         (9)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfe_ret_en_l2_START       (10)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfe_ret_en_l2_END         (10)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfi_ret_en_l2_START       (11)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfi_ret_en_l2_END         (11)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_dyn_ret_en_l2_START       (12)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_dyn_ret_en_l2_END         (12)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_l2flushreq_START          (13)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_l2flushreq_END            (13)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_sys_cnt_en_dly_START      (14)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_sys_cnt_en_dly_END        (19)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_START      (20)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_END        (25)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_chg_START  (26)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_chg_END    (26)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_pmusnapshotreq_START      (28)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_pmusnapshotreq_END        (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_STAT_UNION
 结构说明  : MAIA_STAT 寄存器结构定义。地址偏移量:0x1F4，初值:0x0000100F，宽度:32
 寄存器说明: A57 CLUSTER状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_standbywfi   : 4;  /* bit[0-3]  : 指示CPU是否处于WFI状态 */
        unsigned int  a57_standbywfe   : 4;  /* bit[4-7]  : 指示CPU是否处于WFE状态 */
        unsigned int  a57_smpen        : 4;  /* bit[8-11] : 0：Disables receiving of instruction cache and TLB maintenance operations. This is the reset 
                                                            value
                                                            1：Enables receiving of instruction cache and TLB maintenance operations */
        unsigned int  a57_standbywfil2 : 1;  /* bit[12]   : 指示L2是否处于WFI状态 */
        unsigned int  a57_dbgack       : 1;  /* bit[13]   : A53 core进入debug状态后的状态指示，高有效。当任一core进入debug状态时，该信号有效 */
        unsigned int  a57_l2flushdone  : 1;  /* bit[14]   : L2硬件flush已完成。 */
        unsigned int  a57_idle_flag    : 1;  /* bit[15]   : a57idle指示状态，为1表示idle，可以切tcxo */
        unsigned int  a57_sbgpwrupreq  : 4;  /* bit[16-19]: Processor powerup request:
                                                            0: No request for processor power up.
                                                            1: Request for processor power up. */
        unsigned int  a57_dbgnopwrdwn  : 4;  /* bit[20-23]: No powerdown request. On a powerdown request:
                                                            0: The SoC power controller powers down the processor.
                                                            1: The SoC power controller does not power down the processor */
        unsigned int  a57_snoop_cnt    : 6;  /* bit[24-29]: A53 snoop counter计数值 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_STAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfi_START    (0)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfi_END      (3)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfe_START    (4)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfe_END      (7)
#define SOC_CRGPERIPH_MAIA_STAT_a57_smpen_START         (8)
#define SOC_CRGPERIPH_MAIA_STAT_a57_smpen_END           (11)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfil2_START  (12)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfil2_END    (12)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgack_START        (13)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgack_END          (13)
#define SOC_CRGPERIPH_MAIA_STAT_a57_l2flushdone_START   (14)
#define SOC_CRGPERIPH_MAIA_STAT_a57_l2flushdone_END     (14)
#define SOC_CRGPERIPH_MAIA_STAT_a57_idle_flag_START     (15)
#define SOC_CRGPERIPH_MAIA_STAT_a57_idle_flag_END       (15)
#define SOC_CRGPERIPH_MAIA_STAT_a57_sbgpwrupreq_START   (16)
#define SOC_CRGPERIPH_MAIA_STAT_a57_sbgpwrupreq_END     (19)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgnopwrdwn_START   (20)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgnopwrdwn_END     (23)
#define SOC_CRGPERIPH_MAIA_STAT_a57_snoop_cnt_START     (24)
#define SOC_CRGPERIPH_MAIA_STAT_a57_snoop_cnt_END       (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_STAT_1_UNION
 结构说明  : MAIA_STAT_1 寄存器结构定义。地址偏移量:0x1F8，初值:0x00000000，宽度:32
 寄存器说明: A57 CLUSTER状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_pmusnapshotack : 4;  /* bit[0-3] : a57 pmusnapshotack */
        unsigned int  reserved           : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_STAT_1_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_STAT_1_a57_pmusnapshotack_START  (0)
#define SOC_CRGPERIPH_MAIA_STAT_1_a57_pmusnapshotack_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CORESIGHTSTAT_UNION
 结构说明  : CORESIGHTSTAT 寄存器结构定义。地址偏移量:0x200，初值:0x00000000，宽度:32
 寄存器说明: core sight状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_CORESIGHTSTAT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CORESIGHTLPSTAT_UNION
 结构说明  : CORESIGHTLPSTAT 寄存器结构定义。地址偏移量:0x204，初值:0x00000003，宽度:32
 寄存器说明: core sight低功耗寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csysreq_etr_lpi : 1;  /* bit[0]   : ETR AXI master接口停止请求，低有效 */
        unsigned int  csysack_etr_lpi : 1;  /* bit[1]   : ETR AXI master接口停止应答，低有效 */
        unsigned int  cactive_etr_lpi : 1;  /* bit[2]   : 始终为低，指示低功耗请求被接受 */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_CORESIGHTLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysreq_etr_lpi_START  (0)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysreq_etr_lpi_END    (0)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysack_etr_lpi_START  (1)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysack_etr_lpi_END    (1)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_cactive_etr_lpi_START  (2)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_cactive_etr_lpi_END    (2)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CORESIGHTCTRL0_UNION
 结构说明  : CORESIGHTCTRL0 寄存器结构定义。地址偏移量:0x208，初值:0x00000000，宽度:32
 寄存器说明: core sight控制配置寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_s_cssys : 16; /* bit[0-15] : ETF ram控制信号，使用TSMC memory，bit分配如下：
                                                            bit[0]：SLP
                                                            bit[1]：DSLP
                                                            bit[2]：SD
                                                            bit[15:3]：unused */
        unsigned int  reserved         : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_CORESIGHTCTRL0_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTCTRL0_mem_ctrl_s_cssys_START  (0)
#define SOC_CRGPERIPH_CORESIGHTCTRL0_mem_ctrl_s_cssys_END    (15)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CORESIGHTETFINT_UNION
 结构说明  : CORESIGHTETFINT 寄存器结构定义。地址偏移量:0x20C，初值:0x00000000，宽度:32
 寄存器说明: core sight ETF中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  etf_a53_1_full : 1;  /* bit[0]   : ETF A53 CLUSTER1 FULL指示，高有效。 */
        unsigned int  etf_a53_0_full : 1;  /* bit[1]   : ETF A53 CLUSTER0 FULL指示，高有效。 */
        unsigned int  etf_top_full   : 1;  /* bit[2]   : ETF TOP FULL指示，高有效。 */
        unsigned int  reserved       : 29; /* bit[3-31]: 保留。由etf_top_full、etf_a53_0_full、etf_a53_1_full产生的中断intr_etf_full，可通过写该寄存器写清。 */
    } reg;
} SOC_CRGPERIPH_CORESIGHTETFINT_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_1_full_START  (0)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_1_full_END    (0)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_0_full_START  (1)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_0_full_END    (1)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_top_full_START    (2)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_top_full_END      (2)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CORESIGHTETRINT_UNION
 结构说明  : CORESIGHTETRINT 寄存器结构定义。地址偏移量:0x210，初值:0x00000000，宽度:32
 寄存器说明: core sight ETR中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  etr_top_full         : 1;  /* bit[0]   : ETR FULL指示，高有效。 */
        unsigned int  intr_a53_0_core0_gic : 1;  /* bit[1]   : a53_0_core0 原始gic中断寄存 */
        unsigned int  intr_a53_0_core1_gic : 1;  /* bit[2]   : a53_0_core1 原始gic中断寄存 */
        unsigned int  intr_a53_0_core2_gic : 1;  /* bit[3]   : a53_0_core2 原始gic中断寄存 */
        unsigned int  intr_a53_0_core3_gic : 1;  /* bit[4]   : a53_0_core3 原始gic中断寄存 */
        unsigned int  intr_a53_1_core0_gic : 1;  /* bit[5]   : a53_1_core0 原始gic中断寄存 */
        unsigned int  intr_a53_1_core1_gic : 1;  /* bit[6]   : a53_1_core1 原始gic中断寄存 */
        unsigned int  intr_a53_1_core2_gic : 1;  /* bit[7]   : a53_1_core2 原始gic中断寄存 */
        unsigned int  intr_a53_1_core3_gic : 1;  /* bit[8]   : a53_1_core3 原始gic中断寄存 */
        unsigned int  reserved             : 23; /* bit[9-31]: 保留。由etr_top_full产生的中断intr_etr_full，写清。 */
    } reg;
} SOC_CRGPERIPH_CORESIGHTETRINT_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTETRINT_etr_top_full_START          (0)
#define SOC_CRGPERIPH_CORESIGHTETRINT_etr_top_full_END            (0)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core0_gic_START  (1)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core0_gic_END    (1)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core1_gic_START  (2)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core1_gic_END    (2)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core2_gic_START  (3)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core2_gic_END    (3)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core3_gic_START  (4)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core3_gic_END    (4)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core0_gic_START  (5)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core0_gic_END    (5)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core1_gic_START  (6)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core1_gic_END    (6)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core2_gic_START  (7)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core2_gic_END    (7)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core3_gic_START  (8)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core3_gic_END    (8)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CCI400STAT1_UNION
 结构说明  : CCI400STAT1 寄存器结构定义。地址偏移量:0x21C，初值:0x00000000，宽度:32
 寄存器说明: CCI400状态寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rs_awvalid_s3        : 1;  /* bit[0]    : S3接口的awvalid状态；
                                                                0：awvalid无效；
                                                                1：awvalid有效。 */
        unsigned int  rs_arvalid_s3        : 1;  /* bit[1]    : S3接口的arvalid状态；
                                                                0：arvalid无效；
                                                                1：arvalid有效。 */
        unsigned int  rs_awvalid_s4        : 1;  /* bit[2]    : S4接口的awvalid状态；
                                                                0：awvalid无效；
                                                                1：awvalid有效。 */
        unsigned int  rs_arvalid_s4        : 1;  /* bit[3]    : S4接口的arvalid状态；
                                                                0：arvalid无效；
                                                                1：arvalid有效。 */
        unsigned int  cactive_asi_s3       : 1;  /* bit[4]    : S3的ASI模块是否有操作在处理；
                                                                0：有操作；
                                                                1：无操作。 */
        unsigned int  cactive_asi_s4       : 1;  /* bit[5]    : S4的ASI模块是否有操作在处理；
                                                                0：有操作；
                                                                1：无操作。 */
        unsigned int  dvm_complete_expect1 : 2;  /* bit[6-7]  : 第一组dvm complete的master信息（发起dvm complete方）；注意dvm complete完成后该信息不清除；
                                                                0：空闲状态，无发起dvm complete的master信息；
                                                                1：dvm complete发起方是A53；
                                                                2：dvm complete发起方是MAIA；
                                                                3：保留；  */
        unsigned int  dvm_complete_expect2 : 2;  /* bit[8-9]  : 第二组dvm complete的master信息（发起dvm complete方）；注意dvm complete完成后该信息不清除；
                                                                0：空闲状态，无发起dvm complete的master信息；
                                                                1：dvm complete发起方是A53；
                                                                2：dvm complete发起方是MAIA；
                                                                3：保留；  */
        unsigned int  dvm_complete_expect3 : 2;  /* bit[10-11]: 第三组dvm complete的master信息（发起dvm complete方）；注意dvm complete完成后该信息不清除；
                                                                0：空闲状态，无发起dvm complete的master信息；
                                                                1：dvm complete发起方是A53；
                                                                2：dvm complete发起方是MAIA；
                                                                3：保留；  */
        unsigned int  dvm_complete_expect4 : 2;  /* bit[12-13]: 第四组dvm complete的master信息（发起dvm complete方）；注意dvm complete完成后该信息不清除；
                                                                0：空闲状态，无发起dvm complete的master信息；
                                                                1：dvm complete发起方是A53；
                                                                2：dvm complete发起方是MAIA；
                                                                3：保留； */
        unsigned int  dvm_complete_expect5 : 2;  /* bit[14-15]: 第五组dvm complete的master信息（发起dvm complete方）；注意dvm complete完成后改信息不清除；
                                                                0：空闲状态，无发起dvm complete的master信息；
                                                                1：dvm complete发起方是A53；
                                                                2：dvm complete发起方是MAIA；
                                                                3：保留；  */
        unsigned int  srb_entry_expect_cr3 : 1;  /* bit[16]   : A53的CR通道上是否有未完成的命令；
                                                                0：无未完成的命令；
                                                                1：有未完成的命令。  */
        unsigned int  srb_entry_expect_cd3 : 1;  /* bit[17]   : A53的CD通道上是否有未完成的命令；
                                                                0：无未完成的命令；
                                                                1：有未完成的命令。 */
        unsigned int  srb_entry_expect_cr4 : 1;  /* bit[18]   : MAIA的CR通道上是否有未完成的命令；
                                                                0：无未完成的命令；
                                                                1：有未完成的命令。 */
        unsigned int  srb_entry_expect_cd4 : 1;  /* bit[19]   : MAIA的CD通道上是否有未完成的命令；
                                                                0：无未完成的命令；
                                                                1：有未完成的命令。 */
        unsigned int  dvm_scoreboard1      : 2;  /* bit[20-21]: 第一组dvm sync完成与否的状态指示（发起dvm sync方）；
                                                                0：A53和MAIA均无未完成的dvm sync；
                                                                1：A53有未完成的dvm sync；
                                                                2：MAIA有未完成的dvm sync；
                                                                3：A53和MAIA均有未完成的dvm sync； */
        unsigned int  dvm_scoreboard2      : 2;  /* bit[22-23]: 第二组dvm sync完成与否的状态指示（发起dvm sync方）；
                                                                0：A53和MAIA均无未完成的dvm sync；
                                                                1：A53有未完成的dvm sync；
                                                                2：MAIA有未完成的dvm sync；
                                                                3：A53和MAIA均有未完成的dvm sync； */
        unsigned int  dvm_scoreboard3      : 2;  /* bit[24-25]: 第三组dvm sync完成与否的状态指示（发起dvm sync方）；
                                                                0：A53和MAIA均无未完成的dvm sync；
                                                                1：A53有未完成的dvm sync；
                                                                2：MAIA有未完成的dvm sync；
                                                                3：A53和MAIA均有未完成的dvm sync； */
        unsigned int  dvm_scoreboard4      : 2;  /* bit[26-27]: 第四组dvm sync完成与否的状态指示（发起dvm sync方）；
                                                                0：A53和MAIA均无未完成的dvm sync；
                                                                1：A53有未完成的dvm sync；
                                                                2：MAIA有未完成的dvm sync；
                                                                3：A53和MAIA均有未完成的dvm sync； */
        unsigned int  dvm_scoreboard5      : 2;  /* bit[28-29]: 第五组dvm sync完成与否的状态指示（发起dvm sync方）；
                                                                0：A53和MAIA均无未完成的dvm sync；
                                                                1：A53有未完成的dvm sync；
                                                                2：MAIA有未完成的dvm sync；
                                                                3：A53和MAIA均有未完成的dvm sync； */
        unsigned int  reserved             : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_CCI400STAT1_UNION;
#endif
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s3_START         (0)
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s3_END           (0)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s3_START         (1)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s3_END           (1)
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s4_START         (2)
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s4_END           (2)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s4_START         (3)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s4_END           (3)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s3_START        (4)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s3_END          (4)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s4_START        (5)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s4_END          (5)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect1_START  (6)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect1_END    (7)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect2_START  (8)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect2_END    (9)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect3_START  (10)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect3_END    (11)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect4_START  (12)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect4_END    (13)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect5_START  (14)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect5_END    (15)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr3_START  (16)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr3_END    (16)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd3_START  (17)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd3_END    (17)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr4_START  (18)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr4_END    (18)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd4_START  (19)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd4_END    (19)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard1_START       (20)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard1_END         (21)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard2_START       (22)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard2_END         (23)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard3_START       (24)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard3_END         (25)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard4_START       (26)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard4_END         (27)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard5_START       (28)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard5_END         (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ADB400STAT_UNION
 结构说明  : ADB400STAT 寄存器结构定义。地址偏移量:0x220，初值:0x00000000，宽度:32
 寄存器说明: ADB400状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cactivem_adb400_a53_0 : 1;  /* bit[0]   : indicates if there is still an transaction in the bridge */
        unsigned int  cactivem_adb400_a53_1 : 1;  /* bit[1]   : indicates if there is still an transaction in the bridge */
        unsigned int  cactivem_adb400_g3d_0 : 1;  /* bit[2]   : indicates if there is still an transaction in the bridge */
        unsigned int  cactivem_adb400_g3d_1 : 1;  /* bit[3]   : indicates if there is still an transaction in the bridge */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ADB400STAT_UNION;
#endif
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_0_START  (0)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_0_END    (0)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_1_START  (1)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_1_END    (1)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_0_START  (2)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_0_END    (2)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_1_START  (3)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_1_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CCI400CTRL0_UNION
 结构说明  : CCI400CTRL0 寄存器结构定义。地址偏移量:0x228，初值:0x0000E000，宽度:32
 寄存器说明: CCI400控制配置寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0         : 10; /* bit[0-9]  : 保留。 */
        unsigned int  bufferableoverride : 3;  /* bit[10-12]: 覆盖 AWCACHE[0]和ARCACHE[0] 的输出为non-bufferable，一个bit对应一个master接口 */
        unsigned int  barrierterminate   : 3;  /* bit[13-15]: barrier操作是terminate类型还是传输类型，一个bit对应一个master接口 */
        unsigned int  reserved_1         : 13; /* bit[16-28]: 保留。 */
        unsigned int  striping_granule   : 3;  /* bit[29-31]: 配置cci交织粒度 */
    } reg;
} SOC_CRGPERIPH_CCI400CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_CCI400CTRL0_bufferableoverride_START  (10)
#define SOC_CRGPERIPH_CCI400CTRL0_bufferableoverride_END    (12)
#define SOC_CRGPERIPH_CCI400CTRL0_barrierterminate_START    (13)
#define SOC_CRGPERIPH_CCI400CTRL0_barrierterminate_END      (15)
#define SOC_CRGPERIPH_CCI400CTRL0_striping_granule_START    (29)
#define SOC_CRGPERIPH_CCI400CTRL0_striping_granule_END      (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CCI400CTRL1_UNION
 结构说明  : CCI400CTRL1 寄存器结构定义。地址偏移量:0x22C，初值:0x00000000，宽度:32
 寄存器说明: CCI400控制配置寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 26; /* bit[0-25] : 保留。 */
        unsigned int  cci_status_sample_en : 1;  /* bit[26]   : CCI内部信号观测是否使能，1为使能 */
        unsigned int  ecorevnum            : 4;  /* bit[27-30]: 用于ECO时，CCI内部寄存器对于ECO版本进行记录。 */
        unsigned int  reserved_1           : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_CRGPERIPH_CCI400CTRL1_UNION;
#endif
#define SOC_CRGPERIPH_CCI400CTRL1_cci_status_sample_en_START  (26)
#define SOC_CRGPERIPH_CCI400CTRL1_cci_status_sample_en_END    (26)
#define SOC_CRGPERIPH_CCI400CTRL1_ecorevnum_START             (27)
#define SOC_CRGPERIPH_CCI400CTRL1_ecorevnum_END               (30)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_CCI400STAT_UNION
 结构说明  : CCI400STAT 寄存器结构定义。地址偏移量:0x230，初值:0x00000000，宽度:32
 寄存器说明: CCI400状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  activem0 : 1;  /* bit[0]   : clock gating输出，输出给外部状态控制器，做低功耗控制使用 */
        unsigned int  activem1 : 1;  /* bit[1]   : clock gating输出，输出给外部状态控制器，做低功耗控制使用 */
        unsigned int  activem2 : 1;  /* bit[2]   : clock gating输出，输出给外部状态控制器，做低功耗控制使用 */
        unsigned int  reserved : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_CCI400STAT_UNION;
#endif
#define SOC_CRGPERIPH_CCI400STAT_activem0_START  (0)
#define SOC_CRGPERIPH_CCI400STAT_activem0_END    (0)
#define SOC_CRGPERIPH_CCI400STAT_activem1_START  (1)
#define SOC_CRGPERIPH_CCI400STAT_activem1_END    (1)
#define SOC_CRGPERIPH_CCI400STAT_activem2_START  (2)
#define SOC_CRGPERIPH_CCI400STAT_activem2_END    (2)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_G3D_0_ADBLPSTAT_UNION
 结构说明  : G3D_0_ADBLPSTAT 寄存器结构定义。地址偏移量:0x234，初值:0x00000000，宽度:32
 寄存器说明: G3D ADB0低功耗寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_d_pwrdnreqn : 1;  /* bit[0]   : ADB-400异步桥下电请求应答信号，低有效 */
        unsigned int  g3d_d_pwrdnackn : 1;  /* bit[1]   : ADB-400异步桥下电请求应答信号，低有效 */
        unsigned int  g3d_d_cactives  : 1;  /* bit[2]   : 指示ADB-400异步桥中是否尚有活动的transaction。
                                                          0：异步桥中所有transaction都已完成
                                                          1：异步桥中尚存在活动的transaction */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_G3D_0_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnreqn_START  (0)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnreqn_END    (0)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnackn_START  (1)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnackn_END    (1)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_cactives_START   (2)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_cactives_END     (2)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_G3D_1_ADBLPSTAT_UNION
 结构说明  : G3D_1_ADBLPSTAT 寄存器结构定义。地址偏移量:0x238，初值:0x00000000，宽度:32
 寄存器说明: G3D ADB1低功耗寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_d_pwrdnreqn : 1;  /* bit[0]   : ADB-400异步桥下电请求应答信号，低有效 */
        unsigned int  g3d_d_pwrdnackn : 1;  /* bit[1]   : ADB-400异步桥下电请求应答信号，低有效 */
        unsigned int  g3d_d_cactives  : 1;  /* bit[2]   : 指示ADB-400异步桥中是否尚有活动的transaction。
                                                          0：异步桥中所有transaction都已完成
                                                          1：异步桥中尚存在活动的transaction */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_G3D_1_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnreqn_START  (0)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnreqn_END    (0)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnackn_START  (1)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnackn_END    (1)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_cactives_START   (2)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_cactives_END     (2)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_IPCLKRST_BYPASS0_UNION
 结构说明  : IPCLKRST_BYPASS0 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: 外设IP防挂死功能byapss控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vcodec_clkrst_bypass  : 1;  /* bit[0] : 防挂死功能byapss控制：
                                                              0：bypass无效；
                                                              1：bypass有效。 */
        unsigned int  pctrl_clkrst_bypass   : 1;  /* bit[1] :  */
        unsigned int  pwm_clkrst_bypass     : 1;  /* bit[2] :  */
        unsigned int  reserved              : 1;  /* bit[3] : 保留。 */
        unsigned int  wd0_clkrst_bypass     : 1;  /* bit[4] :  */
        unsigned int  wd1_clkrst_bypass     : 1;  /* bit[5] :  */
        unsigned int  gpio0_clkrst_bypass   : 1;  /* bit[6] :  */
        unsigned int  gpio1_clkrst_bypass   : 1;  /* bit[7] :  */
        unsigned int  gpio2_clkrst_bypass   : 1;  /* bit[8] :  */
        unsigned int  gpio3_clkrst_bypass   : 1;  /* bit[9] :  */
        unsigned int  gpio4_clkrst_bypass   : 1;  /* bit[10]:  */
        unsigned int  gpio5_clkrst_bypass   : 1;  /* bit[11]:  */
        unsigned int  gpio6_clkrst_bypass   : 1;  /* bit[12]:  */
        unsigned int  gpio7_clkrst_bypass   : 1;  /* bit[13]:  */
        unsigned int  gpio8_clkrst_bypass   : 1;  /* bit[14]:  */
        unsigned int  gpio9_clkrst_bypass   : 1;  /* bit[15]:  */
        unsigned int  gpio10_clkrst_bypass  : 1;  /* bit[16]:  */
        unsigned int  gpio11_clkrst_bypass  : 1;  /* bit[17]:  */
        unsigned int  gpio12_clkrst_bypass  : 1;  /* bit[18]:  */
        unsigned int  gpio13_clkrst_bypass  : 1;  /* bit[19]:  */
        unsigned int  gpio14_clkrst_bypass  : 1;  /* bit[20]:  */
        unsigned int  gpio15_clkrst_bypass  : 1;  /* bit[21]:  */
        unsigned int  gpio16_clkrst_bypass  : 1;  /* bit[22]:  */
        unsigned int  gpio17_clkrst_bypass  : 1;  /* bit[23]:  */
        unsigned int  gpio18_clkrst_bypass  : 1;  /* bit[24]:  */
        unsigned int  gpio19_clkrst_bypass  : 1;  /* bit[25]:  */
        unsigned int  gpio20_clkrst_bypass  : 1;  /* bit[26]:  */
        unsigned int  gpio21_clkrst_bypass  : 1;  /* bit[27]:  */
        unsigned int  timer9_clkrst_bypass  : 1;  /* bit[28]:  */
        unsigned int  timer10_clkrst_bypass : 1;  /* bit[29]:  */
        unsigned int  timer11_clkrst_bypass : 1;  /* bit[30]:  */
        unsigned int  timer12_clkrst_bypass : 1;  /* bit[31]:  */
    } reg;
} SOC_CRGPERIPH_IPCLKRST_BYPASS0_UNION;
#endif
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_vcodec_clkrst_bypass_START   (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_vcodec_clkrst_bypass_END     (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pctrl_clkrst_bypass_START    (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pctrl_clkrst_bypass_END      (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pwm_clkrst_bypass_START      (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pwm_clkrst_bypass_END        (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd0_clkrst_bypass_START      (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd0_clkrst_bypass_END        (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd1_clkrst_bypass_START      (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd1_clkrst_bypass_END        (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio0_clkrst_bypass_START    (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio0_clkrst_bypass_END      (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio1_clkrst_bypass_START    (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio1_clkrst_bypass_END      (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio2_clkrst_bypass_START    (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio2_clkrst_bypass_END      (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio3_clkrst_bypass_START    (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio3_clkrst_bypass_END      (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio4_clkrst_bypass_START    (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio4_clkrst_bypass_END      (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio5_clkrst_bypass_START    (11)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio5_clkrst_bypass_END      (11)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio6_clkrst_bypass_START    (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio6_clkrst_bypass_END      (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio7_clkrst_bypass_START    (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio7_clkrst_bypass_END      (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio8_clkrst_bypass_START    (14)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio8_clkrst_bypass_END      (14)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio9_clkrst_bypass_START    (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio9_clkrst_bypass_END      (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio10_clkrst_bypass_START   (16)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio10_clkrst_bypass_END     (16)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio11_clkrst_bypass_START   (17)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio11_clkrst_bypass_END     (17)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio12_clkrst_bypass_START   (18)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio12_clkrst_bypass_END     (18)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio13_clkrst_bypass_START   (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio13_clkrst_bypass_END     (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio14_clkrst_bypass_START   (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio14_clkrst_bypass_END     (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio15_clkrst_bypass_START   (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio15_clkrst_bypass_END     (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio16_clkrst_bypass_START   (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio16_clkrst_bypass_END     (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio17_clkrst_bypass_START   (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio17_clkrst_bypass_END     (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio18_clkrst_bypass_START   (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio18_clkrst_bypass_END     (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio19_clkrst_bypass_START   (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio19_clkrst_bypass_END     (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio20_clkrst_bypass_START   (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio20_clkrst_bypass_END     (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio21_clkrst_bypass_START   (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio21_clkrst_bypass_END     (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer9_clkrst_bypass_START   (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer9_clkrst_bypass_END     (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer10_clkrst_bypass_START  (29)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer10_clkrst_bypass_END    (29)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer11_clkrst_bypass_START  (30)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer11_clkrst_bypass_END    (30)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer12_clkrst_bypass_START  (31)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer12_clkrst_bypass_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_IPCLKRST_BYPASS1_UNION
 结构说明  : IPCLKRST_BYPASS1 寄存器结构定义。地址偏移量:0x244，初值:0x00000000，宽度:32
 寄存器说明: 外设IP防挂死功能byapss控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tzpc_clkrst_bypass     : 1;  /* bit[0] : 防挂死功能byapss控制：
                                                               0：bypass无效；
                                                               1：bypass有效。 */
        unsigned int  ipc0_clkrst_bypass     : 1;  /* bit[1] :  */
        unsigned int  ipc1_clkrst_bypass     : 1;  /* bit[2] :  */
        unsigned int  ioc_clkrst_bypass      : 1;  /* bit[3] :  */
        unsigned int  codecssi_clkrst_bypass : 1;  /* bit[4] :  */
        unsigned int  hkadcssi_clkrst_bypass : 1;  /* bit[5] :  */
        unsigned int  memrep_clkrst_bypass   : 1;  /* bit[6] :  */
        unsigned int  ipc_mdm_clkrst_bypass  : 1;  /* bit[7] :  */
        unsigned int  uart0_clkrst_bypass    : 1;  /* bit[8] :  */
        unsigned int  uart1_clkrst_bypass    : 1;  /* bit[9] :  */
        unsigned int  uart2_clkrst_bypass    : 1;  /* bit[10]:  */
        unsigned int  reserved_0             : 1;  /* bit[11]: 保留。 */
        unsigned int  uart4_clkrst_bypass    : 1;  /* bit[12]:  */
        unsigned int  uart5_clkrst_bypass    : 1;  /* bit[13]:  */
        unsigned int  reserved_1             : 1;  /* bit[14]: 保留。 */
        unsigned int  spi1_clkrst_bypass     : 1;  /* bit[15]:  */
        unsigned int  reserved_2             : 1;  /* bit[16]: 保留。 */
        unsigned int  reserved_3             : 1;  /* bit[17]: 保留。 */
        unsigned int  reserved_4             : 1;  /* bit[18]: 保留。 */
        unsigned int  i2c3_clkrst_bypass     : 1;  /* bit[19]:  */
        unsigned int  i2c4_clkrst_bypass     : 1;  /* bit[20]:  */
        unsigned int  dmac_clkrst_bypass     : 1;  /* bit[21]:  */
        unsigned int  emmc0_clkrst_bypass    : 1;  /* bit[22]:  */
        unsigned int  emmc1_clkrst_bypass    : 1;  /* bit[23]:  */
        unsigned int  sd_clkrst_bypass       : 1;  /* bit[24]:  */
        unsigned int  sdio0_clkrst_bypass    : 1;  /* bit[25]:  */
        unsigned int  socp_clkrst_bypass     : 1;  /* bit[26]:  */
        unsigned int  usb3otg_clkrst_bypass  : 1;  /* bit[27]:  */
        unsigned int  isp_clkrst_bypass      : 1;  /* bit[28]:  */
        unsigned int  dss_clkrst_bypass      : 1;  /* bit[29]:  */
        unsigned int  reserved_5             : 1;  /* bit[30]: 保留。 */
        unsigned int  reserved_6             : 1;  /* bit[31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_IPCLKRST_BYPASS1_UNION;
#endif
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_tzpc_clkrst_bypass_START      (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_tzpc_clkrst_bypass_END        (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc0_clkrst_bypass_START      (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc0_clkrst_bypass_END        (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc1_clkrst_bypass_START      (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc1_clkrst_bypass_END        (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ioc_clkrst_bypass_START       (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ioc_clkrst_bypass_END         (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_codecssi_clkrst_bypass_START  (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_codecssi_clkrst_bypass_END    (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_hkadcssi_clkrst_bypass_START  (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_hkadcssi_clkrst_bypass_END    (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_memrep_clkrst_bypass_START    (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_memrep_clkrst_bypass_END      (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc_mdm_clkrst_bypass_START   (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc_mdm_clkrst_bypass_END     (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart0_clkrst_bypass_START     (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart0_clkrst_bypass_END       (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart1_clkrst_bypass_START     (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart1_clkrst_bypass_END       (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart2_clkrst_bypass_START     (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart2_clkrst_bypass_END       (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart4_clkrst_bypass_START     (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart4_clkrst_bypass_END       (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart5_clkrst_bypass_START     (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart5_clkrst_bypass_END       (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_spi1_clkrst_bypass_START      (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_spi1_clkrst_bypass_END        (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c3_clkrst_bypass_START      (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c3_clkrst_bypass_END        (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c4_clkrst_bypass_START      (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c4_clkrst_bypass_END        (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dmac_clkrst_bypass_START      (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dmac_clkrst_bypass_END        (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc0_clkrst_bypass_START     (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc0_clkrst_bypass_END       (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc1_clkrst_bypass_START     (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc1_clkrst_bypass_END       (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sd_clkrst_bypass_START        (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sd_clkrst_bypass_END          (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sdio0_clkrst_bypass_START     (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sdio0_clkrst_bypass_END       (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_socp_clkrst_bypass_START      (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_socp_clkrst_bypass_END        (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_usb3otg_clkrst_bypass_START   (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_usb3otg_clkrst_bypass_END     (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_isp_clkrst_bypass_START       (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_isp_clkrst_bypass_END         (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dss_clkrst_bypass_START       (29)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dss_clkrst_bypass_END         (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_IPCLKRST_BYPASS2_UNION
 结构说明  : IPCLKRST_BYPASS2 寄存器结构定义。地址偏移量:0x248，初值:0x00000000，宽度:32
 寄存器说明: 外设IP防挂死功能byapss控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_clkrst_bypass           : 1;  /* bit[0]    : 防挂死功能byapss控制：
                                                                       0：bypass无效；
                                                                       1：bypass有效。 */
        unsigned int  reserved_0                  : 1;  /* bit[1]    : 保留。 */
        unsigned int  reserved_1                  : 1;  /* bit[2]    : 保留。 */
        unsigned int  usb3otg_mux_clkrst_bypass   : 1;  /* bit[3]    :  */
        unsigned int  usb3otg_ahbif_clkrst_bypass : 1;  /* bit[4]    :  */
        unsigned int  reserved_2                  : 1;  /* bit[5]    : 保留。 */
        unsigned int  dsi0_clkrst_bypass          : 1;  /* bit[6]    :  */
        unsigned int  dsi1_clkrst_bypass          : 1;  /* bit[7]    :  */
        unsigned int  sdio1_clkrst_bypass         : 1;  /* bit[8]    :  */
        unsigned int  perf_clkrst_bypass          : 1;  /* bit[9]    :  */
        unsigned int  secs_clkrst_bypass          : 1;  /* bit[10]   :  */
        unsigned int  secp_clkrst_bypass          : 1;  /* bit[11]   :  */
        unsigned int  reserved_3                  : 20; /* bit[12-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_IPCLKRST_BYPASS2_UNION;
#endif
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_g3d_clkrst_bypass_START            (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_g3d_clkrst_bypass_END              (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_mux_clkrst_bypass_START    (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_mux_clkrst_bypass_END      (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_ahbif_clkrst_bypass_START  (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_ahbif_clkrst_bypass_END    (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi0_clkrst_bypass_START           (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi0_clkrst_bypass_END             (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi1_clkrst_bypass_START           (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi1_clkrst_bypass_END             (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_sdio1_clkrst_bypass_START          (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_sdio1_clkrst_bypass_END            (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_perf_clkrst_bypass_START           (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_perf_clkrst_bypass_END             (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secs_clkrst_bypass_START           (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secs_clkrst_bypass_END             (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secp_clkrst_bypass_START           (11)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secp_clkrst_bypass_END             (11)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_PDCEN_UNION
 结构说明  : A53_PDCEN 寄存器结构定义。地址偏移量:0x260，初值:0x00000000，宽度:32
 寄存器说明: A53上下电状态机使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_pdc_en : 1;  /* bit[0]   : A53_0上下电状态机使能寄存器
                                                       0：状态机不使能
                                                       1：状态机使能 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_PDCEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_PDCEN_a53_0_pdc_en_START  (0)
#define SOC_CRGPERIPH_A53_PDCEN_a53_0_pdc_en_END    (0)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREPWRINTEN_UNION
 结构说明  : A53_COREPWRINTEN 寄存器结构定义。地址偏移量:0x264，初值:0x00000000，宽度:32
 寄存器说明: A53从核上下电完成中断使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_0_core0_pwr_en : 1;  /* bit[0]    : A53_0 CORE0上下电完成中断使能
                                                                   0：不使能
                                                                   1：使能 */
        unsigned int  intr_a53_0_core1_pwr_en : 1;  /* bit[1]    : A53_0 CORE1上下电完成中断使能
                                                                   0：不使能
                                                                   1：使能 */
        unsigned int  intr_a53_0_core2_pwr_en : 1;  /* bit[2]    : A53_0 CORE2上下电完成中断使能
                                                                   0：不使能
                                                                   1：使能 */
        unsigned int  intr_a53_0_core3_pwr_en : 1;  /* bit[3]    : A53_0 CORE3上下电完成中断使能
                                                                   0：不使能
                                                                   1：使能 */
        unsigned int  reserved                : 12; /* bit[4-15] : 保留。 */
        unsigned int  corepwrintenmasken      : 16; /* bit[16-31]: COREPWRINTEN每个比特位的使能位：
                                                                   只有当corepwrintenmasken对应的比特位为1'b1，core_pwr_en相应的比特位才起作用。corepwrintenmasken[0]就是core_pwr_en[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_A53_COREPWRINTEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core0_pwr_en_START  (0)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core0_pwr_en_END    (0)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core1_pwr_en_START  (1)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core1_pwr_en_END    (1)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core2_pwr_en_START  (2)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core2_pwr_en_END    (2)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core3_pwr_en_START  (3)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core3_pwr_en_END    (3)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_corepwrintenmasken_START       (16)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_corepwrintenmasken_END         (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREPWRINTSTAT_UNION
 结构说明  : A53_COREPWRINTSTAT 寄存器结构定义。地址偏移量:0x268，初值:0x00000000，宽度:32
 寄存器说明: A53从核上下电完成中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_0_core0_pwr_stat : 1;  /* bit[0]   : A53_0 CORE0上下电完成中断状态，写1清除中断状态
                                                                    0：上下电没有完成
                                                                    1：上下电完成 */
        unsigned int  intr_a53_0_core1_pwr_stat : 1;  /* bit[1]   : A53_0 CORE1上下电完成中断状态，写1清除中断状态
                                                                    0：上下电没有完成
                                                                    1：上下电完成 */
        unsigned int  intr_a53_0_core2_pwr_stat : 1;  /* bit[2]   : A53_0 CORE2上下电完成中断状态，写1清除中断状态
                                                                    0：上下电没有完成
                                                                    1：上下电完成 */
        unsigned int  intr_a53_0_core3_pwr_stat : 1;  /* bit[3]   : A53_0 CORE3上下电完成中断状态，写1清除中断状态
                                                                    0：上下电没有完成
                                                                    1：上下电完成 */
        unsigned int  reserved                  : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREPWRINTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core0_pwr_stat_START  (0)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core0_pwr_stat_END    (0)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core1_pwr_stat_START  (1)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core1_pwr_stat_END    (1)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core2_pwr_stat_START  (2)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core2_pwr_stat_END    (2)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core3_pwr_stat_START  (3)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core3_pwr_stat_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREGICMASK_UNION
 结构说明  : A53_COREGICMASK 寄存器结构定义。地址偏移量:0x26C，初值:0x00000000，宽度:32
 寄存器说明: A53从核GIC中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_0_core0_gic_mask : 1;  /* bit[0]   : A53_0 CORE0 GIC中断屏蔽
                                                                    0：状态机响应gic中断，自动上电
                                                                    1：状态机不响应gic中断 */
        unsigned int  intr_a53_0_core1_gic_mask : 1;  /* bit[1]   : A53_0 CORE1 GIC中断屏蔽
                                                                    0：状态机响应gic中断，自动上电
                                                                    0：状态机不响应gic中断 */
        unsigned int  intr_a53_0_core2_gic_mask : 1;  /* bit[2]   : A53_0 CORE2 GIC中断屏蔽
                                                                    0：状态机响应gic中断，自动上电
                                                                    1：状态机不响应gic中断 */
        unsigned int  intr_a53_0_core3_gic_mask : 1;  /* bit[3]   : A53_0 CORE3 GIC中断屏蔽
                                                                    0：状态机响应gic中断，自动上电
                                                                    1：状态机不响应gic中断 */
        unsigned int  reserved                  : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREGICMASK_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core0_gic_mask_START  (0)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core0_gic_mask_END    (0)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core1_gic_mask_START  (1)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core1_gic_mask_END    (1)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core2_gic_mask_START  (2)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core2_gic_mask_END    (2)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core3_gic_mask_START  (3)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core3_gic_mask_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREPOWERUP_UNION
 结构说明  : A53_COREPOWERUP 寄存器结构定义。地址偏移量:0x270，初值:0x00000000，宽度:32
 寄存器说明: A53从核上电请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core0_pwrup_req : 1;  /* bit[0]   : A53_0 CORE0 上电请求，写1请求上电 */
        unsigned int  a53_0_core1_pwrup_req : 1;  /* bit[1]   : A53_0 CORE1 上电请求，写1请求上电 */
        unsigned int  a53_0_core2_pwrup_req : 1;  /* bit[2]   : A53_0 CORE2 上电请求，写1请求上电 */
        unsigned int  a53_0_core3_pwrup_req : 1;  /* bit[3]   : A53_0 CORE3 上电请求，写1请求上电 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREPOWERUP_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core0_pwrup_req_START  (0)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core0_pwrup_req_END    (0)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core1_pwrup_req_START  (1)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core1_pwrup_req_END    (1)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core2_pwrup_req_START  (2)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core2_pwrup_req_END    (2)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core3_pwrup_req_START  (3)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core3_pwrup_req_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREPOWERDN_UNION
 结构说明  : A53_COREPOWERDN 寄存器结构定义。地址偏移量:0x274，初值:0x00000000，宽度:32
 寄存器说明: A53从核下电请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core0_pwrdn_req : 1;  /* bit[0]   : A53_0 CORE0 下电请求，写1请求下电 */
        unsigned int  a53_0_core1_pwrdn_req : 1;  /* bit[1]   : A53_0 CORE1 下电请求，写1请求下电 */
        unsigned int  a53_0_core2_pwrdn_req : 1;  /* bit[2]   : A53_0 CORE2 下电请求，写1请求下电 */
        unsigned int  a53_0_core3_pwrdn_req : 1;  /* bit[3]   : A53_0 CORE3 下电请求，写1请求下电 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREPOWERDN_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core0_pwrdn_req_START  (0)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core0_pwrdn_req_END    (0)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core1_pwrdn_req_START  (1)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core1_pwrdn_req_END    (1)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core2_pwrdn_req_START  (2)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core2_pwrdn_req_END    (2)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core3_pwrdn_req_START  (3)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core3_pwrdn_req_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREPOWERSTAT_UNION
 结构说明  : A53_COREPOWERSTAT 寄存器结构定义。地址偏移量:0x278，初值:0x00000000，宽度:32
 寄存器说明: A53从核状态机状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core0_pwr_stat : 4;  /* bit[0-3]  : A53_0 CORE0 状态机状态
                                                                0000：ST_PWRDN
                                                                0001：ST_UP_RESET
                                                                0010：ST_UP_POWER
                                                                0011：ST_UP_ISO
                                                                0100：ST_UP_URESET
                                                                0101：ST_UP_DBGPWR
                                                                0110：ST_PWRON
                                                                0111：ST_DN_WFI
                                                                1000：ST_DN_DBGPWR
                                                                1001：ST_DN_ISO
                                                                1010：ST_DN_POWER */
        unsigned int  a53_0_core1_pwr_stat : 4;  /* bit[4-7]  : A53_0 CORE1 状态机状态
                                                                0000：ST_PWRDN
                                                                0001：ST_UP_RESET
                                                                0010：ST_UP_POWER
                                                                0011：ST_UP_ISO
                                                                0100：ST_UP_URESET
                                                                0101：ST_UP_DBGPWR
                                                                0110：ST_PWRON
                                                                0111：ST_DN_WFI
                                                                1000：ST_DN_DBGPWR
                                                                1001：ST_DN_ISO
                                                                1010：ST_DN_POWER */
        unsigned int  a53_0_core2_pwr_stat : 4;  /* bit[8-11] : A53_0 CORE2 状态机状态
                                                                0000：ST_PWRDN
                                                                0010：ST_UP_POWER
                                                                0011：ST_UP_ISO
                                                                0100：ST_UP_URESET
                                                                0101：ST_UP_DBGPWR
                                                                0110：ST_PWRON
                                                                0111：ST_DN_WFI
                                                                1000：ST_DN_DBGPWR
                                                                1001：ST_DN_ISO
                                                                1010：ST_DN_POWER */
        unsigned int  a53_0_core3_pwr_stat : 4;  /* bit[12-15]: A53_0 CORE3 状态机状态
                                                                0000：ST_PWRDN
                                                                0001：ST_UP_RESET
                                                                0010：ST_UP_POWER
                                                                0011：ST_UP_ISO
                                                                0100：ST_UP_URESET
                                                                0101：ST_UP_DBGPWR
                                                                0110：ST_PWRON
                                                                0111：ST_DN_WFI
                                                                1000：ST_DN_DBGPWR
                                                                1001：ST_DN_ISO
                                                                1010：ST_DN_POWER */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREPOWERSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core0_pwr_stat_START  (0)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core0_pwr_stat_END    (3)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core1_pwr_stat_START  (4)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core1_pwr_stat_END    (7)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core2_pwr_stat_START  (8)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core2_pwr_stat_END    (11)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core3_pwr_stat_START  (12)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core3_pwr_stat_END    (15)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREPWRUPTIME_UNION
 结构说明  : A53_COREPWRUPTIME 寄存器结构定义。地址偏移量:0x27C，初值:0x000030D4，宽度:32
 寄存器说明: A53从核上电时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_pwrup_time : 16; /* bit[0-15] : A53_0从核上电时间，默认100us */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREPWRUPTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRUPTIME_a53_0_core_pwrup_time_START  (0)
#define SOC_CRGPERIPH_A53_COREPWRUPTIME_a53_0_core_pwrup_time_END    (15)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREPWRDNTIME_UNION
 结构说明  : A53_COREPWRDNTIME 寄存器结构定义。地址偏移量:0x280，初值:0x000004E2，宽度:32
 寄存器说明: A53从核下电时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_pwrdn_time : 16; /* bit[0-15] : A53_0从核下电时间，默认10us */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREPWRDNTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRDNTIME_a53_0_core_pwrdn_time_START  (0)
#define SOC_CRGPERIPH_A53_COREPWRDNTIME_a53_0_core_pwrdn_time_END    (15)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREISOTIME_UNION
 结构说明  : A53_COREISOTIME 寄存器结构定义。地址偏移量:0x284，初值:0x0000000F，宽度:32
 寄存器说明: A53从核钳位配置时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_iso_time : 5;  /* bit[0-4] : A53_0从核钳位和解钳位时间，默认16个pclk */
        unsigned int  reserved            : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREISOTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREISOTIME_a53_0_core_iso_time_START  (0)
#define SOC_CRGPERIPH_A53_COREISOTIME_a53_0_core_iso_time_END    (4)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREDBGTIME_UNION
 结构说明  : A53_COREDBGTIME 寄存器结构定义。地址偏移量:0x288，初值:0x00000007，宽度:32
 寄存器说明: A53从核DBG配置时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_dbg_time : 4;  /* bit[0-3] : A53_0从核DBG信号配置时间，默认8个pclk */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREDBGTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREDBGTIME_a53_0_core_dbg_time_START  (0)
#define SOC_CRGPERIPH_A53_COREDBGTIME_a53_0_core_dbg_time_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_CORERSTTIME_UNION
 结构说明  : A53_CORERSTTIME 寄存器结构定义。地址偏移量:0x28C，初值:0x00000007，宽度:32
 寄存器说明: A53从核复位时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_rst_time : 3;  /* bit[0-2] : A53_0从核复位时间，默认8个pclk */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_CORERSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_CORERSTTIME_a53_0_core_rst_time_START  (0)
#define SOC_CRGPERIPH_A53_CORERSTTIME_a53_0_core_rst_time_END    (2)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_COREURSTTIME_UNION
 结构说明  : A53_COREURSTTIME 寄存器结构定义。地址偏移量:0x290，初值:0x0000000F，宽度:32
 寄存器说明: A53从核解复位时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_urst_time : 6;  /* bit[0-5] : A53_0从核解复位时间，默认16个pclk */
        unsigned int  reserved             : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_A53_COREURSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREURSTTIME_a53_0_core_urst_time_START  (0)
#define SOC_CRGPERIPH_A53_COREURSTTIME_a53_0_core_urst_time_END    (5)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_PDCEN_UNION
 结构说明  : MAIA_PDCEN 寄存器结构定义。地址偏移量:0x300，初值:0x00000000，宽度:32
 寄存器说明: MAIA上下电状态机使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_1_pdc_en : 1;  /* bit[0]   : A53_1上下电状态机使能寄存器
                                                       0：状态机不使能
                                                       1：状态机使能 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_PDCEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_PDCEN_a57_1_pdc_en_START  (0)
#define SOC_CRGPERIPH_MAIA_PDCEN_a57_1_pdc_en_END    (0)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREPWRINTEN_UNION
 结构说明  : MAIA_COREPWRINTEN 寄存器结构定义。地址偏移量:0x304，初值:0x00000000，宽度:32
 寄存器说明: MAIA_从核上下电完成中断使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_1_core0_pwr_en : 1;  /* bit[0]    : A53_1 CORE0上下电完成中断使能
                                                                   0：不使能
                                                                   1：使能 */
        unsigned int  intr_a53_1_core1_pwr_en : 1;  /* bit[1]    : A53_1 CORE1上下电完成中断使能
                                                                   0：不使能
                                                                   1：使能 */
        unsigned int  intr_a53_1_core2_pwr_en : 1;  /* bit[2]    : A53_1 CORE2上下电完成中断使能
                                                                   0：不使能
                                                                   1：使能 */
        unsigned int  intr_a53_1_core3_pwr_en : 1;  /* bit[3]    : A53_1 CORE3上下电完成中断使能
                                                                   0：不使能
                                                                   1：使能 */
        unsigned int  reserved                : 12; /* bit[4-15] : 保留。 */
        unsigned int  corepwrintenmasken      : 16; /* bit[16-31]: COREPWRINTEN每个比特位的使能位：
                                                                   只有当corepwrintenmasken对应的比特位为1'b1，core_pwr_en相应的比特位才起作用。corepwrintenmasken[0]就是core_pwr_en[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRINTEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core0_pwr_en_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core0_pwr_en_END    (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core1_pwr_en_START  (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core1_pwr_en_END    (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core2_pwr_en_START  (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core2_pwr_en_END    (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core3_pwr_en_START  (3)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core3_pwr_en_END    (3)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_corepwrintenmasken_START       (16)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_corepwrintenmasken_END         (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_UNION
 结构说明  : MAIA_COREPWRINTSTAT 寄存器结构定义。地址偏移量:0x308，初值:0x00000000，宽度:32
 寄存器说明: MAIA从核上下电完成中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_1_core0_pwr_stat : 1;  /* bit[0]   : A53_1 CORE0上下电完成中断状态，写1清除中断状态
                                                                    0：上下电没有完成
                                                                    1：上下电完成 */
        unsigned int  intr_a53_1_core1_pwr_stat : 1;  /* bit[1]   : A53_1 CORE1上下电完成中断状态，写1清除中断状态
                                                                    0：上下电没有完成
                                                                    1：上下电完成 */
        unsigned int  intr_a53_1_core2_pwr_stat : 1;  /* bit[2]   : A53_1 CORE2上下电完成中断状态，写1清除中断状态
                                                                    0：上下电没有完成
                                                                    1：上下电完成 */
        unsigned int  intr_a53_1_core3_pwr_stat : 1;  /* bit[3]   : A53_1 CORE3上下电完成中断状态，写1清除中断状态
                                                                    0：上下电没有完成
                                                                    1：上下电完成 */
        unsigned int  reserved                  : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core0_pwr_stat_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core0_pwr_stat_END    (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core1_pwr_stat_START  (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core1_pwr_stat_END    (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core2_pwr_stat_START  (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core2_pwr_stat_END    (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core3_pwr_stat_START  (3)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core3_pwr_stat_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREGICMASK_UNION
 结构说明  : MAIA_COREGICMASK 寄存器结构定义。地址偏移量:0x30C，初值:0x00000000，宽度:32
 寄存器说明: MAIA从核GIC中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_1_core0_gic_mask : 1;  /* bit[0]   : A53_1 CORE0 GIC中断屏蔽
                                                                    0：状态机响应gic中断，自动上电
                                                                    1：状态机不响应gic中断 */
        unsigned int  intr_a53_1_core1_gic_mask : 1;  /* bit[1]   : A53_1 CORE1 GIC中断屏蔽
                                                                    0：状态机响应gic中断，自动上电
                                                                    0：状态机不响应gic中断 */
        unsigned int  intr_a53_1_core2_gic_mask : 1;  /* bit[2]   : A53_1 CORE2 GIC中断屏蔽
                                                                    0：状态机响应gic中断，自动上电
                                                                    1：状态机不响应gic中断 */
        unsigned int  intr_a53_1_core3_gic_mask : 1;  /* bit[3]   : A53_1 CORE3 GIC中断屏蔽
                                                                    0：状态机响应gic中断，自动上电
                                                                    1：状态机不响应gic中断 */
        unsigned int  reserved                  : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREGICMASK_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core0_gic_mask_START  (0)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core0_gic_mask_END    (0)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core1_gic_mask_START  (1)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core1_gic_mask_END    (1)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core2_gic_mask_START  (2)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core2_gic_mask_END    (2)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core3_gic_mask_START  (3)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core3_gic_mask_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREPOWERUP_UNION
 结构说明  : MAIA_COREPOWERUP 寄存器结构定义。地址偏移量:0x310，初值:0x00000000，宽度:32
 寄存器说明: MAIA从核上电请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core0_pwrup_req : 1;  /* bit[0]   : A53_1 CORE0 上电请求，写1请求上电 */
        unsigned int  a53_1_core1_pwrup_req : 1;  /* bit[1]   : A53_1 CORE1 上电请求，写1请求上电 */
        unsigned int  a53_1_core2_pwrup_req : 1;  /* bit[2]   : A53_1 CORE2 上电请求，写1请求上电 */
        unsigned int  a53_1_core3_pwrup_req : 1;  /* bit[3]   : A53_1 CORE3 上电请求，写1请求上电 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPOWERUP_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core0_pwrup_req_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core0_pwrup_req_END    (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core1_pwrup_req_START  (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core1_pwrup_req_END    (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core2_pwrup_req_START  (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core2_pwrup_req_END    (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core3_pwrup_req_START  (3)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core3_pwrup_req_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREPOWERDN_UNION
 结构说明  : MAIA_COREPOWERDN 寄存器结构定义。地址偏移量:0x314，初值:0x00000000，宽度:32
 寄存器说明: MAIA从核下电请求寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core0_pwrdn_req : 1;  /* bit[0]   : A53_1 CORE0 下电请求，写1请求下电 */
        unsigned int  a53_1_core1_pwrdn_req : 1;  /* bit[1]   : A53_1 CORE1 下电请求，写1请求下电 */
        unsigned int  a53_1_core2_pwrdn_req : 1;  /* bit[2]   : A53_1 CORE2 下电请求，写1请求下电 */
        unsigned int  a53_1_core3_pwrdn_req : 1;  /* bit[3]   : A53_1 CORE3 下电请求，写1请求下电 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPOWERDN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core0_pwrdn_req_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core0_pwrdn_req_END    (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core1_pwrdn_req_START  (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core1_pwrdn_req_END    (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core2_pwrdn_req_START  (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core2_pwrdn_req_END    (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core3_pwrdn_req_START  (3)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core3_pwrdn_req_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREPOWERSTAT_UNION
 结构说明  : MAIA_COREPOWERSTAT 寄存器结构定义。地址偏移量:0x318，初值:0x00000000，宽度:32
 寄存器说明: MAIA从核状态机状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core0_pwr_stat : 4;  /* bit[0-3]  : A53_1 CORE0 状态机状态
                                                                0000：ST_PWRDN
                                                                0001：ST_UP_RESET
                                                                0010：ST_UP_POWER
                                                                0011：ST_UP_ISO
                                                                0100：ST_UP_URESET
                                                                0101：ST_UP_DBGPWR
                                                                0110：ST_PWRON
                                                                0111：ST_DN_WFI
                                                                1000：ST_DN_DBGPWR
                                                                1001：ST_DN_ISO
                                                                1010：ST_DN_POWER */
        unsigned int  a53_1_core1_pwr_stat : 4;  /* bit[4-7]  : A53_1 CORE1 状态机状态
                                                                0000：ST_PWRDN
                                                                0001：ST_UP_RESET
                                                                0010：ST_UP_POWER
                                                                0011：ST_UP_ISO
                                                                0100：ST_UP_URESET
                                                                0101：ST_UP_DBGPWR
                                                                0110：ST_PWRON
                                                                0111：ST_DN_WFI
                                                                1000：ST_DN_DBGPWR
                                                                1001：ST_DN_ISO
                                                                1010：ST_DN_POWER */
        unsigned int  a53_1_core2_pwr_stat : 4;  /* bit[8-11] : A53_1 CORE2 状态机状态
                                                                0000：ST_PWRDN
                                                                0001：ST_UP_RESET
                                                                0010：ST_UP_POWER
                                                                0011：ST_UP_ISO
                                                                0100：ST_UP_URESET
                                                                0101：ST_UP_DBGPWR
                                                                0110：ST_PWRON
                                                                0111：ST_DN_WFI
                                                                1000：ST_DN_DBGPWR
                                                                1001：ST_DN_ISO
                                                                1010：ST_DN_POWER */
        unsigned int  a53_1_core3_pwr_stat : 4;  /* bit[12-15]: A53_1 CORE3 状态机状态
                                                                0000：ST_PWRDN
                                                                0001：ST_UP_RESET
                                                                0010：ST_UP_POWER
                                                                0011：ST_UP_ISO
                                                                0100：ST_UP_URESET
                                                                0101：ST_UP_DBGPWR
                                                                0110：ST_PWRON
                                                                0111：ST_DN_WFI
                                                                1000：ST_DN_DBGPWR
                                                                1001：ST_DN_ISO
                                                                1010：ST_DN_POWER */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPOWERSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core0_pwr_stat_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core0_pwr_stat_END    (3)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core1_pwr_stat_START  (4)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core1_pwr_stat_END    (7)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core2_pwr_stat_START  (8)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core2_pwr_stat_END    (11)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core3_pwr_stat_START  (12)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core3_pwr_stat_END    (15)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREPWRUPTIME_UNION
 结构说明  : MAIA_COREPWRUPTIME 寄存器结构定义。地址偏移量:0x31C，初值:0x000030D4，宽度:32
 寄存器说明: MAIA从核上电时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_pwrup_time : 16; /* bit[0-15] : A53_1从核上电时间，默认100us */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRUPTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRUPTIME_a53_1_core_pwrup_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPWRUPTIME_a53_1_core_pwrup_time_END    (15)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREPWRDNTIME_UNION
 结构说明  : MAIA_COREPWRDNTIME 寄存器结构定义。地址偏移量:0x320，初值:0x000004E2，宽度:32
 寄存器说明: MAIA从核下电时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_pwrdn_time : 16; /* bit[0-15] : A53_1从核下电时间，默认10us */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRDNTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRDNTIME_a53_1_core_pwrdn_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPWRDNTIME_a53_1_core_pwrdn_time_END    (15)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREISOTIME_UNION
 结构说明  : MAIA_COREISOTIME 寄存器结构定义。地址偏移量:0x324，初值:0x0000000F，宽度:32
 寄存器说明: MAIA从核钳位配置时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_iso_time : 5;  /* bit[0-4] : A53_1从核钳位和解钳位时间，默认16个pclk */
        unsigned int  reserved            : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREISOTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREISOTIME_a53_1_core_iso_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREISOTIME_a53_1_core_iso_time_END    (4)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREDBGTIME_UNION
 结构说明  : MAIA_COREDBGTIME 寄存器结构定义。地址偏移量:0x328，初值:0x00000007，宽度:32
 寄存器说明: MAIA从核DBG配置时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_dbg_time : 4;  /* bit[0-3] : A53_1从核DBG信号配置时间，默认8个pclk */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREDBGTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREDBGTIME_a53_1_core_dbg_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREDBGTIME_a53_1_core_dbg_time_END    (3)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_CORERSTTIME_UNION
 结构说明  : MAIA_CORERSTTIME 寄存器结构定义。地址偏移量:0x32C，初值:0x00000007，宽度:32
 寄存器说明: MAIA从核复位时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_rst_time : 3;  /* bit[0-2] : A53_1从核复位时间，默认8个pclk */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_CORERSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CORERSTTIME_a53_1_core_rst_time_START  (0)
#define SOC_CRGPERIPH_MAIA_CORERSTTIME_a53_1_core_rst_time_END    (2)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_COREURSTTIME_UNION
 结构说明  : MAIA_COREURSTTIME 寄存器结构定义。地址偏移量:0x330，初值:0x0000000F，宽度:32
 寄存器说明: MAIA从核解复位时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_urst_time : 6;  /* bit[0-5] : A53_1从核解复位时间，默认16个pclk */
        unsigned int  reserved             : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MAIA_COREURSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREURSTTIME_a53_1_core_urst_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREURSTTIME_a53_1_core_urst_time_END    (5)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISPA7_CLKEN_UNION
 结构说明  : ISPA7_CLKEN 寄存器结构定义。地址偏移量:0x340，初值:0x0000017F，宽度:32
 寄存器说明: ISPA7子系统时钟使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_clkinen                    : 1;  /* bit[0]    : CPU时钟使能系统控制：
                                                                            0：关闭时钟
                                                                            1：开启时钟 */
        unsigned int  ispa7_atclkoff_n                 : 1;  /* bit[1]    : ATCLK时钟门控系统控制：
                                                                            0：关闭时钟
                                                                            1：开启时钟 */
        unsigned int  pclkdbg_to_asyn_bri_clkoff_n     : 1;  /* bit[2]    : PCLKDBG_TO_A7_ASYN_BRI时钟使能系统控制：
                                                                            0：关闭时钟
                                                                            1：开启时钟 */
        unsigned int  ispa7_atclk_to_asyn_bri_clkoff_n : 1;  /* bit[3]    : ATCLK_TO_ASYN_BRI时钟使能系统控制：
                                                                            0：关闭时钟；
                                                                            1：开启时钟 */
        unsigned int  ispa7_pclkdbg_to_cs_clkoff_n     : 1;  /* bit[4]    : PCLKDBG_TO_A7_CS时钟使能系统控制：
                                                                            0：关闭时钟
                                                                            1：开启时钟 */
        unsigned int  ispa7_aclkenm_sel                : 1;  /* bit[5]    : A7 ACE master接口时钟频率比选择：
                                                                            0：1:1
                                                                            1：1:2 */
        unsigned int  ispa7_sys_cnt_en_dly             : 4;  /* bit[6-9]  : system counter采样使能信号延时设定 */
        unsigned int  reserved                         : 6;  /* bit[10-15]: 保留。 */
        unsigned int  clkmasken                        : 16; /* bit[16-31]: clken每个比特位的使能位：
                                                                            只有当clkmasken对应的比特位为1'b1，clken相应的比特位才起作用。clkmasken[0]就是clken[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_ISPA7_CLKEN_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_clkinen_START                     (0)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_clkinen_END                       (0)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclkoff_n_START                  (1)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclkoff_n_END                    (1)
#define SOC_CRGPERIPH_ISPA7_CLKEN_pclkdbg_to_asyn_bri_clkoff_n_START      (2)
#define SOC_CRGPERIPH_ISPA7_CLKEN_pclkdbg_to_asyn_bri_clkoff_n_END        (2)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclk_to_asyn_bri_clkoff_n_START  (3)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclk_to_asyn_bri_clkoff_n_END    (3)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_pclkdbg_to_cs_clkoff_n_START      (4)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_pclkdbg_to_cs_clkoff_n_END        (4)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_aclkenm_sel_START                 (5)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_aclkenm_sel_END                   (5)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_sys_cnt_en_dly_START              (6)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_sys_cnt_en_dly_END                (9)
#define SOC_CRGPERIPH_ISPA7_CLKEN_clkmasken_START                         (16)
#define SOC_CRGPERIPH_ISPA7_CLKEN_clkmasken_END                           (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISPA7_RSTEN_UNION
 结构说明  : ISPA7_RSTEN 寄存器结构定义。地址偏移量:0x344，初值:0x00000000，宽度:32
 寄存器说明: ISPA7子系统软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_core_por_rst_req       : 1;  /* bit[0]   : 单核上电复位请求，电平复位，高有效 */
        unsigned int  ispa7_rst_software_req       : 1;  /* bit[1]   : A7所有核软复位请求，电平复位，高有效 */
        unsigned int  ispa7_core_rst_software_req  : 1;  /* bit[2]   : 单核软复位请求，电平复位，高有效 */
        unsigned int  ispa7_debug_all_rst_req      : 1;  /* bit[3]   : Debug 逻辑总复位请求，电平复位，高有效 */
        unsigned int  ispa7_core_debug_rst_req     : 1;  /* bit[4]   : 单核debug逻辑复位请求，电平复位，高有效 */
        unsigned int  ispa7_coresight_soft_rst_req : 1;  /* bit[5]   : Coresight 系统软复位请求，高有效 */
        unsigned int  ispa7_dbgrstreq              : 1;  /* bit[6]   : 除Debug APB、CTI和CTM外所有逻辑复位请求，电平复位，高有效 */
        unsigned int  reserved                     : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISPA7_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_por_rst_req_START        (0)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_por_rst_req_END          (0)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_rst_software_req_START        (1)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_rst_software_req_END          (1)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_rst_software_req_START   (2)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_rst_software_req_END     (2)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_debug_all_rst_req_START       (3)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_debug_all_rst_req_END         (3)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_debug_rst_req_START      (4)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_debug_rst_req_END        (4)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_coresight_soft_rst_req_START  (5)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_coresight_soft_rst_req_END    (5)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_dbgrstreq_START               (6)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_dbgrstreq_END                 (6)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISPA7_RSTDIS_UNION
 结构说明  : ISPA7_RSTDIS 寄存器结构定义。地址偏移量:0x348，初值:0x00000000，宽度:32
 寄存器说明: ISPA7子系统软复位撤离寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_core_por_rst_req       : 1;  /* bit[0]   : 单核上电复位请求，电平复位，高有效 */
        unsigned int  ispa7_rst_software_req       : 1;  /* bit[1]   : A7所有核软复位请求，电平复位，高有效 */
        unsigned int  ispa7_core_rst_software_req  : 1;  /* bit[2]   : 单核软复位请求，电平复位，高有效 */
        unsigned int  ispa7_debug_all_rst_req      : 1;  /* bit[3]   : Debug 逻辑总复位请求，电平复位，高有效 */
        unsigned int  ispa7_core_debug_rst_req     : 1;  /* bit[4]   : 单核debug逻辑复位请求，电平复位，高有效 */
        unsigned int  ispa7_coresight_soft_rst_req : 1;  /* bit[5]   : Coresight 系统软复位请求，高有效 */
        unsigned int  ispa7_dbgrstreq              : 1;  /* bit[6]   : 除Debug APB、CTI和CTM外所有逻辑复位请求，电平复位，高有效 */
        unsigned int  reserved                     : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISPA7_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_por_rst_req_START        (0)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_por_rst_req_END          (0)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_rst_software_req_START        (1)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_rst_software_req_END          (1)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_rst_software_req_START   (2)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_rst_software_req_END     (2)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_debug_all_rst_req_START       (3)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_debug_all_rst_req_END         (3)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_debug_rst_req_START      (4)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_debug_rst_req_END        (4)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_coresight_soft_rst_req_START  (5)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_coresight_soft_rst_req_END    (5)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_dbgrstreq_START               (6)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_dbgrstreq_END                 (6)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISPA7_RSTSTAT_UNION
 结构说明  : ISPA7_RSTSTAT 寄存器结构定义。地址偏移量:0x34C，初值:0x00000000，宽度:32
 寄存器说明: ISPA7子系统软复位使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_core_por_rst_req       : 1;  /* bit[0]   : 单核上电复位请求，电平复位，高有效 */
        unsigned int  ispa7_rst_software_req       : 1;  /* bit[1]   : A7所有核软复位请求，电平复位，高有效 */
        unsigned int  ispa7_core_rst_software_req  : 1;  /* bit[2]   : 单核软复位请求，电平复位，高有效 */
        unsigned int  ispa7_debug_all_rst_req      : 1;  /* bit[3]   : Debug 逻辑总复位请求，电平复位，高有效 */
        unsigned int  ispa7_core_debug_rst_req     : 1;  /* bit[4]   : 单核debug逻辑复位请求，电平复位，高有效 */
        unsigned int  ispa7_coresight_soft_rst_req : 1;  /* bit[5]   : Coresight 系统软复位请求，高有效 */
        unsigned int  ispa7_dbgrstreq              : 1;  /* bit[6]   : 除Debug APB、CTI和CTM外所有逻辑复位请求，电平复位，高有效 */
        unsigned int  reserved                     : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISPA7_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_por_rst_req_START        (0)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_por_rst_req_END          (0)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_rst_software_req_START        (1)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_rst_software_req_END          (1)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_rst_software_req_START   (2)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_rst_software_req_END     (2)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_debug_all_rst_req_START       (3)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_debug_all_rst_req_END         (3)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_debug_rst_req_START      (4)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_debug_rst_req_END        (4)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_coresight_soft_rst_req_START  (5)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_coresight_soft_rst_req_END    (5)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_dbgrstreq_START               (6)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_dbgrstreq_END                 (6)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISPA7_STAT_UNION
 结构说明  : ISPA7_STAT 寄存器结构定义。地址偏移量:0x354，初值:0x00000000，宽度:32
 寄存器说明: ISPA7状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_standbywfi   : 1;  /* bit[0]   : 指示CPU是否处于WFI状态 */
        unsigned int  ispa7_standbywfe   : 1;  /* bit[1]   : 指示CPU是否处于WFE状态 */
        unsigned int  ispa7_smpnamp      : 1;  /* bit[2]   : 指示CPU核处于SMP或AMP模式 */
        unsigned int  ispa7_standbywfil2 : 1;  /* bit[3]   : 指示L2是否处于WFI状态 */
        unsigned int  ispa7_dbgack       : 1;  /* bit[4]   : A7 core进入debug状态后的状态指示，高有效。当任一core进入debug状态时，该信号有效 */
        unsigned int  reserved           : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISPA7_STAT_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfi_START    (0)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfi_END      (0)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfe_START    (1)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfe_END      (1)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_smpnamp_START       (2)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_smpnamp_END         (2)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfil2_START  (3)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfil2_END    (3)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_dbgack_START        (4)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_dbgack_END          (4)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV0_UNION
 结构说明  : PERI_AUTODIV0 寄存器结构定义。地址偏移量:0x360，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp_div_auto_reduce_bypass : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                      0：不bypass；
                                                                      1：bypass。 */
        unsigned int  ivp_auto_waitcfg_in        : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  ivp_auto_waitcfg_out       : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  ivp_div_auto_cfg           : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                      6'h00:1；
                                                                      6'h01:2；
                                                                      …
                                                                      6'h3F:64； */
        unsigned int  ivp_pwaitmode_bypass       : 1;  /* bit[27]   : dw_axi_m1_st 是否加入自动降频判断条件：
                                                                      1'h0:加入；
                                                                      1'h1:不加入； */
        unsigned int  ivp_dw_axi_m1_st_bypass    : 1;  /* bit[28]   : dw_axi_m1_st 是否加入自动降频判断条件：
                                                                      1'h0:加入；
                                                                      1'h1:不加入； */
        unsigned int  ivp_dw_axi_m2_st_bypass    : 1;  /* bit[29]   : dw_axi_m2_st 是否加入自动降频判断条件：
                                                                      1'h0:加入；
                                                                      1'h1:不加入； */
        unsigned int  reserved                   : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV0_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_pwaitmode_bypass_START        (27)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_pwaitmode_bypass_END          (27)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m1_st_bypass_START     (28)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m1_st_bypass_END       (28)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m2_st_bypass_START     (29)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m2_st_bypass_END       (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV1_UNION
 结构说明  : PERI_AUTODIV1 寄存器结构定义。地址偏移量:0x364，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_div_auto_reduce_bypass : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                        0：不bypass；
                                                                        1：bypass。 */
        unsigned int  ispa7_auto_waitcfg_in        : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  ispa7_auto_waitcfg_out       : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  ispa7_div_auto_cfg           : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                        6'h00:1；
                                                                        6'h01:2；
                                                                        …
                                                                        6'h3F:64； */
        unsigned int  reserved                     : 5;  /* bit[27-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV1_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_cfg_END              (26)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV2_UNION
 结构说明  : PERI_AUTODIV2 寄存器结构定义。地址偏移量:0x368，初值:0x0BE07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  venc_div_auto_reduce_bypass : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                       0：不bypass；
                                                                       1：bypass。 */
        unsigned int  venc_auto_waitcfg_in        : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  venc_auto_waitcfg_out       : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  venc_div_auto_cfg           : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                       6'h00:1；
                                                                       6'h01:2；
                                                                       …
                                                                       6'h3F:64； */
        unsigned int  venc_vcodecbus_cfg_bypass   : 1;  /* bit[27]   : cfg 是否加入自动降频判断条件：
                                                                       1'h0:加入；
                                                                       1'h1:不加入； */
        unsigned int  reserved                    : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV2_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_vcodecbus_cfg_bypass_START    (27)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_vcodecbus_cfg_bypass_END      (27)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV3_UNION
 结构说明  : PERI_AUTODIV3 寄存器结构定义。地址偏移量:0x36C，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vdec_div_auto_reduce_bypass : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                       0：不bypass；
                                                                       1：bypass。 */
        unsigned int  vdec_auto_waitcfg_in        : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  vdec_auto_waitcfg_out       : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  vdec_div_auto_cfg           : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                       6'h00:1；
                                                                       6'h01:2；
                                                                       …
                                                                       6'h3F:64； */
        unsigned int  vdec_vcodecbus_cfg_bypass   : 1;  /* bit[27]   : cfg 是否加入自动降频判断条件：
                                                                       1'h0:加入；
                                                                       1'h1:不加入； */
        unsigned int  reserved                    : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV3_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_vcodecbus_cfg_bypass_START    (27)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_vcodecbus_cfg_bypass_END      (27)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV4_UNION
 结构说明  : PERI_AUTODIV4 寄存器结构定义。地址偏移量:0x370，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vivobus_div_auto_reduce_bypass : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                          0：不bypass；
                                                                          1：bypass。 */
        unsigned int  vivobus_auto_waitcfg_in        : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  vivobus_auto_waitcfg_out       : 9;  /* bit[11-19]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  vivobus_ispa7_wfi_bypass       : 1;  /* bit[20]   : ispa7_wfi 是否加入vivobus自动降频判断条件：
                                                                          1'h0:加入；
                                                                          1'h1:不加入； */
        unsigned int  vivobus_div_auto_cfg           : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                          6'h00:1；
                                                                          6'h01:2；
                                                                          …
                                                                          6'h3F:64； */
        unsigned int  vivobus_vivo_cfg_bypass        : 1;  /* bit[27]   : cfg 是否加入自动降频判断条件：
                                                                          1'h0:加入；
                                                                          1'h1:不加入； */
        unsigned int  vivobus_dss0_bypass            : 1;  /* bit[28]   : dss0 是否加入自动降频判断条件： */
        unsigned int  vivobus_dss1_bypass            : 1;  /* bit[29]   : dss1 是否加入自动降频判断条件： */
        unsigned int  vivobus_isp_bypass             : 1;  /* bit[30]   : isp 是否加入自动降频判断条件： */
        unsigned int  vivobus_ispa7_bypass           : 1;  /* bit[31]   : iaps7状态是否加入自动降频判断条件：
                                                                          1'h0:加入；
                                                                          1'h1:不加入； */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV4_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_out_END          (19)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_wfi_bypass_START        (20)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_wfi_bypass_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_vivo_cfg_bypass_START         (27)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_vivo_cfg_bypass_END           (27)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss0_bypass_START             (28)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss0_bypass_END               (28)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss1_bypass_START             (29)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss1_bypass_END               (29)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_isp_bypass_START              (30)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_isp_bypass_END                (30)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_bypass_START            (31)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_bypass_END              (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV5_UNION
 结构说明  : PERI_AUTODIV5 寄存器结构定义。地址偏移量:0x374，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vcodecbus_div_auto_reduce_bypass : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                            0：不bypass；
                                                                            1：bypass。 */
        unsigned int  vcodecbus_auto_waitcfg_in        : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  vcodecbus_auto_waitcfg_out       : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  vcodecbus_div_auto_cfg           : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                            6'h00:1；
                                                                            6'h01:2；
                                                                            …
                                                                            6'h3F:64； */
        unsigned int  vcodecbus_vcodec_cfg_bypass      : 1;  /* bit[27]   : cfg 是否加入自动降频判断条件：
                                                                            1'h0:加入；
                                                                            1'h1:不加入； */
        unsigned int  reserved_0                       : 1;  /* bit[28]   : 保留。 */
        unsigned int  reserved_1                       : 1;  /* bit[29]   : 保留。 */
        unsigned int  vcodecbus_venc_bypass            : 1;  /* bit[30]   : venc 是否加入自动降频判断条件： */
        unsigned int  vcodecbus_vdec_bypass            : 1;  /* bit[31]   : vdec状态是否加入自动降频判断条件：
                                                                            1'h0:加入；
                                                                            1'h1:不加入； */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV5_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vcodec_cfg_bypass_START       (27)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vcodec_cfg_bypass_END         (27)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_venc_bypass_START             (30)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_venc_bypass_END               (30)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vdec_bypass_START             (31)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vdec_bypass_END               (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV6_UNION
 结构说明  : PERI_AUTODIV6 寄存器结构定义。地址偏移量:0x378，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sysbus_div_auto_reduce_bypass_lpm3 : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                              0：不bypass；
                                                                              1：bypass。 */
        unsigned int  sysbus_auto_waitcfg_in             : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  sysbus_auto_waitcfg_out            : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  sysbus_div_auto_cfg                : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                              6'h00:1；
                                                                              6'h01:2；
                                                                              …
                                                                              6'h3F:64； */
        unsigned int  reserved                           : 5;  /* bit[27-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV6_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_reduce_bypass_lpm3_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_reduce_bypass_lpm3_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_in_START              (1)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_in_END                (10)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_out_START             (11)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_out_END               (20)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_cfg_START                 (21)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_cfg_END                   (26)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV7_UNION
 结构说明  : PERI_AUTODIV7 寄存器结构定义。地址偏移量:0x37C，初值:0x00000000，宽度:32
 寄存器说明: 外设自动降频控制寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sysbus_aobus_bypass         : 1;  /* bit[0]    : aobus 是否加入自动降频判断条件：
                                                                       1'h0:加入；
                                                                       1'h1:不加入； */
        unsigned int  sysbus_top_cssys_bypass     : 1;  /* bit[1]    :  */
        unsigned int  sysbus_perf_stat_bypass     : 1;  /* bit[2]    :  */
        unsigned int  sysbus_usb3_bypass          : 1;  /* bit[3]    :  */
        unsigned int  sysbus_secp_bypass          : 1;  /* bit[4]    :  */
        unsigned int  sysbus_secs_bypass          : 1;  /* bit[5]    :  */
        unsigned int  sysbus_socp_bypass          : 1;  /* bit[6]    :  */
        unsigned int  sysbus_dmac_mst_bypass      : 1;  /* bit[7]    :  */
        unsigned int  sysbus_emmc0_bypass         : 1;  /* bit[8]    :  */
        unsigned int  sysbus_emmc1_bypass         : 1;  /* bit[9]    :  */
        unsigned int  sysbus_mmc1bus_bypass       : 1;  /* bit[10]   :  */
        unsigned int  reserved_0                  : 1;  /* bit[11]   :  */
        unsigned int  sysbus_cci2sysbus_bypass    : 1;  /* bit[12]   :  */
        unsigned int  sysbus_modem_mst_bypass     : 1;  /* bit[13]   :  */
        unsigned int  reserved_1                  : 1;  /* bit[14]   :  */
        unsigned int  sysbus_djtag_mst_bypass     : 1;  /* bit[15]   :  */
        unsigned int  sysbus_lpm3_mst_bypass      : 1;  /* bit[16]   :  */
        unsigned int  sysbus_a72cfg_bypass        : 1;  /* bit[17]   :  */
        unsigned int  sysbus_ivp32_mst_bypass     : 1;  /* bit[18]   :  */
        unsigned int  sysbus_mmc0bus_sdio0_bypass : 1;  /* bit[19]   :  */
        unsigned int  reserved_2                  : 6;  /* bit[20-25]:  */
        unsigned int  cfgbus_vivo_cfg_bypass      : 1;  /* bit[26]   :  */
        unsigned int  cfgbus_vcodec_cfg_bypass    : 1;  /* bit[27]   :  */
        unsigned int  reserved_3                  : 1;  /* bit[28]   :  */
        unsigned int  cfgbus_djtag_mst_bypass     : 1;  /* bit[29]   :  */
        unsigned int  cfgbus_lpm3_mst_bypass      : 1;  /* bit[30]   :  */
        unsigned int  cfgbus_a7tocfg_bypass       : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV7_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_aobus_bypass_START          (0)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_aobus_bypass_END            (0)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_top_cssys_bypass_START      (1)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_top_cssys_bypass_END        (1)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_perf_stat_bypass_START      (2)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_perf_stat_bypass_END        (2)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_usb3_bypass_START           (3)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_usb3_bypass_END             (3)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secp_bypass_START           (4)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secp_bypass_END             (4)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secs_bypass_START           (5)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secs_bypass_END             (5)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_socp_bypass_START           (6)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_socp_bypass_END             (6)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_dmac_mst_bypass_START       (7)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_dmac_mst_bypass_END         (7)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc0_bypass_START          (8)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc0_bypass_END            (8)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc1_bypass_START          (9)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc1_bypass_END            (9)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc1bus_bypass_START        (10)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc1bus_bypass_END          (10)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_cci2sysbus_bypass_START     (12)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_cci2sysbus_bypass_END       (12)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_modem_mst_bypass_START      (13)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_modem_mst_bypass_END        (13)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_djtag_mst_bypass_START      (15)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_djtag_mst_bypass_END        (15)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_lpm3_mst_bypass_START       (16)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_lpm3_mst_bypass_END         (16)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_a72cfg_bypass_START         (17)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_a72cfg_bypass_END           (17)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_ivp32_mst_bypass_START      (18)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_ivp32_mst_bypass_END        (18)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc0bus_sdio0_bypass_START  (19)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc0bus_sdio0_bypass_END    (19)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vivo_cfg_bypass_START       (26)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vivo_cfg_bypass_END         (26)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vcodec_cfg_bypass_START     (27)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vcodec_cfg_bypass_END       (27)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_djtag_mst_bypass_START      (29)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_djtag_mst_bypass_END        (29)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_lpm3_mst_bypass_START       (30)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_lpm3_mst_bypass_END         (30)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_a7tocfg_bypass_START        (31)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_a7tocfg_bypass_END          (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV8_UNION
 结构说明  : PERI_AUTODIV8 寄存器结构定义。地址偏移量:0x380，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器8。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfgbus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                                   0：不bypass；
                                                                                   1：bypass。 */
        unsigned int  cfgbus_auto_waitcfg_in                  : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  cfgbus_auto_waitcfg_out                 : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  cfgbus_div_auto_cfg                     : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                                   6'h00:1；
                                                                                   6'h01:2；
                                                                                   …
                                                                                   6'h3F:64； */
        unsigned int  cfgbus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[27]   : sysbus降频时cfgbus是否自动退出自动降频bypass控制（sysbus自动降频时cfgbus是否自动退出自动降频）：
                                                                                   1'h0:不bypass（退出）；
                                                                                   1'h1:bypass（不退出）； */
        unsigned int  reserved                                : 4;  /* bit[28-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV8_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_out_END                    (20)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_cfg_START                      (21)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_cfg_END                        (26)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_sysbus_relate_auto_reduce_bypass_START  (27)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_sysbus_relate_auto_reduce_bypass_END    (27)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV9_UNION
 结构说明  : PERI_AUTODIV9 寄存器结构定义。地址偏移量:0x384，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器9。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmabus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                                   0：不bypass；
                                                                                   1：bypass。 */
        unsigned int  dmabus_auto_waitcfg_in                  : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  dmabus_auto_waitcfg_out                 : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  dmabus_div_auto_cfg                     : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                                   6'h00:1；
                                                                                   6'h01:2；
                                                                                   …
                                                                                   6'h3F:64； */
        unsigned int  dmabus_dmac_mst_bypass                  : 1;  /* bit[27]   : dma_mst 是否加入自动降频判断条件：
                                                                                   1'h0:加入；
                                                                                   1'h1:不加入； */
        unsigned int  dmabus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[28]   : sysbus降频时dmabus是否自动退出自动降频bypass控制（sysbus自动降频时dmabus是否自动退出自动降频）：
                                                                                   1'h0:不bypass（退出）；
                                                                                   1'h1:bypass（不退出）； */
        unsigned int  reserved                                : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV9_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_out_END                    (20)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_cfg_START                      (21)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_cfg_END                        (26)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_dmac_mst_bypass_START                   (27)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_dmac_mst_bypass_END                     (27)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_sysbus_relate_auto_reduce_bypass_START  (28)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_sysbus_relate_auto_reduce_bypass_END    (28)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV10_UNION
 结构说明  : PERI_AUTODIV10 寄存器结构定义。地址偏移量:0x388，初值:0x01F07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器10。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbgbus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                                   0：不bypass；
                                                                                   1：bypass。 */
        unsigned int  dbgbus_auto_waitcfg_in                  : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  dbgbus_auto_waitcfg_out                 : 8;  /* bit[11-18]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  dbgbus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[19]   : sysbus降频时dbgbus是否自动退出自动降频bypass控制（sysbus自动降频时dbgbus是否自动退出自动降频）：
                                                                                   1'h0:不bypass（退出）；
                                                                                   1'h1:bypass（不退出）； */
        unsigned int  dbgbus_div_auto_cfg                     : 6;  /* bit[20-25]: 硬件自动降频倍数配置
                                                                                   6'h00:1；
                                                                                   6'h01:2；
                                                                                   …
                                                                                   6'h3F:64； */
        unsigned int  dbgbus_socp_bypass                      : 1;  /* bit[26]   : socp是否加入自动降频判断条件：
                                                                                   1'h0:加入；
                                                                                   1'h1:不加入； */
        unsigned int  dbgbus_secp_bypass                      : 1;  /* bit[27]   : secp是否加入自动降频判断条件：
                                                                                   1'h0:加入；
                                                                                   1'h1:不加入； */
        unsigned int  dbgbus_secs_bypass                      : 1;  /* bit[28]   : secs是否加入自动降频判断条件：
                                                                                   1'h0:加入；
                                                                                   1'h1:不加入； */
        unsigned int  dbgbus_usb3_bypass                      : 1;  /* bit[29]   : usb3是否加入自动降频判断条件：
                                                                                   1'h0:加入；
                                                                                   1'h1:不加入； */
        unsigned int  dbgbus_perf_stat_bypass                 : 1;  /* bit[30]   : perf_stat是否加入自动降频判断条件：
                                                                                   1'h0:加入；
                                                                                   1'h1:不加入； */
        unsigned int  dbgbus_top_cssys_bypass                 : 1;  /* bit[31]   : top_cssys状态是否加入自动降频判断条件：
                                                                                   1'h0:加入；
                                                                                   1'h1:不加入； */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV10_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_out_END                    (18)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_sysbus_relate_auto_reduce_bypass_START  (19)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_sysbus_relate_auto_reduce_bypass_END    (19)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_cfg_START                      (20)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_cfg_END                        (25)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_socp_bypass_START                       (26)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_socp_bypass_END                         (26)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secp_bypass_START                       (27)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secp_bypass_END                         (27)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secs_bypass_START                       (28)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secs_bypass_END                         (28)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_usb3_bypass_START                       (29)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_usb3_bypass_END                         (29)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_perf_stat_bypass_START                  (30)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_perf_stat_bypass_END                    (30)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_top_cssys_bypass_START                  (31)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_top_cssys_bypass_END                    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV11_UNION
 结构说明  : PERI_AUTODIV11 寄存器结构定义。地址偏移量:0x38C，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器11。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc0bus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                                     0：不bypass；
                                                                                     1：bypass。 */
        unsigned int  emmc0bus_auto_waitcfg_in                  : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  emmc0bus_auto_waitcfg_out                 : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  emmc0bus_div_auto_cfg                     : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                                     6'h00:1；
                                                                                     6'h01:2；
                                                                                     …
                                                                                     6'h3F:64； */
        unsigned int  emmc0bus_emm0_bypass                      : 1;  /* bit[27]   : emm0 是否加入自动降频判断条件：
                                                                                     1'h0:加入；
                                                                                     1'h1:不加入； */
        unsigned int  emmc0bus_emm1_bypass                      : 1;  /* bit[28]   : emm1 是否加入自动降频判断条件：
                                                                                     1'h0:加入；
                                                                                     1'h1:不加入； */
        unsigned int  emmc0bus_sdio_bypass                      : 1;  /* bit[29]   : sdio0 是否加入自动降频判断条件：
                                                                                     1'h0:加入；
                                                                                     1'h1:不加入； */
        unsigned int  emmc0bus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[30]   : sysbus降频时emmc0bus是否自动退出自动降频bypass控制（sysbus自动降频时emmc0bus是否自动退出自动降频）：
                                                                                     1'h0:不bypass（退出）；
                                                                                     1'h1:bypass（不退出）； */
        unsigned int  reserved                                  : 1;  /* bit[31]   : 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV11_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_out_END                    (20)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_cfg_START                      (21)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_cfg_END                        (26)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm0_bypass_START                       (27)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm0_bypass_END                         (27)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm1_bypass_START                       (28)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm1_bypass_END                         (28)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sdio_bypass_START                       (29)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sdio_bypass_END                         (29)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sysbus_relate_auto_reduce_bypass_START  (30)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sysbus_relate_auto_reduce_bypass_END    (30)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV12_UNION
 结构说明  : PERI_AUTODIV12 寄存器结构定义。地址偏移量:0x390，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器12。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc1bus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                                     0：不bypass；
                                                                                     1：bypass。 */
        unsigned int  emmc1bus_auto_waitcfg_in                  : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  emmc1bus_auto_waitcfg_out                 : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  emmc1bus_div_auto_cfg                     : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                                     6'h00:1；
                                                                                     6'h01:2；
                                                                                     …
                                                                                     6'h3F:64； */
        unsigned int  emmc1bus_other_bypass                     : 1;  /* bit[27]   : emmc1bus 是否加入自动降频判断条件：
                                                                                     1'h0:加入；
                                                                                     1'h1:不加入； */
        unsigned int  emmc1bus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[28]   : sysbus降频时emmc1bus是否自动退出自动降频bypass控制（sysbus自动降频时emmc1bus是否自动退出自动降频）：
                                                                                     1'h0:不bypass（退出）；
                                                                                     1'h1:bypass（不退出）； */
        unsigned int  reserved                                  : 3;  /* bit[29-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV12_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_out_END                    (20)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_cfg_START                      (21)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_cfg_END                        (26)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_other_bypass_START                      (27)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_other_bypass_END                        (27)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_sysbus_relate_auto_reduce_bypass_START  (28)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_sysbus_relate_auto_reduce_bypass_END    (28)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV13_UNION
 结构说明  : PERI_AUTODIV13 寄存器结构定义。地址偏移量:0x394，初值:0x03E07BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器13。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpmcu_div_auto_reduce_bypass : 1;  /* bit[0]    : 硬件自动降频功能bypass配置：
                                                                        0：不bypass；
                                                                        1：bypass。 */
        unsigned int  lpmcu_auto_waitcfg_in        : 10; /* bit[1-10] : 硬件进入自动降频IDLE等待时钟周期配置 */
        unsigned int  lpmcu_auto_waitcfg_out       : 10; /* bit[11-20]: 硬件退出自动降频IDLE等待时钟周期配置 */
        unsigned int  lpmcu_div_auto_cfg           : 6;  /* bit[21-26]: 硬件自动降频倍数配置
                                                                        6'h00:1；
                                                                        6'h01:2；
                                                                        …
                                                                        6'h3F:64； */
        unsigned int  reserved                     : 5;  /* bit[27-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV13_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_cfg_END              (26)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV14_UNION
 结构说明  : PERI_AUTODIV14 寄存器结构定义。地址偏移量:0x398，初值:0x00007BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器14。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_auto_swtotcxo_bypass : 1;  /* bit[0]    : 硬件自动切换tcxo功能bypass配置：
                                                                    0：不bypass；
                                                                    1：bypass。 */
        unsigned int  a57_auto_waitcfg_in      : 10; /* bit[1-10] : 硬件进入自动切换tcxo等待时钟周期配置 */
        unsigned int  a57_auto_waitcfg_out     : 10; /* bit[11-20]: 硬件退出自动切换tcxo等待时钟周期配置 */
        unsigned int  reserved                 : 11; /* bit[21-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV14_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_swtotcxo_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_swtotcxo_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_in_START       (1)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_in_END         (10)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_out_START      (11)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_out_END        (20)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV15_UNION
 结构说明  : PERI_AUTODIV15 寄存器结构定义。地址偏移量:0x39C，初值:0x00007BFF，宽度:32
 寄存器说明: 外设自动降频控制寄存器15。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_auto_swtotcxo_bypass : 1;  /* bit[0]    : 硬件自动切换tcxo功能bypass配置：
                                                                    0：不bypass；
                                                                    1：bypass。 */
        unsigned int  a53_auto_waitcfg_in      : 10; /* bit[1-10] : 硬件进入自动切换tcxo等待时钟周期配置 */
        unsigned int  a53_auto_waitcfg_out     : 10; /* bit[11-20]: 硬件退出自动切换tcxo等待时钟周期配置 */
        unsigned int  reserved                 : 11; /* bit[21-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV15_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_swtotcxo_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_swtotcxo_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_in_START       (1)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_in_END         (10)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_out_START      (11)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_out_END        (20)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV_ACPU_UNION
 结构说明  : PERI_AUTODIV_ACPU 寄存器结构定义。地址偏移量:0x404，初值:0x00000000，宽度:32
 寄存器说明: 外设自动降频控制寄存器ACPU。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc1bus_div_auto_reduce_bypass_acpu : 1;  /* bit[0]    : acpu配置投票是否bypass 总线自动降频 */
        unsigned int  emmc0bus_div_auto_reduce_bypass_acpu : 1;  /* bit[1]    :  */
        unsigned int  dbgbus_div_auto_reduce_bypass_acpu   : 1;  /* bit[2]    :  */
        unsigned int  dmabus_div_auto_reduce_bypass_acpu   : 1;  /* bit[3]    :  */
        unsigned int  cfgbus_div_auto_reduce_bypass_acpu   : 1;  /* bit[4]    :  */
        unsigned int  sysbus_div_auto_reduce_bypass_acpu   : 1;  /* bit[5]    :  */
        unsigned int  reserved                             : 10; /* bit[6-15] : 保留。 */
        unsigned int  autodivmasken                        : 16; /* bit[16-31]: peri_autodiv_acpu每个比特位的使能位：
                                                                                只有当autodivmasken对应的比特位为1'b1，peri_autodiv_acpu相应的比特位才起作用。autodivmasken[0]就是peri_autodiv_acpu[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV_ACPU_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc1bus_div_auto_reduce_bypass_acpu_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc1bus_div_auto_reduce_bypass_acpu_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc0bus_div_auto_reduce_bypass_acpu_START  (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc0bus_div_auto_reduce_bypass_acpu_END    (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dbgbus_div_auto_reduce_bypass_acpu_START    (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dbgbus_div_auto_reduce_bypass_acpu_END      (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dmabus_div_auto_reduce_bypass_acpu_START    (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dmabus_div_auto_reduce_bypass_acpu_END      (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_cfgbus_div_auto_reduce_bypass_acpu_START    (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_cfgbus_div_auto_reduce_bypass_acpu_END      (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_sysbus_div_auto_reduce_bypass_acpu_START    (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_sysbus_div_auto_reduce_bypass_acpu_END      (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_autodivmasken_START                         (16)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_autodivmasken_END                           (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERI_AUTODIV_MCPU_UNION
 结构说明  : PERI_AUTODIV_MCPU 寄存器结构定义。地址偏移量:0x408，初值:0x00000000，宽度:32
 寄存器说明: 外设自动降频控制寄存器MCPU。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc1bus_div_auto_reduce_bypass_mcpu : 1;  /* bit[0]    : mcpu配置投票是否bypass 总线自动降频 */
        unsigned int  emmc0bus_div_auto_reduce_bypass_mcpu : 1;  /* bit[1]    :  */
        unsigned int  dbgbus_div_auto_reduce_bypass_mcpu   : 1;  /* bit[2]    :  */
        unsigned int  dmabus_div_auto_reduce_bypass_mcpu   : 1;  /* bit[3]    :  */
        unsigned int  cfgbus_div_auto_reduce_bypass_mcpu   : 1;  /* bit[4]    :  */
        unsigned int  sysbus_div_auto_reduce_bypass_mcpu   : 1;  /* bit[5]    :  */
        unsigned int  reserved                             : 10; /* bit[6-15] :  */
        unsigned int  autodivmasken                        : 16; /* bit[16-31]: peri_autodiv_mcpu每个比特位的使能位：
                                                                                只有当autodivmasken对应的比特位为1'b1，peri_autodiv_mcpu相应的比特位才起作用。autodivmasken[0]就是peri_autodiv_mcpu[0]的mask使能位。写1有效。 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV_MCPU_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc1bus_div_auto_reduce_bypass_mcpu_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc1bus_div_auto_reduce_bypass_mcpu_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc0bus_div_auto_reduce_bypass_mcpu_START  (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc0bus_div_auto_reduce_bypass_mcpu_END    (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dbgbus_div_auto_reduce_bypass_mcpu_START    (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dbgbus_div_auto_reduce_bypass_mcpu_END      (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dmabus_div_auto_reduce_bypass_mcpu_START    (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dmabus_div_auto_reduce_bypass_mcpu_END      (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_cfgbus_div_auto_reduce_bypass_mcpu_START    (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_cfgbus_div_auto_reduce_bypass_mcpu_END      (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_sysbus_div_auto_reduce_bypass_mcpu_START    (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_sysbus_div_auto_reduce_bypass_mcpu_END      (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_autodivmasken_START                         (16)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_autodivmasken_END                           (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PEREN6_UNION
 结构说明  : PEREN6 寄存器结构定义。地址偏移量:0x410，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_autodiv_ivp       : 1;  /* bit[0]    : 外设时钟使能控制：
                                                                    0：写0无效果；
                                                                    1：使能IP时钟。 */
        unsigned int  gt_clk_autodiv_ispa7     : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_autodiv_venc      : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_autodiv_vdec      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_autodiv_vivobus   : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_autodiv_vcodecbus : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_autodiv_sysbus    : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_autodiv_cfgbus    : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_autodiv_dmabus    : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_autodiv_dbgbus    : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_autodiv_emmc0bus  : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_autodiv_emmc1bus  : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_autodiv_lpmcu     : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_autodiv_a57       : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_autodiv_a53       : 1;  /* bit[14]   :  */
        unsigned int  reserved                 : 17; /* bit[15-31]: 外设时钟使能控制：
                                                                    0：写0无效果；
                                                                    1：使能IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PEREN6_UNION;
#endif
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ivp_START        (0)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ivp_END          (0)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ispa7_START      (1)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ispa7_END        (1)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_venc_START       (2)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_venc_END         (2)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vdec_START       (3)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vdec_END         (3)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vivobus_START    (4)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vivobus_END      (4)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vcodecbus_START  (5)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vcodecbus_END    (5)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_sysbus_START     (6)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_sysbus_END       (6)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_cfgbus_START     (7)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_cfgbus_END       (7)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dmabus_START     (8)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dmabus_END       (8)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dbgbus_START     (9)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dbgbus_END       (9)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc0bus_START   (10)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc0bus_END     (10)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc1bus_START   (11)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc1bus_END     (11)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_lpmcu_START      (12)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_lpmcu_END        (12)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a57_START        (13)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a57_END          (13)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a53_START        (14)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a53_END          (14)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERDIS6_UNION
 结构说明  : PERDIS6 寄存器结构定义。地址偏移量:0x414，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_autodiv_ivp       : 1;  /* bit[0]    : 外设时钟禁止控制：
                                                                    0：写0无效果；
                                                                    1：禁止IP时钟。 */
        unsigned int  gt_clk_autodiv_ispa7     : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_autodiv_venc      : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_autodiv_vdec      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_autodiv_vivobus   : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_autodiv_vcodecbus : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_autodiv_sysbus    : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_autodiv_cfgbus    : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_autodiv_dmabus    : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_autodiv_dbgbus    : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_autodiv_emmc0bus  : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_autodiv_emmc1bus  : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_autodiv_lpmcu     : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_autodiv_a57       : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_autodiv_a53       : 1;  /* bit[14]   :  */
        unsigned int  reserved                 : 17; /* bit[15-31]: 外设时钟禁止控制：
                                                                    0：写0无效果；
                                                                    1：禁止IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PERDIS6_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ivp_START        (0)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ivp_END          (0)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ispa7_START      (1)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ispa7_END        (1)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_venc_START       (2)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_venc_END         (2)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vdec_START       (3)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vdec_END         (3)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vivobus_START    (4)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vivobus_END      (4)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vcodecbus_START  (5)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vcodecbus_END    (5)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_sysbus_START     (6)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_sysbus_END       (6)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_cfgbus_START     (7)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_cfgbus_END       (7)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dmabus_START     (8)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dmabus_END       (8)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dbgbus_START     (9)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dbgbus_END       (9)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc0bus_START   (10)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc0bus_END     (10)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc1bus_START   (11)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc1bus_END     (11)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_lpmcu_START      (12)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_lpmcu_END        (12)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a57_START        (13)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a57_END          (13)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a53_START        (14)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a53_END          (14)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCLKEN6_UNION
 结构说明  : PERCLKEN6 寄存器结构定义。地址偏移量:0x418，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能状态寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_autodiv_ivp       : 1;  /* bit[0]    : 外设时钟使能状态：
                                                                    0：IP时钟使能撤销状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_autodiv_ispa7     : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_autodiv_venc      : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_autodiv_vdec      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_autodiv_vivobus   : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_autodiv_vcodecbus : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_autodiv_sysbus    : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_autodiv_cfgbus    : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_autodiv_dmabus    : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_autodiv_dbgbus    : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_autodiv_emmc0bus  : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_autodiv_emmc1bus  : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_autodiv_lpmcu     : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_autodiv_a57       : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_autodiv_a53       : 1;  /* bit[14]   :  */
        unsigned int  reserved                 : 17; /* bit[15-31]: 外设时钟使能状态：
                                                                    0：IP时钟使能撤销状态；
                                                                    1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERCLKEN6_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ivp_START        (0)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ivp_END          (0)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ispa7_START      (1)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ispa7_END        (1)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_venc_START       (2)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_venc_END         (2)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vdec_START       (3)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vdec_END         (3)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vivobus_START    (4)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vivobus_END      (4)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vcodecbus_START  (5)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vcodecbus_END    (5)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_sysbus_START     (6)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_sysbus_END       (6)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_cfgbus_START     (7)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_cfgbus_END       (7)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dmabus_START     (8)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dmabus_END       (8)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dbgbus_START     (9)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dbgbus_END       (9)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc0bus_START   (10)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc0bus_END     (10)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc1bus_START   (11)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc1bus_END     (11)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_lpmcu_START      (12)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_lpmcu_END        (12)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a57_START        (13)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a57_END          (13)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a53_START        (14)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a53_END          (14)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERSTAT6_UNION
 结构说明  : PERSTAT6 寄存器结构定义。地址偏移量:0x41C，初值:0xFFFF8000，宽度:32
 寄存器说明: 外设时钟最终状态寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_autodiv_ivp       : 1;  /* bit[0]    : 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
        unsigned int  gt_clk_autodiv_ispa7     : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_autodiv_venc      : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_autodiv_vdec      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_autodiv_vivobus   : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_autodiv_vcodecbus : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_autodiv_sysbus    : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_autodiv_cfgbus    : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_autodiv_dmabus    : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_autodiv_dbgbus    : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_autodiv_emmc0bus  : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_autodiv_emmc1bus  : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_autodiv_lpmcu     : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_autodiv_a57       : 1;  /* bit[13]   : 1：IP时钟使能状态。 */
        unsigned int  gt_clk_autodiv_a53       : 1;  /* bit[14]   : 0：IP时钟禁止状态； */
        unsigned int  reserved                 : 17; /* bit[15-31]: 外设时钟最终状态：
                                                                    0：IP时钟禁止状态；
                                                                    1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERSTAT6_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ivp_START        (0)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ivp_END          (0)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ispa7_START      (1)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ispa7_END        (1)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_venc_START       (2)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_venc_END         (2)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vdec_START       (3)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vdec_END         (3)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vivobus_START    (4)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vivobus_END      (4)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vcodecbus_START  (5)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vcodecbus_END    (5)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_sysbus_START     (6)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_sysbus_END       (6)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_cfgbus_START     (7)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_cfgbus_END       (7)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dmabus_START     (8)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dmabus_END       (8)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dbgbus_START     (9)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dbgbus_END       (9)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc0bus_START   (10)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc0bus_END     (10)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc1bus_START   (11)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc1bus_END     (11)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_lpmcu_START      (12)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_lpmcu_END        (12)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a57_START        (13)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a57_END          (13)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a53_START        (14)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a53_END          (14)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PEREN7_UNION
 结构说明  : PEREN7 寄存器结构定义。地址偏移量:0x420，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟使能寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_rs0   : 1;  /* bit[0]   : 外设时钟使能控制：
                                                              0：写0无效果；
                                                              1：使能IP时钟。 */
        unsigned int  gt_clk_ddrphy_rs1   : 1;  /* bit[1]   :  */
        unsigned int  gt_clk_ddrphy_rs2   : 1;  /* bit[2]   :  */
        unsigned int  gt_clk_ddrphy_rs3   : 1;  /* bit[3]   :  */
        unsigned int  gt_clk_ddrphy_gt    : 1;  /* bit[4]   : ddrphy rs/phy 相关时钟总门控 */
        unsigned int  reserved_0          : 1;  /* bit[5]   :  */
        unsigned int  gt_clk_ddrphy_rsadd : 1;  /* bit[6]   :  */
        unsigned int  reserved_1          : 25; /* bit[7-31]: 外设时钟使能控制：
                                                              0：写0无效果；
                                                              1：使能IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PEREN7_UNION;
#endif
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs0_START    (0)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs0_END      (0)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs1_START    (1)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs1_END      (1)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs2_START    (2)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs2_END      (2)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs3_START    (3)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs3_END      (3)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_gt_START     (4)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_gt_END       (4)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rsadd_START  (6)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rsadd_END    (6)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERDIS7_UNION
 结构说明  : PERDIS7 寄存器结构定义。地址偏移量:0x424，初值:0x00000000，宽度:32
 寄存器说明: 外设时钟禁止寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_rs0   : 1;  /* bit[0]   : 外设时钟禁止控制：
                                                              0：写0无效果；
                                                              1：禁止IP时钟。 */
        unsigned int  gt_clk_ddrphy_rs1   : 1;  /* bit[1]   :  */
        unsigned int  gt_clk_ddrphy_rs2   : 1;  /* bit[2]   :  */
        unsigned int  gt_clk_ddrphy_rs3   : 1;  /* bit[3]   :  */
        unsigned int  gt_clk_ddrphy_gt    : 1;  /* bit[4]   : ddrphy rs/phy 相关时钟总门控 */
        unsigned int  reserved_0          : 1;  /* bit[5]   :  */
        unsigned int  gt_clk_ddrphy_rsadd : 1;  /* bit[6]   :  */
        unsigned int  reserved_1          : 25; /* bit[7-31]: 外设时钟禁止控制：
                                                              0：写0无效果；
                                                              1：禁止IP时钟。 */
    } reg;
} SOC_CRGPERIPH_PERDIS7_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs0_START    (0)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs0_END      (0)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs1_START    (1)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs1_END      (1)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs2_START    (2)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs2_END      (2)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs3_START    (3)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs3_END      (3)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_gt_START     (4)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_gt_END       (4)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rsadd_START  (6)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rsadd_END    (6)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERCLKEN7_UNION
 结构说明  : PERCLKEN7 寄存器结构定义。地址偏移量:0x428，初值:0x0000001F，宽度:32
 寄存器说明: 外设时钟使能状态寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_rs0   : 1;  /* bit[0]   : 外设时钟使能状态：
                                                              0：IP时钟使能撤销状态；
                                                              1：IP时钟使能状态。 */
        unsigned int  gt_clk_ddrphy_rs1   : 1;  /* bit[1]   :  */
        unsigned int  gt_clk_ddrphy_rs2   : 1;  /* bit[2]   :  */
        unsigned int  gt_clk_ddrphy_rs3   : 1;  /* bit[3]   :  */
        unsigned int  gt_clk_ddrphy_gt    : 1;  /* bit[4]   : ddrphy rs/phy 相关时钟总门控 */
        unsigned int  reserved_0          : 1;  /* bit[5]   :  */
        unsigned int  gt_clk_ddrphy_rsadd : 1;  /* bit[6]   :  */
        unsigned int  reserved_1          : 25; /* bit[7-31]: 外设时钟使能状态：
                                                              0：IP时钟使能撤销状态；
                                                              1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERCLKEN7_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs0_START    (0)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs0_END      (0)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs1_START    (1)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs1_END      (1)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs2_START    (2)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs2_END      (2)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs3_START    (3)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs3_END      (3)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_gt_START     (4)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_gt_END       (4)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rsadd_START  (6)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rsadd_END    (6)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_PERSTAT7_UNION
 结构说明  : PERSTAT7 寄存器结构定义。地址偏移量:0x42C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 外设时钟最终状态寄存器7。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_rs0 : 1;  /* bit[0]   : 外设时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
        unsigned int  gt_clk_ddrphy_rs1 : 1;  /* bit[1]   :  */
        unsigned int  gt_clk_ddrphy_rs2 : 1;  /* bit[2]   :  */
        unsigned int  gt_clk_ddrphy_rs3 : 1;  /* bit[3]   :  */
        unsigned int  gt_clk_ddrphy_gt  : 1;  /* bit[4]   : ddrphy rs/phy 相关时钟总门控 */
        unsigned int  reserved          : 27; /* bit[5-31]: 外设时钟最终状态：
                                                            0：IP时钟禁止状态；
                                                            1：IP时钟使能状态。 */
    } reg;
} SOC_CRGPERIPH_PERSTAT7_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs0_START  (0)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs0_END    (0)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs1_START  (1)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs1_END    (1)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs2_START  (2)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs2_END    (2)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs3_START  (3)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs3_END    (3)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_gt_START   (4)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_gt_END     (4)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_IVP_SEC_RSTEN_UNION
 结构说明  : IVP_SEC_RSTEN 寄存器结构定义。地址偏移量:0xC00，初值:0x00000000，宽度:32
 寄存器说明: IVP安全软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ivp32dsp_subsys_crg : 1;  /* bit[0]   : IP软复位使能：
                                                                     0：IP软复位使能状态不变；
                                                                     1：IP软复位使能。 */
        unsigned int  ip_rst_ivp32dsp_subsys     : 1;  /* bit[1]   :  */
        unsigned int  reserved                   : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_IVP_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_crg_START  (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_crg_END    (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_START      (1)
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_END        (1)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_IVP_SEC_RSTDIS_UNION
 结构说明  : IVP_SEC_RSTDIS 寄存器结构定义。地址偏移量:0xC04，初值:0x00000000，宽度:32
 寄存器说明: IVP安全软复位撤离寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ivp32dsp_subsys_crg : 1;  /* bit[0]   : IP软复位撤离：
                                                                     0：IP软复位使能状态不变；
                                                                     1：IP软复位撤离。 */
        unsigned int  ip_rst_ivp32dsp_subsys     : 1;  /* bit[1]   :  */
        unsigned int  reserved                   : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_IVP_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_crg_START  (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_crg_END    (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_START      (1)
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_END        (1)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_IVP_SEC_RSTSTAT_UNION
 结构说明  : IVP_SEC_RSTSTAT 寄存器结构定义。地址偏移量:0xC08，初值:0x00000003，宽度:32
 寄存器说明: IVP安全软复位使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ivp32dsp_subsys_crg : 1;  /* bit[0]   : IP软复位使能状态：
                                                                     0：IP处于复位撤离状态；
                                                                     1：IP处于软复位使能状态。 */
        unsigned int  ip_rst_ivp32dsp_subsys     : 1;  /* bit[1]   :  */
        unsigned int  reserved                   : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_IVP_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_crg_START  (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_crg_END    (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_START      (1)
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_END        (1)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISP_SEC_RSTEN_UNION
 结构说明  : ISP_SEC_RSTEN 寄存器结构定义。地址偏移量:0xC80，初值:0x00000000，宽度:32
 寄存器说明: ISP安全软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_isp      : 1;  /* bit[0]   : IP软复位使能：
                                                          0：IP软复位使能状态不变；
                                                          1：IP软复位使能。 */
        unsigned int  ip_arst_isp     : 1;  /* bit[1]   :  */
        unsigned int  ip_hrst_isp     : 1;  /* bit[2]   :  */
        unsigned int  ip_rst_ispa7cfg : 1;  /* bit[3]   :  */
        unsigned int  ip_rst_ispa7    : 1;  /* bit[4]   :  */
        unsigned int  reserved        : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISP_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_isp_START       (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_isp_END         (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_arst_isp_START      (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_arst_isp_END        (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_hrst_isp_START      (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_hrst_isp_END        (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7cfg_START  (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7cfg_END    (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7_START     (4)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7_END       (4)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISP_SEC_RSTDIS_UNION
 结构说明  : ISP_SEC_RSTDIS 寄存器结构定义。地址偏移量:0xC84，初值:0x00000000，宽度:32
 寄存器说明: ISP安全软复位撤离寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_isp      : 1;  /* bit[0]   : IP软复位撤离：
                                                          0：IP软复位使能状态不变；
                                                          1：IP软复位撤离。 */
        unsigned int  ip_arst_isp     : 1;  /* bit[1]   :  */
        unsigned int  ip_hrst_isp     : 1;  /* bit[2]   :  */
        unsigned int  ip_rst_ispa7cfg : 1;  /* bit[3]   :  */
        unsigned int  ip_rst_ispa7    : 1;  /* bit[4]   :  */
        unsigned int  reserved        : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISP_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_isp_START       (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_isp_END         (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_arst_isp_START      (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_arst_isp_END        (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_hrst_isp_START      (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_hrst_isp_END        (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7cfg_START  (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7cfg_END    (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7_START     (4)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7_END       (4)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISP_SEC_RSTSTAT_UNION
 结构说明  : ISP_SEC_RSTSTAT 寄存器结构定义。地址偏移量:0xC88，初值:0x0000001F，宽度:32
 寄存器说明: ISP安全软复位状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_isp      : 1;  /* bit[0]   : IP软复位使能状态：
                                                          0：IP处于复位撤离状态；
                                                          1：IP处于软复位使能状态。 */
        unsigned int  ip_arst_isp     : 1;  /* bit[1]   :  */
        unsigned int  ip_hrst_isp     : 1;  /* bit[2]   :  */
        unsigned int  ip_rst_ispa7cfg : 1;  /* bit[3]   :  */
        unsigned int  ip_rst_ispa7    : 1;  /* bit[4]   :  */
        unsigned int  reserved        : 27; /* bit[5-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISP_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_isp_START       (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_isp_END         (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_arst_isp_START      (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_arst_isp_END        (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_hrst_isp_START      (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_hrst_isp_END        (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7cfg_START  (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7cfg_END    (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7_START     (4)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7_END       (4)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_ISPA7_CTRL0_UNION
 结构说明  : ISPA7_CTRL0 寄存器结构定义。地址偏移量:0xC90，初值:0x00000284，宽度:32
 寄存器说明: ISPA7控制配置寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_cfgend       : 1;  /* bit[0]    : A7大小端配置:
                                                              0:小端
                                                              1:大端 */
        unsigned int  ispa7_vinithi      : 1;  /* bit[1]    : A7启动方式选择，每bit对应一个core：
                                                              0：从低位地址（0x00000000）启动
                                                              1：从高位地址（0xFFFF0000）启动 */
        unsigned int  ispa7_dbgpwrdup    : 1;  /* bit[2]    : CPU核是否上电的检查信号 */
        unsigned int  ispa7_l2rstdisable : 1;  /* bit[3]    : 复位阶段禁止L2 cache自动invalidate信号 */
        unsigned int  ispa7_l1rstdisable : 1;  /* bit[4]    : 复位阶段禁止L1 cache自动invalidate信号 */
        unsigned int  reserved_0         : 2;  /* bit[5-6]  : 保留。 */
        unsigned int  ispa7_tsel_a7      : 4;  /* bit[7-10] : A7 cpu内部memory速度调节信号 */
        unsigned int  ispa7_remap_enable : 1;  /* bit[11]   : A7 AXI master接口地址重映射使能信号 */
        unsigned int  ispa7_remap_offset : 18; /* bit[12-29]: A7 AXI master接口地址重映射offset设置 */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_ISPA7_CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_cfgend_START        (0)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_cfgend_END          (0)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_vinithi_START       (1)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_vinithi_END         (1)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_dbgpwrdup_START     (2)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_dbgpwrdup_END       (2)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l2rstdisable_START  (3)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l2rstdisable_END    (3)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l1rstdisable_START  (4)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l1rstdisable_END    (4)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_tsel_a7_START       (7)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_tsel_a7_END         (10)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_enable_START  (11)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_enable_END    (11)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_offset_START  (12)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_offset_END    (29)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MDM_SEC_RSTEN_UNION
 结构说明  : MDM_SEC_RSTEN 寄存器结构定义。地址偏移量:0xD00，初值:0x00000000，宽度:32
 寄存器说明: MODEM安全软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_modem : 1;  /* bit[0]   : IP软复位使能：
                                                       0：IP软复位使能状态不变；
                                                       1：IP软复位使能。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MDM_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_MDM_SEC_RSTEN_ip_rst_modem_START  (0)
#define SOC_CRGPERIPH_MDM_SEC_RSTEN_ip_rst_modem_END    (0)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MDM_SEC_RSTDIS_UNION
 结构说明  : MDM_SEC_RSTDIS 寄存器结构定义。地址偏移量:0xD04，初值:0x00000000，宽度:32
 寄存器说明: MODEM安全软复位撤离寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_modem : 1;  /* bit[0]   : IP软复位撤离：
                                                       0：IP软复位使能状态不变；
                                                       1：IP软复位撤离。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MDM_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_MDM_SEC_RSTDIS_ip_rst_modem_START  (0)
#define SOC_CRGPERIPH_MDM_SEC_RSTDIS_ip_rst_modem_END    (0)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MDM_SEC_RSTSTAT_UNION
 结构说明  : MDM_SEC_RSTSTAT 寄存器结构定义。地址偏移量:0xD08，初值:0x00000001，宽度:32
 寄存器说明: MODEM安全软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_modem : 1;  /* bit[0]   : IP软复位使能状态：
                                                       0：IP处于复位撤离状态；
                                                       1：IP处于软复位使能状态。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_MDM_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MDM_SEC_RSTSTAT_ip_rst_modem_START  (0)
#define SOC_CRGPERIPH_MDM_SEC_RSTSTAT_ip_rst_modem_END    (0)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_CTRL3_UNION
 结构说明  : A53_CTRL3 寄存器结构定义。地址偏移量:0xE00，初值:0x00000000，宽度:32
 寄存器说明: A53 CLUSTER控制配置寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_rvbaraddr0 : 32; /* bit[0-31]: AArch64模式下核0的向量表基地址。 */
    } reg;
} SOC_CRGPERIPH_A53_CTRL3_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL3_a53_rvbaraddr0_START  (0)
#define SOC_CRGPERIPH_A53_CTRL3_a53_rvbaraddr0_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_CTRL4_UNION
 结构说明  : A53_CTRL4 寄存器结构定义。地址偏移量:0xE04，初值:0x00000000，宽度:32
 寄存器说明: A53 CLUSTER控制配置寄存器4。。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_rvbaraddr1 : 32; /* bit[0-31]: AArch64模式下核1的向量表基地址。 */
    } reg;
} SOC_CRGPERIPH_A53_CTRL4_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL4_a53_rvbaraddr1_START  (0)
#define SOC_CRGPERIPH_A53_CTRL4_a53_rvbaraddr1_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_CTRL5_UNION
 结构说明  : A53_CTRL5 寄存器结构定义。地址偏移量:0xE08，初值:0x00000000，宽度:32
 寄存器说明: A53 CLUSTER控制配置寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_rvbaraddr2 : 32; /* bit[0-31]: AArch64模式下核2的向量表基地址。 */
    } reg;
} SOC_CRGPERIPH_A53_CTRL5_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL5_a53_rvbaraddr2_START  (0)
#define SOC_CRGPERIPH_A53_CTRL5_a53_rvbaraddr2_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_A53_CTRL6_UNION
 结构说明  : A53_CTRL6 寄存器结构定义。地址偏移量:0xE0C，初值:0x00000000，宽度:32
 寄存器说明: A53 CLUSTER控制配置寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_rvbaraddr3 : 32; /* bit[0-31]: AArch64模式下核3的向量表基地址。 */
    } reg;
} SOC_CRGPERIPH_A53_CTRL6_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL6_a53_rvbaraddr3_START  (0)
#define SOC_CRGPERIPH_A53_CTRL6_a53_rvbaraddr3_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_CTRL3_UNION
 结构说明  : MAIA_CTRL3 寄存器结构定义。地址偏移量:0xE10，初值:0x00000000，宽度:32
 寄存器说明: A57 CLUSTER控制配置寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_rvbaraddr0 : 32; /* bit[0-31]: AArch64模式下核0的向量表基地址。 */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL3_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL3_a57_rvbaraddr0_START  (0)
#define SOC_CRGPERIPH_MAIA_CTRL3_a57_rvbaraddr0_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_CTRL4_UNION
 结构说明  : MAIA_CTRL4 寄存器结构定义。地址偏移量:0xE14，初值:0x00000000，宽度:32
 寄存器说明: A57 CLUSTER控制配置寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_rvbaraddr1 : 32; /* bit[0-31]: AArch64模式下核1的向量表基地址。 */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL4_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL4_a57_rvbaraddr1_START  (0)
#define SOC_CRGPERIPH_MAIA_CTRL4_a57_rvbaraddr1_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_CTRL5_UNION
 结构说明  : MAIA_CTRL5 寄存器结构定义。地址偏移量:0xE1C，初值:0x00000000，宽度:32
 寄存器说明: A57 CLUSTER控制配置寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_rvbaraddr2 : 32; /* bit[0-31]: AArch64模式下核2的向量表基地址。 */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL5_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL5_a57_rvbaraddr2_START  (0)
#define SOC_CRGPERIPH_MAIA_CTRL5_a57_rvbaraddr2_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_MAIA_CTRL6_UNION
 结构说明  : MAIA_CTRL6 寄存器结构定义。地址偏移量:0xE18，初值:0x00000000，宽度:32
 寄存器说明: A57 CLUSTER控制配置寄存器6。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_rvbaraddr3 : 32; /* bit[0-31]: AArch64模式下核3的向量表基地址。 */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL6_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL6_a57_rvbaraddr3_START  (0)
#define SOC_CRGPERIPH_MAIA_CTRL6_a57_rvbaraddr3_END    (31)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_GENERAL_SEC_RSTEN_UNION
 结构说明  : GENERAL_SEC_RSTEN 寄存器结构定义。地址偏移量:0xE20，初值:0x00000000，宽度:32
 寄存器说明: 通用安全软复位使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_secs : 1;  /* bit[0]   : IP软复位使能：
                                                      0：IP软复位使能状态不变；
                                                      1：IP软复位使能。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_GENERAL_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_GENERAL_SEC_RSTEN_ip_rst_secs_START  (0)
#define SOC_CRGPERIPH_GENERAL_SEC_RSTEN_ip_rst_secs_END    (0)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_UNION
 结构说明  : GENERAL_SEC_RSTDIS 寄存器结构定义。地址偏移量:0xE24，初值:0x00000000，宽度:32
 寄存器说明: 通用安全软复位撤离寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_secs : 1;  /* bit[0]   : IP软复位撤离：
                                                      0：IP软复位使能状态不变；
                                                      1：IP软复位撤离。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_ip_rst_secs_START  (0)
#define SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_ip_rst_secs_END    (0)


/*****************************************************************************
 结构名    : SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_UNION
 结构说明  : GENERAL_SEC_RSTSTAT 寄存器结构定义。地址偏移量:0xE28，初值:0x00000001，宽度:32
 寄存器说明: 通用安全软复位使能状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_secs : 1;  /* bit[0]   : IP软复位使能状态：
                                                      0：IP处于复位撤离状态；
                                                      1：IP处于软复位使能状态。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_ip_rst_secs_START  (0)
#define SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_ip_rst_secs_END    (0)






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

#endif /* end of soc_crgperiph_interface.h */
